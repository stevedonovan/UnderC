/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GEN_TPARSER_H_INCLUDED
# define YY_YY_GEN_TPARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN = 258,                   /* TOKEN  */
    IDEN = 259,                    /* IDEN  */
    CONSTANT = 260,                /* CONSTANT  */
    TYPENAME = 261,                /* TYPENAME  */
    TYPENAME_FUNCTION = 262,       /* TYPENAME_FUNCTION  */
    TEMPLATE_NAME = 263,           /* TEMPLATE_NAME  */
    TEMPLATE_NAME_EXPR = 264,      /* TEMPLATE_NAME_EXPR  */
    THIS_CLASSNAME = 265,          /* THIS_CLASSNAME  */
    FLOAT = 266,                   /* FLOAT  */
    DOUBLE = 267,                  /* DOUBLE  */
    UNSIGNED = 268,                /* UNSIGNED  */
    INT = 269,                     /* INT  */
    SHORT = 270,                   /* SHORT  */
    LONG = 271,                    /* LONG  */
    CHAR = 272,                    /* CHAR  */
    VOID = 273,                    /* VOID  */
    BOOL = 274,                    /* BOOL  */
    TYPEDEF = 275,                 /* TYPEDEF  */
    CLASS = 276,                   /* CLASS  */
    STRUCT = 277,                  /* STRUCT  */
    ENUM = 278,                    /* ENUM  */
    OPERATOR = 279,                /* OPERATOR  */
    GOTO = 280,                    /* GOTO  */
    UNION = 281,                   /* UNION  */
    STATIC_CAST = 282,             /* STATIC_CAST  */
    CONST_CAST = 283,              /* CONST_CAST  */
    DYNAMIC_CAST = 284,            /* DYNAMIC_CAST  */
    REINTERPRET_CAST = 285,        /* REINTERPRET_CAST  */
    STRUCT_X = 286,                /* STRUCT_X  */
    CLASS_X = 287,                 /* CLASS_X  */
    STRUCT_Y = 288,                /* STRUCT_Y  */
    CLASS_Y = 289,                 /* CLASS_Y  */
    UNION_Y = 290,                 /* UNION_Y  */
    IF = 291,                      /* IF  */
    ELSE = 292,                    /* ELSE  */
    WHILE = 293,                   /* WHILE  */
    DO = 294,                      /* DO  */
    FOR = 295,                     /* FOR  */
    SWITCH = 296,                  /* SWITCH  */
    CASE = 297,                    /* CASE  */
    RETURN = 298,                  /* RETURN  */
    CONTINUE = 299,                /* CONTINUE  */
    BREAK = 300,                   /* BREAK  */
    DEFAULT = 301,                 /* DEFAULT  */
    NAMESPACE = 302,               /* NAMESPACE  */
    USING = 303,                   /* USING  */
    TRY = 304,                     /* TRY  */
    CATCH = 305,                   /* CATCH  */
    THROW = 306,                   /* THROW  */
    TEMPLATE = 307,                /* TEMPLATE  */
    EXTERN = 308,                  /* EXTERN  */
    THREEDOT = 309,                /* THREEDOT  */
    TYPEOF = 310,                  /* TYPEOF  */
    EXPLICIT = 311,                /* EXPLICIT  */
    FRIEND = 312,                  /* FRIEND  */
    LAMBDA = 313,                  /* LAMBDA  */
    FAKE_INIT_LIST = 314,          /* FAKE_INIT_LIST  */
    CONST = 315,                   /* CONST  */
    STATIC = 316,                  /* STATIC  */
    STDCALL = 317,                 /* STDCALL  */
    API = 318,                     /* API  */
    VIRTUAL = 319,                 /* VIRTUAL  */
    PRIVATE = 320,                 /* PRIVATE  */
    PROTECTED = 321,               /* PROTECTED  */
    PUBLIC = 322,                  /* PUBLIC  */
    COMMA = 323,                   /* COMMA  */
    ASSIGN = 324,                  /* ASSIGN  */
    MUL_A = 325,                   /* MUL_A  */
    DIV_A = 326,                   /* DIV_A  */
    MOD_A = 327,                   /* MOD_A  */
    ADD_A = 328,                   /* ADD_A  */
    MINUS_A = 329,                 /* MINUS_A  */
    SHL_A = 330,                   /* SHL_A  */
    SHR_A = 331,                   /* SHR_A  */
    BAND_A = 332,                  /* BAND_A  */
    BOR_A = 333,                   /* BOR_A  */
    XOR_A = 334,                   /* XOR_A  */
    ARITH_IF = 335,                /* ARITH_IF  */
    LOG_OR = 336,                  /* LOG_OR  */
    LOG_AND = 337,                 /* LOG_AND  */
    BIN_OR = 338,                  /* BIN_OR  */
    BIN_XOR = 339,                 /* BIN_XOR  */
    BIN_AND = 340,                 /* BIN_AND  */
    EQUAL = 341,                   /* EQUAL  */
    NOT_EQUAL = 342,               /* NOT_EQUAL  */
    LESS_THAN = 343,               /* LESS_THAN  */
    LEQ = 344,                     /* LEQ  */
    GREATER = 345,                 /* GREATER  */
    GEQ = 346,                     /* GEQ  */
    LSHIFT = 347,                  /* LSHIFT  */
    RSHIFT = 348,                  /* RSHIFT  */
    PLUS = 349,                    /* PLUS  */
    MINUS = 350,                   /* MINUS  */
    STAR = 351,                    /* STAR  */
    DIVIDE = 352,                  /* DIVIDE  */
    MODULO = 353,                  /* MODULO  */
    MEMBER_ARROW = 354,            /* MEMBER_ARROW  */
    MEMBER_DOT = 355,              /* MEMBER_DOT  */
    NEW = 356,                     /* NEW  */
    DELETE = 357,                  /* DELETE  */
    TYPECAST = 358,                /* TYPECAST  */
    DEREF = 359,                   /* DEREF  */
    ADDR = 360,                    /* ADDR  */
    UPLUS = 361,                   /* UPLUS  */
    UMINUS = 362,                  /* UMINUS  */
    LOG_NOT = 363,                 /* LOG_NOT  */
    BIN_NOT = 364,                 /* BIN_NOT  */
    INCR = 365,                    /* INCR  */
    DECR = 366,                    /* DECR  */
    SIZEOF = 367,                  /* SIZEOF  */
    TYPE_CONSTRUCT = 368,          /* TYPE_CONSTRUCT  */
    FUN_CALL = 369,                /* FUN_CALL  */
    ARRAY = 370,                   /* ARRAY  */
    ARROW = 371,                   /* ARROW  */
    DOT = 372,                     /* DOT  */
    BINARY_SCOPE = 373,            /* BINARY_SCOPE  */
    UNARY_SCOPE = 374              /* UNARY_SCOPE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
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
union YYSTYPE
{
#line 99 "build/parser.y"

  int    val; 
  unsigned int ctype;
  const char*  str;
  Entry* entry;
  Expr*  expression;
  ExprList *elist;
  Class *classptr;
  TypeList *typelist;

#line 316 "gen/tparser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_GEN_TPARSER_H_INCLUDED  */
