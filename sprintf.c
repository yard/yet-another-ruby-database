/**********************************************************************

  sprintf.c -

  $Author: akr $
  $Date: 2007-12-21 11:31:11 +0900 (Fri, 21 Dec 2007) $
  created at: Fri Oct 15 10:39:26 JST 1993

  Copyright (C) 1993-2007 Yukihiro Matsumoto
  Copyright (C) 2000  Network Applied Communication Laboratory, Inc.
  Copyright (C) 2000  Information-technology Promotion Agency, Japan

**********************************************************************/

#include "ruby/ruby.h"
#include "ruby/re.h"
#include "ruby/encoding.h"
#include <math.h>
#include <stdarg.h>

#define BIT_DIGITS(N)   (((N)*146)/485 + 1)  /* log2(10) =~ 146/485 */
#define BITSPERDIG (SIZEOF_BDIGITS*CHAR_BIT)
#define EXTENDSIGN(n, l) (((~0 << (n)) >> (((n)*(l)) % BITSPERDIG)) & ~(~0 << (n)))

static void fmt_setup(char*,int,int,int,int);

static char*
remove_sign_bits(char *str, int base)
{
    char *s, *t;
    
    s = t = str;

    if (base == 16) {
	while (*t == 'f') {
	    t++;
	}
    }
    else if (base == 8) {
	*t |= EXTENDSIGN(3, strlen(t));
	while (*t == '7') {
	    t++;
	}
    }
    else if (base == 2) {
	while (*t == '1') {
	    t++;
	}
    }
    if (t > s) {
	while (*t) *s++ = *t++;
	*s = '\0';
    }

    return str;
}

static char
sign_bits(int base, const char *p)
{
    char c = '.';

    switch (base) {
      case 16:
	if (*p == 'X') c = 'F';
	else c = 'f';
	break;
      case 8:
	c = '7'; break;
      case 2:
	c = '1'; break;
    }
    return c;
}

#define FNONE  0
#define FSHARP 1
#define FMINUS 2
#define FPLUS  4
#define FZERO  8
#define FSPACE 16
#define FWIDTH 32
#define FPREC  64
#define FPREC0 128

#define CHECK(l) do {\
    while (blen + (l) >= bsiz) {\
	bsiz*=2;\
    }\
    rb_str_resize(result, bsiz);\
    buf = RSTRING_PTR(result);\
} while (0)

#define PUSH(s, l) do { \
    CHECK(l);\
    memcpy(&buf[blen], s, l);\
    blen += (l);\
} while (0)

#define FILL(c, l) do { \
    CHECK(l);\
    memset(&buf[blen], c, l);\
    blen += (l);\
} while (0)

#define GETARG() (nextvalue != Qundef ? nextvalue : \
    posarg < 0 ? \
    (rb_raise(rb_eArgError, "unnumbered(%d) mixed with numbered", nextarg), 0) : \
    (posarg = nextarg++, GETNTHARG(posarg)))

#define GETPOSARG(n) (posarg > 0 ? \
    (rb_raise(rb_eArgError, "numbered(%d) after unnumbered(%d)", n, posarg), 0) : \
    ((n < 1) ? (rb_raise(rb_eArgError, "invalid index - %d$", n), 0) : \
	       (posarg = -1, GETNTHARG(n))))

#define GETNTHARG(nth) \
    ((nth >= argc) ? (rb_raise(rb_eArgError, "too few arguments"), 0) : argv[nth])

#define GETNUM(n, val) \
    for (; p < end && rb_enc_isdigit(*p, enc); p++) {	\
	int next_n = 10 * n + (*p - '0'); \
        if (next_n / 10 != n) {\
	    rb_raise(rb_eArgError, #val " too big"); \
	} \
	n = next_n; \
    } \
    if (p >= end) { \
	rb_raise(rb_eArgError, "malformed format string - %%*[0-9]"); \
    }

#define GETASTER(val) do { \
    t = p++; \
    n = 0; \
    GETNUM(n, val); \
    if (*p == '$') { \
	tmp = GETPOSARG(n); \
    } \
    else { \
	tmp = GETARG(); \
	p = t; \
    } \
    val = NUM2INT(tmp); \
} while (0)


/*
 *  call-seq:
 *     format(format_string [, arguments...] )   => string
 *     sprintf(format_string [, arguments...] )  => string
 *  
 *  Returns the string resulting from applying <i>format_string</i> to
 *  any additional arguments. Within the format string, any characters
 *  other than format sequences are copied to the result. A format
 *  sequence consists of a percent sign, followed by optional flags,
 *  width, and precision indicators, then terminated with a field type
 *  character. The field type controls how the corresponding
 *  <code>sprintf</code> argument is to be interpreted, while the flags
 *  modify that interpretation. The field type characters are listed
 *  in the table at the end of this section. The flag characters are:
 *
 *    Flag     | Applies to   | Meaning
 *    ---------+--------------+-----------------------------------------
 *    space    | bdeEfgGiouxX | Leave a space at the start of 
 *             |              | positive numbers.
 *    ---------+--------------+-----------------------------------------
 *    (digit)$ | all          | Specifies the absolute argument number
 *             |              | for this field. Absolute and relative
 *             |              | argument numbers cannot be mixed in a
 *             |              | sprintf string.
 *    ---------+--------------+-----------------------------------------
 *     #       | beEfgGoxX    | Use an alternative format. For the
 *             |              | conversions `o', `x', `X', and `b', 
 *             |              | prefix the result with ``0'', ``0x'', ``0X'',
 *             |              |  and ``0b'', respectively. For `e',
 *             |              | `E', `f', `g', and 'G', force a decimal
 *             |              | point to be added, even if no digits follow.
 *             |              | For `g' and 'G', do not remove trailing zeros.
 *    ---------+--------------+-----------------------------------------
 *    +        | bdeEfgGiouxX | Add a leading plus sign to positive numbers.
 *    ---------+--------------+-----------------------------------------
 *    -        | all          | Left-justify the result of this conversion.
 *    ---------+--------------+-----------------------------------------
 *    0 (zero) | bdeEfgGiouxX | Pad with zeros, not spaces.
 *    ---------+--------------+-----------------------------------------
 *    *        | all          | Use the next argument as the field width. 
 *             |              | If negative, left-justify the result. If the
 *             |              | asterisk is followed by a number and a dollar 
 *             |              | sign, use the indicated argument as the width.
 *
 *     
 *  The field width is an optional integer, followed optionally by a
 *  period and a precision. The width specifies the minimum number of
 *  characters that will be written to the result for this field. For
 *  numeric fields, the precision controls the number of decimal places
 *  displayed. For string fields, the precision determines the maximum
 *  number of characters to be copied from the string. (Thus, the format
 *  sequence <code>%10.10s</code> will always contribute exactly ten
 *  characters to the result.)
 *
 *  The field types are:
 *
 *      Field |  Conversion
 *      ------+--------------------------------------------------------------
 *        b   | Convert argument as a binary number.
 *        c   | Argument is the numeric code for a single character.
 *        d   | Convert argument as a decimal number.
 *        E   | Equivalent to `e', but uses an uppercase E to indicate
 *            | the exponent.
 *        e   | Convert floating point argument into exponential notation 
 *            | with one digit before the decimal point. The precision
 *            | determines the number of fractional digits (defaulting to six).
 *        f   | Convert floating point argument as [-]ddd.ddd, 
 *            |  where the precision determines the number of digits after
 *            | the decimal point.
 *        G   | Equivalent to `g', but use an uppercase `E' in exponent form.
 *        g   | Convert a floating point number using exponential form
 *            | if the exponent is less than -4 or greater than or
 *            | equal to the precision, or in d.dddd form otherwise.
 *        i   | Identical to `d'.
 *        o   | Convert argument as an octal number.
 *        p   | The valuing of argument.inspect.
 *        s   | Argument is a string to be substituted. If the format
 *            | sequence contains a precision, at most that many characters
 *            | will be copied.
 *        u   | Treat argument as an unsigned decimal number. Negative integers
 *            | are displayed as a 32 bit two's complement plus one for the
 *            | underlying architecture; that is, 2 ** 32 + n.  However, since
 *            | Ruby has no inherent limit on bits used to represent the
 *            | integer, this value is preceded by two dots (..) in order to
 *            | indicate a infinite number of leading sign bits.
 *        X   | Convert argument as a hexadecimal number using uppercase
 *            | letters. Negative numbers will be displayed with two
 *            | leading periods (representing an infinite string of
 *            | leading 'FF's.
 *        x   | Convert argument as a hexadecimal number.
 *            | Negative numbers will be displayed with two
 *            | leading periods (representing an infinite string of
 *            | leading 'ff's.
 *     
 *  Examples:
 *
 *     sprintf("%d %04x", 123, 123)               #=> "123 007b"
 *     sprintf("%08b '%4s'", 123, 123)            #=> "01111011 ' 123'"
 *     sprintf("%1$*2$s %2$d %1$s", "hello", 8)   #=> "   hello 8 hello"
 *     sprintf("%1$*2$s %2$d", "hello", -8)       #=> "hello    -8"
 *     sprintf("%+g:% g:%-g", 1.23, 1.23, 1.23)   #=> "+1.23: 1.23:1.23"
 *     sprintf("%u", -123)                        #=> "..4294967173"
 */

VALUE
rb_f_sprintf(int argc, const VALUE *argv)
{
    return rb_str_format(argc - 1, argv + 1, GETNTHARG(0));
}

VALUE
rb_str_format(int argc, const VALUE *argv, VALUE fmt)
{
    rb_encoding *enc;
    const char *p, *end;
    char *buf;
    int blen, bsiz;
    VALUE result;

    int width, prec, flags = FNONE;
    int nextarg = 1;
    int posarg = 0;
    int tainted = 0;
    VALUE nextvalue;
    VALUE tmp;
    VALUE str;

#define CHECK_FOR_WIDTH(f)				 \
    if ((f) & FWIDTH) {					 \
	rb_raise(rb_eArgError, "width given twice");	 \
    }							 \
    if ((f) & FPREC0) {					 \
	rb_raise(rb_eArgError, "width after precision"); \
    }
#define CHECK_FOR_FLAGS(f)				 \
    if ((f) & FWIDTH) {					 \
	rb_raise(rb_eArgError, "flag after width");	 \
    }							 \
    if ((f) & FPREC0) {					 \
	rb_raise(rb_eArgError, "flag after precision"); \
    }

    ++argc;
    --argv;
    if (OBJ_TAINTED(fmt)) tainted = 1;
    StringValue(fmt);
    enc = rb_enc_get(fmt);
    fmt = rb_str_new4(fmt);
    p = RSTRING_PTR(fmt);
    end = p + RSTRING_LEN(fmt);
    blen = 0;
    bsiz = 120;
    result = rb_str_buf_new(bsiz);
    rb_enc_copy(result, fmt);
    buf = RSTRING_PTR(result);
    memset(buf, 0, bsiz);

    for (; p < end; p++) {
	const char *t;
	int n;

	for (t = p; t < end && *t != '%'; t++) ;
	PUSH(p, t - p);
	if (t >= end) {
	    /* end of fmt string */
	    goto sprint_exit;
	}
	p = t + 1;		/* skip `%' */

	width = prec = -1;
	nextvalue = Qundef;
      retry:
	switch (*p) {
	  default:
	    if (rb_enc_isprint(*p, enc))
		rb_raise(rb_eArgError, "malformed format string - %%%c", *p);
	    else
		rb_raise(rb_eArgError, "malformed format string");
	    break;

	  case ' ':
	    CHECK_FOR_FLAGS(flags);
	    flags |= FSPACE;
	    p++;
	    goto retry;

	  case '#':
	    CHECK_FOR_FLAGS(flags);
	    flags |= FSHARP;
	    p++;
	    goto retry;

	  case '+':
	    CHECK_FOR_FLAGS(flags);
	    flags |= FPLUS;
	    p++;
	    goto retry;

	  case '-':
	    CHECK_FOR_FLAGS(flags);
	    flags |= FMINUS;
	    p++;
	    goto retry;

	  case '0':
	    CHECK_FOR_FLAGS(flags);
	    flags |= FZERO;
	    p++;
	    goto retry;

	  case '1': case '2': case '3': case '4':
	  case '5': case '6': case '7': case '8': case '9':
	    n = 0;
	    GETNUM(n, width);
	    if (*p == '$') {
		if (nextvalue != Qundef) {
		    rb_raise(rb_eArgError, "value given twice - %d$", n);
		}
		nextvalue = GETPOSARG(n);
		p++;
		goto retry;
	    }
	    CHECK_FOR_WIDTH(flags);
	    width = n;
	    flags |= FWIDTH;
	    goto retry;

	  case '*':
	    CHECK_FOR_WIDTH(flags);
	    flags |= FWIDTH;
	    GETASTER(width);
	    if (width < 0) {
		flags |= FMINUS;
		width = -width;
	    }
	    p++;
	    goto retry;

	  case '.':
	    if (flags & FPREC0) {
		rb_raise(rb_eArgError, "precision given twice");
	    }
	    flags |= FPREC|FPREC0;

	    prec = 0;
	    p++;
	    if (*p == '*') {
		GETASTER(prec);
		if (prec < 0) {	/* ignore negative precision */
		    flags &= ~FPREC;
		}
		p++;
		goto retry;
	    }

	    GETNUM(prec, precision);
	    goto retry;

	  case '\n':
	  case '\0':
	    p--;
	  case '%':
	    if (flags != FNONE) {
		rb_raise(rb_eArgError, "invalid format character - %%");
	    }
	    PUSH("%", 1);
	    break;

	  case 'c':
	    {
		VALUE val = GETARG();
		VALUE tmp;
		int c, n;

		tmp = rb_check_string_type(val);
		if (!NIL_P(tmp)) {
		    if (rb_enc_strlen(RSTRING_PTR(tmp),RSTRING_END(tmp),enc) != 1) {
			rb_raise(rb_eArgError, "%%c requires a character");
		    }
		    c = rb_enc_codepoint(RSTRING_PTR(tmp), RSTRING_END(tmp), enc);
		}
		else {
		    c = NUM2INT(val);
		}
		n = rb_enc_codelen(c, enc);
		if (n == 0) {
		    rb_raise(rb_eArgError, "invalid character");
		}
		if (!(flags & FWIDTH)) {
		    CHECK(n);
		    rb_enc_mbcput(c, &buf[blen], enc);
		    blen += n;
		}
		else if ((flags & FMINUS)) {
		    CHECK(n);
		    rb_enc_mbcput(c, &buf[blen], enc);
		    blen += n;
		    FILL(' ', width-1);
		}
		else {
		    FILL(' ', width-1);
		    CHECK(n);
		    rb_enc_mbcput(c, &buf[blen], enc);
		    blen += n;
		}
	    }
	    break;

	  case 's':
	  case 'p':
	    {
		VALUE arg = GETARG();
		long len, slen;

		if (*p == 'p') arg = rb_inspect(arg);
		str = rb_obj_as_string(arg);
		if (OBJ_TAINTED(str)) tainted = 1;
		len = RSTRING_LEN(str);
		enc = rb_enc_check(result, str);
		if (flags&(FPREC|FWIDTH)) {
		    slen = rb_enc_strlen(RSTRING_PTR(str),RSTRING_END(str),enc);
		    if (slen < 0) {
			rb_raise(rb_eArgError, "invalid mbstring sequence");
		    }
		}
		if (flags&FPREC) {
		    if (prec < slen) {
			char *p = rb_enc_nth(RSTRING_PTR(str), RSTRING_END(str),
					     prec, enc);
			slen = prec;
			len = p - RSTRING_PTR(str);
		    }
		}
		/* need to adjust multi-byte string pos */
		if (flags&FWIDTH) {
		    if (width > slen) {
			width -= slen;
			if (!(flags&FMINUS)) {
			    CHECK(width);
			    while (width--) {
				buf[blen++] = ' ';
			    }
			}
			CHECK(len);
			memcpy(&buf[blen], RSTRING_PTR(str), len);
			blen += len;
			if (flags&FMINUS) {
			    CHECK(width);
			    while (width--) {
				buf[blen++] = ' ';
			    }
			}
			break;
		    }
		}
		PUSH(RSTRING_PTR(str), len);
		rb_enc_associate(result, enc);
	    }
	    break;

	  case 'd':
	  case 'i':
	  case 'o':
	  case 'x':
	  case 'X':
	  case 'b':
	  case 'B':
	  case 'u':
	    {
		volatile VALUE val = GETARG();
		char fbuf[32], nbuf[64], *s, *t;
		const char *prefix = 0;
		int sign = 0;
		char sc = 0;
		long v = 0;
		int base, bignum = 0;
		int len, pos;

		switch (*p) {
		  case 'd':
		  case 'i':
		  case 'u':
		    sign = 1; break;
		  case 'o':
		  case 'x':
		  case 'X':
		  case 'b':
		  case 'B':
		    if (flags&(FPLUS|FSPACE)) sign = 1;
		    break;
		}
		if (flags & FSHARP) {
		    switch (*p) {
		      case 'o':
			prefix = "0"; break;
		      case 'x':
			prefix = "0x"; break;
		      case 'X':
			prefix = "0X"; break;
		      case 'b':
			prefix = "0b"; break;
		      case 'B':
			prefix = "0B"; break;
		    }
		    if (prefix) {
			width -= strlen(prefix);
		    }
		}

	      bin_retry:
		switch (TYPE(val)) {
		  case T_FLOAT:
		    if (FIXABLE((long)RFLOAT_VALUE(val))) {
			val = LONG2FIX((long)RFLOAT_VALUE(val));
			goto bin_retry;
		    }
		    val = rb_dbl2big(RFLOAT_VALUE(val));
		    if (FIXNUM_P(val)) goto bin_retry;
		    bignum = 1;
		    break;
		  case T_STRING:
		    val = rb_str_to_inum(val, 0, Qtrue);
		    goto bin_retry;
		  case T_BIGNUM:
		    bignum = 1;
		    break;
		  case T_FIXNUM:
		    v = FIX2LONG(val);
		    break;
		  default:
		    val = rb_Integer(val);
		    goto bin_retry;
		}

		switch (*p) {
		  case 'o':
		    base = 8; break;
		  case 'x':
		  case 'X':
		    base = 16; break;
		  case 'b':
		  case 'B':
		    base = 2; break;
		  case 'u':
		  case 'd':
		  case 'i':
		  default:
		    base = 10; break;
		}

		if (!bignum) {
		    if (base == 2) {
			val = rb_int2big(v);
			goto bin_retry;
		    }
		    if (sign) {
			char c = *p;
			if (c == 'i') c = 'd'; /* %d and %i are identical */
			if (v < 0) {
			    v = -v;
			    sc = '-';
			    width--;
			}
			else if (flags & FPLUS) {
			    sc = '+';
			    width--;
			}
			else if (flags & FSPACE) {
			    sc = ' ';
			    width--;
			}
			sprintf(fbuf, "%%l%c", c);
			sprintf(nbuf, fbuf, v);
		    }
		    else {
			s = nbuf;
			if (v < 0) {
			    strcpy(s, "..");
			    s += 2;
			}
			sprintf(fbuf, "%%l%c", *p == 'X' ? 'x' : *p);
			sprintf(s, fbuf, v);
			if (v < 0) {
			    char d = 0;

			    remove_sign_bits(s, base);
			    switch (base) {
			      case 16:
				d = 'f'; break;
			      case 8:
				d = '7'; break;
			    }
			    if (d && *s != d) {
				memmove(s+1, s, strlen(s)+1);
				*s = d;
			    }
			}
		    }
		    s = nbuf;
		}
		else {
		    if (sign) {
			tmp = rb_big2str(val, base);
			s = RSTRING_PTR(tmp);
			if (s[0] == '-') {
			    s++;
			    sc = '-';
			    width--;
			}
			else if (flags & FPLUS) {
			    sc = '+';
			    width--;
			}
			else if (flags & FSPACE) {
			    sc = ' ';
			    width--;
			}
		    }
		    else {
                        volatile VALUE tmp1;
			if (!RBIGNUM_SIGN(val)) {
			    val = rb_big_clone(val);
			    rb_big_2comp(val);
			}
			tmp1 = tmp = rb_big2str0(val, base, RBIGNUM_SIGN(val));
			s = RSTRING_PTR(tmp);
			if (*s == '-') {
			    if (base == 10) {
				rb_warning("negative number for %%u specifier");
			    }
			    remove_sign_bits(++s, base);
			    tmp = rb_str_new(0, 3+strlen(s));
			    t = RSTRING_PTR(tmp);
			    if (!(flags&(FPREC|FZERO))) {
				strcpy(t, "..");
				t += 2;
			    }
			    switch (base) {
			      case 16:
				if (s[0] != 'f') strcpy(t++, "f"); break;
			      case 8:
				if (s[0] != '7') strcpy(t++, "7"); break;
			      case 2:
				if (s[0] != '1') strcpy(t++, "1"); break;
			    }
			    strcpy(t, s);
			    s  = RSTRING_PTR(tmp);
			}
		    }
		}

		pos = -1;
		len = strlen(s);

		if (*p == 'X') {
		    char *pp = s;
		    int c;
		    while ((c = (int)(unsigned char)*pp) != 0) {
			*pp = rb_enc_toupper(c, enc);
			pp++;
		    }
		}
		if ((flags&(FZERO|FPREC)) == FZERO) {
		    prec = width;
		    width = 0;
		}
		else {
		    if (prec < len) prec = len;
		    width -= prec;
		}
		if (!(flags&FMINUS)) {
		    CHECK(width);
		    while (width-- > 0) {
			buf[blen++] = ' ';
		    }
		}
		if (sc) PUSH(&sc, 1);
		if (prefix) {
		    int plen = strlen(prefix);
		    PUSH(prefix, plen);
		}
		CHECK(prec - len);
		if (!bignum && v < 0) {
		    char c = sign_bits(base, p);
		    while (len < prec--) {
			buf[blen++] = c;
		    }
		}
		else {
		    char c;

		    if (!sign && bignum && !RBIGNUM_SIGN(val))
			c = sign_bits(base, p);
		    else
			c = '0';
		    while (len < prec--) {
			buf[blen++] = c;
		    }
		}
		PUSH(s, len);
		CHECK(width);
		while (width-- > 0) {
		    buf[blen++] = ' ';
		}
	    }
	    break;

	  case 'f':
	  case 'g':
	  case 'G':
	  case 'e':
	  case 'E':
	    {
		VALUE val = GETARG();
		double fval;
		int i, need = 6;
		char fbuf[32];

		fval = RFLOAT_VALUE(rb_Float(val));
		if (isnan(fval) || isinf(fval)) {
		    const char *expr;

		    if  (isnan(fval)) {
			expr = "NaN";
		    }
		    else {
			expr = "Inf";
		    }
		    need = strlen(expr);
		    if ((!isnan(fval) && fval < 0.0) || (flags & FPLUS))
			need++;
		    if ((flags & FWIDTH) && need < width)
			need = width;

		    CHECK(need);
		    sprintf(&buf[blen], "%*s", need, "");
		    if (flags & FMINUS) {
			if (!isnan(fval) && fval < 0.0)
			    buf[blen++] = '-';
			else if (flags & FPLUS)
			    buf[blen++] = '+';
			else if (flags & FSPACE)
			    blen++;
			strncpy(&buf[blen], expr, strlen(expr));
		    }
		    else if (flags & FZERO) {
			if (!isnan(fval) && fval < 0.0) {
			    buf[blen++] = '-';
			    need--;
			}
			else if (flags & FPLUS) {
			    buf[blen++] = '+';
			    need--;
			}
			else if (flags & FSPACE) {
			    blen++;
			    need--;
			}
			while (need-- - strlen(expr) > 0) {
			    buf[blen++] = '0';
			}
			strncpy(&buf[blen], expr, strlen(expr));
		    }
		    else {
			if (!isnan(fval) && fval < 0.0)
			    buf[blen + need - strlen(expr) - 1] = '-';
			else if (flags & FPLUS)
			    buf[blen + need - strlen(expr) - 1] = '+';
			strncpy(&buf[blen + need - strlen(expr)], expr,
				strlen(expr));
		    }
		    blen += strlen(&buf[blen]);
		    break;
		}

		fmt_setup(fbuf, *p, flags, width, prec);
		need = 0;
		if (*p != 'e' && *p != 'E') {
		    i = INT_MIN;
		    frexp(fval, &i);
		    if (i > 0)
			need = BIT_DIGITS(i);
		}
		need += (flags&FPREC) ? prec : 6;
		if ((flags&FWIDTH) && need < width)
		    need = width;
		need += 20;

		CHECK(need);
		sprintf(&buf[blen], fbuf, fval);
		blen += strlen(&buf[blen]);
	    }
	    break;
	}
	flags = FNONE;
    }

  sprint_exit:
    /* XXX - We cannot validiate the number of arguments if (digit)$ style used.
     */
    if (posarg >= 0 && nextarg < argc) {
	const char *mesg = "too many arguments for format string";
	if (RTEST(ruby_debug)) rb_raise(rb_eArgError, mesg);
	if (RTEST(ruby_verbose)) rb_warn(mesg);
    }
    rb_str_resize(result, blen);

    if (tainted) OBJ_TAINT(result);
    return result;
}

static void
fmt_setup(char *buf, int c, int flags, int width, int prec)
{
    *buf++ = '%';
    if (flags & FSHARP) *buf++ = '#';
    if (flags & FPLUS)  *buf++ = '+';
    if (flags & FMINUS) *buf++ = '-';
    if (flags & FZERO)  *buf++ = '0';
    if (flags & FSPACE) *buf++ = ' ';

    if (flags & FWIDTH) {
	sprintf(buf, "%d", width);
	buf += strlen(buf);
    }

    if (flags & FPREC) {
	sprintf(buf, ".%d", prec);
	buf += strlen(buf);
    }

    *buf++ = c;
    *buf = '\0';
}

#undef FILE
#define FILE rb_printf_buffer
#define __sbuf rb_printf_sbuf
#define __sFILE rb_printf_sfile
#undef feof
#undef ferror
#undef clearerr
#undef fileno
#if SIZEOF_LONG < SIZEOF_VOIDP
# if  SIZEOF_LONG_LONG == SIZEOF_VOIDP
#  define _HAVE_SANE_QUAD_
#  define _HAVE_LLP64_
#  define quad_t LONG_LONG
#  define u_quad_t unsigned LONG_LONG
# endif
#endif
#undef vsnprintf
#undef snprintf
#include "missing/vsnprintf.c"

static int
ruby__sfvwrite(register rb_printf_buffer *fp, register struct __suio *uio)
{
    struct __siov *iov;
    VALUE result = (VALUE)fp->_bf._base;
    char *buf = (char*)fp->_p;
    size_t len, n;
    int blen = buf - RSTRING_PTR(result), bsiz = fp->_w;

    if (RBASIC(result)->klass) {
	rb_raise(rb_eRuntimeError, "rb_vsprintf reentered");
    }
    if ((len = uio->uio_resid) == 0)
	return 0;
    CHECK(len);
    buf += blen;
    fp->_w = bsiz;
    for (iov = uio->uio_iov; len > 0; ++iov) {
	MEMCPY(buf, iov->iov_base, char, n = iov->iov_len);
	buf += n;
	len -= n;
    }
    fp->_p = (unsigned char *)buf;
    return 0;
}

VALUE
rb_vsprintf(const char *fmt, va_list ap)
{
    rb_printf_buffer f;
    VALUE result;

    f._flags = __SWR | __SSTR;
    f._bf._size = 0;
    f._w = 120;
    result = rb_str_buf_new(f._w);
    f._bf._base = (unsigned char *)result;
    f._p = (unsigned char *)RSTRING_PTR(result);
    RBASIC(result)->klass = 0;
    f.vwrite = ruby__sfvwrite;
    BSD_vfprintf(&f, fmt, ap);
    RBASIC(result)->klass = rb_cString;
    rb_str_resize(result, (char *)f._p - RSTRING_PTR(result));

    return result;
}

VALUE
rb_sprintf(const char *format, ...)
{
    VALUE result;
    va_list ap;

    va_start(ap, format);
    result = rb_vsprintf(format, ap);
    va_end(ap);

    return result;
}
