/**********************************************************************

  array.c -

  $Author: akr $
  $Date: 2007-12-24 17:19:28 +0900 (Mon, 24 Dec 2007) $
  created at: Fri Aug  6 09:46:12 JST 1993

  Copyright (C) 1993-2007 Yukihiro Matsumoto
  Copyright (C) 2000  Network Applied Communication Laboratory, Inc.
  Copyright (C) 2000  Information-technology Promotion Agency, Japan

**********************************************************************/

#include "ruby/ruby.h"
#include "ruby/util.h"
#include "ruby/st.h"

#include "yard/include/yard.h"

VALUE rb_cArray;

static ID id_cmp;

#define ARY_DEFAULT_SIZE 16

void
rb_mem_clear(register VALUE *mem, register long size)
{
    while (size--) {
  *mem++ = Qnil;
    }
}

static inline void
memfill(register VALUE *mem, register long size, register VALUE val)
{
    while (size--) {
  *mem++ = val;
    }
}

#define ARY_ITERLOCK FL_USER1
static void
ary_iter_check(VALUE ary)
{
    if (FL_TEST(ary, ARY_ITERLOCK)) {
      rb_raise(rb_eRuntimeError, "can't modify array during iteration");
    }
}
#define ARY_SORTLOCK FL_USER3
#define ARY_SHARED_P(a) FL_TEST(a, ELTS_SHARED)

#define ARY_SET_LEN(ary, n) do { \
    RARRAY(ary)->len = (n);\
} while (0) 

#define ARY_CAPA(ary) RARRAY(ary)->aux.capa
#define RESIZE_CAPA(ary,capacity) do {\
    REALLOC_N(RARRAY(ary)->ptr, VALUE, (capacity));\
    RARRAY(ary)->aux.capa = (capacity);\
} while (0)

#define ITERATE(func, ary) do { \
    FL_SET(ary, ARY_ITERLOCK); \
    return rb_ensure(func, (ary), each_unlock, (ary));\
} while (0)

static inline void
rb_ary_modify_check(VALUE ary)
{
    if (OBJ_FROZEN(ary)) rb_error_frozen("array");
    if (FL_TEST(ary, ARY_SORTLOCK))
  rb_raise(rb_eRuntimeError, "can't modify array during sort");
    if (!OBJ_TAINTED(ary) && rb_safe_level() >= 4)
  rb_raise(rb_eSecurityError, "Insecure: can't modify array");
}

static void
rb_ary_modify(VALUE ary)
{
    VALUE *ptr;

    rb_ary_modify_check(ary);
    if (ARY_SHARED_P(ary)) {
  ptr = ALLOC_N(VALUE, RARRAY_LEN(ary));
  FL_UNSET(ary, ELTS_SHARED);
  RARRAY(ary)->aux.capa = RARRAY_LEN(ary);
  MEMCPY(ptr, RARRAY_PTR(ary), VALUE, RARRAY_LEN(ary));
  RARRAY(ary)->ptr = ptr;
    }
}

VALUE
rb_ary_freeze(VALUE ary)
{
    return rb_obj_freeze(ary);
}

/*
 *  call-seq:
 *     array.frozen?  -> true or false
 *
 *  Return <code>true</code> if this array is frozen (or temporarily frozen
 *  while being sorted).
 */

static VALUE
rb_ary_frozen_p(VALUE ary)
{
    if (OBJ_FROZEN(ary)) return Qtrue;
    if (FL_TEST(ary, ARY_SORTLOCK)) return Qtrue;
    return Qfalse;
}

static VALUE
ary_alloc(VALUE klass)
{
    NEWOBJ(ary, struct RArray);
    OBJSETUP(ary, klass, T_ARRAY);

    ary->len = 0;
    ary->ptr = 0;
    ary->aux.capa = 0;

    return (VALUE)ary;
}

static VALUE
ary_new(VALUE klass, long len)
{
    VALUE ary;

    if (len < 0) {
  rb_raise(rb_eArgError, "negative array size (or size too big)");
    }
    if (len > 0 && len * sizeof(VALUE) <= len) {
  rb_raise(rb_eArgError, "array size too big");
    }
    ary = ary_alloc(klass);
    if (len == 0) len++;
    RARRAY(ary)->ptr = ALLOC_N(VALUE, len);
    RARRAY(ary)->aux.capa = len;

    return ary;
}

VALUE
rb_ary_new2(long len)
{
    return ary_new(rb_cArray, len);
}


VALUE
rb_ary_new(void)
{
    return rb_ary_new2(ARY_DEFAULT_SIZE);
}

#include <stdarg.h>

VALUE
rb_ary_new3(long n, ...)
{
    va_list ar;
    VALUE ary;
    long i;

    ary = rb_ary_new2(n);

    va_start(ar, n);
    for (i=0; i<n; i++) {
  RARRAY_PTR(ary)[i] = va_arg(ar, VALUE);
    }
    va_end(ar);

    RARRAY(ary)->len = n;
    return ary;
}

VALUE
rb_ary_new4(long n, const VALUE *elts)
{
    VALUE ary;

    ary = rb_ary_new2(n);
    if (n > 0 && elts) {
  MEMCPY(RARRAY_PTR(ary), elts, VALUE, n);
  RARRAY(ary)->len = n;
    }

    return ary;
}

void
rb_ary_free(VALUE ary)
{
    if (!ARY_SHARED_P(ary)) {
  xfree(RARRAY(ary)->ptr);
    }
}

static VALUE
ary_make_shared(VALUE ary)
{
    if (ARY_SHARED_P(ary)) {
  return RARRAY(ary)->aux.shared;
    }
    else {
  NEWOBJ(shared, struct RArray);
  OBJSETUP(shared, 0, T_ARRAY);

  shared->len = RARRAY(ary)->len;
  shared->ptr = RARRAY(ary)->ptr;
  shared->aux.capa = RARRAY(ary)->aux.capa;
  RARRAY(ary)->aux.shared = (VALUE)shared;
  FL_SET(ary, ELTS_SHARED);
  OBJ_FREEZE(shared);
  return (VALUE)shared;
    }
}

VALUE
rb_assoc_new(VALUE car, VALUE cdr)
{
    return rb_ary_new3(2, car, cdr);
}

static VALUE
to_ary(VALUE ary)
{
    return rb_convert_type(ary, T_ARRAY, "Array", "to_ary");
}

VALUE
rb_check_array_type(VALUE ary)
{
    return rb_check_convert_type(ary, T_ARRAY, "Array", "to_ary");
}

/*
 *  call-seq:
 *     Array.try_convert(obj) -> array or nil
 *
 *  Try to convert <i>obj</i> into an array, using to_ary method.
 *  Returns converted array or nil if <i>obj</i> cannot be converted
 *  for any reason.  This method is to check if an argument is an
 *  array.  
 *
 *     Array.try_convert([1])   # => [1]
 *     Array.try_convert("1")   # => nil
 *     
 *     if tmp = Array.try_convert(arg)
 *       # the argument is an array
 *     elsif tmp = String.try_convert(arg)
 *       # the argument is a string
 *     end
 *
 */

static VALUE
rb_ary_s_try_convert(VALUE dummy, VALUE ary)
{
    return rb_check_array_type(ary);
}

/*
 *  call-seq:
 *     Array.new(size=0, obj=nil)
 *     Array.new(array)
 *     Array.new(size) {|index| block }
 *
 *  Returns a new array. In the first form, the new array is
 *  empty. In the second it is created with _size_ copies of _obj_
 *  (that is, _size_ references to the same
 *  _obj_). The third form creates a copy of the array
 *  passed as a parameter (the array is generated by calling
 *  to_ary  on the parameter). In the last form, an array
 *  of the given size is created. Each element in this array is
 *  calculated by passing the element's index to the given block and
 *  storing the return value.
 *
 *     Array.new
 *     Array.new(2)
 *     Array.new(5, "A")
 * 
 *     # only one copy of the object is created
 *     a = Array.new(2, Hash.new)
 *     a[0]['cat'] = 'feline'
 *     a
 *     a[1]['cat'] = 'Felix'
 *     a
 * 
 *     # here multiple copies are created
 *     a = Array.new(2) { Hash.new }
 *     a[0]['cat'] = 'feline'
 *     a
 * 
 *     squares = Array.new(5) {|i| i*i}
 *     squares
 * 
 *     copy = Array.new(squares)
 */

static VALUE
rb_ary_initialize(int argc, VALUE *argv, VALUE ary)
{
    long len;
    VALUE size, val;

    rb_ary_modify(ary);
    ary_iter_check(ary);
    if (rb_scan_args(argc, argv, "02", &size, &val) == 0) {
  if (RARRAY_PTR(ary) && !ARY_SHARED_P(ary)) {
      free(RARRAY(ary)->ptr);
  }
  RARRAY(ary)->len = 0;
  if (rb_block_given_p()) {
      rb_warning("given block not used");
  }
  return ary;
    }

    if (argc == 1 && !FIXNUM_P(size)) {
  val = rb_check_array_type(size);
  if (!NIL_P(val)) {
      rb_ary_replace(ary, val);
      return ary;
  }
    }

    len = NUM2LONG(size);
    if (len < 0) {
  rb_raise(rb_eArgError, "negative array size");
    }
    if (len > 0 && len * (long)sizeof(VALUE) <= len) {
  rb_raise(rb_eArgError, "array size too big");
    }
    rb_ary_modify(ary);
  RESIZE_CAPA(ary, len);
    if (rb_block_given_p()) {
  long i;

  if (argc == 2) {
      rb_warn("block supersedes default value argument");
  }
  for (i=0; i<len; i++) {
      rb_ary_store(ary, i, rb_yield(LONG2NUM(i)));
      RARRAY(ary)->len = i + 1;
  }
    }
    else {
  memfill(RARRAY_PTR(ary), len, val);
  RARRAY(ary)->len = len;
    }
    return ary;
}


/* 
* Returns a new array populated with the given objects. 
*
*   Array.[]( 1, 'a', /^A/ )
*   Array[ 1, 'a', /^A/ ]
*   [ 1, 'a', /^A/ ]
*/

static VALUE
rb_ary_s_create(int argc, VALUE *argv, VALUE klass)
{
    VALUE ary = ary_alloc(klass);

    if (argc < 0) {
  rb_raise(rb_eArgError, "negative array size");
    }
    RARRAY(ary)->ptr = ALLOC_N(VALUE, argc);
    RARRAY(ary)->aux.capa = argc;
    MEMCPY(RARRAY_PTR(ary), argv, VALUE, argc);
    RARRAY(ary)->len = argc;

    return ary;
}

void
rb_ary_store(VALUE ary, long idx, VALUE val)
{
  if (idx < 0) {
      idx += RARRAY_LEN(ary);
      if (idx < 0) {
        rb_raise(rb_eIndexError, "index %ld out of array",
        idx - RARRAY_LEN(ary));
      }
  }

  rb_ary_modify(ary);
  if (idx >= ARY_CAPA(ary)) {
    long new_capa = ARY_CAPA(ary) / 2;

    if (new_capa < ARY_DEFAULT_SIZE) {
        new_capa = ARY_DEFAULT_SIZE;
    }
    if (new_capa + idx < new_capa) {
        rb_raise(rb_eArgError, "index too big");
    }
    new_capa += idx;
    if (new_capa * (long)sizeof(VALUE) <= new_capa) {
        rb_raise(rb_eArgError, "index too big");
    }
    RESIZE_CAPA(ary, new_capa);
  }
  
  if (idx > RARRAY_LEN(ary)) {
    rb_mem_clear(RARRAY_PTR(ary) + RARRAY_LEN(ary), idx-RARRAY_LEN(ary) + 1);
  }

  if (idx >= RARRAY_LEN(ary)) {
    RARRAY(ary)->len = idx + 1;
  }
  
  RARRAY_PTR(ary)[idx] = val;
    
  yard_object_modification(ary, val, YARD_ARRAY_ELEMENT_PUSH, idx);
}

static VALUE
ary_shared_array(VALUE klass, VALUE ary)
{
    VALUE val = ary_alloc(klass);

    ary_make_shared(ary);
    RARRAY(val)->ptr = RARRAY(ary)->ptr;
    RARRAY(val)->len = RARRAY(ary)->len;
    RARRAY(val)->aux.shared = RARRAY(ary)->aux.shared;
    FL_SET(val, ELTS_SHARED);
    return val;
}

static VALUE
ary_shared_first(int argc, VALUE *argv, VALUE ary, int last)
{
    VALUE nv, result;
    long n;
    long offset = 0;

    rb_scan_args(argc, argv, "1", &nv);
    n = NUM2LONG(nv);
    if (n > RARRAY_LEN(ary)) {
  n = RARRAY_LEN(ary);
    }
    else if (n < 0) {
  rb_raise(rb_eArgError, "negative array size");
    }
    if (last) {
  offset = RARRAY_LEN(ary) - n;
    }
    result = ary_shared_array(rb_cArray, ary);
    RARRAY(result)->ptr += offset;
    RARRAY(result)->len = n;

    return result;
}

/*
 *  call-seq:
 *     array << obj            -> array
 *  
 *  Append---Pushes the given object on to the end of this array. This
 *  expression returns the array itself, so several appends
 *  may be chained together.
 *
 *     [ 1, 2 ] << "c" << "d" << [ 3, 4 ]
 *             #=>  [ 1, 2, "c", "d", [ 3, 4 ] ]
 *
 */

VALUE
rb_ary_push(VALUE ary, VALUE item)
{
    rb_ary_store(ary, RARRAY_LEN(ary), item);
    return ary;
}

/* 
 *  call-seq:
 *     array.push(obj, ... )   -> array
 *  
 *  Append---Pushes the given object(s) on to the end of this array. This
 *  expression returns the array itself, so several appends
 *  may be chained together.
 *
 *     a = [ "a", "b", "c" ]
 *     a.push("d", "e", "f")  
 *             #=> ["a", "b", "c", "d", "e", "f"]
 */

static VALUE
rb_ary_push_m(int argc, VALUE *argv, VALUE ary)
{
    while (argc--) {
  rb_ary_push(ary, *argv++);
    }
    return ary;
}

VALUE
rb_ary_pop(VALUE ary)
{
    long n;
    rb_ary_modify_check(ary);
    if (RARRAY_LEN(ary) == 0) return Qnil;
    if (!ARY_SHARED_P(ary) &&
  RARRAY_LEN(ary) * 3 < ARY_CAPA(ary) &&
  ARY_CAPA(ary) > ARY_DEFAULT_SIZE)
    {
  RESIZE_CAPA(ary, RARRAY_LEN(ary) * 2);
    }
    n = RARRAY_LEN(ary)-1;
    RARRAY(ary)->len = n;
    return yard_resolve_stub(RARRAY_PTR(ary)[n]);
}

/*
 *  call-seq:
 *     array.pop  -> obj or nil
 *  
 *  Removes the last element from <i>self</i> and returns it, or
 *  <code>nil</code> if the array is empty.
 *     
 *     a = [ "a", "b", "c", "d" ]
 *     a.pop     #=> "d"
 *     a.pop(2)  #=> ["b", "c"]
 *     a         #=> ["a"]
 */

static VALUE
rb_ary_pop_m(int argc, VALUE *argv, VALUE ary)
{
    VALUE result;

    if (argc == 0) {
  return rb_ary_pop(ary);
    }

    rb_ary_modify_check(ary);
    result = ary_shared_first(argc, argv, ary, Qtrue);
    RARRAY(ary)->len -= RARRAY_LEN(result);
    return result;
}

VALUE
rb_ary_shift(VALUE ary)
{
    VALUE top;

    rb_ary_modify_check(ary);
    ary_iter_check(ary);
    if (RARRAY_LEN(ary) == 0) return Qnil;
    top = yard_resolve_stub(RARRAY_PTR(ary)[0]);
    if (!ARY_SHARED_P(ary)) {
  if (RARRAY_LEN(ary) < ARY_DEFAULT_SIZE) {
      MEMMOVE(RARRAY_PTR(ary), RARRAY_PTR(ary)+1, VALUE, RARRAY_LEN(ary)-1);
      RARRAY(ary)->len--;
      return top;
  }
  RARRAY_PTR(ary)[0] = Qnil;
  ary_make_shared(ary);
    }
    RARRAY(ary)->ptr++;		/* shift ptr */
    RARRAY(ary)->len--;

    return top;
}

/*
 *  call-seq:
 *     array.shift   ->   obj or nil
 *  
 *  Returns the first element of <i>self</i> and removes it (shifting all
 *  other elements down by one). Returns <code>nil</code> if the array
 *  is empty.
 *     
 *     args = [ "-m", "-q", "filename" ]
 *     args.shift     #=> "-m"
 *     args           #=> ["-q", "filename"]
 *
 *     args = [ "-m", "-q", "filename" ]
 *     args.shift(2)  #=> ["-m", "-q"]
 *     args           #=> ["filename"]
 */

static VALUE
rb_ary_shift_m(int argc, VALUE *argv, VALUE ary)
{
    VALUE result;
    long n;

    if (argc == 0) {
  return rb_ary_shift(ary);
    }

    rb_ary_modify_check(ary);
    ary_iter_check(ary);
    result = ary_shared_first(argc, argv, ary, Qfalse);
    n = RARRAY_LEN(result);
    if (ARY_SHARED_P(ary)) {
  RARRAY(ary)->ptr += n;
  RARRAY(ary)->len -= n;
  }
    else {
  MEMMOVE(RARRAY_PTR(ary), RARRAY_PTR(ary)+n, VALUE, RARRAY_LEN(ary)-n);
  RARRAY(ary)->len -= n;
    }

    return result;
}

/*
 *  call-seq:
 *     array.unshift(obj, ...)  -> array
 *  
 *  Prepends objects to the front of <i>array</i>.
 *  other elements up one.
 *     
 *     a = [ "b", "c", "d" ]
 *     a.unshift("a")   #=> ["a", "b", "c", "d"]
 *     a.unshift(1, 2)  #=> [ 1, 2, "a", "b", "c", "d"]
 */

static VALUE
rb_ary_unshift_m(int argc, VALUE *argv, VALUE ary)
{
    long len = RARRAY(ary)->len;

    if (argc == 0) return ary;
    rb_ary_modify(ary);
    ary_iter_check(ary);
    if (RARRAY(ary)->aux.capa <= RARRAY_LEN(ary)+argc) {
  RESIZE_CAPA(ary, RARRAY(ary)->aux.capa + ARY_DEFAULT_SIZE);
    }

    /* sliding items */
    MEMMOVE(RARRAY(ary)->ptr + argc, RARRAY(ary)->ptr, VALUE, len);
    MEMCPY(RARRAY(ary)->ptr, argv, VALUE, argc);
    RARRAY(ary)->len += argc;
    
    return ary;
}

VALUE
rb_ary_unshift(VALUE ary, VALUE item)
{
    return rb_ary_unshift_m(1,&item,ary);
}

/* faster version - use this if you don't need to treat negative offset */
static inline VALUE
rb_ary_elt(VALUE ary, long offset)
{
    if (RARRAY_LEN(ary) == 0) return Qnil;
    if (offset < 0 || RARRAY_LEN(ary) <= offset) {
      return Qnil;
    }
    
    return yard_resolve_stub(RARRAY_PTR(ary)[offset]);
}

VALUE
rb_ary_entry(VALUE ary, long offset)
{
    if (offset < 0) {
      offset += RARRAY_LEN(ary);
    }
    return rb_ary_elt(ary, offset);
}

VALUE
rb_ary_subseq(VALUE ary, long beg, long len)
{
    VALUE klass, ary2, shared;
    VALUE *ptr;

    if (beg > RARRAY_LEN(ary)) return Qnil;
    if (beg < 0 || len < 0) return Qnil;

    if (RARRAY_LEN(ary) < len || RARRAY_LEN(ary) < beg + len) {
  len = RARRAY_LEN(ary) - beg;
    }
    klass = rb_obj_class(ary);
    if (len == 0) return ary_new(klass, 0);

    shared = ary_make_shared(ary);
    ptr = RARRAY_PTR(ary);
    ary2 = ary_alloc(klass);
    RARRAY(ary2)->ptr = ptr + beg;
    RARRAY(ary2)->len = len;
    RARRAY(ary2)->aux.shared = shared;
    FL_SET(ary2, ELTS_SHARED);

    return ary2;
}

/* 
 *  call-seq:
 *     array[index]                -> obj      or nil
 *     array[start, length]        -> an_array or nil
 *     array[range]                -> an_array or nil
 *     array.slice(index)          -> obj      or nil
 *     array.slice(start, length)  -> an_array or nil
 *     array.slice(range)          -> an_array or nil
 *
 *  Element Reference---Returns the element at _index_,
 *  or returns a subarray starting at _start_ and
 *  continuing for _length_ elements, or returns a subarray
 *  specified by _range_.
 *  Negative indices count backward from the end of the
 *  array (-1 is the last element). Returns nil if the index
 *  (or starting index) are out of range.
 *
 *     a = [ "a", "b", "c", "d", "e" ]
 *     a[2] +  a[0] + a[1]    #=> "cab"
 *     a[6]                   #=> nil
 *     a[1, 2]                #=> [ "b", "c" ]
 *     a[1..3]                #=> [ "b", "c", "d" ]
 *     a[4..7]                #=> [ "e" ]
 *     a[6..10]               #=> nil
 *     a[-3, 3]               #=> [ "c", "d", "e" ]
 *     # special cases
 *     a[5]                   #=> nil
 *     a[5, 1]                #=> []
 *     a[5..10]               #=> []
 *
 */

VALUE
rb_ary_aref(int argc, VALUE *argv, VALUE ary)
{
    VALUE arg;
    long beg, len;

    if (argc == 2) {
  beg = NUM2LONG(argv[0]);
  len = NUM2LONG(argv[1]);
  if (beg < 0) {
      beg += RARRAY_LEN(ary);
  }
  return rb_ary_subseq(ary, beg, len);
    }
    if (argc != 1) {
  rb_scan_args(argc, argv, "11", 0, 0);
    }
    arg = argv[0];
    /* special case - speeding up */
    if (FIXNUM_P(arg)) {
  return rb_ary_entry(ary, FIX2LONG(arg));
    }
    /* check if idx is Range */
    switch (rb_range_beg_len(arg, &beg, &len, RARRAY_LEN(ary), 0)) {
      case Qfalse:
  break;
      case Qnil:
  return Qnil;
      default:
  return rb_ary_subseq(ary, beg, len);
    }
    return rb_ary_entry(ary, NUM2LONG(arg));
}

/* 
 *  call-seq:
 *     array.at(index)   ->   obj  or nil
 *
 *  Returns the element at _index_. A
 *  negative index counts from the end of _self_.  Returns +nil+
 *  if the index is out of range. See also <code>Array#[]</code>.
 *
 *     a = [ "a", "b", "c", "d", "e" ]
 *     a.at(0)     #=> "a"
 *     a.at(-1)    #=> "e"
 */

static VALUE
rb_ary_at(VALUE ary, VALUE pos)
{
    return rb_ary_entry(ary, NUM2LONG(pos));
}

/*
 *  call-seq:
 *     array.first     ->   obj or nil
 *     array.first(n)  ->   an_array
 *  
 *  Returns the first element, or the first +n+ elements, of the array.
 *  If the array is empty, the first form returns <code>nil</code>, and the
 *  second form returns an empty array.
 *     
 *     a = [ "q", "r", "s", "t" ]
 *     a.first     #=> "q"
 *     a.first(2)  #=> ["q", "r"]
 */

static VALUE
rb_ary_first(int argc, VALUE *argv, VALUE ary)
{
    if (argc == 0) {
  if (RARRAY_LEN(ary) == 0) return Qnil;
  return yard_resolve_stub(RARRAY_PTR(ary)[0]);
    }
    else {
  return ary_shared_first(argc, argv, ary, Qfalse);
    }
}

/*
 *  call-seq:
 *     array.last     ->  obj or nil
 *     array.last(n)  ->  an_array
 *  
 *  Returns the last element(s) of <i>self</i>. If the array is empty,
 *  the first form returns <code>nil</code>.
 *     
 *     a = [ "w", "x", "y", "z" ]
 *     a.last     #=> "z"
 *     a.last(2)  #=> ["y", "z"]
 */

VALUE
rb_ary_last(int argc, VALUE *argv, VALUE ary)
{
    if (argc == 0) {
  if (RARRAY_LEN(ary) == 0) return Qnil;
  return yard_resolve_stub(RARRAY_PTR(ary)[RARRAY_LEN(ary)-1]);
    }
    else {
  return ary_shared_first(argc, argv, ary, Qtrue);
    }
}

/*
 *  call-seq:
 *     array.fetch(index)                    -> obj
 *     array.fetch(index, default )          -> obj
 *     array.fetch(index) {|index| block }   -> obj
 *  
 *  Tries to return the element at position <i>index</i>. If the index
 *  lies outside the array, the first form throws an
 *  <code>IndexError</code> exception, the second form returns
 *  <i>default</i>, and the third form returns the value of invoking
 *  the block, passing in the index. Negative values of <i>index</i>
 *  count from the end of the array.
 *     
 *     a = [ 11, 22, 33, 44 ]
 *     a.fetch(1)               #=> 22
 *     a.fetch(-1)              #=> 44
 *     a.fetch(4, 'cat')        #=> "cat"
 *     a.fetch(4) { |i| i*i }   #=> 16
 */

static VALUE
rb_ary_fetch(int argc, VALUE *argv, VALUE ary)
{
    VALUE pos, ifnone;
    long block_given;
    long idx;

    rb_scan_args(argc, argv, "11", &pos, &ifnone);
    block_given = rb_block_given_p();
    if (block_given && argc == 2) {
  rb_warn("block supersedes default value argument");
    }
    idx = NUM2LONG(pos);

    if (idx < 0) {
  idx +=  RARRAY_LEN(ary);
    }
    if (idx < 0 || RARRAY_LEN(ary) <= idx) {
  if (block_given) return rb_yield(pos);
  if (argc == 1) {
      rb_raise(rb_eIndexError, "index %ld out of array", idx);
  }
  return ifnone;
    }
    return yard_resolve_stub(RARRAY_PTR(ary)[idx]);
}

/*
 *  call-seq:
 *     array.index(obj)           ->  int or nil
 *     array.index {|item| block} ->  int or nil
 *  
 *  Returns the index of the first object in <i>self</i> such that is
 *  <code>==</code> to <i>obj</i>. If a block is given instead of an
 *  argument, returns first object for which <em>block</em> is true.
 *  Returns <code>nil</code> if no match is found.
 *     
 *     a = [ "a", "b", "c" ]
 *     a.index("b")        #=> 1
 *     a.index("z")        #=> nil
 *     a.index{|x|x=="b"}  #=> 1
 */

static VALUE
rb_ary_index(int argc, VALUE *argv, VALUE ary)
{
    VALUE val;
    long i;

    if (rb_scan_args(argc, argv, "01", &val) == 0) {
  RETURN_ENUMERATOR(ary, 0, 0);
  for (i=0; i<RARRAY_LEN(ary); i++) {
      if (RTEST(rb_yield(yard_resolve_stub(RARRAY_PTR(ary)[i])))) {
    return LONG2NUM(i);
      }
  }
    }
    else {
  for (i=0; i<RARRAY_LEN(ary); i++) {
      if (rb_equal(yard_resolve_stub(RARRAY_PTR(ary)[i]), val))
    return LONG2NUM(i);
  }
    }
    return Qnil;
}

/*
 *  call-seq:
 *     array.rindex(obj)    ->  int or nil
 *  
 *  Returns the index of the last object in <i>array</i>
 *  <code>==</code> to <i>obj</i>. If a block is given instead of an
 *  argument, returns first object for which <em>block</em> is
 *  true. Returns <code>nil</code> if no match is found.
 *     
 *     a = [ "a", "b", "b", "b", "c" ]
 *     a.rindex("b")        #=> 3
 *     a.rindex("z")        #=> nil
 *     a.rindex{|x|x=="b"}  #=> 3
 */

static VALUE
rb_ary_rindex(int argc, VALUE *argv, VALUE ary)
{
    VALUE val;
    long i = RARRAY_LEN(ary);

    if (rb_scan_args(argc, argv, "01", &val) == 0) {
  RETURN_ENUMERATOR(ary, 0, 0);
  while (i--) {
      if (RTEST(rb_yield(yard_resolve_stub(RARRAY_PTR(ary)[i]))))
    return LONG2NUM(i);
      if (i > RARRAY_LEN(ary)) {
    i = RARRAY_LEN(ary);
      }
  }
    }
    else {
  while (i--) {
      if (rb_equal(yard_resolve_stub(RARRAY_PTR(ary)[i]), val))
    return LONG2NUM(i);
      if (i > RARRAY_LEN(ary)) {
    i = RARRAY_LEN(ary);
      }
  }
    }
    return Qnil;
}

VALUE
rb_ary_to_ary(VALUE obj)
{
    if (TYPE(obj) == T_ARRAY) {
  return obj;
    }
    if (rb_respond_to(obj, rb_intern("to_ary"))) {
  return to_ary(obj);
    }
    return rb_ary_new3(1, obj);
}

static void
rb_ary_splice(VALUE ary, long beg, long len, VALUE rpl)
{
    long rlen;

    if (len < 0) rb_raise(rb_eIndexError, "negative length (%ld)", len);
    if (beg < 0) {
  beg += RARRAY_LEN(ary);
  if (beg < 0) {
      beg -= RARRAY_LEN(ary);
      rb_raise(rb_eIndexError, "index %ld out of array", beg);
  }
    }
    if (RARRAY_LEN(ary) < len || RARRAY_LEN(ary) < beg + len) {
  len = RARRAY_LEN(ary) - beg;
    }

    if (rpl == Qundef) {
  rlen = 0;
    }
    else {
  rpl = rb_ary_to_ary(rpl);
  rlen = RARRAY_LEN(rpl);
    }
    rb_ary_modify(ary);
    ary_iter_check(ary);
    if (beg >= RARRAY_LEN(ary)) {
  len = beg + rlen;
  if (len >= ARY_CAPA(ary)) {
      RESIZE_CAPA(ary, len);
  }
  rb_mem_clear(RARRAY_PTR(ary) + RARRAY_LEN(ary), beg - RARRAY_LEN(ary));
  if (rlen > 0) {
      MEMCPY(RARRAY_PTR(ary) + beg, RARRAY_PTR(rpl), VALUE, rlen);
  }
  RARRAY(ary)->len = len;
    }
    else {
  long alen;

  if (beg + len > RARRAY_LEN(ary)) {
      len = RARRAY_LEN(ary) - beg;
  }

  alen = RARRAY_LEN(ary) + rlen - len;
  if (alen >= ARY_CAPA(ary)) {
      RESIZE_CAPA(ary, alen);
  }

  if (len != rlen) {
      MEMMOVE(RARRAY_PTR(ary) + beg + rlen, RARRAY_PTR(ary) + beg + len,
        VALUE, RARRAY_LEN(ary) - (beg + len));
      RARRAY(ary)->len = alen;
  }
  if (rlen > 0) {
      MEMMOVE(RARRAY_PTR(ary) + beg, RARRAY_PTR(rpl), VALUE, rlen);
  }
    }
}

/* 
 *  call-seq:
 *     array[index]         = obj                     ->  obj
 *     array[start, length] = obj or an_array or nil  ->  obj or an_array or nil
 *     array[range]         = obj or an_array or nil  ->  obj or an_array or nil
 *
 *  Element Assignment---Sets the element at _index_,
 *  or replaces a subarray starting at _start_ and
 *  continuing for _length_ elements, or replaces a subarray
 *  specified by _range_.  If indices are greater than
 *  the current capacity of the array, the array grows
 *  automatically. A negative indices will count backward
 *  from the end of the array. Inserts elements if _length_ is
 *  zero. An +IndexError+ is raised if a negative index points
 *  past the beginning of the array. See also
 *  <code>Array#push</code>, and <code>Array#unshift</code>.
 * 
 *     a = Array.new
 *     a[4] = "4";                 #=> [nil, nil, nil, nil, "4"]
 *     a[0, 3] = [ 'a', 'b', 'c' ] #=> ["a", "b", "c", nil, "4"]
 *     a[1..2] = [ 1, 2 ]          #=> ["a", 1, 2, nil, "4"]
 *     a[0, 2] = "?"               #=> ["?", 2, nil, "4"]
 *     a[0..2] = "A"               #=> ["A", "4"]
 *     a[-1]   = "Z"               #=> ["A", "Z"]
 *     a[1..-1] = nil              #=> ["A", nil]
 *     a[1..-1] = []              #=> ["A"]
 */

static VALUE
rb_ary_aset(int argc, VALUE *argv, VALUE ary)
{
    long offset, beg, len;

    if (argc == 3) {
  rb_ary_splice(ary, NUM2LONG(argv[0]), NUM2LONG(argv[1]), argv[2]);
  return argv[2];
    }
    if (argc != 2) {
  rb_raise(rb_eArgError, "wrong number of arguments (%d for 2)", argc);
    }
    if (FIXNUM_P(argv[0])) {
  offset = FIX2LONG(argv[0]);
  goto fixnum;
    }
    if (rb_range_beg_len(argv[0], &beg, &len, RARRAY_LEN(ary), 1)) {
  /* check if idx is Range */
  rb_ary_splice(ary, beg, len, argv[1]);
  return argv[1];
    }

    offset = NUM2LONG(argv[0]);
fixnum:
    rb_ary_store(ary, offset, argv[1]);
    return argv[1];
}

/*
 *  call-seq:
 *     array.insert(index, obj...)  -> array
 *  
 *  Inserts the given values before the element with the given index
 *  (which may be negative).
 *     
 *     a = %w{ a b c d }
 *     a.insert(2, 99)         #=> ["a", "b", 99, "c", "d"]
 *     a.insert(-2, 1, 2, 3)   #=> ["a", "b", 99, "c", 1, 2, 3, "d"]
 */

static VALUE
rb_ary_insert(int argc, VALUE *argv, VALUE ary)
{
    long pos;

    if (argc == 1) return ary;
    if (argc < 1) {
  rb_raise(rb_eArgError, "wrong number of arguments (at least 1)");
    }
    pos = NUM2LONG(argv[0]);
    if (pos == -1) {
  pos = RARRAY_LEN(ary);
    }
    if (pos < 0) {
  pos++;
    }
    rb_ary_splice(ary, pos, 0, rb_ary_new4(argc - 1, argv + 1));
    return ary;
}

static VALUE
each_unlock(VALUE ary)
{
    FL_UNSET(ary, ARY_ITERLOCK);
    return ary;
}

static VALUE
each_i(VALUE ary)
{
    long i;

    for (i=0; i<RARRAY_LEN(ary); i++) {
  rb_yield(yard_resolve_stub(RARRAY_PTR(ary)[i]));
    }
    return ary;
}

/*
 *  call-seq:
 *     array.each {|item| block }   ->   array
 *  
 *  Calls <i>block</i> once for each element in <i>self</i>, passing that
 *  element as a parameter.
 *     
 *     a = [ "a", "b", "c" ]
 *     a.each {|x| print x, " -- " }
 *     
 *  produces:
 *     
 *     a -- b -- c --
 */

VALUE
rb_ary_each(VALUE ary)
{
    RETURN_ENUMERATOR(ary, 0, 0);
    ITERATE(each_i, ary);
    return ary;
}

static VALUE
each_index_i(VALUE ary)
{
    long i;

    for (i=0; i<RARRAY_LEN(ary); i++) {
      rb_yield(LONG2NUM(i));
    }
    return ary;
}

/*
 *  call-seq:
 *     array.each_index {|index| block }  ->  array
 *  
 *  Same as <code>Array#each</code>, but passes the index of the element
 *  instead of the element itself.
 *     
 *     a = [ "a", "b", "c" ]
 *     a.each_index {|x| print x, " -- " }
 *     
 *  produces:
 *     
 *     0 -- 1 -- 2 --
 */

static VALUE
rb_ary_each_index(VALUE ary)
{
    RETURN_ENUMERATOR(ary, 0, 0);
    ITERATE(each_index_i, ary);
    return ary;
}

static VALUE
reverse_each_i(VALUE ary)
{
    long len = RARRAY_LEN(ary);

    while (len--) {
  rb_yield(yard_resolve_stub(RARRAY_PTR(ary)[len]));
  if (RARRAY_LEN(ary) < len) {
      len = RARRAY_LEN(ary);
  }
    }
    return ary;
}

/*
 *  call-seq:
 *     array.reverse_each {|item| block } 
 *  
 *  Same as <code>Array#each</code>, but traverses <i>self</i> in reverse
 *  order.
 *     
 *     a = [ "a", "b", "c" ]
 *     a.reverse_each {|x| print x, " " }
 *     
 *  produces:
 *     
 *     c b a
 */

static VALUE
rb_ary_reverse_each(VALUE ary)
{
    RETURN_ENUMERATOR(ary, 0, 0);
    ITERATE(reverse_each_i, ary);
}

/*
 *  call-seq:
 *     array.length -> int
 *  
 *  Returns the number of elements in <i>self</i>. May be zero.
 *     
 *     [ 1, 2, 3, 4, 5 ].length   #=> 5
 */

static VALUE
rb_ary_length(VALUE ary)
{
    long len = RARRAY_LEN(ary);
    return LONG2NUM(len);
}

/*
 *  call-seq:
 *     array.empty?   -> true or false
 *  
 *  Returns <code>true</code> if <i>self</i> array contains no elements.
 *     
 *     [].empty?   #=> true
 */

static VALUE
rb_ary_empty_p(VALUE ary)
{
    if (RARRAY_LEN(ary) == 0)
  return Qtrue;
    return Qfalse;
}

VALUE
rb_ary_dup(VALUE ary)
{
    VALUE dup = rb_ary_new2(RARRAY_LEN(ary));

    MEMCPY(RARRAY_PTR(dup), RARRAY_PTR(ary), VALUE, RARRAY_LEN(ary));
    RARRAY(dup)->len = RARRAY_LEN(ary);
    OBJ_INFECT(dup, ary);

    return dup;
}

extern VALUE rb_output_fs;

static VALUE
recursive_join(VALUE ary, VALUE argp, int recur)
{
    VALUE *arg = (VALUE *)argp;
    if (recur) {
  return rb_str_new2("[...]");
    }
    return rb_ary_join(arg[0], arg[1]);
}

VALUE
rb_ary_join(VALUE ary, VALUE sep)
{
    long len = 1, i;
    int taint = Qfalse;
    VALUE result, tmp;

    if (RARRAY_LEN(ary) == 0) return rb_str_new(0, 0);
    if (OBJ_TAINTED(ary) || OBJ_TAINTED(sep)) taint = Qtrue;

    for (i=0; i<RARRAY_LEN(ary); i++) {
  tmp = rb_check_string_type(yard_resolve_stub(RARRAY_PTR(ary)[i]));
  len += NIL_P(tmp) ? 10 : RSTRING_LEN(tmp);
    }
    if (!NIL_P(sep)) {
  StringValue(sep);
  len += RSTRING_LEN(sep) * (RARRAY_LEN(ary) - 1);
    }
    result = rb_str_buf_new(len);
    for (i=0; i<RARRAY_LEN(ary); i++) {
  tmp = yard_resolve_stub(RARRAY_PTR(ary)[i]);
  switch (TYPE(tmp)) {
    case T_STRING:
      break;
    case T_ARRAY:
      {
    VALUE args[2];

    args[0] = tmp;
    args[1] = sep;
    tmp = rb_exec_recursive(recursive_join, ary, (VALUE)args);
      }
      break;
    default:
      tmp = rb_obj_as_string(tmp);
  }
  if (i > 0 && !NIL_P(sep))
      rb_str_buf_append(result, sep);
  rb_str_buf_append(result, tmp);
  if (OBJ_TAINTED(tmp)) taint = Qtrue;
    }

    if (taint) OBJ_TAINT(result);
    return result;
}

/*
 *  call-seq:
 *     array.join(sep=$,)    -> str
 *  
 *  Returns a string created by converting each element of the array to
 *  a string, separated by <i>sep</i>.
 *     
 *     [ "a", "b", "c" ].join        #=> "abc"
 *     [ "a", "b", "c" ].join("-")   #=> "a-b-c"
 */

static VALUE
rb_ary_join_m(int argc, VALUE *argv, VALUE ary)
{
    VALUE sep;

    rb_scan_args(argc, argv, "01", &sep);
    if (NIL_P(sep)) sep = rb_output_fs;
    
    return rb_ary_join(ary, sep);
}

static VALUE
inspect_ary(VALUE ary, VALUE dummy, int recur)
{
    int tainted = OBJ_TAINTED(ary);
    long i;
    VALUE s, str;

    if (recur) return rb_tainted_str_new2("[...]");
    str = rb_str_buf_new2("[");
    for (i=0; i<RARRAY_LEN(ary); i++) {
  s = rb_inspect(yard_resolve_stub(RARRAY_PTR(ary)[i]));
  if (OBJ_TAINTED(s)) tainted = Qtrue;
  if (i > 0) rb_str_buf_cat2(str, ", ");
  rb_str_buf_append(str, s);
    }
    rb_str_buf_cat2(str, "]");
    if (tainted) OBJ_TAINT(str);
    return str;
}

/*
 *  call-seq:
 *     array.to_s -> string
 *     array.inspect  -> string
 *
 *  Create a printable version of <i>array</i>.
 */

static VALUE
rb_ary_inspect(VALUE ary)
{
    if (RARRAY_LEN(ary) == 0) return rb_str_new2("[]");
    return rb_exec_recursive(inspect_ary, ary, 0);
}

VALUE
rb_ary_to_s(VALUE ary)
{
    return rb_ary_inspect(ary);
}

/*
 *  call-seq:
 *     array.to_a     -> array
 *  
 *  Returns _self_. If called on a subclass of Array, converts
 *  the receiver to an Array object.
 */

static VALUE
rb_ary_to_a(VALUE ary)
{
    if (rb_obj_class(ary) != rb_cArray) {
  VALUE dup = rb_ary_new2(RARRAY_LEN(ary));
  rb_ary_replace(dup, ary);
  return dup;
    }
    return ary;
}

/*
 *  call-seq:
 *     array.to_ary -> array
 *  
 *  Returns _self_.
 */

static VALUE
rb_ary_to_ary_m(VALUE ary)
{
    return ary;
}

VALUE
rb_ary_reverse(VALUE ary)
{
    VALUE *p1, *p2;
    VALUE tmp;

    rb_ary_modify(ary);
    ary_iter_check(ary);
    if (RARRAY_LEN(ary) > 1) {
  p1 = RARRAY_PTR(ary);
  p2 = p1 + RARRAY_LEN(ary) - 1;	/* points last item */

  while (p1 < p2) {
      tmp = *p1;
      *p1++ = *p2;
      *p2-- = tmp;
  }
    }
    return ary;
}

/*
 *  call-seq:
 *     array.reverse!   -> array 
 *  
 *  Reverses _self_ in place.
 *     
 *     a = [ "a", "b", "c" ]
 *     a.reverse!       #=> ["c", "b", "a"]
 *     a                #=> ["c", "b", "a"]
 */

static VALUE
rb_ary_reverse_bang(VALUE ary)
{
    return rb_ary_reverse(ary);
}

/*
 *  call-seq:
 *     array.reverse -> an_array
 *  
 *  Returns a new array containing <i>self</i>'s elements in reverse order.
 *     
 *     [ "a", "b", "c" ].reverse   #=> ["c", "b", "a"]
 *     [ 1 ].reverse               #=> [1]
 */

static VALUE
rb_ary_reverse_m(VALUE ary)
{
    return rb_ary_reverse(rb_ary_dup(ary));
}

struct ary_sort_data {
    VALUE ary;
    VALUE *ptr;
    long len;
};

static void
ary_sort_check(struct ary_sort_data *data)
{
    if (RARRAY_PTR(data->ary) != data->ptr || RARRAY_LEN(data->ary) != data->len) {
  rb_raise(rb_eRuntimeError, "array modified during sort");
    }
}

static int
sort_1(const void *ap, const void *bp, void *data)
{
    VALUE a = *(const VALUE *)ap, b = *(const VALUE *)bp;
    VALUE retval = rb_yield_values(2, a, b);
    int n;

    n = rb_cmpint(retval, a, b);
    ary_sort_check((struct ary_sort_data *)data);
    return n;
}

static int
sort_2(const void *ap, const void *bp, void *data)
{
    VALUE retval;
    VALUE a = *(const VALUE *)ap, b = *(const VALUE *)bp;
    int n;

    if (FIXNUM_P(a) && FIXNUM_P(b)) {
  if ((long)a > (long)b) return 1;
  if ((long)a < (long)b) return -1;
  return 0;
    }
    if (TYPE(a) == T_STRING) {
  if (TYPE(b) == T_STRING) return rb_str_cmp(a, b);
    }

    retval = rb_funcall(a, id_cmp, 1, b);
    n = rb_cmpint(retval, a, b);
    ary_sort_check((struct ary_sort_data *)data);

    return n;
}

static VALUE
sort_i(VALUE ary)
{
    struct ary_sort_data data;

    data.ary = ary;
    data.ptr = RARRAY_PTR(ary); data.len = RARRAY_LEN(ary);
    ruby_qsort(RARRAY_PTR(ary), RARRAY_LEN(ary), sizeof(VALUE),
    rb_block_given_p()?sort_1:sort_2, &data);
    return ary;
}

static VALUE
sort_unlock(VALUE ary)
{
    FL_UNSET(ary, ARY_SORTLOCK);
    return ary;
}

/*
 *  call-seq:
 *     array.sort!                   -> array
 *     array.sort! {| a,b | block }  -> array 
 *  
 *  Sorts _self_. Comparisons for
 *  the sort will be done using the <code><=></code> operator or using
 *  an optional code block. The block implements a comparison between
 *  <i>a</i> and <i>b</i>, returning -1, 0, or +1. See also
 *  <code>Enumerable#sort_by</code>.
 *     
 *     a = [ "d", "a", "e", "c", "b" ]
 *     a.sort                    #=> ["a", "b", "c", "d", "e"]
 *     a.sort {|x,y| y <=> x }   #=> ["e", "d", "c", "b", "a"]
 */

VALUE
rb_ary_sort_bang(VALUE ary)
{
    rb_ary_modify(ary);
    ary_iter_check(ary);
    if (RARRAY_LEN(ary) > 1) {
  FL_SET(ary, ARY_SORTLOCK);	/* prohibit modification during sort */
  rb_ensure(sort_i, ary, sort_unlock, ary);
    }
    return ary;
}

/*
 *  call-seq:
 *     array.sort                   -> an_array 
 *     array.sort {| a,b | block }  -> an_array 
 *  
 *  Returns a new array created by sorting <i>self</i>. Comparisons for
 *  the sort will be done using the <code><=></code> operator or using
 *  an optional code block. The block implements a comparison between
 *  <i>a</i> and <i>b</i>, returning -1, 0, or +1. See also
 *  <code>Enumerable#sort_by</code>.
 *     
 *     a = [ "d", "a", "e", "c", "b" ]
 *     a.sort                    #=> ["a", "b", "c", "d", "e"]
 *     a.sort {|x,y| y <=> x }   #=> ["e", "d", "c", "b", "a"]
 */

VALUE
rb_ary_sort(VALUE ary)
{
    ary = rb_ary_dup(ary);
    rb_ary_sort_bang(ary);
    return ary;
}


static VALUE
collect_i(VALUE ary)
{
    long i;
    VALUE collect;

    collect = rb_ary_new2(RARRAY_LEN(ary));
    for (i = 0; i < RARRAY_LEN(ary); i++) {
  rb_ary_push(collect, rb_yield(yard_resolve_stub(RARRAY_PTR(ary)[i])));
    }
    return collect;
}

/*
 *  call-seq:
 *     array.collect {|item| block }  -> an_array
 *     array.map     {|item| block }  -> an_array
 *  
 *  Invokes <i>block</i> once for each element of <i>self</i>. Creates a 
 *  new array containing the values returned by the block.
 *  See also <code>Enumerable#collect</code>.
 *     
 *     a = [ "a", "b", "c", "d" ]
 *     a.collect {|x| x + "!" }   #=> ["a!", "b!", "c!", "d!"]
 *     a                          #=> ["a", "b", "c", "d"]
 */

static VALUE
rb_ary_collect(VALUE ary)
{
    RETURN_ENUMERATOR(ary, 0, 0);
    ITERATE(collect_i, ary);
}


static VALUE
collect_bang_i(VALUE ary)
{
    long i;

    rb_ary_modify(ary);
    for (i = 0; i < RARRAY_LEN(ary); i++) {
  RARRAY_PTR(ary)[i] = rb_yield(yard_resolve_stub(RARRAY_PTR(ary)[i]));
    }
    return ary;
}

/* 
 *  call-seq:
 *     array.collect! {|item| block }   ->   array
 *     array.map!     {|item| block }   ->   array
 *
 *  Invokes the block once for each element of _self_, replacing the
 *  element with the value returned by _block_.
 *  See also <code>Enumerable#collect</code>.
 *   
 *     a = [ "a", "b", "c", "d" ]
 *     a.collect! {|x| x + "!" }
 *     a             #=>  [ "a!", "b!", "c!", "d!" ]
 */

static VALUE
rb_ary_collect_bang(VALUE ary)
{
    RETURN_ENUMERATOR(ary, 0, 0);
    ITERATE(collect_bang_i, ary);
}

VALUE
rb_get_values_at(VALUE obj, long olen, int argc, VALUE *argv, VALUE (*func) (VALUE, long))
{
    VALUE result = rb_ary_new2(argc);
    long beg, len, i, j;

    for (i=0; i<argc; i++) {
  if (FIXNUM_P(argv[i])) {
      rb_ary_push(result, (*func)(obj, FIX2LONG(argv[i])));
      continue;
  }
  /* check if idx is Range */
  switch (rb_range_beg_len(argv[i], &beg, &len, olen, 0)) {
    case Qfalse:
      break;
    case Qnil:
      continue;
    default:
      for (j=0; j<len; j++) {
    rb_ary_push(result, (*func)(obj, j+beg));
      }
      continue;
  }
  rb_ary_push(result, (*func)(obj, NUM2LONG(argv[i])));
    }
    return result;
}

/* 
 *  call-seq:
 *     array.values_at(selector,... )  -> an_array
 *
 *  Returns an array containing the elements in
 *  _self_ corresponding to the given selector(s). The selectors
 *  may be either integer indices or ranges. 
 *  See also <code>Array#select</code>.
 * 
 *     a = %w{ a b c d e f }
 *     a.values_at(1, 3, 5)
 *     a.values_at(1, 3, 5, 7)
 *     a.values_at(-1, -3, -5, -7)
 *     a.values_at(1..3, 2...5)
 */

static VALUE
rb_ary_values_at(int argc, VALUE *argv, VALUE ary)
{
    return rb_get_values_at(ary, RARRAY_LEN(ary), argc, argv, rb_ary_entry);
}


static VALUE
select_i(VALUE ary)
{
    VALUE result;
    long i;

    result = rb_ary_new2(RARRAY_LEN(ary));
    for (i = 0; i < RARRAY_LEN(ary); i++) {
  if (RTEST(rb_yield(yard_resolve_stub(RARRAY_PTR(ary)[i])))) {
      rb_ary_push(result, rb_ary_elt(ary, i));
  }
    }
    return result;
}

/*
 *  call-seq:
 *     array.select {|item| block } -> an_array
 *  
 *  Invokes the block passing in successive elements from <i>array</i>,
 *  returning an array containing those elements for which the block
 *  returns a true value (equivalent to <code>Enumerable#select</code>).
 *     
 *     a = %w{ a b c d e f }
 *     a.select {|v| v =~ /[aeiou]/}   #=> ["a", "e"]
 */

static VALUE
rb_ary_select(VALUE ary)
{
    RETURN_ENUMERATOR(ary, 0, 0);
    ITERATE(select_i, ary);
}

/*
 *  call-seq:
 *     array.delete(obj)            -> obj or nil 
 *     array.delete(obj) { block }  -> obj or nil
 *  
 *  Deletes items from <i>self</i> that are equal to <i>obj</i>. If
 *  the item is not found, returns <code>nil</code>. If the optional
 *  code block is given, returns the result of <i>block</i> if the item
 *  is not found.
 *     
 *     a = [ "a", "b", "b", "b", "c" ]
 *     a.delete("b")                   #=> "b"
 *     a                               #=> ["a", "c"]
 *     a.delete("z")                   #=> nil
 *     a.delete("z") { "not found" }   #=> "not found"
 */

VALUE
rb_ary_delete(VALUE ary, VALUE item)
{
    long i1, i2;

    for (i1 = i2 = 0; i1 < RARRAY_LEN(ary); i1++) {
  VALUE e = yard_resolve_stub(RARRAY_PTR(ary)[i1]);

  if (rb_equal(e, item)) continue;
  if (i1 != i2) {
      rb_ary_store(ary, i2, e);
  }
  i2++;
    }
    if (RARRAY_LEN(ary) == i2) {
  if (rb_block_given_p()) {
      return rb_yield(item);
  }
  return Qnil;
    }

    rb_ary_modify(ary);
    ary_iter_check(ary);
    if (RARRAY_LEN(ary) > i2) {
  RARRAY(ary)->len = i2;
  if (i2 * 2 < ARY_CAPA(ary) &&
      ARY_CAPA(ary) > ARY_DEFAULT_SIZE) {
      RESIZE_CAPA(ary, i2*2);
  }
    }

    return item;
}

VALUE
rb_ary_delete_at(VALUE ary, long pos)
{
    long len = RARRAY_LEN(ary);
    VALUE del;

    if (pos >= len) return Qnil;
    if (pos < 0) {
  pos += len;
  if (pos < 0) return Qnil;
    }

    rb_ary_modify(ary);
    ary_iter_check(ary);
    del = yard_resolve_stub(RARRAY_PTR(ary)[pos]);
    MEMMOVE(RARRAY_PTR(ary)+pos, RARRAY_PTR(ary)+pos+1, VALUE,
      RARRAY_LEN(ary)-pos-1);
    RARRAY(ary)->len--;

    return del;
}

/*
 *  call-seq:
 *     array.delete_at(index)  -> obj or nil
 *  
 *  Deletes the element at the specified index, returning that element,
 *  or <code>nil</code> if the index is out of range. See also
 *  <code>Array#slice!</code>.
 *     
 *     a = %w( ant bat cat dog )
 *     a.delete_at(2)    #=> "cat"
 *     a                 #=> ["ant", "bat", "dog"]
 *     a.delete_at(99)   #=> nil
 */

static VALUE
rb_ary_delete_at_m(VALUE ary, VALUE pos)
{
    return rb_ary_delete_at(ary, NUM2LONG(pos));
}

/*
 *  call-seq:
 *     array.slice!(index)         -> obj or nil
 *     array.slice!(start, length) -> sub_array or nil
 *     array.slice!(range)         -> sub_array or nil 
 *  
 *  Deletes the element(s) given by an index (optionally with a length)
 *  or by a range. Returns the deleted object, subarray, or
 *  <code>nil</code> if the index is out of range. Equivalent to:
 *     
 *     def slice!(*args)
 *       result = self[*args]
 *       self[*args] = nil
 *       result
 *     end
 *     
 *     a = [ "a", "b", "c" ]
 *     a.slice!(1)     #=> "b"
 *     a               #=> ["a", "c"]
 *     a.slice!(-1)    #=> "c"
 *     a               #=> ["a"]
 *     a.slice!(100)   #=> nil
 *     a               #=> ["a"]
 */

static VALUE
rb_ary_slice_bang(int argc, VALUE *argv, VALUE ary)
{
    VALUE arg1, arg2;
    long pos, len;

    if (rb_scan_args(argc, argv, "11", &arg1, &arg2) == 2) {
  pos = NUM2LONG(arg1);
  len = NUM2LONG(arg2);
      delete_pos_len:
  if (pos < 0) {
      pos = RARRAY_LEN(ary) + pos;
      if (pos < 0) return Qnil;
  }
  arg2 = rb_ary_subseq(ary, pos, len);
  rb_ary_splice(ary, pos, len, Qundef);	/* Qnil/rb_ary_new2(0) */
  return arg2;
    }

    if (!FIXNUM_P(arg1)) {
  switch (rb_range_beg_len(arg1, &pos, &len, RARRAY_LEN(ary), 0)) {
    case Qtrue:
      /* valid range */
      goto delete_pos_len;
    case Qnil:
      /* invalid range */
      return Qnil;
    default:
      /* not a range */
      break;
  }
    }

    return rb_ary_delete_at(ary, NUM2LONG(arg1));
}

static VALUE
reject_bang_i(VALUE ary)
{
    long i1, i2;

    rb_ary_modify(ary);
    for (i1 = i2 = 0; i1 < RARRAY_LEN(ary); i1++) {
  VALUE v = yard_resolve_stub(RARRAY_PTR(ary)[i1]);
  if (RTEST(rb_yield(v))) continue;
  if (i1 != i2) {
      rb_ary_store(ary, i2, v);
  }
  i2++;
    }

    if (RARRAY_LEN(ary) == i2) return Qnil;
    if (i2 < RARRAY_LEN(ary))
  RARRAY(ary)->len = i2;
    return ary;
}

/*
 *  call-seq:
 *     array.reject! {|item| block }  -> array or nil
 *  
 *  Equivalent to <code>Array#delete_if</code>, deleting elements from
 *  _self_ for which the block evaluates to true, but returns
 *  <code>nil</code> if no changes were made. Also see
 *  <code>Enumerable#reject</code>.
 */

static VALUE
rb_ary_reject_bang(VALUE ary)
{
    RETURN_ENUMERATOR(ary, 0, 0);
    ary_iter_check(ary);
    ITERATE(reject_bang_i, ary);
}

/*
 *  call-seq:
 *     array.reject {|item| block }  -> an_array
 *  
 *  Returns a new array containing the items in _self_
 *  for which the block is not true.
 */

static VALUE
rb_ary_reject(VALUE ary)
{
    RETURN_ENUMERATOR(ary, 0, 0);
    ary = rb_ary_dup(ary);
    rb_ary_reject_bang(ary);
    return ary;
}

/*
 *  call-seq:
 *     array.delete_if {|item| block }  -> array
 *  
 *  Deletes every element of <i>self</i> for which <i>block</i> evaluates
 *  to <code>true</code>.
 *     
 *     a = [ "a", "b", "c" ]
 *     a.delete_if {|x| x >= "b" }   #=> ["a"]
 */

static VALUE
rb_ary_delete_if(VALUE ary)
{
    rb_ary_reject_bang(ary);
    return ary;
}

/*
 *  call-seq:
 *     array.transpose -> an_array
 *  
 *  Assumes that <i>self</i> is an array of arrays and transposes the
 *  rows and columns.
 *     
 *     a = [[1,2], [3,4], [5,6]]
 *     a.transpose   #=> [[1, 3, 5], [2, 4, 6]]
 */

static VALUE
rb_ary_transpose(VALUE ary)
{
    long elen = -1, alen, i, j;
    VALUE tmp, result = 0;

    alen = RARRAY_LEN(ary);
    if (alen == 0) return rb_ary_dup(ary);
    for (i=0; i<alen; i++) {
  tmp = to_ary(rb_ary_elt(ary, i));
  if (elen < 0) {		/* first element */
      elen = RARRAY_LEN(tmp);
      result = rb_ary_new2(elen);
      for (j=0; j<elen; j++) {
    rb_ary_store(result, j, rb_ary_new2(alen));
      }
  }
  else if (elen != RARRAY_LEN(tmp)) {
      rb_raise(rb_eIndexError, "element size differs (%ld should be %ld)",
         RARRAY_LEN(tmp), elen);
  }
  for (j=0; j<elen; j++) {
      rb_ary_store(rb_ary_elt(result, j), i, rb_ary_elt(tmp, j));
  }
    }
    return result;
}

/*
 *  call-seq:
 *     array.replace(other_array)  -> array
 *  
 *  Replaces the contents of <i>self</i> with the contents of
 *  <i>other_array</i>, truncating or expanding if necessary.
 *     
 *     a = [ "a", "b", "c", "d", "e" ]
 *     a.replace([ "x", "y", "z" ])   #=> ["x", "y", "z"]
 *     a                              #=> ["x", "y", "z"]
 */

VALUE
rb_ary_replace(VALUE copy, VALUE orig)
{
    VALUE shared;
    VALUE *ptr;

    orig = to_ary(orig);
    rb_ary_modify_check(copy);
    ary_iter_check(copy);
    if (copy == orig) return copy;
    shared = ary_make_shared(orig);
    if (!ARY_SHARED_P(copy)) {
  ptr = RARRAY(copy)->ptr;
  xfree(ptr);
    }
    RARRAY(copy)->ptr = RARRAY(orig)->ptr;
    RARRAY(copy)->len = RARRAY(orig)->len;
    RARRAY(copy)->aux.shared = shared;
    FL_SET(copy, ELTS_SHARED);

    return copy;
}

/* 
 *  call-seq:
 *     array.clear    ->  array
 *
 *  Removes all elements from _self_.
 *
 *     a = [ "a", "b", "c", "d", "e" ]
 *     a.clear    #=> [ ]
 */

VALUE
rb_ary_clear(VALUE ary)
{
    rb_ary_modify(ary);
    ary_iter_check(ary);
    RARRAY(ary)->len = 0;
    if (ARY_DEFAULT_SIZE * 2 < ARY_CAPA(ary)) {
  RESIZE_CAPA(ary, ARY_DEFAULT_SIZE * 2);
    }
    return ary;
}

/*
 *  call-seq:
 *     array.fill(obj)                                -> array
 *     array.fill(obj, start [, length])              -> array
 *     array.fill(obj, range )                        -> array
 *     array.fill {|index| block }                    -> array
 *     array.fill(start [, length] ) {|index| block } -> array
 *     array.fill(range) {|index| block }             -> array
 *  
 *  The first three forms set the selected elements of <i>self</i> (which
 *  may be the entire array) to <i>obj</i>. A <i>start</i> of
 *  <code>nil</code> is equivalent to zero. A <i>length</i> of
 *  <code>nil</code> is equivalent to <i>self.length</i>. The last three
 *  forms fill the array with the value of the block. The block is
 *  passed the absolute index of each element to be filled.
 *     
 *     a = [ "a", "b", "c", "d" ]
 *     a.fill("x")              #=> ["x", "x", "x", "x"]
 *     a.fill("z", 2, 2)        #=> ["x", "x", "z", "z"]
 *     a.fill("y", 0..1)        #=> ["y", "y", "z", "z"]
 *     a.fill {|i| i*i}         #=> [0, 1, 4, 9]
 *     a.fill(-2) {|i| i*i*i}   #=> [0, 1, 8, 27]
 */

static VALUE
rb_ary_fill(int argc, VALUE *argv, VALUE ary)
{
    VALUE item, arg1, arg2;
    long beg = 0, end = 0, len = 0;
    VALUE *p, *pend;
    int block_p = Qfalse;

    if (rb_block_given_p()) {
  block_p = Qtrue;
  rb_scan_args(argc, argv, "02", &arg1, &arg2);
  argc += 1;		/* hackish */
    }
    else {
  rb_scan_args(argc, argv, "12", &item, &arg1, &arg2);
    }
    switch (argc) {
      case 1:
  beg = 0;
  len = RARRAY_LEN(ary);
  break;
      case 2:
  if (rb_range_beg_len(arg1, &beg, &len, RARRAY_LEN(ary), 1)) {
      break;
  }
  /* fall through */
      case 3:
  beg = NIL_P(arg1) ? 0 : NUM2LONG(arg1);
  if (beg < 0) {
      beg = RARRAY_LEN(ary) + beg;
      if (beg < 0) beg = 0;
  }
  len = NIL_P(arg2) ? RARRAY_LEN(ary) - beg : NUM2LONG(arg2);
  if (len < 0) rb_raise(rb_eIndexError, "negative length (%ld)", len);
  break;
    }
    rb_ary_modify(ary);
    ary_iter_check(ary);
    end = beg + len;
    if (end < 0) {
  rb_raise(rb_eArgError, "argument too big");
    }
    if (RARRAY_LEN(ary) < end) {
  if (end >= ARY_CAPA(ary)) {
      RESIZE_CAPA(ary, end);
  }
  rb_mem_clear(RARRAY_PTR(ary) + RARRAY_LEN(ary), end - RARRAY_LEN(ary));
  RARRAY(ary)->len = end;
    }

    if (block_p) {
  VALUE v;
  long i;

  for (i=beg; i<end; i++) {
      v = rb_yield(LONG2NUM(i));
      if (i>=RARRAY_LEN(ary)) break;
      RARRAY_PTR(ary)[i] = v;
  }
    }
    else {
  p = RARRAY_PTR(ary) + beg;
  pend = p + len;
  while (p < pend) {
      *p++ = item;
  }
    }
    return ary;
}

/* 
 *  call-seq:
 *     array + other_array   -> an_array
 *
 *  Concatenation---Returns a new array built by concatenating the
 *  two arrays together to produce a third array.
 * 
 *     [ 1, 2, 3 ] + [ 4, 5 ]    #=> [ 1, 2, 3, 4, 5 ]
 */

VALUE
rb_ary_plus(VALUE x, VALUE y)
{
    VALUE z;
    long len;

    y = to_ary(y);
    len = RARRAY_LEN(x) + RARRAY_LEN(y);
    z = rb_ary_new2(len);
    MEMCPY(RARRAY_PTR(z), RARRAY_PTR(x), VALUE, RARRAY_LEN(x));
    MEMCPY(RARRAY_PTR(z) + RARRAY_LEN(x), RARRAY_PTR(y), VALUE, RARRAY_LEN(y));
    RARRAY(z)->len = len;
    return z;
}

/* 
 *  call-seq:
 *     array.concat(other_array)   ->  array
 *
 *  Appends the elements in other_array to _self_.
 *  
 *     [ "a", "b" ].concat( ["c", "d"] ) #=> [ "a", "b", "c", "d" ]
 */


VALUE
rb_ary_concat(VALUE x, VALUE y)
{
    y = to_ary(y);
    if (RARRAY_LEN(y) > 0) {
  rb_ary_splice(x, RARRAY_LEN(x), 0, y);
    }
    return x;
}


/* 
 *  call-seq:
 *     array * int     ->    an_array
 *     array * str     ->    a_string
 *
 *  Repetition---With a String argument, equivalent to
 *  self.join(str). Otherwise, returns a new array
 *  built by concatenating the _int_ copies of _self_.
 *
 *
 *     [ 1, 2, 3 ] * 3    #=> [ 1, 2, 3, 1, 2, 3, 1, 2, 3 ]
 *     [ 1, 2, 3 ] * ","  #=> "1,2,3"
 *
 */

static VALUE
rb_ary_times(VALUE ary, VALUE times)
{
    VALUE ary2, tmp;
    long i, len;

    tmp = rb_check_string_type(times);
    if (!NIL_P(tmp)) {
  return rb_ary_join(ary, tmp);
    }

    len = NUM2LONG(times);
    if (len == 0) return ary_new(rb_obj_class(ary), 0);
    if (len < 0) {
  rb_raise(rb_eArgError, "negative argument");
    }
    if (LONG_MAX/len < RARRAY_LEN(ary)) {
  rb_raise(rb_eArgError, "argument too big");
    }
    len *= RARRAY_LEN(ary);

    ary2 = ary_new(rb_obj_class(ary), len);
    RARRAY(ary2)->len = len;

    for (i=0; i<len; i+=RARRAY_LEN(ary)) {
  MEMCPY(RARRAY_PTR(ary2)+i, RARRAY_PTR(ary), VALUE, RARRAY_LEN(ary));
    }
    OBJ_INFECT(ary2, ary);

    return ary2;
}

/* 
 *  call-seq:
 *     array.assoc(obj)   ->  an_array  or  nil
 *
 *  Searches through an array whose elements are also arrays
 *  comparing _obj_ with the first element of each contained array
 *  using obj.==.
 *  Returns the first contained array that matches (that
 *  is, the first associated array),
 *  or +nil+ if no match is found.
 *  See also <code>Array#rassoc</code>.
 *
 *     s1 = [ "colors", "red", "blue", "green" ]
 *     s2 = [ "letters", "a", "b", "c" ]
 *     s3 = "foo"
 *     a  = [ s1, s2, s3 ]
 *     a.assoc("letters")  #=> [ "letters", "a", "b", "c" ]
 *     a.assoc("foo")      #=> nil
 */

VALUE
rb_ary_assoc(VALUE ary, VALUE key)
{
    long i;
    VALUE v;

    for (i = 0; i < RARRAY_LEN(ary); ++i) {
  v = rb_check_array_type(yard_resolve_stub(RARRAY_PTR(ary)[i]));
  if (!NIL_P(v) && RARRAY_LEN(v) > 0 &&
      rb_equal(yard_resolve_stub(RARRAY_PTR(v)[0]), key))
      return v;
    }
    return Qnil;
}

/*
 *  call-seq:
 *     array.rassoc(obj) -> an_array or nil
 *  
 *  Searches through the array whose elements are also arrays. Compares
 *  _obj_ with the second element of each contained array using
 *  <code>==</code>. Returns the first contained array that matches. See
 *  also <code>Array#assoc</code>.
 *     
 *     a = [ [ 1, "one"], [2, "two"], [3, "three"], ["ii", "two"] ]
 *     a.rassoc("two")    #=> [2, "two"]
 *     a.rassoc("four")   #=> nil
 */

VALUE
rb_ary_rassoc(VALUE ary, VALUE value)
{
    long i;
    VALUE v;

    for (i = 0; i < RARRAY_LEN(ary); ++i) {
  v = yard_resolve_stub(RARRAY_PTR(ary)[i]);
  if (TYPE(v) == T_ARRAY &&
      RARRAY_LEN(v) > 1 &&
      rb_equal(yard_resolve_stub(RARRAY_PTR(v)[1]), value))
      return v;
    }
    return Qnil;
}

static VALUE
recursive_equal(VALUE ary1, VALUE ary2, int recur)
{
    long i;

    if (recur) return Qfalse;
    for (i=0; i<RARRAY_LEN(ary1); i++) {
  if (!rb_equal(rb_ary_elt(ary1, i), rb_ary_elt(ary2, i)))
      return Qfalse;
    }
    return Qtrue;
}

/* 
 *  call-seq:
 *     array == other_array   ->   bool
 *
 *  Equality---Two arrays are equal if they contain the same number
 *  of elements and if each element is equal to (according to
 *  Object.==) the corresponding element in the other array.
 *
 *     [ "a", "c" ]    == [ "a", "c", 7 ]     #=> false
 *     [ "a", "c", 7 ] == [ "a", "c", 7 ]     #=> true
 *     [ "a", "c", 7 ] == [ "a", "d", "f" ]   #=> false
 *
 */

static VALUE
rb_ary_equal(VALUE ary1, VALUE ary2)
{
    if (ary1 == ary2) return Qtrue;
    if (TYPE(ary2) != T_ARRAY) {
  if (!rb_respond_to(ary2, rb_intern("to_ary"))) {
      return Qfalse;
  }
  return rb_equal(ary2, ary1);
    }
    if (RARRAY_LEN(ary1) != RARRAY_LEN(ary2)) return Qfalse;
    return rb_exec_recursive(recursive_equal, ary1, ary2);
}

/*
 *  call-seq:
 *     array.eql?(other)  -> true or false
 *
 *  Returns <code>true</code> if _array_ and _other_ are the same object,
 *  or are both arrays with the same content.
 */

static VALUE
rb_ary_eql(VALUE ary1, VALUE ary2)
{
    long i;

    if (ary1 == ary2) return Qtrue;
    if (TYPE(ary2) != T_ARRAY) return Qfalse;
    if (RARRAY_LEN(ary1) != RARRAY_LEN(ary2)) return Qfalse;
    for (i=0; i<RARRAY_LEN(ary1); i++) {
  if (!rb_eql(rb_ary_elt(ary1, i), rb_ary_elt(ary2, i)))
      return Qfalse;
    }
    return Qtrue;
}

static VALUE
recursive_hash(VALUE ary, VALUE dummy, int recur)
{
    long i, h;
    VALUE n;

    if (recur) {
  return LONG2FIX(0);
    }
    h = RARRAY_LEN(ary);
    for (i=0; i<RARRAY_LEN(ary); i++) {
  h = (h << 1) | (h<0 ? 1 : 0);
  n = rb_hash(yard_resolve_stub(RARRAY_PTR(ary)[i]));
  h ^= NUM2LONG(n);
    }
    return LONG2FIX(h);
}

/*
 *  call-seq:
 *     array.hash   -> fixnum
 *
 *  Compute a hash-code for this array. Two arrays with the same content
 *  will have the same hash code (and will compare using <code>eql?</code>).
 */

static VALUE
rb_ary_hash(VALUE ary)
{
    return rb_exec_recursive(recursive_hash, ary, 0);
}

/*
 *  call-seq:
 *     array.include?(obj)   -> true or false
 *  
 *  Returns <code>true</code> if the given object is present in
 *  <i>self</i> (that is, if any object <code>==</code> <i>anObject</i>),
 *  <code>false</code> otherwise.
 *     
 *     a = [ "a", "b", "c" ]
 *     a.include?("b")   #=> true
 *     a.include?("z")   #=> false
 */

VALUE
rb_ary_includes(VALUE ary, VALUE item)
{
    long i;
    
    for (i=0; i<RARRAY_LEN(ary); i++) {
  if (rb_equal(yard_resolve_stub(RARRAY_PTR(ary)[i]), item)) {
      return Qtrue;
  }
    }
    return Qfalse;
}


/* 
 *  call-seq:
 *     array <=> other_array   ->  -1, 0, +1
 *
 *  Comparison---Returns an integer (-1, 0,
 *  or +1) if this array is less than, equal to, or greater than
 *  other_array.  Each object in each array is compared
 *  (using <=>). If any value isn't
 *  equal, then that inequality is the return value. If all the
 *  values found are equal, then the return is based on a
 *  comparison of the array lengths.  Thus, two arrays are
 *  ``equal'' according to <code>Array#<=></code> if and only if they have
 *  the same length and the value of each element is equal to the
 *  value of the corresponding element in the other array.
 *  
 *     [ "a", "a", "c" ]    <=> [ "a", "b", "c" ]   #=> -1
 *     [ 1, 2, 3, 4, 5, 6 ] <=> [ 1, 2 ]            #=> +1
 *
 */

VALUE
rb_ary_cmp(VALUE ary1, VALUE ary2)
{
    long i, len;

    ary2 = to_ary(ary2);
    len = RARRAY_LEN(ary1);
    if (len > RARRAY_LEN(ary2)) {
  len = RARRAY_LEN(ary2);
    }
    for (i=0; i<len; i++) {
  VALUE v = rb_funcall(rb_ary_elt(ary1, i), id_cmp, 1, rb_ary_elt(ary2, i));
  if (v != INT2FIX(0)) {
      return v;
  }
    }
    len = RARRAY_LEN(ary1) - RARRAY_LEN(ary2);
    if (len == 0) return INT2FIX(0);
    if (len > 0) return INT2FIX(1);
    return INT2FIX(-1);
}

static VALUE
ary_make_hash(VALUE ary1, VALUE ary2)
{
    VALUE hash = rb_hash_new();
    long i;

    for (i=0; i<RARRAY_LEN(ary1); i++) {
  rb_hash_aset(hash, yard_resolve_stub(RARRAY_PTR(ary1)[i]), Qtrue);
    }
    if (ary2) {
  for (i=0; i<RARRAY_LEN(ary2); i++) {
      rb_hash_aset(hash, yard_resolve_stub(RARRAY_PTR(ary2)[i]), Qtrue);
  }
    }
    return hash;
}

/* 
 *  call-seq:
 *     array - other_array    -> an_array
 *
 *  Array Difference---Returns a new array that is a copy of
 *  the original array, removing any items that also appear in
 *  other_array. (If you need set-like behavior, see the
 *  library class Set.)
 *
 *     [ 1, 1, 2, 2, 3, 3, 4, 5 ] - [ 1, 2, 4 ]  #=>  [ 3, 3, 5 ]
 */

static VALUE
rb_ary_diff(VALUE ary1, VALUE ary2)
{
    VALUE ary3;
    volatile VALUE hash;
    long i;

    hash = ary_make_hash(to_ary(ary2), 0);
    ary3 = rb_ary_new();

    for (i=0; i<RARRAY_LEN(ary1); i++) {
  if (st_lookup(RHASH_TBL(hash), yard_resolve_stub(RARRAY_PTR(ary1)[i]), 0)) continue;
  rb_ary_push(ary3, rb_ary_elt(ary1, i));
    }
    return ary3;
}

/* 
 *  call-seq:
 *     array & other_array
 *
 *  Set Intersection---Returns a new array
 *  containing elements common to the two arrays, with no duplicates.
 *
 *     [ 1, 1, 3, 5 ] & [ 1, 2, 3 ]   #=> [ 1, 3 ]
 */


static VALUE
rb_ary_and(VALUE ary1, VALUE ary2)
{
    VALUE hash, ary3, v, vv;
    long i;

    ary2 = to_ary(ary2);
    ary3 = rb_ary_new2(RARRAY_LEN(ary1) < RARRAY_LEN(ary2) ?
      RARRAY_LEN(ary1) : RARRAY_LEN(ary2));
    hash = ary_make_hash(ary2, 0);

    if (RHASH_EMPTY_P(hash))
        return ary3;

    for (i=0; i<RARRAY_LEN(ary1); i++) {
  v = vv = rb_ary_elt(ary1, i);
  if (st_delete(RHASH_TBL(hash), (st_data_t*)&vv, 0)) {
      rb_ary_push(ary3, v);
  }
    }

    return ary3;
}

/* 
 *  call-seq:
 *     array | other_array     ->  an_array
 *
 *  Set Union---Returns a new array by joining this array with
 *  other_array, removing duplicates.
 *
 *     [ "a", "b", "c" ] | [ "c", "d", "a" ]
 *            #=> [ "a", "b", "c", "d" ]
 */

static VALUE
rb_ary_or(VALUE ary1, VALUE ary2)
{
    VALUE hash, ary3;
    VALUE v, vv;
    long i;

    ary2 = to_ary(ary2);
    ary3 = rb_ary_new2(RARRAY_LEN(ary1)+RARRAY_LEN(ary2));
    hash = ary_make_hash(ary1, ary2);

    for (i=0; i<RARRAY_LEN(ary1); i++) {
  v = vv = rb_ary_elt(ary1, i);
  if (st_delete(RHASH_TBL(hash), (st_data_t*)&vv, 0)) {
      rb_ary_push(ary3, v);
  }
    }
    for (i=0; i<RARRAY_LEN(ary2); i++) {
  v = vv = rb_ary_elt(ary2, i);
  if (st_delete(RHASH_TBL(hash), (st_data_t*)&vv, 0)) {
      rb_ary_push(ary3, v);
  }
    }
    return ary3;
}

/*
 *  call-seq:
 *     array.uniq! -> array or nil
 *  
 *  Removes duplicate elements from _self_.
 *  Returns <code>nil</code> if no changes are made (that is, no
 *  duplicates are found).
 *     
 *     a = [ "a", "a", "b", "b", "c" ]
 *     a.uniq!   #=> ["a", "b", "c"]
 *     b = [ "a", "b", "c" ]
 *     b.uniq!   #=> nil
 */

static VALUE
rb_ary_uniq_bang(VALUE ary)
{
    VALUE hash, v, vv;
    long i, j;

    ary_iter_check(ary);
    hash = ary_make_hash(ary, 0);

    if (RARRAY_LEN(ary) == RHASH_SIZE(hash)) {
  return Qnil;
    }
    for (i=j=0; i<RARRAY_LEN(ary); i++) {
  v = vv = rb_ary_elt(ary, i);
  if (st_delete(RHASH_TBL(hash), (st_data_t*)&vv, 0)) {
      rb_ary_store(ary, j++, v);
  }
    }
    RARRAY(ary)->len = j;

    return ary;
}

/*
 *  call-seq:
 *     array.uniq   -> an_array
 *  
 *  Returns a new array by removing duplicate values in <i>self</i>.
 *     
 *     a = [ "a", "a", "b", "b", "c" ]
 *     a.uniq   #=> ["a", "b", "c"]
 */

static VALUE
rb_ary_uniq(VALUE ary)
{
    ary = rb_ary_dup(ary);
    rb_ary_uniq_bang(ary);
    return ary;
}

/* 
 *  call-seq:
 *     array.compact!    ->   array  or  nil
 *
 *  Removes +nil+ elements from array.
 *  Returns +nil+ if no changes were made.
 *
 *     [ "a", nil, "b", nil, "c" ].compact! #=> [ "a", "b", "c" ]
 *     [ "a", "b", "c" ].compact!           #=> nil
 */

static VALUE
rb_ary_compact_bang(VALUE ary)
{
    VALUE *p, *t, *end;
    long n;

    rb_ary_modify(ary);
    ary_iter_check(ary);
    p = t = RARRAY_PTR(ary);
    end = p + RARRAY_LEN(ary);
    
    while (t < end) {
  if (NIL_P(*t)) t++;
  else *p++ = *t++;
    }
    if (RARRAY_LEN(ary) == (p - RARRAY_PTR(ary))) {
  return Qnil;
    }
    n = p - RARRAY_PTR(ary);
    RESIZE_CAPA(ary, n);
    RARRAY(ary)->len = n;

    return ary;
}

/*
 *  call-seq:
 *     array.compact     ->  an_array
 *
 *  Returns a copy of _self_ with all +nil+ elements removed.
 *
 *     [ "a", nil, "b", nil, "c", nil ].compact
 *                       #=> [ "a", "b", "c" ]
 */

static VALUE
rb_ary_compact(VALUE ary)
{
    ary = rb_ary_dup(ary);
    rb_ary_compact_bang(ary);
    return ary;
}

/*
 *  call-seq:
 *     array.nitems -> int
 *     array.nitems { |item| block }  -> int
 *  
 *  Returns the number of non-<code>nil</code> elements in _self_.
 *  If a block is given, the elements yielding a true value are
 *  counted.
 *
 *  May be zero.
 *     
 *     [ 1, nil, 3, nil, 5 ].nitems   #=> 3
 *     [5,6,7,8,9].nitems { |x| x % 2 != 0 }  #=> 3
 */

static VALUE
rb_ary_nitems(VALUE ary)
{
    long n = 0;
 
    if (rb_block_given_p()) {
  long i;

  for (i=0; i<RARRAY_LEN(ary); i++) {
      VALUE v = yard_resolve_stub(RARRAY_PTR(ary)[i]);
      if (RTEST(rb_yield(v))) n++;
  }
    }
    else {
  VALUE *p = RARRAY_PTR(ary);
  VALUE *pend = p + RARRAY_LEN(ary);

  while (p < pend) {
      if (!NIL_P(*p)) n++;
      p++;
  }
    }
    return LONG2NUM(n);
}

static VALUE
flatten(VALUE ary, int level, int *modified)
{
    long i = 0;
    VALUE stack, result, tmp, elt;
    st_table *memo;
    st_data_t id;

    stack = rb_ary_new();
    result = rb_ary_new();
    memo = st_init_numtable();
    st_insert(memo, (st_data_t)ary, (st_data_t)Qtrue);
    *modified = 0;

    while (1) {
  while (i < RARRAY_LEN(ary)) {
      elt = yard_resolve_stub(RARRAY_PTR(ary)[i++]);
      tmp = rb_check_array_type(elt);
      if (NIL_P(tmp) || (level >= 0 && RARRAY_LEN(stack) / 2 >= level)) {
    rb_ary_push(result, elt);
      }
      else {
    *modified = 1;
    id = (st_data_t)tmp;
    if (st_lookup(memo, id, 0)) {
        rb_raise(rb_eArgError, "tried to flatten recursive array");
    }
    st_insert(memo, id, (st_data_t)Qtrue);
    rb_ary_push(stack, ary);
    rb_ary_push(stack, LONG2NUM(i));
    ary = tmp;
    i = 0;
      }
  }
  if (RARRAY_LEN(stack) == 0) {
      break;
  }
  id = (st_data_t)ary;
  st_delete(memo, &id, 0);
  tmp = rb_ary_pop(stack);
  i = NUM2LONG(tmp);
  ary = rb_ary_pop(stack);
    }

    return result;
}

/*
 *  call-seq:
 *     array.flatten! -> array or nil
 *     array.flatten!(level) -> array or nil
 *  
 *  Flattens _self_ in place.
 *  Returns <code>nil</code> if no modifications were made (i.e.,
 *  <i>array</i> contains no subarrays.)  If the optional <i>level</i>
 *  argument determins the level of recursion to flatten.
 *     
 *     a = [ 1, 2, [3, [4, 5] ] ]
 *     a.flatten!   #=> [1, 2, 3, 4, 5]
 *     a.flatten!   #=> nil
 *     a            #=> [1, 2, 3, 4, 5]
 *     a = [ 1, 2, [3, [4, 5] ] ]
 *     a.flatten!(1) #=> [1, 2, 3, [4, 5]]
 */

static VALUE
rb_ary_flatten_bang(int argc, VALUE *argv, VALUE ary)
{
    int mod = 0, level = -1;
    VALUE result, lv;

    rb_scan_args(argc, argv, "01", &lv);
    if (!NIL_P(lv)) level = NUM2INT(lv);
    if (level == 0) return ary;

    result = flatten(ary, level, &mod);
    if (mod == 0) return Qnil;
    rb_ary_replace(ary, result);

    return ary;
}

/*
 *  call-seq:
 *     array.flatten -> an_array
 *     array.flatten(level) -> an_array
 *  
 *  Returns a new array that is a one-dimensional flattening of this
 *  array (recursively). That is, for every element that is an array,
 *  extract its elements into the new array.  If the optional
 *  <i>level</i> argument determins the level of recursion to flatten.
 *     
 *     s = [ 1, 2, 3 ]           #=> [1, 2, 3]
 *     t = [ 4, 5, 6, [7, 8] ]   #=> [4, 5, 6, [7, 8]]
 *     a = [ s, t, 9, 10 ]       #=> [[1, 2, 3], [4, 5, 6, [7, 8]], 9, 10]
 *     a.flatten                 #=> [1, 2, 3, 4, 5, 6, 7, 8, 9, 10
 *     a = [ 1, 2, [3, [4, 5] ] ]
 *     a.flatten(1)              #=> [1, 2, 3, [4, 5]]
 */

static VALUE
rb_ary_flatten(int argc, VALUE *argv, VALUE ary)
{
    int mod = 0, level = -1;
    VALUE result, lv;

    rb_scan_args(argc, argv, "01", &lv);
    if (!NIL_P(lv)) level = NUM2INT(lv);
    if (level == 0) return ary;

    result = flatten(ary, level, &mod);
    if (OBJ_TAINTED(ary)) OBJ_TAINT(result);

    return result;
}

/*
 *  call-seq:
 *     array.shuffle!        -> array or nil
 *  
 *  Shuffles elements in _self_ in place.
 */


static VALUE
rb_ary_shuffle_bang(VALUE ary)
{
    long i = RARRAY_LEN(ary);

    rb_ary_modify(ary);
    ary_iter_check(ary);
    while (i) {
  long j = rb_genrand_real()*i;
  VALUE tmp = RARRAY_PTR(ary)[--i];
  RARRAY_PTR(ary)[i] = RARRAY_PTR(ary)[j];
  RARRAY_PTR(ary)[j] = tmp;
    }
    return ary;
}


/*
 *  call-seq:
 *     array.shuffle -> an_array
 *  
 *  Returns a new array with elements of this array shuffled.
 *     
 *     a = [ 1, 2, 3 ]           #=> [1, 2, 3]
 *     a.shuffle                 #=> [2, 3, 1]
 */

static VALUE
rb_ary_shuffle(VALUE ary)
{
    ary = rb_ary_dup(ary);
    rb_ary_shuffle_bang(ary);
    return ary;
}


/*
 *  call-seq:
 *     array.choice        -> obj
 *  
 *  Choose a random element from an array.
 */


static VALUE
rb_ary_choice(VALUE ary)
{
    long i, j;

    i = RARRAY_LEN(ary);
    if (i == 0) return Qnil;
    j = rb_genrand_real()*i;
    return yard_resolve_stub(RARRAY_PTR(ary)[j]);
}


/*
 *  call-seq:
 *     ary.cycle {|obj| block }
 *  
 *  Calls <i>block</i> repeatedly forever.
 *     
 *     a = ["a", "b", "c"]
 *     a.cycle {|x| puts x }  # print, a, b, c, a, b, c,.. forever.
 *     
 */

static VALUE
rb_ary_cycle(VALUE ary)
{
    long i;

    RETURN_ENUMERATOR(ary, 0, 0);
    while (RARRAY_LEN(ary) > 0) {
  for (i=0; i<RARRAY_LEN(ary); i++) {
      rb_yield(yard_resolve_stub(RARRAY_PTR(ary)[i]));
  }
    }
    return Qnil;
}

static VALUE
tmpbuf(int n, int size)
{
    VALUE buf = rb_str_new(0, n*size);

    RBASIC(buf)->klass = 0;
    return buf;
}

/*
 * Recursively compute permutations of r elements of the set [0..n-1].
 * When we have a complete permutation of array indexes, copy the values
 * at those indexes into a new array and yield that array. 
 *
 * n: the size of the set 
 * r: the number of elements in each permutation
 * p: the array (of size r) that we're filling in
 * index: what index we're filling in now
 * used: an array of booleans: whether a given index is already used
 * values: the Ruby array that holds the actual values to permute
 */
static void
permute0(long n, long r, long *p, long index, int *used, VALUE values)
{
    long i,j;
    for (i = 0; i < n; i++) {
  if (used[i] == 0) {
      p[index] = i;
      if (index < r-1) {             /* if not done yet */
    used[i] = 1;               /* mark index used */
    permute0(n, r, p, index+1, /* recurse */
       used, values);  
    used[i] = 0;               /* index unused */
      }
      else {
    /* We have a complete permutation of array indexes */
    /* Build a ruby array of the corresponding values */
    /* And yield it to the associated block */
    VALUE result = rb_ary_new2(r);
    VALUE *result_array = RARRAY_PTR(result);
    const VALUE *values_array = RARRAY_PTR(values);

    for (j = 0; j < r; j++) result_array[j] = values_array[p[j]];
    RARRAY(result)->len = r;
    rb_yield(yard_resolve_stub(result));
      }
  }
    }
}

/*
 *  call-seq:
 *     ary.permutation { |p| block }          -> array
 *     ary.permutation                        -> enumerator
 *     ary.permutation(n) { |p| block }       -> array
 *     ary.permutation(n)                     -> enumerator
 *  
 * When invoked with a block, yield all permutations of length <i>n</i>
 * of the elements of <i>ary</i>, then return the array itself.
 * If <i>n</i> is not specified, yield all permutations of all elements.
 * The implementation makes no guarantees about the order in which 
 * the permutations are yielded.
 *
 * When invoked without a block, return an enumerator object instead.
 * 
 * Examples:
 *     a = [1, 2, 3]
 *     a.permutation.to_a     #=> [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *     a.permutation(1).to_a  #=> [[1],[2],[3]]
 *     a.permutation(2).to_a  #=> [[1,2],[1,3],[2,1],[2,3],[3,1],[3,2]]
 *     a.permutation(3).to_a  #=> [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *     a.permutation(0).to_a  #=> [[]]: one permutation of length 0
 *     a.permutation(4).to_a  #=> []  : no permutations of length 4
 */

static VALUE
rb_ary_permutation(int argc, VALUE *argv, VALUE ary)
{
    VALUE num;
    long r, n, i;

    RETURN_ENUMERATOR(ary, argc, argv);   /* Return enumerator if no block */
    n = RARRAY_LEN(ary);                  /* Array length */
    rb_scan_args(argc, argv, "01", &num);
    r = NIL_P(num) ? n : NUM2LONG(num);   /* Permutation size from argument */

    if (r < 0 || n < r) { 
  /* no permutations: yield nothing */
    }
    else if (r == 0) { /* exactly one permutation: the zero-length array */
  rb_yield(rb_ary_new2(0));
    }
    else if (r == 1) { /* this is a special, easy case */
  for (i = 0; i < RARRAY_LEN(ary); i++) {
      rb_yield(rb_ary_new3(1, yard_resolve_stub(RARRAY_PTR(ary)[i])));
  }
    }
    else {             /* this is the general case */
  volatile VALUE t0 = tmpbuf(n,sizeof(long));
  long *p = (long*)RSTRING_PTR(t0);
  volatile VALUE t1 = tmpbuf(n,sizeof(int));
  int *used = (int*)RSTRING_PTR(t1);
  VALUE ary0 = ary_make_shared(ary); /* private defensive copy of ary */

  for (i = 0; i < n; i++) used[i] = 0; /* initialize array */

  permute0(n, r, p, 0, used, ary0); /* compute and yield permutations */
  RB_GC_GUARD(t0);
  RB_GC_GUARD(t1);
    }
    return ary;
}

static long
combi_len(long n, long k)
{
    long i, val = 1;

    if (k*2 > n) k = n-k;
    if (k == 0) return 1;
    if (k < 0) return 0;
    val = 1;
    for (i=1; i <= k; i++,n--) {
  val *= n;
  val /= i;
    }
    return val;
}

/*
 *  call-seq:
 *     ary.combination(n) { |c| block }    -> ary
 *     ary.combination(n)                  -> enumerator
 *  
 * When invoked with a block, yields all combinations of length <i>n</i> 
 * of elements from <i>ary</i> and then returns <i>ary</i> itself.
 * The implementation makes no guarantees about the order in which 
 * the combinations are yielded.
 *
 * When invoked without a block, returns an enumerator object instead.
 *     
 * Examples:
 *     a = [1, 2, 3, 4]
 *     a.combination(1).to_a  #=> [[1],[2],[3],[4]]
 *     a.combination(2).to_a  #=> [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 *     a.combination(3).to_a  #=> [[1,2,3],[1,2,4],[1,3,4],[2,3,4]]
 *     a.combination(4).to_a  #=> [[1,2,3,4]]
 *     a.combination(0).to_a  #=> [[]]: one combination of length 0
 *     a.combination(5).to_a  #=> []  : no combinations of length 5
 *     
 */

static VALUE
rb_ary_combination(VALUE ary, VALUE num)
{
    long n, i, len;

    RETURN_ENUMERATOR(ary, 1, &num);
    n = NUM2LONG(num);
    len = RARRAY_LEN(ary);
    if (n < 0 || len < n) {
  /* yield nothing */
    }
    else if (n == 0) {
  rb_yield(rb_ary_new2(0));
    }
    else if (n == 1) {
  for (i = 0; i < len; i++) {
      rb_yield(rb_ary_new3(1, yard_resolve_stub(RARRAY_PTR(ary)[i])));
  }
    }
    else {
  volatile VALUE t0 = tmpbuf(n+1, sizeof(long));
  long *stack = (long*)RSTRING_PTR(t0);
  long nlen = combi_len(len, n);
  volatile VALUE cc = rb_ary_new2(n);
  VALUE *chosen = RARRAY_PTR(cc);
  long lev = 0;

  RBASIC(cc)->klass = 0;
  MEMZERO(stack, long, n);
  stack[0] = -1;
  for (i = 0; i < nlen; i++) {
      chosen[lev] = yard_resolve_stub(RARRAY_PTR(ary)[stack[lev+1]]);
      for (lev++; lev < n; lev++) {
    chosen[lev] = yard_resolve_stub(RARRAY_PTR(ary)[stack[lev+1] = stack[lev]+1]);
      }
      rb_yield(rb_ary_new4(n, chosen));
      do {
    stack[lev--]++;
      } while (lev && (stack[lev+1]+n == len+lev+1));
  }
    }
    return ary;
}

/*
 *  call-seq:
 *     ary.product(other_ary, ...)
 *  
 *  Returns an array of all combinations of elements from all arrays.
 *  The length of the returned array is the product of the length
 *  of ary and the argument arrays
 *     
 *     [1,2,3].product([4,5])     # => [[1,4],[1,5],[2,4],[2,5],[3,4],[3,5]]
 *     [1,2].product([1,2])       # => [[1,1],[1,2],[2,1],[2,2]]
 *     [1,2].product([3,4],[5,6]) # => [[1,3,5],[1,3,6],[1,4,5],[1,4,6],
 *                                #     [2,3,5],[2,3,6],[2,4,5],[2,4,6]]
 *     [1,2].product()            # => [[1],[2]]
 *     [1,2].product([])          # => []
 */

static VALUE
rb_ary_product(int argc, VALUE *argv, VALUE ary)
{
    int n = argc+1;    /* How many arrays we're operating on */
    volatile VALUE t0 = tmpbuf(n, sizeof(VALUE));
    volatile VALUE t1 = tmpbuf(n, sizeof(int));
    VALUE *arrays = (VALUE*)RSTRING_PTR(t0); /* The arrays we're computing the product of */
    int *counters = (int*)RSTRING_PTR(t1); /* The current position in each one */
    VALUE result;      /* The array we'll be returning */
    long i,j;
    long resultlen = 1;

    RBASIC(t0)->klass = 0;
    RBASIC(t1)->klass = 0;

    /* initialize the arrays of arrays */
    arrays[0] = ary;
    for (i = 1; i < n; i++) arrays[i] = to_ary(argv[i-1]);
    
    /* initialize the counters for the arrays */
    for (i = 0; i < n; i++) counters[i] = 0;

    /* Compute the length of the result array; return [] if any is empty */
    for (i = 0; i < n; i++) {
  resultlen *= RARRAY_LEN(arrays[i]);
  if (resultlen == 0) return rb_ary_new2(0);
    }

    /* Otherwise, allocate and fill in an array of results */
    result = rb_ary_new2(resultlen);
    for (i = 0; i < resultlen; i++) {
  int m;
  /* fill in one subarray */
  VALUE subarray = rb_ary_new2(n);
  for (j = 0; j < n; j++) {
      rb_ary_push(subarray, rb_ary_entry(arrays[j], counters[j]));
  }

  /* put it on the result array */
  rb_ary_push(result, subarray);

  /*
   * Increment the last counter.  If it overflows, reset to 0
   * and increment the one before it.
   */
  m = n-1;
  counters[m]++;
  while (m > 0 && counters[m] == RARRAY_LEN(arrays[m])) {
      counters[m] = 0;
      m--;
      counters[m]++;
  }
    }

    return result;
}



/* Arrays are ordered, integer-indexed collections of any object. 
 * Array indexing starts at 0, as in C or Java.  A negative index is 
 * assumed to be relative to the end of the array---that is, an index of -1 
 * indicates the last element of the array, -2 is the next to last 
 * element in the array, and so on. 
 */

void
Init_Array(void)
{
    rb_cArray  = rb_define_class("Array", rb_cObject);
    rb_include_module(rb_cArray, rb_mEnumerable);

    rb_define_alloc_func(rb_cArray, ary_alloc);
    rb_define_singleton_method(rb_cArray, "[]", rb_ary_s_create, -1);
    rb_define_singleton_method(rb_cArray, "try_convert", rb_ary_s_try_convert, 1);
    rb_define_method(rb_cArray, "initialize", rb_ary_initialize, -1);
    rb_define_method(rb_cArray, "initialize_copy", rb_ary_replace, 1);

    rb_define_method(rb_cArray, "to_s", rb_ary_inspect, 0);
    rb_define_method(rb_cArray, "inspect", rb_ary_inspect, 0);
    rb_define_method(rb_cArray, "to_a", rb_ary_to_a, 0);
    rb_define_method(rb_cArray, "to_ary", rb_ary_to_ary_m, 0);
    rb_define_method(rb_cArray, "frozen?",  rb_ary_frozen_p, 0);

    rb_define_method(rb_cArray, "==", rb_ary_equal, 1);
    rb_define_method(rb_cArray, "eql?", rb_ary_eql, 1);
    rb_define_method(rb_cArray, "hash", rb_ary_hash, 0);

    rb_define_method(rb_cArray, "[]", rb_ary_aref, -1);
    rb_define_method(rb_cArray, "[]=", rb_ary_aset, -1);
    rb_define_method(rb_cArray, "at", rb_ary_at, 1);
    rb_define_method(rb_cArray, "fetch", rb_ary_fetch, -1);
    rb_define_method(rb_cArray, "first", rb_ary_first, -1);
    rb_define_method(rb_cArray, "last", rb_ary_last, -1);
    rb_define_method(rb_cArray, "concat", rb_ary_concat, 1);
    rb_define_method(rb_cArray, "<<", rb_ary_push, 1);
    rb_define_method(rb_cArray, "push", rb_ary_push_m, -1);
    rb_define_method(rb_cArray, "pop", rb_ary_pop_m, -1);
    rb_define_method(rb_cArray, "shift", rb_ary_shift_m, -1);
    rb_define_method(rb_cArray, "unshift", rb_ary_unshift_m, -1);
    rb_define_method(rb_cArray, "insert", rb_ary_insert, -1);
    rb_define_method(rb_cArray, "each", rb_ary_each, 0);
    rb_define_method(rb_cArray, "each_index", rb_ary_each_index, 0);
    rb_define_method(rb_cArray, "reverse_each", rb_ary_reverse_each, 0);
    rb_define_method(rb_cArray, "length", rb_ary_length, 0);
    rb_define_alias(rb_cArray,  "size", "length");
    rb_define_method(rb_cArray, "empty?", rb_ary_empty_p, 0);
    rb_define_method(rb_cArray, "index", rb_ary_index, -1);
    rb_define_method(rb_cArray, "rindex", rb_ary_rindex, -1);
    rb_define_method(rb_cArray, "join", rb_ary_join_m, -1);
    rb_define_method(rb_cArray, "reverse", rb_ary_reverse_m, 0);
    rb_define_method(rb_cArray, "reverse!", rb_ary_reverse_bang, 0);
    rb_define_method(rb_cArray, "sort", rb_ary_sort, 0);
    rb_define_method(rb_cArray, "sort!", rb_ary_sort_bang, 0);
    rb_define_method(rb_cArray, "collect", rb_ary_collect, 0);
    rb_define_method(rb_cArray, "collect!", rb_ary_collect_bang, 0);
    rb_define_method(rb_cArray, "map", rb_ary_collect, 0);
    rb_define_method(rb_cArray, "map!", rb_ary_collect_bang, 0);
    rb_define_method(rb_cArray, "select", rb_ary_select, 0);
    rb_define_method(rb_cArray, "values_at", rb_ary_values_at, -1);
    rb_define_method(rb_cArray, "delete", rb_ary_delete, 1);
    rb_define_method(rb_cArray, "delete_at", rb_ary_delete_at_m, 1);
    rb_define_method(rb_cArray, "delete_if", rb_ary_delete_if, 0);
    rb_define_method(rb_cArray, "reject", rb_ary_reject, 0);
    rb_define_method(rb_cArray, "reject!", rb_ary_reject_bang, 0);
    rb_define_method(rb_cArray, "transpose", rb_ary_transpose, 0);
    rb_define_method(rb_cArray, "replace", rb_ary_replace, 1);
    rb_define_method(rb_cArray, "clear", rb_ary_clear, 0);
    rb_define_method(rb_cArray, "fill", rb_ary_fill, -1);
    rb_define_method(rb_cArray, "include?", rb_ary_includes, 1);
    rb_define_method(rb_cArray, "<=>", rb_ary_cmp, 1);

    rb_define_method(rb_cArray, "slice", rb_ary_aref, -1);
    rb_define_method(rb_cArray, "slice!", rb_ary_slice_bang, -1);

    rb_define_method(rb_cArray, "assoc", rb_ary_assoc, 1);
    rb_define_method(rb_cArray, "rassoc", rb_ary_rassoc, 1);

    rb_define_method(rb_cArray, "+", rb_ary_plus, 1);
    rb_define_method(rb_cArray, "*", rb_ary_times, 1);

    rb_define_method(rb_cArray, "-", rb_ary_diff, 1);
    rb_define_method(rb_cArray, "&", rb_ary_and, 1);
    rb_define_method(rb_cArray, "|", rb_ary_or, 1);

    rb_define_method(rb_cArray, "uniq", rb_ary_uniq, 0);
    rb_define_method(rb_cArray, "uniq!", rb_ary_uniq_bang, 0);
    rb_define_method(rb_cArray, "compact", rb_ary_compact, 0);
    rb_define_method(rb_cArray, "compact!", rb_ary_compact_bang, 0);
    rb_define_method(rb_cArray, "flatten", rb_ary_flatten, -1);
    rb_define_method(rb_cArray, "flatten!", rb_ary_flatten_bang, -1);
    rb_define_method(rb_cArray, "nitems", rb_ary_nitems, 0);
    rb_define_method(rb_cArray, "shuffle!", rb_ary_shuffle_bang, 0);
    rb_define_method(rb_cArray, "shuffle", rb_ary_shuffle, 0);
    rb_define_method(rb_cArray, "choice", rb_ary_choice, 0);
    rb_define_method(rb_cArray, "cycle", rb_ary_cycle, 0);
    rb_define_method(rb_cArray, "permutation", rb_ary_permutation, -1);
    rb_define_method(rb_cArray, "combination", rb_ary_combination, 1);
    rb_define_method(rb_cArray, "product", rb_ary_product, -1);

    id_cmp = rb_intern("<=>");
}
