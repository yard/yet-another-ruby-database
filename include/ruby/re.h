/**********************************************************************

  re.h -

  $Author: matz $
  $Date: 2007-11-23 11:10:44 +0900 (Fri, 23 Nov 2007) $
  created at: Thu Sep 30 14:18:32 JST 1993

  Copyright (C) 1993-2007 Yukihiro Matsumoto

**********************************************************************/

#ifndef RUBY_RE_H
#define RUBY_RE_H 1

#if defined(__cplusplus)
extern "C" {
#if 0
} /* satisfy cc-mode */
#endif
#endif

#include <sys/types.h>
#include <stdio.h>

#include "ruby/regex.h"

typedef struct re_pattern_buffer Regexp;

struct RMatch {
    struct RBasic basic;
    VALUE str;
    struct re_registers *regs;
    VALUE regexp;  /* RRegexp */
};

#define RMATCH(obj)  (R_CAST(RMatch)(obj))

VALUE rb_reg_regcomp(VALUE);
int rb_reg_search(VALUE, VALUE, int, int);
VALUE rb_reg_regsub(VALUE, VALUE, struct re_registers *, VALUE);
int rb_reg_adjust_startpos(VALUE, VALUE, int, int);
void rb_match_busy(VALUE);
VALUE rb_reg_quote(VALUE);

#if defined(__cplusplus)
#if 0
{ /* satisfy cc-mode */
#endif
}  /* extern "C" { */
#endif

#endif /* RUBY_RE_H */
