/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN = 258,
    IDEN = 259,
    CONSTANT = 260,
    TYPENAME = 261,
    TYPENAME_FUNCTION = 262,
    TEMPLATE_NAME = 263,
    TEMPLATE_NAME_EXPR = 264,
    THIS_CLASSNAME = 265,
    FLOAT = 266,
    DOUBLE = 267,
    UNSIGNED = 268,
    INT = 269,
    SHORT = 270,
    LONG = 271,
    CHAR = 272,
    VOID = 273,
    BOOL = 274,
    TYPEDEF = 275,
    CLASS = 276,
    STRUCT = 277,
    ENUM = 278,
    OPERATOR = 279,
    GOTO = 280,
    UNION = 281,
    STATIC_CAST = 282,
    CONST_CAST = 283,
    DYNAMIC_CAST = 284,
    REINTERPRET_CAST = 285,
    STRUCT_X = 286,
    CLASS_X = 287,
    STRUCT_Y = 288,
    CLASS_Y = 289,
    UNION_Y = 290,
    IF = 291,
    ELSE = 292,
    WHILE = 293,
    DO = 294,
    FOR = 295,
    SWITCH = 296,
    CASE = 297,
    RETURN = 298,
    CONTINUE = 299,
    BREAK = 300,
    DEFAULT = 301,
    NAMESPACE = 302,
    USING = 303,
    TRY = 304,
    CATCH = 305,
    THROW = 306,
    TEMPLATE = 307,
    EXTERN = 308,
    THREEDOT = 309,
    TYPEOF = 310,
    EXPLICIT = 311,
    FRIEND = 312,
    LAMBDA = 313,
    FAKE_INIT_LIST = 314,
    CONST = 315,
    STATIC = 316,
    STDCALL = 317,
    API = 318,
    VIRTUAL = 319,
    PRIVATE = 320,
    PROTECTED = 321,
    PUBLIC = 322,
    COMMA = 323,
    ASSIGN = 324,
    MUL_A = 325,
    DIV_A = 326,
    MOD_A = 327,
    ADD_A = 328,
    MINUS_A = 329,
    SHL_A = 330,
    SHR_A = 331,
    BAND_A = 332,
    BOR_A = 333,
    XOR_A = 334,
    ARITH_IF = 335,
    LOG_OR = 336,
    LOG_AND = 337,
    BIN_OR = 338,
    BIN_XOR = 339,
    BIN_AND = 340,
    EQUAL = 341,
    NOT_EQUAL = 342,
    LESS_THAN = 343,
    LEQ = 344,
    GREATER = 345,
    GEQ = 346,
    LSHIFT = 347,
    RSHIFT = 348,
    PLUS = 349,
    MINUS = 350,
    STAR = 351,
    DIVIDE = 352,
    MODULO = 353,
    MEMBER_ARROW = 354,
    MEMBER_DOT = 355,
    NEW = 356,
    DELETE = 357,
    TYPECAST = 358,
    DEREF = 359,
    ADDR = 360,
    UPLUS = 361,
    UMINUS = 362,
    LOG_NOT = 363,
    BIN_NOT = 364,
    INCR = 365,
    DECR = 366,
    SIZEOF = 367,
    TYPE_CONSTRUCT = 368,
    FUN_CALL = 369,
    ARRAY = 370,
    ARROW = 371,
    DOT = 372,
    BINARY_SCOPE = 373,
    UNARY_SCOPE = 374
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 107 "parser.y" /* yacc.c:1909  */

  int       val; 
  long      ctype;
  char*     str;
  Entry*    entry;
  Expr*     expression;
  ExprList *elist;
  Class    *classptr;
  TypeList *typelist;

#line 185 "parser.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
