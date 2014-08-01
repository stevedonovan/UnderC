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
#define TYPEDEF 275
#define CLASS 276
#define STRUCT 277
#define ENUM 278
#define OPERATOR 279
#define GOTO 280
#define UNION 281
#define STATIC_CAST 282
#define CONST_CAST 283
#define DYNAMIC_CAST 284
#define REINTERPRET_CAST 285
#define STRUCT_X 286
#define CLASS_X 287
#define STRUCT_Y 288
#define CLASS_Y 289
#define UNION_Y 290
#define IF 291
#define ELSE 292
#define WHILE 293
#define DO 294
#define FOR 295
#define SWITCH 296
#define CASE 297
#define RETURN 298
#define CONTINUE 299
#define BREAK 300
#define DEFAULT 301
#define NAMESPACE 302
#define USING 303
#define TRY 304
#define CATCH 305
#define THROW 306
#define TEMPLATE 307
#define EXTERN 308
#define THREEDOT 309
#define TYPEOF 310
#define EXPLICIT 311
#define FRIEND 312
#define LAMBDA 313
#define FAKE_INIT_LIST 314
#define CONST 315
#define STATIC 316
#define STDCALL 317
#define API 318
#define VIRTUAL 319
#define PRIVATE 320
#define PROTECTED 321
#define PUBLIC 322
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
#line 107 "parser.y" /* yacc.c:1909  */

  int    val; 
  long   ctype;
  char*  str;
  Entry* entry;
  Expr*  expression;
  ExprList *elist;
  Class *classptr;
  TypeList *typelist;

#line 303 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
