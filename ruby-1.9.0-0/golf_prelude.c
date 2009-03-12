#include "ruby/ruby.h"
#include "vm_core.h"

static const char prelude_name0[] = "golf_prelude.rb";
static const char prelude_code0[] =
"class Object\n"
"  def method_missing m, *a, &b\n"
"    r = /^#{m}/\n"
"    t = (methods + private_methods).sort.find{|e|r=~e}\n"
"    t ? __send__(t, *a, &b) : super\n"
"  end\n"
"\n"
"  def h(a='H', b='w', c='!')\n"
"    puts \"#{a}ello, #{b}orld#{c}\"\n"
"  end\n"
"end\n"
;

void
Init_golf(void)
{
  rb_iseq_eval(rb_iseq_compile(
    rb_str_new(prelude_code0, sizeof(prelude_code0) - 1),
    rb_str_new(prelude_name0, sizeof(prelude_name0) - 1),
    INT2FIX(1)));

#if 0
    puts(prelude_code0);
#endif
}
