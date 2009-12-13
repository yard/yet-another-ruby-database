/**********************************************************************

  debug.c -

  $Author: nobu $
  $Date: 2007-12-21 17:31:24 +0900 (Fri, 21 Dec 2007) $
  created at: 04/08/25 02:31:54 JST

  Copyright (C) 2004-2007 Koichi Sasada

**********************************************************************/

#include "ruby/ruby.h"
#include "ruby/encoding.h"
#include "debug.h"
#include "vm_core.h"

/* for gdb */
static const union {
    enum ruby_special_consts    special_consts;
    enum ruby_value_type        value_type;
    enum node_type              node_type;
    enum {
        RUBY_ENCODING_INLINE_MAX = ENCODING_INLINE_MAX,
        RUBY_ENCODING_SHIFT = ENCODING_SHIFT,
        RUBY_ENCODING_MASK  = ENCODING_MASK,
        RUBY_ENC_CODERANGE_MASK    = ENC_CODERANGE_MASK,
        RUBY_ENC_CODERANGE_UNKNOWN = ENC_CODERANGE_UNKNOWN,
        RUBY_ENC_CODERANGE_7BIT    = ENC_CODERANGE_7BIT,
        RUBY_ENC_CODERANGE_VALID   = ENC_CODERANGE_VALID,
        RUBY_ENC_CODERANGE_BROKEN  = ENC_CODERANGE_BROKEN, 
        RUBY_FL_MARK        = FL_MARK,
        RUBY_FL_RESERVED    = FL_RESERVED,
        RUBY_FL_FINALIZE    = FL_FINALIZE,
        RUBY_FL_TAINT       = FL_TAINT,
        RUBY_FL_EXIVAR      = FL_EXIVAR,
        RUBY_FL_FREEZE      = FL_FREEZE,
        RUBY_FL_SINGLETON   = FL_SINGLETON,
        RUBY_FL_USER0       = FL_USER0,
        RUBY_FL_USER1       = FL_USER1,
        RUBY_FL_USER2       = FL_USER2,
        RUBY_FL_USER3       = FL_USER3,
        RUBY_FL_USER4       = FL_USER4,
        RUBY_FL_USER5       = FL_USER5,
        RUBY_FL_USER6       = FL_USER6,
        RUBY_FL_USER7       = FL_USER7,
        RUBY_FL_USER8       = FL_USER8,
        RUBY_FL_USER9       = FL_USER9,
        RUBY_FL_USER10      = FL_USER10,
        RUBY_FL_USER11      = FL_USER11,
        RUBY_FL_USER12      = FL_USER12,
        RUBY_FL_USER13      = FL_USER13,
        RUBY_FL_USER14      = FL_USER14,
        RUBY_FL_USER15      = FL_USER15,
        RUBY_FL_USER16      = FL_USER16,
        RUBY_FL_USER17      = FL_USER17,
        RUBY_FL_USER18      = FL_USER18,
        RUBY_FL_USER19      = FL_USER19,
        RUBY_FL_USHIFT      = FL_USHIFT,
        RUBY_NODE_NEWLINE   = NODE_NEWLINE,
        RUBY_NODE_TYPESHIFT = NODE_TYPESHIFT,
        RUBY_NODE_TYPEMASK  = NODE_TYPEMASK,
        RUBY_NODE_LSHIFT    = NODE_LSHIFT,
        RUBY_NODE_LMASK     = NODE_LMASK,
    } various;
} dummy_gdb_enums;

const VALUE RUBY_FL_USER20    = FL_USER20;

void
ruby_debug_print_indent(int level, int debug_level, int indent_level)
{
    if (level < debug_level) {
	int i;
	for (i = 0; i < indent_level; i++) {
	    fprintf(stderr, " ");
	}
	fflush(stderr);
    }
}

VALUE
ruby_debug_print_value(int level, int debug_level, const char *header, VALUE obj)
{
    if (level < debug_level) {
	VALUE str;
	str = rb_inspect(obj);
	fprintf(stderr, "DBG> %s: %s\n", header,
		obj == -1 ? "" : StringValueCStr(str));
	fflush(stderr);
    }
    return obj;
}

void
ruby_debug_print_v(VALUE v)
{
    ruby_debug_print_value(0, 1, "", v);
}

ID
ruby_debug_print_id(int level, int debug_level, const char *header, ID id)
{
    if (level < debug_level) {
	fprintf(stderr, "DBG> %s: %s\n", header, rb_id2name(id));
	fflush(stderr);
    }
    return id;
}

NODE *
ruby_debug_print_node(int level, int debug_level, const char *header, const NODE *node)
{
    if (level < debug_level) {
	fprintf(stderr, "DBG> %s: %s (%lu)\n", header,
		ruby_node_name(nd_type(node)), nd_line(node));
    }
    return (NODE *)node;
}

void
ruby_debug_breakpoint(void)
{
    /* */
}

#ifdef RUBY_DEBUG_ENV
#include <ctype.h>

void
ruby_set_debug_option(const char *str)
{
    const char *end;
    int len;

    if (!str) return;
    for (; *str; str = end) {
	while (ISSPACE(*str) || *str == ',') str++;
	if (!*str) break;
	end = str;
	while (*end && !ISSPACE(*end) && *end != ',') end++;
	len = end - str;
#define SET_WHEN(name, var)		    \
	if (len == sizeof(name) - 1 &&	    \
	    strncmp(str, name, len) == 0) { \
	    extern int ruby_##var;	    \
	    ruby_##var = 1;		    \
	    continue;			    \
	}
	SET_WHEN("gc_stress", gc_stress);
	SET_WHEN("core", enable_coredump);
	fprintf(stderr, "unexpected debug option: %.*s\n", len, str);
    }
}
#endif
