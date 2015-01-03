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
#line 9 "parser.y" /* yacc.c:339  */

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


#line 164 "parser.tab.c" /* yacc.c:339  */

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
   by #include "parser.tab.h".  */
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
#line 107 "parser.y" /* yacc.c:355  */

  int       val; 
  long      ctype;
  char*     str;
  Entry*    entry;
  Expr*     expression;
  ExprList *elist;
  Class    *classptr;
  TypeList *typelist;

#line 335 "parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 350 "parser.tab.c" /* yacc.c:358  */

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
       0,   166,   166,   168,   169,   170,   173,   173,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   210,   219,
     218,   224,   225,   229,   239,   240,   247,   254,   257,   261,
     269,   277,   278,   279,   292,   293,   294,   297,   298,   301,
     304,   309,   311,   313,   315,   319,   324,   326,   325,   332,
     333,   334,   337,   346,   354,   357,   358,   361,   362,   363,
     364,   367,   368,   369,   370,   373,   375,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   395,   396,
     397,   402,   405,   408,   408,   413,   417,   418,   424,   430,
     431,   432,   433,   435,   436,   437,   440,   441,   442,   444,
     447,   449,   452,   454,   455,   456,   457,   463,   471,   480,
     481,   482,   484,   485,   491,   493,   494,   498,   501,   501,
     505,   511,   513,   514,   516,   517,   526,   527,   528,   530,
     530,   532,   532,   532,   534,   535,   536,   538,   539,   543,
     544,   546,   547,   548,   553,   555,   555,   561,   560,   573,
     576,   580,   580,   581,   590,   591,   590,   598,   599,   601,
     602,   603,   606,   611,   612,   613,   619,   620,   619,   627,
     628,   631,   641,   643,   645,   650,   650,   650,   654,   655,
     661,   665,   669,   672,   672,   672,   672,   672,   673,   673,
     673,   673,   673,   675,   676,   678,   681,   684,   685,   687,
     690,   690,   690,   690,   692,   697,   698,   699,   701,   702,
     703,   704,   705,   706,   707,   709,   710,   712,   713,   714,
     715,   716,   717,   718,   719,   720,   722,   723,   725,   726,
     727,   728,   732,   736,   737,   738,   739,   742,   742,   745,
     747,   748,   749,   751,   754,   757,   761,   762,   763,   764,
     765,   766,   768,   771,   774,   773,   779,   778,   783,   782,
     788,   791,   793,   794,   799,   800,   803,   808,   809,   810,
     814,   817,   818,   821,   821,   826,   829,   833,   832,   837,
     838,   837,   843,   843,   847,   848,   849,   852,   853,   855,
     852,   861,   861,   863,   867,   869,   872,   875,   881,   886,
     885,   891,   898,   897,   903,   904,   907,   913,   914,   918,
     919,   920,   924,   925,   926,   929,   933,   938,   942,   949,
     955,   963,   963,   966,   969,   970,   973,   975,   978,   979,
     983,   984,   987,   988,   991,   998,  1002,  1003
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
  "CHAR", "VOID", "BOOL", "TYPEDEF", "CLASS", "STRUCT", "ENUM", "OPERATOR",
  "GOTO", "UNION", "STATIC_CAST", "CONST_CAST", "DYNAMIC_CAST",
  "REINTERPRET_CAST", "STRUCT_X", "CLASS_X", "STRUCT_Y", "CLASS_Y",
  "UNION_Y", "IF", "ELSE", "WHILE", "DO", "FOR", "SWITCH", "CASE",
  "RETURN", "CONTINUE", "BREAK", "DEFAULT", "NAMESPACE", "USING", "TRY",
  "CATCH", "THROW", "TEMPLATE", "EXTERN", "THREEDOT", "TYPEOF", "EXPLICIT",
  "FRIEND", "LAMBDA", "FAKE_INIT_LIST", "CONST", "STATIC", "STDCALL",
  "API", "VIRTUAL", "PRIVATE", "PROTECTED", "PUBLIC", "COMMA", "ASSIGN",
  "MUL_A", "DIV_A", "MOD_A", "ADD_A", "MINUS_A", "SHL_A", "SHR_A",
  "BAND_A", "BOR_A", "XOR_A", "ARITH_IF", "LOG_OR", "LOG_AND", "BIN_OR",
  "BIN_XOR", "BIN_AND", "EQUAL", "NOT_EQUAL", "LESS_THAN", "LEQ",
  "GREATER", "GEQ", "LSHIFT", "RSHIFT", "PLUS", "MINUS", "STAR", "DIVIDE",
  "MODULO", "MEMBER_ARROW", "MEMBER_DOT", "NEW", "DELETE", "TYPECAST",
  "DEREF", "ADDR", "UPLUS", "UMINUS", "LOG_NOT", "BIN_NOT", "INCR", "DECR",
  "SIZEOF", "TYPE_CONSTRUCT", "FUN_CALL", "ARRAY", "ARROW", "DOT",
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
  "templ_item_list", "class_item", "class_parm", "templ_item", YY_NULL
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

#define YYPACT_NINF -340

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-340)))

#define YYTABLE_NINF -333

#define yytable_value_is_error(Yytable_value) \
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
static const yytype_uint16 yydefact[] =
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
      -1,    76,    77,    78,   207,    79,    80,    81,   150,   323,
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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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
#line 169 "parser.y" /* yacc.c:1646  */
    {statement_end();}
#line 2466 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 170 "parser.y" /* yacc.c:1646  */
    {statement_end();}
#line 2472 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 173 "parser.y" /* yacc.c:1646  */
    { state.init_block(PLAIN_BLOCK); IEF_set(); }
#line 2478 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 175 "parser.y" /* yacc.c:1646  */
    { state.finalize_block(); IEF_reset();}
#line 2484 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 183 "parser.y" /* yacc.c:1646  */
    {expression_end((yyvsp[-1].expression));}
#line 2490 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 206 "parser.y" /* yacc.c:1646  */
    { raise_error("Error in statement"); YYABORT; }
#line 2496 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 211 "parser.y" /* yacc.c:1646  */
    { 
    Type dt = tpop();
	dcl_reset();
	state.check_dcl_init(dt);
 }
#line 2506 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 219 "parser.y" /* yacc.c:1646  */
    { state.in_typedef = true; }
#line 2512 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 221 "parser.y" /* yacc.c:1646  */
    { state.in_typedef = false; }
#line 2518 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 230 "parser.y" /* yacc.c:1646  */
    {
   dcl_set();
   state.token_stack.push((yyvsp[0].classptr)->constructor_name());
   tpush(t_void);
   state.in_construct_destruct = IsConstructor;
   (yyval.classptr) = (yyvsp[0].classptr);
  }
#line 2530 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 239 "parser.y" /* yacc.c:1646  */
    {}
#line 2536 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 241 "parser.y" /* yacc.c:1646  */
    {
  state.token_stack.TOS() = (yyvsp[0].classptr)->destructor_name();
  state.in_construct_destruct = IsDestructor;
}
#line 2545 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 248 "parser.y" /* yacc.c:1646  */
    { 
   state.token_stack.push(CONVERSION_OPNAME);
   ttpush((yyvsp[-1].ctype)); (yyval.ctype) = (yyvsp[-1].ctype);
  }
#line 2554 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 255 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype)=(yyvsp[-3].ctype); stots((yyval.ctype)); state.member_is_const = (yyvsp[-1].val); gFunInit = (yyvsp[0].expression); }
#line 2560 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 258 "parser.y" /* yacc.c:1646  */
    { state.modifier = Explicit; }
#line 2566 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 262 "parser.y" /* yacc.c:1646  */
    {  
   state.declare_function(t_void,state.token_stack.pop());
   tpop();
   check_error();
 }
#line 2576 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 270 "parser.y" /* yacc.c:1646  */
    {
   state.declare_function(AsType((yyvsp[-1].ctype)),state.token_stack.pop(), gFunInit); 
   dcl_reset();
   gFunInit = NULL;
   tpop();
   check_error();
 }
#line 2588 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 280 "parser.y" /* yacc.c:1646  */
    { 
    state.declare_function(AsType((yyvsp[-1].ctype)),state.token_stack.pop());
	tpop();
	check_error();
  }
#line 2598 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 292 "parser.y" /* yacc.c:1646  */
    { state.extern_flag = false; }
#line 2604 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 293 "parser.y" /* yacc.c:1646  */
    { state.extern_flag_C = false; }
#line 2610 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 294 "parser.y" /* yacc.c:1646  */
    { state.extern_flag_C = false; }
#line 2616 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 301 "parser.y" /* yacc.c:1646  */
    { state.extern_flag_C = true; }
#line 2622 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 304 "parser.y" /* yacc.c:1646  */
    { state.extern_flag = true; }
#line 2628 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 310 "parser.y" /* yacc.c:1646  */
    { }
#line 2634 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 312 "parser.y" /* yacc.c:1646  */
    {}
#line 2640 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 314 "parser.y" /* yacc.c:1646  */
    {}
#line 2646 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 316 "parser.y" /* yacc.c:1646  */
    {}
#line 2652 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 326 "parser.y" /* yacc.c:1646  */
    {   state.init_block(CONSTRUCTOR_BLOCK);  }
#line 2658 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 328 "parser.y" /* yacc.c:1646  */
    {  check_error(); state.in_method = true; }
#line 2664 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 338 "parser.y" /* yacc.c:1646  */
    { 
	 ((Class*)state.context().parent_context())
	    ->add_class_init_list(AsType((yyvsp[-1].ctype)).as_class()->entry(),(yyvsp[0].elist));
	 /* fix 1.2.3a Can crash UC if we don't catch errors in the init list */
	 if (check_error()) YYABORT;  
	}
#line 2675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 347 "parser.y" /* yacc.c:1646  */
    { ((Class*)state.context().parent_context())
	      ->add_class_init_list((yyvsp[-1].entry),(yyvsp[0].elist));
	 if (check_error()) YYABORT;
    }
#line 2684 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 355 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[0].ctype);  }
#line 2690 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 357 "parser.y" /* yacc.c:1646  */
    { (yyval.val)=0; }
#line 2696 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 358 "parser.y" /* yacc.c:1646  */
    { (yyval.val)=1; }
#line 2702 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 361 "parser.y" /* yacc.c:1646  */
    {dcl_set();}
#line 2708 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 362 "parser.y" /* yacc.c:1646  */
    {dcl_set();}
#line 2714 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 363 "parser.y" /* yacc.c:1646  */
    {dcl_set(); tots().make_const();}
#line 2720 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 364 "parser.y" /* yacc.c:1646  */
    {dcl_set(); tots().make_const();}
#line 2726 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 367 "parser.y" /* yacc.c:1646  */
    {state.modifier = Static;  }
#line 2732 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 368 "parser.y" /* yacc.c:1646  */
    {state.modifier = Virtual; }
#line 2738 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 369 "parser.y" /* yacc.c:1646  */
    {state.modifier = Stdcall; }
#line 2744 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 370 "parser.y" /* yacc.c:1646  */
    {state.modifier = Api;     }
#line 2750 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 373 "parser.y" /* yacc.c:1646  */
    {dcl_set(false);}
#line 2756 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 375 "parser.y" /* yacc.c:1646  */
    {dcl_reset();}
#line 2762 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 377 "parser.y" /* yacc.c:1646  */
    { ttpush((yyvsp[0].ctype));  }
#line 2768 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 378 "parser.y" /* yacc.c:1646  */
    { tpush(typeof_op((yyvsp[-1].expression))); }
#line 2774 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 379 "parser.y" /* yacc.c:1646  */
    { }
#line 2780 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 380 "parser.y" /* yacc.c:1646  */
    { tots().make_unsigned(); }
#line 2786 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 381 "parser.y" /* yacc.c:1646  */
    { tpush(t_int); tots().make_unsigned(); }
#line 2792 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 382 "parser.y" /* yacc.c:1646  */
    { tpush(t_float);  }
#line 2798 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 383 "parser.y" /* yacc.c:1646  */
    { tpush(t_double); }
#line 2804 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 384 "parser.y" /* yacc.c:1646  */
    { tpush(t_bool); }
#line 2810 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 385 "parser.y" /* yacc.c:1646  */
    { tpush(t_void); }
#line 2816 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 386 "parser.y" /* yacc.c:1646  */
    { }
#line 2822 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 387 "parser.y" /* yacc.c:1646  */
    { }
#line 2828 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 395 "parser.y" /* yacc.c:1646  */
    { tpush(t_int);   }
#line 2834 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 396 "parser.y" /* yacc.c:1646  */
    { tpush(t_short); }
#line 2840 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 397 "parser.y" /* yacc.c:1646  */
    { tpush(t_long);  }
#line 2846 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 402 "parser.y" /* yacc.c:1646  */
    { tpush(t_char);  }
#line 2852 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 405 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = incr_ptr((yyvsp[-1].ctype)); }
#line 2858 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 408 "parser.y" /* yacc.c:1646  */
    {dcl_set(false);}
#line 2864 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 410 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.expression) = (yyvsp[-1].expression); }
#line 2870 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 413 "parser.y" /* yacc.c:1646  */
    { 
    (yyval.ctype)=ttots();
    state.token_stack.push("");
}
#line 2879 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 417 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype)=(yyvsp[0].ctype);   }
#line 2885 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 419 "parser.y" /* yacc.c:1646  */
    { 
    Type t = AsType((yyvsp[-1].ctype));
    t.decr_pointer();
    (yyval.ctype) = AsTType(state.signature_type(t));
 }
#line 2895 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 426 "parser.y" /* yacc.c:1646  */
    { 
     state.class_dcl = AsType((yyvsp[-5].ctype));
     (yyval.ctype) = AsTType(state.signature_type(AsType((yyvsp[-3].ctype)))); 
}
#line 2904 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 430 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = incr_ptr((yyvsp[0].ctype));         }
#line 2910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 431 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = make_ref((yyvsp[0].ctype));         }
#line 2916 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 432 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[-1].ctype);   state.class_dcl = AsType((yyvsp[-2].ctype)); }
#line 2922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 434 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[-1].ctype);   state.class_dcl = AsType((yyvsp[-2].ctype)); }
#line 2928 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 435 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = make_array((yyvsp[-1].ctype),(yyvsp[0].expression)); check_error();   }
#line 2934 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 436 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = make_array((yyvsp[-1].ctype),(yyvsp[0].expression)); check_error();   }
#line 2940 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 437 "parser.y" /* yacc.c:1646  */
    { raise_error("Error in type expression"); YYABORT; }
#line 2946 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 440 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = ttots(); }
#line 2952 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 441 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = incr_ptr((yyvsp[0].ctype)); }
#line 2958 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 442 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = make_ref((yyvsp[0].ctype)); }
#line 2964 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 444 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype)=ttots(); state.token_stack.push((yyvsp[0].str)); }
#line 2970 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 447 "parser.y" /* yacc.c:1646  */
    { dcl_set(false); state.begin_args(); }
#line 2976 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 449 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); }
#line 2982 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 458 "parser.y" /* yacc.c:1646  */
    { 
   state.add_to_arg_list(t_void,"...",0);
 }
#line 2990 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 464 "parser.y" /* yacc.c:1646  */
    {  
  state.add_to_arg_list(AsType((yyvsp[-1].ctype)),state.token_stack.pop(),(yyvsp[0].expression));
  tpop();
  dcl_reset();
}
#line 3000 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 472 "parser.y" /* yacc.c:1646  */
    {
  string name = state.token_stack.pop();
  Type t = AsType((yyvsp[-1].ctype));
  temp_context()->reserved_space(t.size());
  state.add_variable(t,name,(yyvsp[0].expression),state.modifier);
  if (check_error()) YYABORT;
  }
#line 3012 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 484 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=NULL; }
#line 3018 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 485 "parser.y" /* yacc.c:1646  */
    {(yyval.expression)=(yyvsp[0].expression);}
#line 3024 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 491 "parser.y" /* yacc.c:1646  */
    { dcl_set(false); }
#line 3030 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 493 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=NULL; }
#line 3036 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 496 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.expression)=(yyvsp[0].expression); }
#line 3042 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 499 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=expr_list_op((yyvsp[0].elist),true); }
#line 3048 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 501 "parser.y" /* yacc.c:1646  */
    { enter_arglist();}
#line 3054 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 503 "parser.y" /* yacc.c:1646  */
    {leave_arglist(); dcl_reset(); (yyval.expression)=expr_list_op((yyvsp[-1].elist),false); }
#line 3060 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 506 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new Expr(ECONST,t_void,(yyvsp[0].entry),NULL); }
#line 3066 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 511 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = (yyvsp[-1].elist); }
#line 3072 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 513 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 3078 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 514 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_list_op((yyvsp[0].elist),false); }
#line 3084 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 516 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = new ExprList; (yyval.elist)->push_back((yyvsp[0].expression));  }
#line 3090 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 517 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = (yyvsp[-2].elist); (yyval.elist)->push_back((yyvsp[0].expression)); }
#line 3096 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 526 "parser.y" /* yacc.c:1646  */
    {(yyval.val)=Public;}
#line 3102 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 527 "parser.y" /* yacc.c:1646  */
    {(yyval.val)=Private;}
#line 3108 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 528 "parser.y" /* yacc.c:1646  */
    {(yyval.val)=Protected;}
#line 3114 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 530 "parser.y" /* yacc.c:1646  */
    { (yyval.val)=Default; }
#line 3120 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 534 "parser.y" /* yacc.c:1646  */
    { (yyval.val) = CLASS; }
#line 3126 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 535 "parser.y" /* yacc.c:1646  */
    { (yyval.val) = STRUCT; }
#line 3132 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 536 "parser.y" /* yacc.c:1646  */
    { (yyval.val) = UNION;  }
#line 3138 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 538 "parser.y" /* yacc.c:1646  */
    { (yyval.val)=NotDerived; }
#line 3144 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 540 "parser.y" /* yacc.c:1646  */
    { (yyval.val)=(yyvsp[-1].val); state.class_dcl = AsType((yyvsp[0].ctype)); }
#line 3150 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 543 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str);  }
#line 3156 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 544 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].entry)->name.c_str(); }
#line 3162 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 546 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = "";   }
#line 3168 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 547 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str);   }
#line 3174 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 549 "parser.y" /* yacc.c:1646  */
    {
    PClass pc = AsType((yyvsp[0].ctype)).as_class();
    (yyval.str) = pc->name().c_str();
}
#line 3183 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 553 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].entry)->name.c_str(); }
#line 3189 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 555 "parser.y" /* yacc.c:1646  */
    { dcl_set();}
#line 3195 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 555 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.str) = (yyvsp[0].str);  }
#line 3201 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 561 "parser.y" /* yacc.c:1646  */
    { 
	   tpush(state.add_class((yyvsp[-3].val),(yyvsp[-2].str),(yyvsp[-1].val),state.class_dcl));
       if (check_error()) YYABORT;
	   state.init_block(CLASS_BLOCK); IEF_set();
       typedef_stack.push(state.in_typedef);
       state.in_typedef = false;
      }
#line 3213 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 569 "parser.y" /* yacc.c:1646  */
    {
	   state.finalize_block(); IEF_reset();
  	   state.in_typedef = typedef_stack.pop(); 
	 }
#line 3222 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 574 "parser.y" /* yacc.c:1646  */
    { tpush(state.add_class((yyvsp[-1].val),(yyvsp[0].str),ForwardClass,t_void)); }
#line 3228 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 577 "parser.y" /* yacc.c:1646  */
    { state.set_access_mode((yyvsp[-1].val)); }
#line 3234 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 580 "parser.y" /* yacc.c:1646  */
    { state.in_friend_dcl = true; }
#line 3240 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 581 "parser.y" /* yacc.c:1646  */
    { state.add_friend_class((yyvsp[-2].val)); }
#line 3246 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 590 "parser.y" /* yacc.c:1646  */
    { dcl_set(); }
#line 3252 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 591 "parser.y" /* yacc.c:1646  */
    {
    tpush(state.do_enum(tag_name));
    if (check_error()) YYABORT;
   }
#line 3261 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 596 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); }
#line 3267 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 601 "parser.y" /* yacc.c:1646  */
    {(yyval.str)=NULL; tag_name="";}
#line 3273 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 602 "parser.y" /* yacc.c:1646  */
    {(yyval.str)=(yyvsp[0].str); tag_name=(yyvsp[0].str);}
#line 3279 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 603 "parser.y" /* yacc.c:1646  */
    {(yyval.str)=""; tag_name=(yyvsp[0].entry)->name.c_str();}
#line 3285 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 607 "parser.y" /* yacc.c:1646  */
    { 
  state.add_enum(tots(),(yyvsp[-1].str),(yyvsp[0].expression));
 }
#line 3293 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 619 "parser.y" /* yacc.c:1646  */
    { dcl_set(); }
#line 3299 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 620 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); 
    state.add_namespace((yyvsp[0].str) ? (yyvsp[0].str) : "");
    state.in_class = true;
    if (check_error()) YYABORT;
   }
#line 3309 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 627 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = NULL; }
#line 3315 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 628 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str);  }
#line 3321 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 633 "parser.y" /* yacc.c:1646  */
    { 
   	if ((Namespace *)(yyvsp[-1].entry)->data != &state.context()) 
      state.context().inject_namespace((Namespace *)(yyvsp[-1].entry)->data);
    else raise_error("Cannot inject a namespace into itself");
    if (check_error()) YYABORT;
   }
#line 3332 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 642 "parser.y" /* yacc.c:1646  */
    {  state.context().inject_entry((yyvsp[-1].entry));  }
#line 3338 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 644 "parser.y" /* yacc.c:1646  */
    { state.context().inject_entry((yyvsp[-1].entry)); }
#line 3344 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 646 "parser.y" /* yacc.c:1646  */
    { state.context().inject_entry(last_type_entry);  }
#line 3350 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 650 "parser.y" /* yacc.c:1646  */
    { dcl_set(true); }
#line 3356 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 650 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); }
#line 3362 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 651 "parser.y" /* yacc.c:1646  */
    { do_goto((yyvsp[-2].str)); }
#line 3368 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 654 "parser.y" /* yacc.c:1646  */
    { goto_label_new((yyvsp[-1].str)); }
#line 3374 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 655 "parser.y" /* yacc.c:1646  */
    { goto_label_existing((yyvsp[-1].entry)); }
#line 3380 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 662 "parser.y" /* yacc.c:1646  */
    { state.begin_scope(AsType((yyvsp[-1].ctype))); (yyval.ctype) = (yyvsp[-1].ctype); }
#line 3386 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 666 "parser.y" /* yacc.c:1646  */
    { state.begin_scope(&global()); }
#line 3392 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 669 "parser.y" /* yacc.c:1646  */
    { state.end_scope(); }
#line 3398 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 677 "parser.y" /* yacc.c:1646  */
    { (yyval.entry) = (yyvsp[-1].entry); }
#line 3404 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 679 "parser.y" /* yacc.c:1646  */
    { (yyval.entry) = (yyvsp[-1].entry); }
#line 3410 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 682 "parser.y" /* yacc.c:1646  */
    {   if (check_error()) YYABORT;   (yyval.expression) = (yyvsp[0].expression); }
#line 3416 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 684 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = NULL; }
#line 3422 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 685 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[-1].expression); }
#line 3428 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 688 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.ctype)=(yyvsp[0].ctype); state.token_stack.pop(); tpop(); }
#line 3434 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 693 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype)=(yyvsp[-1].ctype); }
#line 3440 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 697 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) =  entry_op((yyvsp[0].entry)); }
#line 3446 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 698 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) =  entry_op((yyvsp[0].entry)); }
#line 3452 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 699 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) =  (yyvsp[-1].expression); }
#line 3458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 701 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(STAR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3464 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 702 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(DIVIDE,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3470 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 703 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(MODULO,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3476 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 704 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(PLUS,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3482 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 705 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(MINUS,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3488 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 706 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(BIN_AND,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3494 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 707 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_op(BIN_OR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3500 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 709 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=(yyvsp[0].expression); }
#line 3506 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 710 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=unary_op(UMINUS,(yyvsp[0].expression)); }
#line 3512 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 712 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(LOG_NOT,(yyvsp[0].expression),NULL); }
#line 3518 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 713 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(LESS_THAN,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3524 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 714 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(GREATER,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3530 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 715 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(LEQ,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3536 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 716 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(GEQ,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3542 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 717 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=equal_op((yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3548 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 718 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(NOT_EQUAL,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3554 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 719 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(LOG_AND,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3560 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 720 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=relational_op(LOG_OR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3566 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 722 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=assign_op((yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3572 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 723 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=compound_assign_op((yyvsp[-1].val),(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3578 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 725 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=inc_dec_op(INCR,(yyvsp[-1].expression),true); }
#line 3584 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 726 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=inc_dec_op(INCR,(yyvsp[0].expression),false); }
#line 3590 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 727 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=inc_dec_op(DECR,(yyvsp[-1].expression),true); }
#line 3596 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 728 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=inc_dec_op(DECR,(yyvsp[0].expression),false); }
#line 3602 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 732 "parser.y" /* yacc.c:1646  */
    { 
    if ((yyvsp[-1].expression)->is_entry()) (yyval.expression) = sizeof_op(size_of_entry((yyvsp[-1].expression)->entry()));
	              else  (yyval.expression) = sizeof_op((yyvsp[-1].expression)->type().size());
  }
#line 3611 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 736 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=sizeof_op(AsType((yyvsp[-1].ctype)).size());  }
#line 3617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 737 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=arith_if_op((yyvsp[-4].expression),(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3623 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 738 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=bin_op(COMMA,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 740 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new_op(tpop(),(yyvsp[0].expression),NULL);  }
#line 3635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 742 "parser.y" /* yacc.c:1646  */
    { tpush((yyvsp[0].entry)->type); }
#line 3641 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 743 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new_op(tpop(),NULL,(yyvsp[0].elist));  }
#line 3647 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 746 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new_op(tpop(),NULL,(yyvsp[0].elist));  }
#line 3653 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 747 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = delete_op((yyvsp[0].expression),(yyvsp[-1].val)==1); }
#line 3659 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 748 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = deref_op((yyvsp[0].expression)); }
#line 3665 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 749 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = addr_op((yyvsp[0].expression)); }
#line 3671 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 752 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = typecast_op((yyvsp[-4].val),AsType((yyvsp[-3].ctype)),(yyvsp[-1].expression)); }
#line 3677 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 755 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = function_cast_op((yyvsp[-1].entry)->type /*AsType($1)*/,(yyvsp[0].elist)); }
#line 3683 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 758 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = typecast_op(REINTERPRET_CAST,AsType((yyvsp[-2].ctype)),(yyvsp[0].expression)); }
#line 3689 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 761 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=unary_op(BIN_NOT,(yyvsp[0].expression)); }
#line 3695 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 762 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=bin_op(LSHIFT,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 763 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=bin_op(RSHIFT,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3707 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 764 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=bin_op(BIN_AND,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3713 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 765 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=bin_op(BIN_XOR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3719 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 766 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=bin_op(BIN_OR,(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 3725 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 769 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=array_op((yyvsp[-3].expression), (yyvsp[-1].expression)); }
#line 3731 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 771 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=function_op((yyvsp[-1].expression),(yyvsp[0].elist)); }
#line 3737 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 774 "parser.y" /* yacc.c:1646  */
    {dcl_set(); }
#line 3743 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 776 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.expression)=selection_op((yyvsp[-3].expression),(yyvsp[0].str),false);  }
#line 3749 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 779 "parser.y" /* yacc.c:1646  */
    {dcl_set();}
#line 3755 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 781 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.expression)=selection_op((yyvsp[-3].expression),(yyvsp[0].str),true);  }
#line 3761 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 783 "parser.y" /* yacc.c:1646  */
    {dcl_set();}
#line 3767 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 785 "parser.y" /* yacc.c:1646  */
    { dcl_reset(); (yyval.expression)=selection_op((yyvsp[-3].expression),(yyvsp[0].str),true,true);  }
#line 3773 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 789 "parser.y" /* yacc.c:1646  */
    { (yyval.expression)=lambda_op(0);   }
#line 3779 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 791 "parser.y" /* yacc.c:1646  */
    { raise_error("error in expression"); YYABORT; }
#line 3785 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 793 "parser.y" /* yacc.c:1646  */
    { (yyval.val) = 0; }
#line 3791 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 794 "parser.y" /* yacc.c:1646  */
    { (yyval.val) = 1; }
#line 3797 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 799 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = new ExprList; }
#line 3803 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 800 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = (yyvsp[0].elist); }
#line 3809 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 805 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = (yyvsp[-1].elist); }
#line 3815 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 808 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = new ExprList; (yyval.elist)->push_back((yyvsp[0].expression));  }
#line 3821 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 809 "parser.y" /* yacc.c:1646  */
    { (yyval.elist) = (yyvsp[-2].elist); (yyval.elist)->push_back((yyvsp[0].expression)); }
#line 3827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 810 "parser.y" /* yacc.c:1646  */
    { raise_error("Error in arg list"); YYABORT; }
#line 3833 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 814 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[-1].expression); }
#line 3839 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 817 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = NULL; }
#line 3845 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 818 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 3851 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 821 "parser.y" /* yacc.c:1646  */
    {IEF_set();}
#line 3857 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 823 "parser.y" /* yacc.c:1646  */
    {IEF_reset(); check_temp_context(); }
#line 3863 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 826 "parser.y" /* yacc.c:1646  */
    { do_loop_start((yyvsp[0].expression),false); }
#line 3869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 829 "parser.y" /* yacc.c:1646  */
    { do_loop_end(false); }
#line 3875 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 833 "parser.y" /* yacc.c:1646  */
    { do_loop_end(true,true); }
#line 3881 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 834 "parser.y" /* yacc.c:1646  */
    { do_loop_end(false);     }
#line 3887 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 837 "parser.y" /* yacc.c:1646  */
    { label_here(); state.in_loop = true; }
#line 3893 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 838 "parser.y" /* yacc.c:1646  */
    { do_loop_start((yyvsp[0].expression),true); }
#line 3899 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 839 "parser.y" /* yacc.c:1646  */
    { do_loop_end(true); state.in_loop = false;}
#line 3905 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 843 "parser.y" /* yacc.c:1646  */
    { label_here(); push_label_stack(); state.in_loop = true;}
#line 3911 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 845 "parser.y" /* yacc.c:1646  */
    { do_do_end((yyvsp[0].expression)); state.in_loop = false; }
#line 3917 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 848 "parser.y" /* yacc.c:1646  */
    { code().compile((yyvsp[-1].expression),DROP_VALUE); }
#line 3923 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 852 "parser.y" /* yacc.c:1646  */
    { state.init_block(PLAIN_BLOCK); }
#line 3929 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 853 "parser.y" /* yacc.c:1646  */
    { label_here();	state.in_loop = true; }
#line 3935 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 855 "parser.y" /* yacc.c:1646  */
    { do_loop_start((yyvsp[-3].expression),true); }
#line 3941 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 856 "parser.y" /* yacc.c:1646  */
    { do_for_end((yyvsp[-3].expression));    state.in_loop = false;
								 state.finalize_block();
							   }
#line 3949 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 861 "parser.y" /* yacc.c:1646  */
    { do_switch((yyvsp[-1].expression)); }
#line 3955 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 864 "parser.y" /* yacc.c:1646  */
    { if (!do_return ((yyvsp[-1].expression))) { check_error(); YYABORT; }  }
#line 3961 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 868 "parser.y" /* yacc.c:1646  */
    { do_case ((yyvsp[-1].expression));   }
#line 3967 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 870 "parser.y" /* yacc.c:1646  */
    { do_case(NULL);  }
#line 3973 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 873 "parser.y" /* yacc.c:1646  */
    { if (!do_break_continue(BREAK)) { check_error(); YYABORT; } }
#line 3979 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 876 "parser.y" /* yacc.c:1646  */
    { if (!do_break_continue(CONTINUE)) { check_error(); YYABORT; } }
#line 3985 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 882 "parser.y" /* yacc.c:1646  */
    { do_end_try_catch_block(true); }
#line 3991 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 886 "parser.y" /* yacc.c:1646  */
    { state.init_block(PLAIN_BLOCK); IEF_set(); 
	do_start_try_block();  }
#line 3998 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 893 "parser.y" /* yacc.c:1646  */
    { state.finalize_block(); IEF_reset();
     do_end_try_catch_block(false);   }
#line 4005 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 898 "parser.y" /* yacc.c:1646  */
    { state.init_block(PLAIN_BLOCK); IEF_set(); 
    do_start_catch_block(); if (check_error()) YYABORT; }
#line 4012 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 908 "parser.y" /* yacc.c:1646  */
    { do_throw((yyvsp[-1].expression)); }
#line 4018 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 913 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = AsTType((yyvsp[0].entry)->type); }
#line 4024 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 914 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4030 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 918 "parser.y" /* yacc.c:1646  */
    { last_type_entry = (yyvsp[0].entry); (yyval.ctype) = AsTType((yyvsp[0].entry)->type); }
#line 4036 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 919 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4042 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 920 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[-1].ctype); }
#line 4048 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 924 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = AsTType((yyvsp[0].entry)->type); }
#line 4054 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 925 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4060 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 926 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[-1].ctype); }
#line 4066 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 930 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = AsTType(Template::get_template_type((yyvsp[-1].entry),(yyvsp[0].typelist))); }
#line 4072 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 934 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = AsTType(Template::get_template_type((yyvsp[-1].entry),(yyvsp[0].typelist))); }
#line 4078 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 939 "parser.y" /* yacc.c:1646  */
    { Template::do_template_header((yyvsp[0].typelist)); }
#line 4084 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 944 "parser.y" /* yacc.c:1646  */
    { Template::do_function_template(); 
  	if (yychar != YYEMPTY) yyclearin;
  }
#line 4092 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 950 "parser.y" /* yacc.c:1646  */
    {
    dcl_reset();    
    Template::do_class_template((yyvsp[-1].val),(yyvsp[0].str),yychar,NULL);
	if (yychar != YYEMPTY) yyclearin;
   }
#line 4102 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 956 "parser.y" /* yacc.c:1646  */
    {
    dcl_reset();        
    Template::do_class_template((yyvsp[-2].val),(yyvsp[-1].str),yychar,(yyvsp[0].typelist));
	if (yychar != YYEMPTY) yyclearin;
   }
#line 4112 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 967 "parser.y" /* yacc.c:1646  */
    { dcl_set(); (yyval.val) = (yyvsp[0].val); }
#line 4118 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 969 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str);                     }
#line 4124 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 970 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].entry)->name.c_str();      }
#line 4130 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 973 "parser.y" /* yacc.c:1646  */
    { dcl_set(true); state.begin_templ_list(); }
#line 4136 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 975 "parser.y" /* yacc.c:1646  */
    { dcl_reset();   state.end_templ_list();   }
#line 4142 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 978 "parser.y" /* yacc.c:1646  */
    { (yyval.typelist) = new TypeList; }
#line 4148 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 979 "parser.y" /* yacc.c:1646  */
    { (yyval.typelist) = (yyvsp[-1].typelist); }
#line 4154 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 983 "parser.y" /* yacc.c:1646  */
    { (yyval.typelist) = new TypeList; (yyval.typelist)->push_back(AsType((yyvsp[0].ctype))); }
#line 4160 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 984 "parser.y" /* yacc.c:1646  */
    { (yyval.typelist) = (yyvsp[-2].typelist); (yyval.typelist)->push_back(AsType((yyvsp[0].ctype)));   }
#line 4166 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 987 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str); }
#line 4172 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 988 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].entry)->name.c_str(); }
#line 4178 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 991 "parser.y" /* yacc.c:1646  */
    {
    string c = (yyvsp[0].str);
    (yyval.ctype) = AsTType(Template::dummy(t_null,c));
   }
#line 4187 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 998 "parser.y" /* yacc.c:1646  */
    {
                      (yyval.ctype) = AsTType(Template::dummy(AsType((yyvsp[0].ctype)),state.token_stack.pop()));
	                  dcl_reset();  tpop();
	                }
#line 4196 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 1002 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = AsTType(Template::dummy((yyvsp[0].entry))); }
#line 4202 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 1003 "parser.y" /* yacc.c:1646  */
    { (yyval.ctype) = (yyvsp[0].ctype); }
#line 4208 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 4212 "parser.tab.c" /* yacc.c:1646  */
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
#line 1006 "parser.y" /* yacc.c:1906  */
  



