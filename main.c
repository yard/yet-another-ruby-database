/**********************************************************************

  main.c -

  $Author: nobu $
  $Date: 2007-12-25 16:04:30 +0900 (Tue, 25 Dec 2007) $
  created at: Fri Aug 19 13:19:58 JST 1994

  Copyright (C) 1993-2007 Yukihiro Matsumoto

**********************************************************************/

#undef RUBY_EXPORT
#include "ruby/ruby.h"
#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif

RUBY_GLOBAL_SETUP

int
main(int argc, char **argv, char **envp)
{
#ifdef RUBY_DEBUG_ENV
    extern void ruby_set_debug_option(const char *);
    ruby_set_debug_option(getenv("RUBY_DEBUG"));
#endif
#ifdef HAVE_LOCALE_H
    setlocale(LC_CTYPE, "");
#endif

    ruby_sysinit(&argc, &argv);
    {
	RUBY_INIT_STACK;
	ruby_init();
#ifdef RUBY_MAIN_INIT
	RUBY_MAIN_INIT();
#endif
	return ruby_run_node(ruby_options(argc, argv));
    }
}
