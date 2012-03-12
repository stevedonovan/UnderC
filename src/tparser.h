
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     XOR_A = 324,
     BOR_A = 325,
     BAND_A = 326,
     SHR_A = 327,
     SHL_A = 328,
     MINUS_A = 329,
     ADD_A = 330,
     MOD_A = 331,
     DIV_A = 332,
     MUL_A = 333,
     ASSIGN = 334,
     ARITH_IF = 335,
     LOG_OR = 336,
     LOG_AND = 337,
     BIN_OR = 338,
     BIN_XOR = 339,
     BIN_AND = 340,
     NOT_EQUAL = 341,
     EQUAL = 342,
     GEQ = 343,
     GREATER = 344,
     LEQ = 345,
     LESS_THAN = 346,
     RSHIFT = 347,
     LSHIFT = 348,
     MINUS = 349,
     PLUS = 350,
     MODULO = 351,
     DIVIDE = 352,
     STAR = 353,
     MEMBER_DOT = 354,
     MEMBER_ARROW = 355,
     SIZEOF = 356,
     DECR = 357,
     INCR = 358,
     BIN_NOT = 359,
     LOG_NOT = 360,
     UMINUS = 361,
     UPLUS = 362,
     ADDR = 363,
     DEREF = 364,
     TYPECAST = 365,
     DELETE = 366,
     NEW = 367,
     DOT = 368,
     ARROW = 369,
     ARRAY = 370,
     FUN_CALL = 371,
     TYPE_CONSTRUCT = 372,
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
#define XOR_A 324
#define BOR_A 325
#define BAND_A 326
#define SHR_A 327
#define SHL_A 328
#define MINUS_A 329
#define ADD_A 330
#define MOD_A 331
#define DIV_A 332
#define MUL_A 333
#define ASSIGN 334
#define ARITH_IF 335
#define LOG_OR 336
#define LOG_AND 337
#define BIN_OR 338
#define BIN_XOR 339
#define BIN_AND 340
#define NOT_EQUAL 341
#define EQUAL 342
#define GEQ 343
#define GREATER 344
#define LEQ 345
#define LESS_THAN 346
#define RSHIFT 347
#define LSHIFT 348
#define MINUS 349
#define PLUS 350
#define MODULO 351
#define DIVIDE 352
#define STAR 353
#define MEMBER_DOT 354
#define MEMBER_ARROW 355
#define SIZEOF 356
#define DECR 357
#define INCR 358
#define BIN_NOT 359
#define LOG_NOT 360
#define UMINUS 361
#define UPLUS 362
#define ADDR 363
#define DEREF 364
#define TYPECAST 365
#define DELETE 366
#define NEW 367
#define DOT 368
#define ARROW 369
#define ARRAY 370
#define FUN_CALL 371
#define TYPE_CONSTRUCT 372
#define BINARY_SCOPE 373
#define UNARY_SCOPE 374




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 107 "parser.y"

  int    val; 
  long   ctype;
  char*  str;
  Entry* entry;
  Expr*  expression;
  ExprList *elist;
  Class *classptr;
  TypeList *typelist;



/* Line 1676 of yacc.c  */
#line 303 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


