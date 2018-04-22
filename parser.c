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
#line 2 "parser.y" /* yacc.c:339  */

int yyerror(const char *);
int yylex(void);
#define YYDEBUG 1
#include <math.h>
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
char* vars[100];
double vals[100];
char* argslist[100];
char* argsvals[100];
int argscount = 0;
int countvars = 0;

FILE* outprod;

extern int yylineno;

double get_value(char* vars[], double vals[], int count, char* varname){
	double ans = 0.00;
	for(int i=0; i<count; i++){
		if(strcmp(vars[i], varname)==0){
			ans = vals[i];
		}
	}
	return ans;
}

#line 96 "parser.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif


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
    IDENT = 258,
    DOT = 259,
    NUM = 260,
    FLOAT = 261,
    STRING = 262,
    LP = 263,
    RP = 264,
    PLUS = 265,
    MINUS = 266,
    ASSIGN = 267,
    DIV = 268,
    MULT = 269,
    IF = 270,
    THEN = 271,
    ELIF = 272,
    ELSE = 273,
    BEG = 274,
    END = 275,
    GT = 276,
    LT = 277,
    GTEQ = 278,
    LTEQ = 279,
    EQ = 280,
    NEQ = 281,
    FOR = 282,
    WHILE = 283,
    DO = 284,
    LSQ = 285,
    RSQ = 286,
    COMMA = 287,
    SEMICOLON = 288,
    COLON = 289,
    NAME = 290,
    PROCESSOR = 291,
    ISRUN = 292,
    SUBJOBS = 293,
    GETCLSP = 294,
    RUN = 295,
    DISCJOB = 296,
    ISA = 297,
    CLSP = 298,
    L1MEM = 299,
    ARCHTYPE = 300,
    L2MEM = 301,
    LINK = 302,
    STPNT = 303,
    ENDPNT = 304,
    BW = 305,
    CHCAP = 306,
    MEMORY = 307,
    GETAVMEM = 308,
    MEMTYPE = 309,
    MEMSIZE = 310,
    JOB = 311,
    GETMEM = 312,
    JOBID = 313,
    FLOPS = 314,
    DEADLINE = 315,
    MEMREQ = 316,
    AFFINITY = 317,
    CLUSTER = 318,
    PROCESSORS = 319,
    TOPO = 320,
    LINKBW = 321,
    LINKCAP = 322,
    INCR = 323,
    DCR = 324,
    ENDALL = 325,
    PROCESSORSLIST = 326,
    JOBS = 327,
    SCHALGO = 328,
    PRIOLIST = 329,
    FINDEADLINE = 330,
    LOADBALALGO = 331,
    SCHEDULER = 332,
    SCHEDULE = 333
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 33 "parser.y" /* yacc.c:355  */

		int num;
		double decimal;
		char* string;

#line 218 "parser.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 233 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  49
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   508

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  135
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  307

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   333

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
      75,    76,    77,    78
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   129,   129,   130,   131,   134,   135,   136,   137,   138,
     139,   140,   149,   150,   151,   152,   153,   154,   155,   158,
     161,   162,   163,   164,   165,   166,   169,   172,   173,   174,
     177,   178,   182,   183,   187,   188,   189,   193,   194,   195,
     196,   197,   198,   202,   203,   204,   207,   210,   211,   212,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     227,   230,   231,   235,   236,   237,   238,   239,   242,   243,
     244,   247,   248,   249,   250,   251,   254,   255,   256,   257,
     258,   261,   264,   267,   270,   273,   276,   279,   282,   286,
     287,   290,   291,   292,   295,   296,   299,   300,   303,   304,
     307,   308,   312,   315,   316,   319,   320,   323,   324,   327,
     328,   332,   335,   336,   339,   340,   344,   347,   348,   351,
     352,   355,   356,   359,   360,   363,   364,   368,   371,   372,
     375,   376,   379,   380,   383,   384
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "DOT", "NUM", "FLOAT", "STRING",
  "LP", "RP", "PLUS", "MINUS", "ASSIGN", "DIV", "MULT", "IF", "THEN",
  "ELIF", "ELSE", "BEG", "END", "GT", "LT", "GTEQ", "LTEQ", "EQ", "NEQ",
  "FOR", "WHILE", "DO", "LSQ", "RSQ", "COMMA", "SEMICOLON", "COLON",
  "NAME", "PROCESSOR", "ISRUN", "SUBJOBS", "GETCLSP", "RUN", "DISCJOB",
  "ISA", "CLSP", "L1MEM", "ARCHTYPE", "L2MEM", "LINK", "STPNT", "ENDPNT",
  "BW", "CHCAP", "MEMORY", "GETAVMEM", "MEMTYPE", "MEMSIZE", "JOB",
  "GETMEM", "JOBID", "FLOPS", "DEADLINE", "MEMREQ", "AFFINITY", "CLUSTER",
  "PROCESSORS", "TOPO", "LINKBW", "LINKCAP", "INCR", "DCR", "ENDALL",
  "PROCESSORSLIST", "JOBS", "SCHALGO", "PRIOLIST", "FINDEADLINE",
  "LOADBALALGO", "SCHEDULER", "SCHEDULE", "$accept", "statements",
  "statement", "statement-with-else", "selection", "selection_prime",
  "selection-with-else", "selection-with-else_prime", "opt_block",
  "expression", "expr_temp", "RA_TERM", "expression_prime", "term",
  "term_prime", "factor", "array", "array_prime", "constructor",
  "function", "argsAll", "method", "argsRUN", "argsISRUN", "argsSUBJOBS",
  "argsGETCLSP", "argsDISCJOB", "argsGETAVMEM", "argsGETMEM", "argsPROC",
  "archterm", "nameterm", "isaterm", "clspterm", "l1memterm", "l2memterm",
  "argsLINK", "stpntterm", "endpntterm", "bwterm", "chcapterm", "argsMEM",
  "memtypeterm", "memsizeterm", "argsJOB", "jobidterm", "flopterm",
  "deadterm", "memreqterm", "affineterm", "argsCLUSTER", "processorsterm",
  "topoterm", "linkbwterm", "linkcapterm", YY_NULL
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
     325,   326,   327,   328,   329,   330,   331,   332,   333
};
# endif

#define YYPACT_NINF -219

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-219)))

#define YYTABLE_NINF -28

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     253,    14,   -48,  -219,  -219,    59,     0,     9,    22,    59,
      25,    32,    38,    67,    79,    82,    84,  -219,    36,   253,
    -219,    60,    28,    18,    29,  -219,    63,   -26,   445,    59,
      59,  -219,  -219,  -219,  -219,    11,    89,    59,   366,    59,
      71,    68,    62,    59,    59,    64,    53,    50,    54,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,    59,   125,
     125,  -219,   125,   125,  -219,  -219,   111,   112,   119,   121,
     126,  -219,     2,   103,   127,   105,   108,  -219,   131,    59,
     133,    59,  -219,  -219,   132,   134,    59,  -219,   141,  -219,
     147,   146,   150,    59,   149,   153,    59,   154,   158,    59,
     156,   160,    59,  -219,   -13,    18,    18,    29,    29,  -219,
      59,  -219,  -219,  -219,    59,   445,  -219,  -219,   159,   305,
     139,   163,    71,  -219,  -219,   151,  -219,  -219,  -219,  -219,
     152,  -219,  -219,   162,  -219,  -219,   164,  -219,  -219,   165,
    -219,  -219,  -219,  -219,   169,  -219,   170,   176,   177,   179,
     166,  -219,    59,    33,   182,   253,   191,   192,  -219,   183,
    -219,  -219,   184,   171,   172,    59,  -219,  -219,   167,   157,
     161,   148,   143,  -219,  -219,  -219,  -219,  -219,   445,   178,
      59,    59,    59,    15,   366,    59,   323,   323,   194,   195,
     200,   180,    59,   203,    59,   205,    59,   206,    59,   207,
      59,  -219,  -219,   190,   193,   216,   208,  -219,    59,   217,
    -219,  -219,  -219,  -219,   163,  -219,   198,  -219,   199,  -219,
     202,  -219,   204,  -219,   209,   214,   215,   305,  -219,   210,
     163,  -219,   201,   185,   427,  -219,   187,   173,    59,   220,
    -219,   226,    59,   231,   240,    59,   241,    59,   242,  -219,
     243,    59,   250,    59,   230,   305,   305,   255,  -219,   233,
    -219,   218,    59,  -219,   234,  -219,   238,   254,  -219,   256,
    -219,   163,   118,  -219,  -219,  -219,   259,   202,  -219,   212,
     211,   257,   264,   265,  -219,  -219,   267,    59,   275,    59,
      59,    59,  -219,   258,  -219,   202,   202,   260,   229,  -219,
    -219,   409,  -219,   276,    59,  -219,  -219
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    55,    54,    57,    56,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     4,     0,     3,
       8,     0,    32,    45,    49,    35,     0,     0,    75,     0,
       0,    52,    53,    50,    51,    55,     0,     0,     0,     0,
      62,     0,    95,     0,     0,   104,   113,   118,   129,     1,
       2,     7,    40,    39,    38,    37,    41,    42,     0,     0,
       0,    34,     0,     0,    46,     9,     0,     0,     0,     0,
       0,    36,    55,    73,     0,     0,     0,    59,     0,     0,
       0,     0,    60,    58,     0,     0,     0,    81,     0,    85,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,    55,    45,    45,    49,    49,    82,
       0,    84,    86,    87,     0,    75,    70,     5,     0,     0,
       0,     0,    62,    94,    63,     0,    68,    69,   103,    64,
       0,   112,    65,     0,   117,    66,     0,   128,    67,     0,
      43,    44,    48,    47,     0,    83,     0,     0,     0,     0,
      74,    72,     0,    55,     0,     0,     0,     0,    23,     0,
      19,    15,    20,     0,     0,     0,    10,    61,    97,   106,
     115,   120,   131,    76,    77,    78,    79,    80,    75,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     7,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,     6,     0,     0,     0,     0,    30,     0,     0,
      25,    24,    22,    21,     0,    96,     0,   105,     0,   114,
      92,   119,     0,   130,     0,     5,     0,     0,    31,     0,
       0,    11,    99,   108,     0,   111,   122,   133,     0,     0,
      26,    20,     0,    10,     0,     0,     0,     0,     0,    93,
       0,     0,     0,     0,     0,     0,     0,     0,    98,    92,
     107,   110,     0,   121,     0,   132,     0,     6,    29,    24,
      28,     0,     0,   101,    90,    88,     0,    92,    91,   124,
     135,    11,     0,     0,   109,   102,     0,     0,     0,     0,
       0,     0,   123,     0,   134,    92,    92,    92,   126,   127,
      89,     0,   100,     0,     0,   125,   116
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -219,   -18,   -35,  -208,  -219,  -219,  -219,  -219,  -114,    -5,
     237,  -219,   -45,    -2,   -39,    23,  -219,   175,  -219,  -110,
    -105,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
       1,  -218,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    18,    19,   159,    20,   160,   161,   240,   213,    21,
      22,    58,    61,    23,    64,    24,    41,    82,    25,    26,
      74,    71,    88,   144,   146,   147,    90,   148,   149,    85,
     273,   274,    86,   192,   245,   275,    92,    93,   194,   247,
     277,    95,    96,   196,    98,    99,   198,   251,   287,   304,
     101,   102,   200,   253,   289
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,    50,   235,    79,    40,   162,    27,   166,    37,   164,
     151,    66,    67,    68,   114,    27,   206,    38,    27,   239,
      33,    34,    28,    73,    75,    76,    29,    69,    59,    60,
      39,    70,    78,    42,    80,   207,    49,    27,    87,    89,
      43,    28,    62,    63,    30,   180,    44,   268,   270,    52,
      53,    54,    55,    56,    57,    31,    32,   105,   106,   285,
     140,   141,    35,   181,     2,     3,     4,     5,   142,   143,
      31,    32,   211,   201,   120,    45,   122,   299,   300,    31,
      32,   125,    31,    32,   158,   107,   108,    46,   130,     9,
      47,   133,    48,    51,   136,    10,    65,   139,    77,    83,
     231,    31,    32,    81,    84,   145,    13,    94,    97,   150,
      73,    14,    91,   241,   163,    15,   243,   164,   100,   109,
     110,    35,    16,     2,     3,     4,     5,   111,   104,   112,
       2,     3,     4,     5,   113,   115,   116,   183,   117,   118,
     119,   269,   121,   124,   123,   164,   164,   179,     9,   208,
     126,   210,   212,   248,    10,     9,   127,   281,   128,   129,
     190,   131,   132,   282,   283,    13,   134,   135,   137,   138,
      14,   152,   165,    73,    15,   203,   204,   205,   173,   174,
     209,    16,   155,   168,   169,   175,   176,   216,   177,   218,
     182,   220,   158,   222,   170,   224,   171,   172,   178,   184,
     185,   186,   187,   229,   188,   189,   193,   197,   199,   214,
     191,   202,   -14,   -16,   215,   217,   195,   219,   221,   223,
     210,   212,   163,   225,   226,   227,   230,   238,   228,   249,
     232,   233,   -12,   254,   234,   246,   236,   257,   255,   252,
     259,   237,   261,   242,   256,   244,   264,   250,   266,   -17,
     163,   163,   258,   260,   262,   263,     1,   278,     2,     3,
       4,     5,   265,   267,   271,   272,   279,   249,     6,   276,
     280,   284,   -13,   286,   -27,   -18,   290,   291,   288,   292,
       7,     8,   293,     9,   295,   296,   297,   294,   305,    10,
     298,   303,   301,    11,    12,   103,   249,   167,   302,   306,
      13,     0,     0,     0,     0,    14,     0,     0,   153,    15,
       2,     3,     4,     5,     0,     0,    16,     0,     0,     0,
     154,     0,     0,    17,   155,     0,     1,     0,     2,     3,
       4,     5,   156,   157,     0,     9,     0,     0,     6,     0,
       0,    10,   155,     0,     0,    11,    12,     0,     0,     0,
       7,     8,    13,     9,     0,     0,     0,    14,     0,    10,
       0,    15,     0,    11,    12,     0,     0,     0,    16,     1,
      13,     2,     3,     4,     5,    14,     0,     0,     0,    15,
       0,     6,     0,     0,     0,     0,    16,     0,     0,     0,
       0,     0,     0,     7,     8,     0,     9,     0,     0,     0,
       0,     0,    10,     0,     0,     0,    11,    12,     0,     0,
       0,     0,    35,    13,     2,     3,     4,     5,    14,     0,
       0,     0,    15,     0,     0,     0,     0,     0,     0,    16,
      35,     0,     2,     3,     4,     5,     0,     0,     0,     9,
       0,     0,     0,     0,   248,    10,     0,     0,    72,     0,
       2,     3,     4,     5,   282,     0,    13,     9,     0,     0,
       0,    14,   248,    10,     0,    15,     0,     0,     0,     0,
       0,     0,    16,     0,    13,     9,     0,     0,     0,    14,
       0,    10,     0,    15,     0,     0,     0,     0,     0,     0,
      16,     0,    13,     0,     0,     0,     0,    14,     0,     0,
       0,    15,     0,     0,     0,     0,     0,     0,    16
};

static const yytype_int16 yycheck[] =
{
       5,    19,   220,    38,     9,   119,     4,   121,     8,   119,
     115,    37,    38,    39,    12,     4,     1,     8,     4,   227,
      68,    69,     8,    28,    29,    30,    12,    53,    10,    11,
       8,    57,    37,     8,    39,    20,     0,     4,    43,    44,
       8,     8,    13,    14,    30,    12,     8,   255,   256,    21,
      22,    23,    24,    25,    26,    68,    69,    59,    60,   277,
     105,   106,     3,    30,     5,     6,     7,     8,   107,   108,
      68,    69,   186,   178,    79,     8,    81,   295,   296,    68,
      69,    86,    68,    69,   119,    62,    63,     8,    93,    30,
       8,    96,     8,    33,    99,    36,    33,   102,     9,    31,
     214,    68,    69,    32,    42,   110,    47,    54,    58,   114,
     115,    52,    48,   227,   119,    56,   230,   227,    64,     8,
       8,     3,    63,     5,     6,     7,     8,     8,     3,     8,
       5,     6,     7,     8,     8,    32,     9,   155,    33,    31,
       9,   255,     9,     9,    12,   255,   256,   152,    30,   184,
       9,   186,   187,    35,    36,    30,     9,   271,    12,     9,
     165,    12,     9,    45,    46,    47,    12,     9,    12,     9,
      52,    12,    33,   178,    56,   180,   181,   182,     9,     9,
     185,    63,    19,    32,    32,     9,     9,   192,     9,   194,
       8,   196,   227,   198,    32,   200,    32,    32,    32,     8,
       8,    18,    18,   208,    33,    33,    49,    59,    65,     9,
      43,    33,    18,    18,    34,    12,    55,    12,    12,    12,
     255,   256,   227,    33,    31,     9,     9,    12,    20,   234,
      32,    32,    18,   238,    32,    50,    32,   242,    18,    66,
     245,    32,   247,    33,    18,    44,   251,    60,   253,    18,
     255,   256,    12,    12,    12,    12,     3,   262,     5,     6,
       7,     8,    12,    33,     9,    32,    32,   272,    15,    51,
      32,    12,    18,    61,    18,    18,    12,    12,    67,    12,
      27,    28,   287,    30,   289,   290,   291,    12,    12,    36,
      32,    62,    32,    40,    41,    58,   301,   122,   297,   304,
      47,    -1,    -1,    -1,    -1,    52,    -1,    -1,     3,    56,
       5,     6,     7,     8,    -1,    -1,    63,    -1,    -1,    -1,
      15,    -1,    -1,    70,    19,    -1,     3,    -1,     5,     6,
       7,     8,    27,    28,    -1,    30,    -1,    -1,    15,    -1,
      -1,    36,    19,    -1,    -1,    40,    41,    -1,    -1,    -1,
      27,    28,    47,    30,    -1,    -1,    -1,    52,    -1,    36,
      -1,    56,    -1,    40,    41,    -1,    -1,    -1,    63,     3,
      47,     5,     6,     7,     8,    52,    -1,    -1,    -1,    56,
      -1,    15,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    40,    41,    -1,    -1,
      -1,    -1,     3,    47,     5,     6,     7,     8,    52,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    63,
       3,    -1,     5,     6,     7,     8,    -1,    -1,    -1,    30,
      -1,    -1,    -1,    -1,    35,    36,    -1,    -1,     3,    -1,
       5,     6,     7,     8,    45,    -1,    47,    30,    -1,    -1,
      -1,    52,    35,    36,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    47,    30,    -1,    -1,    -1,    52,
      -1,    36,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    47,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    63
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,     8,    15,    27,    28,    30,
      36,    40,    41,    47,    52,    56,    63,    70,    80,    81,
      83,    88,    89,    92,    94,    97,    98,     4,     8,    12,
      30,    68,    69,    68,    69,     3,    88,     8,     8,     8,
      88,    95,     8,     8,     8,     8,     8,     8,     8,     0,
      80,    33,    21,    22,    23,    24,    25,    26,    90,    10,
      11,    91,    13,    14,    93,    33,    37,    38,    39,    53,
      57,   100,     3,    88,    99,    88,    88,     9,    88,    81,
      88,    32,    96,    31,    42,   108,   111,    88,   101,    88,
     105,    48,   115,   116,    54,   120,   121,    58,   123,   124,
      64,   129,   130,    89,     3,    92,    92,    94,    94,     8,
       8,     8,     8,     8,    12,    32,     9,    33,    31,     9,
      88,     9,    88,    12,     9,    88,     9,     9,    12,     9,
      88,    12,     9,    88,    12,     9,    88,    12,     9,    88,
      91,    91,    93,    93,   102,    88,   103,   104,   106,   107,
      88,    99,    12,     3,    15,    19,    27,    28,    81,    82,
      84,    85,    87,    88,    98,    33,    87,    96,    32,    32,
      32,    32,    32,     9,     9,     9,     9,     9,    32,    88,
      12,    30,     8,    80,     8,     8,    18,    18,    33,    33,
      88,    43,   112,    49,   117,    55,   122,    59,   125,    65,
     131,    99,    33,    88,    88,    88,     1,    20,    81,    88,
      81,    87,    81,    87,     9,    34,    88,    12,    88,    12,
      88,    12,    88,    12,    88,    33,    31,     9,    20,    88,
       9,    87,    32,    32,    32,   110,    32,    32,    12,    82,
      86,    87,    33,    87,    44,   113,    50,   118,    35,    88,
      60,   126,    66,   132,    88,    18,    18,    88,    12,    88,
      12,    88,    12,    12,    88,    12,    88,    33,    82,    87,
      82,     9,    32,   109,   110,   114,    51,   119,    88,    32,
      32,    87,    45,    46,    12,   110,    61,   127,    67,   133,
      12,    12,    12,    88,    12,    88,    88,    88,    32,   110,
     110,    32,   109,    62,   128,    12,    88
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    80,    80,    81,    81,    81,    81,    81,
      81,    81,    82,    82,    82,    82,    82,    82,    82,    83,
      84,    84,    84,    84,    84,    84,    85,    86,    86,    86,
      87,    87,    88,    88,    89,    89,    89,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    92,    93,    93,    93,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      95,    96,    96,    97,    97,    97,    97,    97,    98,    98,
      98,    99,    99,    99,    99,    99,   100,   100,   100,   100,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     109,   110,   110,   110,   111,   111,   112,   112,   113,   113,
     114,   114,   115,   116,   116,   117,   117,   118,   118,   119,
     119,   120,   121,   121,   122,   122,   123,   124,   124,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   130,   130,
     131,   131,   132,   132,   133,   133
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     4,     7,     2,     1,     2,
       5,     8,     4,     7,     2,     1,     2,     5,     8,     5,
       1,     3,     3,     1,     3,     3,     5,     3,     3,     3,
       3,     4,     1,     3,     2,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     0,     2,     3,     3,     0,
       2,     2,     2,     2,     1,     1,     1,     1,     3,     3,
       2,     3,     0,     4,     4,     4,     4,     4,     4,     4,
       4,     5,     3,     1,     3,     0,     4,     4,     4,     4,
       4,     1,     0,     1,     0,     1,     0,     0,     9,     5,
       1,     4,     0,     2,     2,     0,     2,     0,     2,     0,
       5,     1,    10,     2,     0,     2,     0,     2,     0,     2,
       0,     6,     2,     0,     2,     0,    14,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     0,    12,     2,     0,
       2,     0,     2,     0,     2,     0
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
        case 2:
#line 129 "parser.y" /* yacc.c:1646  */
    {yyerrok; fprintf(outprod, "statements --> statement statements\n");}
#line 1553 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 130 "parser.y" /* yacc.c:1646  */
    {yyerrok;fprintf(outprod, "statements --> statement\n"); }
#line 1559 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 131 "parser.y" /* yacc.c:1646  */
    {yyerrok;fprintf(outprod, "statements --> ENDALL\n"); }
#line 1565 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 134 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> IDENT ASSIGN expression SEMICOLON\n"); fprintf(outprod, ">>> %s = %.2f\n",(yyvsp[-3].string), (yyvsp[-1].decimal)); vars[countvars++] = strdup((yyvsp[-3].string)); vals[countvars-1] = (float)(yyvsp[-1].decimal);}
#line 1571 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 135 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> IDENT LSQ expression RSQ ASSIGN expression SEMICOLON\n"); }
#line 1577 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 136 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> expression SEMICOLON\n"); }
#line 1583 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 137 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> selection\n"); }
#line 1589 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 138 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> function\n");}
#line 1595 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 139 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> WHILE LP expression RP DO opt_block \n"); }
#line 1601 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 140 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> FOR LP statement expression SEMICOLON expression RP opt_block\n"); }
#line 1607 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 149 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement-with-else --> IDENT ASSIGN expression SEMICOLON\n"); fprintf(outprod, ">>> %s = %.2f\n",(yyvsp[-3].string), (yyvsp[-1].decimal)); vars[countvars++] = strdup((yyvsp[-3].string)); vals[countvars-1] = (float)(yyvsp[-1].decimal);}
#line 1613 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 150 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement-with-else --> IDENT LSQ expression RSQ ASSIGN expression SEMICOLON\n"); }
#line 1619 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 151 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement-with-else --> expression SEMICOLON\n"); }
#line 1625 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 152 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement-with-else --> selection-with-else\n"); }
#line 1631 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 153 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement-with-else --> function\n");}
#line 1637 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 154 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement-with-else --> WHILE LP expression RP opt_block \n"); }
#line 1643 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 155 "parser.y" /* yacc.c:1646  */
    {printf("GGGGGGGGGGGGGGGGGGGG\n"); fprintf(outprod, "statement-with-else --> FOR LP statement expression SEMICOLON expression RP opt_block\n"); }
#line 1649 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 158 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection --> IF LP expression RP selection_prime\n");}
#line 1655 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 161 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection_prime --> opt_block\n");}
#line 1661 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 162 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection_prime --> opt_block ELSE opt_block\n");}
#line 1667 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 163 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection_prime --> opt_block ELSE statement\n");}
#line 1673 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 164 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection_prime --> statement\n");}
#line 1679 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 165 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection_prime --> statement-with-else ELSE opt_block\n");}
#line 1685 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 166 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection_prime --> statement-with-else ELSE statement\n");}
#line 1691 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 169 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection-with-else --> IF LP expression RP selection-with-else_prime\n");}
#line 1697 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 172 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection-with-else_prime --> statement-with-else ELSE opt_block\n");}
#line 1703 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 173 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection-with-else_prime --> opt_block ELSE statement-with-else\n");}
#line 1709 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 174 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection-with-else_prime --> statement-with-else ELSE statement-with-else\n");}
#line 1715 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 177 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "opt_block --> BEG statements END\n");}
#line 1721 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 178 "parser.y" /* yacc.c:1646  */
    {printf("LINE %d : NO START BRACES!\n", yylineno+1);}
#line 1727 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 182 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expression --> expr_temp\n"); }
#line 1733 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 183 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expression --> expr_temp RA_TERM expr_temp\n"); }
#line 1739 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 187 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expr_temp --> term expression_prime\n"); (yyval.decimal)=(yyvsp[-1].decimal)+(yyvsp[0].decimal);}
#line 1745 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 188 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expr_temp --> constructor\n"); (yyval.decimal)=0.00;}
#line 1751 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 189 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expr_temp --> IDENT DOT method\n"); (yyval.decimal)=0.00;}
#line 1757 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 193 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> LTEQ\n");(yyval.decimal)=0.00;}
#line 1763 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 194 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> GTEQ\n");(yyval.decimal)=0.00;}
#line 1769 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 195 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> LT\n");(yyval.decimal)=0.00;}
#line 1775 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 196 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> GT\n");(yyval.decimal)=0.00;}
#line 1781 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 197 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> EQ\n");(yyval.decimal)=0.00;}
#line 1787 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 198 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> NEQ\n");(yyval.decimal)=0.00;}
#line 1793 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 202 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expression_prime --> PLUS term expression_prime\n"); (yyval.decimal)=(yyvsp[-1].decimal)+(yyvsp[0].decimal);}
#line 1799 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 203 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expression_prime --> MINUS term expression_prime \n"); (yyval.decimal)=-((yyvsp[-1].decimal)+(yyvsp[0].decimal));}
#line 1805 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 204 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expression_prime --> (nil)\n"); (yyval.decimal)=0.00;}
#line 1811 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 207 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "term --> factor term_prime\n"); (yyval.decimal)=(yyvsp[-1].decimal)*(yyvsp[0].decimal);}
#line 1817 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 210 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "term_prime --> MULT factor term_prime\n"); (yyval.decimal)=(yyvsp[-1].decimal)*(yyvsp[0].decimal);}
#line 1823 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 211 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "term_prime --> DIV factor term_prime\n"); (yyval.decimal)=1/((yyvsp[-1].decimal)*(yyvsp[0].decimal));}
#line 1829 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 212 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "term_prime --> (nil)\n"); (yyval.decimal)=1.00;}
#line 1835 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 215 "parser.y" /* yacc.c:1646  */
    {(yyval.decimal)=(double)(yyvsp[-1].num)+1; fprintf(outprod, "factor --> NUM INCR\n");}
#line 1841 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 216 "parser.y" /* yacc.c:1646  */
    {(yyval.decimal)=(double)(yyvsp[-1].num)-1; fprintf(outprod, "factor --> NUM DCR\n"); }
#line 1847 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 217 "parser.y" /* yacc.c:1646  */
    {(yyval.decimal)=11.00;fprintf(outprod, "factor --> IDENT INCR\n"); }
#line 1853 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 218 "parser.y" /* yacc.c:1646  */
    {(yyval.decimal)=9.00;fprintf(outprod, "factor --> IDENT DCR\n"); }
#line 1859 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 219 "parser.y" /* yacc.c:1646  */
    {(yyval.decimal)=(double)(yyvsp[0].num); fprintf(outprod, "factor --> NUM\n"); }
#line 1865 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 220 "parser.y" /* yacc.c:1646  */
    {(yyval.decimal)=get_value(vars, vals, countvars, (yyvsp[0].string));fprintf(outprod, "factor --> IDENT\n"); }
#line 1871 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 221 "parser.y" /* yacc.c:1646  */
    {(yyval.decimal)=0.00; fprintf(outprod, "factor --> STRING\n"); }
#line 1877 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.decimal)=(yyvsp[0].decimal); fprintf(outprod, "factor --> FLOAT\n"); }
#line 1883 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 223 "parser.y" /* yacc.c:1646  */
    {(yyval.decimal)=1.00; fprintf(outprod, "factor --> LSQ array RSQ\n"); }
#line 1889 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 224 "parser.y" /* yacc.c:1646  */
    {(yyval.decimal)=(yyvsp[-1].decimal);fprintf(outprod, "factor --> LP expression RP\n"); }
#line 1895 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 227 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "array --> IDENT array_prime\n");}
#line 1901 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 230 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "array_prime --> COMMA IDENT array_prime\n");}
#line 1907 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 231 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "array_prime --> (nil)\n");}
#line 1913 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 235 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "constructor -->  PROCESSOR LP argsPROC RP\n");}
#line 1919 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 236 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "constructor --> LINK LP argsLINK RP\n");}
#line 1925 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 237 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "constructor --> MEMORY LP argsMEM RP\n");}
#line 1931 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 238 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "constructor --> JOB LP argsJOB RP\n");}
#line 1937 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 239 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "constructor --> CLUSTER LP argsCLUSTER RP\n");}
#line 1943 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 242 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "function --> RUN LP argsRUN RP\n");}
#line 1949 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 243 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "function --> DISCJOB LP argsDISCJOB RP\n");}
#line 1955 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 244 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "function -->  IDENT LP argsAll RP\n");}
#line 1961 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 247 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsAll --> IDENT ASSIGN expression COMMA argsAll\n");}
#line 1967 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 248 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsAll --> expression COMMA argsAll\n");}
#line 1973 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 249 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsAll --> expression\n");}
#line 1979 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 250 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsAll --> IDENT ASSIGN expression\n");}
#line 1985 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 251 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsAll --> (nil)\n");}
#line 1991 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 254 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "method --> ISRUN LP argsISRUN RP\n");}
#line 1997 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 255 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "method --> SUBJOBS LP argsSUBJOBS\n");}
#line 2003 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 256 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "method --> GETCLSP LP argsGETCLSP RP\n");}
#line 2009 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 257 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "method --> GETAVMEM LP argsGETAVMEM RP\n");}
#line 2015 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 258 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "method --> GETMEM LP argsGETMEM RP\n");}
#line 2021 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 261 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsRUN --> expression\n");}
#line 2027 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 264 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsISRUN --> (nil)\n");}
#line 2033 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 267 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsSUBJOBS --> expression\n");}
#line 2039 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 270 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsGETCLSP --> (nil)\n");}
#line 2045 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 273 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsDISCJOB --> expression\n");}
#line 2051 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 276 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsGETAVMEM --> (nil)\n");}
#line 2057 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 279 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsGETMEM --> (nil)\n");}
#line 2063 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 282 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsProc --> isaterm expression COMMA clspterm expression COMMA l1memterm expression l2memterm\n");}
#line 2069 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 286 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "archterm --> COMMA ARCHTYPE ASSIGN expression nameterm\n");}
#line 2075 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 287 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "archterm --> nameterm\n");}
#line 2081 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 290 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "nameterm --> COMMA NAME ASSIGN expression\n");}
#line 2087 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 291 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "nameterm --> (nil)\n");}
#line 2093 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 292 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "nameterm --> COMMA epxression\n");}
#line 2099 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 295 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "isaterm --> ISA ASSIGN\n");}
#line 2105 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 296 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "isaterm --> (nil)\n");}
#line 2111 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 299 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "clspterm --> CLSP COLON\n");}
#line 2117 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 300 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "clspterm --> (nil)\n");}
#line 2123 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 303 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "l1memterm --> L1MEM ASSIGN\n");}
#line 2129 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 304 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "l1memterm --> (nil)\n");}
#line 2135 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 307 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "l2memterm --> COMMA L2MEM ASSIGN expression archterm\n");}
#line 2141 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 308 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "l2memterm --> archterm\n");}
#line 2147 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 312 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsLINK -> stpntterm expression COMMA endpntterm expression COMMA bwterm expression chcapterm nameterm\n");}
#line 2153 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 315 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "stpntterm → STPNT  ASSIGN\n");}
#line 2159 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 316 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "stpntterm → (nil)\n");}
#line 2165 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 319 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "endpntterm → ENDPNT  ASSIGN\n");}
#line 2171 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 320 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "endpntterm → (nil)\n");}
#line 2177 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 323 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "bwterm → BW  ASSIGN\n");}
#line 2183 "parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 324 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "bwterm → (nil)\n");}
#line 2189 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 327 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "chcapterm → CHCAP  ASSIGN\n");}
#line 2195 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 328 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "chcapterm → (nil)\n");}
#line 2201 "parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 332 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsMEM → memtypeterm  expression COMMA memsizeterm  expression nameterm\n");}
#line 2207 "parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 335 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "memtypeterm → MEMTYPE ASSIGN\n");}
#line 2213 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 336 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "memtypeterm → (nil)\n");}
#line 2219 "parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 339 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "memsizeterm --> MEMSIZE ASSIGN\n");}
#line 2225 "parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 340 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "memsizeterm --> (nil)\n");}
#line 2231 "parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 344 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsJOB --> jobidterm expression COMMA flopterm expression COMMA deadterm expression COMMA memreqterm expression affineterm expression\n");}
#line 2237 "parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 347 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "jobidterm --> JOBID ASSIGN\n");}
#line 2243 "parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 348 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "jobidterm --> (nil)\n");}
#line 2249 "parser.c" /* yacc.c:1646  */
    break;

  case 119:
#line 351 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "flopterm --> FLOPS ASSIGN\n");}
#line 2255 "parser.c" /* yacc.c:1646  */
    break;

  case 120:
#line 352 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "flopterm --> (nil)\n");}
#line 2261 "parser.c" /* yacc.c:1646  */
    break;

  case 121:
#line 355 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "deadterm --> DEADLINE ASSIGN\n");}
#line 2267 "parser.c" /* yacc.c:1646  */
    break;

  case 122:
#line 356 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "deadterm --> (nil)\n");}
#line 2273 "parser.c" /* yacc.c:1646  */
    break;

  case 123:
#line 359 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "memreqterm --> MEMREQ ASSIGN\n");}
#line 2279 "parser.c" /* yacc.c:1646  */
    break;

  case 124:
#line 360 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "memreqterm --> (nil)\n");}
#line 2285 "parser.c" /* yacc.c:1646  */
    break;

  case 125:
#line 363 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "affineterm --> AFFINITY ASSIGN\n");}
#line 2291 "parser.c" /* yacc.c:1646  */
    break;

  case 126:
#line 364 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "affineterm --> (nil)\n");}
#line 2297 "parser.c" /* yacc.c:1646  */
    break;

  case 127:
#line 368 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "argsCLUSTER --> processorsterm expression COMMA topoterm expression COMMA linkbwterm expression COMMA linkcapterm expression nameterm\n");}
#line 2303 "parser.c" /* yacc.c:1646  */
    break;

  case 128:
#line 371 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "processorsterm --> PROCESSORS ASSIGN\n");}
#line 2309 "parser.c" /* yacc.c:1646  */
    break;

  case 129:
#line 372 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "processorsterm --> (nil)\n");}
#line 2315 "parser.c" /* yacc.c:1646  */
    break;

  case 130:
#line 375 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "topoterm --> TOPO ASSIGN\n");}
#line 2321 "parser.c" /* yacc.c:1646  */
    break;

  case 131:
#line 376 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "topoterm --> (nil)\n");}
#line 2327 "parser.c" /* yacc.c:1646  */
    break;

  case 132:
#line 379 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "linkbwterm --> LINKBW ASSIGN\n");}
#line 2333 "parser.c" /* yacc.c:1646  */
    break;

  case 133:
#line 380 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "linkbwterm --> (nil)\n");}
#line 2339 "parser.c" /* yacc.c:1646  */
    break;

  case 134:
#line 383 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "linkcapterm --> LINKCAP ASSIGN\n");}
#line 2345 "parser.c" /* yacc.c:1646  */
    break;

  case 135:
#line 384 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "linkcapterm --> (nil)\n");}
#line 2351 "parser.c" /* yacc.c:1646  */
    break;


#line 2355 "parser.c" /* yacc.c:1646  */
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
#line 386 "parser.y" /* yacc.c:1906  */

int yyerror(const char *s) {
 fprintf(stderr, "%s\n", s);
}
int main() {
       outprod = fopen("outprod", "w+");
 if (yyparse())
     fprintf(stderr, "Successful parsing.\n");
  else
     fprintf(stderr, "error found.\n");
fclose(outprod);
  for(int i=0; i<countvars; i++){
	printf("%s --> %.2f\n", vars[i], vals[i]);
  }
  for(int i=0; i<argscount; i++){
	printf("%s --> %s\n", argslist[i], argsvals[i]);
  }
  // fclose(outprod);
return 0;
}
