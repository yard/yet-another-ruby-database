/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     keyword_class = 258,
     keyword_module = 259,
     keyword_def = 260,
     keyword_undef = 261,
     keyword_begin = 262,
     keyword_rescue = 263,
     keyword_ensure = 264,
     keyword_end = 265,
     keyword_if = 266,
     keyword_unless = 267,
     keyword_then = 268,
     keyword_elsif = 269,
     keyword_else = 270,
     keyword_case = 271,
     keyword_when = 272,
     keyword_while = 273,
     keyword_until = 274,
     keyword_for = 275,
     keyword_break = 276,
     keyword_next = 277,
     keyword_redo = 278,
     keyword_retry = 279,
     keyword_in = 280,
     keyword_do = 281,
     keyword_do_cond = 282,
     keyword_do_block = 283,
     keyword_do_LAMBDA = 284,
     keyword_return = 285,
     keyword_yield = 286,
     keyword_super = 287,
     keyword_self = 288,
     keyword_nil = 289,
     keyword_true = 290,
     keyword_false = 291,
     keyword_and = 292,
     keyword_or = 293,
     keyword_not = 294,
     modifier_if = 295,
     modifier_unless = 296,
     modifier_while = 297,
     modifier_until = 298,
     modifier_rescue = 299,
     keyword_alias = 300,
     keyword_defined = 301,
     keyword_BEGIN = 302,
     keyword_END = 303,
     keyword__LINE__ = 304,
     keyword__FILE__ = 305,
     keyword__ENCODING__ = 306,
     tIDENTIFIER = 307,
     tFID = 308,
     tGVAR = 309,
     tIVAR = 310,
     tCONSTANT = 311,
     tCVAR = 312,
     tLABEL = 313,
     tINTEGER = 314,
     tFLOAT = 315,
     tSTRING_CONTENT = 316,
     tCHAR = 317,
     tNTH_REF = 318,
     tBACK_REF = 319,
     tREGEXP_END = 320,
     tUPLUS = 321,
     tUMINUS = 322,
     tPOW = 323,
     tCMP = 324,
     tEQ = 325,
     tEQQ = 326,
     tNEQ = 327,
     tGEQ = 328,
     tLEQ = 329,
     tANDOP = 330,
     tOROP = 331,
     tMATCH = 332,
     tNMATCH = 333,
     tDOT2 = 334,
     tDOT3 = 335,
     tAREF = 336,
     tASET = 337,
     tLSHFT = 338,
     tRSHFT = 339,
     tCOLON2 = 340,
     tCOLON3 = 341,
     tOP_ASGN = 342,
     tASSOC = 343,
     tLPAREN = 344,
     tLPAREN_ARG = 345,
     tRPAREN = 346,
     tLBRACK = 347,
     tLBRACE = 348,
     tLBRACE_ARG = 349,
     tSTAR = 350,
     tAMPER = 351,
     tLAMBDA = 352,
     tSYMBEG = 353,
     tSTRING_BEG = 354,
     tXSTRING_BEG = 355,
     tREGEXP_BEG = 356,
     tWORDS_BEG = 357,
     tQWORDS_BEG = 358,
     tSTRING_DBEG = 359,
     tSTRING_DVAR = 360,
     tSTRING_END = 361,
     tLAMBEG = 362,
     tLOWEST = 363,
     tUMINUS_NUM = 364,
     tLAST_TOKEN = 365
   };
#endif
/* Tokens.  */
#define keyword_class 258
#define keyword_module 259
#define keyword_def 260
#define keyword_undef 261
#define keyword_begin 262
#define keyword_rescue 263
#define keyword_ensure 264
#define keyword_end 265
#define keyword_if 266
#define keyword_unless 267
#define keyword_then 268
#define keyword_elsif 269
#define keyword_else 270
#define keyword_case 271
#define keyword_when 272
#define keyword_while 273
#define keyword_until 274
#define keyword_for 275
#define keyword_break 276
#define keyword_next 277
#define keyword_redo 278
#define keyword_retry 279
#define keyword_in 280
#define keyword_do 281
#define keyword_do_cond 282
#define keyword_do_block 283
#define keyword_do_LAMBDA 284
#define keyword_return 285
#define keyword_yield 286
#define keyword_super 287
#define keyword_self 288
#define keyword_nil 289
#define keyword_true 290
#define keyword_false 291
#define keyword_and 292
#define keyword_or 293
#define keyword_not 294
#define modifier_if 295
#define modifier_unless 296
#define modifier_while 297
#define modifier_until 298
#define modifier_rescue 299
#define keyword_alias 300
#define keyword_defined 301
#define keyword_BEGIN 302
#define keyword_END 303
#define keyword__LINE__ 304
#define keyword__FILE__ 305
#define keyword__ENCODING__ 306
#define tIDENTIFIER 307
#define tFID 308
#define tGVAR 309
#define tIVAR 310
#define tCONSTANT 311
#define tCVAR 312
#define tLABEL 313
#define tINTEGER 314
#define tFLOAT 315
#define tSTRING_CONTENT 316
#define tCHAR 317
#define tNTH_REF 318
#define tBACK_REF 319
#define tREGEXP_END 320
#define tUPLUS 321
#define tUMINUS 322
#define tPOW 323
#define tCMP 324
#define tEQ 325
#define tEQQ 326
#define tNEQ 327
#define tGEQ 328
#define tLEQ 329
#define tANDOP 330
#define tOROP 331
#define tMATCH 332
#define tNMATCH 333
#define tDOT2 334
#define tDOT3 335
#define tAREF 336
#define tASET 337
#define tLSHFT 338
#define tRSHFT 339
#define tCOLON2 340
#define tCOLON3 341
#define tOP_ASGN 342
#define tASSOC 343
#define tLPAREN 344
#define tLPAREN_ARG 345
#define tRPAREN 346
#define tLBRACK 347
#define tLBRACE 348
#define tLBRACE_ARG 349
#define tSTAR 350
#define tAMPER 351
#define tLAMBDA 352
#define tSYMBEG 353
#define tSTRING_BEG 354
#define tXSTRING_BEG 355
#define tREGEXP_BEG 356
#define tWORDS_BEG 357
#define tQWORDS_BEG 358
#define tSTRING_DBEG 359
#define tSTRING_DVAR 360
#define tSTRING_END 361
#define tLAMBEG 362
#define tLOWEST 363
#define tUMINUS_NUM 364
#define tLAST_TOKEN 365




/* Copy the first part of user declarations.  */
#line 13 "ripper.y"


#define YYDEBUG 1
#define YYERROR_VERBOSE 1
#define YYSTACK_USE_ALLOCA 0

#include "ruby/ruby.h"
#include "ruby/intern.h"
#include "ruby/node.h"
#include "ruby/st.h"
#include "ruby/encoding.h"
#include "id.h"
#include "regenc.h"
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

#define YYMALLOC(size)		rb_parser_malloc(parser, size)
#define YYREALLOC(ptr, size)	rb_parser_realloc(parser, ptr, size)
#define YYCALLOC(nelem, size)	rb_parser_calloc(parser, nelem, size)
#define YYFREE(ptr)		rb_parser_free(parser, ptr)
#define malloc	YYMALLOC
#define realloc	YYREALLOC
#define calloc	YYCALLOC
#define free	YYFREE

#define ID_SCOPE_SHIFT 3
#define ID_SCOPE_MASK 0x07
#define ID_LOCAL      0x00
#define ID_INSTANCE   0x01
#define ID_GLOBAL     0x03
#define ID_ATTRSET    0x04
#define ID_CONST      0x05
#define ID_CLASS      0x06
#define ID_JUNK       0x07
#define ID_INTERNAL   ID_JUNK

#define is_notop_id(id) ((id)>tLAST_TOKEN)
#define is_local_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_LOCAL)
#define is_global_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_GLOBAL)
#define is_instance_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_INSTANCE)
#define is_attrset_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_ATTRSET)
#define is_const_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_CONST)
#define is_class_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_CLASS)
#define is_junk_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_JUNK)

#define is_asgn_or_id(id) ((is_notop_id(id)) && \
	(((id)&ID_SCOPE_MASK) == ID_GLOBAL || \
	 ((id)&ID_SCOPE_MASK) == ID_INSTANCE || \
	 ((id)&ID_SCOPE_MASK) == ID_CLASS))

enum lex_state_e {
    EXPR_BEG,			/* ignore newline, +/- is a sign. */
    EXPR_END,			/* newline significant, +/- is a operator. */
    EXPR_ENDARG,		/* ditto, and unbound braces. */
    EXPR_ARG,			/* newline significant, +/- is a operator. */
    EXPR_CMDARG,		/* newline significant, +/- is a operator. */
    EXPR_MID,			/* newline significant, +/- is a operator. */
    EXPR_FNAME,			/* ignore newline, no reserved words. */
    EXPR_DOT,			/* right after `.' or `::', no reserved words. */
    EXPR_CLASS,			/* immediate after `class', no here document. */
    EXPR_VALUE,			/* alike EXPR_BEG but label is disallowed. */
};

# ifdef HAVE_LONG_LONG
typedef unsigned LONG_LONG stack_type;
# else
typedef unsigned long stack_type;
# endif

# define BITSTACK_PUSH(stack, n)	(stack = (stack<<1)|((n)&1))
# define BITSTACK_POP(stack)	(stack = stack >> 1)
# define BITSTACK_LEXPOP(stack)	(stack = (stack >> 1) | (stack & 1))
# define BITSTACK_SET_P(stack)	(stack&1)

#define COND_PUSH(n)	BITSTACK_PUSH(cond_stack, n)
#define COND_POP()	BITSTACK_POP(cond_stack)
#define COND_LEXPOP()	BITSTACK_LEXPOP(cond_stack)
#define COND_P()	BITSTACK_SET_P(cond_stack)

#define CMDARG_PUSH(n)	BITSTACK_PUSH(cmdarg_stack, n)
#define CMDARG_POP()	BITSTACK_POP(cmdarg_stack)
#define CMDARG_LEXPOP()	BITSTACK_LEXPOP(cmdarg_stack)
#define CMDARG_P()	BITSTACK_SET_P(cmdarg_stack)

/* must sync with real YYSTYPE */
union tmpyystype {
    VALUE val;
    NODE *node;
    unsigned long id;
    int num;
    struct RVarmap *vars;
};

struct vtable {
    ID *tbl;
    int pos;
    int capa;
    struct vtable *prev;
};

struct local_vars {
    struct vtable *args;
    struct vtable *vars;
    struct local_vars *prev;
};

#define DVARS_INHERIT ((void*)1)
#define DVARS_TOPSCOPE NULL
#define DVARS_SPECIAL_P(tbl) (!POINTER_P(tbl))
#define POINTER_P(val) ((VALUE)(val) & ~(VALUE)3)

#ifndef RIPPER
static int
vtable_size(const struct vtable *tbl)
{
    if (POINTER_P(tbl)) {
        return tbl->pos;
    }
    else {
        return 0;
    }
}

#define VTBL_DEBUG 0

static struct vtable *
vtable_alloc(struct vtable *prev)
{
    struct vtable *tbl = ALLOC(struct vtable);
    tbl->pos = 0;
    tbl->capa = 8;
    tbl->tbl = ALLOC_N(ID, tbl->capa);
    tbl->prev = prev;
    if (VTBL_DEBUG) printf("vtable_alloc: %p\n", tbl);
    return tbl;
}

static void
vtable_free(struct vtable *tbl)
{
    if (VTBL_DEBUG)printf("vtable_free: %p\n", tbl);
    if (POINTER_P(tbl)) {
        if (tbl->tbl) {
            xfree(tbl->tbl);
        }
        if (tbl) {
            xfree(tbl);
        }
    }
}

static void
vtable_add(struct vtable *tbl, ID id)
{
    if (!POINTER_P(tbl)) {
        rb_bug("vtable_add: vtable is not allocated (%p)", tbl);
    }
    if (VTBL_DEBUG) printf("vtable_add: %p, %s\n", tbl, rb_id2name(id));

    if (tbl->pos == tbl->capa) {
        tbl->capa = tbl->capa * 2;
        REALLOC_N(tbl->tbl, ID, tbl->capa);
    }
    tbl->tbl[tbl->pos++] = id;
}

static int
vtable_included(const struct vtable * tbl, ID id)
{
    int i;

    if (POINTER_P(tbl)) {
        for (i = 0; i < tbl->pos; i++) {
            if (tbl->tbl[i] == id) {
                return 1;
            }
        }
    }
    return 0;
}
#endif

/*
    Structure of Lexer Buffer:

 lex_pbeg      tokp         lex_p        lex_pend
    |           |              |            |
    |-----------+--------------+------------|
                |<------------>|
                     token
*/
struct parser_params {
    int is_ripper;
    NODE *heap;

    union tmpyystype *parser_yylval;   /* YYSTYPE not defined yet */
    VALUE eofp;

    NODE *parser_lex_strterm;
    enum lex_state_e parser_lex_state;
    stack_type parser_cond_stack;
    stack_type parser_cmdarg_stack;
    int parser_class_nest;
    int parser_paren_nest;
    int parser_lpar_beg;
    int parser_in_single;
    int parser_in_def;
    int parser_compile_for_eval;
    VALUE parser_cur_mid;
    int parser_in_defined;
    char *parser_tokenbuf;
    int parser_tokidx;
    int parser_toksiz;
    VALUE parser_lex_input;
    VALUE parser_lex_lastline;
    VALUE parser_lex_nextline;
    const char *parser_lex_pbeg;
    const char *parser_lex_p;
    const char *parser_lex_pend;
    int parser_heredoc_end;
    int parser_command_start;
    int parser_lex_gets_ptr;
    VALUE (*parser_lex_gets)(struct parser_params*,VALUE);
    struct local_vars *parser_lvtbl;
    int parser_ruby__end__seen;
    int line_count;
    int has_shebang;
    char *parser_ruby_sourcefile; /* current source file */
    int parser_ruby_sourceline;	/* current line no. */
    rb_encoding *enc;
    rb_encoding *utf8;

    int parser_yydebug;

#ifndef RIPPER
    /* Ruby core only */
    NODE *parser_eval_tree_begin;
    NODE *parser_eval_tree;
    VALUE debug_lines;
    int nerr;
#else
    /* Ripper only */
    VALUE parser_ruby_sourcefile_string;
    const char *tokp;
    VALUE delayed;
    int delayed_line;
    int delayed_col;

    VALUE value;
    VALUE result;
    VALUE parsing_thread;
    int toplevel_p;
#endif
};

#define UTF8_ENC() (parser->utf8 ? parser->utf8 : \
		    (parser->utf8 = rb_utf8_encoding()))
#define STR_NEW(p,n) rb_enc_str_new((p),(n),parser->enc)
#define STR_NEW0() rb_str_new(0,0)
#define STR_NEW2(p) rb_enc_str_new((p),strlen(p),parser->enc)
#define STR_NEW3(p,n,e,func) parser_str_new((p),(n),(e),(func))
#define STR_ENC(m) ((m)?parser->enc:rb_enc_from_index(0))
#define ENC_SINGLE(cr) ((cr)==ENC_CODERANGE_7BIT)
#define TOK_INTERN(mb) rb_intern3(tok(), toklen(), STR_ENC(mb))

#ifdef YYMALLOC
void *rb_parser_malloc(struct parser_params *, size_t);
void *rb_parser_realloc(struct parser_params *, void *, size_t);
void *rb_parser_calloc(struct parser_params *, size_t, size_t);
void rb_parser_free(struct parser_params *, void *);
#endif

static int parser_yyerror(struct parser_params*, const char*);
#define yyerror(msg) parser_yyerror(parser, msg)

#define YYLEX_PARAM parser

#define lex_strterm		(parser->parser_lex_strterm)
#define lex_state		(parser->parser_lex_state)
#define cond_stack		(parser->parser_cond_stack)
#define cmdarg_stack		(parser->parser_cmdarg_stack)
#define class_nest		(parser->parser_class_nest)
#define paren_nest		(parser->parser_paren_nest)
#define lpar_beg		(parser->parser_lpar_beg)
#define in_single		(parser->parser_in_single)
#define in_def			(parser->parser_in_def)
#define compile_for_eval	(parser->parser_compile_for_eval)
#define cur_mid			(parser->parser_cur_mid)
#define in_defined		(parser->parser_in_defined)
#define tokenbuf		(parser->parser_tokenbuf)
#define tokidx			(parser->parser_tokidx)
#define toksiz			(parser->parser_toksiz)
#define lex_input		(parser->parser_lex_input)
#define lex_lastline		(parser->parser_lex_lastline)
#define lex_nextline		(parser->parser_lex_nextline)
#define lex_pbeg		(parser->parser_lex_pbeg)
#define lex_p			(parser->parser_lex_p)
#define lex_pend		(parser->parser_lex_pend)
#define heredoc_end		(parser->parser_heredoc_end)
#define command_start		(parser->parser_command_start)
#define lex_gets_ptr		(parser->parser_lex_gets_ptr)
#define lex_gets		(parser->parser_lex_gets)
#define lvtbl			(parser->parser_lvtbl)
#define ruby__end__seen		(parser->parser_ruby__end__seen)
#define ruby_sourceline		(parser->parser_ruby_sourceline)
#define ruby_sourcefile		(parser->parser_ruby_sourcefile)
#define yydebug			(parser->parser_yydebug)
#ifdef RIPPER
#else
#define ruby_eval_tree		(parser->parser_eval_tree)
#define ruby_eval_tree_begin	(parser->parser_eval_tree_begin)
#define ruby_debug_lines	(parser->debug_lines)
#endif

static int yylex(void*, void*);

#ifndef RIPPER
#define yyparse ruby_yyparse

static NODE* node_newnode(struct parser_params *, enum node_type, VALUE, VALUE, VALUE);
#define rb_node_newnode(type, a1, a2, a3) node_newnode(parser, type, a1, a2, a3)

static NODE *cond_gen(struct parser_params*,NODE*);
#define cond(node) cond_gen(parser, node)
static NODE *logop_gen(struct parser_params*,enum node_type,NODE*,NODE*);
#define logop(type,node1,node2) logop_gen(parser, type, node1, node2)

static NODE *newline_node(NODE*);
static void fixpos(NODE*,NODE*);

static int value_expr_gen(struct parser_params*,NODE*);
static void void_expr_gen(struct parser_params*,NODE*);
static NODE *remove_begin(NODE*);
#define value_expr(node) value_expr_gen(parser, (node) = remove_begin(node))
#define void_expr0(node) void_expr_gen(parser, (node))
#define void_expr(node) void_expr0((node) = remove_begin(node))
static void void_stmts_gen(struct parser_params*,NODE*);
#define void_stmts(node) void_stmts_gen(parser, node)
static void reduce_nodes_gen(struct parser_params*,NODE**);
#define reduce_nodes(n) reduce_nodes_gen(parser,n)
static void block_dup_check_gen(struct parser_params*,NODE*,NODE*);
#define block_dup_check(n1,n2) block_dup_check_gen(parser,n1,n2)

static NODE *block_append_gen(struct parser_params*,NODE*,NODE*);
#define block_append(h,t) block_append_gen(parser,h,t)
static NODE *list_append_gen(struct parser_params*,NODE*,NODE*);
#define list_append(l,i) list_append_gen(parser,l,i)
static NODE *list_concat_gen(struct parser_params*,NODE*,NODE*);
#define list_concat(h,t) list_concat_gen(parser,h,t)
static NODE *arg_append_gen(struct parser_params*,NODE*,NODE*);
#define arg_append(h,t) arg_append_gen(parser,h,t)
static NODE *arg_concat_gen(struct parser_params*,NODE*,NODE*);
#define arg_concat(h,t) arg_concat_gen(parser,h,t)
static NODE *literal_concat_gen(struct parser_params*,NODE*,NODE*);
#define literal_concat(h,t) literal_concat_gen(parser,h,t)
static NODE *new_evstr_gen(struct parser_params*,NODE*);
#define new_evstr(n) new_evstr_gen(parser,n)
static NODE *evstr2dstr_gen(struct parser_params*,NODE*);
#define evstr2dstr(n) evstr2dstr_gen(parser,n)

static NODE *call_bin_op_gen(struct parser_params*,NODE*,ID,NODE*);
#define call_bin_op(recv,id,arg1) call_bin_op_gen(parser, recv,id,arg1)
static NODE *call_uni_op_gen(struct parser_params*,NODE*,ID);
#define call_uni_op(recv,id) call_uni_op_gen(parser, recv,id)

static NODE *new_args_gen(struct parser_params*,NODE*,NODE*,ID,NODE*,ID);
#define new_args(f,o,r,p,b) new_args_gen(parser, f,o,r,p,b)
static void shadowing_lvar_gen(struct parser_params*,ID);
#define shadowing_lvar(name) shadowing_lvar_gen(parser, name)

static NODE *negate_lit(NODE*);
static NODE *ret_args_gen(struct parser_params*,NODE*);
#define ret_args(node) ret_args_gen(parser, node)
static NODE *arg_blk_pass(NODE*,NODE*);
static NODE *new_yield_gen(struct parser_params*,NODE*);
#define new_yield(node) new_yield_gen(parser, node)

static NODE *gettable_gen(struct parser_params*,ID);
#define gettable(id) gettable_gen(parser,id)
static NODE *assignable_gen(struct parser_params*,ID,NODE*);
#define assignable(id,node) assignable_gen(parser, id, node)
static void new_bv_gen(struct parser_params*,ID);
#define new_bv(id) new_bv_gen(parser, id)
static NODE *aryset_gen(struct parser_params*,NODE*,NODE*);
#define aryset(node1,node2) aryset_gen(parser, node1, node2)
static NODE *attrset_gen(struct parser_params*,NODE*,ID);
#define attrset(node,id) attrset_gen(parser, node, id)

static void rb_backref_error_gen(struct parser_params*,NODE*);
#define rb_backref_error(n) rb_backref_error_gen(parser,n)
static NODE *node_assign_gen(struct parser_params*,NODE*,NODE*);
#define node_assign(node1, node2) node_assign_gen(parser, node1, node2)

static NODE *match_op_gen(struct parser_params*,NODE*,NODE*);
#define match_op(node1,node2) match_op_gen(parser, node1, node2)

static void local_push_gen(struct parser_params*,int);
#define local_push(top) local_push_gen(parser,top)
static void local_pop_gen(struct parser_params*);
#define local_pop() local_pop_gen(parser)
static int local_var_gen(struct parser_params*, ID);
#define local_var(id) local_var_gen(parser, id);
static int arg_var_gen(struct parser_params*, ID);
#define arg_var(id) arg_var_gen(parser, id)
static int  local_id_gen(struct parser_params*, ID);
#define local_id(id) local_id_gen(parser, id)
static ID  *local_tbl_gen(struct parser_params*);
#define local_tbl() local_tbl_gen(parser)
static ID   internal_id_gen(struct parser_params*);
#define internal_id() internal_id_gen(parser)

static void dyna_push_gen(struct parser_params*);
#define dyna_push() dyna_push_gen(parser)
static void dyna_pop_gen(struct parser_params*);
#define dyna_pop() dyna_pop_gen(parser)
static int dyna_in_block_gen(struct parser_params*);
#define dyna_in_block() dyna_in_block_gen(parser)
#define dyna_var(id) local_var(id)
static int dvar_defined_gen(struct parser_params*,ID);
#define dvar_defined(id) dvar_defined_gen(parser, id)
static int dvar_curr_gen(struct parser_params*,ID);
#define dvar_curr(id) dvar_curr_gen(parser, id)

extern int rb_dvar_defined(ID);
extern int rb_local_defined(ID);
extern int rb_parse_in_eval(void);

static VALUE reg_compile_gen(struct parser_params*, VALUE, int);
#define reg_compile(str,options) reg_compile_gen(parser, str, options)
static void reg_fragment_setenc_gen(struct parser_params*, VALUE, int);
#define reg_fragment_setenc(str,options) reg_fragment_setenc_gen(parser, str, options)
static void reg_fragment_check_gen(struct parser_params*, VALUE, int);
#define reg_fragment_check(str,options) reg_fragment_check_gen(parser, str, options)
static NODE *reg_named_capture_assign_gen(struct parser_params* parser, VALUE regexp, NODE *match);
#define reg_named_capture_assign(regexp,match) reg_named_capture_assign_gen(parser,regexp,match)
int rb_enc_symname2_p(const char *, int, rb_encoding *);
#else
#define remove_begin(node) (node)
#endif /* !RIPPER */
static int lvar_defined_gen(struct parser_params*, ID);
#define lvar_defined(id) lvar_defined_gen(parser, id)

#define RE_OPTION_ONCE (1<<16)
#define RE_OPTION_ENCODING_SHIFT 8
#define RE_OPTION_ENCODING(e) (((e)&0xff)<<RE_OPTION_ENCODING_SHIFT)
#define RE_OPTION_ENCODING_IDX(o) (((o)>>RE_OPTION_ENCODING_SHIFT)&0xff)
#define RE_OPTION_MASK  0xff

#define NODE_STRTERM NODE_ZARRAY	/* nothing to gc */
#define NODE_HEREDOC NODE_ARRAY 	/* 1, 3 to gc */
#define SIGN_EXTEND(x,n) (((1<<(n)-1)^((x)&~(~0<<(n))))-(1<<(n)-1))
#define nd_func u1.id
#if SIZEOF_SHORT == 2
#define nd_term(node) ((signed short)(node)->u2.id)
#else
#define nd_term(node) SIGN_EXTEND((node)->u2.id, CHAR_BIT*2)
#endif
#define nd_paren(node) (char)((node)->u2.id >> CHAR_BIT*2)
#define nd_nest u3.cnt

/****** Ripper *******/

#ifdef RIPPER
#define RIPPER_VERSION "0.1.0"

#include "eventids1.c"
#include "eventids2.c"
static ID ripper_id_gets;

static VALUE ripper_dispatch0(struct parser_params*,ID);
static VALUE ripper_dispatch1(struct parser_params*,ID,VALUE);
static VALUE ripper_dispatch2(struct parser_params*,ID,VALUE,VALUE);
static VALUE ripper_dispatch3(struct parser_params*,ID,VALUE,VALUE,VALUE);
static VALUE ripper_dispatch4(struct parser_params*,ID,VALUE,VALUE,VALUE,VALUE);
static VALUE ripper_dispatch5(struct parser_params*,ID,VALUE,VALUE,VALUE,VALUE,VALUE);

#define dispatch0(n)            ripper_dispatch0(parser, TOKEN_PASTE(ripper_id_, n))
#define dispatch1(n,a)          ripper_dispatch1(parser, TOKEN_PASTE(ripper_id_, n), a)
#define dispatch2(n,a,b)        ripper_dispatch2(parser, TOKEN_PASTE(ripper_id_, n), a, b)
#define dispatch3(n,a,b,c)      ripper_dispatch3(parser, TOKEN_PASTE(ripper_id_, n), a, b, c)
#define dispatch4(n,a,b,c,d)    ripper_dispatch4(parser, TOKEN_PASTE(ripper_id_, n), a, b, c, d)
#define dispatch5(n,a,b,c,d,e)  ripper_dispatch5(parser, TOKEN_PASTE(ripper_id_, n), a, b, c, d, e)

#define yyparse ripper_yyparse

static VALUE ripper_intern(const char*);
static VALUE ripper_id2sym(ID);

#define arg_new() dispatch0(args_new)
#define arg_add(l,a) dispatch2(args_add, l, a)
#define arg_prepend(l,a) dispatch2(args_prepend, l, a)
#define arg_add_star(l,a) dispatch2(args_add_star, l, a)
#define arg_add_block(l,b) dispatch2(args_add_block, l, b)
#define arg_add_optblock(l,b) ((b)==Qundef? l : dispatch2(args_add_block, l, b))
#define bare_assoc(v) dispatch1(bare_assoc_hash, v)
#define arg_add_assocs(l,b) arg_add(l, bare_assoc(b))

#define args2mrhs(a) dispatch1(mrhs_new_from_args, a)
#define mrhs_new() dispatch0(mrhs_new)
#define mrhs_add(l,a) dispatch2(mrhs_add, l, a)
#define mrhs_add_star(l,a) dispatch2(mrhs_add_star, l, a)

#define mlhs_new() dispatch0(mlhs_new)
#define mlhs_add(l,a) dispatch2(mlhs_add, l, a)
#define mlhs_add_star(l,a) dispatch2(mlhs_add_star, l, a)

#define params_new(pars, opts, rest, pars2, blk) \
        dispatch5(params, pars, opts, rest, pars2, blk)

#define blockvar_new(p,v) dispatch2(block_var, p, v)
#define blockvar_add_star(l,a) dispatch2(block_var_add_star, l, a)
#define blockvar_add_block(l,a) dispatch2(block_var_add_block, l, a)

#define method_optarg(m,a) ((a)==Qundef ? m : dispatch2(method_add_arg,m,a))
#define method_arg(m,a) dispatch2(method_add_arg,m,a)
#define method_add_block(m,b) dispatch2(method_add_block, m, b)

#define escape_Qundef(x) ((x)==Qundef ? Qnil : (x))

#define FIXME 0

#endif /* RIPPER */

#ifndef RIPPER
# define ifndef_ripper(x) x
#else
# define ifndef_ripper(x)
#endif

#ifndef RIPPER
# define rb_warn0(fmt)    rb_compile_warn(ruby_sourcefile, ruby_sourceline, fmt)
# define rb_warnI(fmt,a)  rb_compile_warn(ruby_sourcefile, ruby_sourceline, fmt, a)
# define rb_warnS(fmt,a)  rb_compile_warn(ruby_sourcefile, ruby_sourceline, fmt, a)
# define rb_warning0(fmt) rb_compile_warning(ruby_sourcefile, ruby_sourceline, fmt)
# define rb_warningS(fmt,a) rb_compile_warning(ruby_sourcefile, ruby_sourceline, fmt, a)
#else
# define rb_warn0(fmt)    ripper_warn0(parser, fmt)
# define rb_warnI(fmt,a)  ripper_warnI(parser, fmt, a)
# define rb_warnS(fmt,a)  ripper_warnS(parser, fmt, a)
# define rb_warning0(fmt) ripper_warning0(parser, fmt)
# define rb_warningS(fmt,a) ripper_warningS(parser, fmt, a)
static void ripper_warn0(struct parser_params*, const char*);
static void ripper_warnI(struct parser_params*, const char*, int);
static void ripper_warnS(struct parser_params*, const char*, const char*);
static void ripper_warning0(struct parser_params*, const char*);
#if 0				/* unused in ripper right now */
static void ripper_warningS(struct parser_params*, const char*, const char*);
#endif
#endif

#ifdef RIPPER
static void ripper_compile_error(struct parser_params*, const char *fmt, ...);
# define rb_compile_error ripper_compile_error
# define compile_error ripper_compile_error
# define PARSER_ARG parser,
#else
# define compile_error parser->nerr++,rb_compile_error
# define PARSER_ARG ruby_sourcefile, ruby_sourceline,
#endif

/* Older versions of Yacc set YYMAXDEPTH to a very low value by default (150,
   for instance).  This is too low for Ruby to parse some files, such as
   date/format.rb, therefore bump the value up to at least Bison's default. */
#ifdef OLD_YACC
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif
#endif



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 588 "ripper.y"
{
    VALUE val;
    NODE *node;
    ID id;
    int num;
    struct RVarmap *vars;
}
/* Line 187 of yacc.c.  */
#line 896 "parse.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 909 "parse.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   9758

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  138
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  157
/* YYNRULES -- Number of rules.  */
#define YYNRULES  539
/* YYNRULES -- Number of states.  */
#define YYNSTATES  934

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   365

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     137,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,   136,   123,     2,     2,     2,   121,   116,     2,
     132,   133,   119,   117,   130,   118,   129,   120,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   111,   135,
     113,   109,   112,   110,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   128,     2,   134,   115,     2,   131,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   126,   114,   127,   124,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   122,   125
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    12,    15,    17,    19,    23,
      26,    27,    32,    36,    40,    44,    47,    51,    55,    59,
      63,    67,    68,    74,    79,    83,    87,    91,    98,   104,
     110,   116,   120,   124,   128,   132,   134,   136,   140,   144,
     147,   150,   152,   154,   156,   158,   161,   164,   167,   169,
     174,   179,   180,   186,   189,   193,   198,   204,   209,   215,
     218,   221,   223,   227,   229,   233,   235,   238,   242,   248,
     251,   256,   259,   264,   266,   270,   272,   276,   279,   283,
     285,   289,   291,   296,   300,   304,   308,   312,   315,   317,
     319,   324,   328,   332,   336,   340,   343,   345,   347,   349,
     352,   354,   358,   360,   362,   364,   366,   368,   370,   372,
     374,   376,   378,   379,   384,   386,   388,   390,   392,   394,
     396,   398,   400,   402,   404,   406,   408,   410,   412,   414,
     416,   418,   420,   422,   424,   426,   428,   430,   432,   434,
     436,   438,   440,   442,   444,   446,   448,   450,   452,   454,
     456,   458,   460,   462,   464,   466,   468,   470,   472,   474,
     476,   478,   480,   482,   484,   486,   488,   490,   492,   494,
     496,   498,   500,   502,   504,   506,   508,   510,   512,   514,
     516,   518,   520,   522,   524,   528,   534,   538,   545,   551,
     557,   563,   569,   574,   578,   582,   586,   590,   594,   598,
     602,   606,   610,   615,   620,   623,   626,   630,   634,   638,
     642,   646,   650,   654,   658,   662,   666,   670,   674,   678,
     681,   684,   688,   692,   696,   700,   701,   706,   713,   715,
     717,   719,   722,   727,   730,   734,   736,   738,   740,   742,
     744,   747,   750,   755,   757,   762,   766,   769,   774,   781,
     783,   784,   787,   789,   790,   794,   795,   800,   803,   806,
     808,   810,   813,   817,   822,   826,   831,   834,   836,   838,
     840,   842,   844,   846,   848,   850,   852,   853,   858,   859,
     864,   868,   872,   875,   879,   883,   885,   890,   894,   896,
     897,   904,   907,   909,   912,   915,   922,   929,   930,   931,
     939,   940,   941,   949,   955,   960,   961,   962,   972,   973,
     980,   981,   982,   991,   992,   998,   999,  1006,  1007,  1008,
    1018,  1020,  1022,  1024,  1026,  1028,  1030,  1032,  1035,  1037,
    1039,  1041,  1047,  1049,  1052,  1054,  1056,  1058,  1062,  1064,
    1068,  1070,  1075,  1082,  1086,  1092,  1095,  1100,  1102,  1106,
    1111,  1114,  1121,  1124,  1127,  1132,  1134,  1136,  1138,  1142,
    1144,  1149,  1151,  1154,  1156,  1160,  1162,  1164,  1165,  1169,
    1174,  1177,  1181,  1185,  1186,  1192,  1195,  1200,  1205,  1208,
    1213,  1218,  1222,  1226,  1230,  1233,  1235,  1240,  1241,  1247,
    1248,  1254,  1260,  1262,  1264,  1271,  1273,  1275,  1277,  1279,
    1282,  1284,  1287,  1289,  1291,  1293,  1295,  1297,  1299,  1301,
    1304,  1308,  1312,  1316,  1320,  1324,  1325,  1329,  1331,  1334,
    1338,  1342,  1343,  1347,  1348,  1351,  1352,  1355,  1357,  1358,
    1362,  1363,  1368,  1370,  1372,  1374,  1376,  1379,  1381,  1383,
    1385,  1387,  1391,  1393,  1395,  1398,  1401,  1403,  1405,  1407,
    1409,  1411,  1413,  1415,  1417,  1419,  1421,  1423,  1425,  1427,
    1429,  1431,  1433,  1435,  1436,  1441,  1444,  1448,  1451,  1458,
    1467,  1472,  1479,  1484,  1491,  1494,  1499,  1506,  1509,  1514,
    1517,  1522,  1524,  1525,  1527,  1529,  1531,  1533,  1535,  1537,
    1539,  1543,  1545,  1549,  1553,  1555,  1559,  1561,  1563,  1566,
    1568,  1570,  1572,  1575,  1578,  1580,  1582,  1583,  1588,  1590,
    1593,  1595,  1599,  1603,  1606,  1608,  1610,  1612,  1614,  1616,
    1618,  1620,  1622,  1624,  1626,  1628,  1630,  1631,  1633,  1634,
    1636,  1639,  1642,  1643,  1645,  1647,  1649,  1651,  1653,  1656
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     139,     0,    -1,    -1,   140,   142,    -1,   142,   234,   210,
     237,    -1,   143,   287,    -1,   294,    -1,   144,    -1,   143,
     293,   144,    -1,     1,   144,    -1,    -1,    45,   166,   145,
     166,    -1,    45,    54,    54,    -1,    45,    54,    64,    -1,
      45,    54,    63,    -1,     6,   167,    -1,   144,    40,   148,
      -1,   144,    41,   148,    -1,   144,    42,   148,    -1,   144,
      43,   148,    -1,   144,    44,   144,    -1,    -1,    47,   146,
     126,   142,   127,    -1,    48,   126,   142,   127,    -1,   161,
     109,   149,    -1,   154,   109,   149,    -1,   261,    87,   149,
      -1,   206,   128,   177,   290,    87,   149,    -1,   206,   129,
      52,    87,   149,    -1,   206,   129,    56,    87,   149,    -1,
     206,    85,    52,    87,   149,    -1,   262,    87,   149,    -1,
     161,   109,   188,    -1,   154,   109,   173,    -1,   154,   109,
     188,    -1,   147,    -1,   149,    -1,   147,    37,   147,    -1,
     147,    38,   147,    -1,    39,   147,    -1,   123,   149,    -1,
     171,    -1,   147,    -1,   153,    -1,   150,    -1,    30,   178,
      -1,    21,   178,    -1,    22,   178,    -1,   227,    -1,   227,
     129,   284,   180,    -1,   227,    85,   284,   180,    -1,    -1,
      94,   152,   216,   142,   127,    -1,   283,   180,    -1,   283,
     180,   151,    -1,   206,   129,   284,   180,    -1,   206,   129,
     284,   180,   151,    -1,   206,    85,   284,   180,    -1,   206,
      85,   284,   180,   151,    -1,    32,   180,    -1,    31,   180,
      -1,   156,    -1,    89,   155,   289,    -1,   156,    -1,    89,
     155,   289,    -1,   158,    -1,   158,   157,    -1,   158,    95,
     160,    -1,   158,    95,   160,   130,   159,    -1,   158,    95,
      -1,   158,    95,   130,   159,    -1,    95,   160,    -1,    95,
     160,   130,   159,    -1,    95,    -1,    95,   130,   159,    -1,
     160,    -1,    89,   155,   289,    -1,   157,   130,    -1,   158,
     157,   130,    -1,   157,    -1,   159,   130,   157,    -1,   259,
      -1,   206,   128,   177,   290,    -1,   206,   129,    52,    -1,
     206,    85,    52,    -1,   206,   129,    56,    -1,   206,    85,
      56,    -1,    86,    56,    -1,   262,    -1,   259,    -1,   206,
     128,   177,   290,    -1,   206,   129,    52,    -1,   206,    85,
      52,    -1,   206,   129,    56,    -1,   206,    85,    56,    -1,
      86,    56,    -1,   262,    -1,    52,    -1,    56,    -1,    86,
     162,    -1,   162,    -1,   206,    85,   162,    -1,    52,    -1,
      56,    -1,    53,    -1,   169,    -1,   170,    -1,   164,    -1,
     255,    -1,   165,    -1,   257,    -1,   166,    -1,    -1,   167,
     130,   168,   166,    -1,   114,    -1,   115,    -1,   116,    -1,
      69,    -1,    70,    -1,    71,    -1,    77,    -1,    78,    -1,
     112,    -1,    73,    -1,   113,    -1,    74,    -1,    72,    -1,
      83,    -1,    84,    -1,   117,    -1,   118,    -1,   119,    -1,
      95,    -1,   120,    -1,   121,    -1,    68,    -1,   123,    -1,
     124,    -1,    66,    -1,    67,    -1,    81,    -1,    82,    -1,
     131,    -1,    49,    -1,    50,    -1,    51,    -1,    47,    -1,
      48,    -1,    45,    -1,    37,    -1,     7,    -1,    21,    -1,
      16,    -1,     3,    -1,     5,    -1,    46,    -1,    26,    -1,
      15,    -1,    14,    -1,    10,    -1,     9,    -1,    36,    -1,
      20,    -1,    25,    -1,     4,    -1,    22,    -1,    34,    -1,
      39,    -1,    38,    -1,    23,    -1,     8,    -1,    24,    -1,
      30,    -1,    33,    -1,    32,    -1,    13,    -1,    35,    -1,
       6,    -1,    17,    -1,    31,    -1,    11,    -1,    12,    -1,
      18,    -1,    19,    -1,   161,   109,   171,    -1,   161,   109,
     171,    44,   171,    -1,   261,    87,   171,    -1,   206,   128,
     177,   290,    87,   171,    -1,   206,   129,    52,    87,   171,
      -1,   206,   129,    56,    87,   171,    -1,   206,    85,    52,
      87,   171,    -1,   206,    85,    56,    87,   171,    -1,    86,
      56,    87,   171,    -1,   262,    87,   171,    -1,   171,    79,
     171,    -1,   171,    80,   171,    -1,   171,   117,   171,    -1,
     171,   118,   171,    -1,   171,   119,   171,    -1,   171,   120,
     171,    -1,   171,   121,   171,    -1,   171,    68,   171,    -1,
     122,    59,    68,   171,    -1,   122,    60,    68,   171,    -1,
      66,   171,    -1,    67,   171,    -1,   171,   114,   171,    -1,
     171,   115,   171,    -1,   171,   116,   171,    -1,   171,    69,
     171,    -1,   171,   112,   171,    -1,   171,    73,   171,    -1,
     171,   113,   171,    -1,   171,    74,   171,    -1,   171,    70,
     171,    -1,   171,    71,   171,    -1,   171,    72,   171,    -1,
     171,    77,   171,    -1,   171,    78,   171,    -1,   123,   171,
      -1,   124,   171,    -1,   171,    83,   171,    -1,   171,    84,
     171,    -1,   171,    75,   171,    -1,   171,    76,   171,    -1,
      -1,    46,   288,   172,   171,    -1,   171,   110,   171,   288,
     111,   171,    -1,   189,    -1,   171,    -1,   294,    -1,   187,
     291,    -1,   187,   130,   281,   291,    -1,   281,   291,    -1,
     132,   177,   289,    -1,   294,    -1,   175,    -1,   294,    -1,
     178,    -1,   153,    -1,   187,   186,    -1,   281,   186,    -1,
     187,   130,   281,   186,    -1,   185,    -1,   173,   130,   187,
     186,    -1,   173,   130,   185,    -1,   281,   186,    -1,   173,
     130,   281,   186,    -1,   173,   130,   187,   130,   281,   186,
      -1,   185,    -1,    -1,   181,   182,    -1,   178,    -1,    -1,
      90,   183,   289,    -1,    -1,    90,   179,   184,   289,    -1,
      96,   173,    -1,   130,   185,    -1,   294,    -1,   173,    -1,
      95,   173,    -1,   187,   130,   173,    -1,   187,   130,    95,
     173,    -1,   187,   130,   173,    -1,   187,   130,    95,   173,
      -1,    95,   173,    -1,   238,    -1,   239,    -1,   242,    -1,
     243,    -1,   244,    -1,   247,    -1,   260,    -1,   262,    -1,
      53,    -1,    -1,     7,   190,   141,    10,    -1,    -1,    90,
     147,   191,   289,    -1,    89,   142,   133,    -1,   206,    85,
      56,    -1,    86,    56,    -1,    92,   174,   134,    -1,    93,
     280,   127,    -1,    30,    -1,    31,   132,   178,   289,    -1,
      31,   132,   289,    -1,    31,    -1,    -1,    46,   288,   132,
     192,   147,   289,    -1,   283,   229,    -1,   228,    -1,   228,
     229,    -1,    97,   221,    -1,    11,   148,   207,   142,   209,
      10,    -1,    12,   148,   207,   142,   210,    10,    -1,    -1,
      -1,    18,   193,   148,   208,   194,   142,    10,    -1,    -1,
      -1,    19,   195,   148,   208,   196,   142,    10,    -1,    16,
     148,   287,   232,    10,    -1,    16,   287,   232,    10,    -1,
      -1,    -1,    20,   211,    25,   197,   148,   208,   198,   142,
      10,    -1,    -1,     3,   163,   263,   199,   141,    10,    -1,
      -1,    -1,     3,    83,   147,   200,   292,   201,   141,    10,
      -1,    -1,     4,   163,   202,   141,    10,    -1,    -1,     5,
     164,   203,   265,   141,    10,    -1,    -1,    -1,     5,   278,
     286,   204,   164,   205,   265,   141,    10,    -1,    21,    -1,
      22,    -1,    23,    -1,    24,    -1,   189,    -1,   292,    -1,
      13,    -1,   292,    13,    -1,   292,    -1,    27,    -1,   210,
      -1,    14,   148,   207,   142,   209,    -1,   294,    -1,    15,
     142,    -1,   161,    -1,   154,    -1,   268,    -1,    89,   214,
     289,    -1,   212,    -1,   213,   130,   212,    -1,   213,    -1,
     213,   130,    95,   268,    -1,   213,   130,    95,   268,   130,
     213,    -1,   213,   130,    95,    -1,   213,   130,    95,   130,
     213,    -1,    95,   268,    -1,    95,   268,   130,   213,    -1,
      95,    -1,    95,   130,   213,    -1,   270,   130,   274,   277,
      -1,   270,   130,    -1,   270,   130,   274,   130,   270,   277,
      -1,   270,   277,    -1,   274,   277,    -1,   274,   130,   270,
     277,    -1,   276,    -1,   294,    -1,   217,    -1,   114,   218,
     114,    -1,    76,    -1,   114,   215,   218,   114,    -1,   294,
      -1,   135,   219,    -1,   220,    -1,   219,   130,   220,    -1,
      52,    -1,   267,    -1,    -1,   222,   223,   224,    -1,   132,
     266,   218,   289,    -1,   266,   218,    -1,   107,   142,   127,
      -1,    29,   142,    10,    -1,    -1,    28,   226,   216,   142,
      10,    -1,   153,   225,    -1,   227,   129,   284,   176,    -1,
     227,    85,   284,   176,    -1,   283,   175,    -1,   206,   129,
     284,   176,    -1,   206,    85,   284,   175,    -1,   206,    85,
     285,    -1,   206,   129,   175,    -1,   206,    85,   175,    -1,
      32,   175,    -1,    32,    -1,   206,   128,   177,   290,    -1,
      -1,   126,   230,   216,   142,   127,    -1,    -1,    26,   231,
     216,   142,    10,    -1,    17,   187,   207,   142,   233,    -1,
     210,    -1,   232,    -1,     8,   235,   236,   207,   142,   234,
      -1,   294,    -1,   173,    -1,   188,    -1,   294,    -1,    88,
     161,    -1,   294,    -1,     9,   142,    -1,   294,    -1,   258,
      -1,   255,    -1,   257,    -1,   240,    -1,    62,    -1,   241,
      -1,   240,   241,    -1,    99,   249,   106,    -1,   100,   250,
     106,    -1,   101,   250,    65,    -1,   102,   136,   106,    -1,
     102,   245,   106,    -1,    -1,   245,   246,   136,    -1,   251,
      -1,   246,   251,    -1,   103,   136,   106,    -1,   103,   248,
     106,    -1,    -1,   248,    61,   136,    -1,    -1,   249,   251,
      -1,    -1,   250,   251,    -1,    61,    -1,    -1,   105,   252,
     254,    -1,    -1,   104,   253,   142,   127,    -1,    54,    -1,
      55,    -1,    57,    -1,   262,    -1,    98,   256,    -1,   164,
      -1,    55,    -1,    54,    -1,    57,    -1,    98,   250,   106,
      -1,    59,    -1,    60,    -1,   122,    59,    -1,   122,    60,
      -1,    52,    -1,    55,    -1,    54,    -1,    56,    -1,    57,
      -1,    34,    -1,    33,    -1,    35,    -1,    36,    -1,    50,
      -1,    49,    -1,    51,    -1,   259,    -1,   259,    -1,    63,
      -1,    64,    -1,   292,    -1,    -1,   113,   264,   148,   292,
      -1,     1,   292,    -1,   132,   266,   289,    -1,   266,   292,
      -1,   270,   130,   272,   130,   274,   277,    -1,   270,   130,
     272,   130,   274,   130,   270,   277,    -1,   270,   130,   272,
     277,    -1,   270,   130,   272,   130,   270,   277,    -1,   270,
     130,   274,   277,    -1,   270,   130,   274,   130,   270,   277,
      -1,   270,   277,    -1,   272,   130,   274,   277,    -1,   272,
     130,   274,   130,   270,   277,    -1,   272,   277,    -1,   272,
     130,   270,   277,    -1,   274,   277,    -1,   274,   130,   270,
     277,    -1,   276,    -1,    -1,    56,    -1,    55,    -1,    54,
      -1,    57,    -1,   267,    -1,    52,    -1,   268,    -1,    89,
     214,   289,    -1,   269,    -1,   270,   130,   269,    -1,    52,
     109,   173,    -1,   271,    -1,   272,   130,   271,    -1,   119,
      -1,    95,    -1,   273,    52,    -1,   273,    -1,   116,    -1,
      96,    -1,   275,    52,    -1,   130,   276,    -1,   294,    -1,
     260,    -1,    -1,   132,   279,   147,   289,    -1,   294,    -1,
     281,   291,    -1,   282,    -1,   281,   130,   282,    -1,   173,
      88,   173,    -1,    58,   173,    -1,    52,    -1,    56,    -1,
      53,    -1,    52,    -1,    56,    -1,    53,    -1,   169,    -1,
      52,    -1,    53,    -1,   169,    -1,   129,    -1,    85,    -1,
      -1,   293,    -1,    -1,   137,    -1,   288,   133,    -1,   288,
     134,    -1,    -1,   137,    -1,   130,    -1,   135,    -1,   137,
      -1,   292,    -1,   293,   135,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   741,   741,   741,   771,   804,   814,   823,   831,   839,
     845,   845,   853,   861,   872,   882,   890,   899,   908,   921,
     934,   944,   943,   965,   977,   986,   996,  1025,  1046,  1063,
    1080,  1097,  1107,  1116,  1125,  1134,  1137,  1138,  1146,  1154,
    1162,  1170,  1173,  1185,  1186,  1187,  1195,  1203,  1213,  1214,
    1223,  1235,  1234,  1256,  1265,  1277,  1286,  1298,  1307,  1319,
    1328,  1339,  1340,  1350,  1351,  1361,  1369,  1377,  1385,  1393,
    1401,  1409,  1417,  1425,  1433,  1443,  1444,  1454,  1462,  1472,
    1480,  1490,  1498,  1506,  1514,  1522,  1530,  1542,  1552,  1564,
    1572,  1580,  1588,  1596,  1604,  1617,  1630,  1641,  1649,  1652,
    1660,  1668,  1678,  1679,  1680,  1681,  1691,  1703,  1704,  1707,
    1715,  1718,  1726,  1726,  1736,  1737,  1738,  1739,  1740,  1741,
    1742,  1743,  1744,  1745,  1746,  1747,  1748,  1749,  1750,  1751,
    1752,  1753,  1754,  1755,  1756,  1757,  1758,  1759,  1760,  1761,
    1762,  1763,  1764,  1767,  1767,  1767,  1768,  1768,  1769,  1769,
    1769,  1770,  1770,  1770,  1770,  1771,  1771,  1771,  1771,  1772,
    1772,  1772,  1773,  1773,  1773,  1773,  1774,  1774,  1774,  1774,
    1775,  1775,  1775,  1775,  1776,  1776,  1776,  1776,  1777,  1777,
    1777,  1777,  1778,  1778,  1781,  1790,  1798,  1827,  1848,  1865,
    1882,  1899,  1910,  1921,  1932,  1949,  1966,  1974,  1982,  1990,
    1998,  2006,  2014,  2023,  2032,  2040,  2048,  2056,  2064,  2072,
    2080,  2088,  2096,  2104,  2112,  2120,  2128,  2136,  2147,  2155,
    2163,  2171,  2179,  2187,  2195,  2203,  2203,  2213,  2223,  2229,
    2241,  2242,  2246,  2254,  2264,  2274,  2275,  2278,  2279,  2282,
    2290,  2298,  2308,  2317,  2326,  2334,  2342,  2352,  2362,  2372,
    2375,  2375,  2387,  2388,  2388,  2397,  2397,  2408,  2418,  2422,
    2428,  2436,  2444,  2452,  2462,  2470,  2478,  2488,  2489,  2490,
    2491,  2492,  2493,  2494,  2495,  2496,  2505,  2504,  2529,  2529,
    2538,  2546,  2554,  2562,  2575,  2583,  2591,  2599,  2607,  2615,
    2615,  2625,  2636,  2637,  2648,  2652,  2664,  2676,  2676,  2676,
    2687,  2687,  2687,  2698,  2709,  2718,  2720,  2717,  2773,  2772,
    2794,  2803,  2793,  2829,  2828,  2850,  2849,  2877,  2878,  2877,
    2902,  2910,  2918,  2926,  2936,  2948,  2953,  2954,  2961,  2966,
    2969,  2970,  2983,  2984,  2994,  2995,  2998,  3006,  3016,  3024,
    3034,  3042,  3050,  3058,  3066,  3074,  3082,  3093,  3101,  3111,
    3119,  3128,  3136,  3144,  3152,  3160,  3170,  3171,  3174,  3183,
    3192,  3203,  3204,  3214,  3221,  3230,  3238,  3244,  3244,  3266,
    3274,  3284,  3288,  3295,  3294,  3315,  3326,  3335,  3346,  3355,
    3365,  3375,  3383,  3394,  3405,  3413,  3421,  3436,  3435,  3455,
    3454,  3475,  3487,  3488,  3491,  3510,  3513,  3521,  3522,  3525,
    3529,  3532,  3540,  3543,  3544,  3552,  3555,  3572,  3573,  3574,
    3584,  3594,  3621,  3663,  3671,  3678,  3685,  3695,  3703,  3713,
    3721,  3728,  3735,  3746,  3753,  3764,  3771,  3781,  3783,  3782,
    3799,  3798,  3820,  3828,  3836,  3844,  3847,  3859,  3860,  3861,
    3862,  3865,  3901,  3902,  3903,  3911,  3921,  3922,  3923,  3924,
    3925,  3926,  3927,  3928,  3929,  3930,  3931,  3932,  3935,  3945,
    3955,  3956,  3959,  3968,  3967,  3975,  3987,  3999,  4005,  4013,
    4021,  4029,  4037,  4045,  4053,  4061,  4069,  4077,  4085,  4093,
    4101,  4109,  4118,  4127,  4136,  4145,  4154,  4165,  4166,  4178,
    4186,  4205,  4212,  4225,  4239,  4247,  4263,  4264,  4267,  4279,
    4290,  4291,  4294,  4310,  4314,  4324,  4334,  4334,  4363,  4364,
    4374,  4381,  4391,  4399,  4409,  4410,  4411,  4414,  4415,  4416,
    4417,  4420,  4421,  4422,  4425,  4430,  4437,  4438,  4441,  4442,
    4445,  4448,  4451,  4452,  4453,  4456,  4457,  4460,  4461,  4465
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "keyword_class", "keyword_module",
  "keyword_def", "keyword_undef", "keyword_begin", "keyword_rescue",
  "keyword_ensure", "keyword_end", "keyword_if", "keyword_unless",
  "keyword_then", "keyword_elsif", "keyword_else", "keyword_case",
  "keyword_when", "keyword_while", "keyword_until", "keyword_for",
  "keyword_break", "keyword_next", "keyword_redo", "keyword_retry",
  "keyword_in", "keyword_do", "keyword_do_cond", "keyword_do_block",
  "keyword_do_LAMBDA", "keyword_return", "keyword_yield", "keyword_super",
  "keyword_self", "keyword_nil", "keyword_true", "keyword_false",
  "keyword_and", "keyword_or", "keyword_not", "modifier_if",
  "modifier_unless", "modifier_while", "modifier_until", "modifier_rescue",
  "keyword_alias", "keyword_defined", "keyword_BEGIN", "keyword_END",
  "keyword__LINE__", "keyword__FILE__", "keyword__ENCODING__",
  "tIDENTIFIER", "tFID", "tGVAR", "tIVAR", "tCONSTANT", "tCVAR", "tLABEL",
  "tINTEGER", "tFLOAT", "tSTRING_CONTENT", "tCHAR", "tNTH_REF",
  "tBACK_REF", "tREGEXP_END", "tUPLUS", "tUMINUS", "tPOW", "tCMP", "tEQ",
  "tEQQ", "tNEQ", "tGEQ", "tLEQ", "tANDOP", "tOROP", "tMATCH", "tNMATCH",
  "tDOT2", "tDOT3", "tAREF", "tASET", "tLSHFT", "tRSHFT", "tCOLON2",
  "tCOLON3", "tOP_ASGN", "tASSOC", "tLPAREN", "tLPAREN_ARG", "tRPAREN",
  "tLBRACK", "tLBRACE", "tLBRACE_ARG", "tSTAR", "tAMPER", "tLAMBDA",
  "tSYMBEG", "tSTRING_BEG", "tXSTRING_BEG", "tREGEXP_BEG", "tWORDS_BEG",
  "tQWORDS_BEG", "tSTRING_DBEG", "tSTRING_DVAR", "tSTRING_END", "tLAMBEG",
  "tLOWEST", "'='", "'?'", "':'", "'>'", "'<'", "'|'", "'^'", "'&'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "tUMINUS_NUM", "'!'", "'~'", "tLAST_TOKEN",
  "'{'", "'}'", "'['", "'.'", "','", "'`'", "'('", "')'", "']'", "';'",
  "' '", "'\\n'", "$accept", "program", "@1", "bodystmt", "compstmt",
  "stmts", "stmt", "@2", "@3", "expr", "expr_value", "command_call",
  "block_command", "cmd_brace_block", "@4", "command", "mlhs",
  "mlhs_inner", "mlhs_basic", "mlhs_item", "mlhs_head", "mlhs_post",
  "mlhs_node", "lhs", "cname", "cpath", "fname", "fsym", "fitem",
  "undef_list", "@5", "op", "reswords", "arg", "@6", "arg_value",
  "aref_args", "paren_args", "opt_paren_args", "opt_call_args",
  "call_args", "call_args2", "command_args", "@7", "open_args", "@8", "@9",
  "block_arg", "opt_block_arg", "args", "mrhs", "primary", "@10", "@11",
  "@12", "@13", "@14", "@15", "@16", "@17", "@18", "@19", "@20", "@21",
  "@22", "@23", "@24", "@25", "primary_value", "then", "do", "if_tail",
  "opt_else", "for_var", "f_marg", "f_marg_list", "f_margs", "block_param",
  "opt_block_param", "block_param_def", "opt_bv_decl", "bv_decls", "bvar",
  "lambda", "@26", "f_larglist", "lambda_body", "do_block", "@27",
  "block_call", "method_call", "brace_block", "@28", "@29", "case_body",
  "cases", "opt_rescue", "exc_list", "exc_var", "opt_ensure", "literal",
  "strings", "string", "string1", "xstring", "regexp", "words",
  "word_list", "word", "qwords", "qword_list", "string_contents",
  "xstring_contents", "string_content", "@30", "@31", "string_dvar",
  "symbol", "sym", "dsym", "numeric", "variable", "var_ref", "var_lhs",
  "backref", "superclass", "@32", "f_arglist", "f_args", "f_bad_arg",
  "f_norm_arg", "f_arg_item", "f_arg", "f_opt", "f_optarg", "restarg_mark",
  "f_rest_arg", "blkarg_mark", "f_block_arg", "opt_f_block_arg",
  "singleton", "@33", "assoc_list", "assocs", "assoc", "operation",
  "operation2", "operation3", "dot_or_colon", "opt_terms", "opt_nl",
  "rparen", "rbracket", "trailer", "term", "terms", "none", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,    61,
      63,    58,    62,    60,   124,    94,    38,    43,    45,    42,
      47,    37,   364,    33,   126,   365,   123,   125,    91,    46,
      44,    96,    40,    41,    93,    59,    32,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   138,   140,   139,   141,   142,   143,   143,   143,   143,
     145,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   146,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   147,   147,   147,   147,
     147,   147,   148,   149,   149,   149,   149,   149,   150,   150,
     150,   152,   151,   153,   153,   153,   153,   153,   153,   153,
     153,   154,   154,   155,   155,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   157,   157,   158,   158,   159,
     159,   160,   160,   160,   160,   160,   160,   160,   160,   161,
     161,   161,   161,   161,   161,   161,   161,   162,   162,   163,
     163,   163,   164,   164,   164,   164,   164,   165,   165,   166,
     166,   167,   168,   167,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   172,   171,   171,   171,   173,
     174,   174,   174,   174,   175,   176,   176,   177,   177,   178,
     178,   178,   178,   178,   179,   179,   179,   179,   179,   179,
     181,   180,   182,   183,   182,   184,   182,   185,   186,   186,
     187,   187,   187,   187,   188,   188,   188,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   190,   189,   191,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   192,
     189,   189,   189,   189,   189,   189,   189,   193,   194,   189,
     195,   196,   189,   189,   189,   197,   198,   189,   199,   189,
     200,   201,   189,   202,   189,   203,   189,   204,   205,   189,
     189,   189,   189,   189,   206,   207,   207,   207,   208,   208,
     209,   209,   210,   210,   211,   211,   212,   212,   213,   213,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   215,
     215,   215,   215,   215,   215,   215,   216,   216,   217,   217,
     217,   218,   218,   219,   219,   220,   220,   222,   221,   223,
     223,   224,   224,   226,   225,   227,   227,   227,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   230,   229,   231,
     229,   232,   233,   233,   234,   234,   235,   235,   235,   236,
     236,   237,   237,   238,   238,   238,   239,   240,   240,   240,
     241,   242,   243,   244,   244,   245,   245,   246,   246,   247,
     247,   248,   248,   249,   249,   250,   250,   251,   252,   251,
     253,   251,   254,   254,   254,   254,   255,   256,   256,   256,
     256,   257,   258,   258,   258,   258,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   260,   261,
     262,   262,   263,   264,   263,   263,   265,   265,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   267,   267,   267,   267,   268,   268,   269,
     269,   270,   270,   271,   272,   272,   273,   273,   274,   274,
     275,   275,   276,   277,   277,   278,   279,   278,   280,   280,
     281,   281,   282,   282,   283,   283,   283,   284,   284,   284,
     284,   285,   285,   285,   286,   286,   287,   287,   288,   288,
     289,   290,   291,   291,   291,   292,   292,   293,   293,   294
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     4,     2,     1,     1,     3,     2,
       0,     4,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     0,     5,     4,     3,     3,     3,     6,     5,     5,
       5,     3,     3,     3,     3,     1,     1,     3,     3,     2,
       2,     1,     1,     1,     1,     2,     2,     2,     1,     4,
       4,     0,     5,     2,     3,     4,     5,     4,     5,     2,
       2,     1,     3,     1,     3,     1,     2,     3,     5,     2,
       4,     2,     4,     1,     3,     1,     3,     2,     3,     1,
       3,     1,     4,     3,     3,     3,     3,     2,     1,     1,
       4,     3,     3,     3,     3,     2,     1,     1,     1,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     3,     6,     5,     5,
       5,     5,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     4,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     3,     3,     3,     0,     4,     6,     1,     1,
       1,     2,     4,     2,     3,     1,     1,     1,     1,     1,
       2,     2,     4,     1,     4,     3,     2,     4,     6,     1,
       0,     2,     1,     0,     3,     0,     4,     2,     2,     1,
       1,     2,     3,     4,     3,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       3,     3,     2,     3,     3,     1,     4,     3,     1,     0,
       6,     2,     1,     2,     2,     6,     6,     0,     0,     7,
       0,     0,     7,     5,     4,     0,     0,     9,     0,     6,
       0,     0,     8,     0,     5,     0,     6,     0,     0,     9,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     5,     1,     2,     1,     1,     1,     3,     1,     3,
       1,     4,     6,     3,     5,     2,     4,     1,     3,     4,
       2,     6,     2,     2,     4,     1,     1,     1,     3,     1,
       4,     1,     2,     1,     3,     1,     1,     0,     3,     4,
       2,     3,     3,     0,     5,     2,     4,     4,     2,     4,
       4,     3,     3,     3,     2,     1,     4,     0,     5,     0,
       5,     5,     1,     1,     6,     1,     1,     1,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     3,     3,     3,     3,     0,     3,     1,     2,     3,
       3,     0,     3,     0,     2,     0,     2,     1,     0,     3,
       0,     4,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     3,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     2,     3,     2,     6,     8,
       4,     6,     4,     6,     2,     4,     6,     2,     4,     2,
       4,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     3,     1,     3,     1,     1,     2,     1,
       1,     1,     2,     2,     1,     1,     0,     4,     1,     2,
       1,     3,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     0,     1,
       2,     2,     0,     1,     1,     1,     1,     1,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     0,     0,   276,
       0,     0,   526,   297,   300,     0,   320,   321,   322,   323,
     285,   250,   250,   452,   451,   453,   454,     0,     0,   528,
      21,     0,   456,   455,   457,   446,   516,   448,   447,   449,
     450,   442,   443,   407,   460,   461,     0,     0,     0,     0,
       0,   539,   539,    73,   367,   425,   423,   425,   425,   415,
     421,     0,     0,     0,     3,   526,     7,    35,    36,    44,
      43,     0,    61,     0,    65,    75,     0,    41,   228,     0,
      48,   292,   267,   268,   406,   408,   269,   270,   271,   272,
     404,   405,   403,   458,   273,     0,   274,   250,     6,     9,
     320,   321,   285,   288,   385,   528,    97,    98,     0,     0,
       0,     0,   100,     0,   324,     0,   458,   274,     0,   313,
     153,   164,   154,   177,   150,   170,   160,   159,   180,   181,
     175,   158,   157,   152,   178,   182,   183,   162,   151,   165,
     169,   171,   163,   156,   172,   179,   174,   173,   166,   176,
     161,   149,   168,   167,   148,   155,   146,   147,   143,   144,
     145,   102,   104,   103,   138,   139,   135,   117,   118,   119,
     126,   123,   125,   120,   121,   140,   141,   127,   128,   132,
     122,   124,   114,   115,   116,   129,   130,   131,   133,   134,
     136,   137,   142,   506,   315,   105,   106,   505,     0,   173,
     166,   176,   161,   143,   144,   145,   102,   103,   107,   109,
     111,    15,   108,   110,     0,     0,    42,     0,     0,     0,
     458,     0,   274,     0,   535,   536,   526,     0,   537,   527,
       0,     0,     0,   335,   334,     0,     0,   458,   274,     0,
       0,     0,     0,   239,   229,   260,    46,   243,   539,   539,
     510,    47,    45,   528,    60,     0,   539,   384,    59,    39,
       0,    10,   529,   225,     0,     0,   204,     0,   205,   282,
       0,     0,   528,    63,   278,     0,   532,   532,   230,     0,
       0,   532,   508,     0,     0,    71,     0,    81,    88,   294,
     482,   439,   438,   440,   437,     0,   436,     0,     0,     0,
       0,     0,     0,     0,   444,   445,    40,   219,   220,     5,
     527,     0,     0,     0,     0,     0,     0,     0,   373,   375,
       0,    77,     0,    69,    66,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   539,     0,     0,     0,   389,   387,   293,
     409,     0,     0,   378,    53,   291,     0,   310,    97,    98,
      99,   444,   445,     0,   463,   308,   462,     0,   539,     0,
       0,     0,   482,   525,   524,   317,   112,     0,   539,   282,
     326,     0,   325,     0,     0,   539,     0,     0,     0,     0,
       0,     0,     0,   538,     0,     0,   282,     0,   539,     0,
     305,   513,   261,   257,     0,     0,   240,   259,     0,   241,
     528,     0,   287,   253,   252,   251,   528,   238,   237,    12,
      14,    13,     0,   289,     0,     0,     0,     0,     0,     0,
     528,   280,    62,   528,   283,   534,   533,   231,   534,   233,
     284,   509,    87,    79,    74,     0,     0,   539,     0,   488,
     485,   484,   483,   486,     0,   497,   501,   500,   496,   482,
       0,   539,   487,   489,   491,   539,   494,   539,   499,   539,
       0,   481,   427,   430,   428,   441,   426,   410,   424,   411,
     412,   413,   414,     0,   417,   419,     0,   420,     0,     0,
       8,    16,    17,    18,    19,    20,    37,    38,   539,     0,
      25,    33,     0,    34,   528,     0,    67,    78,    24,   184,
     260,    32,   201,   209,   214,   215,   216,   211,   213,   223,
     224,   217,   218,   194,   195,   221,   222,   528,   210,   212,
     206,   207,   208,   196,   197,   198,   199,   200,   517,   522,
     518,   523,   383,   250,   381,   528,   517,   519,   518,   520,
     382,   250,   517,   518,   250,   250,   539,   539,    26,   186,
      31,   193,    51,    54,     0,   465,     0,     0,    97,    98,
     101,     0,   528,   539,     0,   528,   482,     0,     0,     0,
       0,   277,   539,   539,   395,   539,   327,   184,   521,   281,
     528,   517,   518,   539,     0,     0,   304,   329,   298,   328,
     301,   521,   281,   528,   517,   518,     0,   512,     0,   262,
     258,   539,   511,   286,   530,    41,     0,   255,   528,   249,
     539,   234,    11,     0,   226,     0,    23,   192,    64,   279,
     532,     0,    72,    84,    86,   528,   517,   518,     0,   488,
       0,   347,   338,   340,   528,   336,   539,     0,     0,   368,
       0,   370,   361,     0,   474,   504,     0,   477,   498,     0,
     479,   502,     0,     0,   416,   418,   422,   202,   203,   359,
     539,     0,   357,   356,   266,     0,    76,    70,     0,     0,
       0,     0,     0,   380,    57,     0,   386,     0,     0,   236,
     379,    55,   235,   377,    50,   376,    49,     0,     0,   539,
     311,     0,     0,   386,   314,   507,   528,     0,   467,   318,
     113,   396,   397,   539,   398,     0,   539,   332,     0,     0,
     330,     0,   386,     0,     0,     0,   303,     0,     0,     0,
       0,   386,     0,   263,   242,     0,   528,   254,   246,   528,
      22,   232,    80,    82,   493,   528,     0,   345,     0,   490,
     528,     0,     0,   365,   362,   363,   366,   492,   539,   539,
     503,   539,   495,   539,   539,     0,   432,   433,   434,   429,
     435,   539,     0,   539,   539,   355,     0,     0,   264,    68,
     185,     0,    30,   190,   191,    58,   531,     0,    28,   188,
      29,   189,    56,     0,     0,     0,     0,   464,   309,   466,
     316,   482,     0,     0,   400,   333,     0,     4,   402,     0,
     295,     0,   296,   262,   539,     0,     0,   306,   245,   539,
     539,   256,   290,   337,   348,     0,   343,   339,   369,   372,
     371,     0,     0,   470,     0,   472,     0,   478,     0,   475,
     480,   431,     0,   358,   350,   352,     0,   353,   374,   265,
     227,    27,   187,   390,   388,     0,     0,     0,     0,   399,
       0,    89,    96,     0,   401,     0,   392,   393,   391,   299,
     302,     0,     0,   244,   247,     0,   346,     0,   341,   364,
     539,   539,   539,   539,   360,   539,   539,    52,   312,     0,
      95,     0,   539,     0,   539,   539,     0,   539,   344,     0,
     471,     0,   468,   473,   476,     0,   349,   354,   319,   521,
      94,   528,   517,   518,   394,   331,   307,   248,   342,   539,
     539,   386,   469,   351
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   387,   388,    65,    66,   432,   264,    67,
     217,    68,    69,   573,   709,    70,    71,   272,    72,    73,
      74,   454,    75,   218,   112,   113,   208,   209,   210,   211,
     590,   559,   196,    77,   434,   245,   275,   552,   700,   426,
     427,   627,   254,   255,   425,   628,   746,   247,   416,   248,
     513,    78,   214,   443,   633,   230,   739,   231,   740,   616,
     881,   577,   574,   806,   380,   382,   589,   811,   267,   391,
     608,   729,   730,   236,   652,   653,   654,   781,   681,   682,
     661,   764,   765,   289,   290,   470,   659,   319,   508,    80,
      81,   365,   567,   566,   402,   878,   593,   723,   813,   817,
      82,    83,    84,    85,    86,    87,    88,   301,   493,    89,
     303,   297,   295,   486,   673,   672,   779,    90,   296,    91,
      92,   220,    94,   221,   222,   375,   576,   587,   588,   472,
     473,   474,   475,   476,   477,   478,   479,   480,   770,   664,
     198,   381,   280,   249,   250,   118,   581,   554,   385,   227,
     421,   422,   696,   447,   392,   229,    98
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -702
static const yytype_int16 yypact[] =
{
    -702,   129,  2240,  -702,  6207,  8169,  8484,  4622,  5746,  -702,
    7188,  7188,  4380,  -702,  -702,  8274,  6316,  6316,  -702,  -702,
    6316,  2737,  2344,  -702,  -702,  -702,  -702,  7188,  5617,    -3,
    -702,    56,  -702,  -702,  -702,  4744,  2475,  -702,  -702,  4868,
    -702,  -702,  -702,  -702,  -702,  -702,  7951,  7951,   130,  3757,
    7188,  6861,  7297,  5997,  -702,  5488,  -702,  -702,  -702,    90,
     148,   236,  8060,  7951,  -702,   226,  1019,   366,  -702,  -702,
     174,   198,  -702,   239,  8379,  -702,   310,  2327,    60,   323,
      37,    53,  -702,  -702,   291,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,   411,  -702,   336,   558,    81,  -702,  1019,
    -702,  -702,  -702,   317,   322,    -3,   437,   555,  7188,    94,
    3892,   384,  -702,    62,  -702,   353,  -702,  -702,    81,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,    45,    66,   142,
     146,  -702,  -702,  -702,  -702,  -702,  -702,  -702,   164,   177,
     193,   205,  -702,   273,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,   281,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,   339,  -702,  -702,  3134,   406,   366,    79,   369,   371,
      28,   392,   178,    79,  -702,  -702,   226,   463,  -702,   359,
    7188,  7188,   446,  -702,  -702,   379,   479,    64,    68,  7951,
    7951,  7951,  7951,  -702,  2327,   424,  -702,  -702,   375,   389,
    -702,  -702,  -702,  4271,  -702,  6425,  6316,  -702,  -702,  -702,
     332,  -702,  -702,   394,   401,  4027,  -702,   492,   461,   560,
    3757,   399,    -3,   426,   366,   405,    32,    33,  -702,   424,
     413,    33,  -702,   487,  8589,   423,   497,   501,   547,  -702,
     774,  -702,  -702,  -702,  -702,   220,  -702,   237,   269,   491,
     449,   412,   451,    77,   493,   494,  -702,  -702,  -702,  -702,
    4489,  7188,  7188,  7188,  7188,  6207,  7188,  7188,  -702,  -702,
    7406,  -702,  3757,  6102,   429,  7406,  7951,  7951,  7951,  7951,
    7951,  7951,  7951,  7951,  7951,  7951,  7951,  7951,  7951,  7951,
    7951,  7951,  7951,  7951,  7951,  7951,  7951,  7951,  7951,  7951,
    7951,  7951,  8751,  6316,  8824,  9627,  9627,  -702,  -702,  -702,
    -702,  8060,  8060,  -702,   470,  -702,   394,   366,  -702,   575,
    -702,  -702,  -702,   226,  -702,  -702,  -702,  8897,  6316,  8970,
    3134,  7188,   884,  -702,  -702,  -702,  -702,   561,   565,   207,
    -702,  3269,   563,  7951,  9043,  6316,  9116,  7951,  7951,  3539,
     463,  7515,   569,  -702,    41,    41,    76,  9189,  6316,  9262,
    -702,  -702,  -702,  -702,  7951,  6534,  -702,  -702,  6970,  -702,
      -3,   447,  -702,  6643,  -702,  -702,    -3,  -702,  -702,  -702,
    -702,  -702,  5746,  -702,  7951,  4027,   465,  9043,  9116,  7951,
      -3,  -702,   458,    -3,  -702,  7079,  -702,  -702,  7297,  -702,
    -702,  -702,   575,  -702,   460,  8589,  9335,  6316,  9408,   495,
    -702,  -702,  -702,  -702,   870,  -702,  -702,  -702,  -702,  1023,
      61,   466,  -702,  -702,  -702,   473,  -702,   478,   557,   480,
     559,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,   200,  -702,  -702,   481,  -702,  7951,  7951,
    1019,  -702,  -702,  -702,  -702,  -702,  -702,  -702,    57,  7951,
    -702,   485,   513,  -702,    -3,  8589,   522,  -702,  -702,  1104,
    -702,  -702,   461,  2589,  2589,  2589,  2589,  1216,  1216,  2720,
    1331,  2589,  2589,  2458,  2458,   767,   767,  2065,  1216,  1216,
     681,   681,   741,    35,    35,   461,   461,   461,  2868,  5236,
    2999,  5358,  -702,   322,  -702,    -3,   620,  -702,   621,  -702,
    -702,  2606,  -702,  -702,  1837,  1837,    57,    57,  -702,  2327,
    -702,  2327,  -702,  -702,   226,  -702,  7188,  3134,   648,    20,
    -702,   322,    -3,   322,   612,   121,  1023,  3134,   226,  5875,
    5746,  -702,  7624,   643,  -702,   443,  -702,  2846,  4992,  5114,
      -3,   245,   263,   643,   652,    74,  -702,  -702,  -702,  -702,
    -702,    55,   114,    -3,    91,   103,  7188,  -702,  7951,   424,
    -702,   389,  -702,  -702,  -702,  2977,   153,  -702,    -3,  -702,
     389,  -702,  -702,  7188,  2327,   539,  -702,  2327,   235,  -702,
      33,  8589,   460,   648,    20,    -3,    87,   155,  7951,  -702,
     870,   581,  -702,   538,    -3,  -702,   466,  4162,  4027,  -702,
     790,  -702,  -702,  1023,  -702,  -702,  1023,  -702,  -702,  1069,
    -702,  -702,  4027,   847,  -702,  -702,  -702,   461,   461,  -702,
     435,  4162,  -702,  -702,   542,  7733,  -702,   460,  8589,  7951,
     567,  8060,  7951,  -702,   470,   546,   638,  8060,  8060,  -702,
    -702,   470,  -702,  -702,  -702,  -702,  -702,  4162,  4027,    57,
    -702,   226,   672,  -702,  -702,  -702,    -3,   675,  -702,  -702,
    -702,   485,  -702,   605,  -702,  3648,   685,  -702,  7188,   687,
    -702,  7951,   275,  7951,  7951,   690,  -702,  7842,  3404,  4162,
    4162,   122,    41,  -702,  -702,  6752,    -3,  -702,  -702,   121,
    -702,  -702,  -702,   586,  -702,    -3,   840,   587,   920,  -702,
      -3,   706,   592,  -702,   590,  -702,  -702,  -702,   594,   597,
    -702,   604,  -702,   623,   604,   595,  -702,  -702,  -702,  -702,
    -702,   466,   629,   627,   628,  -702,   725,  7951,   631,   460,
    2327,  7951,  -702,  2327,  2327,  -702,  -702,  8060,  -702,  2327,
    -702,  2327,  -702,   749,   635,  4027,  3134,  -702,  -702,  -702,
    -702,   884,  8694,    79,  -702,  -702,  4162,  -702,  -702,    79,
    -702,  7951,  -702,  -702,   403,   757,   761,  -702,  -702,   636,
     389,  -702,  -702,  -702,   645,   840,   734,  -702,  -702,  -702,
    -702,   790,  1023,  -702,  1069,  -702,  1069,  -702,  1069,  -702,
    -702,  -702,   664,  -702,  1152,  -702,  1069,  -702,  -702,   649,
    2327,  -702,  2327,  -702,  -702,   654,   772,  3134,   727,  -702,
     613,   501,   547,  3134,  -702,  3269,  -702,  -702,  -702,  -702,
    -702,  4162,  6534,  -702,  -702,   840,   645,   840,   655,  -702,
     604,   662,   604,   604,  -702,   686,   604,  -702,  -702,   784,
     575,  9481,  6316,  9554,   565,   443,   795,   389,   645,   840,
    -702,  1069,  -702,  -702,  -702,  1069,  -702,  -702,  -702,    73,
      20,    -3,    97,   105,  -702,  -702,  -702,  -702,   645,   604,
     604,   108,  -702,  -702
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -702,  -702,  -702,  -339,   112,  -702,    42,  -702,  -702,   337,
      26,   -34,  -702,  -428,  -702,    14,   796,  -150,   -20,   -54,
    -702,  -416,   -26,  1279,   -76,   811,    -6,  -702,     7,  -702,
    -702,     4,  -702,   693,  -702,  1385,  -702,    63,   -99,  -313,
      80,  -702,   -16,  -702,  -702,  -702,  -702,  -357,  -230,   -46,
    -289,   186,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,    -2,  -206,
    -389,   -87,  -548,  -702,  -701,  -694,   171,  -702,  -490,  -702,
    -578,  -702,    -9,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,   760,  -702,  -702,  -374,  -702,   -48,  -702,  -702,  -702,
    -702,  -702,  -702,   773,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,   417,  -213,  -702,  -702,  -702,    15,  -702,    16,
    -702,  1043,   859,  1242,  1358,  -702,  -702,    67,  -269,  -604,
    -351,  -599,  -183,  -624,   204,  -702,  -523,  -702,  -192,    65,
    -702,  -702,  -702,     1,  -159,   115,  -285,  -702,  -702,     9,
     -22,   543,  -509,  -227,    10,   803,   756
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -540
static const yytype_int16 yytable[] =
{
      79,   194,    79,   115,   115,   276,   258,   263,   219,   219,
     219,   195,   195,   235,   219,   219,   610,   399,   219,   419,
     324,   471,   228,   212,   213,   219,   604,   285,   306,   273,
     243,   243,   195,   370,   243,   261,   521,   223,   226,   642,
     555,   584,   772,   212,   213,   726,    99,    79,   219,   294,
     449,   286,   277,   281,   451,   735,   766,   837,   620,   195,
     219,   620,   834,   373,   767,   582,   629,   553,   607,   561,
     564,   565,   286,   713,   309,   228,   707,   708,   760,   357,
     -92,   364,   600,   366,   488,   257,   -92,   390,   494,   -89,
     657,   732,   390,   -96,   583,   613,   246,   251,   481,   687,
     252,   -95,   782,   326,   741,  -281,   219,   357,    79,   553,
     -91,   561,   -83,   655,    64,  -459,   -91,    97,   -93,    97,
     440,   -90,   355,   376,   583,    97,    97,    97,   -93,     3,
    -452,    97,    97,   679,   262,    97,   753,   -89,   496,   -94,
     769,   886,    97,   773,   645,  -324,   368,   -90,  -281,  -281,
     369,  -451,  -518,   583,   349,   350,   351,   784,   316,   317,
     363,   271,   445,   448,    97,    97,   356,   257,   658,   446,
     446,   680,   514,   583,  -452,   374,   224,    97,   225,   358,
     -85,   363,   265,   497,   837,   -84,   269,  -517,  -324,  -324,
     481,   114,   114,   908,   -81,  -451,   -83,   224,   -88,   225,
     656,   114,   318,   852,   737,  -517,   -87,   358,   -92,   224,
     -92,   225,    79,   256,   224,   928,   225,   -83,   772,   805,
     -83,   -83,   271,    97,   -83,    97,   300,  -453,   219,   219,
     453,  -454,   -91,   -85,   -91,   400,   228,   766,   712,   114,
     -93,   414,   -93,   -90,   -86,   -90,  -518,   767,   717,  -456,
     273,   219,   -82,   219,   219,   767,   404,   405,   262,   622,
     114,   482,  -455,    79,   -85,   398,   795,   243,    79,   243,
     243,  -453,   789,   802,   512,  -454,   876,   481,  -457,   512,
     675,   482,   286,   745,   302,   -85,   510,   -96,   -85,   622,
    -446,   518,   -85,  -456,   439,   304,   305,   516,   482,   655,
     757,   580,   273,   722,   483,   484,  -455,   320,    79,   219,
     219,   219,   219,    79,   219,   219,   -95,   716,   219,   891,
      79,   286,  -457,   219,   483,   484,   485,   568,   570,    97,
     482,   895,   733,   420,  -446,   424,   674,   501,   502,   503,
     504,   483,   484,   487,   -62,    97,    97,   216,   216,   216,
     734,   219,   500,   827,   -91,   605,   551,   505,  -449,   219,
     219,   224,   821,   225,   259,   -76,   383,   243,    97,   321,
      97,    97,   -93,   483,   484,   489,   219,   436,    79,   219,
      97,   551,   271,   575,   -90,    97,   429,   274,   828,    79,
      56,   744,   243,   219,   481,   430,   431,    79,   551,   738,
     748,   453,  -449,   316,   317,   655,   219,   655,   352,   243,
     384,   551,   931,   751,   609,   609,   621,   560,   725,   325,
     401,   219,   243,   361,   630,    97,    97,    97,    97,    97,
      97,    97,    97,    79,   271,    97,   195,    97,   377,   632,
      97,   551,   560,   371,   372,   367,   640,   212,   213,   253,
     877,   353,   354,   286,   256,   219,   394,   728,   725,   560,
     551,   453,   389,  -514,   407,   703,   705,   866,    97,   386,
     114,   243,   560,   482,   298,   299,    97,    97,   393,   397,
     401,   378,   379,   771,   655,   888,   774,   649,   785,   460,
     461,   462,   463,    97,   403,    97,    97,   783,  -459,   395,
     396,   560,   406,   595,   410,   415,    97,   408,   409,   114,
      97,   603,   414,   286,    97,   690,   483,   484,   492,   418,
     -89,   560,  -446,    97,   464,   620,   433,   435,   899,   326,
     465,   466,   441,   695,   655,   -61,   655,   694,    97,   444,
     450,   -81,   667,   452,   670,   701,   512,   635,   704,   706,
      97,   467,   482,   455,   468,   491,   490,   495,   655,   517,
     695,   498,   499,  -514,   572,  -446,  -446,   216,   216,  -514,
     660,   591,    97,   592,   219,    79,   596,   437,   695,   606,
     624,  -515,   456,   719,   710,    79,  -458,   752,   -76,   921,
     641,   695,   636,   195,   195,   483,   484,   720,   718,   883,
     884,   660,   711,   663,   648,   212,   213,   873,   666,   668,
     669,   671,  -386,   875,   219,  -260,   693,   676,   583,   481,
     395,   438,   714,   695,   699,   457,   458,   699,   699,  -458,
    -458,   219,  -274,   649,   453,   460,   461,   462,   463,   286,
    -449,   114,   742,   685,   693,   362,   699,   439,   216,   216,
     216,   216,   688,   506,   507,    79,    79,   792,   725,   890,
    -282,   892,   736,   798,   800,   893,   750,   -96,   758,   -95,
      79,  -386,  -261,   896,  -521,  -274,  -274,   927,   791,    79,
     796,  -515,   808,  -449,  -449,   810,   286,  -515,   -88,   219,
     -87,    97,    97,   812,   816,   219,   219,   820,   901,   829,
     822,   114,    97,  -282,  -282,    79,    79,   697,   698,   244,
     244,   756,  -386,   244,  -386,  -386,   839,   835,   585,   840,
     841,   807,   851,    79,   842,   797,   219,   844,   929,   -91,
     -93,    97,   930,  -521,   846,   858,    79,    79,    79,   266,
     268,   902,   903,   853,   244,   244,   830,   -90,    97,   326,
     -83,   -85,   609,   848,   819,   307,   308,   854,   856,   863,
     274,  -262,   864,   861,   339,   340,   882,   879,   -82,   761,
     762,   880,    97,    97,  -521,   885,  -521,  -521,   894,  -263,
    -517,   897,   898,   900,   775,   909,   649,    97,   460,   461,
     462,   463,   911,   786,   918,   219,    97,   346,   347,   348,
     349,   350,   351,    79,    79,   926,    97,   278,   282,   326,
     870,   233,    97,    97,    79,   442,   915,   119,   925,   803,
     804,   755,    97,    97,   339,   340,   459,   114,   460,   461,
     462,   463,   889,   843,   845,   326,   847,   815,   849,   850,
      97,   359,   763,    97,   460,   461,   462,   463,   855,   857,
     824,   825,   826,    97,    97,    97,   924,   360,   347,   348,
     349,   350,   351,   464,   887,    79,   197,   768,   310,   465,
     466,    79,     0,    79,   114,     0,     0,     0,   867,    79,
       0,     0,     0,   907,   347,   348,   349,   350,   351,     0,
     467,     0,   649,   468,   460,   461,   462,   463,     0,   695,
     219,   776,   777,     0,   778,   551,   469,     0,     0,     0,
      44,    45,    97,   216,     0,     0,   243,   865,     0,     0,
      97,    97,   649,     0,   460,   461,   462,   463,   874,   650,
       0,    97,   244,   244,   244,   307,   459,     0,   460,   461,
     462,   463,     0,     0,     0,     0,   244,     0,   244,   244,
       0,     0,     0,   216,     0,   910,   912,   913,   914,   650,
     916,   917,     0,   623,     0,   651,   560,     0,     0,   631,
     749,     0,   649,   464,   460,   461,   462,   463,     0,   465,
     466,     0,    97,   638,     0,   904,   639,   905,    97,     0,
      97,     0,     0,   906,   932,   933,    97,     0,   114,     0,
     467,     0,     0,   468,   417,   417,     0,     0,     0,   650,
       0,     0,   428,   244,     0,   836,   586,    97,   519,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,    93,   244,    93,   116,   116,
     116,     0,     0,     0,   569,   571,     0,   686,   237,   311,
     312,   313,   314,   315,     0,   216,     0,     0,     0,     0,
       0,   244,     0,     0,     0,   459,     0,   460,   461,   462,
     463,     0,     0,     0,     0,     0,   597,     0,   244,     0,
     569,   571,    93,     0,   244,     0,   287,     0,     0,     0,
       0,   244,     0,     0,     0,     0,     0,   244,   244,   428,
       0,   244,   464,     0,     0,     0,   625,   287,   465,   466,
       0,   649,     0,   460,   461,   462,   463,   634,   715,     0,
       0,     0,   637,     0,   428,     0,     0,     0,   244,   467,
       0,   244,   468,     0,   594,     0,     0,     0,   689,     0,
     244,   428,     0,    93,     0,     0,     0,     0,   464,     0,
       0,     0,     0,     0,   428,   466,     0,     0,     0,     0,
       0,   747,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   467,     0,   339,   340,     0,
       0,   677,   678,     0,     0,     0,     0,   759,     0,     0,
       0,     0,   244,     0,   649,     0,   460,   461,   462,   463,
       0,     0,     0,   428,   341,     0,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,     0,   662,     0,     0,
       0,   665,     0,   665,  -229,   665,     0,     0,     0,     0,
       0,   464,     0,     0,    95,     0,    95,   465,   466,     0,
       0,     0,     0,     0,     0,     0,     0,    93,     0,   809,
       0,     0,     0,     0,   683,     0,     0,     0,   467,     0,
       0,   468,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,     0,    76,   326,   244,     0,     0,     0,   831,
       0,    95,   832,     0,   234,     0,     0,     0,   833,   339,
     340,     0,     0,   838,     0,     0,     0,     0,    93,     0,
       0,   244,     0,    93,     0,     0,     0,   702,     0,     0,
     702,   702,   683,   683,     0,     0,     0,   287,    76,     0,
     344,   345,   346,   347,   348,   349,   350,   351,     0,   702,
       0,   244,     0,     0,     0,     0,     0,     0,   724,   727,
       0,   727,    95,    93,     0,     0,     0,     0,    93,   727,
      96,     0,    96,   117,   117,    93,   287,     0,     0,     0,
       0,     0,     0,   238,     0,     0,     0,   417,   244,     0,
       0,     0,   790,     0,   793,   794,   417,     0,     0,    76,
     799,   801,     0,     0,     0,     0,     0,     0,     0,   326,
     327,   328,   329,   330,   331,   332,   333,    96,   335,   336,
       0,   288,   662,     0,   339,   340,     0,     0,     0,     0,
       0,     0,     0,    93,   793,     0,   799,   801,     0,     0,
     244,     0,   288,     0,    93,     0,   662,   279,   244,     0,
       0,     0,    93,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,     0,     0,    95,     0,     0,     0,
       0,     0,     0,     0,     0,   683,     0,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,   814,
     244,     0,   818,     0,   860,     0,     0,     0,     0,     0,
     862,     0,     0,    76,     0,     0,     0,     0,   287,     0,
       0,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,    95,     0,   862,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   665,   665,     0,   665,     0,   665,
     665,     0,     0,     0,     0,     0,     0,   662,     0,   665,
     665,     0,     0,     0,    76,     0,     0,     0,     0,    76,
       0,     0,    95,     0,     0,     0,     0,    95,   287,     0,
       0,     0,     0,     0,    95,     0,     0,     0,     0,     0,
       0,     0,    96,     0,     0,   244,     0,     0,     0,     0,
     727,     0,     0,     0,     0,   417,   417,     0,     0,    76,
       0,     0,     0,     0,    76,   244,     0,     0,     0,     0,
       0,    76,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,    95,    96,   411,   412,   413,     0,    96,     0,
      93,     0,     0,    95,     0,     0,     0,     0,     0,     0,
       0,    95,   288,     0,     0,     0,   665,   665,   665,   665,
       0,   665,   665,     0,     0,     0,     0,     0,   428,    76,
     594,   727,     0,   417,     0,     0,     0,     0,    96,     0,
      76,     0,     0,    96,     0,     0,     0,    95,    76,     0,
      96,   288,     0,     0,   287,   665,   665,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,    93,     0,     0,     0,   511,     0,     0,     0,     0,
     520,     0,     0,     0,    76,    93,     0,     0,     0,     0,
       0,     0,     0,     0,    93,     0,     0,     0,     0,     0,
       0,   287,     0,     0,     0,     0,     0,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    96,
      93,    93,     0,     0,     0,     0,     0,    96,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    93,    93,    93,     0,     0,   520,     0,     0,     0,
       0,     0,     0,    96,     0,     0,     0,     0,     0,   617,
     619,     0,     0,   279,     0,     0,     0,     0,   626,     0,
       0,     0,     0,   288,     0,     0,     0,     0,     0,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
     619,     0,     0,   279,     0,     0,     0,  -539,     0,     0,
       0,     0,     0,     0,     0,  -539,  -539,  -539,    93,    93,
    -539,  -539,  -539,     0,  -539,   871,    76,     0,     0,    93,
       0,     0,     0,     0,  -539,     0,    76,     0,     0,     0,
       0,     0,     0,   288,  -539,  -539,     0,  -539,  -539,  -539,
    -539,  -539,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   684,     0,     0,     0,     0,    95,
      95,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,     0,     0,    95,     0,    93,     0,    93,     0,
       0,     0,  -539,    95,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,    76,    76,     0,     0,
       0,     0,     0,     0,     0,    96,     0,     0,     0,    95,
      95,    76,     0,     0,     0,     0,     0,     0,     0,     0,
      76,     0,     0,     0,  -539,     0,  -539,    95,     0,   256,
    -539,     0,  -539,     0,  -539,     0,     0,   721,     0,     0,
      95,    95,    95,     0,     0,     0,    76,    76,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   288,
       0,     0,     0,   743,    76,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,    96,    76,    76,    76,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      96,   780,     0,   754,     0,     0,     0,     0,     0,    96,
       0,     0,     0,     0,     0,     0,   288,    95,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    95,     0,
       0,     0,     0,     0,     0,    96,    96,     0,     0,     0,
     788,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,    76,    76,     0,     0,     0,     0,
       0,   869,     0,     0,     0,    76,    96,    96,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
       0,     0,     0,     0,     0,    95,     0,    95,     0,     0,
       0,     0,   823,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,    76,     0,   339,   340,
       0,     0,    76,     0,    76,     0,     0,     0,     0,     0,
      76,     0,     0,    96,    96,     0,     0,     0,     0,     0,
     872,     0,   859,     0,    96,   341,     0,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   262,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,     0,     0,     0,     0,
       0,    96,     0,    96,     0,     0,     0,     0,     0,    96,
    -539,     4,     0,     5,     6,     7,     8,     9,     0,     0,
       0,    10,    11,     0,     0,     0,    12,     0,    13,    14,
      15,    16,    17,    18,    19,     0,     0,   619,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,     0,    43,    44,    45,     0,    46,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,     0,     0,    49,
      50,     0,    51,    52,     0,    53,     0,    54,    55,    56,
      57,    58,    59,    60,  -385,     0,     0,     0,     0,     0,
       0,     0,  -385,  -385,  -385,     0,     0,  -385,  -385,  -385,
       0,  -385,    61,    62,    63,     0,     0,     0,     0,     0,
    -385,  -385,  -385,     0,     0,  -539,     0,  -539,     0,     0,
       0,  -385,  -385,     0,  -385,  -385,  -385,  -385,  -385,     0,
       0,     0,     0,     0,     0,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,     0,     0,
     339,   340,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,     0,     0,  -385,  -385,  -385,
       0,     0,  -385,     0,     0,     0,     0,   341,  -385,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,     0,
       0,     0,     0,     0,  -385,     0,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,     0,     0,     0,     0,
    -385,  -385,  -385,  -385,  -385,  -275,   256,  -385,  -385,  -385,
       0,  -385,     0,  -275,  -275,  -275,     0,     0,  -275,  -275,
    -275,     0,  -275,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -275,  -275,  -275,     0,     0,     0,     0,     0,
       0,     0,  -275,  -275,     0,  -275,  -275,  -275,  -275,  -275,
       0,     0,     0,     0,     0,     0,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,  -540,  -540,     0,
       0,   339,   340,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,     0,     0,  -275,  -275,
    -275,     0,     0,  -275,     0,     0,     0,     0,     0,  -275,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
       0,     0,  -275,     0,     0,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,     0,     0,     0,
       0,     0,  -275,  -275,  -275,  -275,  -539,     0,  -275,  -275,
    -275,     0,  -275,     0,  -539,  -539,  -539,     0,     0,  -539,
    -539,  -539,     0,  -539,     0,     0,     0,     0,     0,     0,
       0,     0,  -539,  -539,  -539,     0,     0,     0,     0,     0,
       0,     0,     0,  -539,  -539,     0,  -539,  -539,  -539,  -539,
    -539,     0,     0,     0,     0,     0,     0,   326,  -540,  -540,
    -540,  -540,   331,   332,     0,     0,  -540,  -540,     0,     0,
       0,     0,   339,   340,  -539,  -539,  -539,  -539,  -539,  -539,
    -539,  -539,  -539,  -539,  -539,  -539,  -539,     0,     0,  -539,
    -539,  -539,     0,     0,  -539,     0,     0,     0,     0,     0,
    -539,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,     0,     0,     0,     0,     0,  -539,     0,  -539,  -539,
    -539,  -539,  -539,  -539,  -539,  -539,  -539,  -539,     0,     0,
       0,     0,  -539,  -539,  -539,  -539,  -539,  -288,   256,  -539,
    -539,  -539,     0,  -539,     0,  -288,  -288,  -288,     0,     0,
    -288,  -288,  -288,     0,  -288,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -288,  -288,     0,     0,     0,     0,
       0,     0,     0,     0,  -288,  -288,     0,  -288,  -288,  -288,
    -288,  -288,     0,     0,     0,     0,     0,     0,   326,   327,
     328,   329,   330,   331,   332,     0,     0,   335,   336,     0,
       0,     0,     0,   339,   340,  -288,  -288,  -288,  -288,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,     0,     0,
    -288,  -288,  -288,     0,     0,  -288,     0,     0,     0,     0,
       0,  -288,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,     0,     0,     0,     0,  -288,     0,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,     0,
       0,     0,     0,     0,  -288,  -288,  -288,  -288,  -521,   253,
    -288,  -288,  -288,     0,  -288,     0,  -521,  -521,  -521,     0,
       0,     0,  -521,  -521,     0,  -521,     0,     0,     0,     0,
     689,     0,     0,     0,  -521,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -521,  -521,     0,  -521,  -521,
    -521,  -521,  -521,     0,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,     0,     0,   339,
     340,     0,     0,     0,     0,     0,  -521,  -521,  -521,  -521,
    -521,  -521,  -521,  -521,  -521,  -521,  -521,  -521,  -521,     0,
       0,  -521,  -521,  -521,     0,   691,   341,     0,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -92,  -521,     0,
    -521,  -521,  -521,  -521,  -521,  -521,  -521,  -521,  -521,  -521,
       0,     0,     0,     0,  -521,  -521,  -521,  -521,   -84,  -281,
       0,  -521,     0,  -521,     0,  -521,     0,  -281,  -281,  -281,
       0,     0,     0,  -281,  -281,     0,  -281,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -281,  -281,     0,  -281,
    -281,  -281,  -281,  -281,     0,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,     0,     0,
     339,   340,     0,     0,     0,  -229,     0,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
       0,     0,  -281,  -281,  -281,     0,   692,   341,     0,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,     0,
       0,     0,     0,     0,     0,     0,     0,  -229,   -94,  -281,
       0,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,     0,     0,     0,     0,     0,  -281,  -281,  -281,   -86,
       0,     0,  -281,     0,  -281,     4,  -281,     5,     6,     7,
       8,     9,  -539,  -539,  -539,    10,    11,     0,     0,  -539,
      12,     0,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,     0,    43,    44,    45,     0,
      46,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      48,     0,     0,    49,    50,     0,    51,    52,     0,    53,
       0,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,    62,    63,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -539,
       4,  -539,     5,     6,     7,     8,     9,     0,     0,  -539,
      10,    11,     0,  -539,  -539,    12,     0,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,     0,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     0,    41,    42,
       0,    43,    44,    45,     0,    46,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,     0,     0,    49,    50,
       0,    51,    52,     0,    53,     0,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -539,     4,  -539,     5,     6,     7,
       8,     9,     0,     0,  -539,    10,    11,     0,     0,  -539,
      12,  -539,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,     0,    43,    44,    45,     0,
      46,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      48,     0,     0,    49,    50,     0,    51,    52,     0,    53,
       0,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,    62,    63,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -539,
       4,  -539,     5,     6,     7,     8,     9,     0,     0,  -539,
      10,    11,     0,     0,  -539,    12,     0,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,     0,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     0,    41,    42,
       0,    43,    44,    45,     0,    46,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,     0,     0,    49,    50,
       0,    51,    52,     0,    53,     0,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,     0,     0,     0,     4,
       0,     5,     6,     7,     8,     9,     0,  -539,  -539,    10,
      11,    61,    62,    63,    12,     0,    13,    14,    15,    16,
      17,    18,    19,     0,  -539,     0,  -539,     0,    20,    21,
      22,    23,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,     0,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     0,    41,    42,     0,
      43,    44,    45,     0,    46,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    48,     0,     0,    49,    50,     0,
      51,    52,     0,    53,     0,    54,    55,    56,    57,    58,
      59,    60,     0,     0,     0,     0,     0,     0,     4,     0,
       5,     6,     7,     8,     9,     0,     0,     0,    10,    11,
      61,    62,    63,    12,     0,    13,    14,    15,    16,    17,
      18,    19,     0,  -539,     0,  -539,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,     0,    43,
      44,    45,     0,    46,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,     0,     0,   270,    50,     0,    51,
      52,     0,    53,     0,    54,    55,    56,    57,    58,    59,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,     0,     0,     0,     0,     0,     0,     0,     0,
    -539,     0,  -539,     4,  -539,     5,     6,     7,     8,     9,
       0,     0,     0,    10,    11,     0,     0,     0,    12,     0,
      13,    14,    15,    16,    17,    18,    19,     0,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,     0,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       0,    41,    42,     0,    43,    44,    45,     0,    46,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,     0,
       0,    49,    50,     0,    51,    52,     0,    53,     0,    54,
      55,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,     0,     0,     0,
       0,     0,     0,     0,     0,  -539,     0,  -539,     4,  -539,
       5,     6,     7,     8,     9,     0,     0,     0,    10,    11,
       0,     0,     0,    12,     0,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,     0,    43,
      44,    45,     0,    46,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,     0,     0,    49,    50,     0,    51,
      52,     0,    53,     0,    54,    55,    56,    57,    58,    59,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,     0,     0,  -539,     0,     0,     0,     0,     0,
       0,     0,  -539,     4,  -539,     5,     6,     7,     8,     9,
       0,     0,  -539,    10,    11,     0,     0,     0,    12,     0,
      13,    14,    15,    16,    17,    18,    19,     0,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,     0,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       0,    41,    42,     0,    43,    44,    45,     0,    46,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,     0,
       0,    49,    50,     0,    51,    52,     0,    53,     0,    54,
      55,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    61,    62,    63,    12,     0,    13,
      14,    15,   100,   101,    18,    19,     0,  -539,     0,  -539,
       0,   102,    21,    22,    23,    24,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,   239,
      41,    42,     0,    43,    44,    45,     0,    46,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   215,     0,     0,
     110,    50,     0,    51,    52,     0,   240,   241,    54,    55,
      56,    57,    58,    59,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     9,     0,     0,
       0,    10,    11,    61,   242,    63,    12,     0,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,   262,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,     0,    29,     0,     0,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,     0,    43,    44,    45,     0,    46,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   215,     0,     0,   110,
      50,     0,    51,    52,     0,     0,     0,    54,    55,    56,
      57,    58,    59,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     6,     7,     8,     9,     0,     0,     0,
      10,    11,    61,    62,    63,    12,     0,    13,    14,    15,
      16,    17,    18,    19,     0,   224,     0,   225,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,     0,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     0,    41,    42,
       0,    43,    44,    45,     0,    46,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,     0,     0,    49,    50,
       0,    51,    52,     0,    53,     0,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   403,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,     0,
       0,     0,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,     0,     0,     0,     0,     0,   154,   155,   156,
     157,   158,   159,   160,   161,   162,    37,    38,   163,    40,
       0,     0,     0,     0,     0,     0,     0,     0,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,   173,
     174,     0,     0,   175,   176,   177,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,     0,   190,   191,  -514,  -514,  -514,
       0,  -514,     0,   192,   193,  -514,  -514,     0,     0,     0,
    -514,     0,  -514,  -514,  -514,  -514,  -514,  -514,  -514,     0,
    -514,     0,     0,     0,  -514,  -514,  -514,  -514,  -514,  -514,
    -514,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -514,     0,     0,  -514,  -514,  -514,  -514,  -514,  -514,  -514,
    -514,  -514,  -514,  -514,  -514,     0,  -514,  -514,  -514,     0,
    -514,  -514,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -514,     0,     0,  -514,  -514,     0,  -514,  -514,     0,  -514,
    -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -514,  -514,  -514,     0,
    -514,  -515,  -515,  -515,     0,  -515,  -514,     0,     0,  -515,
    -515,     0,     0,     0,  -515,     0,  -515,  -515,  -515,  -515,
    -515,  -515,  -515,     0,  -515,     0,     0,     0,  -515,  -515,
    -515,  -515,  -515,  -515,  -515,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -515,     0,     0,  -515,  -515,  -515,
    -515,  -515,  -515,  -515,  -515,  -515,  -515,  -515,  -515,     0,
    -515,  -515,  -515,     0,  -515,  -515,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -515,     0,     0,  -515,  -515,     0,
    -515,  -515,     0,  -515,  -515,  -515,  -515,  -515,  -515,  -515,
    -515,  -515,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -515,  -515,  -515,     0,  -515,  -517,  -517,  -517,     0,  -517,
    -515,     0,     0,  -517,  -517,     0,     0,     0,  -517,     0,
    -517,  -517,  -517,  -517,  -517,  -517,  -517,     0,     0,     0,
       0,     0,  -517,  -517,  -517,  -517,  -517,  -517,  -517,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -517,     0,
       0,  -517,  -517,  -517,  -517,  -517,  -517,  -517,  -517,  -517,
    -517,  -517,  -517,     0,  -517,  -517,  -517,     0,  -517,  -517,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -517,   731,
       0,  -517,  -517,     0,  -517,  -517,     0,  -517,  -517,  -517,
    -517,  -517,  -517,  -517,  -517,  -517,     0,     0,     0,     0,
       0,   -92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -517,  -517,  -517,  -518,  -518,  -518,
       0,  -518,     0,     0,  -517,  -518,  -518,     0,     0,     0,
    -518,     0,  -518,  -518,  -518,  -518,  -518,  -518,  -518,     0,
       0,     0,     0,     0,  -518,  -518,  -518,  -518,  -518,  -518,
    -518,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -518,     0,     0,  -518,  -518,  -518,  -518,  -518,  -518,  -518,
    -518,  -518,  -518,  -518,  -518,     0,  -518,  -518,  -518,     0,
    -518,  -518,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -518,   692,     0,  -518,  -518,     0,  -518,  -518,     0,  -518,
    -518,  -518,  -518,  -518,  -518,  -518,  -518,  -518,     0,     0,
       0,     0,     0,   -94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -518,  -518,  -518,  -519,
    -519,  -519,     0,  -519,     0,     0,  -518,  -519,  -519,     0,
       0,     0,  -519,     0,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,     0,     0,     0,     0,     0,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -519,     0,     0,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,  -519,  -519,  -519,  -519,     0,  -519,  -519,
    -519,     0,  -519,  -519,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -519,     0,     0,  -519,  -519,     0,  -519,  -519,
       0,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -519,  -519,
    -519,  -520,  -520,  -520,     0,  -520,     0,     0,  -519,  -520,
    -520,     0,     0,     0,  -520,     0,  -520,  -520,  -520,  -520,
    -520,  -520,  -520,     0,     0,     0,     0,     0,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -520,     0,     0,  -520,  -520,  -520,
    -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,  -520,     0,
    -520,  -520,  -520,     0,  -520,  -520,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -520,     0,     0,  -520,  -520,     0,
    -520,  -520,     0,  -520,  -520,  -520,  -520,  -520,  -520,  -520,
    -520,  -520,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -520,  -520,  -520,     0,     0,     0,     0,     0,     0,     0,
    -520,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,     0,     0,     0,   144,   145,
     146,   199,   200,   201,   202,   151,   152,   153,     0,     0,
       0,     0,     0,   154,   155,   156,   157,   203,   204,   205,
     206,   162,   291,   292,   207,   293,     0,     0,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,   173,   174,     0,     0,   175,
     176,   177,   178,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
       0,   190,   191,     0,     0,     0,     0,     0,     0,   192,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,     0,     0,     0,   144,   145,   146,
     199,   200,   201,   202,   151,   152,   153,     0,     0,     0,
       0,     0,   154,   155,   156,   157,   203,   204,   205,   206,
     162,   260,     0,   207,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     0,     0,   173,   174,     0,     0,   175,   176,
     177,   178,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
     190,   191,     0,     0,     0,     0,     0,     0,   192,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,     0,     0,     0,   144,   145,   146,   199,
     200,   201,   202,   151,   152,   153,     0,     0,     0,     0,
       0,   154,   155,   156,   157,   203,   204,   205,   206,   162,
       0,     0,   207,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,   173,   174,     0,     0,   175,   176,   177,
     178,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,     0,     0,    55,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,     0,   190,
     191,     0,     0,     0,     0,     0,     0,   192,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,     0,     0,     0,   144,   145,   146,   199,   200,
     201,   202,   151,   152,   153,     0,     0,     0,     0,     0,
     154,   155,   156,   157,   203,   204,   205,   206,   162,     0,
       0,   207,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   164,   165,   166,   167,   168,   169,   170,   171,   172,
       0,     0,   173,   174,     0,     0,   175,   176,   177,   178,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,   190,   191,
       5,     6,     7,     0,     9,     0,   192,     0,    10,    11,
       0,     0,     0,    12,     0,    13,    14,    15,   100,   101,
      18,    19,     0,     0,     0,     0,     0,   102,   103,   104,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   105,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,     0,    43,
      44,    45,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   283,     0,     0,   110,    50,     0,    51,
      52,     0,     0,     0,    54,    55,    56,    57,    58,    59,
      60,     0,     0,     0,     0,     5,     6,     7,     0,     9,
       0,     0,     0,    10,    11,     0,     0,     0,    12,   111,
      13,    14,    15,   100,   101,    18,    19,   284,     0,     0,
       0,     0,   102,   103,   104,    23,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,     0,
       0,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       0,    41,    42,     0,    43,    44,    45,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   283,     0,
       0,   110,    50,     0,    51,    52,     0,     0,     0,    54,
      55,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       5,     6,     7,     8,     9,     0,     0,     0,    10,    11,
       0,     0,     0,    12,   111,    13,    14,    15,    16,    17,
      18,    19,   515,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,     0,    43,
      44,    45,     0,    46,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,     0,     0,    49,    50,     0,    51,
      52,     0,    53,     0,    54,    55,    56,    57,    58,    59,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    61,
      62,    63,    12,     0,    13,    14,    15,   100,   101,    18,
      19,     0,     0,     0,     0,     0,   102,    21,    22,    23,
      24,    25,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,   239,    41,    42,     0,    43,    44,
      45,     0,    46,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   215,     0,     0,   110,    50,     0,    51,    52,
       0,   240,   241,    54,    55,    56,    57,    58,    59,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,    61,   242,
      63,    12,     0,    13,    14,    15,   100,   101,    18,    19,
       0,     0,     0,     0,     0,   102,    21,    22,    23,    24,
      25,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    29,     0,     0,    32,    33,    34,    35,    36,    37,
      38,    39,    40,   239,    41,    42,     0,    43,    44,    45,
       0,    46,    47,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,     0,     0,   110,   423,     0,    51,    52,     0,
     240,   241,    54,    55,    56,    57,    58,    59,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,    61,   242,    63,
      12,     0,    13,    14,    15,   100,   101,    18,    19,     0,
       0,     0,     0,     0,   102,   103,   104,    23,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      29,     0,     0,    32,    33,    34,    35,    36,    37,    38,
      39,    40,   239,    41,    42,     0,    43,    44,    45,     0,
      46,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     215,     0,     0,   110,    50,     0,    51,    52,     0,   618,
     241,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       9,     0,     0,     0,    10,    11,    61,   242,    63,    12,
       0,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,     0,     0,    29,
       0,     0,    32,    33,    34,    35,    36,    37,    38,    39,
      40,   239,    41,    42,     0,    43,    44,    45,     0,    46,
      47,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   215,
       0,     0,   110,    50,     0,    51,    52,     0,     0,   241,
      54,    55,    56,    57,    58,    59,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     0,     9,
       0,     0,     0,    10,    11,    61,    62,    63,    12,     0,
      13,    14,    15,   100,   101,    18,    19,     0,     0,     0,
       0,     0,   102,   103,   104,    23,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
       0,    32,    33,    34,    35,    36,    37,    38,    39,    40,
     239,    41,    42,     0,    43,    44,    45,     0,    46,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
       0,   110,    50,     0,    51,    52,     0,   240,   241,    54,
      55,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    61,   242,    63,    12,     0,    13,
      14,    15,   100,   101,    18,    19,     0,     0,     0,     0,
       0,   102,   103,   104,    23,    24,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,   239,
      41,    42,     0,    43,    44,    45,     0,    46,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   215,     0,     0,
     110,    50,     0,    51,    52,     0,   240,     0,    54,    55,
      56,    57,    58,    59,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     9,     0,     0,
       0,    10,    11,    61,   242,    63,    12,     0,    13,    14,
      15,   100,   101,    18,    19,     0,     0,     0,     0,     0,
     102,   103,   104,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,     0,     0,    32,
      33,    34,    35,    36,    37,    38,    39,    40,   239,    41,
      42,     0,    43,    44,    45,     0,    46,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   215,     0,     0,   110,
      50,     0,    51,    52,     0,     0,   241,    54,    55,    56,
      57,    58,    59,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,    61,   242,    63,    12,     0,    13,    14,    15,
     100,   101,    18,    19,     0,     0,     0,     0,     0,   102,
     103,   104,    23,    24,    25,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,     0,     0,    32,    33,
      34,    35,    36,    37,    38,    39,    40,   239,    41,    42,
       0,    43,    44,    45,     0,    46,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,     0,     0,   110,    50,
       0,    51,    52,     0,   618,     0,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     6,     7,     0,     9,     0,     0,     0,    10,
      11,    61,   242,    63,    12,     0,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,     0,     0,    20,    21,
      22,    23,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,     0,     0,    29,     0,     0,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     0,    41,    42,     0,
      43,    44,    45,     0,    46,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,     0,   110,    50,     0,
      51,    52,     0,     0,     0,    54,    55,    56,    57,    58,
      59,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
      61,    62,    63,    12,     0,    13,    14,    15,   100,   101,
      18,    19,     0,     0,     0,     0,     0,   102,   103,   104,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    40,   239,    41,    42,     0,    43,
      44,    45,     0,    46,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   215,     0,     0,   110,    50,     0,    51,
      52,     0,     0,     0,    54,    55,    56,    57,    58,    59,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    61,
     242,    63,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,     0,    43,    44,
      45,     0,    46,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   215,     0,     0,   110,    50,     0,    51,    52,
       0,   509,     0,    54,    55,    56,    57,    58,    59,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,    61,   242,
      63,    12,     0,    13,    14,    15,   100,   101,    18,    19,
       0,     0,     0,     0,     0,   102,   103,   104,    23,    24,
      25,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    29,     0,     0,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     0,    41,    42,     0,    43,    44,    45,
       0,    46,    47,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,     0,     0,   110,    50,     0,    51,    52,     0,
     240,     0,    54,    55,    56,    57,    58,    59,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,    61,   242,    63,
      12,     0,    13,    14,    15,   100,   101,    18,    19,     0,
       0,     0,     0,     0,   102,   103,   104,    23,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      29,     0,     0,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,     0,    43,    44,    45,     0,
      46,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     215,     0,     0,   110,    50,     0,    51,    52,     0,   509,
       0,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       9,     0,     0,     0,    10,    11,    61,   242,    63,    12,
       0,    13,    14,    15,   100,   101,    18,    19,     0,     0,
       0,     0,     0,   102,   103,   104,    23,    24,    25,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,     0,    32,    33,    34,    35,    36,    37,    38,    39,
      40,     0,    41,    42,     0,    43,    44,    45,     0,    46,
      47,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   215,
       0,     0,   110,    50,     0,    51,    52,     0,   787,     0,
      54,    55,    56,    57,    58,    59,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     0,     9,
       0,     0,     0,    10,    11,    61,   242,    63,    12,     0,
      13,    14,    15,   100,   101,    18,    19,     0,     0,     0,
       0,     0,   102,   103,   104,    23,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
       0,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       0,    41,    42,     0,    43,    44,    45,     0,    46,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
       0,   110,    50,     0,    51,    52,     0,   618,     0,    54,
      55,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    61,   242,    63,    12,     0,    13,
      14,    15,   100,   101,    18,    19,     0,     0,     0,     0,
       0,   102,   103,   104,    23,    24,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,     0,    43,    44,    45,     0,    46,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   215,     0,     0,
     110,    50,     0,    51,    52,     0,     0,     0,    54,    55,
      56,    57,    58,    59,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     9,     0,     0,
       0,    10,    11,    61,   242,    63,    12,     0,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,     0,     0,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,     0,    43,    44,    45,     0,    46,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   215,     0,     0,   110,
      50,     0,    51,    52,     0,     0,     0,    54,    55,    56,
      57,    58,    59,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,    61,   242,    63,    12,     0,    13,    14,    15,
     100,   101,    18,    19,     0,     0,     0,     0,     0,   102,
     103,   104,    23,    24,    25,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,     0,     0,    32,    33,
      34,   106,    36,    37,    38,   107,    40,     0,    41,    42,
       0,    43,    44,    45,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   108,     0,     0,   109,     0,     0,   110,    50,
       0,    51,    52,     0,     0,     0,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,     0,     0,     0,
      12,   111,    13,    14,    15,   100,   101,    18,    19,     0,
       0,     0,     0,     0,   102,   103,   104,    23,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,     0,     0,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,     0,    43,    44,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     232,     0,     0,    49,    50,     0,    51,    52,     0,    53,
       0,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,     0,     0,     0,    12,   111,    13,    14,    15,
     100,   101,    18,    19,     0,     0,     0,     0,     0,   102,
     103,   104,    23,    24,    25,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,     0,     0,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     0,    41,    42,
       0,    43,    44,    45,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   283,     0,     0,   322,    50,
       0,    51,    52,     0,   323,     0,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,     0,     0,     0,
      12,   111,    13,    14,    15,   100,   101,    18,    19,     0,
       0,     0,     0,     0,   102,   103,   104,    23,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,     0,     0,    32,    33,    34,   106,    36,    37,    38,
     107,    40,     0,    41,    42,     0,    43,    44,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,     0,     0,   110,    50,     0,    51,    52,     0,     0,
       0,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,     0,     0,     0,    12,   111,    13,    14,    15,
     100,   101,    18,    19,     0,     0,     0,     0,     0,   102,
     103,   104,    23,    24,    25,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,     0,     0,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     0,    41,    42,
       0,    43,    44,    45,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   283,     0,     0,   322,    50,
       0,    51,    52,     0,     0,     0,    54,    55,    56,    57,
      58,    59,    60,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,     0,     0,     0,
      12,   111,    13,    14,    15,   100,   101,    18,    19,     0,
       0,     0,     0,     0,   102,   103,   104,    23,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,     0,     0,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,     0,    43,    44,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     868,     0,     0,   110,    50,     0,    51,    52,     0,     0,
       0,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,     0,     0,   548,   549,     0,     0,   550,     0,     0,
       0,     0,     0,     0,     0,     0,   111,   164,   165,   166,
     167,   168,   169,   170,   171,   172,     0,     0,   173,   174,
       0,     0,   175,   176,   177,   178,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,   190,   191,   556,   557,     0,     0,
     558,     0,   192,   256,     0,     0,     0,     0,     0,     0,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,   173,   174,     0,     0,   175,   176,   177,   178,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,     0,   190,   191,   578,
     549,     0,     0,   579,     0,   192,   256,     0,     0,     0,
       0,     0,     0,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     0,     0,   173,   174,     0,     0,   175,   176,
     177,   178,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
     190,   191,   562,   557,     0,     0,   563,     0,   192,   256,
       0,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,   173,   174,     0,
       0,   175,   176,   177,   178,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,     0,   190,   191,   598,   549,     0,     0,   599,
       0,   192,   256,     0,     0,     0,     0,     0,     0,   164,
     165,   166,   167,   168,   169,   170,   171,   172,     0,     0,
     173,   174,     0,     0,   175,   176,   177,   178,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,     0,   190,   191,   601,   557,
       0,     0,   602,     0,   192,   256,     0,     0,     0,     0,
       0,     0,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,   173,   174,     0,     0,   175,   176,   177,
     178,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,     0,   190,
     191,   611,   549,     0,     0,   612,     0,   192,   256,     0,
       0,     0,     0,     0,     0,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,     0,   173,   174,     0,     0,
     175,   176,   177,   178,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,     0,   190,   191,   614,   557,     0,     0,   615,     0,
     192,   256,     0,     0,     0,     0,     0,     0,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,   173,
     174,     0,     0,   175,   176,   177,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,     0,   190,   191,   643,   549,     0,
       0,   644,     0,   192,   256,     0,     0,     0,     0,     0,
       0,   164,   165,   166,   167,   168,   169,   170,   171,   172,
       0,     0,   173,   174,     0,     0,   175,   176,   177,   178,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,   190,   191,
     646,   557,     0,     0,   647,     0,   192,   256,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,   173,   174,     0,     0,   175,
     176,   177,   178,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
       0,   190,   191,   919,   549,     0,     0,   920,     0,   192,
     256,     0,     0,     0,     0,     0,     0,   164,   165,   166,
     167,   168,   169,   170,   171,   172,     0,     0,   173,   174,
       0,     0,   175,   176,   177,   178,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,   190,   191,   922,   557,     0,     0,
     923,     0,   192,   256,     0,     0,     0,     0,     0,     0,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,   173,   174,     0,     0,   175,   176,   177,   178,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,     0,   190,   191,   562,
     557,     0,     0,   563,     0,   192,   256,     0,     0,     0,
       0,     0,     0,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     0,     0,   173,   174,     0,     0,   175,   176,
     177,   178,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
     190,   191,     0,     0,     0,     0,     0,     0,   192
};

static const yytype_int16 yycheck[] =
{
       2,     7,     4,     5,     6,    51,    22,    29,    10,    11,
      12,     7,     8,    15,    16,    17,   405,   223,    20,   249,
      74,   290,    12,     8,     8,    27,   400,    53,    62,    49,
      16,    17,    28,   109,    20,    28,   325,    11,    12,   455,
     353,   380,   666,    28,    28,   593,     4,    49,    50,    55,
     277,    53,    51,    52,   281,   603,   660,   758,   415,    55,
      62,   418,   756,     1,   663,   378,   423,   352,    27,   354,
     355,   356,    74,   582,    65,    65,   566,   567,   656,    26,
      25,    97,   395,   105,   297,    22,    13,    13,   301,    25,
      29,   600,    13,    25,   379,   408,    16,    17,   290,   515,
      20,    25,   680,    68,   613,    85,   108,    26,   110,   394,
      13,   396,    25,   464,     2,    87,    25,     2,    13,     4,
     270,    13,    85,   113,   409,    10,    11,    12,    25,     0,
      85,    16,    17,    76,   137,    20,   645,   109,    61,    25,
     663,   835,    27,   666,   457,    85,    52,    25,   128,   129,
      56,    85,   132,   438,   119,   120,   121,   680,    37,    38,
      97,    49,   130,   130,    49,    50,   129,   104,   107,   137,
     137,   114,   322,   458,   129,   113,   135,    62,   137,   126,
      25,   118,   126,   106,   885,   130,    56,   132,   128,   129,
     382,     5,     6,   887,   130,   129,   109,   135,   130,   137,
     469,    15,    28,   781,   130,   132,   130,   126,   135,   135,
     137,   137,   214,   132,   135,   909,   137,   130,   842,   709,
     133,   130,   110,   108,   137,   110,   136,    85,   230,   231,
     284,    85,   135,   130,   137,   226,   226,   841,   577,    53,
     135,    88,   137,   135,   130,   137,   132,   846,   587,    85,
     270,   253,   130,   255,   256,   854,   230,   231,   137,   418,
      74,    61,    85,   265,   109,    87,   694,   253,   270,   255,
     256,   129,   688,   701,   320,   129,   824,   469,    85,   325,
     493,    61,   284,   130,   136,   130,   320,   109,   133,   448,
      85,   325,   137,   129,    87,    59,    60,   323,    61,   650,
     651,   377,   322,   592,   104,   105,   129,   109,   310,   311,
     312,   313,   314,   315,   316,   317,   109,   586,   320,   842,
     322,   323,   129,   325,   104,   105,   106,   361,   362,   214,
      61,   854,    87,   253,   129,   255,   136,   311,   312,   313,
     314,   104,   105,   106,   109,   230,   231,    10,    11,    12,
      87,   353,   310,   742,   109,   401,   352,   315,    85,   361,
     362,   135,    87,   137,    27,   130,    85,   353,   253,   130,
     255,   256,   109,   104,   105,   106,   378,   265,   380,   381,
     265,   377,   270,   373,   109,   270,    54,    50,   745,   391,
      99,   621,   378,   395,   586,    63,    64,   399,   394,   605,
     630,   455,   129,    37,    38,   756,   408,   758,    85,   395,
     129,   407,   921,   640,   404,   405,   415,   354,    15,   109,
      17,   423,   408,    87,   423,   310,   311,   312,   313,   314,
     315,   316,   317,   435,   322,   320,   432,   322,    85,   432,
     325,   437,   379,    59,    60,   108,   445,   432,   432,   132,
     824,   128,   129,   455,   132,   457,    85,    14,    15,   396,
     456,   515,    56,    26,    85,   564,   565,   806,   353,   130,
     284,   457,   409,    61,    57,    58,   361,   362,   109,    87,
      17,   128,   129,   666,   835,   836,   669,    52,   680,    54,
      55,    56,    57,   378,   135,   380,   381,   680,    87,   128,
     129,   438,    56,   391,    25,   130,   391,   128,   129,   323,
     395,   399,    88,   515,   399,   537,   104,   105,   106,   130,
     109,   458,    85,   408,    89,   882,   132,   126,   867,    68,
      95,    96,   133,   555,   885,   109,   887,   553,   423,   134,
     127,   130,   477,    56,   479,   561,   592,   435,   564,   565,
     435,   116,    61,   130,   119,   106,    65,   106,   909,   130,
     582,    68,    68,   126,    94,   128,   129,   230,   231,   132,
     135,    10,   457,     8,   576,   577,    13,    85,   600,    10,
     133,    26,    85,   589,   574,   587,    85,   641,   130,   902,
     130,   613,   127,   589,   590,   104,   105,   590,   588,   829,
     830,   135,   576,   130,   109,   590,   590,   813,   130,    52,
     130,    52,    26,   819,   616,   130,   553,   136,   903,   811,
     128,   129,    10,   645,   561,   128,   129,   564,   565,   128,
     129,   633,    85,    52,   688,    54,    55,    56,    57,   641,
      85,   455,   616,   130,   581,    87,   583,    87,   311,   312,
     313,   314,   130,   316,   317,   657,   658,   691,    15,   842,
      85,   844,    10,   697,   698,   848,   127,   109,   130,   109,
     672,    85,   130,   856,    26,   128,   129,   907,   111,   681,
     134,   126,    10,   128,   129,    10,   688,   132,   130,   691,
     130,   576,   577,    88,     9,   697,   698,    10,    85,   745,
      10,   515,   587,   128,   129,   707,   708,    87,    87,    16,
      17,   130,   126,    20,   128,   129,    10,   130,   381,   127,
     130,   711,   127,   725,   130,    87,   728,   130,   911,   109,
     109,   616,   915,    85,   130,    10,   738,   739,   740,    46,
      47,   128,   129,   114,    51,    52,   745,   109,   633,    68,
     130,   130,   742,   130,   728,    62,    63,   130,   130,    10,
     423,   130,   127,   797,    83,    84,   130,    10,   130,   657,
     658,    10,   657,   658,   126,   130,   128,   129,   114,   130,
     132,   127,    10,    56,   672,   130,    52,   672,    54,    55,
      56,    57,   130,   681,    10,   797,   681,   116,   117,   118,
     119,   120,   121,   805,   806,    10,   691,    51,    52,    68,
     812,    15,   697,   698,   816,   272,   130,     6,   905,   707,
     708,   650,   707,   708,    83,    84,    52,   641,    54,    55,
      56,    57,   841,   768,   769,    68,   771,   725,   773,   774,
     725,    81,    52,   728,    54,    55,    56,    57,   783,   784,
     738,   739,   740,   738,   739,   740,   904,    84,   117,   118,
     119,   120,   121,    89,   130,   867,     7,   663,    65,    95,
      96,   873,    -1,   875,   688,    -1,    -1,    -1,   811,   881,
      -1,    -1,    -1,   882,   117,   118,   119,   120,   121,    -1,
     116,    -1,    52,   119,    54,    55,    56,    57,    -1,   921,
     902,    54,    55,    -1,    57,   901,   132,    -1,    -1,    -1,
      63,    64,   797,   576,    -1,    -1,   902,   805,    -1,    -1,
     805,   806,    52,    -1,    54,    55,    56,    57,   816,    89,
      -1,   816,   239,   240,   241,   242,    52,    -1,    54,    55,
      56,    57,    -1,    -1,    -1,    -1,   253,    -1,   255,   256,
      -1,    -1,    -1,   616,    -1,   890,   891,   892,   893,    89,
     895,   896,    -1,   420,    -1,    95,   903,    -1,    -1,   426,
     633,    -1,    52,    89,    54,    55,    56,    57,    -1,    95,
      96,    -1,   867,   440,    -1,   873,   443,   875,   873,    -1,
     875,    -1,    -1,   881,   929,   930,   881,    -1,   812,    -1,
     116,    -1,    -1,   119,   248,   249,    -1,    -1,    -1,    89,
      -1,    -1,   256,   320,    -1,    95,   132,   902,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,     2,   353,     4,     5,     6,
       7,    -1,    -1,    -1,   361,   362,    -1,   514,    15,    40,
      41,    42,    43,    44,    -1,   728,    -1,    -1,    -1,    -1,
      -1,   378,    -1,    -1,    -1,    52,    -1,    54,    55,    56,
      57,    -1,    -1,    -1,    -1,    -1,   393,    -1,   395,    -1,
     397,   398,    49,    -1,   401,    -1,    53,    -1,    -1,    -1,
      -1,   408,    -1,    -1,    -1,    -1,    -1,   414,   415,   353,
      -1,   418,    89,    -1,    -1,    -1,   423,    74,    95,    96,
      -1,    52,    -1,    54,    55,    56,    57,   434,   585,    -1,
      -1,    -1,   439,    -1,   378,    -1,    -1,    -1,   445,   116,
      -1,   448,   119,    -1,   388,    -1,    -1,    -1,    44,    -1,
     457,   395,    -1,   110,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    -1,   408,    96,    -1,    -1,    -1,    -1,
      -1,   628,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,   116,    -1,    83,    84,    -1,
      -1,   498,   499,    -1,    -1,    -1,    -1,   654,    -1,    -1,
      -1,    -1,   509,    -1,    52,    -1,    54,    55,    56,    57,
      -1,    -1,    -1,   457,   110,    -1,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,    -1,   471,    -1,    -1,
      -1,   475,    -1,   477,   130,   479,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,     2,    -1,     4,    95,    96,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   214,    -1,   716,
      -1,    -1,    -1,    -1,   508,    -1,    -1,    -1,   116,    -1,
      -1,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     2,    -1,     4,    68,   592,    -1,    -1,    -1,   746,
      -1,    49,   749,    -1,    15,    -1,    -1,    -1,   755,    83,
      84,    -1,    -1,   760,    -1,    -1,    -1,    -1,   265,    -1,
      -1,   618,    -1,   270,    -1,    -1,    -1,   561,    -1,    -1,
     564,   565,   566,   567,    -1,    -1,    -1,   284,    49,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,    -1,   583,
      -1,   648,    -1,    -1,    -1,    -1,    -1,    -1,   592,   593,
      -1,   595,   110,   310,    -1,    -1,    -1,    -1,   315,   603,
       2,    -1,     4,     5,     6,   322,   323,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    -1,   621,   685,    -1,
      -1,    -1,   689,    -1,   691,   692,   630,    -1,    -1,   110,
     697,   698,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    49,    77,    78,
      -1,    53,   656,    -1,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   380,   731,    -1,   733,   734,    -1,    -1,
     737,    -1,    74,    -1,   391,    -1,   680,    52,   745,    -1,
      -1,    -1,   399,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,    -1,    -1,    -1,   214,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   709,    -1,    -1,   110,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   435,   723,
     787,    -1,   726,    -1,   791,    -1,    -1,    -1,    -1,    -1,
     797,    -1,    -1,   214,    -1,    -1,    -1,    -1,   455,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,    -1,    -1,
      -1,    -1,   270,    -1,   821,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   768,   769,    -1,   771,    -1,   773,
     774,    -1,    -1,    -1,    -1,    -1,    -1,   781,    -1,   783,
     784,    -1,    -1,    -1,   265,    -1,    -1,    -1,    -1,   270,
      -1,    -1,   310,    -1,    -1,    -1,    -1,   315,   515,    -1,
      -1,    -1,    -1,    -1,   322,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   214,    -1,    -1,   882,    -1,    -1,    -1,    -1,
     824,    -1,    -1,    -1,    -1,   829,   830,    -1,    -1,   310,
      -1,    -1,    -1,    -1,   315,   902,    -1,    -1,    -1,    -1,
      -1,   322,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     577,    -1,   380,   265,   239,   240,   241,    -1,   270,    -1,
     587,    -1,    -1,   391,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   399,   284,    -1,    -1,    -1,   890,   891,   892,   893,
      -1,   895,   896,    -1,    -1,    -1,    -1,    -1,   902,   380,
     904,   905,    -1,   907,    -1,    -1,    -1,    -1,   310,    -1,
     391,    -1,    -1,   315,    -1,    -1,    -1,   435,   399,    -1,
     322,   323,    -1,    -1,   641,   929,   930,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     657,   658,    -1,    -1,    -1,   320,    -1,    -1,    -1,    -1,
     325,    -1,    -1,    -1,   435,   672,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   681,    -1,    -1,    -1,    -1,    -1,
      -1,   688,    -1,    -1,    -1,    -1,    -1,    -1,   380,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   391,
     707,   708,    -1,    -1,    -1,    -1,    -1,   399,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   725,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   738,   739,   740,    -1,    -1,   401,    -1,    -1,    -1,
      -1,    -1,    -1,   435,    -1,    -1,    -1,    -1,    -1,   414,
     415,    -1,    -1,   418,    -1,    -1,    -1,    -1,   423,    -1,
      -1,    -1,    -1,   455,    -1,    -1,    -1,    -1,    -1,   577,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   587,
     445,    -1,    -1,   448,    -1,    -1,    -1,     0,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,     9,    10,   805,   806,
      13,    14,    15,    -1,    17,   812,   577,    -1,    -1,   816,
      -1,    -1,    -1,    -1,    27,    -1,   587,    -1,    -1,    -1,
      -1,    -1,    -1,   515,    37,    38,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   509,    -1,    -1,    -1,    -1,   657,
     658,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     867,    -1,    -1,    -1,   672,    -1,   873,    -1,   875,    -1,
      -1,    -1,    85,   681,   881,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   577,   657,   658,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   587,    -1,    -1,    -1,   707,
     708,   672,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     681,    -1,    -1,    -1,   127,    -1,   129,   725,    -1,   132,
     133,    -1,   135,    -1,   137,    -1,    -1,   592,    -1,    -1,
     738,   739,   740,    -1,    -1,    -1,   707,   708,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   641,
      -1,    -1,    -1,   618,   725,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   657,   658,   738,   739,   740,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     672,   673,    -1,   648,    -1,    -1,    -1,    -1,    -1,   681,
      -1,    -1,    -1,    -1,    -1,    -1,   688,   805,   806,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   816,    -1,
      -1,    -1,    -1,    -1,    -1,   707,   708,    -1,    -1,    -1,
     685,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   725,   805,   806,    -1,    -1,    -1,    -1,
      -1,   812,    -1,    -1,    -1,   816,   738,   739,   740,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   867,
      -1,    -1,    -1,    -1,    -1,   873,    -1,   875,    -1,    -1,
      -1,    -1,   737,   881,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   867,    -1,    83,    84,
      -1,    -1,   873,    -1,   875,    -1,    -1,    -1,    -1,    -1,
     881,    -1,    -1,   805,   806,    -1,    -1,    -1,    -1,    -1,
     812,    -1,   787,    -1,   816,   110,    -1,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   137,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   867,    -1,    -1,    -1,    -1,
      -1,   873,    -1,   875,    -1,    -1,    -1,    -1,    -1,   881,
       0,     1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,   882,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    64,    -1,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      90,    -1,    92,    93,    -1,    95,    -1,    97,    98,    99,
     100,   101,   102,   103,     0,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     8,     9,    10,    -1,    -1,    13,    14,    15,
      -1,    17,   122,   123,   124,    -1,    -1,    -1,    -1,    -1,
      26,    27,    28,    -1,    -1,   135,    -1,   137,    -1,    -1,
      -1,    37,    38,    -1,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    -1,
      83,    84,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    -1,    -1,    83,    84,    85,
      -1,    -1,    88,    -1,    -1,    -1,    -1,   110,    94,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,    -1,   110,    -1,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,    -1,    -1,    -1,    -1,
     126,   127,   128,   129,   130,     0,   132,   133,   134,   135,
      -1,   137,    -1,     8,     9,    10,    -1,    -1,    13,    14,
      15,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      -1,    83,    84,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    83,    84,
      85,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    94,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      -1,    -1,   107,    -1,    -1,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,    -1,    -1,    -1,
      -1,    -1,   127,   128,   129,   130,     0,    -1,   133,   134,
     135,    -1,   137,    -1,     8,     9,    10,    -1,    -1,    13,
      14,    15,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    77,    78,    -1,    -1,
      -1,    -1,    83,    84,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    -1,    -1,    83,
      84,    85,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,
      94,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,    -1,    -1,    -1,    -1,    -1,   110,    -1,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,    -1,    -1,
      -1,    -1,   126,   127,   128,   129,   130,     0,   132,   133,
     134,   135,    -1,   137,    -1,     8,     9,    10,    -1,    -1,
      13,    14,    15,    -1,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    -1,    -1,    77,    78,    -1,
      -1,    -1,    -1,    83,    84,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    -1,
      83,    84,    85,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      -1,    94,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,    -1,    -1,    -1,    -1,    -1,   110,    -1,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,    -1,   127,   128,   129,   130,     0,   132,
     133,   134,   135,    -1,   137,    -1,     8,     9,    10,    -1,
      -1,    -1,    14,    15,    -1,    17,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,
      42,    43,    44,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    -1,    -1,    83,
      84,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      -1,    83,    84,    85,    -1,    87,   110,    -1,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,   110,    -1,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,     0,
      -1,   133,    -1,   135,    -1,   137,    -1,     8,     9,    10,
      -1,    -1,    -1,    14,    15,    -1,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,
      41,    42,    43,    44,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    -1,
      83,    84,    -1,    -1,    -1,    88,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      -1,    -1,    83,    84,    85,    -1,    87,   110,    -1,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,   109,   110,
      -1,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,    -1,    -1,    -1,    -1,    -1,   127,   128,   129,   130,
      -1,    -1,   133,    -1,   135,     1,   137,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    -1,    -1,    15,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    64,    -1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    90,    -1,    92,    93,    -1,    95,
      -1,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,   123,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   135,
       1,   137,     3,     4,     5,     6,     7,    -1,    -1,    10,
      11,    12,    -1,    14,    15,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    64,    -1,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,
      -1,    92,    93,    -1,    95,    -1,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   122,   123,   124,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   135,     1,   137,     3,     4,     5,
       6,     7,    -1,    -1,    10,    11,    12,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    64,    -1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    90,    -1,    92,    93,    -1,    95,
      -1,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,   123,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   135,
       1,   137,     3,     4,     5,     6,     7,    -1,    -1,    10,
      11,    12,    -1,    -1,    15,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    64,    -1,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,
      -1,    92,    93,    -1,    95,    -1,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,     4,     5,     6,     7,    -1,     9,    10,    11,
      12,   122,   123,   124,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,   135,    -1,   137,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      62,    63,    64,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,
      92,    93,    -1,    95,    -1,    97,    98,    99,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    12,
     122,   123,   124,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,   135,    -1,   137,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    64,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,    92,
      93,    -1,    95,    -1,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,
     123,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     133,    -1,   135,     1,   137,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    64,    -1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    90,    -1,    92,    93,    -1,    95,    -1,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   122,   123,   124,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   133,    -1,   135,     1,   137,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    64,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,    92,
      93,    -1,    95,    -1,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,
     123,   124,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   135,     1,   137,     3,     4,     5,     6,     7,
      -1,    -1,    10,    11,    12,    -1,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    64,    -1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    90,    -1,    92,    93,    -1,    95,    -1,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   122,   123,   124,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,   135,    -1,   137,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      89,    90,    -1,    92,    93,    -1,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,   122,   123,   124,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,   137,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    64,    -1,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      90,    -1,    92,    93,    -1,    -1,    -1,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    12,   122,   123,   124,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,   135,    -1,   137,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    64,    -1,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,
      -1,    92,    93,    -1,    95,    -1,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   122,   123,   124,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   135,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    77,
      78,    -1,    -1,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,    -1,   123,   124,     3,     4,     5,
      -1,     7,    -1,   131,   132,    11,    12,    -1,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    63,    64,    -1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    90,    -1,    92,    93,    -1,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,   123,   124,    -1,
     126,     3,     4,     5,    -1,     7,   132,    -1,    -1,    11,
      12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    63,    64,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,
      92,    93,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,   123,   124,    -1,   126,     3,     4,     5,    -1,     7,
     132,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    63,    64,    -1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      -1,    89,    90,    -1,    92,    93,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   122,   123,   124,     3,     4,     5,
      -1,     7,    -1,    -1,   132,    11,    12,    -1,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    63,    64,    -1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    87,    -1,    89,    90,    -1,    92,    93,    -1,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,   123,   124,     3,
       4,     5,    -1,     7,    -1,    -1,   132,    11,    12,    -1,
      -1,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    63,
      64,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    89,    90,    -1,    92,    93,
      -1,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,   123,
     124,     3,     4,     5,    -1,     7,    -1,    -1,   132,    11,
      12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    63,    64,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,
      92,    93,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,   123,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     132,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    77,    78,    -1,    -1,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      -1,   123,   124,    -1,    -1,    -1,    -1,    -1,    -1,   131,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    77,    78,    -1,    -1,    81,    82,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    -1,    -1,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,    -1,
     123,   124,    -1,    -1,    -1,    -1,    -1,    -1,   131,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    77,    78,    -1,    -1,    81,    82,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,    -1,   123,
     124,    -1,    -1,    -1,    -1,    -1,    -1,   131,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    77,    78,    -1,    -1,    81,    82,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,    -1,   123,   124,
       3,     4,     5,    -1,     7,    -1,   131,    -1,    11,    12,
      -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,    92,
      93,    -1,    -1,    -1,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,   122,
      18,    19,    20,    21,    22,    23,    24,   130,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    90,    -1,    92,    93,    -1,    -1,    -1,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    16,   122,    18,    19,    20,    21,    22,
      23,    24,   130,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    64,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,    92,
      93,    -1,    95,    -1,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   122,
     123,   124,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    63,
      64,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    89,    90,    -1,    92,    93,
      -1,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,   122,   123,
     124,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    89,    90,    -1,    92,    93,    -1,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,   122,   123,   124,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    63,    64,    -1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    90,    -1,    92,    93,    -1,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,   122,   123,   124,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    89,    90,    -1,    92,    93,    -1,    -1,    96,
      97,    98,    99,   100,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,   122,   123,   124,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    63,    64,    -1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    90,    -1,    92,    93,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   122,   123,   124,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      89,    90,    -1,    92,    93,    -1,    95,    -1,    97,    98,
      99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,   122,   123,   124,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    63,    64,    -1,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      90,    -1,    92,    93,    -1,    -1,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,   122,   123,   124,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,
      -1,    92,    93,    -1,    95,    -1,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,   122,   123,   124,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      62,    63,    64,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,
      92,    93,    -1,    -1,    -1,    97,    98,    99,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
     122,   123,   124,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,    92,
      93,    -1,    -1,    -1,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   122,
     123,   124,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    62,    63,
      64,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    89,    90,    -1,    92,    93,
      -1,    95,    -1,    97,    98,    99,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,   122,   123,
     124,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    -1,    62,    63,    64,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    89,    90,    -1,    92,    93,    -1,
      95,    -1,    97,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,   122,   123,   124,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    64,    -1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    90,    -1,    92,    93,    -1,    95,
      -1,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,   122,   123,   124,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    -1,    62,    63,    64,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    89,    90,    -1,    92,    93,    -1,    95,    -1,
      97,    98,    99,   100,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,   122,   123,   124,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    64,    -1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    90,    -1,    92,    93,    -1,    95,    -1,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   122,   123,   124,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    -1,    62,    63,    64,    -1,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      89,    90,    -1,    92,    93,    -1,    -1,    -1,    97,    98,
      99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,   122,   123,   124,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    64,    -1,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      90,    -1,    92,    93,    -1,    -1,    -1,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,   122,   123,   124,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    -1,    -1,    86,    -1,    -1,    89,    90,
      -1,    92,    93,    -1,    -1,    -1,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      16,   122,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    90,    -1,    92,    93,    -1,    95,
      -1,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,    -1,    -1,    -1,    16,   122,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,
      -1,    92,    93,    -1,    95,    -1,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      16,   122,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    90,    -1,    92,    93,    -1,    -1,
      -1,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,    -1,    -1,    -1,    16,   122,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,
      -1,    92,    93,    -1,    -1,    -1,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      16,   122,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    90,    -1,    92,    93,    -1,    -1,
      -1,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    77,    78,
      -1,    -1,    81,    82,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,    -1,   123,   124,    52,    53,    -1,    -1,
      56,    -1,   131,   132,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    77,    78,    -1,    -1,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,    -1,   123,   124,    52,
      53,    -1,    -1,    56,    -1,   131,   132,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    77,    78,    -1,    -1,    81,    82,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,    -1,
     123,   124,    52,    53,    -1,    -1,    56,    -1,   131,   132,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    -1,    -1,    77,    78,    -1,
      -1,    81,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,    -1,   123,   124,    52,    53,    -1,    -1,    56,
      -1,   131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      77,    78,    -1,    -1,    81,    82,    83,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,    -1,   123,   124,    52,    53,
      -1,    -1,    56,    -1,   131,   132,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    77,    78,    -1,    -1,    81,    82,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,    -1,   123,
     124,    52,    53,    -1,    -1,    56,    -1,   131,   132,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    77,    78,    -1,    -1,
      81,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,    -1,   123,   124,    52,    53,    -1,    -1,    56,    -1,
     131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    77,
      78,    -1,    -1,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,    -1,   123,   124,    52,    53,    -1,
      -1,    56,    -1,   131,   132,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    77,    78,    -1,    -1,    81,    82,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,    -1,   123,   124,
      52,    53,    -1,    -1,    56,    -1,   131,   132,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    77,    78,    -1,    -1,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      -1,   123,   124,    52,    53,    -1,    -1,    56,    -1,   131,
     132,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    77,    78,
      -1,    -1,    81,    82,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,    -1,   123,   124,    52,    53,    -1,    -1,
      56,    -1,   131,   132,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    77,    78,    -1,    -1,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,    -1,   123,   124,    52,
      53,    -1,    -1,    56,    -1,   131,   132,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    77,    78,    -1,    -1,    81,    82,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,    -1,
     123,   124,    -1,    -1,    -1,    -1,    -1,    -1,   131
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   139,   140,     0,     1,     3,     4,     5,     6,     7,
      11,    12,    16,    18,    19,    20,    21,    22,    23,    24,
      30,    31,    32,    33,    34,    35,    36,    39,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    59,    60,    62,    63,    64,    66,    67,    86,    89,
      90,    92,    93,    95,    97,    98,    99,   100,   101,   102,
     103,   122,   123,   124,   142,   143,   144,   147,   149,   150,
     153,   154,   156,   157,   158,   160,   161,   171,   189,   206,
     227,   228,   238,   239,   240,   241,   242,   243,   244,   247,
     255,   257,   258,   259,   260,   261,   262,   283,   294,   144,
      21,    22,    30,    31,    32,    46,    52,    56,    83,    86,
      89,   122,   162,   163,   189,   206,   259,   262,   283,   163,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    56,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    77,    78,    81,    82,    83,    84,    95,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     123,   124,   131,   132,   164,   169,   170,   260,   278,    33,
      34,    35,    36,    49,    50,    51,    52,    56,   164,   165,
     166,   167,   255,   257,   190,    86,   147,   148,   161,   206,
     259,   261,   262,   148,   135,   137,   148,   287,   292,   293,
     193,   195,    86,   154,   161,   206,   211,   259,   262,    58,
      95,    96,   123,   153,   171,   173,   178,   185,   187,   281,
     282,   178,   178,   132,   180,   181,   132,   175,   180,   147,
      54,   166,   137,   288,   146,   126,   171,   206,   171,    56,
      89,   142,   155,   156,   147,   174,   187,   281,   294,   173,
     280,   281,   294,    86,   130,   160,   206,   259,   262,   221,
     222,    54,    55,    57,   164,   250,   256,   249,   250,   250,
     136,   245,   136,   248,    59,    60,   149,   171,   171,   287,
     293,    40,    41,    42,    43,    44,    37,    38,    28,   225,
     109,   130,    89,    95,   157,   109,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    83,
      84,   110,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,    85,   128,   129,    85,   129,    26,   126,   229,
     241,    87,    87,   175,   180,   229,   288,   147,    52,    56,
     162,    59,    60,     1,   113,   263,   292,    85,   128,   129,
     202,   279,   203,    85,   129,   286,   130,   141,   142,    56,
      13,   207,   292,   109,    85,   128,   129,    87,    87,   207,
     287,    17,   232,   135,   148,   148,    56,    85,   128,   129,
      25,   173,   173,   173,    88,   130,   186,   294,   130,   186,
     178,   288,   289,    90,   178,   182,   177,   178,   294,    54,
      63,    64,   145,   132,   172,   126,   142,    85,   129,    87,
     155,   133,   289,   191,   134,   130,   137,   291,   130,   291,
     127,   291,    56,   157,   159,   130,    85,   128,   129,    52,
      54,    55,    56,    57,    89,    95,    96,   116,   119,   132,
     223,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    61,   104,   105,   106,   251,   106,   251,   106,
      65,   106,   106,   246,   251,   106,    61,   106,    68,    68,
     144,   148,   148,   148,   148,   144,   147,   147,   226,    95,
     149,   173,   187,   188,   155,   130,   160,   130,   149,   171,
     173,   188,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,    52,    53,
      56,   169,   175,   284,   285,   177,    52,    53,    56,   169,
     175,   284,    52,    56,   284,   284,   231,   230,   149,   171,
     149,   171,    94,   151,   200,   292,   264,   199,    52,    56,
     162,   284,   177,   284,   141,   147,   132,   265,   266,   204,
     168,    10,     8,   234,   294,   142,    13,   171,    52,    56,
     177,    52,    56,   142,   232,   187,    10,    27,   208,   292,
     208,    52,    56,   177,    52,    56,   197,   173,    95,   173,
     185,   281,   282,   289,   133,   171,   173,   179,   183,   185,
     281,   289,   166,   192,   171,   142,   127,   171,   289,   289,
     281,   130,   159,    52,    56,   177,    52,    56,   109,    52,
      89,    95,   212,   213,   214,   268,   266,    29,   107,   224,
     135,   218,   294,   130,   277,   294,   130,   277,    52,   130,
     277,    52,   253,   252,   136,   251,   136,   171,   171,    76,
     114,   216,   217,   294,   173,   130,   289,   159,   130,    44,
     288,    87,    87,   175,   180,   288,   290,    87,    87,   175,
     176,   180,   294,   176,   180,   176,   180,   216,   216,   152,
     292,   148,   141,   290,    10,   289,   266,   141,   292,   164,
     166,   173,   188,   235,   294,    15,   210,   294,    14,   209,
     210,    87,   290,    87,    87,   210,    10,   130,   207,   194,
     196,   290,   148,   173,   186,   130,   184,   289,   186,   147,
     127,   291,   157,   290,   173,   214,   130,   268,   130,   289,
     218,   142,   142,    52,   219,   220,   267,   269,   272,   274,
     276,   270,   271,   274,   270,   142,    54,    55,    57,   254,
     262,   215,   218,   270,   274,   276,   142,    95,   173,   159,
     171,   111,   149,   171,   171,   151,   134,    87,   149,   171,
     149,   171,   151,   142,   142,   216,   201,   292,    10,   289,
      10,   205,    88,   236,   294,   142,     9,   237,   294,   148,
      10,    87,    10,   173,   142,   142,   142,   208,   185,   187,
     281,   289,   289,   289,   213,   130,    95,   212,   289,    10,
     127,   130,   130,   277,   130,   277,   130,   277,   130,   277,
     277,   127,   218,   114,   130,   277,   130,   277,    10,   173,
     171,   149,   171,    10,   127,   142,   141,   265,    86,   161,
     206,   259,   262,   207,   142,   207,   210,   232,   233,    10,
      10,   198,   130,   186,   186,   130,   213,   130,   268,   220,
     270,   274,   270,   270,   114,   274,   270,   127,    10,   141,
      56,    85,   128,   129,   142,   142,   142,   281,   213,   130,
     277,   130,   277,   277,   277,   130,   277,   277,    10,    52,
      56,   177,    52,    56,   234,   209,    10,   186,   213,   270,
     270,   290,   277,   277
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      parser_yyerror (parser, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, parser); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct parser_params *parser)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct parser_params *parser;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (parser);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct parser_params *parser)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct parser_params *parser;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, struct parser_params *parser)
#else
static void
yy_reduce_print (yyvsp, yyrule, parser)
    YYSTYPE *yyvsp;
    int yyrule;
    struct parser_params *parser;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , parser);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parser); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
#ifndef yydebug
int yydebug;
#endif
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, struct parser_params *parser)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parser)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    struct parser_params *parser;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parser);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (struct parser_params *parser);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (struct parser_params *parser)
#else
int
yyparse (parser)
    struct parser_params *parser;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 741 "ripper.y"
    {
			lex_state = EXPR_BEG;
#if 0
			local_push(compile_for_eval);
#endif

		    ;}
    break;

  case 3:
#line 749 "ripper.y"
    {
#if 0
			if ((yyvsp[(2) - (2)].val) && !compile_for_eval) {
			    /* last expression should not be void */
			    if (nd_type((yyvsp[(2) - (2)].val)) != NODE_BLOCK) void_expr((yyvsp[(2) - (2)].val));
			    else {
				NODE *node = (yyvsp[(2) - (2)].val);
				while (node->nd_next) {
				    node = node->nd_next;
				}
				void_expr(node->nd_head);
			    }
			}
			ruby_eval_tree = NEW_SCOPE(0, block_append(ruby_eval_tree, (yyvsp[(2) - (2)].val)));
			local_pop();
#endif
			(yyval.val) = (yyvsp[(2) - (2)].val);
			parser->result = dispatch1(program, (yyval.val));

		    ;}
    break;

  case 4:
#line 775 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (4)].val);
			if ((yyvsp[(2) - (4)].val)) {
			    (yyval.val) = NEW_RESCUE((yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val));
			}
			else if ((yyvsp[(3) - (4)].val)) {
			    rb_warn0("else without rescue is useless");
			    (yyval.val) = block_append((yyval.val), (yyvsp[(3) - (4)].val));
			}
			if ((yyvsp[(4) - (4)].val)) {
			    if ((yyval.val)) {
				(yyval.val) = NEW_ENSURE((yyval.val), (yyvsp[(4) - (4)].val));
			    }
			    else {
				(yyval.val) = block_append((yyvsp[(4) - (4)].val), NEW_NIL());
			    }
			}
			fixpos((yyval.val), (yyvsp[(1) - (4)].val));
#endif
			(yyval.val) = dispatch4(body_stmt,
				       escape_Qundef((yyvsp[(1) - (4)].val)),
				       escape_Qundef((yyvsp[(2) - (4)].val)),
				       escape_Qundef((yyvsp[(3) - (4)].val)),
				       escape_Qundef((yyvsp[(4) - (4)].val)));

		    ;}
    break;

  case 5:
#line 805 "ripper.y"
    {
#if 0
			void_stmts((yyvsp[(1) - (2)].val));
#endif

			(yyval.val) = (yyvsp[(1) - (2)].val);
		    ;}
    break;

  case 6:
#line 815 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch2(stmts_add, dispatch0(stmts_new),
						  dispatch0(void_stmt));

		    ;}
    break;

  case 7:
#line 824 "ripper.y"
    {
#if 0
			(yyval.val) = newline_node((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = dispatch2(stmts_add, dispatch0(stmts_new), (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 8:
#line 832 "ripper.y"
    {
#if 0
			(yyval.val) = block_append((yyvsp[(1) - (3)].val), newline_node((yyvsp[(3) - (3)].val)));
#endif
			(yyval.val) = dispatch2(stmts_add, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 9:
#line 840 "ripper.y"
    {
			(yyval.val) = remove_begin((yyvsp[(2) - (2)].val));
		    ;}
    break;

  case 10:
#line 845 "ripper.y"
    {lex_state = EXPR_FNAME;;}
    break;

  case 11:
#line 846 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ALIAS((yyvsp[(2) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = dispatch2(alias, (yyvsp[(2) - (4)].val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 12:
#line 854 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_VALIAS((yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(var_alias, (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 13:
#line 862 "ripper.y"
    {
#if 0
			char buf[3];

			sprintf(buf, "$%c", (char)(yyvsp[(3) - (3)].val)->nd_nth);
			(yyval.val) = NEW_VALIAS((yyvsp[(2) - (3)].val), rb_intern(buf));
#endif
			(yyval.val) = dispatch2(var_alias, (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 14:
#line 873 "ripper.y"
    {
#if 0
			yyerror("can't make alias for the number variables");
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch2(var_alias, (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
			(yyval.val) = dispatch1(alias_error, (yyval.val));

		    ;}
    break;

  case 15:
#line 883 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch1(undef, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 16:
#line 891 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_IF(cond((yyvsp[(3) - (3)].val)), remove_begin((yyvsp[(1) - (3)].val)), 0);
			fixpos((yyval.val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(if_mod, (yyvsp[(3) - (3)].val), (yyvsp[(1) - (3)].val));

		    ;}
    break;

  case 17:
#line 900 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_UNLESS(cond((yyvsp[(3) - (3)].val)), remove_begin((yyvsp[(1) - (3)].val)), 0);
			fixpos((yyval.val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(unless_mod, (yyvsp[(3) - (3)].val), (yyvsp[(1) - (3)].val));

		    ;}
    break;

  case 18:
#line 909 "ripper.y"
    {
#if 0
			if ((yyvsp[(1) - (3)].val) && nd_type((yyvsp[(1) - (3)].val)) == NODE_BEGIN) {
			    (yyval.val) = NEW_WHILE(cond((yyvsp[(3) - (3)].val)), (yyvsp[(1) - (3)].val)->nd_body, 0);
			}
			else {
			    (yyval.val) = NEW_WHILE(cond((yyvsp[(3) - (3)].val)), (yyvsp[(1) - (3)].val), 1);
			}
#endif
			(yyval.val) = dispatch2(while_mod, (yyvsp[(3) - (3)].val), (yyvsp[(1) - (3)].val));

		    ;}
    break;

  case 19:
#line 922 "ripper.y"
    {
#if 0
			if ((yyvsp[(1) - (3)].val) && nd_type((yyvsp[(1) - (3)].val)) == NODE_BEGIN) {
			    (yyval.val) = NEW_UNTIL(cond((yyvsp[(3) - (3)].val)), (yyvsp[(1) - (3)].val)->nd_body, 0);
			}
			else {
			    (yyval.val) = NEW_UNTIL(cond((yyvsp[(3) - (3)].val)), (yyvsp[(1) - (3)].val), 1);
			}
#endif
			(yyval.val) = dispatch2(until_mod, (yyvsp[(3) - (3)].val), (yyvsp[(1) - (3)].val));

		    ;}
    break;

  case 20:
#line 935 "ripper.y"
    {
#if 0
			NODE *resq = NEW_RESBODY(0, remove_begin((yyvsp[(3) - (3)].val)), 0);
			(yyval.val) = NEW_RESCUE(remove_begin((yyvsp[(1) - (3)].val)), resq, 0);
#endif
			(yyval.val) = dispatch2(rescue_mod, (yyvsp[(3) - (3)].val), (yyvsp[(1) - (3)].val));

		    ;}
    break;

  case 21:
#line 944 "ripper.y"
    {
			if (in_def || in_single) {
			    yyerror("BEGIN in method");
			}
#if 0
			/* local_push(0); */
#endif

		    ;}
    break;

  case 22:
#line 954 "ripper.y"
    {
#if 0
			ruby_eval_tree_begin = block_append(ruby_eval_tree_begin,
							    (yyvsp[(4) - (5)].val));
			/* NEW_PREEXE($4)); */
			/* local_pop(); */
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch1(BEGIN, (yyvsp[(4) - (5)].val));

		    ;}
    break;

  case 23:
#line 966 "ripper.y"
    {
			if (in_def || in_single) {
			    rb_warn0("END in method; use at_exit");
			}
#if 0
			(yyval.val) = NEW_POSTEXE(NEW_NODE(
			    NODE_SCOPE, 0 /* tbl */, (yyvsp[(3) - (4)].val) /* body */, 0 /* args */));
#endif
			(yyval.val) = dispatch1(END, (yyvsp[(3) - (4)].val));

		    ;}
    break;

  case 24:
#line 978 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (3)].val));
			(yyval.val) = node_assign((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(assign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 25:
#line 987 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (3)].val));
			(yyvsp[(1) - (3)].val)->nd_value = (yyvsp[(3) - (3)].val);
			(yyval.val) = (yyvsp[(1) - (3)].val);
#endif
			(yyval.val) = dispatch2(massign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 26:
#line 997 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (3)].val));
			if ((yyvsp[(1) - (3)].val)) {
			    ID vid = (yyvsp[(1) - (3)].val)->nd_vid;
			    if ((yyvsp[(2) - (3)].val) == tOROP) {
				(yyvsp[(1) - (3)].val)->nd_value = (yyvsp[(3) - (3)].val);
				(yyval.val) = NEW_OP_ASGN_OR(gettable(vid), (yyvsp[(1) - (3)].val));
				if (is_asgn_or_id(vid)) {
				    (yyval.val)->nd_aid = vid;
				}
			    }
			    else if ((yyvsp[(2) - (3)].val) == tANDOP) {
				(yyvsp[(1) - (3)].val)->nd_value = (yyvsp[(3) - (3)].val);
				(yyval.val) = NEW_OP_ASGN_AND(gettable(vid), (yyvsp[(1) - (3)].val));
			    }
			    else {
				(yyval.val) = (yyvsp[(1) - (3)].val);
				(yyval.val)->nd_value = NEW_CALL(gettable(vid), (yyvsp[(2) - (3)].val), NEW_LIST((yyvsp[(3) - (3)].val)));
			    }
			}
			else {
			    (yyval.val) = NEW_BEGIN(0);
			}
#endif
			(yyval.val) = dispatch3(opassign, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 27:
#line 1026 "ripper.y"
    {
#if 0
			NODE *args;

			value_expr((yyvsp[(6) - (6)].val));
			if (!(yyvsp[(3) - (6)].val)) (yyvsp[(3) - (6)].val) = NEW_ZARRAY();
			args = arg_concat((yyvsp[(6) - (6)].val), (yyvsp[(3) - (6)].val));
			if ((yyvsp[(5) - (6)].val) == tOROP) {
			    (yyvsp[(5) - (6)].val) = 0;
			}
			else if ((yyvsp[(5) - (6)].val) == tANDOP) {
			    (yyvsp[(5) - (6)].val) = 1;
			}
			(yyval.val) = NEW_OP_ASGN1((yyvsp[(1) - (6)].val), (yyvsp[(5) - (6)].val), args);
			fixpos((yyval.val), (yyvsp[(1) - (6)].val));
#endif
			(yyval.val) = dispatch2(aref_field, (yyvsp[(1) - (6)].val), escape_Qundef((yyvsp[(3) - (6)].val)));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));

		    ;}
    break;

  case 28:
#line 1047 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(5) - (5)].val));
			if ((yyvsp[(4) - (5)].val) == tOROP) {
			    (yyvsp[(4) - (5)].val) = 0;
			}
			else if ((yyvsp[(4) - (5)].val) == tANDOP) {
			    (yyvsp[(4) - (5)].val) = 1;
			}
			(yyval.val) = NEW_OP_ASGN2((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));

		    ;}
    break;

  case 29:
#line 1064 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(5) - (5)].val));
			if ((yyvsp[(4) - (5)].val) == tOROP) {
			    (yyvsp[(4) - (5)].val) = 0;
			}
			else if ((yyvsp[(4) - (5)].val) == tANDOP) {
			    (yyvsp[(4) - (5)].val) = 1;
			}
			(yyval.val) = NEW_OP_ASGN2((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));

		    ;}
    break;

  case 30:
#line 1081 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(5) - (5)].val));
			if ((yyvsp[(4) - (5)].val) == tOROP) {
			    (yyvsp[(4) - (5)].val) = 0;
			}
			else if ((yyvsp[(4) - (5)].val) == tANDOP) {
			    (yyvsp[(4) - (5)].val) = 1;
			}
			(yyval.val) = NEW_OP_ASGN2((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (5)].val), ripper_intern("::"), (yyvsp[(3) - (5)].val));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));

		    ;}
    break;

  case 31:
#line 1098 "ripper.y"
    {
#if 0
			rb_backref_error((yyvsp[(1) - (3)].val));
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch2(assign, dispatch1(var_field, (yyvsp[(1) - (3)].val)), (yyvsp[(3) - (3)].val));
			(yyval.val) = dispatch1(assign_error, (yyval.val));

		    ;}
    break;

  case 32:
#line 1108 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (3)].val));
			(yyval.val) = node_assign((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(assign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 33:
#line 1117 "ripper.y"
    {
#if 0
			(yyvsp[(1) - (3)].val)->nd_value = (yyvsp[(3) - (3)].val);
			(yyval.val) = (yyvsp[(1) - (3)].val);
#endif
			dispatch2(massign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 34:
#line 1126 "ripper.y"
    {
#if 0
			(yyvsp[(1) - (3)].val)->nd_value = (yyvsp[(3) - (3)].val);
			(yyval.val) = (yyvsp[(1) - (3)].val);
#endif
			(yyval.val) = dispatch2(massign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 37:
#line 1139 "ripper.y"
    {
#if 0
			(yyval.val) = logop(NODE_AND, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("and"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 38:
#line 1147 "ripper.y"
    {
#if 0
			(yyval.val) = logop(NODE_OR, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("or"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 39:
#line 1155 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op(cond((yyvsp[(2) - (2)].val)), '!');
#endif
			(yyval.val) = dispatch2(unary, ripper_intern("not"), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 40:
#line 1163 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op(cond((yyvsp[(2) - (2)].val)), '!');
#endif
			(yyval.val) = dispatch2(unary, ripper_id2sym('!'), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 42:
#line 1174 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (1)].val));
			(yyval.val) = (yyvsp[(1) - (1)].val);
		        if (!(yyval.val)) (yyval.val) = NEW_NIL();
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    ;}
    break;

  case 45:
#line 1188 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_RETURN(ret_args((yyvsp[(2) - (2)].val)));
#endif
			(yyval.val) = dispatch1(return, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 46:
#line 1196 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_BREAK(ret_args((yyvsp[(2) - (2)].val)));
#endif
			(yyval.val) = dispatch1(break, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 47:
#line 1204 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_NEXT(ret_args((yyvsp[(2) - (2)].val)));
#endif
			(yyval.val) = dispatch1(next, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 49:
#line 1215 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (4)].val), ripper_id2sym('.'), (yyvsp[(3) - (4)].val));
			(yyval.val) = method_arg((yyval.val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 50:
#line 1224 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (4)].val), ripper_intern("::"), (yyvsp[(3) - (4)].val));
			(yyval.val) = method_arg((yyval.val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 51:
#line 1235 "ripper.y"
    {
#if 0
			dyna_push();
			(yyval.num) = ruby_sourceline;
#endif

		    ;}
    break;

  case 52:
#line 1245 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ITER((yyvsp[(3) - (5)].val),(yyvsp[(4) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(2) - (5)].num));
			dyna_pop();
#endif
			(yyval.val) = dispatch2(brace_block, escape_Qundef((yyvsp[(3) - (5)].val)), (yyvsp[(4) - (5)].val));

		    ;}
    break;

  case 53:
#line 1257 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_FCALL((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
			fixpos((yyval.val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(command, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 54:
#line 1266 "ripper.y"
    {
#if 0
			block_dup_check((yyvsp[(2) - (3)].val),(yyvsp[(3) - (3)].val));
		        (yyvsp[(3) - (3)].val)->nd_iter = NEW_FCALL((yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));
			(yyval.val) = (yyvsp[(3) - (3)].val);
			fixpos((yyval.val), (yyvsp[(2) - (3)].val));
#endif
			(yyval.val) = dispatch2(command, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));
			(yyval.val) = method_add_block((yyval.val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 55:
#line 1278 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
			fixpos((yyval.val), (yyvsp[(1) - (4)].val));
#endif
			(yyval.val) = dispatch4(command_call, (yyvsp[(1) - (4)].val), ripper_id2sym('.'), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 56:
#line 1287 "ripper.y"
    {
#if 0
			block_dup_check((yyvsp[(4) - (5)].val),(yyvsp[(5) - (5)].val));
		        (yyvsp[(5) - (5)].val)->nd_iter = NEW_CALL((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = (yyvsp[(5) - (5)].val);
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyval.val) = dispatch4(command_call, (yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = method_add_block((yyval.val), (yyvsp[(5) - (5)].val));

		   ;}
    break;

  case 57:
#line 1299 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
			fixpos((yyval.val), (yyvsp[(1) - (4)].val));
#endif
			(yyval.val) = dispatch4(command_call, (yyvsp[(1) - (4)].val), ripper_intern("::"), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 58:
#line 1308 "ripper.y"
    {
#if 0
			block_dup_check((yyvsp[(4) - (5)].val),(yyvsp[(5) - (5)].val));
		        (yyvsp[(5) - (5)].val)->nd_iter = NEW_CALL((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = (yyvsp[(5) - (5)].val);
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyval.val) = dispatch4(command_call, (yyvsp[(1) - (5)].val), ripper_intern("::"), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = method_add_block((yyval.val), (yyvsp[(5) - (5)].val));

		   ;}
    break;

  case 59:
#line 1320 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_SUPER((yyvsp[(2) - (2)].val));
			fixpos((yyval.val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch1(super, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 60:
#line 1329 "ripper.y"
    {
#if 0
			(yyval.val) = new_yield((yyvsp[(2) - (2)].val));
			fixpos((yyval.val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch1(yield, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 62:
#line 1341 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 64:
#line 1352 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(NEW_LIST((yyvsp[(2) - (3)].val)), 0);
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 65:
#line 1362 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (1)].val), 0);
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    ;}
    break;

  case 66:
#line 1370 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(list_append((yyvsp[(1) - (2)].val),(yyvsp[(2) - (2)].val)), 0);
#endif
			(yyval.val) = mlhs_add((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 67:
#line 1378 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 68:
#line 1386 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (5)].val), NEW_POSTARG((yyvsp[(3) - (5)].val),(yyvsp[(5) - (5)].val)));
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val));

		    ;}
    break;

  case 69:
#line 1394 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (2)].val), -1);
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (2)].val), Qnil);

		    ;}
    break;

  case 70:
#line 1402 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (4)].val), NEW_POSTARG(-1, (yyvsp[(4) - (4)].val)));
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (4)].val), Qnil);

		    ;}
    break;

  case 71:
#line 1410 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 72:
#line 1418 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, NEW_POSTARG((yyvsp[(2) - (4)].val),(yyvsp[(4) - (4)].val)));
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), (yyvsp[(2) - (4)].val));

		    ;}
    break;

  case 73:
#line 1426 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, -1);
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), Qnil);

		    ;}
    break;

  case 74:
#line 1434 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, NEW_POSTARG(-1, (yyvsp[(3) - (3)].val)));
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), Qnil);

		    ;}
    break;

  case 76:
#line 1445 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 77:
#line 1455 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST((yyvsp[(1) - (2)].val));
#endif
			(yyval.val) = mlhs_add(mlhs_new(), (yyvsp[(1) - (2)].val));

		    ;}
    break;

  case 78:
#line 1463 "ripper.y"
    {
#if 0
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));
#endif
			(yyval.val) = mlhs_add((yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 79:
#line 1473 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = mlhs_add(mlhs_new(), (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 80:
#line 1481 "ripper.y"
    {
#if 0
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = mlhs_add((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 81:
#line 1491 "ripper.y"
    {
#if 0
			(yyval.val) = assignable((yyvsp[(1) - (1)].val), 0);
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    ;}
    break;

  case 82:
#line 1499 "ripper.y"
    {
#if 0
			(yyval.val) = aryset((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val));
#endif
			(yyval.val) = dispatch2(aref_field, (yyvsp[(1) - (4)].val), escape_Qundef((yyvsp[(3) - (4)].val)));

		    ;}
    break;

  case 83:
#line 1507 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (3)].val), ripper_id2sym('.'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 84:
#line 1515 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(const_path_field, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 85:
#line 1523 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (3)].val), ripper_id2sym('.'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 86:
#line 1531 "ripper.y"
    {
#if 0
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.val) = NEW_CDECL(0, 0, NEW_COLON2((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val)));
#endif
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.val) = dispatch2(const_path_field, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 87:
#line 1543 "ripper.y"
    {
#if 0
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.val) = NEW_CDECL(0, 0, NEW_COLON3((yyvsp[(2) - (2)].val)));
#endif
			(yyval.val) = dispatch1(top_const_field, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 88:
#line 1553 "ripper.y"
    {
#if 0
			rb_backref_error((yyvsp[(1) - (1)].val));
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(var_field, (yyvsp[(1) - (1)].val));
			(yyval.val) = dispatch1(assign_error, (yyval.val));

		    ;}
    break;

  case 89:
#line 1565 "ripper.y"
    {
#if 0
			if (!((yyval.val) = assignable((yyvsp[(1) - (1)].val), 0))) (yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(var_field, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 90:
#line 1573 "ripper.y"
    {
#if 0
			(yyval.val) = aryset((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val));
#endif
			(yyval.val) = dispatch2(aref_field, (yyvsp[(1) - (4)].val), escape_Qundef((yyvsp[(3) - (4)].val)));

		    ;}
    break;

  case 91:
#line 1581 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (3)].val), ripper_id2sym('.'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 92:
#line 1589 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (3)].val), ripper_intern("::"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 93:
#line 1597 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (3)].val), ripper_id2sym('.'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 94:
#line 1605 "ripper.y"
    {
#if 0
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.val) = NEW_CDECL(0, 0, NEW_COLON2((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val)));
#endif
			(yyval.val) = dispatch2(const_path_field, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
			if (in_def || in_single) {
			    (yyval.val) = dispatch1(assign_error, (yyval.val));
			}

		    ;}
    break;

  case 95:
#line 1618 "ripper.y"
    {
#if 0
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.val) = NEW_CDECL(0, 0, NEW_COLON3((yyvsp[(2) - (2)].val)));
#endif
			(yyval.val) = dispatch1(top_const_field, (yyvsp[(2) - (2)].val));
			if (in_def || in_single) {
			    (yyval.val) = dispatch1(assign_error, (yyval.val));
			}

		    ;}
    break;

  case 96:
#line 1631 "ripper.y"
    {
#if 0
			rb_backref_error((yyvsp[(1) - (1)].val));
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(assign_error, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 97:
#line 1642 "ripper.y"
    {
#if 0
			yyerror("class/module name must be CONSTANT");
#endif
			(yyval.val) = dispatch1(class_name_error, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 99:
#line 1653 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON3((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch1(top_const_ref, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 100:
#line 1661 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON2(0, (yyval.val));
#endif
			(yyval.val) = dispatch1(const_ref, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 101:
#line 1669 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON2((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(const_path_ref, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 105:
#line 1682 "ripper.y"
    {
#if 0
			lex_state = EXPR_END;
			(yyval.val) = (yyvsp[(1) - (1)].val);
#endif
			lex_state = EXPR_END;
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    ;}
    break;

  case 106:
#line 1692 "ripper.y"
    {
#if 0
			lex_state = EXPR_END;
			(yyval.val) = (yyvsp[(1) - (1)].id);
#endif
			lex_state = EXPR_END;
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    ;}
    break;

  case 109:
#line 1708 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIT(ID2SYM((yyvsp[(1) - (1)].val)));
#endif
			(yyval.val) = dispatch1(symbol_literal, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 111:
#line 1719 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_UNDEF((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 112:
#line 1726 "ripper.y"
    {lex_state = EXPR_FNAME;;}
    break;

  case 113:
#line 1727 "ripper.y"
    {
#if 0
			(yyval.val) = block_append((yyvsp[(1) - (4)].val), NEW_UNDEF((yyvsp[(4) - (4)].val)));
#endif
			rb_ary_push((yyvsp[(1) - (4)].val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 114:
#line 1736 "ripper.y"
    { ifndef_ripper((yyval.val) = '|'); ;}
    break;

  case 115:
#line 1737 "ripper.y"
    { ifndef_ripper((yyval.val) = '^'); ;}
    break;

  case 116:
#line 1738 "ripper.y"
    { ifndef_ripper((yyval.val) = '&'); ;}
    break;

  case 117:
#line 1739 "ripper.y"
    { ifndef_ripper((yyval.val) = tCMP); ;}
    break;

  case 118:
#line 1740 "ripper.y"
    { ifndef_ripper((yyval.val) = tEQ); ;}
    break;

  case 119:
#line 1741 "ripper.y"
    { ifndef_ripper((yyval.val) = tEQQ); ;}
    break;

  case 120:
#line 1742 "ripper.y"
    { ifndef_ripper((yyval.val) = tMATCH); ;}
    break;

  case 121:
#line 1743 "ripper.y"
    { ifndef_ripper((yyval.val) = tNMATCH); ;}
    break;

  case 122:
#line 1744 "ripper.y"
    { ifndef_ripper((yyval.val) = '>'); ;}
    break;

  case 123:
#line 1745 "ripper.y"
    { ifndef_ripper((yyval.val) = tGEQ); ;}
    break;

  case 124:
#line 1746 "ripper.y"
    { ifndef_ripper((yyval.val) = '<'); ;}
    break;

  case 125:
#line 1747 "ripper.y"
    { ifndef_ripper((yyval.val) = tLEQ); ;}
    break;

  case 126:
#line 1748 "ripper.y"
    { ifndef_ripper((yyval.val) = tNEQ); ;}
    break;

  case 127:
#line 1749 "ripper.y"
    { ifndef_ripper((yyval.val) = tLSHFT); ;}
    break;

  case 128:
#line 1750 "ripper.y"
    { ifndef_ripper((yyval.val) = tRSHFT); ;}
    break;

  case 129:
#line 1751 "ripper.y"
    { ifndef_ripper((yyval.val) = '+'); ;}
    break;

  case 130:
#line 1752 "ripper.y"
    { ifndef_ripper((yyval.val) = '-'); ;}
    break;

  case 131:
#line 1753 "ripper.y"
    { ifndef_ripper((yyval.val) = '*'); ;}
    break;

  case 132:
#line 1754 "ripper.y"
    { ifndef_ripper((yyval.val) = '*'); ;}
    break;

  case 133:
#line 1755 "ripper.y"
    { ifndef_ripper((yyval.val) = '/'); ;}
    break;

  case 134:
#line 1756 "ripper.y"
    { ifndef_ripper((yyval.val) = '%'); ;}
    break;

  case 135:
#line 1757 "ripper.y"
    { ifndef_ripper((yyval.val) = tPOW); ;}
    break;

  case 136:
#line 1758 "ripper.y"
    { ifndef_ripper((yyval.val) = '!'); ;}
    break;

  case 137:
#line 1759 "ripper.y"
    { ifndef_ripper((yyval.val) = '~'); ;}
    break;

  case 138:
#line 1760 "ripper.y"
    { ifndef_ripper((yyval.val) = tUPLUS); ;}
    break;

  case 139:
#line 1761 "ripper.y"
    { ifndef_ripper((yyval.val) = tUMINUS); ;}
    break;

  case 140:
#line 1762 "ripper.y"
    { ifndef_ripper((yyval.val) = tAREF); ;}
    break;

  case 141:
#line 1763 "ripper.y"
    { ifndef_ripper((yyval.val) = tASET); ;}
    break;

  case 142:
#line 1764 "ripper.y"
    { ifndef_ripper((yyval.val) = '`'); ;}
    break;

  case 184:
#line 1782 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (3)].val));
			(yyval.val) = node_assign((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(assign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 185:
#line 1791 "ripper.y"
    {
#if 0
			(yyval.val) = node_assign((yyvsp[(1) - (5)].val), NEW_RESCUE((yyvsp[(3) - (5)].val), NEW_RESBODY(0,(yyvsp[(5) - (5)].val),0), 0));
#endif
			(yyval.val) = dispatch2(assign, (yyvsp[(1) - (5)].val), dispatch2(rescue_mod,(yyvsp[(3) - (5)].val),(yyvsp[(5) - (5)].val)));

		    ;}
    break;

  case 186:
#line 1799 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (3)].val));
			if ((yyvsp[(1) - (3)].val)) {
			    ID vid = (yyvsp[(1) - (3)].val)->nd_vid;
			    if ((yyvsp[(2) - (3)].val) == tOROP) {
				(yyvsp[(1) - (3)].val)->nd_value = (yyvsp[(3) - (3)].val);
				(yyval.val) = NEW_OP_ASGN_OR(gettable(vid), (yyvsp[(1) - (3)].val));
				if (is_asgn_or_id(vid)) {
				    (yyval.val)->nd_aid = vid;
				}
			    }
			    else if ((yyvsp[(2) - (3)].val) == tANDOP) {
				(yyvsp[(1) - (3)].val)->nd_value = (yyvsp[(3) - (3)].val);
				(yyval.val) = NEW_OP_ASGN_AND(gettable(vid), (yyvsp[(1) - (3)].val));
			    }
			    else {
				(yyval.val) = (yyvsp[(1) - (3)].val);
				(yyval.val)->nd_value = NEW_CALL(gettable(vid), (yyvsp[(2) - (3)].val), NEW_LIST((yyvsp[(3) - (3)].val)));
			    }
			}
			else {
			    (yyval.val) = NEW_BEGIN(0);
			}
#endif
			(yyval.val) = dispatch3(opassign, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 187:
#line 1828 "ripper.y"
    {
#if 0
			NODE *args;

			value_expr((yyvsp[(6) - (6)].val));
			if (!(yyvsp[(3) - (6)].val)) (yyvsp[(3) - (6)].val) = NEW_ZARRAY();
			args = arg_concat((yyvsp[(6) - (6)].val), (yyvsp[(3) - (6)].val));
			if ((yyvsp[(5) - (6)].val) == tOROP) {
			    (yyvsp[(5) - (6)].val) = 0;
			}
			else if ((yyvsp[(5) - (6)].val) == tANDOP) {
			    (yyvsp[(5) - (6)].val) = 1;
			}
			(yyval.val) = NEW_OP_ASGN1((yyvsp[(1) - (6)].val), (yyvsp[(5) - (6)].val), args);
			fixpos((yyval.val), (yyvsp[(1) - (6)].val));
#endif
			(yyvsp[(1) - (6)].val) = dispatch2(aref_field, (yyvsp[(1) - (6)].val), escape_Qundef((yyvsp[(3) - (6)].val)));
			(yyval.val) = dispatch3(opassign, (yyvsp[(1) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));

		    ;}
    break;

  case 188:
#line 1849 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(5) - (5)].val));
			if ((yyvsp[(4) - (5)].val) == tOROP) {
			    (yyvsp[(4) - (5)].val) = 0;
			}
			else if ((yyvsp[(4) - (5)].val) == tANDOP) {
			    (yyvsp[(4) - (5)].val) = 1;
			}
			(yyval.val) = NEW_OP_ASGN2((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyvsp[(1) - (5)].val) = dispatch3(field, (yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val));
			(yyval.val) = dispatch3(opassign, (yyvsp[(1) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));

		    ;}
    break;

  case 189:
#line 1866 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(5) - (5)].val));
			if ((yyvsp[(4) - (5)].val) == tOROP) {
			    (yyvsp[(4) - (5)].val) = 0;
			}
			else if ((yyvsp[(4) - (5)].val) == tANDOP) {
			    (yyvsp[(4) - (5)].val) = 1;
			}
			(yyval.val) = NEW_OP_ASGN2((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyvsp[(1) - (5)].val) = dispatch3(field, (yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val));
			(yyval.val) = dispatch3(opassign, (yyvsp[(1) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));

		    ;}
    break;

  case 190:
#line 1883 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(5) - (5)].val));
			if ((yyvsp[(4) - (5)].val) == tOROP) {
			    (yyvsp[(4) - (5)].val) = 0;
			}
			else if ((yyvsp[(4) - (5)].val) == tANDOP) {
			    (yyvsp[(4) - (5)].val) = 1;
			}
			(yyval.val) = NEW_OP_ASGN2((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyvsp[(1) - (5)].val) = dispatch3(field, (yyvsp[(1) - (5)].val), ripper_intern("::"), (yyvsp[(3) - (5)].val));
			(yyval.val) = dispatch3(opassign, (yyvsp[(1) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));

		    ;}
    break;

  case 191:
#line 1900 "ripper.y"
    {
#if 0
			yyerror("constant re-assignment");
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch2(const_path_field, (yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
			(yyval.val) = dispatch1(assign_error, (yyval.val));

		    ;}
    break;

  case 192:
#line 1911 "ripper.y"
    {
#if 0
			yyerror("constant re-assignment");
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(top_const_field, (yyvsp[(2) - (4)].val));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
			(yyval.val) = dispatch1(assign_error, (yyval.val));

		    ;}
    break;

  case 193:
#line 1922 "ripper.y"
    {
#if 0
			rb_backref_error((yyvsp[(1) - (3)].val));
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(var_field, (yyvsp[(1) - (3)].val));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
			(yyval.val) = dispatch1(assign_error, (yyval.val));

		    ;}
    break;

  case 194:
#line 1933 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (3)].val));
			value_expr((yyvsp[(3) - (3)].val));
			if (nd_type((yyvsp[(1) - (3)].val)) == NODE_LIT && FIXNUM_P((yyvsp[(1) - (3)].val)->nd_lit) &&
			    nd_type((yyvsp[(3) - (3)].val)) == NODE_LIT && FIXNUM_P((yyvsp[(3) - (3)].val)->nd_lit)) {
			    (yyvsp[(1) - (3)].val)->nd_lit = rb_range_new((yyvsp[(1) - (3)].val)->nd_lit, (yyvsp[(3) - (3)].val)->nd_lit, Qfalse);
			    (yyval.val) = (yyvsp[(1) - (3)].val);
			}
			else {
			    (yyval.val) = NEW_DOT2((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
			}
#endif
			(yyval.val) = dispatch2(dot2, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 195:
#line 1950 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (3)].val));
			value_expr((yyvsp[(3) - (3)].val));
			if (nd_type((yyvsp[(1) - (3)].val)) == NODE_LIT && FIXNUM_P((yyvsp[(1) - (3)].val)->nd_lit) &&
			    nd_type((yyvsp[(3) - (3)].val)) == NODE_LIT && FIXNUM_P((yyvsp[(3) - (3)].val)->nd_lit)) {
			    (yyvsp[(1) - (3)].val)->nd_lit = rb_range_new((yyvsp[(1) - (3)].val)->nd_lit, (yyvsp[(3) - (3)].val)->nd_lit, Qtrue);
			    (yyval.val) = (yyvsp[(1) - (3)].val);
			}
			else {
			    (yyval.val) = NEW_DOT3((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
			}
#endif
			(yyval.val) = dispatch2(dot3, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 196:
#line 1967 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '+', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('+'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 197:
#line 1975 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '-', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('-'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 198:
#line 1983 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '*', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('*'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 199:
#line 1991 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '/', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('/'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 200:
#line 1999 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '%', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('%'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 201:
#line 2007 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tPOW, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("**"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 202:
#line 2015 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL(call_bin_op((yyvsp[(2) - (4)].val), tPOW, (yyvsp[(4) - (4)].val)), tUMINUS, 0);
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(2) - (4)].val), ripper_intern("**"), (yyvsp[(4) - (4)].val));
			(yyval.val) = dispatch2(unary, ripper_intern("-@"), (yyval.val));

		    ;}
    break;

  case 203:
#line 2024 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL(call_bin_op((yyvsp[(2) - (4)].val), tPOW, (yyvsp[(4) - (4)].val)), tUMINUS, 0);
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(2) - (4)].val), ripper_intern("**"), (yyvsp[(4) - (4)].val));
			(yyval.val) = dispatch2(unary, ripper_intern("-@"), (yyval.val));

		    ;}
    break;

  case 204:
#line 2033 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op((yyvsp[(2) - (2)].val), tUPLUS);
#endif
			(yyval.val) = dispatch2(unary, ripper_intern("+@"), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 205:
#line 2041 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op((yyvsp[(2) - (2)].val), tUMINUS);
#endif
			(yyval.val) = dispatch2(unary, ripper_intern("-@"), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 206:
#line 2049 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '|', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('|'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 207:
#line 2057 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '^', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('^'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 208:
#line 2065 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '&', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('&'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 209:
#line 2073 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tCMP, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("<=>"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 210:
#line 2081 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '>', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('>'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 211:
#line 2089 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tGEQ, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern(">="), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 212:
#line 2097 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '<', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('<'), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 213:
#line 2105 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tLEQ, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("<="), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 214:
#line 2113 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tEQ, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("=="), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 215:
#line 2121 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tEQQ, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("==="), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 216:
#line 2129 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tNEQ, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("!="), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 217:
#line 2137 "ripper.y"
    {
#if 0
			(yyval.val) = match_op((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
                        if (nd_type((yyvsp[(1) - (3)].val)) == NODE_LIT && TYPE((yyvsp[(1) - (3)].val)->nd_lit) == T_REGEXP) {
                            (yyval.val) = reg_named_capture_assign((yyvsp[(1) - (3)].val)->nd_lit, (yyval.val));
                        }
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("=~"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 218:
#line 2148 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tNMATCH, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("!~"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 219:
#line 2156 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op(cond((yyvsp[(2) - (2)].val)), '!');
#endif
			(yyval.val) = dispatch2(unary, ID2SYM('!'), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 220:
#line 2164 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op((yyvsp[(2) - (2)].val), '~');
#endif
			(yyval.val) = dispatch2(unary, ID2SYM('~'), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 221:
#line 2172 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tLSHFT, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("<<"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 222:
#line 2180 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tRSHFT, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern(">>"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 223:
#line 2188 "ripper.y"
    {
#if 0
			(yyval.val) = logop(NODE_AND, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("&&"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 224:
#line 2196 "ripper.y"
    {
#if 0
			(yyval.val) = logop(NODE_OR, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("||"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 225:
#line 2203 "ripper.y"
    {in_defined = 1;;}
    break;

  case 226:
#line 2204 "ripper.y"
    {
#if 0
			in_defined = 0;
			(yyval.val) = NEW_DEFINED((yyvsp[(4) - (4)].val));
#endif
			in_defined = 0;
			(yyval.val) = dispatch1(defined, (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 227:
#line 2214 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (6)].val));
			(yyval.val) = NEW_IF(cond((yyvsp[(1) - (6)].val)), (yyvsp[(3) - (6)].val), (yyvsp[(6) - (6)].val));
			fixpos((yyval.val), (yyvsp[(1) - (6)].val));
#endif
			(yyval.val) = dispatch3(ifop, (yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(6) - (6)].val));

		    ;}
    break;

  case 228:
#line 2224 "ripper.y"
    {
			(yyval.val) = (yyvsp[(1) - (1)].val);
		    ;}
    break;

  case 229:
#line 2230 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (1)].val));
			(yyval.val) = (yyvsp[(1) - (1)].val);
		        if (!(yyval.val)) (yyval.val) = NEW_NIL();
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    ;}
    break;

  case 231:
#line 2243 "ripper.y"
    {
			(yyval.val) = (yyvsp[(1) - (2)].val);
		    ;}
    break;

  case 232:
#line 2247 "ripper.y"
    {
#if 0
			(yyval.val) = arg_append((yyvsp[(1) - (4)].val), NEW_HASH((yyvsp[(3) - (4)].val)));
#endif
			(yyval.val) = arg_add_assocs((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val));

		    ;}
    break;

  case 233:
#line 2255 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST(NEW_HASH((yyvsp[(1) - (2)].val)));
#endif
			(yyval.val) = arg_add_assocs(arg_new(), (yyvsp[(1) - (2)].val));

		    ;}
    break;

  case 234:
#line 2265 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(arg_paren, escape_Qundef((yyvsp[(2) - (3)].val)));

		    ;}
    break;

  case 239:
#line 2283 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = arg_add(arg_new(), (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 240:
#line 2291 "ripper.y"
    {
#if 0
			(yyval.val) = arg_blk_pass((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = arg_add_optblock((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 241:
#line 2299 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST(NEW_HASH((yyvsp[(1) - (2)].val)));
			(yyval.val) = arg_blk_pass((yyval.val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = arg_add_assocs(arg_new(), (yyvsp[(1) - (2)].val));
			(yyval.val) = arg_add_optblock((yyval.val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 242:
#line 2309 "ripper.y"
    {
#if 0
			(yyval.val) = arg_append((yyvsp[(1) - (4)].val), NEW_HASH((yyvsp[(3) - (4)].val)));
			(yyval.val) = arg_blk_pass((yyval.val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = arg_add_optblock(arg_add_assocs((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val)), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 243:
#line 2320 "ripper.y"
    {
			(yyval.val) = arg_add_block(arg_new(), (yyvsp[(1) - (1)].val));
		    ;}
    break;

  case 244:
#line 2327 "ripper.y"
    {
#if 0
			(yyval.val) = arg_blk_pass(list_concat(NEW_LIST((yyvsp[(1) - (4)].val)),(yyvsp[(3) - (4)].val)), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = arg_add_optblock(arg_prepend((yyvsp[(3) - (4)].val), (yyvsp[(1) - (4)].val)), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 245:
#line 2335 "ripper.y"
    {
#if 0
			(yyval.val) = arg_blk_pass(NEW_LIST((yyvsp[(1) - (3)].val)), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = arg_add_block(arg_add(arg_new(), (yyvsp[(1) - (3)].val)), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 246:
#line 2343 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST(NEW_HASH((yyvsp[(1) - (2)].val)));
			(yyval.val) = arg_blk_pass((yyval.val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = arg_add_assocs(arg_new(), (yyvsp[(1) - (2)].val));
			(yyval.val) = arg_add_optblock((yyval.val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 247:
#line 2353 "ripper.y"
    {
#if 0
			(yyval.val) = arg_append(NEW_LIST((yyvsp[(1) - (4)].val)), NEW_HASH((yyvsp[(3) - (4)].val)));
			(yyval.val) = arg_blk_pass((yyval.val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = arg_add_assocs(arg_add(arg_new(), (yyvsp[(1) - (4)].val)), (yyvsp[(3) - (4)].val));
			(yyval.val) = arg_add_optblock((yyval.val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 248:
#line 2363 "ripper.y"
    {
#if 0
			(yyval.val) = arg_append(list_concat(NEW_LIST((yyvsp[(1) - (6)].val)),(yyvsp[(3) - (6)].val)), NEW_HASH((yyvsp[(5) - (6)].val)));
			(yyval.val) = arg_blk_pass((yyval.val), (yyvsp[(6) - (6)].val));
#endif
			(yyval.val) = arg_add_assocs(arg_prepend((yyvsp[(3) - (6)].val), (yyvsp[(1) - (6)].val)), (yyvsp[(5) - (6)].val));
			(yyval.val) = arg_add_optblock((yyval.val), (yyvsp[(6) - (6)].val));

		    ;}
    break;

  case 250:
#line 2375 "ripper.y"
    {
			(yyval.num) = cmdarg_stack;
			CMDARG_PUSH(1);
		    ;}
    break;

  case 251:
#line 2380 "ripper.y"
    {
			/* CMDARG_POP() */
			cmdarg_stack = (yyvsp[(1) - (2)].num);
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    ;}
    break;

  case 253:
#line 2388 "ripper.y"
    {lex_state = EXPR_ENDARG;;}
    break;

  case 254:
#line 2389 "ripper.y"
    {
#if 0
			rb_warning0("don't put space before argument parentheses");
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch1(space, dispatch1(arg_paren, arg_new()));

		    ;}
    break;

  case 255:
#line 2397 "ripper.y"
    {lex_state = EXPR_ENDARG;;}
    break;

  case 256:
#line 2398 "ripper.y"
    {
#if 0
			rb_warning0("don't put space before argument parentheses");
			(yyval.val) = (yyvsp[(2) - (4)].val);
#endif
			(yyval.val) = dispatch1(space, dispatch1(arg_paren, (yyvsp[(2) - (4)].val)));

		    ;}
    break;

  case 257:
#line 2409 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_BLOCK_PASS((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = (yyvsp[(2) - (2)].val);

		    ;}
    break;

  case 258:
#line 2419 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    ;}
    break;

  case 259:
#line 2423 "ripper.y"
    {
			(yyval.val) = 0;
		    ;}
    break;

  case 260:
#line 2429 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = arg_add(arg_new(), (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 261:
#line 2437 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_SPLAT((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = arg_add_star(arg_new(), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 262:
#line 2445 "ripper.y"
    {
#if 0
			(yyval.val) = arg_append((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = arg_add((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 263:
#line 2453 "ripper.y"
    {
#if 0
			(yyval.val) = arg_concat((yyvsp[(1) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = arg_add_star((yyvsp[(1) - (4)].val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 264:
#line 2463 "ripper.y"
    {
#if 0
			(yyval.val) = arg_append((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = mrhs_add(args2mrhs((yyvsp[(1) - (3)].val)), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 265:
#line 2471 "ripper.y"
    {
#if 0
			(yyval.val) = arg_concat((yyvsp[(1) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = mrhs_add_star(args2mrhs((yyvsp[(1) - (4)].val)), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 266:
#line 2479 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_SPLAT((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = mrhs_add_star(mrhs_new(), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 275:
#line 2497 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_FCALL((yyvsp[(1) - (1)].val), 0);
#endif
			(yyval.val) = method_arg(dispatch1(fcall, (yyvsp[(1) - (1)].val)), arg_new());

		    ;}
    break;

  case 276:
#line 2505 "ripper.y"
    {
#if 0
			(yyval.num) = ruby_sourceline;
#endif

		    ;}
    break;

  case 277:
#line 2513 "ripper.y"
    {
#if 0
			if ((yyvsp[(3) - (4)].val) == NULL) {
			    (yyval.val) = NEW_NIL();
			}
			else {
			    if (nd_type((yyvsp[(3) - (4)].val)) == NODE_RESCUE ||
				nd_type((yyvsp[(3) - (4)].val)) == NODE_ENSURE)
				nd_set_line((yyvsp[(3) - (4)].val), (yyvsp[(2) - (4)].num));
			    (yyval.val) = NEW_BEGIN((yyvsp[(3) - (4)].val));
			}
			nd_set_line((yyval.val), (yyvsp[(2) - (4)].num));
#endif
			(yyval.val) = dispatch1(begin, (yyvsp[(3) - (4)].val));

		    ;}
    break;

  case 278:
#line 2529 "ripper.y"
    {lex_state = EXPR_ENDARG;;}
    break;

  case 279:
#line 2530 "ripper.y"
    {
			rb_warning0("(...) interpreted as grouped expression");
#if 0
			(yyval.val) = (yyvsp[(2) - (4)].val);
#endif
			(yyval.val) = dispatch1(paren, (yyvsp[(2) - (4)].val));

		    ;}
    break;

  case 280:
#line 2539 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(paren, (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 281:
#line 2547 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON2((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(const_path_ref, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 282:
#line 2555 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON3((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch1(top_const_ref, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 283:
#line 2563 "ripper.y"
    {
#if 0
			if ((yyvsp[(2) - (3)].val) == 0) {
			    (yyval.val) = NEW_ZARRAY(); /* zero length array*/
			}
			else {
			    (yyval.val) = (yyvsp[(2) - (3)].val);
			}
#endif
			(yyval.val) = dispatch1(array, escape_Qundef((yyvsp[(2) - (3)].val)));

		    ;}
    break;

  case 284:
#line 2576 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_HASH((yyvsp[(2) - (3)].val));
#endif
			(yyval.val) = dispatch1(hash, escape_Qundef((yyvsp[(2) - (3)].val)));

		    ;}
    break;

  case 285:
#line 2584 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_RETURN(0);
#endif
			(yyval.val) = dispatch0(return0);

		    ;}
    break;

  case 286:
#line 2592 "ripper.y"
    {
#if 0
			(yyval.val) = new_yield((yyvsp[(3) - (4)].val));
#endif
			(yyval.val) = dispatch1(yield, dispatch1(paren, (yyvsp[(3) - (4)].val)));

		    ;}
    break;

  case 287:
#line 2600 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_YIELD(0, Qfalse);
#endif
			(yyval.val) = dispatch1(yield, dispatch1(paren, arg_new()));

		    ;}
    break;

  case 288:
#line 2608 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_YIELD(0, Qfalse);
#endif
			(yyval.val) = dispatch0(yield0);

		    ;}
    break;

  case 289:
#line 2615 "ripper.y"
    {in_defined = 1;;}
    break;

  case 290:
#line 2616 "ripper.y"
    {
#if 0
			in_defined = 0;
			(yyval.val) = NEW_DEFINED((yyvsp[(5) - (6)].val));
#endif
			in_defined = 0;
			(yyval.val) = dispatch1(defined, (yyvsp[(5) - (6)].val));

		    ;}
    break;

  case 291:
#line 2626 "ripper.y"
    {
#if 0
			(yyvsp[(2) - (2)].val)->nd_iter = NEW_FCALL((yyvsp[(1) - (2)].val), 0);
			(yyval.val) = (yyvsp[(2) - (2)].val);
			fixpos((yyvsp[(2) - (2)].val)->nd_iter, (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = method_arg(dispatch1(fcall, (yyvsp[(1) - (2)].val)), arg_new());
			(yyval.val) = method_add_block((yyval.val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 293:
#line 2638 "ripper.y"
    {
#if 0
			block_dup_check((yyvsp[(1) - (2)].val)->nd_args, (yyvsp[(2) - (2)].val));
			(yyvsp[(2) - (2)].val)->nd_iter = (yyvsp[(1) - (2)].val);
			(yyval.val) = (yyvsp[(2) - (2)].val);
			fixpos((yyval.val), (yyvsp[(1) - (2)].val));
#endif
			(yyval.val) = method_add_block((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 294:
#line 2649 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    ;}
    break;

  case 295:
#line 2656 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_IF(cond((yyvsp[(2) - (6)].val)), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val));
			fixpos((yyval.val), (yyvsp[(2) - (6)].val));
#endif
			(yyval.val) = dispatch3(if, (yyvsp[(2) - (6)].val), (yyvsp[(4) - (6)].val), escape_Qundef((yyvsp[(5) - (6)].val)));

		    ;}
    break;

  case 296:
#line 2668 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_UNLESS(cond((yyvsp[(2) - (6)].val)), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val));
			fixpos((yyval.val), (yyvsp[(2) - (6)].val));
#endif
			(yyval.val) = dispatch3(unless, (yyvsp[(2) - (6)].val), (yyvsp[(4) - (6)].val), escape_Qundef((yyvsp[(5) - (6)].val)));

		    ;}
    break;

  case 297:
#line 2676 "ripper.y"
    {COND_PUSH(1);;}
    break;

  case 298:
#line 2676 "ripper.y"
    {COND_POP();;}
    break;

  case 299:
#line 2679 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_WHILE(cond((yyvsp[(3) - (7)].val)), (yyvsp[(6) - (7)].val), 1);
			fixpos((yyval.val), (yyvsp[(3) - (7)].val));
#endif
			(yyval.val) = dispatch2(while, (yyvsp[(3) - (7)].val), (yyvsp[(6) - (7)].val));

		    ;}
    break;

  case 300:
#line 2687 "ripper.y"
    {COND_PUSH(1);;}
    break;

  case 301:
#line 2687 "ripper.y"
    {COND_POP();;}
    break;

  case 302:
#line 2690 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_UNTIL(cond((yyvsp[(3) - (7)].val)), (yyvsp[(6) - (7)].val), 1);
			fixpos((yyval.val), (yyvsp[(3) - (7)].val));
#endif
			(yyval.val) = dispatch2(until, (yyvsp[(3) - (7)].val), (yyvsp[(6) - (7)].val));

		    ;}
    break;

  case 303:
#line 2701 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CASE((yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val));
			fixpos((yyval.val), (yyvsp[(2) - (5)].val));
#endif
			(yyval.val) = dispatch2(case, (yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val));

		    ;}
    break;

  case 304:
#line 2710 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CASE(0, (yyvsp[(3) - (4)].val));
#endif
			(yyval.val) = dispatch2(case, Qnil, (yyvsp[(3) - (4)].val));

		    ;}
    break;

  case 305:
#line 2718 "ripper.y"
    {COND_PUSH(1);;}
    break;

  case 306:
#line 2720 "ripper.y"
    {COND_POP();;}
    break;

  case 307:
#line 2723 "ripper.y"
    {
#if 0
			/*
			 *  for a, b, c in e
			 *  #=>
			 *  e.each{|*x| a, b, c = x
			 *
			 *  for a in e
			 *  #=>
			 *  e.each{|x| a, = x}
			 */
			ID id = internal_id();
			ID *tbl = ALLOC_N(ID, 2);
			NODE *m = NEW_ARGS_AUX(0, 0);
			NODE *args, *scope;

			if (nd_type((yyvsp[(2) - (9)].val)) == NODE_MASGN) {
			    /* if args.length == 1 && args[0].kind_of?(Array)
			     *   args = args[0]
			     * end
			     */
			    NODE *one = NEW_LIST(NEW_LIT(INT2FIX(1)));
			    NODE *zero = NEW_LIST(NEW_LIT(INT2FIX(0)));
			    m->nd_next = block_append(
				NEW_IF(
				    NEW_NODE(NODE_AND,
					     NEW_CALL(NEW_CALL(NEW_DVAR(id), rb_intern("length"), 0),
						      rb_intern("=="), one),
					     NEW_CALL(NEW_CALL(NEW_DVAR(id), rb_intern("[]"), zero),
						      rb_intern("kind_of?"), NEW_LIST(NEW_LIT(rb_cArray))),
					     0),
					NEW_DASGN_CURR(id,
						       NEW_CALL(NEW_DVAR(id), rb_intern("[]"), zero)),
					0),
				node_assign((yyvsp[(2) - (9)].val), NEW_DVAR(id)));
			}
			else {
			    m->nd_next = node_assign(NEW_MASGN(NEW_LIST((yyvsp[(2) - (9)].val)), 0), NEW_DVAR(id));
			}

			args = new_args(m, 0, id, 0, 0);
			scope = NEW_NODE(NODE_SCOPE, tbl, (yyvsp[(8) - (9)].val), args);
			tbl[0] = 1; tbl[1] = id;
			(yyval.val) = NEW_FOR(0, (yyvsp[(5) - (9)].val), scope);
			fixpos((yyval.val), (yyvsp[(2) - (9)].val));
#endif
			(yyval.val) = dispatch3(for, (yyvsp[(2) - (9)].val), (yyvsp[(5) - (9)].val), (yyvsp[(8) - (9)].val));

		    ;}
    break;

  case 308:
#line 2773 "ripper.y"
    {
			if (in_def || in_single)
			    yyerror("class definition in method body");
#if 0
			local_push(0);
			(yyval.num) = ruby_sourceline;
#endif

		    ;}
    break;

  case 309:
#line 2784 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CLASS((yyvsp[(2) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(3) - (6)].val));
			nd_set_line((yyval.val), (yyvsp[(4) - (6)].num));
			local_pop();
#endif
			(yyval.val) = dispatch3(class, (yyvsp[(2) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val));

		    ;}
    break;

  case 310:
#line 2794 "ripper.y"
    {
#if 0
			(yyval.num) = in_def;
			in_def = 0;
#endif
			in_def = 0;

		    ;}
    break;

  case 311:
#line 2803 "ripper.y"
    {
#if 0
			(yyval.num) = in_single;
			in_single = 0;
			local_push(0);
#endif
			(yyval.val) = in_single;
			in_single = 0;

		    ;}
    break;

  case 312:
#line 2815 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_SCLASS((yyvsp[(3) - (8)].val), (yyvsp[(7) - (8)].val));
			fixpos((yyval.val), (yyvsp[(3) - (8)].val));
			local_pop();
			in_def = (yyvsp[(4) - (8)].num);
			in_single = (yyvsp[(6) - (8)].num);
#endif
			(yyval.val) = dispatch2(sclass, (yyvsp[(3) - (8)].val), (yyvsp[(7) - (8)].val));
			in_def = (yyvsp[(4) - (8)].val);
			in_single = (yyvsp[(6) - (8)].val);

		    ;}
    break;

  case 313:
#line 2829 "ripper.y"
    {
			if (in_def || in_single)
			    yyerror("module definition in method body");
#if 0
			local_push(0);
			(yyval.num) = ruby_sourceline;
#endif

		    ;}
    break;

  case 314:
#line 2840 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MODULE((yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(3) - (5)].num));
			local_pop();
#endif
			(yyval.val) = dispatch2(module, (yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val));

		    ;}
    break;

  case 315:
#line 2850 "ripper.y"
    {
			(yyval.id) = cur_mid;
			cur_mid = (yyvsp[(2) - (2)].val);
			in_def++;
#if 0
			local_push(0);
#endif

		    ;}
    break;

  case 316:
#line 2862 "ripper.y"
    {
#if 0
			NODE *body = remove_begin((yyvsp[(5) - (6)].val));
			reduce_nodes(&body);
			(yyval.val) = NEW_DEFN((yyvsp[(2) - (6)].val), (yyvsp[(4) - (6)].val), body, NOEX_PRIVATE);
			fixpos((yyval.val), (yyvsp[(4) - (6)].val));
			local_pop();
			in_def--;
			cur_mid = (yyvsp[(3) - (6)].id);
#endif
			(yyval.val) = dispatch3(def, (yyvsp[(2) - (6)].val), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val));
			in_def--;
			cur_mid = (yyvsp[(3) - (6)].id);

		    ;}
    break;

  case 317:
#line 2877 "ripper.y"
    {lex_state = EXPR_FNAME;;}
    break;

  case 318:
#line 2878 "ripper.y"
    {
			in_single++;
			lex_state = EXPR_END; /* force for args */
#if 0
			local_push(0);
#endif

		    ;}
    break;

  case 319:
#line 2889 "ripper.y"
    {
#if 0
			NODE *body = remove_begin((yyvsp[(8) - (9)].val));
			reduce_nodes(&body);
			(yyval.val) = NEW_DEFS((yyvsp[(2) - (9)].val), (yyvsp[(5) - (9)].val), (yyvsp[(7) - (9)].val), body);
			fixpos((yyval.val), (yyvsp[(2) - (9)].val));
			local_pop();
			in_single--;
#endif
			(yyval.val) = dispatch5(defs, (yyvsp[(2) - (9)].val), (yyvsp[(3) - (9)].val), (yyvsp[(5) - (9)].val), (yyvsp[(7) - (9)].val), (yyvsp[(8) - (9)].val));
			in_single--;

		    ;}
    break;

  case 320:
#line 2903 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_BREAK(0);
#endif
			(yyval.val) = dispatch1(break, arg_new());

		    ;}
    break;

  case 321:
#line 2911 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_NEXT(0);
#endif
			(yyval.val) = dispatch1(next, arg_new());

		    ;}
    break;

  case 322:
#line 2919 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_REDO();
#endif
			(yyval.val) = dispatch0(redo);

		    ;}
    break;

  case 323:
#line 2927 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_RETRY();
#endif
			(yyval.val) = dispatch0(retry);

		    ;}
    break;

  case 324:
#line 2937 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (1)].val));
			(yyval.val) = (yyvsp[(1) - (1)].val);
		        if (!(yyval.val)) (yyval.val) = NEW_NIL();
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    ;}
    break;

  case 325:
#line 2951 "ripper.y"
    { (yyval.val) = Qnil; ;}
    break;

  case 327:
#line 2957 "ripper.y"
    { (yyval.val) = (yyvsp[(2) - (2)].val); ;}
    break;

  case 328:
#line 2964 "ripper.y"
    { (yyval.val) = Qnil; ;}
    break;

  case 331:
#line 2973 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_IF(cond((yyvsp[(2) - (5)].val)), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
			fixpos((yyval.val), (yyvsp[(2) - (5)].val));
#endif
			(yyval.val) = dispatch3(elsif, (yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val), escape_Qundef((yyvsp[(5) - (5)].val)));

		    ;}
    break;

  case 333:
#line 2985 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch1(else, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 336:
#line 2999 "ripper.y"
    {
#if 0
			(yyval.val) = assignable((yyvsp[(1) - (1)].val), 0);
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 337:
#line 3007 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 338:
#line 3017 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = mlhs_add(mlhs_new(), (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 339:
#line 3025 "ripper.y"
    {
#if 0
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = mlhs_add((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 340:
#line 3035 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (1)].val), 0);
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    ;}
    break;

  case 341:
#line 3043 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (4)].val), assignable((yyvsp[(4) - (4)].val), 0));
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (4)].val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 342:
#line 3051 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (6)].val), NEW_POSTARG(assignable((yyvsp[(4) - (6)].val), 0), (yyvsp[(6) - (6)].val)));
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (6)].val), (yyvsp[(4) - (6)].val));

		    ;}
    break;

  case 343:
#line 3059 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (3)].val), -1);
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (3)].val), Qnil);

		    ;}
    break;

  case 344:
#line 3067 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (5)].val), NEW_POSTARG(-1, (yyvsp[(5) - (5)].val)));
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (5)].val), (yyvsp[(5) - (5)].val));

		    ;}
    break;

  case 345:
#line 3075 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, assignable((yyvsp[(2) - (2)].val), 0));
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 346:
#line 3083 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, NEW_POSTARG(assignable((yyvsp[(2) - (4)].val), 0), (yyvsp[(4) - (4)].val)));
#endif
		      #if 0
		      TODO: Check me
		      #endif
			(yyval.val) = mlhs_add_star((yyvsp[(2) - (4)].val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 347:
#line 3094 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, -1);
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), Qnil);

		    ;}
    break;

  case 348:
#line 3102 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, NEW_POSTARG(-1, (yyvsp[(3) - (3)].val)));
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), Qnil);

		    ;}
    break;

  case 349:
#line 3112 "ripper.y"
    {
#if 0
			(yyval.val) = new_args((yyvsp[(1) - (4)].val), 0, (yyvsp[(3) - (4)].val), 0, (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = params_new((yyvsp[(1) - (4)].val), Qnil, (yyvsp[(3) - (4)].val), Qnil, escape_Qundef((yyvsp[(4) - (4)].val)));

		    ;}
    break;

  case 350:
#line 3120 "ripper.y"
    {
#if 0
			(yyval.val) = new_args((yyvsp[(1) - (2)].val), 0, 1, 0, 0);
#endif
			(yyval.val) = params_new((yyvsp[(1) - (2)].val), Qnil, Qnil, Qnil, Qnil);
                        dispatch1(excessed_comma, (yyval.val));

		    ;}
    break;

  case 351:
#line 3129 "ripper.y"
    {
#if 0
			(yyval.val) = new_args((yyvsp[(1) - (6)].val), 0, (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
#endif
			(yyval.val) = params_new((yyvsp[(1) - (6)].val), Qnil, (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), escape_Qundef((yyvsp[(6) - (6)].val)));

		    ;}
    break;

  case 352:
#line 3137 "ripper.y"
    {
#if 0
			(yyval.val) = new_args((yyvsp[(1) - (2)].val), 0, 0, 0, (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = params_new((yyvsp[(1) - (2)].val), Qnil,Qnil, Qnil, escape_Qundef((yyvsp[(2) - (2)].val)));

		    ;}
    break;

  case 353:
#line 3145 "ripper.y"
    {
#if 0
			(yyval.val) = new_args(0, 0, (yyvsp[(1) - (2)].val), 0, (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = params_new(Qnil, Qnil, (yyvsp[(1) - (2)].val), Qnil, escape_Qundef((yyvsp[(2) - (2)].val)));

		    ;}
    break;

  case 354:
#line 3153 "ripper.y"
    {
#if 0
			(yyval.val) = new_args(0, 0, (yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = params_new(Qnil, Qnil, (yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), escape_Qundef((yyvsp[(4) - (4)].val)));

		    ;}
    break;

  case 355:
#line 3161 "ripper.y"
    {
#if 0
			(yyval.val) = new_args(0, 0, 0, 0, (yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = params_new(Qnil, Qnil, Qnil, Qnil, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 358:
#line 3175 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = blockvar_new(params_new(Qnil,Qnil,Qnil,Qnil,Qnil),
                                          escape_Qundef((yyvsp[(2) - (3)].val)));

		    ;}
    break;

  case 359:
#line 3184 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = blockvar_new(params_new(Qnil,Qnil,Qnil,Qnil,Qnil),
                                          Qnil);

		    ;}
    break;

  case 360:
#line 3193 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (4)].val);
#endif
			(yyval.val) = blockvar_new(escape_Qundef((yyvsp[(2) - (4)].val)), escape_Qundef((yyvsp[(3) - (4)].val)));

		    ;}
    break;

  case 362:
#line 3205 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = (yyvsp[(2) - (2)].val);

		    ;}
    break;

  case 363:
#line 3217 "ripper.y"
    {
			(yyval.val) = rb_ary_new2((yyvsp[(1) - (1)].val));
		    ;}
    break;

  case 364:
#line 3224 "ripper.y"
    {
			rb_ary_push((yyval.val), (yyvsp[(3) - (3)].val));
		    ;}
    break;

  case 365:
#line 3231 "ripper.y"
    {
#if 0
			new_bv((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    ;}
    break;

  case 366:
#line 3239 "ripper.y"
    {
			(yyval.val) = 0;
		    ;}
    break;

  case 367:
#line 3244 "ripper.y"
    {
#if 0
			dyna_push();
			(yyval.num) = lpar_beg;
			lpar_beg = ++paren_nest;
#endif

		    ;}
    break;

  case 368:
#line 3254 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
			(yyval.val)->nd_body = NEW_SCOPE((yyvsp[(2) - (3)].val)->nd_head, (yyvsp[(3) - (3)].val));
			dyna_pop();
			lpar_beg = (yyvsp[(1) - (3)].num);
#endif
			(yyval.val) = dispatch2(lambda, (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 369:
#line 3267 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LAMBDA((yyvsp[(2) - (4)].val));
#endif
			(yyval.val) = dispatch1(paren, (yyvsp[(2) - (4)].val));

		    ;}
    break;

  case 370:
#line 3275 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LAMBDA((yyvsp[(1) - (2)].val));
#endif
			(yyval.val) = (yyvsp[(1) - (2)].val);

		    ;}
    break;

  case 371:
#line 3285 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (3)].val);
		    ;}
    break;

  case 372:
#line 3289 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (3)].val);
		    ;}
    break;

  case 373:
#line 3295 "ripper.y"
    {
#if 0
			dyna_push();
			(yyval.num) = ruby_sourceline;
#endif
		    ;}
    break;

  case 374:
#line 3304 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ITER((yyvsp[(3) - (5)].val),(yyvsp[(4) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(2) - (5)].num));
			dyna_pop();
#endif
			(yyval.val) = dispatch2(do_block, escape_Qundef((yyvsp[(3) - (5)].val)), (yyvsp[(4) - (5)].val));

		    ;}
    break;

  case 375:
#line 3316 "ripper.y"
    {
#if 0
			block_dup_check((yyvsp[(1) - (2)].val)->nd_args, (yyvsp[(2) - (2)].val));
			(yyvsp[(2) - (2)].val)->nd_iter = (yyvsp[(1) - (2)].val);
			(yyval.val) = (yyvsp[(2) - (2)].val);
			fixpos((yyval.val), (yyvsp[(1) - (2)].val));
#endif
			(yyval.val) = method_add_block((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 376:
#line 3327 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (4)].val), ripper_id2sym('.'), (yyvsp[(3) - (4)].val));
			(yyval.val) = method_optarg((yyval.val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 377:
#line 3336 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (4)].val), ripper_intern("::"), (yyvsp[(3) - (4)].val));
			(yyval.val) = method_optarg((yyval.val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 378:
#line 3347 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_FCALL((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
			fixpos((yyval.val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = method_arg(dispatch1(fcall, (yyvsp[(1) - (2)].val)), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 379:
#line 3356 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
			fixpos((yyval.val), (yyvsp[(1) - (4)].val));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (4)].val), ripper_id2sym('.'), (yyvsp[(3) - (4)].val));
			(yyval.val) = method_optarg((yyval.val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 380:
#line 3366 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
			fixpos((yyval.val), (yyvsp[(1) - (4)].val));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (4)].val), ripper_id2sym('.'), (yyvsp[(3) - (4)].val));
			(yyval.val) = method_optarg((yyval.val), (yyvsp[(4) - (4)].val));

		    ;}
    break;

  case 381:
#line 3376 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val), 0);
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (3)].val), ripper_intern("::"), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 382:
#line 3384 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (3)].val), rb_intern("call"), (yyvsp[(3) - (3)].val));
			fixpos((yyval.val), (yyvsp[(1) - (3)].val));
#endif
			(yyval.val) = dispatch3(call, dispatch1(paren, (yyvsp[(1) - (3)].val)),
				       ripper_id2sym('.'), rb_intern("call"));
			(yyval.val) = method_optarg((yyval.val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 383:
#line 3395 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (3)].val), rb_intern("call"), (yyvsp[(3) - (3)].val));
			fixpos((yyval.val), (yyvsp[(1) - (3)].val));
#endif
			(yyval.val) = dispatch3(call, dispatch1(paren, (yyvsp[(1) - (3)].val)),
				       ripper_id2sym('.'), rb_intern("call"));
			(yyval.val) = method_optarg((yyval.val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 384:
#line 3406 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_SUPER((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch1(super, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 385:
#line 3414 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ZSUPER();
#endif
			(yyval.val) = dispatch0(zsuper);

		    ;}
    break;

  case 386:
#line 3422 "ripper.y"
    {
#if 0
			if ((yyvsp[(1) - (4)].val) && nd_type((yyvsp[(1) - (4)].val)) == NODE_SELF)
			    (yyval.val) = NEW_FCALL(tAREF, (yyvsp[(3) - (4)].val));
			else
			    (yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), tAREF, (yyvsp[(3) - (4)].val));
			fixpos((yyval.val), (yyvsp[(1) - (4)].val));
#endif
			(yyval.val) = dispatch2(aref, (yyvsp[(1) - (4)].val), escape_Qundef((yyvsp[(3) - (4)].val)));

		    ;}
    break;

  case 387:
#line 3436 "ripper.y"
    {
#if 0
			dyna_push();
			(yyval.num) = ruby_sourceline;
#endif

		    ;}
    break;

  case 388:
#line 3445 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ITER((yyvsp[(3) - (5)].val),(yyvsp[(4) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(2) - (5)].num));
			dyna_pop();
#endif
			(yyval.val) = dispatch2(brace_block, escape_Qundef((yyvsp[(3) - (5)].val)), (yyvsp[(4) - (5)].val));

		    ;}
    break;

  case 389:
#line 3455 "ripper.y"
    {
#if 0
			dyna_push();
			(yyval.num) = ruby_sourceline;
#endif

		    ;}
    break;

  case 390:
#line 3464 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ITER((yyvsp[(3) - (5)].val),(yyvsp[(4) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(2) - (5)].num));
			dyna_pop();
#endif
			(yyval.val) = dispatch2(do_block, escape_Qundef((yyvsp[(3) - (5)].val)), (yyvsp[(4) - (5)].val));

		    ;}
    break;

  case 391:
#line 3478 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_WHEN((yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
#endif
			(yyval.val) = dispatch3(when, (yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val), escape_Qundef((yyvsp[(5) - (5)].val)));

		    ;}
    break;

  case 394:
#line 3494 "ripper.y"
    {
#if 0
			if ((yyvsp[(3) - (6)].val)) {
			    (yyvsp[(3) - (6)].val) = node_assign((yyvsp[(3) - (6)].val), NEW_ERRINFO());
			    (yyvsp[(5) - (6)].val) = block_append((yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val));
			}
			(yyval.val) = NEW_RESBODY((yyvsp[(2) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
			fixpos((yyval.val), (yyvsp[(2) - (6)].val)?(yyvsp[(2) - (6)].val):(yyvsp[(5) - (6)].val));
#endif
			(yyval.val) = dispatch4(rescue,
				       escape_Qundef((yyvsp[(2) - (6)].val)),
				       escape_Qundef((yyvsp[(3) - (6)].val)),
				       escape_Qundef((yyvsp[(5) - (6)].val)),
				       escape_Qundef((yyvsp[(6) - (6)].val)));

		    ;}
    break;

  case 396:
#line 3514 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 399:
#line 3526 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    ;}
    break;

  case 401:
#line 3533 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch1(ensure, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 404:
#line 3545 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIT(ID2SYM((yyvsp[(1) - (1)].val)));
#endif
			(yyval.val) = dispatch1(symbol_literal, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 406:
#line 3556 "ripper.y"
    {
#if 0
			NODE *node = (yyvsp[(1) - (1)].val);
			if (!node) {
			    node = NEW_STR(STR_NEW0());
			}
			else {
			    node = evstr2dstr(node);
			}
			(yyval.val) = node;
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    ;}
    break;

  case 409:
#line 3575 "ripper.y"
    {
#if 0
			(yyval.val) = literal_concat((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(string_concat, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 410:
#line 3585 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(string_literal, (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 411:
#line 3595 "ripper.y"
    {
#if 0
			NODE *node = (yyvsp[(2) - (3)].val);
			if (!node) {
			    node = NEW_XSTR(STR_NEW0());
			}
			else {
			    switch (nd_type(node)) {
			      case NODE_STR:
				nd_set_type(node, NODE_XSTR);
				break;
			      case NODE_DSTR:
				nd_set_type(node, NODE_DXSTR);
				break;
			      default:
				node = NEW_NODE(NODE_DXSTR, STR_NEW0(), 1, NEW_LIST(node));
				break;
			    }
			}
			(yyval.val) = node;
#endif
			(yyval.val) = dispatch1(xstring_literal, (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 412:
#line 3622 "ripper.y"
    {
#if 0
			int options = (yyvsp[(3) - (3)].val);
			NODE *node = (yyvsp[(2) - (3)].val);
                        NODE *list;
			if (!node) {
			    node = NEW_LIT(reg_compile(STR_NEW0(), options));
			}
			else switch (nd_type(node)) {
			  case NODE_STR:
			    {
				VALUE src = node->nd_lit;
				nd_set_type(node, NODE_LIT);
				node->nd_lit = reg_compile(src, options);
			    }
			    break;
			  default:
			    node = NEW_NODE(NODE_DSTR, STR_NEW0(), 1, NEW_LIST(node));
			  case NODE_DSTR:
			    if (options & RE_OPTION_ONCE) {
				nd_set_type(node, NODE_DREGX_ONCE);
			    }
			    else {
				nd_set_type(node, NODE_DREGX);
			    }
			    node->nd_cflag = options & RE_OPTION_MASK;
                            reg_fragment_check(node->nd_lit, options);
                            for (list = node->nd_next; list; list = list->nd_next) {
                                if (nd_type(list->nd_head) == NODE_STR) {
                                    reg_fragment_check(list->nd_head->nd_lit, options);
                                }
                            }
			    break;
			}
			(yyval.val) = node;
#endif
			(yyval.val) = dispatch2(regexp_literal, (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 413:
#line 3664 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ZARRAY();
#endif
			(yyval.val) = dispatch0(words_new);

		    ;}
    break;

  case 414:
#line 3672 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (3)].val);
		    ;}
    break;

  case 415:
#line 3678 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch0(words_new);

		    ;}
    break;

  case 416:
#line 3686 "ripper.y"
    {
#if 0
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), evstr2dstr((yyvsp[(2) - (3)].val)));
#endif
			(yyval.val) = dispatch2(words_add, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 417:
#line 3698 "ripper.y"
    {
			(yyval.val) = dispatch0(word_new);
			(yyval.val) = dispatch2(word_add, (yyval.val), (yyvsp[(1) - (1)].val));
		    ;}
    break;

  case 418:
#line 3704 "ripper.y"
    {
#if 0
			(yyval.val) = literal_concat((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(word_add, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 419:
#line 3714 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ZARRAY();
#endif
			(yyval.val) = dispatch0(qwords_new);

		    ;}
    break;

  case 420:
#line 3722 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (3)].val);
		    ;}
    break;

  case 421:
#line 3728 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch0(qwords_new);

		    ;}
    break;

  case 422:
#line 3736 "ripper.y"
    {
#if 0
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));
#endif
			(yyval.val) = dispatch2(qwords_add, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 423:
#line 3746 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch0(string_content);

		    ;}
    break;

  case 424:
#line 3754 "ripper.y"
    {
#if 0
			(yyval.val) = literal_concat((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(string_add, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 425:
#line 3764 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch0(xstring_new);

		    ;}
    break;

  case 426:
#line 3772 "ripper.y"
    {
#if 0
			(yyval.val) = literal_concat((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(xstring_add, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 428:
#line 3783 "ripper.y"
    {
			(yyval.node) = lex_strterm;
			lex_strterm = 0;
			lex_state = EXPR_BEG;
		    ;}
    break;

  case 429:
#line 3789 "ripper.y"
    {
#if 0
			lex_strterm = (yyvsp[(2) - (3)].node);
			(yyval.val) = NEW_EVSTR((yyvsp[(3) - (3)].val));
#endif
			lex_strterm = (yyvsp[(2) - (3)].node);
			(yyval.val) = dispatch1(string_dvar, (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 430:
#line 3799 "ripper.y"
    {
			(yyval.node) = lex_strterm;
			lex_strterm = 0;
			lex_state = EXPR_BEG;
			COND_PUSH(0);
			CMDARG_PUSH(0);
		    ;}
    break;

  case 431:
#line 3807 "ripper.y"
    {
			lex_strterm = (yyvsp[(2) - (4)].node);
			COND_LEXPOP();
			CMDARG_LEXPOP();
#if 0
			if ((yyvsp[(3) - (4)].val)) (yyvsp[(3) - (4)].val)->flags &= ~NODE_NEWLINE;
			(yyval.val) = new_evstr((yyvsp[(3) - (4)].val));
#endif
			(yyval.val) = dispatch1(string_embexpr, (yyvsp[(3) - (4)].val));

		    ;}
    break;

  case 432:
#line 3821 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_GVAR((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = dispatch1(var_ref, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 433:
#line 3829 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_IVAR((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = dispatch1(var_ref, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 434:
#line 3837 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CVAR((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = dispatch1(var_ref, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 436:
#line 3848 "ripper.y"
    {
#if 0
			lex_state = EXPR_ENDARG;
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			lex_state = EXPR_ENDARG;
			(yyval.val) = dispatch1(symbol, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 441:
#line 3866 "ripper.y"
    {
#if 0
			lex_state = EXPR_ENDARG;
			if (!((yyval.val) = (yyvsp[(2) - (3)].val))) {
			    (yyval.val) = NEW_NIL();
			    yyerror("empty symbol literal");
			}
			else {
			    VALUE lit;

			    switch (nd_type((yyval.val))) {
			      case NODE_DSTR:
				nd_set_type((yyval.val), NODE_DSYM);
				break;
			      case NODE_STR:
				lit = (yyval.val)->nd_lit;
				if (RSTRING_LEN(lit) == 0) {
				    yyerror("empty symbol literal");
				    break;
				}
				(yyval.val)->nd_lit = ID2SYM(rb_intern_str(lit));
				nd_set_type((yyval.val), NODE_LIT);
				break;
			      default:
				(yyval.val) = NEW_NODE(NODE_DSYM, STR_NEW0(), 1, NEW_LIST((yyval.val)));
				break;
			    }
			}
#endif
			lex_state = EXPR_ENDARG;
			(yyval.val) = dispatch1(dyna_symbol, (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 444:
#line 3904 "ripper.y"
    {
#if 0
			(yyval.val) = negate_lit((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(unary, ripper_intern("-@"), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 445:
#line 3912 "ripper.y"
    {
#if 0
			(yyval.val) = negate_lit((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(unary, ripper_intern("-@"), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 451:
#line 3926 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword_nil);;}
    break;

  case 452:
#line 3927 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword_self);;}
    break;

  case 453:
#line 3928 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword_true);;}
    break;

  case 454:
#line 3929 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword_false);;}
    break;

  case 455:
#line 3930 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword__FILE__);;}
    break;

  case 456:
#line 3931 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword__LINE__);;}
    break;

  case 457:
#line 3932 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword__ENCODING__);;}
    break;

  case 458:
#line 3936 "ripper.y"
    {
#if 0
			if (!((yyval.val) = gettable((yyvsp[(1) - (1)].val)))) (yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(var_ref, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 459:
#line 3946 "ripper.y"
    {
#if 0
			(yyval.val) = assignable((yyvsp[(1) - (1)].val), 0);
#endif
			(yyval.val) = dispatch1(var_field, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 462:
#line 3960 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = Qnil;

		    ;}
    break;

  case 463:
#line 3968 "ripper.y"
    {
			lex_state = EXPR_BEG;
		    ;}
    break;

  case 464:
#line 3972 "ripper.y"
    {
			(yyval.val) = (yyvsp[(3) - (4)].val);
		    ;}
    break;

  case 465:
#line 3976 "ripper.y"
    {
#if 0
			yyerrok;
			(yyval.val) = 0;
#endif
			yyerrok;
			(yyval.val) = Qnil;

		    ;}
    break;

  case 466:
#line 3988 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
			lex_state = EXPR_BEG;
			command_start = Qtrue;
#endif
			(yyval.val) = dispatch1(paren, (yyvsp[(2) - (3)].val));
			lex_state = EXPR_BEG;
			command_start = Qtrue;

		    ;}
    break;

  case 467:
#line 4000 "ripper.y"
    {
			(yyval.val) = (yyvsp[(1) - (2)].val);
		    ;}
    break;

  case 468:
#line 4006 "ripper.y"
    {
#if 0
			(yyval.val) = new_args((yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), 0, (yyvsp[(6) - (6)].val));
#endif
			(yyval.val) = params_new((yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), Qnil, escape_Qundef((yyvsp[(6) - (6)].val)));

		    ;}
    break;

  case 469:
#line 4014 "ripper.y"
    {
#if 0
			(yyval.val) = new_args((yyvsp[(1) - (8)].val), (yyvsp[(3) - (8)].val), (yyvsp[(5) - (8)].val), (yyvsp[(7) - (8)].val), (yyvsp[(8) - (8)].val));
#endif
			(yyval.val) = params_new((yyvsp[(1) - (8)].val), (yyvsp[(3) - (8)].val), (yyvsp[(5) - (8)].val), (yyvsp[(7) - (8)].val), escape_Qundef((yyvsp[(8) - (8)].val)));

		    ;}
    break;

  case 470:
#line 4022 "ripper.y"
    {
#if 0
			(yyval.val) = new_args((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), 0, 0, (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = params_new((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), Qnil, Qnil, escape_Qundef((yyvsp[(4) - (4)].val)));

		    ;}
    break;

  case 471:
#line 4030 "ripper.y"
    {
#if 0
			(yyval.val) = new_args((yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), 0, (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
#endif
			(yyval.val) = params_new((yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), Qnil, (yyvsp[(5) - (6)].val), escape_Qundef((yyvsp[(6) - (6)].val)));

		    ;}
    break;

  case 472:
#line 4038 "ripper.y"
    {
#if 0
			(yyval.val) = new_args((yyvsp[(1) - (4)].val), 0, (yyvsp[(3) - (4)].val), 0, (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = params_new((yyvsp[(1) - (4)].val), Qnil, (yyvsp[(3) - (4)].val), Qnil, escape_Qundef((yyvsp[(4) - (4)].val)));

		    ;}
    break;

  case 473:
#line 4046 "ripper.y"
    {
#if 0
			(yyval.val) = new_args((yyvsp[(1) - (6)].val), 0, (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
#endif
			(yyval.val) = params_new((yyvsp[(1) - (6)].val), Qnil, (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), escape_Qundef((yyvsp[(6) - (6)].val)));

		    ;}
    break;

  case 474:
#line 4054 "ripper.y"
    {
#if 0
			(yyval.val) = new_args((yyvsp[(1) - (2)].val), 0, 0, 0, (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = params_new((yyvsp[(1) - (2)].val), Qnil, Qnil, Qnil,escape_Qundef((yyvsp[(2) - (2)].val)));

		    ;}
    break;

  case 475:
#line 4062 "ripper.y"
    {
#if 0
			(yyval.val) = new_args(0, (yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), 0, (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = params_new(Qnil, (yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), Qnil, escape_Qundef((yyvsp[(4) - (4)].val)));

		    ;}
    break;

  case 476:
#line 4070 "ripper.y"
    {
#if 0
			(yyval.val) = new_args(0, (yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
#endif
			(yyval.val) = params_new(Qnil, (yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), escape_Qundef((yyvsp[(6) - (6)].val)));

		    ;}
    break;

  case 477:
#line 4078 "ripper.y"
    {
#if 0
			(yyval.val) = new_args(0, (yyvsp[(1) - (2)].val), 0, 0, (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = params_new(Qnil, (yyvsp[(1) - (2)].val), Qnil, Qnil,escape_Qundef((yyvsp[(2) - (2)].val)));

		    ;}
    break;

  case 478:
#line 4086 "ripper.y"
    {
#if 0
			(yyval.val) = new_args(0, (yyvsp[(1) - (4)].val), 0, (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = params_new(Qnil, (yyvsp[(1) - (4)].val), Qnil, (yyvsp[(3) - (4)].val), escape_Qundef((yyvsp[(4) - (4)].val)));

		    ;}
    break;

  case 479:
#line 4094 "ripper.y"
    {
#if 0
			(yyval.val) = new_args(0, 0, (yyvsp[(1) - (2)].val), 0, (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = params_new(Qnil, Qnil, (yyvsp[(1) - (2)].val), Qnil,escape_Qundef((yyvsp[(2) - (2)].val)));

		    ;}
    break;

  case 480:
#line 4102 "ripper.y"
    {
#if 0
			(yyval.val) = new_args(0, 0, (yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = params_new(Qnil, Qnil, (yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), escape_Qundef((yyvsp[(4) - (4)].val)));

		    ;}
    break;

  case 481:
#line 4110 "ripper.y"
    {
#if 0
			(yyval.val) = new_args(0, 0, 0, 0, (yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = params_new(Qnil, Qnil, Qnil, Qnil, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 482:
#line 4118 "ripper.y"
    {
#if 0
			(yyval.val) = new_args(0, 0, 0, 0, 0);
#endif
			(yyval.val) = params_new(Qnil, Qnil, Qnil, Qnil, Qnil);

		    ;}
    break;

  case 483:
#line 4128 "ripper.y"
    {
#if 0
			yyerror("formal argument cannot be a constant");
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch1(param_error, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 484:
#line 4137 "ripper.y"
    {
#if 0
			yyerror("formal argument cannot be an instance variable");
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch1(param_error, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 485:
#line 4146 "ripper.y"
    {
#if 0
			yyerror("formal argument cannot be a global variable");
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch1(param_error, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 486:
#line 4155 "ripper.y"
    {
#if 0
			yyerror("formal argument cannot be a class variable");
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch1(param_error, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 488:
#line 4167 "ripper.y"
    {
#if 0
			if (!is_local_id((yyvsp[(1) - (1)].val)))
			    yyerror("formal argument must be local variable");
			shadowing_lvar((yyvsp[(1) - (1)].val));
#endif

			(yyval.val) = (yyvsp[(1) - (1)].val);
		    ;}
    break;

  case 489:
#line 4179 "ripper.y"
    {
#if 0
			arg_var((yyvsp[(1) - (1)].val));
			(yyval.val) = NEW_ARGS_AUX((yyvsp[(1) - (1)].val), 1);
#endif

		    ;}
    break;

  case 490:
#line 4187 "ripper.y"
    {
#if 0
			ID tid = internal_id();
			arg_var(tid);
			if (dyna_in_block()) {
			    (yyvsp[(2) - (3)].val)->nd_value = NEW_DVAR(tid);
			}
			else {
			    (yyvsp[(2) - (3)].val)->nd_value = NEW_LVAR(tid);
			}
			(yyval.val) = NEW_ARGS_AUX(tid, 1);
			(yyval.val)->nd_next = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyvsp[(2) - (3)].val));

		    ;}
    break;

  case 491:
#line 4208 "ripper.y"
    {
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));
		    ;}
    break;

  case 492:
#line 4213 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (3)].val);
			(yyval.val)->nd_plen++;
			(yyval.val)->nd_next = block_append((yyval.val)->nd_next, (yyvsp[(3) - (3)].val)->nd_next);
			rb_gc_force_recycle((VALUE)(yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = rb_ary_push((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 493:
#line 4226 "ripper.y"
    {
#if 0
			if (!is_local_id((yyvsp[(1) - (3)].val)))
			    yyerror("formal argument must be local variable");
			shadowing_lvar((yyvsp[(1) - (3)].val));
			arg_var((yyvsp[(1) - (3)].val));
			(yyval.val) = NEW_OPT_ARG(0, assignable((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val)));
#endif
			(yyval.val) = rb_assoc_new((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 494:
#line 4240 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (1)].val);
#endif
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));

		    ;}
    break;

  case 495:
#line 4248 "ripper.y"
    {
#if 0
			NODE *opts = (yyvsp[(1) - (3)].val);

			while (opts->nd_next) {
			    opts = opts->nd_next;
			}
			opts->nd_next = (yyvsp[(3) - (3)].val);
			(yyval.val) = (yyvsp[(1) - (3)].val);
#endif
			(yyval.val) = rb_ary_push((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 498:
#line 4268 "ripper.y"
    {
#if 0
			if (!is_local_id((yyvsp[(2) - (2)].val)))
			    yyerror("rest argument must be local variable");
			shadowing_lvar((yyvsp[(2) - (2)].val));
			arg_var((yyvsp[(2) - (2)].val));
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch1(rest_param, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 499:
#line 4280 "ripper.y"
    {
#if 0
			(yyval.val) = internal_id();
			arg_var((yyval.val));
#endif
			(yyval.val) = dispatch1(rest_param, Qnil);

		    ;}
    break;

  case 502:
#line 4295 "ripper.y"
    {
#if 0
			if (!is_local_id((yyvsp[(2) - (2)].val)))
			    yyerror("block argument must be local variable");
			else if (!dyna_in_block() && local_id((yyvsp[(2) - (2)].val)))
			    yyerror("duplicated block argument name");
			shadowing_lvar((yyvsp[(2) - (2)].val));
			arg_var((yyvsp[(2) - (2)].val));
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch1(blockarg, (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 503:
#line 4311 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    ;}
    break;

  case 504:
#line 4315 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = Qundef;

		    ;}
    break;

  case 505:
#line 4325 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (1)].val));
			(yyval.val) = (yyvsp[(1) - (1)].val);
		        if (!(yyval.val)) (yyval.val) = NEW_NIL();
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    ;}
    break;

  case 506:
#line 4334 "ripper.y"
    {lex_state = EXPR_BEG;;}
    break;

  case 507:
#line 4335 "ripper.y"
    {
#if 0
			if ((yyvsp[(3) - (4)].val) == 0) {
			    yyerror("can't define singleton method for ().");
			}
			else {
			    switch (nd_type((yyvsp[(3) - (4)].val))) {
			      case NODE_STR:
			      case NODE_DSTR:
			      case NODE_XSTR:
			      case NODE_DXSTR:
			      case NODE_DREGX:
			      case NODE_LIT:
			      case NODE_ARRAY:
			      case NODE_ZARRAY:
				yyerror("can't define singleton method for literals");
			      default:
				value_expr((yyvsp[(3) - (4)].val));
				break;
			    }
			}
			(yyval.val) = (yyvsp[(3) - (4)].val);
#endif
			(yyval.val) = dispatch1(paren, (yyvsp[(3) - (4)].val));

		    ;}
    break;

  case 509:
#line 4365 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (2)].val);
#endif
			(yyval.val) = dispatch1(assoclist_from_args, (yyvsp[(1) - (2)].val));

		    ;}
    break;

  case 510:
#line 4377 "ripper.y"
    {
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));
		    ;}
    break;

  case 511:
#line 4382 "ripper.y"
    {
#if 0
			(yyval.val) = list_concat((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = rb_ary_push((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 512:
#line 4392 "ripper.y"
    {
#if 0
			(yyval.val) = list_append(NEW_LIST((yyvsp[(1) - (3)].val)), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(assoc_new, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    ;}
    break;

  case 513:
#line 4400 "ripper.y"
    {
#if 0
			(yyval.val) = list_append(NEW_LIST(NEW_LIT(ID2SYM((yyvsp[(1) - (2)].val)))), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(assoc_new, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    ;}
    break;

  case 524:
#line 4428 "ripper.y"
    { (yyval.val) = (yyvsp[(1) - (1)].val); ;}
    break;

  case 525:
#line 4433 "ripper.y"
    { (yyval.val) = (yyvsp[(1) - (1)].val); ;}
    break;

  case 535:
#line 4456 "ripper.y"
    {yyerrok;;}
    break;

  case 538:
#line 4461 "ripper.y"
    {yyerrok;;}
    break;

  case 539:
#line 4465 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = Qundef;

		    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 9389 "parse.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      parser_yyerror (parser, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    parser_yyerror (parser, yymsg);
	  }
	else
	  {
	    parser_yyerror (parser, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, parser);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  parser_yyerror (parser, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, parser);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parser);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 4473 "ripper.y"

# undef parser
# undef yylex
# undef yylval
# define yylval  (*((YYSTYPE*)(parser->parser_yylval)))

static int parser_regx_options(struct parser_params*);
static int parser_tokadd_string(struct parser_params*,int,int,int,long*,rb_encoding**);
static void parser_tokaddmbc(struct parser_params *parser, int c, rb_encoding *enc);
static int parser_parse_string(struct parser_params*,NODE*);
static int parser_here_document(struct parser_params*,NODE*);


# define nextc()                   parser_nextc(parser)
# define pushback(c)               parser_pushback(parser, c)
# define newtok()                  parser_newtok(parser)
# define tokspace(n)               parser_tokspace(parser, n)
# define tokadd(c)                 parser_tokadd(parser, c)
# define tok_hex(numlen)           parser_tok_hex(parser, numlen)
# define read_escape(flags,e)      parser_read_escape(parser, flags, e)
# define tokadd_escape(t,e)        parser_tokadd_escape(parser, t, e)
# define regx_options()            parser_regx_options(parser)
# define tokadd_string(f,t,p,n,e)  parser_tokadd_string(parser,f,t,p,n,e)
# define parse_string(n)           parser_parse_string(parser,n)
# define tokaddmbc(c, enc)         parser_tokaddmbc(parser, c, enc)
# define here_document(n)          parser_here_document(parser,n)
# define heredoc_identifier()      parser_heredoc_identifier(parser)
# define heredoc_restore(n)        parser_heredoc_restore(parser,n)
# define whole_match_p(e,l,i)      parser_whole_match_p(parser,e,l,i)

#ifdef RIPPER
/* FIXME */
# define local_id(x)       1
# define dyna_in_block()   1
#endif /* RIPPER */

#ifndef RIPPER
# define set_yylval_str(x) yylval.node = NEW_STR(x)
# define set_yylval_num(x) yylval.num = x
# define set_yylval_id(x)  yylval.id = x
# define set_yylval_literal(x) yylval.node = NEW_LIT(x)
# define set_yylval_node(x) yylval.node = x
# define yylval_id() yylval.id
#else
# define set_yylval_str(x) (void)(x)
# define set_yylval_num(x) (void)(x)
# define set_yylval_id(x) (void)(x)
# define set_yylval_literal(x) (void)(x)
# define set_yylval_node(x) (void)(x)
# define yylval_id() SYM2ID(yylval.val)
#endif

#ifdef RIPPER
#define ripper_flush(p) (p->tokp = p->parser_lex_p)

static void
ripper_dispatch_scan_event(struct parser_params *parser, int t)
{
    VALUE str;

    if (lex_p < parser->tokp) rb_raise(rb_eRuntimeError, "lex_p < tokp");
    if (lex_p == parser->tokp) return;
    str = STR_NEW(parser->tokp, lex_p - parser->tokp);
    yylval.val = ripper_dispatch1(parser, ripper_token2eventid(t), str);
    ripper_flush(parser);
}

static void
ripper_dispatch_delayed_token(struct parser_params *parser, int t)
{
    int saved_line = ruby_sourceline;
    const char *saved_tokp = parser->tokp;

    ruby_sourceline = parser->delayed_line;
    parser->tokp = lex_pbeg + parser->delayed_col;
    yylval.val = ripper_dispatch1(parser, ripper_token2eventid(t), parser->delayed);
    parser->delayed = Qnil;
    ruby_sourceline = saved_line;
    parser->tokp = saved_tokp;
}
#endif /* RIPPER */

#include "ruby/regex.h"
#include "ruby/util.h"

/* We remove any previous definition of `SIGN_EXTEND_CHAR',
   since ours (we hope) works properly with all combinations of
   machines, compilers, `char' and `unsigned char' argument types.
   (Per Bothner suggested the basic approach.)  */
#undef SIGN_EXTEND_CHAR
#if __STDC__
# define SIGN_EXTEND_CHAR(c) ((signed char)(c))
#else  /* not __STDC__ */
/* As in Harbison and Steele.  */
# define SIGN_EXTEND_CHAR(c) ((((unsigned char)(c)) ^ 128) - 128)
#endif

#define parser_mbclen()  mbclen((lex_p-1),lex_pend,parser->enc)
#define parser_precise_mbclen()  rb_enc_precise_mbclen((lex_p-1),lex_pend,parser->enc)
#define is_identchar(p,e,enc) (rb_enc_isalnum(*p,enc) || (*p) == '_' || !ISASCII(*p))
#define parser_is_identchar() (!parser->eofp && is_identchar((lex_p-1),lex_pend,parser->enc))

#define parser_isascii() ISASCII(*(lex_p-1))

static int
parser_yyerror(struct parser_params *parser, const char *msg)
{
#ifndef RIPPER
    const int max_line_margin = 30;
    const char *p, *pe;
    char *buf;
    int len, i;

    compile_error(PARSER_ARG "%s", msg);
    p = lex_p;
    while (lex_pbeg <= p) {
	if (*p == '\n') break;
	p--;
    }
    p++;

    pe = lex_p;
    while (pe < lex_pend) {
	if (*pe == '\n') break;
	pe++;
    }

    len = pe - p;
    if (len > 4) {
	char *p2;
	const char *pre = "", *post = "";

	if (len > max_line_margin * 2 + 10) {
	    if (lex_p - p > max_line_margin) {
		p = rb_enc_prev_char(p, lex_p - max_line_margin, rb_enc_get(lex_lastline));
		pre = "...";
	    }
	    if (pe - lex_p > max_line_margin) {
		pe = rb_enc_prev_char(lex_p, lex_p + max_line_margin, rb_enc_get(lex_lastline));
		post = "...";
	    }
	    len = pe - p;
	}
	buf = ALLOCA_N(char, len+2);
	MEMCPY(buf, p, char, len);
	buf[len] = '\0';
	rb_compile_error_append("%s%s%s", pre, buf, post);

	i = lex_p - p;
	p2 = buf; pe = buf + len;

	while (p2 < pe) {
	    if (*p2 != '\t') *p2 = ' ';
	    p2++;
	}
	buf[i] = '^';
	buf[i+1] = '\0';
	rb_compile_error_append("%s%s", pre, buf);
    }
#else
    dispatch1(parse_error, STR_NEW2(msg));
#endif /* !RIPPER */
    return 0;
}

static void parser_prepare(struct parser_params *parser);

#ifndef RIPPER
VALUE ruby_suppress_tracing(VALUE (*func)(VALUE, int), VALUE arg, int always);

static VALUE
debug_lines(const char *f)
{
    if (rb_const_defined_at(rb_cObject, rb_intern("SCRIPT_LINES__"))) {
	VALUE hash = rb_const_get_at(rb_cObject, rb_intern("SCRIPT_LINES__"));
	if (TYPE(hash) == T_HASH) {
	    VALUE fname = rb_str_new2(f);
	    VALUE lines = rb_hash_lookup(hash, fname);
	    if (NIL_P(lines)) {
		lines = rb_ary_new();
		rb_hash_aset(hash, fname, lines);
	    }
	    return lines;
	}
    }
    return 0;
}

static VALUE
yycompile0(VALUE arg, int tracing)
{
    int n;
    NODE *tree;
    struct parser_params *parser = (struct parser_params *)arg;

    if (!compile_for_eval && rb_safe_level() == 0) {
	ruby_debug_lines = debug_lines(ruby_sourcefile);
	if (ruby_debug_lines && ruby_sourceline > 0) {
	    VALUE str = rb_str_new(0, 0);
	    n = ruby_sourceline;
	    do {
		rb_ary_push(ruby_debug_lines, str);
	    } while (--n);
	}
    }

    parser->enc = rb_enc_get(lex_input);
    parser_prepare(parser);
    n = yyparse((void*)parser);
    ruby_debug_lines = 0;
    compile_for_eval = 0;

    lex_strterm = 0;
    if (parser->nerr) {
	return 0;
    }
    tree = ruby_eval_tree;
    if (!tree) {
	tree = NEW_NIL();
    }
    if (ruby_eval_tree_begin) {
	NODE *scope = ruby_eval_tree;

        if (scope) {
	    scope->nd_body = NEW_PRELUDE(ruby_eval_tree_begin, scope->nd_body);
	}
	tree = scope;
    }
    else {
	tree = ruby_eval_tree;
    }
    return (VALUE)tree;
}

static NODE*
yycompile(struct parser_params *parser, const char *f, int line)
{
    ruby_sourcefile = rb_source_filename(f);
    ruby_sourceline = line - 1;
    return (NODE *)ruby_suppress_tracing(yycompile0, (VALUE)parser, Qtrue);
}
#endif /* !RIPPER */

static VALUE
lex_get_str(struct parser_params *parser, VALUE s)
{
    char *beg, *end, *pend;

    beg = RSTRING_PTR(s);
    if (lex_gets_ptr) {
	if (RSTRING_LEN(s) == lex_gets_ptr) return Qnil;
	beg += lex_gets_ptr;
    }
    pend = RSTRING_PTR(s) + RSTRING_LEN(s);
    end = beg;
    while (end < pend) {
	if (*end++ == '\n') break;
    }
    lex_gets_ptr = end - RSTRING_PTR(s);
    return STR_NEW(beg, end - beg);
}

static VALUE
lex_getline(struct parser_params *parser)
{
    VALUE line = (*parser->parser_lex_gets)(parser, parser->parser_lex_input);
#ifndef RIPPER
    if (ruby_debug_lines && !NIL_P(line)) {
	rb_ary_push(ruby_debug_lines, line);
    }
#endif
    return line;
}

#ifndef RIPPER
NODE*
rb_compile_string(const char *f, VALUE s, int line)
{
    VALUE volatile vparser = rb_parser_new();

    return rb_parser_compile_string(vparser, f, s, line);
}

NODE*
rb_parser_compile_string(volatile VALUE vparser, const char *f, VALUE s, int line)
{
    struct parser_params *parser;
    NODE *node;
    volatile VALUE tmp;

    Data_Get_Struct(vparser, struct parser_params, parser);
    lex_gets = lex_get_str;
    lex_gets_ptr = 0;
    lex_input = s;
    lex_pbeg = lex_p = lex_pend = 0;
    compile_for_eval = rb_parse_in_eval();

    node = yycompile(parser, f, line);
    tmp = vparser; /* prohibit tail call optimization */

    return node;
}

NODE*
rb_compile_cstr(const char *f, const char *s, int len, int line)
{
    return rb_compile_string(f, rb_str_new(s, len), line);
}

NODE*
rb_parser_compile_cstr(volatile VALUE vparser, const char *f, const char *s, int len, int line)
{
    return rb_parser_compile_string(vparser, f, rb_str_new(s, len), line);
}

static VALUE
lex_io_gets(struct parser_params *parser, VALUE io)
{
    return rb_io_gets(io);
}

NODE*
rb_compile_file(const char *f, VALUE file, int start)
{
    VALUE volatile vparser = rb_parser_new();

    return rb_parser_compile_file(vparser, f, file, start);
}

NODE*
rb_parser_compile_file(volatile VALUE vparser, const char *f, VALUE file, int start)
{
    struct parser_params *parser;
    volatile VALUE tmp;
    NODE *node;

    Data_Get_Struct(vparser, struct parser_params, parser);
    lex_gets = lex_io_gets;
    lex_input = file;
    lex_pbeg = lex_p = lex_pend = 0;

    node = yycompile(parser, f, start);
    tmp = vparser; /* prohibit tail call optimization */

    return node;
}
#endif  /* !RIPPER */

#define STR_FUNC_ESCAPE 0x01
#define STR_FUNC_EXPAND 0x02
#define STR_FUNC_REGEXP 0x04
#define STR_FUNC_QWORDS 0x08
#define STR_FUNC_SYMBOL 0x10
#define STR_FUNC_INDENT 0x20

enum string_type {
    str_squote = (0),
    str_dquote = (STR_FUNC_EXPAND),
    str_xquote = (STR_FUNC_EXPAND),
    str_regexp = (STR_FUNC_REGEXP|STR_FUNC_ESCAPE|STR_FUNC_EXPAND),
    str_sword  = (STR_FUNC_QWORDS),
    str_dword  = (STR_FUNC_QWORDS|STR_FUNC_EXPAND),
    str_ssym   = (STR_FUNC_SYMBOL),
    str_dsym   = (STR_FUNC_SYMBOL|STR_FUNC_EXPAND),
};

static VALUE
parser_str_new(const char *p, long n, rb_encoding *enc, int func)
{
    VALUE str;

    str = rb_enc_str_new(p, n, enc);
    if (!(func & STR_FUNC_REGEXP) &&
        rb_enc_asciicompat(enc) &&
        rb_enc_str_coderange(str) == ENC_CODERANGE_7BIT) {
        rb_enc_associate(str, rb_ascii8bit_encoding());
    }

    return str;
}

static inline int
parser_nextc(struct parser_params *parser)
{
    int c;

    if (lex_p == lex_pend) {
	VALUE v = lex_nextline;
	lex_nextline = 0;
	if (!v) {
	    if (parser->eofp)
		return -1;

	    if (!lex_input || NIL_P(v = lex_getline(parser))) {
		parser->eofp = Qtrue;
		lex_lastline = 0;
		return -1;
	    }
	}
	{	
#ifdef RIPPER
	    if (parser->tokp < lex_pend) {
		if (NIL_P(parser->delayed)) {
		    parser->delayed = rb_str_buf_new(1024);
		    rb_str_buf_cat(parser->delayed,
				   parser->tokp, lex_pend - parser->tokp);
		    parser->delayed_line = ruby_sourceline;
		    parser->delayed_col = parser->tokp - lex_pbeg;
		}
		else {
		    rb_str_buf_cat(parser->delayed,
				   parser->tokp, lex_pend - parser->tokp);
		}
	    }
#endif
	    if (heredoc_end > 0) {
		ruby_sourceline = heredoc_end;
		heredoc_end = 0;
	    }
	    ruby_sourceline++;
	    parser->line_count++;
	    lex_pbeg = lex_p = RSTRING_PTR(v);
	    lex_pend = lex_p + RSTRING_LEN(v);
#ifdef RIPPER
	    ripper_flush(parser);
#endif
	    lex_lastline = v;
	}
    }
    c = (unsigned char)*lex_p++;
    if (c == '\r' && lex_p < lex_pend && *lex_p == '\n') {
	lex_p++;
	c = '\n';
    }

    return c;
}

static void
parser_pushback(struct parser_params *parser, int c)
{
    if (c == -1) return;
    lex_p--;
    if (lex_p > lex_pbeg && lex_p[0] == '\n' && lex_p[-1] == '\r') {
	lex_p--;
    }
}

#define lex_goto_eol(parser) (parser->parser_lex_p = parser->parser_lex_pend)
#define was_bol() (lex_p == lex_pbeg + 1)
#define peek(c) (lex_p != lex_pend && (c) == *lex_p)

#define tokfix() (tokenbuf[tokidx]='\0')
#define tok() tokenbuf
#define toklen() tokidx
#define toklast() (tokidx>0?tokenbuf[tokidx-1]:0)

static char*
parser_newtok(struct parser_params *parser)
{
    tokidx = 0;
    if (!tokenbuf) {
	toksiz = 60;
	tokenbuf = ALLOC_N(char, 60);
    }
    if (toksiz > 4096) {
	toksiz = 60;
	REALLOC_N(tokenbuf, char, 60);
    }
    return tokenbuf;
}

static char *
parser_tokspace(struct parser_params *parser, int n)
{
    tokidx += n;

    if (tokidx >= toksiz) {
	do {toksiz *= 2;} while (toksiz < tokidx);
	REALLOC_N(tokenbuf, char, toksiz);
    }
    return &tokenbuf[tokidx-n];
}

static void
parser_tokadd(struct parser_params *parser, int c)
{
    tokenbuf[tokidx++] = (char)c;
    if (tokidx >= toksiz) {
	toksiz *= 2;
	REALLOC_N(tokenbuf, char, toksiz);
    }
}

static int
parser_tok_hex(struct parser_params *parser, int *numlen)
{
    int c;

    c = scan_hex(lex_p, 2, numlen);
    if (!*numlen) {
	yyerror("invalid hex escape");
	return 0;
    }
    lex_p += *numlen;
    return c;
}

#define tokcopy(n) memcpy(tokspace(n), lex_p - (n), (n))

static int
parser_tokadd_utf8(struct parser_params *parser, rb_encoding **encp,
                   int string_literal, int symbol_literal, int regexp_literal)
{
    /*
     * If string_literal is true, then we allow multiple codepoints
     * in \u{}, and add the codepoints to the current token.
     * Otherwise we're parsing a character literal and return a single
     * codepoint without adding it 
     */

    int codepoint;
    int numlen;

    if (regexp_literal) { tokadd('\\'); tokadd('u'); }

    if (peek('{')) {  /* handle \u{...} form */
	do {
            if (regexp_literal) { tokadd(*lex_p); }
	    nextc();
	    codepoint = scan_hex(lex_p, 6, &numlen);
	    if (numlen == 0)  {
		yyerror("invalid Unicode escape");
		return 0;
	    }
	    if (codepoint > 0x10ffff) {
		yyerror("invalid Unicode codepoint (too large)");
		return 0;
	    }
	    lex_p += numlen;
            if (regexp_literal) {
                tokcopy(numlen);
            }
            else if (codepoint >= 0x80) {
		*encp = UTF8_ENC();
		if (string_literal) tokaddmbc(codepoint, *encp);
	    }
	    else if (string_literal) {
		if (codepoint == 0 && symbol_literal) {
		    yyerror("symbol cannot contain '\\u{0}'");
		    return 0;
		}

		tokadd(codepoint);
	    }
	} while (string_literal && (peek(' ') || peek('\t')));

	if (!peek('}')) {
	    yyerror("unterminated Unicode escape");
	    return 0;
	}

        if (regexp_literal) { tokadd('}'); }
	nextc();
    }
    else {			/* handle \uxxxx form */
	codepoint = scan_hex(lex_p, 4, &numlen);
	if (numlen < 4) {
	    yyerror("invalid Unicode escape");
	    return 0;
	}
	lex_p += 4;
        if (regexp_literal) {
            tokcopy(4);
        }
	else if (codepoint >= 0x80) {
	    *encp = UTF8_ENC();
	    if (string_literal) tokaddmbc(codepoint, *encp);
	}
	else if (string_literal) {
	    if (codepoint == 0 && symbol_literal) {
		yyerror("symbol cannot contain '\\u0000'");
		return 0;
	    }

	    tokadd(codepoint);
	}
    }

    return codepoint;
}

#define ESCAPE_CONTROL 1
#define ESCAPE_META    2

static int
parser_read_escape(struct parser_params *parser, int flags,
		   rb_encoding **encp)
{
    int c;
    int numlen;

    switch (c = nextc()) {
      case '\\':	/* Backslash */
	return c;

      case 'n':	/* newline */
	return '\n';

      case 't':	/* horizontal tab */
	return '\t';

      case 'r':	/* carriage-return */
	return '\r';

      case 'f':	/* form-feed */
	return '\f';

      case 'v':	/* vertical tab */
	return '\13';

      case 'a':	/* alarm(bell) */
	return '\007';

      case 'e':	/* escape */
	return 033;

      case '0': case '1': case '2': case '3': /* octal constant */
      case '4': case '5': case '6': case '7':
	if (flags & (ESCAPE_CONTROL|ESCAPE_META)) goto eof;
	{
	    int numlen;

	    pushback(c);
	    c = scan_oct(lex_p, 3, &numlen);
	    lex_p += numlen;
	}
	return c;

      case 'x':	/* hex constant */
	if (flags & (ESCAPE_CONTROL|ESCAPE_META)) goto eof;
	c = tok_hex(&numlen);
	if (numlen == 0) return 0;
	return c;

      case 'b':	/* backspace */
	return '\010';

      case 's':	/* space */
	return ' ';

      case 'M':
	if (flags & ESCAPE_META) goto eof;
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
	if ((c = nextc()) == '\\') {
	    return read_escape(flags|ESCAPE_META, encp) | 0x80;
	}
	else if (c == -1 || !ISASCII(c)) goto eof;
	else {
	    return ((c & 0xff) | 0x80);
	}

      case 'C':
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
      case 'c':
	if (flags & ESCAPE_CONTROL) goto eof;
	if ((c = nextc())== '\\') {
	    c = read_escape(flags|ESCAPE_CONTROL, encp);
	}
	else if (c == '?')
	    return 0177;
	else if (c == -1 || !ISASCII(c)) goto eof;
	return c & 0x9f;

      eof:
      case -1:
        yyerror("Invalid escape character syntax");
	return '\0';

      default:
	return c;
    }
}

static void
parser_tokaddmbc(struct parser_params *parser, int c, rb_encoding *enc)
{
    int len = rb_enc_codelen(c, enc);
    rb_enc_mbcput(c, tokspace(len), enc);
}

static int
parser_tokadd_escape(struct parser_params *parser, int term,
		     rb_encoding **encp)
{
    int c;
    int flags = 0;

  first:
    switch (c = nextc()) {
      case '\n':
	return 0;		/* just ignore */

      case '0': case '1': case '2': case '3': /* octal constant */
      case '4': case '5': case '6': case '7':
	if (flags & (ESCAPE_CONTROL|ESCAPE_META)) goto eof;
	{
	    int numlen;
	    int oct;

	    oct = scan_oct(--lex_p, 3, &numlen);
	    if (numlen == 0) goto eof;
	    lex_p += numlen;
	    tokcopy(numlen + 1);
	}
	return 0;

      case 'x':	/* hex constant */
	if (flags & (ESCAPE_CONTROL|ESCAPE_META)) goto eof;
	{
	    int numlen;
	    int hex;

	    hex = tok_hex(&numlen);
	    if (numlen == 0) goto eof;
	    tokcopy(numlen + 2);
	}
	return 0;

      case 'M':
	if (flags & ESCAPE_META) goto eof;
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
	tokcopy(3);
	flags |= ESCAPE_META;
	goto escaped;

      case 'C':
	if (flags & ESCAPE_CONTROL) goto eof;
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
	tokcopy(3);
	goto escaped;

      case 'c':
	if (flags & ESCAPE_CONTROL) goto eof;
	tokcopy(2);
	flags |= ESCAPE_CONTROL;
      escaped:
	if ((c = nextc()) == '\\') {
	    goto first;
	}
	else if (c == -1) goto eof;
	tokadd(c);
	return 0;

      eof:
      case -1:
        yyerror("Invalid escape character syntax");
	return -1;

      default:
	if (c != '\\' || c != term)
	    tokadd('\\');
	tokadd(c);
    }
    return 0;
}

extern int rb_char_to_option_kcode(int c, int *option, int *kcode);

static int
parser_regx_options(struct parser_params *parser)
{
    int kcode = 0;
    int options = 0;
    int c, opt, kc;

    newtok();
    while (c = nextc(), ISALPHA(c)) {
        if (c == 'o') {
            options |= RE_OPTION_ONCE;
        }
        else if (rb_char_to_option_kcode(c, &opt, &kc)) {
            options |= opt;
	    if (kc >= 0) kcode = c;
        }
        else {
	    tokadd(c);
        }
    }
    pushback(c);
    if (toklen()) {
	tokfix();
	compile_error(PARSER_ARG "unknown regexp option%s - %s",
		      toklen() > 1 ? "s" : "", tok());
    }
    return options | RE_OPTION_ENCODING(kcode);
}

static void
dispose_string(VALUE str)
{
    /* TODO: should use another API? */
    if (RBASIC(str)->flags & RSTRING_NOEMBED)
	xfree(RSTRING_PTR(str));
    rb_gc_force_recycle(str);
}

static int
parser_tokadd_mbchar(struct parser_params *parser, int c)
{
    int len = parser_precise_mbclen();
    if (!MBCLEN_CHARFOUND(len)) {
	compile_error(PARSER_ARG "invalid multibyte char");
	return -1;
    }
    tokadd(c);
    lex_p += --len;
    if (len > 0) tokcopy(len);
    return c;
}

#define tokadd_mbchar(c) parser_tokadd_mbchar(parser, c)

static int
parser_tokadd_string(struct parser_params *parser,
		     int func, int term, int paren, long *nest,
		     rb_encoding **encp)
{
    int c;
    int has_nonascii = 0;
    rb_encoding *enc = *encp;
    char *errbuf = 0;
    static const char mixed_msg[] = "%s mixed within %s source";

#define mixed_error(enc1, enc2) if (!errbuf) {	\
	int len = sizeof(mixed_msg) - 4;	\
	len += strlen(rb_enc_name(enc1));	\
	len += strlen(rb_enc_name(enc2));	\
	errbuf = ALLOCA_N(char, len);		\
	snprintf(errbuf, len, mixed_msg,	\
		 rb_enc_name(enc1),		\
		 rb_enc_name(enc2));		\
	yyerror(errbuf);			\
    }
#define mixed_escape(beg, enc1, enc2) do {	\
	const char *pos = lex_p;		\
	lex_p = beg;				\
	mixed_error(enc1, enc2);		\
	lex_p = pos;				\
    } while (0)

    while ((c = nextc()) != -1) {
	if (paren && c == paren) {
	    ++*nest;
	}
	else if (c == term) {
	    if (!nest || !*nest) {
		pushback(c);
		break;
	    }
	    --*nest;
	}
	else if ((func & STR_FUNC_EXPAND) && c == '#' && lex_p < lex_pend) {
	    int c2 = *lex_p;
	    if (c2 == '$' || c2 == '@' || c2 == '{') {
		pushback(c);
		break;
	    }
	}
	else if (c == '\\') {
	    const char *beg = lex_p - 1;
	    c = nextc();
	    switch (c) {
	      case '\n':
		if (func & STR_FUNC_QWORDS) break;
		if (func & STR_FUNC_EXPAND) continue;
		tokadd('\\');
		break;

	      case '\\':
		if (func & STR_FUNC_ESCAPE) tokadd(c);
		break;

	      case 'u':
		if ((func & STR_FUNC_EXPAND) == 0) {
		    tokadd('\\');
		    break;
		}
		parser_tokadd_utf8(parser, &enc, 1,
				   func & STR_FUNC_SYMBOL,
                                   func & STR_FUNC_REGEXP);
		if (has_nonascii && enc != *encp) {
		    mixed_escape(beg, enc, *encp);
		}
		continue;

	      default:
		if (func & STR_FUNC_REGEXP) {
		    pushback(c);
		    if ((c = tokadd_escape(term, &enc)) < 0)
			return -1;
		    if (has_nonascii && enc != *encp) {
			mixed_escape(beg, enc, *encp);
		    }
		    continue;
		}
		else if (func & STR_FUNC_EXPAND) {
		    pushback(c);
		    if (func & STR_FUNC_ESCAPE) tokadd('\\');
		    c = read_escape(0, &enc);
		}
		else if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
		    /* ignore backslashed spaces in %w */
		}
		else if (c != term && !(paren && c == paren)) {
		    tokadd('\\');
		}
	    }
	}
	else if (!parser_isascii()) {
	    has_nonascii = 1;
	    if (enc != *encp) {
		mixed_error(enc, *encp);
		continue;
	    }
	    if (tokadd_mbchar(c) == -1) return -1;
	    continue;
	}
	else if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
	    pushback(c);
	    break;
	}
	if (!c && (func & STR_FUNC_SYMBOL)) {
	    func &= ~STR_FUNC_SYMBOL;
	    compile_error(PARSER_ARG "symbol cannot contain '\\0'");
	    continue;
	}
        if (c & 0x80) {
            has_nonascii = 1;
	    if (enc != *encp) {
		mixed_error(enc, *encp);
		continue;
	    }
        }
	tokadd(c);
    }
    *encp = enc;
    return c;
}

#define NEW_STRTERM(func, term, paren) \
	rb_node_newnode(NODE_STRTERM, (func), (term) | ((paren) << (CHAR_BIT * 2)), 0)

static int
parser_parse_string(struct parser_params *parser, NODE *quote)
{
    int func = quote->nd_func;
    int term = nd_term(quote);
    int paren = nd_paren(quote);
    int c, space = 0;
    rb_encoding *enc = parser->enc;

    if (func == -1) return tSTRING_END;
    c = nextc();
    if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
	do {c = nextc();} while (ISSPACE(c));
	space = 1;
    }
    if (c == term && !quote->nd_nest) {
	if (func & STR_FUNC_QWORDS) {
	    quote->nd_func = -1;
	    return ' ';
	}
	if (!(func & STR_FUNC_REGEXP)) return tSTRING_END;
        set_yylval_num(regx_options());
	return tREGEXP_END;
    }
    if (space) {
	pushback(c);
	return ' ';
    }
    newtok();
    if ((func & STR_FUNC_EXPAND) && c == '#') {
	switch (c = nextc()) {
	  case '$':
	  case '@':
	    pushback(c);
	    return tSTRING_DVAR;
	  case '{':
	    return tSTRING_DBEG;
	}
	tokadd('#');
    }
    pushback(c);
    if (tokadd_string(func, term, paren, &quote->nd_nest,
		      &enc) == -1) {
	ruby_sourceline = nd_line(quote);
	if (func & STR_FUNC_REGEXP) {
	    if (parser->eofp)
		compile_error(PARSER_ARG "unterminated regexp meets end of file");
	    return tREGEXP_END;
	}
	else {
	    if (parser->eofp)
		compile_error(PARSER_ARG "unterminated string meets end of file");
	    return tSTRING_END;
	}
    }

    tokfix();
    set_yylval_str(STR_NEW3(tok(), toklen(), enc, func));
    return tSTRING_CONTENT;
}

static int
parser_heredoc_identifier(struct parser_params *parser)
{
    int c = nextc(), term, func = 0, len;

    if (c == '-') {
	c = nextc();
	func = STR_FUNC_INDENT;
    }
    switch (c) {
      case '\'':
	func |= str_squote; goto quoted;
      case '"':
	func |= str_dquote; goto quoted;
      case '`':
	func |= str_xquote;
      quoted:
	newtok();
	tokadd(func);
	term = c;
	while ((c = nextc()) != -1 && c != term) {
	    if (tokadd_mbchar(c) == -1) return 0;
	}
	if (c == -1) {
	    compile_error(PARSER_ARG "unterminated here document identifier");
	    return 0;
	}
	break;

      default:
	if (!parser_is_identchar()) {
	    pushback(c);
	    if (func & STR_FUNC_INDENT) {
		pushback('-');
	    }
	    return 0;
	}
	newtok();
	term = '"';
	tokadd(func |= str_dquote);
	do {
	    if (tokadd_mbchar(c) == -1) return 0;
	} while ((c = nextc()) != -1 && parser_is_identchar());
	pushback(c);
	break;
    }

    tokfix();
#ifdef RIPPER
    ripper_dispatch_scan_event(parser, tHEREDOC_BEG);
#endif
    len = lex_p - lex_pbeg;
    lex_goto_eol(parser);
    lex_strterm = rb_node_newnode(NODE_HEREDOC,
				  STR_NEW(tok(), toklen()),	/* nd_lit */
				  len,				/* nd_nth */
				  lex_lastline);		/* nd_orig */
    nd_set_line(lex_strterm, ruby_sourceline);
#ifdef RIPPER
    ripper_flush(parser);
#endif
    return term == '`' ? tXSTRING_BEG : tSTRING_BEG;
}

static void
parser_heredoc_restore(struct parser_params *parser, NODE *here)
{
    VALUE line;

#ifdef RIPPER
    if (!NIL_P(parser->delayed))
	ripper_dispatch_delayed_token(parser, tSTRING_CONTENT);
    lex_goto_eol(parser);
    ripper_dispatch_scan_event(parser, tHEREDOC_END);
#endif
    line = here->nd_orig;
    lex_lastline = line;
    lex_pbeg = RSTRING_PTR(line);
    lex_pend = lex_pbeg + RSTRING_LEN(line);
    lex_p = lex_pbeg + here->nd_nth;
    heredoc_end = ruby_sourceline;
    ruby_sourceline = nd_line(here);
    dispose_string(here->nd_lit);
    rb_gc_force_recycle((VALUE)here);
#ifdef RIPPER
    ripper_flush(parser);
#endif
}

static int
parser_whole_match_p(struct parser_params *parser,
    const char *eos, int len, int indent)
{
    const char *p = lex_pbeg;
    int n;

    if (indent) {
	while (*p && ISSPACE(*p)) p++;
    }
    n= lex_pend - (p + len);
    if (n < 0 || (n > 0 && p[len] != '\n' && p[len] != '\r')) return Qfalse;
    if (strncmp(eos, p, len) == 0) return Qtrue;
    return Qfalse;
}

static int
parser_here_document(struct parser_params *parser, NODE *here)
{
    int c, func, indent = 0;
    const char *eos, *p, *pend;
    long len;
    VALUE str = 0;

    eos = RSTRING_PTR(here->nd_lit);
    len = RSTRING_LEN(here->nd_lit) - 1;
    indent = (func = *eos++) & STR_FUNC_INDENT;

    if ((c = nextc()) == -1) {
      error:
	compile_error(PARSER_ARG "can't find string \"%s\" anywhere before EOF", eos);
      restore:
	heredoc_restore(lex_strterm);
	lex_strterm = 0;
	return 0;
    }
    if (was_bol() && whole_match_p(eos, len, indent)) {
	heredoc_restore(lex_strterm);
	return tSTRING_END;
    }

    if (!(func & STR_FUNC_EXPAND)) {
	do {
	    p = RSTRING_PTR(lex_lastline);
	    pend = lex_pend;
	    if (pend > p) {
		switch (pend[-1]) {
		  case '\n':
		    if (--pend == p || pend[-1] != '\r') {
			pend++;
			break;
		    }
		  case '\r':
		    --pend;
		}
	    }
	    if (str)
		rb_str_cat(str, p, pend - p);
	    else
		str = STR_NEW(p, pend - p);
	    if (pend < lex_pend) rb_str_cat(str, "\n", 1);
	    lex_goto_eol(parser);
	    if (nextc() == -1) {
		if (str) dispose_string(str);
		goto error;
	    }
	} while (!whole_match_p(eos, len, indent));
    }
    else {
	/*	int mb = ENC_CODERANGE_7BIT, *mbp = &mb;*/
	rb_encoding *enc = parser->enc;
	newtok();
	if (c == '#') {
	    switch (c = nextc()) {
	      case '$':
	      case '@':
		pushback(c);
		return tSTRING_DVAR;
	      case '{':
		return tSTRING_DBEG;
	    }
	    tokadd('#');
	}
	do {
	    pushback(c);
	    if ((c = tokadd_string(func, '\n', 0, NULL, &enc)) == -1) {
		if (parser->eofp) goto error;
		goto restore;
	    }
	    if (c != '\n') {
		set_yylval_str(STR_NEW3(tok(), toklen(), enc, func));
		return tSTRING_CONTENT;
	    }
	    tokadd(nextc());
	    /*	    if (mbp && mb == ENC_CODERANGE_UNKNOWN) mbp = 0;*/
	    if ((c = nextc()) == -1) goto error;
	} while (!whole_match_p(eos, len, indent));
	str = STR_NEW3(tok(), toklen(), enc, func);
    }
    heredoc_restore(lex_strterm);
    lex_strterm = NEW_STRTERM(-1, 0, 0);
    set_yylval_str(str);
    return tSTRING_CONTENT;
}

#include "lex.c"

#ifndef RIPPER
static void
arg_ambiguous_gen(struct parser_params *parser)
{
    rb_warning0("ambiguous first argument; put parentheses or even spaces");
}
#else
static void
arg_ambiguous_gen(struct parser_params *parser)
{
    dispatch0(arg_ambiguous);
}
#endif
#define arg_ambiguous() arg_ambiguous_gen(parser)

static int
lvar_defined_gen(struct parser_params *parser, ID id)
{
#ifndef RIPPER
    return (dyna_in_block() && dvar_defined(id)) || local_id(id);
#else
    return 0;
#endif
}

/* emacsen -*- hack */
static int
parser_encode_length(struct parser_params *parser, const char *name, int len)
{
    int nlen;

    if (len > 5 && name[nlen = len - 5] == '-') {
	if (rb_memcicmp(name + nlen + 1, "unix", 4) == 0)
	    return nlen;
    }
    if (len > 4 && name[nlen = len - 5] == '-') {
	if (rb_memcicmp(name + nlen + 1, "dos", 3) == 0)
	    return nlen;
	if (rb_memcicmp(name + nlen + 1, "mac", 3) == 0)
	    return nlen;
    }
    return len;
}

static void
parser_set_encode(struct parser_params *parser, const char *name)
{
    int idx = rb_enc_find_index(name);
    if (idx < 0) {
	rb_raise(rb_eArgError, "unknown encoding name: %s", name);
    }
    parser->enc = rb_enc_from_index(idx);
}

#ifndef RIPPER
typedef int (*rb_magic_comment_length_t)(struct parser_params *parser, const char *name, int len);
typedef void (*rb_magic_comment_setter_t)(struct parser_params *parser, const char *name, const char *val);

static void
magic_comment_encoding(struct parser_params *parser, const char *name, const char *val)
{
    if (parser && parser->line_count != (parser->has_shebang ? 2 : 1))
	return;
    parser_set_encode(parser, val);
}

struct magic_comment {
    const char *name;
    rb_magic_comment_setter_t func;
    rb_magic_comment_length_t length;
};

static const struct magic_comment magic_comments[] = {
    {"coding", magic_comment_encoding, parser_encode_length},
    {"encoding", magic_comment_encoding, parser_encode_length},
};
#endif

static const char *
magic_comment_marker(const char *str, int len)
{
    int i = 2;

    while (i < len) {
	switch (str[i]) {
	  case '-':
	    if (str[i-1] == '*' && str[i-2] == '-') {
		return str + i + 1;
	    }
	    i += 2;
	    break;
	  case '*':
	    if (i + 1 >= len) return 0;
	    if (str[i+1] != '-') {
		i += 4;
	    }
	    else if (str[i-1] != '-') {
		i += 2;
	    }
	    else {
		return str + i + 2;
	    }
	    break;
	  default:
	    i += 3;
	    break;
	}
    }
    return 0;
}

static int
parser_magic_comment(struct parser_params *parser, const char *str, int len)
{
    VALUE name = 0, val = 0;
    const char *beg, *end, *vbeg, *vend;
#define str_copy(_s, _p, _n) ((_s) \
	? (rb_str_resize((_s), (_n)), \
	   MEMCPY(RSTRING_PTR(_s), (_p), char, (_n)), (_s)) \
	: ((_s) = STR_NEW((_p), (_n))))

    if (len <= 7) return Qfalse;
    if (!(beg = magic_comment_marker(str, len))) return Qfalse;
    if (!(end = magic_comment_marker(beg, str + len - beg))) return Qfalse;
    str = beg;
    len = end - beg - 3;

    /* %r"([^\\s\'\":;]+)\\s*:\\s*(\"(?:\\\\.|[^\"])*\"|[^\"\\s;]+)[\\s;]*" */
    while (len > 0) {
#ifndef RIPPER
	const struct magic_comment *p = magic_comments;
#endif
	int n = 0;

	for (; len > 0 && *str; str++, --len) {
	    switch (*str) {
	      case '\'': case '"': case ':': case ';':
		continue;
	    }
	    if (!ISSPACE(*str)) break;
	}
	for (beg = str; len > 0; str++, --len) {
	    switch (*str) {
	      case '\'': case '"': case ':': case ';':
		break;
	      default:
		if (ISSPACE(*str)) break;
		continue;
	    }
	    break;
	}
	for (end = str; len > 0 && ISSPACE(*str); str++, --len);
	if (!len) break;
	if (*str != ':') continue;

	do str++; while (--len > 0 && ISSPACE(*str));
	if (!len) break;
	if (*str == '"') {
	    for (vbeg = ++str; --len > 0 && *str != '"'; str++) {
		if (*str == '\\') {
		    --len;
		    ++str;
		}
	    }
	    vend = str;
	    if (len) {
		--len;
		++str;
	    }
	}
	else {
	    for (vbeg = str; len > 0 && *str != '"' && *str != ';' && !ISSPACE(*str); --len, str++);
	    vend = str;
	}
	while (len > 0 && (*str == ';' || ISSPACE(*str))) --len, str++;

	n = end - beg;
	str_copy(name, beg, n);
#ifndef RIPPER
	do {
	    if (strncasecmp(p->name, RSTRING_PTR(name), n) == 0) {
		n = vend - vbeg;
		if (p->length) {
		    n = (*p->length)(parser, vbeg, n);
		}
		str_copy(val, vbeg, n);
		(*p->func)(parser, RSTRING_PTR(name), RSTRING_PTR(val));
		break;
	    }
	} while (++p < magic_comments + sizeof(magic_comments) / sizeof(*p));
#else
	dispatch2(magic_comment, name, val);
#endif
    }

    return Qtrue;
}

static void
set_file_encoding(struct parser_params *parser, const char *str, const char *send)
{
    int sep = 0;
    const char *beg = str;
    VALUE s;

    for (;;) {
	if (send - str <= 6) return;
	switch (str[6]) {
	  case 'C': case 'c': str += 6; continue;
	  case 'O': case 'o': str += 5; continue;
	  case 'D': case 'd': str += 4; continue;
	  case 'I': case 'i': str += 3; continue;
	  case 'N': case 'n': str += 2; continue;
	  case 'G': case 'g': str += 1; continue;
	  case '=': case ':':
	    sep = 1;
	    str += 6;
	    break;
	  default:
	    str += 6;
	    if (ISSPACE(*str)) break;
	    continue;
	}
	if (strncasecmp(str-6, "coding", 6) == 0) break;
    }
    for (;;) {
	do {
	    if (++str >= send) return;
	} while (ISSPACE(*str));
	if (sep) break;
	if (*str != '=' && *str != ':') return;
	sep = 1;
	str++;
    }
    beg = str;
    while ((*str == '-' || *str == '_' || ISALNUM(*str)) && ++str < send);
    s = rb_str_new(beg, parser_encode_length(parser, beg, str - beg));
    parser_set_encode(parser, RSTRING_PTR(s));
    rb_str_resize(s, 0);
}

static void
parser_prepare(struct parser_params *parser)
{
    int c = nextc();
    switch (c) {
      case '#':
	if (peek('!')) parser->has_shebang = 1;
	break;
      case 0xef:		/* UTF-8 BOM marker */
	if (lex_pend - lex_p >= 2 &&
	    (unsigned char)lex_p[0] == 0xbb &&
	    (unsigned char)lex_p[1] == 0xbf) {
	    parser_set_encode(parser, "UTF-8");
	    lex_p += 2;
	    lex_pbeg = lex_p;
	    return;
	}
	break;
      case EOF:
	return;
    }
    pushback(c);
}

#define IS_ARG() (lex_state == EXPR_ARG || lex_state == EXPR_CMDARG)
#define IS_BEG() (lex_state == EXPR_BEG || lex_state == EXPR_MID || lex_state == EXPR_VALUE || lex_state == EXPR_CLASS)

static int
parser_yylex(struct parser_params *parser)
{
    register int c;
    int space_seen = 0;
    int cmd_state;
    enum lex_state_e last_state;
    rb_encoding *enc;
    int mb;
#ifdef RIPPER
    int fallthru = Qfalse;
#endif

    if (lex_strterm) {
	int token;
	if (nd_type(lex_strterm) == NODE_HEREDOC) {
	    token = here_document(lex_strterm);
	    if (token == tSTRING_END) {
		lex_strterm = 0;
		lex_state = EXPR_ENDARG;
	    }
	}
	else {
	    token = parse_string(lex_strterm);
	    if (token == tSTRING_END || token == tREGEXP_END) {
		rb_gc_force_recycle((VALUE)lex_strterm);
		lex_strterm = 0;
		lex_state = EXPR_ENDARG;
	    }
	}
	return token;
    }
    cmd_state = command_start;
    command_start = Qfalse;
  retry:
    switch (c = nextc()) {
      case '\0':		/* NUL */
      case '\004':		/* ^D */
      case '\032':		/* ^Z */
      case -1:			/* end of script. */
	return 0;

	/* white spaces */
      case ' ': case '\t': case '\f': case '\r':
      case '\13': /* '\v' */
	space_seen++;
#ifdef RIPPER
	while ((c = nextc())) {
	    switch (c) {
	      case ' ': case '\t': case '\f': case '\r':
	      case '\13': /* '\v' */
		break;
	      default:
		goto outofloop;
	    }
	}
      outofloop:
	pushback(c);
	ripper_dispatch_scan_event(parser, tSP);
#endif
	goto retry;

      case '#':		/* it's a comment */
	if (!parser->has_shebang || parser->line_count != 1) {
	    /* no magic_comment in shebang line */
	    if (!parser_magic_comment(parser, lex_p, lex_pend - lex_p)) {
		if (parser->line_count == (parser->has_shebang ? 2 : 1)) {
		    set_file_encoding(parser, lex_p, lex_pend);
		}
	    }
	}
	lex_p = lex_pend;
#ifdef RIPPER
        ripper_dispatch_scan_event(parser, tCOMMENT);
        fallthru = Qtrue;
#endif
	/* fall through */
      case '\n':
	switch (lex_state) {
	  case EXPR_BEG:
	  case EXPR_FNAME:
	  case EXPR_DOT:
	  case EXPR_CLASS:
	  case EXPR_VALUE:
#ifdef RIPPER
            if (!fallthru) {
                ripper_dispatch_scan_event(parser, tIGNORED_NL);
            }
            fallthru = Qfalse;
#endif
	    goto retry;
	  default:
	    break;
	}
	while ((c = nextc())) {
	    switch (c) {
	      case ' ': case '\t': case '\f': case '\r':
	      case '\13': /* '\v' */
		space_seen++;
		break;
	      case '.': {
		  if ((c = nextc()) != '.') {
		      pushback(c);
		      pushback('.');
		    goto retry;
		  }
	      }
	      default:
		--ruby_sourceline;
	      case -1:		/* EOF no decrement*/
		lex_nextline = lex_lastline;
		lex_p = lex_pend;
#ifdef RIPPER
		if (c != -1) {
		    parser->tokp = lex_p;
		}
#endif
		goto normal_newline;
	    }
	}
      normal_newline:
	command_start = Qtrue;
	lex_state = EXPR_BEG;
	return '\n';

      case '*':
	if ((c = nextc()) == '*') {
	    if ((c = nextc()) == '=') {
                set_yylval_id(tPOW);
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    c = tPOW;
	}
	else {
	    if (c == '=') {
                set_yylval_id('*');
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    if (IS_ARG() && space_seen && !ISSPACE(c)) {
		rb_warning0("`*' interpreted as argument prefix");
		c = tSTAR;
	    }
	    else if (IS_BEG()) {
		c = tSTAR;
	    }
	    else {
		c = '*';
	    }
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	return c;

      case '!':
	c = nextc();
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	    if (c == '@') {
		return '!';
	    }
	}
	else {
	    lex_state = EXPR_BEG;
	}
	if (c == '=') {
	    return tNEQ;
	}
	if (c == '~') {
	    return tNMATCH;
	}
	pushback(c);
	return '!';

      case '=':
	if (was_bol()) {
	    /* skip embedded rd document */
	    if (strncmp(lex_p, "begin", 5) == 0 && ISSPACE(lex_p[5])) {
#ifdef RIPPER
                int first_p = Qtrue;

                lex_goto_eol(parser);
                ripper_dispatch_scan_event(parser, tEMBDOC_BEG);
#endif
		for (;;) {
		    lex_goto_eol(parser);
#ifdef RIPPER
                    if (!first_p) {
                        ripper_dispatch_scan_event(parser, tEMBDOC);
                    }
                    first_p = Qfalse;
#endif
		    c = nextc();
		    if (c == -1) {
			compile_error(PARSER_ARG "embedded document meets end of file");
			return 0;
		    }
		    if (c != '=') continue;
		    if (strncmp(lex_p, "end", 3) == 0 &&
			(lex_p + 3 == lex_pend || ISSPACE(lex_p[3]))) {
			break;
		    }
		}
		lex_goto_eol(parser);
#ifdef RIPPER
                ripper_dispatch_scan_event(parser, tEMBDOC_END);
#endif
		goto retry;
	    }
	}

	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	if ((c = nextc()) == '=') {
	    if ((c = nextc()) == '=') {
		return tEQQ;
	    }
	    pushback(c);
	    return tEQ;
	}
	if (c == '~') {
	    return tMATCH;
	}
	else if (c == '>') {
	    return tASSOC;
	}
	pushback(c);
	return '=';

      case '<':
	c = nextc();
	if (c == '<' &&
	    lex_state != EXPR_END &&
	    lex_state != EXPR_DOT &&
	    lex_state != EXPR_ENDARG &&
	    lex_state != EXPR_CLASS &&
	    (!IS_ARG() || space_seen)) {
	    int token = heredoc_identifier();
	    if (token) return token;
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	if (c == '=') {
	    if ((c = nextc()) == '>') {
		return tCMP;
	    }
	    pushback(c);
	    return tLEQ;
	}
	if (c == '<') {
	    if ((c = nextc()) == '=') {
                set_yylval_id(tLSHFT);
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tLSHFT;
	}
	pushback(c);
	return '<';

      case '>':
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	if ((c = nextc()) == '=') {
	    return tGEQ;
	}
	if (c == '>') {
	    if ((c = nextc()) == '=') {
                set_yylval_id(tRSHFT);
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tRSHFT;
	}
	pushback(c);
	return '>';

      case '"':
	lex_strterm = NEW_STRTERM(str_dquote, '"', 0);
	return tSTRING_BEG;

      case '`':
	if (lex_state == EXPR_FNAME) {
	    lex_state = EXPR_END;
	    return c;
	}
	if (lex_state == EXPR_DOT) {
	    if (cmd_state)
		lex_state = EXPR_CMDARG;
	    else
		lex_state = EXPR_ARG;
	    return c;
	}
	lex_strterm = NEW_STRTERM(str_xquote, '`', 0);
	return tXSTRING_BEG;

      case '\'':
	lex_strterm = NEW_STRTERM(str_squote, '\'', 0);
	return tSTRING_BEG;

      case '?':
	if (lex_state == EXPR_END ||
	    lex_state == EXPR_ENDARG) {
	    lex_state = EXPR_VALUE;
	    return '?';
	}
	c = nextc();
	if (c == -1) {
	    compile_error(PARSER_ARG "incomplete character syntax");
	    return 0;
	}
	if (rb_enc_isspace(c, parser->enc)) {
	    if (!IS_ARG()) {
		int c2 = 0;
		switch (c) {
		  case ' ':
		    c2 = 's';
		    break;
		  case '\n':
		    c2 = 'n';
		    break;
		  case '\t':
		    c2 = 't';
		    break;
		  case '\v':
		    c2 = 'v';
		    break;
		  case '\r':
		    c2 = 'r';
		    break;
		  case '\f':
		    c2 = 'f';
		    break;
		}
		if (c2) {
		    rb_warnI("invalid character syntax; use ?\\%c", c2);
		}
	    }
	  ternary:
	    pushback(c);
	    lex_state = EXPR_VALUE;
	    return '?';
	}
	newtok();
	enc = parser->enc;
	if (!parser_isascii()) {
	    if (tokadd_mbchar(c) == -1) return 0;
	}
	else if ((rb_enc_isalnum(c, parser->enc) || c == '_') &&
		 lex_p < lex_pend && is_identchar(lex_p, lex_pend, parser->enc)) {
	    goto ternary;
	}
        else if (c == '\\') {
            if (peek('u')) {
                nextc();
                c = parser_tokadd_utf8(parser, &enc, 0, 0, 0);
                if (0x80 <= c) {
                    tokaddmbc(c, enc);
                }
                else {
                    tokadd(c);
                }
            }
            else {
                c = read_escape(0, &enc);
                tokadd(c);
            }
        }
        else {
	    tokadd(c);
        }
	tokfix();
	set_yylval_str(STR_NEW3(tok(), toklen(), enc, 0));
	lex_state = EXPR_ENDARG;
	return tCHAR;

      case '&':
	if ((c = nextc()) == '&') {
	    lex_state = EXPR_BEG;
	    if ((c = nextc()) == '=') {
                set_yylval_id(tANDOP);
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tANDOP;
	}
	else if (c == '=') {
            set_yylval_id('&');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	pushback(c);
	if (IS_ARG() && space_seen && !ISSPACE(c)) {
	    rb_warning0("`&' interpreted as argument prefix");
	    c = tAMPER;
	}
	else if (IS_BEG()) {
	    c = tAMPER;
	}
	else {
	    c = '&';
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG;
	}
	return c;

      case '|':
	if ((c = nextc()) == '|') {
	    lex_state = EXPR_BEG;
	    if ((c = nextc()) == '=') {
                set_yylval_id(tOROP);
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tOROP;
	}
	if (c == '=') {
            set_yylval_id('|');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	}
	else {
	    lex_state = EXPR_BEG;
	}
	pushback(c);
	return '|';

      case '+':
	c = nextc();
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	    if (c == '@') {
		return tUPLUS;
	    }
	    pushback(c);
	    return '+';
	}
	if (c == '=') {
            set_yylval_id('+');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (IS_BEG() ||
	    (IS_ARG() && space_seen && !ISSPACE(c))) {
	    if (IS_ARG()) arg_ambiguous();
	    lex_state = EXPR_BEG;
	    pushback(c);
	    if (ISDIGIT(c)) {
		c = '+';
		goto start_num;
	    }
	    return tUPLUS;
	}
	lex_state = EXPR_BEG;
	pushback(c);
	return '+';

      case '-':
	c = nextc();
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	    if (c == '@') {
		return tUMINUS;
	    }
	    pushback(c);
	    return '-';
	}
	if (c == '=') {
            set_yylval_id('-');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (c == '>') {
	    lex_state = EXPR_ARG;
	    return tLAMBDA;
	}
	if (IS_BEG() ||
	    (IS_ARG() && space_seen && !ISSPACE(c))) {
	    if (IS_ARG()) arg_ambiguous();
	    lex_state = EXPR_BEG;
	    pushback(c);
	    if (ISDIGIT(c)) {
		return tUMINUS_NUM;
	    }
	    return tUMINUS;
	}
	lex_state = EXPR_BEG;
	pushback(c);
	return '-';

      case '.':
	lex_state = EXPR_BEG;
	if ((c = nextc()) == '.') {
	    if ((c = nextc()) == '.') {
		return tDOT3;
	    }
	    pushback(c);
	    return tDOT2;
	}
	pushback(c);
	if (ISDIGIT(c)) {
	    yyerror("no .<digit> floating literal anymore; put 0 before dot");
	}
	lex_state = EXPR_DOT;
	return '.';

      start_num:
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
	{
	    int is_float, seen_point, seen_e, nondigit;

	    is_float = seen_point = seen_e = nondigit = 0;
	    lex_state = EXPR_ENDARG;
	    newtok();
	    if (c == '-' || c == '+') {
		tokadd(c);
		c = nextc();
	    }
	    if (c == '0') {
		int start = toklen();
		c = nextc();
		if (c == 'x' || c == 'X') {
		    /* hexadecimal */
		    c = nextc();
		    if (ISXDIGIT(c)) {
			do {
			    if (c == '_') {
				if (nondigit) break;
				nondigit = c;
				continue;
			    }
			    if (!ISXDIGIT(c)) break;
			    nondigit = 0;
			    tokadd(c);
			} while ((c = nextc()) != -1);
		    }
		    pushback(c);
		    tokfix();
		    if (toklen() == start) {
			yyerror("numeric literal without digits");
		    }
		    else if (nondigit) goto trailing_uc;
                    set_yylval_literal(rb_cstr_to_inum(tok(), 16, Qfalse));
		    return tINTEGER;
		}
		if (c == 'b' || c == 'B') {
		    /* binary */
		    c = nextc();
		    if (c == '0' || c == '1') {
			do {
			    if (c == '_') {
				if (nondigit) break;
				nondigit = c;
				continue;
			    }
			    if (c != '0' && c != '1') break;
			    nondigit = 0;
			    tokadd(c);
			} while ((c = nextc()) != -1);
		    }
		    pushback(c);
		    tokfix();
		    if (toklen() == start) {
			yyerror("numeric literal without digits");
		    }
		    else if (nondigit) goto trailing_uc;
                    set_yylval_literal(rb_cstr_to_inum(tok(), 2, Qfalse));
		    return tINTEGER;
		}
		if (c == 'd' || c == 'D') {
		    /* decimal */
		    c = nextc();
		    if (ISDIGIT(c)) {
			do {
			    if (c == '_') {
				if (nondigit) break;
				nondigit = c;
				continue;
			    }
			    if (!ISDIGIT(c)) break;
			    nondigit = 0;
			    tokadd(c);
			} while ((c = nextc()) != -1);
		    }
		    pushback(c);
		    tokfix();
		    if (toklen() == start) {
			yyerror("numeric literal without digits");
		    }
		    else if (nondigit) goto trailing_uc;
                    set_yylval_literal(rb_cstr_to_inum(tok(), 10, Qfalse));
		    return tINTEGER;
		}
		if (c == '_') {
		    /* 0_0 */
		    goto octal_number;
		}
		if (c == 'o' || c == 'O') {
		    /* prefixed octal */
		    c = nextc();
		    if (c == '_') {
			yyerror("numeric literal without digits");
		    }
		}
		if (c >= '0' && c <= '7') {
		    /* octal */
		  octal_number:
	            do {
			if (c == '_') {
			    if (nondigit) break;
			    nondigit = c;
			    continue;
			}
			if (c < '0' || c > '7') break;
			nondigit = 0;
			tokadd(c);
		    } while ((c = nextc()) != -1);
		    if (toklen() > start) {
			pushback(c);
			tokfix();
			if (nondigit) goto trailing_uc;
                        set_yylval_literal(rb_cstr_to_inum(tok(), 8, Qfalse));
			return tINTEGER;
		    }
		    if (nondigit) {
			pushback(c);
			goto trailing_uc;
		    }
		}
		if (c > '7' && c <= '9') {
		    yyerror("Illegal octal digit");
		}
		else if (c == '.' || c == 'e' || c == 'E') {
		    tokadd('0');
		}
		else {
		    pushback(c);
                    set_yylval_literal(INT2FIX(0));
		    return tINTEGER;
		}
	    }

	    for (;;) {
		switch (c) {
		  case '0': case '1': case '2': case '3': case '4':
		  case '5': case '6': case '7': case '8': case '9':
		    nondigit = 0;
		    tokadd(c);
		    break;

		  case '.':
		    if (nondigit) goto trailing_uc;
		    if (seen_point || seen_e) {
			goto decode_num;
		    }
		    else {
			int c0 = nextc();
			if (!ISDIGIT(c0)) {
			    pushback(c0);
			    goto decode_num;
			}
			c = c0;
		    }
		    tokadd('.');
		    tokadd(c);
		    is_float++;
		    seen_point++;
		    nondigit = 0;
		    break;

		  case 'e':
		  case 'E':
		    if (nondigit) {
			pushback(c);
			c = nondigit;
			goto decode_num;
		    }
		    if (seen_e) {
			goto decode_num;
		    }
		    tokadd(c);
		    seen_e++;
		    is_float++;
		    nondigit = c;
		    c = nextc();
		    if (c != '-' && c != '+') continue;
		    tokadd(c);
		    nondigit = c;
		    break;

		  case '_':	/* `_' in number just ignored */
		    if (nondigit) goto decode_num;
		    nondigit = c;
		    break;

		  default:
		    goto decode_num;
		}
		c = nextc();
	    }

	  decode_num:
	    pushback(c);
	    tokfix();
	    if (nondigit) {
		char tmp[30];
	      trailing_uc:
		sprintf(tmp, "trailing `%c' in number", nondigit);
		yyerror(tmp);
	    }
	    if (is_float) {
		double d = strtod(tok(), 0);
		if (errno == ERANGE) {
		    rb_warnS("Float %s out of range", tok());
		    errno = 0;
		}
                set_yylval_literal(DOUBLE2NUM(d));
		return tFLOAT;
	    }
            set_yylval_literal(rb_cstr_to_inum(tok(), 10, Qfalse));
	    return tINTEGER;
	}

      case ')':
      case ']':
	paren_nest--;
      case '}':
	COND_LEXPOP();
	CMDARG_LEXPOP();
	if (c == ')')
	    lex_state = EXPR_END;
	else
	    lex_state = EXPR_ENDARG;
	return c;

      case ':':
	c = nextc();
	if (c == ':') {
	    if (IS_BEG() ||
		lex_state == EXPR_CLASS || (IS_ARG() && space_seen)) {
		lex_state = EXPR_BEG;
		return tCOLON3;
	    }
	    lex_state = EXPR_DOT;
	    return tCOLON2;
	}
	if (lex_state == EXPR_END ||
	    lex_state == EXPR_ENDARG || ISSPACE(c)) {
	    pushback(c);
	    lex_state = EXPR_BEG;
	    return ':';
	}
	switch (c) {
	  case '\'':
	    lex_strterm = NEW_STRTERM(str_ssym, c, 0);
	    break;
	  case '"':
	    lex_strterm = NEW_STRTERM(str_dsym, c, 0);
	    break;
	  default:
	    pushback(c);
	    break;
	}
	lex_state = EXPR_FNAME;
	return tSYMBEG;

      case '/':
	if (IS_BEG()) {
	    lex_strterm = NEW_STRTERM(str_regexp, '/', 0);
	    return tREGEXP_BEG;
	}
	if ((c = nextc()) == '=') {
            set_yylval_id('/');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	pushback(c);
	if (IS_ARG() && space_seen) {
	    if (!ISSPACE(c)) {
		arg_ambiguous();
		lex_strterm = NEW_STRTERM(str_regexp, '/', 0);
		return tREGEXP_BEG;
	    }
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	return '/';

      case '^':
	if ((c = nextc()) == '=') {
            set_yylval_id('^');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	pushback(c);
	return '^';

      case ';':
	lex_state = EXPR_BEG;
	command_start = Qtrue;
	return ';';

      case ',':
	lex_state = EXPR_BEG;
	return ',';

      case '~':
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    if ((c = nextc()) != '@') {
		pushback(c);
	    }
	    lex_state = EXPR_ARG;
	}
	else {
	    lex_state = EXPR_BEG;
	}
	return '~';

      case '(':
	if (IS_BEG()) {
	    c = tLPAREN;
	}
	else if (space_seen) {
	    if (lex_state == EXPR_CMDARG) {
		c = tLPAREN_ARG;
	    }
	    else if (lex_state == EXPR_ARG) {
		rb_warning0("don't put space before argument parentheses");
		c = '(';
	    }
	}
	paren_nest++;
	COND_PUSH(0);
	CMDARG_PUSH(0);
	lex_state = EXPR_BEG;
	return c;

      case '[':
	paren_nest++;
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	    if ((c = nextc()) == ']') {
		if ((c = nextc()) == '=') {
		    return tASET;
		}
		pushback(c);
		return tAREF;
	    }
	    pushback(c);
	    return '[';
	}
	else if (IS_BEG()) {
	    c = tLBRACK;
	}
	else if (IS_ARG() && space_seen) {
	    c = tLBRACK;
	}
	lex_state = EXPR_BEG;
	COND_PUSH(0);
	CMDARG_PUSH(0);
	return c;

      case '{':
	if (lpar_beg && lpar_beg == paren_nest) {
	    lex_state = EXPR_BEG;
	    lpar_beg = 0;
	    --paren_nest;
	    return tLAMBEG;
	}
	if (IS_ARG() || lex_state == EXPR_END)
	    c = '{';          /* block (primary) */
	else if (lex_state == EXPR_ENDARG)
	    c = tLBRACE_ARG;  /* block (expr) */
	else
	    c = tLBRACE;      /* hash */
	COND_PUSH(0);
	CMDARG_PUSH(0);
	lex_state = EXPR_BEG;
	if (c != tLBRACE) command_start = Qtrue;
	return c;

      case '\\':
	c = nextc();
	if (c == '\n') {
	    space_seen = 1;
#ifdef RIPPER
	    ripper_dispatch_scan_event(parser, tSP);
#endif
	    goto retry; /* skip \\n */
	}
	pushback(c);
	return '\\';

      case '%':
	if (IS_BEG()) {
	    int term;
	    int paren;

	    c = nextc();
	  quotation:
	    if (!ISALNUM(c)) {
		term = c;
		c = 'Q';
	    }
	    else {
		term = nextc();
		if (rb_enc_isalnum(term, parser->enc) || !parser_isascii()) {
		    yyerror("unknown type of %string");
		    return 0;
		}
	    }
	    if (c == -1 || term == -1) {
		compile_error(PARSER_ARG "unterminated quoted string meets end of file");
		return 0;
	    }
	    paren = term;
	    if (term == '(') term = ')';
	    else if (term == '[') term = ']';
	    else if (term == '{') term = '}';
	    else if (term == '<') term = '>';
	    else paren = 0;

	    switch (c) {
	      case 'Q':
		lex_strterm = NEW_STRTERM(str_dquote, term, paren);
		return tSTRING_BEG;

	      case 'q':
		lex_strterm = NEW_STRTERM(str_squote, term, paren);
		return tSTRING_BEG;

	      case 'W':
		lex_strterm = NEW_STRTERM(str_dword, term, paren);
		do {c = nextc();} while (ISSPACE(c));
		pushback(c);
		return tWORDS_BEG;

	      case 'w':
		lex_strterm = NEW_STRTERM(str_sword, term, paren);
		do {c = nextc();} while (ISSPACE(c));
		pushback(c);
		return tQWORDS_BEG;

	      case 'x':
		lex_strterm = NEW_STRTERM(str_xquote, term, paren);
		return tXSTRING_BEG;

	      case 'r':
		lex_strterm = NEW_STRTERM(str_regexp, term, paren);
		return tREGEXP_BEG;

	      case 's':
		lex_strterm = NEW_STRTERM(str_ssym, term, paren);
		lex_state = EXPR_FNAME;
		return tSYMBEG;

	      default:
		yyerror("unknown type of %string");
		return 0;
	    }
	}
	if ((c = nextc()) == '=') {
            set_yylval_id('%');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (IS_ARG() && space_seen && !ISSPACE(c)) {
	    goto quotation;
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	pushback(c);
	return '%';

      case '$':
	last_state = lex_state;
	lex_state = EXPR_ENDARG;
	newtok();
	c = nextc();
	switch (c) {
	  case '_':		/* $_: last read line string */
	    c = nextc();
	    if (parser_is_identchar()) {
		tokadd('$');
		tokadd('_');
		break;
	    }
	    pushback(c);
	    c = '_';
	    /* fall through */
	  case '~':		/* $~: match-data */
	  case '*':		/* $*: argv */
	  case '$':		/* $$: pid */
	  case '?':		/* $?: last status */
	  case '!':		/* $!: error string */
	  case '@':		/* $@: error position */
	  case '/':		/* $/: input record separator */
	  case '\\':		/* $\: output record separator */
	  case ';':		/* $;: field separator */
	  case ',':		/* $,: output field separator */
	  case '.':		/* $.: last read line number */
	  case '=':		/* $=: ignorecase */
	  case ':':		/* $:: load path */
	  case '<':		/* $<: reading filename */
	  case '>':		/* $>: default output handle */
	  case '\"':		/* $": already loaded files */
	    tokadd('$');
	    tokadd(c);
	    tokfix();
            set_yylval_id(rb_intern(tok()));
	    return tGVAR;

	  case '-':
	    tokadd('$');
	    tokadd(c);
	    c = nextc();
	    if (parser_is_identchar()) {
		if (tokadd_mbchar(c) == -1) return 0;
	    }
	    else {
		pushback(c);
	    }
	  gvar:
	    tokfix();
            set_yylval_id(rb_intern(tok()));
	    return tGVAR;

	  case '&':		/* $&: last match */
	  case '`':		/* $`: string before last match */
	  case '\'':		/* $': string after last match */
	  case '+':		/* $+: string matches last paren. */
	    if (last_state == EXPR_FNAME) {
		tokadd('$');
		tokadd(c);
		goto gvar;
	    }
	    set_yylval_node(NEW_BACK_REF(c));
	    return tBACK_REF;

	  case '1': case '2': case '3':
	  case '4': case '5': case '6':
	  case '7': case '8': case '9':
	    tokadd('$');
	    do {
		tokadd(c);
		c = nextc();
	    } while (ISDIGIT(c));
	    pushback(c);
	    if (last_state == EXPR_FNAME) goto gvar;
	    tokfix();
	    set_yylval_node(NEW_NTH_REF(atoi(tok()+1)));
	    return tNTH_REF;

	  default:
	    if (!parser_is_identchar()) {
		pushback(c);
		return '$';
	    }
	  case '0':
	    tokadd('$');
	}
	break;

      case '@':
	c = nextc();
	newtok();
	tokadd('@');
	if (c == '@') {
	    tokadd('@');
	    c = nextc();
	}
	if (ISDIGIT(c)) {
	    if (tokidx == 1) {
		compile_error(PARSER_ARG "`@%c' is not allowed as an instance variable name", c);
	    }
	    else {
		compile_error(PARSER_ARG "`@@%c' is not allowed as a class variable name", c);
	    }
	    return 0;
	}
	if (!parser_is_identchar()) {
	    pushback(c);
	    return '@';
	}
	break;

      case '_':
	if (was_bol() && whole_match_p("__END__", 7, 0)) {
	    ruby__end__seen = 1;
	    lex_lastline = 0;
#ifndef RIPPER
	    return -1;
#else
            lex_goto_eol(parser);
            ripper_dispatch_scan_event(parser, k__END__);
            return 0;
#endif
	}
	newtok();
	break;

      default:
	if (!parser_is_identchar()) {
	    rb_compile_error(PARSER_ARG  "Invalid char `\\x%02X' in expression", c);
	    goto retry;
	}

	newtok();
	break;
    }

    mb = ENC_CODERANGE_7BIT;
    do {
	if (!ISASCII(c)) mb = ENC_CODERANGE_UNKNOWN;
	if (tokadd_mbchar(c) == -1) return 0;
	c = nextc();
    } while (parser_is_identchar());
    if ((c == '!' || c == '?') && !peek('=')) {
	tokadd(c);
    }
    else {
	pushback(c);
    }
    tokfix();

    {
	int result = 0;

	last_state = lex_state;
	switch (tok()[0]) {
	  case '$':
	    lex_state = EXPR_ENDARG;
	    result = tGVAR;
	    break;
	  case '@':
	    lex_state = EXPR_ENDARG;
	    if (tok()[1] == '@')
		result = tCVAR;
	    else
		result = tIVAR;
	    break;

	  default:
	    if (toklast() == '!' || toklast() == '?') {
		result = tFID;
	    }
	    else {
		if (lex_state == EXPR_FNAME) {
		    if ((c = nextc()) == '=' && !peek('~') && !peek('>') &&
			(!peek('=') || (lex_p + 1 < lex_pend && lex_p[1] == '>'))) {
			result = tIDENTIFIER;
			tokadd(c);
			tokfix();
		    }
		    else {
			pushback(c);
		    }
		}
		if (result == 0 && ISUPPER(tok()[0])) {
		    result = tCONSTANT;
		}
		else {
		    result = tIDENTIFIER;
		}
	    }

	    if (mb == ENC_CODERANGE_7BIT && lex_state != EXPR_DOT) {
		const struct kwtable *kw;

		/* See if it is a reserved word.  */
		kw = rb_reserved_word(tok(), toklen());
		if (kw) {
		    enum lex_state_e state = lex_state;
		    lex_state = kw->state;
		    if (state == EXPR_FNAME) {
                        set_yylval_id(rb_intern(kw->name));
			return kw->id[0];
		    }
		    if (kw->id[0] == keyword_do) {
			command_start = Qtrue;
			if (lpar_beg && lpar_beg == paren_nest) {
			    lpar_beg = 0;
			    --paren_nest;
			    return keyword_do_LAMBDA;
			}
			if (COND_P()) return keyword_do_cond;
			if (CMDARG_P() && state != EXPR_CMDARG)
			    return keyword_do_block;
			if (state == EXPR_ENDARG || state == EXPR_BEG)
			    return keyword_do_block;
			return keyword_do;
		    }
		    if (state == EXPR_BEG || state == EXPR_VALUE)
			return kw->id[0];
		    else {
			if (kw->id[0] != kw->id[1])
			    lex_state = EXPR_BEG;
			return kw->id[1];
		    }
		}
	    }

	    if ((lex_state == EXPR_BEG && !cmd_state) ||
		lex_state == EXPR_ARG ||
		lex_state == EXPR_CMDARG) {
		if (peek(':') && !(lex_p + 1 < lex_pend && lex_p[1] == ':')) {
		    lex_state = EXPR_BEG;
		    nextc();
		    set_yylval_id(TOK_INTERN(!ENC_SINGLE(mb)));
		    return tLABEL;
		}
	    }
	    if (IS_BEG() ||
		lex_state == EXPR_DOT ||
		IS_ARG()) {
		if (cmd_state) {
		    lex_state = EXPR_CMDARG;
		}
		else {
		    lex_state = EXPR_ARG;
		}
	    }
	    else {
		lex_state = EXPR_END;
	    }
	}
        {
            ID ident = TOK_INTERN(!ENC_SINGLE(mb));

            set_yylval_id(ident);
            if (last_state != EXPR_DOT && is_local_id(ident) && lvar_defined(ident)) {
                lex_state = EXPR_END;
            }
        }
	return result;
    }
}

#if YYPURE
static int
yylex(void *lval, void *p)
#else
yylex(void *p)
#endif
{
    struct parser_params *parser = (struct parser_params*)p;
    int t;

#if YYPURE
    parser->parser_yylval = (union tmpyystype*)lval;
    parser->parser_yylval->val = Qundef;
#endif
    t = parser_yylex(parser);
#ifdef RIPPER
    if (!NIL_P(parser->delayed)) {
	ripper_dispatch_delayed_token(parser, t);
	return t;
    }
    if (t != 0)
	ripper_dispatch_scan_event(parser, t);
#endif

    return t;
}

#ifndef RIPPER
static NODE*
node_newnode(struct parser_params *parser, enum node_type type, VALUE a0, VALUE a1, VALUE a2)
{
    NODE *n = (rb_node_newnode)(type, a0, a1, a2);
    nd_set_line(n, ruby_sourceline);
    n->nd_file = ruby_sourcefile;
    return n;
}

enum node_type
nodetype(NODE *node)			/* for debug */
{
    return (enum node_type)nd_type(node);
}

int
nodeline(NODE *node)
{
    return nd_line(node);
}

static NODE*
newline_node(NODE *node)
{
    if (node) {
	node = remove_begin(node);
	node->flags |= NODE_NEWLINE;
    }
    return node;
}

static void
fixpos(NODE *node, NODE *orig)
{
    if (!node) return;
    if (!orig) return;
    if (orig == (NODE*)1) return;
    node->nd_file = orig->nd_file;
    nd_set_line(node, nd_line(orig));
}

static void
parser_warning(NODE *node, const char *mesg)
{
    rb_compile_warning(node->nd_file, nd_line(node), "%s", mesg);
}

static void
parser_warn(NODE *node, const char *mesg)
{
    rb_compile_warn(node->nd_file, nd_line(node), "%s", mesg);
}

static NODE*
block_append_gen(struct parser_params *parser, NODE *head, NODE *tail)
{
    NODE *end, *h = head, *nd;

    if (tail == 0) return head;

    if (h == 0) return tail;
    switch (nd_type(h)) {
      case NODE_LIT:
      case NODE_STR:
      case NODE_SELF:
      case NODE_TRUE:
      case NODE_FALSE:
      case NODE_NIL:
	parser_warning(h, "unused literal ignored");
	return tail;
      default:
	h = end = NEW_BLOCK(head);
	end->nd_end = end;
	fixpos(end, head);
	head = end;
	break;
      case NODE_BLOCK:
	end = h->nd_end;
	break;
    }

    nd = end->nd_head;
    switch (nd_type(nd)) {
      case NODE_RETURN:
      case NODE_BREAK:
      case NODE_NEXT:
      case NODE_REDO:
      case NODE_RETRY:
	if (RTEST(ruby_verbose)) {
	    parser_warning(nd, "statement not reached");
	}
	break;

      default:
	break;
    }

    if (nd_type(tail) != NODE_BLOCK) {
	tail = NEW_BLOCK(tail);
	tail->nd_end = tail;
    }
    end->nd_next = tail;
    h->nd_end = tail->nd_end;
    return head;
}

/* append item to the list */
static NODE*
list_append_gen(struct parser_params *parser, NODE *list, NODE *item)
{
    NODE *last;

    if (list == 0) return NEW_LIST(item);
    if (list->nd_next) {
	last = list->nd_next->nd_end;
    }
    else {
	last = list;
    }

    list->nd_alen += 1;
    last->nd_next = NEW_LIST(item);
    list->nd_next->nd_end = last->nd_next;
    return list;
}

/* concat two lists */
static NODE*
list_concat_gen(struct parser_params *parser, NODE *head, NODE *tail)
{
    NODE *last;

    if (head->nd_next) {
	last = head->nd_next->nd_end;
    }
    else {
	last = head;
    }

    head->nd_alen += tail->nd_alen;
    last->nd_next = tail;
    if (tail->nd_next) {
	head->nd_next->nd_end = tail->nd_next->nd_end;
    }
    else {
	head->nd_next->nd_end = tail;
    }

    return head;
}

static void
literal_concat0(struct parser_params *parser, VALUE head, VALUE tail)
{
    if (!rb_enc_compatible(head, tail)) {
	compile_error(PARSER_ARG "string literal encodings differ (%s / %s)",
		      rb_enc_name(rb_enc_get(head)),
		      rb_enc_name(rb_enc_get(tail)));
    }
    rb_str_buf_append(head, tail);
}

/* concat two string literals */
static NODE *
literal_concat_gen(struct parser_params *parser, NODE *head, NODE *tail)
{
    enum node_type htype;

    if (!head) return tail;
    if (!tail) return head;

    htype = nd_type(head);
    if (htype == NODE_EVSTR) {
	NODE *node = NEW_DSTR(rb_str_new(0, 0));
	head = list_append(node, head);
    }
    switch (nd_type(tail)) {
      case NODE_STR:
	if (htype == NODE_STR) {
	    literal_concat0(parser, head->nd_lit, tail->nd_lit);
	    rb_gc_force_recycle((VALUE)tail);
	}
	else {
	    list_append(head, tail);
	}
	break;

      case NODE_DSTR:
	if (htype == NODE_STR) {
	    literal_concat0(parser, head->nd_lit, tail->nd_lit);
	    tail->nd_lit = head->nd_lit;
	    rb_gc_force_recycle((VALUE)head);
	    head = tail;
	}
	else {
	    nd_set_type(tail, NODE_ARRAY);
	    tail->nd_head = NEW_STR(tail->nd_lit);
	    list_concat(head, tail);
	}
	break;

      case NODE_EVSTR:
	if (htype == NODE_STR) {
	    nd_set_type(head, NODE_DSTR);
	    head->nd_alen = 1;
	}
	list_append(head, tail);
	break;
    }
    return head;
}

static NODE *
evstr2dstr_gen(struct parser_params *parser, NODE *node)
{
    if (nd_type(node) == NODE_EVSTR) {
	node = list_append(NEW_DSTR(rb_str_new(0, 0)), node);
    }
    return node;
}

static NODE *
new_evstr_gen(struct parser_params *parser, NODE *node)
{
    NODE *head = node;

    if (node) {
	switch (nd_type(node)) {
	  case NODE_STR: case NODE_DSTR: case NODE_EVSTR:
	    return node;
	}
    }
    return NEW_EVSTR(head);
}

static NODE *
call_bin_op_gen(struct parser_params *parser, NODE *recv, ID id, NODE *arg1)
{
    value_expr(recv);
    value_expr(arg1);
    return NEW_CALL(recv, id, NEW_LIST(arg1));
}

static NODE *
call_uni_op_gen(struct parser_params *parser, NODE *recv, ID id)
{
    value_expr(recv);
    return NEW_CALL(recv, id, 0);
}

static NODE*
match_op_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    value_expr(node1);
    value_expr(node2);
    if (node1) {
	switch (nd_type(node1)) {
	  case NODE_DREGX:
	  case NODE_DREGX_ONCE:
	    return NEW_MATCH2(node1, node2);

	  case NODE_LIT:
	    if (TYPE(node1->nd_lit) == T_REGEXP) {
		return NEW_MATCH2(node1, node2);
	    }
	}
    }

    if (node2) {
	switch (nd_type(node2)) {
	  case NODE_DREGX:
	  case NODE_DREGX_ONCE:
	    return NEW_MATCH3(node2, node1);

	  case NODE_LIT:
	    if (TYPE(node2->nd_lit) == T_REGEXP) {
		return NEW_MATCH3(node2, node1);
	    }
	}
    }

    return NEW_CALL(node1, tMATCH, NEW_LIST(node2));
}

static NODE*
gettable_gen(struct parser_params *parser, ID id)
{
    if (id == keyword_self) {
	return NEW_SELF();
    }
    else if (id == keyword_nil) {
	return NEW_NIL();
    }
    else if (id == keyword_true) {
	return NEW_TRUE();
    }
    else if (id == keyword_false) {
	return NEW_FALSE();
    }
    else if (id == keyword__FILE__) {
	return NEW_STR(STR_NEW2(ruby_sourcefile));
    }
    else if (id == keyword__LINE__) {
	return NEW_LIT(INT2FIX(ruby_sourceline));
    }
    else if (id == keyword__ENCODING__) {
	return NEW_LIT(rb_enc_from_encoding(parser->enc));
    }
    else if (is_local_id(id)) {
	if (dyna_in_block() && dvar_defined(id)) return NEW_DVAR(id);
	if (local_id(id)) return NEW_LVAR(id);
	/* method call without arguments */
	return NEW_VCALL(id);
    }
    else if (is_global_id(id)) {
	return NEW_GVAR(id);
    }
    else if (is_instance_id(id)) {
	return NEW_IVAR(id);
    }
    else if (is_const_id(id)) {
	return NEW_CONST(id);
    }
    else if (is_class_id(id)) {
	return NEW_CVAR(id);
    }
    compile_error(PARSER_ARG "identifier %s is not valid to get", rb_id2name(id));
    return 0;
}

static NODE*
assignable_gen(struct parser_params *parser, ID id, NODE *val)
{
    if (!id) return 0;
    if (id == keyword_self) {
	yyerror("Can't change the value of self");
    }
    else if (id == keyword_nil) {
	yyerror("Can't assign to nil");
    }
    else if (id == keyword_true) {
	yyerror("Can't assign to true");
    }
    else if (id == keyword_false) {
	yyerror("Can't assign to false");
    }
    else if (id == keyword__FILE__) {
	yyerror("Can't assign to __FILE__");
    }
    else if (id == keyword__LINE__) {
	yyerror("Can't assign to __LINE__");
    }
    else if (is_local_id(id)) {
	if (dyna_in_block()) {
	    if (dvar_curr(id)) {
		return NEW_DASGN_CURR(id, val);
	    }
	    else if (dvar_defined(id)) {
		return NEW_DASGN(id, val);
	    }
	    else if (local_id(id)) {
		return NEW_LASGN(id, val);
	    }
	    else{
		dyna_var(id);
		return NEW_DASGN_CURR(id, val);
	    }
	}
	else {
	    if (!local_id(id)) {
		local_var(id);
	    }
	    return NEW_LASGN(id, val);
	}
    }
    else if (is_global_id(id)) {
	return NEW_GASGN(id, val);
    }
    else if (is_instance_id(id)) {
	return NEW_IASGN(id, val);
    }
    else if (is_const_id(id)) {
	if (in_def || in_single)
	    yyerror("dynamic constant assignment");
	return NEW_CDECL(id, val, 0);
    }
    else if (is_class_id(id)) {
	return NEW_CVASGN(id, val);
    }
    compile_error(PARSER_ARG "identifier %s is not valid to set", rb_id2name(id));
    return 0;
}

static void
shadowing_lvar_gen(struct parser_params *parser, ID name)
{
    static ID uscore;

    if (!uscore) uscore = rb_intern("_");
    if (uscore == name) return;
    if (dyna_in_block()) {
	if (dvar_curr(name)) {
	    yyerror("duplicated argument name");
	}
	else if (dvar_defined(name) || local_id(name)) {
	    rb_warningS("shadowing outer local variable - %s", rb_id2name(name));
	    vtable_add(lvtbl->vars, name);
	}
    }
    else {
	if (local_id(name)) {
	    yyerror("duplicated argument name");
	}
    }
}

static void
new_bv_gen(struct parser_params *parser, ID name)
{
    if (!name) return;
    if (!is_local_id(name)) {
	compile_error(PARSER_ARG "invalid local variable - %s",
		      rb_id2name(name));
	return;
    }
    shadowing_lvar(name);
    dyna_var(name);
}

static NODE *
aryset_gen(struct parser_params *parser, NODE *recv, NODE *idx)
{
    if (recv && nd_type(recv) == NODE_SELF)
	recv = (NODE *)1;
    return NEW_ATTRASGN(recv, tASET, idx);
}

static void
block_dup_check_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    if (node2 && node1 && nd_type(node1) == NODE_BLOCK_PASS) {
	compile_error(PARSER_ARG "both block arg and actual block given");
    }
}

ID
rb_id_attrset(ID id)
{
    id &= ~ID_SCOPE_MASK;
    id |= ID_ATTRSET;
    return id;
}

static NODE *
attrset_gen(struct parser_params *parser, NODE *recv, ID id)
{
    if (recv && nd_type(recv) == NODE_SELF)
	recv = (NODE *)1;
    return NEW_ATTRASGN(recv, rb_id_attrset(id), 0);
}

static void
rb_backref_error_gen(struct parser_params *parser, NODE *node)
{
    switch (nd_type(node)) {
      case NODE_NTH_REF:
	compile_error(PARSER_ARG "Can't set variable $%ld", node->nd_nth);
	break;
      case NODE_BACK_REF:
	compile_error(PARSER_ARG "Can't set variable $%c", (int)node->nd_nth);
	break;
    }
}

static NODE *
arg_concat_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    if (!node2) return node1;
    if (nd_type(node1) == NODE_BLOCK_PASS) {
	node1->nd_iter = arg_concat(node1->nd_iter, node2);
	return node1;
    }
    return NEW_ARGSCAT(node1, node2);
}

static NODE *
arg_append_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    if (!node1) return NEW_LIST(node2);
    switch (nd_type(node1))  {
      case NODE_ARRAY:
	return list_append(node1, node2);
      case NODE_BLOCK_PASS:
	node1->nd_head = arg_append(node1->nd_head, node2);
	return node1;
      default:
	return NEW_ARGSPUSH(node1, node2);
    }
}

#define arg_add(n1, n2) arg_add_gen(parser,n1,n2)
static NODE *
arg_add_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    if (!node1) return NEW_LIST(node2);
    switch (nd_type(node1))  {
      case NODE_ARRAY:
	return list_append(node1, node2);
      case NODE_BLOCK_PASS:
	node1->nd_head = arg_add(node1->nd_head, node2);
	return node1;
      default:
	return NEW_ARGSPUSH(node1, node2);
    }
}

static NODE *
node_assign_gen(struct parser_params *parser, NODE *lhs, NODE *rhs)
{
    if (!lhs) return 0;

    switch (nd_type(lhs)) {
      case NODE_GASGN:
      case NODE_IASGN:
      case NODE_IASGN2:
      case NODE_LASGN:
      case NODE_DASGN:
      case NODE_DASGN_CURR:
      case NODE_MASGN:
      case NODE_CDECL:
      case NODE_CVASGN:
	lhs->nd_value = rhs;
	break;

      case NODE_ATTRASGN:
      case NODE_CALL:
	lhs->nd_args = arg_add(lhs->nd_args, rhs);
	break;

      default:
	/* should not happen */
	break;
    }

    return lhs;
}

static int
value_expr_gen(struct parser_params *parser, NODE *node)
{
    if (!node) {
	rb_warning0("empty expression");
    }
    while (node) {
	switch (nd_type(node)) {
	  case NODE_DEFN:
	  case NODE_DEFS:
	    parser_warning(node, "void value expression");
	    return Qfalse;

	  case NODE_RETURN:
	  case NODE_BREAK:
	  case NODE_NEXT:
	  case NODE_REDO:
	  case NODE_RETRY:
	    yyerror("void value expression");
	    /* or "control never reach"? */
	    return Qfalse;

	  case NODE_BLOCK:
	    while (node->nd_next) {
		node = node->nd_next;
	    }
	    node = node->nd_head;
	    break;

	  case NODE_BEGIN:
	    node = node->nd_body;
	    break;

	  case NODE_IF:
	    if (!value_expr(node->nd_body)) return Qfalse;
	    node = node->nd_else;
	    break;

	  case NODE_AND:
	  case NODE_OR:
	    node = node->nd_2nd;
	    break;

	  default:
	    return Qtrue;
	}
    }

    return Qtrue;
}

static void
void_expr_gen(struct parser_params *parser, NODE *node)
{
    const char *useless = 0;

    if (!RTEST(ruby_verbose)) return;

    if (!node) return;
    switch (nd_type(node)) {
      case NODE_CALL:
	switch (node->nd_mid) {
	  case '+':
	  case '-':
	  case '*':
	  case '/':
	  case '%':
	  case tPOW:
	  case tUPLUS:
	  case tUMINUS:
	  case '|':
	  case '^':
	  case '&':
	  case tCMP:
	  case '>':
	  case tGEQ:
	  case '<':
	  case tLEQ:
	  case tEQ:
	  case tNEQ:
	    useless = rb_id2name(node->nd_mid);
	    break;
	}
	break;

      case NODE_LVAR:
      case NODE_DVAR:
      case NODE_GVAR:
      case NODE_IVAR:
      case NODE_CVAR:
      case NODE_NTH_REF:
      case NODE_BACK_REF:
	useless = "a variable";
	break;
      case NODE_CONST:
	useless = "a constant";
	break;
      case NODE_LIT:
      case NODE_STR:
      case NODE_DSTR:
      case NODE_DREGX:
      case NODE_DREGX_ONCE:
	useless = "a literal";
	break;
      case NODE_COLON2:
      case NODE_COLON3:
	useless = "::";
	break;
      case NODE_DOT2:
	useless = "..";
	break;
      case NODE_DOT3:
	useless = "...";
	break;
      case NODE_SELF:
	useless = "self";
	break;
      case NODE_NIL:
	useless = "nil";
	break;
      case NODE_TRUE:
	useless = "true";
	break;
      case NODE_FALSE:
	useless = "false";
	break;
      case NODE_DEFINED:
	useless = "defined?";
	break;
    }

    if (useless) {
	int line = ruby_sourceline;

	ruby_sourceline = nd_line(node);
	rb_warnS("useless use of %s in void context", useless);
	ruby_sourceline = line;
    }
}

static void
void_stmts_gen(struct parser_params *parser, NODE *node)
{
    if (!RTEST(ruby_verbose)) return;
    if (!node) return;
    if (nd_type(node) != NODE_BLOCK) return;

    for (;;) {
	if (!node->nd_next) return;
	void_expr0(node->nd_head);
	node = node->nd_next;
    }
}

static NODE *
remove_begin(NODE *node)
{
    NODE **n = &node, *n1 = node;
    while (n1 && nd_type(n1) == NODE_BEGIN && n1->nd_body) {
	*n = n1 = n1->nd_body;
    }
    return node;
}

static void
reduce_nodes_gen(struct parser_params *parser, NODE **body)
{
    NODE *node = *body;

    if (!node) {
	*body = NEW_NIL();
	return;
    }
#define subnodes(n1, n2) \
    ((!node->n1) ? (node->n2 ? (body = &node->n2, 1) : 0) : \
     (!node->n2) ? (body = &node->n1, 1) : \
     (reduce_nodes(&node->n1), body = &node->n2, 1))

    while (node) {
	switch (nd_type(node)) {
	  end:
	  case NODE_NIL:
	    *body = 0;
	    return;
	  case NODE_RETURN:
	    *body = node = node->nd_stts;
	    continue;
	  case NODE_BEGIN:
	    *body = node = node->nd_body;
	    continue;
	  case NODE_BLOCK:
	    body = &node->nd_end->nd_head;
	    break;
	  case NODE_IF:
	    if (subnodes(nd_body, nd_else)) break;
	    return;
	  case NODE_CASE:
	    body = &node->nd_body;
	    break;
	  case NODE_WHEN:
	    if (!subnodes(nd_body, nd_next)) goto end;
	    break;
	  case NODE_ENSURE:
	    if (!subnodes(nd_head, nd_resq)) goto end;
	    break;
	  case NODE_RESCUE:
	    if (!subnodes(nd_head, nd_resq)) goto end;
	    break;
	  default:
	    return;
	}
	node = *body;
    }

#undef subnodes
}

static int
assign_in_cond(struct parser_params *parser, NODE *node)
{
    switch (nd_type(node)) {
      case NODE_MASGN:
	yyerror("multiple assignment in conditional");
	return 1;

      case NODE_LASGN:
      case NODE_DASGN:
      case NODE_GASGN:
      case NODE_IASGN:
	break;

      default:
	return 0;
    }

    switch (nd_type(node->nd_value)) {
      case NODE_LIT:
      case NODE_STR:
      case NODE_NIL:
      case NODE_TRUE:
      case NODE_FALSE:
	/* reports always */
	parser_warn(node->nd_value, "found = in conditional, should be ==");
	return 1;

      case NODE_DSTR:
      case NODE_XSTR:
      case NODE_DXSTR:
      case NODE_EVSTR:
      case NODE_DREGX:
      default:
	break;
    }
    return 1;
}

static int
e_option_supplied(NODE *node)
{
    if (strcmp(node->nd_file, "-e") == 0)
	return Qtrue;
    return Qfalse;
}

static void
warn_unless_e_option(NODE *node, const char *str)
{
    if (!e_option_supplied(node)) parser_warn(node, str);
}

static void
warning_unless_e_option(NODE *node, const char *str)
{
    if (!e_option_supplied(node)) parser_warning(node, str);
}

static NODE *cond0(struct parser_params*,NODE*);

static NODE*
range_op(struct parser_params *parser, NODE *node)
{
    enum node_type type;

    if (!e_option_supplied(node)) return node;
    if (node == 0) return 0;

    value_expr(node);
    node = cond0(parser, node);
    type = nd_type(node);
    if (type == NODE_LIT && FIXNUM_P(node->nd_lit)) {
	warn_unless_e_option(node, "integer literal in conditional range");
	return NEW_CALL(node, tEQ, NEW_LIST(NEW_GVAR(rb_intern("$."))));
    }
    return node;
}

static int
literal_node(NODE *node)
{
    if (!node) return 1;	/* same as NODE_NIL */
    switch (nd_type(node)) {
      case NODE_LIT:
      case NODE_STR:
      case NODE_DSTR:
      case NODE_EVSTR:
      case NODE_DREGX:
      case NODE_DREGX_ONCE:
      case NODE_DSYM:
	return 2;
      case NODE_TRUE:
      case NODE_FALSE:
      case NODE_NIL:
	return 1;
    }
    return 0;
}

static NODE*
cond0(struct parser_params *parser, NODE *node)
{
    if (node == 0) return 0;
    assign_in_cond(parser, node);

    switch (nd_type(node)) {
      case NODE_DSTR:
      case NODE_EVSTR:
      case NODE_STR:
	rb_warn0("string literal in condition");
	break;

      case NODE_DREGX:
      case NODE_DREGX_ONCE:
	warning_unless_e_option(node, "regex literal in condition");
	return NEW_MATCH2(node, NEW_GVAR(rb_intern("$_")));

      case NODE_AND:
      case NODE_OR:
	node->nd_1st = cond0(parser, node->nd_1st);
	node->nd_2nd = cond0(parser, node->nd_2nd);
	break;

      case NODE_DOT2:
      case NODE_DOT3:
	node->nd_beg = range_op(parser, node->nd_beg);
	node->nd_end = range_op(parser, node->nd_end);
	if (nd_type(node) == NODE_DOT2) nd_set_type(node,NODE_FLIP2);
	else if (nd_type(node) == NODE_DOT3) nd_set_type(node, NODE_FLIP3);
	if (!e_option_supplied(node)) {
	    int b = literal_node(node->nd_beg);
	    int e = literal_node(node->nd_end);
	    if ((b == 1 && e == 1) || (b + e >= 2 && RTEST(ruby_verbose))) {
		parser_warn(node, "range literal in condition");
	    }
	}
	break;

      case NODE_DSYM:
	parser_warning(node, "literal in condition");
	break;

      case NODE_LIT:
	if (TYPE(node->nd_lit) == T_REGEXP) {
	    warn_unless_e_option(node, "regex literal in condition");
	    nd_set_type(node, NODE_MATCH);
	}
	else {
	    parser_warning(node, "literal in condition");
	}
      default:
	break;
    }
    return node;
}

static NODE*
cond_gen(struct parser_params *parser, NODE *node)
{
    if (node == 0) return 0;
    return cond0(parser, node);
}

static NODE*
logop_gen(struct parser_params *parser, enum node_type type, NODE *left, NODE *right)
{
    value_expr(left);
    if (left && nd_type(left) == type) {
	NODE *node = left, *second;
	while ((second = node->nd_2nd) != 0 && nd_type(second) == type) {
	    node = second;
	}
	node->nd_2nd = NEW_NODE(type, second, right, 0);
	return left;
    }
    return NEW_NODE(type, left, right, 0);
}

static void
no_blockarg(struct parser_params *parser, NODE *node)
{
    if (node && nd_type(node) == NODE_BLOCK_PASS) {
	compile_error(PARSER_ARG "block argument should not be given");
    }
}

static NODE *
ret_args_gen(struct parser_params *parser, NODE *node)
{
    if (node) {
	no_blockarg(parser, node);
	if (nd_type(node) == NODE_ARRAY) {
	    if (node->nd_next == 0) {
		node = node->nd_head;
	    }
	    else {
		nd_set_type(node, NODE_VALUES);
	    }
	}
    }
    return node;
}

static NODE *
new_yield_gen(struct parser_params *parser, NODE *node)
{
    long state = Qtrue;

    if (node) {
        no_blockarg(parser, node);
	if (node && nd_type(node) == NODE_SPLAT) {
	    state = Qtrue;
	}
    }
    else {
        state = Qfalse;
    }
    return NEW_YIELD(node, state);
}

static NODE*
negate_lit(NODE *node)
{
    switch (TYPE(node->nd_lit)) {
      case T_FIXNUM:
	node->nd_lit = LONG2FIX(-FIX2LONG(node->nd_lit));
	break;
      case T_BIGNUM:
	node->nd_lit = rb_funcall(node->nd_lit,tUMINUS,0,0);
	break;
      case T_FLOAT:
	RFLOAT(node->nd_lit)->float_value = -RFLOAT_VALUE(node->nd_lit);
	break;
      default:
	break;
    }
    return node;
}

static NODE *
arg_blk_pass(NODE *node1, NODE *node2)
{
    if (node2) {
	node2->nd_head = node1;
	return node2;
    }
    return node1;
}

static NODE*
new_args_gen(struct parser_params *parser, NODE *m, NODE *o, ID r, NODE *p, ID b)
{
    int saved_line = ruby_sourceline;
    NODE *node;
    NODE *i1, *i2 = 0;

    node = NEW_ARGS(m ? m->nd_plen : 0, o);
    i1 = m ? m->nd_next : 0;
    node->nd_next = NEW_ARGS_AUX(r, b);

    if (p) {
	i2 = p->nd_next;
	node->nd_next->nd_next = NEW_ARGS_AUX(p->nd_pid, p->nd_plen);
    }
    else if (i1) {
	node->nd_next->nd_next = NEW_ARGS_AUX(0, 0);
    }
    if (i1 || i2) {
	node->nd_next->nd_next->nd_next = NEW_NODE(NODE_AND, i1, i2, 0);
    }
    ruby_sourceline = saved_line;
    return node;
}

static void
local_push_gen(struct parser_params *parser, int inherit_dvars)
{
    struct local_vars *local;

    local = ALLOC(struct local_vars);
    local->prev = lvtbl;
    local->args = vtable_alloc(0);
    local->vars = vtable_alloc(inherit_dvars ? DVARS_INHERIT : DVARS_TOPSCOPE);
    lvtbl = local;
}

static void
local_pop_gen(struct parser_params *parser)
{
    struct local_vars *local = lvtbl->prev;
    vtable_free(lvtbl->args);
    vtable_free(lvtbl->vars);
    xfree(lvtbl);
    lvtbl = local;
}

static ID*
vtable_tblcpy(ID *buf, const struct vtable *src)
{
    int i, cnt = vtable_size(src);

    if (cnt > 0) {
        buf[0] = cnt;
        for (i = 0; i < cnt; i++) {
            buf[i] = src->tbl[i];
        }
        return buf;
    }
    return 0;
}

static ID*
local_tbl_gen(struct parser_params *parser)
{
    int cnt = vtable_size(lvtbl->args) + vtable_size(lvtbl->vars);
    ID *buf;

    if (cnt <= 0) return 0;
    buf = ALLOC_N(ID, cnt + 1);
    vtable_tblcpy(buf+1, lvtbl->args);
    vtable_tblcpy(buf+vtable_size(lvtbl->args)+1, lvtbl->vars);
    buf[0] = cnt;
    return buf;
}

#include "debug.h"
static int
arg_var_gen(struct parser_params *parser, ID id)
{
    vtable_add(lvtbl->args, id);
    return vtable_size(lvtbl->args) - 1;
}

static int
local_var_gen(struct parser_params *parser, ID id)
{
    vtable_add(lvtbl->vars, id);
    return vtable_size(lvtbl->vars) - 1;
}

static int
local_id_gen(struct parser_params *parser, ID id)
{
    struct vtable *vars, *args;

    vars = lvtbl->vars;
    args = lvtbl->args;

    while (vars && POINTER_P(vars->prev)) {
	vars = vars->prev;
	args = args->prev;
    }

    if (vars && vars->prev == DVARS_INHERIT) {
	return rb_local_defined(id);
    }
    else {
	return (vtable_included(args, id) ||
		vtable_included(vars, id));
    }
}

static void
dyna_push_gen(struct parser_params *parser)
{
    lvtbl->args = vtable_alloc(lvtbl->args);
    lvtbl->vars = vtable_alloc(lvtbl->vars);
}

static void
dyna_pop_gen(struct parser_params *parser)
{
    struct vtable *tmp;

    tmp = lvtbl->args;
    lvtbl->args = lvtbl->args->prev;
    vtable_free(tmp);
    tmp = lvtbl->vars;
    lvtbl->vars = lvtbl->vars->prev;
    vtable_free(tmp);
}

static int
dyna_in_block_gen(struct parser_params *parser)
{
    return POINTER_P(lvtbl->vars) && lvtbl->vars->prev != DVARS_TOPSCOPE;
}

static int
dvar_defined_gen(struct parser_params *parser, ID id)
{
    struct vtable *vars, *args;

    args = lvtbl->args;
    vars = lvtbl->vars;

    while (POINTER_P(vars)) {
	if (vtable_included(args, id)) {
	    return 1;
	}
	if (vtable_included(vars, id)) {
	    return 1;
	}
	args = args->prev;
	vars = vars->prev;
    }

    if (vars == DVARS_INHERIT) {
        return rb_dvar_defined(id);
    }

    return 0;
}

static int
dvar_curr_gen(struct parser_params *parser, ID id)
{
    return (vtable_included(lvtbl->args, id) ||
	    vtable_included(lvtbl->vars, id));
}

VALUE rb_reg_compile(VALUE str, int options);
VALUE rb_reg_check_preprocess(VALUE);

static void
reg_fragment_setenc_gen(struct parser_params* parser, VALUE str, int options)
{
    int c = RE_OPTION_ENCODING_IDX(options);

    if (c) {
	int opt, idx;
	rb_char_to_option_kcode(c, &opt, &idx);
	if (idx != ENCODING_GET(str) && ENCODING_GET(str) &&
	    rb_enc_str_coderange(str) != ENC_CODERANGE_7BIT) {
	    compile_error(PARSER_ARG
			  "regexp encoding option '%c' differs from source encoding '%s'",
			  c, rb_enc_name(rb_enc_get(str)));
	}
	ENCODING_SET(str, idx);
    }
}

static void
reg_fragment_check_gen(struct parser_params* parser, VALUE str, int options)
{
    VALUE err;
    reg_fragment_setenc_gen(parser, str, options);
    err = rb_reg_check_preprocess(str);
    if (err != Qnil) {
        err = rb_obj_as_string(err);
        compile_error(PARSER_ARG "%s", RSTRING_PTR(err));
	RB_GC_GUARD(err);
    }
}

typedef struct {
    struct parser_params* parser;
    rb_encoding *enc;
    NODE *succ_block;
    NODE *fail_block;
    int num;
} reg_named_capture_assign_t;

static int
reg_named_capture_assign_iter(const OnigUChar *name, const OnigUChar *name_end,
          int back_num, int *back_refs, OnigRegex regex, void *arg0)
{
    reg_named_capture_assign_t *arg = (reg_named_capture_assign_t*)arg0;
    struct parser_params* parser = arg->parser;
    rb_encoding *enc = arg->enc;
    int len = name_end - name;
    const char *s = (const char *)name;
    ID var;

    arg->num++;

    if (arg->succ_block == 0) {
        arg->succ_block = NEW_BEGIN(0);
        arg->fail_block = NEW_BEGIN(0);
    }

    if (!len || (*name != '_' && ISASCII(*name) && !rb_enc_islower(*name, enc)) ||
	rb_reserved_word(s, len) || !rb_enc_symname2_p(s, len, enc)) {
        return ST_CONTINUE;
    }
    var = rb_intern3(s, len, enc);
    if (dvar_defined(var) || local_id(var)) {
        rb_warningS("named capture conflicts a local variable - %s", 
                    rb_id2name(var));
    }
    arg->succ_block = block_append(arg->succ_block,
        newline_node(node_assign(assignable(var,0),
            NEW_CALL(
              gettable(rb_intern("$~")),
              idAREF,
              NEW_LIST(NEW_LIT(ID2SYM(var))))
            )));
    arg->fail_block = block_append(arg->fail_block,
        newline_node(node_assign(assignable(var,0), NEW_LIT(Qnil))));
    return ST_CONTINUE;
}

static NODE *
reg_named_capture_assign_gen(struct parser_params* parser, VALUE regexp, NODE *match)
{
    reg_named_capture_assign_t arg;

    arg.parser = parser;
    arg.enc = rb_enc_get(regexp);
    arg.succ_block = 0;
    arg.fail_block = 0;
    arg.num = 0;
    onig_foreach_name(RREGEXP(regexp)->ptr, reg_named_capture_assign_iter, (void*)&arg);

    if (arg.num == 0)
        return match;

    return 
        block_append(
            newline_node(match),
            NEW_IF(gettable(rb_intern("$~")),
                block_append(
                    newline_node(arg.succ_block),
                    newline_node(
                        NEW_CALL(
                          gettable(rb_intern("$~")),
                          rb_intern("begin"),
                          NEW_LIST(NEW_LIT(INT2FIX(0)))))),
                block_append(
                    newline_node(arg.fail_block),
                    newline_node(
                        NEW_LIT(Qnil)))));
}

static VALUE
reg_compile_gen(struct parser_params* parser, VALUE str, int options)
{
    VALUE re;

    reg_fragment_setenc(str, options);
    re = rb_reg_compile(str, options & RE_OPTION_MASK);
    if (NIL_P(re)) {
	RB_GC_GUARD(re) = rb_obj_as_string(rb_errinfo());
	compile_error(PARSER_ARG "%s", RSTRING_PTR(re));
	return Qnil;
    }
    return re;
}

void
rb_gc_mark_parser(void)
{
}

NODE*
rb_parser_append_print(VALUE vparser, NODE *node)
{
    NODE *prelude = 0;
    NODE *scope = node;
    struct parser_params *parser;

    if (!node) return node;

    Data_Get_Struct(vparser, struct parser_params, parser);

    node = node->nd_body;

    if (nd_type(node) == NODE_PRELUDE) {
	prelude = node;
	node = node->nd_body;
    }

    node = block_append(node,
			NEW_FCALL(rb_intern("print"),
				  NEW_ARRAY(NEW_GVAR(rb_intern("$_")))));
    if (prelude) {
	prelude->nd_body = node;
	scope->nd_body = prelude;
    }
    else {
	scope->nd_body = node;
    }

    return scope;
}

NODE *
rb_parser_while_loop(VALUE vparser, NODE *node, int chop, int split)
{
    NODE *prelude = 0;
    NODE *scope = node;
    struct parser_params *parser;

    if (!node) return node;

    Data_Get_Struct(vparser, struct parser_params, parser);

    node = node->nd_body;

    if (nd_type(node) == NODE_PRELUDE) {
	prelude = node;
	node = node->nd_body;
    }
    if (split) {
	node = block_append(NEW_GASGN(rb_intern("$F"),
				      NEW_CALL(NEW_GVAR(rb_intern("$_")),
					       rb_intern("split"), 0)),
			    node);
    }
    if (chop) {
	node = block_append(NEW_CALL(NEW_GVAR(rb_intern("$_")),
				     rb_intern("chop!"), 0), node);
    }

    node = NEW_OPT_N(node);

    if (prelude) {
	prelude->nd_body = node;
	scope->nd_body = prelude;
    }
    else {
	scope->nd_body = node;
    }

    return scope;
}

static const struct {
    ID token;
    const char *name;
} op_tbl[] = {
    {tDOT2,	".."},
    {tDOT3,	"..."},
    {'+',	"+"},
    {'-',	"-"},
    {'+',	"+(binary)"},
    {'-',	"-(binary)"},
    {'*',	"*"},
    {'/',	"/"},
    {'%',	"%"},
    {tPOW,	"**"},
    {tUPLUS,	"+@"},
    {tUMINUS,	"-@"},
    {'|',	"|"},
    {'^',	"^"},
    {'&',	"&"},
    {'!',	"!"},
    {tCMP,	"<=>"},
    {'>',	">"},
    {tGEQ,	">="},
    {'<',	"<"},
    {tLEQ,	"<="},
    {tEQ,	"=="},
    {tEQQ,	"==="},
    {tNEQ,	"!="},
    {tMATCH,	"=~"},
    {tNMATCH,	"!~"},
    {'~',	"~"},
    {'!',	"!"},
    {tAREF,	"[]"},
    {tASET,	"[]="},
    {tLSHFT,	"<<"},
    {tRSHFT,	">>"},
    {tCOLON2,	"::"},
    {'`',	"`"},
    {0,	0}
};

static struct symbols {
    ID last_id;
    st_table *sym_id;
    st_table *id_str;
    st_table *ivar2_id;
    st_table *id_ivar2;
    VALUE op_sym[tLAST_TOKEN];
} global_symbols = {tLAST_TOKEN >> ID_SCOPE_SHIFT};

static const struct st_hash_type symhash = {
    rb_str_cmp,
    rb_str_hash,
};

struct ivar2_key {
    ID id;
    VALUE klass;
};

static int
ivar2_cmp(struct ivar2_key *key1, struct ivar2_key *key2)
{
    if (key1->id == key2->id && key1->klass == key2->klass) {
	return 0;
    }
    return 1;
}

static int
ivar2_hash(struct ivar2_key *key)
{
    return (key->id << 8) ^ (key->klass >> 2);
}

static const struct st_hash_type ivar2_hash_type = {
    ivar2_cmp,
    ivar2_hash,
};

void
Init_sym(void)
{
    global_symbols.sym_id = st_init_table_with_size(&symhash, 1000);
    global_symbols.id_str = st_init_numtable_with_size(1000);
    global_symbols.ivar2_id = st_init_table_with_size(&ivar2_hash_type, 1000);
    global_symbols.id_ivar2 = st_init_numtable_with_size(1000);
    rb_intern2("", 0);
}

void
rb_gc_mark_symbols(void)
{
    rb_mark_tbl(global_symbols.id_str);
    rb_gc_mark_locations(global_symbols.op_sym,
			 global_symbols.op_sym + tLAST_TOKEN);
}

static ID
internal_id_gen(struct parser_params *parser)
{
    ID id = (ID)vtable_size(lvtbl->args) + (ID)vtable_size(lvtbl->vars);
    id += ((tLAST_TOKEN - ID_INTERNAL) >> ID_SCOPE_SHIFT) + 1;
    return ID_INTERNAL | (id << ID_SCOPE_SHIFT);
}

static int
is_special_global_name(const char *m, const char *e, rb_encoding *enc)
{
    int mb = 0;

    if (m >= e) return 0;
    switch (*m) {
      case '~': case '*': case '$': case '?': case '!': case '@':
      case '/': case '\\': case ';': case ',': case '.': case '=':
      case ':': case '<': case '>': case '\"':
      case '&': case '`': case '\'': case '+':
      case '0':
	++m;
	break;
      case '-':
	++m;
	if (m < e && is_identchar(m, e, enc)) {
	    if (!ISASCII(*m)) mb = 1;
	    m += rb_enc_mbclen(m, e, enc);
	}
	break;
      default:
	if (!rb_enc_isdigit(*m, enc)) return 0;
	do {
	    if (!ISASCII(*m)) mb = 1;
	    ++m;
	} while (rb_enc_isdigit(*m, enc));
    }
    return m == e ? mb + 1 : 0;
}

int
rb_symname_p(const char *name)
{
    return rb_enc_symname_p(name, rb_enc_from_index(0));
}

int
rb_enc_symname_p(const char *name, rb_encoding *enc)
{
    return rb_enc_symname2_p(name, strlen(name), enc);
}

int
rb_enc_symname2_p(const char *name, int len, rb_encoding *enc)
{
    const char *m = name;
    const char *e = m + len;
    int localid = Qfalse;

    if (!m) return Qfalse;
    switch (*m) {
      case '\0':
	return Qfalse;

      case '$':
	if (is_special_global_name(++m, e, enc)) return Qtrue;
	goto id;

      case '@':
	if (*++m == '@') ++m;
	goto id;

      case '<':
	switch (*++m) {
	  case '<': ++m; break;
	  case '=': if (*++m == '>') ++m; break;
	  default: break;
	}
	break;

      case '>':
	switch (*++m) {
	  case '>': case '=': ++m; break;
	}
	break;

      case '=':
	switch (*++m) {
	  case '~': ++m; break;
	  case '=': if (*++m == '=') ++m; break;
	  default: return Qfalse;
	}
	break;

      case '*':
	if (*++m == '*') ++m;
	break;

      case '+': case '-':
	if (*++m == '@') ++m;
	break;

      case '|': case '^': case '&': case '/': case '%': case '~': case '`':
	++m;
	break;

      case '[':
	if (*++m != ']') return Qfalse;
	if (*++m == '=') ++m;
	break;

      default:
	localid = !rb_enc_isupper(*m, enc);
      id:
	if (m >= e || (*m != '_' && !rb_enc_isalpha(*m, enc) && ISASCII(*m)))
		  return Qfalse;
	while (m < e && is_identchar(m, e, enc)) m += rb_enc_mbclen(m, e, enc);
	if (localid) {
	    switch (*m) {
	      case '!': case '?': case '=': ++m;
	    }
	}
	break;
    }
    return *m ? Qfalse : Qtrue;
}

ID
rb_intern3(const char *name, long len, rb_encoding *enc)
{
    const char *m = name;
    const char *e = m + len;
    VALUE str;
    ID id;
    int last;
    int mb;
    struct RString fake_str;
    fake_str.basic.flags = T_STRING|RSTRING_NOEMBED|FL_FREEZE;
    fake_str.basic.klass = rb_cString;
    fake_str.as.heap.len = len;
    fake_str.as.heap.ptr = (char *)name;
    fake_str.as.heap.aux.capa = len;
    str = (VALUE)&fake_str;
    rb_enc_associate(str, enc);

    if (st_lookup(global_symbols.sym_id, str, (st_data_t *)&id))
	return id;

    last = len-1;
    id = 0;
    switch (*m) {
      case '$':
	id |= ID_GLOBAL;
	if ((mb = is_special_global_name(++m, e, enc)) != 0) {
	    if (!--mb) enc = rb_enc_from_index(0);
	    goto new_id;
	}
	break;
      case '@':
	if (m[1] == '@') {
	    m++;
	    id |= ID_CLASS;
	}
	else {
	    id |= ID_INSTANCE;
	}
	m++;
	break;
      default:
	if (m[0] != '_' && rb_enc_isascii((unsigned char)m[0], enc)
	    && !rb_enc_isalnum(m[0], enc)) {
	    /* operators */
	    int i;

	    for (i=0; op_tbl[i].token; i++) {
		if (*op_tbl[i].name == *m &&
		    strcmp(op_tbl[i].name, m) == 0) {
		    id = op_tbl[i].token;
		    goto id_register;
		}
	    }
	}

	if (m[last] == '=') {
	    /* attribute assignment */
	    id = rb_intern3(name, last, enc);
	    if (id > tLAST_TOKEN && !is_attrset_id(id)) {
		enc = rb_enc_get(rb_id2str(id));
		id = rb_id_attrset(id);
		goto id_register;
	    }
	    id = ID_ATTRSET;
	}
	else if (rb_enc_isupper(m[0], enc)) {
	    id = ID_CONST;
        }
	else {
	    id = ID_LOCAL;
	}
	break;
    }
    mb = 0;
    if (!rb_enc_isdigit(*m, enc)) {
	while (m <= name + last && is_identchar(m, e, enc)) {
	    if (!ISASCII(*m)) mb = 1;
	    m += rb_enc_mbclen(m, e, enc);
	}
    }
    if (m - name < len) id = ID_JUNK;
    if (enc != rb_ascii8bit_encoding()) {
	/*
	 * this clause makes sense only when called from other than
	 * rb_intern_str() taking care of code-range.
	 */
	if (!mb) {
	    for (; m <= name + len; ++m) {
		if (!ISASCII(*m)) goto mbstr;
	    }
	    enc = rb_ascii8bit_encoding();
	}
      mbstr:;
    }
  new_id:
    id |= ++global_symbols.last_id << ID_SCOPE_SHIFT;
  id_register:
    str = rb_enc_str_new(name, len, enc);
    OBJ_FREEZE(str);
    st_add_direct(global_symbols.sym_id, (st_data_t)str, id);
    st_add_direct(global_symbols.id_str, id, (st_data_t)str);
    return id;
}

ID
rb_intern2(const char *name, long len)
{
    return rb_intern3(name, len, rb_enc_from_index(0));
}

ID
rb_intern(const char *name)
{
    return rb_intern2(name, strlen(name));
}

ID
rb_intern_str(VALUE str)
{
    int idx = 0;
    ID id;

    if (rb_enc_str_coderange(str) != ENC_CODERANGE_7BIT) {
	idx = rb_enc_get_index(str);
    }
    id = rb_intern3(RSTRING_PTR(str), RSTRING_LEN(str),
		    rb_enc_from_index(idx));
    RB_GC_GUARD(str);
    return id;
}

VALUE
rb_id2str(ID id)
{
    st_data_t data;

    if (id < tLAST_TOKEN) {
	int i = 0;

	for (i=0; op_tbl[i].token; i++) {
	    if (op_tbl[i].token == id) {
		VALUE str = global_symbols.op_sym[i];
		if (!str) {
		    str = rb_str_new2(op_tbl[i].name);
		    OBJ_FREEZE(str);
		    global_symbols.op_sym[i] = str;
		}
		return str;
	    }
	}
    }

    if (st_lookup(global_symbols.id_str, id, &data)) {
        VALUE str = (VALUE)data;
        if (RBASIC(str)->klass == 0)
            RBASIC(str)->klass = rb_cString;
	return str;
    }

    if (is_attrset_id(id)) {
	ID id2 = (id & ~ID_SCOPE_MASK) | ID_LOCAL;
	VALUE str;

	while (!(str = rb_id2str(id2))) {
	    if (!is_local_id(id2)) return 0;
	    id2 = (id & ~ID_SCOPE_MASK) | ID_CONST;
	}
	str = rb_str_dup(str);
	rb_str_cat(str, "=", 1);
	rb_intern_str(str);
	if (st_lookup(global_symbols.id_str, id, &data)) {
            VALUE str = (VALUE)data;
            if (RBASIC(str)->klass == 0)
                RBASIC(str)->klass = rb_cString;
            return str;
        }
    }
    return 0;
}

const char *
rb_id2name(ID id)
{
    VALUE str = rb_id2str(id);

    if (!str) return 0;
    return RSTRING_PTR(str);
}

static int
symbols_i(VALUE sym, ID value, VALUE ary)
{
    rb_ary_push(ary, ID2SYM(value));
    return ST_CONTINUE;
}

/*
 *  call-seq:
 *     Symbol.all_symbols    => array
 *
 *  Returns an array of all the symbols currently in Ruby's symbol
 *  table.
 *
 *     Symbol.all_symbols.size    #=> 903
 *     Symbol.all_symbols[1,20]   #=> [:floor, :ARGV, :Binding, :symlink,
 *                                     :chown, :EOFError, :$;, :String,
 *                                     :LOCK_SH, :"setuid?", :$<,
 *                                     :default_proc, :compact, :extend,
 *                                     :Tms, :getwd, :$=, :ThreadGroup,
 *                                     :wait2, :$>]
 */

VALUE
rb_sym_all_symbols(void)
{
    VALUE ary = rb_ary_new2(global_symbols.sym_id->num_entries);

    st_foreach(global_symbols.sym_id, symbols_i, ary);
    return ary;
}

int
rb_is_const_id(ID id)
{
    if (is_const_id(id)) return Qtrue;
    return Qfalse;
}

int
rb_is_class_id(ID id)
{
    if (is_class_id(id)) return Qtrue;
    return Qfalse;
}

int
rb_is_instance_id(ID id)
{
    if (is_instance_id(id)) return Qtrue;
    return Qfalse;
}

int
rb_is_local_id(ID id)
{
    if (is_local_id(id)) return Qtrue;
    return Qfalse;
}

int
rb_is_junk_id(ID id)
{
    if (is_junk_id(id)) return Qtrue;
    return Qfalse;
}

#endif /* !RIPPER */

static void
parser_initialize(struct parser_params *parser)
{
    parser->eofp = Qfalse;

    parser->parser_lex_strterm = 0;
    parser->parser_cond_stack = 0;
    parser->parser_cmdarg_stack = 0;
    parser->parser_class_nest = 0;
    parser->parser_paren_nest = 0;
    parser->parser_lpar_beg = 0;
    parser->parser_in_single = 0;
    parser->parser_in_def = 0;
    parser->parser_in_defined = 0;
    parser->parser_compile_for_eval = 0;
    parser->parser_cur_mid = 0;
    parser->parser_tokenbuf = NULL;
    parser->parser_tokidx = 0;
    parser->parser_toksiz = 0;
    parser->parser_heredoc_end = 0;
    parser->parser_command_start = Qtrue;
    parser->parser_lex_pbeg = 0;
    parser->parser_lex_p = 0;
    parser->parser_lex_pend = 0;
    parser->parser_lvtbl = 0;
    parser->parser_ruby__end__seen = 0;
    parser->parser_ruby_sourcefile = 0;
#ifndef RIPPER
    parser->is_ripper = 0;
    parser->parser_eval_tree_begin = 0;
    parser->parser_eval_tree = 0;
#else
    parser->is_ripper = 1;
    parser->parser_ruby_sourcefile_string = Qnil;
    parser->delayed = Qnil;

    parser->result = Qnil;
    parser->parsing_thread = Qnil;
    parser->toplevel_p = Qtrue;
#endif
#ifdef YYMALLOC
    parser->heap = NULL;
#endif
    parser->enc = rb_enc_from_index(0);
}

extern void rb_mark_source_filename(char *);

#ifdef RIPPER
#define parser_mark ripper_parser_mark
#define parser_free ripper_parser_free
#endif

static void
parser_mark(void *ptr)
{
    struct parser_params *p = (struct parser_params*)ptr;

    rb_gc_mark((VALUE)p->parser_lex_strterm);
    rb_gc_mark(p->parser_lex_input);
    rb_gc_mark(p->parser_lex_lastline);
    rb_gc_mark(p->parser_lex_nextline);
#ifndef RIPPER
    rb_gc_mark((VALUE)p->parser_eval_tree_begin) ;
    rb_gc_mark((VALUE)p->parser_eval_tree) ;
    rb_gc_mark(p->debug_lines);
    rb_mark_source_filename(p->parser_ruby_sourcefile);
#else
    rb_gc_mark(p->parser_ruby_sourcefile_string);
    rb_gc_mark(p->delayed);
    rb_gc_mark(p->value);
    rb_gc_mark(p->result);
    rb_gc_mark(p->parsing_thread);
#endif
#ifdef YYMALLOC
    rb_gc_mark((VALUE)p->heap);
#endif
}

static void
parser_free(void *ptr)
{
    struct parser_params *p = (struct parser_params*)ptr;
    struct local_vars *local, *prev;

    if (p->parser_tokenbuf) {
        xfree(p->parser_tokenbuf);
    }
    for (local = p->parser_lvtbl; local; local = prev) {
	if (local->vars) xfree(local->vars);
	prev = local->prev;
	xfree(local);
    }
    xfree(p);
}

VALUE rb_parser_get_yydebug(VALUE);
VALUE rb_parser_set_yydebug(VALUE, VALUE);

#ifndef RIPPER
static struct parser_params *
parser_new(void)
{
    struct parser_params *p;

    p = ALLOC_N(struct parser_params, 1);
    MEMZERO(p, struct parser_params, 1);
    parser_initialize(p);
    return p;
}

VALUE
rb_parser_new(void)
{
    struct parser_params *p = parser_new();

    return Data_Wrap_Struct(0, parser_mark, parser_free, p);
}

/*
 *  call-seq:
 *    ripper#end_seen?   -> Boolean
 *
 *  Return if parsed source ended by +\_\_END\_\_+.
 *  This number starts from 1.
 */
VALUE
rb_parser_end_seen_p(VALUE vparser)
{
    struct parser_params *parser;

    Data_Get_Struct(vparser, struct parser_params, parser);
    return ruby__end__seen ? Qtrue : Qfalse;
}

/*
 *  call-seq:
 *    ripper#encoding   -> encoding
 *
 *  Return encoding of the source.
 */
VALUE
rb_parser_encoding(VALUE vparser)
{
    struct parser_params *parser;

    Data_Get_Struct(vparser, struct parser_params, parser);
    return rb_enc_from_encoding(parser->enc);
}

/*
 *  call-seq:
 *    ripper.yydebug   -> true or false
 *
 *  Get yydebug.
 */
VALUE
rb_parser_get_yydebug(VALUE self)
{
    struct parser_params *parser;

    Data_Get_Struct(self, struct parser_params, parser);
    return yydebug ? Qtrue : Qfalse;
}

/*
 *  call-seq:
 *    ripper.yydebug = flag
 *
 *  Set yydebug.
 */
VALUE
rb_parser_set_yydebug(VALUE self, VALUE flag)
{
    struct parser_params *parser;

    Data_Get_Struct(self, struct parser_params, parser);
    yydebug = RTEST(flag);
    return flag;
}

#ifdef YYMALLOC
#define HEAPCNT(n, size) ((n) * (size) / sizeof(YYSTYPE))
#define NEWHEAP() rb_node_newnode(NODE_ALLOCA, 0, (VALUE)parser->heap, 0)
#define ADD2HEAP(n, c, p) ((parser->heap = (n))->u1.node = (p), \
			   (n)->u3.cnt = (c), (p))

void *
rb_parser_malloc(struct parser_params *parser, size_t size)
{
    size_t cnt = HEAPCNT(1, size);
    NODE *n = NEWHEAP();
    void *ptr = xmalloc(size);

    return ADD2HEAP(n, cnt, ptr);
}

void *
rb_parser_calloc(struct parser_params *parser, size_t nelem, size_t size)
{
    size_t cnt = HEAPCNT(nelem, size);
    NODE *n = NEWHEAP();
    void *ptr = xcalloc(nelem, size);

    return ADD2HEAP(n, cnt, ptr);
}

void *
rb_parser_realloc(struct parser_params *parser, void *ptr, size_t size)
{
    NODE *n;
    size_t cnt = HEAPCNT(1, size);

    if (ptr && (n = parser->heap) != NULL) {
	do {
	    if (n->u1.node == ptr) {
		n->u1.node = ptr = xrealloc(ptr, size);
		if (n->u3.cnt) n->u3.cnt = cnt;
		return ptr;
	    }
	} while ((n = n->u2.node) != NULL);
    }
    n = NEWHEAP();
    ptr = xrealloc(ptr, size);
    return ADD2HEAP(n, cnt, ptr);
}

void
rb_parser_free(struct parser_params *parser, void *ptr)
{
    NODE **prev = &parser->heap, *n;

    while ((n = *prev) != NULL) {
	if (n->u1.node == ptr) {
	    *prev = n->u2.node;
	    rb_gc_force_recycle((VALUE)n);
	    break;
	}
	prev = &n->u2.node;
    }
    xfree(ptr);
}
#endif
#endif

#ifdef RIPPER
#ifdef RIPPER_DEBUG
extern int rb_is_pointer_to_heap(VALUE);

/* :nodoc: */
static VALUE
ripper_validate_object(VALUE self, VALUE x)
{
    if (x == Qfalse) return x;
    if (x == Qtrue) return x;
    if (x == Qnil) return x;
    if (x == Qundef)
        rb_raise(rb_eArgError, "Qundef given");
    if (FIXNUM_P(x)) return x;
    if (SYMBOL_P(x)) return x;
    if (!rb_is_pointer_to_heap(x))
        rb_raise(rb_eArgError, "invalid pointer: %p", x);
    switch (TYPE(x)) {
      case T_STRING:
      case T_OBJECT:
      case T_ARRAY:
      case T_BIGNUM:
      case T_FLOAT:
        return x;
      case T_NODE:
        rb_raise(rb_eArgError, "NODE given: %p", x);
      default:
        rb_raise(rb_eArgError, "wrong type of ruby object: %p (%s)",
                 x, rb_obj_classname(x));
    }
    return x;
}
#endif

#define validate(x)

static VALUE
ripper_dispatch0(struct parser_params *parser, ID mid)
{
    return rb_funcall(parser->value, mid, 0);
}

static VALUE
ripper_dispatch1(struct parser_params *parser, ID mid, VALUE a)
{
    validate(a);
    return rb_funcall(parser->value, mid, 1, a);
}

static VALUE
ripper_dispatch2(struct parser_params *parser, ID mid, VALUE a, VALUE b)
{
    validate(a);
    validate(b);
    return rb_funcall(parser->value, mid, 2, a, b);
}

static VALUE
ripper_dispatch3(struct parser_params *parser, ID mid, VALUE a, VALUE b, VALUE c)
{
    validate(a);
    validate(b);
    validate(c);
    return rb_funcall(parser->value, mid, 3, a, b, c);
}

static VALUE
ripper_dispatch4(struct parser_params *parser, ID mid, VALUE a, VALUE b, VALUE c, VALUE d)
{
    validate(a);
    validate(b);
    validate(c);
    validate(d);
    return rb_funcall(parser->value, mid, 4, a, b, c, d);
}

static VALUE
ripper_dispatch5(struct parser_params *parser, ID mid, VALUE a, VALUE b, VALUE c, VALUE d, VALUE e)
{
    validate(a);
    validate(b);
    validate(c);
    validate(d);
    validate(e);
    return rb_funcall(parser->value, mid, 5, a, b, c, d, e);
}

static const struct kw_assoc {
    ID id;
    const char *name;
} keyword_to_name[] = {
    {keyword_class,	"class"},
    {keyword_module,	"module"},
    {keyword_def,	"def"},
    {keyword_undef,	"undef"},
    {keyword_begin,	"begin"},
    {keyword_rescue,	"rescue"},
    {keyword_ensure,	"ensure"},
    {keyword_end,	"end"},
    {keyword_if,	"if"},
    {keyword_unless,	"unless"},
    {keyword_then,	"then"},
    {keyword_elsif,	"elsif"},
    {keyword_else,	"else"},
    {keyword_case,	"case"},
    {keyword_when,	"when"},
    {keyword_while,	"while"},
    {keyword_until,	"until"},
    {keyword_for,	"for"},
    {keyword_break,	"break"},
    {keyword_next,	"next"},
    {keyword_redo,	"redo"},
    {keyword_retry,	"retry"},
    {keyword_in,	"in"},
    {keyword_do,	"do"},
    {keyword_do_cond,	"do"},
    {keyword_do_block,	"do"},
    {keyword_return,	"return"},
    {keyword_yield,	"yield"},
    {keyword_super,	"super"},
    {keyword_self,	"self"},
    {keyword_nil,	"nil"},
    {keyword_true,	"true"},
    {keyword_false,	"false"},
    {keyword_and,	"and"},
    {keyword_or,	"or"},
    {keyword_not,	"not"},
    {modifier_if,	"if"},
    {modifier_unless,	"unless"},
    {modifier_while,	"while"},
    {modifier_until,	"until"},
    {modifier_rescue,	"rescue"},
    {keyword_alias,	"alias"},
    {keyword_defined,	"defined?"},
    {keyword_BEGIN,	"BEGIN"},
    {keyword_END,	"END"},
    {keyword__LINE__,	"__LINE__"},
    {keyword__FILE__,	"__FILE__"},
    {0, NULL}
};

static const char*
keyword_id_to_str(ID id)
{
    const struct kw_assoc *a;

    for (a = keyword_to_name; a->id; a++) {
        if (a->id == id)
            return a->name;
    }
    return NULL;
}

static VALUE
ripper_id2sym(ID id)
{
    const char *name;
    char buf[8];

    if (id <= 256) {
        buf[0] = id;
        buf[1] = '\0';
        return ID2SYM(rb_intern(buf));
    }
    if ((name = keyword_id_to_str(id))) {
        return ID2SYM(rb_intern(name));
    }
    switch (id) {
      case tOROP:
        name = "||";
        break;
      case tANDOP:
        name = "&&";
        break;
      default:
        name = rb_id2name(id);
        if (!name) {
            rb_bug("cannot convert ID to string: %ld", (unsigned long)id);
        }
        break;
    }
    return ID2SYM(rb_intern(name));
}

static VALUE
ripper_intern(const char *s)
{
    return ID2SYM(rb_intern(s));
}

static void
ripper_compile_error(struct parser_params *parser, const char *fmt, ...)
{
    VALUE str;
    va_list args;

    va_start(args, fmt);
    str = rb_vsprintf(fmt, args);
    va_end(args);
    rb_funcall(parser->value, rb_intern("compile_error"), 1, str);
}

static void
ripper_warn0(struct parser_params *parser, const char *fmt)
{
    rb_funcall(parser->value, rb_intern("warn"), 1, STR_NEW2(fmt));
}

static void
ripper_warnI(struct parser_params *parser, const char *fmt, int a)
{
    rb_funcall(parser->value, rb_intern("warn"), 2,
               STR_NEW2(fmt), INT2NUM(a));
}

static void
ripper_warnS(struct parser_params *parser, const char *fmt, const char *str)
{
    rb_funcall(parser->value, rb_intern("warn"), 2,
    	       STR_NEW2(fmt), STR_NEW2(str));
}

static void
ripper_warning0(struct parser_params *parser, const char *fmt)
{
    rb_funcall(parser->value, rb_intern("warning"), 1, STR_NEW2(fmt));
}

#if 0				/* unused in ripper right now */
static void
ripper_warningS(struct parser_params *parser, const char *fmt, const char *str)
{
    rb_funcall(parser->value, rb_intern("warning"), 2,
    	       STR_NEW2(fmt), STR_NEW2(str));
}
#endif

static VALUE
ripper_lex_get_generic(struct parser_params *parser, VALUE src)
{
    return rb_funcall(src, ripper_id_gets, 0);
}

static VALUE
ripper_s_allocate(VALUE klass)
{
    struct parser_params *p;
    VALUE self;

    p = ALLOC_N(struct parser_params, 1);
    MEMZERO(p, struct parser_params, 1);
    self = Data_Wrap_Struct(klass, parser_mark, parser_free, p);
    p->value = self;
    return self;
}

#define ripper_initialized_p(r) ((r)->parser_lex_input != 0)

/*
 *  call-seq:
 *    Ripper.new(src, filename="(ripper)", lineno=1) -> ripper
 *
 *  Create a new Ripper object.
 *  _src_ must be a String, a IO, or an Object which has #gets method.
 *
 *  This method does not starts parsing.
 *  See also Ripper#parse and Ripper.parse.
 */
static VALUE
ripper_initialize(int argc, VALUE *argv, VALUE self)
{
    struct parser_params *parser;
    VALUE src, fname, lineno;
    VALUE fname2;

    Data_Get_Struct(self, struct parser_params, parser);
    rb_scan_args(argc, argv, "12", &src, &fname, &lineno);
    if (rb_obj_respond_to(src, ripper_id_gets, 0)) {
        parser->parser_lex_gets = ripper_lex_get_generic;
    }
    else {
        StringValue(src);
        parser->parser_lex_gets = lex_get_str;
    }
    parser->parser_lex_input = src;
    parser->eofp = Qfalse;
    if (NIL_P(fname)) {
        fname2 = STR_NEW2(" (ripper)");
    }
    else {
        StringValue(fname);
        fname2 = rb_str_new2(" ");
        rb_str_append(fname2, fname);
    }
    parser_initialize(parser);

    parser->parser_ruby_sourcefile_string = fname2;
    parser->parser_ruby_sourcefile = RSTRING_PTR(fname2)+1;
    parser->parser_ruby_sourceline = NIL_P(lineno) ? 0 : NUM2INT(lineno) - 1;

    return Qnil;
}

extern VALUE rb_thread_pass(void);

struct ripper_args {
    struct parser_params *parser;
    int argc;
    VALUE *argv;
};

static VALUE
ripper_parse0(VALUE parser_v)
{
    struct parser_params *parser;

    Data_Get_Struct(parser_v, struct parser_params, parser);
    parser_prepare(parser);
    ripper_yyparse((void*)parser);
    return parser->result;
}

static VALUE
ripper_ensure(VALUE parser_v)
{
    struct parser_params *parser;

    Data_Get_Struct(parser_v, struct parser_params, parser);
    parser->parsing_thread = Qnil;
    return Qnil;
}

/*
 *  call-seq:
 *    ripper#parse
 *
 *  Start parsing and returns the value of the root action.
 */
static VALUE
ripper_parse(VALUE self)
{
    struct parser_params *parser;

    Data_Get_Struct(self, struct parser_params, parser);
    if (!ripper_initialized_p(parser)) {
        rb_raise(rb_eArgError, "method called for uninitialized object");
    }
    if (!NIL_P(parser->parsing_thread)) {
        if (parser->parsing_thread == rb_thread_current())
            rb_raise(rb_eArgError, "Ripper#parse is not reentrant");
        else
            rb_raise(rb_eArgError, "Ripper#parse is not multithread-safe");
    }
    parser->parsing_thread = rb_thread_current();
    rb_ensure(ripper_parse0, self, ripper_ensure, self);

    return parser->result;
}

/*
 *  call-seq:
 *    ripper#column   -> Integer
 *
 *  Return column number of current parsing line.
 *  This number starts from 0.
 */
static VALUE
ripper_column(VALUE self)
{
    struct parser_params *parser;
    long col;

    Data_Get_Struct(self, struct parser_params, parser);
    if (!ripper_initialized_p(parser)) {
        rb_raise(rb_eArgError, "method called for uninitialized object");
    }
    if (NIL_P(parser->parsing_thread)) return Qnil;
    col = parser->tokp - parser->parser_lex_pbeg;
    return LONG2NUM(col);
}

/*
 *  call-seq:
 *    ripper#lineno   -> Integer
 *
 *  Return line number of current parsing line.
 *  This number starts from 1.
 */
static VALUE
ripper_lineno(VALUE self)
{
    struct parser_params *parser;

    Data_Get_Struct(self, struct parser_params, parser);
    if (!ripper_initialized_p(parser)) {
        rb_raise(rb_eArgError, "method called for uninitialized object");
    }
    if (NIL_P(parser->parsing_thread)) return Qnil;
    return INT2NUM(parser->parser_ruby_sourceline);
}

#ifdef RIPPER_DEBUG
/* :nodoc: */
static VALUE
ripper_assert_Qundef(VALUE self, VALUE obj, VALUE msg)
{
    StringValue(msg);
    if (obj == Qundef) {
        rb_raise(rb_eArgError, "%s", RSTRING_PTR(msg));
    }
    return Qnil;
}

/* :nodoc: */
static VALUE
ripper_value(VALUE self, VALUE obj)
{
    return ULONG2NUM(obj);
}
#endif

void
Init_ripper(void)
{
    VALUE Ripper;

    Ripper = rb_define_class("Ripper", rb_cObject);
    rb_define_const(Ripper, "Version", rb_str_new2(RIPPER_VERSION));
    rb_define_alloc_func(Ripper, ripper_s_allocate);
    rb_define_method(Ripper, "initialize", ripper_initialize, -1);
    rb_define_method(Ripper, "parse", ripper_parse, 0);
    rb_define_method(Ripper, "column", ripper_column, 0);
    rb_define_method(Ripper, "lineno", ripper_lineno, 0);
    rb_define_method(Ripper, "end_seen?", rb_parser_end_seen_p, 0);
    rb_define_method(Ripper, "encoding", rb_parser_encoding, 0);
    rb_define_method(Ripper, "yydebug", rb_parser_get_yydebug, 0);
    rb_define_method(Ripper, "yydebug=", rb_parser_set_yydebug, 1);
#ifdef RIPPER_DEBUG
    rb_define_method(rb_mKernel, "assert_Qundef", ripper_assert_Qundef, 2);
    rb_define_method(rb_mKernel, "rawVALUE", ripper_value, 1);
    rb_define_method(rb_mKernel, "validate_object", ripper_validate_object, 1);
#endif

    ripper_id_gets = rb_intern("gets");
    ripper_init_eventids1(Ripper);
    ripper_init_eventids2(Ripper);
    /* ensure existing in symbol table */
    rb_intern("||");
    rb_intern("&&");
}
#endif /* RIPPER */

