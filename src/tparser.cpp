
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 9 "parser.y"

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



/* Line 189 of yacc.c  */
#line 157 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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

/* Line 214 of yacc.c  */
#line 92 "parser.y"

  int    val; 
  long   ctype;
  char*  str;
  Entry* entry;
  Expr*  expression;
  ExprList *elist;
  Class *classptr;
  TypeList *typelist;



/* Line 214 of yacc.c  */
#line 444 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 456 "y.tab.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  212
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3384

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  129
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  155
/* YYNRULES -- Number of rules.  */
#define YYNRULES  357
/* YYNRULES -- Number of states.  */
#define YYNSTATES  573

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   374

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    12,    17,    19,
      21,    23,    25,    27,    29,    32,    34,    36,    38,    40,
      42,    44,    46,    48,    50,    52,    54,    56,    58,    60,
      62,    64,    66,    68,    70,    72,    74,    76,    79,    83,
      84,    88,    90,    92,    94,    96,    99,   104,   110,   112,
     116,   119,   121,   124,   127,   130,   135,   138,   140,   142,
     145,   147,   150,   152,   155,   158,   163,   164,   165,   169,
     171,   173,   177,   180,   183,   186,   187,   189,   191,   194,
     197,   201,   203,   205,   207,   209,   211,   213,   215,   220,
     222,   225,   227,   229,   231,   233,   235,   237,   239,   241,
     243,   245,   247,   252,   253,   258,   259,   261,   264,   272,
     276,   279,   283,   287,   290,   293,   295,   296,   299,   302,
     304,   306,   308,   312,   313,   315,   319,   321,   324,   327,
     328,   330,   334,   335,   337,   339,   340,   343,   345,   346,
     352,   355,   359,   361,   363,   365,   369,   371,   373,   375,
     376,   378,   380,   382,   384,   386,   388,   390,   391,   395,
     397,   399,   400,   402,   404,   406,   407,   410,   411,   419,
     422,   425,   426,   430,   435,   436,   437,   443,   444,   448,
     449,   451,   453,   456,   457,   459,   463,   464,   465,   471,
     472,   474,   479,   483,   488,   492,   493,   494,   500,   503,
     506,   509,   511,   512,   514,   516,   518,   520,   522,   524,
     526,   528,   530,   532,   534,   538,   542,   544,   545,   549,
     551,   553,   555,   557,   559,   563,   565,   567,   571,   575,
     579,   583,   587,   591,   595,   599,   602,   605,   608,   612,
     616,   620,   624,   628,   632,   636,   640,   644,   648,   651,
     654,   657,   660,   665,   670,   676,   680,   684,   685,   690,
     694,   698,   701,   704,   710,   713,   718,   721,   725,   729,
     733,   737,   741,   746,   749,   750,   755,   756,   761,   762,
     767,   770,   772,   773,   776,   779,   781,   785,   787,   791,
     793,   797,   798,   800,   801,   804,   807,   810,   811,   817,
     818,   819,   825,   826,   832,   834,   837,   839,   840,   841,
     842,   854,   855,   862,   866,   870,   873,   876,   879,   882,
     883,   887,   891,   892,   897,   899,   902,   906,   908,   910,
     912,   914,   918,   920,   922,   926,   929,   932,   935,   938,
     941,   945,   947,   949,   952,   954,   956,   958,   960,   963,
     967,   969,   973,   976,   979,   981,   983,   985
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     130,     0,    -1,   131,    -1,    -1,   134,    -1,   131,   134,
      -1,    -1,   120,   133,   131,   121,    -1,   122,    -1,   132,
      -1,   135,    -1,   145,    -1,   150,    -1,   196,    -1,   220,
     122,    -1,   136,    -1,   195,    -1,   239,    -1,   240,    -1,
     242,    -1,   245,    -1,   248,    -1,   252,    -1,   254,    -1,
     255,    -1,   256,    -1,   257,    -1,   211,    -1,   214,    -1,
     273,    -1,   272,    -1,   258,    -1,   265,    -1,   205,    -1,
     209,    -1,   210,    -1,   146,    -1,     1,   122,    -1,   158,
     176,   122,    -1,    -1,    20,   137,   138,    -1,   135,    -1,
     145,    -1,    10,    -1,   139,    -1,   104,   139,    -1,    24,
     158,   168,   172,    -1,   158,   167,   172,   157,   179,    -1,
      56,    -1,   140,   172,   122,    -1,   142,   122,    -1,   144,
      -1,   143,   144,    -1,   141,   122,    -1,   149,   147,    -1,
     148,   120,   131,   121,    -1,   148,   147,    -1,   145,    -1,
     135,    -1,    53,     5,    -1,    53,    -1,   142,   132,    -1,
     151,    -1,   143,   151,    -1,   141,   132,    -1,   140,   172,
     152,   132,    -1,    -1,    -1,   123,   153,   154,    -1,    59,
      -1,   155,    -1,   155,    68,   154,    -1,   266,   231,    -1,
       4,   231,    -1,   158,   167,    -1,    -1,    60,    -1,   162,
      -1,   159,   162,    -1,    60,   162,    -1,   159,    60,   162,
      -1,    61,    -1,    64,    -1,    62,    -1,    63,    -1,   124,
      -1,   125,    -1,   267,    -1,    55,   160,   220,   161,    -1,
     163,    -1,    13,   163,    -1,    13,    -1,    11,    -1,    12,
      -1,    19,    -1,    18,    -1,   193,    -1,   198,    -1,    14,
      -1,    15,    -1,    16,    -1,    17,    -1,   124,    98,   169,
     125,    -1,    -1,   126,   166,   177,   127,    -1,    -1,   169,
      -1,   164,   172,    -1,   124,   215,    98,   169,   125,   217,
     172,    -1,    98,   157,   167,    -1,   108,   167,    -1,   215,
     169,   217,    -1,   215,   141,   217,    -1,   167,   165,    -1,
     164,   165,    -1,     1,    -1,    -1,    98,   168,    -1,   108,
     168,    -1,     3,    -1,   124,    -1,   125,    -1,   170,   173,
     171,    -1,    -1,   174,    -1,   174,   128,   173,    -1,    54,
      -1,   156,   179,    -1,   167,   179,    -1,    -1,   175,    -1,
     175,   128,   176,    -1,    -1,   220,    -1,    79,    -1,    -1,
     178,   220,    -1,   232,    -1,    -1,   178,   120,   180,   183,
     121,    -1,   123,     5,    -1,   120,   183,   121,    -1,   225,
      -1,   181,    -1,   182,    -1,   183,   128,   182,    -1,    67,
      -1,    65,    -1,    66,    -1,    -1,   184,    -1,    21,    -1,
      22,    -1,    26,    -1,    34,    -1,    33,    -1,    35,    -1,
      -1,   123,   185,   267,    -1,     3,    -1,     6,    -1,    -1,
     189,    -1,   269,    -1,     8,    -1,    -1,   192,   190,    -1,
      -1,   186,   191,   188,   120,   194,   131,   121,    -1,   187,
     191,    -1,   184,   123,    -1,    -1,    57,   197,   145,    -1,
      57,    21,   190,   122,    -1,    -1,    -1,    23,   199,   202,
     200,   201,    -1,    -1,   120,   204,   121,    -1,    -1,     3,
      -1,     6,    -1,     3,   179,    -1,    -1,   203,    -1,   204,
     128,   203,    -1,    -1,    -1,    47,   206,   208,   207,   132,
      -1,    -1,   190,    -1,    48,    47,     6,   122,    -1,    48,
     219,   122,    -1,    48,   215,     8,   217,    -1,    48,   267,
     122,    -1,    -1,    -1,    25,   212,     3,   213,   122,    -1,
       3,   123,    -1,     4,   123,    -1,   268,   118,    -1,   118,
      -1,    -1,    78,    -1,    77,    -1,    76,    -1,    75,    -1,
      74,    -1,    73,    -1,    72,    -1,    71,    -1,    70,    -1,
      69,    -1,     4,    -1,   215,   219,   217,    -1,   216,     4,
     217,    -1,   225,    -1,    -1,   126,   225,   127,    -1,   156,
      -1,    27,    -1,    28,    -1,    29,    -1,    30,    -1,    91,
     222,    89,    -1,     5,    -1,   219,    -1,   124,   225,   125,
      -1,   225,    98,   225,    -1,   225,    97,   225,    -1,   225,
      96,   225,    -1,   225,    95,   225,    -1,   225,    94,   225,
      -1,   225,    85,   225,    -1,   225,    83,   225,    -1,    95,
     225,    -1,    94,   225,    -1,   105,   225,    -1,   225,    91,
     225,    -1,   225,    89,   225,    -1,   225,    90,   225,    -1,
     225,    88,   225,    -1,   225,    87,   225,    -1,   225,    86,
     225,    -1,   225,    82,   225,    -1,   225,    81,   225,    -1,
     225,    79,   225,    -1,   225,   218,   225,    -1,   225,   103,
      -1,   103,   225,    -1,   225,   102,    -1,   102,   225,    -1,
     101,   124,   225,   125,    -1,   101,   124,   222,   125,    -1,
     225,    80,   225,   123,   225,    -1,   225,    68,   225,    -1,
     112,   162,   221,    -1,    -1,   112,     7,   226,   231,    -1,
     112,   162,   231,    -1,   111,   230,   225,    -1,    98,   225,
      -1,   108,   225,    -1,   223,   224,   124,   225,   125,    -1,
       7,   231,    -1,   124,   222,   125,   225,    -1,   104,   225,
      -1,   225,    93,   225,    -1,   225,    92,   225,    -1,   225,
     108,   225,    -1,   225,    84,   225,    -1,   225,   108,   225,
      -1,   225,   126,   225,   127,    -1,   225,   231,    -1,    -1,
     225,   113,   227,     3,    -1,    -1,   225,   114,   228,     3,
      -1,    -1,   225,   100,   229,     3,    -1,    58,   150,    -1,
       1,    -1,    -1,   126,   127,    -1,   124,   125,    -1,   232,
      -1,   170,   233,   171,    -1,   225,    -1,   233,   128,   225,
      -1,     1,    -1,   124,   220,   125,    -1,    -1,   220,    -1,
      -1,   237,   134,    -1,    36,   234,    -1,   238,   236,    -1,
      -1,   238,   236,    37,   241,   236,    -1,    -1,    -1,    38,
     243,   234,   244,   236,    -1,    -1,    39,   246,   236,    38,
     234,    -1,   122,    -1,   220,   122,    -1,   135,    -1,    -1,
      -1,    -1,    40,   124,   249,   247,   250,   235,   122,   235,
     125,   251,   236,    -1,    -1,    41,   124,   220,   125,   253,
     132,    -1,    43,   235,   122,    -1,    42,   220,   123,    -1,
      46,   123,    -1,    45,   122,    -1,    44,   122,    -1,   259,
     264,    -1,    -1,    49,   260,   261,    -1,   120,   131,   121,
      -1,    -1,    50,   172,   263,   261,    -1,   262,    -1,   262,
     264,    -1,    51,   235,   122,    -1,     7,    -1,   269,    -1,
       6,    -1,   269,    -1,   215,   267,   217,    -1,     7,    -1,
     270,    -1,   215,   268,   217,    -1,     8,   279,    -1,     9,
     279,    -1,    52,   279,    -1,   271,   142,    -1,   275,   276,
      -1,   275,   276,   279,    -1,    31,    -1,    32,    -1,   271,
     274,    -1,     3,    -1,     8,    -1,    91,    -1,    89,    -1,
     277,   278,    -1,   277,   280,   278,    -1,   283,    -1,   280,
     128,   283,    -1,    21,     3,    -1,    21,     6,    -1,   281,
      -1,   156,    -1,     5,    -1,   282,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   151,   151,   153,   154,   155,   159,   159,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   198,   208,
     207,   214,   215,   220,   231,   232,   240,   248,   252,   257,
     266,   274,   275,   276,   290,   291,   292,   296,   297,   301,
     305,   311,   313,   315,   317,   322,   328,   330,   329,   337,
     338,   339,   343,   352,   361,   365,   366,   370,   371,   372,
     373,   377,   378,   379,   380,   383,   386,   389,   390,   391,
     392,   393,   394,   395,   396,   397,   398,   399,   409,   410,
     411,   416,   420,   424,   424,   429,   430,   431,   432,   435,
     436,   437,   438,   440,   441,   442,   446,   447,   448,   451,
     455,   458,   462,   465,   466,   467,   468,   475,   484,   494,
     495,   496,   499,   500,   506,   509,   510,   514,   517,   517,
     521,   529,   532,   533,   536,   537,   547,   548,   549,   552,
     552,   555,   555,   555,   558,   559,   560,   563,   564,   569,
     570,   573,   574,   575,   579,   582,   582,   589,   588,   604,
     608,   613,   613,   614,   624,   625,   624,   633,   634,   637,
     638,   639,   643,   649,   650,   651,   658,   659,   658,   667,
     668,   672,   683,   685,   687,   693,   693,   693,   698,   699,
     706,   711,   715,   719,   719,   719,   719,   719,   720,   720,
     720,   720,   720,   723,   724,   726,   730,   734,   735,   738,
     742,   742,   742,   742,   745,   751,   752,   753,   755,   756,
     757,   758,   759,   760,   761,   763,   764,   766,   767,   768,
     769,   770,   771,   772,   773,   774,   776,   777,   779,   780,
     781,   782,   786,   790,   791,   792,   793,   796,   796,   799,
     801,   802,   803,   805,   808,   811,   815,   816,   817,   818,
     819,   820,   822,   825,   828,   827,   833,   832,   837,   836,
     842,   845,   848,   849,   856,   857,   861,   867,   868,   869,
     874,   878,   879,   883,   883,   889,   893,   898,   897,   903,
     904,   903,   910,   910,   915,   916,   917,   921,   922,   924,
     921,   931,   931,   935,   940,   942,   946,   950,   957,   963,
     962,   969,   977,   976,   983,   984,   988,   995,   996,  1001,
    1002,  1003,  1008,  1009,  1010,  1014,  1019,  1025,  1030,  1038,
    1044,  1053,  1053,  1057,  1061,  1062,  1066,  1068,  1072,  1073,
    1078,  1079,  1083,  1084,  1088,  1096,  1100,  1101
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN", "IDEN", "CONSTANT", "TYPENAME",
  "TYPENAME_FUNCTION", "TEMPLATE_NAME", "TEMPLATE_NAME_EXPR",
  "THIS_CLASSNAME", "FLOAT", "DOUBLE", "UNSIGNED", "INT", "SHORT", "LONG",
  "CHAR", "VOID", "BOOL", "TYPEDEF", "CLASS", "STRUCT", "ENUM", "OPERATOR",
  "GOTO", "UNION", "STATIC_CAST", "CONST_CAST", "DYNAMIC_CAST",
  "REINTERPRET_CAST", "STRUCT_X", "CLASS_X", "STRUCT_Y", "CLASS_Y",
  "UNION_Y", "IF", "ELSE", "WHILE", "DO", "FOR", "SWITCH", "CASE",
  "RETURN", "CONTINUE", "BREAK", "DEFAULT", "NAMESPACE", "USING", "TRY",
  "CATCH", "THROW", "TEMPLATE", "EXTERN", "THREEDOT", "TYPEOF", "EXPLICIT",
  "FRIEND", "LAMBDA", "FAKE_INIT_LIST", "CONST", "STATIC", "STDCALL",
  "API", "VIRTUAL", "PRIVATE", "PROTECTED", "PUBLIC", "COMMA", "XOR_A",
  "BOR_A", "BAND_A", "SHR_A", "SHL_A", "MINUS_A", "ADD_A", "MOD_A",
  "DIV_A", "MUL_A", "ASSIGN", "ARITH_IF", "LOG_OR", "LOG_AND", "BIN_OR",
  "BIN_XOR", "BIN_AND", "NOT_EQUAL", "EQUAL", "GEQ", "GREATER", "LEQ",
  "LESS_THAN", "RSHIFT", "LSHIFT", "MINUS", "PLUS", "MODULO", "DIVIDE",
  "STAR", "MEMBER_DOT", "MEMBER_ARROW", "SIZEOF", "DECR", "INCR",
  "BIN_NOT", "LOG_NOT", "UMINUS", "UPLUS", "ADDR", "DEREF", "TYPECAST",
  "DELETE", "NEW", "DOT", "ARROW", "ARRAY", "FUN_CALL", "TYPE_CONSTRUCT",
  "BINARY_SCOPE", "UNARY_SCOPE", "'{'", "'}'", "';'", "':'", "'('", "')'",
  "'['", "']'", "','", "$accept", "program", "statement_list", "block",
  "$@1", "statement", "declaration", "typedef_stmt", "$@2",
  "declaration_stmt", "this_classname", "construct_destruct",
  "conversion_operator", "function_front", "explicit_mod", "ctor_dtor_dcl",
  "function_declaration", "extern_c_declaration", "any_declaration",
  "extern_c", "extern_qualifier", "function_definition", "ctor_dtor",
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
  "templ_item_list", "class_item", "class_parm", "templ_item", 0
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
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     123,   125,    59,    58,    40,    41,    91,    93,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
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

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   281,     0,   213,   225,   329,   332,     0,     0,    43,
      92,    93,    91,    98,    99,   100,   101,    95,    94,    39,
     151,   152,   174,     0,   195,   153,   220,   221,   222,   223,
     155,   154,   156,     0,   299,   302,     0,     0,     0,     0,
       0,     0,     0,   186,     0,   319,     0,     0,    60,     0,
      48,   171,     0,     0,    81,    83,    84,    82,   147,   148,
     146,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     282,     0,   201,     6,     8,     0,     0,     0,     9,     4,
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
     280,     0,    79,   236,   235,   261,     0,   251,   249,    45,
     266,   237,   262,     0,     0,   257,   217,     0,   219,     0,
       0,     0,     1,     5,   120,   123,    66,    53,    64,    50,
      61,    52,    63,     0,    58,     0,     0,     0,     0,    57,
      56,    54,   115,   119,    75,     0,     0,     0,   135,   106,
     130,     0,     0,     0,    78,   170,   157,   161,   169,   202,
     202,     0,   202,    14,     0,     0,     0,   212,   211,   210,
     209,   208,   207,   206,   205,   204,   203,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   278,   250,   248,
       0,   274,   276,     0,     0,   273,   296,     0,     0,   324,
     318,   200,   341,   342,   338,   343,   344,   345,   339,   284,
     281,   287,     0,   356,   151,   347,   355,   348,     0,   354,
     357,   350,    41,    40,    42,   180,   181,   175,   116,   116,
       0,   196,     0,   300,     0,     0,     0,   314,   313,   159,
     160,   164,   162,   190,   187,   163,     0,   202,   192,   194,
       0,   320,   326,     0,     0,   172,    66,     0,     0,     0,
     283,   260,     0,     0,   256,   259,     0,    74,     0,   227,
     126,   135,     0,   124,    49,    67,     0,     0,     0,    76,
       0,   110,     0,     0,   103,   114,   107,   134,     0,   113,
       0,    75,     0,   128,   137,     0,    38,   202,   202,     0,
      80,   149,     0,   166,   214,   331,   334,   215,     0,     0,
     255,   246,     0,   245,   244,   234,   270,   233,   243,   242,
     241,   239,   240,   238,   268,   267,   232,   231,   230,   229,
     228,     0,   269,     0,     0,     0,   247,   297,   294,   322,
     325,   340,   121,     0,   286,   352,   353,     0,   349,   177,
     117,   118,    46,     0,   290,   293,     0,   304,   306,     0,
       0,   308,   311,     0,   191,   193,     0,    86,    88,   173,
     253,   252,   258,     0,     7,   265,   127,   122,   123,     0,
      65,    55,   109,     0,     0,     0,   140,   135,   138,   136,
     135,   131,   112,   111,   150,     0,   167,   224,     0,     0,
     279,   275,   277,   272,   293,     0,   288,   351,   183,   176,
     197,   301,   303,   305,     0,     0,   188,   321,   218,   125,
       0,   327,    69,    68,    70,     0,   328,   102,     0,     0,
     133,    47,     0,   158,     0,   263,   254,   298,   323,   135,
     184,     0,     0,   312,    73,     0,    72,   202,   104,     0,
     143,   144,     0,   142,     0,   182,   178,     0,     0,    71,
       0,     0,   139,     0,   168,   185,     0,   108,   141,   145,
     309,   293,   310
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    76,    77,    78,   207,    79,    80,    81,   150,   323,
      82,    83,    84,    85,    86,    87,    88,    89,   230,    90,
      91,    92,    93,   376,   479,   523,   524,   208,   380,    94,
      95,   182,   468,    96,    97,   237,   389,   485,   490,   330,
     239,   142,   444,   391,   372,   373,   240,   241,   529,   392,
     393,   532,   550,   551,   552,    98,   495,    99,   100,   402,
     342,   343,   246,   247,   101,   534,   102,   103,   184,   104,
     151,   449,   509,   327,   540,   541,   105,   172,   463,   344,
     106,   107,   108,   155,   453,   109,   165,   111,   404,   294,
     112,   113,   364,   210,   114,   255,   115,   362,   433,   434,
     431,   204,   295,   144,   312,   157,   168,   296,   297,   116,
     117,   118,   504,   119,   158,   455,   120,   159,   461,   121,
     335,   514,   571,   122,   515,   123,   124,   125,   126,   127,
     128,   177,   351,   299,   505,   300,   129,   525,   130,   131,
     132,   133,   134,   135,   136,   305,   137,   308,   146,   317,
     147,   318,   319,   320,   321
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -346
static const yytype_int16 yypact[] =
{
     660,   -89,   -76,   -65,  -346,  -346,   -73,    20,    20,  -346,
    -346,  -346,   277,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  3144,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,     8,  -346,  -346,    64,    80,  2254,  1962,
      -4,    60,    25,  -346,   193,  -346,  1962,    20,   190,    84,
    -346,   212,  2492,  2136,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  2254,  2254,  2254,    90,  2254,  2254,  2078,  2254,  2254,
     111,  2280,  -346,  -346,  -346,  1924,   238,   785,  -346,  -346,
    -346,  -346,  -346,   117,   112,   131,    11,  -346,  -346,  -346,
    2392,  2492,  -346,  -346,   210,  3261,  -346,  -346,   160,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
      98,   282,  -346,   173,   208,  2905,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,   250,  -346,
    -346,   194,  -346,  -346,  3026,  -346,  -346,   177,  -346,  -346,
    -346,   197,  2366,  -346,  -346,  -346,   561,  -346,  -346,  -346,
    2492,    42,  -346,   -28,   297,   328,  2254,  -346,     8,  -346,
    -346,  2254,  -346,  -346,  2254,    75,   207,  -346,   219,  -346,
    -346,  -346,    95,   340,   240,   226,   227,   232,   231,  -346,
    -346,  -346,  2254,    95,  2492,   344,   117,   236,   236,    11,
    -346,   336,  -346,   489,   489,   489,  1924,   489,   489,  -346,
     489,   489,   489,   243,  2254,   246,   195,  1070,  -346,   366,
     247,  2669,  -346,  -346,  -346,  3085,   -36,  -346,  -346,  -346,
    -346,  -346,  -346,  1070,  -346,   117,   249,   252,    11,  -346,
    -346,  -346,  -346,  -346,   305,   407,    58,   199,   237,  -346,
     248,   256,   215,  2136,  -346,  -346,   259,    95,  -346,  -346,
    -346,   194,  -346,  -346,  3144,   255,  2254,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  2254,  2254,  2254,
    2254,  2254,  2254,  2254,  2254,  2254,  2254,  2254,  2254,  2254,
    2254,  2254,  2254,  2254,  2254,  2254,  2254,  -346,  -346,  -346,
    2254,  -346,  -346,  2254,  2254,  -346,   348,  1680,   117,   250,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,    20,  -346,
    -346,  2905,    24,  -346,   183,  -346,  -346,  -346,   -43,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,   -28,   -28,
     117,  -346,   262,  -346,   350,  1802,   264,  -346,  -346,  -346,
    -346,    20,  -346,  -346,  -346,  -346,   269,    20,  -346,  -346,
    1070,  -346,  -346,   267,   271,  -346,   275,   199,   276,  2728,
    -346,   489,   -73,  2254,  -346,  -346,  1192,   268,  2254,  -346,
    -346,   -11,   279,   272,  -346,  -346,   236,  1314,   280,  -346,
     407,   268,   402,   161,  -346,  -346,  -346,  -346,   401,  -346,
     907,   305,  2110,  -346,  -346,   210,  -346,  -346,  -346,   333,
    -346,   106,   287,  -346,  -346,  -346,  -346,  -346,   320,  2254,
    3140,  3140,  2787,  1785,  3215,  3258,   643,   768,  1053,  1053,
     327,   327,   327,   327,  1175,  1175,   880,   880,   399,   399,
     399,   408,   768,   409,   410,  2489,  2905,  -346,  -346,  -346,
    -346,  -346,  -346,  2254,  -346,  -346,  -346,  2672,  -346,   295,
    -346,  -346,  -346,   304,  -346,  -346,     8,  -346,  -346,   210,
     306,  -346,  -346,   236,  -346,  -346,  1436,  -346,  -346,  -346,
    -346,  -346,  -346,  2549,  -346,   489,  -346,  -346,  3085,   122,
    -346,  -346,   268,   292,   402,   535,  -346,   -11,  -346,  -346,
     237,  -346,  -346,  -346,  -346,   297,  -346,  -346,  2846,  2254,
    -346,  -346,  -346,  -346,  -346,   232,  2905,  -346,   428,  -346,
    -346,  -346,  -346,  -346,  1962,   236,  -346,  -346,  -346,  -346,
     -73,  -346,  -346,  -346,   364,   -73,  -346,  -346,   308,   309,
    -346,  -346,  2222,  -346,  1070,  -346,  2905,  -346,  -346,   -11,
    -346,   -32,   317,  -346,  -346,   122,  -346,  -346,  -346,  2222,
    -346,  -346,    10,  2905,  1558,  -346,  -346,   428,   945,  -346,
     117,    23,  -346,  2222,  -346,  -346,   318,  -346,  -346,  -346,
    -346,  -346,  -346
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -346,  -346,  -187,   -66,  -346,   -70,   -53,  -346,  -346,  -346,
     -50,   140,   -17,    71,    26,   -59,   -41,  -346,   351,  -346,
    -346,   394,   -61,  -346,  -346,   -95,  -346,  -134,    61,    -9,
    -346,  -346,  -346,   -31,   442,  -346,   220,  -346,   -52,  -100,
    -203,   -72,    86,   -78,   -22,  -346,  -346,    68,  -346,  -346,
    -345,  -346,  -346,   -98,   -81,    66,  -346,  -346,  -346,  -346,
    -346,  -154,   370,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,   -86,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,     0,  -346,  -220,  -346,
     -10,   -37,  -346,  -155,  -346,  -346,    -6,  -346,  -346,  -346,
    -346,  -346,    -3,  -230,  -346,  -142,   -42,  -153,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,   -30,  -346,  -346,   174,  -346,  -346,   -34,   -82,
    -159,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,   158,
       7,  -346,  -346,  -346,    32
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -333
static const yytype_int16 yytable[] =
{
     110,   166,   167,   143,   178,   216,   334,   213,   394,   167,
     176,   215,   316,   345,   153,   148,   333,   199,   218,   220,
     366,     9,   192,   154,   345,   222,   476,   221,   251,   354,
     405,   406,   407,   138,   175,   187,   377,   224,   224,   398,
     206,   358,   238,   191,   174,   325,   315,   139,   326,   229,
     229,   141,   154,   154,   179,   193,   194,   195,   140,   197,
     198,   200,   201,   202,   244,   152,   209,     8,   387,   211,
     328,   154,   251,   226,   226,   110,   250,   110,   189,   163,
     329,   371,   152,   251,     8,   447,   374,   375,   345,   556,
     154,   154,   251,   403,   242,   154,   557,   322,   339,   408,
     249,   340,   163,   341,     5,   152,     7,     8,   356,   324,
     110,   145,   388,   214,   215,   185,   228,   228,   169,   332,
     250,   218,   220,   188,   336,   191,   520,   465,   222,   521,
       7,   562,   156,   226,   154,   199,   311,   209,   563,   357,
     250,   394,   531,   355,   568,   353,   154,   378,   171,   442,
     154,   563,   443,   215,   154,   249,   382,   367,   200,   386,
     251,   227,   227,   466,   249,   215,   390,   226,   152,   221,
       8,    58,    59,    60,   110,   191,   228,   492,   493,   483,
     306,   522,   170,   381,   154,   307,   445,   209,   160,   446,
     359,   242,   186,    72,   555,   180,   110,   163,   361,     5,
     152,     7,     8,   365,   161,   304,   209,   110,   181,   242,
     228,   232,   400,   233,   196,   154,    72,   152,   233,     8,
     439,   227,   152,   110,     8,   397,   215,   438,   450,   451,
     225,   225,    73,   183,   217,   242,   383,   203,   212,    23,
     173,   214,   399,   154,   163,   209,     5,   152,   347,     8,
     410,    73,   452,   219,   154,   227,   371,   394,   215,   484,
     394,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   528,   458,   245,   432,   215,   252,   435,   436,  -105,
     225,    13,    14,    15,    16,   253,   213,   110,   460,   254,
     298,   251,   511,     5,   152,     7,     8,   213,   234,   394,
     480,    72,   301,   316,   512,   441,   387,   251,   235,   141,
     526,   363,   309,   214,   225,   384,   459,   560,   482,   186,
     337,   331,  -105,  -105,   236,   110,  -105,   232,  -105,   233,
     152,   338,     8,   152,   371,     8,   346,   554,   348,   349,
     110,   537,   350,   352,     9,   489,    73,   473,    72,   472,
     388,   214,   475,   384,  -332,   379,   110,   232,   225,   233,
     360,   217,   368,   152,   219,     8,   395,   110,   396,   409,
     242,   209,   401,   399,   311,   437,   526,   454,   456,   462,
     110,   464,   467,   469,   384,   242,   213,   516,   375,   399,
     478,   470,   374,   498,   442,   233,   486,   496,   232,   497,
     233,   500,   501,   502,   152,   508,     8,   527,   572,   280,
     281,   282,   283,   284,   285,   286,   510,   287,   513,   288,
     289,   539,   545,   547,   234,   290,   548,   506,   209,   558,
     291,   292,   231,   570,   235,  -105,   190,   154,   530,   543,
     559,   141,   487,   293,   149,  -105,   519,   385,   477,   242,
     236,   533,  -105,   491,   234,   569,   110,   494,   561,   209,
     248,   565,   542,   440,   235,   538,   448,   167,   154,   507,
       0,     0,   567,     0,   213,     0,  -105,     0,   215,  -105,
     236,  -105,  -105,   536,  -105,   154,  -105,     0,     0,   287,
       0,   288,   289,     0,     0,   234,     0,   290,     0,     0,
       0,     0,   291,   292,     0,   235,   566,   544,     0,     0,
       0,   167,   546,   141,     0,   293,   553,     0,     0,  -105,
    -105,   236,  -105,  -105,   110,  -105,   162,     0,     0,   163,
       4,     0,     6,   553,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,     0,     0,   553,     0,     0,
       0,     0,    26,    27,    28,    29,   313,     5,   152,     7,
       8,     0,    10,    11,    12,    13,    14,    15,    16,    17,
      18,     0,   314,    21,    22,     0,     0,    25,     0,     0,
       0,   288,   289,    52,    30,    31,    32,   290,     0,     0,
       0,     0,   291,   292,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   141,     0,   293,    49,     0,     0,     0,
       0,    53,    54,    55,    56,    57,     0,     0,     0,    61,
      62,     0,     0,    63,     0,     0,    64,    65,    66,   164,
      68,     0,     0,    69,     0,     0,    70,    71,     0,     0,
     315,     0,     0,    72,     0,     0,     0,     0,     0,    75,
      -3,     1,  -132,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,     0,    30,    31,    32,    33,     0,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,    46,    47,    48,     0,    49,    50,    51,    52,     0,
      53,    54,    55,    56,    57,    58,    59,    60,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,     0,   287,     0,   288,   289,     0,     0,     0,
       0,   290,     0,     0,    61,    62,   291,   292,    63,     0,
       0,    64,    65,    66,    67,    68,     0,   141,    69,   293,
       0,    70,    71,     0,     0,     0,     0,     0,    72,     0,
      73,     0,    74,     0,    75,    -2,     1,     0,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,     0,     0,    30,    31,
      32,    33,     0,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,     0,    46,    47,    48,     0,
      49,    50,    51,    52,     0,    53,    54,    55,    56,    57,
      58,    59,    60,     0,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,     0,   287,     0,
     288,   289,     0,     0,     0,     0,   290,     0,     0,    61,
      62,   291,   292,    63,     0,     0,    64,    65,    66,    67,
      68,     0,   141,    69,   293,     0,    70,    71,     0,     0,
       0,     0,     0,    72,     0,    73,     0,    74,   310,    75,
       0,   163,     4,     5,     6,     7,     8,     0,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     0,    20,    21,
      22,     0,     0,    25,    26,    27,    28,    29,     0,     0,
      30,    31,    32,     0,     0,     0,   162,     0,     0,   163,
       4,     0,     6,     0,     8,     0,     0,     0,     0,     0,
       0,   370,    49,     0,     0,    52,     0,    53,    54,    55,
      56,    57,    26,    27,    28,    29,   284,   285,   286,     0,
     287,     0,   288,   289,     0,     0,     0,     0,   290,     0,
       0,     0,     0,   291,   292,     0,     0,     0,     0,     0,
       0,    61,    62,    52,   141,    63,   293,     0,    64,    65,
      66,   164,    68,     0,     0,    69,     0,     0,    70,    71,
       0,     0,     0,     0,     0,    72,     0,     0,     0,     0,
       0,    75,  -123,     0,     0,     0,     0,     0,     0,    61,
      62,     0,     0,    63,     0,     0,    64,    65,    66,   164,
      68,     0,     0,    69,     0,     0,    70,    71,     0,     0,
       0,     0,     0,    72,     0,     0,     0,     0,     0,    75,
    -291,     1,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,     0,    30,    31,    32,    33,     0,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,    46,    47,    48,     0,    49,    50,    51,    52,     0,
      53,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,     0,   287,     0,   288,   289,     0,     0,     0,
       0,   290,     0,     0,    61,    62,   291,   292,    63,     0,
       0,    64,    65,    66,    67,    68,     0,   141,    69,   293,
       0,    70,    71,     0,     0,     0,     0,     0,    72,     0,
      73,    -3,    74,     1,    75,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,     0,     0,    30,    31,    32,    33,     0,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     0,    46,    47,    48,     0,    49,    50,    51,
      52,     0,    53,    54,    55,    56,    57,    58,    59,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   282,
     283,   284,   285,   286,     0,   287,     0,   288,   289,     0,
       0,     0,     0,   290,     0,     0,    61,    62,   291,   292,
      63,     0,     0,    64,    65,    66,    67,    68,     0,   141,
      69,   293,     0,    70,    71,     0,     0,     0,     0,     0,
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
       0,     0,    63,     0,     0,    64,    65,    66,    67,    68,
       0,     0,    69,     0,     0,    70,    71,     0,     0,     0,
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
      61,    62,     0,     0,    63,     0,     0,    64,    65,    66,
      67,    68,     0,     0,    69,     0,     0,    70,    71,     0,
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
       0,     0,    61,    62,     0,     0,    63,     0,     0,    64,
      65,    66,    67,    68,     0,     0,    69,     0,     0,    70,
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
       0,     0,     0,     0,    61,    62,     0,     0,    63,     0,
       0,    64,    65,    66,    67,    68,     0,     0,    69,     0,
       0,    70,    71,     0,     0,     0,     0,     0,    72,     0,
      73,     0,    74,   162,    75,     0,   163,     4,     5,     6,
       7,     8,     0,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     0,    20,    21,    22,     0,     0,    25,    26,
      27,    28,    29,     0,     0,    30,    31,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,     0,     0,
      52,     0,    53,    54,    55,    56,    57,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,     0,   287,     0,   288,   289,     0,
       0,     0,     0,   290,     0,     0,    61,    62,   291,   292,
      63,     0,     0,    64,    65,    66,   164,    68,     0,   141,
      69,   293,     0,    70,    71,     0,     0,     0,     0,     0,
      72,     0,     0,     0,   457,   162,    75,     0,   163,     4,
       5,     6,     7,     8,     0,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     0,    20,    21,    22,     0,     0,
      25,    26,    27,    28,    29,     0,     0,    30,    31,    32,
       0,     0,     0,   162,     0,     0,   163,     4,     0,     6,
       0,     8,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,    52,     0,    53,    54,    55,    56,    57,    26,
      27,    28,    29,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      52,     0,    63,     0,     0,    64,    65,    66,   164,    68,
       0,     0,    69,     0,     0,    70,    71,     0,     0,     0,
       0,     0,    72,     0,     0,     0,     0,     0,    75,     0,
       0,     0,     0,     0,     0,     0,    61,    62,     0,     0,
      63,     0,     0,    64,    65,    66,   164,    68,     0,     0,
      69,     0,     0,    70,    71,     0,     0,     0,     0,   162,
      72,     0,   163,     4,  -291,     6,    75,     8,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    26,    27,    28,    29,     0,
       0,   162,     0,     0,   163,     4,     0,     6,     0,     8,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,    26,    27,    28,
      29,     0,     5,   152,     7,     8,     0,    10,    11,    12,
      13,    14,    15,    16,    17,    18,     0,    20,    21,    22,
       0,     0,    25,     0,     0,     0,     0,     0,    52,    30,
      31,    32,    61,    62,     0,     0,    63,     0,     0,    64,
      65,    66,   164,    68,     0,     0,    69,     0,     0,    70,
      71,    49,     0,     0,     0,     0,    72,     0,     0,     0,
       0,     0,    75,     0,    61,    62,     0,     0,    63,     0,
       0,    64,    65,    66,   164,    68,     0,     0,    69,     0,
       0,    70,    71,   162,     0,     0,   163,     4,    72,     6,
     488,     8,     0,     0,    75,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
      27,    28,    29,     0,     0,   162,     0,     0,   163,     4,
       0,     6,     0,     8,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,    26,    27,    28,    29,     0,     5,   205,     7,     8,
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
       0,    20,    21,    22,     0,     0,    25,     0,     0,     0,
       0,     0,    52,    30,    31,    32,    61,    62,     0,     0,
      63,     0,     0,    64,    65,    66,   164,    68,     0,     0,
      69,     0,     0,    70,    71,    49,     0,     0,     0,     0,
      72,     0,   549,     0,     0,     0,    75,     0,    61,    62,
       0,     0,    63,     0,     0,    64,    65,    66,   164,    68,
       0,     0,    69,     0,     0,    70,    71,   310,     0,     0,
     163,     4,    72,     6,     0,     8,     0,     0,    75,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,    27,    28,    29,     0,     5,   152,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     0,    20,    21,    22,    23,     0,    25,     0,
       0,     0,     0,     0,    52,    30,    31,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,    50,     0,
       0,     0,    53,    54,    55,    56,    57,     0,     0,     0,
      61,    62,     0,     0,    63,     0,     0,    64,    65,    66,
     164,    68,     0,     0,    69,     0,     0,    70,    71,     0,
       0,     0,     0,     0,    72,     0,     0,     0,     0,     0,
      75,     0,     0,     0,     0,     0,   185,     0,     5,   152,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   223,    20,    21,    22,    23,     0,    25,     0,
       0,     0,     0,     0,     0,    30,    31,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,    50,     0,
       0,     0,    53,    54,    55,    56,    57,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,     0,   287,
       0,   288,   289,     0,     0,     0,   185,   290,     0,     0,
       0,     0,   291,   292,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   141,     0,   293,   503,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,     0,   287,
       0,   288,   289,     0,     0,     0,     0,   290,     0,     0,
       0,     0,   291,   292,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   141,     0,   293,   518,   313,     5,   152,
       7,     8,     0,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     0,   314,    21,    22,     0,     0,    25,     0,
       0,     0,     0,     0,     0,    30,    31,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,     0,     0,
       0,     0,    53,    54,    55,    56,    57,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,     0,   287,
       0,   288,   289,     0,     0,     0,     0,   290,     0,     0,
       0,     0,   291,   292,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   141,   369,   293,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,     0,   287,     0,
     288,   289,     0,     0,     0,     0,   290,     0,     0,     0,
       0,   291,   292,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   141,   471,   293,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,     0,   287,     0,   288,
     289,     0,     0,     0,     0,   290,     0,     0,     0,     0,
     291,   292,     0,     0,     0,     0,     0,     0,     0,     0,
     499,   141,     0,   293,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,     0,   287,     0,   288,   289,
       0,     0,     0,     0,   290,     0,     0,     0,     0,   291,
     292,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     141,   535,   293,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,     0,   287,     0,   288,   289,     0,
       0,     0,     0,   290,     0,     0,     0,     0,   291,   292,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
       0,   293,     5,   152,     7,     8,     0,    10,    11,    12,
      13,    14,    15,    16,    17,    18,     0,    20,    21,    22,
       0,     0,    25,     0,     0,     0,     0,   302,   303,    30,
      31,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    49,     0,     0,     0,     0,    53,    54,    55,    56,
      57,     5,   152,     7,     8,     0,    10,    11,    12,    13,
      14,    15,    16,    17,    18,     0,    20,    21,    22,     0,
       0,    25,     0,     0,     0,     0,     0,     0,    30,    31,
      32,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   370,
      49,     0,     0,     0,     0,    53,    54,    55,    56,    57,
       5,   152,     7,     8,     0,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     0,    20,    21,    22,     0,     0,
      25,     0,     0,     0,     0,     0,     0,    30,    31,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,     0,    53,    54,    55,    56,    57,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,     0,
     287,     0,   288,   289,     0,     0,     0,     0,   290,     0,
       0,     0,     0,   291,   292,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   141,     0,   293,     5,   152,     7,
       8,     0,    10,    11,    12,    13,    14,    15,    16,    17,
      18,     0,    20,    21,    22,     0,     0,    25,     0,     0,
       0,     0,     0,     0,    30,    31,    32,     0,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,     0,   287,    49,   288,   289,     0,
       0,   243,     0,   290,     0,     0,     0,     0,   291,   292,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
       0,   293,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,     0,   287,     0,
     288,   289,     0,     0,     0,     0,   290,     0,     0,     0,
       0,   291,   292,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   141,     0,   293
};

static const yytype_int16 yycheck[] =
{
       0,    38,    39,     6,    46,    83,   159,    77,   238,    46,
      44,    83,   146,   172,    23,     8,   158,    67,    84,    85,
     207,    10,    53,    23,   183,    86,   371,    86,   110,   183,
     250,   251,   252,   122,    44,    52,   223,    90,    91,   242,
      71,   196,    94,    52,    44,     3,    89,   123,     6,    90,
      91,   124,    52,    53,    47,    61,    62,    63,   123,    65,
      66,    67,    68,    69,    95,     7,    75,     9,    79,    75,
      98,    71,   154,    90,    91,    75,   110,    77,    52,     4,
     108,   215,     7,   165,     9,   128,   122,   123,   247,   121,
      90,    91,   174,   247,    94,    95,   128,   150,     3,   254,
     110,     6,     4,     8,     6,     7,     8,     9,   186,   150,
     110,    91,   123,   124,   186,   104,    90,    91,   122,   156,
     154,   187,   188,    52,   161,   134,     4,   347,   189,     7,
       8,   121,   124,   150,   134,   185,   142,   146,   128,   191,
     174,   371,   487,   184,   121,   182,   146,   225,   123,   125,
     150,   128,   128,   225,   154,   165,    98,   209,   164,   237,
     242,    90,    91,   350,   174,   237,   238,   184,     7,   228,
       9,    65,    66,    67,   174,   184,   150,   397,   398,   382,
       3,    59,   122,   235,   184,     8,     3,   196,   124,     6,
     196,   191,    52,   118,   539,     5,   196,     4,   204,     6,
       7,     8,     9,   206,   124,   134,   215,   207,   124,   209,
     184,     1,   243,     3,   124,   215,   118,     7,     3,     9,
     298,   150,     7,   223,     9,   242,   298,   297,   328,   329,
      90,    91,   120,    21,   122,   235,   236,   126,     0,    24,
      47,   124,   242,   243,     4,   254,     6,     7,     8,     9,
     256,   120,   330,   122,   254,   184,   390,   487,   330,    98,
     490,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   484,   335,   123,   290,   357,     4,   293,   294,    79,
     150,    14,    15,    16,    17,   122,   366,   297,   335,    91,
      50,   383,   455,     6,     7,     8,     9,   377,    98,   539,
     376,   118,   118,   447,   456,   308,    79,   399,   108,   124,
     479,   126,   125,   124,   184,   126,   335,   547,   380,   189,
     123,     3,   122,   123,   124,   335,   126,     1,   128,     3,
       7,   122,     9,     7,   478,     9,     6,   534,   122,   122,
     350,   504,   120,   122,    10,   392,   120,   363,   118,   362,
     123,   124,   368,   126,   118,    60,   366,     1,   228,     3,
     127,   122,   125,     7,   122,     9,   128,   377,   122,   124,
     380,   390,   123,   383,   390,    37,   545,   125,    38,   125,
     390,   122,   125,   122,   126,   395,   466,   463,   123,   399,
     128,   125,   122,   409,   125,     3,     5,   120,     1,    89,
       3,     3,     3,     3,     7,   120,     9,   125,   571,    92,
      93,    94,    95,    96,    97,    98,   122,   100,   122,   102,
     103,     3,    68,   125,    98,   108,   127,   443,   447,   122,
     113,   114,    91,   125,   108,    79,    52,   447,   485,   515,
     545,   124,   391,   126,    12,    89,   478,   237,   372,   459,
     124,   495,   126,   395,    98,   563,   466,   401,   549,   478,
     100,   557,   514,   299,   108,   505,   318,   514,   478,   447,
      -1,    -1,   560,    -1,   554,    -1,    79,    -1,   560,   123,
     124,   125,   126,   499,   128,   495,    89,    -1,    -1,   100,
      -1,   102,   103,    -1,    -1,    98,    -1,   108,    -1,    -1,
      -1,    -1,   113,   114,    -1,   108,   558,   520,    -1,    -1,
      -1,   558,   525,   124,    -1,   126,   532,    -1,    -1,   122,
     123,   124,   125,   126,   534,   128,     1,    -1,    -1,     4,
       5,    -1,     7,   549,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   554,    -1,    -1,   563,    -1,    -1,
      -1,    -1,    27,    28,    29,    30,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    -1,    -1,    26,    -1,    -1,
      -1,   102,   103,    58,    33,    34,    35,   108,    -1,    -1,
      -1,    -1,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,    -1,   126,    55,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    -1,    -1,    -1,    94,
      95,    -1,    -1,    98,    -1,    -1,   101,   102,   103,   104,
     105,    -1,    -1,   108,    -1,    -1,   111,   112,    -1,    -1,
      89,    -1,    -1,   118,    -1,    -1,    -1,    -1,    -1,   124,
       0,     1,   127,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    -1,    55,    56,    57,    58,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    -1,   100,    -1,   102,   103,    -1,    -1,    -1,
      -1,   108,    -1,    -1,    94,    95,   113,   114,    98,    -1,
      -1,   101,   102,   103,   104,   105,    -1,   124,   108,   126,
      -1,   111,   112,    -1,    -1,    -1,    -1,    -1,   118,    -1,
     120,    -1,   122,    -1,   124,     0,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    -1,    -1,    33,    34,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    -1,    51,    52,    53,    -1,
      55,    56,    57,    58,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,   100,    -1,
     102,   103,    -1,    -1,    -1,    -1,   108,    -1,    -1,    94,
      95,   113,   114,    98,    -1,    -1,   101,   102,   103,   104,
     105,    -1,   124,   108,   126,    -1,   111,   112,    -1,    -1,
      -1,    -1,    -1,   118,    -1,   120,    -1,   122,     1,   124,
      -1,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    -1,    -1,    26,    27,    28,    29,    30,    -1,    -1,
      33,    34,    35,    -1,    -1,    -1,     1,    -1,    -1,     4,
       5,    -1,     7,    -1,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    -1,    -1,    58,    -1,    60,    61,    62,
      63,    64,    27,    28,    29,    30,    96,    97,    98,    -1,
     100,    -1,   102,   103,    -1,    -1,    -1,    -1,   108,    -1,
      -1,    -1,    -1,   113,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    95,    58,   124,    98,   126,    -1,   101,   102,
     103,   104,   105,    -1,    -1,   108,    -1,    -1,   111,   112,
      -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,    -1,
      -1,   124,   125,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      95,    -1,    -1,    98,    -1,    -1,   101,   102,   103,   104,
     105,    -1,    -1,   108,    -1,    -1,   111,   112,    -1,    -1,
      -1,    -1,    -1,   118,    -1,    -1,    -1,    -1,    -1,   124,
     125,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    -1,    55,    56,    57,    58,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    -1,   100,    -1,   102,   103,    -1,    -1,    -1,
      -1,   108,    -1,    -1,    94,    95,   113,   114,    98,    -1,
      -1,   101,   102,   103,   104,   105,    -1,   124,   108,   126,
      -1,   111,   112,    -1,    -1,    -1,    -1,    -1,   118,    -1,
     120,   121,   122,     1,   124,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    -1,    51,    52,    53,    -1,    55,    56,    57,
      58,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      95,    96,    97,    98,    -1,   100,    -1,   102,   103,    -1,
      -1,    -1,    -1,   108,    -1,    -1,    94,    95,   113,   114,
      98,    -1,    -1,   101,   102,   103,   104,   105,    -1,   124,
     108,   126,    -1,   111,   112,    -1,    -1,    -1,    -1,    -1,
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
      -1,    -1,    98,    -1,    -1,   101,   102,   103,   104,   105,
      -1,    -1,   108,    -1,    -1,   111,   112,    -1,    -1,    -1,
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
      94,    95,    -1,    -1,    98,    -1,    -1,   101,   102,   103,
     104,   105,    -1,    -1,   108,    -1,    -1,   111,   112,    -1,
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
      -1,    -1,    94,    95,    -1,    -1,    98,    -1,    -1,   101,
     102,   103,   104,   105,    -1,    -1,   108,    -1,    -1,   111,
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
      -1,    -1,    -1,    -1,    94,    95,    -1,    -1,    98,    -1,
      -1,   101,   102,   103,   104,   105,    -1,    -1,   108,    -1,
      -1,   111,   112,    -1,    -1,    -1,    -1,    -1,   118,    -1,
     120,    -1,   122,     1,   124,    -1,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    -1,    -1,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      58,    -1,    60,    61,    62,    63,    64,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    -1,   100,    -1,   102,   103,    -1,
      -1,    -1,    -1,   108,    -1,    -1,    94,    95,   113,   114,
      98,    -1,    -1,   101,   102,   103,   104,   105,    -1,   124,
     108,   126,    -1,   111,   112,    -1,    -1,    -1,    -1,    -1,
     118,    -1,    -1,    -1,   122,     1,   124,    -1,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    -1,    -1,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      -1,    -1,    -1,     1,    -1,    -1,     4,     5,    -1,     7,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      -1,    -1,    58,    -1,    60,    61,    62,    63,    64,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      58,    -1,    98,    -1,    -1,   101,   102,   103,   104,   105,
      -1,    -1,   108,    -1,    -1,   111,   112,    -1,    -1,    -1,
      -1,    -1,   118,    -1,    -1,    -1,    -1,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    -1,    -1,
      98,    -1,    -1,   101,   102,   103,   104,   105,    -1,    -1,
     108,    -1,    -1,   111,   112,    -1,    -1,    -1,    -1,     1,
     118,    -1,     4,     5,   122,     7,   124,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    29,    30,    -1,
      -1,     1,    -1,    -1,     4,     5,    -1,     7,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    27,    28,    29,
      30,    -1,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    58,    33,
      34,    35,    94,    95,    -1,    -1,    98,    -1,    -1,   101,
     102,   103,   104,   105,    -1,    -1,   108,    -1,    -1,   111,
     112,    55,    -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,
      -1,    -1,   124,    -1,    94,    95,    -1,    -1,    98,    -1,
      -1,   101,   102,   103,   104,   105,    -1,    -1,   108,    -1,
      -1,   111,   112,     1,    -1,    -1,     4,     5,   118,     7,
     120,     9,    -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      28,    29,    30,    -1,    -1,     1,    -1,    -1,     4,     5,
      -1,     7,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      58,    27,    28,    29,    30,    -1,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    58,    33,    34,    35,    94,    95,    -1,    -1,
      98,    -1,    -1,   101,   102,   103,   104,   105,    -1,    -1,
     108,    -1,    -1,   111,   112,    55,    -1,    -1,    -1,    -1,
     118,    -1,   120,    -1,    -1,    -1,   124,    -1,    94,    95,
      -1,    -1,    98,    -1,    -1,   101,   102,   103,   104,   105,
      -1,    -1,   108,    -1,    -1,   111,   112,     1,    -1,    -1,
       4,     5,   118,     7,    -1,     9,    -1,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    29,    30,    -1,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    58,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      94,    95,    -1,    -1,    98,    -1,    -1,   101,   102,   103,
     104,   105,    -1,    -1,   108,    -1,    -1,   111,   112,    -1,
      -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,    -1,    -1,
     124,    -1,    -1,    -1,    -1,    -1,   104,    -1,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,   120,    21,    22,    23,    24,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    -1,   100,
      -1,   102,   103,    -1,    -1,    -1,   104,   108,    -1,    -1,
      -1,    -1,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,    -1,   126,   127,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    -1,   100,
      -1,   102,   103,    -1,    -1,    -1,    -1,   108,    -1,    -1,
      -1,    -1,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,    -1,   126,   127,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    -1,   100,
      -1,   102,   103,    -1,    -1,    -1,    -1,   108,    -1,    -1,
      -1,    -1,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,   125,   126,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,   100,    -1,
     102,   103,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   124,   125,   126,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    -1,   100,    -1,   102,
     103,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,
     113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     123,   124,    -1,   126,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    -1,   100,    -1,   102,   103,
      -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,   113,
     114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,   125,   126,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    -1,   100,    -1,   102,   103,    -1,
      -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,   113,   114,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,
      -1,   126,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    -1,
     100,    -1,   102,   103,    -1,    -1,    -1,    -1,   108,    -1,
      -1,    -1,    -1,   113,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,    -1,   126,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    -1,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    -1,   100,    55,   102,   103,    -1,
      -1,    60,    -1,   108,    -1,    -1,    -1,    -1,   113,   114,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,
      -1,   126,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,   100,    -1,
     102,   103,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   124,    -1,   126
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      33,    34,    35,    36,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    51,    52,    53,    55,
      56,    57,    58,    60,    61,    62,    63,    64,    65,    66,
      67,    94,    95,    98,   101,   102,   103,   104,   105,   108,
     111,   112,   118,   120,   122,   124,   130,   131,   132,   134,
     135,   136,   139,   140,   141,   142,   143,   144,   145,   146,
     148,   149,   150,   151,   158,   159,   162,   163,   184,   186,
     187,   193,   195,   196,   198,   205,   209,   210,   211,   214,
     215,   216,   219,   220,   223,   225,   238,   239,   240,   242,
     245,   248,   252,   254,   255,   256,   257,   258,   259,   265,
     267,   268,   269,   270,   271,   272,   273,   275,   122,   123,
     123,   124,   170,   231,   232,    91,   277,   279,   279,   163,
     137,   199,     7,   158,   215,   212,   124,   234,   243,   246,
     124,   124,     1,     4,   104,   215,   220,   220,   235,   122,
     122,   123,   206,    47,   215,   219,   267,   260,   235,   279,
       5,   124,   160,    21,   197,   104,   140,   141,   142,   143,
     150,   158,   162,   225,   225,   225,   124,   225,   225,   139,
     225,   225,   225,   126,   230,     7,   162,   133,   156,   158,
     222,   225,     0,   134,   124,   170,   172,   122,   132,   122,
     132,   144,   151,   120,   135,   140,   141,   142,   143,   145,
     147,   147,     1,     3,    98,   108,   124,   164,   167,   169,
     175,   176,   215,    60,   162,   123,   191,   192,   191,   219,
     267,   268,     4,   122,    91,   224,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,   100,   102,   103,
     108,   113,   114,   126,   218,   231,   236,   237,    50,   262,
     264,   118,    31,    32,   142,   274,     3,     8,   276,   125,
       1,   225,   233,     5,    21,    89,   156,   278,   280,   281,
     282,   283,   135,   138,   145,     3,     6,   202,    98,   108,
     168,     3,   220,   234,   236,   249,   220,   123,   122,     3,
       6,     8,   189,   190,   208,   269,     6,     8,   122,   122,
     120,   261,   122,   220,   190,   145,   172,   167,   222,   225,
     127,   225,   226,   126,   221,   231,   131,   167,   125,   125,
      54,   156,   173,   174,   122,   123,   152,   131,   172,    60,
     157,   167,    98,   215,   126,   165,   172,    79,   123,   165,
     170,   172,   178,   179,   232,   128,   122,   141,   169,   215,
     162,   123,   188,   190,   217,   217,   217,   217,   222,   124,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   229,   225,   227,   228,   225,   225,    37,   134,   172,
     264,   279,   125,   128,   171,     3,     6,   128,   278,   200,
     168,   168,   172,   213,   125,   244,    38,   122,   135,   158,
     220,   247,   125,   207,   122,   217,   131,   125,   161,   122,
     125,   125,   231,   225,   121,   225,   179,   171,   128,   153,
     132,   121,   167,   169,    98,   166,     5,   157,   120,   220,
     167,   176,   217,   217,   184,   185,   120,    89,   225,   123,
       3,     3,     3,   127,   241,   263,   225,   283,   120,   201,
     122,   236,   234,   122,   250,   253,   132,   121,   127,   173,
       4,     7,    59,   154,   155,   266,   269,   125,   169,   177,
     220,   179,   180,   267,   194,   125,   225,   236,   261,     3,
     203,   204,   235,   132,   231,    68,   231,   125,   127,   120,
     181,   182,   183,   225,   131,   179,   121,   128,   122,   154,
     217,   183,   121,   128,   121,   203,   235,   172,   121,   182,
     125,   251,   236
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
      yyerror (YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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
        case 4:

/* Line 1455 of yacc.c  */
#line 154 "parser.y"
    {statement_end();}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    {statement_end();}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    { state.init_block(PLAIN_BLOCK); IEF_set(); }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 161 "parser.y"
    { state.finalize_block(); IEF_reset();}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 170 "parser.y"
    {expression_end((yyvsp[(1) - (2)].expression));}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    { raise_error("Error in statement"); YYABORT; }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 199 "parser.y"
    { 
    Type dt = tpop();
	dcl_reset();
	state.check_dcl_init(dt);
 }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 208 "parser.y"
    { state.in_typedef = true; }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    { state.in_typedef = false; }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 221 "parser.y"
    {
   dcl_set();
   state.token_stack.push((yyvsp[(1) - (1)].classptr)->constructor_name());
   tpush(t_void);
   state.in_construct_destruct = IsConstructor;
   (yyval.classptr) = (yyvsp[(1) - (1)].classptr);
  }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 231 "parser.y"
    {}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 233 "parser.y"
    {
  state.token_stack.TOS() = (yyvsp[(2) - (2)].classptr)->destructor_name();
  state.in_construct_destruct = IsDestructor;
}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 241 "parser.y"
    { 
   state.token_stack.push(CONVERSION_OPNAME);
   ttpush((yyvsp[(3) - (4)].ctype)); (yyval.ctype) = (yyvsp[(3) - (4)].ctype);
  }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 249 "parser.y"
    { (yyval.ctype)=(yyvsp[(2) - (5)].ctype); stots((yyval.ctype)); state.member_is_const = (yyvsp[(4) - (5)].val); gFunInit = (yyvsp[(5) - (5)].expression); }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 253 "parser.y"
    { state.modifier = Explicit; }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    {  
   state.declare_function(t_void,state.token_stack.pop());
   tpop();
   check_error();
 }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 267 "parser.y"
    {
   state.declare_function(AsType((yyvsp[(1) - (2)].ctype)),state.token_stack.pop(), gFunInit); 
   dcl_reset();
   gFunInit = NULL;
   tpop();
   check_error();
 }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 277 "parser.y"
    { 
    state.declare_function(AsType((yyvsp[(1) - (2)].ctype)),state.token_stack.pop());
	tpop();
	check_error();
  }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 290 "parser.y"
    { state.extern_flag = false; }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 291 "parser.y"
    { state.extern_flag_C = false; }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 292 "parser.y"
    { state.extern_flag_C = false; }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    { state.extern_flag_C = true; }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 305 "parser.y"
    { state.extern_flag = true; }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 312 "parser.y"
    { }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 314 "parser.y"
    {}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 316 "parser.y"
    {}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 318 "parser.y"
    {}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 330 "parser.y"
    {   state.init_block(CONSTRUCTOR_BLOCK);  }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 332 "parser.y"
    {  check_error(); state.in_method = true; }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 344 "parser.y"
    { 
	 ((Class*)state.context().parent_context())
	    ->add_class_init_list(AsType((yyvsp[(1) - (2)].ctype)).as_class()->entry(),(yyvsp[(2) - (2)].elist));
	/* fix 1.2.3a Can crash UC if we don't catch errors in the init list */
	 if (check_error()) YYABORT;  
	}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 353 "parser.y"
    { ((Class*)state.context().parent_context())
	      ->add_class_init_list((yyvsp[(1) - (2)].entry),(yyvsp[(2) - (2)].elist));
	 if (check_error()) YYABORT;
    }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 362 "parser.y"
    { (yyval.ctype) = (yyvsp[(2) - (2)].ctype);  }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 365 "parser.y"
    { (yyval.val)=0; }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 366 "parser.y"
    { (yyval.val)=1; }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 370 "parser.y"
    {dcl_set();}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 371 "parser.y"
    {dcl_set();}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 372 "parser.y"
    {dcl_set(); tots().make_const();}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 373 "parser.y"
    {dcl_set(); tots().make_const();}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 377 "parser.y"
    {state.modifier = Static;  }
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 378 "parser.y"
    {state.modifier = Virtual; }
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 379 "parser.y"
    {state.modifier = Stdcall; }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 380 "parser.y"
    {state.modifier = Api;     }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 383 "parser.y"
    {dcl_set(false);}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 386 "parser.y"
    {dcl_reset();}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 389 "parser.y"
    { ttpush((yyvsp[(1) - (1)].ctype));  }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 390 "parser.y"
    { tpush(typeof_op((yyvsp[(3) - (4)].expression))); }
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 391 "parser.y"
    { }
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 392 "parser.y"
    { tots().make_unsigned(); }
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 393 "parser.y"
    { tpush(t_int); tots().make_unsigned(); }
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 394 "parser.y"
    { tpush(t_float);  }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 395 "parser.y"
    { tpush(t_double); }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 396 "parser.y"
    { tpush(t_bool); }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 397 "parser.y"
    { tpush(t_void); }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 398 "parser.y"
    { }
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 399 "parser.y"
    { }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 409 "parser.y"
    { tpush(t_int);   }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 410 "parser.y"
    { tpush(t_short); }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 411 "parser.y"
    { tpush(t_long);  }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 416 "parser.y"
    { tpush(t_char);  }
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 420 "parser.y"
    { (yyval.ctype) = incr_ptr((yyvsp[(3) - (4)].ctype)); }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 424 "parser.y"
    {dcl_set(false);}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 426 "parser.y"
    { dcl_reset(); (yyval.expression) = (yyvsp[(3) - (4)].expression); }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 429 "parser.y"
    { (yyval.ctype)=ttots(); state.token_stack.push(""); }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 430 "parser.y"
    { (yyval.ctype)=(yyvsp[(1) - (1)].ctype);   }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 431 "parser.y"
    { Type t = AsType((yyvsp[(1) - (2)].ctype)); t.decr_pointer(); (yyval.ctype) = AsTType(state.signature_type(t));     }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 434 "parser.y"
    { state.class_dcl = AsType((yyvsp[(2) - (7)].ctype)); (yyval.ctype) = AsTType(state.signature_type(AsType((yyvsp[(4) - (7)].ctype))));  }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 435 "parser.y"
    { (yyval.ctype) = incr_ptr((yyvsp[(3) - (3)].ctype));         }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 436 "parser.y"
    { (yyval.ctype) = make_ref((yyvsp[(2) - (2)].ctype));         }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 437 "parser.y"
    { (yyval.ctype) = (yyvsp[(2) - (3)].ctype);   state.class_dcl = AsType((yyvsp[(1) - (3)].ctype)); }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 439 "parser.y"
    { (yyval.ctype) = (yyvsp[(2) - (3)].ctype);   state.class_dcl = AsType((yyvsp[(1) - (3)].ctype)); }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 440 "parser.y"
    { (yyval.ctype) = make_array((yyvsp[(1) - (2)].ctype),(yyvsp[(2) - (2)].expression)); check_error();   }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 441 "parser.y"
    { (yyval.ctype) = make_array((yyvsp[(1) - (2)].ctype),(yyvsp[(2) - (2)].expression)); check_error();   }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 442 "parser.y"
    { raise_error("Error in type expression"); YYABORT; }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 446 "parser.y"
    { (yyval.ctype) = ttots(); }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 447 "parser.y"
    { (yyval.ctype) = incr_ptr((yyvsp[(2) - (2)].ctype)); }
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 448 "parser.y"
    { (yyval.ctype) = make_ref((yyvsp[(2) - (2)].ctype)); }
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 451 "parser.y"
    { (yyval.ctype)=ttots(); state.token_stack.push((yyvsp[(1) - (1)].str)); }
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 455 "parser.y"
    { dcl_set(false); state.begin_args(); }
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 458 "parser.y"
    { dcl_reset(); }
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 469 "parser.y"
    { 
   state.add_to_arg_list(t_void,"...",0);
 }
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 476 "parser.y"
    {  
  state.add_to_arg_list(AsType((yyvsp[(1) - (2)].ctype)),state.token_stack.pop(),(yyvsp[(2) - (2)].expression));
  tpop();
  dcl_reset();
}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 485 "parser.y"
    {
  string name = state.token_stack.pop();
  Type t = AsType((yyvsp[(1) - (2)].ctype));
  temp_context()->reserved_space(t.size());
  state.add_variable(t,name,(yyvsp[(2) - (2)].expression),state.modifier);
  if (check_error()) YYABORT;
  }
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 499 "parser.y"
    { (yyval.expression)=NULL; }
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 500 "parser.y"
    {(yyval.expression)=(yyvsp[(1) - (1)].expression);}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 506 "parser.y"
    { dcl_set(false); }
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 509 "parser.y"
    { (yyval.expression)=NULL; }
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 512 "parser.y"
    { dcl_reset(); (yyval.expression)=(yyvsp[(2) - (2)].expression); }
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 515 "parser.y"
    { (yyval.expression)=expr_list_op((yyvsp[(1) - (1)].elist),true); }
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 517 "parser.y"
    { enter_arglist();}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 519 "parser.y"
    {leave_arglist(); dcl_reset(); (yyval.expression)=expr_list_op((yyvsp[(4) - (5)].elist),false); }
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 522 "parser.y"
    { (yyval.expression) = new Expr(ECONST,t_void,(yyvsp[(2) - (2)].entry),NULL); }
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 529 "parser.y"
    { (yyval.elist) = (yyvsp[(2) - (3)].elist); }
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 532 "parser.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 533 "parser.y"
    { (yyval.expression) = expr_list_op((yyvsp[(1) - (1)].elist),false); }
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 536 "parser.y"
    { (yyval.elist) = new ExprList; (yyval.elist)->push_back((yyvsp[(1) - (1)].expression));  }
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 537 "parser.y"
    { (yyval.elist) = (yyvsp[(1) - (3)].elist); (yyval.elist)->push_back((yyvsp[(3) - (3)].expression)); }
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 547 "parser.y"
    {(yyval.val)=Public;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 548 "parser.y"
    {(yyval.val)=Private;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 549 "parser.y"
    {(yyval.val)=Protected;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 552 "parser.y"
    { (yyval.val)=Default; }
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 558 "parser.y"
    { (yyval.val) = CLASS; }
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 559 "parser.y"
    { (yyval.val) = STRUCT; }
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 560 "parser.y"
    { (yyval.val) = UNION;  }
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 563 "parser.y"
    { (yyval.val)=NotDerived; }
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 565 "parser.y"
    { (yyval.val)=(yyvsp[(2) - (3)].val); state.class_dcl = AsType((yyvsp[(3) - (3)].ctype)); }
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 569 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);               }
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 570 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].entry)->name.c_str(); }
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 573 "parser.y"
    { (yyval.str) = "";               }
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 574 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);               }
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 576 "parser.y"
    { PClass pc = AsType((yyvsp[(1) - (1)].ctype)).as_class();
     (yyval.str) = pc->name().c_str();
    }
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 579 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].entry)->name.c_str(); }
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 582 "parser.y"
    { dcl_set();}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 582 "parser.y"
    { dcl_reset(); (yyval.str) = (yyvsp[(2) - (2)].str);  }
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 589 "parser.y"
    { 
	   tpush(state.add_class((yyvsp[(1) - (4)].val),(yyvsp[(2) - (4)].str),(yyvsp[(3) - (4)].val),state.class_dcl));
       if (check_error()) YYABORT;
	   state.init_block(CLASS_BLOCK); IEF_set();
       typedef_stack.push(state.in_typedef);
       state.in_typedef = false;
      }
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 599 "parser.y"
    {
	   state.finalize_block(); IEF_reset();
  	   state.in_typedef = typedef_stack.pop(); 
	 }
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 605 "parser.y"
    { tpush(state.add_class((yyvsp[(1) - (2)].val),(yyvsp[(2) - (2)].str),ForwardClass,t_void)); }
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 609 "parser.y"
    { state.set_access_mode((yyvsp[(1) - (2)].val)); }
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 613 "parser.y"
    { state.in_friend_dcl = true; }
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 614 "parser.y"
    { state.add_friend_class((yyvsp[(2) - (4)].val)); }
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 624 "parser.y"
    { dcl_set(); }
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 625 "parser.y"
    {
    tpush(state.do_enum(tag_name));
    if (check_error()) YYABORT;
   }
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 630 "parser.y"
    { dcl_reset(); }
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 637 "parser.y"
    {(yyval.str)=NULL; tag_name="";}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 638 "parser.y"
    {(yyval.str)=(yyvsp[(1) - (1)].str); tag_name=(yyvsp[(1) - (1)].str);}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 639 "parser.y"
    {(yyval.str)=""; tag_name=(yyvsp[(1) - (1)].entry)->name.c_str();}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 644 "parser.y"
    { 
  state.add_enum(tots(),(yyvsp[(1) - (2)].str),(yyvsp[(2) - (2)].expression));
 }
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 658 "parser.y"
    { dcl_set(); }
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 659 "parser.y"
    { dcl_reset(); 
    state.add_namespace((yyvsp[(3) - (3)].str) ? (yyvsp[(3) - (3)].str) : "");
    state.in_class = true;
    if (check_error()) YYABORT;
   }
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 667 "parser.y"
    { (yyval.str) = NULL; }
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 668 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);  }
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 674 "parser.y"
    { 
   	if ((Namespace *)(yyvsp[(3) - (4)].entry)->data != &state.context()) 
      state.context().inject_namespace((Namespace *)(yyvsp[(3) - (4)].entry)->data);
    else raise_error("Cannot inject a namespace into itself");
    if (check_error()) YYABORT;
   }
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 684 "parser.y"
    {  state.context().inject_entry((yyvsp[(2) - (3)].entry));  }
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 686 "parser.y"
    { state.context().inject_entry((yyvsp[(3) - (4)].entry)); }
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 688 "parser.y"
    { state.context().inject_entry(last_type_entry);  }
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 693 "parser.y"
    { dcl_set(true); }
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 693 "parser.y"
    { dcl_reset(); }
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 694 "parser.y"
    { do_goto((yyvsp[(3) - (5)].str)); }
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 698 "parser.y"
    { goto_label_new((yyvsp[(1) - (2)].str)); }
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 699 "parser.y"
    { goto_label_existing((yyvsp[(1) - (2)].entry)); }
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 707 "parser.y"
    { state.begin_scope(AsType((yyvsp[(1) - (2)].ctype))); (yyval.ctype) = (yyvsp[(1) - (2)].ctype); }
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 712 "parser.y"
    { state.begin_scope(&global()); }
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 715 "parser.y"
    { state.end_scope(); }
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 725 "parser.y"
    { (yyval.entry) = (yyvsp[(2) - (3)].entry); }
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 727 "parser.y"
    { (yyval.entry) = (yyvsp[(2) - (3)].entry); }
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 731 "parser.y"
    {   if (check_error()) YYABORT;   (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 734 "parser.y"
    { (yyval.expression) = NULL; }
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 735 "parser.y"
    { (yyval.expression) = (yyvsp[(2) - (3)].expression); }
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 739 "parser.y"
    { dcl_reset(); (yyval.ctype)=(yyvsp[(1) - (1)].ctype); state.token_stack.pop(); tpop(); }
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 746 "parser.y"
    { (yyval.ctype)=(yyvsp[(2) - (3)].ctype); }
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 751 "parser.y"
    { (yyval.expression) =  entry_op((yyvsp[(1) - (1)].entry)); }
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 752 "parser.y"
    { (yyval.expression) =  entry_op((yyvsp[(1) - (1)].entry)); }
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 753 "parser.y"
    { (yyval.expression) =  (yyvsp[(2) - (3)].expression); }
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 755 "parser.y"
    { (yyval.expression)=arith_op(STAR,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 756 "parser.y"
    { (yyval.expression)=arith_op(DIVIDE,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 757 "parser.y"
    { (yyval.expression)=arith_op(MODULO,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 758 "parser.y"
    { (yyval.expression)=arith_op(PLUS,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 759 "parser.y"
    { (yyval.expression)=arith_op(MINUS,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 760 "parser.y"
    { (yyval.expression)=arith_op(BIN_AND,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 761 "parser.y"
    { (yyval.expression)=arith_op(BIN_OR,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 763 "parser.y"
    { (yyval.expression)=(yyvsp[(2) - (2)].expression); }
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 764 "parser.y"
    { (yyval.expression)=unary_op(UMINUS,(yyvsp[(2) - (2)].expression)); }
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 766 "parser.y"
    { (yyval.expression)=relational_op(LOG_NOT,(yyvsp[(2) - (2)].expression),NULL); }
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 767 "parser.y"
    { (yyval.expression)=relational_op(LESS_THAN,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 768 "parser.y"
    { (yyval.expression)=relational_op(GREATER,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 769 "parser.y"
    { (yyval.expression)=relational_op(LEQ,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 770 "parser.y"
    { (yyval.expression)=relational_op(GEQ,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 771 "parser.y"
    { (yyval.expression)=equal_op((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 772 "parser.y"
    { (yyval.expression)=relational_op(NOT_EQUAL,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 773 "parser.y"
    { (yyval.expression)=relational_op(LOG_AND,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 774 "parser.y"
    { (yyval.expression)=relational_op(LOG_OR,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 776 "parser.y"
    { (yyval.expression)=assign_op((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 777 "parser.y"
    { (yyval.expression)=compound_assign_op((yyvsp[(2) - (3)].val),(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 779 "parser.y"
    { (yyval.expression)=inc_dec_op(INCR,(yyvsp[(1) - (2)].expression),true); }
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 780 "parser.y"
    { (yyval.expression)=inc_dec_op(INCR,(yyvsp[(2) - (2)].expression),false); }
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 781 "parser.y"
    { (yyval.expression)=inc_dec_op(DECR,(yyvsp[(1) - (2)].expression),true); }
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 782 "parser.y"
    { (yyval.expression)=inc_dec_op(DECR,(yyvsp[(2) - (2)].expression),false); }
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 786 "parser.y"
    { 
    if ((yyvsp[(3) - (4)].expression)->is_entry()) (yyval.expression) = sizeof_op(size_of_entry((yyvsp[(3) - (4)].expression)->entry()));
	              else  (yyval.expression) = sizeof_op((yyvsp[(3) - (4)].expression)->type().size());
 }
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 790 "parser.y"
    { (yyval.expression)=sizeof_op(AsType((yyvsp[(3) - (4)].ctype)).size());  }
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 791 "parser.y"
    { (yyval.expression)=arith_if_op((yyvsp[(1) - (5)].expression),(yyvsp[(3) - (5)].expression),(yyvsp[(5) - (5)].expression)); }
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 792 "parser.y"
    { (yyval.expression)=bin_op(COMMA,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 794 "parser.y"
    { (yyval.expression) = new_op(tpop(),(yyvsp[(3) - (3)].expression),NULL);  }
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 796 "parser.y"
    { tpush((yyvsp[(2) - (2)].entry)->type); }
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 797 "parser.y"
    { (yyval.expression) = new_op(tpop(),NULL,(yyvsp[(4) - (4)].elist));  }
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 800 "parser.y"
    { (yyval.expression) = new_op(tpop(),NULL,(yyvsp[(3) - (3)].elist));  }
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 801 "parser.y"
    { (yyval.expression) = delete_op((yyvsp[(3) - (3)].expression),(yyvsp[(2) - (3)].val)==1); }
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 802 "parser.y"
    { (yyval.expression) = deref_op((yyvsp[(2) - (2)].expression)); }
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 803 "parser.y"
    { (yyval.expression) = addr_op((yyvsp[(2) - (2)].expression)); }
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 806 "parser.y"
    { (yyval.expression) = typecast_op((yyvsp[(1) - (5)].val),AsType((yyvsp[(2) - (5)].ctype)),(yyvsp[(4) - (5)].expression)); }
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 809 "parser.y"
    { (yyval.expression) = function_cast_op((yyvsp[(1) - (2)].entry)->type /*AsType($1)*/,(yyvsp[(2) - (2)].elist)); }
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 812 "parser.y"
    { (yyval.expression) = typecast_op(REINTERPRET_CAST,AsType((yyvsp[(2) - (4)].ctype)),(yyvsp[(4) - (4)].expression)); }
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 815 "parser.y"
    { (yyval.expression)=unary_op(BIN_NOT,(yyvsp[(2) - (2)].expression)); }
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 816 "parser.y"
    { (yyval.expression)=bin_op(LSHIFT,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 817 "parser.y"
    { (yyval.expression)=bin_op(RSHIFT,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 818 "parser.y"
    { (yyval.expression)=bin_op(BIN_AND,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 819 "parser.y"
    { (yyval.expression)=bin_op(BIN_XOR,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 820 "parser.y"
    { (yyval.expression)=bin_op(BIN_OR,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)); }
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 823 "parser.y"
    { (yyval.expression)=array_op((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression)); }
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 825 "parser.y"
    { (yyval.expression)=function_op((yyvsp[(1) - (2)].expression),(yyvsp[(2) - (2)].elist)); }
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 828 "parser.y"
    {dcl_set(); }
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 830 "parser.y"
    { dcl_reset(); (yyval.expression)=selection_op((yyvsp[(1) - (4)].expression),(yyvsp[(4) - (4)].str),false);  }
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 833 "parser.y"
    {dcl_set();}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 835 "parser.y"
    { dcl_reset(); (yyval.expression)=selection_op((yyvsp[(1) - (4)].expression),(yyvsp[(4) - (4)].str),true);  }
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 837 "parser.y"
    {dcl_set();}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 839 "parser.y"
    { dcl_reset(); (yyval.expression)=selection_op((yyvsp[(1) - (4)].expression),(yyvsp[(4) - (4)].str),true,true);  }
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 843 "parser.y"
    { (yyval.expression)=lambda_op(0);   }
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 845 "parser.y"
    { raise_error("error in expression"); YYABORT; }
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 848 "parser.y"
    { (yyval.val) = 0; }
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 849 "parser.y"
    { (yyval.val) = 1; }
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 856 "parser.y"
    { (yyval.elist) = new ExprList; }
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 857 "parser.y"
    { (yyval.elist) = (yyvsp[(1) - (1)].elist); }
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 863 "parser.y"
    { (yyval.elist) = (yyvsp[(2) - (3)].elist); }
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 867 "parser.y"
    { (yyval.elist) = new ExprList; (yyval.elist)->push_back((yyvsp[(1) - (1)].expression));  }
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 868 "parser.y"
    { (yyval.elist) = (yyvsp[(1) - (3)].elist); (yyval.elist)->push_back((yyvsp[(3) - (3)].expression)); }
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 869 "parser.y"
    { raise_error("Error in arg list"); YYABORT; }
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 874 "parser.y"
    { (yyval.expression) = (yyvsp[(2) - (3)].expression); }
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 878 "parser.y"
    { (yyval.expression) = NULL; }
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 879 "parser.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); }
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 883 "parser.y"
    {IEF_set();}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 885 "parser.y"
    {IEF_reset(); check_temp_context(); }
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 889 "parser.y"
    { do_loop_start((yyvsp[(2) - (2)].expression),false); }
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 893 "parser.y"
    { do_loop_end(false); }
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 898 "parser.y"
    { do_loop_end(true,true); }
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 899 "parser.y"
    { do_loop_end(false);     }
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 903 "parser.y"
    { label_here(); state.in_loop = true; }
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 904 "parser.y"
    { do_loop_start((yyvsp[(3) - (3)].expression),true); }
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 905 "parser.y"
    { do_loop_end(true); state.in_loop = false;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 910 "parser.y"
    { label_here(); push_label_stack(); state.in_loop = true;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 912 "parser.y"
    { do_do_end((yyvsp[(5) - (5)].expression)); state.in_loop = false; }
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 916 "parser.y"
    { code().compile((yyvsp[(1) - (2)].expression),DROP_VALUE); }
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 921 "parser.y"
    { state.init_block(PLAIN_BLOCK); }
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 922 "parser.y"
    { label_here();	state.in_loop = true; }
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 924 "parser.y"
    { do_loop_start((yyvsp[(6) - (9)].expression),true); }
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 925 "parser.y"
    { do_for_end((yyvsp[(8) - (11)].expression));    state.in_loop = false;
								 state.finalize_block();
							   }
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 931 "parser.y"
    { do_switch((yyvsp[(3) - (4)].expression)); }
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 936 "parser.y"
    { if (!do_return ((yyvsp[(2) - (3)].expression))) { check_error(); YYABORT; }  }
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 941 "parser.y"
    { do_case ((yyvsp[(2) - (3)].expression));   }
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 943 "parser.y"
    { do_case(NULL);  }
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 947 "parser.y"
    { if (!do_break_continue(BREAK)) { check_error(); YYABORT; } }
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 951 "parser.y"
    { if (!do_break_continue(CONTINUE)) { check_error(); YYABORT; } }
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 958 "parser.y"
    { do_end_try_catch_block(true); }
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 963 "parser.y"
    { state.init_block(PLAIN_BLOCK); IEF_set(); 
	do_start_try_block();  }
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 971 "parser.y"
    { state.finalize_block(); IEF_reset();
     do_end_try_catch_block(false);   }
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 977 "parser.y"
    { state.init_block(PLAIN_BLOCK); IEF_set(); 
    do_start_catch_block(); if (check_error()) YYABORT; }
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 989 "parser.y"
    { do_throw((yyvsp[(2) - (3)].expression)); }
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 995 "parser.y"
    { (yyval.ctype) = AsTType((yyvsp[(1) - (1)].entry)->type); }
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 996 "parser.y"
    { (yyval.ctype) = (yyvsp[(1) - (1)].ctype); }
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 1001 "parser.y"
    { last_type_entry = (yyvsp[(1) - (1)].entry); (yyval.ctype) = AsTType((yyvsp[(1) - (1)].entry)->type); }
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 1002 "parser.y"
    { (yyval.ctype) = (yyvsp[(1) - (1)].ctype); }
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 1003 "parser.y"
    { (yyval.ctype) = (yyvsp[(2) - (3)].ctype); }
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 1008 "parser.y"
    { (yyval.ctype) = AsTType((yyvsp[(1) - (1)].entry)->type); }
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 1009 "parser.y"
    { (yyval.ctype) = (yyvsp[(1) - (1)].ctype); }
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 1010 "parser.y"
    { (yyval.ctype) = (yyvsp[(2) - (3)].ctype); }
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 1015 "parser.y"
    { (yyval.ctype) = AsTType(Template::get_template_type((yyvsp[(1) - (2)].entry),(yyvsp[(2) - (2)].typelist))); }
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 1020 "parser.y"
    { (yyval.ctype) = AsTType(Template::get_template_type((yyvsp[(1) - (2)].entry),(yyvsp[(2) - (2)].typelist))); }
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 1026 "parser.y"
    { Template::do_template_header((yyvsp[(2) - (2)].typelist)); }
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 1032 "parser.y"
    { Template::do_function_template(); 
  	if (yychar != YYEMPTY) yyclearin;
  }
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 1039 "parser.y"
    {
    dcl_reset();    
    Template::do_class_template((yyvsp[(1) - (2)].val),(yyvsp[(2) - (2)].str),yychar,NULL);
	if (yychar != YYEMPTY) yyclearin;
   }
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 1045 "parser.y"
    {
    dcl_reset();        
    Template::do_class_template((yyvsp[(1) - (3)].val),(yyvsp[(2) - (3)].str),yychar,(yyvsp[(3) - (3)].typelist));
	if (yychar != YYEMPTY) yyclearin;
   }
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 1058 "parser.y"
    { dcl_set(); (yyval.val) = (yyvsp[(2) - (2)].val); }
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 1061 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);                     }
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 1062 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].entry)->name.c_str();       }
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 1066 "parser.y"
    { dcl_set(true); state.begin_templ_list(); }
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 1068 "parser.y"
    { dcl_reset();   state.end_templ_list();   }
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 1072 "parser.y"
    { (yyval.typelist) = new TypeList; }
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 1073 "parser.y"
    { (yyval.typelist) = (yyvsp[(2) - (3)].typelist); }
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 1078 "parser.y"
    { (yyval.typelist) = new TypeList; (yyval.typelist)->push_back(AsType((yyvsp[(1) - (1)].ctype))); }
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 1079 "parser.y"
    { (yyval.typelist) = (yyvsp[(1) - (3)].typelist); (yyval.typelist)->push_back(AsType((yyvsp[(3) - (3)].ctype)));   }
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 1083 "parser.y"
    { (yyval.str) = (yyvsp[(2) - (2)].str); }
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 1084 "parser.y"
    { (yyval.str) = (yyvsp[(2) - (2)].entry)->name.c_str(); }
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 1088 "parser.y"
    {
   string c = (yyvsp[(1) - (1)].str);
   (yyval.ctype) = AsTType(Template::dummy(t_null,c));
  }
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 1096 "parser.y"
    {
                     (yyval.ctype) = AsTType(Template::dummy(AsType((yyvsp[(1) - (1)].ctype)),state.token_stack.pop()));
	                 dcl_reset();  tpop();
	               }
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 1100 "parser.y"
    { (yyval.ctype) = AsTType(Template::dummy((yyvsp[(1) - (1)].entry))); }
    break;

  case 357:

/* Line 1455 of yacc.c  */
#line 1101 "parser.y"
    { (yyval.ctype) = (yyvsp[(1) - (1)].ctype); }
    break;



/* Line 1455 of yacc.c  */
#line 4834 "y.tab.c"
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
      yyerror (YY_("syntax error"));
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
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1105 "parser.y"
  




