/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

/* *SJD* essential prototypes for C++ compilation */
int yylex();
int yyerror(const char *s);
#include <cstdlib>
#include <cstring>
#define xmalloc malloc

#define MSDOS
#include "common.h"
using namespace Parser;
using namespace Expressions;

#define YYERROR_VERBOSE 1
#define YYDEBUG 1

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

inline void enter_arglist() {
  dcl_set(false);
}

void leave_arglist() {
  dcl_reset();
}

string tag_name; /* A fiddle */
bool IEF=false;
/*BoolStack ief_stack;*/

void IEF_set()   {
  /*ief_stack.push(IEF);*/
  IEF=true;
}

void IEF_reset() {
  IEF=false;
  /*ief_stack.pop();*/
}

void ttpush(TType t) {
  tpush(AsType(t));
}

void raise_error(string msg)
{
  int yyerror(const char *);

  if (state.err != "") { msg = state.err; state.err = ""; }
  state.reset();
  als.clear();
  als.push(false);
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


#line 164 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 98 "parser.y" /* yacc.c:355  */

  int       val;
  long      ctype;
  char*     str;
  Entry*    entry;
  Expr*     expression;
  ExprList *elist;
  Class    *classptr;
  TypeList *typelist;

#line 453 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 468 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  223
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2907

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  129
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  166
/* YYNRULES -- Number of rules.  */
#define YYNRULES  367
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  584

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   374

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
static const yytype_uint16 yyrline[] =
{
       0,   156,   156,   158,   159,   160,   162,   162,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   188,
     189,   190,   192,   193,   195,   196,   197,   199,   200,   201,
     203,   204,   205,   206,   208,   215,   215,   218,   219,   222,
     225,   226,   228,   228,   232,   234,   237,   236,   240,   241,
     240,   245,   245,   249,   250,   251,   253,   254,   256,   253,
     261,   261,   263,   266,   269,   272,   281,   282,   288,   294,
     297,   299,   306,   314,   315,   316,   327,   328,   329,   331,
     332,   334,   336,   339,   340,   341,   342,   344,   349,   350,
     350,   354,   355,   356,   358,   365,   371,   373,   375,   376,
     378,   379,   380,   381,   383,   384,   385,   386,   388,   390,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   410,   411,   412,   417,   419,   421,   421,   426,   430,
     431,   437,   443,   444,   445,   446,   447,   448,   449,   452,
     453,   454,   456,   459,   461,   463,   465,   466,   467,   468,
     470,   477,   486,   487,   488,   490,   491,   497,   499,   500,
     501,   502,   502,   505,   509,   511,   512,   514,   515,   521,
     522,   523,   525,   526,   528,   528,   528,   530,   531,   532,
     534,   535,   538,   539,   541,   542,   543,   548,   550,   550,
     555,   554,   567,   570,   572,   572,   573,   580,   581,   580,
     587,   588,   590,   591,   592,   594,   599,   600,   601,   605,
     606,   605,   613,   614,   616,   625,   626,   627,   629,   629,
     629,   631,   632,   635,   637,   639,   641,   642,   643,   645,
     646,   648,   648,   648,   648,   650,   652,   653,   655,   656,
     657,   658,   659,   660,   661,   662,   664,   665,   666,   667,
     668,   669,   670,   671,   673,   674,   675,   676,   678,   679,
     682,   683,   684,   685,   686,   687,   688,   689,   690,   691,
     695,   696,   697,   697,   699,   700,   702,   703,   704,   705,
     706,   708,   709,   709,   711,   711,   713,   713,   715,   717,
     719,   720,   721,   723,   724,   725,   727,   729,   730,   731,
     734,   734,   734,   734,   734,   735,   735,   735,   735,   735,
     737,   738,   743,   744,   746,   748,   749,   750,   754,   756,
     756,   760,   765,   764,   769,   770,   772,   775,   776,   779,
     780,   781,   784,   785,   786,   788,   791,   795,   797,   802,
     808,   815,   815,   817,   819,   820,   823,   825,   827,   828,
     831,   832,   834,   835,   837,   843,   847,   848
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN", "IDEN", "CONSTANT", "TYPENAME",
  "TYPENAME_FUNCTION", "TEMPLATE_NAME", "TEMPLATE_NAME_EXPR",
  "THIS_CLASSNAME", "FLOAT", "DOUBLE", "UNSIGNED", "INT", "SHORT", "LONG",
  "CHAR", "VOID", "BOOL", "STATIC_CAST", "CONST_CAST", "DYNAMIC_CAST",
  "REINTERPRET_CAST", "STRUCT_X", "CLASS_X", "STRUCT_Y", "CLASS_Y",
  "UNION_Y", "IF", "ELSE", "WHILE", "DO", "FOR", "SWITCH", "CASE",
  "RETURN", "CONTINUE", "BREAK", "OPERATOR", "DEFAULT", "TYPEDEF", "ENUM",
  "GOTO", "NAMESPACE", "USING", "TRY", "CATCH", "THROW", "TEMPLATE",
  "EXTERN", "THREEDOT", "TYPEOF", "EXPLICIT", "FRIEND", "LAMBDA",
  "FAKE_INIT_LIST", "CONST", "STATIC", "STDCALL", "API", "VIRTUAL",
  "PRIVATE", "PROTECTED", "PUBLIC", "CLASS", "STRUCT", "UNION", "COMMA",
  "ASSIGN", "MUL_A", "DIV_A", "MOD_A", "ADD_A", "MINUS_A", "SHL_A",
  "SHR_A", "BAND_A", "BOR_A", "XOR_A", "ARITH_IF", "LOG_OR", "LOG_AND",
  "BIN_OR", "BIN_XOR", "BIN_AND", "EQUAL", "NOT_EQUAL", "LESS_THAN", "LEQ",
  "GREATER", "GEQ", "LSHIFT", "RSHIFT", "PLUS", "MINUS", "STAR", "DIVIDE",
  "MODULO", "MEMBER_ARROW", "MEMBER_DOT", "NEW", "DELETE", "TYPECAST",
  "DEREF", "ADDR", "UPLUS", "UMINUS", "LOG_NOT", "BIN_NOT", "INCR", "DECR",
  "SIZEOF", "TYPE_CONSTRUCT", "FUN_CALL", "ARRAY", "ARROW", "DOT",
  "BINARY_SCOPE", "UNARY_SCOPE", "'{'", "'}'", "';'", "':'", "'('", "')'",
  "'['", "']'", "','", "$accept", "program", "statement_list", "block",
  "$@1", "statement", "label_stmt", "expr_stmt", "select_stmt",
  "iter_stmt", "jump_stmt", "declaration", "typedef_stmt", "$@2",
  "declaration_stmt", "condition", "poss_expr", "controlled_statement",
  "$@3", "if_front", "if_stmt", "if_else_stmt", "$@4", "while_stmt", "$@5",
  "$@6", "do_stmt", "$@7", "for_init", "for_stmt", "$@8", "$@9", "$@10",
  "switch_stmt", "$@11", "return_stmt", "break_stmt", "continue_stmt",
  "this_classname", "construct_destruct", "conversion_operator",
  "function_front", "explicit_mod", "ctor_dtor_dcl",
  "function_declaration", "extern_c_declaration", "any_declaration",
  "extern_c", "extern_qualifier", "function_definition", "ctor_dtor",
  "poss_class_init_list", "$@12", "class_init_list", "class_init_item",
  "type_expr", "type_id", "poss_const", "mod_type_name", "modifiers",
  "open_parens", "close_parens", "type_name", "integer", "pointer_expr",
  "array_expr", "$@13", "tname_expr", "tname_exp2", "token", "begin_list",
  "end_list", "arg_list", "type_list", "type_expr_init", "init_tname_expr",
  "tname_expr_list", "poss_int_const", "init_assign",
  "poss_initialization", "$@14", "brace_expr", "brace_item", "brace_list",
  "access_modifier", "poss_access_modifier", "class_key", "class_key_ex",
  "poss_derived", "token_or_typename", "class_name", "class_id", "$@15",
  "class_declaration", "$@16", "access_specifier", "friend_declaration",
  "$@17", "enum_stmt", "$@18", "$@19", "poss_enum_list", "poss_tag",
  "enum_item", "enum_list", "namespace_declaration", "$@20", "$@21",
  "poss_class_name", "using_directive", "using_declaration", "goto_stmt",
  "$@22", "$@23", "goto_label", "scope", "global_scope", "end_scope",
  "scoped_name", "poss_size", "typecast_type", "type_bracket",
  "conditional_expr", "log_or_expr", "cast_expr", "unary_expr", "$@24",
  "post_expr", "$@25", "$@26", "$@27", "primary_expr", "_expr", "expr",
  "assign_expr", "assign_op", "poss_array", "function_arg_list",
  "init_list", "expr_list", "try_catch_stmt", "try_block", "$@28",
  "except_block", "catch_block", "$@29", "catch_block_list", "throw_stmt",
  "typename_function", "typename_class", "typename_expr", "template_class",
  "template_expr", "template_header", "template_function_declaration",
  "template_class_declaration", "struct_or_class_x",
  "template_class_header", "template_class_name", "begin_templ_list",
  "end_templ_list", "template_type_list", "templ_item_list", "class_item",
  "class_parm", "templ_item", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
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
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     123,   125,    59,    58,    40,    41,    91,    93,    44
};
# endif

#define YYPACT_NINF -378

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-378)))

#define YYTABLE_NINF -343

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     661,   -88,   -81,   -39,  -378,  -378,    31,    63,    63,  -378,
    -378,  -378,   286,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,    53,  -378,  -378,    58,
      82,  2178,  2021,    89,    94,  2677,   100,  -378,  -378,  -378,
    -378,   206,  -378,  2021,    63,   239,   127,  -378,   199,  2428,
    2771,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  2245,  2245,  2245,  2803,   126,  2245,  2245,   933,  2245,
    2245,   150,  -378,  -378,  -378,  1954,   280,   786,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,   162,   117,
     148,    19,  -378,  -378,  -378,  2364,  2428,  -378,  -378,   406,
    2739,  -378,  -378,   174,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,    61,   310,  -378,   227,  -378,
    2802,  -378,  -378,   172,  -378,   251,   201,  -378,  -378,   279,
    -378,  -378,   216,  -378,  -378,  2553,  -378,  -378,   116,  -378,
    -378,  -378,   210,  2203,  -378,  -378,  -378,   568,  -378,  -378,
    -378,  2178,  -378,    53,  -378,  -378,  2178,  -378,  -378,  2245,
     163,   220,   224,  -378,  -378,  -378,  -378,   -18,   349,  -378,
    2428,   197,   345,   221,   343,   234,   237,   238,   242,   241,
    -378,  -378,  -378,  2178,   221,  2428,   354,   162,   245,   245,
      19,  -378,   338,  -378,  -378,  -378,  -378,   235,   184,   240,
    2178,  -378,  -378,  -378,  -378,  -378,  -378,  1954,  1100,  -378,
     243,   443,   -37,  -378,  -378,   336,  1710,  -378,  2615,   110,
    -378,  -378,  -378,  -378,  -378,  -378,  1100,  -378,   162,   248,
     249,    19,  -378,  -378,  -378,  -378,  -378,   315,   373,    87,
     187,    73,  -378,   250,   257,   149,  2771,  -378,  -378,   258,
     221,  -378,  -378,  -378,   216,  -378,  2677,   262,  2245,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  2178,
    2245,  2245,  2245,  2245,  2245,  2245,  2245,  2245,  2245,  2245,
    2245,  2245,  2245,  2245,  2245,  2245,  2245,  2245,  2245,  2245,
    -378,  -378,  -378,  -378,  -378,  2178,  -378,  2245,  -378,   162,
     279,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,    63,
    -378,  -378,   251,   132,  -378,   281,  -378,  -378,  -378,    97,
    -378,  -378,  -378,   263,  -378,   342,  1832,   266,  -378,  -378,
     -18,   -18,   162,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,    63,  -378,  -378,  -378,  -378,   270,    63,  -378,
    -378,  1100,  -378,  -378,   269,   273,  -378,   264,   187,    31,
    2178,  -378,  -378,  -378,  -378,   272,    -2,  1222,  2245,   274,
    -378,  -378,  -378,  -378,   122,   276,   271,  -378,  -378,   245,
    1344,   282,  -378,   373,   274,   395,    88,  -378,  -378,  -378,
    -378,   397,  -378,   908,   315,  2066,  -378,  -378,   406,  -378,
    -378,  -378,   335,  -378,   231,   290,  -378,  -378,  -378,  -378,
    -378,   316,  2178,  -378,     4,   647,   771,  1084,  1205,   511,
     426,   426,   457,   457,   457,   457,   233,   233,   180,   180,
     306,   306,   306,   511,  -378,   411,   413,   415,   -24,  -378,
    -378,  -378,  -378,  -378,  2178,  -378,  -378,  -378,  2491,  -378,
    -378,  -378,    53,  -378,  -378,  -378,   406,   297,  -378,  -378,
    -378,  -378,   300,   299,   245,  -378,  -378,  1466,  -378,  -378,
    -378,  -378,   -20,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    2615,   265,  -378,  -378,   274,   298,   395,   536,  -378,   122,
    -378,  -378,    73,  -378,  -378,  -378,  -378,   349,  -378,  -378,
      12,  2245,  -378,  -378,  -378,  -378,   242,   251,  -378,  -378,
    -378,  2021,  -378,   245,   421,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,    31,  -378,  -378,  -378,   357,    31,  -378,  -378,
     301,   302,  -378,  -378,  2133,  -378,  1100,  -378,  -378,  -378,
     305,  -378,   122,  -378,   -47,  -378,   265,  -378,  -378,  -378,
    2133,  -378,  -378,   -42,   251,  1588,   975,  -378,  -378,   421,
    -378,   162,    13,  -378,  2133,  -378,   307,  -378,  -378,  -378,
    -378,  -378,  -378,  -378
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   305,     0,   236,   299,   339,   342,     0,     0,    75,
     125,   126,   124,   131,   132,   133,   134,   128,   127,   241,
     242,   243,   244,   188,   187,   189,     0,    58,    61,     0,
       0,     0,     0,     0,     0,     0,     0,    45,   207,   228,
     219,     0,   329,     0,     0,    92,     0,    80,   204,     0,
       0,   114,   116,   117,   115,   180,   181,   179,   184,   185,
     186,     0,     0,     0,     0,   320,     0,     0,     0,     0,
       0,     0,   234,     6,    32,     0,     0,     0,    13,     4,
       8,     9,    10,    11,    12,    14,    18,    52,    34,    35,
      37,    38,    39,    36,    42,    40,    41,    76,     0,     0,
       0,     0,    83,    15,    27,     0,     0,    16,    94,     0,
       0,   110,   122,     0,   198,   198,   129,    19,    17,   130,
      24,    25,    26,    43,    31,     0,     0,   301,     0,   307,
     246,   248,   268,   270,   286,   306,     0,   303,    22,     0,
      23,   120,     0,   340,   343,     0,    21,    20,     0,    28,
     231,   232,   153,     0,   290,   323,   356,     0,   345,   346,
     123,     0,    54,     0,    52,    66,     0,   305,   236,     0,
       0,     0,     0,    51,    74,    73,   342,   149,     0,    30,
       0,   212,     0,   194,     0,     0,     0,     0,     0,     0,
     347,    91,   118,     0,   194,     0,     0,     0,     0,     0,
       0,   302,     0,   112,   273,   274,   276,   282,   239,     0,
       0,   277,   275,    77,   278,   271,   272,     0,     0,   107,
       0,     0,     0,     1,     5,    55,     0,   153,   156,    98,
      85,    96,    82,    93,    84,    95,     0,    90,     0,     0,
       0,     0,    89,    88,    86,   148,   152,   108,     0,     0,
       0,   168,   139,   163,     0,     0,     0,   111,   203,   190,
     194,   202,   235,   235,     0,   235,     0,     0,     0,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     296,   288,   289,   294,   292,     0,   291,     0,    33,     0,
     334,   328,   233,   351,   352,   348,   353,   354,   355,   349,
     322,   305,   325,     0,   366,   184,   357,   365,   358,     0,
     364,   367,   360,     0,    59,     0,     0,     0,    29,    72,
     149,   149,     0,    47,    46,    48,   213,   214,   208,   229,
     192,   193,   197,   195,   223,   220,   196,     0,   235,   225,
     227,     0,   330,   336,     0,     0,   205,    98,     0,     0,
       0,   281,   284,   321,   285,     0,     0,     0,     0,   106,
     300,    56,    53,   159,   168,     0,   157,    81,    99,     0,
       0,     0,   109,     0,   143,     0,     0,   136,   147,   140,
     167,     0,   146,     0,   108,     0,   161,   170,     0,    44,
     235,   235,     0,   113,   182,     0,   199,   237,   341,   344,
     238,     0,     0,   308,     0,   263,   262,   255,   267,   254,
     260,   261,   256,   258,   257,   259,   264,   265,   252,   253,
     249,   250,   251,   266,   309,     0,     0,     0,     0,   304,
     332,   335,   350,   154,     0,   324,   362,   363,     0,   359,
      49,    52,     0,    63,    65,    67,     0,     0,    70,   150,
     151,    78,   210,     0,     0,   224,   226,     0,   119,   121,
     206,   283,     0,   280,   279,     7,   269,    52,   160,   155,
     156,     0,    97,    87,   142,     0,     0,     0,   173,   168,
     171,   169,   168,   164,   145,   144,   183,     0,   200,   245,
       0,     0,   297,   295,   293,   287,     0,   326,   361,    60,
      62,     0,    64,     0,   216,   209,   230,   221,   331,   240,
      57,   158,     0,   337,   101,   100,   102,     0,   338,   135,
       0,     0,   166,    79,     0,   191,     0,   298,   247,   333,
       0,    71,   168,   217,     0,   105,     0,   104,   235,   137,
       0,   176,   177,     0,   175,     0,     0,   215,   211,     0,
     103,     0,     0,   172,     0,   201,     0,   218,   141,   174,
     178,    68,    52,    69
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -378,  -378,  -196,   -85,  -378,   -72,  -378,  -378,  -378,  -378,
    -378,   -78,  -378,  -378,  -378,  -146,   -40,  -154,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,   -48,    -6,
       6,    24,    27,   -68,    10,  -378,   324,  -378,  -378,   382,
     -65,  -378,  -378,  -123,  -378,  -136,  -113,    32,   -19,  -378,
    -378,  -378,   -25,   423,  -378,   190,  -378,  -101,   -50,  -231,
     -89,    52,   -79,   -49,  -378,  -378,    37,  -378,  -378,  -377,
    -378,  -378,  -127,  -112,    35,  -378,  -378,  -378,  -378,  -378,
    -143,   339,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -118,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,     0,  -378,  -218,    -4,  -378,
    -378,  -378,  -378,  1132,    -9,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,   -71,   -30,  -236,  -378,  -378,  -115,  -240,  -378,
    -378,  -378,  -378,   -63,  -378,  -378,   145,  -378,  -378,   -35,
     -87,  -171,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
     128,    18,  -378,  -378,  -378,     1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    76,    77,    78,   218,    79,    80,    81,    82,    83,
      84,    85,    86,   180,   344,   162,   172,   225,   226,    87,
      88,    89,   487,    90,   163,   461,    91,   164,   465,    92,
     336,   521,   582,    93,   523,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   243,   105,   106,   107,
     108,   389,   491,   535,   536,   219,   220,   393,   109,   110,
     193,   479,   111,   112,   250,   402,   497,   502,   342,   252,
     153,   455,   404,   385,   386,   253,   254,   541,   405,   406,
     544,   561,   562,   563,   113,   507,   114,   115,   415,   353,
     354,   259,   260,   116,   546,   117,   118,   195,   119,   181,
     472,   525,   348,   553,   554,   120,   183,   474,   355,   121,
     122,   123,   182,   473,   124,   170,   126,   417,   127,   371,
     128,   267,   129,   130,   131,   132,   369,   133,   447,   446,
     445,   134,   135,   136,   137,   299,   210,   154,   155,   323,
     138,   139,   188,   362,   310,   516,   311,   140,   537,   141,
     142,   143,   144,   145,   146,   147,   316,   148,   319,   157,
     328,   158,   329,   330,   331,   332
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     125,   171,   173,   189,   222,   224,   187,   488,   251,   228,
     335,   407,   356,   173,   231,   233,   177,   334,   306,   229,
     213,   327,   377,   356,   411,   203,   159,   237,   237,     9,
     202,   307,   423,   234,   149,   178,   235,   186,   264,   208,
     390,   185,   150,   197,   307,   418,   419,   420,   307,   178,
     178,   365,   204,   205,   206,   198,   221,   211,   212,   214,
     215,   216,   190,   444,   178,   168,   307,     5,   176,     7,
       8,   449,   307,   199,   568,   125,   200,   125,   340,   573,
     307,   569,   322,   264,   151,   257,   574,   341,   380,   356,
     263,   264,   384,   372,   176,   176,     8,     8,   264,   238,
     238,   368,   343,   515,   375,   178,   178,   529,   228,   255,
     178,   239,   239,   231,   233,   242,   242,   416,   367,   317,
     379,   262,   543,   484,   318,   125,   202,   511,   196,   240,
     240,   333,   241,   241,   579,   235,   337,   547,   221,   374,
     476,   574,   400,   263,   407,   178,   376,   394,   213,   228,
     263,   156,   246,   421,   382,   152,   176,   178,     8,   391,
     214,   228,   403,   364,   495,   477,   262,   168,   264,   315,
     176,   399,     8,   234,   238,   567,   202,   161,   178,    72,
     178,   262,   165,   395,   496,   125,   239,   326,    35,   238,
     345,   400,   504,   505,   197,   178,   401,   227,   221,   397,
     346,   239,   255,   347,   240,   366,   166,   241,   424,   221,
     168,   174,     5,   176,     7,     8,   175,   125,   125,   240,
     228,   255,   241,   179,   350,   458,   125,   351,   178,   352,
     450,   413,   387,   388,   448,   238,   125,    73,   168,   230,
       5,   176,   358,     8,   191,   401,   227,   221,   255,   396,
     184,   192,   209,   228,   481,   412,   178,   453,   464,   407,
     454,   410,   407,   471,   194,   540,   178,   384,    73,   532,
     232,   300,   533,     7,   217,   548,   295,   296,   297,   228,
     223,    72,   301,   302,   456,   298,   227,   457,   303,   304,
     469,   470,   494,    55,    56,    57,   152,   258,   305,   482,
      13,    14,    15,    16,   492,   224,   467,   519,   152,   264,
     370,   227,   407,   397,   265,   266,   520,   466,   224,   307,
     538,   534,   327,   308,    72,   264,   309,   293,   294,   295,
     296,   297,   322,   530,   312,   320,   125,   452,   298,   245,
     571,   246,   176,   338,     8,   176,   339,     8,   349,   357,
     565,   510,    72,  -342,   384,     5,   176,     7,     8,   359,
     360,   125,   361,   363,     9,    73,   381,   373,   378,   486,
     230,   232,   392,   462,   245,   501,   246,   125,   408,   409,
     176,   414,     8,   517,   221,   538,   422,   388,   460,   527,
     125,   468,   475,   255,   478,   480,   412,   483,   246,   490,
     397,   453,   498,   125,   387,   224,   509,   245,   255,   246,
     508,   298,   412,   176,   512,     8,   513,   555,   514,   522,
     524,   526,   557,   539,   552,   556,   558,   566,   583,   559,
     244,   201,   581,   570,   247,   160,   499,   489,   551,   221,
     398,   531,  -138,   248,   245,   503,   246,   580,   572,   506,
     176,   577,     8,   549,   261,   451,     0,   459,   178,   518,
       0,     0,   249,  -138,  -138,     0,   255,   542,     0,   247,
       0,   221,   545,   564,     0,  -138,     0,   125,   248,     0,
       0,   550,   228,     0,     0,     0,     0,     0,     0,   564,
     178,   173,   578,   224,     0,  -138,  -138,   249,  -138,  -138,
       0,  -138,   247,   564,     0,     0,     0,   178,     0,     0,
       0,   248,  -138,     0,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,     0,   576,     0,  -138,  -138,
     249,   298,  -138,  -138,  -138,     0,   173,   167,     0,   247,
     168,     4,     0,     6,     0,     8,   125,     0,   248,   291,
     292,   293,   294,   295,   296,   297,    19,    20,    21,    22,
       0,     0,   298,     0,     0,   125,  -138,   249,  -138,  -138,
       0,  -138,     0,   324,     5,   176,     7,     8,     0,    10,
      11,    12,    13,    14,    15,    16,    17,    18,     0,     0,
       0,    49,     0,     0,    23,    24,    25,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
      38,     0,     0,     0,     0,     0,   298,     0,     0,     0,
      46,     0,     0,     0,     0,    50,    51,    52,    53,    54,
      61,    62,    63,   325,    59,    60,     0,    64,    65,     0,
       0,    66,     0,     0,    67,   169,    69,    70,    71,     0,
       0,     0,     0,     0,    72,     0,     0,     0,   326,     0,
      75,    -3,     1,  -165,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,     0,     0,    23,    24,    25,
      26,     0,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,     0,    43,
      44,    45,     0,    46,    47,    48,    49,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,     0,     0,     0,     0,
       0,     0,   298,     0,     0,    61,    62,    63,     0,     0,
       0,     0,    64,    65,     0,     0,    66,     0,     0,    67,
      68,    69,    70,    71,     0,     0,     0,     0,     0,    72,
       0,    73,     0,    74,     0,    75,    -2,     1,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
       0,     0,    23,    24,    25,    26,     0,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     0,    43,    44,    45,     0,    46,    47,
      48,    49,     0,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
       0,     0,     0,     0,     0,     0,   298,     0,     0,     0,
      61,    62,    63,     0,     0,     0,     0,    64,    65,     0,
       0,    66,     0,     0,    67,    68,    69,    70,    71,     0,
       0,     0,     0,     0,    72,     0,    73,     0,    74,   321,
      75,     0,   168,     4,     5,     6,     7,     8,     0,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,     0,     0,    23,    24,    25,   168,     4,     0,
       6,     0,     8,     9,     0,     0,     0,     0,     0,     0,
      38,     0,     0,    19,    20,    21,    22,     0,     0,   383,
      46,     0,     0,    49,     0,    50,    51,    52,    53,    54,
       0,     0,     0,    58,    59,    60,   167,     0,     0,   168,
       4,     0,     6,     0,     8,     0,     0,     0,    49,     0,
       0,     0,     0,     0,     0,    19,    20,    21,    22,     0,
       0,     0,    61,    62,    63,     0,     0,     0,     0,    64,
      65,     0,     0,    66,     0,     0,    67,   169,    69,    70,
      71,     0,     0,     0,     0,     0,    72,    61,    62,    63,
      49,     0,    75,  -156,    64,    65,     0,     0,    66,     0,
       0,    67,   169,    69,    70,    71,     0,     0,     0,     0,
       0,    72,     0,     0,     0,     0,     0,    75,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,     0,     0,     0,     0,    64,    65,     0,     0,
      66,     0,     0,    67,   169,    69,    70,    71,     0,     0,
       0,     0,     0,    72,     0,     0,     0,     0,     0,    75,
     -50,     1,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,     0,     0,    23,    24,    25,    26,
       0,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,     0,    43,    44,
      45,     0,    46,    47,    48,    49,     0,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,     0,     0,     0,     0,     0,     0,   298,
       0,     0,     0,     0,    61,    62,    63,     0,     0,     0,
       0,    64,    65,     0,     0,    66,     0,     0,    67,    68,
      69,    70,    71,     0,     0,     0,     0,     0,    72,     0,
      73,    -3,    74,     1,    75,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,     0,     0,    23,    24,
      25,    26,     0,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,     0,
      43,    44,    45,     0,    46,    47,    48,    49,     0,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,     0,     0,     0,     0,     0,     0,
     298,     0,     0,     0,     0,     0,    61,    62,    63,     0,
       0,     0,     0,    64,    65,     0,     0,    66,     0,     0,
      67,    68,    69,    70,    71,     0,     0,     0,     0,     0,
      72,     0,    73,   485,    74,     1,    75,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,     0,     0,
      23,    24,    25,    26,     0,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,     0,    43,    44,    45,     0,    46,    47,    48,    49,
       0,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,     0,     0,     0,     0,    64,    65,     0,     0,    66,
       0,     0,    67,    68,    69,    70,    71,     0,     0,     0,
       0,     0,    72,     0,    73,   493,    74,     1,    75,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
       0,     0,    23,    24,    25,    26,     0,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     0,    43,    44,    45,     0,    46,    47,
      48,    49,     0,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,     0,     0,     0,     0,    64,    65,     0,
       0,    66,     0,     0,    67,    68,    69,    70,    71,     0,
       0,     0,     0,     0,    72,     0,    73,   528,    74,     1,
      75,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,     0,     0,    23,    24,    25,    26,     0,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,     0,    43,    44,    45,     0,
      46,    47,    48,    49,     0,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,    62,    63,     0,     0,     0,     0,    64,
      65,     0,     0,    66,     0,     0,    67,    68,    69,    70,
      71,     0,     0,     0,     0,     0,    72,     0,    73,   575,
      74,     1,    75,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,     0,     0,    23,    24,    25,    26,
       0,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,     0,    43,    44,
      45,     0,    46,    47,    48,    49,     0,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,     0,     0,     0,
       0,    64,    65,     0,     0,    66,     0,     0,    67,    68,
      69,    70,    71,     0,     0,     0,     0,     0,    72,     0,
      73,     0,    74,   167,    75,     0,   168,     4,     5,     6,
       7,     8,     0,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,     0,     0,    23,    24,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,     0,     0,    49,     0,    50,
      51,    52,    53,    54,     0,     0,     0,    58,    59,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,    62,    63,     0,
       0,     0,     0,    64,    65,     0,     0,    66,     0,     0,
      67,   169,    69,    70,    71,     0,     0,     0,     0,     0,
      72,     0,     0,     0,   463,   167,    75,     0,   168,     4,
       5,     6,     7,     8,     0,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,     0,     0,
      23,    24,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46,     0,     0,    49,
       0,    50,    51,    52,    53,    54,     0,     0,     0,    58,
      59,    60,   167,     0,     0,   168,     4,     0,     6,     0,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,    20,    21,    22,     0,     0,     0,    61,    62,
      63,     0,     0,     0,     0,    64,    65,     0,     0,    66,
       0,     0,    67,   169,    69,    70,    71,   167,     0,     0,
     168,     4,    72,     6,     0,     8,    49,     0,    75,     0,
       0,     0,     0,     0,     0,     0,    19,    20,    21,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,     0,     0,
       0,    49,    64,    65,     0,     0,    66,     0,     0,    67,
     169,    69,    70,    71,   167,     0,     0,   168,     4,    72,
       6,     0,     8,   -50,     0,    75,     0,     0,     0,     0,
       0,     0,     0,    19,    20,    21,    22,     0,     0,     0,
      61,    62,    63,     0,     0,     0,     0,    64,    65,     0,
       0,    66,     0,     0,    67,   169,    69,    70,    71,   167,
       0,     0,   168,     4,    72,     6,   500,     8,    49,     0,
      75,     0,     0,     0,     0,     0,     0,     0,    19,    20,
      21,    22,     0,     0,   321,     0,     0,   168,     4,     0,
       6,     0,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,    20,    21,    22,    61,    62,    63,
       0,     0,     0,    49,    64,    65,     0,     0,    66,     0,
       0,    67,   169,    69,    70,    71,     0,     0,     0,   168,
       4,    72,     6,   560,     8,     0,     0,    75,    49,     0,
       0,     0,     0,     0,     0,    19,    20,    21,    22,     0,
       0,     0,    61,    62,    63,     0,     0,     0,     0,    64,
      65,     0,     0,    66,     0,     0,    67,   169,    69,    70,
      71,     0,     0,     0,     0,     0,    72,    61,    62,    63,
      49,     0,    75,     0,    64,    65,     0,     0,    66,     0,
       0,    67,   169,    69,    70,    71,     0,     0,     0,     0,
       0,    72,     0,     0,     0,     0,     0,    75,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,     0,     0,     0,     0,    64,    65,     0,     0,
      66,     0,     0,    67,   169,    69,    70,    71,     0,     0,
       0,     0,     0,    72,     0,     0,     0,     0,     0,    75,
       5,   176,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     0,     0,     0,     0,     0,     0,
      23,    24,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,     0,     0,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46,    47,     0,     0,
       0,    50,    51,    52,    53,    54,     0,     0,     0,    58,
      59,    60,     0,     0,     5,   176,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,     0,     0,
       0,     0,     0,     0,    23,    24,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,     0,     0,
      38,     0,     0,   196,     0,     0,     0,     0,     0,     0,
      46,    47,     0,     0,   236,    50,    51,    52,    53,    54,
       0,     0,     0,    58,    59,    60,   324,     5,   176,     7,
       8,     0,    10,    11,    12,    13,    14,    15,    16,    17,
      18,     0,     0,     0,     0,     0,     0,    23,    24,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    38,     0,     0,     0,   196,     0,     0,
       0,     0,     0,    46,     0,     0,     0,     0,    50,    51,
      52,    53,    54,     0,     0,     0,   325,    59,    60,     5,
     176,     7,     8,     0,    10,    11,    12,    13,    14,    15,
      16,    17,    18,     0,     0,     0,     0,   313,   314,    23,
      24,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     0,     0,     0,
      50,    51,    52,    53,    54,     0,     0,     0,    58,    59,
      60,     5,   176,     7,     8,     0,    10,    11,    12,    13,
      14,    15,    16,    17,    18,     0,     0,     0,     0,     0,
       0,    23,    24,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,     0,     0,     0,     0,     0,   383,    46,     0,     0,
       0,     0,    50,    51,    52,    53,    54,     0,     0,     0,
      58,    59,    60,     5,   176,     7,     8,     0,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     0,     0,     0,
       0,     0,     0,    23,    24,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
       0,     0,     0,     0,    50,    51,    52,    53,    54,     0,
       0,     0,    58,    59,    60,     5,   176,     7,     8,     0,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     0,
       0,     0,     0,     0,     0,    23,    24,    25,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,   176,     7,
       8,    38,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    46,     0,     0,     0,     0,   256,    23,    24,    25,
       0,     0,     0,     0,    58,    59,    60,     0,     0,     5,
     207,     7,     8,    38,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    46,     0,     0,     0,     0,     0,    23,
      24,    25,     0,     0,     0,     0,    58,    59,    60,     0,
       0,     0,     0,     0,     0,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    59,
      60,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,     0,     0,     0,     0,     0,     0,   298
};

static const yytype_int16 yycheck[] =
{
       0,    31,    32,    43,    75,    77,    41,   384,   109,    98,
     164,   251,   183,    43,    99,   100,    35,   163,   133,    98,
      68,   157,   218,   194,   255,    50,     8,   105,   106,    10,
      49,    68,   268,   101,   122,    35,   101,    41,   125,    64,
     236,    41,   123,    49,    68,   263,   264,   265,    68,    49,
      50,   194,    61,    62,    63,    49,    75,    66,    67,    68,
      69,    70,    44,   299,    64,     4,    68,     6,     7,     8,
       9,   307,    68,    49,   121,    75,    49,    77,    96,   121,
      68,   128,   153,   170,   123,   110,   128,   105,   125,   260,
     125,   178,   228,   208,     7,     7,     9,     9,   185,   105,
     106,   202,   180,   127,   217,   105,   106,   127,   197,   109,
     110,   105,   106,   198,   199,   105,   106,   260,   197,     3,
     221,   125,   499,   125,     8,   125,   145,   123,   109,   105,
     106,   161,   105,   106,   121,   200,   166,   125,   157,   210,
     358,   128,    69,   178,   384,   145,   217,   248,   196,   238,
     185,    88,     3,   266,   226,   124,     7,   157,     9,   238,
     169,   250,   251,   193,   395,   361,   170,     4,   255,   145,
       7,   250,     9,   241,   180,   552,   195,   124,   178,   118,
     180,   185,   124,    96,    96,   185,   180,    90,    39,   195,
     180,    69,   410,   411,   200,   195,   123,   124,   217,   126,
       3,   195,   202,     6,   180,   195,   124,   180,   279,   228,
       4,   122,     6,     7,     8,     9,   122,   217,   218,   195,
     309,   221,   195,   123,     3,   128,   226,     6,   228,     8,
     309,   256,   122,   123,   305,   241,   236,   120,     4,   122,
       6,     7,     8,     9,     5,   123,   124,   266,   248,   249,
      44,   124,   126,   342,   369,   255,   256,   125,   336,   499,
     128,   255,   502,   342,    65,   496,   266,   403,   120,     4,
     122,    99,     7,     8,   124,   511,    96,    97,    98,   368,
       0,   118,   110,   111,     3,   105,   124,     6,   116,   117,
     340,   341,   393,    62,    63,    64,   124,   123,   126,   370,
      14,    15,    16,    17,   389,   377,   336,   461,   124,   396,
     126,   124,   552,   126,     4,    88,   462,   336,   390,    68,
     491,    56,   458,   122,   118,   412,    47,    94,    95,    96,
      97,    98,   403,   487,   118,   125,   336,   319,   105,     1,
     558,     3,     7,   123,     9,     7,   122,     9,     3,     6,
     546,   422,   118,   118,   490,     6,     7,     8,     9,   122,
     122,   361,   120,   122,    10,   120,    30,   127,   125,   378,
     122,   122,    57,    31,     1,   405,     3,   377,   128,   122,
       7,   123,     9,   454,   403,   556,   124,   123,   125,   474,
     390,   125,   122,   393,   125,   122,   396,   125,     3,   128,
     126,   125,     5,   403,   122,   477,    90,     1,   408,     3,
     120,   105,   412,     7,     3,     9,     3,   532,     3,   122,
     120,   122,   537,   125,     3,    68,   125,   122,   582,   127,
     106,    49,   125,   556,    96,    12,   404,   385,   523,   458,
     250,   490,    69,   105,     1,   408,     3,   574,   560,   414,
       7,   569,     9,   516,   115,   310,    -1,   329,   458,   458,
      -1,    -1,   124,    90,   126,    -1,   466,   497,    -1,    96,
      -1,   490,   507,   544,    -1,    69,    -1,   477,   105,    -1,
      -1,   521,   571,    -1,    -1,    -1,    -1,    -1,    -1,   560,
     490,   521,   571,   565,    -1,   122,   123,   124,   125,   126,
      -1,   128,    96,   574,    -1,    -1,    -1,   507,    -1,    -1,
      -1,   105,    69,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    -1,   566,    -1,   122,   123,
     124,   105,   126,    90,   128,    -1,   566,     1,    -1,    96,
       4,     5,    -1,     7,    -1,     9,   546,    -1,   105,    92,
      93,    94,    95,    96,    97,    98,    20,    21,    22,    23,
      -1,    -1,   105,    -1,    -1,   565,   123,   124,   125,   126,
      -1,   128,    -1,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    55,    -1,    -1,    26,    27,    28,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      42,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      94,    95,    96,    65,    66,    67,    -1,   101,   102,    -1,
      -1,   105,    -1,    -1,   108,   109,   110,   111,   112,    -1,
      -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,    90,    -1,
     124,     0,     1,   127,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    -1,    26,    27,    28,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      49,    50,    -1,    52,    53,    54,    55,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,    -1,   105,    -1,    -1,    94,    95,    96,    -1,    -1,
      -1,    -1,   101,   102,    -1,    -1,   105,    -1,    -1,   108,
     109,   110,   111,   112,    -1,    -1,    -1,    -1,    -1,   118,
      -1,   120,    -1,   122,    -1,   124,     0,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    49,    50,    -1,    52,    53,
      54,    55,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,
      94,    95,    96,    -1,    -1,    -1,    -1,   101,   102,    -1,
      -1,   105,    -1,    -1,   108,   109,   110,   111,   112,    -1,
      -1,    -1,    -1,    -1,   118,    -1,   120,    -1,   122,     1,
     124,    -1,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,    26,    27,    28,     4,     5,    -1,
       7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    -1,    20,    21,    22,    23,    -1,    -1,    51,
      52,    -1,    -1,    55,    -1,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    65,    66,    67,     1,    -1,    -1,     4,
       5,    -1,     7,    -1,     9,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,    -1,
      -1,    -1,    94,    95,    96,    -1,    -1,    -1,    -1,   101,
     102,    -1,    -1,   105,    -1,    -1,   108,   109,   110,   111,
     112,    -1,    -1,    -1,    -1,    -1,   118,    94,    95,    96,
      55,    -1,   124,   125,   101,   102,    -1,    -1,   105,    -1,
      -1,   108,   109,   110,   111,   112,    -1,    -1,    -1,    -1,
      -1,   118,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      95,    96,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,
     105,    -1,    -1,   108,   109,   110,   111,   112,    -1,    -1,
      -1,    -1,    -1,   118,    -1,    -1,    -1,    -1,    -1,   124,
     125,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    48,    49,
      50,    -1,    52,    53,    54,    55,    -1,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    94,    95,    96,    -1,    -1,    -1,
      -1,   101,   102,    -1,    -1,   105,    -1,    -1,   108,   109,
     110,   111,   112,    -1,    -1,    -1,    -1,    -1,   118,    -1,
     120,   121,   122,     1,   124,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      48,    49,    50,    -1,    52,    53,    54,    55,    -1,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,
     105,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,    -1,
      -1,    -1,    -1,   101,   102,    -1,    -1,   105,    -1,    -1,
     108,   109,   110,   111,   112,    -1,    -1,    -1,    -1,    -1,
     118,    -1,   120,   121,   122,     1,   124,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      26,    27,    28,    29,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    49,    50,    -1,    52,    53,    54,    55,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,   105,
      -1,    -1,   108,   109,   110,   111,   112,    -1,    -1,    -1,
      -1,    -1,   118,    -1,   120,   121,   122,     1,   124,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    49,    50,    -1,    52,    53,
      54,    55,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    95,    96,    -1,    -1,    -1,    -1,   101,   102,    -1,
      -1,   105,    -1,    -1,   108,   109,   110,   111,   112,    -1,
      -1,    -1,    -1,    -1,   118,    -1,   120,   121,   122,     1,
     124,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    48,    49,    50,    -1,
      52,    53,    54,    55,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    95,    96,    -1,    -1,    -1,    -1,   101,
     102,    -1,    -1,   105,    -1,    -1,   108,   109,   110,   111,
     112,    -1,    -1,    -1,    -1,    -1,   118,    -1,   120,   121,
     122,     1,   124,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    48,    49,
      50,    -1,    52,    53,    54,    55,    -1,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    95,    96,    -1,    -1,    -1,
      -1,   101,   102,    -1,    -1,   105,    -1,    -1,   108,   109,
     110,   111,   112,    -1,    -1,    -1,    -1,    -1,   118,    -1,
     120,    -1,   122,     1,   124,    -1,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    55,    -1,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,    -1,
      -1,    -1,    -1,   101,   102,    -1,    -1,   105,    -1,    -1,
     108,   109,   110,   111,   112,    -1,    -1,    -1,    -1,    -1,
     118,    -1,    -1,    -1,   122,     1,   124,    -1,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    55,
      -1,    57,    58,    59,    60,    61,    -1,    -1,    -1,    65,
      66,    67,     1,    -1,    -1,     4,     5,    -1,     7,    -1,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    21,    22,    23,    -1,    -1,    -1,    94,    95,
      96,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,   105,
      -1,    -1,   108,   109,   110,   111,   112,     1,    -1,    -1,
       4,     5,   118,     7,    -1,     9,    55,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    95,    96,    -1,    -1,
      -1,    55,   101,   102,    -1,    -1,   105,    -1,    -1,   108,
     109,   110,   111,   112,     1,    -1,    -1,     4,     5,   118,
       7,    -1,     9,   122,    -1,   124,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    21,    22,    23,    -1,    -1,    -1,
      94,    95,    96,    -1,    -1,    -1,    -1,   101,   102,    -1,
      -1,   105,    -1,    -1,   108,   109,   110,   111,   112,     1,
      -1,    -1,     4,     5,   118,     7,   120,     9,    55,    -1,
     124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,
      22,    23,    -1,    -1,     1,    -1,    -1,     4,     5,    -1,
       7,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    21,    22,    23,    94,    95,    96,
      -1,    -1,    -1,    55,   101,   102,    -1,    -1,   105,    -1,
      -1,   108,   109,   110,   111,   112,    -1,    -1,    -1,     4,
       5,   118,     7,   120,     9,    -1,    -1,   124,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,    -1,
      -1,    -1,    94,    95,    96,    -1,    -1,    -1,    -1,   101,
     102,    -1,    -1,   105,    -1,    -1,   108,   109,   110,   111,
     112,    -1,    -1,    -1,    -1,    -1,   118,    94,    95,    96,
      55,    -1,   124,    -1,   101,   102,    -1,    -1,   105,    -1,
      -1,   108,   109,   110,   111,   112,    -1,    -1,    -1,    -1,
      -1,   118,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      95,    96,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,
     105,    -1,    -1,   108,   109,   110,   111,   112,    -1,    -1,
      -1,    -1,    -1,   118,    -1,    -1,    -1,    -1,    -1,   124,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    -1,    -1,    -1,    65,
      66,    67,    -1,    -1,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      42,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    53,    -1,    -1,   120,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    65,    66,    67,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    -1,    -1,    -1,   109,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    65,    66,    67,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    24,    25,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    65,    66,
      67,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      65,    66,    67,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    65,    66,    67,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
       9,    42,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    52,    -1,    -1,    -1,    -1,    57,    26,    27,    28,
      -1,    -1,    -1,    -1,    65,    66,    67,    -1,    -1,     6,
       7,     8,     9,    42,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    52,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,    -1,   105
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    26,    27,    28,    29,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    48,    49,    50,    52,    53,    54,    55,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    94,    95,    96,   101,   102,   105,   108,   109,   110,
     111,   112,   118,   120,   122,   124,   130,   131,   132,   134,
     135,   136,   137,   138,   139,   140,   141,   148,   149,   150,
     152,   155,   158,   162,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   176,   177,   178,   179,   187,
     188,   191,   192,   213,   215,   216,   222,   224,   225,   227,
     234,   238,   239,   240,   243,   244,   245,   247,   249,   251,
     252,   253,   254,   256,   260,   261,   262,   263,   269,   270,
     276,   278,   279,   280,   281,   282,   283,   284,   286,   122,
     123,   123,   124,   199,   266,   267,    88,   288,   290,   290,
     192,   124,   144,   153,   156,   124,   124,     1,     4,   109,
     244,   262,   145,   262,   122,   122,     7,   187,   244,   123,
     142,   228,   241,   235,    44,   244,   247,   278,   271,   145,
     290,     5,   124,   189,    65,   226,   109,   168,   169,   170,
     171,   178,   187,   191,   253,   253,   253,     7,   191,   126,
     265,   253,   253,   167,   253,   253,   253,   124,   133,   184,
     185,   187,   261,     0,   134,   146,   147,   124,   199,   201,
     122,   132,   122,   132,   172,   179,   120,   140,   168,   169,
     170,   171,   173,   175,   175,     1,     3,    96,   105,   124,
     193,   196,   198,   204,   205,   244,    57,   191,   123,   220,
     221,   220,   247,   278,   279,     4,    88,   250,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,   105,   264,
      99,   110,   111,   116,   117,   126,   266,    68,   122,    47,
     273,   275,   118,    24,    25,   170,   285,     3,     8,   287,
     125,     1,   261,   268,     5,    65,    90,   184,   289,   291,
     292,   293,   294,   262,   144,   146,   159,   262,   123,   122,
      96,   105,   197,   140,   143,   173,     3,     6,   231,     3,
       3,     6,     8,   218,   219,   237,   280,     6,     8,   122,
     122,   120,   272,   122,   262,   219,   173,   201,   196,   255,
     126,   248,   266,   127,   261,   185,   261,   131,   125,   196,
     125,    30,   134,    51,   184,   202,   203,   122,   123,   180,
     131,   201,    57,   186,   196,    96,   244,   126,   194,   201,
      69,   123,   194,   199,   201,   207,   208,   267,   128,   122,
     169,   198,   244,   191,   123,   217,   219,   246,   246,   246,
     246,   185,   124,   263,   261,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   263,   259,   258,   257,   261,   263,
     201,   275,   290,   125,   128,   200,     3,     6,   128,   289,
     125,   154,    31,   122,   140,   157,   187,   262,   125,   197,
     197,   201,   229,   242,   236,   122,   246,   131,   125,   190,
     122,   266,   261,   125,   125,   121,   253,   151,   208,   200,
     128,   181,   132,   121,   196,   198,    96,   195,     5,   186,
     120,   262,   196,   205,   246,   246,   213,   214,   120,    90,
     261,   123,     3,     3,     3,   127,   274,   261,   294,   146,
     144,   160,   122,   163,   120,   230,   122,   132,   121,   127,
     146,   202,     4,     7,    56,   182,   183,   277,   280,   125,
     198,   206,   262,   208,   209,   278,   223,   125,   263,   272,
     145,   132,     3,   232,   233,   266,    68,   266,   125,   127,
     120,   210,   211,   212,   261,   131,   122,   208,   121,   128,
     182,   246,   212,   121,   128,   121,   145,   232,   201,   121,
     211,   125,   161,   146
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   129,   130,   131,   131,   131,   133,   132,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   135,
     135,   135,   136,   136,   137,   137,   137,   138,   138,   138,
     139,   139,   139,   139,   140,   142,   141,   143,   143,   144,
     145,   145,   147,   146,   148,   149,   151,   150,   153,   154,
     152,   156,   155,   157,   157,   157,   159,   160,   161,   158,
     163,   162,   164,   165,   166,   167,   168,   168,   169,   170,
     171,   172,   173,   173,   173,   173,   174,   174,   174,   175,
     175,   176,   177,   178,   178,   178,   178,   179,   180,   181,
     180,   182,   182,   182,   183,   183,   184,   185,   186,   186,
     187,   187,   187,   187,   188,   188,   188,   188,   189,   190,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   192,   192,   192,   192,   193,   195,   194,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   197,
     197,   197,   198,   199,   200,   201,   202,   202,   202,   202,
     203,   204,   205,   205,   205,   206,   206,   207,   208,   208,
     208,   209,   208,   208,   210,   211,   211,   212,   212,   213,
     213,   213,   214,   214,   215,   215,   215,   216,   216,   216,
     217,   217,   218,   218,   219,   219,   219,   219,   221,   220,
     223,   222,   222,   224,   226,   225,   225,   228,   229,   227,
     230,   230,   231,   231,   231,   232,   233,   233,   233,   235,
     236,   234,   237,   237,   238,   239,   239,   239,   241,   242,
     240,   243,   243,   244,   245,   246,   247,   247,   247,   248,
     248,   249,   249,   249,   249,   250,   251,   251,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   253,   253,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   255,   254,   254,   254,   256,   256,   256,   256,
     256,   256,   257,   256,   258,   256,   259,   256,   256,   260,
     260,   260,   260,   261,   261,   261,   262,   263,   263,   263,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     265,   265,   266,   266,   267,   268,   268,   268,   269,   271,
     270,   272,   274,   273,   275,   275,   276,   277,   277,   278,
     278,   278,   279,   279,   279,   280,   281,   282,   283,   284,
     284,   285,   285,   286,   287,   287,   288,   289,   290,   290,
     291,   291,   292,   292,   293,   294,   294,   294
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     0,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       2,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     3,     1,     1,     3,
       0,     1,     0,     2,     2,     2,     0,     5,     0,     0,
       5,     0,     5,     1,     2,     1,     0,     0,     0,    11,
       0,     6,     3,     2,     2,     1,     1,     2,     4,     5,
       1,     3,     2,     1,     2,     2,     2,     4,     2,     1,
       1,     2,     1,     2,     1,     2,     2,     4,     0,     0,
       3,     1,     1,     3,     2,     2,     2,     1,     0,     1,
       1,     2,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     0,     4,     0,     1,
       2,     7,     3,     2,     3,     3,     2,     2,     1,     0,
       2,     2,     1,     1,     1,     3,     0,     1,     3,     1,
       2,     2,     0,     1,     3,     0,     1,     1,     0,     2,
       1,     0,     5,     2,     3,     1,     1,     1,     3,     1,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       0,     3,     1,     1,     0,     1,     1,     1,     0,     2,
       0,     7,     2,     2,     0,     3,     4,     0,     0,     5,
       0,     3,     0,     1,     1,     2,     0,     1,     3,     0,
       0,     5,     0,     1,     4,     3,     4,     3,     0,     0,
       5,     2,     2,     2,     1,     0,     1,     3,     3,     0,
       3,     1,     1,     1,     1,     3,     1,     5,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     4,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       4,     3,     0,     4,     3,     3,     1,     4,     2,     2,
       2,     2,     0,     4,     0,     4,     0,     4,     5,     1,
       3,     1,     2,     1,     3,     1,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     2,     2,     1,     3,     1,     3,     1,     2,     0,
       3,     3,     0,     4,     1,     2,     3,     1,     1,     1,
       1,     3,     1,     1,     3,     2,     2,     2,     2,     2,
       3,     1,     1,     2,     1,     1,     1,     1,     2,     3,
       1,     3,     2,     2,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 4:
#line 159 "parser.y" /* yacc.c:1646  */
    {statement_end();}
#line 2486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 160 "parser.y" /* yacc.c:1646  */
    {statement_end();}
#line 2492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 162 "parser.y" /* yacc.c:1646  */
    { state.init_block(PLAIN_BLOCK); IEF_set(); }
#line 2498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 164 "parser.y" /* yacc.c:1646  */
    { state.finalize_block(); IEF_reset();}
#line 2504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 186 "parser.y" /* yacc.c:1646  */
    { raise_error("Error in statement"); YYABORT; }
#line 2510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 188 "parser.y" /* yacc.c:1646  */
    { do_case ((yyvsp[-1].expression));   }
#line 2516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 189 "parser.y" /* yacc.c:1646  */
    { do_case(NULL);  }
#line 2522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 193 "parser.y" /* yacc.c:1646  */
    {expression_end((yyvsp[-1].expression));}
#line 2528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 209 "parser.y" /* yacc.c:1646  */
    {
               Type dt = tpop();
               dcl_reset();
               state.check_dcl_init(dt);
             }
#line 2538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 215 "parser.y" /* yacc.c:1646  */
    { state.in_typedef = true; }
#line 2544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 216 "parser.y" /* yacc.c:1646  */
    { state.in_typedef = false; }
#line 2550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 222 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[-1].expression); }
#line 2556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 225 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = NULL; }
#line 2562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 226 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 2568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 228 "parser.y" /* yacc.c:1646  */
    {IEF_set();}
#line 2574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 230 "parser.y" /* yacc.c:1646  */
    {IEF_reset(); check_temp_context(); }
#line 2580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 232 "parser.y" /* yacc.c:1646  */
    { do_loop_start((yyvsp[0].expression),false); }
#line 2586 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 234 "parser.y" /* yacc.c:1646  */
    { do_loop_end(false); }
#line 2592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 237 "parser.y" /* yacc.c:1646  */
    { do_loop_end(true,true); }
#line 2598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 238 "parser.y" /* yacc.c:1646  */
    { do_loop_end(false); }
#line 2604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 240 "parser.y" /* yacc.c:1646  */
    { label_here(); state.in_loop = true; }
#line 2610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 241 "parser.y" /* yacc.c:1646  */
    { do_loop_start((yyvsp[0].expression),true); }
#line 2616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 242 "parser.y" /* yacc.c:1646  */
    { do_loop_end(true); state.in_loop = false;}
#line 2622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 245 "parser.y" /* yacc.c:1646  */
    { label_here(); push_label_stack(); state.in_loop = true;}
#line 2628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 247 "parser.y" /* yacc.c:1646  */
    { do_do_end((yyvsp[0].expression)); state.in_loop = false; }
#line 2634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 250 "parser.y" /* yacc.c:1646  */
    { code().compile((yyvsp[-1].expression),DROP_VALUE); }
#line 2640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 253 "parser.y" /* yacc.c:1646  */
    { state.init_block(PLAIN_BLOCK); }
#line 2646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 254 "parser.y" /* yacc.c:1646  */
    { label_here();	state.in_loop = true; }
#line 2652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 256 "parser.y" /* yacc.c:1646  */
    { do_loop_start((yyvsp[-3].expression),true); }
#line 2658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 257 "parser.y" /* yacc.c:1646  */
    { do_for_end((yyvsp[-3].expression));    state.in_loop = false;
                                       state.finalize_block();
                                     }
#line 2666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 261 "parser.y" /* yacc.c:1646  */
    { do_switch((yyvsp[-1].expression)); }
#line 2672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 264 "parser.y" /* yacc.c:1646  */
    { if (!do_return ((yyvsp[-1].expression))) { check_error(); YYABORT; }  }
#line 2678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 267 "parser.y" /* yacc.c:1646  */
    { if (!do_break_continue(BREAK)) { check_error(); YYABORT; } }
#line 2684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 270 "parser.y" /* yacc.c:1646  */
    { if (!do_break_continue(CONTINUE)) { check_error(); YYABORT; } }
#line 2690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 273 "parser.y" /* yacc.c:1646  */
    {
                  dcl_set();
                  state.token_stack.push((yyvsp[0].classptr)->constructor_name());
                  tpush(t_void);
                  state.in_construct_destruct = IsConstructor;
                  (yyval.classptr) = (yyvsp[0].classptr);
                }
#line 2702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 281 "parser.y" /* yacc.c:1646  */
    {}
#line 2708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 283 "parser.y" /* yacc.c:1646  */
    {
                      state.token_stack.TOS() = (yyvsp[0].classptr)->destructor_name();
                      state.in_construct_destruct = IsDestructor;
                    }
#line 2717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 289 "parser.y" /* yacc.c:1646  */
    {
                       state.token_stack.push(CONVERSION_OPNAME);
                       ttpush((yyvsp[-1].ctype)); (yyval.ctype) = (yyvsp[-1].ctype);
                     }
#line 2726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 295 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype)=(yyvsp[-3].ctype); stots((yyval.ctype)); state.member_is_const = (yyvsp[-1].val); gFunInit = (yyvsp[0].expression); }
#line 2732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 297 "parser.y" /* yacc.c:1646  */
    { state.modifier = Explicit; }
#line 2738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 300 "parser.y" /* yacc.c:1646  */
    {
                 state.declare_function(t_void,state.token_stack.pop());
                 tpop();
                 check_error();
               }
#line 2748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 307 "parser.y" /* yacc.c:1646  */
    {
                        state.declare_function(AsType((yyvsp[-1].ctype)),state.token_stack.pop(), gFunInit);
                        dcl_reset();
                        gFunInit = NULL;
                        tpop();
                        check_error();
                      }
#line 2760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 317 "parser.y" /* yacc.c:1646  */
    {
                        state.declare_function(AsType((yyvsp[-1].ctype)),state.token_stack.pop());
                        tpop();
                        check_error();
                      }
#line 2770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 327 "parser.y" /* yacc.c:1646  */
    { state.extern_flag = false; }
#line 2776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 328 "parser.y" /* yacc.c:1646  */
    { state.extern_flag_C = false; }
#line 2782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 329 "parser.y" /* yacc.c:1646  */
    { state.extern_flag_C = false; }
#line 2788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 334 "parser.y" /* yacc.c:1646  */
    { state.extern_flag_C = true; }
#line 2794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 336 "parser.y" /* yacc.c:1646  */
    { state.extern_flag = true; }
#line 2800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 339 "parser.y" /* yacc.c:1646  */
    { }
#line 2806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 340 "parser.y" /* yacc.c:1646  */
    {}
#line 2812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 341 "parser.y" /* yacc.c:1646  */
    {}
#line 2818 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 342 "parser.y" /* yacc.c:1646  */
    {}
#line 2824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 350 "parser.y" /* yacc.c:1646  */
    {   state.init_block(CONSTRUCTOR_BLOCK);  }
#line 2830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 351 "parser.y" /* yacc.c:1646  */
    {  check_error(); state.in_method = true; }
#line 2836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 359 "parser.y" /* yacc.c:1646  */
    {
                   ((Class*)state.context().parent_context())
                     ->add_class_init_list(AsType((yyvsp[-1].ctype)).as_class()->entry(),(yyvsp[0].elist));
                   /* fix 1.2.3a Can crash UC if we don't catch errors in the init list */
                   if (check_error()) YYABORT;
                 }
#line 2847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 366 "parser.y" /* yacc.c:1646  */
    { ((Class*)state.context().parent_context())
                     ->add_class_init_list((yyvsp[-1].entry),(yyvsp[0].elist));
                   if (check_error()) YYABORT;
                 }
#line 2856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 371 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[0].ctype);  }
#line 2862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 373 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.ctype)=(yyvsp[0].ctype); state.token_stack.pop(); tpop(); }
#line 2868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 375 "parser.y" /* yacc.c:1646  */
    { (yyval.val)=0; }
#line 2874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 376 "parser.y" /* yacc.c:1646  */
    { (yyval.val)=1; }
#line 2880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 378 "parser.y" /* yacc.c:1646  */
    {dcl_set();}
#line 2886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 379 "parser.y" /* yacc.c:1646  */
    {dcl_set();}
#line 2892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 380 "parser.y" /* yacc.c:1646  */
    {dcl_set(); tots().make_const();}
#line 2898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 381 "parser.y" /* yacc.c:1646  */
    {dcl_set(); tots().make_const();}
#line 2904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 383 "parser.y" /* yacc.c:1646  */
    {state.modifier = Static;  }
#line 2910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 384 "parser.y" /* yacc.c:1646  */
    {state.modifier = Virtual; }
#line 2916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 385 "parser.y" /* yacc.c:1646  */
    {state.modifier = Stdcall; }
#line 2922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 386 "parser.y" /* yacc.c:1646  */
    {state.modifier = Api;     }
#line 2928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 388 "parser.y" /* yacc.c:1646  */
    {dcl_set(false);}
#line 2934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 390 "parser.y" /* yacc.c:1646  */
    {dcl_reset();}
#line 2940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 392 "parser.y" /* yacc.c:1646  */
    { ttpush((yyvsp[0].ctype));  }
#line 2946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 393 "parser.y" /* yacc.c:1646  */
    { tpush(typeof_op((yyvsp[-1].expression))); }
#line 2952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 394 "parser.y" /* yacc.c:1646  */
    { }
#line 2958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 395 "parser.y" /* yacc.c:1646  */
    { tots().make_unsigned(); }
#line 2964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 396 "parser.y" /* yacc.c:1646  */
    { tpush(t_int); tots().make_unsigned(); }
#line 2970 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 397 "parser.y" /* yacc.c:1646  */
    { tpush(t_float);  }
#line 2976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 398 "parser.y" /* yacc.c:1646  */
    { tpush(t_double); }
#line 2982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 399 "parser.y" /* yacc.c:1646  */
    { tpush(t_bool); }
#line 2988 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 400 "parser.y" /* yacc.c:1646  */
    { tpush(t_void); }
#line 2994 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 401 "parser.y" /* yacc.c:1646  */
    { }
#line 3000 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 402 "parser.y" /* yacc.c:1646  */
    { }
#line 3006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 410 "parser.y" /* yacc.c:1646  */
    { tpush(t_int);   }
#line 3012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 411 "parser.y" /* yacc.c:1646  */
    { tpush(t_short); }
#line 3018 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 412 "parser.y" /* yacc.c:1646  */
    { tpush(t_long);  }
#line 3024 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 417 "parser.y" /* yacc.c:1646  */
    { tpush(t_char);  }
#line 3030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 419 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = incr_ptr((yyvsp[-1].ctype)); }
#line 3036 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 421 "parser.y" /* yacc.c:1646  */
    {dcl_set(false);}
#line 3042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 423 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.expression) = (yyvsp[-1].expression); }
#line 3048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 426 "parser.y" /* yacc.c:1646  */
    {
             (yyval.ctype)=ttots();
             state.token_stack.push("");
           }
#line 3057 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 430 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype)=(yyvsp[0].ctype);   }
#line 3063 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 432 "parser.y" /* yacc.c:1646  */
    {
              Type t = AsType((yyvsp[-1].ctype));
              t.decr_pointer();
              (yyval.ctype) = AsTType(state.signature_type(t));
            }
#line 3073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 439 "parser.y" /* yacc.c:1646  */
    {
             state.class_dcl = AsType((yyvsp[-5].ctype));
             (yyval.ctype) = AsTType(state.signature_type(AsType((yyvsp[-3].ctype))));
           }
#line 3082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 443 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = incr_ptr((yyvsp[0].ctype));         }
#line 3088 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 444 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = make_ref((yyvsp[0].ctype));         }
#line 3094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 445 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[-1].ctype);   state.class_dcl = AsType((yyvsp[-2].ctype)); }
#line 3100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 446 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[-1].ctype);   state.class_dcl = AsType((yyvsp[-2].ctype)); }
#line 3106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 447 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = make_array((yyvsp[-1].ctype),(yyvsp[0].expression)); check_error();   }
#line 3112 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 448 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = make_array((yyvsp[-1].ctype),(yyvsp[0].expression)); check_error();   }
#line 3118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 449 "parser.y" /* yacc.c:1646  */
    { raise_error("Error in type expression"); YYABORT; }
#line 3124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 452 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = ttots(); }
#line 3130 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 453 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = incr_ptr((yyvsp[0].ctype)); }
#line 3136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 454 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = make_ref((yyvsp[0].ctype)); }
#line 3142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 456 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype)=ttots(); state.token_stack.push((yyvsp[0].str)); }
#line 3148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 459 "parser.y" /* yacc.c:1646  */
    { dcl_set(false); state.begin_args(); }
#line 3154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 461 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); }
#line 3160 "y.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 468 "parser.y" /* yacc.c:1646  */
    { state.add_to_arg_list(t_void,"...",0); }
#line 3166 "y.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 471 "parser.y" /* yacc.c:1646  */
    {
                  state.add_to_arg_list(AsType((yyvsp[-1].ctype)),state.token_stack.pop(),(yyvsp[0].expression));
                  tpop();
                  dcl_reset();
                }
#line 3176 "y.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 478 "parser.y" /* yacc.c:1646  */
    {
                   string name = state.token_stack.pop();
                   Type t = AsType((yyvsp[-1].ctype));
                   temp_context()->reserved_space(t.size());
                   state.add_variable(t,name,(yyvsp[0].expression),state.modifier);
                   if (check_error()) YYABORT;
                 }
#line 3188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 490 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=NULL; }
#line 3194 "y.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 491 "parser.y" /* yacc.c:1646  */
    {(yyval.expression)=(yyvsp[0].expression);}
#line 3200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 497 "parser.y" /* yacc.c:1646  */
    { dcl_set(false); }
#line 3206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 499 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=NULL; }
#line 3212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 500 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.expression)=(yyvsp[0].expression); }
#line 3218 "y.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 501 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=expr_list_op((yyvsp[0].elist),true); }
#line 3224 "y.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 502 "parser.y" /* yacc.c:1646  */
    { enter_arglist();}
#line 3230 "y.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 504 "parser.y" /* yacc.c:1646  */
    {leave_arglist(); dcl_reset(); (yyval.expression)=expr_list_op((yyvsp[-1].elist),false); }
#line 3236 "y.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 505 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new Expr(ECONST,t_void,(yyvsp[0].entry),NULL); }
#line 3242 "y.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 509 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = (yyvsp[-1].elist); }
#line 3248 "y.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 511 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 3254 "y.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 512 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_list_op((yyvsp[0].elist),false); }
#line 3260 "y.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 514 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = new ExprList; (yyval.elist)->push_back((yyvsp[0].expression));  }
#line 3266 "y.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 515 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = (yyvsp[-2].elist); (yyval.elist)->push_back((yyvsp[0].expression)); }
#line 3272 "y.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 521 "parser.y" /* yacc.c:1646  */
    {(yyval.val)=Public;}
#line 3278 "y.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 522 "parser.y" /* yacc.c:1646  */
    {(yyval.val)=Private;}
#line 3284 "y.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 523 "parser.y" /* yacc.c:1646  */
    {(yyval.val)=Protected;}
#line 3290 "y.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 525 "parser.y" /* yacc.c:1646  */
    { (yyval.val)=Default; }
#line 3296 "y.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 530 "parser.y" /* yacc.c:1646  */
    { (yyval.val) = CLASS; }
#line 3302 "y.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 531 "parser.y" /* yacc.c:1646  */
    { (yyval.val) = STRUCT; }
#line 3308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 532 "parser.y" /* yacc.c:1646  */
    { (yyval.val) = UNION;  }
#line 3314 "y.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 534 "parser.y" /* yacc.c:1646  */
    { (yyval.val)=NotDerived; }
#line 3320 "y.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 536 "parser.y" /* yacc.c:1646  */
    { (yyval.val)=(yyvsp[-1].val); state.class_dcl = AsType((yyvsp[0].ctype)); }
#line 3326 "y.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 538 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str);  }
#line 3332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 539 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].entry)->name.c_str(); }
#line 3338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 541 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = "";   }
#line 3344 "y.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 542 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str);   }
#line 3350 "y.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 544 "parser.y" /* yacc.c:1646  */
    {
              PClass pc = AsType((yyvsp[0].ctype)).as_class();
              (yyval.str) = pc->name().c_str();
            }
#line 3359 "y.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 548 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].entry)->name.c_str(); }
#line 3365 "y.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 550 "parser.y" /* yacc.c:1646  */
    { dcl_set();}
#line 3371 "y.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 550 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.str) = (yyvsp[0].str);  }
#line 3377 "y.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 555 "parser.y" /* yacc.c:1646  */
    {
                     tpush(state.add_class((yyvsp[-3].val),(yyvsp[-2].str),(yyvsp[-1].val),state.class_dcl));
                     if (check_error()) YYABORT;
                     state.init_block(CLASS_BLOCK); IEF_set();
                     typedef_stack.push(state.in_typedef);
                     state.in_typedef = false;
                   }
#line 3389 "y.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 563 "parser.y" /* yacc.c:1646  */
    {
                     state.finalize_block(); IEF_reset();
                     state.in_typedef = typedef_stack.pop();
                   }
#line 3398 "y.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 568 "parser.y" /* yacc.c:1646  */
    { tpush(state.add_class((yyvsp[-1].val),(yyvsp[0].str),ForwardClass,t_void)); }
#line 3404 "y.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 570 "parser.y" /* yacc.c:1646  */
    { state.set_access_mode((yyvsp[-1].val)); }
#line 3410 "y.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 572 "parser.y" /* yacc.c:1646  */
    { state.in_friend_dcl = true; }
#line 3416 "y.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 573 "parser.y" /* yacc.c:1646  */
    { state.add_friend_class((yyvsp[-2].val)); }
#line 3422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 580 "parser.y" /* yacc.c:1646  */
    { dcl_set(); }
#line 3428 "y.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 581 "parser.y" /* yacc.c:1646  */
    {
             tpush(state.do_enum(tag_name));
             if (check_error()) YYABORT;
           }
#line 3437 "y.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 585 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); }
#line 3443 "y.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 590 "parser.y" /* yacc.c:1646  */
    {(yyval.str)=NULL; tag_name="";}
#line 3449 "y.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 591 "parser.y" /* yacc.c:1646  */
    {(yyval.str)=(yyvsp[0].str); tag_name=(yyvsp[0].str);}
#line 3455 "y.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 592 "parser.y" /* yacc.c:1646  */
    {(yyval.str)=""; tag_name=(yyvsp[0].entry)->name.c_str();}
#line 3461 "y.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 595 "parser.y" /* yacc.c:1646  */
    {
             state.add_enum(tots(),(yyvsp[-1].str),(yyvsp[0].expression));
           }
#line 3469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 605 "parser.y" /* yacc.c:1646  */
    { dcl_set(); }
#line 3475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 606 "parser.y" /* yacc.c:1646  */
    { dcl_reset();
                         state.add_namespace((yyvsp[0].str) ? (yyvsp[0].str) : "");
                         state.in_class = true;
                         if (check_error()) YYABORT;
                       }
#line 3485 "y.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 613 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = NULL; }
#line 3491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 614 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str);  }
#line 3497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 618 "parser.y" /* yacc.c:1646  */
    {
                   if ((Namespace *)(yyvsp[-1].entry)->data != &state.context())
                     state.context().inject_namespace((Namespace *)(yyvsp[-1].entry)->data);
                   else raise_error("Cannot inject a namespace into itself");
                   if (check_error()) YYABORT;
                 }
#line 3508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 625 "parser.y" /* yacc.c:1646  */
    {  state.context().inject_entry((yyvsp[-1].entry));  }
#line 3514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 626 "parser.y" /* yacc.c:1646  */
    { state.context().inject_entry((yyvsp[-1].entry)); }
#line 3520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 627 "parser.y" /* yacc.c:1646  */
    { state.context().inject_entry(last_type_entry);  }
#line 3526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 629 "parser.y" /* yacc.c:1646  */
    { dcl_set(true); }
#line 3532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 629 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); }
#line 3538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 629 "parser.y" /* yacc.c:1646  */
    { do_goto((yyvsp[-2].str)); }
#line 3544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 631 "parser.y" /* yacc.c:1646  */
    { goto_label_new((yyvsp[-1].str)); }
#line 3550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 632 "parser.y" /* yacc.c:1646  */
    { goto_label_existing((yyvsp[-1].entry)); }
#line 3556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 635 "parser.y" /* yacc.c:1646  */
    { state.begin_scope(AsType((yyvsp[-1].ctype))); (yyval.ctype) = (yyvsp[-1].ctype); }
#line 3562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 637 "parser.y" /* yacc.c:1646  */
    { state.begin_scope(&global()); }
#line 3568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 639 "parser.y" /* yacc.c:1646  */
    { state.end_scope(); }
#line 3574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 642 "parser.y" /* yacc.c:1646  */
    { (yyval.entry) = (yyvsp[-1].entry); }
#line 3580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 643 "parser.y" /* yacc.c:1646  */
    { (yyval.entry) = (yyvsp[-1].entry); }
#line 3586 "y.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 645 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = NULL; }
#line 3592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 646 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[-1].expression); }
#line 3598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 650 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype)=(yyvsp[-1].ctype); }
#line 3604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 653 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_if_op((yyvsp[-4].expression),(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 656 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(STAR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 657 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(DIVIDE,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 658 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(MODULO,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 659 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(PLUS,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 660 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(MINUS,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 661 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(BIN_AND,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 662 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(BIN_OR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 664 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(LESS_THAN,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 665 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(GREATER,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 666 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(LEQ,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 667 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(GEQ,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 668 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=equal_op((yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 669 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(NOT_EQUAL,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 670 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(LOG_AND,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 671 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(LOG_OR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 673 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=bin_op(LSHIFT,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 674 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=bin_op(RSHIFT,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 675 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=bin_op(BIN_AND,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 676 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=bin_op(BIN_XOR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 680 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = typecast_op(REINTERPRET_CAST,AsType((yyvsp[-2].ctype)),(yyvsp[0].expression)); }
#line 3730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 683 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = inc_dec_op(INCR,(yyvsp[0].expression),false); }
#line 3736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 684 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = inc_dec_op(DECR,(yyvsp[0].expression),false); }
#line 3742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 685 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 3748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 686 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = unary_op(UMINUS,(yyvsp[0].expression)); }
#line 3754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 687 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = relational_op(LOG_NOT,(yyvsp[0].expression),NULL); }
#line 3760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 688 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = deref_op((yyvsp[0].expression)); }
#line 3766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 689 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = addr_op((yyvsp[0].expression)); }
#line 3772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 690 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = unary_op(BIN_NOT,(yyvsp[0].expression)); }
#line 3778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 691 "parser.y" /* yacc.c:1646  */
    {
                                              if ((yyvsp[-1].expression)->is_entry()) (yyval.expression) = sizeof_op(size_of_entry((yyvsp[-1].expression)->entry()));
                                              else  (yyval.expression) = sizeof_op((yyvsp[-1].expression)->type().size());
                                            }
#line 3787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 695 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=sizeof_op(AsType((yyvsp[-1].ctype)).size());  }
#line 3793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 696 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new_op(tpop(),(yyvsp[0].expression),NULL);  }
#line 3799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 697 "parser.y" /* yacc.c:1646  */
    { tpush((yyvsp[0].entry)->type); }
#line 3805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 698 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new_op(tpop(),NULL,(yyvsp[0].elist));  }
#line 3811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 699 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new_op(tpop(),NULL,(yyvsp[0].elist));  }
#line 3817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 700 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = delete_op((yyvsp[0].expression),(yyvsp[-1].val)==1); }
#line 3823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 703 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = array_op((yyvsp[-3].expression), (yyvsp[-1].expression)); }
#line 3829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 704 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = inc_dec_op(INCR,(yyvsp[-1].expression),true); }
#line 3835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 705 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = inc_dec_op(DECR,(yyvsp[-1].expression),true); }
#line 3841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 707 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = function_cast_op((yyvsp[-1].entry)->type /*AsType($1)*/,(yyvsp[0].elist)); }
#line 3847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 708 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = function_op((yyvsp[-1].expression),(yyvsp[0].elist)); }
#line 3853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 709 "parser.y" /* yacc.c:1646  */
    {dcl_set(); }
#line 3859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 710 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.expression) = selection_op((yyvsp[-3].expression),(yyvsp[0].str),false);  }
#line 3865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 711 "parser.y" /* yacc.c:1646  */
    {dcl_set();}
#line 3871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 712 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.expression) = selection_op((yyvsp[-3].expression),(yyvsp[0].str),true);  }
#line 3877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 713 "parser.y" /* yacc.c:1646  */
    {dcl_set();}
#line 3883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 714 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.expression) = selection_op((yyvsp[-3].expression),(yyvsp[0].str),true,true);  }
#line 3889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 715 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = typecast_op((yyvsp[-4].val),AsType((yyvsp[-3].ctype)),(yyvsp[-1].expression)); }
#line 3895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 717 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = entry_op((yyvsp[0].entry)); }
#line 3901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 719 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[-1].expression); }
#line 3907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 720 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = entry_op((yyvsp[0].entry)); }
#line 3913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 721 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = lambda_op(0); }
#line 3919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 724 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = bin_op(COMMA,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 725 "parser.y" /* yacc.c:1646  */
    { raise_error("error in expression"); YYABORT; }
#line 3931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 727 "parser.y" /* yacc.c:1646  */
    { if (check_error()) YYABORT;   (yyval.expression) = (yyvsp[0].expression); }
#line 3937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 730 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = assign_op((yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 731 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = compound_assign_op((yyvsp[-1].val),(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 737 "parser.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 3955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 738 "parser.y" /* yacc.c:1646  */
    { (yyval.val) = 1; }
#line 3961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 743 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = new ExprList; }
#line 3967 "y.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 744 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = (yyvsp[0].elist); }
#line 3973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 746 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = (yyvsp[-1].elist); }
#line 3979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 748 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = new ExprList; (yyval.elist)->push_back((yyvsp[0].expression));  }
#line 3985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 749 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = (yyvsp[-2].elist); (yyval.elist)->push_back((yyvsp[0].expression)); }
#line 3991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 750 "parser.y" /* yacc.c:1646  */
    { raise_error("Error in arg list"); YYABORT; }
#line 3997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 754 "parser.y" /* yacc.c:1646  */
    { do_end_try_catch_block(true); }
#line 4003 "y.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 756 "parser.y" /* yacc.c:1646  */
    { state.init_block(PLAIN_BLOCK); IEF_set();
                 do_start_try_block();  }
#line 4010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 761 "parser.y" /* yacc.c:1646  */
    { state.finalize_block(); IEF_reset();
                do_end_try_catch_block(false);   }
#line 4017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 765 "parser.y" /* yacc.c:1646  */
    { state.init_block(PLAIN_BLOCK); IEF_set();
               do_start_catch_block(); if (check_error()) YYABORT; }
#line 4024 "y.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 772 "parser.y" /* yacc.c:1646  */
    { do_throw((yyvsp[-1].expression)); }
#line 4030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 775 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = AsTType((yyvsp[0].entry)->type); }
#line 4036 "y.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 776 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 779 "parser.y" /* yacc.c:1646  */
    { last_type_entry = (yyvsp[0].entry); (yyval.ctype) = AsTType((yyvsp[0].entry)->type); }
#line 4048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 780 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 781 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[-1].ctype); }
#line 4060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 784 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = AsTType((yyvsp[0].entry)->type); }
#line 4066 "y.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 785 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4072 "y.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 786 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[-1].ctype); }
#line 4078 "y.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 789 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = AsTType(Template::get_template_type((yyvsp[-1].entry),(yyvsp[0].typelist))); }
#line 4084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 792 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = AsTType(Template::get_template_type((yyvsp[-1].entry),(yyvsp[0].typelist))); }
#line 4090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 795 "parser.y" /* yacc.c:1646  */
    { Template::do_template_header((yyvsp[0].typelist)); }
#line 4096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 798 "parser.y" /* yacc.c:1646  */
    { Template::do_function_template();
                                 if (yychar != YYEMPTY) yyclearin;
                               }
#line 4104 "y.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 803 "parser.y" /* yacc.c:1646  */
    {
                              dcl_reset();
                              Template::do_class_template((yyvsp[-1].val),(yyvsp[0].str),yychar,NULL);
                              if (yychar != YYEMPTY) yyclearin;
                            }
#line 4114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 809 "parser.y" /* yacc.c:1646  */
    {
                              dcl_reset();
                              Template::do_class_template((yyvsp[-2].val),(yyvsp[-1].str),yychar,(yyvsp[0].typelist));
                              if (yychar != YYEMPTY) yyclearin;
                            }
#line 4124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 817 "parser.y" /* yacc.c:1646  */
    { dcl_set(); (yyval.val) = (yyvsp[0].val); }
#line 4130 "y.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 819 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str);                     }
#line 4136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 820 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].entry)->name.c_str();      }
#line 4142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 823 "parser.y" /* yacc.c:1646  */
    { dcl_set(true); state.begin_templ_list(); }
#line 4148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 825 "parser.y" /* yacc.c:1646  */
    { dcl_reset();   state.end_templ_list();   }
#line 4154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 827 "parser.y" /* yacc.c:1646  */
    { (yyval.typelist) = new TypeList; }
#line 4160 "y.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 828 "parser.y" /* yacc.c:1646  */
    { (yyval.typelist) = (yyvsp[-1].typelist); }
#line 4166 "y.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 831 "parser.y" /* yacc.c:1646  */
    { (yyval.typelist) = new TypeList; (yyval.typelist)->push_back(AsType((yyvsp[0].ctype))); }
#line 4172 "y.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 832 "parser.y" /* yacc.c:1646  */
    { (yyval.typelist) = (yyvsp[-2].typelist); (yyval.typelist)->push_back(AsType((yyvsp[0].ctype)));   }
#line 4178 "y.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 834 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str); }
#line 4184 "y.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 835 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].entry)->name.c_str(); }
#line 4190 "y.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 837 "parser.y" /* yacc.c:1646  */
    {
              string c = (yyvsp[0].str);
              (yyval.ctype) = AsTType(Template::dummy(t_null,c));
            }
#line 4199 "y.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 843 "parser.y" /* yacc.c:1646  */
    {
              (yyval.ctype) = AsTType(Template::dummy(AsType((yyvsp[0].ctype)),state.token_stack.pop()));
              dcl_reset();  tpop();
            }
#line 4208 "y.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 847 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = AsTType(Template::dummy((yyvsp[0].entry))); }
#line 4214 "y.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 848 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4220 "y.tab.c" /* yacc.c:1646  */
    break;


#line 4224 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}
#line 850 "parser.y" /* yacc.c:1906  */

