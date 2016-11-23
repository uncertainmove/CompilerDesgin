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
#line 1 "syntax.y" /* yacc.c:339  */


#include"lex.yy.c"
#include"Node.h"
#include<string.h>
extern struct Node *p;
void StarToString(char **type, const char *s);
int yyerror(const char *msg);
//yydebug = 1;
enum { array, program, extdeflist, extdef, specifier, def, declist, vardec, dec, extdeclist, fundec, compst, type, structspecifier, opttag, deflist, tag, varlist, paramdec, stmtlist, stmt, exp, args, constant, };


#line 79 "syntax.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
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
    POUND = 258,
    INCLUDE = 259,
    VOID = 260,
    INT = 261,
    FLOAT = 262,
    CHAR = 263,
    INT_DIGIT = 264,
    CHAR_DIGIT = 265,
    FLOAT_DIGIT = 266,
    WORD = 267,
    DOUBLE = 268,
    OCTAL = 269,
    HEXADECIMAL = 270,
    SHORT = 271,
    UNSIGNED = 272,
    UNSIGNED_DIGIT = 273,
    PLUS = 274,
    SUB = 275,
    MUL = 276,
    DIV = 277,
    MOD = 278,
    ASSIGNOP = 279,
    COMMA = 280,
    SEMICOLON = 281,
    POINT = 282,
    SINGLE_QUOTE = 283,
    DOUBLE_QUOTE = 284,
    JUDGE_BiGGER = 285,
    JUDGE_SMALLER = 286,
    JUDGE_BIGGER_EQUAL = 287,
    JUDGE_SMALLER_EQUAL = 288,
    JUDGE_EQUAL = 289,
    JUDGE_NOT_EQUAL = 290,
    NOT = 291,
    FOR = 292,
    WHILE = 293,
    IF = 294,
    ELSE = 295,
    RETURN = 296,
    BREAK = 297,
    STRUCT = 298,
    LP = 299,
    RP = 300,
    LC = 301,
    RC = 302,
    LB = 303,
    RB = 304,
    LEFT_ANGLE_BRA = 305,
    RIGHT_ANGLE_BRA = 306,
    OR = 307,
    AND = 308,
    ANNOTATION_LINE = 309,
    ANNOTATION_BLOCK_START = 310,
    ANNOTATION_BLOCK_STOP = 311,
    STRING = 312,
    JUDGE_BIGGER = 313,
    LOWER_THAN_ELSE = 314
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "syntax.y" /* yacc.c:355  */

    int type_int;
    char type_char;
    float type_float;
    char *type_string;
    struct Node *token_p;

#line 187 "syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 204 "syntax.tab.c" /* yacc.c:358  */

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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   421

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

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
      55,    56,    57,    58,    59
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    69,    69,    77,    83,    90,    97,    98,   104,   115,
     120,   129,   135,   144,   151,   156,   165,   172,   182,   191,
     198,   208,   212,   218,   228,   234,   242,   251,   257,   264,
     270,   277,   283,   284,   290,   296,   301,   308,   316,   326,
     332,   340,   346,   350,   355,   364,   370,   380,   387,   394,
     401,   408,   415,   422,   429,   436,   443,   450,   457,   464,
     471,   477,   483,   489,   497,   504,   511,   519,   526,   535,
     541,   547,   556,   562,   604,   609,   614,   619
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "POUND", "INCLUDE", "VOID", "INT",
  "FLOAT", "CHAR", "INT_DIGIT", "CHAR_DIGIT", "FLOAT_DIGIT", "WORD",
  "DOUBLE", "OCTAL", "HEXADECIMAL", "SHORT", "UNSIGNED", "UNSIGNED_DIGIT",
  "PLUS", "SUB", "MUL", "DIV", "MOD", "ASSIGNOP", "COMMA", "SEMICOLON",
  "POINT", "SINGLE_QUOTE", "DOUBLE_QUOTE", "JUDGE_BiGGER", "JUDGE_SMALLER",
  "JUDGE_BIGGER_EQUAL", "JUDGE_SMALLER_EQUAL", "JUDGE_EQUAL",
  "JUDGE_NOT_EQUAL", "NOT", "FOR", "WHILE", "IF", "ELSE", "RETURN",
  "BREAK", "STRUCT", "LP", "RP", "LC", "RC", "LB", "RB", "LEFT_ANGLE_BRA",
  "RIGHT_ANGLE_BRA", "OR", "AND", "ANNOTATION_LINE",
  "ANNOTATION_BLOCK_START", "ANNOTATION_BLOCK_STOP", "STRING",
  "JUDGE_BIGGER", "LOWER_THAN_ELSE", "$accept", "program", "extdeflist",
  "extdef", "extdeclist", "specifier", "structspecifier", "opttag", "tag",
  "vardec", "fundec", "varlist", "paramdec", "compst", "stmtlist", "stmt",
  "deflist", "def", "declist", "dec", "exp", "constant", "args", "type", YY_NULLPTR
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
};
# endif

#define YYPACT_NINF -59

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-59)))

#define YYTABLE_NINF -17

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      57,   -59,   -59,   -59,   -59,    -6,    18,   -59,    57,    86,
     -59,   -59,   -38,   -31,   -59,   -59,   -59,   -20,   -59,    65,
     -22,   -12,    57,     6,    30,   -59,    56,    60,    57,   -59,
      56,     8,    57,    32,   -59,    56,    41,    64,   -59,   -59,
     -59,    48,   339,    51,    75,    77,    43,   -59,   -59,   -59,
      59,   -59,    57,   -59,   -59,   -59,   -59,    66,   194,   194,
      78,    80,   377,   194,   -59,    15,   339,    26,   -59,   194,
      82,   -59,    56,   -59,   -59,   124,   -13,   -13,   194,   194,
     -59,    61,    96,    74,   -59,   -59,    99,   194,   194,   194,
     194,   194,   -59,   114,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   271,   -59,   -59,   -59,   131,    94,   166,
     201,   -59,   -59,   -59,   -59,   154,   154,   -13,   -13,   271,
     -59,    84,    84,    84,    84,    84,   236,   306,   336,    84,
     194,   -59,   339,   339,   -59,   -59,   -59,   100,   339,   -59
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    74,    75,    77,    76,    17,     0,     2,     4,     0,
      12,    11,    18,     0,    15,     1,     3,    19,     7,     0,
       9,     0,    40,     0,     0,     5,     0,     0,    40,     8,
       0,     0,    40,     0,    22,     0,     0,    25,     6,    19,
      10,     0,    30,    45,     0,    43,     0,    13,    39,    21,
      26,    23,     0,    20,    69,    70,    71,    67,     0,     0,
       0,     0,     0,     0,    33,     0,    30,     0,    68,     0,
       0,    41,     0,    14,    24,     0,    61,    62,     0,     0,
      35,     0,     0,     0,    27,    29,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,    42,    44,    64,    73,     0,     0,
       0,    34,    60,    28,    32,    56,    57,    58,    59,    47,
      66,    51,    52,    53,    55,    54,     0,    49,    48,    50,
       0,    63,     0,     0,    65,    72,    38,    36,     0,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -59,   -59,   134,   -59,   120,     2,   -59,   -59,   -59,    -7,
     -59,    95,   -59,   136,    93,     5,    39,   -59,    89,   -59,
     -58,   -59,    37,   -59
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,    19,    30,    10,    13,    14,    20,
      21,    36,    37,    64,    65,    66,    31,    32,    44,    45,
      67,    68,   108,    11
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      76,    77,     9,    26,    81,    82,    12,    33,   -16,    46,
       9,   103,     1,     2,    93,    22,    83,   107,    15,     3,
     109,   110,     4,    43,    23,    35,    27,    86,    50,   115,
     116,   117,   118,   119,    28,    99,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    87,    88,    89,    90,     5,
      91,    34,    92,    93,    35,    47,    38,    94,    95,    96,
      97,    98,    84,     1,     2,    43,    24,    42,    39,    41,
       3,    48,   107,     4,    99,    69,    70,    49,   100,   101,
      87,    88,    89,    90,   102,    91,    51,   111,    93,    52,
      73,    25,    94,    95,    96,    97,    98,    53,    17,    27,
       5,    71,    72,    87,    88,    89,    90,    27,   104,    99,
      75,    93,    18,   100,   101,    87,    88,    89,    90,   102,
      91,   113,    78,    93,    79,   114,   120,    94,    95,    96,
      97,    98,    99,    54,    55,    56,    57,   136,   137,   131,
     138,   112,    16,   139,    99,    58,    40,    74,   100,   101,
      87,    88,    89,    90,   102,    91,   130,    29,    93,    85,
      59,   105,    94,    95,    96,    97,    98,   135,    63,   106,
       0,     0,     0,     0,     0,    89,    90,     0,     0,    99,
       0,    93,     0,   100,   101,    87,    88,    89,    90,   102,
      91,     0,     0,    93,     0,     0,     0,    94,    95,    96,
      97,    98,    99,    54,    55,    56,    57,     0,     0,     0,
       0,   132,     0,     0,    99,    58,     0,     0,   100,   101,
      87,    88,    89,    90,   102,    91,     0,     0,    93,     0,
      59,     0,    94,    95,    96,    97,    98,     0,    63,     0,
       0,     0,     0,     0,     0,     0,   133,     0,     0,    99,
       0,     0,     0,   100,   101,    87,    88,    89,    90,   102,
      91,     0,     0,    93,     0,     0,     0,    94,    95,    96,
      97,    98,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    99,   134,     0,     0,   100,   101,
      87,    88,    89,    90,   102,    91,     0,     0,    93,     0,
       0,     0,    94,    95,    96,    97,    98,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    99,
       0,     0,     0,   100,   101,    87,    88,    89,    90,   102,
       0,     0,     0,    93,     0,     0,     0,    94,    95,    96,
      97,    98,     0,     0,     0,     0,     0,     0,    54,    55,
      56,    57,     0,     0,    99,    87,    88,    89,    90,   101,
      58,     0,     0,    93,   102,     0,     0,    94,    95,    96,
      97,    98,     0,     0,     0,    59,     0,    60,    61,     0,
      62,     0,     0,    63,    99,    28,    54,    55,    56,    57,
       0,     0,     0,     0,   102,     0,     0,     0,    58,     0,
       0,     0,     0,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,     0,     0,     0,     0,     0,     0,
       0,    63
};

static const yytype_int16 yycheck[] =
{
      58,    59,     0,    25,    62,    63,    12,     1,    46,     1,
       8,    69,     6,     7,    27,    46,     1,    75,     0,    13,
      78,    79,    16,    30,    44,    23,    48,     1,    35,    87,
      88,    89,    90,    91,    46,    48,    94,    95,    96,    97,
      98,    99,   100,   101,   102,    19,    20,    21,    22,    43,
      24,    45,    26,    27,    52,    47,    26,    31,    32,    33,
      34,    35,    47,     6,     7,    72,     1,    28,    12,     9,
      13,    32,   130,    16,    48,    24,     1,    45,    52,    53,
      19,    20,    21,    22,    58,    24,    45,    26,    27,    25,
      47,    26,    31,    32,    33,    34,    35,    49,    12,    48,
      43,    26,    25,    19,    20,    21,    22,    48,    26,    48,
      44,    27,    26,    52,    53,    19,    20,    21,    22,    58,
      24,    47,    44,    27,    44,    26,    12,    31,    32,    33,
      34,    35,    48,     9,    10,    11,    12,   132,   133,    45,
      40,    45,     8,   138,    48,    21,    26,    52,    52,    53,
      19,    20,    21,    22,    58,    24,    25,    21,    27,    66,
      36,    72,    31,    32,    33,    34,    35,   130,    44,    45,
      -1,    -1,    -1,    -1,    -1,    21,    22,    -1,    -1,    48,
      -1,    27,    -1,    52,    53,    19,    20,    21,    22,    58,
      24,    -1,    -1,    27,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    48,     9,    10,    11,    12,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    21,    -1,    -1,    52,    53,
      19,    20,    21,    22,    58,    24,    -1,    -1,    27,    -1,
      36,    -1,    31,    32,    33,    34,    35,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      -1,    -1,    -1,    52,    53,    19,    20,    21,    22,    58,
      24,    -1,    -1,    27,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    -1,    -1,    52,    53,
      19,    20,    21,    22,    58,    24,    -1,    -1,    27,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    52,    53,    19,    20,    21,    22,    58,
      -1,    -1,    -1,    27,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    -1,    -1,    48,    19,    20,    21,    22,    53,
      21,    -1,    -1,    27,    58,    -1,    -1,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    36,    -1,    38,    39,    -1,
      41,    -1,    -1,    44,    48,    46,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    13,    16,    43,    61,    62,    63,    65,
      66,    83,    12,    67,    68,     0,    62,    12,    26,    64,
      69,    70,    46,    44,     1,    26,    25,    48,    46,    73,
      65,    76,    77,     1,    45,    65,    71,    72,    26,    12,
      64,     9,    76,    69,    78,    79,     1,    47,    76,    45,
      69,    45,    25,    49,     9,    10,    11,    12,    21,    36,
      38,    39,    41,    44,    73,    74,    75,    80,    81,    24,
       1,    26,    25,    47,    71,    44,    80,    80,    44,    44,
      26,    80,    80,     1,    47,    74,     1,    19,    20,    21,
      22,    24,    26,    27,    31,    32,    33,    34,    35,    48,
      52,    53,    58,    80,    26,    78,    45,    80,    82,    80,
      80,    26,    45,    47,    26,    80,    80,    80,    80,    80,
      12,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      25,    45,    45,    45,    49,    82,    75,    75,    40,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    63,    63,    63,    64,
      64,    65,    65,    66,    66,    66,    67,    67,    68,    69,
      69,    70,    70,    70,    71,    71,    72,    73,    73,    74,
      74,    75,    75,    75,    75,    75,    75,    75,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      81,    81,    82,    82,    83,    83,    83,    83
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     4,     2,     3,     1,
       3,     1,     1,     5,     6,     2,     1,     0,     1,     1,
       4,     4,     3,     4,     3,     1,     2,     4,     5,     2,
       0,     2,     3,     1,     3,     2,     5,     7,     5,     2,
       0,     3,     4,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     3,     4,     3,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1
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
#line 69 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(program, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[0].token_p));
            (yyval.token_p) = p;
        }
#line 1444 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 77 "syntax.y" /* yacc.c:1646  */
    {
                p = NewNode(extdeflist, yylineno, yylloc.first_column, 0);
                insert(p, (yyvsp[-1].token_p));
                insert(p, (yyvsp[0].token_p));
                (yyval.token_p) = p;
           }
#line 1455 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 83 "syntax.y" /* yacc.c:1646  */
    {
                p = NULL;
                (yyval.token_p) = p;
           }
#line 1464 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 90 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(extdef, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[-1].token_p));
            p->type = extdeclist;
            (yyval.token_p) = p;
       }
#line 1476 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 98 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(extdef, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-1].token_p));
            p->type = -1;
            (yyval.token_p) = p;
       }
#line 1487 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 104 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(extdef, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[-1].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = fundec;
            (yyval.token_p) = p;
       }
#line 1500 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 115 "syntax.y" /* yacc.c:1646  */
    {
                p = NewNode(extdeclist, yylineno, yylloc.first_column, 0);
                insert(p, (yyvsp[0].token_p));
                (yyval.token_p) = p;
           }
#line 1510 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 120 "syntax.y" /* yacc.c:1646  */
    {
                p = NewNode(extdeclist, yylineno, yylloc.first_column, 0);
                insert(p, (yyvsp[-2].token_p));
                insert(p, (yyvsp[0].token_p));
                (yyval.token_p) = p;
           }
#line 1521 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 129 "syntax.y" /* yacc.c:1646  */
    {
                p = NewNode(specifier, yylineno, yylloc.first_column, 0);
                insert(p, (yyvsp[0].token_p));
                p->type = type;
                (yyval.token_p) = p;
          }
#line 1532 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 135 "syntax.y" /* yacc.c:1646  */
    {
                p = NewNode(specifier, yylineno, yylloc.first_column, 0);
                insert(p, (yyvsp[0].token_p));
                p->type = structspecifier;
                (yyval.token_p) = p;
          }
#line 1543 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 144 "syntax.y" /* yacc.c:1646  */
    {
                    p = NewNode(structspecifier, yylineno, yylloc.first_column, 0);
                    insert(p, (yyvsp[-3].token_p));
                    insert(p, (yyvsp[-1].token_p));
                    p->type = opttag;
                    (yyval.token_p) = p;
                }
#line 1555 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 151 "syntax.y" /* yacc.c:1646  */
    {
                    p = NewNode(structspecifier, yylineno, yylloc.first_column, 0);
                    p->type = opttag;
                    (yyval.token_p) = p;
                }
#line 1565 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 156 "syntax.y" /* yacc.c:1646  */
    {
                    p = NewNode(structspecifier, yylineno, yylloc.first_column, 0);
                    insert(p, (yyvsp[0].token_p));
                    p->type = tag;
                    (yyval.token_p) = p;
                }
#line 1576 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 165 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(opttag, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * strlen((yyvsp[0].type_string)));
            strcpy(p->word_name, (yyvsp[0].type_string));
            p->type = STRUCT;
            (yyval.token_p) = p;
       }
#line 1588 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 172 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(opttag, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * 5);
            strcpy(p->word_name, "NULL");
            p->type = STRUCT;
            (yyval.token_p) = p;
       }
#line 1600 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 182 "syntax.y" /* yacc.c:1646  */
    {
        p = NewNode(tag, yylineno, yylloc.first_column, 0);
        p->word_name = (char *)malloc(sizeof(char) * strlen((yyvsp[0].type_string)));
        strcpy(p->word_name, (yyvsp[0].type_string));
        (yyval.token_p) = p;
    }
#line 1611 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 191 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(vardec, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * strlen((yyvsp[0].type_string)));
            strcpy(p->word_name, (yyvsp[0].type_string));
            p->type = WORD;
            (yyval.token_p) = p;
       }
#line 1623 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 198 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(vardec, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-3].token_p));
            p->capacity = (yyvsp[-1].type_int);
            p->type = array;
            (yyval.token_p) = p;
       }
#line 1635 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 208 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(fundec, yylineno, yylloc.first_column, 0);
            (yyval.token_p) = p;
       }
#line 1644 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 212 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(fundec, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * strlen((yyvsp[-2].type_string)));
            strcpy(p->word_name, (yyvsp[-2].type_string));
            (yyval.token_p) = p;
       }
#line 1655 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 218 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(fundec, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * strlen((yyvsp[-3].type_string)));
            strcpy(p->word_name, (yyvsp[-3].type_string));
            insert(p, (yyvsp[-1].token_p));
            (yyval.token_p) = p;
        }
#line 1667 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 228 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(varlist, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            (yyval.token_p) = p;
        }
#line 1678 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 234 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(varlist, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[0].token_p));
            (yyval.token_p) = p;
        }
#line 1688 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 242 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(paramdec, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-1].token_p));
            insert(p, (yyvsp[0].token_p));
            (yyval.token_p) = p; 
         }
#line 1699 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 251 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(compst, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[-1].token_p));
            (yyval.token_p) = p; 
       }
#line 1710 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 257 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(compst, yylineno, yylloc.first_column, 0);
            (yyval.token_p) = p;
       }
#line 1719 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 264 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(stmtlist, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-1].token_p));
            insert(p, (yyvsp[0].token_p));
            (yyval.token_p) = p; 
         }
#line 1730 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 270 "syntax.y" /* yacc.c:1646  */
    {
            p = NULL; 
            (yyval.token_p) = p; 
         }
#line 1739 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 277 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-1].token_p));
            p->type = exp;
            (yyval.token_p) = p;
     }
#line 1750 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 284 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[0].token_p));
            p->type = compst;
            (yyval.token_p) = p;
     }
#line 1761 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 290 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-1].token_p));
            p->type = RETURN;
            (yyval.token_p) = p;
     }
#line 1772 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 296 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            p->type = RETURN;
            (yyval.token_p) = p;
     }
#line 1782 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 301 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = IF;
            (yyval.token_p) = p;
     }
#line 1794 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 308 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-4].token_p));
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = IF;
            (yyval.token_p) = p;
     }
#line 1807 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 316 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = WHILE;
            (yyval.token_p) = p;
     }
#line 1819 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 326 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(deflist, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-1].token_p));
            insert(p, (yyvsp[0].token_p));
            (yyval.token_p) = p;
        }
#line 1830 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 332 "syntax.y" /* yacc.c:1646  */
    {
            p = NULL; 
            (yyval.token_p) = p;
        }
#line 1839 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 340 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(def, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[-1].token_p));
            (yyval.token_p) = p;
    }
#line 1850 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 350 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(declist, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[0].token_p));
            (yyval.token_p)  = p;
        }
#line 1860 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 355 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(declist, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            (yyval.token_p) = p;
        }
#line 1871 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 364 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(dec, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[0].token_p));
            p->type = vardec;
            (yyval.token_p) = p;
    }
#line 1882 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 370 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(dec, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = ASSIGNOP;
            (yyval.token_p) = p;
    }
#line 1894 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 380 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = ASSIGNOP;
            (yyval.token_p) = p;
    }
#line 1906 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 387 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = AND;
            (yyval.token_p) = p;
    }
#line 1918 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 394 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = OR;
            (yyval.token_p) = p;
    }
#line 1930 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 401 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = JUDGE_BIGGER;
            (yyval.token_p) = p;
    }
#line 1942 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 408 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = JUDGE_SMALLER;
            (yyval.token_p) = p;
    }
#line 1954 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 415 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = JUDGE_BIGGER_EQUAL;
            (yyval.token_p) = p;
    }
#line 1966 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 422 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = JUDGE_SMALLER_EQUAL;
            (yyval.token_p) = p;
    }
#line 1978 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 429 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = JUDGE_NOT_EQUAL;
            (yyval.token_p) = p;
    }
#line 1990 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 436 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = JUDGE_EQUAL;
            (yyval.token_p) = p;
    }
#line 2002 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 443 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = PLUS;
            (yyval.token_p) = p;
    }
#line 2014 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 450 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = SUB;
            (yyval.token_p) = p;
    }
#line 2026 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 457 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = MUL;
            (yyval.token_p) = p;
    }
#line 2038 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 464 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            p->type = DIV;
            (yyval.token_p) = p;
    }
#line 2050 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 471 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-1].token_p));
            p->type = exp;
            (yyval.token_p) = p;
    }
#line 2061 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 477 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[0].token_p));
            p->type = MUL;
            (yyval.token_p) = p;
    }
#line 2072 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 483 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[0].token_p));
            p->type = NOT;
            (yyval.token_p) = p;
    }
#line 2083 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 489 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-1].token_p));
            p->word_name = (char *)malloc(sizeof(char) * strlen((yyvsp[-3].type_string)));
            strcpy(p->word_name, (yyvsp[-3].type_string));
            p->type = fundec;
            (yyval.token_p) = p; 
    }
#line 2096 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 497 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * strlen((yyvsp[-2].type_string)));
            strcpy(p->word_name, (yyvsp[-2].type_string));
            p->type = fundec;
            (yyval.token_p) = p;
    }
#line 2108 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 504 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-3].token_p));
            insert(p, (yyvsp[-1].token_p));
            p->type = array;  // 代表节点下为数组
            (yyval.token_p) = p;
    }
#line 2120 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 511 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            p->word_name = (char *)malloc(sizeof(char) * strlen((yyvsp[0].type_string)));
            strcpy(p->word_name, (yyvsp[0].type_string));
            p->type = POINT;
            (yyval.token_p) = p;
    }
#line 2133 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 519 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            p->type = WORD;
            p->word_name = (char *)malloc(sizeof(char) * strlen((yyvsp[0].type_string)));
            strcpy(p->word_name, (yyvsp[0].type_string));
            (yyval.token_p) =  p;
    }
#line 2145 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 526 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[0].token_p));
            p->type = constant;
            (yyval.token_p) =  p;
    }
#line 2156 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 535 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(constant, yylineno, yylloc.first_column, 0);
            p->type = INT;
            p->v.int_value = (yyvsp[0].type_int);
            (yyval.token_p) = p; 
         }
#line 2167 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 541 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(constant, yylineno, yylloc.first_column, 0);
            p->type = CHAR;
            p->v.char_value = (yyvsp[0].type_char);
            (yyval.token_p) = p;
         }
#line 2178 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 547 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(constant, yylineno, yylloc.first_column, 0);
            p->type = FLOAT;
            p->v.float_value = (yyvsp[0].type_float);
            (yyval.token_p) = p;
         }
#line 2189 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 556 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(args, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[-2].token_p));
            insert(p, (yyvsp[0].token_p));
            (yyval.token_p) = p;
     }
#line 2200 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 562 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(args, yylineno, yylloc.first_column, 0);
            insert(p, (yyvsp[0].token_p));
            (yyval.token_p) = p;
     }
#line 2210 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 604 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(type, yylineno, yylloc.first_column, 0);
            p->type = INT;
            (yyval.token_p) = p;
     }
#line 2220 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 609 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(type, yylineno, yylloc.first_column, 0);
            p->type = FLOAT;
            (yyval.token_p) = p;
     }
#line 2230 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 614 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(type, yylineno, yylloc.first_column, 0);
            p->type = SHORT;
            (yyval.token_p) = p;
     }
#line 2240 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 619 "syntax.y" /* yacc.c:1646  */
    {
            p = NewNode(type, yylineno, yylloc.first_column, 0);
            p->type = DOUBLE;
            (yyval.token_p) = p;
     }
#line 2250 "syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2254 "syntax.tab.c" /* yacc.c:1646  */
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
#line 626 "syntax.y" /* yacc.c:1906  */


/* --yyerror-- */
int yyerror(const char* msg) {
    fprintf(stderr, "Error type B in line %d:%d: \"%s\"\n",yylineno,yylloc.first_column, msg);
    return 1;
}

/* --insert-- */
void insert(struct Node* parent, struct Node* child) {
    struct Node *p;
    if(child == NULL) {
        return;
    }
    if(parent->No_Child == 0) {
        parent->child = child;
        child->IsBegin = 1;
        parent->No_Child = 1;
    }
    else {
        p = parent->child;
        while(p->brother!= NULL) {
            p = p->brother;
        }
        p->brother = child;
        child->IsBegin = 0;
        parent->No_Child++;
    }
}


