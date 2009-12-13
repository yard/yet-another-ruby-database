/************************************************

  enumerator.c - provides Enumerator class

  $Author: nobu $

  Copyright (C) 2001-2003 Akinori MUSHA

  $Idaemons: /home/cvs/rb/enumerator/enumerator.c,v 1.1.1.1 2001/07/15 10:12:48 knu Exp $
  $RoughId: enumerator.c,v 1.6 2003/07/27 11:03:24 nobu Exp $
  $Id: enumerator.c 14416 2007-12-21 07:33:31Z nobu $

************************************************/

#include "ruby/ruby.h"
#include "debug.h"

/*
 * Document-class: Enumerable::Enumerator
 *
 * A class which provides a method `each' to be used as an Enumerable
 * object.
 */
static VALUE rb_cEnumerator;
static VALUE sym_each, sym_call;

VALUE rb_eStopIteration;

static VALUE
proc_call(VALUE proc, VALUE args)
{
    if (TYPE(args) != T_ARRAY) {
	args = rb_ary_new3(1, args);
    }
    return rb_proc_call(proc, args);
}

struct enumerator {
    VALUE method;
    VALUE proc;
    VALUE args;
    rb_block_call_func *iter;
    VALUE fib;
    VALUE dst;
    VALUE no_next;
};

static void
enumerator_mark(void *p)
{
    struct enumerator *ptr = p;
    rb_gc_mark(ptr->method);
    rb_gc_mark(ptr->proc);
    rb_gc_mark(ptr->args);
    rb_gc_mark(ptr->fib);
    rb_gc_mark(ptr->dst);
}

static struct enumerator *
enumerator_ptr(VALUE obj)
{
    struct enumerator *ptr;

    Data_Get_Struct(obj, struct enumerator, ptr);
    if (RDATA(obj)->dmark != enumerator_mark) {
	rb_raise(rb_eTypeError,
		 "wrong argument type %s (expected Enumerable::Enumerator)",
		 rb_obj_classname(obj));
    }
    if (!ptr) {
	rb_raise(rb_eArgError, "uninitialized enumerator");
    }
    return ptr;
}

static VALUE
enumerator_iter_i(VALUE i, VALUE enum_obj, int argc, VALUE *argv)
{
    struct enumerator *e = (struct enumerator *)enum_obj;
    return rb_yield(proc_call(e->proc, i));
}

/*
 *  call-seq:
 *    obj.to_enum(method = :each, *args)
 *    obj.enum_for(method = :each, *args)
 *
 *  Returns Enumerable::Enumerator.new(self, method, *args).
 *
 *  e.g.:
 *     str = "xyz"
 *
 *     enum = str.enum_for(:each_byte)
 *     a = enum.map {|b| '%02x' % b } #=> ["78", "79", "7a"]
 *
 *     # protects an array from being modified
 *     a = [1, 2, 3]
 *     some_method(a.to_enum)
 *
 */
static VALUE
obj_to_enum(int argc, VALUE *argv, VALUE obj)
{
    VALUE meth = sym_each;

    if (argc > 0) {
	--argc;
	meth = *argv++;
    }
    return rb_enumeratorize(obj, meth, argc, argv);
}

static VALUE
each_slice_i(VALUE val, VALUE *memo)
{
    VALUE ary = memo[0];
    VALUE v = Qnil;
    long size = (long)memo[1];

    rb_ary_push(ary, val);

    if (RARRAY_LEN(ary) == size) {
	v = rb_yield(ary);
	memo[0] = rb_ary_new2(size);
    }

    return v;
}

/*
 *  call-seq:
 *    e.each_slice(n) {...}
 *
 *  Iterates the given block for each slice of <n> elements.
 *
 *  e.g.:
 *      (1..10).each_slice(3) {|a| p a}
 *      # outputs below
 *      [1, 2, 3]
 *      [4, 5, 6]
 *      [7, 8, 9]
 *      [10]
 *
 */
static VALUE
enum_each_slice(VALUE obj, VALUE n)
{
    long size = NUM2LONG(n);
    VALUE args[2], ary;

    if (size <= 0) rb_raise(rb_eArgError, "invalid slice size");
    RETURN_ENUMERATOR(obj, 1, &n);
    args[0] = rb_ary_new2(size);
    args[1] = (VALUE)size;

    rb_block_call(obj, SYM2ID(sym_each), 0, 0, each_slice_i, (VALUE)args);

    ary = args[0];
    if (RARRAY_LEN(ary) > 0) rb_yield(ary);

    return Qnil;
}

static VALUE
each_cons_i(VALUE val, VALUE *memo)
{
    VALUE ary = memo[0];
    VALUE v = Qnil;
    long size = (long)memo[1];

    if (RARRAY_LEN(ary) == size) {
	rb_ary_shift(ary);
    }
    rb_ary_push(ary, val);
    if (RARRAY_LEN(ary) == size) {
	v = rb_yield(rb_ary_dup(ary));
    }
    return v;
}

/*
 *  call-seq:
 *    each_cons(n) {...}
 *
 *  Iterates the given block for each array of consecutive <n>
 *  elements.
 *
 *  e.g.:
 *      (1..10).each_cons(3) {|a| p a}
 *      # outputs below
 *      [1, 2, 3]
 *      [2, 3, 4]
 *      [3, 4, 5]
 *      [4, 5, 6]
 *      [5, 6, 7]
 *      [6, 7, 8]
 *      [7, 8, 9]
 *      [8, 9, 10]
 *
 */
static VALUE
enum_each_cons(VALUE obj, VALUE n)
{
    long size = NUM2LONG(n);
    VALUE args[2];

    if (size <= 0) rb_raise(rb_eArgError, "invalid size");
    RETURN_ENUMERATOR(obj, 1, &n);
    args[0] = rb_ary_new2(size);
    args[1] = (VALUE)size;

    rb_block_call(obj, SYM2ID(sym_each), 0, 0, each_cons_i, (VALUE)args);

    return Qnil;
}

static VALUE
enumerator_allocate(VALUE klass)
{
    struct enumerator *ptr;
    return Data_Make_Struct(klass, struct enumerator,
			    enumerator_mark, -1, ptr);
}

static VALUE
enumerator_each_i(VALUE v, VALUE enum_obj, int argc, VALUE *argv)
{
    return rb_yield_values2(argc, argv);
}

static VALUE
enumerator_init(VALUE enum_obj, VALUE obj, VALUE meth, int argc, VALUE *argv)
{
    struct enumerator *ptr = enumerator_ptr(enum_obj);

    ptr->method = rb_obj_method(obj, meth);
    if (rb_block_given_p()) {
	ptr->proc = rb_block_proc();
	ptr->iter = enumerator_iter_i;
    }
    else {
	ptr->iter = enumerator_each_i;
    }
    if (argc) ptr->args = rb_ary_new4(argc, argv);
    ptr->fib = 0;
    ptr->dst = Qnil;
    ptr->no_next = Qfalse;

    return enum_obj;
}

/*
 *  call-seq:
 *    Enumerable::Enumerator.new(obj, method = :each, *args)
 *
 *  Creates a new Enumerable::Enumerator object, which is to be
 *  used as an Enumerable object using the given object's given
 *  method with the given arguments.
 *
 *  e.g.:
 *      str = "xyz"
 *
 *      enum = Enumerable::Enumerator.new(str, :each_byte)
 *      a = enum.map {|b| '%02x' % b } #=> ["78", "79", "7a"]
 *
 */
static VALUE
enumerator_initialize(int argc, VALUE *argv, VALUE obj)
{
    VALUE recv, meth = sym_each;

    if (argc == 0)
	rb_raise(rb_eArgError, "wrong number of argument (0 for 1)");
    recv = *argv++;
    if (--argc) {
	meth = *argv++;
	--argc;
    }
    return enumerator_init(obj, recv, meth, argc, argv);
}

/* :nodoc: */
static VALUE
enumerator_init_copy(VALUE obj, VALUE orig)
{
    struct enumerator *ptr0, *ptr1;

    ptr0 = enumerator_ptr(orig);
    if (ptr0->fib) {
	/* Fibers cannot be copied */
	rb_raise(rb_eTypeError, "can't copy execution context");
    }
    ptr1 = enumerator_ptr(obj);

    ptr1->method = ptr0->method;
    ptr1->proc = ptr0->proc;
    ptr1->iter = ptr0->iter;
    ptr1->args = ptr0->args;
    ptr1->fib  = 0;

    return obj;
}

VALUE
rb_enumeratorize(VALUE obj, VALUE meth, int argc, VALUE *argv)
{
    return enumerator_init(enumerator_allocate(rb_cEnumerator), obj, meth, argc, argv);
}

/*
 *  call-seq:
 *    enum.each {...}
 *
 *  Iterates the given block using the object and the method specified
 *  in the first place.
 *
 */
static VALUE
enumerator_each(VALUE obj)
{
    struct enumerator *e;
    int argc = 0;
    VALUE *argv = 0;

    if (!rb_block_given_p()) return obj;
    e = enumerator_ptr(obj);
    if (e->args) {
	argc = RARRAY_LEN(e->args);
	argv = RARRAY_PTR(e->args);
    }
    return rb_block_call(e->method, SYM2ID(sym_call), argc, argv, e->iter, (VALUE)e);
}

static VALUE
enumerator_with_index_i(VALUE val, VALUE *memo)
{
    val = rb_yield_values(2, val, INT2FIX(*memo));
    ++*memo;
    return val;
}

/*
 *  call-seq:
 *    e.with_index {|(*args), idx| ... }
 *
 *  Iterates the given block for each elements with an index, which
 *  start from 0.
 *
 */
static VALUE
enumerator_with_index(VALUE obj)
{
    struct enumerator *e = enumerator_ptr(obj);
    VALUE memo = 0;
    int argc = 0;
    VALUE *argv = 0;

    RETURN_ENUMERATOR(obj, 0, 0);
    if (e->args) {
	argc = RARRAY_LEN(e->args);
	argv = RARRAY_PTR(e->args);
    }
    return rb_block_call(e->method, SYM2ID(sym_call), argc, argv,
			 enumerator_with_index_i, (VALUE)&memo);
}

static VALUE
next_ii(VALUE i, VALUE obj)
{
    rb_fiber_yield(1, &i);
    return Qnil;
}

static VALUE
next_i(VALUE curr, VALUE obj)
{
    struct enumerator *e = enumerator_ptr(obj);
    VALUE nil = Qnil;

    rb_block_call(obj, rb_intern("each"), 0, 0, next_ii, obj);
    e->no_next = Qtrue;
    return rb_fiber_yield(1, &nil);
}

static void
next_init(VALUE obj, struct enumerator *e)
{
    VALUE curr = rb_fiber_current();
    e->dst = curr;
    e->fib = rb_fiber_new(next_i, obj);
}

/*
 * call-seq:
 *   e.next   => object
 *
 * Returns the next object in the enumerator, and move the internal
 * position forward.  When the position reached at the end, internal
 * position is rewinded then StopIteration is raised.
 *
 * Note that enumeration sequence by next method does not affect other
 * non-external enumeration methods, unless underlying iteration
 * methods itself has side-effect, e.g. IO#each_line.
 *
 */

static VALUE
enumerator_next(VALUE obj)
{
    struct enumerator *e = enumerator_ptr(obj);
    VALUE curr, v;
    curr = rb_fiber_current();

    if (!e->fib || !rb_fiber_alive_p(e->fib)) {
	next_init(obj, e);
    }

    v = rb_fiber_resume(e->fib, 1, &curr);
    if (e->no_next) {
	e->fib = 0;
	e->dst = Qnil;
	e->no_next = Qfalse;
	rb_raise(rb_eStopIteration, "iteration reached at end");
    }
    return v;
}

/*
 * call-seq:
 *   e.next?   => e
 *
 * Rewinds the enumeration sequence by the next method.
 */

static VALUE
enumerator_rewind(VALUE obj)
{
    struct enumerator *e = enumerator_ptr(obj);

    e->fib = 0;
    e->dst = Qnil;
    e->no_next = Qfalse;
    return obj;
}

void
Init_Enumerator(void)
{
    rb_define_method(rb_mKernel, "to_enum", obj_to_enum, -1);
    rb_define_method(rb_mKernel, "enum_for", obj_to_enum, -1);

    rb_define_method(rb_mEnumerable, "each_slice", enum_each_slice, 1);
    rb_define_method(rb_mEnumerable, "each_cons", enum_each_cons, 1);

    rb_cEnumerator = rb_define_class_under(rb_mEnumerable, "Enumerator", rb_cObject);
    rb_include_module(rb_cEnumerator, rb_mEnumerable);

    rb_define_alloc_func(rb_cEnumerator, enumerator_allocate);
    rb_define_method(rb_cEnumerator, "initialize", enumerator_initialize, -1);
    rb_define_method(rb_cEnumerator, "initialize_copy", enumerator_init_copy, 1);
    rb_define_method(rb_cEnumerator, "each", enumerator_each, 0);
    rb_define_method(rb_cEnumerator, "with_index", enumerator_with_index, 0);
    rb_define_method(rb_cEnumerator, "next", enumerator_next, 0);
    rb_define_method(rb_cEnumerator, "rewind", enumerator_rewind, 0);

    rb_eStopIteration   = rb_define_class("StopIteration", rb_eIndexError);

    sym_each		= ID2SYM(rb_intern("each"));
    sym_call		= ID2SYM(rb_intern("call"));

    rb_provide("enumerator.so");	/* for backward compatibility */
}
