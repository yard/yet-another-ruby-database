/**********************************************************************

  insnhelper.h - helper macros to implement each instructions

  $Author: ko1 $
  $Date: 2007-11-14 07:13:04 +0900 (Wed, 14 Nov 2007) $
  created at: 04/01/01 15:50:34 JST

  Copyright (C) 2004-2007 Koichi Sasada

**********************************************************************/

#ifndef _INSNHELPER_H_INCLUDED_
#define _INSNHELPER_H_INCLUDED_

#include "ruby/ruby.h"
#include "ruby/node.h"
#include "eval_intern.h"
#include "vm_core.h"
#include "vm.h"

/**********************************************************/
/* deal with stack                                        */
/**********************************************************/

#define PUSH(x) (SET_SV(x), INC_SP(1))
#define TOPN(n) (*(GET_SP()-(n)-1))
#define POPN(n) (DEC_SP(n))
#define POP()   (DEC_SP(1))
#define STACK_ADDR_FROM_TOP(n) (GET_SP()-(n))

#define GET_TOS()  (tos)	/* dummy */

/**********************************************************/
/* deal with registers                                    */
/**********************************************************/

#define REG_CFP (reg_cfp)
#define REG_PC  (REG_CFP->pc)
#define REG_SP  (REG_CFP->sp)
#define REG_LFP (REG_CFP->lfp)
#define REG_DFP (REG_CFP->dfp)

#define RESTORE_REGS() do { \
  REG_CFP = th->cfp; \
} while (0)

#define REG_A   reg_a
#define REG_B   reg_b

#ifdef COLLECT_USAGE_ANALYSIS
#define USAGE_ANALYSIS_REGISTER_HELPER(a, b, v) \
  (USAGE_ANALYSIS_REGISTER(a, b), (v))
#else
#define USAGE_ANALYSIS_REGISTER_HELPER(a, b, v) (v)
#endif

/* PC */
#define GET_PC()           (USAGE_ANALYSIS_REGISTER_HELPER(0, 0, REG_PC))
#define SET_PC(x)          (REG_PC = (USAGE_ANALYSIS_REGISTER_HELPER(0, 1, x)))
#define GET_CURRENT_INSN() (*GET_PC())
#define GET_OPERAND(n)     (GET_PC()[(n)])
#define ADD_PC(n)          (SET_PC(REG_PC + (n)))

#define GET_PC_COUNT()     (REG_PC - GET_ISEQ()->iseq_encoded)
#define JUMP(dst)          (REG_PC += (dst))

/* FP */
#define GET_CFP()  (USAGE_ANALYSIS_REGISTER_HELPER(2, 0, REG_CFP))
#define GET_LFP()  (USAGE_ANALYSIS_REGISTER_HELPER(3, 0, REG_LFP))
#define SET_LFP(x) (REG_LFP = (USAGE_ANALYSIS_REGISTER_HELPER(3, 1, (x))))
#define GET_DFP()  (USAGE_ANALYSIS_REGISTER_HELPER(4, 0, REG_DFP))
#define SET_DFP(x) (REG_DFP = (USAGE_ANALYSIS_REGISTER_HELPER(4, 1, (x))))

/* SP */
#define GET_SP()   (USAGE_ANALYSIS_REGISTER_HELPER(1, 0, REG_SP))
#define SET_SP(x)  (REG_SP  = (USAGE_ANALYSIS_REGISTER_HELPER(1, 1, (x))))
#define INC_SP(x)  (REG_SP += (USAGE_ANALYSIS_REGISTER_HELPER(1, 1, (x))))
#define DEC_SP(x)  (REG_SP -= (USAGE_ANALYSIS_REGISTER_HELPER(1, 1, (x))))
#define SET_SV(x)  (*GET_SP() = (x))
  /* set current stack value as x */

#define GET_SP_COUNT() (REG_SP - th->stack)

/* instruction sequence C struct */
#define GET_ISEQ() (GET_CFP()->iseq)

/**********************************************************/
/* deal with variables                                    */
/**********************************************************/

#define GET_PREV_DFP(dfp)                ((VALUE *)((dfp)[0] & ~0x03))

#define GET_GLOBAL(entry)       rb_gvar_get((struct global_entry*)entry)
#define SET_GLOBAL(entry, val)  rb_gvar_set((struct global_entry*)entry, val)

#define GET_CONST_INLINE_CACHE(dst) ((IC) * (GET_PC() + (dst) + 1))

/**********************************************************/
/* deal with values                                       */
/**********************************************************/

#define GET_SELF() (USAGE_ANALYSIS_REGISTER_HELPER(5, 0, GET_CFP()->self))

/**********************************************************/
/* deal with control flow 2: method/iterator              */
/**********************************************************/

#define COPY_CREF(c1, c2) do {  \
  NODE *__tmp_c2 = (c2); \
  c1->nd_clss = __tmp_c2->nd_clss; \
  c1->nd_visi = __tmp_c2->nd_visi; \
  c1->nd_next = __tmp_c2->nd_next; \
} while (0)

#define CALL_METHOD(num, blockptr, flag, id, mn, recv, klass) do { \
    VALUE v = vm_call_method(th, GET_CFP(), num, blockptr, flag, id, mn, recv, klass); \
    if (v == Qundef) { \
	RESTORE_REGS(); \
	NEXT_INSN(); \
    } \
    else { \
	val = v; \
    } \
} while (0)

#define GET_BLOCK_PTR() \
  ((rb_block_t *)(GC_GUARDED_PTR_REF(GET_LFP()[0])))

/**********************************************************/
/* deal with control flow 3: exception                    */
/**********************************************************/


/**********************************************************/
/* others                                                 */
/**********************************************************/

/* optimize insn */
#define FIXNUM_2_P(a, b) ((a) & (b) & 1)
#define BASIC_OP_UNREDEFINED_P(op) ((ruby_vm_redefined_flag & (op)) == 0)
#define HEAP_CLASS_OF(obj) RBASIC(obj)->klass

#define CALL_SIMPLE_METHOD(num, id, recv) do { \
    VALUE klass = CLASS_OF(recv); \
    CALL_METHOD(num, 0, 0, id, rb_method_node(klass, id), recv, CLASS_OF(recv)); \
} while (0)

#endif /* _INSNHELPER_H_INCLUDED_ */
