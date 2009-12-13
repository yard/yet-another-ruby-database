#include "../include/yard.h"

struct __thread_param {
  YardThreadFunction function;
  void * data;  
};

/*
    Defines an entry point for the thread. Used to wrap YARD function pointers
    in order not to maintain OS-specific modifiers required by thread implementations (like stdcall from mustdie).
    
    void * param: holds a reference to the function that should be called.
*/
DWORD WINAPI __thread_func(void * param) {
  struct __thread_param * thread_param = (struct __thread_param *)param;
  
  thread_param->function(thread_param->data);    
}

/*
    Spawns a new thread being given a thread function to be used.
    
    int stack_size: Size of thread's stack.
    YardThreadFunction tf: YARD thread function to be exeuted from thread.
    void * data: data to pass to thread function.
*/
THREAD yard_create_thread(int stack_size, YardThreadFunction tf, void * data) {
  DWORD thread_id;
  struct __thread_param * thread_param = (struct __thread_param *)malloc(sizeof(struct __thread_param));
  thread_param->function = tf;
  thread_param->data = data;
  
  return CreateThread(NULL, stack_size, &__thread_func, thread_param, 0, &thread_id);        
}

/*
    Initializes a lightweight lock entity.
    
    THREAD_LOCK * lock: Lock descriptor to intialize.
*/
void yard_create_thread_lock(THREAD_LOCK * lock) {
  // just create a critical section entity
  InitializeCriticalSection(lock);
}

/*
    Attempts to acquire lightweight lock.
    
    THREAD_LOCK * lock: Lock descriptor to use.
*/
void yard_thread_lock_start(THREAD_LOCK * lock) {
  EnterCriticalSection(lock);
}

/*
    Attempts to release lightweight lock.
    THREAD_LOCK * lock: Lock descriptor to use.
*/
void yard_thread_lock_end(THREAD_LOCK * lock) {
  LeaveCriticalSection(lock);      
}

/*
    Gets this thread to sleep for some time.
    
    THREAD thread: a thread to make sleep.
    int time: how long to sleep (msec).
*/
void yard_thread_sleep(int time) {
  Sleep(time);
}

/*
    Returns the current thread.
*/
THREAD yard_get_current_thread() {
  return GetCurrentThread();        
}
