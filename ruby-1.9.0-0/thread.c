/**********************************************************************

  thread.c -

  $Author: ko1 $
  $Date: 2007-12-25 22:14:23 +0900 (Tue, 25 Dec 2007) $

  Copyright (C) 2004-2007 Koichi Sasada

**********************************************************************/

/*
  YARV Thread Desgin

  model 1: Userlevel Thread
    Same as traditional ruby thread.

  model 2: Native Thread with Giant VM lock
    Using pthread (or Windows thread) and Ruby threads run concurrent.

  model 3: Native Thread with fine grain lock
    Using pthread and Ruby threads run concurrent or parallel.

------------------------------------------------------------------------

  model 2:
    A thread has mutex (GVL: Global VM Lock) can run.  When thread
    scheduling, running thread release GVL.  If running thread
    try blocking operation, this thread must release GVL and another
    thread can continue this flow.  After blocking operation, thread
    must check interrupt (RUBY_VM_CHECK_INTS).

    Every VM can run parallel.

    Ruby threads are scheduled by OS thread scheduler.

------------------------------------------------------------------------

  model 3:
    Every threads run concurrent or parallel and to access shared object
    exclusive access control is needed.  For example, to access String
    object or Array object, fine grain lock must be locked every time.
 */


/* for model 2 */

#include "eval_intern.h"
#include "vm.h"
#include "gc.h"

#ifndef THREAD_DEBUG
#define THREAD_DEBUG 0
#endif

VALUE rb_cMutex;
VALUE rb_cBarrier;

static void sleep_timeval(rb_thread_t *th, struct timeval time);
static void sleep_wait_for_interrupt(rb_thread_t *th, double sleepsec);
static void sleep_forever(rb_thread_t *th);
static double timeofday(void);
struct timeval rb_time_interval(VALUE);
static int rb_thread_dead(rb_thread_t *th);

void rb_signal_exec(rb_thread_t *th, int sig);
void rb_disable_interrupt(void);

static VALUE eKillSignal = INT2FIX(0);
static VALUE eTerminateSignal = INT2FIX(1);
static volatile int system_working = 1;

inline static void
st_delete_wrap(st_table * table, VALUE key)
{
    st_delete(table, (st_data_t *) & key, 0);
}

/********************************************************************************/

#define THREAD_SYSTEM_DEPENDENT_IMPLEMENTATION

static void set_unblock_function(rb_thread_t *th, rb_unblock_function_t *func, void *ptr,
         rb_unblock_function_t **oldfunc, void **oldptr);

#define GVL_UNLOCK_BEGIN() do { \
  rb_thread_t *_th_stored = GET_THREAD(); \
  rb_gc_save_machine_context(_th_stored); \
  native_mutex_unlock(&_th_stored->vm->global_interpreter_lock)

#define GVL_UNLOCK_END() \
  native_mutex_lock(&_th_stored->vm->global_interpreter_lock); \
  rb_thread_set_current(_th_stored); \
} while(0)

#define BLOCKING_REGION(exec, ubf, ubfarg) do { \
    rb_thread_t *__th = GET_THREAD(); \
    int __prev_status = __th->status; \
    rb_unblock_function_t *__oldubf; \
    void *__oldubfarg; \
    set_unblock_function(__th, ubf, ubfarg, &__oldubf, &__oldubfarg); \
    __th->status = THREAD_STOPPED; \
    thread_debug("enter blocking region (%p)\n", __th); \
    GVL_UNLOCK_BEGIN(); {\
      exec; \
    } \
    GVL_UNLOCK_END(); \
    thread_debug("leave blocking region (%p)\n", __th); \
    remove_signal_thread_list(__th); \
    set_unblock_function(__th, __oldubf, __oldubfarg, 0, 0); \
    if (__th->status == THREAD_STOPPED) { \
  __th->status = __prev_status; \
    } \
    RUBY_VM_CHECK_INTS(); \
} while(0)

#if THREAD_DEBUG
void rb_thread_debug(const char *fmt, ...);

# if THREAD_DEBUG < 0
static int rb_thread_debug_enabled;

static VALUE
rb_thread_s_debug(void)
{
    return INT2NUM(rb_thread_debug_enabled);
}

static VALUE
rb_thread_s_debug_set(VALUE self, VALUE val)
{
    rb_thread_debug_enabled = RTEST(val);
    return val;
}
# else
# define rb_thread_debug_enabled THREAD_DEBUG
# endif
#define thread_debug rb_thread_debug
#else
#define thread_debug if(0)printf
#endif

#ifndef __ia64
#define thread_start_func_2(th, st, rst) thread_start_func_2(th, st)
#endif
NOINLINE(static int thread_start_func_2(rb_thread_t *th, VALUE *stack_start,
          VALUE *register_stack_start));

#if   defined(_WIN32)
#include "thread_win32.c"

#define DEBUG_OUT() \
  WaitForSingleObject(&debug_mutex, INFINITE); \
  printf("%p - %s", GetCurrentThreadId(), buf); \
  fflush(stdout); \
  ReleaseMutex(&debug_mutex);

#elif defined(HAVE_PTHREAD_H)
#include "thread_pthread.c"

#define DEBUG_OUT() \
  pthread_mutex_lock(&debug_mutex); \
  printf("%p - %s", pthread_self(), buf); \
  fflush(stdout); \
  pthread_mutex_unlock(&debug_mutex);

#else
#error "unsupported thread type"
#endif

#if THREAD_DEBUG
static int debug_mutex_initialized = 1;
static rb_thread_lock_t debug_mutex;

void
rb_thread_debug(const char *fmt, ...)
{
    va_list args;
    char buf[BUFSIZ];

    if (!rb_thread_debug_enabled) return;

    if (debug_mutex_initialized == 1) {
  debug_mutex_initialized = 0;
  native_mutex_initialize(&debug_mutex);
    }

    va_start(args, fmt);
    vsnprintf(buf, BUFSIZ, fmt, args);
    va_end(args);

    DEBUG_OUT();
}
#endif


static void
set_unblock_function(rb_thread_t *th, rb_unblock_function_t *func, void *arg,
         rb_unblock_function_t **oldfunc, void **oldarg)
{
  check_ints:
    RUBY_VM_CHECK_INTS(); /* check signal or so */
    native_mutex_lock(&th->interrupt_lock);
    if (th->interrupt_flag) {
  native_mutex_unlock(&th->interrupt_lock);
  goto check_ints;
    }
    else {
  if (oldfunc) *oldfunc = th->unblock_function;
  if (oldarg) *oldarg = th->unblock_function_arg;
  th->unblock_function = func;
  th->unblock_function_arg = arg;
    }
    native_mutex_unlock(&th->interrupt_lock);
}

static void
rb_thread_interrupt(rb_thread_t *th)
{
    native_mutex_lock(&th->interrupt_lock);
    RUBY_VM_SET_INTERRUPT(th);
    if (th->unblock_function) {
  (th->unblock_function)(th->unblock_function_arg);
    }
    else {
  /* none */
    }
    native_mutex_unlock(&th->interrupt_lock);
}


static int
terminate_i(st_data_t key, st_data_t val, rb_thread_t *main_thread)
{
    VALUE thval = key;
    rb_thread_t *th;
    GetThreadPtr(thval, th);

    if (th != main_thread) {
  thread_debug("terminate_i: %p\n", th);
  rb_thread_interrupt(th);
  th->thrown_errinfo = eTerminateSignal;
  th->status = THREAD_TO_KILL;
    }
    else {
  thread_debug("terminate_i: main thread (%p)\n", th);
    }
    return ST_CONTINUE;
}

void
rb_thread_terminate_all(void)
{
    rb_thread_t *th = GET_THREAD(); /* main thread */
    rb_vm_t *vm = th->vm;
    if (vm->main_thread != th) {
  rb_bug("rb_thread_terminate_all: called by child thread (%p, %p)", vm->main_thread, th);
    }

    thread_debug("rb_thread_terminate_all (main thread: %p)\n", th);
    st_foreach(vm->living_threads, terminate_i, (st_data_t)th);

    while (!rb_thread_alone()) {
  PUSH_TAG();
  if (EXEC_TAG() == 0) {
      rb_thread_schedule();
  }
  else {
      /* ignore exception */
  }
  POP_TAG();
    }
    system_working = 0;
}

static void
thread_cleanup_func(void *th_ptr)
{
    rb_thread_t *th = th_ptr;
    th->status = THREAD_KILLED;
    th->machine_stack_start = th->machine_stack_end = 0;
#ifdef __ia64
    th->machine_register_stack_start = th->machine_register_stack_end = 0;
#endif
    native_mutex_destroy(&th->interrupt_lock);
    native_thread_destroy(th);
}

extern void ruby_error_print(void);
static VALUE rb_thread_raise(int, VALUE *, rb_thread_t *);
void rb_thread_recycle_stack_release(VALUE *);

static int
thread_start_func_2(rb_thread_t *th, VALUE *stack_start, VALUE *register_stack_start)
{
    int state;
    VALUE args = th->first_args;
    rb_proc_t *proc;
    rb_thread_t *join_th;
    rb_thread_t *main_th;
    VALUE errinfo = Qnil;

    th->machine_stack_start = stack_start;
#ifdef __ia64
    th->machine_register_stack_start = register_stack_start;
#endif
    th->thgroup = th->vm->thgroup_default;
    thread_debug("thread start: %p\n", th);

    native_mutex_lock(&th->vm->global_interpreter_lock);
    {
  thread_debug("thread start (get lock): %p\n", th);
  rb_thread_set_current(th);

  TH_PUSH_TAG(th);
  if ((state = EXEC_TAG()) == 0) {
      SAVE_ROOT_JMPBUF(th, {
    if (th->first_proc) {
        GetProcPtr(th->first_proc, proc);
        th->errinfo = Qnil;
        th->local_lfp = proc->block.lfp;
        th->local_svar = Qnil;
        th->value = vm_invoke_proc(th, proc, proc->block.self,
                 RARRAY_LEN(args), RARRAY_PTR(args), 0);
    }
    else {
        th->value = (*th->first_func)((void *)th->first_args);
    }
      });
  }
  else {
      if (th->safe_level < 4 &&
    (th->vm->thread_abort_on_exception ||
     th->abort_on_exception || RTEST(ruby_debug))) {
    errinfo = th->errinfo;
    if (NIL_P(errinfo)) errinfo = rb_errinfo();
      }
      th->value = Qnil;
  }

  th->status = THREAD_KILLED;
  thread_debug("thread end: %p\n", th);

  main_th = th->vm->main_thread;
  if (th != main_th) {
      if (TYPE(errinfo) == T_OBJECT) {
    /* treat with normal error object */
    rb_thread_raise(1, &errinfo, main_th);
      }
  }
  TH_POP_TAG();

  st_delete_wrap(th->vm->living_threads, th->self);

  /* wake up joinning threads */
  join_th = th->join_list_head;
  while (join_th) {
      if (join_th == main_th) errinfo = Qnil;
      rb_thread_interrupt(join_th);
      join_th = join_th->join_list_next;
  }
  st_delete_wrap(th->vm->living_threads, th->self);

  if (!th->root_fiber) {
      rb_thread_recycle_stack_release(th->stack);
      th->stack = 0;
  }
    }
    thread_cleanup_func(th);
    native_mutex_unlock(&th->vm->global_interpreter_lock);

    return 0;
}

static VALUE
thread_create_core(VALUE thval, VALUE args, VALUE (*fn)(ANYARGS))
{
    rb_thread_t *th;

    GetThreadPtr(thval, th);

    /* setup thread environment */
    th->first_args = args;
    th->first_proc = fn ? Qfalse : rb_block_proc();
    th->first_func = fn;

    th->priority = GET_THREAD()->priority;

    native_mutex_initialize(&th->interrupt_lock);
    /* kick thread */
    st_insert(th->vm->living_threads, thval, (st_data_t) th->thread_id);
    native_thread_create(th);
    return thval;
}

static VALUE
thread_s_new(int argc, VALUE *argv, VALUE klass)
{
    rb_thread_t *th;
    VALUE thread = rb_thread_alloc(klass);
    rb_obj_call_init(thread, argc, argv);
    GetThreadPtr(thread, th);
    if (!th->first_args) {
      rb_raise(rb_eThreadError, "uninitialized thread - check `%s#initialize'",
      rb_class2name(klass));
    }
    return thread;
}

/*
 *  call-seq:
 *     Thread.start([args]*) {|args| block }   => thread
 *     Thread.fork([args]*) {|args| block }    => thread
 *
 *  Basically the same as <code>Thread::new</code>. However, if class
 *  <code>Thread</code> is subclassed, then calling <code>start</code> in that
 *  subclass will not invoke the subclass's <code>initialize</code> method.
 */

static VALUE
thread_start(VALUE klass, VALUE args)
{
    return thread_create_core(rb_thread_alloc(klass), args, 0);
}

static VALUE
thread_initialize(VALUE thread, VALUE args)
{
    rb_thread_t *th;
    if (!rb_block_given_p()) {
  rb_raise(rb_eThreadError, "must be called with a block");
    }
    GetThreadPtr(thread, th);
    if (th->first_args) {
  VALUE rb_proc_location(VALUE self);
  VALUE proc = th->first_proc, line, loc;
  const char *file;
        if (!proc || !RTEST(loc = rb_proc_location(proc))) {
            rb_raise(rb_eThreadError, "already initialized thread");
        }
  file = RSTRING_PTR(RARRAY_PTR(loc)[0]);
  if (NIL_P(line = RARRAY_PTR(loc)[1])) {
      rb_raise(rb_eThreadError, "already initialized thread - %s",
         file);
  }
        rb_raise(rb_eThreadError, "already initialized thread - %s:%d",
                 file, NUM2INT(line));
    }
    return thread_create_core(thread, args, 0);
}

VALUE
rb_thread_create(VALUE (*fn)(ANYARGS), void *arg)
{
    return thread_create_core(rb_thread_alloc(rb_cThread), (VALUE)arg, fn);
}


/* +infty, for this purpose */
#define DELAY_INFTY 1E30

static VALUE
thread_join(rb_thread_t *target_th, double delay)
{
    rb_thread_t *th = GET_THREAD();
    double now, limit = timeofday() + delay;

    thread_debug("thread_join (thid: %p)\n", (void *)target_th->thread_id);

    if (target_th->status != THREAD_KILLED) {
  th->join_list_next = target_th->join_list_head;
  target_th->join_list_head = th;
    }
    while (target_th->status != THREAD_KILLED) {
  if (delay == DELAY_INFTY) {
      sleep_forever(th);
  }
  else {
      now = timeofday();
      if (now > limit) {
    thread_debug("thread_join: timeout (thid: %p)\n",
           (void *)target_th->thread_id);
    return Qnil;
      }
      sleep_wait_for_interrupt(th, limit - now);
  }
  thread_debug("thread_join: interrupted (thid: %p)\n",
         (void *)target_th->thread_id);
    }

    thread_debug("thread_join: success (thid: %p)\n",
     (void *)target_th->thread_id);

    if (target_th->errinfo != Qnil) {
  VALUE err = target_th->errinfo;

  if (FIXNUM_P(err)) {
      /* */
  }
  else if (TYPE(target_th->errinfo) == T_NODE) {
      rb_exc_raise(vm_make_jump_tag_but_local_jump(
    GET_THROWOBJ_STATE(err), GET_THROWOBJ_VAL(err)));
  }
  else {
      /* normal exception */
      rb_exc_raise(err);
  }
    }
    return target_th->self;
}

/*
 *  call-seq:
 *     thr.join          => thr
 *     thr.join(limit)   => thr
 *
 *  The calling thread will suspend execution and run <i>thr</i>. Does not
 *  return until <i>thr</i> exits or until <i>limit</i> seconds have passed. If
 *  the time limit expires, <code>nil</code> will be returned, otherwise
 *  <i>thr</i> is returned.
 *
 *  Any threads not joined will be killed when the main program exits.  If
 *  <i>thr</i> had previously raised an exception and the
 *  <code>abort_on_exception</code> and <code>$DEBUG</code> flags are not set
 *  (so the exception has not yet been processed) it will be processed at this
 *  time.
 *
 *     a = Thread.new { print "a"; sleep(10); print "b"; print "c" }
 *     x = Thread.new { print "x"; Thread.pass; print "y"; print "z" }
 *     x.join # Let x thread finish, a will be killed on exit.
 *
 *  <em>produces:</em>
 *
 *     axyz
 *
 *  The following example illustrates the <i>limit</i> parameter.
 *
 *     y = Thread.new { 4.times { sleep 0.1; puts 'tick... ' }}
 *     puts "Waiting" until y.join(0.15)
 *
 *  <em>produces:</em>
 *
 *     tick...
 *     Waiting
 *     tick...
 *     Waitingtick...
 *
 *
 *     tick...
 */

static VALUE
thread_join_m(int argc, VALUE *argv, VALUE self)
{
    rb_thread_t *target_th;
    double delay = DELAY_INFTY;
    VALUE limit;

    GetThreadPtr(self, target_th);

    rb_scan_args(argc, argv, "01", &limit);
    if (!NIL_P(limit)) {
  delay = rb_num2dbl(limit);
    }

    return thread_join(target_th, delay);
}

/*
 *  call-seq:
 *     thr.value   => obj
 *
 *  Waits for <i>thr</i> to complete (via <code>Thread#join</code>) and returns
 *  its value.
 *
 *     a = Thread.new { 2 + 2 }
 *     a.value   #=> 4
 */

static VALUE
thread_value(VALUE self)
{
    rb_thread_t *th;
    GetThreadPtr(self, th);
    thread_join(th, DELAY_INFTY);
    return th->value;
}

/*
 * Thread Scheduling
 */

static struct timeval
double2timeval(double d)
{
    struct timeval time;

    time.tv_sec = (int)d;
    time.tv_usec = (int)((d - (int)d) * 1e6);
    if (time.tv_usec < 0) {
  time.tv_usec += (long)1e6;
  time.tv_sec -= 1;
    }
    return time;
}

static void
sleep_forever(rb_thread_t *th)
{
    native_sleep(th, 0);
}

static void
sleep_timeval(rb_thread_t *th, struct timeval tv)
{
    native_sleep(th, &tv);
}

void
rb_thread_sleep_forever()
{
    thread_debug("rb_thread_sleep_forever\n");
    sleep_forever(GET_THREAD());
}

static double
timeofday(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec * 1e-6;
}

static void
sleep_wait_for_interrupt(rb_thread_t *th, double sleepsec)
{
    sleep_timeval(th, double2timeval(sleepsec));
}

static void
sleep_for_polling(rb_thread_t *th)
{
    struct timeval time;
    time.tv_sec = 0;
    time.tv_usec = 100 * 1000;	/* 0.1 sec */
    sleep_timeval(th, time);
}

void
rb_thread_wait_for(struct timeval time)
{
    rb_thread_t *th = GET_THREAD();
    sleep_timeval(th, time);
}

void
rb_thread_polling(void)
{
    RUBY_VM_CHECK_INTS();
    if (!rb_thread_alone()) {
  rb_thread_t *th = GET_THREAD();
  sleep_for_polling(th);
    }
}

struct timeval rb_time_timeval();

void
rb_thread_sleep(int sec)
{
    rb_thread_wait_for(rb_time_timeval(INT2FIX(sec)));
}

void
rb_thread_schedule(void)
{
    thread_debug("rb_thread_schedule\n");
    if (!rb_thread_alone()) {
  rb_thread_t *th = GET_THREAD();

  thread_debug("rb_thread_schedule/switch start\n");

  rb_gc_save_machine_context(th);
  native_mutex_unlock(&th->vm->global_interpreter_lock);
  {
      native_thread_yield();
  }
  native_mutex_lock(&th->vm->global_interpreter_lock);

  rb_thread_set_current(th);
  thread_debug("rb_thread_schedule/switch done\n");

  RUBY_VM_CHECK_INTS();
    }
}

int rb_thread_critical; /* TODO: dummy variable */

VALUE
rb_thread_blocking_region(
    rb_blocking_function_t *func, void *data1,
    rb_unblock_function_t *ubf, void *data2)
{
    VALUE val;
    rb_thread_t *th = GET_THREAD();

    if (ubf == RB_UBF_DFL) {
  ubf = ubf_select;
  data2 = th;
    }

    BLOCKING_REGION({
  val = func(data1);
    }, ubf, data2);

    return val;
}

/*
 *  call-seq:
 *     Thread.pass   => nil
 *
 *  Invokes the thread scheduler to pass execution to another thread.
 *
 *     a = Thread.new { print "a"; Thread.pass;
 *                      print "b"; Thread.pass;
 *                      print "c" }
 *     b = Thread.new { print "x"; Thread.pass;
 *                      print "y"; Thread.pass;
 *                      print "z" }
 *     a.join
 *     b.join
 *
 *  <em>produces:</em>
 *
 *     axbycz
 */

static VALUE
thread_s_pass(VALUE klass)
{
    rb_thread_schedule();
    return Qnil;
}

/*
 *
 */

void
rb_thread_execute_interrupts(rb_thread_t *th)
{
    while (th->interrupt_flag) {
  int status = th->status;
  th->status = THREAD_RUNNABLE;
  th->interrupt_flag = 0;

  /* signal handling */
  if (th->exec_signal) {
      int sig = th->exec_signal;
      th->exec_signal = 0;
      rb_signal_exec(th, sig);
  }

  /* exception from another thread */
  if (th->thrown_errinfo) {
      VALUE err = th->thrown_errinfo;
      th->thrown_errinfo = 0;
      thread_debug("rb_thread_execute_interrupts: %ld\n", err);

      if (err == eKillSignal || err == eTerminateSignal) {
    th->errinfo = INT2FIX(TAG_FATAL);
    TH_JUMP_TAG(th, TAG_FATAL);
      }
      else {
    rb_exc_raise(err);
      }
  }
  th->status = status;

  /* thread pass */
  rb_thread_schedule();
    }
    EXEC_EVENT_HOOK(th, RUBY_EVENT_SWITCH, th->cfp->self, 0, 0);
}


void
rb_gc_mark_threads(void)
{
    /* TODO: remove */
}

/*****************************************************/

static void
rb_thread_ready(rb_thread_t *th)
{
    rb_thread_interrupt(th);
}

static VALUE
rb_thread_raise(int argc, VALUE *argv, rb_thread_t *th)
{
    VALUE exc;

  again:
    if (rb_thread_dead(th)) {
  return Qnil;
    }

    if (th->thrown_errinfo != 0 || th->raised_flag) {
  rb_thread_schedule();
  goto again;
    }

    exc = rb_make_exception(argc, argv);
    th->thrown_errinfo = exc;
    rb_thread_ready(th);
    return Qnil;
}

void
rb_thread_signal_raise(void *thptr, int sig)
{
    VALUE argv[2];
    rb_thread_t *th = thptr;

    argv[0] = rb_eSignal;
    argv[1] = INT2FIX(sig);
    rb_thread_raise(2, argv, th->vm->main_thread);
}

void
rb_thread_signal_exit(void *thptr)
{
    VALUE argv[2];
    rb_thread_t *th = thptr;

    argv[0] = rb_eSystemExit;
    argv[1] = rb_str_new2("exit");
    rb_thread_raise(2, argv, th->vm->main_thread);
}

int
thread_set_raised(rb_thread_t *th)
{
    if (th->raised_flag) {
  return 1;
    }
    th->raised_flag = 1;
    return 0;
}

int
thread_reset_raised(rb_thread_t *th)
{
    if (th->raised_flag == 0) {
  return 0;
    }
    th->raised_flag = 0;
    return 1;
}

void
rb_thread_fd_close(int fd)
{
    /* TODO: fix me */
}

/*
 *  call-seq:
 *     thr.raise(exception)
 *
 *  Raises an exception (see <code>Kernel::raise</code>) from <i>thr</i>. The
 *  caller does not have to be <i>thr</i>.
 *
 *     Thread.abort_on_exception = true
 *     a = Thread.new { sleep(200) }
 *     a.raise("Gotcha")
 *
 *  <em>produces:</em>
 *
 *     prog.rb:3: Gotcha (RuntimeError)
 *     	from prog.rb:2:in `initialize'
 *     	from prog.rb:2:in `new'
 *     	from prog.rb:2
 */

static VALUE
thread_raise_m(int argc, VALUE *argv, VALUE self)
{
    rb_thread_t *th;
    GetThreadPtr(self, th);
    rb_thread_raise(argc, argv, th);
    return Qnil;
}


/*
 *  call-seq:
 *     thr.exit        => thr or nil
 *     thr.kill        => thr or nil
 *     thr.terminate   => thr or nil
 *
 *  Terminates <i>thr</i> and schedules another thread to be run. If this thread
 *  is already marked to be killed, <code>exit</code> returns the
 *  <code>Thread</code>. If this is the main thread, or the last thread, exits
 *  the process.
 */

VALUE
rb_thread_kill(VALUE thread)
{
    rb_thread_t *th;

    GetThreadPtr(thread, th);

    if (th != GET_THREAD() && th->safe_level < 4) {
  rb_secure(4);
    }
    if (th->status == THREAD_TO_KILL || th->status == THREAD_KILLED) {
  return thread;
    }
    if (th == th->vm->main_thread) {
  rb_exit(EXIT_SUCCESS);
    }

    thread_debug("rb_thread_kill: %p (%p)\n", th, (void *)th->thread_id);

    rb_thread_interrupt(th);
    th->thrown_errinfo = eKillSignal;
    th->status = THREAD_TO_KILL;

    return thread;
}


/*
 *  call-seq:
 *     Thread.kill(thread)   => thread
 *
 *  Causes the given <em>thread</em> to exit (see <code>Thread::exit</code>).
 *
 *     count = 0
 *     a = Thread.new { loop { count += 1 } }
 *     sleep(0.1)       #=> 0
 *     Thread.kill(a)   #=> #<Thread:0x401b3d30 dead>
 *     count            #=> 93947
 *     a.alive?         #=> false
 */

static VALUE
rb_thread_s_kill(VALUE obj, VALUE th)
{
    return rb_thread_kill(th);
}


/*
 *  call-seq:
 *     Thread.exit   => thread
 *
 *  Terminates the currently running thread and schedules another thread to be
 *  run. If this thread is already marked to be killed, <code>exit</code>
 *  returns the <code>Thread</code>. If this is the main thread, or the last
 *  thread, exit the process.
 */

static VALUE
rb_thread_exit(void)
{
    return rb_thread_kill(GET_THREAD()->self);
}


/*
 *  call-seq:
 *     thr.wakeup   => thr
 *
 *  Marks <i>thr</i> as eligible for scheduling (it may still remain blocked on
 *  I/O, however). Does not invoke the scheduler (see <code>Thread#run</code>).
 *
 *     c = Thread.new { Thread.stop; puts "hey!" }
 *     c.wakeup
 *
 *  <em>produces:</em>
 *
 *     hey!
 */

VALUE
rb_thread_wakeup(VALUE thread)
{
    rb_thread_t *th;
    GetThreadPtr(thread, th);

    if (th->status == THREAD_KILLED) {
  rb_raise(rb_eThreadError, "killed thread");
    }
    rb_thread_ready(th);
    return thread;
}


/*
 *  call-seq:
 *     thr.run   => thr
 *
 *  Wakes up <i>thr</i>, making it eligible for scheduling.
 *
 *     a = Thread.new { puts "a"; Thread.stop; puts "c" }
 *     Thread.pass
 *     puts "Got here"
 *     a.run
 *     a.join
 *
 *  <em>produces:</em>
 *
 *     a
 *     Got here
 *     c
 */

VALUE
rb_thread_run(VALUE thread)
{
    rb_thread_wakeup(thread);
    rb_thread_schedule();
    return thread;
}


/*
 *  call-seq:
 *     Thread.stop   => nil
 *
 *  Stops execution of the current thread, putting it into a ``sleep'' state,
 *  and schedules execution of another thread.
 *
 *     a = Thread.new { print "a"; Thread.stop; print "c" }
 *     Thread.pass
 *     print "b"
 *     a.run
 *     a.join
 *
 *  <em>produces:</em>
 *
 *     abc
 */

VALUE
rb_thread_stop(void)
{
    if (rb_thread_alone()) {
  rb_raise(rb_eThreadError,
     "stopping only thread\n\tnote: use sleep to stop forever");
    }
    rb_thread_sleep_forever();
    return Qnil;
}

static int
thread_list_i(st_data_t key, st_data_t val, void *data)
{
    VALUE ary = (VALUE)data;
    rb_thread_t *th;
    GetThreadPtr((VALUE)key, th);

    switch (th->status) {
      case THREAD_RUNNABLE:
      case THREAD_STOPPED:
      case THREAD_TO_KILL:
  rb_ary_push(ary, th->self);
      default:
  break;
    }
    return ST_CONTINUE;
}

/********************************************************************/

/*
 *  call-seq:
 *     Thread.list   => array
 *
 *  Returns an array of <code>Thread</code> objects for all threads that are
 *  either runnable or stopped.
 *
 *     Thread.new { sleep(200) }
 *     Thread.new { 1000000.times {|i| i*i } }
 *     Thread.new { Thread.stop }
 *     Thread.list.each {|t| p t}
 *
 *  <em>produces:</em>
 *
 *     #<Thread:0x401b3e84 sleep>
 *     #<Thread:0x401b3f38 run>
 *     #<Thread:0x401b3fb0 sleep>
 *     #<Thread:0x401bdf4c run>
 */

VALUE
rb_thread_list(void)
{
    VALUE ary = rb_ary_new();
    st_foreach(GET_THREAD()->vm->living_threads, thread_list_i, ary);
    return ary;
}

VALUE
rb_thread_current(void)
{
    return GET_THREAD()->self;
}

/*
 *  call-seq:
 *     Thread.current   => thread
 *
 *  Returns the currently executing thread.
 *
 *     Thread.current   #=> #<Thread:0x401bdf4c run>
 */

static VALUE
thread_s_current(VALUE klass)
{
    return rb_thread_current();
}

VALUE
rb_thread_main(void)
{
    return GET_THREAD()->vm->main_thread->self;
}

static VALUE
rb_thread_s_main(VALUE klass)
{
    return rb_thread_main();
}


/*
 *  call-seq:
 *     Thread.abort_on_exception   => true or false
 *
 *  Returns the status of the global ``abort on exception'' condition.  The
 *  default is <code>false</code>. When set to <code>true</code>, or if the
 *  global <code>$DEBUG</code> flag is <code>true</code> (perhaps because the
 *  command line option <code>-d</code> was specified) all threads will abort
 *  (the process will <code>exit(0)</code>) if an exception is raised in any
 *  thread. See also <code>Thread::abort_on_exception=</code>.
 */

static VALUE
rb_thread_s_abort_exc(void)
{
    return GET_THREAD()->vm->thread_abort_on_exception ? Qtrue : Qfalse;
}


/*
 *  call-seq:
 *     Thread.abort_on_exception= boolean   => true or false
 *
 *  When set to <code>true</code>, all threads will abort if an exception is
 *  raised. Returns the new state.
 *
 *     Thread.abort_on_exception = true
 *     t1 = Thread.new do
 *       puts  "In new thread"
 *       raise "Exception from thread"
 *     end
 *     sleep(1)
 *     puts "not reached"
 *
 *  <em>produces:</em>
 *
 *     In new thread
 *     prog.rb:4: Exception from thread (RuntimeError)
 *     	from prog.rb:2:in `initialize'
 *     	from prog.rb:2:in `new'
 *     	from prog.rb:2
 */

static VALUE
rb_thread_s_abort_exc_set(VALUE self, VALUE val)
{
    rb_secure(4);
    GET_THREAD()->vm->thread_abort_on_exception = RTEST(val);
    return val;
}


/*
 *  call-seq:
 *     thr.abort_on_exception   => true or false
 *
 *  Returns the status of the thread-local ``abort on exception'' condition for
 *  <i>thr</i>. The default is <code>false</code>. See also
 *  <code>Thread::abort_on_exception=</code>.
 */

static VALUE
rb_thread_abort_exc(VALUE thread)
{
    rb_thread_t *th;
    GetThreadPtr(thread, th);
    return th->abort_on_exception ? Qtrue : Qfalse;
}


/*
 *  call-seq:
 *     thr.abort_on_exception= boolean   => true or false
 *
 *  When set to <code>true</code>, causes all threads (including the main
 *  program) to abort if an exception is raised in <i>thr</i>. The process will
 *  effectively <code>exit(0)</code>.
 */

static VALUE
rb_thread_abort_exc_set(VALUE thread, VALUE val)
{
    rb_thread_t *th;
    rb_secure(4);

    GetThreadPtr(thread, th);
    th->abort_on_exception = RTEST(val);
    return val;
}


/*
 *  call-seq:
 *     thr.group   => thgrp or nil
 *
 *  Returns the <code>ThreadGroup</code> which contains <i>thr</i>, or nil if
 *  the thread is not a member of any group.
 *
 *     Thread.main.group   #=> #<ThreadGroup:0x4029d914>
 */

VALUE
rb_thread_group(VALUE thread)
{
    rb_thread_t *th;
    VALUE group;
    GetThreadPtr(thread, th);
    group = th->thgroup;

    if (!group) {
  group = Qnil;
    }
    return group;
}

static const char *
thread_status_name(enum rb_thread_status status)
{
    switch (status) {
      case THREAD_RUNNABLE:
  return "run";
      case THREAD_STOPPED:
  return "sleep";
      case THREAD_TO_KILL:
  return "aborting";
      case THREAD_KILLED:
  return "dead";
      default:
  return "unknown";
    }
}

static int
rb_thread_dead(rb_thread_t *th)
{
    return th->status == THREAD_KILLED;
}


/*
 *  call-seq:
 *     thr.status   => string, false or nil
 *
 *  Returns the status of <i>thr</i>: ``<code>sleep</code>'' if <i>thr</i> is
 *  sleeping or waiting on I/O, ``<code>run</code>'' if <i>thr</i> is executing,
 *  ``<code>aborting</code>'' if <i>thr</i> is aborting, <code>false</code> if
 *  <i>thr</i> terminated normally, and <code>nil</code> if <i>thr</i>
 *  terminated with an exception.
 *
 *     a = Thread.new { raise("die now") }
 *     b = Thread.new { Thread.stop }
 *     c = Thread.new { Thread.exit }
 *     d = Thread.new { sleep }
 *     d.kill                  #=> #<Thread:0x401b3678 aborting>
 *     a.status                #=> nil
 *     b.status                #=> "sleep"
 *     c.status                #=> false
 *     d.status                #=> "aborting"
 *     Thread.current.status   #=> "run"
 */

static VALUE
rb_thread_status(VALUE thread)
{
    rb_thread_t *th;
    GetThreadPtr(thread, th);

    if (rb_thread_dead(th)) {
  if (!NIL_P(th->errinfo) && !FIXNUM_P(th->errinfo)
      /* TODO */ ) {
      return Qnil;
  }
  return Qfalse;
    }
    return rb_str_new2(thread_status_name(th->status));
}


/*
 *  call-seq:
 *     thr.alive?   => true or false
 *
 *  Returns <code>true</code> if <i>thr</i> is running or sleeping.
 *
 *     thr = Thread.new { }
 *     thr.join                #=> #<Thread:0x401b3fb0 dead>
 *     Thread.current.alive?   #=> true
 *     thr.alive?              #=> false
 */

static VALUE
rb_thread_alive_p(VALUE thread)
{
    rb_thread_t *th;
    GetThreadPtr(thread, th);

    if (rb_thread_dead(th))
  return Qfalse;
    return Qtrue;
}

/*
 *  call-seq:
 *     thr.stop?   => true or false
 *
 *  Returns <code>true</code> if <i>thr</i> is dead or sleeping.
 *
 *     a = Thread.new { Thread.stop }
 *     b = Thread.current
 *     a.stop?   #=> true
 *     b.stop?   #=> false
 */

static VALUE
rb_thread_stop_p(VALUE thread)
{
    rb_thread_t *th;
    GetThreadPtr(thread, th);

    if (rb_thread_dead(th))
  return Qtrue;
    if (th->status == THREAD_STOPPED)
  return Qtrue;
    return Qfalse;
}

/*
 *  call-seq:
 *     thr.safe_level   => integer
 *
 *  Returns the safe level in effect for <i>thr</i>. Setting thread-local safe
 *  levels can help when implementing sandboxes which run insecure code.
 *
 *     thr = Thread.new { $SAFE = 3; sleep }
 *     Thread.current.safe_level   #=> 0
 *     thr.safe_level              #=> 3
 */

static VALUE
rb_thread_safe_level(VALUE thread)
{
    rb_thread_t *th;
    GetThreadPtr(thread, th);

    return INT2NUM(th->safe_level);
}

/*
 * call-seq:
 *   thr.inspect   => string
 *
 * Dump the name, id, and status of _thr_ to a string.
 */

static VALUE
rb_thread_inspect(VALUE thread)
{
    char *cname = rb_obj_classname(thread);
    rb_thread_t *th;
    const char *status;
    VALUE str;

    GetThreadPtr(thread, th);
    status = thread_status_name(th->status);
    str = rb_sprintf("#<%s:%p %s>", cname, (void *)thread, status);
    OBJ_INFECT(str, thread);

    return str;
}

VALUE
rb_thread_local_aref(VALUE thread, ID id)
{
    rb_thread_t *th;
    VALUE val;

    GetThreadPtr(thread, th);
    if (rb_safe_level() >= 4 && th != GET_THREAD()) {
  rb_raise(rb_eSecurityError, "Insecure: thread locals");
    }
    if (!th->local_storage) {
  return Qnil;
    }
    if (st_lookup(th->local_storage, id, &val)) {
  return val;
    }
    return Qnil;
}

/*
 *  call-seq:
 *      thr[sym]   => obj or nil
 *
 *  Attribute Reference---Returns the value of a thread-local variable, using
 *  either a symbol or a string name. If the specified variable does not exist,
 *  returns <code>nil</code>.
 *
 *     a = Thread.new { Thread.current["name"] = "A"; Thread.stop }
 *     b = Thread.new { Thread.current[:name]  = "B"; Thread.stop }
 *     c = Thread.new { Thread.current["name"] = "C"; Thread.stop }
 *     Thread.list.each {|x| puts "#{x.inspect}: #{x[:name]}" }
 *
 *  <em>produces:</em>
 *
 *     #<Thread:0x401b3b3c sleep>: C
 *     #<Thread:0x401b3bc8 sleep>: B
 *     #<Thread:0x401b3c68 sleep>: A
 *     #<Thread:0x401bdf4c run>:
 */

static VALUE
rb_thread_aref(VALUE thread, VALUE id)
{
    return rb_thread_local_aref(thread, rb_to_id(id));
}

VALUE
rb_thread_local_aset(VALUE thread, ID id, VALUE val)
{
    rb_thread_t *th;
    GetThreadPtr(thread, th);

    if (rb_safe_level() >= 4 && th != GET_THREAD()) {
  rb_raise(rb_eSecurityError, "Insecure: can't modify thread locals");
    }
    if (OBJ_FROZEN(thread)) {
  rb_error_frozen("thread locals");
    }
    if (!th->local_storage) {
  th->local_storage = st_init_numtable();
    }
    if (NIL_P(val)) {
  st_delete(th->local_storage, (st_data_t *) & id, 0);
  return Qnil;
    }
    st_insert(th->local_storage, id, val);
    return val;
}

/*
 *  call-seq:
 *      thr[sym] = obj   => obj
 *
 *  Attribute Assignment---Sets or creates the value of a thread-local variable,
 *  using either a symbol or a string. See also <code>Thread#[]</code>.
 */

static VALUE
rb_thread_aset(VALUE self, ID id, VALUE val)
{
    return rb_thread_local_aset(self, rb_to_id(id), val);
}

/*
 *  call-seq:
 *     thr.key?(sym)   => true or false
 *
 *  Returns <code>true</code> if the given string (or symbol) exists as a
 *  thread-local variable.
 *
 *     me = Thread.current
 *     me[:oliver] = "a"
 *     me.key?(:oliver)    #=> true
 *     me.key?(:stanley)   #=> false
 */

static VALUE
rb_thread_key_p(VALUE self, ID id)
{
    rb_thread_t *th;
    GetThreadPtr(self, th);

    if (!th->local_storage) {
  return Qfalse;
    }
    if (st_lookup(th->local_storage, rb_to_id(id), 0)) {
  return Qtrue;
    }
    return Qfalse;
}

static int
thread_keys_i(ID key, VALUE value, VALUE ary)
{
    rb_ary_push(ary, ID2SYM(key));
    return ST_CONTINUE;
}

int
rb_thread_alone()
{
    int num = 1;
    if (GET_THREAD()->vm->living_threads) {
  num = GET_THREAD()->vm->living_threads->num_entries;
  thread_debug("rb_thread_alone: %d\n", num);
    }
    return num == 1;
}

/*
 *  call-seq:
 *     thr.keys   => array
 *
 *  Returns an an array of the names of the thread-local variables (as Symbols).
 *
 *     thr = Thread.new do
 *       Thread.current[:cat] = 'meow'
 *       Thread.current["dog"] = 'woof'
 *     end
 *     thr.join   #=> #<Thread:0x401b3f10 dead>
 *     thr.keys   #=> [:dog, :cat]
 */

static VALUE
rb_thread_keys(VALUE self)
{
    rb_thread_t *th;
    VALUE ary = rb_ary_new();
    GetThreadPtr(self, th);

    if (th->local_storage) {
  st_foreach(th->local_storage, thread_keys_i, ary);
    }
    return ary;
}

/*
 *  call-seq:
 *     thr.priority   => integer
 *
 *  Returns the priority of <i>thr</i>. Default is inherited from the
 *  current thread which creating the new thread, or zero for the
 *  initial main thread; higher-priority threads will run before
 *  lower-priority threads.
 *
 *     Thread.current.priority   #=> 0
 */

static VALUE
rb_thread_priority(VALUE thread)
{
    rb_thread_t *th;
    GetThreadPtr(thread, th);
    return INT2NUM(th->priority);
}


/*
 *  call-seq:
 *     thr.priority= integer   => thr
 *
 *  Sets the priority of <i>thr</i> to <i>integer</i>. Higher-priority threads
 *  will run before lower-priority threads.
 *
 *     count1 = count2 = 0
 *     a = Thread.new do
 *           loop { count1 += 1 }
 *         end
 *     a.priority = -1
 *
 *     b = Thread.new do
 *           loop { count2 += 1 }
 *         end
 *     b.priority = -2
 *     sleep 1   #=> 1
 *     count1    #=> 622504
 *     count2    #=> 5832
 */

static VALUE
rb_thread_priority_set(VALUE thread, VALUE prio)
{
    rb_thread_t *th;
    GetThreadPtr(thread, th);

    rb_secure(4);

    th->priority = NUM2INT(prio);
    native_thread_apply_priority(th);
    return prio;
}

/* for IO */

#if defined(NFDBITS) && defined(HAVE_RB_FD_INIT)
void
rb_fd_init(volatile rb_fdset_t *fds)
{
    fds->maxfd = 0;
    fds->fdset = ALLOC(fd_set);
    FD_ZERO(fds->fdset);
}

void
rb_fd_term(rb_fdset_t *fds)
{
    if (fds->fdset) free(fds->fdset);
    fds->maxfd = 0;
    fds->fdset = 0;
}

void
rb_fd_zero(rb_fdset_t *fds)
{
    if (fds->fdset) {
  MEMZERO(fds->fdset, fd_mask, howmany(fds->maxfd, NFDBITS));
  FD_ZERO(fds->fdset);
    }
}

static void
rb_fd_resize(int n, rb_fdset_t *fds)
{
    int m = howmany(n + 1, NFDBITS) * sizeof(fd_mask);
    int o = howmany(fds->maxfd, NFDBITS) * sizeof(fd_mask);

    if (m < sizeof(fd_set)) m = sizeof(fd_set);
    if (o < sizeof(fd_set)) o = sizeof(fd_set);

    if (m > o) {
  fds->fdset = realloc(fds->fdset, m);
  memset((char *)fds->fdset + o, 0, m - o);
    }
    if (n >= fds->maxfd) fds->maxfd = n + 1;
}

void
rb_fd_set(int n, rb_fdset_t *fds)
{
    rb_fd_resize(n, fds);
    FD_SET(n, fds->fdset);
}

void
rb_fd_clr(int n, rb_fdset_t *fds)
{
    if (n >= fds->maxfd) return;
    FD_CLR(n, fds->fdset);
}

int
rb_fd_isset(int n, const rb_fdset_t *fds)
{
    if (n >= fds->maxfd) return 0;
    return FD_ISSET(n, fds->fdset) != 0; /* "!= 0" avoids FreeBSD PR 91421 */
}

void
rb_fd_copy(rb_fdset_t *dst, const fd_set *src, int max)
{
    int size = howmany(max, NFDBITS) * sizeof(fd_mask);

    if (size < sizeof(fd_set)) size = sizeof(fd_set);
    dst->maxfd = max;
    dst->fdset = realloc(dst->fdset, size);
    memcpy(dst->fdset, src, size);
}

#undef FD_ZERO
#undef FD_SET
#undef FD_CLR
#undef FD_ISSET

#define FD_ZERO(f)	rb_fd_zero(f)
#define FD_SET(i, f)	rb_fd_set(i, f)
#define FD_CLR(i, f)	rb_fd_clr(i, f)
#define FD_ISSET(i, f)	rb_fd_isset(i, f)

#endif

#if defined(__CYGWIN__) || defined(_WIN32)
static long
cmp_tv(const struct timeval *a, const struct timeval *b)
{
    long d = (a->tv_sec - b->tv_sec);
    return (d != 0) ? d : (a->tv_usec - b->tv_usec);
}

static int
subst(struct timeval *rest, const struct timeval *wait)
{
    while (rest->tv_usec < wait->tv_usec) {
  if (rest->tv_sec <= wait->tv_sec) {
      return 0;
  }
  rest->tv_sec -= 1;
  rest->tv_usec += 1000 * 1000;
    }
    rest->tv_sec -= wait->tv_sec;
    rest->tv_usec -= wait->tv_usec;
    return 1;
}
#endif

static int
do_select(int n, fd_set *read, fd_set *write, fd_set *except,
    struct timeval *timeout)
{
    int result, lerrno;
    fd_set orig_read, orig_write, orig_except;

#ifndef linux
    double limit;
    struct timeval wait_rest;

    if (timeout) {
  limit = timeofday() +
    (double)timeout->tv_sec+(double)timeout->tv_usec*1e-6;
  wait_rest = *timeout;
  timeout = &wait_rest;
    }
#endif

    if (read) orig_read = *read;
    if (write) orig_write = *write;
    if (except) orig_except = *except;

  retry:
    lerrno = 0;

#if defined(__CYGWIN__) || defined(_WIN32)
    {
  /* polling duration: 100ms */
  struct timeval wait_100ms, *wait;
  wait_100ms.tv_sec = 0;
  wait_100ms.tv_usec = 100 * 1000; /* 100 ms */

  do {
      wait = (timeout == 0 || cmp_tv(&wait_100ms, timeout) > 0) ? &wait_100ms : timeout;
      BLOCKING_REGION({
    do {
        result = select(n, read, write, except, wait);
        if (result < 0) lerrno = errno;
        if (result != 0) break;

        if (read) *read = orig_read;
        if (write) *write = orig_write;
        if (except) *except = orig_except;
        wait = &wait_100ms;
    } while (__th->interrupt_flag == 0 && (timeout == 0 || subst(timeout, &wait_100ms)));
      }, 0, 0);
  } while (result == 0 && (timeout == 0 || subst(timeout, &wait_100ms)));
    }
#else
    BLOCKING_REGION({
  result = select(n, read, write, except, timeout);
  if (result < 0) lerrno = errno;
    }, ubf_select, GET_THREAD());
#endif

    errno = lerrno;

    if (result < 0) {
  if (errno == EINTR
#ifdef ERESTART
      || errno == ERESTART
#endif
      ) {
      if (read) *read = orig_read;
      if (write) *write = orig_write;
      if (except) *except = orig_except;
#ifndef linux
      if (timeout) {
    double d = limit - timeofday();

    wait_rest.tv_sec = (unsigned int)d;
    wait_rest.tv_usec = (long)((d-(double)wait_rest.tv_sec)*1e6);
    if (wait_rest.tv_sec < 0)  wait_rest.tv_sec = 0;
    if (wait_rest.tv_usec < 0) wait_rest.tv_usec = 0;
      }
#endif
      goto retry;
  }
    }
    return result;
}

static void
rb_thread_wait_fd_rw(int fd, int read)
{
    int result = 0;
    thread_debug("rb_thread_wait_fd_rw(%d, %s)\n", fd, read ? "read" : "write");

    while (result <= 0) {
  rb_fdset_t set;
  rb_fd_init(&set);
  FD_SET(fd, &set);

  if (read) {
      result = do_select(fd + 1, rb_fd_ptr(&set), 0, 0, 0);
  }
  else {
      result = do_select(fd + 1, 0, rb_fd_ptr(&set), 0, 0);
  }

  rb_fd_term(&set);

  if (result < 0) {
      rb_sys_fail(0);
  }
    }

    thread_debug("rb_thread_wait_fd_rw(%d, %s): done\n", fd, read ? "read" : "write");
}

void
rb_thread_wait_fd(int fd)
{
    rb_thread_wait_fd_rw(fd, 1);
}

int
rb_thread_fd_writable(int fd)
{
    rb_thread_wait_fd_rw(fd, 0);
    return Qtrue;
}

int
rb_thread_select(int max, fd_set * read, fd_set * write, fd_set * except,
     struct timeval *timeout)
{
    if (!read && !write && !except) {
  if (!timeout) {
      rb_thread_sleep_forever();
      return 0;
  }
  rb_thread_wait_for(*timeout);
  return 0;
    }
    else {
  return do_select(max, read, write, except, timeout);
    }
}


/*
 * for GC
 */

#ifdef USE_CONSERVATIVE_STACK_END
void
rb_gc_set_stack_end(VALUE **stack_end_p)
{
    VALUE stack_end;
    *stack_end_p = &stack_end;
}
#endif

void
rb_gc_save_machine_context(rb_thread_t *th)
{
    SET_MACHINE_STACK_END(&th->machine_stack_end);
#ifdef __ia64
    th->machine_register_stack_end = rb_ia64_bsp();
#endif
    setjmp(th->machine_regs);
}

/*
 *
 */

int rb_get_next_signal(rb_vm_t *vm);

static void
timer_thread_function(void)
{
    rb_vm_t *vm = GET_VM(); /* TODO: fix me for Multi-VM */

    /* for time slice */
    RUBY_VM_SET_TIMER_INTERRUPT(vm->running_thread);

    /* check signal */
    if (vm->buffered_signal_size && vm->main_thread->exec_signal == 0) {
  vm->main_thread->exec_signal = rb_get_next_signal(vm);
  thread_debug("buffered_signal_size: %d, sig: %d\n",
         vm->buffered_signal_size, vm->main_thread->exec_signal);
  rb_thread_interrupt(vm->main_thread);
    }

#if 0
    /* prove profiler */
    if (vm->prove_profile.enable) {
  rb_thread_t *th = vm->running_thread;

  if (vm->during_gc) {
      /* GC prove profiling */
  }
    }
#endif
}

void
rb_thread_stop_timer_thread(void)
{
    if (timer_thread_id) {
  system_working = 0;
  native_thread_join(timer_thread_id);
    }
}

void
rb_thread_reset_timer_thread(void)
{
    timer_thread_id = 0;
}

void
rb_thread_start_timer_thread(void)
{
    rb_thread_create_timer_thread();
}

/***/

void
rb_thread_atfork(void)
{
    rb_thread_t *th = GET_THREAD();
    rb_vm_t *vm = th->vm;
    VALUE thval = th->self;
    vm->main_thread = th;

    st_clear(vm->living_threads);
    st_insert(vm->living_threads, thval, (st_data_t) th->thread_id);
}

struct thgroup {
    int enclosed;
    VALUE group;
};

/*
 * Document-class: ThreadGroup
 *
 *  <code>ThreadGroup</code> provides a means of keeping track of a number of
 *  threads as a group. A <code>Thread</code> can belong to only one
 *  <code>ThreadGroup</code> at a time; adding a thread to a new group will
 *  remove it from any previous group.
 *
 *  Newly created threads belong to the same group as the thread from which they
 *  were created.
 */

static VALUE thgroup_s_alloc(VALUE);
static VALUE
thgroup_s_alloc(VALUE klass)
{
    VALUE group;
    struct thgroup *data;

    group = Data_Make_Struct(klass, struct thgroup, 0, free, data);
    data->enclosed = 0;
    data->group = group;

    return group;
}

struct thgroup_list_params {
    VALUE ary;
    VALUE group;
};

static int
thgroup_list_i(st_data_t key, st_data_t val, st_data_t data)
{
    VALUE thread = (VALUE)key;
    VALUE ary = ((struct thgroup_list_params *)data)->ary;
    VALUE group = ((struct thgroup_list_params *)data)->group;
    rb_thread_t *th;
    GetThreadPtr(thread, th);

    if (th->thgroup == group) {
  rb_ary_push(ary, thread);
    }
    return ST_CONTINUE;
}

/*
 *  call-seq:
 *     thgrp.list   => array
 *
 *  Returns an array of all existing <code>Thread</code> objects that belong to
 *  this group.
 *
 *     ThreadGroup::Default.list   #=> [#<Thread:0x401bdf4c run>]
 */

static VALUE
thgroup_list(VALUE group)
{
    VALUE ary = rb_ary_new();
    struct thgroup_list_params param;
    
    param.ary = ary;
    param.group = group;
    st_foreach(GET_THREAD()->vm->living_threads, thgroup_list_i, (st_data_t) & param);
    return ary;
}


/*
 *  call-seq:
 *     thgrp.enclose   => thgrp
 *
 *  Prevents threads from being added to or removed from the receiving
 *  <code>ThreadGroup</code>. New threads can still be started in an enclosed
 *  <code>ThreadGroup</code>.
 *
 *     ThreadGroup::Default.enclose        #=> #<ThreadGroup:0x4029d914>
 *     thr = Thread::new { Thread.stop }   #=> #<Thread:0x402a7210 sleep>
 *     tg = ThreadGroup::new               #=> #<ThreadGroup:0x402752d4>
 *     tg.add thr
 *
 *  <em>produces:</em>
 *
 *     ThreadError: can't move from the enclosed thread group
 */

VALUE
thgroup_enclose(VALUE group)
{
    struct thgroup *data;

    Data_Get_Struct(group, struct thgroup, data);
    data->enclosed = 1;

    return group;
}


/*
 *  call-seq:
 *     thgrp.enclosed?   => true or false
 *
 *  Returns <code>true</code> if <em>thgrp</em> is enclosed. See also
 *  ThreadGroup#enclose.
 */

static VALUE
thgroup_enclosed_p(VALUE group)
{
    struct thgroup *data;

    Data_Get_Struct(group, struct thgroup, data);
    if (data->enclosed)
  return Qtrue;
    return Qfalse;
}


/*
 *  call-seq:
 *     thgrp.add(thread)   => thgrp
 *
 *  Adds the given <em>thread</em> to this group, removing it from any other
 *  group to which it may have previously belonged.
 *
 *     puts "Initial group is #{ThreadGroup::Default.list}"
 *     tg = ThreadGroup.new
 *     t1 = Thread.new { sleep }
 *     t2 = Thread.new { sleep }
 *     puts "t1 is #{t1}"
 *     puts "t2 is #{t2}"
 *     tg.add(t1)
 *     puts "Initial group now #{ThreadGroup::Default.list}"
 *     puts "tg group now #{tg.list}"
 *
 *  <em>produces:</em>
 *
 *     Initial group is #<Thread:0x401bdf4c>
 *     t1 is #<Thread:0x401b3c90>
 *     t2 is #<Thread:0x401b3c18>
 *     Initial group now #<Thread:0x401b3c18>#<Thread:0x401bdf4c>
 *     tg group now #<Thread:0x401b3c90>
 */

static VALUE
thgroup_add(VALUE group, VALUE thread)
{
    rb_thread_t *th;
    struct thgroup *data;

    rb_secure(4);
    GetThreadPtr(thread, th);

    if (OBJ_FROZEN(group)) {
  rb_raise(rb_eThreadError, "can't move to the frozen thread group");
    }
    Data_Get_Struct(group, struct thgroup, data);
    if (data->enclosed) {
  rb_raise(rb_eThreadError, "can't move to the enclosed thread group");
    }

    if (!th->thgroup) {
  return Qnil;
    }

    if (OBJ_FROZEN(th->thgroup)) {
  rb_raise(rb_eThreadError, "can't move from the frozen thread group");
    }
    Data_Get_Struct(th->thgroup, struct thgroup, data);
    if (data->enclosed) {
  rb_raise(rb_eThreadError,
     "can't move from the enclosed thread group");
    }

    th->thgroup = group;
    return group;
}


/*
 *  Document-class: Mutex
 *
 *  Mutex implements a simple semaphore that can be used to coordinate access to
 *  shared data from multiple concurrent threads.
 *
 *  Example:
 *
 *    require 'thread'
 *    semaphore = Mutex.new
 *
 *    a = Thread.new {
 *      semaphore.synchronize {
 *        # access shared resource
 *      }
 *    }
 *
 *    b = Thread.new {
 *      semaphore.synchronize {
 *        # access shared resource
 *      }
 *    }
 *
 */

typedef struct mutex_struct {
    rb_thread_lock_t lock;
    rb_thread_cond_t cond;
    rb_thread_t volatile *th;
    volatile int cond_waiting;
} mutex_t;

#define GetMutexPtr(obj, tobj) \
  Data_Get_Struct(obj, mutex_t, tobj)

static void
mutex_mark(void *ptr)
{
    if (ptr) {
  mutex_t *mutex = ptr;
  if (mutex->th) {
      rb_gc_mark(mutex->th->self);
  }
    }
}

static void
mutex_free(void *ptr)
{
    if (ptr) {
  mutex_t *mutex = ptr;
  native_mutex_destroy(&mutex->lock);
  native_cond_destroy(&mutex->cond);
    }
    ruby_xfree(ptr);
}

static VALUE
mutex_alloc(VALUE klass)
{
    VALUE volatile obj;
    mutex_t *mutex;

    obj = Data_Make_Struct(klass, mutex_t, mutex_mark, mutex_free, mutex);
    native_mutex_initialize(&mutex->lock);
    native_cond_initialize(&mutex->cond);
    return obj;
}

/*
 *  call-seq:
 *     Mutex.new   => mutex
 *
 *  Creates a new Mutex
 */
static VALUE
mutex_initialize(VALUE self)
{
    return self;
}

VALUE
rb_mutex_new(void)
{
    return mutex_alloc(rb_cMutex);
}

/*
 * call-seq:
 *    mutex.locked?  => true or false
 *
 * Returns +true+ if this lock is currently held by some thread.
 */
VALUE
rb_mutex_locked_p(VALUE self)
{
    mutex_t *mutex;
    GetMutexPtr(self, mutex);
    return mutex->th ? Qtrue : Qfalse;
}

/*
 * call-seq:
 *    mutex.try_lock  => true or false
 *
 * Attempts to obtain the lock and returns immediately. Returns +true+ if the
 * lock was granted.
 */
VALUE
rb_mutex_trylock(VALUE self)
{
    mutex_t *mutex;
    VALUE locked = Qfalse;
    GetMutexPtr(self, mutex);

    if (mutex->th == GET_THREAD()) {
  rb_raise(rb_eThreadError, "deadlock; recursive locking");
    }

    native_mutex_lock(&mutex->lock);
    if (mutex->th == 0) {
  mutex->th = GET_THREAD();
  locked = Qtrue;
    }
    native_mutex_unlock(&mutex->lock);

    return locked;
}

static VALUE
lock_func(rb_thread_t *th, mutex_t *mutex)
{
    int locked = 0;

    while (locked == 0) {
  native_mutex_lock(&mutex->lock);
  {
      if (mutex->th == 0) {
    mutex->th = th;
    locked = 1;
      }
      else {
    mutex->cond_waiting++;
    native_cond_wait(&mutex->cond, &mutex->lock);

    if (th->interrupt_flag) {
        locked = 1;
    }
    else if (mutex->th == 0) {
        mutex->th = th;
        locked = 1;
    }
      }
  }
  native_mutex_unlock(&mutex->lock);
    }
    return Qnil;
}

static void
lock_interrupt(void *ptr)
{
    mutex_t *mutex = (mutex_t *)ptr;
    native_mutex_lock(&mutex->lock);
    if (mutex->cond_waiting > 0) {
  native_cond_broadcast(&mutex->cond);
  mutex->cond_waiting = 0;
    }
    native_mutex_unlock(&mutex->lock);
}

/*
 * call-seq:
 *    mutex.lock  => true or false
 *
 * Attempts to grab the lock and waits if it isn't available.
 * Raises +ThreadError+ if +mutex+ was locked by the current thread.
 */
VALUE
rb_mutex_lock(VALUE self)
{
    if (rb_mutex_trylock(self) == Qfalse) {
  mutex_t *mutex;
  rb_thread_t *th = GET_THREAD();
  GetMutexPtr(self, mutex);

  while (mutex->th != th) {
      BLOCKING_REGION({
    lock_func(th, mutex);
      }, lock_interrupt, mutex);

      RUBY_VM_CHECK_INTS();
  }
    }
    return self;
}

/*
 * call-seq:
 *    mutex.unlock    => self
 *
 * Releases the lock.
 * Raises +ThreadError+ if +mutex+ wasn't locked by the current thread.
 */
VALUE
rb_mutex_unlock(VALUE self)
{
    mutex_t *mutex;
    GetMutexPtr(self, mutex);

    if (mutex->th != GET_THREAD()) {
  rb_raise(rb_eThreadError,
     "Attempt to unlock a mutex which is locked by another thread");
    }

    native_mutex_lock(&mutex->lock);
    mutex->th = 0;
    if (mutex->cond_waiting > 0) {
  /* waiting thread */
  native_cond_signal(&mutex->cond);
  mutex->cond_waiting--;
    }
    native_mutex_unlock(&mutex->lock);

    return self;
}

VALUE
rb_mutex_sleep(VALUE self, VALUE timeout)
{
    time_t beg, end;
    struct timeval t;

    if (!NIL_P(timeout)) {
        t = rb_time_interval(timeout);
    }
    rb_mutex_unlock(self);
    beg = time(0);
    if (NIL_P(timeout)) {
  rb_thread_sleep_forever();
    }
    else {
  rb_thread_wait_for(t);
    }
    rb_mutex_lock(self);
    end = time(0) - beg;
    return INT2FIX(end);
}

/*
 * call-seq:
 *    mutex.sleep(timeout = nil)    => self
 *
 * Releases the lock and sleeps +timeout+ seconds if it is given and
 * non-nil or forever.  Raises +ThreadError+ if +mutex+ wasn't locked by
 * the current thread.
 */
static VALUE
mutex_sleep(int argc, VALUE *argv, VALUE self)
{
    VALUE timeout;

    rb_scan_args(argc, argv, "01", &timeout);
    return rb_mutex_sleep(self, timeout);
}

/*
 * call-seq:
 *    mutex.synchronize { ... }    => result of the block
 *
 * Obtains a lock, runs the block, and releases the lock when the block
 * completes.  See the example under +Mutex+.
 */

VALUE
rb_thread_synchronize(VALUE mutex, VALUE (*func)(VALUE arg), VALUE arg)
{
    rb_mutex_lock(mutex);
    return rb_ensure(func, arg, rb_mutex_unlock, mutex);
}

/*
 * Document-class: Barrier
 */
typedef struct rb_thread_list_struct rb_thread_list_t;

struct rb_thread_list_struct {
    rb_thread_t *th;
    rb_thread_list_t *next;
};

static void
thlist_mark(void *ptr)
{
    rb_thread_list_t *q = ptr;

    for (; q; q = q->next) {
  rb_gc_mark(q->th->self);
    }
}

static void
thlist_free(void *ptr)
{
    rb_thread_list_t *q = ptr, *next;

    for (; q; q = next) {
  next = q->next;
  ruby_xfree(q);
    }
}

static int
thlist_signal(rb_thread_list_t **list, unsigned int maxth, rb_thread_t **woken_thread)
{
    int woken = 0;
    rb_thread_list_t *q;

    while ((q = *list) != NULL) {
  rb_thread_t *th = q->th;

  *list = q->next;
  ruby_xfree(q);
  if (th->status != THREAD_KILLED) {
      rb_thread_ready(th);
      if (!woken && woken_thread) *woken_thread = th;
      if (++woken >= maxth && maxth) break;
  }
    }
    return woken;
}

typedef struct {
    rb_thread_t *owner;
    rb_thread_list_t *waiting, **tail;
} rb_barrier_t;

static void
barrier_mark(void *ptr)
{
    rb_barrier_t *b = ptr;

    if (b->owner) rb_gc_mark(b->owner->self);
    thlist_mark(b->waiting);
}

static void
barrier_free(void *ptr)
{
    rb_barrier_t *b = ptr;

    b->owner = 0;
    thlist_free(b->waiting);
    b->waiting = 0;
    ruby_xfree(ptr);
}

static VALUE
barrier_alloc(VALUE klass)
{
    VALUE volatile obj;
    rb_barrier_t *barrier;

    obj = Data_Make_Struct(klass, rb_barrier_t,
         barrier_mark, barrier_free, barrier);
    barrier->owner = GET_THREAD();
    barrier->waiting = 0;
    barrier->tail = &barrier->waiting;
    return obj;
}

VALUE
rb_barrier_new(void)
{
    return barrier_alloc(rb_cBarrier);
}

VALUE
rb_barrier_wait(VALUE self)
{
    rb_barrier_t *barrier;
    rb_thread_list_t *q;

    Data_Get_Struct(self, rb_barrier_t, barrier);
    if (!barrier->owner || barrier->owner->status == THREAD_KILLED) {
  barrier->owner = 0;
  if (thlist_signal(&barrier->waiting, 1, &barrier->owner)) return Qfalse;
  return Qtrue;
    }
    else if (barrier->owner == GET_THREAD()) {
  return Qfalse;
    }
    else {
  *barrier->tail = q = ALLOC(rb_thread_list_t);
  q->th = GET_THREAD();
  q->next = 0;
  barrier->tail = &q->next;
  rb_thread_sleep_forever();
  return barrier->owner == GET_THREAD() ? Qtrue : Qfalse;
    }
}

VALUE
rb_barrier_release(VALUE self)
{
    rb_barrier_t *barrier;
    unsigned int n;

    Data_Get_Struct(self, rb_barrier_t, barrier);
    if (barrier->owner != GET_THREAD()) {
  rb_raise(rb_eThreadError, "not owned");
    }
    n = thlist_signal(&barrier->waiting, 0, &barrier->owner);
    return n ? UINT2NUM(n) : Qfalse;
}

/* variables for recursive traversals */
static ID recursive_key;

static VALUE
recursive_check(VALUE hash, VALUE obj)
{
    if (NIL_P(hash) || TYPE(hash) != T_HASH) {
  return Qfalse;
    }
    else {
  VALUE list = rb_hash_aref(hash, ID2SYM(rb_frame_this_func()));

  if (NIL_P(list) || TYPE(list) != T_HASH)
      return Qfalse;
  if (NIL_P(rb_hash_lookup(list, obj)))
      return Qfalse;
  return Qtrue;
    }
}

static VALUE
recursive_push(VALUE hash, VALUE obj)
{
    VALUE list, sym;

    sym = ID2SYM(rb_frame_this_func());
    if (NIL_P(hash) || TYPE(hash) != T_HASH) {
  hash = rb_hash_new();
  rb_thread_local_aset(rb_thread_current(), recursive_key, hash);
  list = Qnil;
    }
    else {
  list = rb_hash_aref(hash, sym);
    }
    if (NIL_P(list) || TYPE(list) != T_HASH) {
  list = rb_hash_new();
  rb_hash_aset(hash, sym, list);
    }
    rb_hash_aset(list, obj, Qtrue);
    return hash;
}

static void
recursive_pop(VALUE hash, VALUE obj)
{
    VALUE list, sym;

    sym = ID2SYM(rb_frame_this_func());
    if (NIL_P(hash) || TYPE(hash) != T_HASH) {
  VALUE symname;
  VALUE thrname;
  symname = rb_inspect(sym);
  thrname = rb_inspect(rb_thread_current());

  rb_raise(rb_eTypeError, "invalid inspect_tbl hash for %s in %s",
     StringValuePtr(symname), StringValuePtr(thrname));
    }
    list = rb_hash_aref(hash, sym);
    if (NIL_P(list) || TYPE(list) != T_HASH) {
  VALUE symname = rb_inspect(sym);
  VALUE thrname = rb_inspect(rb_thread_current());
  rb_raise(rb_eTypeError, "invalid inspect_tbl list for %s in %s",
     StringValuePtr(symname), StringValuePtr(thrname));
    }
    rb_hash_delete(list, obj);
}

VALUE
rb_exec_recursive(VALUE (*func) (VALUE, VALUE, int), VALUE obj, VALUE arg)
{
    VALUE hash = rb_thread_local_aref(rb_thread_current(), recursive_key);
    VALUE objid = rb_obj_id(obj);

    if (recursive_check(hash, objid)) {
  return (*func) (obj, arg, Qtrue);
    }
    else {
  VALUE result = Qundef;
  int state;

  hash = recursive_push(hash, objid);
  PUSH_TAG();
  if ((state = EXEC_TAG()) == 0) {
      result = (*func) (obj, arg, Qfalse);
  }
  POP_TAG();
  recursive_pop(hash, objid);
  if (state)
      JUMP_TAG(state);
  return result;
    }
}

/* tracer */

static rb_event_hook_t *
alloc_event_fook(rb_event_hook_func_t func, rb_event_flag_t events, VALUE data)
{
    rb_event_hook_t *hook = ALLOC(rb_event_hook_t);
    hook->func = func;
    hook->flag = events;
    hook->data = data;
    return hook;
}

static void
thread_reset_event_flags(rb_thread_t *th)
{
    rb_event_hook_t *hook = th->event_hooks;
    rb_event_flag_t flag = th->event_flags & RUBY_EVENT_VM;

    while (hook) {
  flag |= hook->flag;
  hook = hook->next;
    }
}

void
rb_thread_add_event_hook(rb_thread_t *th,
       rb_event_hook_func_t func, rb_event_flag_t events, VALUE data)
{
    rb_event_hook_t *hook = alloc_event_fook(func, events, data);
    hook->next = th->event_hooks;
    th->event_hooks = hook;
    thread_reset_event_flags(th);
}

static int
set_threads_event_flags_i(st_data_t key, st_data_t val, st_data_t flag)
{
    VALUE thval = key;
    rb_thread_t *th;
    GetThreadPtr(thval, th);

    if (flag) {
  th->event_flags |= RUBY_EVENT_VM;
    }
    else {
  th->event_flags &= (~RUBY_EVENT_VM);
    }
    return ST_CONTINUE;
}

static void
set_threads_event_flags(int flag)
{
    st_foreach(GET_VM()->living_threads, set_threads_event_flags_i, (st_data_t) flag);
}

void
rb_add_event_hook(rb_event_hook_func_t func, rb_event_flag_t events, VALUE data)
{
    rb_event_hook_t *hook = alloc_event_fook(func, events, data);
    rb_vm_t *vm = GET_VM();

    hook->next = vm->event_hooks;
    vm->event_hooks = hook;

    set_threads_event_flags(1);
}

static int
remove_event_hook(rb_event_hook_t **root, rb_event_hook_func_t func)
{
    rb_event_hook_t *prev = NULL, *hook = *root;

    while (hook) {
  if (func == 0 || hook->func == func) {
      if (prev) {
    prev->next = hook->next;
      }
      else {
    *root = hook->next;
      }
      xfree(hook);
  }
  prev = hook;
  hook = hook->next;
    }
    return -1;
}

int
rb_thread_remove_event_hook(rb_thread_t *th, rb_event_hook_func_t func)
{
    int ret = remove_event_hook(&th->event_hooks, func);
    thread_reset_event_flags(th);
    return ret;
}

int
rb_remove_event_hook(rb_event_hook_func_t func)
{
    rb_vm_t *vm = GET_VM();
    rb_event_hook_t *hook = vm->event_hooks;
    int ret = remove_event_hook(&vm->event_hooks, func);

    if (hook != NULL && vm->event_hooks == NULL) {
  set_threads_event_flags(0);
    }

    return ret;
}

static int
clear_trace_func_i(st_data_t key, st_data_t val, st_data_t flag)
{
    rb_thread_t *th;
    GetThreadPtr((VALUE)key, th);
    rb_thread_remove_event_hook(th, 0);
    return ST_CONTINUE;
}

void
rb_clear_trace_func(void)
{
    st_foreach(GET_VM()->living_threads, clear_trace_func_i, (st_data_t) 0);
    rb_remove_event_hook(0);
}

static void call_trace_func(rb_event_flag_t, VALUE data, VALUE self, ID id, VALUE klass);

/*
 *  call-seq:
 *     set_trace_func(proc)    => proc
 *     set_trace_func(nil)     => nil
 *
 *  Establishes _proc_ as the handler for tracing, or disables
 *  tracing if the parameter is +nil+. _proc_ takes up
 *  to six parameters: an event name, a filename, a line number, an
 *  object id, a binding, and the name of a class. _proc_ is
 *  invoked whenever an event occurs. Events are: <code>c-call</code>
 *  (call a C-language routine), <code>c-return</code> (return from a
 *  C-language routine), <code>call</code> (call a Ruby method),
 *  <code>class</code> (start a class or module definition),
 *  <code>end</code> (finish a class or module definition),
 *  <code>line</code> (execute code on a new line), <code>raise</code>
 *  (raise an exception), and <code>return</code> (return from a Ruby
 *  method). Tracing is disabled within the context of _proc_.
 *
 *      class Test
 *	def test
 *	  a = 1
 *	  b = 2
 *	end
 *      end
 *
 *      set_trace_func proc { |event, file, line, id, binding, classname|
 *	   printf "%8s %s:%-2d %10s %8s\n", event, file, line, id, classname
 *      }
 *      t = Test.new
 *      t.test
 *
 *	  line prog.rb:11               false
 *      c-call prog.rb:11        new    Class
 *      c-call prog.rb:11 initialize   Object
 *    c-return prog.rb:11 initialize   Object
 *    c-return prog.rb:11        new    Class
 *	  line prog.rb:12               false
 *  	  call prog.rb:2        test     Test
 *	  line prog.rb:3        test     Test
 *	  line prog.rb:4        test     Test
 *      return prog.rb:4        test     Test
 */

static VALUE
set_trace_func(VALUE obj, VALUE trace)
{
    rb_remove_event_hook(call_trace_func);

    if (NIL_P(trace)) {
  return Qnil;
    }

    if (!rb_obj_is_proc(trace)) {
  rb_raise(rb_eTypeError, "trace_func needs to be Proc");
    }

    rb_add_event_hook(call_trace_func, RUBY_EVENT_ALL, trace);
    return trace;
}

static void
thread_add_trace_func(rb_thread_t *th, VALUE trace)
{
    if (!rb_obj_is_proc(trace)) {
  rb_raise(rb_eTypeError, "trace_func needs to be Proc");
    }

    rb_thread_add_event_hook(th, call_trace_func, RUBY_EVENT_ALL, trace);
}

static VALUE
thread_add_trace_func_m(VALUE obj, VALUE trace)
{
    rb_thread_t *th;
    GetThreadPtr(obj, th);
    thread_add_trace_func(th, trace);
    return trace;
}

static VALUE
thread_set_trace_func_m(VALUE obj, VALUE trace)
{
    rb_thread_t *th;
    GetThreadPtr(obj, th);
    rb_thread_remove_event_hook(th, call_trace_func);

    if (!NIL_P(trace)) {
  return Qnil;
    }
    thread_add_trace_func(th, trace);
    return trace;
}

static char *
get_event_name(rb_event_flag_t event)
{
    switch (event) {
      case RUBY_EVENT_LINE:
  return "line";
      case RUBY_EVENT_CLASS:
  return "class";
      case RUBY_EVENT_END:
  return "end";
      case RUBY_EVENT_CALL:
  return "call";
      case RUBY_EVENT_RETURN:
  return "return";
      case RUBY_EVENT_C_CALL:
  return "c-call";
      case RUBY_EVENT_C_RETURN:
  return "c-return";
      case RUBY_EVENT_RAISE:
  return "raise";
      default:
  return "unknown";
    }
}

VALUE ruby_suppress_tracing(VALUE (*func)(VALUE, int), VALUE arg, int always);

struct call_trace_func_args {
    rb_event_flag_t event;
    VALUE proc;
    VALUE self;
    ID id;
    VALUE klass;
};

static VALUE
call_trace_proc(VALUE args, int tracing)
{
    struct call_trace_func_args *p = (struct call_trace_func_args *)args;
    VALUE eventname = rb_str_new2(get_event_name(p->event));
    VALUE filename = rb_str_new2(rb_sourcefile());
    int line = rb_sourceline();
    ID id = 0;
    VALUE klass = 0;

    if (p->event == RUBY_EVENT_C_CALL ||
  p->event == RUBY_EVENT_C_RETURN) {
  id = p->id;
  klass = p->klass;
    }
    else {
  rb_thread_method_id_and_class(GET_THREAD(), &id, &klass);
    }
    if (id == ID_ALLOCATOR)
  return Qnil;
    if (klass) {
  if (TYPE(klass) == T_ICLASS) {
      klass = RBASIC(klass)->klass;
  }
  else if (FL_TEST(klass, FL_SINGLETON)) {
      klass = rb_iv_get(klass, "__attached__");
  }
    }
    return rb_proc_call(p->proc, rb_ary_new3(6,
               eventname, filename, INT2FIX(line),
               id ? ID2SYM(id) : Qnil,
               p->self ? rb_binding_new() : Qnil,
               klass ? klass : Qnil));
}

static void
call_trace_func(rb_event_flag_t event, VALUE proc, VALUE self, ID id, VALUE klass)
{
    struct call_trace_func_args args;
    
    args.event = event;
    args.proc = proc;
    args.self = self;
    args.id = id;
    args.klass = klass;
    ruby_suppress_tracing(call_trace_proc, (VALUE)&args, Qfalse);
}

VALUE
ruby_suppress_tracing(VALUE (*func)(VALUE, int), VALUE arg, int always)
{
    rb_thread_t *th = GET_THREAD();
    int state, raised, tracing;
    VALUE result = Qnil;

    if ((tracing = th->tracing) != 0 && !always) {
  return Qnil;
    }
    else {
  th->tracing = 1;
    }

    raised = thread_reset_raised(th);

    PUSH_TAG();
    if ((state = EXEC_TAG()) == 0) {
  result = (*func)(arg, tracing);
    }

    if (raised) {
  thread_set_raised(th);
    }
    POP_TAG();

    th->tracing = tracing;
    if (state) {
  JUMP_TAG(state);
    }

    return result;
}

/*
 *  +Thread+ encapsulates the behavior of a thread of
 *  execution, including the main thread of the Ruby script.
 *
 *  In the descriptions of the methods in this class, the parameter _sym_
 *  refers to a symbol, which is either a quoted string or a
 *  +Symbol+ (such as <code>:name</code>).
 */

void
Init_Thread(void)
{
    VALUE cThGroup;

    rb_define_singleton_method(rb_cThread, "new", thread_s_new, -1);
    rb_define_singleton_method(rb_cThread, "start", thread_start, -2);
    rb_define_singleton_method(rb_cThread, "fork", thread_start, -2);
    rb_define_singleton_method(rb_cThread, "main", rb_thread_s_main, 0);
    rb_define_singleton_method(rb_cThread, "current", thread_s_current, 0);
    rb_define_singleton_method(rb_cThread, "stop", rb_thread_stop, 0);
    rb_define_singleton_method(rb_cThread, "kill", rb_thread_s_kill, 1);
    rb_define_singleton_method(rb_cThread, "exit", rb_thread_exit, 0);
    rb_define_singleton_method(rb_cThread, "pass", thread_s_pass, 0);
    rb_define_singleton_method(rb_cThread, "list", rb_thread_list, 0);
    rb_define_singleton_method(rb_cThread, "abort_on_exception", rb_thread_s_abort_exc, 0);
    rb_define_singleton_method(rb_cThread, "abort_on_exception=", rb_thread_s_abort_exc_set, 1);
#if THREAD_DEBUG < 0
    rb_define_singleton_method(rb_cThread, "DEBUG", rb_thread_s_debug, 0);
    rb_define_singleton_method(rb_cThread, "DEBUG=", rb_thread_s_debug_set, 1);
#endif

    rb_define_method(rb_cThread, "initialize", thread_initialize, -2);
    rb_define_method(rb_cThread, "raise", thread_raise_m, -1);
    rb_define_method(rb_cThread, "join", thread_join_m, -1);
    rb_define_method(rb_cThread, "value", thread_value, 0);
    rb_define_method(rb_cThread, "kill", rb_thread_kill, 0);
    rb_define_method(rb_cThread, "terminate", rb_thread_kill, 0);
    rb_define_method(rb_cThread, "exit", rb_thread_kill, 0);
    rb_define_method(rb_cThread, "run", rb_thread_run, 0);
    rb_define_method(rb_cThread, "wakeup", rb_thread_wakeup, 0);
    rb_define_method(rb_cThread, "[]", rb_thread_aref, 1);
    rb_define_method(rb_cThread, "[]=", rb_thread_aset, 2);
    rb_define_method(rb_cThread, "key?", rb_thread_key_p, 1);
    rb_define_method(rb_cThread, "keys", rb_thread_keys, 0);
    rb_define_method(rb_cThread, "priority", rb_thread_priority, 0);
    rb_define_method(rb_cThread, "priority=", rb_thread_priority_set, 1);
    rb_define_method(rb_cThread, "status", rb_thread_status, 0);
    rb_define_method(rb_cThread, "alive?", rb_thread_alive_p, 0);
    rb_define_method(rb_cThread, "stop?", rb_thread_stop_p, 0);
    rb_define_method(rb_cThread, "abort_on_exception", rb_thread_abort_exc, 0);
    rb_define_method(rb_cThread, "abort_on_exception=", rb_thread_abort_exc_set, 1);
    rb_define_method(rb_cThread, "safe_level", rb_thread_safe_level, 0);
    rb_define_method(rb_cThread, "group", rb_thread_group, 0);

    rb_define_method(rb_cThread, "inspect", rb_thread_inspect, 0);

    cThGroup = rb_define_class("ThreadGroup", rb_cObject);
    rb_define_alloc_func(cThGroup, thgroup_s_alloc);
    rb_define_method(cThGroup, "list", thgroup_list, 0);
    rb_define_method(cThGroup, "enclose", thgroup_enclose, 0);
    rb_define_method(cThGroup, "enclosed?", thgroup_enclosed_p, 0);
    rb_define_method(cThGroup, "add", thgroup_add, 1);

    {
  rb_thread_t *th = GET_THREAD();
  th->thgroup = th->vm->thgroup_default = rb_obj_alloc(cThGroup);
  rb_define_const(cThGroup, "Default", th->thgroup);
    }

    rb_cMutex = rb_define_class("Mutex", rb_cObject);
    rb_define_alloc_func(rb_cMutex, mutex_alloc);
    rb_define_method(rb_cMutex, "initialize", mutex_initialize, 0);
    rb_define_method(rb_cMutex, "locked?", rb_mutex_locked_p, 0);
    rb_define_method(rb_cMutex, "try_lock", rb_mutex_trylock, 0);
    rb_define_method(rb_cMutex, "lock", rb_mutex_lock, 0);
    rb_define_method(rb_cMutex, "unlock", rb_mutex_unlock, 0);
    rb_define_method(rb_cMutex, "sleep", mutex_sleep, -1);

    recursive_key = rb_intern("__recursive_key__");
    rb_eThreadError = rb_define_class("ThreadError", rb_eStandardError);

    /* trace */
    rb_define_global_function("set_trace_func", set_trace_func, 1);
    rb_define_method(rb_cThread, "set_trace_func", thread_set_trace_func_m, 1);
    rb_define_method(rb_cThread, "add_trace_func", thread_add_trace_func_m, 1);

    /* init thread core */
    Init_native_thread();
    {
  /* main thread setting */
  {
      /* acquire global interpreter lock */
      rb_thread_lock_t *lp = &GET_THREAD()->vm->global_interpreter_lock;
      native_mutex_initialize(lp);
      native_mutex_lock(lp);
      native_mutex_initialize(&GET_THREAD()->interrupt_lock);
  }
    }

    rb_thread_create_timer_thread();
}

int
ruby_native_thread_p(void)
{
    rb_thread_t *rb_thread_check_ptr(rb_thread_t *ptr);
    rb_thread_t *th = ruby_thread_from_native();

    return th ? Qtrue : Qfalse;
}
