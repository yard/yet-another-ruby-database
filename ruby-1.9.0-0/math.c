/**********************************************************************

  math.c -

  $Author: naruse $
  $Date: 2007-11-28 18:22:57 +0900 (Wed, 28 Nov 2007) $
  created at: Tue Jan 25 14:12:56 JST 1994

  Copyright (C) 1993-2007 Yukihiro Matsumoto

**********************************************************************/

#include "ruby/ruby.h"
#include <math.h>
#include <errno.h>

VALUE rb_mMath;

#define Need_Float(x) (x) = rb_Float(x)
#define Need_Float2(x,y) do {\
    Need_Float(x);\
    Need_Float(y);\
} while (0)

static void
domain_check(double x, char *msg)
{
    while(1) {
	if (errno) {
	    rb_sys_fail(msg);
	}
	if (isnan(x)) {
#if defined(EDOM)
	    errno = EDOM;
#elif defined(ERANGE)
	    errno = ERANGE;
#endif
	    continue;
	}
	break;
    }
}


/*
 *  call-seq:
 *     Math.atan2(y, x)  => float
 *  
 *  Computes the arc tangent given <i>y</i> and <i>x</i>. Returns
 *  -PI..PI.
 *     
 */

static VALUE
math_atan2(VALUE obj, VALUE y, VALUE x)
{
    Need_Float2(y, x);
    return DOUBLE2NUM(atan2(RFLOAT_VALUE(y), RFLOAT_VALUE(x)));
}


/*
 *  call-seq:
 *     Math.cos(x)    => float
 *  
 *  Computes the cosine of <i>x</i> (expressed in radians). Returns
 *  -1..1.
 */

static VALUE
math_cos(VALUE obj, VALUE x)
{
    Need_Float(x);
    return DOUBLE2NUM(cos(RFLOAT_VALUE(x)));
}

/*
 *  call-seq:
 *     Math.sin(x)    => float
 *  
 *  Computes the sine of <i>x</i> (expressed in radians). Returns
 *  -1..1.
 */

static VALUE
math_sin(VALUE obj, VALUE x)
{
    Need_Float(x);

    return DOUBLE2NUM(sin(RFLOAT_VALUE(x)));
}


/*
 *  call-seq:
 *     Math.tan(x)    => float
 *  
 *  Returns the tangent of <i>x</i> (expressed in radians).
 */

static VALUE
math_tan(VALUE obj, VALUE x)
{
    Need_Float(x);

    return DOUBLE2NUM(tan(RFLOAT_VALUE(x)));
}

/*
 *  call-seq:
 *     Math.acos(x)    => float
 *  
 *  Computes the arc cosine of <i>x</i>. Returns 0..PI.
 */

static VALUE
math_acos(VALUE obj, VALUE x)
{
    double d;

    Need_Float(x);
    errno = 0;
    d = acos(RFLOAT_VALUE(x));
    domain_check(d, "acos");
    return DOUBLE2NUM(d);
}

/*
 *  call-seq:
 *     Math.asin(x)    => float
 *  
 *  Computes the arc sine of <i>x</i>. Returns 0..PI.
 */

static VALUE
math_asin(VALUE obj, VALUE x)
{
    double d;

    Need_Float(x);
    errno = 0;
    d = asin(RFLOAT_VALUE(x));
    domain_check(d, "asin");
    return DOUBLE2NUM(d);
}

/*
 *  call-seq:
 *     Math.atan(x)    => float
 *  
 *  Computes the arc tangent of <i>x</i>. Returns -{PI/2} .. {PI/2}.
 */

static VALUE
math_atan(VALUE obj, VALUE x)
{
    Need_Float(x);
    return DOUBLE2NUM(atan(RFLOAT_VALUE(x)));
}

#ifndef HAVE_COSH
double
cosh(double x)
{
    return (exp(x) + exp(-x)) / 2;
}
#endif

/*
 *  call-seq:
 *     Math.cosh(x)    => float
 *  
 *  Computes the hyperbolic cosine of <i>x</i> (expressed in radians).
 */

static VALUE
math_cosh(VALUE obj, VALUE x)
{
    Need_Float(x);
    
    return DOUBLE2NUM(cosh(RFLOAT_VALUE(x)));
}

#ifndef HAVE_SINH
double
sinh(double x)
{
    return (exp(x) - exp(-x)) / 2;
}
#endif

/*
 *  call-seq:
 *     Math.sinh(x)    => float
 *  
 *  Computes the hyperbolic sine of <i>x</i> (expressed in
 *  radians).
 */

static VALUE
math_sinh(VALUE obj, VALUE x)
{
    Need_Float(x);
    return DOUBLE2NUM(sinh(RFLOAT_VALUE(x)));
}

#ifndef HAVE_TANH
double
tanh(double x)
{
    return sinh(x) / cosh(x);
}
#endif

/*
 *  call-seq:
 *     Math.tanh()    => float
 *  
 *  Computes the hyperbolic tangent of <i>x</i> (expressed in
 *  radians).
 */

static VALUE
math_tanh(VALUE obj, VALUE x)
{
    Need_Float(x);
    return DOUBLE2NUM(tanh(RFLOAT_VALUE(x)));
}

/*
 *  call-seq:
 *     Math.acosh(x)    => float
 *  
 *  Computes the inverse hyperbolic cosine of <i>x</i>.
 */

static VALUE
math_acosh(VALUE obj, VALUE x)
{
    double d;

    Need_Float(x);
    errno = 0;
    d = acosh(RFLOAT_VALUE(x));
    domain_check(d, "acosh");
    return DOUBLE2NUM(d);
}

/*
 *  call-seq:
 *     Math.asinh(x)    => float
 *  
 *  Computes the inverse hyperbolic sine of <i>x</i>.
 */

static VALUE
math_asinh(VALUE obj, VALUE x)
{
    Need_Float(x);
    return DOUBLE2NUM(asinh(RFLOAT_VALUE(x)));
}

/*
 *  call-seq:
 *     Math.atanh(x)    => float
 *  
 *  Computes the inverse hyperbolic tangent of <i>x</i>.
 */

static VALUE
math_atanh(VALUE obj, VALUE x)
{
    double d;

    Need_Float(x);
    errno = 0;
    d = atanh(RFLOAT_VALUE(x));
    domain_check(d, "atanh");
    return DOUBLE2NUM(d);
}

/*
 *  call-seq:
 *     Math.exp(x)    => float
 *  
 *  Returns e**x.
 */

static VALUE
math_exp(VALUE obj, VALUE x)
{
    Need_Float(x);
    return DOUBLE2NUM(exp(RFLOAT_VALUE(x)));
}

#if defined __CYGWIN__
# include <cygwin/version.h>
# if CYGWIN_VERSION_DLL_MAJOR < 1005
#  define nan(x) nan()
# endif
# define log(x) ((x) < 0.0 ? nan("") : log(x))
# define log10(x) ((x) < 0.0 ? nan("") : log10(x))
#endif

/*
 *  call-seq:
 *     Math.log(numeric)    => float
 *     Math.log(num,base)   => float
 *  
 *  Returns the natural logarithm of <i>numeric</i>.
 *  If additional second argument is given, it will be the base
 *  of logarithm.
 */

static VALUE
math_log(int argc, VALUE *argv)
{
    VALUE x, base;
    double d;

    rb_scan_args(argc, argv, "11", &x, &base);
    Need_Float(x);
    errno = 0;
    d = log(RFLOAT_VALUE(x));
    if (!NIL_P(base)) {
	Need_Float(base);
	d /= log(RFLOAT_VALUE(base));
    }
    domain_check(d, "log");
    return DOUBLE2NUM(d);
}

#ifndef log2
#ifndef HAVE_LOG2
double
log2(double x)
{
    return log10(x)/log10(2.0);
}
#else
extern double log2(double);
#endif
#endif

/*
 *  call-seq:
 *     Math.log2(numeric)    => float
 *  
 *  Returns the base 2 logarithm of <i>numeric</i>.
 */

static VALUE
math_log2(VALUE obj, VALUE x)
{
    double d;

    Need_Float(x);
    errno = 0;
    d = log2(RFLOAT_VALUE(x));
    if (errno) {
	rb_sys_fail("log2");
    }
    return DOUBLE2NUM(d);
}

/*
 *  call-seq:
 *     Math.log10(numeric)    => float
 *  
 *  Returns the base 10 logarithm of <i>numeric</i>.
 */

static VALUE
math_log10(VALUE obj, VALUE x)
{
    double d;

    Need_Float(x);
    errno = 0;
    d = log10(RFLOAT_VALUE(x));
    domain_check(d, "log10");
    return DOUBLE2NUM(d);
}

/*
 *  call-seq:
 *     Math.sqrt(numeric)    => float
 *  
 *  Returns the non-negative square root of <i>numeric</i>.
 */

static VALUE
math_sqrt(VALUE obj, VALUE x)
{
    double d;

    Need_Float(x);
    errno = 0;
    d = sqrt(RFLOAT_VALUE(x));
    domain_check(d, "sqrt");
    return DOUBLE2NUM(d);
}

/*
 *  call-seq:
 *     Math.frexp(numeric)    => [ fraction, exponent ]
 *  
 *  Returns a two-element array containing the normalized fraction (a
 *  <code>Float</code>) and exponent (a <code>Fixnum</code>) of
 *  <i>numeric</i>.
 *     
 *     fraction, exponent = Math.frexp(1234)   #=> [0.6025390625, 11]
 *     fraction * 2**exponent                  #=> 1234.0
 */

static VALUE
math_frexp(VALUE obj, VALUE x)
{
    double d;
    int exp;

    Need_Float(x);
    
    d = frexp(RFLOAT_VALUE(x), &exp);
    return rb_assoc_new(DOUBLE2NUM(d), INT2NUM(exp));
}

/*
 *  call-seq:
 *     Math.ldexp(flt, int) -> float
 *  
 *  Returns the value of <i>flt</i>*(2**<i>int</i>).
 *     
 *     fraction, exponent = Math.frexp(1234)
 *     Math.ldexp(fraction, exponent)   #=> 1234.0
 */

static VALUE
math_ldexp(VALUE obj, VALUE x, VALUE n)
{
    Need_Float(x);
    return DOUBLE2NUM(ldexp(RFLOAT_VALUE(x), NUM2INT(n)));
}

/*
 *  call-seq:
 *     Math.hypot(x, y)    => float
 *  
 *  Returns sqrt(x**2 + y**2), the hypotenuse of a right-angled triangle
 *  with sides <i>x</i> and <i>y</i>.
 *     
 *     Math.hypot(3, 4)   #=> 5.0
 */

static VALUE
math_hypot(VALUE obj, VALUE x, VALUE y)
{
    Need_Float2(x, y);
    return DOUBLE2NUM(hypot(RFLOAT_VALUE(x), RFLOAT_VALUE(y)));
}

/*
 * call-seq:
 *    Math.erf(x)  => float
 *
 *  Calculates the error function of x.
 */

static VALUE
math_erf(VALUE obj, VALUE x)
{
    Need_Float(x);
    return DOUBLE2NUM(erf(RFLOAT_VALUE(x)));
}

/*
 * call-seq:
 *    Math.erfc(x)  => float
 *
 *  Calculates the complementary error function of x.
 */

static VALUE
math_erfc(VALUE obj, VALUE x)
{
    Need_Float(x);
    return DOUBLE2NUM(erfc(RFLOAT_VALUE(x)));
}

/*
 *  The <code>Math</code> module contains module functions for basic
 *  trigonometric and transcendental functions. See class
 *  <code>Float</code> for a list of constants that
 *  define Ruby's floating point accuracy.
 */     


void
Init_Math(void)
{
    rb_mMath = rb_define_module("Math");

#ifdef M_PI
    rb_define_const(rb_mMath, "PI", DOUBLE2NUM(M_PI));
#else
    rb_define_const(rb_mMath, "PI", DOUBLE2NUM(atan(1.0)*4.0));
#endif

#ifdef M_E
    rb_define_const(rb_mMath, "E", DOUBLE2NUM(M_E));
#else
    rb_define_const(rb_mMath, "E", DOUBLE2NUM(exp(1.0)));
#endif

    rb_define_module_function(rb_mMath, "atan2", math_atan2, 2);
    rb_define_module_function(rb_mMath, "cos", math_cos, 1);
    rb_define_module_function(rb_mMath, "sin", math_sin, 1);
    rb_define_module_function(rb_mMath, "tan", math_tan, 1);

    rb_define_module_function(rb_mMath, "acos", math_acos, 1);
    rb_define_module_function(rb_mMath, "asin", math_asin, 1);
    rb_define_module_function(rb_mMath, "atan", math_atan, 1);

    rb_define_module_function(rb_mMath, "cosh", math_cosh, 1);
    rb_define_module_function(rb_mMath, "sinh", math_sinh, 1);
    rb_define_module_function(rb_mMath, "tanh", math_tanh, 1);

    rb_define_module_function(rb_mMath, "acosh", math_acosh, 1);
    rb_define_module_function(rb_mMath, "asinh", math_asinh, 1);
    rb_define_module_function(rb_mMath, "atanh", math_atanh, 1);

    rb_define_module_function(rb_mMath, "exp", math_exp, 1);
    rb_define_module_function(rb_mMath, "log", math_log, -1);
    rb_define_module_function(rb_mMath, "log2", math_log2, 1);
    rb_define_module_function(rb_mMath, "log10", math_log10, 1);
    rb_define_module_function(rb_mMath, "sqrt", math_sqrt, 1);

    rb_define_module_function(rb_mMath, "frexp", math_frexp, 1);
    rb_define_module_function(rb_mMath, "ldexp", math_ldexp, 2);

    rb_define_module_function(rb_mMath, "hypot", math_hypot, 2);

    rb_define_module_function(rb_mMath, "erf",  math_erf,  1);
    rb_define_module_function(rb_mMath, "erfc", math_erfc, 1);
}
