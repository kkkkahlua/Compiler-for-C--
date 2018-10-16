/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "./syntax.y" /* yacc.c:339  */

#define YYSTYPE TreeNode*
#define YYERROR_VERBOSE 1

#include "lex.yy.c"

#include <stdio.h>

extern int error_lex;
extern int yylineno;
int error_syntax = 0;
int yyerror(const char* msg);

TreeNode* root;

#line 82 "./syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
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
    SEMI = 258,
    COMMA = 259,
    LC = 260,
    RC = 261,
    TYPE = 262,
    ID = 263,
    INT = 264,
    FLOAT = 265,
    RETURN = 266,
    IF = 267,
    WHILE = 268,
    STRUCT = 269,
    ASSIGNOP = 270,
    OR = 271,
    AND = 272,
    RELOP = 273,
    PLUS = 274,
    MINUS = 275,
    STAR = 276,
    DIV = 277,
    NOT = 278,
    LP = 279,
    RP = 280,
    LB = 281,
    RB = 282,
    DOT = 283,
    LOWER_THAN_ELSE = 284,
    ELSE = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 164 "./syntax.tab.c" /* yacc.c:358  */

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   468

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    34,    34,    36,    37,    39,    40,    41,    42,    43,
      45,    46,    50,    51,    53,    54,    55,    57,    58,    60,
      64,    65,    66,    68,    69,    71,    72,    74,    78,    79,
      80,    82,    83,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,   100,   101,   103,
     104,   108,   109,   111,   112,   114,   115,   117,   118,   119,
     120,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   148,   149
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMI", "COMMA", "LC", "RC", "TYPE",
  "ID", "INT", "FLOAT", "RETURN", "IF", "WHILE", "STRUCT", "ASSIGNOP",
  "OR", "AND", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "NOT", "LP", "RP",
  "LB", "RB", "DOT", "LOWER_THAN_ELSE", "ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "RedundantRP", "RedundantLP", "DefList", "Def",
  "DecList", "Dec", "Exp", "Args", YY_NULLPTR
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
     285
};
# endif

#define YYPACT_NINF -62

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-62)))

#define YYTABLE_NINF -53

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     260,     9,   -62,    14,    29,   -62,   260,   118,   -62,   -62,
      37,    38,   -62,   -62,   -62,    70,   -62,    25,    71,     4,
      65,   278,   -62,    93,   -62,    69,    46,    52,   -62,    75,
      95,    90,     2,   -62,    69,    81,   121,   -62,   -62,    97,
     100,   133,    78,   -62,   -62,   -62,    54,    12,   146,   -62,
     -62,   126,   -62,     2,   -62,   -62,   -62,    91,   129,   -62,
     -62,   229,   130,   131,   246,   246,   263,   -62,   151,    78,
      94,   246,   155,   -62,    95,   -62,   -62,   -62,   169,   120,
     114,   280,   297,   163,   188,    67,     3,   314,   246,   358,
     -62,   -62,   -62,   246,   246,   246,   246,   246,   246,   246,
     246,   331,   164,   428,   -62,   -62,    23,   -62,   147,   149,
     -62,   -62,    42,   372,    43,   386,   -62,   348,   400,   -62,
     428,   440,   290,   307,   188,   188,    67,    67,    17,   414,
     -62,   -62,   246,   -62,   175,   195,   212,   136,   -62,   -62,
     -62,   -62,    11,   152,    15,   160,   -62,   156,   -62,   212,
     212,   212,   212,   212,   -62,   -62,   -62,   -62,   -62,   -62
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    12,    18,     0,     2,     0,     0,    13,     9,
      19,     0,    16,     1,     3,     0,     6,    20,     0,    10,
       0,     0,     8,     0,     5,     0,     0,     0,     7,     0,
       0,     0,    52,    24,     0,     0,    26,    20,    11,     0,
       0,     0,     0,    15,    58,    59,    57,     0,    55,    14,
      51,    27,    23,     0,    22,    21,    30,     0,    77,    78,
      79,     0,     0,     0,     0,     0,     0,    34,    29,     0,
       0,     0,     0,    53,     0,    25,    46,    83,     0,     0,
       0,     0,     0,     0,    71,    72,     0,     0,     0,     0,
      28,    31,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    54,    56,     0,    74,    85,     0,
      36,    35,     0,     0,     0,     0,    80,     0,     0,    69,
      61,    63,    62,    64,    65,    66,    67,    68,     0,     0,
      76,    81,     0,    73,     0,     0,     0,     0,    70,    82,
      75,    84,     0,    42,     0,    37,    41,    48,    39,     0,
       0,     0,     0,     0,    47,    40,    45,    43,    44,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -62,   -62,   185,   -62,   172,     1,   -62,   -62,   -62,   -28,
     -62,   148,   -62,   182,   142,    92,    84,   125,   111,   -62,
     159,   -62,   -61,   102
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    18,    30,     8,    11,    12,    19,
      20,    35,    36,    67,    68,    69,   149,    88,    31,    32,
      47,    48,    70,   109
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,     7,    46,    84,    85,    89,    51,     7,    25,     2,
     103,    77,     9,    72,    76,    73,     3,   108,    76,    77,
     113,   115,    10,    77,    34,    77,    89,   118,   116,    13,
      26,    77,   120,   121,   122,   123,   124,   125,   126,   127,
     129,   150,   -17,    21,   139,   152,    46,    39,   131,    23,
      77,    77,   -52,    41,    34,    40,   118,   -52,   -52,     2,
     -52,   -52,   -52,   -52,   -52,   -52,     3,   134,   136,    71,
      27,   108,   -52,    22,    24,   -52,   -52,    37,   -32,    57,
      26,    43,   -52,    27,   -32,   -32,    58,    59,    60,    61,
      62,    63,   -32,   101,    76,   102,    49,    92,    64,    77,
       2,    65,    66,    37,    44,    45,    52,     3,   -32,    93,
      94,    95,    96,    97,    98,    99,   100,   111,    33,    15,
     101,    16,   102,   110,    54,    53,    17,    55,    77,    93,
      94,    95,    96,    97,    98,    99,   100,    57,    42,    56,
     101,    27,   102,    50,    58,    59,    60,    61,    62,    63,
      74,   132,    26,    78,    81,    82,    64,    90,   104,    65,
      66,   147,    93,    94,    95,    96,    97,    98,    99,   100,
     106,    77,   130,   101,   133,   102,   142,    58,    59,    60,
      27,   147,   151,    58,    59,    60,    61,    62,    63,    64,
     153,    14,    65,    66,   107,    64,   144,    38,    65,    66,
      27,    75,    28,    58,    59,    60,    61,    62,    63,    99,
     100,    91,   117,    57,   101,    64,   102,    27,    65,    66,
      58,    59,    60,    61,    62,    63,   143,   145,   146,   148,
      79,   154,    64,   105,   141,    65,    66,    58,    59,    60,
       0,   155,   156,   157,   158,   159,     0,    83,     0,    64,
       0,     0,    65,    66,    58,    59,    60,     0,     0,     0,
      -4,     1,     0,     0,    86,     0,    64,     2,     0,    65,
      66,    58,    59,    60,     3,     0,     0,     0,     0,    29,
       0,   112,     0,    64,   -52,     2,    65,    87,    58,    59,
      60,     0,     3,     0,     0,     0,     0,     0,   114,     0,
      64,     0,     0,    65,    66,    58,    59,    60,    96,    97,
      98,    99,   100,     0,     0,    86,   101,    64,   102,     0,
      65,    66,    58,    59,    60,     0,    97,    98,    99,   100,
       0,     0,   128,   101,   -50,   102,     0,   -50,   -50,    58,
      59,    60,     0,     0,     0,     0,     0,     0,     0,    83,
       0,    64,     0,     0,    65,    66,    58,    59,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -49,     0,
       0,   -49,   -49,    93,    94,    95,    96,    97,    98,    99,
     100,     0,     0,   119,   101,     0,   102,    93,    94,    95,
      96,    97,    98,    99,   100,     0,     0,   135,   101,     0,
     102,    93,    94,    95,    96,    97,    98,    99,   100,     0,
       0,   137,   101,     0,   102,    93,    94,    95,    96,    97,
      98,    99,   100,     0,     0,   138,   101,     0,   102,    93,
      94,    95,    96,    97,    98,    99,   100,     0,     0,     0,
     101,   140,   102,    93,    94,    95,    96,    97,    98,    99,
     100,     0,     0,     0,   101,     0,   102,    95,    96,    97,
      98,    99,   100,     0,     0,     0,   101,     0,   102
};

static const yytype_int16 yycheck[] =
{
      61,     0,    30,    64,    65,    66,    34,     6,     4,     7,
      71,     8,     3,     1,     3,     3,    14,    78,     3,     8,
      81,    82,     8,     8,    23,     8,    87,    88,    25,     0,
      26,     8,    93,    94,    95,    96,    97,    98,    99,   100,
     101,    30,     5,     5,    27,    30,    74,     1,    25,    24,
       8,     8,     0,     1,    53,     9,   117,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    25,    25,    15,
       5,   132,    20,     3,     3,    23,    24,     8,     0,     1,
      26,     6,    30,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    26,     3,    28,     6,     3,    20,     8,
       7,    23,    24,     8,     9,    10,    25,    14,    30,    15,
      16,    17,    18,    19,    20,    21,    22,     3,    25,     1,
      26,     3,    28,     3,    27,     4,     8,    27,     8,    15,
      16,    17,    18,    19,    20,    21,    22,     1,    27,     6,
      26,     5,    28,    32,     8,     9,    10,    11,    12,    13,
       4,     4,    26,    24,    24,    24,    20,     6,     3,    23,
      24,    25,    15,    16,    17,    18,    19,    20,    21,    22,
       1,     8,     8,    26,    25,    28,     1,     8,     9,    10,
       5,    25,    30,     8,     9,    10,    11,    12,    13,    20,
      30,     6,    23,    24,    25,    20,     1,    25,    23,    24,
       5,    53,    20,     8,     9,    10,    11,    12,    13,    21,
      22,    69,    87,     1,    26,    20,    28,     5,    23,    24,
       8,     9,    10,    11,    12,    13,   134,   135,   136,   137,
       1,   147,    20,    74,   132,    23,    24,     8,     9,    10,
      -1,   149,   150,   151,   152,   153,    -1,     1,    -1,    20,
      -1,    -1,    23,    24,     8,     9,    10,    -1,    -1,    -1,
       0,     1,    -1,    -1,     1,    -1,    20,     7,    -1,    23,
      24,     8,     9,    10,    14,    -1,    -1,    -1,    -1,     1,
      -1,     1,    -1,    20,     6,     7,    23,    24,     8,     9,
      10,    -1,    14,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      20,    -1,    -1,    23,    24,     8,     9,    10,    18,    19,
      20,    21,    22,    -1,    -1,     1,    26,    20,    28,    -1,
      23,    24,     8,     9,    10,    -1,    19,    20,    21,    22,
      -1,    -1,     1,    26,    20,    28,    -1,    23,    24,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    20,    -1,    -1,    23,    24,     8,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    23,    24,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    -1,    25,    26,    -1,    28,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    25,    26,    -1,
      28,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    25,    26,    -1,    28,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    -1,    25,    26,    -1,    28,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      26,    27,    28,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    -1,    -1,    26,    -1,    28,    17,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    26,    -1,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     7,    14,    32,    33,    34,    36,    37,     3,
       8,    38,    39,     0,    33,     1,     3,     8,    35,    40,
      41,     5,     3,    24,     3,     4,    26,     5,    44,     1,
      36,    49,    50,    25,    36,    42,    43,     8,    35,     1,
       9,     1,    49,     6,     9,    10,    40,    51,    52,     6,
      49,    40,    25,     4,    27,    27,     6,     1,     8,     9,
      10,    11,    12,    13,    20,    23,    24,    44,    45,    46,
      53,    15,     1,     3,     4,    42,     3,     8,    24,     1,
      53,    24,    24,     1,    53,    53,     1,    24,    48,    53,
       6,    45,     3,    15,    16,    17,    18,    19,    20,    21,
      22,    26,    28,    53,     3,    51,     1,    25,    53,    54,
       3,     3,     1,    53,     1,    53,    25,    48,    53,    25,
      53,    53,    53,    53,    53,    53,    53,    53,     1,    53,
       8,    25,     4,    25,    25,    25,    25,    25,    25,    27,
      27,    54,     1,    46,     1,    46,    46,    25,    46,    47,
      30,    30,    30,    30,    47,    46,    46,    46,    46,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    34,
      35,    35,    36,    36,    37,    37,    37,    38,    38,    39,
      40,    40,    40,    41,    41,    42,    42,    43,    44,    44,
      44,    45,    45,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    47,    47,    48,
      48,    49,    49,    50,    50,    51,    51,    52,    52,    52,
      52,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     2,
       1,     3,     1,     1,     5,     5,     2,     1,     0,     1,
       1,     4,     4,     4,     3,     3,     1,     2,     4,     3,
       3,     2,     0,     2,     1,     3,     3,     5,     7,     5,
       6,     5,     5,     7,     7,     7,     2,     2,     1,     2,
       1,     2,     0,     3,     4,     1,     3,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     2,     2,     4,     3,     4,     3,     1,     1,     1,
       3,     4,     4,     2,     3,     1
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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
#line 34 "./syntax.y" /* yacc.c:1646  */
    { root = CreateInternalTreeNode("Program", 1, (yyvsp[0])); }
#line 1406 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 36 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("ExtDefList", 2, (yyvsp[-1]), (yyvsp[0])); }
#line 1412 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 37 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("ExtDefList", 0); }
#line 1418 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 39 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("ExtDef", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1424 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 40 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("ExtDef", 2, (yyvsp[-1]), (yyvsp[0])); }
#line 1430 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 41 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("ExtDef", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1436 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 42 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1442 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 43 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1448 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 45 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("ExtDecList", 1, (yyvsp[0])); }
#line 1454 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 46 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("ExtDecList", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1460 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 50 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Specifier", 1, (yyvsp[0])); }
#line 1466 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 51 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Specifier", 1, (yyvsp[0])); }
#line 1472 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 53 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("StructSpecifier", 5, (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1478 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 54 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1484 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 55 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("StructSpecifier", 2, (yyvsp[-1]), (yyvsp[0])); }
#line 1490 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 57 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("OptTag", 1, (yyvsp[0])); }
#line 1496 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 58 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("OptTag", 0); }
#line 1502 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 60 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Tag", 1, (yyvsp[0])); }
#line 1508 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 64 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("VarDec", 1, (yyvsp[0])); }
#line 1514 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 65 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("VarDec", 4, (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1520 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 66 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1526 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 68 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("FunDec", 4, (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1532 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 69 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("FunDec", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1538 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 71 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("VarList", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1544 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 72 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("VarList", 1, (yyvsp[0])); }
#line 1550 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 74 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("ParamDec", 2, (yyvsp[-1]), (yyvsp[0])); }
#line 1556 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 78 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("CompSt", 4, (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1562 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 79 "./syntax.y" /* yacc.c:1646  */
    { yyerror("syntax error, expecting RC"); yyerrok; }
#line 1568 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 80 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1574 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 82 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("StmtList", 2, (yyvsp[-1]), (yyvsp[0])); }
#line 1580 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 83 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("StmtList", 0); }
#line 1586 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 85 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Stmt", 2, (yyvsp[-1]), (yyvsp[0])); }
#line 1592 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 86 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Stmt", 1, (yyvsp[0])); }
#line 1598 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 87 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Stmt", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1604 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 88 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1610 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 89 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Stmt", 5, (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1616 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 90 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Stmt", 7, (yyvsp[-6]), (yyvsp[-5]), (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1622 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 91 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Stmt", 5, (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1628 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 92 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1634 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 93 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1640 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 94 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1646 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 95 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1652 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 96 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1658 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 97 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1664 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 98 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1670 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 101 "./syntax.y" /* yacc.c:1646  */
    { yyerror("syntax error, redundant RP"); yyerrok; }
#line 1676 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 108 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("DefList", 2, (yyvsp[-1]), (yyvsp[0])); }
#line 1682 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 109 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("DefList", 0); }
#line 1688 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 111 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Def", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1694 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 112 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1700 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 114 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("DecList", 1, (yyvsp[0])); }
#line 1706 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 115 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("DecList", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1712 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 117 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Dec", 1, (yyvsp[0])); }
#line 1718 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 118 "./syntax.y" /* yacc.c:1646  */
    { yyerror("syntax error, unexpected INT, expecting ID"); yyerrok; }
#line 1724 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 119 "./syntax.y" /* yacc.c:1646  */
    { yyerror("syntax error, unexpected FLOAT, expecting ID"); yyerrok; }
#line 1730 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 120 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Dec", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1736 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 124 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1742 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 125 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1748 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 126 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1754 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 127 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1760 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 128 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1766 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 129 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1772 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 130 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1778 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 131 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1784 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 132 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1790 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 133 "./syntax.y" /* yacc.c:1646  */
    { yyerror("syntax error, redundant LP"); yyerrok; }
#line 1796 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 134 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 2, (yyvsp[-1]), (yyvsp[0])); }
#line 1802 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 135 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 2, (yyvsp[-1]), (yyvsp[0])); }
#line 1808 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 136 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 4, (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1814 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 137 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1820 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 138 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 4, (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1826 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 139 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1832 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 140 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 1, (yyvsp[0])); }
#line 1838 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 141 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 1, (yyvsp[0])); }
#line 1844 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 142 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Exp", 1, (yyvsp[0])); }
#line 1850 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 143 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1856 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 144 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1862 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 145 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1868 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 146 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1874 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 148 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Args", 3, (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1880 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 149 "./syntax.y" /* yacc.c:1646  */
    { (yyval) = CreateInternalTreeNode("Args", 1, (yyvsp[0])); }
#line 1886 "./syntax.tab.c" /* yacc.c:1646  */
    break;


#line 1890 "./syntax.tab.c" /* yacc.c:1646  */
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
#line 151 "./syntax.y" /* yacc.c:1906  */


int main(int argc, char** argv) {
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			perror(argv[1]);
			return 1;
		}
	}
	yyparse();

	if (error_lex == 1 || error_syntax == 1) return 0;

	OutputTree(root, 0);
	return 0;
}
int yyerror(const char* msg) {
	printf("Error Type B at Line %d: %s.\n", yylineno, msg);
	error_syntax = 1;
}
