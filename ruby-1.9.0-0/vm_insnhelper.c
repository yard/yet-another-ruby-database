/**********************************************************************

  insnhelper.c - instruction helper functions.

  $Author: ko1 $
  $Date: 2007-12-20 18:29:46 +0900 (Thu, 20 Dec 2007) $

  Copyright (C) 2007 Koichi Sasada

**********************************************************************/

/* finish iseq array */
#include "insns.inc"

/* control stack frame */


#ifndef INLINE
#define INLINE inline
#endif

static inline rb_control_frame_t *
vm_push_frame(rb_thread_t *th, rb_iseq_t *iseq, VALUE type,
	      VALUE self, VALUE specval, VALUE *pc,
	      VALUE *sp, VALUE *lfp, int local_size)
{
    VALUE *dfp;
    rb_control_frame_t *cfp;
    int i;

    /* nil initialize */
    for (i=0; i < local_size; i++) {
	*sp = Qnil;
	sp++;
    }

    /* set special val */
    *sp = GC_GUARDED_PTR(specval);
    dfp = sp;

    if (lfp == 0) {
	lfp = sp;
    }

    cfp = th->cfp = th->cfp - 1;
    cfp->pc = pc;
    cfp->sp = sp + 1;
    cfp->bp = sp + 1;
    cfp->iseq = iseq;
    cfp->flag = type;
    cfp->self = self;
    cfp->lfp = lfp;
    cfp->dfp = dfp;
    cfp->proc = 0;

#define COLLECT_PROFILE 0
#if COLLECT_PROFILE
    cfp->prof_time_self = clock();
    cfp->prof_time_chld = 0;
#endif

    if (VMDEBUG == 2) {
	SDR();
    }

    return cfp;
}

static inline void
vm_pop_frame(rb_thread_t *th)
{
#if COLLECT_PROFILE
    rb_control_frame_t *cfp = th->cfp;

    if (RUBY_VM_NORMAL_ISEQ_P(cfp->iseq)) {
	VALUE current_time = clock();
	rb_control_frame_t *cfp = th->cfp;
	cfp->prof_time_self = current_time - cfp->prof_time_self;
	(cfp+1)->prof_time_chld += cfp->prof_time_self;

	cfp->iseq->profile.count++;
	cfp->iseq->profile.time_cumu = cfp->prof_time_self;
	cfp->iseq->profile.time_self = cfp->prof_time_self - cfp->prof_time_chld;
    }
    else if (0 /* c method? */) {

    }
#endif
    th->cfp = RUBY_VM_PREVIOUS_CONTROL_FRAME(th->cfp);

    if (VMDEBUG == 2) {
	SDR();
    }
}

/* method dispatch */

static inline int
vm_callee_setup_arg(rb_thread_t *th, rb_iseq_t *iseq,
		    int argc, VALUE *argv, rb_block_t **block)
{
    const int m = iseq->argc;
    const int orig_argc = argc;

    if (LIKELY(iseq->arg_simple & 0x01)) {
	/* simple check */
	if (argc != m) {
	    rb_raise(rb_eArgError, "wrong number of arguments (%d for %d)",
		     argc, m);
	}
	return 0;
    }
    else {
	VALUE * const dst = argv;
	int opt_pc = 0;
	th->mark_stack_len = argc + iseq->arg_size;

	/* mandatory */
	if (argc < (m + iseq->arg_post_len)) { /* check with post arg */
	    rb_raise(rb_eArgError, "wrong number of arguments (%d for %d)",
		     argc, m + iseq->arg_post_len);
	}

	argv += m;
	argc -= m;

	/* post arguments */
	if (iseq->arg_post_len) {
	    if (!(orig_argc < iseq->arg_post_start)) {
		VALUE *new_argv = ALLOCA_N(VALUE, argc);
		MEMCPY(new_argv, argv, VALUE, argc);
		argv = new_argv;
	    }

	    MEMCPY(&dst[iseq->arg_post_start], &argv[argc -= iseq->arg_post_len],
		   VALUE, iseq->arg_post_len);
	}

	/* opt arguments */
	if (iseq->arg_opts) {
	    const int opts = iseq->arg_opts - 1 /* no opt */;

	    if (iseq->arg_rest == -1 && argc > opts) {
		rb_raise(rb_eArgError, "wrong number of arguments (%d for %d)",
			 orig_argc, m + opts + iseq->arg_post_len);
	    }

	    if (argc > opts) {
		argc -= opts;
		argv += opts;
		opt_pc = iseq->arg_opt_table[opts]; /* no opt */
	    }
	    else {
		int i;
		for (i = argc; i<opts; i++) {
		    dst[i + m] = Qnil;
		}
		opt_pc = iseq->arg_opt_table[argc];
		argc = 0;
	    }
	}

	/* rest arguments */
	if (iseq->arg_rest != -1) {
	    dst[iseq->arg_rest] = rb_ary_new4(argc, argv);
	    argc = 0;
	}

	/* block arguments */
	if (block && iseq->arg_block != -1) {
	    VALUE blockval = Qnil;
	    rb_block_t * const blockptr = *block;

	    if (argc != 0) {
		rb_raise(rb_eArgError, "wrong number of arguments (%d for %d)",
			 orig_argc, m + iseq->arg_post_len);
	    }

	    if (blockptr) {
		/* make Proc object */
		if (blockptr->proc == 0) {
		    rb_proc_t *proc;

		    blockval = vm_make_proc(th, th->cfp, blockptr);

		    GetProcPtr(blockval, proc);
		    *block = &proc->block;
		}
		else {
		    blockval = blockptr->proc;
		}
	    }

	    dst[iseq->arg_block] = blockval; /* Proc or nil */
	}

	th->mark_stack_len = 0;
	return opt_pc;
    }
}

static inline int
caller_setup_args(rb_thread_t *th, rb_control_frame_t *cfp, VALUE flag,
		  int argc, rb_iseq_t *blockiseq, rb_block_t **block)
{
    rb_block_t *blockptr = 0;

    if (block) {
	if (flag & VM_CALL_ARGS_BLOCKARG_BIT) {
	    rb_proc_t *po;
	    VALUE proc;

	    proc = *(--cfp->sp);

	    if (proc != Qnil) {
		if (!rb_obj_is_proc(proc)) {
		    VALUE b = rb_check_convert_type(proc, T_DATA, "Proc", "to_proc");
		    if (NIL_P(b)) {
			rb_raise(rb_eTypeError,
				 "wrong argument type %s (expected Proc)",
				 rb_obj_classname(proc));
		    }
		    proc = b;
		}
		GetProcPtr(proc, po);
		blockptr = &po->block;
		RUBY_VM_GET_BLOCK_PTR_IN_CFP(cfp)->proc = proc;
		*block = blockptr;
	    }
	}
	else if (blockiseq) {
	    blockptr = RUBY_VM_GET_BLOCK_PTR_IN_CFP(cfp);
	    blockptr->iseq = blockiseq;
	    blockptr->proc = 0;
	    *block = blockptr;
	}
    }

    /* expand top of stack? */
    if (flag & VM_CALL_ARGS_SPLAT_BIT) {
	VALUE ary = *(cfp->sp - 1);
	VALUE *ptr;
	int i;
	VALUE tmp = rb_check_convert_type(ary, T_ARRAY, "Array", "to_a");

	if (NIL_P(tmp)) {
	    /* do nothing */
	}
	else {
	    int len = RARRAY_LEN(tmp);
	    ptr = RARRAY_PTR(tmp);
	    cfp->sp -= 1;

	    CHECK_STACK_OVERFLOW(cfp, len);

	    for (i = 0; i < len; i++) {
		*cfp->sp++ = ptr[i];
	    }
	    argc += i-1;
	}
    }

    return argc;
}

static inline VALUE
call_cfunc(VALUE (*func)(), VALUE recv, int len, int argc, const VALUE *argv)
{
    /* printf("len: %d, argc: %d\n", len, argc); */

    if (len >= 0 && argc != len) {
	rb_raise(rb_eArgError, "wrong number of arguments(%d for %d)",
		 argc, len);
    }

    switch (len) {
      case -2:
	return (*func) (recv, rb_ary_new4(argc, argv));
	break;
      case -1:
	return (*func) (argc, argv, recv);
	break;
      case 0:
	return (*func) (recv);
	break;
      case 1:
	return (*func) (recv, argv[0]);
	break;
      case 2:
	return (*func) (recv, argv[0], argv[1]);
	break;
      case 3:
	return (*func) (recv, argv[0], argv[1], argv[2]);
	break;
      case 4:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3]);
	break;
      case 5:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3], argv[4]);
	break;
      case 6:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3], argv[4],
			argv[5]);
	break;
      case 7:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3], argv[4],
			argv[5], argv[6]);
	break;
      case 8:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3], argv[4],
			argv[5], argv[6], argv[7]);
	break;
      case 9:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3], argv[4],
			argv[5], argv[6], argv[7], argv[8]);
	break;
      case 10:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3], argv[4],
			argv[5], argv[6], argv[7], argv[8], argv[9]);
	break;
      case 11:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3], argv[4],
			argv[5], argv[6], argv[7], argv[8], argv[9],
			argv[10]);
	break;
      case 12:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3], argv[4],
			argv[5], argv[6], argv[7], argv[8], argv[9],
			argv[10], argv[11]);
	break;
      case 13:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3], argv[4],
			argv[5], argv[6], argv[7], argv[8], argv[9], argv[10],
			argv[11], argv[12]);
	break;
      case 14:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3], argv[4],
			argv[5], argv[6], argv[7], argv[8], argv[9], argv[10],
			argv[11], argv[12], argv[13]);
	break;
      case 15:
	return (*func) (recv, argv[0], argv[1], argv[2], argv[3], argv[4],
			argv[5], argv[6], argv[7], argv[8], argv[9], argv[10],
			argv[11], argv[12], argv[13], argv[14]);
	break;
      default:
	rb_raise(rb_eArgError, "too many arguments(%d)", len);
	break;
    }
    return Qnil;		/* not reached */
}

static inline VALUE
vm_call_cfunc(rb_thread_t *th, rb_control_frame_t *reg_cfp, int num,
	      ID id, VALUE recv, VALUE klass, VALUE flag,
	      NODE *mn, rb_block_t *blockptr)
{
    VALUE val;

    EXEC_EVENT_HOOK(th, RUBY_EVENT_C_CALL, recv, id, klass);
    {
	rb_control_frame_t *cfp =
	    vm_push_frame(th, 0, FRAME_MAGIC_CFUNC | (flag << FRAME_MAGIC_MASK_BITS),
			  recv, (VALUE) blockptr, 0, reg_cfp->sp, 0, 1);

	cfp->method_id = id;
	cfp->method_class = klass;

	reg_cfp->sp -= num + 1;

	val = call_cfunc(mn->nd_cfnc, recv, mn->nd_argc, num, reg_cfp->sp + 1);

	if (reg_cfp != th->cfp + 1) {
	    rb_bug("cfp consistency error - send");
	}
	vm_pop_frame(th);
    }
    EXEC_EVENT_HOOK(th, RUBY_EVENT_C_RETURN, recv, id, klass);

    return val;
}

static int
vm_cfunc_flags(rb_control_frame_t *cfp)
{
    if (RUBYVM_CFUNC_FRAME_P(cfp))
	return cfp->flag >> FRAME_MAGIC_MASK_BITS;
    return 0;
}

static inline VALUE
vm_call_bmethod(rb_thread_t *th, ID id, VALUE procval, VALUE recv,
		VALUE klass, int argc, VALUE *argv, rb_block_t *blockptr)
{
    rb_control_frame_t *cfp = th->cfp;
    rb_proc_t *proc;
    VALUE val;

    /* control block frame */
    (cfp-2)->method_id = id;
    (cfp-2)->method_class = klass;

    GetProcPtr(procval, proc);
    val = vm_invoke_proc(th, proc, recv, argc, argv, blockptr);
    return val;
}

static inline VALUE
vm_method_missing(rb_thread_t *th, ID id, VALUE recv, int num,
		  rb_block_t *blockptr, int opt)
{
    rb_control_frame_t *reg_cfp = th->cfp;
    VALUE *argv = STACK_ADDR_FROM_TOP(num + 1);
    VALUE val;
    argv[0] = ID2SYM(id);
    th->method_missing_reason = opt;
    th->passed_block = blockptr;
    val = rb_funcall2(recv, idMethodMissing, num + 1, argv);
    POPN(num + 1);
    return val;
}

static inline void
vm_setup_method(rb_thread_t *th, rb_control_frame_t *cfp,
		int argc, rb_block_t *blockptr, VALUE flag,
		VALUE iseqval, VALUE recv, VALUE klass)
{
    rb_iseq_t *iseq;
    int opt_pc, i;
    VALUE *sp, *rsp = cfp->sp - argc;

    /* TODO: eliminate it */
    GetISeqPtr(iseqval, iseq);
    opt_pc = vm_callee_setup_arg(th, iseq, argc, rsp, &blockptr);

    /* stack overflow check */
    CHECK_STACK_OVERFLOW(cfp, iseq->stack_max);

    sp = rsp + iseq->arg_size;

    if (LIKELY(!(flag & VM_CALL_TAILCALL_BIT))) {
	if (0) printf("local_size: %d, arg_size: %d\n",
		      iseq->local_size, iseq->arg_size);

	/* clear local variables */
	for (i = 0; i < iseq->local_size - iseq->arg_size; i++) {
	    *sp++ = Qnil;
	}

	vm_push_frame(th, iseq,
		      FRAME_MAGIC_METHOD, recv, (VALUE) blockptr,
		      iseq->iseq_encoded + opt_pc, sp, 0, 0);

	cfp->sp = rsp - 1 /* recv */;
    }
    else {
	VALUE *p_rsp;
	cfp = ++th->cfp; /* pop cf */
	p_rsp = th->cfp->sp;

	/* copy arguments */
	for (i=0; i < (sp - rsp); i++) {
	    p_rsp[i] = rsp[i];
	}

	sp -= rsp - p_rsp;

	/* clear local variables */
	for (i = 0; i < iseq->local_size - iseq->arg_size; i++) {
	    *sp++ = Qnil;
	}

	vm_push_frame(th, iseq,
		      FRAME_MAGIC_METHOD, recv, (VALUE) blockptr,
		      iseq->iseq_encoded + opt_pc, sp, 0, 0);
    }
}

static inline VALUE
vm_call_method(rb_thread_t *th, rb_control_frame_t *cfp,
	       int num, rb_block_t *blockptr, VALUE flag,
	       ID id, NODE *mn, VALUE recv, VALUE klass)
{
    VALUE val;

  start_method_dispatch:

    if ((mn != 0)) {
	if ((mn->nd_noex == 0)) {
	    /* dispatch method */
	    NODE *node;

	  normal_method_dispatch:

	    node = mn->nd_body;

	    switch (nd_type(node)) {
	      case RUBY_VM_METHOD_NODE:{
		  vm_setup_method(th, cfp, num, blockptr, flag, (VALUE)node->nd_body, recv, klass);
		  return Qundef;
	      }
	      case NODE_CFUNC:{
		  val = vm_call_cfunc(th, cfp, num, id, recv, mn->nd_clss, flag, node, blockptr);
		  break;
	      }
	      case NODE_ATTRSET:{
		  val = rb_ivar_set(recv, node->nd_vid, *(cfp->sp - 1));
		  cfp->sp -= 2;
		  break;
	      }
	      case NODE_IVAR:{
		  val = rb_ivar_get(recv, node->nd_vid);
		  cfp->sp -= 1;
		  break;
	      }
	      case NODE_BMETHOD:{
		  VALUE *argv = cfp->sp - num;
		  val = vm_call_bmethod(th, id, node->nd_cval, recv, klass, num, argv, blockptr);
		  cfp->sp += - num - 1;
		  break;
	      }
	      case NODE_ZSUPER:{
		  klass = RCLASS_SUPER(mn->nd_clss);
		  mn = rb_method_node(klass, id);

		  if (mn != 0) {
		      goto normal_method_dispatch;
		  }
		  else {
		      goto start_method_dispatch;
		  }
	      }
	      default:{
		  printf("node: %s\n", ruby_node_name(nd_type(node)));
		  rb_bug("eval_invoke_method: unreachable");
		  /* unreachable */
		  break;
	      }
	    }
	}
	else {
	    int noex_safe;

	    if (!(flag & VM_CALL_FCALL_BIT) &&
		(mn->nd_noex & NOEX_MASK) & NOEX_PRIVATE) {
		int stat = NOEX_PRIVATE;

		if (flag & VM_CALL_VCALL_BIT) {
		    stat |= NOEX_VCALL;
		}
		val = vm_method_missing(th, id, recv, num, blockptr, stat);
	    }
	    else if (((mn->nd_noex & NOEX_MASK) & NOEX_PROTECTED) &&
		     !(flag & VM_CALL_SEND_BIT)) {
		VALUE defined_class = mn->nd_clss;

		if (TYPE(defined_class) == T_ICLASS) {
		    defined_class = RBASIC(defined_class)->klass;
		}

		if (!rb_obj_is_kind_of(cfp->self, rb_class_real(defined_class))) {
		    val = vm_method_missing(th, id, recv, num, blockptr, NOEX_PROTECTED);
		}
		else {
		    goto normal_method_dispatch;
		}
	    }
	    else if ((noex_safe = NOEX_SAFE(mn->nd_noex)) > th->safe_level &&
		     (noex_safe > 2)) {
		rb_raise(rb_eSecurityError, "calling insecure method: %s", rb_id2name(id));
	    }
	    else {
		goto normal_method_dispatch;
	    }
	}
    }
    else {
	/* method missing */
	if (id == idMethodMissing) {
	    rb_bug("method missing");
	}
	else {
	    int stat = 0;
	    if (flag & VM_CALL_VCALL_BIT) {
		stat |= NOEX_VCALL;
	    }
	    if (flag & VM_CALL_SUPER_BIT) {
		stat |= NOEX_SUPER;
	    }
	    val = vm_method_missing(th, id, recv, num, blockptr, stat);
	}
    }

    RUBY_VM_CHECK_INTS();
    return val;
}

static inline void
vm_send_optimize(rb_control_frame_t *reg_cfp,
		 NODE **mn, rb_num_t *flag, rb_num_t *num, ID *id, VALUE klass)
{
    if (*mn && nd_type((*mn)->nd_body) == NODE_CFUNC) {
	NODE *node = (*mn)->nd_body;
	extern VALUE rb_f_send(int argc, VALUE *argv, VALUE recv);

	if (node->nd_cfnc == rb_f_send) {
	    int i = *num - 1;
	    VALUE sym = TOPN(i);
	    *id = SYMBOL_P(sym) ? SYM2ID(sym) : rb_to_id(sym);

	    /* shift arguments */
	    if (i > 0) {
		MEMMOVE(&TOPN(i), &TOPN(i-1), VALUE, i);
	    }

	    *mn = rb_method_node(klass, *id);
	    *num -= 1;
	    DEC_SP(1);
	    *flag |= VM_CALL_FCALL_BIT;
	}
    }
}

/* yield */

static inline int
block_proc_is_lambda(VALUE procval)
{
    rb_proc_t *proc;

    if (procval) {
	GetProcPtr(procval, proc);
	return proc->is_lambda;
    }
    else {
	return 0;
    }
}

static inline VALUE
vm_yield_with_cfunc(rb_thread_t *th, rb_block_t *block,
		    VALUE self, int argc, VALUE *argv)
{
    NODE *ifunc = (NODE *) block->iseq;
    VALUE val;
    VALUE arg;
    int lambda = block_proc_is_lambda(block->proc);

    if (lambda) {
	arg = rb_ary_new4(argc, argv);
    }
    else if (argc == 0) {
	arg = Qnil;
    }
    else {
	arg = argv[0];
    }

    vm_push_frame(th, 0, FRAME_MAGIC_IFUNC,
		  self, (VALUE)block->dfp,
		  0, th->cfp->sp, block->lfp, 1);

    val = (*ifunc->nd_cfnc) (arg, ifunc->nd_tval, argc, argv);

    th->cfp++;
    return val;
}

static inline int
vm_yield_setup_args(rb_thread_t *th, rb_iseq_t *iseq,
		    int argc, VALUE *argv, rb_block_t *blockptr, int lambda)
{
    if (0) { /* for debug */
	printf("     argc: %d\n", argc);
	printf("iseq argc: %d\n", iseq->argc);
	printf("iseq opts: %d\n", iseq->arg_opts);
	printf("iseq rest: %d\n", iseq->arg_rest);
	printf("iseq post: %d\n", iseq->arg_post_len);
	printf("iseq blck: %d\n", iseq->arg_block);
	printf("iseq smpl: %d\n", iseq->arg_simple);
	printf("   lambda: %s\n", lambda ? "true" : "false");
    }

    if (lambda) {
	/* call as method */
	return vm_callee_setup_arg(th, iseq, argc, argv, &blockptr);
    }
    else {
	int i;
	const int m = iseq->argc;

	th->mark_stack_len = argc;

	/*
	 * yield [1, 2]
	 *  => {|a|} => a = [1, 2]
	 *  => {|a, b|} => a, b = [1, 2]
	 */
	if (!(iseq->arg_simple & 0x02) &&
	    (m + iseq->arg_post_len) > 0 &&
	    argc == 1 && TYPE(argv[0]) == T_ARRAY) {
	    VALUE ary = argv[0];
	    th->mark_stack_len = argc = RARRAY_LEN(ary);

	    CHECK_STACK_OVERFLOW(th->cfp, argc);

	    MEMCPY(argv, RARRAY_PTR(ary), VALUE, argc);
	}

	for (i=argc; i<m; i++) {
	    argv[i] = Qnil;
	}

	if (iseq->arg_rest == -1) {
	    if (m < argc) {
		/*
		 * yield 1, 2
		 * => {|a|} # truncate
		 */
		th->mark_stack_len = argc = m;
	    }
	}
	else {
	    int r = iseq->arg_rest;

	    if (iseq->arg_post_len) {
		int len = iseq->arg_post_len;
		int start = iseq->arg_post_start;
		int rsize = argc > m ? argc - m : 0;
		int psize = rsize;
		VALUE ary;

		if (psize > len) psize = len;

		ary = rb_ary_new4(rsize - psize, &argv[r]);

		if (0) {
		    printf(" argc: %d\n", argc);
		    printf("  len: %d\n", len);
		    printf("start: %d\n", start);
		    printf("rsize: %d\n", rsize);
		}

		/* copy post argument */
		MEMMOVE(&argv[start], &argv[r + rsize - psize], VALUE, psize);

		for (i=psize; i<len; i++) {
		    argv[start + i] = Qnil;
		}
		argv[r] = ary;
	    }
	    else {
		if (argc < r) {
		    /* yield 1
		     * => {|a, b, *r|}
		     */
		    for (i=argc; i<r; i++) {
			argv[i] = Qnil;
		    }
		    argv[r] = rb_ary_new();
		}
		else {
		    argv[r] = rb_ary_new4(argc-r, &argv[r]);
		}
	    }

	    th->mark_stack_len = iseq->arg_size;
	}

	/* {|&b|} */
	if (iseq->arg_block != -1) {
	    VALUE procval = Qnil;

	    if (blockptr) {
		procval = blockptr->proc;
	    }

	    argv[iseq->arg_block] = procval;
	}

	th->mark_stack_len = 0;
	return 0;
    }
}

static VALUE
vm_invoke_block(rb_thread_t *th, rb_control_frame_t *reg_cfp, rb_num_t num, rb_num_t flag)
{
    VALUE val;
    rb_block_t *block = GET_BLOCK_PTR();
    rb_iseq_t *iseq;
    int argc = num;

    if (GET_ISEQ()->local_iseq->type != ISEQ_TYPE_METHOD || block == 0) {
	vm_localjump_error("no block given (yield)", Qnil, 0);
    }
    iseq = block->iseq;

    argc = caller_setup_args(th, GET_CFP(), flag, argc, 0, 0);

    if (BUILTIN_TYPE(iseq) != T_NODE) {
	int opt_pc;
	const int arg_size = iseq->arg_size;
	VALUE *rsp = GET_SP() - argc;
	SET_SP(rsp);

	CHECK_STACK_OVERFLOW(GET_CFP(), iseq->stack_max);
	opt_pc = vm_yield_setup_args(th, iseq, argc, rsp, 0,
				     block_proc_is_lambda(block->proc));

	vm_push_frame(th, iseq,
		      FRAME_MAGIC_BLOCK, block->self, (VALUE) block->dfp,
		      iseq->iseq_encoded + opt_pc, rsp + arg_size, block->lfp,
		      iseq->local_size - arg_size);

	return Qundef;
    }
    else {
	val = vm_yield_with_cfunc(th, block, block->self, argc, STACK_ADDR_FROM_TOP(argc));
	POPN(argc); /* TODO: should put before C/yield? */
	return val;
    }
}

/* cref */

static NODE *
lfp_get_special_cref(VALUE *lfp)
{
    struct RValues *values;
    if (((VALUE)(values = (void *)lfp[-1])) != Qnil && values->basic.klass) {
	return (NODE *)values->basic.klass;
    }
    else {
	return 0;
    }
}

static struct RValues *
new_value(void)
{
    struct RValues *val = RVALUES(rb_newobj());
    OBJSETUP(val, 0, T_VALUES);
    val->v1 = val->v2 = val->v3 = Qnil;
    return val;
}

static struct RValues *
lfp_svar_place(rb_thread_t *th, VALUE *lfp)
{
    struct RValues *svar;

    if (th->local_lfp != lfp) {
	svar = (struct RValues *)lfp[-1];
	if ((VALUE)svar == Qnil) {
	    svar = new_value();
	    lfp[-1] = (VALUE)svar;
	}
    }
    else {
	svar = (struct RValues *)th->local_svar;
	if ((VALUE)svar == Qnil) {
	    svar = new_value();
	    th->local_svar = (VALUE)svar;
	}
    }
    return svar;
}

static VALUE
lfp_svar_get(rb_thread_t *th, VALUE *lfp, VALUE key)
{
    struct RValues *svar = lfp_svar_place(th, lfp);

    switch (key) {
      case 0:
	return svar->v1;
      case 1:
	return svar->v2;
      case 2:
	return svar->basic.klass;
      default: {
	VALUE hash = svar->v3;

	if (hash == Qnil) {
	    return Qnil;
	}
	else {
	    return rb_hash_lookup(hash, key);
	}
      }
    }
}

static void
lfp_svar_set(rb_thread_t *th, VALUE *lfp, VALUE key, VALUE val)
{
    struct RValues *svar = lfp_svar_place(th, lfp);

    switch (key) {
      case 0:
	svar->v1 = val;
	return;
      case 1:
	svar->v2 = val;
	return;
      case 2:
	svar->basic.klass = val;
	return;
      default: {
	VALUE hash = svar->v3;

	if (hash == Qnil) {
	    svar->v3 = hash = rb_hash_new();
	}
	rb_hash_aset(hash, key, val);
      }
    }
}

static NODE *
get_cref(rb_iseq_t *iseq, VALUE *lfp)
{
    NODE *cref;
    if ((cref = lfp_get_special_cref(lfp)) != 0) {
	/* */
    }
    else if ((cref = iseq->cref_stack) != 0) {
	/* */
    }
    else {
	rb_bug("get_cref: unreachable");
    }
    return cref;
}

static inline VALUE
vm_getspecial(rb_thread_t *th, VALUE *lfp, VALUE key, rb_num_t type)
{
    VALUE val;

    if (type == 0) {
	if (FIXNUM_P(key)) key = FIX2INT(key);
	val = lfp_svar_get(th, lfp, key);
    }
    else {
	VALUE backref = lfp_svar_get(th, lfp, 1);

	if (type & 0x01) {
	    switch (type >> 1) {
	      case '&':
		val = rb_reg_last_match(backref);
		break;
	      case '`':
		val = rb_reg_match_pre(backref);
		break;
	      case '\'':
		val = rb_reg_match_post(backref);
		break;
	      case '+':
		val = rb_reg_match_last(backref);
		break;
	      default:
		rb_bug("unexpected back-ref");
	    }
	}
	else {
	    val = rb_reg_nth_match(type >> 1, backref);
	}
    }
    return val;
}

static inline VALUE
vm_get_ev_const(rb_thread_t *th, rb_iseq_t *iseq,
		VALUE klass, ID id, int is_defined)
{
    VALUE val;

    if (klass == Qnil) {
	/* in current lexical scope */
	NODE *root_cref = get_cref(iseq, th->cfp->lfp);
	NODE *cref = root_cref;

	while (cref && cref->nd_next) {
	    klass = cref->nd_clss;
	    cref = cref->nd_next;

	    if (klass == 0) {
		continue;
	    }
	    if (NIL_P(klass)) {
		if (is_defined) {
		    /* TODO: check */
		    return 1;
		}
		else {
		    klass = CLASS_OF(th->cfp->self);
		    return rb_const_get(klass, id);
		}
	    }
	  search_continue:
	    if (RCLASS_IV_TBL(klass) &&
		st_lookup(RCLASS_IV_TBL(klass), id, &val)) {
		if (val == Qundef) {
		    rb_autoload_load(klass, id);
		    goto search_continue;
		}
		else {
		    if (is_defined) {
			return 1;
		    }
		    else {
			return val;
		    }
		}
	    }
	}
	klass = root_cref->nd_clss;
	if (is_defined) {
	    return rb_const_defined(klass, id);
	}
	else {
	    return rb_const_get(klass, id);
	}
    }
    else {
	switch (TYPE(klass)) {
	  case T_CLASS:
	  case T_MODULE:
	    break;
	  default:
	    rb_raise(rb_eTypeError, "%s is not a class/module",
		     RSTRING_PTR(rb_obj_as_string(klass)));
	}
	if (is_defined) {
	    return rb_const_defined(klass, id);
	}
	else {
	    return rb_const_get(klass, id);
	}
    }
}

static inline VALUE
vm_get_cvar_base(rb_thread_t *th, rb_iseq_t *iseq)
{
    NODE *cref = get_cref(iseq, th->cfp->lfp);
    VALUE klass = Qnil;

    if (cref) {
	klass = cref->nd_clss;
	if (!cref->nd_next) {
	    rb_warn("class variable access from toplevel");
	}
    }
    if (NIL_P(klass)) {
	rb_raise(rb_eTypeError, "no class variables available");
    }
    return klass;
}

static inline void
vm_define_method(rb_thread_t *th, VALUE obj,
		   ID id, rb_iseq_t *miseq, rb_num_t is_singleton, NODE *cref)
{
    NODE *newbody;
    int noex = cref->nd_visi;
    VALUE klass = cref->nd_clss;

    if (is_singleton) {
	if (FIXNUM_P(obj) || SYMBOL_P(obj)) {
	    rb_raise(rb_eTypeError,
		     "can't define singleton method \"%s\" for %s",
		     rb_id2name(id), rb_obj_classname(obj));
	}

	if (OBJ_FROZEN(obj)) {
	    rb_error_frozen("object");
	}

	klass = rb_singleton_class(obj);
	noex = NOEX_PUBLIC;
    }

    /* dup */
    COPY_CREF(miseq->cref_stack, cref);
    miseq->klass = klass;
    miseq->defined_method_id = id;
    newbody = NEW_NODE(RUBY_VM_METHOD_NODE, 0, miseq->self, 0);
    rb_add_method(klass, id, newbody, noex);

    if (!is_singleton && noex == NOEX_MODFUNC) {
	rb_add_method(rb_singleton_class(klass), id, newbody, NOEX_PUBLIC);
    }
    INC_VM_STATE_VERSION();
}

static inline NODE *
vm_method_search(VALUE id, VALUE klass, IC ic)
{
    NODE *mn;

#if OPT_INLINE_METHOD_CACHE
    {
	if (LIKELY(klass == ic->ic_class) &&
	    LIKELY(GET_VM_STATE_VERSION() == ic->ic_vmstat)) {
	    mn = ic->ic_method;
	}
	else {
	    mn = rb_method_node(klass, id);
	    ic->ic_class = klass;
	    ic->ic_method = mn;
	    ic->ic_vmstat = GET_VM_STATE_VERSION();
	}
    }
#else
    mn = rb_method_node(klass, id);
#endif
    return mn;
}

static inline VALUE
vm_search_normal_superclass(VALUE klass, VALUE recv)
{
    if (BUILTIN_TYPE(klass) == T_CLASS) {
	klass = RCLASS_SUPER(klass);
    }
    else if (BUILTIN_TYPE(klass) == T_MODULE) {
	VALUE k = CLASS_OF(recv);
	while (k) {
	    if (BUILTIN_TYPE(k) == T_ICLASS && RBASIC(k)->klass == klass) {
		klass = RCLASS_SUPER(k);
		break;
	    }
	    k = RCLASS_SUPER(k);
	}
    }
    return klass;
}

static void
vm_search_superclass(rb_control_frame_t *reg_cfp, rb_iseq_t *ip, VALUE recv, VALUE sigval, ID *idp, VALUE *klassp)
{
    ID id;
    VALUE klass;

    while (ip && !ip->klass) {
	ip = ip->parent_iseq;
    }

    if (ip == 0) {
	rb_raise(rb_eNoMethodError, "super called outside of method");
    }

    id = ip->defined_method_id;

    if (ip != ip->local_iseq) {
	/* defined by Module#define_method() */
	rb_control_frame_t *lcfp = GET_CFP();

	while (lcfp->iseq != ip) {
	    VALUE *tdfp = GET_PREV_DFP(lcfp->dfp);
	    while (1) {
		lcfp = RUBY_VM_PREVIOUS_CONTROL_FRAME(lcfp);
		if (lcfp->dfp == tdfp) {
		    break;
		}
	    }
	}

	id = lcfp->method_id;
	klass = vm_search_normal_superclass(lcfp->method_class, recv);

	if (sigval == Qfalse) {
	    /* zsuper */
	    rb_raise(rb_eRuntimeError, "implicit argument passing of super from method defined by define_method() is not supported. Specify all arguments explicitly.");
	}
    }
    else {
	klass = vm_search_normal_superclass(ip->klass, recv);
    }

    *idp = id;
    *klassp = klass;
}

static VALUE
vm_throw(rb_thread_t *th, rb_control_frame_t *reg_cfp, rb_num_t throw_state, VALUE throwobj)
{
    rb_num_t state = throw_state & 0xff;
    rb_num_t flag = throw_state & 0x8000;
    rb_num_t level = throw_state >> 16;

    if (state != 0) {
	VALUE *pt;
	int i;
	if (flag != 0) {
	    if (throw_state & 0x4000) {
		pt = (void *)1;
	    }
	    else {
		pt = 0;
	    }
	}
	else {
	    if (state == TAG_BREAK) {
		rb_control_frame_t *cfp = GET_CFP();
		VALUE *dfp = GET_DFP();
		int is_orphan = 1;
		rb_iseq_t *base_iseq = GET_ISEQ();

	      search_parent:
		if (cfp->iseq->type != ISEQ_TYPE_BLOCK) {
		    dfp = GC_GUARDED_PTR_REF((VALUE *) *dfp);
		    base_iseq = base_iseq->parent_iseq;

		    while ((VALUE *) cfp < th->stack + th->stack_size) {
			if (cfp->dfp == dfp) {
			    goto search_parent;
			}
			cfp++;
		    }
		    rb_bug("VM (throw): can't find break base.");
		}

		if (VM_FRAME_TYPE(cfp) == FRAME_MAGIC_LAMBDA) {
		    /* lambda{... break ...} */
		    is_orphan = 0;
		    pt = dfp;
		}
		else {
		    dfp = GC_GUARDED_PTR_REF((VALUE *) *dfp);

		    while ((VALUE *)cfp < th->stack + th->stack_size) {
			if (cfp->dfp == dfp) {
			    VALUE epc = epc = cfp->pc - cfp->iseq->iseq_encoded;
			    rb_iseq_t *iseq = cfp->iseq;
			    int i;

			    for (i=0; i<iseq->catch_table_size; i++) {
				struct iseq_catch_table_entry *entry = &iseq->catch_table[i];

				if (entry->type == CATCH_TYPE_BREAK &&
				    entry->start < epc && entry->end >= epc) {
				    if (entry->cont == epc) {
					goto found;
				    }
				    else {
					break;
				    }
				}
			    }
			    break;

			  found:
			    pt = dfp;
			    is_orphan = 0;
			    break;
			}
			cfp++;
		    }
		}

		if (is_orphan) {
		    vm_localjump_error("break from proc-closure", throwobj, TAG_BREAK);
		}
	    }
	    else if (state == TAG_RETRY) {
		pt = GC_GUARDED_PTR_REF((VALUE *) * GET_DFP());
		for (i = 0; i < level; i++) {
		    pt = GC_GUARDED_PTR_REF((VALUE *) * pt);
		}
	    }
	    else if (state == TAG_RETURN) {
		rb_control_frame_t *cfp = GET_CFP();
		VALUE *dfp = GET_DFP();
		int is_orphan = 1;

		/**
		 * check orphan:
		 */
		while ((VALUE *) cfp < th->stack + th->stack_size) {
		    if (GET_DFP() == dfp) {
			if (VM_FRAME_TYPE(cfp) == FRAME_MAGIC_LAMBDA) {
			    /* in lambda */
			    is_orphan = 0;
			    break;
			}
		    }
		    if (GET_LFP() == cfp->lfp &&
			cfp->iseq->type == ISEQ_TYPE_METHOD) {
			is_orphan = 0;
			break;
		    }
		    cfp++;
		}

		if (is_orphan) {
		    vm_localjump_error("unexpected return", throwobj, TAG_RETURN);
		}

		pt = GET_LFP();
	    }
	    else {
		rb_bug("isns(throw): unsupport throw type");
	    }
	}
	th->state = state;
	return (VALUE)NEW_THROW_OBJECT(throwobj, (VALUE) pt, state);
    }
    else {
	/* continue throw */
	VALUE err = throwobj;

	if (FIXNUM_P(err)) {
	    th->state = FIX2INT(err);
	}
	else if (SYMBOL_P(err)) {
	    th->state = TAG_THROW;
	}
	else if (BUILTIN_TYPE(err) == T_NODE) {
	    th->state = GET_THROWOBJ_STATE(err);
	}
	else {
	    th->state = TAG_RAISE;
	    /*th->state = FIX2INT(rb_ivar_get(err, idThrowState));*/
	}
	return err;
    }
}

static inline void
vm_expandarray(rb_control_frame_t *cfp, VALUE ary, int num, int flag)
{
    int is_splat = flag & 0x01;
    int space_size = num + is_splat;
    VALUE *base = cfp->sp, *ptr;
    volatile VALUE tmp_ary;
    int len;

    if (TYPE(ary) != T_ARRAY) {
	ary = rb_ary_to_ary(ary);
    }

    cfp->sp += space_size;

    tmp_ary = ary;
    ptr = RARRAY_PTR(ary);
    len = RARRAY_LEN(ary);

    if (flag & 0x02) {
	/* post: ..., nil ,ary[-1], ..., ary[0..-num] # top */
	int i = 0, j;

	if (len < num) {
	    for (i=0; i<num-len; i++) {
		*base++ = Qnil;
	    }
	}
	for (j=0; i<num; i++, j++) {
	    VALUE v = ptr[len - j - 1];
	    *base++ = v;
	}
	if (is_splat) {
	    *base = rb_ary_new4(len - j, ptr);
	}
    }
    else {
	/* normal: ary[num..-1], ary[num-2], ary[num-3], ..., ary[0] # top */
	int i;
	VALUE *bptr = &base[space_size - 1];

	for (i=0; i<num; i++) {
	    if (len <= i) {
		for (; i<num; i++) {
		    *bptr-- = Qnil;
		}
		break;
	    }
	    *bptr-- = ptr[i];
	}
	if (is_splat) {
	    if (num > len) {
		*bptr = rb_ary_new();
	    }
	    else {
		*bptr = rb_ary_new4(len - num, ptr + num);
	    }
	}
    }
}

static inline int
check_cfunc(NODE *mn, void *func)
{
    if (mn && nd_type(mn->nd_body) == NODE_CFUNC &&
	mn->nd_body->nd_cfnc == func) {
	return 1;
    }
    else {
	return 0;
    }
}

static VALUE
opt_eq_func(VALUE recv, VALUE obj, IC ic)
{
    VALUE val = Qundef;

    if (FIXNUM_2_P(recv, obj) &&
	BASIC_OP_UNREDEFINED_P(BOP_EQ)) {
	long a = FIX2LONG(recv), b = FIX2LONG(obj);

	if (a == b) {
	    val = Qtrue;
	}
	else {
	    val = Qfalse;
	}
    }
    else if (!SPECIAL_CONST_P(recv) && !SPECIAL_CONST_P(obj)) {
	if (HEAP_CLASS_OF(recv) == rb_cFloat &&
		 HEAP_CLASS_OF(obj) == rb_cFloat &&
		 BASIC_OP_UNREDEFINED_P(BOP_EQ)) {
	    double a = RFLOAT_VALUE(recv);
	    double b = RFLOAT_VALUE(obj);

	    if (isnan(a) || isnan(b)) {
		val = Qfalse;
	    }
	    else if (a == b) {
		val = Qtrue;
	    }
	    else {
		val = Qfalse;
	    }
	}
	else if (HEAP_CLASS_OF(recv) == rb_cString &&
		 HEAP_CLASS_OF(obj) == rb_cString &&
		 BASIC_OP_UNREDEFINED_P(BOP_EQ)) {
	    val = rb_str_equal(recv, obj);
	}
	else {
	    NODE *mn = vm_method_search(idEq, CLASS_OF(recv), ic);
	    extern VALUE rb_obj_equal(VALUE obj1, VALUE obj2);

	    if (check_cfunc(mn, rb_obj_equal)) {
		return recv == obj ? Qtrue : Qfalse;
	    }
	}
    }

    return val;
}
