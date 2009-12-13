/**********************************************************************

  string.c -

  $Author: nobu $
  $Date: 2007-12-25 19:01:06 +0900 (Tue, 25 Dec 2007) $
  created at: Mon Aug  9 17:12:58 JST 1993

  Copyright (C) 1993-2007 Yukihiro Matsumoto
  Copyright (C) 2000  Network Applied Communication Laboratory, Inc.
  Copyright (C) 2000  Information-technology Promotion Agency, Japan

**********************************************************************/

#include "ruby/ruby.h"
#include "ruby/re.h"
#include "ruby/encoding.h"

#define BEG(no) regs->beg[no]
#define END(no) regs->end[no]

#include <math.h>
#include <ctype.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

VALUE rb_cString;
VALUE rb_cSymbol;

#define STR_TMPLOCK FL_USER7
#define STR_NOEMBED FL_USER1
#define STR_SHARED  FL_USER2 /* = ELTS_SHARED */
#define STR_ASSOC   FL_USER3
#define STR_SHARED_P(s) FL_ALL(s, STR_NOEMBED|ELTS_SHARED)
#define STR_ASSOC_P(s)  FL_ALL(s, STR_NOEMBED|STR_ASSOC)
#define STR_NOCAPA  (STR_NOEMBED|ELTS_SHARED|STR_ASSOC)
#define STR_NOCAPA_P(s) (FL_TEST(s,STR_NOEMBED) && FL_ANY(s,ELTS_SHARED|STR_ASSOC))
#define STR_UNSET_NOCAPA(s) do {\
    if (FL_TEST(s,STR_NOEMBED)) FL_UNSET(s,(ELTS_SHARED|STR_ASSOC));\
} while (0)
				    

#define STR_SET_NOEMBED(str) do {\
    FL_SET(str, STR_NOEMBED);\
    STR_SET_EMBED_LEN(str, 0);\
} while (0)
#define STR_SET_EMBED(str) FL_UNSET(str, STR_NOEMBED)
#define STR_EMBED_P(str) (!FL_TEST(str, STR_NOEMBED))
#define STR_SET_EMBED_LEN(str, n) do { \
    long tmp_n = (n);\
    RBASIC(str)->flags &= ~RSTRING_EMBED_LEN_MASK;\
    RBASIC(str)->flags |= (tmp_n) << RSTRING_EMBED_LEN_SHIFT;\
} while (0)

#define STR_SET_LEN(str, n) do { \
    if (STR_EMBED_P(str)) {\
	STR_SET_EMBED_LEN(str, n);\
    }\
    else {\
	RSTRING(str)->as.heap.len = (n);\
    }\
} while (0) 

#define STR_DEC_LEN(str) do {\
    if (STR_EMBED_P(str)) {\
	long n = RSTRING_LEN(str);\
	n--;\
	STR_SET_EMBED_LEN(str, n);\
    }\
    else {\
	RSTRING(str)->as.heap.len--;\
    }\
} while (0)

#define RESIZE_CAPA(str,capacity) do {\
    if (STR_EMBED_P(str)) {\
	if ((capacity) > RSTRING_EMBED_LEN_MAX) {\
	    char *tmp = ALLOC_N(char, capacity+1);\
	    memcpy(tmp, RSTRING_PTR(str), RSTRING_LEN(str));\
	    RSTRING(str)->as.heap.ptr = tmp;\
	    RSTRING(str)->as.heap.len = RSTRING_LEN(str);\
            STR_SET_NOEMBED(str);\
	    RSTRING(str)->as.heap.aux.capa = (capacity);\
	}\
    }\
    else {\
	REALLOC_N(RSTRING(str)->as.heap.ptr, char, (capacity)+1);\
	if (!STR_NOCAPA_P(str))\
	    RSTRING(str)->as.heap.aux.capa = (capacity);\
    }\
} while (0)

#define is_ascii_string(str) (rb_enc_str_coderange(str) == ENC_CODERANGE_7BIT)
#define IS_7BIT(str) (ENC_CODERANGE(str) == ENC_CODERANGE_7BIT)
#define is_broken_string(str) (rb_enc_str_coderange(str) == ENC_CODERANGE_BROKEN)

VALUE rb_fs;

int
rb_enc_str_coderange(VALUE str)
{
    int cr = ENC_CODERANGE(str);

    if (cr == ENC_CODERANGE_UNKNOWN) {
	rb_encoding *enc = rb_enc_get(str);

        const char *p = RSTRING_PTR(str);
        const char *e = p + RSTRING_LEN(str);

        cr = rb_enc_asciicompat(enc) ? ENC_CODERANGE_7BIT : ENC_CODERANGE_VALID;
        while (p < e) {
            int ret = rb_enc_precise_mbclen(p, e, enc);
            int len = MBCLEN_CHARFOUND(ret);

            if (len) {
                if (len != 1 || !rb_enc_isascii((unsigned char)*p, enc)) {
                    cr = ENC_CODERANGE_VALID;
                }
                p += len;
            }
            else {
                cr = ENC_CODERANGE_BROKEN;
                break;
            }
        }
        ENC_CODERANGE_SET(str, cr);
    }
    return cr;
}

int rb_enc_str_asciionly_p(VALUE str)
{
    rb_encoding *enc = rb_enc_get(str);

    if (!rb_enc_asciicompat(enc))
        return Qfalse;
    else if (rb_enc_str_coderange(str) == ENC_CODERANGE_7BIT)
        return Qtrue;
    return Qfalse;
}

static inline void
str_mod_check(VALUE s, char *p, long len)
{
    if (RSTRING_PTR(s) != p || RSTRING_LEN(s) != len){
	rb_raise(rb_eRuntimeError, "string modified");
    }
}

static inline void
str_frozen_check(VALUE s)
{
    if (OBJ_FROZEN(s)) {
	rb_raise(rb_eRuntimeError, "string frozen");
    }
}

static VALUE
str_alloc(VALUE klass)
{
    NEWOBJ(str, struct RString);
    OBJSETUP(str, klass, T_STRING);

    if (klass == rb_cSymbol) {
	/* need to be registered in table */
	RBASIC(str)->klass = rb_cString;
    }
    str->as.heap.ptr = 0;
    str->as.heap.len = 0;
    str->as.heap.aux.capa = 0;

    return (VALUE)str;
}

static VALUE
str_new(VALUE klass, const char *ptr, long len)
{
    VALUE str;

    if (len < 0) {
	rb_raise(rb_eArgError, "negative string size (or size too big)");
    }

    str = str_alloc(klass);
    if (len > RSTRING_EMBED_LEN_MAX) {
	RSTRING(str)->as.heap.aux.capa = len;
	RSTRING(str)->as.heap.ptr = ALLOC_N(char,len+1);
	STR_SET_NOEMBED(str);
    }
    if (ptr) {
	memcpy(RSTRING_PTR(str), ptr, len);
    }
    STR_SET_LEN(str, len);
    RSTRING_PTR(str)[len] = '\0';
    return str;
}

VALUE
rb_str_new(const char *ptr, long len)
{
    return str_new(rb_cString, ptr, len);
}

VALUE
rb_enc_str_new(const char *ptr, long len, rb_encoding *enc)
{
    VALUE str = str_new(rb_cString, ptr, len);

    rb_enc_associate(str, enc);
    return str;
}

VALUE
rb_str_new2(const char *ptr)
{
    if (!ptr) {
	rb_raise(rb_eArgError, "NULL pointer given");
    }
    return rb_str_new(ptr, strlen(ptr));
}

VALUE
rb_tainted_str_new(const char *ptr, long len)
{
    VALUE str = rb_str_new(ptr, len);

    OBJ_TAINT(str);
    return str;
}

VALUE
rb_tainted_str_new2(const char *ptr)
{
    VALUE str = rb_str_new2(ptr);

    OBJ_TAINT(str);
    return str;
}

static VALUE
str_new_shared(VALUE klass, VALUE str)
{
    VALUE str2 = str_alloc(klass);

    if (RSTRING_LEN(str) <= RSTRING_EMBED_LEN_MAX) {
	STR_SET_EMBED(str2);
	memcpy(RSTRING_PTR(str2), RSTRING_PTR(str), RSTRING_LEN(str)+1);
	STR_SET_EMBED_LEN(str2, RSTRING_LEN(str));
    }
    else {
	FL_SET(str2, STR_NOEMBED);
	RSTRING(str2)->as.heap.len = RSTRING_LEN(str);
	RSTRING(str2)->as.heap.ptr = RSTRING_PTR(str);
	RSTRING(str2)->as.heap.aux.shared = str;
	FL_SET(str2, ELTS_SHARED);
    }

    return str2;
}

static VALUE
str_new3(VALUE klass, VALUE str)
{
    VALUE str2 = str_new_shared(klass, str);

    rb_enc_copy(str2, str);
    return str2;
}

VALUE
rb_str_new3(VALUE str)
{
    VALUE str2 = str_new3(rb_obj_class(str), str);

    OBJ_INFECT(str2, str);
    return str2;
}

static VALUE
str_new4(VALUE klass, VALUE str)
{
    VALUE str2;

    str2 = str_alloc(klass);
    STR_SET_NOEMBED(str2);
    RSTRING(str2)->as.heap.len = RSTRING_LEN(str);
    RSTRING(str2)->as.heap.ptr = RSTRING_PTR(str);
    if (STR_SHARED_P(str)) {
	FL_SET(str2, ELTS_SHARED);
	RSTRING(str2)->as.heap.aux.shared = RSTRING(str)->as.heap.aux.shared;
    }
    else {
	FL_SET(str, ELTS_SHARED);
	RSTRING(str)->as.heap.aux.shared = str2;
    }
    rb_enc_copy(str2, str);
    OBJ_INFECT(str2, str);
    return str2;
}

VALUE
rb_str_new4(VALUE orig)
{
    VALUE klass, str;

    if (OBJ_FROZEN(orig)) return orig;
    klass = rb_obj_class(orig);
    if (STR_SHARED_P(orig) && (str = RSTRING(orig)->as.heap.aux.shared)
	&& klass == RBASIC(str)->klass) {
	long ofs;
	ofs = RSTRING_LEN(str) - RSTRING_LEN(orig);
	if ((ofs > 0) || (!OBJ_TAINTED(str) && OBJ_TAINTED(orig))) {
	    str = str_new3(klass, str);
	    RSTRING(str)->as.heap.ptr += ofs;
	    RSTRING(str)->as.heap.len -= ofs;
	}
    }
    else if (STR_ASSOC_P(orig) || STR_EMBED_P(orig)) {
	str = str_new(klass, RSTRING_PTR(orig), RSTRING_LEN(orig));
	rb_enc_copy(str, orig);
    }
    else {
	str = str_new4(klass, orig);
    }
    OBJ_INFECT(str, orig);
    OBJ_FREEZE(str);
    return str;
}

VALUE
rb_str_new5(VALUE obj, const char *ptr, long len)
{
    return str_new(rb_obj_class(obj), ptr, len);
}

#define STR_BUF_MIN_SIZE 128

VALUE
rb_str_buf_new(long capa)
{
    VALUE str = str_alloc(rb_cString);

    if (capa < STR_BUF_MIN_SIZE) {
	capa = STR_BUF_MIN_SIZE;
    }
    FL_SET(str, STR_NOEMBED);
    RSTRING(str)->as.heap.aux.capa = capa;
    RSTRING(str)->as.heap.ptr = ALLOC_N(char, capa+1);
    RSTRING(str)->as.heap.ptr[0] = '\0';

    return str;
}

VALUE
rb_str_buf_new2(const char *ptr)
{
    VALUE str;
    long len = strlen(ptr);

    str = rb_str_buf_new(len);
    rb_str_buf_cat(str, ptr, len);

    return str;
}

VALUE
rb_str_tmp_new(long len)
{
    return str_new(0, 0, len);
}

void
rb_str_free(VALUE str)
{
    if (!STR_EMBED_P(str) && !STR_SHARED_P(str)) {
	xfree(RSTRING(str)->as.heap.ptr);
    }
}

VALUE
rb_str_to_str(VALUE str)
{
    return rb_convert_type(str, T_STRING, "String", "to_str");
}

void
rb_str_shared_replace(VALUE str, VALUE str2)
{
    if (str == str2) return;
    rb_str_modify(str);
    if (OBJ_TAINTED(str2)) OBJ_TAINT(str);
    if (RSTRING_LEN(str2) <= RSTRING_EMBED_LEN_MAX) {
	STR_SET_EMBED(str);
	memcpy(RSTRING_PTR(str), RSTRING_PTR(str2), RSTRING_LEN(str2)+1);
	STR_SET_EMBED_LEN(str, RSTRING_LEN(str2));
	return;
    }
    if (!STR_SHARED_P(str) && !STR_EMBED_P(str)) {
	free(RSTRING_PTR(str));
    }
    STR_SET_NOEMBED(str);
    STR_UNSET_NOCAPA(str);
    RSTRING(str)->as.heap.ptr = RSTRING_PTR(str2);
    RSTRING(str)->as.heap.len = RSTRING_LEN(str2);
    if (STR_NOCAPA_P(str2)) {
	FL_SET(str, RBASIC(str2)->flags & STR_NOCAPA);
	RSTRING(str)->as.heap.aux.shared = RSTRING(str2)->as.heap.aux.shared;
    }
    else {
	RSTRING(str)->as.heap.aux.capa = RSTRING(str2)->as.heap.aux.capa;
    }
    RSTRING(str2)->as.heap.ptr = 0;	/* abandon str2 */
    RSTRING(str2)->as.heap.len = 0;
    RSTRING(str2)->as.heap.aux.capa = 0;
    STR_UNSET_NOCAPA(str2);
}

static ID id_to_s;

VALUE
rb_obj_as_string(VALUE obj)
{
    VALUE str;

    if (TYPE(obj) == T_STRING) {
	return obj;
    }
    str = rb_funcall(obj, id_to_s, 0);
    if (TYPE(str) != T_STRING)
	return rb_any_to_s(obj);
    if (OBJ_TAINTED(obj)) OBJ_TAINT(str);
    return str;
}

static VALUE rb_str_replace(VALUE, VALUE);

VALUE
rb_str_dup(VALUE str)
{
    VALUE dup = str_alloc(rb_obj_class(str));
    rb_str_replace(dup, str);
    return dup;
}


/*
 *  call-seq:
 *     String.new(str="")   => new_str
 *  
 *  Returns a new string object containing a copy of <i>str</i>.
 */

static VALUE
rb_str_init(int argc, VALUE *argv, VALUE str)
{
    VALUE orig;

    if (rb_scan_args(argc, argv, "01", &orig) == 1)
	rb_str_replace(str, orig);
    return str;
}

static long
str_strlen(VALUE str, rb_encoding *enc)
{
    long len;

    if (is_ascii_string(str)) return RSTRING_LEN(str);
    if (!enc) enc = rb_enc_get(str);
    len = rb_enc_strlen(RSTRING_PTR(str), RSTRING_END(str), enc);
    if (len < 0) {
	rb_raise(rb_eArgError, "invalid mbstring sequence");
    }
    return len;
}

/*
 *  call-seq:
 *     str.length   => integer
 *     str.size     => integer
 *  
 *  Returns the character length of <i>str</i>.
 */

VALUE
rb_str_length(VALUE str)
{
    int len;

    len = str_strlen(str, rb_enc_get(str));
    return INT2NUM(len);
}

/*
 *  call-seq:
 *     str.bytesize  => integer
 *  
 *  Returns the length of <i>str</i> in bytes.
 */

static VALUE
rb_str_bytesize(VALUE str)
{
    return INT2NUM(RSTRING_LEN(str));
}

/*
 *  call-seq:
 *     str.empty?   => true or false
 *  
 *  Returns <code>true</code> if <i>str</i> has a length of zero.
 *     
 *     "hello".empty?   #=> false
 *     "".empty?        #=> true
 */

static VALUE
rb_str_empty(VALUE str)
{
    if (RSTRING_LEN(str) == 0)
	return Qtrue;
    return Qfalse;
}

/*
 *  call-seq:
 *     str + other_str   => new_str
 *  
 *  Concatenation---Returns a new <code>String</code> containing
 *  <i>other_str</i> concatenated to <i>str</i>.
 *     
 *     "Hello from " + self.to_s   #=> "Hello from main"
 */

VALUE
rb_str_plus(VALUE str1, VALUE str2)
{
    VALUE str3;
    rb_encoding *enc;

    StringValue(str2);
    enc = rb_enc_check(str1, str2);
    str3 = rb_str_new(0, RSTRING_LEN(str1)+RSTRING_LEN(str2));
    memcpy(RSTRING_PTR(str3), RSTRING_PTR(str1), RSTRING_LEN(str1));
    memcpy(RSTRING_PTR(str3) + RSTRING_LEN(str1),
	   RSTRING_PTR(str2), RSTRING_LEN(str2));
    RSTRING_PTR(str3)[RSTRING_LEN(str3)] = '\0';

    if (OBJ_TAINTED(str1) || OBJ_TAINTED(str2))
	OBJ_TAINT(str3);
    rb_enc_associate(str3, enc);
    return str3;
}

/*
 *  call-seq:
 *     str * integer   => new_str
 *  
 *  Copy---Returns a new <code>String</code> containing <i>integer</i> copies of
 *  the receiver.
 *     
 *     "Ho! " * 3   #=> "Ho! Ho! Ho! "
 */

VALUE
rb_str_times(VALUE str, VALUE times)
{
    VALUE str2;
    long i, len;

    len = NUM2LONG(times);
    if (len < 0) {
	rb_raise(rb_eArgError, "negative argument");
    }
    if (len && LONG_MAX/len <  RSTRING_LEN(str)) {
	rb_raise(rb_eArgError, "argument too big");
    }

    str2 = rb_str_new5(str, 0, len *= RSTRING_LEN(str));
    for (i = 0; i < len; i += RSTRING_LEN(str)) {
	memcpy(RSTRING_PTR(str2) + i,
	       RSTRING_PTR(str), RSTRING_LEN(str));
    }
    RSTRING_PTR(str2)[RSTRING_LEN(str2)] = '\0';
    OBJ_INFECT(str2, str);
    rb_enc_copy(str2, str);

    return str2;
}

/*
 *  call-seq:
 *     str % arg   => new_str
 *  
 *  Format---Uses <i>str</i> as a format specification, and returns the result
 *  of applying it to <i>arg</i>. If the format specification contains more than
 *  one substitution, then <i>arg</i> must be an <code>Array</code> containing
 *  the values to be substituted. See <code>Kernel::sprintf</code> for details
 *  of the format string.
 *     
 *     "%05d" % 123                       #=> "00123"
 *     "%-5s: %08x" % [ "ID", self.id ]   #=> "ID   : 200e14d6"
 */

static VALUE
rb_str_format_m(VALUE str, VALUE arg)
{
    VALUE tmp = rb_check_array_type(arg);

    if (!NIL_P(tmp)) {
	return rb_str_format(RARRAY_LEN(tmp), RARRAY_PTR(tmp), str);
    }
    return rb_str_format(1, &arg, str);
}

static void
str_modifiable(VALUE str)
{
    if (FL_TEST(str, STR_TMPLOCK)) {
	rb_raise(rb_eRuntimeError, "can't modify string; temporarily locked");
    }
    if (OBJ_FROZEN(str)) rb_error_frozen("string");
    if (!OBJ_TAINTED(str) && rb_safe_level() >= 4)
	rb_raise(rb_eSecurityError, "Insecure: can't modify string");
}

static int
str_independent(VALUE str)
{
    str_modifiable(str);
    if (!STR_SHARED_P(str)) return 1;
    if (STR_EMBED_P(str)) return 1;
    return 0;
}

static void
str_make_independent(VALUE str)
{
    char *ptr;
    long len = RSTRING_LEN(str);

    ptr = ALLOC_N(char, len+1);
    if (RSTRING_PTR(str)) {
	memcpy(ptr, RSTRING_PTR(str), len);
    }
    STR_SET_NOEMBED(str);
    ptr[len] = 0;
    RSTRING(str)->as.heap.ptr = ptr;
    RSTRING(str)->as.heap.aux.capa = len;
    STR_UNSET_NOCAPA(str);
}

void
rb_str_modify(VALUE str)
{
    if (!str_independent(str))
	str_make_independent(str);
    ENC_CODERANGE_CLEAR(str);
}

void
rb_str_associate(VALUE str, VALUE add)
{
    if (STR_ASSOC_P(str)) {
	/* sanity check */
	if (OBJ_FROZEN(str)) rb_error_frozen("string");
	/* already associated */
	rb_ary_concat(RSTRING(str)->as.heap.aux.shared, add);
    }
    else {
	if (STR_SHARED_P(str) || STR_EMBED_P(str)) {
	    str_make_independent(str);
	}
	else if (RSTRING(str)->as.heap.aux.capa != RSTRING_LEN(str)) {
	    RESIZE_CAPA(str, RSTRING_LEN(str));
	}
	FL_SET(str, STR_ASSOC);
	RSTRING(str)->as.heap.aux.shared = add;
    }
}

VALUE
rb_str_associated(VALUE str)
{
    if (STR_ASSOC_P(str)) {
	if (OBJ_FROZEN(str)) return Qfalse;
	return RSTRING(str)->as.heap.aux.shared;
    }
    return Qfalse;
}

VALUE
rb_string_value(volatile VALUE *ptr)
{
    VALUE s = *ptr;
    if (TYPE(s) != T_STRING) {
	s = rb_str_to_str(s);
	*ptr = s;
    }
    return s;
}

char *
rb_string_value_ptr(volatile VALUE *ptr)
{
    return RSTRING_PTR(rb_string_value(ptr));
}

char *
rb_string_value_cstr(volatile VALUE *ptr)
{
    VALUE str = rb_string_value(ptr);
    char *s = RSTRING_PTR(str);

    if (!s || RSTRING_LEN(str) != strlen(s)) {
	rb_raise(rb_eArgError, "string contains null byte");
    }
    return s;
}

VALUE
rb_check_string_type(VALUE str)
{
    str = rb_check_convert_type(str, T_STRING, "String", "to_str");
    return str;
}

/*
 *  call-seq:
 *     String.try_convert(obj) -> string or nil
 *
 *  Try to convert <i>obj</i> into a String, using to_str method.
 *  Returns converted regexp or nil if <i>obj</i> cannot be converted
 *  for any reason.
 *
 *     String.try_convert("str")     # => str
 *     String.try_convert(/re/)      # => nil
 */
static VALUE
rb_str_s_try_convert(VALUE dummy, VALUE str)
{
    return rb_check_string_type(str);
}

static char*
str_nth(char *p, char *e, int nth, rb_encoding *enc, int asc)
{
    if (asc)
	p += nth;
    else
	p = rb_enc_nth(p, e, nth, enc);
    if (!p) return 0;
    if (p > e) return e;
    return p;
}

static int
str_offset(char *p, char *e, int nth, rb_encoding *enc, int asc)
{
    const char *pp = str_nth(p, e, nth, enc, asc);
    if (!pp) return e - p;
    return pp - p;
}

static long
str_sublen(VALUE str, long pos, rb_encoding *enc)
{
    if (rb_enc_mbmaxlen(enc) == 1 || pos < 0) return pos;
    else {
	char *p = RSTRING_PTR(str);
	char *e = p + pos;
	long i;

	i = 0;
	while (p < e) {
	    p += rb_enc_mbclen(p, RSTRING_END(str), enc);
	    i++;
	}
	if (p == e) return i;
	return i - 1;
    }
}

int
rb_str_sublen(VALUE str, int len)
{
    return str_sublen(str, len, rb_enc_get(str));
}

VALUE
rb_str_subseq(VALUE str, long beg, long len)
{
    VALUE str2 = rb_str_new5(str, RSTRING_PTR(str)+beg, len);

    rb_enc_copy(str2, str);
    OBJ_INFECT(str2, str);

    return str2;
}

VALUE
rb_str_substr(VALUE str, long beg, long len)
{
    rb_encoding *enc = rb_enc_get(str);
    VALUE str2;
    char *p, *s = RSTRING_PTR(str), *e = s + RSTRING_LEN(str);
    int asc = IS_7BIT(str);

    if (len < 0) return Qnil;
    if (!RSTRING_LEN(str)) {
	len = 0;
    }
    if (beg < 0) {
	if (len > -beg) len = -beg;
	if (-beg * rb_enc_mbmaxlen(enc) < RSTRING_LEN(str) / 8) {
	    beg = -beg;
	    while (len++ < beg && (e = rb_enc_prev_char(s, e, enc)) != 0);
	    p = e;
	    if (!p) return Qnil;
	    while (beg-- > 0 && (p = rb_enc_prev_char(s, p, enc)) != 0);
	    if (!p) return Qnil;
	    len = e - p;
	    goto sub;
	}
	else {
	    beg += str_strlen(str, enc);
	    if (beg < 0) return Qnil;
	}
    }
    else if (beg > 0 && beg > str_strlen(str, enc)) {
	return Qnil;
    }
    if (len == 0) {
	p = 0;
    }
    else if ((p = str_nth(s, e, beg, enc, asc)) == e) {
	len = 0;
    }
    else if (rb_enc_mbmaxlen(enc) == rb_enc_mbminlen(enc)) {
	long rest = (e - p) / rb_enc_mbmaxlen(enc);
	if (len > rest)
	    len = rest;
	else
	    len *= rb_enc_mbmaxlen(enc);
    }
    else {
	len = str_offset(p, e, len, enc, asc);
    }
  sub:
    str2 = rb_str_new5(str, p, len);
    rb_enc_copy(str2, str);
    OBJ_INFECT(str2, str);

    return str2;
}

VALUE
rb_str_freeze(VALUE str)
{
    return rb_obj_freeze(str);
}

VALUE
rb_str_dup_frozen(VALUE str)
{
    if (STR_SHARED_P(str) && RSTRING(str)->as.heap.aux.shared) {
	VALUE shared = RSTRING(str)->as.heap.aux.shared;
	if (RSTRING_LEN(shared) == RSTRING_LEN(str)) {
	    OBJ_FREEZE(shared);
	    return shared;
	}
    }
    if (OBJ_FROZEN(str)) return str;
    str = rb_str_dup(str);
    OBJ_FREEZE(str);
    return str;
}

VALUE
rb_str_locktmp(VALUE str)
{
    if (FL_TEST(str, STR_TMPLOCK)) {
	rb_raise(rb_eRuntimeError, "temporal locking already locked string");
    }
    FL_SET(str, STR_TMPLOCK);
    return str;
}

VALUE
rb_str_unlocktmp(VALUE str)
{
    if (!FL_TEST(str, STR_TMPLOCK)) {
	rb_raise(rb_eRuntimeError, "temporal unlocking already unlocked string");
    }
    FL_UNSET(str, STR_TMPLOCK);
    return str;
}

void
rb_str_set_len(VALUE str, long len)
{
    STR_SET_LEN(str, len);
    RSTRING_PTR(str)[len] = '\0';
}

VALUE
rb_str_resize(VALUE str, long len)
{
    if (len < 0) {
	rb_raise(rb_eArgError, "negative string size (or size too big)");
    }

    rb_str_modify(str);
    if (len != RSTRING_LEN(str)) {
	if (STR_EMBED_P(str)) {
	    char *ptr;
	    if (len <= RSTRING_EMBED_LEN_MAX) {
		STR_SET_EMBED_LEN(str, len);
		RSTRING_PTR(str)[len] = '\0';
		return str;
	    }
	    ptr = ALLOC_N(char,len+1);
	    MEMCPY(ptr, RSTRING_PTR(str), char, RSTRING_LEN(str));
	    RSTRING(str)->as.heap.ptr = ptr;
	    STR_SET_NOEMBED(str);
	}
	else if (RSTRING_LEN(str) < len || RSTRING_LEN(str) - len > 1024) {
	    REALLOC_N(RSTRING(str)->as.heap.ptr, char, len+1);
	}
	if (!STR_NOCAPA_P(str)) {
	    RSTRING(str)->as.heap.aux.capa = len;
	}
	RSTRING(str)->as.heap.len = len;
	RSTRING(str)->as.heap.ptr[len] = '\0';	/* sentinel */
    }
    return str;
}

VALUE
rb_str_buf_cat(VALUE str, const char *ptr, long len)
{
    long capa, total;

    if (len == 0) return str;
    if (len < 0) {
	rb_raise(rb_eArgError, "negative string size (or size too big)");
    }
    rb_str_modify(str);
    if (STR_ASSOC_P(str)) {
	FL_UNSET(str, STR_ASSOC);
	capa = RSTRING(str)->as.heap.aux.capa = RSTRING_LEN(str);
    }
    else if (STR_EMBED_P(str)) {
	capa = RSTRING_EMBED_LEN_MAX;
    }
    else {
	capa = RSTRING(str)->as.heap.aux.capa;
    }
    total = RSTRING_LEN(str)+len;
    if (capa <= total) {
	while (total > capa) {
	    capa = (capa + 1) * 2;
	}
	RESIZE_CAPA(str, capa);
    }
    memcpy(RSTRING_PTR(str) + RSTRING_LEN(str), ptr, len);
    STR_SET_LEN(str, total);
    RSTRING_PTR(str)[total] = '\0'; /* sentinel */

    return str;
}

VALUE
rb_str_buf_cat2(VALUE str, const char *ptr)
{
    return rb_str_buf_cat(str, ptr, strlen(ptr));
}

VALUE
rb_str_cat(VALUE str, const char *ptr, long len)
{
    if (len < 0) {
	rb_raise(rb_eArgError, "negative string size (or size too big)");
    }
    if (STR_ASSOC_P(str)) {
	rb_str_modify(str);
	if (STR_EMBED_P(str)) str_make_independent(str);
	REALLOC_N(RSTRING(str)->as.heap.ptr, char, RSTRING(str)->as.heap.len+len);
	memcpy(RSTRING(str)->as.heap.ptr + RSTRING(str)->as.heap.len, ptr, len);
	RSTRING(str)->as.heap.len += len;
	RSTRING(str)->as.heap.ptr[RSTRING(str)->as.heap.len] = '\0'; /* sentinel */
	return str;
    }

    return rb_str_buf_cat(str, ptr, len);
}

VALUE
rb_str_cat2(VALUE str, const char *ptr)
{
    return rb_str_cat(str, ptr, strlen(ptr));
}

VALUE
rb_str_buf_append(VALUE str, VALUE str2)
{
    rb_encoding *enc;
    long capa, len;
    int cr1, cr2;

    enc = rb_enc_check(str, str2);
    cr1 = ENC_CODERANGE(str);
    cr2 = ENC_CODERANGE(str2);
    if (cr1 == ENC_CODERANGE_BROKEN || cr2 == ENC_CODERANGE_BROKEN) {
	cr1 = ENC_CODERANGE_UNKNOWN;
    }
    else if (cr2 > cr1) {
	cr1 = cr2;
    }
    rb_str_modify(str);
    if (STR_ASSOC_P(str)) {
	FL_UNSET(str, STR_ASSOC);
	capa = RSTRING(str)->as.heap.aux.capa = RSTRING_LEN(str);
    }
    else if (STR_EMBED_P(str)) {
	capa = RSTRING_EMBED_LEN_MAX;
    }
    else {
	capa = RSTRING(str)->as.heap.aux.capa;
    }
    len = RSTRING_LEN(str)+RSTRING_LEN(str2);
    if (capa <= len) {
	while (len > capa) {
	    capa = (capa + 1) * 2;
	}
	RESIZE_CAPA(str, capa);
    }
    memcpy(RSTRING_PTR(str) + RSTRING_LEN(str),
	   RSTRING_PTR(str2), RSTRING_LEN(str2)+1);
    STR_SET_LEN(str, len);
    OBJ_INFECT(str, str2);
    rb_enc_associate(str, enc);
    if (cr1 != ENC_CODERANGE_UNKNOWN) {
	ENC_CODERANGE_SET(str, cr1);
    }

    return str;
}

VALUE
rb_str_append(VALUE str, VALUE str2)
{
    rb_encoding *enc;
    int cr, cr2;

    StringValue(str2);
    enc = rb_enc_check(str, str2);
    cr = ENC_CODERANGE(str);
    if ((cr2 = ENC_CODERANGE(str2)) > cr) cr = cr2;
    rb_str_modify(str);
    if (RSTRING_LEN(str2) > 0) {
	if (STR_ASSOC_P(str)) {
	    long len = RSTRING_LEN(str)+RSTRING_LEN(str2);
	    REALLOC_N(RSTRING(str)->as.heap.ptr, char, len+1);
	    memcpy(RSTRING(str)->as.heap.ptr + RSTRING(str)->as.heap.len,
		   RSTRING_PTR(str2), RSTRING_LEN(str2)+1);
	    RSTRING(str)->as.heap.len = len;
	}
	else {
	    rb_str_buf_append(str, str2);
	}
    }
    OBJ_INFECT(str, str2);
    rb_enc_associate(str, enc);
    ENC_CODERANGE_SET(str, cr);
    return str;
}


/*
 *  call-seq:
 *     str << fixnum        => str
 *     str.concat(fixnum)   => str
 *     str << obj           => str
 *     str.concat(obj)      => str
 *  
 *  Append---Concatenates the given object to <i>str</i>. If the object is a
 *  <code>Fixnum</code>, it is considered as a codepoint, and is converted
 *  to a character before concatenation.
 *     
 *     a = "hello "
 *     a << "world"   #=> "hello world"
 *     a.concat(33)   #=> "hello world!"
 */

VALUE
rb_str_concat(VALUE str1, VALUE str2)
{
    if (FIXNUM_P(str2)) {
	rb_encoding *enc = rb_enc_get(str1);
	int c = FIX2INT(str2);
	int pos = RSTRING_LEN(str1);
	int len = rb_enc_codelen(c, enc);

	if (len == 0) {
	    rb_raise(rb_eArgError, "invalid codepoint 0x%x", c);
	}
	rb_str_resize(str1, pos+len);
	rb_enc_mbcput(c, RSTRING_PTR(str1)+pos, enc);
	return str1;
    }
    return rb_str_append(str1, str2);
}

typedef  unsigned int  ub4;   /* unsigned 4-byte quantities */
typedef  unsigned char ub1;   /* unsigned 1-byte quantities */

#define hashsize(n) ((ub4)1<<(n))
#define hashmask(n) (hashsize(n)-1)

/*
--------------------------------------------------------------------
mix -- mix 3 32-bit values reversibly.
For every delta with one or two bits set, and the deltas of all three
  high bits or all three low bits, whether the original value of a,b,c
  is almost all zero or is uniformly distributed,
* If mix() is run forward or backward, at least 32 bits in a,b,c
  have at least 1/4 probability of changing.
* If mix() is run forward, every bit of c will change between 1/3 and
  2/3 of the time.  (Well, 22/100 and 78/100 for some 2-bit deltas.)
mix() was built out of 36 single-cycle latency instructions in a 
  structure that could supported 2x parallelism, like so:
      a -= b; 
      a -= c; x = (c>>13);
      b -= c; a ^= x;
      b -= a; x = (a<<8);
      c -= a; b ^= x;
      c -= b; x = (b>>13);
      ...
  Unfortunately, superscalar Pentiums and Sparcs can't take advantage 
  of that parallelism.  They've also turned some of those single-cycle
  latency instructions into multi-cycle latency instructions.  Still,
  this is the fastest good hash I could find.  There were about 2^^68
  to choose from.  I only looked at a billion or so.
--------------------------------------------------------------------
*/
#define mix(a,b,c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8); \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12);  \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

/*
--------------------------------------------------------------------
hash() -- hash a variable-length key into a 32-bit value
  k       : the key (the unaligned variable-length array of bytes)
  len     : the length of the key, counting by bytes
  initval : can be any 4-byte value
Returns a 32-bit value.  Every bit of the key affects every bit of
the return value.  Every 1-bit and 2-bit delta achieves avalanche.
About 6*len+35 instructions.

The best hash table sizes are powers of 2.  There is no need to do
mod a prime (mod is sooo slow!).  If you need less than 32 bits,
use a bitmask.  For example, if you need only 10 bits, do
  h = (h & hashmask(10));
In which case, the hash table should have hashsize(10) elements.

If you are hashing n strings (ub1 **)k, do it like this:
  for (i=0, h=0; i<n; ++i) h = hash( k[i], len[i], h);

By Bob Jenkins, 1996.  bob_jenkins@burtleburtle.net.  You may use this
code any way you wish, private, educational, or commercial.  It's free.

See http://burtleburtle.net/bob/hash/evahash.html
Use for hash table lookup, or anything where one collision in 2^^32 is
acceptable.  Do NOT use for cryptographic purposes.
--------------------------------------------------------------------
*/

static ub4
hash(const ub1 *k, ub4 length, ub4 initval)
    /* k: the key */
    /* length: the length of the key */
    /* initval: the previous hash, or an arbitrary value */
{
    register ub4 a,b,c,len;

    /* Set up the internal state */
    len = length;
    a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
    c = initval;         /* the previous hash value */

   /*---------------------------------------- handle most of the key */
    while (len >= 12) {
	a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
	b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
	c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
	mix(a,b,c);
	k += 12; len -= 12;
    }

    /*------------------------------------- handle the last 11 bytes */
    c += length;
    switch(len)              /* all the case statements fall through */
    {
      case 11: c+=((ub4)k[10]<<24);
      case 10: c+=((ub4)k[9]<<16);
      case 9 : c+=((ub4)k[8]<<8);
	/* the first byte of c is reserved for the length */
      case 8 : b+=((ub4)k[7]<<24);
      case 7 : b+=((ub4)k[6]<<16);
      case 6 : b+=((ub4)k[5]<<8);
      case 5 : b+=k[4];
      case 4 : a+=((ub4)k[3]<<24);
      case 3 : a+=((ub4)k[2]<<16);
      case 2 : a+=((ub4)k[1]<<8);
      case 1 : a+=k[0];
	/* case 0: nothing left to add */
    }
    mix(a,b,c);
    /*-------------------------------------------- report the result */
    return c;
}

int
rb_memhash(const void *ptr, long len)
{
    return hash(ptr, len, 0);
}

int
rb_str_hash(VALUE str)
{
    int e = rb_enc_get_index(str);
    if (e && is_ascii_string(str)) {
	e = 0;
    }
    return hash((const void *)RSTRING_PTR(str), RSTRING_LEN(str), e);
}

/*
 * call-seq:
 *    str.hash   => fixnum
 *
 * Return a hash based on the string's length and content.
 */

static VALUE
rb_str_hash_m(VALUE str)
{
    int hval = rb_str_hash(str);
    return INT2FIX(hval);
}

#define lesser(a,b) (((a)>(b))?(b):(a))

int
rb_str_comparable(VALUE str1, VALUE str2)
{
    int idx1 = rb_enc_get_index(str1);
    int idx2 = rb_enc_get_index(str2);
    int rc1, rc2;

    if (idx1 == idx2) return Qtrue;
    rc1 = rb_enc_str_coderange(str1);
    rc2 = rb_enc_str_coderange(str2);
    if (rc1 == ENC_CODERANGE_7BIT) {
	if (rc2 == ENC_CODERANGE_7BIT) return Qtrue;
	if (rb_enc_asciicompat(rb_enc_from_index(idx1)))
	    return Qtrue;
    }
    if (rc2 == ENC_CODERANGE_7BIT) {
	if (rb_enc_asciicompat(rb_enc_from_index(idx2)))
	    return Qtrue;
    }
    return Qfalse;
}

int
rb_str_cmp(VALUE str1, VALUE str2)
{
    long len;
    int retval;
    rb_encoding *enc;

    enc = rb_enc_compatible(str1, str2);
    len = lesser(RSTRING_LEN(str1), RSTRING_LEN(str2));
    retval = memcmp(RSTRING_PTR(str1), RSTRING_PTR(str2), len);
    if (retval == 0) {
	if (RSTRING_LEN(str1) == RSTRING_LEN(str2)) {
	    if (!enc) {
		if (rb_enc_get(str1) - rb_enc_get(str2) > 0)
		    return 1;
		return -1;
	    }
	    return 0;
	}
	if (RSTRING_LEN(str1) > RSTRING_LEN(str2)) return 1;
	return -1;
    }
    if (retval > 0) return 1;
    return -1;
}


/*
 *  call-seq:
 *     str == obj   => true or false
 *  
 *  Equality---If <i>obj</i> is not a <code>String</code>, returns
 *  <code>false</code>. Otherwise, returns <code>true</code> if <i>str</i>
 *  <code><=></code> <i>obj</i> returns zero.
 */

VALUE
rb_str_equal(VALUE str1, VALUE str2)
{
    if (str1 == str2) return Qtrue;
    if (TYPE(str2) != T_STRING) {
	if (!rb_respond_to(str2, rb_intern("to_str"))) {
	    return Qfalse;
	}
	return rb_equal(str2, str1);
    }
    if (!rb_str_comparable(str1, str2)) return Qfalse;
    if (RSTRING_LEN(str1) == RSTRING_LEN(str2) &&
	rb_str_cmp(str1, str2) == 0) {
	return Qtrue;
    }
    return Qfalse;
}

/*
 * call-seq:
 *   str.eql?(other)   => true or false
 *
 * Two strings are equal if the have the same length and content.
 */

static VALUE
rb_str_eql(VALUE str1, VALUE str2)
{
    if (TYPE(str2) != T_STRING || RSTRING_LEN(str1) != RSTRING_LEN(str2))
	return Qfalse;

    if (!rb_str_comparable(str1, str2)) return Qfalse;
    if (memcmp(RSTRING_PTR(str1), RSTRING_PTR(str2),
	       lesser(RSTRING_LEN(str1), RSTRING_LEN(str2))) == 0)
	return Qtrue;

    return Qfalse;
}

/*
 *  call-seq:
 *     str <=> other_str   => -1, 0, +1
 *  
 *  Comparison---Returns -1 if <i>other_str</i> is less than, 0 if
 *  <i>other_str</i> is equal to, and +1 if <i>other_str</i> is greater than
 *  <i>str</i>. If the strings are of different lengths, and the strings are
 *  equal when compared up to the shortest length, then the longer string is
 *  considered greater than the shorter one. In older versions of Ruby, setting
 *  <code>$=</code> allowed case-insensitive comparisons; this is now deprecated
 *  in favor of using <code>String#casecmp</code>.
 *
 *  <code><=></code> is the basis for the methods <code><</code>,
 *  <code><=</code>, <code>></code>, <code>>=</code>, and <code>between?</code>,
 *  included from module <code>Comparable</code>.  The method
 *  <code>String#==</code> does not use <code>Comparable#==</code>.
 *     
 *     "abcdef" <=> "abcde"     #=> 1
 *     "abcdef" <=> "abcdef"    #=> 0
 *     "abcdef" <=> "abcdefg"   #=> -1
 *     "abcdef" <=> "ABCDEF"    #=> 1
 */

static VALUE
rb_str_cmp_m(VALUE str1, VALUE str2)
{
    long result;

    if (TYPE(str2) != T_STRING) {
	if (!rb_respond_to(str2, rb_intern("to_str"))) {
	    return Qnil;
	}
	else if (!rb_respond_to(str2, rb_intern("<=>"))) {
	    return Qnil;
	}
	else {
	    VALUE tmp = rb_funcall(str2, rb_intern("<=>"), 1, str1);

	    if (NIL_P(tmp)) return Qnil;
	    if (!FIXNUM_P(tmp)) {
		return rb_funcall(LONG2FIX(0), '-', 1, tmp);
	    }
	    result = -FIX2LONG(tmp);
	}
    }
    else {
	result = rb_str_cmp(str1, str2);
    }
    return LONG2NUM(result);
}

/*
 *  call-seq:
 *     str.casecmp(other_str)   => -1, 0, +1
 *  
 *  Case-insensitive version of <code>String#<=></code>.
 *     
 *     "abcdef".casecmp("abcde")     #=> 1
 *     "aBcDeF".casecmp("abcdef")    #=> 0
 *     "abcdef".casecmp("abcdefg")   #=> -1
 *     "abcdef".casecmp("ABCDEF")    #=> 0
 */

static VALUE
rb_str_casecmp(VALUE str1, VALUE str2)
{
    long len;
    rb_encoding *enc;
    char *p1, *p1end, *p2, *p2end;

    StringValue(str2);
    enc = rb_enc_compatible(str1, str2);
    if (!enc) {
	return rb_str_cmp(str1, str2);
    }

    p1 = RSTRING_PTR(str1); p1end = RSTRING_END(p1);
    p2 = RSTRING_PTR(str2); p2end = RSTRING_END(str2);
    while (p1 < p1end && p2 < p2end) {
	int c1 = rb_enc_codepoint(p1, p1end, enc);
	int c2 = rb_enc_codepoint(p2, p2end, enc);

	if (c1 != c2) {
	    c1 = rb_enc_toupper(c1, enc);
	    c2 = rb_enc_toupper(c2, enc);
	    if (c1 > c2) return INT2FIX(1);
	    if (c1 < c2) return INT2FIX(-1);
	}
	len = rb_enc_codelen(c1, enc);
	p1 += len;
	p2 += len;
    }
    if (RSTRING_LEN(str1) == RSTRING_LEN(str2)) return INT2FIX(0);
    if (RSTRING_LEN(str1) > RSTRING_LEN(str2)) return INT2FIX(1);
    return INT2FIX(-1);
}

static long
rb_str_index(VALUE str, VALUE sub, long offset)
{
    long pos;
    char *s, *sptr;
    long len, slen;
    rb_encoding *enc;

    enc = rb_enc_check(str, sub);
    if (is_broken_string(sub)) {
	return -1;
    }
    len = str_strlen(str, enc);
    slen = str_strlen(sub, enc);
    if (offset < 0) {
	offset += len;
	if (offset < 0) return -1;
    }
    if (len - offset < slen) return -1;
    s = RSTRING_PTR(str);
    if (offset) {
	offset = str_offset(s, RSTRING_END(str), offset, enc, IS_7BIT(str));
	s += offset;
    }
    if (slen == 0) return offset;
    /* need proceed one character at a time */
    sptr = RSTRING_PTR(sub);
    slen = RSTRING_LEN(sub);
    len = RSTRING_LEN(str) - offset;
    for (;;) {
	char *t;
	pos = rb_memsearch(sptr, slen, s, len);
	if (pos < 0) return pos;
	t = rb_enc_right_char_head(s, s+pos, enc);
	if (t == s) break;
	if ((len -= t - s) <= 0) return -1;
	offset += t - s;
	s = t;
    }
    return pos + offset;
}


/*
 *  call-seq:
 *     str.index(substring [, offset])   => fixnum or nil
 *     str.index(fixnum [, offset])      => fixnum or nil
 *     str.index(regexp [, offset])      => fixnum or nil
 *  
 *  Returns the index of the first occurrence of the given <i>substring</i>,
 *  character (<i>fixnum</i>), or pattern (<i>regexp</i>) in <i>str</i>. Returns
 *  <code>nil</code> if not found. If the second parameter is present, it
 *  specifies the position in the string to begin the search.
 *     
 *     "hello".index('e')             #=> 1
 *     "hello".index('lo')            #=> 3
 *     "hello".index('a')             #=> nil
 *     "hello".index(101)             #=> 1
 *     "hello".index(/[aeiou]/, -3)   #=> 4
 */

static VALUE
rb_str_index_m(int argc, VALUE *argv, VALUE str)
{
    VALUE sub;
    VALUE initpos;
    long pos;

    if (rb_scan_args(argc, argv, "11", &sub, &initpos) == 2) {
	pos = NUM2LONG(initpos);
    }
    else {
	pos = 0;
    }
    if (pos < 0) {
	pos += str_strlen(str, rb_enc_get(str));
	if (pos < 0) {
	    if (TYPE(sub) == T_REGEXP) {
		rb_backref_set(Qnil);
	    }
	    return Qnil;
	}
    }

    switch (TYPE(sub)) {
      case T_REGEXP:
	pos = rb_reg_adjust_startpos(sub, str, pos, 0);
	pos = rb_reg_search(sub, str, pos, 0);
	pos = rb_str_sublen(str, pos);
	break;

      default: {
	VALUE tmp;

	tmp = rb_check_string_type(sub);
	if (NIL_P(tmp)) {
	    rb_raise(rb_eTypeError, "type mismatch: %s given",
		     rb_obj_classname(sub));
	}
	sub = tmp;
      }
	/* fall through */
      case T_STRING:
	pos = rb_str_index(str, sub, pos);
	pos = rb_str_sublen(str, pos);
	break;
    }

    if (pos == -1) return Qnil;
    return LONG2NUM(pos);
}

static long
rb_str_rindex(VALUE str, VALUE sub, long pos)
{
    long len, slen;
    char *s, *sbeg, *e, *t;
    rb_encoding *enc;
    int asc = IS_7BIT(str);

    enc = rb_enc_check(str, sub);
    if (is_broken_string(sub)) {
	return -1;
    }
    len = str_strlen(str, enc);
    slen = str_strlen(sub, enc);
    /* substring longer than string */
    if (len < slen) return -1;
    if (len - pos < slen) {
	pos = len - slen;
    }
    if (len == 0) {
	return pos;
    }
    sbeg = RSTRING_PTR(str);
    e = RSTRING_END(str);
    t = RSTRING_PTR(sub);
    slen = RSTRING_LEN(sub);
    for (;;) {
	s = str_nth(sbeg, e, pos, enc, asc);
	if (!s) return -1;
	if (memcmp(s, t, slen) == 0) {
	    return pos;
	}
	if (pos == 0) break;
	pos--;
    }
    return -1;
}


/*
 *  call-seq:
 *     str.rindex(substring [, fixnum])   => fixnum or nil
 *     str.rindex(fixnum [, fixnum])   => fixnum or nil
 *     str.rindex(regexp [, fixnum])   => fixnum or nil
 *  
 *  Returns the index of the last occurrence of the given <i>substring</i>,
 *  character (<i>fixnum</i>), or pattern (<i>regexp</i>) in <i>str</i>. Returns
 *  <code>nil</code> if not found. If the second parameter is present, it
 *  specifies the position in the string to end the search---characters beyond
 *  this point will not be considered.
 *     
 *     "hello".rindex('e')             #=> 1
 *     "hello".rindex('l')             #=> 3
 *     "hello".rindex('a')             #=> nil
 *     "hello".rindex(101)             #=> 1
 *     "hello".rindex(/[aeiou]/, -2)   #=> 1
 */

static VALUE
rb_str_rindex_m(int argc, VALUE *argv, VALUE str)
{
    VALUE sub;
    VALUE vpos;
    rb_encoding *enc = rb_enc_get(str);
    long pos, len = str_strlen(str, enc);

    if (rb_scan_args(argc, argv, "11", &sub, &vpos) == 2) {
	pos = NUM2LONG(vpos);
	if (pos < 0) {
	    pos += len;
	    if (pos < 0) {
		if (TYPE(sub) == T_REGEXP) {
		    rb_backref_set(Qnil);
		}
		return Qnil;
	    }
	}
	if (pos > len) pos = len;
    }
    else {
	pos = len;
    }

    switch (TYPE(sub)) {
      case T_REGEXP:
	/* enc = rb_get_check(str, sub); */
	if (RREGEXP(sub)->len) {
	    pos = rb_reg_adjust_startpos(sub, str, pos, 1);
	    pos = rb_reg_search(sub, str, pos, 1);
	    pos = rb_str_sublen(str, pos);
	}
	if (pos >= 0) return LONG2NUM(pos);
	break;

      default: {
	VALUE tmp;

	tmp = rb_check_string_type(sub);
	if (NIL_P(tmp)) {
	    rb_raise(rb_eTypeError, "type mismatch: %s given",
		     rb_obj_classname(sub));
	}
	sub = tmp;
      }
	/* fall through */
      case T_STRING:
	pos = rb_str_rindex(str, sub, pos);
	if (pos >= 0) return LONG2NUM(pos);
	break;
    }
    return Qnil;
}

/*
 *  call-seq:
 *     str =~ obj   => fixnum or nil
 *  
 *  Match---If <i>obj</i> is a <code>Regexp</code>, use it as a pattern to match
 *  against <i>str</i>,and returns the position the match starts, or 
 *  <code>nil</code> if there is no match. Otherwise, invokes
 *  <i>obj.=~</i>, passing <i>str</i> as an argument. The default
 *  <code>=~</code> in <code>Object</code> returns <code>false</code>.
 *     
 *     "cat o' 9 tails" =~ /\d/   #=> 7
 *     "cat o' 9 tails" =~ 9      #=> false
 */

static VALUE
rb_str_match(VALUE x, VALUE y)
{
    switch (TYPE(y)) {
      case T_STRING:
	rb_raise(rb_eTypeError, "type mismatch: String given");

      case T_REGEXP:
	return rb_reg_match(y, x);

      default:
	return rb_funcall(y, rb_intern("=~"), 1, x);
    }
}


static VALUE get_pat(VALUE, int);


/*
 *  call-seq:
 *     str.match(pattern)   => matchdata or nil
 *  
 *  Converts <i>pattern</i> to a <code>Regexp</code> (if it isn't already one),
 *  then invokes its <code>match</code> method on <i>str</i>.  If the second
 *  parameter is present, it specifies the position in the string to begin the
 *  search.
 *     
 *     'hello'.match('(.)\1')      #=> #<MatchData "ll" "l">
 *     'hello'.match('(.)\1')[0]   #=> "ll"
 *     'hello'.match(/(.)\1/)[0]   #=> "ll"
 *     'hello'.match('xx')         #=> nil
 *     
 *  If a block is given, invoke the block with MatchData if match succeed, so
 *  that you can write
 *     
 *     str.match(pat) {|m| ...}
 *     
 *  instead of
 *      
 *     if m = str.match(pat)
 *       ...
 *     end
 *      
 *  The retuen value is a value from block exection in this case.
 */

static VALUE
rb_str_match_m(int argc, VALUE *argv, VALUE str)
{
    VALUE re, result;
    if (argc < 1)
	rb_raise(rb_eArgError, "wrong number of arguments (%d for 1)", argc);
    re = argv[0];
    argv[0] = str;
    result = rb_funcall2(get_pat(re, 0), rb_intern("match"), argc, argv);
    if (!NIL_P(result) && rb_block_given_p()) {
	return rb_yield(result);
    }
    return result;
}

static int
succ_char(char *s)
{
    char c = *s;

    /* numerics */
    if ('0' <= c && c < '9') (*s)++;
    else if (c == '9') {
	*s = '0';
	return '1';
    }
    /* small alphabets */
    else if ('a' <= c && c < 'z') (*s)++;
    else if (c == 'z') {
	return *s = 'a';
    }
    /* capital alphabets */
    else if ('A' <= c && c < 'Z') (*s)++;
    else if (c == 'Z') {
	return *s = 'A';
    }
    return 0;
}

/*
  overwrite +s+ by succeeding letter of +c+ in +enc+ and returns
  carried-out letter.  assuming each ranges are successive, and mbclen
  never change in each ranges.
 */
static int
enc_succ_char(unsigned int c, char *s, rb_encoding *enc)
{
    unsigned int cs;

    /* numerics */
    if (rb_enc_isdigit(c, enc)) {
	cs = c++;
	if (rb_enc_isdigit(c, enc)) {
	    rb_enc_mbcput(c, s, enc);
	    return 0;
	}
	do c = cs--; while (rb_enc_isdigit(cs, enc));
	rb_enc_mbcput(c, s, enc);
	return ++c;
    }
    /* small alphabets */
    if (rb_enc_islower(c, enc)) {
	cs = c++;
	if (rb_enc_islower(c, enc)) {
	    rb_enc_mbcput(c, s, enc);
	    return 0;
	}
	do c = cs--; while (rb_enc_islower(cs, enc));
	rb_enc_mbcput(c, s, enc);
	return c;
    }
    /* capital alphabets */
    if (rb_enc_isupper(c, enc)) {
	cs = c++;
	if (rb_enc_isupper(c, enc)) {
	    rb_enc_mbcput(c, s, enc);
	    return 0;
	}
	do c = cs--; while (rb_enc_isupper(cs, enc));
	rb_enc_mbcput(c, s, enc);
	return c;
    }
    return -1;
}


/*
 *  call-seq:
 *     str.succ   => new_str
 *     str.next   => new_str
 *  
 *  Returns the successor to <i>str</i>. The successor is calculated by
 *  incrementing characters starting from the rightmost alphanumeric (or
 *  the rightmost character if there are no alphanumerics) in the
 *  string. Incrementing a digit always results in another digit, and
 *  incrementing a letter results in another letter of the same case.
 *  Incrementing nonalphanumerics uses the underlying character set's
 *  collating sequence.
 *     
 *  If the increment generates a ``carry,'' the character to the left of
 *  it is incremented. This process repeats until there is no carry,
 *  adding an additional character if necessary.
 *     
 *     "abcd".succ        #=> "abce"
 *     "THX1138".succ     #=> "THX1139"
 *     "<<koala>>".succ   #=> "<<koalb>>"
 *     "1999zzz".succ     #=> "2000aaa"
 *     "ZZZ9999".succ     #=> "AAAA0000"
 *     "***".succ         #=> "**+"
 */

VALUE
rb_str_succ(VALUE orig)
{
    rb_encoding *enc;
    VALUE str;
    char *sbeg, *s, *e;
    int c = -1;
    unsigned int cc = 0;
    long n = 0, o = 0, l;
    char carry[ONIGENC_CODE_TO_MBC_MAXLEN];

    str = rb_str_new5(orig, RSTRING_PTR(orig), RSTRING_LEN(orig));
    rb_enc_copy(str, orig);
    OBJ_INFECT(str, orig);
    if (RSTRING_LEN(str) == 0) return str;

    enc = rb_enc_get(orig);
    sbeg = RSTRING_PTR(str);
    s = e = sbeg + RSTRING_LEN(str);

    while ((s = rb_enc_prev_char(sbeg, s, enc)) != 0) {
	if ((l = rb_enc_precise_mbclen(s, e, enc)) <= 0) continue;
	cc = rb_enc_mbc_to_codepoint(s, e, enc);
	if (rb_enc_isalnum(cc, enc)) {
	    if (rb_enc_isascii(cc, enc)) {
		if ((c = succ_char(s)) == 0) break;
	    }
	    else {
		if ((c = enc_succ_char(cc, s, enc)) == 0) break;
	    }
	    n = s - sbeg;
	}
    }
    if (c == -1) {		/* str contains no alnum */
	c = '\001';
	s = e;
	while ((s = rb_enc_prev_char(sbeg, s, enc)) != 0) {
	    int limit = 256;
	    if ((l = rb_enc_precise_mbclen(s, e, enc)) <= 0) continue;
	    cc = rb_enc_mbc_to_codepoint(s, e, enc);
	    while ((l = rb_enc_mbcput(++cc, carry, enc)) < 0 && --limit);
	    if (l > 0) {
		if (l == (o = e - s)) goto overlay;
		n = s - sbeg;
		goto insert;
	    }
	}
    }
    if (!s && (l = rb_enc_mbcput(c, carry, enc)) > 0) {
      insert:
	RESIZE_CAPA(str, RSTRING_LEN(str) + l - o);
	s = RSTRING_PTR(str) + n;
	memmove(s + l, s + o, RSTRING_LEN(str) - n - o);
      overlay:
	memmove(s, carry, l);
	STR_SET_LEN(str, RSTRING_LEN(str) + l - o);
	RSTRING_PTR(str)[RSTRING_LEN(str)] = '\0';
    }

    return str;
}


/*
 *  call-seq:
 *     str.succ!   => str
 *     str.next!   => str
 *  
 *  Equivalent to <code>String#succ</code>, but modifies the receiver in
 *  place.
 */

static VALUE
rb_str_succ_bang(VALUE str)
{
    rb_str_shared_replace(str, rb_str_succ(str));

    return str;
}


/*
 *  call-seq:
 *     str.upto(other_str, exclusive=false) {|s| block }   => str
 *  
 *  Iterates through successive values, starting at <i>str</i> and
 *  ending at <i>other_str</i> inclusive, passing each value in turn to
 *  the block. The <code>String#succ</code> method is used to generate
 *  each value.  If optional second arguent excle is omitted or is <code>false</code>,
 *  the last value will be included; otherwise it will be excluded.
 *     
 *     "a8".upto("b6") {|s| print s, ' ' }
 *     for s in "a8".."b6"
 *       print s, ' '
 *     end
 *     
 *  <em>produces:</em>
 *     
 *     a8 a9 b0 b1 b2 b3 b4 b5 b6
 *     a8 a9 b0 b1 b2 b3 b4 b5 b6
 */

static VALUE
rb_str_upto(int argc, VALUE *argv, VALUE beg)
{
    VALUE end, exclusive;
    VALUE current, after_end;
    ID succ;
    int n, excl;

    rb_scan_args(argc, argv, "11", &end, &exclusive);
    rb_enc_check(beg, end);
    excl = RTEST(exclusive);
    succ = rb_intern("succ");
    StringValue(end);
    n = rb_str_cmp(beg, end);
    if (n > 0 || (excl && n == 0)) return beg;
    after_end = rb_funcall(end, succ, 0, 0);
    current = beg;
    while (!rb_str_equal(current, after_end)) {
	rb_yield(current);
	if (!excl && rb_str_equal(current, end)) break;
	current = rb_funcall(current, succ, 0, 0);
	StringValue(current);
	if (excl && rb_str_equal(current, end)) break;
	StringValue(current);
	if (RSTRING_LEN(current) > RSTRING_LEN(end) || RSTRING_LEN(current) == 0)
	    break;
    }

    return beg;
}

static VALUE
rb_str_subpat(VALUE str, VALUE re, int nth)
{
    if (rb_reg_search(re, str, 0, 0) >= 0) {
	return rb_reg_nth_match(nth, rb_backref_get());
    }
    return Qnil;
}

static VALUE
rb_str_aref(VALUE str, VALUE indx)
{
    long idx;

    switch (TYPE(indx)) {
      case T_FIXNUM:
	idx = FIX2LONG(indx);

      num_index:
	str = rb_str_substr(str, idx, 1);
	if (!NIL_P(str) && RSTRING_LEN(str) == 0) return Qnil;
	return str;

      case T_REGEXP:
	return rb_str_subpat(str, indx, 0);

      case T_STRING:
	if (rb_str_index(str, indx, 0) != -1)
	    return rb_str_dup(indx);
	return Qnil;

      default:
	/* check if indx is Range */
	{
	    long beg, len;
	    VALUE tmp;

	    len = str_strlen(str, rb_enc_get(str));
	    switch (rb_range_beg_len(indx, &beg, &len, len, 0)) {
	      case Qfalse:
		break;
	      case Qnil:
		return Qnil;
	      default:
		tmp = rb_str_substr(str, beg, len);
		return tmp;
	    }
	}
	idx = NUM2LONG(indx);
	goto num_index;
    }
    return Qnil;		/* not reached */
}


/*
 *  call-seq:
 *     str[fixnum]                 => new_str or nil
 *     str[fixnum, fixnum]         => new_str or nil
 *     str[range]                  => new_str or nil
 *     str[regexp]                 => new_str or nil
 *     str[regexp, fixnum]         => new_str or nil
 *     str[other_str]              => new_str or nil
 *     str.slice(fixnum)           => new_str or nil
 *     str.slice(fixnum, fixnum)   => new_str or nil
 *     str.slice(range)            => new_str or nil
 *     str.slice(regexp)           => new_str or nil
 *     str.slice(regexp, fixnum)   => new_str or nil
 *     str.slice(other_str)        => new_str or nil
 *  
 *  Element Reference---If passed a single <code>Fixnum</code>, returns a
 *  substring of one character at that position. If passed two <code>Fixnum</code>
 *  objects, returns a substring starting at the offset given by the first, and
 *  a length given by the second. If given a range, a substring containing
 *  characters at offsets given by the range is returned. In all three cases, if
 *  an offset is negative, it is counted from the end of <i>str</i>. Returns
 *  <code>nil</code> if the initial offset falls outside the string, the length
 *  is negative, or the beginning of the range is greater than the end.
 *     
 *  If a <code>Regexp</code> is supplied, the matching portion of <i>str</i> is
 *  returned. If a numeric parameter follows the regular expression, that
 *  component of the <code>MatchData</code> is returned instead. If a
 *  <code>String</code> is given, that string is returned if it occurs in
 *  <i>str</i>. In both cases, <code>nil</code> is returned if there is no
 *  match.
 *     
 *     a = "hello there"
 *     a[1]                   #=> "e"
 *     a[1,3]                 #=> "ell"
 *     a[1..3]                #=> "ell"
 *     a[-3,2]                #=> "er"
 *     a[-4..-2]              #=> "her"
 *     a[12..-1]              #=> nil
 *     a[-2..-4]              #=> ""
 *     a[/[aeiou](.)\1/]      #=> "ell"
 *     a[/[aeiou](.)\1/, 0]   #=> "ell"
 *     a[/[aeiou](.)\1/, 1]   #=> "l"
 *     a[/[aeiou](.)\1/, 2]   #=> nil
 *     a["lo"]                #=> "lo"
 *     a["bye"]               #=> nil
 */

static VALUE
rb_str_aref_m(int argc, VALUE *argv, VALUE str)
{
    if (argc == 2) {
	if (TYPE(argv[0]) == T_REGEXP) {
	    return rb_str_subpat(str, argv[0], NUM2INT(argv[1]));
	}
	return rb_str_substr(str, NUM2LONG(argv[0]), NUM2LONG(argv[1]));
    }
    if (argc != 1) {
	rb_raise(rb_eArgError, "wrong number of arguments (%d for 1)", argc);
    }
    return rb_str_aref(str, argv[0]);
}

static void
rb_str_splice_0(VALUE str, long beg, long len, VALUE val)
{
    rb_str_modify(str);
    if (len < RSTRING_LEN(val)) {
	/* expand string */
	RESIZE_CAPA(str, RSTRING_LEN(str) + RSTRING_LEN(val) - len + 1);
    }

    if (RSTRING_LEN(val) != len) {
	memmove(RSTRING_PTR(str) + beg + RSTRING_LEN(val),
		RSTRING_PTR(str) + beg + len,
		RSTRING_LEN(str) - (beg + len));
    }
    if (RSTRING_LEN(val) < beg && len < 0) {
	MEMZERO(RSTRING_PTR(str) + RSTRING_LEN(str), char, -len);
    }
    if (RSTRING_LEN(val) > 0) {
	memmove(RSTRING_PTR(str)+beg, RSTRING_PTR(val), RSTRING_LEN(val));
    }
    STR_SET_LEN(str, RSTRING_LEN(str) + RSTRING_LEN(val) - len);
    if (RSTRING_PTR(str)) {
	RSTRING_PTR(str)[RSTRING_LEN(str)] = '\0';
    }
    OBJ_INFECT(str, val);
}

static void
rb_str_splice(VALUE str, long beg, long len, VALUE val)
{
    long slen;
    char *p, *e;
    rb_encoding *enc;
    int asc = IS_7BIT(str);

    if (len < 0) rb_raise(rb_eIndexError, "negative length %ld", len);

    StringValue(val);
    rb_str_modify(str);
    enc = rb_enc_check(str, val);
    slen = str_strlen(str, enc);

    if (slen < beg) {
      out_of_range:
	rb_raise(rb_eIndexError, "index %ld out of string", beg);
    }
    if (beg < 0) {
	if (-beg > slen) {
	    goto out_of_range;
	}
	beg += slen;
    }
    if (slen < len || slen < beg + len) {
	len = slen - beg;
    }
    p = str_nth(RSTRING_PTR(str), RSTRING_END(str), beg, enc, asc);
    if (!p) p = RSTRING_END(str);
    e = str_nth(p, RSTRING_END(str), len, enc, asc);
    if (!e) e = RSTRING_END(str);
    /* error check */
    beg = p - RSTRING_PTR(str);	/* physical position */
    len = e - p;		/* physical length */
    rb_str_splice_0(str, beg, len, val);
    rb_enc_associate(str, enc);
}

void
rb_str_update(VALUE str, long beg, long len, VALUE val)
{
    rb_str_splice(str, beg, len, val);
}

static void
rb_str_subpat_set(VALUE str, VALUE re, int nth, VALUE val)
{
    VALUE match;
    long start, end, len;
    rb_encoding *enc;

    if (rb_reg_search(re, str, 0, 0) < 0) {
	rb_raise(rb_eIndexError, "regexp not matched");
    }
    match = rb_backref_get();
    if (nth >= RMATCH(match)->regs->num_regs) {
      out_of_range:
	rb_raise(rb_eIndexError, "index %d out of regexp", nth);
    }
    if (nth < 0) {
	if (-nth >= RMATCH(match)->regs->num_regs) {
	    goto out_of_range;
	}
	nth += RMATCH(match)->regs->num_regs;
    }

    start = RMATCH(match)->BEG(nth);
    if (start == -1) {
	rb_raise(rb_eIndexError, "regexp group %d not matched", nth);
    }
    end = RMATCH(match)->END(nth);
    len = end - start;
    StringValue(val);
    enc = rb_enc_check(str, val);
    rb_str_splice_0(str, start, len, val);
    rb_enc_associate(str, enc);
}

static VALUE
rb_str_aset(VALUE str, VALUE indx, VALUE val)
{
    long idx, beg;

    switch (TYPE(indx)) {
      case T_FIXNUM:
	idx = FIX2LONG(indx);
      num_index:
	rb_str_splice(str, idx, 1, val);
	return val;

      case T_REGEXP:
	rb_str_subpat_set(str, indx, 0, val);
	return val;

      case T_STRING:
	beg = rb_str_index(str, indx, 0);
	if (beg < 0) {
	    rb_raise(rb_eIndexError, "string not matched");
	}
	beg = rb_str_sublen(str, beg);
	rb_str_splice(str, beg, str_strlen(indx, 0), val);
	return val;

      default:
	/* check if indx is Range */
	{
	    long beg, len;
	    if (rb_range_beg_len(indx, &beg, &len, str_strlen(str, 0), 2)) {
		rb_str_splice(str, beg, len, val);
		return val;
	    }
	}
	idx = NUM2LONG(indx);
	goto num_index;
    }
}

/*
 *  call-seq:
 *     str[fixnum] = new_str
 *     str[fixnum, fixnum] = new_str
 *     str[range] = aString
 *     str[regexp] = new_str
 *     str[regexp, fixnum] = new_str
 *     str[other_str] = new_str
 *  
 *  Element Assignment---Replaces some or all of the content of <i>str</i>. The
 *  portion of the string affected is determined using the same criteria as
 *  <code>String#[]</code>. If the replacement string is not the same length as
 *  the text it is replacing, the string will be adjusted accordingly. If the
 *  regular expression or string is used as the index doesn't match a position
 *  in the string, <code>IndexError</code> is raised. If the regular expression
 *  form is used, the optional second <code>Fixnum</code> allows you to specify
 *  which portion of the match to replace (effectively using the
 *  <code>MatchData</code> indexing rules. The forms that take a
 *  <code>Fixnum</code> will raise an <code>IndexError</code> if the value is
 *  out of range; the <code>Range</code> form will raise a
 *  <code>RangeError</code>, and the <code>Regexp</code> and <code>String</code>
 *  forms will silently ignore the assignment.
 */

static VALUE
rb_str_aset_m(int argc, VALUE *argv, VALUE str)
{
    if (argc == 3) {
	if (TYPE(argv[0]) == T_REGEXP) {
	    rb_str_subpat_set(str, argv[0], NUM2INT(argv[1]), argv[2]);
	}
	else {
	    rb_str_splice(str, NUM2LONG(argv[0]), NUM2LONG(argv[1]), argv[2]);
	}
	return argv[2];
    }
    if (argc != 2) {
	rb_raise(rb_eArgError, "wrong number of arguments (%d for 2)", argc);
    }
    return rb_str_aset(str, argv[0], argv[1]);
}

/*
 *  call-seq:
 *     str.insert(index, other_str)   => str
 *  
 *  Inserts <i>other_str</i> before the character at the given
 *  <i>index</i>, modifying <i>str</i>. Negative indices count from the
 *  end of the string, and insert <em>after</em> the given character.
 *  The intent is insert <i>aString</i> so that it starts at the given
 *  <i>index</i>.
 *     
 *     "abcd".insert(0, 'X')    #=> "Xabcd"
 *     "abcd".insert(3, 'X')    #=> "abcXd"
 *     "abcd".insert(4, 'X')    #=> "abcdX"
 *     "abcd".insert(-3, 'X')   #=> "abXcd"
 *     "abcd".insert(-1, 'X')   #=> "abcdX"
 */

static VALUE
rb_str_insert(VALUE str, VALUE idx, VALUE str2)
{
    long pos = NUM2LONG(idx);

    if (pos == -1) {
	return rb_str_append(str, str2);
    }
    else if (pos < 0) {
	pos++;
    }
    rb_str_splice(str, pos, 0, str2);
    return str;
}


/*
 *  call-seq:
 *     str.slice!(fixnum)           => fixnum or nil
 *     str.slice!(fixnum, fixnum)   => new_str or nil
 *     str.slice!(range)            => new_str or nil
 *     str.slice!(regexp)           => new_str or nil
 *     str.slice!(other_str)        => new_str or nil
 *  
 *  Deletes the specified portion from <i>str</i>, and returns the portion
 *  deleted.
 *     
 *     string = "this is a string"
 *     string.slice!(2)        #=> 105
 *     string.slice!(3..6)     #=> " is "
 *     string.slice!(/s.*t/)   #=> "sa st"
 *     string.slice!("r")      #=> "r"
 *     string                  #=> "thing"
 */

static VALUE
rb_str_slice_bang(int argc, VALUE *argv, VALUE str)
{
    VALUE result;
    VALUE buf[3];
    int i;

    if (argc < 1 || 2 < argc) {
	rb_raise(rb_eArgError, "wrong number of arguments (%d for 1)", argc);
    }
    for (i=0; i<argc; i++) {
	buf[i] = argv[i];
    }
    rb_str_modify(str);
    buf[i] = rb_str_new(0,0);
    result = rb_str_aref_m(argc, buf, str);
    if (!NIL_P(result)) {
	rb_str_aset_m(argc+1, buf, str);
    }
    return result;
}

static VALUE
get_pat(VALUE pat, int quote)
{
    VALUE val;

    switch (TYPE(pat)) {
      case T_REGEXP:
	return pat;

      case T_STRING:
	break;

      default:
	val = rb_check_string_type(pat);
	if (NIL_P(val)) {
	    Check_Type(pat, T_REGEXP);
	}
	pat = val;
    }

    if (quote) {
	pat = rb_reg_quote(pat);
    }

    return rb_reg_regcomp(pat);
}


/*
 *  call-seq:
 *     str.sub!(pattern, replacement)          => str or nil
 *     str.sub!(pattern) {|match| block }      => str or nil
 *  
 *  Performs the substitutions of <code>String#sub</code> in place,
 *  returning <i>str</i>, or <code>nil</code> if no substitutions were
 *  performed.
 */

static VALUE
rb_str_sub_bang(int argc, VALUE *argv, VALUE str)
{
    VALUE pat, repl, match;
    struct re_registers *regs;
    int iter = 0;
    int tainted = 0;
    long plen;

    if (argc == 1 && rb_block_given_p()) {
	iter = 1;
    }
    else if (argc == 2) {
	repl = argv[1];
	StringValue(repl);
	if (OBJ_TAINTED(repl)) tainted = 1;
    }
    else {
	rb_raise(rb_eArgError, "wrong number of arguments (%d for 2)", argc);
    }

    pat = get_pat(argv[0], 1);
    if (rb_reg_search(pat, str, 0, 0) >= 0) {
	rb_encoding *enc;

	match = rb_backref_get();
	regs = RMATCH(match)->regs;

	if (iter) {
	    char *p = RSTRING_PTR(str); long len = RSTRING_LEN(str);

	    rb_match_busy(match);
	    repl = rb_obj_as_string(rb_yield(rb_reg_nth_match(0, match)));
	    enc = rb_enc_check(str, repl);
	    str_mod_check(str, p, len);
	    str_frozen_check(str);
	    rb_backref_set(match);
	}
	else {
	    repl = rb_reg_regsub(repl, str, regs, pat);
	    enc = rb_enc_check(str, repl);
	}
	rb_str_modify(str);
	rb_enc_associate(str, enc);
	if (OBJ_TAINTED(repl)) tainted = 1;
	plen = END(0) - BEG(0);
	if (RSTRING_LEN(repl) > plen) {
	    RESIZE_CAPA(str, RSTRING_LEN(str) + RSTRING_LEN(repl) - plen);
	}
	if (RSTRING_LEN(repl) != plen) {
	    memmove(RSTRING_PTR(str) + BEG(0) + RSTRING_LEN(repl),
		    RSTRING_PTR(str) + BEG(0) + plen,
		    RSTRING_LEN(str) - BEG(0) - plen);
	}
	memcpy(RSTRING_PTR(str) + BEG(0),
	       RSTRING_PTR(repl), RSTRING_LEN(repl));
	STR_SET_LEN(str, RSTRING_LEN(str) + RSTRING_LEN(repl) - plen);
	RSTRING_PTR(str)[RSTRING_LEN(str)] = '\0';
	if (tainted) OBJ_TAINT(str);

	return str;
    }
    return Qnil;
}


/*
 *  call-seq:
 *     str.sub(pattern, replacement)         => new_str
 *     str.sub(pattern) {|match| block }     => new_str
 *  
 *  Returns a copy of <i>str</i> with the <em>first</em> occurrence of
 *  <i>pattern</i> replaced with either <i>replacement</i> or the value of the
 *  block. The <i>pattern</i> will typically be a <code>Regexp</code>; if it is
 *  a <code>String</code> then no regular expression metacharacters will be
 *  interpreted (that is <code>/\d/</code> will match a digit, but
 *  <code>'\d'</code> will match a backslash followed by a 'd').
 *     
 *  If the method call specifies <i>replacement</i>, special variables such as
 *  <code>$&</code> will not be useful, as substitution into the string occurs
 *  before the pattern match starts. However, the sequences <code>\1</code>,
 *  <code>\2</code>, <code>\k<group_name></code>, etc., may be used.
 *     
 *  In the block form, the current match string is passed in as a parameter, and
 *  variables such as <code>$1</code>, <code>$2</code>, <code>$`</code>,
 *  <code>$&</code>, and <code>$'</code> will be set appropriately. The value
 *  returned by the block will be substituted for the match on each call.
 *     
 *  The result inherits any tainting in the original string or any supplied
 *  replacement string.
 *     
 *     "hello".sub(/[aeiou]/, '*')                  #=> "h*llo"
 *     "hello".sub(/([aeiou])/, '<\1>')             #=> "h<e>llo"
 *     "hello".sub(/./) {|s| s[0].to_s + ' ' }      #=> "104 ello"
 *     "hello".sub(/(?<foo>[aeiou])/, '*\k<foo>*')  #=> "h*e*llo"
 */

static VALUE
rb_str_sub(int argc, VALUE *argv, VALUE str)
{
    str = rb_str_dup(str);
    rb_str_sub_bang(argc, argv, str);
    return str;
}

static VALUE
str_gsub(int argc, VALUE *argv, VALUE str, int bang)
{
    VALUE pat, val, repl, match, dest;
    struct re_registers *regs;
    long beg, n;
    long offset, blen, slen, len;
    int iter = 0;
    char *buf, *bp, *sp, *cp;
    int tainted = 0;
    rb_encoding *enc;
    
    switch (argc) {
      case 1:
	RETURN_ENUMERATOR(str, argc, argv);
	iter = 1;
	break;
      case 2:
	repl = argv[1];
	StringValue(repl);
	if (OBJ_TAINTED(repl)) tainted = 1;
	break;
      default:
	rb_raise(rb_eArgError, "wrong number of arguments (%d for 2)", argc);
    }

    pat = get_pat(argv[0], 1);
    enc = rb_enc_get(pat);
    offset=0; n=0;
    beg = rb_reg_search(pat, str, 0, 0);
    if (beg < 0) {
	if (bang) return Qnil;	/* no match, no substitution */
	return rb_str_dup(str);
    }

    blen = RSTRING_LEN(str) + 30; /* len + margin */
    dest = str_new(0, 0, blen);
    buf = RSTRING_PTR(dest);
    bp = buf;
    sp = cp = RSTRING_PTR(str);
    slen = RSTRING_LEN(str);

    rb_str_locktmp(dest);
    do {
	rb_encoding *enc;

	n++;
	match = rb_backref_get();
	regs = RMATCH(match)->regs;
	if (iter) {

	    rb_match_busy(match);
	    val = rb_obj_as_string(rb_yield(rb_reg_nth_match(0, match)));
	    enc = rb_enc_check(str, val);
	    str_mod_check(str, sp, slen);
	    if (bang) str_frozen_check(str);
	    if (val == dest) { 	/* paranoid chack [ruby-dev:24827] */
		rb_raise(rb_eRuntimeError, "block should not cheat");
	    }
	    rb_backref_set(match);
	}
	else {
	    val = rb_reg_regsub(repl, str, regs, pat);
	    enc = rb_enc_check(str, val);
	}
	rb_enc_associate(str, enc);
	if (OBJ_TAINTED(val)) tainted = 1;
	len = (bp - buf) + (beg - offset) + RSTRING_LEN(val) + 3;
	if (blen < len) {
	    while (blen < len) blen *= 2;
	    len = bp - buf;
	    RESIZE_CAPA(dest, blen);
	    STR_SET_LEN(dest, blen);
	    buf = RSTRING_PTR(dest);
	    bp = buf + len;
	}
	len = beg - offset;	/* copy pre-match substr */
	memcpy(bp, cp, len);
	bp += len;
	memcpy(bp, RSTRING_PTR(val), RSTRING_LEN(val));
	bp += RSTRING_LEN(val);
	offset = END(0);
	if (BEG(0) == END(0)) {
	    /*
	     * Always consume at least one character of the input string
	     * in order to prevent infinite loops.
	     */
	    if (RSTRING_LEN(str) <= END(0)) break;
	    len = rb_enc_mbclen(RSTRING_PTR(str)+END(0), RSTRING_END(str), enc);
	    memcpy(bp, RSTRING_PTR(str)+END(0), len);
	    bp += len;
	    offset = END(0) + len;
	}
	cp = RSTRING_PTR(str) + offset;
	if (offset > RSTRING_LEN(str)) break;
	beg = rb_reg_search(pat, str, offset, 0);
    } while (beg >= 0);
    if (RSTRING_LEN(str) > offset) {
	len = bp - buf;
	if (blen - len < RSTRING_LEN(str) - offset) {
	    blen = len + RSTRING_LEN(str) - offset;
	    RESIZE_CAPA(dest, blen);
	    buf = RSTRING_PTR(dest);
	    bp = buf + len;
	}
	memcpy(bp, cp, RSTRING_LEN(str) - offset);
	bp += RSTRING_LEN(str) - offset;
    }
    rb_backref_set(match);
    *bp = '\0';
    rb_str_unlocktmp(dest);
    if (bang) {
	if (str_independent(str) && !STR_EMBED_P(str)) {
	    free(RSTRING_PTR(str));
	}
	STR_SET_NOEMBED(str);
	STR_UNSET_NOCAPA(str);
	RSTRING(str)->as.heap.ptr = buf;
	RSTRING(str)->as.heap.aux.capa = blen;
	RSTRING(dest)->as.heap.ptr = 0;
	RSTRING(dest)->as.heap.len = 0;
    }
    else {
	RBASIC(dest)->klass = rb_obj_class(str);
	OBJ_INFECT(dest, str);
	rb_enc_copy(dest, str);
	str = dest;
    }
    STR_SET_LEN(str, bp - buf);

    if (tainted) OBJ_TAINT(str);
    return str;
}


/*
 *  call-seq:
 *     str.gsub!(pattern, replacement)        => str or nil
 *     str.gsub!(pattern) {|match| block }    => str or nil
 *  
 *  Performs the substitutions of <code>String#gsub</code> in place, returning
 *  <i>str</i>, or <code>nil</code> if no substitutions were performed.
 */

static VALUE
rb_str_gsub_bang(int argc, VALUE *argv, VALUE str)
{
    return str_gsub(argc, argv, str, 1);
}


/*
 *  call-seq:
 *     str.gsub(pattern, replacement)       => new_str
 *     str.gsub(pattern) {|match| block }   => new_str
 *  
 *  Returns a copy of <i>str</i> with <em>all</em> occurrences of <i>pattern</i>
 *  replaced with either <i>replacement</i> or the value of the block. The
 *  <i>pattern</i> will typically be a <code>Regexp</code>; if it is a
 *  <code>String</code> then no regular expression metacharacters will be
 *  interpreted (that is <code>/\d/</code> will match a digit, but
 *  <code>'\d'</code> will match a backslash followed by a 'd').
 *     
 *  If a string is used as the replacement, special variables from the match
 *  (such as <code>$&</code> and <code>$1</code>) cannot be substituted into it,
 *  as substitution into the string occurs before the pattern match
 *  starts. However, the sequences <code>\1</code>, <code>\2</code>,
 *  <code>\k<group_name></code>, and so on may be used to interpolate
 *  successive groups in the match.
 *     
 *  In the block form, the current match string is passed in as a parameter, and
 *  variables such as <code>$1</code>, <code>$2</code>, <code>$`</code>,
 *  <code>$&</code>, and <code>$'</code> will be set appropriately. The value
 *  returned by the block will be substituted for the match on each call.
 *     
 *  The result inherits any tainting in the original string or any supplied
 *  replacement string.
 *     
 *     "hello".gsub(/[aeiou]/, '*')                  #=> "h*ll*"
 *     "hello".gsub(/([aeiou])/, '<\1>')             #=> "h<e>ll<o>"
 *     "hello".gsub(/./) {|s| s[0].to_s + ' '}       #=> "104 101 108 108 111 "
 *     "hello".gsub(/(?<foo>[aeiou])/, '{\k<foo>}')  #=> "h{e}ll{o}"
 */

static VALUE
rb_str_gsub(int argc, VALUE *argv, VALUE str)
{
    return str_gsub(argc, argv, str, 0);
}


/*
 *  call-seq:
 *     str.replace(other_str)   => str
 *  
 *  Replaces the contents and taintedness of <i>str</i> with the corresponding
 *  values in <i>other_str</i>.
 *     
 *     s = "hello"         #=> "hello"
 *     s.replace "world"   #=> "world"
 */

static VALUE
rb_str_replace(VALUE str, VALUE str2)
{
    long len;
    if (str == str2) return str;

    StringValue(str2);
    len = RSTRING_LEN(str2);
    if (STR_SHARED_P(str2)) {
	if (str_independent(str) && !STR_EMBED_P(str)) {
	    free(RSTRING_PTR(str));
	}
	STR_SET_NOEMBED(str);
	RSTRING(str)->as.heap.len = len;
	RSTRING(str)->as.heap.ptr = RSTRING_PTR(str2);
	FL_SET(str, ELTS_SHARED);
	FL_UNSET(str, STR_ASSOC);
	RSTRING(str)->as.heap.aux.shared = RSTRING(str2)->as.heap.aux.shared;
    }
    else if (STR_ASSOC_P(str2)) {
	rb_str_modify(str);
	STR_SET_NOEMBED(str);
	RSTRING(str)->as.heap.ptr = ALLOC_N(char,len+1);
	memcpy(RSTRING_PTR(str), RSTRING_PTR(str2), len+1);
	FL_SET(str, STR_ASSOC);
	RSTRING(str)->as.heap.aux.shared = RSTRING(str2)->as.heap.aux.shared;
    }
    else {
	rb_str_modify(str);
	rb_str_resize(str, len);
	memcpy(RSTRING_PTR(str), RSTRING_PTR(str2), len+1);
    }

    OBJ_INFECT(str, str2);
    rb_enc_copy(str, str2);
    return str;
}

/*
 *  call-seq:
 *     string.clear    ->  string
 *
 *  Makes string empty.
 *
 *     a = "abcde"
 *     a.clear    #=> ""
 */

static VALUE
rb_str_clear(VALUE str)
{
    /* rb_str_modify() */	/* no need for str_make_independent */
    if (str_independent(str) && !STR_EMBED_P(str)) {
	free(RSTRING_PTR(str));
    }
    STR_SET_EMBED(str);
    STR_SET_EMBED_LEN(str, 0);
    RSTRING_PTR(str)[0] = 0;
    return str;
}

/*
 *  call-seq:
 *     string.chr    ->  string
 *
 *  Returns a one-character string at the beginning of the string.
 *
 *     a = "abcde"
 *     a.chr    #=> "a"
 */

static VALUE
rb_str_chr(VALUE str)
{
    return rb_str_substr(str, 0, 1);
}

/*
 *  call-seq:
 *     str.reverse   => new_str
 *  
 *  Returns a new string with the characters from <i>str</i> in reverse order.
 *     
 *     "stressed".reverse   #=> "desserts"
 */

static VALUE
rb_str_reverse(VALUE str)
{
    rb_encoding *enc;
    VALUE obj;
    char *s, *e, *p;

    if (RSTRING_LEN(str) <= 1) return rb_str_dup(str);
    enc = rb_enc_get(str);
    obj = rb_str_new5(str, 0, RSTRING_LEN(str));
    s = RSTRING_PTR(str); e = RSTRING_END(str);
    p = RSTRING_END(obj);

    if (RSTRING_LEN(str) > 1) {
	if (rb_enc_mbmaxlen(enc) == 1) {
	    while (s < e) {
		*--p = *s++;
	    }
	}
	else {
	    while (s < e) {
		int clen = rb_enc_mbclen(s, e, enc);

		p -= clen;
		memcpy(p, s, clen);
		s += clen;
	    }
	}
    }
    STR_SET_LEN(obj, RSTRING_LEN(str));
    OBJ_INFECT(obj, str);
    rb_enc_associate(obj, enc);

    return obj;
}


/*
 *  call-seq:
 *     str.reverse!   => str
 *  
 *  Reverses <i>str</i> in place.
 */

static VALUE
rb_str_reverse_bang(VALUE str)
{
    rb_encoding *enc = rb_enc_get(str);
    char *s, *e, c;

    if (RSTRING_LEN(str) > 1) {
	rb_str_modify(str);
	s = RSTRING_PTR(str);
	e = RSTRING_END(str) - 1;

	if (rb_enc_mbmaxlen(enc) == 1) {
	    while (s < e) {
		c = *s;
		*s++ = *e;
 		*e-- = c;
	    }
	}
	else {
	    rb_str_shared_replace(str, rb_str_reverse(str));
	}
    }
    return str;
}


/*
 *  call-seq:
 *     str.include? other_str   => true or false
 *     str.include? fixnum      => true or false
 *  
 *  Returns <code>true</code> if <i>str</i> contains the given string or
 *  character.
 *     
 *     "hello".include? "lo"   #=> true
 *     "hello".include? "ol"   #=> false
 *     "hello".include? ?h     #=> true
 */

static VALUE
rb_str_include(VALUE str, VALUE arg)
{
    long i;

    StringValue(arg);
    i = rb_str_index(str, arg, 0);

    if (i == -1) return Qfalse;
    return Qtrue;
}


/*
 *  call-seq:
 *     str.to_i(base=10)   => integer
 *  
 *  Returns the result of interpreting leading characters in <i>str</i> as an
 *  integer base <i>base</i> (between 2 and 36). Extraneous characters past the
 *  end of a valid number are ignored. If there is not a valid number at the
 *  start of <i>str</i>, <code>0</code> is returned. This method never raises an
 *  exception.
 *     
 *     "12345".to_i             #=> 12345
 *     "99 red balloons".to_i   #=> 99
 *     "0a".to_i                #=> 0
 *     "0a".to_i(16)            #=> 10
 *     "hello".to_i             #=> 0
 *     "1100101".to_i(2)        #=> 101
 *     "1100101".to_i(8)        #=> 294977
 *     "1100101".to_i(10)       #=> 1100101
 *     "1100101".to_i(16)       #=> 17826049
 */

static VALUE
rb_str_to_i(int argc, VALUE *argv, VALUE str)
{
    VALUE b;
    int base;

    rb_scan_args(argc, argv, "01", &b);
    if (argc == 0) base = 10;
    else base = NUM2INT(b);

    if (base < 0) {
	rb_raise(rb_eArgError, "invalid radix %d", base);
    }
    return rb_str_to_inum(str, base, Qfalse);
}


/*
 *  call-seq:
 *     str.to_f   => float
 *  
 *  Returns the result of interpreting leading characters in <i>str</i> as a
 *  floating point number. Extraneous characters past the end of a valid number
 *  are ignored. If there is not a valid number at the start of <i>str</i>,
 *  <code>0.0</code> is returned. This method never raises an exception.
 *     
 *     "123.45e1".to_f        #=> 1234.5
 *     "45.67 degrees".to_f   #=> 45.67
 *     "thx1138".to_f         #=> 0.0
 */

static VALUE
rb_str_to_f(VALUE str)
{
    return DOUBLE2NUM(rb_str_to_dbl(str, Qfalse));
}


/*
 *  call-seq:
 *     str.to_s     => str
 *     str.to_str   => str
 *  
 *  Returns the receiver.
 */

static VALUE
rb_str_to_s(VALUE str)
{
    if (rb_obj_class(str) != rb_cString) {
	VALUE dup = str_alloc(rb_cString);
	rb_str_replace(dup, str);
	return dup;
    }
    return str;
}

static void
str_cat_char(VALUE str, int c, rb_encoding *enc)
{
    char s[16];
    int n = rb_enc_codelen(c, enc);

    rb_enc_mbcput(c, s, enc);
    rb_str_buf_cat(str, s, n);
}

static void
prefix_escape(VALUE str, int c, rb_encoding *enc)
{
    str_cat_char(str, '\\', enc);
    str_cat_char(str, c, enc);
}

/*
 * call-seq:
 *   str.inspect   => string
 *
 * Returns a printable version of _str_, srrounded by quote marks,
 * with special characters escaped.
 *
 *    str = "hello"
 *    str[3] = "\b"
 *    str.inspect       #=> "\"hel\bo\""
 */

VALUE
rb_str_inspect(VALUE str)
{
    rb_encoding *enc = rb_enc_get(str);
    char *p, *pend;
    VALUE result = rb_str_buf_new2("");

    rb_enc_associate(result, enc);
    str_cat_char(result, '"', enc);
    p = RSTRING_PTR(str); pend = RSTRING_END(str);
    while (p < pend) {
	int c;
	int n;
	int cc;

        n = rb_enc_precise_mbclen(p, pend, enc);
        if (!MBCLEN_CHARFOUND(n)) {
            p++;
            n = 1;
            goto escape_codepoint;
        }

	c = rb_enc_codepoint(p, pend, enc);
	n = rb_enc_codelen(c, enc);

	p += n;
	if (c == '"'|| c == '\\' ||
	    (c == '#' && p < pend &&
                          (cc = rb_enc_codepoint(p,pend,enc),
			  (cc == '$' || cc == '@' || cc == '{')))) {
	    prefix_escape(result, c, enc);
	}
	else if (c == '\n') {
	    prefix_escape(result, 'n', enc);
	}
	else if (c == '\r') {
	    prefix_escape(result, 'r', enc);
	}
	else if (c == '\t') {
	    prefix_escape(result, 't', enc);
	}
	else if (c == '\f') {
	    prefix_escape(result, 'f', enc);
	}
	else if (c == '\013') {
	    prefix_escape(result, 'v', enc);
	}
	else if (c == '\010') {
	    prefix_escape(result, 'b', enc);
	}
	else if (c == '\007') {
	    prefix_escape(result, 'a', enc);
	}
	else if (c == 033) {
	    prefix_escape(result, 'e', enc);
	}
	else if (rb_enc_isprint(c, enc)) {
	    rb_str_buf_cat(result, p-n, n);
	}
	else {
	    char buf[5];
	    char *s;
            char *q;

escape_codepoint:
            for (q = p-n; q < p; q++) {
                s = buf;
                sprintf(buf, "\\x%02X", *q & 0377);
                while (*s) {
                    str_cat_char(result, *s++, enc);
                }
            }
	}
    }
    str_cat_char(result, '"', enc);

    OBJ_INFECT(result, str);
    return result;
}

#define IS_EVSTR(p,e) ((p) < (e) && (*(p) == '$' || *(p) == '@' || *(p) == '{'))

/*
 *  call-seq:
 *     str.dump   => new_str
 *  
 *  Produces a version of <i>str</i> with all nonprinting characters replaced by
 *  <code>\nnn</code> notation and all special characters escaped.
 */

VALUE
rb_str_dump(VALUE str)
{
    rb_encoding *enc = rb_enc_from_index(0);
    long len;
    char *p, *pend;
    char *q, *qend;
    VALUE result;

    len = 2;			/* "" */
    p = RSTRING_PTR(str); pend = p + RSTRING_LEN(str);
    while (p < pend) {
	char c = *p++;
	switch (c) {
	  case '"':  case '\\':
	  case '\n': case '\r':
	  case '\t': case '\f':
	  case '\013': case '\010': case '\007': case '\033':
	    len += 2;
	    break;

	  case '#':
	    len += IS_EVSTR(p, pend) ? 2 : 1;
	    break;

	  default:
	    if (rb_enc_isprint(c, enc)) {
		len++;
	    }
	    else {
		len += 4;		/* \nnn */
	    }
	    break;
	}
    }

    result = rb_str_new5(str, 0, len);
    p = RSTRING_PTR(str); pend = p + RSTRING_LEN(str);
    q = RSTRING_PTR(result); qend = q + len;

    *q++ = '"';
    while (p < pend) {
	char c = *p++;

	if (c == '"' || c == '\\') {
	    *q++ = '\\';
	    *q++ = c;
	}
	else if (c == '#') {
	    if (IS_EVSTR(p, pend)) *q++ = '\\';
	    *q++ = '#';
	}
	else if (c == '\n') {
	    *q++ = '\\';
	    *q++ = 'n';
	}
	else if (c == '\r') {
	    *q++ = '\\';
	    *q++ = 'r';
	}
	else if (c == '\t') {
	    *q++ = '\\';
	    *q++ = 't';
	}
	else if (c == '\f') {
	    *q++ = '\\';
	    *q++ = 'f';
	}
	else if (c == '\013') {
	    *q++ = '\\';
	    *q++ = 'v';
	}
	else if (c == '\010') {
	    *q++ = '\\';
	    *q++ = 'b';
	}
	else if (c == '\007') {
	    *q++ = '\\';
	    *q++ = 'a';
	}
	else if (c == '\033') {
	    *q++ = '\\';
	    *q++ = 'e';
	}
	else if (rb_enc_isprint(c, enc)) {
	    *q++ = c;
	}
	else {
	    *q++ = '\\';
	    sprintf(q, "x%02X", c&0xff);
	    q += 3;
	}
    }
    *q++ = '"';

    OBJ_INFECT(result, str);
    /* result from dump is ASCII */
    rb_enc_associate(result, enc);
    return result;
}


/*
 *  call-seq:
 *     str.upcase!   => str or nil
 *  
 *  Upcases the contents of <i>str</i>, returning <code>nil</code> if no changes
 *  were made.
 *  Note: case replacement is effective only in ASCII region.
 */

static VALUE
rb_str_upcase_bang(VALUE str)
{
    rb_encoding *enc;
    char *s, *send;
    int modify = 0;

    rb_str_modify(str);
    enc = rb_enc_get(str);
    s = RSTRING_PTR(str); send = RSTRING_END(str);
    while (s < send) {
	int c = rb_enc_codepoint(s, send, enc);

	if (rb_enc_islower(c, enc)) {
	    /* assuming toupper returns codepoint with same size */
	    rb_enc_mbcput(rb_enc_toupper(c, enc), s, enc);
	    modify = 1;
	}
	s += rb_enc_codelen(c, enc);
    }

    if (modify) return str;
    return Qnil;
}


/*
 *  call-seq:
 *     str.upcase   => new_str
 *  
 *  Returns a copy of <i>str</i> with all lowercase letters replaced with their
 *  uppercase counterparts. The operation is locale insensitive---only
 *  characters ``a'' to ``z'' are affected.
 *  Note: case replacement is effective only in ASCII region.
 *     
 *     "hEllO".upcase   #=> "HELLO"
 */

static VALUE
rb_str_upcase(VALUE str)
{
    str = rb_str_dup(str);
    rb_str_upcase_bang(str);
    return str;
}


/*
 *  call-seq:
 *     str.downcase!   => str or nil
 *  
 *  Downcases the contents of <i>str</i>, returning <code>nil</code> if no
 *  changes were made.
 *  Note: case replacement is effective only in ASCII region.
 */

static VALUE
rb_str_downcase_bang(VALUE str)
{
    rb_encoding *enc;
    char *s, *send;
    int modify = 0;

    rb_str_modify(str);
    enc = rb_enc_get(str);
    s = RSTRING_PTR(str); send = RSTRING_END(str);
    while (s < send) {
	int c = rb_enc_codepoint(s, send, enc);

	if (rb_enc_isupper(c, enc)) {
	    /* assuming toupper returns codepoint with same size */
	    rb_enc_mbcput(rb_enc_tolower(c, enc), s, enc);
	    modify = 1;
	}
	s += rb_enc_codelen(c, enc);
    }

    if (modify) return str;
    return Qnil;
}


/*
 *  call-seq:
 *     str.downcase   => new_str
 *  
 *  Returns a copy of <i>str</i> with all uppercase letters replaced with their
 *  lowercase counterparts. The operation is locale insensitive---only
 *  characters ``A'' to ``Z'' are affected.
 *  Note: case replacement is effective only in ASCII region.
 *     
 *     "hEllO".downcase   #=> "hello"
 */

static VALUE
rb_str_downcase(VALUE str)
{
    str = rb_str_dup(str);
    rb_str_downcase_bang(str);
    return str;
}


/*
 *  call-seq:
 *     str.capitalize!   => str or nil
 *  
 *  Modifies <i>str</i> by converting the first character to uppercase and the
 *  remainder to lowercase. Returns <code>nil</code> if no changes are made.
 *  Note: case conversion is effective only in ASCII region.
 *     
 *     a = "hello"
 *     a.capitalize!   #=> "Hello"
 *     a               #=> "Hello"
 *     a.capitalize!   #=> nil
 */

static VALUE
rb_str_capitalize_bang(VALUE str)
{
    rb_encoding *enc;
    char *s, *send;
    int modify = 0;
    int c;

    rb_str_modify(str);
    enc = rb_enc_get(str);
    if (RSTRING_LEN(str) == 0 || !RSTRING_PTR(str)) return Qnil;
    s = RSTRING_PTR(str); send = RSTRING_END(str);

    c = rb_enc_codepoint(s, send, enc);
    if (rb_enc_islower(c, enc)) {
	rb_enc_mbcput(rb_enc_toupper(c, enc), s, enc);
	modify = 1;
    }
    s += rb_enc_codelen(c, enc);
    while (s < send) {
	c = rb_enc_codepoint(s, send, enc);
	if (rb_enc_isupper(c, enc)) {
	    rb_enc_mbcput(rb_enc_tolower(c, enc), s, enc);
	    modify = 1;
	}
	s += rb_enc_codelen(c, enc);
    }
    if (modify) return str;
    return Qnil;
}


/*
 *  call-seq:
 *     str.capitalize   => new_str
 *  
 *  Returns a copy of <i>str</i> with the first character converted to uppercase
 *  and the remainder to lowercase.
 *  Note: case conversion is effective only in ASCII region.
 *     
 *     "hello".capitalize    #=> "Hello"
 *     "HELLO".capitalize    #=> "Hello"
 *     "123ABC".capitalize   #=> "123abc"
 */

static VALUE
rb_str_capitalize(VALUE str)
{
    str = rb_str_dup(str);
    rb_str_capitalize_bang(str);
    return str;
}


/*
 *  call-seq: 
*     str.swapcase!   => str or nil
 *  
 *  Equivalent to <code>String#swapcase</code>, but modifies the receiver in
 *  place, returning <i>str</i>, or <code>nil</code> if no changes were made.
 *  Note: case conversion is effective only in ASCII region.
 */

static VALUE
rb_str_swapcase_bang(VALUE str)
{
    rb_encoding *enc;
    char *s, *send;
    int modify = 0;

    rb_str_modify(str);
    enc = rb_enc_get(str);
    s = RSTRING_PTR(str); send = RSTRING_END(str);
    while (s < send) {
	int c = rb_enc_codepoint(s, send, enc);

	if (rb_enc_isupper(c, enc)) {
	    /* assuming toupper returns codepoint with same size */
	    rb_enc_mbcput(rb_enc_tolower(c, enc), s, enc);
	    modify = 1;
	}
	else if (rb_enc_islower(c, enc)) {
	    /* assuming toupper returns codepoint with same size */
	    rb_enc_mbcput(rb_enc_toupper(c, enc), s, enc);
	    modify = 1;
	}
	s += rb_enc_codelen(c, enc);
    }

    if (modify) return str;
    return Qnil;
}


/*
 *  call-seq:
 *     str.swapcase   => new_str
 *  
 *  Returns a copy of <i>str</i> with uppercase alphabetic characters converted
 *  to lowercase and lowercase characters converted to uppercase.
 *  Note: case conversion is effective only in ASCII region.
 *     
 *     "Hello".swapcase          #=> "hELLO"
 *     "cYbEr_PuNk11".swapcase   #=> "CyBeR_pUnK11"
 */

static VALUE
rb_str_swapcase(VALUE str)
{
    str = rb_str_dup(str);
    rb_str_swapcase_bang(str);
    return str;
}

typedef unsigned char *USTR;

struct tr {
    int gen, now, max;
    char *p, *pend;
};

static int
trnext(struct tr *t, rb_encoding *enc)
{
    for (;;) {
	if (!t->gen) {
	    if (t->p == t->pend) return -1;
	    t->now = rb_enc_codepoint(t->p, t->pend, enc);
	    t->p += rb_enc_codelen(t->now, enc);
	    if (t->p < t->pend - 1 && *t->p == '-') {
		t->p++;
		if (t->p < t->pend) {
		    int c = rb_enc_codepoint(t->p, t->pend, enc);
		    t->p += rb_enc_codelen(c, enc);
		    if (t->now > c) continue;
		    t->gen = 1;
		    t->max = c;
		}
	    }
	    return t->now;
	}
	else if (++t->now < t->max) {
	    return t->now;
	}
	else {
	    t->gen = 0;
	    return t->max;
	}
    }
}

static VALUE rb_str_delete_bang(int,VALUE*,VALUE);

static VALUE
tr_trans(VALUE str, VALUE src, VALUE repl, int sflag)
{
    SIGNED_VALUE trans[256];
    rb_encoding *enc, *e1, *e2;
    struct tr trsrc, trrepl;
    int cflag = 0;
    int c, last = 0, modify = 0, i;
    char *s, *send;
    VALUE hash = 0;

    StringValue(src);
    StringValue(repl);
    if (RSTRING_LEN(str) == 0 || !RSTRING_PTR(str)) return Qnil;
    trsrc.p = RSTRING_PTR(src); trsrc.pend = trsrc.p + RSTRING_LEN(src);
    if (RSTRING_LEN(src) >= 2 && RSTRING_PTR(src)[0] == '^') {
	cflag++;
	trsrc.p++;
    }
    if (RSTRING_LEN(repl) == 0) {
	return rb_str_delete_bang(1, &src, str);
    }
    e1 = rb_enc_check(str, src);
    e2 = rb_enc_check(str, repl);
    if (e1 == e2) {
	enc = e1;
    }
    else {
	enc = rb_enc_check(src, repl);
    }
    trrepl.p = RSTRING_PTR(repl);
    trrepl.pend = trrepl.p + RSTRING_LEN(repl);
    trsrc.gen = trrepl.gen = 0;
    trsrc.now = trrepl.now = 0;
    trsrc.max = trrepl.max = 0;

    if (cflag) {
	for (i=0; i<256; i++) {
	    trans[i] = 1;
	}
	while ((c = trnext(&trsrc, enc)) >= 0) {
	    if (c < 256) {
		trans[c] = -1;
	    }
	    else {
		if (!hash) hash = rb_hash_new();
		rb_hash_aset(hash, INT2NUM(c), Qtrue);
	    }
	}
	while ((c = trnext(&trrepl, enc)) >= 0)
	    /* retrieve last replacer */;
	last = trrepl.now;
	for (i=0; i<256; i++) {
	    if (trans[i] >= 0) {
		trans[i] = last;
	    }
	}
    }
    else {
	int r;

	for (i=0; i<256; i++) {
	    trans[i] = -1;
	}
	while ((c = trnext(&trsrc, enc)) >= 0) {
	    r = trnext(&trrepl, enc);
	    if (r == -1) r = trrepl.now;
	    if (c < 256) {
		trans[c] = INT2NUM(r);
	    }
	    else {
		if (!hash) hash = rb_hash_new();
		rb_hash_aset(hash, INT2NUM(c), INT2NUM(r));
	    }
	}
    }

    rb_str_modify(str);
    s = RSTRING_PTR(str); send = RSTRING_END(str);
    if (sflag) {
	int clen, tlen, max = RSTRING_LEN(str);
	int offset, save = -1;
	char *buf = ALLOC_N(char, max), *t = buf;
	VALUE v;

	if (cflag) tlen = rb_enc_codelen(last, enc);
	while (s < send) {
	    c = rb_enc_codepoint(s, send, enc);
	    tlen = clen = rb_enc_codelen(c, enc);

	    s += clen;
	    if (c < 256) {
		v = trans[c] >= 0 ? trans[c] : Qnil;
	    }
	    else {
		v = hash ? rb_hash_aref(hash, INT2NUM(c)) : Qnil;
	    }
	    if (!NIL_P(v)) {
		if (!cflag) {
		    c = NUM2INT(v);
		    if (save == c) continue;
		    save = c;
		    tlen = rb_enc_codelen(c, enc);
		    modify = 1;
		}
		else {
		    save = c = last;
		    modify = 1;
		}
	    }
	    else {
		save = -1;
	    }
	    while (t - buf + tlen >= max) {
		offset = t - buf;
		max *= 2;
		REALLOC_N(buf, char, max);
		t = buf + offset;
	    }
	    rb_enc_mbcput(c, t, enc);
	    t += tlen;
	}
	*t = '\0';
	RSTRING(str)->as.heap.ptr = buf;
	RSTRING(str)->as.heap.len = t - buf;
	STR_SET_NOEMBED(str);
	RSTRING(str)->as.heap.aux.capa = max;
    }
    else if (rb_enc_mbmaxlen(enc) == 1) {
	while (s < send) {
	    c = (unsigned char)*s;
	    if (trans[c] >= 0) {
		if (!cflag) {
		    c = FIX2INT(trans[c]);
		    *s = c;
		    modify = 1;
		}
		else {
		    *s = last;
		    modify = 1;
		}
	    }
	    s++;
	}
    }
    else {
	int clen, tlen, max = RSTRING_LEN(str) * 1.2;
	int offset;
	char *buf = ALLOC_N(char, max), *t = buf;
	VALUE v;

	if (cflag) tlen = rb_enc_codelen(last, enc);
	while (s < send) {
	    c = rb_enc_codepoint(s, send, enc);
	    tlen = clen = rb_enc_codelen(c, enc);

	    if (c < 256) {
		v = trans[c] >= 0 ? trans[c] : Qnil;
	    }
	    else {
		v = hash ? rb_hash_aref(hash, INT2NUM(c)) : Qnil;
	    }
	    if (!NIL_P(v)) {
		if (!cflag) {
		    c = NUM2INT(v);
		    tlen = rb_enc_codelen(c, enc);
		    modify = 1;
		}
		else {
		    c = last;
		    modify = 1;
		}
	    }
	    while (t - buf + tlen >= max) {
		offset = t - buf;
		max *= 2;
		REALLOC_N(buf, char, max);
		t = buf + offset;
	    }
	    if (s != t) rb_enc_mbcput(c, t, enc);
	    s += clen;
	    t += tlen;
	}
	if (!STR_EMBED_P(str)) {
	    free(RSTRING(str)->as.heap.ptr);
	}
	*t = '\0';
	RSTRING(str)->as.heap.ptr = buf;
	RSTRING(str)->as.heap.len = t - buf;
	STR_SET_NOEMBED(str);
	RSTRING(str)->as.heap.aux.capa = max;
    }
    
    if (modify) {
	rb_enc_associate(str, enc);
	return str;
    }
    return Qnil;
}


/*
 *  call-seq:
 *     str.tr!(from_str, to_str)   => str or nil
 *  
 *  Translates <i>str</i> in place, using the same rules as
 *  <code>String#tr</code>. Returns <i>str</i>, or <code>nil</code> if no
 *  changes were made.
 */

static VALUE
rb_str_tr_bang(VALUE str, VALUE src, VALUE repl)
{
    return tr_trans(str, src, repl, 0);
}


/*
 *  call-seq:
 *     str.tr(from_str, to_str)   => new_str
 *  
 *  Returns a copy of <i>str</i> with the characters in <i>from_str</i> replaced
 *  by the corresponding characters in <i>to_str</i>. If <i>to_str</i> is
 *  shorter than <i>from_str</i>, it is padded with its last character. Both
 *  strings may use the c1--c2 notation to denote ranges of characters, and
 *  <i>from_str</i> may start with a <code>^</code>, which denotes all
 *  characters except those listed.
 *     
 *     "hello".tr('aeiou', '*')    #=> "h*ll*"
 *     "hello".tr('^aeiou', '*')   #=> "*e**o"
 *     "hello".tr('el', 'ip')      #=> "hippo"
 *     "hello".tr('a-y', 'b-z')    #=> "ifmmp"
 */

static VALUE
rb_str_tr(VALUE str, VALUE src, VALUE repl)
{
    str = rb_str_dup(str);
    tr_trans(str, src, repl, 0);
    return str;
}

static void
tr_setup_table(VALUE str, char stable[256], int first, 
	       VALUE *tablep, VALUE *ctablep, rb_encoding *enc)
{
    char buf[256];
    struct tr tr;
    int c;
    VALUE table = 0, ptable = 0;
    int i, cflag = 0;

    tr.p = RSTRING_PTR(str); tr.pend = tr.p + RSTRING_LEN(str);
    tr.gen = tr.now = tr.max = 0;
    
    if (RSTRING_LEN(str) > 1 && RSTRING_PTR(str)[0] == '^') {
	cflag = 1;
	tr.p++;
    }
    if (first) {
	for (i=0; i<256; i++) {
	    stable[i] = 1;
	}
    }
    for (i=0; i<256; i++) {
	buf[i] = cflag;
    }

    while ((c = trnext(&tr, enc)) >= 0) {
	if (c < 256) {
	    buf[c & 0xff] = !cflag;
	}
	else {
	    VALUE key = INT2NUM(c);

	    if (!table) {
		table = rb_hash_new();
		if (cflag) {
		    ptable = *ctablep;
		    *ctablep = table;
		}
		else {
		    ptable = *tablep;
		    *tablep = table;
		}
	    }
	    if (!ptable || !NIL_P(rb_hash_aref(ptable, key))) {
		rb_hash_aset(table, key, Qtrue);
	    }
	}
    }
    for (i=0; i<256; i++) {
	stable[i] = stable[i] && buf[i];
    }
}


static int
tr_find(int c, char table[256], VALUE del, VALUE nodel)
{
    if (c < 256) {
	return table[c] ? Qtrue : Qfalse;
    }
    else {
	VALUE v = INT2NUM(c);

	if (!del || NIL_P(rb_hash_lookup(del, v))) {
	    return Qfalse;
	}
	if (nodel && NIL_P(rb_hash_lookup(nodel, v)))
	    return Qfalse;
	return Qtrue;
    }
}

/*
 *  call-seq:
 *     str.delete!([other_str]+)   => str or nil
 *  
 *  Performs a <code>delete</code> operation in place, returning <i>str</i>, or
 *  <code>nil</code> if <i>str</i> was not modified.
 */

static VALUE
rb_str_delete_bang(int argc, VALUE *argv, VALUE str)
{
    char squeez[256];
    rb_encoding *enc = 0;
    char *s, *send, *t;
    VALUE del = 0, nodel = 0;
    int modify = 0;
    int i;

    if (argc < 1) {
	rb_raise(rb_eArgError, "wrong number of arguments");
    }
    for (i=0; i<argc; i++) {
	VALUE s = argv[i];

	StringValue(s);
	enc = rb_enc_check(str, s);
	tr_setup_table(s, squeez, i==0, &del, &nodel, enc);
    }

    rb_str_modify(str);
    s = t = RSTRING_PTR(str);
    if (!s || RSTRING_LEN(str) == 0) return Qnil;
    send = RSTRING_END(str);
    while (s < send) {
	int c = rb_enc_codepoint(s, send, enc);
	int clen = rb_enc_codelen(c, enc);

	if (tr_find(c, squeez, del, nodel)) {
	    modify = 1;
	}
	else {
	    if (t != s) rb_enc_mbcput(c, t, enc);
	    t += clen;
	}
	s += clen;
    }
    *t = '\0';
    STR_SET_LEN(str, t - RSTRING_PTR(str));

    if (modify) return str;
    return Qnil;
}


/*
 *  call-seq:
 *     str.delete([other_str]+)   => new_str
 *  
 *  Returns a copy of <i>str</i> with all characters in the intersection of its
 *  arguments deleted. Uses the same rules for building the set of characters as
 *  <code>String#count</code>.
 *     
 *     "hello".delete "l","lo"        #=> "heo"
 *     "hello".delete "lo"            #=> "he"
 *     "hello".delete "aeiou", "^e"   #=> "hell"
 *     "hello".delete "ej-m"          #=> "ho"
 */

static VALUE
rb_str_delete(int argc, VALUE *argv, VALUE str)
{
    str = rb_str_dup(str);
    rb_str_delete_bang(argc, argv, str);
    return str;
}


/*
 *  call-seq:
 *     str.squeeze!([other_str]*)   => str or nil
 *  
 *  Squeezes <i>str</i> in place, returning either <i>str</i>, or
 *  <code>nil</code> if no changes were made.
 */

static VALUE
rb_str_squeeze_bang(int argc, VALUE *argv, VALUE str)
{
    char squeez[256];
    rb_encoding *enc = 0;
    VALUE del = 0, nodel = 0;
    char *s, *send, *t;
    int save, modify = 0;
    int i;

    if (argc == 0) {
	enc = rb_enc_get(str);
    }
    else {
	for (i=0; i<argc; i++) {
	    VALUE s = argv[i];

	    StringValue(s);
	    enc = rb_enc_check(str, s);
	    tr_setup_table(s, squeez, i==0, &del, &nodel, enc);
	}
    }

    rb_str_modify(str);
    s = t = RSTRING_PTR(str);
    if (!s || RSTRING_LEN(str) == 0) return Qnil;
    send = RSTRING_END(str);
    save = -1;
    while (s < send) {
	int c = rb_enc_codepoint(s, send, enc);
	int clen = rb_enc_codelen(c, enc);

	if (c != save || (argc > 0 && !tr_find(c, squeez, del, nodel))) {
	    if (t != s) rb_enc_mbcput(c, t, enc);
	    save = c;
	    t += clen;
	}
	s += clen;
    }
    *t = '\0';
    if (t - RSTRING_PTR(str) != RSTRING_LEN(str)) {
	STR_SET_LEN(str, t - RSTRING_PTR(str));
	modify = 1;
    }

    if (modify) return str;
    return Qnil;
}


/*
 *  call-seq:
 *     str.squeeze([other_str]*)    => new_str
 *  
 *  Builds a set of characters from the <i>other_str</i> parameter(s) using the
 *  procedure described for <code>String#count</code>. Returns a new string
 *  where runs of the same character that occur in this set are replaced by a
 *  single character. If no arguments are given, all runs of identical
 *  characters are replaced by a single character.
 *     
 *     "yellow moon".squeeze                  #=> "yelow mon"
 *     "  now   is  the".squeeze(" ")         #=> " now is the"
 *     "putters shoot balls".squeeze("m-z")   #=> "puters shot balls"
 */

static VALUE
rb_str_squeeze(int argc, VALUE *argv, VALUE str)
{
    str = rb_str_dup(str);
    rb_str_squeeze_bang(argc, argv, str);
    return str;
}


/*
 *  call-seq:
 *     str.tr_s!(from_str, to_str)   => str or nil
 *  
 *  Performs <code>String#tr_s</code> processing on <i>str</i> in place,
 *  returning <i>str</i>, or <code>nil</code> if no changes were made.
 */

static VALUE
rb_str_tr_s_bang(VALUE str, VALUE src, VALUE repl)
{
    return tr_trans(str, src, repl, 1);
}


/*
 *  call-seq:
 *     str.tr_s(from_str, to_str)   => new_str
 *  
 *  Processes a copy of <i>str</i> as described under <code>String#tr</code>,
 *  then removes duplicate characters in regions that were affected by the
 *  translation.
 *     
 *     "hello".tr_s('l', 'r')     #=> "hero"
 *     "hello".tr_s('el', '*')    #=> "h*o"
 *     "hello".tr_s('el', 'hx')   #=> "hhxo"
 */

static VALUE
rb_str_tr_s(VALUE str, VALUE src, VALUE repl)
{
    str = rb_str_dup(str);
    tr_trans(str, src, repl, 1);
    return str;
}


/*
 *  call-seq:
 *     str.count([other_str]+)   => fixnum
 *  
 *  Each <i>other_str</i> parameter defines a set of characters to count.  The
 *  intersection of these sets defines the characters to count in
 *  <i>str</i>. Any <i>other_str</i> that starts with a caret (^) is
 *  negated. The sequence c1--c2 means all characters between c1 and c2.
 *     
 *     a = "hello world"
 *     a.count "lo"            #=> 5
 *     a.count "lo", "o"       #=> 2
 *     a.count "hello", "^l"   #=> 4
 *     a.count "ej-m"          #=> 4
 */

static VALUE
rb_str_count(int argc, VALUE *argv, VALUE str)
{
    char table[256];
    rb_encoding *enc = 0;
    VALUE del = 0, nodel = 0;
    char *s, *send;
    int i;

    if (argc < 1) {
	rb_raise(rb_eArgError, "wrong number of arguments");
    }
    for (i=0; i<argc; i++) {
	VALUE s = argv[i];

	StringValue(s);
	enc = rb_enc_check(str, s);
	tr_setup_table(s, table,i==0, &del, &nodel, enc);
    }

    s = RSTRING_PTR(str);
    if (!s || RSTRING_LEN(str) == 0) return INT2FIX(0);
    send = RSTRING_END(str);
    i = 0;
    while (s < send) {
	int c = rb_enc_codepoint(s, send, enc);
	int clen = rb_enc_codelen(c, enc);

	if (tr_find(c, table, del, nodel)) {
	    i++;
	}
	s += clen;
    }
    return INT2NUM(i);
}


/*
 *  call-seq:
 *     str.split(pattern=$;, [limit])   => anArray
 *  
 *  Divides <i>str</i> into substrings based on a delimiter, returning an array
 *  of these substrings.
 *     
 *  If <i>pattern</i> is a <code>String</code>, then its contents are used as
 *  the delimiter when splitting <i>str</i>. If <i>pattern</i> is a single
 *  space, <i>str</i> is split on whitespace, with leading whitespace and runs
 *  of contiguous whitespace characters ignored.
 *     
 *  If <i>pattern</i> is a <code>Regexp</code>, <i>str</i> is divided where the
 *  pattern matches. Whenever the pattern matches a zero-length string,
 *  <i>str</i> is split into individual characters. If <i>pattern</i> contains
 *  groups, the respective matches will be returned in the array as well.
 *     
 *  If <i>pattern</i> is omitted, the value of <code>$;</code> is used.  If
 *  <code>$;</code> is <code>nil</code> (which is the default), <i>str</i> is
 *  split on whitespace as if ` ' were specified.
 *     
 *  If the <i>limit</i> parameter is omitted, trailing null fields are
 *  suppressed. If <i>limit</i> is a positive number, at most that number of
 *  fields will be returned (if <i>limit</i> is <code>1</code>, the entire
 *  string is returned as the only entry in an array). If negative, there is no
 *  limit to the number of fields returned, and trailing null fields are not
 *  suppressed.
 *     
 *     " now's  the time".split        #=> ["now's", "the", "time"]
 *     " now's  the time".split(' ')   #=> ["now's", "the", "time"]
 *     " now's  the time".split(/ /)   #=> ["", "now's", "", "the", "time"]
 *     "1, 2.34,56, 7".split(%r{,\s*}) #=> ["1", "2.34", "56", "7"]
 *     "hello".split(//)               #=> ["h", "e", "l", "l", "o"]
 *     "hello".split(//, 3)            #=> ["h", "e", "llo"]
 *     "hi mom".split(%r{\s*})         #=> ["h", "i", "m", "o", "m"]
 *     
 *     "mellow yellow".split("ello")   #=> ["m", "w y", "w"]
 *     "1,2,,3,4,,".split(',')         #=> ["1", "2", "", "3", "4"]
 *     "1,2,,3,4,,".split(',', 4)      #=> ["1", "2", "", "3,4,,"]
 *     "1,2,,3,4,,".split(',', -4)     #=> ["1", "2", "", "3", "4", "", ""]
 */

static VALUE
rb_str_split_m(int argc, VALUE *argv, VALUE str)
{
    rb_encoding *enc;
    VALUE spat;
    VALUE limit;
    int awk_split = Qfalse;
    long beg, end, i = 0;
    int lim = 0;
    VALUE result, tmp;

    if (rb_scan_args(argc, argv, "02", &spat, &limit) == 2) {
	lim = NUM2INT(limit);
	if (lim <= 0) limit = Qnil;
	else if (lim == 1) {
	    if (RSTRING_LEN(str) == 0)
		return rb_ary_new2(0);
	    return rb_ary_new3(1, str);
	}
	i = 1;
    }

    enc = rb_enc_get(str);
    if (NIL_P(spat)) {
	if (!NIL_P(rb_fs)) {
	    spat = rb_fs;
	    goto fs_set;
	}
	awk_split = Qtrue;
    }
    else {
      fs_set:
	if (TYPE(spat) == T_STRING && RSTRING_LEN(spat) == 1) {
	    if (RSTRING_PTR(spat)[0] == ' ') {
		awk_split = Qtrue;
	    }
	    else {
		spat = rb_reg_regcomp(rb_reg_quote(spat));
	    }
	}
	else {
	    spat = get_pat(spat, 1);
	}
    }

    result = rb_ary_new();
    beg = 0;
    if (awk_split) {
	char *ptr = RSTRING_PTR(str);
	char *eptr = RSTRING_END(str);
	char *bptr = ptr;
	int skip = 1;
	int c;

	end = beg;
	while (ptr < eptr) {
	    c = rb_enc_codepoint(ptr, eptr, enc);
	    ptr += rb_enc_mbclen(ptr, eptr, enc);
	    if (skip) {
		if (rb_enc_isspace(c, enc)) {
		    beg = ptr - bptr;
		}
		else {
		    end = ptr - bptr;
		    skip = 0;
		    if (!NIL_P(limit) && lim <= i) break;
		}
	    }
	    else {
		if (rb_enc_isspace(c, enc)) {
		    rb_ary_push(result, rb_str_subseq(str, beg, end-beg));
		    skip = 1;
		    beg = ptr - bptr;
		    if (!NIL_P(limit)) ++i;
		}
		else {
		    end = ptr - bptr;
		}
	    }
	}
    }
    else {
	long start = beg;
	long idx;
	int last_null = 0;
	struct re_registers *regs;

	while ((end = rb_reg_search(spat, str, start, 0)) >= 0) {
	    regs = RMATCH(rb_backref_get())->regs;
	    if (start == end && BEG(0) == END(0)) {
		if (!RSTRING_PTR(str)) {
		    rb_ary_push(result, rb_str_new("", 0));
		    break;
		}
		else if (last_null == 1) {
		    rb_ary_push(result, rb_str_subseq(str, beg,
						      rb_enc_mbclen(RSTRING_PTR(str)+beg,
								    RSTRING_END(str),
								    enc)));
		    beg = start;
		}
		else {
                    if (RSTRING_PTR(str)+start == RSTRING_END(str))
                        start++;
                    else
                        start += rb_enc_mbclen(RSTRING_PTR(str)+start,RSTRING_END(str),enc);
		    last_null = 1;
		    continue;
		}
	    }
	    else {
		rb_ary_push(result, rb_str_subseq(str, beg, end-beg));
		beg = start = END(0);
	    }
	    last_null = 0;

	    for (idx=1; idx < regs->num_regs; idx++) {
		if (BEG(idx) == -1) continue;
		if (BEG(idx) == END(idx))
		    tmp = rb_str_new5(str, 0, 0);
		else
		    tmp = rb_str_subseq(str, BEG(idx), END(idx)-BEG(idx));
		rb_ary_push(result, tmp);
	    }
	    if (!NIL_P(limit) && lim <= ++i) break;
	}
    }
    if (RSTRING_LEN(str) > 0 && (!NIL_P(limit) || RSTRING_LEN(str) > beg || lim < 0)) {
	if (RSTRING_LEN(str) == beg)
	    tmp = rb_str_new5(str, 0, 0);
	else
	    tmp = rb_str_subseq(str, beg, RSTRING_LEN(str)-beg);
	rb_ary_push(result, tmp);
    }
    if (NIL_P(limit) && lim == 0) {
	while (RARRAY_LEN(result) > 0 &&
	       RSTRING_LEN(RARRAY_PTR(result)[RARRAY_LEN(result)-1]) == 0)
	    rb_ary_pop(result);
    }

    return result;
}

VALUE
rb_str_split(VALUE str, const char *sep0)
{
    VALUE sep;

    StringValue(str);
    sep = rb_str_new2(sep0);
    return rb_str_split_m(1, &sep, str);
}


/*
 *  Document-method: lines
 *  call-seq:
 *     str.lines(separator=$/)   => anEnumerator
 *     str.lines(separator=$/) {|substr| block }        => str
 *  
 *  Returns an enumerator that gives each line in the string.  If a block is
 *  given, it iterates over each line in the string.
 *     
 *     "foo\nbar\n".lines.to_a   #=> ["foo\n", "bar\n"]
 *     "foo\nb ar".lines.sort    #=> ["b ar", "foo\n"]
 */

/*
 *  Document-method: each_line
 *  call-seq:
 *     str.each_line(separator=$/) {|substr| block }   => str
 *  
 *  Splits <i>str</i> using the supplied parameter as the record separator
 *  (<code>$/</code> by default), passing each substring in turn to the supplied
 *  block. If a zero-length record separator is supplied, the string is split on
 *  <code>\n</code> characters, except that multiple successive newlines are
 *  appended together.
 *     
 *     print "Example one\n"
 *     "hello\nworld".each {|s| p s}
 *     print "Example two\n"
 *     "hello\nworld".each('l') {|s| p s}
 *     print "Example three\n"
 *     "hello\n\n\nworld".each('') {|s| p s}
 *     
 *  <em>produces:</em>
 *     
 *     Example one
 *     "hello\n"
 *     "world"
 *     Example two
 *     "hel"
 *     "l"
 *     "o\nworl"
 *     "d"
 *     Example three
 *     "hello\n\n\n"
 *     "world"
 */

static VALUE
rb_str_each_line(int argc, VALUE *argv, VALUE str)
{
    rb_encoding *enc;
    VALUE rs;
    int newline;
    char *p = RSTRING_PTR(str), *pend = p + RSTRING_LEN(str), *s = p;
    char *ptr = p;
    long len = RSTRING_LEN(str), rslen;
    VALUE line;

    if (rb_scan_args(argc, argv, "01", &rs) == 0) {
	rs = rb_rs;
    }
    RETURN_ENUMERATOR(str, argc, argv);

    if (NIL_P(rs)) {
	rb_yield(str);
	return str;
    }
    StringValue(rs);
    enc = rb_enc_check(str, rs);
    rslen = RSTRING_LEN(rs);
    if (rslen == 0) {
	newline = '\n';
    }
    else {
	newline = rb_enc_codepoint(RSTRING_PTR(rs), RSTRING_END(rs), enc);
    }

    while (p < pend) {
	int c = rb_enc_codepoint(p, pend, enc);
	int n = rb_enc_codelen(c, enc);

	if (rslen == 0 && c == newline) {
	    while (p < pend && rb_enc_codepoint(p, pend, enc) == newline) {
		p += n;
	    }
	    p -= n;
	}
	if (c == newline &&
	    (rslen <= 1 || memcmp(RSTRING_PTR(rs), p, rslen) == 0)) {
	    line = rb_str_new5(str, s, p - s + (rslen ? rslen : n));
	    OBJ_INFECT(line, str);
	    rb_enc_copy(line, str);
	    rb_yield(line);
	    str_mod_check(str, ptr, len);
	    s = p + (rslen ? rslen : n);
	}
	p += n;
    }

    if (s != pend) {
	if (p > pend) p = pend;
	line = rb_str_new5(str, s, p - s);
	OBJ_INFECT(line, str);
	rb_enc_copy(line, str);
	rb_yield(line);
    }

    return str;
}


/*
 *  Document-method: bytes
 *  call-seq:
 *     str.bytes   => anEnumerator
 *     str.bytes {|fixnum| block }    => str
 *  
 *  Returns an enumerator that gives each byte in the string.  If a block is
 *  given, it iterates over each byte in the string.
 *     
 *     "hello".bytes.to_a        #=> [104, 101, 108, 108, 111]
 */

/*
 *  Document-method: each_byte
 *  call-seq:
 *     str.each_byte {|fixnum| block }    => str
 *  
 *  Passes each byte in <i>str</i> to the given block.
 *     
 *     "hello".each_byte {|c| print c, ' ' }
 *     
 *  <em>produces:</em>
 *     
 *     104 101 108 108 111
 */

static VALUE
rb_str_each_byte(VALUE str)
{
    long i;

    RETURN_ENUMERATOR(str, 0, 0);
    for (i=0; i<RSTRING_LEN(str); i++) {
	rb_yield(INT2FIX(RSTRING_PTR(str)[i] & 0xff));
    }
    return str;
}


/*
 *  Document-method: chars
 *  call-seq:
 *     str.chars                   => anEnumerator
 *     str.chars {|substr| block } => str
 *  
 *  Returns an enumerator that gives each character in the string.
 *  If a block is given, it iterates over each character in the string.
 *     
 *     "foo".chars.to_a   #=> ["f","o","o"]
 */

/*
 *  Document-method: each_char
 *  call-seq:
 *     str.each_char {|cstr| block }    => str
 *  
 *  Passes each character in <i>str</i> to the given block.
 *     
 *     "hello".each_char {|c| print c, ' ' }
 *     
 *  <em>produces:</em>
 *     
 *     h e l l o 
 */

static VALUE
rb_str_each_char(VALUE str)
{
    int i, len = str_strlen(str, 0);

    RETURN_ENUMERATOR(str, 0, 0);
    for (i=0; i<len; i++) {
	rb_yield(rb_str_substr(str, i, 1));
    }
    return str;
}

static long
chopped_length(VALUE str)
{
    rb_encoding *enc = rb_enc_get(str);
    const char *p, *p2, *beg, *end;

    beg = RSTRING_PTR(str);
    end = beg + RSTRING_LEN(str);
    if (beg > end) return 0;
    p = rb_enc_prev_char(beg, end, enc);
    if (!p) return 0;
    if (p > beg && rb_enc_codepoint(p, end, enc) == '\n') {
	p2 = rb_enc_prev_char(beg, p, enc);
	if (p2 && rb_enc_codepoint(p2, end, enc) == '\r') p = p2;
    }
    return p - beg;
}

/*
 *  call-seq:
 *     str.chop!   => str or nil
 *  
 *  Processes <i>str</i> as for <code>String#chop</code>, returning <i>str</i>,
 *  or <code>nil</code> if <i>str</i> is the empty string.  See also
 *  <code>String#chomp!</code>.
 */

static VALUE
rb_str_chop_bang(VALUE str)
{
    if (RSTRING_LEN(str) > 0) {
	long len;
	rb_str_modify(str);
	len = chopped_length(str);
	STR_SET_LEN(str, len);
	RSTRING_PTR(str)[len] = '\0';
	return str;
    }
    return Qnil;
}


/*
 *  call-seq:
 *     str.chop   => new_str
 *  
 *  Returns a new <code>String</code> with the last character removed.  If the
 *  string ends with <code>\r\n</code>, both characters are removed. Applying
 *  <code>chop</code> to an empty string returns an empty
 *  string. <code>String#chomp</code> is often a safer alternative, as it leaves
 *  the string unchanged if it doesn't end in a record separator.
 *     
 *     "string\r\n".chop   #=> "string"
 *     "string\n\r".chop   #=> "string\n"
 *     "string\n".chop     #=> "string"
 *     "string".chop       #=> "strin"
 *     "x".chop.chop       #=> ""
 */

static VALUE
rb_str_chop(VALUE str)
{
    VALUE str2 = rb_str_new5(str, RSTRING_PTR(str), chopped_length(str));
    rb_enc_copy(str2, str);
    OBJ_INFECT(str2, str);
    return str2;
}


/*
 *  call-seq:
 *     str.chomp!(separator=$/)   => str or nil
 *  
 *  Modifies <i>str</i> in place as described for <code>String#chomp</code>,
 *  returning <i>str</i>, or <code>nil</code> if no modifications were made.
 */

static VALUE
rb_str_chomp_bang(int argc, VALUE *argv, VALUE str)
{
    rb_encoding *enc;
    VALUE rs;
    int newline;
    char *p, *pp, *e;
    long len, rslen;

    if (rb_scan_args(argc, argv, "01", &rs) == 0) {
	len = RSTRING_LEN(str);
	if (len == 0) return Qnil;
	p = RSTRING_PTR(str);
	rs = rb_rs;
	if (rs == rb_default_rs) {
	  smart_chomp:
	    rb_str_modify(str);
	    if (RSTRING_PTR(str)[len-1] == '\n') {
		STR_DEC_LEN(str);
		if (RSTRING_LEN(str) > 0 &&
		    RSTRING_PTR(str)[RSTRING_LEN(str)-1] == '\r') {
		    STR_DEC_LEN(str);
		}
	    }
	    else if (RSTRING_PTR(str)[len-1] == '\r') {
		STR_DEC_LEN(str);
	    }
	    else {
		return Qnil;
	    }
	    RSTRING_PTR(str)[RSTRING_LEN(str)] = '\0';
	    return str;
	}
    }
    if (NIL_P(rs)) return Qnil;
    StringValue(rs);
    enc = rb_enc_check(str, rs);
    len = RSTRING_LEN(str);
    if (len == 0) return Qnil;
    p = RSTRING_PTR(str);
    rslen = RSTRING_LEN(rs);
    if (rslen == 0) {
	while (len>0 && p[len-1] == '\n') {
	    len--;
	    if (len>0 && p[len-1] == '\r')
		len--;
	}
	if (len < RSTRING_LEN(str)) {
	    rb_str_modify(str);
	    STR_SET_LEN(str, len);
	    RSTRING_PTR(str)[len] = '\0';
	    return str;
	}
	return Qnil;
    }
    if (rslen > len) return Qnil;
    newline = RSTRING_PTR(rs)[rslen-1];
    if (rslen == 1 && newline == '\n')
	goto smart_chomp;

    if (is_broken_string(rs)) {
	return Qnil;
    }
    e = p + len;
    pp = e - rslen;
    if (p[len-1] == newline &&
	(rslen <= 1 ||
	 memcmp(RSTRING_PTR(rs), pp, rslen) == 0)) {
	if (rb_enc_left_char_head(p, pp, enc) != pp)
	    return Qnil;
	rb_str_modify(str);
	STR_SET_LEN(str, RSTRING_LEN(str) - rslen);
	RSTRING_PTR(str)[RSTRING_LEN(str)] = '\0';
	return str;
    }
    return Qnil;
}


/*
 *  call-seq:
 *     str.chomp(separator=$/)   => new_str
 *  
 *  Returns a new <code>String</code> with the given record separator removed
 *  from the end of <i>str</i> (if present). If <code>$/</code> has not been
 *  changed from the default Ruby record separator, then <code>chomp</code> also
 *  removes carriage return characters (that is it will remove <code>\n</code>,
 *  <code>\r</code>, and <code>\r\n</code>).
 *     
 *     "hello".chomp            #=> "hello"
 *     "hello\n".chomp          #=> "hello"
 *     "hello\r\n".chomp        #=> "hello"
 *     "hello\n\r".chomp        #=> "hello\n"
 *     "hello\r".chomp          #=> "hello"
 *     "hello \n there".chomp   #=> "hello \n there"
 *     "hello".chomp("llo")     #=> "he"
 */

static VALUE
rb_str_chomp(int argc, VALUE *argv, VALUE str)
{
    str = rb_str_dup(str);
    rb_str_chomp_bang(argc, argv, str);
    return str;
}

/*
 *  call-seq:
 *     str.lstrip!   => self or nil
 *  
 *  Removes leading whitespace from <i>str</i>, returning <code>nil</code> if no
 *  change was made. See also <code>String#rstrip!</code> and
 *  <code>String#strip!</code>.
 *     
 *     "  hello  ".lstrip   #=> "hello  "
 *     "hello".lstrip!      #=> nil
 */

static VALUE
rb_str_lstrip_bang(VALUE str)
{
    rb_encoding *enc;
    char *s, *t, *e;

    rb_str_modify(str);
    enc = rb_enc_get(str);
    s = RSTRING_PTR(str);
    if (!s || RSTRING_LEN(str) == 0) return Qnil;
    e = t = RSTRING_END(str);
    /* remove spaces at head */
    while (s < e) {
	int cc = rb_enc_codepoint(s, e, enc);
	
	if (!rb_enc_isspace(cc, enc)) break;
	s += rb_enc_codelen(cc, enc);
    }

    if (s > RSTRING_PTR(str)) {
	rb_str_modify(str);
	STR_SET_LEN(str, t-s);
	memmove(RSTRING_PTR(str), s, RSTRING_LEN(str));
	RSTRING_PTR(str)[RSTRING_LEN(str)] = '\0';
	return str;
    }
    return Qnil;
}


/*
 *  call-seq:
 *     str.lstrip   => new_str
 *  
 *  Returns a copy of <i>str</i> with leading whitespace removed. See also
 *  <code>String#rstrip</code> and <code>String#strip</code>.
 *     
 *     "  hello  ".lstrip   #=> "hello  "
 *     "hello".lstrip       #=> "hello"
 */

static VALUE
rb_str_lstrip(VALUE str)
{
    str = rb_str_dup(str);
    rb_str_lstrip_bang(str);
    return str;
}


/*
 *  call-seq:
 *     str.rstrip!   => self or nil
 *  
 *  Removes trailing whitespace from <i>str</i>, returning <code>nil</code> if
 *  no change was made. See also <code>String#lstrip!</code> and
 *  <code>String#strip!</code>.
 *     
 *     "  hello  ".rstrip   #=> "  hello"
 *     "hello".rstrip!      #=> nil
 */

static VALUE
rb_str_rstrip_bang(VALUE str)
{
    rb_encoding *enc;
    char *s, *t, *e;
    int space_seen = Qfalse;

    rb_str_modify(str);
    enc = rb_enc_get(str);
    s = RSTRING_PTR(str);
    if (!s || RSTRING_LEN(str) == 0) return Qnil;
    t = e = RSTRING_END(str);
    while (s < e) {
	int cc = rb_enc_codepoint(s, e, enc);

	if (!cc || rb_enc_isspace(cc, enc)) {
	    if (!space_seen) t = s;
	    space_seen = Qtrue;
	}
	else {
	    space_seen = Qfalse;
	}
	s += rb_enc_codelen(cc, enc);
    }
    if (!space_seen) t = s;
    if (t < e) {
	rb_str_modify(str);
	STR_SET_LEN(str, t-RSTRING_PTR(str));
	RSTRING_PTR(str)[RSTRING_LEN(str)] = '\0';
	return str;
    }
    return Qnil;
}


/*
 *  call-seq:
 *     str.rstrip   => new_str
 *  
 *  Returns a copy of <i>str</i> with trailing whitespace removed. See also
 *  <code>String#lstrip</code> and <code>String#strip</code>.
 *     
 *     "  hello  ".rstrip   #=> "  hello"
 *     "hello".rstrip       #=> "hello"
 */

static VALUE
rb_str_rstrip(VALUE str)
{
    str = rb_str_dup(str);
    rb_str_rstrip_bang(str);
    return str;
}


/*
 *  call-seq:
 *     str.strip!   => str or nil
 *  
 *  Removes leading and trailing whitespace from <i>str</i>. Returns
 *  <code>nil</code> if <i>str</i> was not altered.
 */

static VALUE
rb_str_strip_bang(VALUE str)
{
    VALUE l = rb_str_lstrip_bang(str);
    VALUE r = rb_str_rstrip_bang(str);

    if (NIL_P(l) && NIL_P(r)) return Qnil;
    return str;
}


/*
 *  call-seq:
 *     str.strip   => new_str
 *  
 *  Returns a copy of <i>str</i> with leading and trailing whitespace removed.
 *     
 *     "    hello    ".strip   #=> "hello"
 *     "\tgoodbye\r\n".strip   #=> "goodbye"
 */

static VALUE
rb_str_strip(VALUE str)
{
    str = rb_str_dup(str);
    rb_str_strip_bang(str);
    return str;
}

static VALUE
scan_once(VALUE str, VALUE pat, long *start)
{
    rb_encoding *enc;
    VALUE result, match;
    struct re_registers *regs;
    long i;

    enc = rb_enc_get(str);
    if (rb_reg_search(pat, str, *start, 0) >= 0) {
	match = rb_backref_get();
	regs = RMATCH(match)->regs;
	if (BEG(0) == END(0)) {
	    /*
	     * Always consume at least one character of the input string
	     */
	    if (RSTRING_LEN(str) > END(0))
		*start = END(0)+rb_enc_mbclen(RSTRING_PTR(str)+END(0),
					      RSTRING_END(str), enc);
	    else
		*start = END(0)+1;
	}
	else {
	    *start = END(0);
	}
	if (regs->num_regs == 1) {
	    return rb_reg_nth_match(0, match);
	}
	result = rb_ary_new2(regs->num_regs);
	for (i=1; i < regs->num_regs; i++) {
	    rb_ary_push(result, rb_reg_nth_match(i, match));
	}

	return result;
    }
    return Qnil;
}


/*
 *  call-seq:
 *     str.scan(pattern)                         => array
 *     str.scan(pattern) {|match, ...| block }   => str
 *  
 *  Both forms iterate through <i>str</i>, matching the pattern (which may be a
 *  <code>Regexp</code> or a <code>String</code>). For each match, a result is
 *  generated and either added to the result array or passed to the block. If
 *  the pattern contains no groups, each individual result consists of the
 *  matched string, <code>$&</code>.  If the pattern contains groups, each
 *  individual result is itself an array containing one entry per group.
 *     
 *     a = "cruel world"
 *     a.scan(/\w+/)        #=> ["cruel", "world"]
 *     a.scan(/.../)        #=> ["cru", "el ", "wor"]
 *     a.scan(/(...)/)      #=> [["cru"], ["el "], ["wor"]]
 *     a.scan(/(..)(..)/)   #=> [["cr", "ue"], ["l ", "wo"]]
 *     
 *  And the block form:
 *     
 *     a.scan(/\w+/) {|w| print "<<#{w}>> " }
 *     print "\n"
 *     a.scan(/(.)(.)/) {|x,y| print y, x }
 *     print "\n"
 *     
 *  <em>produces:</em>
 *     
 *     <<cruel>> <<world>>
 *     rceu lowlr
 */

static VALUE
rb_str_scan(VALUE str, VALUE pat)
{
    VALUE result;
    long start = 0;
    VALUE match = Qnil;
    char *p = RSTRING_PTR(str); long len = RSTRING_LEN(str);

    pat = get_pat(pat, 1);
    if (!rb_block_given_p()) {
	VALUE ary = rb_ary_new();

	while (!NIL_P(result = scan_once(str, pat, &start))) {
	    match = rb_backref_get();
	    rb_ary_push(ary, result);
	}
	rb_backref_set(match);
	return ary;
    }

    while (!NIL_P(result = scan_once(str, pat, &start))) {
	match = rb_backref_get();
	rb_match_busy(match);
	rb_yield(result);
	str_mod_check(str, p, len);
	rb_backref_set(match);	/* restore $~ value */
    }
    rb_backref_set(match);
    return str;
}


/*
 *  call-seq:
 *     str.hex   => integer
 *  
 *  Treats leading characters from <i>str</i> as a string of hexadecimal digits
 *  (with an optional sign and an optional <code>0x</code>) and returns the
 *  corresponding number. Zero is returned on error.
 *     
 *     "0x0a".hex     #=> 10
 *     "-1234".hex    #=> -4660
 *     "0".hex        #=> 0
 *     "wombat".hex   #=> 0
 */

static VALUE
rb_str_hex(VALUE str)
{
    return rb_str_to_inum(str, 16, Qfalse);
}


/*
 *  call-seq:
 *     str.oct   => integer
 *  
 *  Treats leading characters of <i>str</i> as a string of octal digits (with an
 *  optional sign) and returns the corresponding number.  Returns 0 if the
 *  conversion fails.
 *     
 *     "123".oct       #=> 83
 *     "-377".oct      #=> -255
 *     "bad".oct       #=> 0
 *     "0377bad".oct   #=> 255
 */

static VALUE
rb_str_oct(VALUE str)
{
    return rb_str_to_inum(str, -8, Qfalse);
}


/*
 *  call-seq:
 *     str.crypt(other_str)   => new_str
 *  
 *  Applies a one-way cryptographic hash to <i>str</i> by invoking the standard
 *  library function <code>crypt</code>. The argument is the salt string, which
 *  should be two characters long, each character drawn from
 *  <code>[a-zA-Z0-9./]</code>.
 */

static VALUE
rb_str_crypt(VALUE str, VALUE salt)
{
    extern char *crypt(const char *, const char *);
    VALUE result;
    const char *s;

    StringValue(salt);
    if (RSTRING_LEN(salt) < 2)
	rb_raise(rb_eArgError, "salt too short (need >=2 bytes)");

    if (RSTRING_PTR(str)) s = RSTRING_PTR(str);
    else s = "";
    result = rb_str_new2(crypt(s, RSTRING_PTR(salt)));
    OBJ_INFECT(result, str);
    OBJ_INFECT(result, salt);
    return result;
}


/*
 *  call-seq:
 *     str.intern   => symbol
 *     str.to_sym   => symbol
 *  
 *  Returns the <code>Symbol</code> corresponding to <i>str</i>, creating the
 *  symbol if it did not previously exist. See <code>Symbol#id2name</code>.
 *     
 *     "Koala".intern         #=> :Koala
 *     s = 'cat'.to_sym       #=> :cat
 *     s == :cat              #=> true
 *     s = '@cat'.to_sym      #=> :@cat
 *     s == :@cat             #=> true
 *
 *  This can also be used to create symbols that cannot be represented using the
 *  <code>:xxx</code> notation.
 *     
 *     'cat and dog'.to_sym   #=> :"cat and dog"
 */

VALUE
rb_str_intern(VALUE s)
{
    VALUE str = RB_GC_GUARD(s);
    ID id;

    if (OBJ_TAINTED(str) && rb_safe_level() >= 1) {
	rb_raise(rb_eSecurityError, "Insecure: can't intern tainted string");
    }
    id = rb_intern_str(str);
    return ID2SYM(id);
}


/*
 *  call-seq:
 *     str.ord   => integer
 *  
 *  Return the <code>Integer</code> ordinal of a one-character string.
 *     
 *     "a".ord         #=> 97
 */

VALUE
rb_str_ord(VALUE s)
{
    int c;

    c = rb_enc_codepoint(RSTRING_PTR(s), RSTRING_END(s), rb_enc_get(s));
    return INT2NUM(c);
}
/*
 *  call-seq:
 *     str.sum(n=16)   => integer
 *  
 *  Returns a basic <em>n</em>-bit checksum of the characters in <i>str</i>,
 *  where <em>n</em> is the optional <code>Fixnum</code> parameter, defaulting
 *  to 16. The result is simply the sum of the binary value of each character in
 *  <i>str</i> modulo <code>2n - 1</code>. This is not a particularly good
 *  checksum.
 */

static VALUE
rb_str_sum(int argc, VALUE *argv, VALUE str)
{
    VALUE vbits;
    int bits;
    char *ptr, *p, *pend;
    long len;

    if (rb_scan_args(argc, argv, "01", &vbits) == 0) {
	bits = 16;
    }
    else bits = NUM2INT(vbits);

    ptr = p = RSTRING_PTR(str);
    len = RSTRING_LEN(str);
    pend = p + len;
    if (bits >= sizeof(long)*CHAR_BIT) {
	VALUE sum = INT2FIX(0);

	while (p < pend) {
	    str_mod_check(str, ptr, len);
	    sum = rb_funcall(sum, '+', 1, INT2FIX((unsigned char)*p));
	    p++;
	}
	if (bits != 0) {
	    VALUE mod;

	    mod = rb_funcall(INT2FIX(1), rb_intern("<<"), 1, INT2FIX(bits));
	    mod = rb_funcall(mod, '-', 1, INT2FIX(1));
	    sum = rb_funcall(sum, '&', 1, mod);
	}
	return sum;
    }
    else {
       unsigned long sum = 0;

	while (p < pend) {
	    str_mod_check(str, ptr, len);
	    sum += (unsigned char)*p;
	    p++;
	}
	if (bits != 0) {
           sum &= (((unsigned long)1)<<bits)-1;
	}
	return rb_int2inum(sum);
    }
}

static VALUE
rb_str_justify(int argc, VALUE *argv, VALUE str, char jflag)
{
    rb_encoding *enc;
    VALUE w;
    long width, len, flen = 1, fclen = 1;
    VALUE res;
    char *p, *f = " ";
    long n, llen, rlen;
    volatile VALUE pad;
    int asc = 1;

    rb_scan_args(argc, argv, "11", &w, &pad);
    enc = rb_enc_get(str);
    width = NUM2LONG(w);
    if (argc == 2) {
	StringValue(pad);
	enc = rb_enc_check(str, pad);
	f = RSTRING_PTR(pad);
	flen = RSTRING_LEN(pad);
	fclen = str_strlen(pad, enc);
	asc = is_ascii_string(pad);
	if (flen == 0) {
	    rb_raise(rb_eArgError, "zero width padding");
	}
    }
    len = str_strlen(str, enc);
    if (width < 0 || len >= width) return rb_str_dup(str);
    n = width - len;
    llen = (jflag == 'l') ? 0 : ((jflag == 'r') ? n : n/2);
    rlen = n - llen;
    res = rb_str_new5(str, 0, RSTRING_LEN(str)+n*flen/fclen+2);
    p = RSTRING_PTR(res);
    while (llen) {
	if (flen <= 1) {
	    *p++ = *f;
	    llen--;
	}
	else if (llen > fclen) {
	    memcpy(p,f,flen);
	    p += flen;
	    llen -= fclen;
	}
	else {
	    char *fp = str_nth(f, f+flen, llen, enc, asc);
	    n = fp - f;
	    memcpy(p,f,n);
	    p+=n;
	    break;
	}
    }
    memcpy(p, RSTRING_PTR(str), RSTRING_LEN(str));
    p+=RSTRING_LEN(str);
    while (rlen) {
	if (flen <= 1) {
	    *p++ = *f;
	    rlen--;
	}
	else if (rlen > fclen) {
	    memcpy(p,f,flen);
	    p += flen;
	    rlen -= fclen;
	}
	else {
	    char *fp = str_nth(f, f+flen, rlen, enc, asc);
	    n = fp - f;
	    memcpy(p,f,n);
	    p+=n;
	    break;
	}
    }
    *p = '\0';
    STR_SET_LEN(res, p-RSTRING_PTR(res));
    OBJ_INFECT(res, str);
    if (!NIL_P(pad)) OBJ_INFECT(res, pad);
    rb_enc_associate(res, enc);
    return res;
}


/*
 *  call-seq:
 *     str.ljust(integer, padstr=' ')   => new_str
 *  
 *  If <i>integer</i> is greater than the length of <i>str</i>, returns a new
 *  <code>String</code> of length <i>integer</i> with <i>str</i> left justified
 *  and padded with <i>padstr</i>; otherwise, returns <i>str</i>.
 *     
 *     "hello".ljust(4)            #=> "hello"
 *     "hello".ljust(20)           #=> "hello               "
 *     "hello".ljust(20, '1234')   #=> "hello123412341234123"
 */

static VALUE
rb_str_ljust(int argc, VALUE *argv, VALUE str)
{
    return rb_str_justify(argc, argv, str, 'l');
}


/*
 *  call-seq:
 *     str.rjust(integer, padstr=' ')   => new_str
 *  
 *  If <i>integer</i> is greater than the length of <i>str</i>, returns a new
 *  <code>String</code> of length <i>integer</i> with <i>str</i> right justified
 *  and padded with <i>padstr</i>; otherwise, returns <i>str</i>.
 *     
 *     "hello".rjust(4)            #=> "hello"
 *     "hello".rjust(20)           #=> "               hello"
 *     "hello".rjust(20, '1234')   #=> "123412341234123hello"
 */

static VALUE
rb_str_rjust(int argc, VALUE *argv, VALUE str)
{
    return rb_str_justify(argc, argv, str, 'r');
}


/*
 *  call-seq:
 *     str.center(integer, padstr)   => new_str
 *  
 *  If <i>integer</i> is greater than the length of <i>str</i>, returns a new
 *  <code>String</code> of length <i>integer</i> with <i>str</i> centered and
 *  padded with <i>padstr</i>; otherwise, returns <i>str</i>.
 *     
 *     "hello".center(4)         #=> "hello"
 *     "hello".center(20)        #=> "       hello        "
 *     "hello".center(20, '123') #=> "1231231hello12312312"
 */

static VALUE
rb_str_center(int argc, VALUE *argv, VALUE str)
{
    return rb_str_justify(argc, argv, str, 'c');
}

/*
 *  call-seq:
 *     str.partition(sep)              => [head, sep, tail]
 *  
 *  Searches the string for <i>sep</i> and returns the part before
 *  it, the <i>sep</i>, and the part after it.  If <i>sep</i> is not found,
 *  returns <i>str</i> and two empty strings.
 *     
 *     "hello".partition("l")         #=> ["he", "l", "lo"]
 *     "hello".partition("x")         #=> ["hello", "", ""]
 */

static VALUE
rb_str_partition(VALUE str, VALUE sep)
{
    long pos;
    int regex = Qfalse;

    if (TYPE(sep) == T_REGEXP) {
	pos = rb_reg_search(sep, str, 0, 0);
	regex = Qtrue;
    }
    else {
	VALUE tmp;

	tmp = rb_check_string_type(sep);
	if (NIL_P(tmp)) {
	    rb_raise(rb_eTypeError, "type mismatch: %s given",
		     rb_obj_classname(sep));
	}
	pos = rb_str_index(str, sep, 0);
    }
    if (pos < 0) {
      failed:
	return rb_ary_new3(3, str, rb_str_new(0,0),rb_str_new(0,0));
    }
    if (regex) {
	sep = rb_str_subpat(str, sep, 0);
	if (pos == 0 && RSTRING_LEN(sep) == 0) goto failed;
    }
    return rb_ary_new3(3, rb_str_subseq(str, 0, pos),
		          sep,
		          rb_str_subseq(str, pos+RSTRING_LEN(sep),
					     RSTRING_LEN(str)-pos-RSTRING_LEN(sep)));
}

/*
 *  call-seq:
 *     str.rpartition(sep)            => [head, sep, tail]
 *  
 *  Searches <i>sep</i> in the string from the end of the string, and
 *  returns the part before it, the <i>sep</i>, and the part after it.
 *  If <i>sep</i> is not found, returns two empty strings and
 *  <i>str</i>.
 *     
 *     "hello".rpartition("l")         #=> ["hel", "l", "o"]
 *     "hello".rpartition("x")         #=> ["", "", "hello"]
 */

static VALUE
rb_str_rpartition(VALUE str, VALUE sep)
{
    long pos = RSTRING_LEN(str);
    int regex = Qfalse;

    if (TYPE(sep) == T_REGEXP) {
	pos = rb_reg_search(sep, str, pos, 1);
	regex = Qtrue;
    }
    else {
	VALUE tmp;

	tmp = rb_check_string_type(sep);
	if (NIL_P(tmp)) {
	    rb_raise(rb_eTypeError, "type mismatch: %s given",
		     rb_obj_classname(sep));
	}
	pos = rb_str_sublen(str, pos);
	pos = rb_str_rindex(str, sep, pos);
    }
    if (pos < 0) {
	return rb_ary_new3(3, rb_str_new(0,0),rb_str_new(0,0), str);
    }
    if (regex) {
	sep = rb_reg_nth_match(0, rb_backref_get());
    }
    return rb_ary_new3(3, rb_str_subseq(str, 0, pos),
		          sep,
		          rb_str_subseq(str, pos+RSTRING_LEN(sep),
					     RSTRING_LEN(str)-pos-RSTRING_LEN(sep)));
}

/*
 *  call-seq:
 *     str.start_with?([prefix]+)   => true or false
 *  
 *  Returns true if <i>str</i> starts with the prefix given.
 */

static VALUE
rb_str_start_with(int argc, VALUE *argv, VALUE str)
{
    int i;

    for (i=0; i<argc; i++) {
	VALUE tmp = rb_check_string_type(argv[i]);
	if (NIL_P(tmp)) continue;
	rb_enc_check(str, tmp);
	if (RSTRING_LEN(str) < RSTRING_LEN(tmp)) continue;
	if (memcmp(RSTRING_PTR(str), RSTRING_PTR(tmp), RSTRING_LEN(tmp)) == 0)
	    return Qtrue;
    }
    return Qfalse;
}

/*
 *  call-seq:
 *     str.end_with?([suffix]+)   => true or false
 *  
 *  Returns true if <i>str</i> ends with the suffix given.
 */

static VALUE
rb_str_end_with(int argc, VALUE *argv, VALUE str)
{
    int i;

    for (i=0; i<argc; i++) {
	VALUE tmp = rb_check_string_type(argv[i]);
	if (NIL_P(tmp)) continue;
	rb_enc_check(str, tmp);
	if (RSTRING_LEN(str) < RSTRING_LEN(tmp)) continue;
	if (memcmp(RSTRING_PTR(str) + RSTRING_LEN(str) - RSTRING_LEN(tmp),
		   RSTRING_PTR(tmp), RSTRING_LEN(tmp)) == 0)
	    return Qtrue;
    }
    return Qfalse;
}

void
rb_str_setter(VALUE val, ID id, VALUE *var)
{
    if (!NIL_P(val) && TYPE(val) != T_STRING) {
	rb_raise(rb_eTypeError, "value of %s must be String", rb_id2name(id));
    }
    *var = val;
}


/*
 *  call-seq:
 *     str.force_encoding(encoding)   => str
 *
 *  Changes the encoding to +encoding+ and returns self.
 */

static VALUE
rb_str_force_encoding(VALUE str, VALUE enc)
{
    str_modifiable(str);
    rb_enc_associate(str, rb_to_encoding(enc));
    return str;
}

/*
 *  call-seq:
 *     str.valid_encoding?  => true or false
 *  
 *  Returns true for a string which encoded correctly.
 *
 *    "\xc2\xa1".force_encoding("UTF-8").valid_encoding? => true
 *    "\xc2".force_encoding("UTF-8").valid_encoding? => false
 *    "\x80".force_encoding("UTF-8").valid_encoding? => false
 */

static VALUE
rb_str_valid_encoding_p(VALUE str)
{
    int cr = rb_enc_str_coderange(str);

    return cr == ENC_CODERANGE_BROKEN ? Qfalse : Qtrue;
}

/*
 *  call-seq:
 *     str.ascii_only?  => true or false
 *  
 *  Returns true for a string which has only ASCII characters.
 *
 *    "abc".force_encoding("UTF-8").ascii_only? => true
 *    "abc\u{6666}".force_encoding("UTF-8").ascii_only? => false
 */

static VALUE
rb_str_is_ascii_only_p(VALUE str)
{
    int cr = rb_enc_str_coderange(str);

    return cr == ENC_CODERANGE_7BIT ? Qtrue : Qfalse;
}

/**********************************************************************
 * Document-class: Symbol
 *
 *  <code>Symbol</code> objects represent names and some strings
 *  inside the Ruby
 *  interpreter. They are generated using the <code>:name</code> and
 *  <code>:"string"</code> literals
 *  syntax, and by the various <code>to_sym</code> methods. The same
 *  <code>Symbol</code> object will be created for a given name or string
 *  for the duration of a program's execution, regardless of the context
 *  or meaning of that name. Thus if <code>Fred</code> is a constant in
 *  one context, a method in another, and a class in a third, the
 *  <code>Symbol</code> <code>:Fred</code> will be the same object in
 *  all three contexts.
 *     
 *     module One
 *       class Fred
 *       end
 *       $f1 = :Fred
 *     end
 *     module Two
 *       Fred = 1
 *       $f2 = :Fred
 *     end
 *     def Fred()
 *     end
 *     $f3 = :Fred
 *     $f1.id   #=> 2514190
 *     $f2.id   #=> 2514190
 *     $f3.id   #=> 2514190
 *     
 */


/*
 *  call-seq:
 *     sym == obj   => true or false
 *  
 *  Equality---If <i>sym</i> and <i>obj</i> are exactly the same
 *  symbol, returns <code>true</code>. Otherwise, compares them
 *  as strings.
 */

static VALUE
sym_equal(VALUE sym1, VALUE sym2)
{
    if (sym1 == sym2) return Qtrue;
    return Qfalse;
}


/*
 *  call-seq:
 *     sym.to_i      => fixnum
 *  
 *  Returns an integer that is unique for each symbol within a
 *  particular execution of a program.
 *     
 *     :fred.to_i           #=> 9809
 *     "fred".to_sym.to_i   #=> 9809
 */

static VALUE
sym_to_i(VALUE sym)
{
    ID id = SYM2ID(sym);

    return LONG2FIX(id);
}


/*
 *  call-seq:
 *     sym.inspect    => string
 *  
 *  Returns the representation of <i>sym</i> as a symbol literal.
 *     
 *     :fred.inspect   #=> ":fred"
 */

static VALUE
sym_inspect(VALUE sym)
{
    VALUE str, klass = Qundef;
    ID id = SYM2ID(sym);
    rb_encoding *enc;

    sym = rb_id2str(id);
    enc = rb_enc_get(sym);
    str = rb_enc_str_new(0, RSTRING_LEN(sym)+1, enc);
    RSTRING_PTR(str)[0] = ':';
    memcpy(RSTRING_PTR(str)+1, RSTRING_PTR(sym), RSTRING_LEN(sym));
    if (RSTRING_LEN(sym) != strlen(RSTRING_PTR(sym)) ||
	!rb_enc_symname_p(RSTRING_PTR(sym), enc)) {
	str = rb_str_dump(str);
	strncpy(RSTRING_PTR(str), ":\"", 2);
    }
    if (klass != Qundef) {
	rb_str_cat2(str, "/");
	rb_str_append(str, rb_inspect(klass));
    }
    return str;
}


/*
 *  call-seq:
 *     sym.id2name   => string
 *     sym.to_s      => string
 *  
 *  Returns the name or string corresponding to <i>sym</i>.
 *     
 *     :fred.id2name   #=> "fred"
 */


VALUE
rb_sym_to_s(VALUE sym)
{
    ID id = SYM2ID(sym);

    return str_new3(rb_cString, rb_id2str(id));
}


/*
 * call-seq:
 *   sym.to_sym   => sym
 *   sym.intern   => sym
 *
 * In general, <code>to_sym</code> returns the <code>Symbol</code> corresponding
 * to an object. As <i>sym</i> is already a symbol, <code>self</code> is returned
 * in this case.
 */

static VALUE
sym_to_sym(VALUE sym)
{
    return sym;
}

static VALUE
sym_call(VALUE args, VALUE sym, int argc, VALUE *argv)
{
    VALUE obj;

    if (argc < 1) {
	rb_raise(rb_eArgError, "no receiver given");
    }
    obj = argv[0];
    return rb_funcall3(obj, (ID)sym, argc - 1, argv + 1);
}

/*
 * call-seq:
 *   sym.to_proc
 *
 * Returns a _Proc_ object which respond to the given method by _sym_.
 *
 *   (1..3).collect(&:to_s)  #=> ["1", "2", "3"]
 */

static VALUE
sym_to_proc(VALUE sym)
{
    return rb_proc_new(sym_call, (VALUE)SYM2ID(sym));
}


static VALUE
sym_succ(VALUE sym)
{
    return rb_str_intern(rb_str_succ(rb_sym_to_s(sym)));
}

static VALUE
sym_cmp(VALUE sym, VALUE other)
{
    if (!SYMBOL_P(other)) {
	return Qnil;
    }
    return rb_str_cmp_m(rb_sym_to_s(sym), rb_sym_to_s(other));
}

static VALUE
sym_casecmp(VALUE sym, VALUE other)
{
    if (!SYMBOL_P(other)) {
	return Qnil;
    }
    return rb_str_casecmp(rb_sym_to_s(sym), rb_sym_to_s(other));
}

static VALUE
sym_match(VALUE sym, VALUE other)
{
    return rb_str_match(rb_sym_to_s(sym), other);
}

static VALUE
sym_eqq(VALUE sym, VALUE other)
{
    if (sym == other) return Qtrue;
    return rb_str_equal(rb_sym_to_s(sym), other);
}

static VALUE
sym_aref(int argc, VALUE *argv, VALUE sym)
{
    return rb_str_aref_m(argc, argv, rb_sym_to_s(sym));
}

static VALUE
sym_length(VALUE sym)
{
    return rb_str_length(rb_id2str(SYM2ID(sym)));
}

static VALUE
sym_empty(VALUE sym)
{
    return rb_str_empty(rb_id2str(SYM2ID(sym)));
}

static VALUE
sym_upcase(VALUE sym)
{
    return rb_str_intern(rb_str_upcase(rb_id2str(SYM2ID(sym))));
}

static VALUE
sym_downcase(VALUE sym)
{
    return rb_str_intern(rb_str_downcase(rb_id2str(SYM2ID(sym))));
}

static VALUE
sym_capitalize(VALUE sym)
{
    return rb_str_intern(rb_str_capitalize(rb_id2str(SYM2ID(sym))));
}

static VALUE
sym_swapcase(VALUE sym)
{
    return rb_str_intern(rb_str_swapcase(rb_id2str(SYM2ID(sym))));
}

static VALUE
sym_encoding(VALUE sym)
{
    return rb_obj_encoding(rb_id2str(SYM2ID(sym)));
}

ID
rb_to_id(VALUE name)
{
    VALUE tmp;
    ID id;

    switch (TYPE(name)) {
      default:
	tmp = rb_check_string_type(name);
	if (NIL_P(tmp)) {
	    rb_raise(rb_eTypeError, "%s is not a symbol",
		     RSTRING_PTR(rb_inspect(name)));
	}
	name = tmp;
	/* fall through */
      case T_STRING:
	name = rb_str_intern(name);
	/* fall through */
      case T_SYMBOL:
	return SYM2ID(name);
    }
    return id;
}

/*
 *  A <code>String</code> object holds and manipulates an arbitrary sequence of
 *  bytes, typically representing characters. String objects may be created
 *  using <code>String::new</code> or as literals.
 *     
 *  Because of aliasing issues, users of strings should be aware of the methods
 *  that modify the contents of a <code>String</code> object.  Typically,
 *  methods with names ending in ``!'' modify their receiver, while those
 *  without a ``!'' return a new <code>String</code>.  However, there are
 *  exceptions, such as <code>String#[]=</code>.
 *     
 */

void
Init_String(void)
{
    rb_cString  = rb_define_class("String", rb_cObject);
    rb_include_module(rb_cString, rb_mComparable);
    rb_define_alloc_func(rb_cString, str_alloc);
    rb_define_singleton_method(rb_cString, "try_convert", rb_str_s_try_convert, 1);
    rb_define_method(rb_cString, "initialize", rb_str_init, -1);
    rb_define_method(rb_cString, "initialize_copy", rb_str_replace, 1);
    rb_define_method(rb_cString, "<=>", rb_str_cmp_m, 1);
    rb_define_method(rb_cString, "==", rb_str_equal, 1);
    rb_define_method(rb_cString, "eql?", rb_str_eql, 1);
    rb_define_method(rb_cString, "hash", rb_str_hash_m, 0);
    rb_define_method(rb_cString, "casecmp", rb_str_casecmp, 1);
    rb_define_method(rb_cString, "+", rb_str_plus, 1);
    rb_define_method(rb_cString, "*", rb_str_times, 1);
    rb_define_method(rb_cString, "%", rb_str_format_m, 1);
    rb_define_method(rb_cString, "[]", rb_str_aref_m, -1);
    rb_define_method(rb_cString, "[]=", rb_str_aset_m, -1);
    rb_define_method(rb_cString, "insert", rb_str_insert, 2);
    rb_define_method(rb_cString, "length", rb_str_length, 0);
    rb_define_method(rb_cString, "size", rb_str_length, 0);
    rb_define_method(rb_cString, "bytesize", rb_str_bytesize, 0);
    rb_define_method(rb_cString, "empty?", rb_str_empty, 0);
    rb_define_method(rb_cString, "=~", rb_str_match, 1);
    rb_define_method(rb_cString, "match", rb_str_match_m, -1);
    rb_define_method(rb_cString, "succ", rb_str_succ, 0);
    rb_define_method(rb_cString, "succ!", rb_str_succ_bang, 0);
    rb_define_method(rb_cString, "next", rb_str_succ, 0);
    rb_define_method(rb_cString, "next!", rb_str_succ_bang, 0);
    rb_define_method(rb_cString, "upto", rb_str_upto, -1);
    rb_define_method(rb_cString, "index", rb_str_index_m, -1);
    rb_define_method(rb_cString, "rindex", rb_str_rindex_m, -1);
    rb_define_method(rb_cString, "replace", rb_str_replace, 1);
    rb_define_method(rb_cString, "clear", rb_str_clear, 0);
    rb_define_method(rb_cString, "chr", rb_str_chr, 0);

    rb_define_method(rb_cString, "to_i", rb_str_to_i, -1);
    rb_define_method(rb_cString, "to_f", rb_str_to_f, 0);
    rb_define_method(rb_cString, "to_s", rb_str_to_s, 0);
    rb_define_method(rb_cString, "to_str", rb_str_to_s, 0);
    rb_define_method(rb_cString, "inspect", rb_str_inspect, 0);
    rb_define_method(rb_cString, "dump", rb_str_dump, 0);

    rb_define_method(rb_cString, "upcase", rb_str_upcase, 0);
    rb_define_method(rb_cString, "downcase", rb_str_downcase, 0);
    rb_define_method(rb_cString, "capitalize", rb_str_capitalize, 0);
    rb_define_method(rb_cString, "swapcase", rb_str_swapcase, 0);

    rb_define_method(rb_cString, "upcase!", rb_str_upcase_bang, 0);
    rb_define_method(rb_cString, "downcase!", rb_str_downcase_bang, 0);
    rb_define_method(rb_cString, "capitalize!", rb_str_capitalize_bang, 0);
    rb_define_method(rb_cString, "swapcase!", rb_str_swapcase_bang, 0);

    rb_define_method(rb_cString, "hex", rb_str_hex, 0);
    rb_define_method(rb_cString, "oct", rb_str_oct, 0);
    rb_define_method(rb_cString, "split", rb_str_split_m, -1);
    rb_define_method(rb_cString, "lines", rb_str_each_line, -1);
    rb_define_method(rb_cString, "bytes", rb_str_each_byte, 0);
    rb_define_method(rb_cString, "reverse", rb_str_reverse, 0);
    rb_define_method(rb_cString, "reverse!", rb_str_reverse_bang, 0);
    rb_define_method(rb_cString, "concat", rb_str_concat, 1);
    rb_define_method(rb_cString, "<<", rb_str_concat, 1);
    rb_define_method(rb_cString, "crypt", rb_str_crypt, 1);
    rb_define_method(rb_cString, "intern", rb_str_intern, 0);
    rb_define_method(rb_cString, "to_sym", rb_str_intern, 0);
    rb_define_method(rb_cString, "ord", rb_str_ord, 0);

    rb_define_method(rb_cString, "include?", rb_str_include, 1);
    rb_define_method(rb_cString, "start_with?", rb_str_start_with, -1);
    rb_define_method(rb_cString, "end_with?", rb_str_end_with, -1);

    rb_define_method(rb_cString, "scan", rb_str_scan, 1);

    rb_define_method(rb_cString, "ljust", rb_str_ljust, -1);
    rb_define_method(rb_cString, "rjust", rb_str_rjust, -1);
    rb_define_method(rb_cString, "center", rb_str_center, -1);

    rb_define_method(rb_cString, "sub", rb_str_sub, -1);
    rb_define_method(rb_cString, "gsub", rb_str_gsub, -1);
    rb_define_method(rb_cString, "chop", rb_str_chop, 0);
    rb_define_method(rb_cString, "chomp", rb_str_chomp, -1);
    rb_define_method(rb_cString, "strip", rb_str_strip, 0);
    rb_define_method(rb_cString, "lstrip", rb_str_lstrip, 0);
    rb_define_method(rb_cString, "rstrip", rb_str_rstrip, 0);

    rb_define_method(rb_cString, "sub!", rb_str_sub_bang, -1);
    rb_define_method(rb_cString, "gsub!", rb_str_gsub_bang, -1);
    rb_define_method(rb_cString, "chop!", rb_str_chop_bang, 0);
    rb_define_method(rb_cString, "chomp!", rb_str_chomp_bang, -1);
    rb_define_method(rb_cString, "strip!", rb_str_strip_bang, 0);
    rb_define_method(rb_cString, "lstrip!", rb_str_lstrip_bang, 0);
    rb_define_method(rb_cString, "rstrip!", rb_str_rstrip_bang, 0);

    rb_define_method(rb_cString, "tr", rb_str_tr, 2);
    rb_define_method(rb_cString, "tr_s", rb_str_tr_s, 2);
    rb_define_method(rb_cString, "delete", rb_str_delete, -1);
    rb_define_method(rb_cString, "squeeze", rb_str_squeeze, -1);
    rb_define_method(rb_cString, "count", rb_str_count, -1);

    rb_define_method(rb_cString, "tr!", rb_str_tr_bang, 2);
    rb_define_method(rb_cString, "tr_s!", rb_str_tr_s_bang, 2);
    rb_define_method(rb_cString, "delete!", rb_str_delete_bang, -1);
    rb_define_method(rb_cString, "squeeze!", rb_str_squeeze_bang, -1);

    rb_define_method(rb_cString, "each_line", rb_str_each_line, -1);
    rb_define_method(rb_cString, "each_byte", rb_str_each_byte, 0);
    rb_define_method(rb_cString, "each_char", rb_str_each_char, 0);

    rb_define_method(rb_cString, "sum", rb_str_sum, -1);

    rb_define_method(rb_cString, "slice", rb_str_aref_m, -1);
    rb_define_method(rb_cString, "slice!", rb_str_slice_bang, -1);

    rb_define_method(rb_cString, "partition", rb_str_partition, 1);
    rb_define_method(rb_cString, "rpartition", rb_str_rpartition, 1);

    rb_define_method(rb_cString, "encoding", rb_obj_encoding, 0); /* in encoding.c */
    rb_define_method(rb_cString, "force_encoding", rb_str_force_encoding, 1);
    rb_define_method(rb_cString, "valid_encoding?", rb_str_valid_encoding_p, 0);
    rb_define_method(rb_cString, "ascii_only?", rb_str_is_ascii_only_p, 0);

    id_to_s = rb_intern("to_s");

    rb_fs = Qnil;
    rb_define_variable("$;", &rb_fs);
    rb_define_variable("$-F", &rb_fs);

    rb_cSymbol = rb_define_class("Symbol", rb_cObject);
    rb_include_module(rb_cSymbol, rb_mComparable);
    rb_undef_alloc_func(rb_cSymbol);
    rb_undef_method(CLASS_OF(rb_cSymbol), "new");
    rb_define_singleton_method(rb_cSymbol, "all_symbols", rb_sym_all_symbols, 0); /* in parse.y */

    rb_define_method(rb_cSymbol, "==", sym_equal, 1);
    rb_define_method(rb_cSymbol, "to_i", sym_to_i, 0);
    rb_define_method(rb_cSymbol, "inspect", sym_inspect, 0);
    rb_define_method(rb_cSymbol, "to_s", rb_sym_to_s, 0);
    rb_define_method(rb_cSymbol, "id2name", rb_sym_to_s, 0);
    rb_define_method(rb_cSymbol, "intern", sym_to_sym, 0);
    rb_define_method(rb_cSymbol, "to_sym", sym_to_sym, 0);
    rb_define_method(rb_cSymbol, "to_proc", sym_to_proc, 0);
    rb_define_method(rb_cSymbol, "succ", sym_succ, 0);
    rb_define_method(rb_cSymbol, "next", sym_succ, 0);

    rb_define_method(rb_cSymbol, "<=>", sym_cmp, 1);
    rb_define_method(rb_cSymbol, "casecmp", sym_casecmp, 1);
    rb_define_method(rb_cSymbol, "=~", sym_match, 1);
    rb_define_method(rb_cSymbol, "===", sym_eqq, 1);

    rb_define_method(rb_cSymbol, "[]", sym_aref, -1);
    rb_define_method(rb_cSymbol, "slice", sym_aref, -1);
    rb_define_method(rb_cSymbol, "length", sym_length, 0);
    rb_define_method(rb_cSymbol, "size", sym_length, 0);
    rb_define_method(rb_cSymbol, "empty?", sym_empty, 0);
    rb_define_method(rb_cSymbol, "match", sym_match, -1);

    rb_define_method(rb_cSymbol, "upcase", sym_upcase, 0);
    rb_define_method(rb_cSymbol, "downcase", sym_downcase, 0);
    rb_define_method(rb_cSymbol, "capitalize", sym_capitalize, 0);
    rb_define_method(rb_cSymbol, "swapcase", sym_swapcase, 0);

    rb_define_method(rb_cSymbol, "encoding", sym_encoding, 0);
}
