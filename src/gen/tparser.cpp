/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 9 "build/parser.y"

/* *SJD* essential prototypes for C++ compilation */
int yylex();
int yyerror(const char *s);
#include <stdlib.h>
#define xmalloc malloc

#define MSDOS
#include "common.h"
using namespace Parser;
using namespace Expressions;

#define YYERROR_VERBOSE 1
#define YYDEBUG 1

#ifndef YYPURE
 #define YYPURE
#endif 

/* some shortcuts */
typedef Stack<bool,40> BoolStack;
BoolStack als(false);
BoolStack dcl_stack;
BoolStack typedef_stack;

bool dump_it = false;
PEntry last_type_entry;

PExpr gFunInit = NULL;  // used to flag pure virtual methods...

void dcl_set(bool yes, bool comma_flag) {
 dcl_stack.push(state.in_declaration);
 if (dcl_stack.depth() > 40) outln("runaway dcl stack");
 state.in_declaration = yes;
 als.push(comma_flag);  /* force ',' _not_ to be COMMA */
}

void dcl_reset() { 
 state.in_declaration = dcl_stack.pop();
 als.pop();
}

void force_comma_flag() { 
 als.clear();
 dcl_stack.clear();
 dcl_set(false,false);
}

bool in_arg_list()   {
 return als.TOS();
}

inline void enter_arglist() { dcl_set(false); }

void leave_arglist() { dcl_reset(); }

string tag_name; /* A fiddle */
bool IEF=false;
/*BoolStack ief_stack;*/
void IEF_set()   { /*ief_stack.push(IEF);*/ IEF=true; }
void IEF_reset() { IEF=false; /*ief_stack.pop();*/ } 

void ttpush(TType t) { tpush(AsType(t)); }

void raise_error(string msg) 
{
 int yyerror(const char *);

 if (state.err != "") { msg = state.err; state.err = ""; }
 state.reset();
 als.clear(); als.push(false); 
 yyerror(msg.c_str());
}

bool check_error()
{
 if (state.err != "") {
    raise_error(state.err);
	state.err = "";
	return true;
 }
 return false;
}


#line 161 "gen/tparser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "tparser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN = 3,                      /* TOKEN  */
  YYSYMBOL_IDEN = 4,                       /* IDEN  */
  YYSYMBOL_CONSTANT = 5,                   /* CONSTANT  */
  YYSYMBOL_TYPENAME = 6,                   /* TYPENAME  */
  YYSYMBOL_TYPENAME_FUNCTION = 7,          /* TYPENAME_FUNCTION  */
  YYSYMBOL_TEMPLATE_NAME = 8,              /* TEMPLATE_NAME  */
  YYSYMBOL_TEMPLATE_NAME_EXPR = 9,         /* TEMPLATE_NAME_EXPR  */
  YYSYMBOL_THIS_CLASSNAME = 10,            /* THIS_CLASSNAME  */
  YYSYMBOL_FLOAT = 11,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 12,                    /* DOUBLE  */
  YYSYMBOL_UNSIGNED = 13,                  /* UNSIGNED  */
  YYSYMBOL_INT = 14,                       /* INT  */
  YYSYMBOL_SHORT = 15,                     /* SHORT  */
  YYSYMBOL_LONG = 16,                      /* LONG  */
  YYSYMBOL_CHAR = 17,                      /* CHAR  */
  YYSYMBOL_VOID = 18,                      /* VOID  */
  YYSYMBOL_BOOL = 19,                      /* BOOL  */
  YYSYMBOL_TYPEDEF = 20,                   /* TYPEDEF  */
  YYSYMBOL_CLASS = 21,                     /* CLASS  */
  YYSYMBOL_STRUCT = 22,                    /* STRUCT  */
  YYSYMBOL_ENUM = 23,                      /* ENUM  */
  YYSYMBOL_OPERATOR = 24,                  /* OPERATOR  */
  YYSYMBOL_GOTO = 25,                      /* GOTO  */
  YYSYMBOL_UNION = 26,                     /* UNION  */
  YYSYMBOL_STATIC_CAST = 27,               /* STATIC_CAST  */
  YYSYMBOL_CONST_CAST = 28,                /* CONST_CAST  */
  YYSYMBOL_DYNAMIC_CAST = 29,              /* DYNAMIC_CAST  */
  YYSYMBOL_REINTERPRET_CAST = 30,          /* REINTERPRET_CAST  */
  YYSYMBOL_STRUCT_X = 31,                  /* STRUCT_X  */
  YYSYMBOL_CLASS_X = 32,                   /* CLASS_X  */
  YYSYMBOL_STRUCT_Y = 33,                  /* STRUCT_Y  */
  YYSYMBOL_CLASS_Y = 34,                   /* CLASS_Y  */
  YYSYMBOL_UNION_Y = 35,                   /* UNION_Y  */
  YYSYMBOL_IF = 36,                        /* IF  */
  YYSYMBOL_ELSE = 37,                      /* ELSE  */
  YYSYMBOL_WHILE = 38,                     /* WHILE  */
  YYSYMBOL_DO = 39,                        /* DO  */
  YYSYMBOL_FOR = 40,                       /* FOR  */
  YYSYMBOL_SWITCH = 41,                    /* SWITCH  */
  YYSYMBOL_CASE = 42,                      /* CASE  */
  YYSYMBOL_RETURN = 43,                    /* RETURN  */
  YYSYMBOL_CONTINUE = 44,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 45,                     /* BREAK  */
  YYSYMBOL_DEFAULT = 46,                   /* DEFAULT  */
  YYSYMBOL_NAMESPACE = 47,                 /* NAMESPACE  */
  YYSYMBOL_USING = 48,                     /* USING  */
  YYSYMBOL_TRY = 49,                       /* TRY  */
  YYSYMBOL_CATCH = 50,                     /* CATCH  */
  YYSYMBOL_THROW = 51,                     /* THROW  */
  YYSYMBOL_TEMPLATE = 52,                  /* TEMPLATE  */
  YYSYMBOL_EXTERN = 53,                    /* EXTERN  */
  YYSYMBOL_THREEDOT = 54,                  /* THREEDOT  */
  YYSYMBOL_TYPEOF = 55,                    /* TYPEOF  */
  YYSYMBOL_EXPLICIT = 56,                  /* EXPLICIT  */
  YYSYMBOL_FRIEND = 57,                    /* FRIEND  */
  YYSYMBOL_LAMBDA = 58,                    /* LAMBDA  */
  YYSYMBOL_FAKE_INIT_LIST = 59,            /* FAKE_INIT_LIST  */
  YYSYMBOL_CONST = 60,                     /* CONST  */
  YYSYMBOL_STATIC = 61,                    /* STATIC  */
  YYSYMBOL_STDCALL = 62,                   /* STDCALL  */
  YYSYMBOL_API = 63,                       /* API  */
  YYSYMBOL_VIRTUAL = 64,                   /* VIRTUAL  */
  YYSYMBOL_PRIVATE = 65,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 66,                 /* PROTECTED  */
  YYSYMBOL_PUBLIC = 67,                    /* PUBLIC  */
  YYSYMBOL_COMMA = 68,                     /* COMMA  */
  YYSYMBOL_ASSIGN = 69,                    /* ASSIGN  */
  YYSYMBOL_MUL_A = 70,                     /* MUL_A  */
  YYSYMBOL_DIV_A = 71,                     /* DIV_A  */
  YYSYMBOL_MOD_A = 72,                     /* MOD_A  */
  YYSYMBOL_ADD_A = 73,                     /* ADD_A  */
  YYSYMBOL_MINUS_A = 74,                   /* MINUS_A  */
  YYSYMBOL_SHL_A = 75,                     /* SHL_A  */
  YYSYMBOL_SHR_A = 76,                     /* SHR_A  */
  YYSYMBOL_BAND_A = 77,                    /* BAND_A  */
  YYSYMBOL_BOR_A = 78,                     /* BOR_A  */
  YYSYMBOL_XOR_A = 79,                     /* XOR_A  */
  YYSYMBOL_ARITH_IF = 80,                  /* ARITH_IF  */
  YYSYMBOL_LOG_OR = 81,                    /* LOG_OR  */
  YYSYMBOL_LOG_AND = 82,                   /* LOG_AND  */
  YYSYMBOL_BIN_OR = 83,                    /* BIN_OR  */
  YYSYMBOL_BIN_XOR = 84,                   /* BIN_XOR  */
  YYSYMBOL_BIN_AND = 85,                   /* BIN_AND  */
  YYSYMBOL_EQUAL = 86,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 87,                 /* NOT_EQUAL  */
  YYSYMBOL_LESS_THAN = 88,                 /* LESS_THAN  */
  YYSYMBOL_LEQ = 89,                       /* LEQ  */
  YYSYMBOL_GREATER = 90,                   /* GREATER  */
  YYSYMBOL_GEQ = 91,                       /* GEQ  */
  YYSYMBOL_LSHIFT = 92,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 93,                    /* RSHIFT  */
  YYSYMBOL_PLUS = 94,                      /* PLUS  */
  YYSYMBOL_MINUS = 95,                     /* MINUS  */
  YYSYMBOL_STAR = 96,                      /* STAR  */
  YYSYMBOL_DIVIDE = 97,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 98,                    /* MODULO  */
  YYSYMBOL_MEMBER_ARROW = 99,              /* MEMBER_ARROW  */
  YYSYMBOL_MEMBER_DOT = 100,               /* MEMBER_DOT  */
  YYSYMBOL_NEW = 101,                      /* NEW  */
  YYSYMBOL_DELETE = 102,                   /* DELETE  */
  YYSYMBOL_TYPECAST = 103,                 /* TYPECAST  */
  YYSYMBOL_DEREF = 104,                    /* DEREF  */
  YYSYMBOL_ADDR = 105,                     /* ADDR  */
  YYSYMBOL_UPLUS = 106,                    /* UPLUS  */
  YYSYMBOL_UMINUS = 107,                   /* UMINUS  */
  YYSYMBOL_LOG_NOT = 108,                  /* LOG_NOT  */
  YYSYMBOL_BIN_NOT = 109,                  /* BIN_NOT  */
  YYSYMBOL_INCR = 110,                     /* INCR  */
  YYSYMBOL_DECR = 111,                     /* DECR  */
  YYSYMBOL_SIZEOF = 112,                   /* SIZEOF  */
  YYSYMBOL_TYPE_CONSTRUCT = 113,           /* TYPE_CONSTRUCT  */
  YYSYMBOL_FUN_CALL = 114,                 /* FUN_CALL  */
  YYSYMBOL_ARRAY = 115,                    /* ARRAY  */
  YYSYMBOL_ARROW = 116,                    /* ARROW  */
  YYSYMBOL_DOT = 117,                      /* DOT  */
  YYSYMBOL_BINARY_SCOPE = 118,             /* BINARY_SCOPE  */
  YYSYMBOL_UNARY_SCOPE = 119,              /* UNARY_SCOPE  */
  YYSYMBOL_120_ = 120,                     /* '{'  */
  YYSYMBOL_121_ = 121,                     /* '}'  */
  YYSYMBOL_122_ = 122,                     /* ';'  */
  YYSYMBOL_123_ = 123,                     /* ':'  */
  YYSYMBOL_124_ = 124,                     /* '('  */
  YYSYMBOL_125_ = 125,                     /* ')'  */
  YYSYMBOL_126_ = 126,                     /* '['  */
  YYSYMBOL_127_ = 127,                     /* ']'  */
  YYSYMBOL_128_ = 128,                     /* ','  */
  YYSYMBOL_YYACCEPT = 129,                 /* $accept  */
  YYSYMBOL_program = 130,                  /* program  */
  YYSYMBOL_statement_list = 131,           /* statement_list  */
  YYSYMBOL_block = 132,                    /* block  */
  YYSYMBOL_133_1 = 133,                    /* $@1  */
  YYSYMBOL_statement = 134,                /* statement  */
  YYSYMBOL_declaration = 135,              /* declaration  */
  YYSYMBOL_typedef_stmt = 136,             /* typedef_stmt  */
  YYSYMBOL_137_2 = 137,                    /* $@2  */
  YYSYMBOL_declaration_stmt = 138,         /* declaration_stmt  */
  YYSYMBOL_this_classname = 139,           /* this_classname  */
  YYSYMBOL_construct_destruct = 140,       /* construct_destruct  */
  YYSYMBOL_conversion_operator = 141,      /* conversion_operator  */
  YYSYMBOL_function_front = 142,           /* function_front  */
  YYSYMBOL_explicit_mod = 143,             /* explicit_mod  */
  YYSYMBOL_ctor_dtor_dcl = 144,            /* ctor_dtor_dcl  */
  YYSYMBOL_function_declaration = 145,     /* function_declaration  */
  YYSYMBOL_extern_c_declaration = 146,     /* extern_c_declaration  */
  YYSYMBOL_any_declaration = 147,          /* any_declaration  */
  YYSYMBOL_extern_c = 148,                 /* extern_c  */
  YYSYMBOL_extern_qualifier = 149,         /* extern_qualifier  */
  YYSYMBOL_function_definition = 150,      /* function_definition  */
  YYSYMBOL_ctor_dtor = 151,                /* ctor_dtor  */
  YYSYMBOL_poss_class_init_list = 152,     /* poss_class_init_list  */
  YYSYMBOL_153_3 = 153,                    /* $@3  */
  YYSYMBOL_class_init_list = 154,          /* class_init_list  */
  YYSYMBOL_class_init_item = 155,          /* class_init_item  */
  YYSYMBOL_type_expr = 156,                /* type_expr  */
  YYSYMBOL_poss_const = 157,               /* poss_const  */
  YYSYMBOL_mod_type_name = 158,            /* mod_type_name  */
  YYSYMBOL_modifiers = 159,                /* modifiers  */
  YYSYMBOL_open_parens = 160,              /* open_parens  */
  YYSYMBOL_close_parens = 161,             /* close_parens  */
  YYSYMBOL_type_name = 162,                /* type_name  */
  YYSYMBOL_integer = 163,                  /* integer  */
  YYSYMBOL_pointer_expr = 164,             /* pointer_expr  */
  YYSYMBOL_array_expr = 165,               /* array_expr  */
  YYSYMBOL_166_4 = 166,                    /* $@4  */
  YYSYMBOL_tname_expr = 167,               /* tname_expr  */
  YYSYMBOL_tname_exp2 = 168,               /* tname_exp2  */
  YYSYMBOL_token = 169,                    /* token  */
  YYSYMBOL_begin_list = 170,               /* begin_list  */
  YYSYMBOL_end_list = 171,                 /* end_list  */
  YYSYMBOL_arg_list = 172,                 /* arg_list  */
  YYSYMBOL_type_list = 173,                /* type_list  */
  YYSYMBOL_type_expr_init = 174,           /* type_expr_init  */
  YYSYMBOL_init_tname_expr = 175,          /* init_tname_expr  */
  YYSYMBOL_tname_expr_list = 176,          /* tname_expr_list  */
  YYSYMBOL_poss_int_const = 177,           /* poss_int_const  */
  YYSYMBOL_init_assign = 178,              /* init_assign  */
  YYSYMBOL_poss_initialization = 179,      /* poss_initialization  */
  YYSYMBOL_180_5 = 180,                    /* $@5  */
  YYSYMBOL_brace_expr = 181,               /* brace_expr  */
  YYSYMBOL_brace_item = 182,               /* brace_item  */
  YYSYMBOL_brace_list = 183,               /* brace_list  */
  YYSYMBOL_access_modifier = 184,          /* access_modifier  */
  YYSYMBOL_poss_access_modifier = 185,     /* poss_access_modifier  */
  YYSYMBOL_class_or_struct = 186,          /* class_or_struct  */
  YYSYMBOL_class_or_struct_ex = 187,       /* class_or_struct_ex  */
  YYSYMBOL_poss_derived = 188,             /* poss_derived  */
  YYSYMBOL_token_or_typename = 189,        /* token_or_typename  */
  YYSYMBOL_class_name = 190,               /* class_name  */
  YYSYMBOL_class_id = 191,                 /* class_id  */
  YYSYMBOL_192_6 = 192,                    /* $@6  */
  YYSYMBOL_class_declaration = 193,        /* class_declaration  */
  YYSYMBOL_194_7 = 194,                    /* $@7  */
  YYSYMBOL_access_specifier = 195,         /* access_specifier  */
  YYSYMBOL_friend_declaration = 196,       /* friend_declaration  */
  YYSYMBOL_197_8 = 197,                    /* $@8  */
  YYSYMBOL_enum_stmt = 198,                /* enum_stmt  */
  YYSYMBOL_199_9 = 199,                    /* $@9  */
  YYSYMBOL_200_10 = 200,                   /* $@10  */
  YYSYMBOL_poss_enum_list = 201,           /* poss_enum_list  */
  YYSYMBOL_poss_tag = 202,                 /* poss_tag  */
  YYSYMBOL_enum_item = 203,                /* enum_item  */
  YYSYMBOL_enum_list = 204,                /* enum_list  */
  YYSYMBOL_namespace_declaration = 205,    /* namespace_declaration  */
  YYSYMBOL_206_11 = 206,                   /* $@11  */
  YYSYMBOL_207_12 = 207,                   /* $@12  */
  YYSYMBOL_poss_class_name = 208,          /* poss_class_name  */
  YYSYMBOL_using_directive = 209,          /* using_directive  */
  YYSYMBOL_using_declaration = 210,        /* using_declaration  */
  YYSYMBOL_goto_stmt = 211,                /* goto_stmt  */
  YYSYMBOL_212_13 = 212,                   /* $@13  */
  YYSYMBOL_213_14 = 213,                   /* $@14  */
  YYSYMBOL_goto_label = 214,               /* goto_label  */
  YYSYMBOL_scope = 215,                    /* scope  */
  YYSYMBOL_global_scope = 216,             /* global_scope  */
  YYSYMBOL_end_scope = 217,                /* end_scope  */
  YYSYMBOL_assign_op = 218,                /* assign_op  */
  YYSYMBOL_scoped_name = 219,              /* scoped_name  */
  YYSYMBOL_expr = 220,                     /* expr  */
  YYSYMBOL_poss_size = 221,                /* poss_size  */
  YYSYMBOL_type_expression = 222,          /* type_expression  */
  YYSYMBOL_typecast_type = 223,            /* typecast_type  */
  YYSYMBOL_type_bracket = 224,             /* type_bracket  */
  YYSYMBOL__expr = 225,                    /* _expr  */
  YYSYMBOL_226_15 = 226,                   /* $@15  */
  YYSYMBOL_227_16 = 227,                   /* $@16  */
  YYSYMBOL_228_17 = 228,                   /* $@17  */
  YYSYMBOL_229_18 = 229,                   /* $@18  */
  YYSYMBOL_poss_array = 230,               /* poss_array  */
  YYSYMBOL_function_arg_list = 231,        /* function_arg_list  */
  YYSYMBOL_init_list = 232,                /* init_list  */
  YYSYMBOL_expr_list = 233,                /* expr_list  */
  YYSYMBOL_condition = 234,                /* condition  */
  YYSYMBOL_poss_expr = 235,                /* poss_expr  */
  YYSYMBOL_controlled_statement = 236,     /* controlled_statement  */
  YYSYMBOL_237_19 = 237,                   /* $@19  */
  YYSYMBOL_if_front = 238,                 /* if_front  */
  YYSYMBOL_if_stmt = 239,                  /* if_stmt  */
  YYSYMBOL_if_else_stmt = 240,             /* if_else_stmt  */
  YYSYMBOL_241_20 = 241,                   /* $@20  */
  YYSYMBOL_while_stmt = 242,               /* while_stmt  */
  YYSYMBOL_243_21 = 243,                   /* $@21  */
  YYSYMBOL_244_22 = 244,                   /* $@22  */
  YYSYMBOL_do_stmt = 245,                  /* do_stmt  */
  YYSYMBOL_246_23 = 246,                   /* $@23  */
  YYSYMBOL_for_init = 247,                 /* for_init  */
  YYSYMBOL_for_stmt = 248,                 /* for_stmt  */
  YYSYMBOL_249_24 = 249,                   /* $@24  */
  YYSYMBOL_250_25 = 250,                   /* $@25  */
  YYSYMBOL_251_26 = 251,                   /* $@26  */
  YYSYMBOL_switch_stmt = 252,              /* switch_stmt  */
  YYSYMBOL_253_27 = 253,                   /* $@27  */
  YYSYMBOL_return_stmt = 254,              /* return_stmt  */
  YYSYMBOL_case_label = 255,               /* case_label  */
  YYSYMBOL_break_stmt = 256,               /* break_stmt  */
  YYSYMBOL_continue_stmt = 257,            /* continue_stmt  */
  YYSYMBOL_try_catch_stmt = 258,           /* try_catch_stmt  */
  YYSYMBOL_try_block = 259,                /* try_block  */
  YYSYMBOL_260_28 = 260,                   /* $@28  */
  YYSYMBOL_except_block = 261,             /* except_block  */
  YYSYMBOL_catch_block = 262,              /* catch_block  */
  YYSYMBOL_263_29 = 263,                   /* $@29  */
  YYSYMBOL_catch_block_list = 264,         /* catch_block_list  */
  YYSYMBOL_throw_stmt = 265,               /* throw_stmt  */
  YYSYMBOL_typename_function = 266,        /* typename_function  */
  YYSYMBOL_typename_class = 267,           /* typename_class  */
  YYSYMBOL_typename_expr = 268,            /* typename_expr  */
  YYSYMBOL_template_class = 269,           /* template_class  */
  YYSYMBOL_template_expr = 270,            /* template_expr  */
  YYSYMBOL_template_header = 271,          /* template_header  */
  YYSYMBOL_template_function_declaration = 272, /* template_function_declaration  */
  YYSYMBOL_template_class_declaration = 273, /* template_class_declaration  */
  YYSYMBOL_struct_or_class_x = 274,        /* struct_or_class_x  */
  YYSYMBOL_template_class_header = 275,    /* template_class_header  */
  YYSYMBOL_template_class_name = 276,      /* template_class_name  */
  YYSYMBOL_begin_templ_list = 277,         /* begin_templ_list  */
  YYSYMBOL_end_templ_list = 278,           /* end_templ_list  */
  YYSYMBOL_template_type_list = 279,       /* template_type_list  */
  YYSYMBOL_templ_item_list = 280,          /* templ_item_list  */
  YYSYMBOL_class_item = 281,               /* class_item  */
  YYSYMBOL_class_parm = 282,               /* class_parm  */
  YYSYMBOL_templ_item = 283                /* templ_item  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  212
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3447

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  129
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  155
/* YYNRULES -- Number of rules.  */
#define YYNRULES  357
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  573

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   374


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     124,   125,     2,     2,   128,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   123,   122,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   126,     2,   127,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   120,     2,   121,     2,     2,     2,     2,
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
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   158,   158,   160,   161,   162,   166,   166,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   205,   215,
     214,   221,   222,   227,   238,   239,   247,   255,   259,   264,
     273,   281,   282,   283,   297,   298,   299,   303,   304,   308,
     312,   318,   320,   322,   324,   329,   335,   337,   336,   344,
     345,   346,   350,   359,   368,   372,   373,   377,   378,   379,
     380,   384,   385,   386,   387,   390,   393,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   416,   417,
     418,   423,   427,   431,   431,   436,   437,   438,   439,   442,
     443,   444,   445,   447,   448,   449,   453,   454,   455,   458,
     462,   465,   469,   472,   473,   474,   475,   482,   491,   501,
     502,   503,   506,   507,   513,   516,   517,   521,   524,   524,
     528,   536,   539,   540,   543,   544,   554,   555,   556,   559,
     559,   562,   562,   562,   565,   566,   567,   570,   571,   576,
     577,   580,   581,   582,   586,   589,   589,   596,   595,   611,
     615,   620,   620,   621,   631,   632,   631,   640,   641,   644,
     645,   646,   650,   656,   657,   658,   665,   666,   665,   674,
     675,   679,   690,   692,   694,   700,   700,   700,   705,   706,
     713,   718,   722,   726,   726,   726,   726,   726,   727,   727,
     727,   727,   727,   730,   731,   733,   737,   741,   742,   745,
     749,   749,   749,   749,   752,   758,   759,   760,   762,   763,
     764,   765,   766,   767,   768,   770,   771,   773,   774,   775,
     776,   777,   778,   779,   780,   781,   783,   784,   786,   787,
     788,   789,   793,   797,   798,   799,   800,   803,   803,   806,
     808,   809,   810,   812,   815,   818,   822,   823,   824,   825,
     826,   827,   829,   832,   835,   834,   840,   839,   844,   843,
     849,   852,   855,   856,   863,   864,   868,   874,   875,   876,
     881,   885,   886,   890,   890,   896,   900,   905,   904,   910,
     911,   910,   917,   917,   922,   923,   924,   928,   929,   931,
     928,   938,   938,   942,   947,   949,   953,   957,   964,   970,
     969,   976,   984,   983,   990,   991,   995,  1002,  1003,  1008,
    1009,  1010,  1015,  1016,  1017,  1021,  1026,  1032,  1037,  1045,
    1051,  1060,  1060,  1064,  1068,  1069,  1073,  1075,  1079,  1080,
    1085,  1086,  1090,  1091,  1095,  1103,  1107,  1108
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN", "IDEN",
  "CONSTANT", "TYPENAME", "TYPENAME_FUNCTION", "TEMPLATE_NAME",
  "TEMPLATE_NAME_EXPR", "THIS_CLASSNAME", "FLOAT", "DOUBLE", "UNSIGNED",
  "INT", "SHORT", "LONG", "CHAR", "VOID", "BOOL", "TYPEDEF", "CLASS",
  "STRUCT", "ENUM", "OPERATOR", "GOTO", "UNION", "STATIC_CAST",
  "CONST_CAST", "DYNAMIC_CAST", "REINTERPRET_CAST", "STRUCT_X", "CLASS_X",
  "STRUCT_Y", "CLASS_Y", "UNION_Y", "IF", "ELSE", "WHILE", "DO", "FOR",
  "SWITCH", "CASE", "RETURN", "CONTINUE", "BREAK", "DEFAULT", "NAMESPACE",
  "USING", "TRY", "CATCH", "THROW", "TEMPLATE", "EXTERN", "THREEDOT",
  "TYPEOF", "EXPLICIT", "FRIEND", "LAMBDA", "FAKE_INIT_LIST", "CONST",
  "STATIC", "STDCALL", "API", "VIRTUAL", "PRIVATE", "PROTECTED", "PUBLIC",
  "COMMA", "ASSIGN", "MUL_A", "DIV_A", "MOD_A", "ADD_A", "MINUS_A",
  "SHL_A", "SHR_A", "BAND_A", "BOR_A", "XOR_A", "ARITH_IF", "LOG_OR",
  "LOG_AND", "BIN_OR", "BIN_XOR", "BIN_AND", "EQUAL", "NOT_EQUAL",
  "LESS_THAN", "LEQ", "GREATER", "GEQ", "LSHIFT", "RSHIFT", "PLUS",
  "MINUS", "STAR", "DIVIDE", "MODULO", "MEMBER_ARROW", "MEMBER_DOT", "NEW",
  "DELETE", "TYPECAST", "DEREF", "ADDR", "UPLUS", "UMINUS", "LOG_NOT",
  "BIN_NOT", "INCR", "DECR", "SIZEOF", "TYPE_CONSTRUCT", "FUN_CALL",
  "ARRAY", "ARROW", "DOT", "BINARY_SCOPE", "UNARY_SCOPE", "'{'", "'}'",
  "';'", "':'", "'('", "')'", "'['", "']'", "','", "$accept", "program",
  "statement_list", "block", "$@1", "statement", "declaration",
  "typedef_stmt", "$@2", "declaration_stmt", "this_classname",
  "construct_destruct", "conversion_operator", "function_front",
  "explicit_mod", "ctor_dtor_dcl", "function_declaration",
  "extern_c_declaration", "any_declaration", "extern_c",
  "extern_qualifier", "function_definition", "ctor_dtor",
  "poss_class_init_list", "$@3", "class_init_list", "class_init_item",
  "type_expr", "poss_const", "mod_type_name", "modifiers", "open_parens",
  "close_parens", "type_name", "integer", "pointer_expr", "array_expr",
  "$@4", "tname_expr", "tname_exp2", "token", "begin_list", "end_list",
  "arg_list", "type_list", "type_expr_init", "init_tname_expr",
  "tname_expr_list", "poss_int_const", "init_assign",
  "poss_initialization", "$@5", "brace_expr", "brace_item", "brace_list",
  "access_modifier", "poss_access_modifier", "class_or_struct",
  "class_or_struct_ex", "poss_derived", "token_or_typename", "class_name",
  "class_id", "$@6", "class_declaration", "$@7", "access_specifier",
  "friend_declaration", "$@8", "enum_stmt", "$@9", "$@10",
  "poss_enum_list", "poss_tag", "enum_item", "enum_list",
  "namespace_declaration", "$@11", "$@12", "poss_class_name",
  "using_directive", "using_declaration", "goto_stmt", "$@13", "$@14",
  "goto_label", "scope", "global_scope", "end_scope", "assign_op",
  "scoped_name", "expr", "poss_size", "type_expression", "typecast_type",
  "type_bracket", "_expr", "$@15", "$@16", "$@17", "$@18", "poss_array",
  "function_arg_list", "init_list", "expr_list", "condition", "poss_expr",
  "controlled_statement", "$@19", "if_front", "if_stmt", "if_else_stmt",
  "$@20", "while_stmt", "$@21", "$@22", "do_stmt", "$@23", "for_init",
  "for_stmt", "$@24", "$@25", "$@26", "switch_stmt", "$@27", "return_stmt",
  "case_label", "break_stmt", "continue_stmt", "try_catch_stmt",
  "try_block", "$@28", "except_block", "catch_block", "$@29",
  "catch_block_list", "throw_stmt", "typename_function", "typename_class",
  "typename_expr", "template_class", "template_expr", "template_header",
  "template_function_declaration", "template_class_declaration",
  "struct_or_class_x", "template_class_header", "template_class_name",
  "begin_templ_list", "end_templ_list", "template_type_list",
  "templ_item_list", "class_item", "class_parm", "templ_item", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-340)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-333)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     679,  -102,   -76,    20,  -340,  -340,   -44,    23,    23,  -340,
    -340,  -340,   230,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  3121,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,   -21,  -340,  -340,    27,    47,  2275,  1983,
      35,    70,    81,  -340,   367,  -340,  1983,    23,   207,    89,
    -340,   204,  2009,   743,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  2275,  2275,  2275,   868,   105,  2275,  2275,  2099,  2275,
    2275,   115,  -340,  -340,  -340,  1944,   241,   804,  -340,  -340,
    -340,  -340,  -340,   124,    15,    45,    17,  -340,  -340,  -340,
    2413,  2009,  -340,  -340,   451,  1887,  -340,  -340,   126,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
     181,   247,  -340,   131,   174,  2882,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,   214,  -340,
    -340,   147,  -340,  -340,  3003,  -340,  -340,    99,  -340,  -340,
    -340,   141,  2387,  -340,  -340,  -340,   580,  -340,  -340,  -340,
    2009,    33,  -340,   -20,   302,   288,  2275,  -340,   -21,  -340,
    -340,  2275,  -340,  -340,  2275,    34,   172,  -340,   178,  -340,
    -340,  -340,   211,   295,   426,   180,   183,   186,   195,  -340,
    -340,  -340,  2275,   211,  2009,   305,   124,   199,   199,    17,
    -340,   225,  -340,   938,   938,   938,   202,    77,   196,  2275,
     938,   938,  -340,   938,   938,   938,  1944,  1090,  -340,   414,
     197,  2646,  -340,  -340,  -340,  3062,    74,  -340,  -340,  -340,
    -340,  -340,  -340,  1090,  -340,   124,   206,   212,    17,  -340,
    -340,  -340,  -340,  -340,   264,   404,    97,    84,   114,  -340,
     198,   217,   170,   743,  -340,  -340,   213,   211,  -340,  -340,
    -340,   147,  -340,  -340,  3121,   205,  2275,  2275,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  2275,  2275,
    2275,  2275,  2275,  2275,  2275,  2275,  2275,  2275,  2275,  2275,
    2275,  2275,  2275,  2275,  2275,  2275,  2275,  -340,  2275,  -340,
    -340,  -340,  -340,  2275,  2275,  -340,   303,  1700,   124,   214,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,    23,  -340,
    -340,  2882,   -29,  -340,   175,  -340,  -340,  -340,   -41,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,   -20,   -20,
     124,  -340,   216,  -340,   304,  1822,   219,  -340,  -340,  -340,
    -340,    23,  -340,  -340,  -340,  -340,   224,    23,  -340,  -340,
    1090,  -340,  -340,   222,   226,  -340,   229,    84,   -44,  2275,
    -340,  -340,  -340,   938,   232,  2705,  1212,   228,  2275,  -340,
    -340,   -11,   234,   233,  -340,  -340,   199,  1334,   238,  -340,
     404,   228,   359,   122,  -340,  -340,  -340,  -340,   358,  -340,
     926,   264,  2131,  -340,  -340,   451,  -340,  -340,  -340,   215,
    -340,   193,   244,  -340,  -340,  -340,  -340,  -340,   275,  2275,
    3117,  3117,  2764,  3162,  3206,  2057,  2201,  3247,  3286,  3286,
    3321,  3321,  3321,  3321,  1064,  1064,   512,   512,   886,   886,
     886,   365,  3247,   366,   369,  2466,  2882,  -340,  -340,  -340,
    -340,  -340,  -340,  2275,  -340,  -340,  -340,  2649,  -340,   250,
    -340,  -340,  -340,   256,  -340,  -340,   -21,  -340,  -340,   451,
     257,  -340,  -340,   199,  -340,  -340,  1456,  -340,  -340,  -340,
    -340,  2526,  -340,  -340,  -340,   938,  -340,  -340,  3062,    85,
    -340,  -340,   228,   260,   359,   554,  -340,   -11,  -340,  -340,
     114,  -340,  -340,  -340,  -340,   302,  -340,  -340,  2823,  2275,
    -340,  -340,  -340,  -340,  -340,   186,  2882,  -340,   378,  -340,
    -340,  -340,  -340,  -340,  1983,   199,  -340,  -340,  -340,  -340,
     -44,  -340,  -340,  -340,   314,   -44,  -340,  -340,   262,   261,
    -340,  -340,  2243,  -340,  1090,  -340,  2882,  -340,  -340,   -11,
    -340,   -71,   269,  -340,  -340,    85,  -340,  -340,  -340,  2243,
    -340,  -340,   -58,  2882,  1578,  -340,  -340,   378,   965,  -340,
     124,   -40,  -340,  2243,  -340,  -340,   268,  -340,  -340,  -340,
    -340,  -340,  -340
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   281,     0,   213,   225,   329,   332,     0,     0,    43,
      92,    93,    91,    98,    99,   100,   101,    95,    94,    39,
     151,   152,   174,     0,   195,   153,   220,   221,   222,   223,
     155,   154,   156,     0,   299,   302,     0,     0,     0,     0,
       0,     0,     0,   186,     0,   319,     0,     0,    60,     0,
      48,   171,     0,     0,    81,    83,    84,    82,   147,   148,
     146,     0,     0,     0,     0,   282,     0,     0,     0,     0,
       0,     0,   201,     6,     8,     0,     0,     0,     9,     4,
      10,    15,    44,     0,     0,     0,     0,    51,    11,    36,
       0,     0,    12,    62,     0,     0,    77,    89,     0,   165,
     165,    96,    16,    13,    97,    33,    34,    35,    27,    28,
       0,     0,   226,     0,     0,   216,   293,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    31,     0,    32,
      87,     0,   330,   333,     0,    30,    29,     0,    37,   198,
     199,   120,     0,   264,   285,   346,     0,   335,   336,    90,
       0,   179,   332,   116,     0,     0,     0,   295,     0,   293,
     307,     0,   281,   213,     0,     0,     0,   292,     0,   317,
     316,   315,   161,     0,     0,     0,     0,     0,     0,   337,
      59,    85,     0,   161,     0,     0,     0,     0,     0,     0,
     280,     0,    79,   235,   236,   261,   257,   217,     0,     0,
     262,   237,    45,   266,   249,   251,     0,     0,   219,     0,
       0,     0,     1,     5,   120,   123,    66,    53,    64,    50,
      61,    52,    63,     0,    58,     0,     0,     0,     0,    57,
      56,    54,   115,   119,    75,     0,     0,     0,   135,   106,
     130,     0,     0,     0,    78,   170,   157,   161,   169,   202,
     202,     0,   202,    14,     0,     0,     0,     0,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   278,     0,   248,
     250,   276,   274,     0,     0,   273,   296,     0,     0,   324,
     318,   200,   341,   342,   338,   343,   344,   345,   339,   284,
     281,   287,     0,   356,   151,   347,   355,   348,     0,   354,
     357,   350,    41,    40,    42,   180,   181,   175,   116,   116,
       0,   196,     0,   300,     0,     0,     0,   314,   313,   159,
     160,   164,   162,   190,   187,   163,     0,   202,   192,   194,
       0,   320,   326,     0,     0,   172,    66,     0,     0,     0,
     256,   259,   283,   260,     0,     0,     0,    74,     0,   227,
     126,   135,     0,   124,    49,    67,     0,     0,     0,    76,
       0,   110,     0,     0,   103,   114,   107,   134,     0,   113,
       0,    75,     0,   128,   137,     0,    38,   202,   202,     0,
      80,   149,     0,   166,   214,   331,   334,   215,     0,     0,
     255,   246,     0,   245,   244,   234,   270,   233,   242,   243,
     238,   240,   239,   241,   267,   268,   231,   232,   228,   229,
     230,     0,   269,     0,     0,     0,   247,   297,   294,   322,
     325,   340,   121,     0,   286,   352,   353,     0,   349,   177,
     117,   118,    46,     0,   290,   293,     0,   304,   306,     0,
       0,   308,   311,     0,   191,   193,     0,    86,    88,   173,
     258,     0,   253,   252,     7,   265,   127,   122,   123,     0,
      65,    55,   109,     0,     0,     0,   140,   135,   138,   136,
     135,   131,   112,   111,   150,     0,   167,   224,     0,     0,
     279,   277,   275,   272,   293,     0,   288,   351,   183,   176,
     197,   301,   303,   305,     0,     0,   188,   321,   218,   125,
       0,   327,    69,    68,    70,     0,   328,   102,     0,     0,
     133,    47,     0,   158,     0,   263,   254,   298,   323,   135,
     184,     0,     0,   312,    73,     0,    72,   202,   104,     0,
     143,   144,     0,   142,     0,   182,   178,     0,     0,    71,
       0,     0,   139,     0,   168,   185,     0,   108,   141,   145,
     309,   293,   310
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -340,  -340,  -197,   -60,  -340,   -70,   -45,  -340,  -340,  -340,
     -52,   242,   -12,    32,    49,   -68,   -35,  -340,   306,  -340,
    -340,   342,   -27,  -340,  -340,  -147,  -340,  -133,     9,    -4,
    -340,  -340,  -340,   -22,   389,  -340,   165,  -340,   -77,  -208,
    -221,   -69,    37,   -78,   -74,  -340,  -340,    11,  -340,  -340,
    -339,  -340,  -340,  -153,  -137,    18,  -340,  -340,  -340,  -340,
    -340,  -150,   316,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -139,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,     0,  -340,  -222,  -340,
     -10,   -37,  -340,  -171,  -340,  -340,    -1,  -340,  -340,  -340,
    -340,  -340,    -2,  -201,  -340,  -143,   -43,  -151,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,
    -340,  -340,   -83,  -340,  -340,   125,  -340,  -340,   -38,   -56,
    -161,  -340,  -340,  -340,  -340,  -340,  -340,  -340,  -340,   107,
       4,  -340,  -340,  -340,   -19
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    76,    77,    78,   207,    79,    80,    81,   150,   323,
      82,    83,    84,    85,    86,    87,    88,    89,   230,    90,
      91,    92,    93,   376,   479,   523,   524,   208,   380,    94,
      95,   182,   468,    96,    97,   237,   389,   485,   490,   330,
     239,   142,   444,   391,   372,   373,   240,   241,   529,   392,
     393,   532,   550,   551,   552,    98,   495,    99,   100,   402,
     342,   343,   246,   247,   101,   534,   102,   103,   184,   104,
     151,   449,   509,   327,   540,   541,   105,   172,   463,   344,
     106,   107,   108,   155,   453,   109,   165,   111,   404,   294,
     112,   113,   360,   210,   114,   255,   115,   358,   434,   433,
     431,   199,   295,   144,   312,   157,   168,   296,   297,   116,
     117,   118,   504,   119,   158,   455,   120,   159,   461,   121,
     335,   514,   571,   122,   515,   123,   124,   125,   126,   127,
     128,   177,   351,   299,   505,   300,   129,   525,   130,   131,
     132,   133,   134,   135,   136,   305,   137,   308,   146,   317,
     147,   318,   319,   320,   321
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     110,   166,   167,   178,   143,   216,   176,   213,   334,   167,
     366,   345,   148,   316,   215,   333,   202,   238,   221,   153,
     138,   398,   345,   154,   218,   220,   377,     9,   405,   406,
     407,   192,   476,   354,   175,   364,   325,   394,   163,   326,
     187,   152,   197,     8,   174,   224,   224,   139,   191,   315,
     556,   179,   154,   154,   251,   229,   229,   557,   387,   222,
     193,   194,   195,   562,   154,   200,   201,   203,   204,   205,
     563,   209,   250,   244,   211,   110,   328,   110,   226,   226,
     141,   568,   371,   408,   188,   329,   345,   447,   563,   520,
     154,   154,   521,     7,   242,   154,   442,   403,   251,   443,
     249,   189,   306,   156,   152,   322,     8,   307,   356,   251,
     110,   145,   388,   214,   357,   324,   250,   215,   251,   332,
     450,   451,   227,   227,   336,   465,   185,   218,   220,   152,
     191,     8,   367,   202,   154,    73,   250,   217,   226,   228,
     228,   311,   209,   140,   522,   353,   154,   378,   531,   355,
     154,   160,    72,   466,   154,   249,   215,   169,   381,   386,
     221,   483,   222,   203,   249,    73,   304,   219,   215,   390,
     394,   161,   226,   233,   110,   492,   493,   152,   445,     8,
     191,   446,   227,   387,   154,   163,   251,     5,   152,     7,
       8,   242,   170,   382,    23,   361,   374,   375,   363,   228,
     555,   141,   209,   359,   171,   365,   110,   110,   214,   242,
     384,   209,   180,   181,   339,   154,   227,   340,   484,   341,
     439,   400,   152,   110,     8,   183,   232,   438,   233,   215,
     397,   198,   152,   228,     8,   242,   383,   388,   214,   206,
     384,   212,   399,   154,    13,    14,    15,    16,   214,   245,
     209,   252,   452,   253,   154,   410,   411,   371,    58,    59,
      60,   215,   254,   528,   298,   301,   309,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   394,   432,   215,   394,
     458,   331,   435,   436,   186,   337,   213,   110,   460,    72,
     338,   346,   348,   482,   511,   349,   350,   213,     5,   152,
       7,     8,   441,   512,   316,     9,   480,   352,   526,    73,
    -332,   234,   368,   362,   379,   560,   395,   251,   217,   409,
     235,   459,   225,   225,   219,   110,   401,   554,   394,   396,
     437,   454,   456,   251,   462,   371,   464,   467,   469,   236,
     110,  -105,   375,   537,   384,   489,   470,   472,   471,   442,
     374,   478,   233,   486,   496,   497,   110,   475,   500,   501,
     508,   163,   502,     5,   152,     7,     8,   110,   510,   513,
     242,   539,   545,   399,   526,   527,   209,   547,   548,   311,
     110,   558,   225,   570,   190,   242,   213,   231,   559,   399,
     487,   149,   385,   516,   519,   232,   491,   233,   498,   477,
     569,   152,   561,     8,   173,   232,   248,   233,   565,   494,
     572,   152,   538,     8,   440,   448,   225,     0,   507,     0,
     163,   186,     5,   152,   347,     8,     0,     0,     0,     0,
       0,     0,   506,   209,     0,     0,     0,   154,   530,     0,
       0,     0,   232,     0,   233,   543,     0,   533,   152,   242,
       8,     0,     0,     0,     0,     0,   110,     0,     0,     0,
     225,   542,     0,  -105,   209,     0,     0,   167,   154,     0,
       0,     0,   567,  -105,   213,    72,     0,     0,     0,     0,
       0,   215,     0,     0,  -105,   154,     0,     0,   536,     0,
     234,     0,     0,     0,  -105,     0,     0,     0,     0,   235,
     234,     0,     0,     0,     0,   566,     0,     0,   544,   235,
    -105,   167,     0,   546,     0,     0,  -105,  -105,   236,  -105,
    -105,   553,  -105,     0,   110,     0,     0,  -105,   236,  -105,
    -105,     0,  -105,     0,    72,     0,     0,   234,   553,     0,
       0,     0,     0,     0,   110,   162,   235,     0,   163,     4,
       0,     6,   553,     8,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -105,  -105,   236,     0,  -105,     0,  -105,
       0,    26,    27,    28,    29,   313,     5,   152,     7,     8,
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
       0,   314,    21,    22,     0,     0,    25,     0,   284,   285,
     286,   287,    52,    30,    31,    32,     0,   288,     0,     0,
       0,     0,   289,   290,     0,     0,     0,     0,   291,   292,
       0,     0,     0,     0,     0,    49,   141,     0,   293,     0,
      53,    54,    55,    56,    57,     0,     0,     0,    61,    62,
      63,     0,     0,     0,     0,    64,    65,     0,     0,    66,
       0,     0,    67,   164,    69,    70,    71,     0,     0,     0,
     315,     0,    72,     0,     0,     0,     0,     0,    75,    -3,
       1,  -132,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
       0,     0,    30,    31,    32,    33,     0,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
      46,    47,    48,     0,    49,    50,    51,    52,     0,    53,
      54,    55,    56,    57,    58,    59,    60,     0,     0,     5,
     152,     7,     8,     0,    10,    11,    12,    13,    14,    15,
      16,    17,    18,     0,    20,    21,    22,     0,     0,    25,
       0,     0,     0,    61,    62,    63,    30,    31,    32,     0,
      64,    65,     0,     0,    66,     0,     0,    67,    68,    69,
      70,    71,     0,     0,     0,     0,     0,    72,    49,    73,
       0,    74,     0,    75,    -2,     1,     0,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,     0,     0,    30,    31,    32,
      33,     0,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,    46,    47,    48,     0,    49,
      50,    51,    52,     0,    53,    54,    55,    56,    57,    58,
      59,    60,     0,     0,     5,   196,     7,     8,     0,    10,
      11,    12,    13,    14,    15,    16,    17,    18,     0,    20,
      21,    22,     0,     0,    25,     0,     0,     0,    61,    62,
      63,    30,    31,    32,     0,    64,    65,     0,     0,    66,
       0,     0,    67,    68,    69,    70,    71,     0,     0,     0,
       0,     0,    72,    49,    73,     0,    74,   310,    75,     0,
     163,     4,     5,     6,     7,     8,     0,    10,    11,    12,
      13,    14,    15,    16,    17,    18,     0,    20,    21,    22,
       0,     0,    25,    26,    27,    28,    29,     0,     0,    30,
      31,    32,     0,     0,     0,     0,   162,     0,     0,   163,
       4,     0,     6,     0,     8,     0,     0,     0,     0,     0,
     370,    49,     0,     0,    52,   287,    53,    54,    55,    56,
      57,   288,    26,    27,    28,    29,   289,   290,     0,     0,
       0,     0,   291,   292,     0,     0,     0,     0,     0,     0,
     141,     0,   293,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    52,     0,     0,     0,    64,    65,     0,
       0,    66,     0,     0,    67,   164,    69,    70,    71,     0,
       0,     0,     0,   288,    72,     0,     0,     0,   289,   290,
      75,  -123,     0,     0,   291,   292,     0,     0,     0,    61,
      62,    63,   141,     0,   293,     0,    64,    65,     0,     0,
      66,     0,     0,    67,   164,    69,    70,    71,     0,     0,
       0,     0,     0,    72,     0,     0,     0,     0,     0,    75,
    -291,     1,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,     0,    30,    31,    32,    33,     0,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,    46,    47,    48,     0,    49,    50,    51,    52,     0,
      53,    54,    55,    56,    57,    58,    59,    60,   282,   283,
     284,   285,   286,   287,     0,     0,     0,     0,     0,   288,
       0,     0,     0,     0,   289,   290,     0,     0,     0,     0,
     291,   292,     0,     0,    61,    62,    63,     0,   141,     0,
     293,    64,    65,     0,     0,    66,     0,     0,    67,    68,
      69,    70,    71,     0,     0,     0,     0,     0,    72,     0,
      73,    -3,    74,     1,    75,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,     0,     0,    30,    31,    32,    33,     0,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     0,    46,    47,    48,     0,    49,    50,    51,
      52,     0,    53,    54,    55,    56,    57,    58,    59,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,    62,    63,     0,
       0,     0,     0,    64,    65,     0,     0,    66,     0,     0,
      67,    68,    69,    70,    71,     0,     0,     0,     0,     0,
      72,     0,    73,   474,    74,     1,    75,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,     0,     0,    30,    31,    32,
      33,     0,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,    46,    47,    48,     0,    49,
      50,    51,    52,     0,    53,    54,    55,    56,    57,    58,
      59,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,     0,     0,     0,     0,    64,    65,     0,     0,    66,
       0,     0,    67,    68,    69,    70,    71,     0,     0,     0,
       0,     0,    72,     0,    73,   481,    74,     1,    75,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     0,     0,    30,
      31,    32,    33,     0,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     0,    46,    47,    48,
       0,    49,    50,    51,    52,     0,    53,    54,    55,    56,
      57,    58,    59,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,     0,     0,     0,     0,    64,    65,     0,
       0,    66,     0,     0,    67,    68,    69,    70,    71,     0,
       0,     0,     0,     0,    72,     0,    73,   517,    74,     1,
      75,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     0,
       0,    30,    31,    32,    33,     0,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     0,    46,
      47,    48,     0,    49,    50,    51,    52,     0,    53,    54,
      55,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,    62,    63,     0,     0,     0,     0,    64,
      65,     0,     0,    66,     0,     0,    67,    68,    69,    70,
      71,     0,     0,     0,     0,     0,    72,     0,    73,   564,
      74,     1,    75,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,     0,    30,    31,    32,    33,     0,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,    46,    47,    48,     0,    49,    50,    51,    52,     0,
      53,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,     0,     0,     0,
       0,    64,    65,     0,     0,    66,     0,     0,    67,    68,
      69,    70,    71,     0,     0,     0,     0,     0,    72,     0,
      73,     0,    74,   162,    75,     0,   163,     4,     5,     6,
       7,     8,     0,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     0,    20,    21,    22,     0,     0,    25,    26,
      27,    28,    29,     0,     0,    30,    31,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,     0,     0,
      52,     0,    53,    54,    55,    56,    57,     0,     0,     0,
       0,     0,     0,     5,   152,     7,     8,     0,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     0,    20,    21,
      22,     0,     0,    25,     0,     0,    61,    62,    63,     0,
      30,    31,    32,    64,    65,     0,     0,    66,     0,     0,
      67,   164,    69,    70,    71,     0,     0,     0,     0,     0,
      72,     0,    49,     0,   457,   162,    75,   243,   163,     4,
       5,     6,     7,     8,     0,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     0,    20,    21,    22,     0,     0,
      25,    26,    27,    28,    29,     0,     0,    30,    31,    32,
       0,     0,     0,     0,   162,     0,     0,   163,     4,     0,
       6,     0,     8,     0,     0,     0,     0,     0,     0,    49,
       0,     0,    52,     0,    53,    54,    55,    56,    57,     0,
      26,    27,    28,    29,     0,     5,   152,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     0,
      20,    21,    22,    23,     0,    25,     0,     0,    61,    62,
      63,    52,    30,    31,    32,    64,    65,     0,     0,    66,
       0,     0,    67,   164,    69,    70,    71,     0,     0,     0,
       0,     0,    72,     0,    49,    50,     0,     0,    75,    53,
      54,    55,    56,    57,     0,     0,     0,    61,    62,    63,
       0,     0,     0,     0,    64,    65,     0,     0,    66,     0,
       0,    67,   164,    69,    70,    71,     0,     0,     0,     0,
     162,    72,     0,   163,     4,  -291,     6,    75,     8,     9,
       0,     0,     0,     0,     0,     0,     0,     0,   185,     0,
       0,     0,     0,     0,     0,     0,    26,    27,    28,    29,
       0,     0,   162,     0,     0,   163,     4,     0,     6,     0,
       8,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,    52,    26,    27,
      28,    29,   288,     0,     0,     0,     0,   289,   290,     0,
       0,     0,     0,   291,   292,     0,     0,     0,     0,     0,
       0,   141,     0,   293,     0,     0,     0,     0,     0,    52,
       0,     0,     0,    61,    62,    63,     0,     0,     0,     0,
      64,    65,     0,     0,    66,     0,     0,    67,   164,    69,
      70,    71,     0,     0,     0,     0,     0,    72,     0,     0,
       0,     0,     0,    75,     0,    61,    62,    63,     0,     0,
       0,     0,    64,    65,     0,     0,    66,     0,     0,    67,
     164,    69,    70,    71,   162,     0,     0,   163,     4,    72,
       6,   488,     8,     0,     0,    75,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,    27,    28,    29,     0,     0,   162,     0,     0,   163,
       4,     0,     6,     0,     8,     0,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,    52,    26,    27,    28,    29,   288,     0,     0,     0,
       0,   289,   290,     0,     0,     0,     0,   291,   292,     0,
       0,     0,     0,     0,     0,   141,     0,   293,     0,     0,
       0,     0,     0,    52,     0,     0,     0,    61,    62,    63,
       0,     0,     0,     0,    64,    65,     0,     0,    66,     0,
       0,    67,   164,    69,    70,    71,     0,     0,     0,     0,
       0,    72,     0,   549,     0,     0,     0,    75,     0,    61,
      62,    63,     0,     0,     0,     0,    64,    65,     0,     0,
      66,     0,     0,    67,   164,    69,    70,    71,   310,     0,
       0,   163,     4,    72,     6,     0,     8,     0,     0,    75,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    26,    27,    28,    29,     0,     5,
     152,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,     0,    20,    21,    22,    23,     0,    25,
       0,     0,     0,     0,     0,    52,    30,    31,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
       0,     0,     0,    53,    54,    55,    56,    57,     0,     0,
       0,    61,    62,    63,     0,     0,     0,     0,    64,    65,
       0,     0,    66,     0,     0,    67,   164,    69,    70,    71,
       0,     0,     0,     0,     0,    72,     0,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   185,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   223,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,     0,     0,     0,     0,
       0,   288,     0,     0,     0,     0,   289,   290,     0,     0,
       0,     0,   291,   292,     0,     0,     0,     0,     0,     0,
     141,     0,   293,   503,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,     0,     0,     0,     0,
       0,   288,     0,     0,     0,     0,   289,   290,     0,     0,
       0,     0,   291,   292,     0,     0,     0,     0,     0,     0,
     141,     0,   293,   518,   313,     5,   152,     7,     8,     0,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     0,
     314,    21,    22,     0,     0,    25,     0,     0,     0,     0,
       0,     0,    30,    31,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,     0,    53,
      54,    55,    56,    57,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,     0,     0,     0,     0,
       0,   288,     0,     0,     0,     0,   289,   290,     0,     0,
       0,     0,   291,   292,     0,     0,     0,     0,     0,     0,
     141,   369,   293,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,     0,     0,     0,     0,     0,
     288,     0,     0,     0,     0,   289,   290,     0,     0,     0,
       0,   291,   292,     0,     0,     0,     0,     0,     0,   141,
     473,   293,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,     0,     0,     0,     0,     0,   288,
       0,     0,     0,     0,   289,   290,     0,     0,     0,     0,
     291,   292,     0,     0,     0,     0,     0,   499,   141,     0,
     293,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,     0,     0,     0,     0,     0,   288,     0,
       0,     0,     0,   289,   290,     0,     0,     0,     0,   291,
     292,     0,     0,     0,     0,     0,     0,   141,   535,   293,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,     0,     0,     0,     0,     0,   288,     0,     0,
       0,     0,   289,   290,     0,     0,     0,     0,   291,   292,
       0,     0,     0,     0,     0,     0,   141,     0,   293,     5,
     152,     7,     8,     0,    10,    11,    12,    13,    14,    15,
      16,    17,    18,     0,    20,    21,    22,     0,     0,    25,
       0,     0,     0,     0,   302,   303,    30,    31,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,     0,
       0,     0,     0,    53,    54,    55,    56,    57,     5,   152,
       7,     8,     0,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     0,    20,    21,    22,     0,     0,    25,     0,
       0,     0,     0,     0,     0,    30,    31,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   370,    49,     0,     0,
       0,     0,    53,    54,    55,    56,    57,     5,   152,     7,
       8,     0,    10,    11,    12,    13,    14,    15,    16,    17,
      18,     0,    20,    21,    22,     0,     0,    25,     0,     0,
       0,     0,     0,     0,    30,    31,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,     0,     0,     0,
       0,    53,    54,    55,    56,    57,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,     0,     0,     0,
       0,     0,   288,     0,     0,     0,     0,   289,   290,     0,
       0,     0,     0,   291,   292,     0,     0,     0,     0,     0,
       0,   141,     0,   293,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,     0,     0,     0,     0,     0,   288,     0,     0,
       0,     0,   289,   290,     0,     0,     0,     0,   291,   292,
       0,     0,     0,     0,     0,     0,   141,     0,   293,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,     0,     0,     0,     0,
       0,   288,     0,     0,     0,     0,   289,   290,     0,     0,
       0,     0,   291,   292,     0,     0,     0,     0,     0,     0,
     141,     0,   293,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,     0,     0,     0,
       0,     0,   288,     0,     0,     0,     0,   289,   290,     0,
       0,     0,     0,   291,   292,     0,     0,     0,     0,     0,
       0,   141,     0,   293,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,     0,     0,     0,     0,
       0,   288,     0,     0,     0,     0,   289,   290,     0,     0,
       0,     0,   291,   292,     0,     0,     0,     0,     0,     0,
     141,     0,   293,   280,   281,   282,   283,   284,   285,   286,
     287,     0,     0,     0,     0,     0,   288,     0,     0,     0,
       0,   289,   290,     0,     0,     0,     0,   291,   292,     0,
       0,     0,     0,     0,     0,   141,     0,   293
};

static const yytype_int16 yycheck[] =
{
       0,    38,    39,    46,     6,    83,    44,    77,   159,    46,
     207,   172,     8,   146,    83,   158,    68,    94,    86,    23,
     122,   242,   183,    23,    84,    85,   223,    10,   250,   251,
     252,    53,   371,   183,    44,   206,     3,   238,     4,     6,
      52,     7,    64,     9,    44,    90,    91,   123,    52,    90,
     121,    47,    52,    53,   110,    90,    91,   128,    69,    86,
      61,    62,    63,   121,    64,    66,    67,    68,    69,    70,
     128,    75,   110,    95,    75,    75,    96,    77,    90,    91,
     124,   121,   215,   254,    52,   105,   247,   128,   128,     4,
      90,    91,     7,     8,    94,    95,   125,   247,   154,   128,
     110,    52,     3,   124,     7,   150,     9,     8,   186,   165,
     110,    88,   123,   124,   191,   150,   154,   186,   174,   156,
     328,   329,    90,    91,   161,   347,   109,   187,   188,     7,
     134,     9,   209,   185,   134,   120,   174,   122,   150,    90,
      91,   142,   146,   123,    59,   182,   146,   225,   487,   184,
     150,   124,   118,   350,   154,   165,   225,   122,   235,   237,
     228,   382,   189,   164,   174,   120,   134,   122,   237,   238,
     371,   124,   184,     3,   174,   397,   398,     7,     3,     9,
     184,     6,   150,    69,   184,     4,   242,     6,     7,     8,
       9,   191,   122,    96,    24,   197,   122,   123,   199,   150,
     539,   124,   206,   126,   123,   206,   206,   207,   124,   209,
     126,   215,     5,   124,     3,   215,   184,     6,    96,     8,
     298,   243,     7,   223,     9,    21,     1,   297,     3,   298,
     242,   126,     7,   184,     9,   235,   236,   123,   124,   124,
     126,     0,   242,   243,    14,    15,    16,    17,   124,   123,
     254,     4,   330,   122,   254,   256,   257,   390,    65,    66,
      67,   330,    88,   484,    50,   118,   125,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   487,   288,   357,   490,
     335,     3,   293,   294,    52,   123,   366,   297,   335,   118,
     122,     6,   122,   380,   455,   122,   120,   377,     6,     7,
       8,     9,   308,   456,   447,    10,   376,   122,   479,   120,
     118,    96,   125,   127,    60,   547,   128,   383,   122,   124,
     105,   335,    90,    91,   122,   335,   123,   534,   539,   122,
      37,   125,    38,   399,   125,   478,   122,   125,   122,   124,
     350,   126,   123,   504,   126,   392,   358,   125,   359,   125,
     122,   128,     3,     5,   120,    90,   366,   368,     3,     3,
     120,     4,     3,     6,     7,     8,     9,   377,   122,   122,
     380,     3,    68,   383,   545,   125,   390,   125,   127,   390,
     390,   122,   150,   125,    52,   395,   466,    91,   545,   399,
     391,    12,   237,   463,   478,     1,   395,     3,   409,   372,
     563,     7,   549,     9,    47,     1,   100,     3,   557,   401,
     571,     7,   505,     9,   299,   318,   184,    -1,   447,    -1,
       4,   189,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,   443,   447,    -1,    -1,    -1,   447,   485,    -1,
      -1,    -1,     1,    -1,     3,   515,    -1,   495,     7,   459,
       9,    -1,    -1,    -1,    -1,    -1,   466,    -1,    -1,    -1,
     228,   514,    -1,    69,   478,    -1,    -1,   514,   478,    -1,
      -1,    -1,   560,    69,   554,   118,    -1,    -1,    -1,    -1,
      -1,   560,    -1,    -1,    90,   495,    -1,    -1,   499,    -1,
      96,    -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,   105,
      96,    -1,    -1,    -1,    -1,   558,    -1,    -1,   520,   105,
      69,   558,    -1,   525,    -1,    -1,   122,   123,   124,   125,
     126,   532,   128,    -1,   534,    -1,    -1,   123,   124,   125,
     126,    -1,   128,    -1,   118,    -1,    -1,    96,   549,    -1,
      -1,    -1,    -1,    -1,   554,     1,   105,    -1,     4,     5,
      -1,     7,   563,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   122,   123,   124,    -1,   126,    -1,   128,
      -1,    27,    28,    29,    30,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    -1,    -1,    26,    -1,    96,    97,
      98,    99,    58,    33,    34,    35,    -1,   105,    -1,    -1,
      -1,    -1,   110,   111,    -1,    -1,    -1,    -1,   116,   117,
      -1,    -1,    -1,    -1,    -1,    55,   124,    -1,   126,    -1,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    94,    95,
      96,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,   105,
      -1,    -1,   108,   109,   110,   111,   112,    -1,    -1,    -1,
      90,    -1,   118,    -1,    -1,    -1,    -1,    -1,   124,     0,
       1,   127,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    -1,
      51,    52,    53,    -1,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    -1,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    -1,    -1,    26,
      -1,    -1,    -1,    94,    95,    96,    33,    34,    35,    -1,
     101,   102,    -1,    -1,   105,    -1,    -1,   108,   109,   110,
     111,   112,    -1,    -1,    -1,    -1,    -1,   118,    55,   120,
      -1,   122,    -1,   124,     0,     1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    53,    -1,    55,
      56,    57,    58,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    -1,    -1,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    -1,    -1,    26,    -1,    -1,    -1,    94,    95,
      96,    33,    34,    35,    -1,   101,   102,    -1,    -1,   105,
      -1,    -1,   108,   109,   110,   111,   112,    -1,    -1,    -1,
      -1,    -1,   118,    55,   120,    -1,   122,     1,   124,    -1,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      -1,    -1,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    -1,    -1,    -1,    -1,     1,    -1,    -1,     4,
       5,    -1,     7,    -1,     9,    -1,    -1,    -1,    -1,    -1,
      54,    55,    -1,    -1,    58,    99,    60,    61,    62,    63,
      64,   105,    27,    28,    29,    30,   110,   111,    -1,    -1,
      -1,    -1,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    95,    96,    58,    -1,    -1,    -1,   101,   102,    -1,
      -1,   105,    -1,    -1,   108,   109,   110,   111,   112,    -1,
      -1,    -1,    -1,   105,   118,    -1,    -1,    -1,   110,   111,
     124,   125,    -1,    -1,   116,   117,    -1,    -1,    -1,    94,
      95,    96,   124,    -1,   126,    -1,   101,   102,    -1,    -1,
     105,    -1,    -1,   108,   109,   110,   111,   112,    -1,    -1,
      -1,    -1,    -1,   118,    -1,    -1,    -1,    -1,    -1,   124,
     125,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    -1,    55,    56,    57,    58,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    94,    95,
      96,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    -1,    -1,    -1,   110,   111,    -1,    -1,    -1,    -1,
     116,   117,    -1,    -1,    94,    95,    96,    -1,   124,    -1,
     126,   101,   102,    -1,    -1,   105,    -1,    -1,   108,   109,
     110,   111,   112,    -1,    -1,    -1,    -1,    -1,   118,    -1,
     120,   121,   122,     1,   124,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    -1,    51,    52,    53,    -1,    55,    56,    57,
      58,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,    -1,
      -1,    -1,    -1,   101,   102,    -1,    -1,   105,    -1,    -1,
     108,   109,   110,   111,   112,    -1,    -1,    -1,    -1,    -1,
     118,    -1,   120,   121,   122,     1,   124,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    53,    -1,    55,
      56,    57,    58,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,   105,
      -1,    -1,   108,   109,   110,   111,   112,    -1,    -1,    -1,
      -1,    -1,   118,    -1,   120,   121,   122,     1,   124,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    36,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      -1,    55,    56,    57,    58,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    95,    96,    -1,    -1,    -1,    -1,   101,   102,    -1,
      -1,   105,    -1,    -1,   108,   109,   110,   111,   112,    -1,
      -1,    -1,    -1,    -1,   118,    -1,   120,   121,   122,     1,
     124,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    -1,    55,    56,    57,    58,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    95,    96,    -1,    -1,    -1,    -1,   101,
     102,    -1,    -1,   105,    -1,    -1,   108,   109,   110,   111,
     112,    -1,    -1,    -1,    -1,    -1,   118,    -1,   120,   121,
     122,     1,   124,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    -1,    55,    56,    57,    58,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    95,    96,    -1,    -1,    -1,
      -1,   101,   102,    -1,    -1,   105,    -1,    -1,   108,   109,
     110,   111,   112,    -1,    -1,    -1,    -1,    -1,   118,    -1,
     120,    -1,   122,     1,   124,    -1,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    -1,    -1,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      58,    -1,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    -1,    -1,    26,    -1,    -1,    94,    95,    96,    -1,
      33,    34,    35,   101,   102,    -1,    -1,   105,    -1,    -1,
     108,   109,   110,   111,   112,    -1,    -1,    -1,    -1,    -1,
     118,    -1,    55,    -1,   122,     1,   124,    60,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    -1,    -1,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,     1,    -1,    -1,     4,     5,    -1,
       7,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      -1,    -1,    58,    -1,    60,    61,    62,    63,    64,    -1,
      27,    28,    29,    30,    -1,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    -1,    26,    -1,    -1,    94,    95,
      96,    58,    33,    34,    35,   101,   102,    -1,    -1,   105,
      -1,    -1,   108,   109,   110,   111,   112,    -1,    -1,    -1,
      -1,    -1,   118,    -1,    55,    56,    -1,    -1,   124,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    94,    95,    96,
      -1,    -1,    -1,    -1,   101,   102,    -1,    -1,   105,    -1,
      -1,   108,   109,   110,   111,   112,    -1,    -1,    -1,    -1,
       1,   118,    -1,     4,     5,   122,     7,   124,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,    30,
      -1,    -1,     1,    -1,    -1,     4,     5,    -1,     7,    -1,
       9,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    58,    27,    28,
      29,    30,   105,    -1,    -1,    -1,    -1,   110,   111,    -1,
      -1,    -1,    -1,   116,   117,    -1,    -1,    -1,    -1,    -1,
      -1,   124,    -1,   126,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    94,    95,    96,    -1,    -1,    -1,    -1,
     101,   102,    -1,    -1,   105,    -1,    -1,   108,   109,   110,
     111,   112,    -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,
      -1,    -1,    -1,   124,    -1,    94,    95,    96,    -1,    -1,
      -1,    -1,   101,   102,    -1,    -1,   105,    -1,    -1,   108,
     109,   110,   111,   112,     1,    -1,    -1,     4,     5,   118,
       7,   120,     9,    -1,    -1,   124,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    28,    29,    30,    -1,    -1,     1,    -1,    -1,     4,
       5,    -1,     7,    -1,     9,    -1,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,    58,    27,    28,    29,    30,   105,    -1,    -1,    -1,
      -1,   110,   111,    -1,    -1,    -1,    -1,   116,   117,    -1,
      -1,    -1,    -1,    -1,    -1,   124,    -1,   126,    -1,    -1,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    94,    95,    96,
      -1,    -1,    -1,    -1,   101,   102,    -1,    -1,   105,    -1,
      -1,   108,   109,   110,   111,   112,    -1,    -1,    -1,    -1,
      -1,   118,    -1,   120,    -1,    -1,    -1,   124,    -1,    94,
      95,    96,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,
     105,    -1,    -1,   108,   109,   110,   111,   112,     1,    -1,
      -1,     4,     5,   118,     7,    -1,     9,    -1,    -1,   124,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    -1,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    58,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    94,    95,    96,    -1,    -1,    -1,    -1,   101,   102,
      -1,    -1,   105,    -1,    -1,   108,   109,   110,   111,   112,
      -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,    -1,
      -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   120,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,   110,   111,    -1,    -1,
      -1,    -1,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,   126,   127,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,   110,   111,    -1,    -1,
      -1,    -1,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,   126,   127,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,   110,   111,    -1,    -1,
      -1,    -1,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,
     124,   125,   126,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,
     105,    -1,    -1,    -1,    -1,   110,   111,    -1,    -1,    -1,
      -1,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,   124,
     125,   126,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    -1,    -1,    -1,   110,   111,    -1,    -1,    -1,    -1,
     116,   117,    -1,    -1,    -1,    -1,    -1,   123,   124,    -1,
     126,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,    -1,    -1,    -1,    -1,    -1,   105,    -1,
      -1,    -1,    -1,   110,   111,    -1,    -1,    -1,    -1,   116,
     117,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,   126,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,
      -1,    -1,   110,   111,    -1,    -1,    -1,    -1,   116,   117,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,   126,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    -1,    -1,    -1,
      -1,    -1,   105,    -1,    -1,    -1,    -1,   110,   111,    -1,
      -1,    -1,    -1,   116,   117,    -1,    -1,    -1,    -1,    -1,
      -1,   124,    -1,   126,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,
      -1,    -1,   110,   111,    -1,    -1,    -1,    -1,   116,   117,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,   126,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,   110,   111,    -1,    -1,
      -1,    -1,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,   126,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    -1,    -1,    -1,
      -1,    -1,   105,    -1,    -1,    -1,    -1,   110,   111,    -1,
      -1,    -1,    -1,   116,   117,    -1,    -1,    -1,    -1,    -1,
      -1,   124,    -1,   126,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,   110,   111,    -1,    -1,
      -1,    -1,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,   126,    92,    93,    94,    95,    96,    97,    98,
      99,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,
      -1,   110,   111,    -1,    -1,    -1,    -1,   116,   117,    -1,
      -1,    -1,    -1,    -1,    -1,   124,    -1,   126
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      33,    34,    35,    36,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    51,    52,    53,    55,
      56,    57,    58,    60,    61,    62,    63,    64,    65,    66,
      67,    94,    95,    96,   101,   102,   105,   108,   109,   110,
     111,   112,   118,   120,   122,   124,   130,   131,   132,   134,
     135,   136,   139,   140,   141,   142,   143,   144,   145,   146,
     148,   149,   150,   151,   158,   159,   162,   163,   184,   186,
     187,   193,   195,   196,   198,   205,   209,   210,   211,   214,
     215,   216,   219,   220,   223,   225,   238,   239,   240,   242,
     245,   248,   252,   254,   255,   256,   257,   258,   259,   265,
     267,   268,   269,   270,   271,   272,   273,   275,   122,   123,
     123,   124,   170,   231,   232,    88,   277,   279,   279,   163,
     137,   199,     7,   158,   215,   212,   124,   234,   243,   246,
     124,   124,     1,     4,   109,   215,   220,   220,   235,   122,
     122,   123,   206,    47,   215,   219,   267,   260,   235,   279,
       5,   124,   160,    21,   197,   109,   140,   141,   142,   143,
     150,   158,   162,   225,   225,   225,     7,   162,   126,   230,
     225,   225,   139,   225,   225,   225,   124,   133,   156,   158,
     222,   225,     0,   134,   124,   170,   172,   122,   132,   122,
     132,   144,   151,   120,   135,   140,   141,   142,   143,   145,
     147,   147,     1,     3,    96,   105,   124,   164,   167,   169,
     175,   176,   215,    60,   162,   123,   191,   192,   191,   219,
     267,   268,     4,   122,    88,   224,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   105,   110,
     111,   116,   117,   126,   218,   231,   236,   237,    50,   262,
     264,   118,    31,    32,   142,   274,     3,     8,   276,   125,
       1,   225,   233,     5,    21,    90,   156,   278,   280,   281,
     282,   283,   135,   138,   145,     3,     6,   202,    96,   105,
     168,     3,   220,   234,   236,   249,   220,   123,   122,     3,
       6,     8,   189,   190,   208,   269,     6,     8,   122,   122,
     120,   261,   122,   220,   190,   145,   172,   167,   226,   126,
     221,   231,   127,   225,   222,   225,   131,   167,   125,   125,
      54,   156,   173,   174,   122,   123,   152,   131,   172,    60,
     157,   167,    96,   215,   126,   165,   172,    69,   123,   165,
     170,   172,   178,   179,   232,   128,   122,   141,   169,   215,
     162,   123,   188,   190,   217,   217,   217,   217,   222,   124,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   229,   225,   228,   227,   225,   225,    37,   134,   172,
     264,   279,   125,   128,   171,     3,     6,   128,   278,   200,
     168,   168,   172,   213,   125,   244,    38,   122,   135,   158,
     220,   247,   125,   207,   122,   217,   131,   125,   161,   122,
     231,   225,   125,   125,   121,   225,   179,   171,   128,   153,
     132,   121,   167,   169,    96,   166,     5,   157,   120,   220,
     167,   176,   217,   217,   184,   185,   120,    90,   225,   123,
       3,     3,     3,   127,   241,   263,   225,   283,   120,   201,
     122,   236,   234,   122,   250,   253,   132,   121,   127,   173,
       4,     7,    59,   154,   155,   266,   269,   125,   169,   177,
     220,   179,   180,   267,   194,   125,   225,   236,   261,     3,
     203,   204,   235,   132,   231,    68,   231,   125,   127,   120,
     181,   182,   183,   225,   131,   179,   121,   128,   122,   154,
     217,   183,   121,   128,   121,   203,   235,   172,   121,   182,
     125,   251,   236
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   129,   130,   131,   131,   131,   133,   132,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   135,   137,
     136,   138,   138,   139,   140,   140,   141,   142,   143,   144,
     145,   145,   145,   145,   146,   146,   146,   147,   147,   148,
     149,   150,   150,   150,   150,   151,   152,   153,   152,   154,
     154,   154,   155,   155,   156,   157,   157,   158,   158,   158,
     158,   159,   159,   159,   159,   160,   161,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   163,   163,
     163,   163,   164,   166,   165,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   168,   168,   168,   169,
     170,   171,   172,   173,   173,   173,   173,   174,   175,   176,
     176,   176,   177,   177,   178,   179,   179,   179,   180,   179,
     179,   181,   182,   182,   183,   183,   184,   184,   184,   185,
     185,   186,   186,   186,   187,   187,   187,   188,   188,   189,
     189,   190,   190,   190,   190,   192,   191,   194,   193,   193,
     195,   197,   196,   196,   199,   200,   198,   201,   201,   202,
     202,   202,   203,   204,   204,   204,   206,   207,   205,   208,
     208,   209,   210,   210,   210,   212,   213,   211,   214,   214,
     215,   216,   217,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   219,   219,   219,   220,   221,   221,   222,
     223,   223,   223,   223,   224,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   226,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   227,   225,   228,   225,   229,   225,
     225,   225,   230,   230,   231,   231,   232,   233,   233,   233,
     234,   235,   235,   237,   236,   238,   239,   241,   240,   243,
     244,   242,   246,   245,   247,   247,   247,   249,   250,   251,
     248,   253,   252,   254,   255,   255,   256,   257,   258,   260,
     259,   261,   263,   262,   264,   264,   265,   266,   266,   267,
     267,   267,   268,   268,   268,   269,   270,   271,   272,   273,
     273,   274,   274,   275,   276,   276,   277,   278,   279,   279,
     280,   280,   281,   281,   282,   283,   283,   283
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     0,     4,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     0,
       3,     1,     1,     1,     1,     2,     4,     5,     1,     3,
       2,     1,     2,     2,     2,     4,     2,     1,     1,     2,
       1,     2,     1,     2,     2,     4,     0,     0,     3,     1,
       1,     3,     2,     2,     2,     0,     1,     1,     2,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     4,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     0,     4,     0,     1,     2,     7,     3,
       2,     3,     3,     2,     2,     1,     0,     2,     2,     1,
       1,     1,     3,     0,     1,     3,     1,     2,     2,     0,
       1,     3,     0,     1,     1,     0,     2,     1,     0,     5,
       2,     3,     1,     1,     1,     3,     1,     1,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     0,     3,     1,
       1,     0,     1,     1,     1,     0,     2,     0,     7,     2,
       2,     0,     3,     4,     0,     0,     5,     0,     3,     0,
       1,     1,     2,     0,     1,     3,     0,     0,     5,     0,
       1,     4,     3,     4,     3,     0,     0,     5,     2,     2,
       2,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     0,     3,     1,
       1,     1,     1,     1,     3,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     4,     4,     5,     3,     3,     0,     4,     3,
       3,     2,     2,     5,     2,     4,     2,     3,     3,     3,
       3,     3,     4,     2,     0,     4,     0,     4,     0,     4,
       2,     1,     0,     2,     2,     1,     3,     1,     3,     1,
       3,     0,     1,     0,     2,     2,     2,     0,     5,     0,
       0,     5,     0,     5,     1,     2,     1,     0,     0,     0,
      11,     0,     6,     3,     3,     2,     2,     2,     2,     0,
       3,     3,     0,     4,     1,     2,     3,     1,     1,     1,
       1,     3,     1,     1,     3,     2,     2,     2,     2,     2,
       3,     1,     1,     2,     1,     1,     1,     1,     2,     3,
       1,     3,     2,     2,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4: /* statement_list: statement  */
#line 161 "build/parser.y"
                             {statement_end();}
#line 2476 "gen/tparser.cpp"
    break;

  case 5: /* statement_list: statement_list statement  */
#line 162 "build/parser.y"
                             {statement_end();}
#line 2482 "gen/tparser.cpp"
    break;

  case 6: /* $@1: %empty  */
#line 166 "build/parser.y"
      { state.init_block(PLAIN_BLOCK); IEF_set(); }
#line 2488 "gen/tparser.cpp"
    break;

  case 7: /* block: '{' $@1 statement_list '}'  */
#line 168 "build/parser.y"
      { state.finalize_block(); IEF_reset();}
#line 2494 "gen/tparser.cpp"
    break;

  case 14: /* statement: expr ';'  */
#line 177 "build/parser.y"
                         {expression_end((yyvsp[-1].expression));}
#line 2500 "gen/tparser.cpp"
    break;

  case 37: /* statement: error ';'  */
#line 200 "build/parser.y"
                { raise_error("Error in statement"); YYABORT; }
#line 2506 "gen/tparser.cpp"
    break;

  case 38: /* declaration: mod_type_name tname_expr_list ';'  */
#line 206 "build/parser.y"
  { 
    Type dt = tpop();
	dcl_reset();
	state.check_dcl_init(dt);
 }
#line 2516 "gen/tparser.cpp"
    break;

  case 39: /* $@2: %empty  */
#line 215 "build/parser.y"
  { state.in_typedef = true; }
#line 2522 "gen/tparser.cpp"
    break;

  case 40: /* typedef_stmt: TYPEDEF $@2 declaration_stmt  */
#line 217 "build/parser.y"
  { state.in_typedef = false; }
#line 2528 "gen/tparser.cpp"
    break;

  case 43: /* this_classname: THIS_CLASSNAME  */
#line 228 "build/parser.y"
  {
   dcl_set();
   state.token_stack.push((yyvsp[0].classptr)->constructor_name());
   tpush(t_void);
   state.in_construct_destruct = IsConstructor;
   (yyval.classptr) = (yyvsp[0].classptr);
  }
#line 2540 "gen/tparser.cpp"
    break;

  case 44: /* construct_destruct: this_classname  */
#line 238 "build/parser.y"
                 {}
#line 2546 "gen/tparser.cpp"
    break;

  case 45: /* construct_destruct: BIN_NOT this_classname  */
#line 240 "build/parser.y"
{
  state.token_stack.TOS() = (yyvsp[0].classptr)->destructor_name();
  state.in_construct_destruct = IsDestructor;
}
#line 2555 "gen/tparser.cpp"
    break;

  case 46: /* conversion_operator: OPERATOR mod_type_name tname_exp2 arg_list  */
#line 248 "build/parser.y"
 { 
   state.token_stack.push(CONVERSION_OPNAME);
   ttpush((yyvsp[-1].ctype)); (yyval.ctype) = (yyvsp[-1].ctype);
  }
#line 2564 "gen/tparser.cpp"
    break;

  case 47: /* function_front: mod_type_name tname_expr arg_list poss_const poss_initialization  */
#line 256 "build/parser.y"
  { (yyval.ctype)=(yyvsp[-3].ctype); stots((yyval.ctype)); state.member_is_const = (yyvsp[-1].val); gFunInit = (yyvsp[0].expression); }
#line 2570 "gen/tparser.cpp"
    break;

  case 48: /* explicit_mod: EXPLICIT  */
#line 260 "build/parser.y"
 { state.modifier = Explicit; }
#line 2576 "gen/tparser.cpp"
    break;

  case 49: /* ctor_dtor_dcl: construct_destruct arg_list ';'  */
#line 265 "build/parser.y"
 {  
   state.declare_function(t_void,state.token_stack.pop());
   tpop();
   check_error();
 }
#line 2586 "gen/tparser.cpp"
    break;

  case 50: /* function_declaration: function_front ';'  */
#line 274 "build/parser.y"
 {
   state.declare_function(AsType((yyvsp[-1].ctype)),state.token_stack.pop(), gFunInit); 
   dcl_reset();
   gFunInit = NULL;
   tpop();
   check_error();
 }
#line 2598 "gen/tparser.cpp"
    break;

  case 53: /* function_declaration: conversion_operator ';'  */
#line 284 "build/parser.y"
  { 
    state.declare_function(AsType((yyvsp[-1].ctype)),state.token_stack.pop());
	tpop();
	check_error();
  }
#line 2608 "gen/tparser.cpp"
    break;

  case 54: /* extern_c_declaration: extern_qualifier any_declaration  */
#line 297 "build/parser.y"
                                              { state.extern_flag = false; }
#line 2614 "gen/tparser.cpp"
    break;

  case 55: /* extern_c_declaration: extern_c '{' statement_list '}'  */
#line 298 "build/parser.y"
                                              { state.extern_flag_C = false; }
#line 2620 "gen/tparser.cpp"
    break;

  case 56: /* extern_c_declaration: extern_c any_declaration  */
#line 299 "build/parser.y"
                                              { state.extern_flag_C = false; }
#line 2626 "gen/tparser.cpp"
    break;

  case 59: /* extern_c: EXTERN CONSTANT  */
#line 308 "build/parser.y"
                   { state.extern_flag_C = true; }
#line 2632 "gen/tparser.cpp"
    break;

  case 60: /* extern_qualifier: EXTERN  */
#line 312 "build/parser.y"
                   { state.extern_flag = true; }
#line 2638 "gen/tparser.cpp"
    break;

  case 61: /* function_definition: function_front block  */
#line 319 "build/parser.y"
  { }
#line 2644 "gen/tparser.cpp"
    break;

  case 62: /* function_definition: ctor_dtor  */
#line 321 "build/parser.y"
{}
#line 2650 "gen/tparser.cpp"
    break;

  case 63: /* function_definition: explicit_mod ctor_dtor  */
#line 323 "build/parser.y"
{}
#line 2656 "gen/tparser.cpp"
    break;

  case 64: /* function_definition: conversion_operator block  */
#line 325 "build/parser.y"
{}
#line 2662 "gen/tparser.cpp"
    break;

  case 67: /* $@3: %empty  */
#line 337 "build/parser.y"
   {   state.init_block(CONSTRUCTOR_BLOCK);  }
#line 2668 "gen/tparser.cpp"
    break;

  case 68: /* poss_class_init_list: ':' $@3 class_init_list  */
#line 339 "build/parser.y"
   {  check_error(); state.in_method = true; }
#line 2674 "gen/tparser.cpp"
    break;

  case 72: /* class_init_item: typename_function function_arg_list  */
#line 351 "build/parser.y"
    { 
	 ((Class*)state.context().parent_context())
	    ->add_class_init_list(AsType((yyvsp[-1].ctype)).as_class()->entry(),(yyvsp[0].elist));
	/* fix 1.2.3a Can crash UC if we don't catch errors in the init list */
	 if (check_error()) YYABORT;  
	}
#line 2685 "gen/tparser.cpp"
    break;

  case 73: /* class_init_item: IDEN function_arg_list  */
#line 360 "build/parser.y"
    { ((Class*)state.context().parent_context())
	      ->add_class_init_list((yyvsp[-1].entry),(yyvsp[0].elist));
	 if (check_error()) YYABORT;
    }
#line 2694 "gen/tparser.cpp"
    break;

  case 74: /* type_expr: mod_type_name tname_expr  */
#line 369 "build/parser.y"
 { (yyval.ctype) = (yyvsp[0].ctype);  }
#line 2700 "gen/tparser.cpp"
    break;

  case 75: /* poss_const: %empty  */
#line 372 "build/parser.y"
                      { (yyval.val)=0; }
#line 2706 "gen/tparser.cpp"
    break;

  case 76: /* poss_const: CONST  */
#line 373 "build/parser.y"
         { (yyval.val)=1; }
#line 2712 "gen/tparser.cpp"
    break;

  case 77: /* mod_type_name: type_name  */
#line 377 "build/parser.y"
                                 {dcl_set();}
#line 2718 "gen/tparser.cpp"
    break;

  case 78: /* mod_type_name: modifiers type_name  */
#line 378 "build/parser.y"
                                 {dcl_set();}
#line 2724 "gen/tparser.cpp"
    break;

  case 79: /* mod_type_name: CONST type_name  */
#line 379 "build/parser.y"
                                 {dcl_set(); tots().make_const();}
#line 2730 "gen/tparser.cpp"
    break;

  case 80: /* mod_type_name: modifiers CONST type_name  */
#line 380 "build/parser.y"
                                 {dcl_set(); tots().make_const();}
#line 2736 "gen/tparser.cpp"
    break;

  case 81: /* modifiers: STATIC  */
#line 384 "build/parser.y"
           {state.modifier = Static;  }
#line 2742 "gen/tparser.cpp"
    break;

  case 82: /* modifiers: VIRTUAL  */
#line 385 "build/parser.y"
           {state.modifier = Virtual; }
#line 2748 "gen/tparser.cpp"
    break;

  case 83: /* modifiers: STDCALL  */
#line 386 "build/parser.y"
           {state.modifier = Stdcall; }
#line 2754 "gen/tparser.cpp"
    break;

  case 84: /* modifiers: API  */
#line 387 "build/parser.y"
           {state.modifier = Api;     }
#line 2760 "gen/tparser.cpp"
    break;

  case 85: /* open_parens: '('  */
#line 390 "build/parser.y"
                  {dcl_set(false);}
#line 2766 "gen/tparser.cpp"
    break;

  case 86: /* close_parens: ')'  */
#line 393 "build/parser.y"
                  {dcl_reset();}
#line 2772 "gen/tparser.cpp"
    break;

  case 87: /* type_name: typename_class  */
#line 396 "build/parser.y"
                                          { ttpush((yyvsp[0].ctype));  }
#line 2778 "gen/tparser.cpp"
    break;

  case 88: /* type_name: TYPEOF open_parens expr close_parens  */
#line 397 "build/parser.y"
                                          { tpush(typeof_op((yyvsp[-1].expression))); }
#line 2784 "gen/tparser.cpp"
    break;

  case 89: /* type_name: integer  */
#line 398 "build/parser.y"
                                          { }
#line 2790 "gen/tparser.cpp"
    break;

  case 90: /* type_name: UNSIGNED integer  */
#line 399 "build/parser.y"
                                          { tots().make_unsigned(); }
#line 2796 "gen/tparser.cpp"
    break;

  case 91: /* type_name: UNSIGNED  */
#line 400 "build/parser.y"
                                          { tpush(t_int); tots().make_unsigned(); }
#line 2802 "gen/tparser.cpp"
    break;

  case 92: /* type_name: FLOAT  */
#line 401 "build/parser.y"
                                          { tpush(t_float);  }
#line 2808 "gen/tparser.cpp"
    break;

  case 93: /* type_name: DOUBLE  */
#line 402 "build/parser.y"
                                          { tpush(t_double); }
#line 2814 "gen/tparser.cpp"
    break;

  case 94: /* type_name: BOOL  */
#line 403 "build/parser.y"
                                          { tpush(t_bool); }
#line 2820 "gen/tparser.cpp"
    break;

  case 95: /* type_name: VOID  */
#line 404 "build/parser.y"
                                          { tpush(t_void); }
#line 2826 "gen/tparser.cpp"
    break;

  case 96: /* type_name: class_declaration  */
#line 405 "build/parser.y"
                                          { }
#line 2832 "gen/tparser.cpp"
    break;

  case 97: /* type_name: enum_stmt  */
#line 406 "build/parser.y"
                                          { }
#line 2838 "gen/tparser.cpp"
    break;

  case 98: /* integer: INT  */
#line 416 "build/parser.y"
                     { tpush(t_int);   }
#line 2844 "gen/tparser.cpp"
    break;

  case 99: /* integer: SHORT  */
#line 417 "build/parser.y"
                     { tpush(t_short); }
#line 2850 "gen/tparser.cpp"
    break;

  case 100: /* integer: LONG  */
#line 418 "build/parser.y"
                     { tpush(t_long);  }
#line 2856 "gen/tparser.cpp"
    break;

  case 101: /* integer: CHAR  */
#line 423 "build/parser.y"
                     { tpush(t_char);  }
#line 2862 "gen/tparser.cpp"
    break;

  case 102: /* pointer_expr: '(' STAR token ')'  */
#line 427 "build/parser.y"
                   { (yyval.ctype) = incr_ptr((yyvsp[-1].ctype)); }
#line 2868 "gen/tparser.cpp"
    break;

  case 103: /* $@4: %empty  */
#line 431 "build/parser.y"
       {dcl_set(false);}
#line 2874 "gen/tparser.cpp"
    break;

  case 104: /* array_expr: '[' $@4 poss_int_const ']'  */
#line 433 "build/parser.y"
                         { dcl_reset(); (yyval.expression) = (yyvsp[-1].expression); }
#line 2880 "gen/tparser.cpp"
    break;

  case 105: /* tname_expr: %empty  */
#line 436 "build/parser.y"
                                { (yyval.ctype)=ttots(); state.token_stack.push(""); }
#line 2886 "gen/tparser.cpp"
    break;

  case 106: /* tname_expr: token  */
#line 437 "build/parser.y"
                                { (yyval.ctype)=(yyvsp[0].ctype);   }
#line 2892 "gen/tparser.cpp"
    break;

  case 107: /* tname_expr: pointer_expr arg_list  */
#line 438 "build/parser.y"
                                { Type t = AsType((yyvsp[-1].ctype)); t.decr_pointer(); (yyval.ctype) = AsTType(state.signature_type(t));     }
#line 2898 "gen/tparser.cpp"
    break;

  case 108: /* tname_expr: '(' scope STAR token ')' end_scope arg_list  */
#line 441 "build/parser.y"
                                { state.class_dcl = AsType((yyvsp[-5].ctype)); (yyval.ctype) = AsTType(state.signature_type(AsType((yyvsp[-3].ctype))));  }
#line 2904 "gen/tparser.cpp"
    break;

  case 109: /* tname_expr: STAR poss_const tname_expr  */
#line 442 "build/parser.y"
                                { (yyval.ctype) = incr_ptr((yyvsp[0].ctype));         }
#line 2910 "gen/tparser.cpp"
    break;

  case 110: /* tname_expr: ADDR tname_expr  */
#line 443 "build/parser.y"
                                { (yyval.ctype) = make_ref((yyvsp[0].ctype));         }
#line 2916 "gen/tparser.cpp"
    break;

  case 111: /* tname_expr: scope token end_scope  */
#line 444 "build/parser.y"
                                { (yyval.ctype) = (yyvsp[-1].ctype);   state.class_dcl = AsType((yyvsp[-2].ctype)); }
#line 2922 "gen/tparser.cpp"
    break;

  case 112: /* tname_expr: scope conversion_operator end_scope  */
#line 446 "build/parser.y"
                                { (yyval.ctype) = (yyvsp[-1].ctype);   state.class_dcl = AsType((yyvsp[-2].ctype)); }
#line 2928 "gen/tparser.cpp"
    break;

  case 113: /* tname_expr: tname_expr array_expr  */
#line 447 "build/parser.y"
                                { (yyval.ctype) = make_array((yyvsp[-1].ctype),(yyvsp[0].expression)); check_error();   }
#line 2934 "gen/tparser.cpp"
    break;

  case 114: /* tname_expr: pointer_expr array_expr  */
#line 448 "build/parser.y"
                                { (yyval.ctype) = make_array((yyvsp[-1].ctype),(yyvsp[0].expression)); check_error();   }
#line 2940 "gen/tparser.cpp"
    break;

  case 115: /* tname_expr: error  */
#line 449 "build/parser.y"
          { raise_error("Error in type expression"); YYABORT; }
#line 2946 "gen/tparser.cpp"
    break;

  case 116: /* tname_exp2: %empty  */
#line 453 "build/parser.y"
                          { (yyval.ctype) = ttots(); }
#line 2952 "gen/tparser.cpp"
    break;

  case 117: /* tname_exp2: STAR tname_exp2  */
#line 454 "build/parser.y"
                          { (yyval.ctype) = incr_ptr((yyvsp[0].ctype)); }
#line 2958 "gen/tparser.cpp"
    break;

  case 118: /* tname_exp2: ADDR tname_exp2  */
#line 455 "build/parser.y"
                          { (yyval.ctype) = make_ref((yyvsp[0].ctype)); }
#line 2964 "gen/tparser.cpp"
    break;

  case 119: /* token: TOKEN  */
#line 458 "build/parser.y"
             { (yyval.ctype)=ttots(); state.token_stack.push((yyvsp[0].str)); }
#line 2970 "gen/tparser.cpp"
    break;

  case 120: /* begin_list: '('  */
#line 462 "build/parser.y"
                { dcl_set(false); state.begin_args(); }
#line 2976 "gen/tparser.cpp"
    break;

  case 121: /* end_list: ')'  */
#line 465 "build/parser.y"
              { dcl_reset(); }
#line 2982 "gen/tparser.cpp"
    break;

  case 126: /* type_list: THREEDOT  */
#line 476 "build/parser.y"
 { 
   state.add_to_arg_list(t_void,"...",0);
 }
#line 2990 "gen/tparser.cpp"
    break;

  case 127: /* type_expr_init: type_expr poss_initialization  */
#line 483 "build/parser.y"
{  
  state.add_to_arg_list(AsType((yyvsp[-1].ctype)),state.token_stack.pop(),(yyvsp[0].expression));
  tpop();
  dcl_reset();
}
#line 3000 "gen/tparser.cpp"
    break;

  case 128: /* init_tname_expr: tname_expr poss_initialization  */
#line 492 "build/parser.y"
  {
  string name = state.token_stack.pop();
  Type t = AsType((yyvsp[-1].ctype));
  temp_context()->reserved_space(t.size());
  state.add_variable(t,name,(yyvsp[0].expression),state.modifier);
  if (check_error()) YYABORT;
  }
#line 3012 "gen/tparser.cpp"
    break;

  case 132: /* poss_int_const: %empty  */
#line 506 "build/parser.y"
                          { (yyval.expression)=NULL; }
#line 3018 "gen/tparser.cpp"
    break;

  case 133: /* poss_int_const: expr  */
#line 507 "build/parser.y"
        {(yyval.expression)=(yyvsp[0].expression);}
#line 3024 "gen/tparser.cpp"
    break;

  case 134: /* init_assign: ASSIGN  */
#line 513 "build/parser.y"
                    { dcl_set(false); }
#line 3030 "gen/tparser.cpp"
    break;

  case 135: /* poss_initialization: %empty  */
#line 516 "build/parser.y"
                                             { (yyval.expression)=NULL; }
#line 3036 "gen/tparser.cpp"
    break;

  case 136: /* poss_initialization: init_assign expr  */
#line 519 "build/parser.y"
  { dcl_reset(); (yyval.expression)=(yyvsp[0].expression); }
#line 3042 "gen/tparser.cpp"
    break;

  case 137: /* poss_initialization: init_list  */
#line 522 "build/parser.y"
  { (yyval.expression)=expr_list_op((yyvsp[0].elist),true); }
#line 3048 "gen/tparser.cpp"
    break;

  case 138: /* $@5: %empty  */
#line 524 "build/parser.y"
                       { enter_arglist();}
#line 3054 "gen/tparser.cpp"
    break;

  case 139: /* poss_initialization: init_assign '{' $@5 brace_list '}'  */
#line 526 "build/parser.y"
  {leave_arglist(); dcl_reset(); (yyval.expression)=expr_list_op((yyvsp[-1].elist),false); }
#line 3060 "gen/tparser.cpp"
    break;

  case 140: /* poss_initialization: ':' CONSTANT  */
#line 529 "build/parser.y"
  { (yyval.expression) = new Expr(ECONST,t_void,(yyvsp[0].entry),NULL); }
#line 3066 "gen/tparser.cpp"
    break;

  case 141: /* brace_expr: '{' brace_list '}'  */
#line 536 "build/parser.y"
                                { (yyval.elist) = (yyvsp[-1].elist); }
#line 3072 "gen/tparser.cpp"
    break;

  case 142: /* brace_item: _expr  */
#line 539 "build/parser.y"
                  { (yyval.expression) = (yyvsp[0].expression); }
#line 3078 "gen/tparser.cpp"
    break;

  case 143: /* brace_item: brace_expr  */
#line 540 "build/parser.y"
                  { (yyval.expression) = expr_list_op((yyvsp[0].elist),false); }
#line 3084 "gen/tparser.cpp"
    break;

  case 144: /* brace_list: brace_item  */
#line 543 "build/parser.y"
                              { (yyval.elist) = new ExprList; (yyval.elist)->push_back((yyvsp[0].expression));  }
#line 3090 "gen/tparser.cpp"
    break;

  case 145: /* brace_list: brace_list ',' brace_item  */
#line 544 "build/parser.y"
                              { (yyval.elist) = (yyvsp[-2].elist); (yyval.elist)->push_back((yyvsp[0].expression)); }
#line 3096 "gen/tparser.cpp"
    break;

  case 146: /* access_modifier: PUBLIC  */
#line 554 "build/parser.y"
             {(yyval.val)=Public;}
#line 3102 "gen/tparser.cpp"
    break;

  case 147: /* access_modifier: PRIVATE  */
#line 555 "build/parser.y"
             {(yyval.val)=Private;}
#line 3108 "gen/tparser.cpp"
    break;

  case 148: /* access_modifier: PROTECTED  */
#line 556 "build/parser.y"
             {(yyval.val)=Protected;}
#line 3114 "gen/tparser.cpp"
    break;

  case 149: /* poss_access_modifier: %empty  */
#line 559 "build/parser.y"
                                { (yyval.val)=Default; }
#line 3120 "gen/tparser.cpp"
    break;

  case 154: /* class_or_struct_ex: CLASS_Y  */
#line 565 "build/parser.y"
                             { (yyval.val) = CLASS; }
#line 3126 "gen/tparser.cpp"
    break;

  case 155: /* class_or_struct_ex: STRUCT_Y  */
#line 566 "build/parser.y"
                             { (yyval.val) = STRUCT; }
#line 3132 "gen/tparser.cpp"
    break;

  case 156: /* class_or_struct_ex: UNION_Y  */
#line 567 "build/parser.y"
                             { (yyval.val) = UNION;  }
#line 3138 "gen/tparser.cpp"
    break;

  case 157: /* poss_derived: %empty  */
#line 570 "build/parser.y"
                        { (yyval.val)=NotDerived; }
#line 3144 "gen/tparser.cpp"
    break;

  case 158: /* poss_derived: ':' poss_access_modifier typename_class  */
#line 572 "build/parser.y"
 { (yyval.val)=(yyvsp[-1].val); state.class_dcl = AsType((yyvsp[0].ctype)); }
#line 3150 "gen/tparser.cpp"
    break;

  case 159: /* token_or_typename: TOKEN  */
#line 576 "build/parser.y"
                            { (yyval.str) = (yyvsp[0].str);               }
#line 3156 "gen/tparser.cpp"
    break;

  case 160: /* token_or_typename: TYPENAME  */
#line 577 "build/parser.y"
                            { (yyval.str) = (yyvsp[0].entry)->name.c_str(); }
#line 3162 "gen/tparser.cpp"
    break;

  case 161: /* class_name: %empty  */
#line 580 "build/parser.y"
                            { (yyval.str) = "";               }
#line 3168 "gen/tparser.cpp"
    break;

  case 162: /* class_name: token_or_typename  */
#line 581 "build/parser.y"
                            { (yyval.str) = (yyvsp[0].str);               }
#line 3174 "gen/tparser.cpp"
    break;

  case 163: /* class_name: template_class  */
#line 583 "build/parser.y"
   { PClass pc = AsType((yyvsp[0].ctype)).as_class();
     (yyval.str) = pc->name().c_str();
    }
#line 3182 "gen/tparser.cpp"
    break;

  case 164: /* class_name: TEMPLATE_NAME  */
#line 586 "build/parser.y"
                            { (yyval.str) = (yyvsp[0].entry)->name.c_str(); }
#line 3188 "gen/tparser.cpp"
    break;

  case 165: /* $@6: %empty  */
#line 589 "build/parser.y"
          { dcl_set();}
#line 3194 "gen/tparser.cpp"
    break;

  case 166: /* class_id: $@6 class_name  */
#line 589 "build/parser.y"
                                   { dcl_reset(); (yyval.str) = (yyvsp[0].str);  }
#line 3200 "gen/tparser.cpp"
    break;

  case 167: /* $@7: %empty  */
#line 596 "build/parser.y"
      { 
	   tpush(state.add_class((yyvsp[-3].val),(yyvsp[-2].str),(yyvsp[-1].val),state.class_dcl));
       if (check_error()) YYABORT;
	   state.init_block(CLASS_BLOCK); IEF_set();
       typedef_stack.push(state.in_typedef);
       state.in_typedef = false;
      }
#line 3212 "gen/tparser.cpp"
    break;

  case 168: /* class_declaration: class_or_struct class_id poss_derived '{' $@7 statement_list '}'  */
#line 606 "build/parser.y"
     {
	   state.finalize_block(); IEF_reset();
  	   state.in_typedef = typedef_stack.pop(); 
	 }
#line 3221 "gen/tparser.cpp"
    break;

  case 169: /* class_declaration: class_or_struct_ex class_id  */
#line 612 "build/parser.y"
     { tpush(state.add_class((yyvsp[-1].val),(yyvsp[0].str),ForwardClass,t_void)); }
#line 3227 "gen/tparser.cpp"
    break;

  case 170: /* access_specifier: access_modifier ':'  */
#line 616 "build/parser.y"
  { state.set_access_mode((yyvsp[-1].val)); }
#line 3233 "gen/tparser.cpp"
    break;

  case 171: /* $@8: %empty  */
#line 620 "build/parser.y"
          { state.in_friend_dcl = true; }
#line 3239 "gen/tparser.cpp"
    break;

  case 173: /* friend_declaration: FRIEND CLASS class_name ';'  */
#line 621 "build/parser.y"
                              { state.add_friend_class((yyvsp[-1].str)); }
#line 3245 "gen/tparser.cpp"
    break;

  case 174: /* $@9: %empty  */
#line 631 "build/parser.y"
       { dcl_set(); }
#line 3251 "gen/tparser.cpp"
    break;

  case 175: /* $@10: %empty  */
#line 632 "build/parser.y"
   {
    tpush(state.do_enum(tag_name));
    if (check_error()) YYABORT;
   }
#line 3260 "gen/tparser.cpp"
    break;

  case 176: /* enum_stmt: ENUM $@9 poss_tag $@10 poss_enum_list  */
#line 637 "build/parser.y"
  { state.finish_enum((yyvsp[0].val) != 0); dcl_reset(); }
#line 3266 "gen/tparser.cpp"
    break;

  case 177: /* poss_enum_list: %empty  */
#line 640 "build/parser.y"
                          { (yyval.val)=0; }
#line 3272 "gen/tparser.cpp"
    break;

  case 178: /* poss_enum_list: '{' enum_list '}'  */
#line 641 "build/parser.y"
                    { (yyval.val)=1; }
#line 3278 "gen/tparser.cpp"
    break;

  case 179: /* poss_tag: %empty  */
#line 644 "build/parser.y"
                    {(yyval.str)=NULL; tag_name="";}
#line 3284 "gen/tparser.cpp"
    break;

  case 180: /* poss_tag: TOKEN  */
#line 645 "build/parser.y"
        {(yyval.str)=(yyvsp[0].str); tag_name=(yyvsp[0].str);}
#line 3290 "gen/tparser.cpp"
    break;

  case 181: /* poss_tag: TYPENAME  */
#line 646 "build/parser.y"
           {(yyval.str)=""; tag_name=(yyvsp[0].entry)->name.c_str();}
#line 3296 "gen/tparser.cpp"
    break;

  case 182: /* enum_item: TOKEN poss_initialization  */
#line 651 "build/parser.y"
 { 
  state.add_enum(tots(),(yyvsp[-1].str),(yyvsp[0].expression));
 }
#line 3304 "gen/tparser.cpp"
    break;

  case 186: /* $@11: %empty  */
#line 665 "build/parser.y"
            { dcl_set(); }
#line 3310 "gen/tparser.cpp"
    break;

  case 187: /* $@12: %empty  */
#line 666 "build/parser.y"
  { dcl_reset(); 
    state.add_namespace((yyvsp[0].str) ? (yyvsp[0].str) : "");
    state.in_class = true;
    if (check_error()) YYABORT;
   }
#line 3320 "gen/tparser.cpp"
    break;

  case 189: /* poss_class_name: %empty  */
#line 674 "build/parser.y"
                            { (yyval.str) = NULL; }
#line 3326 "gen/tparser.cpp"
    break;

  case 190: /* poss_class_name: class_name  */
#line 675 "build/parser.y"
              { (yyval.str) = (yyvsp[0].str);  }
#line 3332 "gen/tparser.cpp"
    break;

  case 191: /* using_directive: USING NAMESPACE TYPENAME ';'  */
#line 681 "build/parser.y"
   { 
   	if ((Namespace *)(yyvsp[-1].entry)->data != &state.context()) 
      state.context().inject_namespace((Namespace *)(yyvsp[-1].entry)->data);
    else raise_error("Cannot inject a namespace into itself");
    if (check_error()) YYABORT;
   }
#line 3343 "gen/tparser.cpp"
    break;

  case 192: /* using_declaration: USING scoped_name ';'  */
#line 691 "build/parser.y"
   {  state.context().inject_entry((yyvsp[-1].entry));  }
#line 3349 "gen/tparser.cpp"
    break;

  case 193: /* using_declaration: USING scope TEMPLATE_NAME end_scope  */
#line 693 "build/parser.y"
   { state.context().inject_entry((yyvsp[-1].entry)); }
#line 3355 "gen/tparser.cpp"
    break;

  case 194: /* using_declaration: USING typename_class ';'  */
#line 695 "build/parser.y"
   { state.context().inject_entry(last_type_entry);  }
#line 3361 "gen/tparser.cpp"
    break;

  case 195: /* $@13: %empty  */
#line 700 "build/parser.y"
       { dcl_set(true); }
#line 3367 "gen/tparser.cpp"
    break;

  case 196: /* $@14: %empty  */
#line 700 "build/parser.y"
                                { dcl_reset(); }
#line 3373 "gen/tparser.cpp"
    break;

  case 197: /* goto_stmt: GOTO $@13 TOKEN $@14 ';'  */
#line 701 "build/parser.y"
  { do_goto((yyvsp[-2].str)); }
#line 3379 "gen/tparser.cpp"
    break;

  case 198: /* goto_label: TOKEN ':'  */
#line 705 "build/parser.y"
             { goto_label_new((yyvsp[-1].str)); }
#line 3385 "gen/tparser.cpp"
    break;

  case 199: /* goto_label: IDEN ':'  */
#line 706 "build/parser.y"
             { goto_label_existing((yyvsp[-1].entry)); }
#line 3391 "gen/tparser.cpp"
    break;

  case 200: /* scope: typename_expr BINARY_SCOPE  */
#line 714 "build/parser.y"
  { state.begin_scope(AsType((yyvsp[-1].ctype))); (yyval.ctype) = (yyvsp[-1].ctype); }
#line 3397 "gen/tparser.cpp"
    break;

  case 201: /* global_scope: BINARY_SCOPE  */
#line 719 "build/parser.y"
  { state.begin_scope(&global()); }
#line 3403 "gen/tparser.cpp"
    break;

  case 202: /* end_scope: %empty  */
#line 722 "build/parser.y"
  { state.end_scope(); }
#line 3409 "gen/tparser.cpp"
    break;

  case 214: /* scoped_name: scope scoped_name end_scope  */
#line 732 "build/parser.y"
  { (yyval.entry) = (yyvsp[-1].entry); }
#line 3415 "gen/tparser.cpp"
    break;

  case 215: /* scoped_name: global_scope IDEN end_scope  */
#line 734 "build/parser.y"
  { (yyval.entry) = (yyvsp[-1].entry); }
#line 3421 "gen/tparser.cpp"
    break;

  case 216: /* expr: _expr  */
#line 738 "build/parser.y"
 {   if (check_error()) YYABORT;   (yyval.expression) = (yyvsp[0].expression); }
#line 3427 "gen/tparser.cpp"
    break;

  case 217: /* poss_size: %empty  */
#line 741 "build/parser.y"
                     { (yyval.expression) = NULL; }
#line 3433 "gen/tparser.cpp"
    break;

  case 218: /* poss_size: '[' _expr ']'  */
#line 742 "build/parser.y"
                             { (yyval.expression) = (yyvsp[-1].expression); }
#line 3439 "gen/tparser.cpp"
    break;

  case 219: /* type_expression: type_expr  */
#line 746 "build/parser.y"
{ dcl_reset(); (yyval.ctype)=(yyvsp[0].ctype); state.token_stack.pop(); tpop(); }
#line 3445 "gen/tparser.cpp"
    break;

  case 224: /* type_bracket: LESS_THAN type_expression GREATER  */
#line 753 "build/parser.y"
                  { (yyval.ctype)=(yyvsp[-1].ctype); }
#line 3451 "gen/tparser.cpp"
    break;

  case 225: /* _expr: CONSTANT  */
#line 758 "build/parser.y"
                { (yyval.expression) =  entry_op((yyvsp[0].entry)); }
#line 3457 "gen/tparser.cpp"
    break;

  case 226: /* _expr: scoped_name  */
#line 759 "build/parser.y"
                       { (yyval.expression) =  entry_op((yyvsp[0].entry)); }
#line 3463 "gen/tparser.cpp"
    break;

  case 227: /* _expr: '(' _expr ')'  */
#line 760 "build/parser.y"
                 { (yyval.expression) =  (yyvsp[-1].expression); }
#line 3469 "gen/tparser.cpp"
    break;

  case 228: /* _expr: _expr STAR _expr  */
#line 762 "build/parser.y"
                      { (yyval.expression)=arith_op(STAR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3475 "gen/tparser.cpp"
    break;

  case 229: /* _expr: _expr DIVIDE _expr  */
#line 763 "build/parser.y"
                        { (yyval.expression)=arith_op(DIVIDE,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3481 "gen/tparser.cpp"
    break;

  case 230: /* _expr: _expr MODULO _expr  */
#line 764 "build/parser.y"
                        { (yyval.expression)=arith_op(MODULO,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3487 "gen/tparser.cpp"
    break;

  case 231: /* _expr: _expr PLUS _expr  */
#line 765 "build/parser.y"
                     { (yyval.expression)=arith_op(PLUS,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3493 "gen/tparser.cpp"
    break;

  case 232: /* _expr: _expr MINUS _expr  */
#line 766 "build/parser.y"
                     { (yyval.expression)=arith_op(MINUS,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3499 "gen/tparser.cpp"
    break;

  case 233: /* _expr: _expr BIN_AND _expr  */
#line 767 "build/parser.y"
                      { (yyval.expression)=arith_op(BIN_AND,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3505 "gen/tparser.cpp"
    break;

  case 234: /* _expr: _expr BIN_OR _expr  */
#line 768 "build/parser.y"
                     { (yyval.expression)=arith_op(BIN_OR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3511 "gen/tparser.cpp"
    break;

  case 235: /* _expr: PLUS _expr  */
#line 770 "build/parser.y"
                             { (yyval.expression)=(yyvsp[0].expression); }
#line 3517 "gen/tparser.cpp"
    break;

  case 236: /* _expr: MINUS _expr  */
#line 771 "build/parser.y"
                             { (yyval.expression)=unary_op(UMINUS,(yyvsp[0].expression)); }
#line 3523 "gen/tparser.cpp"
    break;

  case 237: /* _expr: LOG_NOT _expr  */
#line 773 "build/parser.y"
                        { (yyval.expression)=relational_op(LOG_NOT,(yyvsp[0].expression),NULL); }
#line 3529 "gen/tparser.cpp"
    break;

  case 238: /* _expr: _expr LESS_THAN _expr  */
#line 774 "build/parser.y"
                          { (yyval.expression)=relational_op(LESS_THAN,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3535 "gen/tparser.cpp"
    break;

  case 239: /* _expr: _expr GREATER _expr  */
#line 775 "build/parser.y"
                        { (yyval.expression)=relational_op(GREATER,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3541 "gen/tparser.cpp"
    break;

  case 240: /* _expr: _expr LEQ _expr  */
#line 776 "build/parser.y"
                    { (yyval.expression)=relational_op(LEQ,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3547 "gen/tparser.cpp"
    break;

  case 241: /* _expr: _expr GEQ _expr  */
#line 777 "build/parser.y"
                    { (yyval.expression)=relational_op(GEQ,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3553 "gen/tparser.cpp"
    break;

  case 242: /* _expr: _expr EQUAL _expr  */
#line 778 "build/parser.y"
                      { (yyval.expression)=equal_op((yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3559 "gen/tparser.cpp"
    break;

  case 243: /* _expr: _expr NOT_EQUAL _expr  */
#line 779 "build/parser.y"
                          { (yyval.expression)=relational_op(NOT_EQUAL,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3565 "gen/tparser.cpp"
    break;

  case 244: /* _expr: _expr LOG_AND _expr  */
#line 780 "build/parser.y"
                        { (yyval.expression)=relational_op(LOG_AND,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3571 "gen/tparser.cpp"
    break;

  case 245: /* _expr: _expr LOG_OR _expr  */
#line 781 "build/parser.y"
                       { (yyval.expression)=relational_op(LOG_OR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3577 "gen/tparser.cpp"
    break;

  case 246: /* _expr: _expr ASSIGN _expr  */
#line 783 "build/parser.y"
                     { (yyval.expression)=assign_op((yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3583 "gen/tparser.cpp"
    break;

  case 247: /* _expr: _expr assign_op _expr  */
#line 784 "build/parser.y"
                        { (yyval.expression)=compound_assign_op((yyvsp[-1].val),(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3589 "gen/tparser.cpp"
    break;

  case 248: /* _expr: _expr INCR  */
#line 786 "build/parser.y"
                    { (yyval.expression)=inc_dec_op(INCR,(yyvsp[-1].expression),true); }
#line 3595 "gen/tparser.cpp"
    break;

  case 249: /* _expr: INCR _expr  */
#line 787 "build/parser.y"
                    { (yyval.expression)=inc_dec_op(INCR,(yyvsp[0].expression),false); }
#line 3601 "gen/tparser.cpp"
    break;

  case 250: /* _expr: _expr DECR  */
#line 788 "build/parser.y"
                    { (yyval.expression)=inc_dec_op(DECR,(yyvsp[-1].expression),true); }
#line 3607 "gen/tparser.cpp"
    break;

  case 251: /* _expr: DECR _expr  */
#line 789 "build/parser.y"
                    { (yyval.expression)=inc_dec_op(DECR,(yyvsp[0].expression),false); }
#line 3613 "gen/tparser.cpp"
    break;

  case 252: /* _expr: SIZEOF '(' _expr ')'  */
#line 793 "build/parser.y"
                           { 
    if ((yyvsp[-1].expression)->is_entry()) (yyval.expression) = sizeof_op(size_of_entry((yyvsp[-1].expression)->entry()));
	              else  (yyval.expression) = sizeof_op((yyvsp[-1].expression)->type().size());
 }
#line 3622 "gen/tparser.cpp"
    break;

  case 253: /* _expr: SIZEOF '(' type_expression ')'  */
#line 797 "build/parser.y"
                                 { (yyval.expression)=sizeof_op(AsType((yyvsp[-1].ctype)).size());  }
#line 3628 "gen/tparser.cpp"
    break;

  case 254: /* _expr: _expr ARITH_IF _expr ':' _expr  */
#line 798 "build/parser.y"
                                 { (yyval.expression)=arith_if_op((yyvsp[-4].expression),(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3634 "gen/tparser.cpp"
    break;

  case 255: /* _expr: _expr COMMA _expr  */
#line 799 "build/parser.y"
                     { (yyval.expression)=bin_op(COMMA,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3640 "gen/tparser.cpp"
    break;

  case 256: /* _expr: NEW type_name poss_size  */
#line 801 "build/parser.y"
  { (yyval.expression) = new_op(tpop(),(yyvsp[0].expression),NULL);  }
#line 3646 "gen/tparser.cpp"
    break;

  case 257: /* $@15: %empty  */
#line 803 "build/parser.y"
                         { tpush((yyvsp[0].entry)->type); }
#line 3652 "gen/tparser.cpp"
    break;

  case 258: /* _expr: NEW TYPENAME_FUNCTION $@15 function_arg_list  */
#line 804 "build/parser.y"
  { (yyval.expression) = new_op(tpop(),NULL,(yyvsp[0].elist));  }
#line 3658 "gen/tparser.cpp"
    break;

  case 259: /* _expr: NEW type_name function_arg_list  */
#line 807 "build/parser.y"
  { (yyval.expression) = new_op(tpop(),NULL,(yyvsp[0].elist));  }
#line 3664 "gen/tparser.cpp"
    break;

  case 260: /* _expr: DELETE poss_array _expr  */
#line 808 "build/parser.y"
                                     { (yyval.expression) = delete_op((yyvsp[0].expression),(yyvsp[-1].val)==1); }
#line 3670 "gen/tparser.cpp"
    break;

  case 261: /* _expr: STAR _expr  */
#line 809 "build/parser.y"
                           { (yyval.expression) = deref_op((yyvsp[0].expression)); }
#line 3676 "gen/tparser.cpp"
    break;

  case 262: /* _expr: ADDR _expr  */
#line 810 "build/parser.y"
                           { (yyval.expression) = addr_op((yyvsp[0].expression)); }
#line 3682 "gen/tparser.cpp"
    break;

  case 263: /* _expr: typecast_type type_bracket '(' _expr ')'  */
#line 813 "build/parser.y"
  { (yyval.expression) = typecast_op((yyvsp[-4].val),AsType((yyvsp[-3].ctype)),(yyvsp[-1].expression)); }
#line 3688 "gen/tparser.cpp"
    break;

  case 264: /* _expr: TYPENAME_FUNCTION function_arg_list  */
#line 816 "build/parser.y"
  { (yyval.expression) = function_cast_op((yyvsp[-1].entry)->type /*AsType($1)*/,(yyvsp[0].elist)); }
#line 3694 "gen/tparser.cpp"
    break;

  case 265: /* _expr: '(' type_expression ')' _expr  */
#line 819 "build/parser.y"
  { (yyval.expression) = typecast_op(REINTERPRET_CAST,AsType((yyvsp[-2].ctype)),(yyvsp[0].expression)); }
#line 3700 "gen/tparser.cpp"
    break;

  case 266: /* _expr: BIN_NOT _expr  */
#line 822 "build/parser.y"
                       { (yyval.expression)=unary_op(BIN_NOT,(yyvsp[0].expression)); }
#line 3706 "gen/tparser.cpp"
    break;

  case 267: /* _expr: _expr LSHIFT _expr  */
#line 823 "build/parser.y"
                        { (yyval.expression)=bin_op(LSHIFT,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3712 "gen/tparser.cpp"
    break;

  case 268: /* _expr: _expr RSHIFT _expr  */
#line 824 "build/parser.y"
                        { (yyval.expression)=bin_op(RSHIFT,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3718 "gen/tparser.cpp"
    break;

  case 269: /* _expr: _expr ADDR _expr  */
#line 825 "build/parser.y"
                                  { (yyval.expression)=bin_op(BIN_AND,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3724 "gen/tparser.cpp"
    break;

  case 270: /* _expr: _expr BIN_XOR _expr  */
#line 826 "build/parser.y"
                       { (yyval.expression)=bin_op(BIN_XOR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3730 "gen/tparser.cpp"
    break;

  case 271: /* _expr: _expr BIN_OR _expr  */
#line 827 "build/parser.y"
                     { (yyval.expression)=bin_op(BIN_OR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3736 "gen/tparser.cpp"
    break;

  case 272: /* _expr: _expr '[' _expr ']'  */
#line 830 "build/parser.y"
  { (yyval.expression)=array_op((yyvsp[-3].expression), (yyvsp[-1].expression)); }
#line 3742 "gen/tparser.cpp"
    break;

  case 273: /* _expr: _expr function_arg_list  */
#line 832 "build/parser.y"
                          { (yyval.expression)=function_op((yyvsp[-1].expression),(yyvsp[0].elist)); }
#line 3748 "gen/tparser.cpp"
    break;

  case 274: /* $@16: %empty  */
#line 835 "build/parser.y"
  {dcl_set(); }
#line 3754 "gen/tparser.cpp"
    break;

  case 275: /* _expr: _expr DOT $@16 TOKEN  */
#line 837 "build/parser.y"
  { dcl_reset(); (yyval.expression)=selection_op((yyvsp[-3].expression),(yyvsp[0].str),false);  }
#line 3760 "gen/tparser.cpp"
    break;

  case 276: /* $@17: %empty  */
#line 840 "build/parser.y"
  {dcl_set();}
#line 3766 "gen/tparser.cpp"
    break;

  case 277: /* _expr: _expr ARROW $@17 TOKEN  */
#line 842 "build/parser.y"
  { dcl_reset(); (yyval.expression)=selection_op((yyvsp[-3].expression),(yyvsp[0].str),true);  }
#line 3772 "gen/tparser.cpp"
    break;

  case 278: /* $@18: %empty  */
#line 844 "build/parser.y"
  {dcl_set();}
#line 3778 "gen/tparser.cpp"
    break;

  case 279: /* _expr: _expr MEMBER_ARROW $@18 TOKEN  */
#line 846 "build/parser.y"
  { dcl_reset(); (yyval.expression)=selection_op((yyvsp[-3].expression),(yyvsp[0].str),true,true);  }
#line 3784 "gen/tparser.cpp"
    break;

  case 280: /* _expr: LAMBDA function_definition  */
#line 850 "build/parser.y"
    { (yyval.expression)=lambda_op(0);   }
#line 3790 "gen/tparser.cpp"
    break;

  case 281: /* _expr: error  */
#line 852 "build/parser.y"
        { raise_error("error in expression"); YYABORT; }
#line 3796 "gen/tparser.cpp"
    break;

  case 282: /* poss_array: %empty  */
#line 855 "build/parser.y"
                      { (yyval.val) = 0; }
#line 3802 "gen/tparser.cpp"
    break;

  case 283: /* poss_array: '[' ']'  */
#line 856 "build/parser.y"
           { (yyval.val) = 1; }
#line 3808 "gen/tparser.cpp"
    break;

  case 284: /* function_arg_list: '(' ')'  */
#line 863 "build/parser.y"
                                { (yyval.elist) = new ExprList; }
#line 3814 "gen/tparser.cpp"
    break;

  case 285: /* function_arg_list: init_list  */
#line 864 "build/parser.y"
                                { (yyval.elist) = (yyvsp[0].elist); }
#line 3820 "gen/tparser.cpp"
    break;

  case 286: /* init_list: begin_list expr_list end_list  */
#line 870 "build/parser.y"
                                     { (yyval.elist) = (yyvsp[-1].elist); }
#line 3826 "gen/tparser.cpp"
    break;

  case 287: /* expr_list: _expr  */
#line 874 "build/parser.y"
                        { (yyval.elist) = new ExprList; (yyval.elist)->push_back((yyvsp[0].expression));  }
#line 3832 "gen/tparser.cpp"
    break;

  case 288: /* expr_list: expr_list ',' _expr  */
#line 875 "build/parser.y"
                        { (yyval.elist) = (yyvsp[-2].elist); (yyval.elist)->push_back((yyvsp[0].expression)); }
#line 3838 "gen/tparser.cpp"
    break;

  case 289: /* expr_list: error  */
#line 876 "build/parser.y"
                       { raise_error("Error in arg list"); YYABORT; }
#line 3844 "gen/tparser.cpp"
    break;

  case 290: /* condition: '(' expr ')'  */
#line 881 "build/parser.y"
                { (yyval.expression) = (yyvsp[-1].expression); }
#line 3850 "gen/tparser.cpp"
    break;

  case 291: /* poss_expr: %empty  */
#line 885 "build/parser.y"
                     { (yyval.expression) = NULL; }
#line 3856 "gen/tparser.cpp"
    break;

  case 292: /* poss_expr: expr  */
#line 886 "build/parser.y"
        { (yyval.expression) = (yyvsp[0].expression); }
#line 3862 "gen/tparser.cpp"
    break;

  case 293: /* $@19: %empty  */
#line 890 "build/parser.y"
  {IEF_set();}
#line 3868 "gen/tparser.cpp"
    break;

  case 294: /* controlled_statement: $@19 statement  */
#line 892 "build/parser.y"
  {IEF_reset(); check_temp_context(); }
#line 3874 "gen/tparser.cpp"
    break;

  case 295: /* if_front: IF condition  */
#line 896 "build/parser.y"
               { do_loop_start((yyvsp[0].expression),false); }
#line 3880 "gen/tparser.cpp"
    break;

  case 296: /* if_stmt: if_front controlled_statement  */
#line 900 "build/parser.y"
                                { do_loop_end(false); }
#line 3886 "gen/tparser.cpp"
    break;

  case 297: /* $@20: %empty  */
#line 905 "build/parser.y"
                                   { do_loop_end(true,true); }
#line 3892 "gen/tparser.cpp"
    break;

  case 298: /* if_else_stmt: if_front controlled_statement ELSE $@20 controlled_statement  */
#line 906 "build/parser.y"
                                   { do_loop_end(false);     }
#line 3898 "gen/tparser.cpp"
    break;

  case 299: /* $@21: %empty  */
#line 910 "build/parser.y"
                         { label_here(); state.in_loop = true; }
#line 3904 "gen/tparser.cpp"
    break;

  case 300: /* $@22: %empty  */
#line 911 "build/parser.y"
                         { do_loop_start((yyvsp[0].expression),true); }
#line 3910 "gen/tparser.cpp"
    break;

  case 301: /* while_stmt: WHILE $@21 condition $@22 controlled_statement  */
#line 912 "build/parser.y"
                         { do_loop_end(true); state.in_loop = false;}
#line 3916 "gen/tparser.cpp"
    break;

  case 302: /* $@23: %empty  */
#line 917 "build/parser.y"
                               { label_here(); push_label_stack(); state.in_loop = true;}
#line 3922 "gen/tparser.cpp"
    break;

  case 303: /* do_stmt: DO $@23 controlled_statement WHILE condition  */
#line 919 "build/parser.y"
                               { do_do_end((yyvsp[0].expression)); state.in_loop = false; }
#line 3928 "gen/tparser.cpp"
    break;

  case 305: /* for_init: expr ';'  */
#line 923 "build/parser.y"
               { code().compile((yyvsp[-1].expression),DROP_VALUE); }
#line 3934 "gen/tparser.cpp"
    break;

  case 307: /* $@24: %empty  */
#line 928 "build/parser.y"
           { state.init_block(PLAIN_BLOCK); }
#line 3940 "gen/tparser.cpp"
    break;

  case 308: /* $@25: %empty  */
#line 929 "build/parser.y"
                               { label_here();	state.in_loop = true; }
#line 3946 "gen/tparser.cpp"
    break;

  case 309: /* $@26: %empty  */
#line 931 "build/parser.y"
                               { do_loop_start((yyvsp[-3].expression),true); }
#line 3952 "gen/tparser.cpp"
    break;

  case 310: /* for_stmt: FOR '(' $@24 for_init $@25 poss_expr ';' poss_expr ')' $@26 controlled_statement  */
#line 932 "build/parser.y"
                               { do_for_end((yyvsp[-3].expression));    state.in_loop = false;
								 state.finalize_block();
							   }
#line 3960 "gen/tparser.cpp"
    break;

  case 311: /* $@27: %empty  */
#line 938 "build/parser.y"
                      { do_switch((yyvsp[-1].expression)); }
#line 3966 "gen/tparser.cpp"
    break;

  case 313: /* return_stmt: RETURN poss_expr ';'  */
#line 943 "build/parser.y"
  { if (!do_return ((yyvsp[-1].expression))) { check_error(); YYABORT; }  }
#line 3972 "gen/tparser.cpp"
    break;

  case 314: /* case_label: CASE expr ':'  */
#line 948 "build/parser.y"
  { do_case ((yyvsp[-1].expression));   }
#line 3978 "gen/tparser.cpp"
    break;

  case 315: /* case_label: DEFAULT ':'  */
#line 950 "build/parser.y"
  { do_case(NULL);  }
#line 3984 "gen/tparser.cpp"
    break;

  case 316: /* break_stmt: BREAK ';'  */
#line 954 "build/parser.y"
 { if (!do_break_continue(BREAK)) { check_error(); YYABORT; } }
#line 3990 "gen/tparser.cpp"
    break;

  case 317: /* continue_stmt: CONTINUE ';'  */
#line 958 "build/parser.y"
 { if (!do_break_continue(CONTINUE)) { check_error(); YYABORT; } }
#line 3996 "gen/tparser.cpp"
    break;

  case 318: /* try_catch_stmt: try_block catch_block_list  */
#line 965 "build/parser.y"
  { do_end_try_catch_block(true); }
#line 4002 "gen/tparser.cpp"
    break;

  case 319: /* $@28: %empty  */
#line 970 "build/parser.y"
  { state.init_block(PLAIN_BLOCK); IEF_set(); 
	do_start_try_block();  }
#line 4009 "gen/tparser.cpp"
    break;

  case 321: /* except_block: '{' statement_list '}'  */
#line 978 "build/parser.y"
   { state.finalize_block(); IEF_reset();
     do_end_try_catch_block(false);   }
#line 4016 "gen/tparser.cpp"
    break;

  case 322: /* $@29: %empty  */
#line 984 "build/parser.y"
  { state.init_block(PLAIN_BLOCK); IEF_set(); 
    do_start_catch_block(); if (check_error()) YYABORT; }
#line 4023 "gen/tparser.cpp"
    break;

  case 326: /* throw_stmt: THROW poss_expr ';'  */
#line 996 "build/parser.y"
  { do_throw((yyvsp[-1].expression)); }
#line 4029 "gen/tparser.cpp"
    break;

  case 327: /* typename_function: TYPENAME_FUNCTION  */
#line 1002 "build/parser.y"
                    { (yyval.ctype) = AsTType((yyvsp[0].entry)->type); }
#line 4035 "gen/tparser.cpp"
    break;

  case 328: /* typename_function: template_class  */
#line 1003 "build/parser.y"
                    { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4041 "gen/tparser.cpp"
    break;

  case 329: /* typename_class: TYPENAME  */
#line 1008 "build/parser.y"
                 { last_type_entry = (yyvsp[0].entry); (yyval.ctype) = AsTType((yyvsp[0].entry)->type); }
#line 4047 "gen/tparser.cpp"
    break;

  case 330: /* typename_class: template_class  */
#line 1009 "build/parser.y"
                 { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4053 "gen/tparser.cpp"
    break;

  case 331: /* typename_class: scope typename_class end_scope  */
#line 1010 "build/parser.y"
                                 { (yyval.ctype) = (yyvsp[-1].ctype); }
#line 4059 "gen/tparser.cpp"
    break;

  case 332: /* typename_expr: TYPENAME_FUNCTION  */
#line 1015 "build/parser.y"
                    { (yyval.ctype) = AsTType((yyvsp[0].entry)->type); }
#line 4065 "gen/tparser.cpp"
    break;

  case 333: /* typename_expr: template_expr  */
#line 1016 "build/parser.y"
                   { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4071 "gen/tparser.cpp"
    break;

  case 334: /* typename_expr: scope typename_expr end_scope  */
#line 1017 "build/parser.y"
                                { (yyval.ctype) = (yyvsp[-1].ctype); }
#line 4077 "gen/tparser.cpp"
    break;

  case 335: /* template_class: TEMPLATE_NAME template_type_list  */
#line 1022 "build/parser.y"
   { (yyval.ctype) = AsTType(Template::get_template_type((yyvsp[-1].entry),(yyvsp[0].typelist))); }
#line 4083 "gen/tparser.cpp"
    break;

  case 336: /* template_expr: TEMPLATE_NAME_EXPR template_type_list  */
#line 1027 "build/parser.y"
   { (yyval.ctype) = AsTType(Template::get_template_type((yyvsp[-1].entry),(yyvsp[0].typelist))); }
#line 4089 "gen/tparser.cpp"
    break;

  case 337: /* template_header: TEMPLATE template_type_list  */
#line 1033 "build/parser.y"
 { Template::do_template_header((yyvsp[0].typelist)); }
#line 4095 "gen/tparser.cpp"
    break;

  case 338: /* template_function_declaration: template_header function_front  */
#line 1039 "build/parser.y"
  { Template::do_function_template(); 
  	if (yychar != YYEMPTY) yyclearin;
  }
#line 4103 "gen/tparser.cpp"
    break;

  case 339: /* template_class_declaration: template_class_header template_class_name  */
#line 1046 "build/parser.y"
   {
    dcl_reset();    
    Template::do_class_template((yyvsp[-1].val),(yyvsp[0].str),yychar,NULL);
	if (yychar != YYEMPTY) yyclearin;
   }
#line 4113 "gen/tparser.cpp"
    break;

  case 340: /* template_class_declaration: template_class_header template_class_name template_type_list  */
#line 1052 "build/parser.y"
   {
    dcl_reset();        
    Template::do_class_template((yyvsp[-2].val),(yyvsp[-1].str),yychar,(yyvsp[0].typelist));
	if (yychar != YYEMPTY) yyclearin;
   }
#line 4123 "gen/tparser.cpp"
    break;

  case 343: /* template_class_header: template_header struct_or_class_x  */
#line 1065 "build/parser.y"
   { dcl_set(); (yyval.val) = (yyvsp[0].val); }
#line 4129 "gen/tparser.cpp"
    break;

  case 344: /* template_class_name: TOKEN  */
#line 1068 "build/parser.y"
                                     { (yyval.str) = (yyvsp[0].str);                     }
#line 4135 "gen/tparser.cpp"
    break;

  case 345: /* template_class_name: TEMPLATE_NAME  */
#line 1069 "build/parser.y"
                                     { (yyval.str) = (yyvsp[0].entry)->name.c_str();       }
#line 4141 "gen/tparser.cpp"
    break;

  case 346: /* begin_templ_list: LESS_THAN  */
#line 1073 "build/parser.y"
                             { dcl_set(true); state.begin_templ_list(); }
#line 4147 "gen/tparser.cpp"
    break;

  case 347: /* end_templ_list: GREATER  */
#line 1075 "build/parser.y"
                             { dcl_reset();   state.end_templ_list();   }
#line 4153 "gen/tparser.cpp"
    break;

  case 348: /* template_type_list: begin_templ_list end_templ_list  */
#line 1079 "build/parser.y"
                                                  { (yyval.typelist) = new TypeList; }
#line 4159 "gen/tparser.cpp"
    break;

  case 349: /* template_type_list: begin_templ_list templ_item_list end_templ_list  */
#line 1080 "build/parser.y"
                                                  { (yyval.typelist) = (yyvsp[-1].typelist); }
#line 4165 "gen/tparser.cpp"
    break;

  case 350: /* templ_item_list: templ_item  */
#line 1085 "build/parser.y"
                                   { (yyval.typelist) = new TypeList; (yyval.typelist)->push_back(AsType((yyvsp[0].ctype))); }
#line 4171 "gen/tparser.cpp"
    break;

  case 351: /* templ_item_list: templ_item_list ',' templ_item  */
#line 1086 "build/parser.y"
                                   { (yyval.typelist) = (yyvsp[-2].typelist); (yyval.typelist)->push_back(AsType((yyvsp[0].ctype)));   }
#line 4177 "gen/tparser.cpp"
    break;

  case 352: /* class_item: CLASS TOKEN  */
#line 1090 "build/parser.y"
              { (yyval.str) = (yyvsp[0].str); }
#line 4183 "gen/tparser.cpp"
    break;

  case 353: /* class_item: CLASS TYPENAME  */
#line 1091 "build/parser.y"
                 { (yyval.str) = (yyvsp[0].entry)->name.c_str(); }
#line 4189 "gen/tparser.cpp"
    break;

  case 354: /* class_parm: class_item  */
#line 1095 "build/parser.y"
               {
   string c = (yyvsp[0].str);
   (yyval.ctype) = AsTType(Template::dummy(t_null,c));
  }
#line 4198 "gen/tparser.cpp"
    break;

  case 355: /* templ_item: type_expr  */
#line 1103 "build/parser.y"
                   {
                     (yyval.ctype) = AsTType(Template::dummy(AsType((yyvsp[0].ctype)),state.token_stack.pop()));
	                 dcl_reset();  tpop();
	               }
#line 4207 "gen/tparser.cpp"
    break;

  case 356: /* templ_item: CONSTANT  */
#line 1107 "build/parser.y"
                   { (yyval.ctype) = AsTType(Template::dummy((yyvsp[0].entry))); }
#line 4213 "gen/tparser.cpp"
    break;

  case 357: /* templ_item: class_parm  */
#line 1108 "build/parser.y"
                   { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4219 "gen/tparser.cpp"
    break;


#line 4223 "gen/tparser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1112 "build/parser.y"
  
