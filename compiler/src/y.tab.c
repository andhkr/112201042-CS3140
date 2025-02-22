/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 18 "src/compiler.y"
	
	#include <stdio.h>
	#include "include/ast.h"
	#include "include/symbtbl_manager.h"
	#include <assert.h>
	#include <string.h>
	#include <stdbool.h>

	int yylex();
	void yyerror( char* );
	extern FILE* yyin;
	extern int wflag;
	int i;

#line 86 "src/y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "y.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_WRITE = 3,                      /* WRITE  */
  YYSYMBOL_DECL = 4,                       /* DECL  */
  YYSYMBOL_ENDDECL = 5,                    /* ENDDECL  */
  YYSYMBOL_T_INT = 6,                      /* T_INT  */
  YYSYMBOL_T_BOOL = 7,                     /* T_BOOL  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_LOGICAL_AND = 10,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_NOT = 11,               /* LOGICAL_NOT  */
  YYSYMBOL_LOGICAL_OR = 12,                /* LOGICAL_OR  */
  YYSYMBOL_EQUALEQUAL = 13,                /* EQUALEQUAL  */
  YYSYMBOL_LESSTHANOREQUAL = 14,           /* LESSTHANOREQUAL  */
  YYSYMBOL_GREATERTHANOREQUAL = 15,        /* GREATERTHANOREQUAL  */
  YYSYMBOL_NOTEQUAL = 16,                  /* NOTEQUAL  */
  YYSYMBOL_FOR = 17,                       /* FOR  */
  YYSYMBOL_VAR = 18,                       /* VAR  */
  YYSYMBOL_NUM = 19,                       /* NUM  */
  YYSYMBOL_T = 20,                         /* T  */
  YYSYMBOL_F = 21,                         /* F  */
  YYSYMBOL_22_ = 22,                       /* '='  */
  YYSYMBOL_23_ = 23,                       /* '<'  */
  YYSYMBOL_24_ = 24,                       /* '>'  */
  YYSYMBOL_25_ = 25,                       /* '+'  */
  YYSYMBOL_26_ = 26,                       /* '-'  */
  YYSYMBOL_27_ = 27,                       /* '*'  */
  YYSYMBOL_28_ = 28,                       /* '/'  */
  YYSYMBOL_29_ = 29,                       /* '%'  */
  YYSYMBOL_30_ = 30,                       /* ';'  */
  YYSYMBOL_31_ = 31,                       /* ','  */
  YYSYMBOL_32_ = 32,                       /* '['  */
  YYSYMBOL_33_ = 33,                       /* ']'  */
  YYSYMBOL_34_ = 34,                       /* '('  */
  YYSYMBOL_35_ = 35,                       /* ')'  */
  YYSYMBOL_36_ = 36,                       /* '"'  */
  YYSYMBOL_37_ = 37,                       /* '{'  */
  YYSYMBOL_38_ = 38,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_Prog = 40,                      /* Prog  */
  YYSYMBOL_Gdecl_sec = 41,                 /* Gdecl_sec  */
  YYSYMBOL_Gdecl_list = 42,                /* Gdecl_list  */
  YYSYMBOL_Gdecl = 43,                     /* Gdecl  */
  YYSYMBOL_ret_type = 44,                  /* ret_type  */
  YYSYMBOL_Glist = 45,                     /* Glist  */
  YYSYMBOL_Gid = 46,                       /* Gid  */
  YYSYMBOL_func = 47,                      /* func  */
  YYSYMBOL_arg_list = 48,                  /* arg_list  */
  YYSYMBOL_arg_list1 = 49,                 /* arg_list1  */
  YYSYMBOL_arg = 50,                       /* arg  */
  YYSYMBOL_arg_type = 51,                  /* arg_type  */
  YYSYMBOL_var_list = 52,                  /* var_list  */
  YYSYMBOL_stmt_list = 53,                 /* stmt_list  */
  YYSYMBOL_statement = 54,                 /* statement  */
  YYSYMBOL_write_stmt = 55,                /* write_stmt  */
  YYSYMBOL_assign_stmt = 56,               /* assign_stmt  */
  YYSYMBOL_cond_stmt = 57,                 /* cond_stmt  */
  YYSYMBOL_expr = 58,                      /* expr  */
  YYSYMBOL_str_expr = 59,                  /* str_expr  */
  YYSYMBOL_var_expr = 60                   /* var_expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   263

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  121

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    36,     2,     2,    29,     2,     2,
      34,    35,    27,    25,    31,    26,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
      23,    22,    24,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    72,    72,    75,    77,    78,    81,    89,    89,    94,
      95,    99,   102,   107,   118,   121,   122,   125,   126,   129,
     132,   135,   136,   139,   140,   141,   144,   149,   152,   157,
     160,   163,   167,   172,   181,   191,   200,   207,   214,   217,
     218,   220,   223,   226,   229,   232,   235,   238,   239,   240,
     241,   242,   245,   246,   247,   249,   254,   257,   262
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "WRITE", "DECL",
  "ENDDECL", "T_INT", "T_BOOL", "IF", "ELSE", "LOGICAL_AND", "LOGICAL_NOT",
  "LOGICAL_OR", "EQUALEQUAL", "LESSTHANOREQUAL", "GREATERTHANOREQUAL",
  "NOTEQUAL", "FOR", "VAR", "NUM", "T", "F", "'='", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "';'", "','", "'['", "']'", "'('", "')'",
  "'\"'", "'{'", "'}'", "$accept", "Prog", "Gdecl_sec", "Gdecl_list",
  "Gdecl", "ret_type", "Glist", "Gid", "func", "arg_list", "arg_list1",
  "arg", "arg_type", "var_list", "stmt_list", "statement", "write_stmt",
  "assign_stmt", "cond_stmt", "expr", "str_expr", "var_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-36)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-24)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       0,    19,    61,   245,   -36,   -36,    12,    19,    47,   -36,
      38,    45,    75,    46,   -36,   -36,    49,    55,    58,   -36,
      26,   -36,   -36,    57,    62,     1,    69,   -36,    63,    75,
     -36,   -36,   -36,    75,    75,   104,    43,    88,   -36,   -36,
     -36,    75,    75,   105,   -36,    47,    93,    47,   106,   124,
     -36,    44,   148,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    52,    83,   215,   172,
     -36,    87,    96,   -36,   107,   -36,    90,   -36,   -36,    41,
     -36,   -36,   -36,   -36,     2,     2,     2,     2,    -7,    -7,
      44,    44,    92,    92,    95,    97,    75,   -36,   -36,   105,
     111,   -36,   -36,   -36,   108,   135,   194,   -36,   107,   -36,
     109,    88,   -36,    52,   110,   116,   118,   -36,    52,   119,
     -36
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     0,     7,     8,     0,     4,     0,     1,
       0,     0,     0,     0,    57,     2,     0,     0,     0,    28,
       0,     3,     5,    12,     0,     9,     0,    25,     0,     0,
      35,    36,    37,     0,     0,     0,    39,     0,    24,    27,
      26,     0,     0,    15,     6,     0,     0,     0,     0,     0,
      52,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
      20,     0,    16,    18,     0,    10,     0,    11,    55,     0,
      29,    40,    53,    54,    51,    49,    48,    50,    46,    47,
      41,    42,    43,    44,    45,     0,     0,    58,    14,     0,
      21,    19,    13,    56,     0,    32,     0,    17,     0,    30,
       0,     0,    22,     0,     0,     0,     0,    33,     0,     0,
      34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -36,   -36,   -36,   149,   -36,   -36,    17,   -36,   -36,   -36,
     -36,    66,   -36,    59,   -15,   -36,   -36,   -35,   -36,   -18,
     -36,    -3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     6,     7,     8,    24,    25,    26,    71,
      72,    73,    74,   101,    15,    16,    17,    18,    19,    35,
      79,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      20,    38,    67,    53,     1,    54,    55,    56,    57,    58,
      49,    50,    53,    20,    54,    51,    52,    21,    61,    62,
      63,    64,    65,    68,    69,     4,     5,    61,    62,    63,
      64,    65,    45,    46,    20,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    41,   -23,
      10,    95,    11,    10,    53,    11,    54,    12,    42,   103,
      12,     9,    75,    20,    77,    23,    13,    14,    27,    13,
      14,    63,    64,    65,    29,    42,   114,   104,   106,    28,
      37,    14,    30,    31,    32,    39,    29,   -23,    40,    33,
     -23,    43,    44,    14,    30,    31,    32,    34,   115,    48,
      47,    33,    53,   119,    54,    53,    14,    54,    20,    34,
      20,    70,    76,    96,    53,    20,    54,    55,    56,    57,
      58,    65,    98,   102,    78,   100,    99,    59,    60,    61,
      62,    63,    64,    65,    53,   105,    54,    55,    56,    57,
      58,    66,   108,   109,   110,   116,   113,    59,    60,    61,
      62,    63,    64,    65,   117,   118,    22,   120,    53,    80,
      54,    55,    56,    57,    58,   107,     0,   112,     0,     0,
       0,    59,    60,    61,    62,    63,    64,    65,     0,     0,
       0,     0,    53,    81,    54,    55,    56,    57,    58,     0,
       0,     0,     0,     0,     0,    59,    60,    61,    62,    63,
      64,    65,     0,     0,    53,    97,    54,    55,    56,    57,
      58,     0,     0,     0,     0,     0,     0,    59,    60,    61,
      62,    63,    64,    65,   111,    53,     0,    54,    55,    56,
      57,    58,     0,     0,     0,     0,     0,     0,    59,    60,
      61,    62,    63,    64,    65,   -23,    10,     0,    11,     0,
       0,     0,     0,    12,     0,     0,     0,     0,     0,     0,
       0,     0,    13,    14
};

static const yytype_int8 yycheck[] =
{
       3,    16,    37,    10,     4,    12,    13,    14,    15,    16,
      28,    29,    10,    16,    12,    33,    34,     5,    25,    26,
      27,    28,    29,    41,    42,     6,     7,    25,    26,    27,
      28,    29,    31,    32,    37,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    22,     0,
       1,    66,     3,     1,    10,     3,    12,     8,    32,    18,
       8,     0,    45,    66,    47,    18,    17,    18,    30,    17,
      18,    27,    28,    29,    11,    32,   111,    36,    96,    34,
      34,    18,    19,    20,    21,    30,    11,    38,    30,    26,
      38,    34,    30,    18,    19,    20,    21,    34,   113,    36,
      31,    26,    10,   118,    12,    10,    18,    12,   111,    34,
     113,     6,    19,    30,    10,   118,    12,    13,    14,    15,
      16,    29,    35,    33,    18,    18,    30,    23,    24,    25,
      26,    27,    28,    29,    10,    38,    12,    13,    14,    15,
      16,    37,    31,    35,     9,    35,    37,    23,    24,    25,
      26,    27,    28,    29,    38,    37,     7,    38,    10,    35,
      12,    13,    14,    15,    16,    99,    -1,   108,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      -1,    -1,    10,    35,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    10,    33,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    10,    -1,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,     0,     1,    -1,     3,    -1,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,    40,    41,     6,     7,    42,    43,    44,     0,
       1,     3,     8,    17,    18,    53,    54,    55,    56,    57,
      60,     5,    42,    18,    45,    46,    47,    30,    34,    11,
      19,    20,    21,    26,    34,    58,    60,    34,    53,    30,
      30,    22,    32,    34,    30,    31,    32,    31,    36,    58,
      58,    58,    58,    10,    12,    13,    14,    15,    16,    23,
      24,    25,    26,    27,    28,    29,    37,    56,    58,    58,
       6,    48,    49,    50,    51,    45,    19,    45,    18,    59,
      35,    35,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    53,    30,    33,    35,    30,
      18,    52,    33,    18,    36,    38,    58,    50,    31,    35,
       9,    30,    52,    37,    56,    53,    35,    38,    37,    53,
      38
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    42,    42,    43,    44,    44,    45,
      45,    45,    46,    46,    47,    48,    48,    49,    49,    50,
      51,    52,    52,    53,    53,    53,    54,    54,    54,    55,
      55,    56,    57,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    59,    59,    60,    60
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     0,     2,     3,     1,     1,     1,
       3,     3,     1,     4,     4,     0,     1,     3,     1,     2,
       1,     1,     3,     0,     2,     2,     2,     2,     1,     4,
       6,     3,     5,     9,    11,     1,     1,     1,     2,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     1,     2,     1,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 3: /* Gdecl_sec: DECL Gdecl_list ENDDECL  */
#line 75 "src/compiler.y"
                                               {}
#line 1235 "src/y.tab.c"
    break;

  case 4: /* Gdecl_list: %empty  */
#line 77 "src/compiler.y"
                                 {}
#line 1241 "src/y.tab.c"
    break;

  case 5: /* Gdecl_list: Gdecl Gdecl_list  */
#line 78 "src/compiler.y"
                                         {}
#line 1247 "src/y.tab.c"
    break;

  case 6: /* Gdecl: ret_type Glist ';'  */
#line 81 "src/compiler.y"
                                            {
										(yyvsp[-2].treeNode)->ptr_sibling = (yyvsp[-1].treeNode);
										node* dec = create_empty_node("DECL");
										dec->ptr_children_list = (yyvsp[-2].treeNode);
										graph(dec);										
									}
#line 1258 "src/y.tab.c"
    break;

  case 8: /* ret_type: T_BOOL  */
#line 89 "src/compiler.y"
                                                {
										(yyval.treeNode) = (yyvsp[0].treeNode);
									}
#line 1266 "src/y.tab.c"
    break;

  case 9: /* Glist: Gid  */
#line 94 "src/compiler.y"
                                        {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 1272 "src/y.tab.c"
    break;

  case 10: /* Glist: Gid ',' Glist  */
#line 95 "src/compiler.y"
                                        { 
								(yyvsp[-2].treeNode)->ptr_sibling = (yyvsp[0].treeNode);
								(yyval.treeNode) = (yyvsp[-2].treeNode);
							}
#line 1281 "src/y.tab.c"
    break;

  case 12: /* Gid: VAR  */
#line 102 "src/compiler.y"
                                        { 
						node* var_node = create_empty_node((yyvsp[0].entry)->name);
						var_node->entry = (yyvsp[0].entry);
						(yyval.treeNode) = var_node;;
					}
#line 1291 "src/y.tab.c"
    break;

  case 13: /* Gid: Gid '[' NUM ']'  */
#line 107 "src/compiler.y"
                                        {
						/*array creation*/
						add_array_to_symbtbl((yyvsp[-3].treeNode),(yyvsp[-1].var));
						node* arr = create_empty_node("array declaration");
						char word[13];
						snprintf(word,sizeof(word),"%d",(yyvsp[-1].var));
						node* right = create_empty_node(word);
						arr->ptr_children_list = (yyvsp[-3].treeNode);
						(yyvsp[-3].treeNode)->ptr_sibling = right;
						(yyval.treeNode) = arr;
					}
#line 1307 "src/y.tab.c"
    break;

  case 14: /* func: VAR '(' arg_list ')'  */
#line 118 "src/compiler.y"
                                                                                { 					}
#line 1313 "src/y.tab.c"
    break;

  case 20: /* arg_type: T_INT  */
#line 132 "src/compiler.y"
                                         {  }
#line 1319 "src/y.tab.c"
    break;

  case 21: /* var_list: VAR  */
#line 135 "src/compiler.y"
                                         { }
#line 1325 "src/y.tab.c"
    break;

  case 22: /* var_list: VAR ',' var_list  */
#line 136 "src/compiler.y"
                                         { 	}
#line 1331 "src/y.tab.c"
    break;

  case 23: /* stmt_list: %empty  */
#line 139 "src/compiler.y"
                                                {  ;}
#line 1337 "src/y.tab.c"
    break;

  case 24: /* stmt_list: statement stmt_list  */
#line 140 "src/compiler.y"
                                                {						}
#line 1343 "src/y.tab.c"
    break;

  case 25: /* stmt_list: error ';'  */
#line 141 "src/compiler.y"
                                                {fprintf(stderr,"Error : Syntax Error\n");}
#line 1349 "src/y.tab.c"
    break;

  case 26: /* statement: assign_stmt ';'  */
#line 144 "src/compiler.y"
                                         { /*print asignment syntax tree*/
								if(stm_stack.sp == 0)
									graph((yyvsp[-1].treeNode));
									
								}
#line 1359 "src/y.tab.c"
    break;

  case 27: /* statement: write_stmt ';'  */
#line 149 "src/compiler.y"
                                                 {/*print write syntax tree*/
									graph((yyvsp[-1].treeNode));
								}
#line 1367 "src/y.tab.c"
    break;

  case 28: /* statement: cond_stmt  */
#line 152 "src/compiler.y"
                                                        {/*print cond_stmt syntax tree*/
									graph((yyvsp[0].treeNode));
								}
#line 1375 "src/y.tab.c"
    break;

  case 29: /* write_stmt: WRITE '(' expr ')'  */
#line 157 "src/compiler.y"
                                                {
										(yyval.treeNode) = create_node_ast(FUN_CALL,NULL,(yyvsp[-3].treeNode),(yyvsp[-1].treeNode));
									}
#line 1383 "src/y.tab.c"
    break;

  case 30: /* write_stmt: WRITE '(' '"' str_expr '"' ')'  */
#line 160 "src/compiler.y"
                                                     { /*unable to understand*/;}
#line 1389 "src/y.tab.c"
    break;

  case 31: /* assign_stmt: var_expr '=' expr  */
#line 163 "src/compiler.y"
                                                { 	
											(yyval.treeNode) = create_node_ast(ASSIGN,NULL,(yyvsp[-2].treeNode),(yyvsp[0].treeNode));		
										}
#line 1397 "src/y.tab.c"
    break;

  case 32: /* cond_stmt: IF expr '{' stmt_list '}'  */
#line 167 "src/compiler.y"
                                                        {	
												(yyvsp[-4].treeNode)->ptr_children_list = (yyvsp[-3].treeNode);
												(yyvsp[-3].treeNode)->ptr_sibling = (yyvsp[-1].treeNode);
												(yyval.treeNode) = (yyvsp[-4].treeNode);
											}
#line 1407 "src/y.tab.c"
    break;

  case 33: /* cond_stmt: IF expr '{' stmt_list '}' ELSE '{' stmt_list '}'  */
#line 172 "src/compiler.y"
                                                                        { 
																node* branch = create_empty_node("branch");
																branch->ptr_children_list = (yyvsp[-8].treeNode);
																(yyvsp[-8].treeNode)->ptr_children_list = (yyvsp[-7].treeNode);
																(yyvsp[-7].treeNode)->ptr_sibling = (yyvsp[-5].treeNode);
																(yyvsp[-8].treeNode)->ptr_sibling = (yyvsp[-3].treeNode);
																(yyvsp[-3].treeNode)->ptr_children_list = (yyvsp[-1].treeNode);
																(yyval.treeNode) = branch;
															}
#line 1421 "src/y.tab.c"
    break;

  case 34: /* cond_stmt: FOR '(' assign_stmt ';' expr ';' assign_stmt ')' '{' stmt_list '}'  */
#line 181 "src/compiler.y"
                                                                                        { 
																						(yyvsp[-10].treeNode)->ptr_children_list = (yyvsp[-8].treeNode);
																						(yyvsp[-8].treeNode)->ptr_sibling = (yyvsp[-6].treeNode);
																						(yyvsp[-6].treeNode)->ptr_sibling = (yyvsp[-4].treeNode);
																						(yyvsp[-4].treeNode)->ptr_sibling = (yyvsp[-1].treeNode);
																						for_loop((yyvsp[-10].treeNode));
																						(yyval.treeNode) = (yyvsp[-10].treeNode);
		                                                							}
#line 1434 "src/y.tab.c"
    break;

  case 35: /* expr: NUM  */
#line 191 "src/compiler.y"
                                        {
								char word[13];
								snprintf(word,sizeof(word),"%d",(yyvsp[0].var));
								node* num = create_empty_node(word);
								num->type = INT;
								memset(&num->exp_value,0,sizeof(datavalue));
								num->exp_value.integer = (yyvsp[0].var);
								(yyval.treeNode) = num;
							}
#line 1448 "src/y.tab.c"
    break;

  case 36: /* expr: T  */
#line 200 "src/compiler.y"
                                                        { 						  	
								node* True = create_empty_node("true");
								True->type = BOOL;
								memset(&True->exp_value,0,sizeof(datavalue));
								True->exp_value.boolean = (yyvsp[0].b_var);
								(yyval.treeNode) = True;
							}
#line 1460 "src/y.tab.c"
    break;

  case 37: /* expr: F  */
#line 207 "src/compiler.y"
                                                        { 
								node* False = create_empty_node("false");
								False->type = BOOL;
								memset(&False->exp_value,0,sizeof(datavalue));
								False->exp_value.boolean = (yyvsp[0].b_var);
								(yyval.treeNode) = False;
							}
#line 1472 "src/y.tab.c"
    break;

  case 38: /* expr: '-' expr  */
#line 214 "src/compiler.y"
                                                {
								(yyval.treeNode) = create_node_ast(U_MINUS,NULL,NULL,(yyvsp[0].treeNode));
							}
#line 1480 "src/y.tab.c"
    break;

  case 39: /* expr: var_expr  */
#line 217 "src/compiler.y"
                                                {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 1486 "src/y.tab.c"
    break;

  case 40: /* expr: '(' expr ')'  */
#line 218 "src/compiler.y"
                                                {(yyval.treeNode) = (yyvsp[-1].treeNode);}
#line 1492 "src/y.tab.c"
    break;

  case 41: /* expr: expr '+' expr  */
#line 220 "src/compiler.y"
                                                { 
									(yyval.treeNode) = create_node_ast(PLUS,NULL,(yyvsp[-2].treeNode),(yyvsp[0].treeNode));
								}
#line 1500 "src/y.tab.c"
    break;

  case 42: /* expr: expr '-' expr  */
#line 223 "src/compiler.y"
                                                {
									(yyval.treeNode) = create_node_ast(SUB,NULL,(yyvsp[-2].treeNode),(yyvsp[0].treeNode));
		 						}
#line 1508 "src/y.tab.c"
    break;

  case 43: /* expr: expr '*' expr  */
#line 226 "src/compiler.y"
                                                {
									(yyval.treeNode) = create_node_ast(MUL,NULL,(yyvsp[-2].treeNode),(yyvsp[0].treeNode));
		 						}
#line 1516 "src/y.tab.c"
    break;

  case 44: /* expr: expr '/' expr  */
#line 229 "src/compiler.y"
                                                { 	
									(yyval.treeNode) = create_node_ast(DIV,NULL,(yyvsp[-2].treeNode),(yyvsp[0].treeNode));
								}
#line 1524 "src/y.tab.c"
    break;

  case 45: /* expr: expr '%' expr  */
#line 232 "src/compiler.y"
                                                {   
															
								}
#line 1532 "src/y.tab.c"
    break;

  case 46: /* expr: expr '<' expr  */
#line 235 "src/compiler.y"
                                                {
									(yyval.treeNode) = create_node_ast(LESSTHAN,NULL,(yyvsp[-2].treeNode),(yyvsp[0].treeNode));
		 						}
#line 1540 "src/y.tab.c"
    break;

  case 47: /* expr: expr '>' expr  */
#line 238 "src/compiler.y"
                                                { 						}
#line 1546 "src/y.tab.c"
    break;

  case 48: /* expr: expr GREATERTHANOREQUAL expr  */
#line 239 "src/compiler.y"
                                                                                { 						}
#line 1552 "src/y.tab.c"
    break;

  case 49: /* expr: expr LESSTHANOREQUAL expr  */
#line 240 "src/compiler.y"
                                                        {  						}
#line 1558 "src/y.tab.c"
    break;

  case 50: /* expr: expr NOTEQUAL expr  */
#line 241 "src/compiler.y"
                                                                { 						}
#line 1564 "src/y.tab.c"
    break;

  case 51: /* expr: expr EQUALEQUAL expr  */
#line 242 "src/compiler.y"
                                                {
										(yyval.treeNode) = create_node_ast(EQUAL_EQUAL,NULL,(yyvsp[-2].treeNode),(yyvsp[0].treeNode));
		 							}
#line 1572 "src/y.tab.c"
    break;

  case 52: /* expr: LOGICAL_NOT expr  */
#line 245 "src/compiler.y"
                                                { 						}
#line 1578 "src/y.tab.c"
    break;

  case 53: /* expr: expr LOGICAL_AND expr  */
#line 246 "src/compiler.y"
                                                { 						}
#line 1584 "src/y.tab.c"
    break;

  case 54: /* expr: expr LOGICAL_OR expr  */
#line 247 "src/compiler.y"
                                                {}
#line 1590 "src/y.tab.c"
    break;

  case 55: /* str_expr: VAR  */
#line 249 "src/compiler.y"
                        {		node* var_node = create_empty_node((yyvsp[0].entry)->name);
							var_node->entry = (yyvsp[0].entry);
							update_data(&var_node->exp_value,&(yyvsp[0].entry)->value,datasize[(yyvsp[0].entry)->type]);
							(yyval.treeNode) = var_node;
								}
#line 1600 "src/y.tab.c"
    break;

  case 56: /* str_expr: str_expr VAR  */
#line 254 "src/compiler.y"
                                   { ;}
#line 1606 "src/y.tab.c"
    break;

  case 57: /* var_expr: VAR  */
#line 257 "src/compiler.y"
                                {			node* var_node = create_empty_node((yyvsp[0].entry)->name);
								var_node->entry = (yyvsp[0].entry);
								update_data(&var_node->exp_value,&(yyvsp[0].entry)->value,datasize[(yyvsp[0].entry)->type]);
								(yyval.treeNode) = var_node;
					}
#line 1616 "src/y.tab.c"
    break;

  case 58: /* var_expr: var_expr '[' expr ']'  */
#line 262 "src/compiler.y"
                                                {
										char* label = "ArrayAccess";
										(yyvsp[-3].treeNode)->label = strdup(label);
										update_data(&(yyvsp[-3].treeNode)->exp_value,&(yyvsp[-1].treeNode)->exp_value.integer,sizeof(int));
										make_node((yyvsp[-3].treeNode));
										(yyvsp[-3].treeNode)->type = (yyvsp[-3].treeNode)->entry->type;
										(yyval.treeNode) = (yyvsp[-3].treeNode);
									}
#line 1629 "src/y.tab.c"
    break;


#line 1633 "src/y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 271 "src/compiler.y"


void yyerror ( char  *s) {
   fprintf (stderr, "%s\n", s);
}

int main(int argc,char** argv){
	symbltbl = create_symbtbl(64,hashvalue_of_key,0);
	init_symbtbl_manager(&manager);
	push_back(&manager,symbltbl);
	init_stmt_stack(&stm_stack);
	wflag = 1;
	yyparse();
	print_symbol_table();
	// free_symbol_table_manager(&manager);
	// free_graph();
	return 0;
}
