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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    STATIC_CAST = 275,
    CONST_CAST = 276,
    DYNAMIC_CAST = 277,
    REINTERPRET_CAST = 278,
    STRUCT_X = 279,
    CLASS_X = 280,
    STRUCT_Y = 281,
    CLASS_Y = 282,
    UNION_Y = 283,
    IF = 284,
    ELSE = 285,
    WHILE = 286,
    DO = 287,
    FOR = 288,
    SWITCH = 289,
    CASE = 290,
    RETURN = 291,
    CONTINUE = 292,
    BREAK = 293,
    OPERATOR = 294,
    DEFAULT = 295,
    TYPEDEF = 296,
    ENUM = 297,
    GOTO = 298,
    NAMESPACE = 299,
    USING = 300,
    TRY = 301,
    CATCH = 302,
    THROW = 303,
    TEMPLATE = 304,
    EXTERN = 305,
    THREEDOT = 306,
    TYPEOF = 307,
    EXPLICIT = 308,
    FRIEND = 309,
    LAMBDA = 310,
    FAKE_INIT_LIST = 311,
    CONST = 312,
    STATIC = 313,
    STDCALL = 314,
    API = 315,
    VIRTUAL = 316,
    PRIVATE = 317,
    PROTECTED = 318,
    PUBLIC = 319,
    CLASS = 320,
    STRUCT = 321,
    UNION = 322,
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
/* Tokens.  */
#define TOKEN 258
#define IDEN 259
#define CONSTANT 260
#define TYPENAME 261
#define TYPENAME_FUNCTION 262
#define TEMPLATE_NAME 263
#define TEMPLATE_NAME_EXPR 264
#define THIS_CLASSNAME 265
#define FLOAT 266
#define DOUBLE 267
#define UNSIGNED 268
#define INT 269
#define SHORT 270
#define LONG 271
#define CHAR 272
#define VOID 273
#define BOOL 274
#define STATIC_CAST 275
#define CONST_CAST 276
#define DYNAMIC_CAST 277
#define REINTERPRET_CAST 278
#define STRUCT_X 279
#define CLASS_X 280
#define STRUCT_Y 281
#define CLASS_Y 282
#define UNION_Y 283
#define IF 284
#define ELSE 285
#define WHILE 286
#define DO 287
#define FOR 288
#define SWITCH 289
#define CASE 290
#define RETURN 291
#define CONTINUE 292
#define BREAK 293
#define OPERATOR 294
#define DEFAULT 295
#define TYPEDEF 296
#define ENUM 297
#define GOTO 298
#define NAMESPACE 299
#define USING 300
#define TRY 301
#define CATCH 302
#define THROW 303
#define TEMPLATE 304
#define EXTERN 305
#define THREEDOT 306
#define TYPEOF 307
#define EXPLICIT 308
#define FRIEND 309
#define LAMBDA 310
#define FAKE_INIT_LIST 311
#define CONST 312
#define STATIC 313
#define STDCALL 314
#define API 315
#define VIRTUAL 316
#define PRIVATE 317
#define PROTECTED 318
#define PUBLIC 319
#define CLASS 320
#define STRUCT 321
#define UNION 322
#define COMMA 323
#define ASSIGN 324
#define MUL_A 325
#define DIV_A 326
#define MOD_A 327
#define ADD_A 328
#define MINUS_A 329
#define SHL_A 330
#define SHR_A 331
#define BAND_A 332
#define BOR_A 333
#define XOR_A 334
#define ARITH_IF 335
#define LOG_OR 336
#define LOG_AND 337
#define BIN_OR 338
#define BIN_XOR 339
#define BIN_AND 340
#define EQUAL 341
#define NOT_EQUAL 342
#define LESS_THAN 343
#define LEQ 344
#define GREATER 345
#define GEQ 346
#define LSHIFT 347
#define RSHIFT 348
#define PLUS 349
#define MINUS 350
#define STAR 351
#define DIVIDE 352
#define MODULO 353
#define MEMBER_ARROW 354
#define MEMBER_DOT 355
#define NEW 356
#define DELETE 357
#define TYPECAST 358
#define DEREF 359
#define ADDR 360
#define UPLUS 361
#define UMINUS 362
#define LOG_NOT 363
#define BIN_NOT 364
#define INCR 365
#define DECR 366
#define SIZEOF 367
#define TYPE_CONSTRUCT 368
#define FUN_CALL 369
#define ARRAY 370
#define ARROW 371
#define DOT 372
#define BINARY_SCOPE 373
#define UNARY_SCOPE 374

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 98 "parser.y" /* yacc.c:1909  */

  int       val;
  long      ctype;
  char*     str;
  Entry*    entry;
  Expr*     expression;
  ExprList *elist;
  Class    *classptr;
  TypeList *typelist;

#line 303 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
