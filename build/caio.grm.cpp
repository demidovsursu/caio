/* A Bison parser, made by GNU Bison 3.7.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */

#include "caio.hpp"

#define YYLLOC_DEFAULT(Current, Rhs, N)                        \
    do {                                                       \
      if (N)                                                   \
        {                                                      \
          (Current).first   = YYRHSLOC (Rhs, 1).first;         \
          (Current).last  = YYRHSLOC (Rhs, N).last;            \
        }                                                      \
      else                                                     \
        {                                                      \
          (Current).first = (Current).last = YYRHSLOC (Rhs, 0).last; \
        }                                                      \
      yyclear_attr(yyval);                                     \
    } while (0)


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
    YYUNDEF = 1023,                /* "invalid token"  */
    T_1001 = 1001,                 /* "%code"  */
    T_1002 = 1002,                 /* "%operator"  */
    T_1003 = 1003,                 /* "%option"  */
    T_1004 = 1004,                 /* "%type"  */
    T_1005 = 1005,                 /* "%using"  */
    T_1006 = 1006,                 /* "%{"  */
    T_1007 = 1007,                 /* "default"  */
    T_1008 = 1008,                 /* "match"  */
    T_1009 = 1009,                 /* "rule"  */
    T_1010 = 1010,                 /* "visit"  */
    T_1011 = 1011,                 /* "visitor"  */
    T_1012 = 1012,                 /* "?%%code?"  */
    T_1013 = 1013,                 /* "?%%grm?"  */
    T_1014 = 1014,                 /* "?%%lex?"  */
    T_1015 = 1015,                 /* "?const?"  */
    T_1016 = 1016,                 /* "?id?"  */
    T_1017 = 1017,                 /* "?lexem?"  */
    T_1018 = 1018,                 /* "?number?"  */
    T_1019 = 1019,                 /* "?re?"  */
    T_1020 = 1020,                 /* "?ref?"  */
    T_1021 = 1021,                 /* "?spaces?"  */
    T_1022 = 1022                  /* "?terminal?"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (void *scanner);


/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_1001 = 3,                     /* "%code"  */
  YYSYMBOL_T_1002 = 4,                     /* "%operator"  */
  YYSYMBOL_T_1003 = 5,                     /* "%option"  */
  YYSYMBOL_T_1004 = 6,                     /* "%type"  */
  YYSYMBOL_T_1005 = 7,                     /* "%using"  */
  YYSYMBOL_T_1006 = 8,                     /* "%{"  */
  YYSYMBOL_T_1007 = 9,                     /* "default"  */
  YYSYMBOL_T_1008 = 10,                    /* "match"  */
  YYSYMBOL_T_1009 = 11,                    /* "rule"  */
  YYSYMBOL_T_1010 = 12,                    /* "visit"  */
  YYSYMBOL_T_1011 = 13,                    /* "visitor"  */
  YYSYMBOL_T_1012 = 14,                    /* "?%%code?"  */
  YYSYMBOL_T_1013 = 15,                    /* "?%%grm?"  */
  YYSYMBOL_T_1014 = 16,                    /* "?%%lex?"  */
  YYSYMBOL_T_1015 = 17,                    /* "?const?"  */
  YYSYMBOL_T_1016 = 18,                    /* "?id?"  */
  YYSYMBOL_T_1017 = 19,                    /* "?lexem?"  */
  YYSYMBOL_T_1018 = 20,                    /* "?number?"  */
  YYSYMBOL_T_1019 = 21,                    /* "?re?"  */
  YYSYMBOL_T_1020 = 22,                    /* "?ref?"  */
  YYSYMBOL_T_1021 = 23,                    /* "?spaces?"  */
  YYSYMBOL_T_1022 = 24,                    /* "?terminal?"  */
  YYSYMBOL_25_ = 25,                       /* '<'  */
  YYSYMBOL_26_ = 26,                       /* '>'  */
  YYSYMBOL_27_ = 27,                       /* '}'  */
  YYSYMBOL_28_ = 28,                       /* '?'  */
  YYSYMBOL_29_ = 29,                       /* '*'  */
  YYSYMBOL_30_ = 30,                       /* ':'  */
  YYSYMBOL_31_ = 31,                       /* '('  */
  YYSYMBOL_32_ = 32,                       /* ')'  */
  YYSYMBOL_33_n_ = 33,                     /* '\n'  */
  YYSYMBOL_34_ = 34,                       /* ';'  */
  YYSYMBOL_35_ = 35,                       /* '|'  */
  YYSYMBOL_36_ = 36,                       /* '{'  */
  YYSYMBOL_37_ = 37,                       /* '+'  */
  YYSYMBOL_38_ = 38,                       /* '-'  */
  YYSYMBOL_39_ = 39,                       /* '['  */
  YYSYMBOL_40_ = 40,                       /* ']'  */
  YYSYMBOL_41_ = 41,                       /* ','  */
  YYSYMBOL_42_ = 42,                       /* '='  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_decl = 45,                      /* decl  */
  YYSYMBOL_type1 = 46,                     /* type1  */
  YYSYMBOL_type2 = 47,                     /* type2  */
  YYSYMBOL_symbol = 48,                    /* symbol  */
  YYSYMBOL_initcode = 49,                  /* initcode  */
  YYSYMBOL_lrule = 50,                     /* lrule  */
  YYSYMBOL_term = 51,                      /* term  */
  YYSYMBOL_lcode = 52,                     /* lcode  */
  YYSYMBOL_alist = 53,                     /* alist  */
  YYSYMBOL_grule = 54,                     /* grule  */
  YYSYMBOL_erule = 55,                     /* erule  */
  YYSYMBOL_xrule = 56,                     /* xrule  */
  YYSYMBOL_lblelem = 57,                   /* lblelem  */
  YYSYMBOL_rcode = 58,                     /* rcode  */
  YYSYMBOL_elem = 59,                      /* elem  */
  YYSYMBOL_xcode = 60,                     /* xcode  */
  YYSYMBOL_ncode = 61,                     /* ncode  */
  YYSYMBOL_xelem = 62,                     /* xelem  */
  YYSYMBOL_mrule = 63,                     /* mrule  */
  YYSYMBOL_vrule = 64,                     /* vrule  */
  YYSYMBOL_list = 65,                      /* list  */
  YYSYMBOL_lelem = 66,                     /* lelem  */
  YYSYMBOL_node = 67,                      /* node  */
  YYSYMBOL_g_1 = 68,                       /* g_1  */
  YYSYMBOL_g_3 = 69,                       /* g_3  */
  YYSYMBOL_g_2 = 70,                       /* g_2  */
  YYSYMBOL_g_4 = 71,                       /* g_4  */
  YYSYMBOL_g_5 = 72,                       /* g_5  */
  YYSYMBOL_g_7 = 73,                       /* g_7  */
  YYSYMBOL_g_6 = 74,                       /* g_6  */
  YYSYMBOL_g_8 = 75,                       /* g_8  */
  YYSYMBOL_g_10 = 76,                      /* g_10  */
  YYSYMBOL_g_9 = 77,                       /* g_9  */
  YYSYMBOL_g_11 = 78,                      /* g_11  */
  YYSYMBOL_g_12 = 79,                      /* g_12  */
  YYSYMBOL_g_14 = 80,                      /* g_14  */
  YYSYMBOL_g_13 = 81,                      /* g_13  */
  YYSYMBOL_g_15 = 82,                      /* g_15  */
  YYSYMBOL_g_16 = 83,                      /* g_16  */
  YYSYMBOL_g_18 = 84,                      /* g_18  */
  YYSYMBOL_g_17 = 85,                      /* g_17  */
  YYSYMBOL_g_20 = 86,                      /* g_20  */
  YYSYMBOL_g_19 = 87,                      /* g_19  */
  YYSYMBOL_g_22 = 88,                      /* g_22  */
  YYSYMBOL_g_21 = 89,                      /* g_21  */
  YYSYMBOL_g_24 = 90,                      /* g_24  */
  YYSYMBOL_g_23 = 91,                      /* g_23  */
  YYSYMBOL_g_26 = 92,                      /* g_26  */
  YYSYMBOL_g_25 = 93,                      /* g_25  */
  YYSYMBOL_g_27 = 94,                      /* g_27  */
  YYSYMBOL_g_29 = 95,                      /* g_29  */
  YYSYMBOL_g_28 = 96,                      /* g_28  */
  YYSYMBOL_g_30 = 97,                      /* g_30  */
  YYSYMBOL_g_31 = 98,                      /* g_31  */
  YYSYMBOL_g_33 = 99,                      /* g_33  */
  YYSYMBOL_g_32 = 100,                     /* g_32  */
  YYSYMBOL_g_34 = 101,                     /* g_34  */
  YYSYMBOL_g_35 = 102,                     /* g_35  */
  YYSYMBOL_g_36 = 103,                     /* g_36  */
  YYSYMBOL_g_37 = 104,                     /* g_37  */
  YYSYMBOL_g_39 = 105,                     /* g_39  */
  YYSYMBOL_g_38 = 106,                     /* g_38  */
  YYSYMBOL_g_40 = 107,                     /* g_40  */
  YYSYMBOL_g_42 = 108,                     /* g_42  */
  YYSYMBOL_g_41 = 109,                     /* g_41  */
  YYSYMBOL_g_43 = 110,                     /* g_43  */
  YYSYMBOL_g_45 = 111,                     /* g_45  */
  YYSYMBOL_g_44 = 112,                     /* g_44  */
  YYSYMBOL_g_47 = 113,                     /* g_47  */
  YYSYMBOL_g_46 = 114,                     /* g_46  */
  YYSYMBOL_g_49 = 115,                     /* g_49  */
  YYSYMBOL_g_48 = 116,                     /* g_48  */
  YYSYMBOL_g_51 = 117,                     /* g_51  */
  YYSYMBOL_g_50 = 118,                     /* g_50  */
  YYSYMBOL_g_52 = 119,                     /* g_52  */
  YYSYMBOL_g_53 = 120,                     /* g_53  */
  YYSYMBOL_g_55 = 121,                     /* g_55  */
  YYSYMBOL_g_54 = 122,                     /* g_54  */
  YYSYMBOL_g_56 = 123,                     /* g_56  */
  YYSYMBOL_g_58 = 124,                     /* g_58  */
  YYSYMBOL_g_57 = 125,                     /* g_57  */
  YYSYMBOL_g_60 = 126,                     /* g_60  */
  YYSYMBOL_g_59 = 127,                     /* g_59  */
  YYSYMBOL_g_61 = 128                      /* g_61  */
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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   246

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  86
/* YYNRULES -- Number of rules.  */
#define YYNRULES  171
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  250

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   1023


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
      33,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      31,    32,    29,    37,    41,    38,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    30,    34,
      25,    42,    26,    28,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,    35,    27,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     2
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   153,   153,   158,   162,   165,   168,   172,   176,   180,
     185,   187,   191,   195,   199,   204,   208,   213,   217,   221,
     226,   231,   236,   240,   244,   248,   253,   257,   261,   265,
     270,   273,   277,   282,   287,   292,   295,   298,   302,   306,
     311,   315,   319,   323,   327,   331,   335,   339,   343,   348,
     351,   354,   358,   362,   366,   370,   374,   378,   382,   386,
     390,   395,   400,   405,   410,   414,   418,   422,   426,   431,
     435,   440,   441,   444,   447,   448,   451,   452,   455,   456,
     459,   462,   463,   466,   467,   472,   475,   476,   479,   480,
     483,   484,   487,   490,   491,   494,   496,   499,   503,   506,
     509,   511,   514,   517,   519,   522,   525,   527,   530,   535,
     537,   540,   543,   544,   547,   548,   553,   556,   557,   560,
     564,   569,   570,   573,   576,   577,   580,   581,   586,   587,
     590,   591,   594,   595,   597,   600,   601,   604,   605,   607,
     610,   611,   614,   616,   621,   624,   625,   628,   631,   632,
     635,   637,   638,   640,   643,   645,   648,   649,   654,   659,
     662,   664,   667,   669,   674,   677,   678,   681,   684,   685,
     688,   689
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"%code\"",
  "\"%operator\"", "\"%option\"", "\"%type\"", "\"%using\"", "\"%{\"",
  "\"default\"", "\"match\"", "\"rule\"", "\"visit\"", "\"visitor\"",
  "\"?%%code?\"", "\"?%%grm?\"", "\"?%%lex?\"", "\"?const?\"", "\"?id?\"",
  "\"?lexem?\"", "\"?number?\"", "\"?re?\"", "\"?ref?\"", "\"?spaces?\"",
  "\"?terminal?\"", "'<'", "'>'", "'}'", "'?'", "'*'", "':'", "'('", "')'",
  "'\\n'", "';'", "'|'", "'{'", "'+'", "'-'", "'['", "']'", "','", "'='",
  "$accept", "program", "decl", "type1", "type2", "symbol", "initcode",
  "lrule", "term", "lcode", "alist", "grule", "erule", "xrule", "lblelem",
  "rcode", "elem", "xcode", "ncode", "xelem", "mrule", "vrule", "list",
  "lelem", "node", "g_1", "g_3", "g_2", "g_4", "g_5", "g_7", "g_6", "g_8",
  "g_10", "g_9", "g_11", "g_12", "g_14", "g_13", "g_15", "g_16", "g_18",
  "g_17", "g_20", "g_19", "g_22", "g_21", "g_24", "g_23", "g_26", "g_25",
  "g_27", "g_29", "g_28", "g_30", "g_31", "g_33", "g_32", "g_34", "g_35",
  "g_36", "g_37", "g_39", "g_38", "g_40", "g_42", "g_41", "g_43", "g_45",
  "g_44", "g_47", "g_46", "g_49", "g_48", "g_51", "g_50", "g_52", "g_53",
  "g_55", "g_54", "g_56", "g_58", "g_57", "g_60", "g_59", "g_61", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,  1023,  1001,  1002,  1003,  1004,  1005,  1006,  1007,
    1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,
    1018,  1019,  1020,  1021,  1022,    60,    62,   125,    63,    42,
      58,    40,    41,    10,    59,   124,   123,    43,    45,    91,
      93,    44,    61
};
#endif

#define YYPACT_NINF (-196)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-122)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -196,    12,    34,  -196,    -2,     5,    13,    19,    48,  -196,
      46,    49,  -196,    42,  -196,    64,    72,    66,  -196,     5,
      61,  -196,  -196,    13,    78,  -196,  -196,    48,    74,    38,
    -196,  -196,  -196,  -196,  -196,  -196,    94,  -196,    76,  -196,
      91,  -196,    83,    92,    65,  -196,  -196,  -196,    88,    99,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,    93,   -15,   103,  -196,  -196,    96,   100,  -196,  -196,
      95,    98,  -196,    78,  -196,  -196,  -196,  -196,  -196,  -196,
      88,    89,  -196,   101,   104,    97,    -9,  -196,   102,  -196,
     111,   -17,   106,  -196,  -196,  -196,  -196,  -196,   100,  -196,
     115,    25,   108,   107,  -196,    81,   118,  -196,  -196,  -196,
    -196,   112,  -196,    11,  -196,  -196,  -196,  -196,  -196,  -196,
     110,  -196,  -196,  -196,   113,  -196,     3,  -196,  -196,  -196,
    -196,   109,   114,  -196,  -196,  -196,  -196,  -196,  -196,   119,
    -196,  -196,    -3,    78,  -196,   127,  -196,  -196,  -196,  -196,
     105,   120,   128,   130,  -196,   122,    41,  -196,   116,  -196,
     123,  -196,    41,  -196,  -196,  -196,   117,  -196,  -196,  -196,
    -196,   124,   121,   129,   131,  -196,  -196,  -196,   134,  -196,
    -196,  -196,  -196,   126,   136,  -196,  -196,   137,    -7,   139,
     135,   141,   132,  -196,  -196,   125,  -196,   145,  -196,  -196,
     133,    88,  -196,  -196,  -196,  -196,  -196,  -196,    36,   138,
    -196,    78,  -196,  -196,   142,  -196,    59,  -196,  -196,    88,
    -196,   143,  -196,  -196,  -196,  -196,  -196,   140,  -196,  -196,
    -196,   158,  -196,   144,  -196,   153,  -196,   127,  -196,  -196,
      -4,    88,  -196,  -196,   147,  -196,  -196,    88,  -196,  -196
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      74,     0,    83,     1,     0,     0,     0,     0,     0,   145,
      76,     0,    72,     0,    75,    88,     0,     0,   109,     6,
      98,    99,   100,     4,     0,   102,   103,     5,     0,    49,
     145,    77,    81,     7,    73,    86,    90,   145,     0,   110,
       0,   101,    15,     0,    10,   104,     8,   143,     0,     0,
      52,    53,    51,    55,    56,    60,    54,   145,   142,   144,
     146,     0,    84,    89,   145,     2,     0,     0,    96,    95,
       0,     0,    93,     0,    11,    13,    67,    66,    64,    65,
       0,     0,   165,     0,     0,     0,     0,    79,     0,    82,
       0,     0,     0,    87,    91,     9,   105,   106,   108,    97,
       0,     3,     0,     0,   151,    63,     0,    57,    20,   117,
     119,     0,    80,   128,   133,   132,   140,    85,   107,    16,
      18,    17,    92,    94,    12,    68,     0,   163,   162,   164,
     166,     0,   120,   122,   145,   129,    27,    28,    21,   130,
      32,   135,    37,   114,    14,     0,   150,   153,   152,   154,
     156,     0,     0,     0,   118,     0,     0,    26,    33,   145,
      41,    40,     0,   140,   140,   140,   137,    34,    36,   141,
     112,     0,    70,     0,     0,   155,   158,    58,     0,   116,
      29,    23,    25,    24,     0,   140,   136,     0,     0,     0,
       0,     0,     0,   138,   139,   115,    19,   170,   148,   148,
       0,   126,   131,   134,    39,    41,    35,    38,    42,    44,
      48,     0,   113,   168,     0,    61,    50,   157,   145,   124,
      30,     0,    47,    43,    45,    46,   111,   171,    69,   147,
     149,     0,    31,   127,    22,     0,   169,     0,   159,   160,
       0,     0,   125,   167,     0,    59,   161,   123,   148,    62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -196,  -196,  -196,  -140,   -71,  -196,  -196,  -196,    -8,  -196,
     -68,  -196,   -77,    -6,  -196,  -196,   -10,   -30,  -195,   -36,
    -196,  -196,   146,  -104,   -55,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,   160,  -196,   157,  -196,   148,  -196,   167,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,    37,  -196,  -196,  -196,   -51,  -196,
    -196,  -196,  -196,  -196,  -196,  -196
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    12,    43,    44,   122,    31,    87,   184,   138,
     219,    92,   140,   141,   166,   167,   168,    28,   215,    58,
     147,   238,    81,    82,   173,    13,    14,     2,    32,    88,
      89,    62,    15,    93,    63,    36,    65,   123,   101,    70,
      21,    22,    23,    26,    27,    97,    98,    18,    19,   212,
     195,   171,   154,   132,   111,    90,   242,   233,   221,   139,
     157,   116,   186,   158,   194,   169,   142,    59,    60,    29,
     230,   216,   148,   126,   149,   150,   176,   151,   239,   240,
     129,   130,   105,   236,   227,   214
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,   128,   102,   170,   217,   159,  -121,    66,   237,   109,
      86,   205,     3,   114,   145,   160,    16,   161,   -78,   134,
     110,   161,   162,   245,   163,   115,   146,    84,   163,   164,
      17,    20,   165,   164,    94,   135,   165,     4,     5,     6,
       7,     8,     9,   120,    24,   136,   137,    47,    48,   121,
      10,    49,    11,   249,    30,    50,    51,    52,   181,    42,
      53,    54,    55,   182,   222,   223,    25,   -71,    56,    48,
      33,   226,    49,   224,    57,    34,    50,    51,    52,    35,
      37,    53,    54,    55,    38,   183,   190,   191,   192,    56,
      73,   183,    40,    74,    75,    57,    42,   220,    76,    77,
      78,    46,    67,    79,   155,    76,    77,    78,    64,    68,
      79,    69,    80,    71,   174,   232,   145,    83,    72,    80,
      85,    91,   127,    95,    96,   104,   106,    99,   100,   187,
     108,   107,   113,   119,   124,   112,   131,   220,   133,   125,
     117,   143,   144,   232,   156,   172,   178,   177,   179,   180,
     152,   185,   197,   188,   189,   153,   196,   201,   193,   198,
     200,   199,   202,   213,   204,   207,   211,   208,   209,   218,
     237,   243,   210,   247,   228,   234,   225,   248,   206,   203,
     229,   235,   244,    41,    45,   241,    39,   175,   231,   246,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118
};

static const yytype_int16 yycheck[] =
{
      30,   105,    73,   143,   199,     8,    21,    37,    12,    18,
      25,    18,     0,    30,    11,    18,    18,    24,    33,     8,
      29,    24,    25,    27,    31,    42,    23,    57,    31,    36,
      25,    18,    39,    36,    64,    24,    39,     3,     4,     5,
       6,     7,     8,    18,    25,    34,    35,     9,    10,    24,
      16,    13,    18,   248,     8,    17,    18,    19,    17,    18,
      22,    23,    24,    22,    28,    29,    18,    33,    30,    10,
      21,   211,    13,    37,    36,    33,    17,    18,    19,    15,
       8,    22,    23,    24,    18,   156,   163,   164,   165,    30,
      25,   162,    31,    28,    29,    36,    18,   201,    17,    18,
      19,    27,    26,    22,   134,    17,    18,    19,    14,    18,
      22,    20,    31,    30,     9,   219,    11,    18,    26,    31,
      27,    18,    41,    27,    24,    36,    25,    32,    30,   159,
      33,    27,    21,    18,    26,    33,    18,   241,    26,    32,
      34,    31,    29,   247,    25,    18,    18,    27,    18,    27,
      41,    35,    31,    30,   162,    41,    32,    31,    41,    30,
      26,    30,    26,    18,    27,    26,    41,    32,    27,    36,
      12,    18,    40,   241,    32,    32,    38,    30,   188,   185,
     216,    41,   237,    23,    27,    41,    19,   150,   218,   240,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,    70,     0,     3,     4,     5,     6,     7,     8,
      16,    18,    45,    68,    69,    75,    18,    25,    90,    91,
      18,    83,    84,    85,    25,    18,    86,    87,    60,   112,
       8,    49,    71,    21,    33,    15,    78,     8,    18,    90,
      31,    84,    18,    46,    47,    86,    27,     9,    10,    13,
      17,    18,    19,    22,    23,    24,    30,    36,    62,   110,
     111,    60,    74,    77,    14,    79,    60,    26,    18,    20,
      82,    30,    26,    25,    28,    29,    17,    18,    19,    22,
      31,    65,    66,    18,    60,    27,    25,    50,    72,    73,
      98,    18,    54,    76,    60,    27,    24,    88,    89,    32,
      30,    81,    47,    65,    36,   125,    25,    27,    33,    18,
      29,    97,    33,    21,    30,    42,   104,    34,    88,    18,
      18,    24,    48,    80,    26,    32,   116,    41,    66,   123,
     124,    18,    96,    26,     8,    24,    34,    35,    52,   102,
      55,    56,   109,    31,    29,    11,    23,    63,   115,   117,
     118,   120,    41,    41,    95,    60,    25,   103,   106,     8,
      18,    24,    25,    31,    36,    39,    57,    58,    59,   108,
      46,    94,    18,    67,     9,   117,   119,    27,    18,    18,
      27,    17,    22,    47,    51,    35,   105,    60,    30,    51,
      55,    55,    55,    41,   107,    93,    32,    31,    30,    30,
      26,    31,    26,    56,    27,    18,    59,    26,    32,    27,
      40,    41,    92,    18,   128,    61,   114,    61,    36,    53,
      66,   101,    28,    29,    37,    38,    46,   127,    32,    62,
     113,    60,    66,   100,    32,    41,   126,    12,    64,   121,
     122,    41,    99,    18,    67,    27,   121,    53,    30,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    45,    45,    45,    45,    45,
      46,    46,    46,    46,    46,    47,    47,    48,    48,    48,
      49,    50,    51,    51,    51,    51,    52,    52,    52,    52,
      53,    53,    54,    55,    56,    57,    57,    58,    58,    58,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    60,
      61,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    63,    64,    65,    66,    66,    66,    66,    66,    67,
      67,    68,    68,    69,    70,    70,    71,    71,    72,    72,
      73,    74,    74,    75,    75,    76,    77,    77,    78,    78,
      79,    79,    80,    81,    81,    82,    82,    83,    83,    84,
      85,    85,    86,    87,    87,    88,    89,    89,    90,    91,
      91,    92,    93,    93,    94,    94,    95,    96,    96,    97,
      97,    98,    98,    99,   100,   100,   101,   101,   102,   102,
     103,   103,   104,   104,   105,   106,   106,   107,   107,   108,
     109,   109,   110,   110,   111,   112,   112,   113,   114,   114,
     115,   116,   116,   117,   118,   118,   119,   119,   120,   121,
     122,   122,   123,   123,   124,   125,   125,   126,   127,   127,
     128,   128
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     5,     2,     2,     2,     2,     3,     5,
       1,     2,     4,     2,     5,     1,     4,     1,     1,     4,
       4,     3,     4,     1,     1,     1,     2,     1,     1,     3,
       1,     2,     3,     2,     2,     3,     1,     0,     3,     3,
       1,     1,     3,     4,     3,     4,     4,     4,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     6,    11,
       1,     4,     4,     2,     1,     1,     1,     1,     3,     4,
       1,     0,     1,     2,     0,     2,     0,     1,     0,     1,
       2,     0,     2,     0,     3,     2,     0,     2,     0,     2,
       0,     2,     1,     0,     2,     1,     1,     4,     1,     1,
       1,     2,     1,     1,     2,     1,     1,     2,     4,     1,
       2,     2,     0,     2,     0,     2,     2,     0,     2,     1,
       2,     0,     3,     2,     0,     2,     0,     2,     0,     1,
       0,     3,     1,     1,     2,     0,     2,     0,     1,     2,
       0,     2,     1,     1,     1,     0,     2,     1,     0,     2,
       1,     0,     2,     1,     1,     2,     0,     3,     2,     1,
       1,     2,     1,     1,     1,     0,     2,     2,     0,     2,
       0,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
        yyerror (&yylloc, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, void *scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_T_1015: /* "?const?"  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_T_1016: /* "?id?"  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_T_1017: /* "?lexem?"  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_T_1018: /* "?number?"  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_T_1019: /* "?re?"  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_T_1020: /* "?ref?"  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_T_1021: /* "?spaces?"  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_T_1022: /* "?terminal?"  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_program: /* program  */
            { if(yydebug_flag==2) ast::astprint(cout,((*yyvaluep).f25_)); else YYINTERPRET(((*yyvaluep).f25_),scanner); ast::destroy(((*yyvaluep).f25_)); }
        break;

    case YYSYMBOL_decl: /* decl  */
            { ast::destroy(((*yyvaluep).f2_)); }
        break;

    case YYSYMBOL_type1: /* type1  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_type2: /* type2  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_symbol: /* symbol  */
            { ast::destroy(((*yyvaluep).f9_)); }
        break;

    case YYSYMBOL_initcode: /* initcode  */
            { ast::destroy(((*yyvaluep).f15_)); }
        break;

    case YYSYMBOL_lrule: /* lrule  */
            { ast::destroy(((*yyvaluep).f15_)); }
        break;

    case YYSYMBOL_term: /* term  */
            { ast::destroy(((*yyvaluep).f13_)); }
        break;

    case YYSYMBOL_lcode: /* lcode  */
            { ast::destroy(((*yyvaluep).f23_)); }
        break;

    case YYSYMBOL_alist: /* alist  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_grule: /* grule  */
            { ast::destroy(((*yyvaluep).f5_)); }
        break;

    case YYSYMBOL_erule: /* erule  */
            { ast::destroy(((*yyvaluep).f4_)); }
        break;

    case YYSYMBOL_xrule: /* xrule  */
            { ast::destroy(((*yyvaluep).f14_)); }
        break;

    case YYSYMBOL_lblelem: /* lblelem  */
            { ast::destroy(((*yyvaluep).f3_)); }
        break;

    case YYSYMBOL_rcode: /* rcode  */
            { ast::destroy(((*yyvaluep).f26_)); }
        break;

    case YYSYMBOL_elem: /* elem  */
            { ast::destroy(((*yyvaluep).f3_)); }
        break;

    case YYSYMBOL_xcode: /* xcode  */
            { ast::destroy(((*yyvaluep).f7_)); }
        break;

    case YYSYMBOL_ncode: /* ncode  */
            { ast::destroy(((*yyvaluep).f7_)); }
        break;

    case YYSYMBOL_xelem: /* xelem  */
            { ast::destroy(((*yyvaluep).f17_)); }
        break;

    case YYSYMBOL_mrule: /* mrule  */
            { ast::destroy(((*yyvaluep).f19_)); }
        break;

    case YYSYMBOL_vrule: /* vrule  */
            { ast::destroy(((*yyvaluep).f21_)); }
        break;

    case YYSYMBOL_list: /* list  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_lelem: /* lelem  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_node: /* node  */
            { ast::destroy(((*yyvaluep).f24_)); }
        break;

    case YYSYMBOL_g_1: /* g_1  */
            { ast::destroy(((*yyvaluep).f2_)); }
        break;

    case YYSYMBOL_g_3: /* g_3  */
            { ast::destroy(((*yyvaluep).f2_)); }
        break;

    case YYSYMBOL_g_2: /* g_2  */
            { ast::destroy(((*yyvaluep).f11_)); }
        break;

    case YYSYMBOL_g_4: /* g_4  */
            { ast::destroy(((*yyvaluep).f15_)); }
        break;

    case YYSYMBOL_g_5: /* g_5  */
            { ast::destroy(((*yyvaluep).f15_)); }
        break;

    case YYSYMBOL_g_7: /* g_7  */
            { ast::destroy(((*yyvaluep).f15_)); }
        break;

    case YYSYMBOL_g_6: /* g_6  */
            { ast::destroy(((*yyvaluep).f22_)); }
        break;

    case YYSYMBOL_g_8: /* g_8  */
            { ast::destroy(((*yyvaluep).f22_)); }
        break;

    case YYSYMBOL_g_10: /* g_10  */
            { ast::destroy(((*yyvaluep).f5_)); }
        break;

    case YYSYMBOL_g_9: /* g_9  */
            { ast::destroy(((*yyvaluep).f6_)); }
        break;

    case YYSYMBOL_g_11: /* g_11  */
            { ast::destroy(((*yyvaluep).f6_)); }
        break;

    case YYSYMBOL_g_12: /* g_12  */
            { ast::destroy(((*yyvaluep).f7_)); }
        break;

    case YYSYMBOL_g_14: /* g_14  */
            { ast::destroy(((*yyvaluep).f9_)); }
        break;

    case YYSYMBOL_g_13: /* g_13  */
            { ast::destroy(((*yyvaluep).f8_)); }
        break;

    case YYSYMBOL_g_15: /* g_15  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_g_16: /* g_16  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_g_18: /* g_18  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_g_17: /* g_17  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_20: /* g_20  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_g_19: /* g_19  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_22: /* g_22  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_g_21: /* g_21  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_24: /* g_24  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_23: /* g_23  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_26: /* g_26  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_g_25: /* g_25  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_27: /* g_27  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_29: /* g_29  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_g_28: /* g_28  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_30: /* g_30  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_31: /* g_31  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_33: /* g_33  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_g_32: /* g_32  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_34: /* g_34  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_35: /* g_35  */
            { ast::destroy(((*yyvaluep).f12_)); }
        break;

    case YYSYMBOL_g_36: /* g_36  */
            { ast::destroy(((*yyvaluep).f13_)); }
        break;

    case YYSYMBOL_g_39: /* g_39  */
            { ast::destroy(((*yyvaluep).f14_)); }
        break;

    case YYSYMBOL_g_38: /* g_38  */
            { ast::destroy(((*yyvaluep).f4_)); }
        break;

    case YYSYMBOL_g_42: /* g_42  */
            { ast::destroy(((*yyvaluep).f3_)); }
        break;

    case YYSYMBOL_g_41: /* g_41  */
            { ast::destroy(((*yyvaluep).f16_)); }
        break;

    case YYSYMBOL_g_43: /* g_43  */
            { ast::destroy(((*yyvaluep).f17_)); }
        break;

    case YYSYMBOL_g_45: /* g_45  */
            { ast::destroy(((*yyvaluep).f17_)); }
        break;

    case YYSYMBOL_g_44: /* g_44  */
            { ast::destroy(((*yyvaluep).f7_)); }
        break;

    case YYSYMBOL_g_47: /* g_47  */
            { ast::destroy(((*yyvaluep).f17_)); }
        break;

    case YYSYMBOL_g_46: /* g_46  */
            { ast::destroy(((*yyvaluep).f7_)); }
        break;

    case YYSYMBOL_g_51: /* g_51  */
            { ast::destroy(((*yyvaluep).f19_)); }
        break;

    case YYSYMBOL_g_50: /* g_50  */
            { ast::destroy(((*yyvaluep).f18_)); }
        break;

    case YYSYMBOL_g_52: /* g_52  */
            { ast::destroy(((*yyvaluep).f19_)); }
        break;

    case YYSYMBOL_g_53: /* g_53  */
            { ast::destroy(((*yyvaluep).f18_)); }
        break;

    case YYSYMBOL_g_55: /* g_55  */
            { ast::destroy(((*yyvaluep).f21_)); }
        break;

    case YYSYMBOL_g_54: /* g_54  */
            { ast::destroy(((*yyvaluep).f20_)); }
        break;

    case YYSYMBOL_g_56: /* g_56  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_58: /* g_58  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_57: /* g_57  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_60: /* g_60  */
            { ast::destroy(((*yyvaluep).f1_)); }
        break;

    case YYSYMBOL_g_59: /* g_59  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

    case YYSYMBOL_g_61: /* g_61  */
            { ast::destroy(((*yyvaluep).f10_)); }
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
    goto yyexhaustedlab;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: g_2 g_8 g_11 g_12  */
                                {
	#line 222 "caio.caio"
                                      (yyval.f25_)=ast::prog((yyvsp[-3].f11_),(yyvsp[-2].f22_),(yyvsp[-1].f6_),(yyvsp[0].f7_),&(yyloc));
 }
    break;

  case 3: /* decl: "%type" '<' type1 '>' g_13  */
                                        {
	#line 224 "caio.caio"
                                             (yyval.f2_)=ast::decltypes((yyvsp[-2].f1_),(yyvsp[0].f8_),&(yyloc));
 ast::destroy((yyvsp[-2].f1_)); }
    break;

  case 4: /* decl: "%option" g_17  */
                                {
	#line 226 "caio.caio"
                                                 for(auto o:(yyvsp[0].f10_)) switch_option(o);  ast::destroy((yyvsp[0].f10_)); }
    break;

  case 5: /* decl: "%using" g_19  */
                        {
	#line 227 "caio.caio"
                                                 for(auto o:(yyvsp[0].f10_)) add_using(o);  ast::destroy((yyvsp[0].f10_)); }
    break;

  case 6: /* decl: "%operator" g_23  */
                                {
	#line 230 "caio.caio"
                                             (yyval.f2_)=ast::decloper((yyvsp[0].f10_),&(yyloc));
 }
    break;

  case 7: /* decl: "?id?" "?re?"  */
                        {
	#line 231 "caio.caio"
                                             (yyval.f2_)=ast::declre((yyvsp[-1].f1_),(yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[-1].f1_)); ast::destroy((yyvsp[0].f1_)); }
    break;

  case 8: /* decl: "%{" xcode '}'  */
                                {
	#line 232 "caio.caio"
                                             (yyval.f2_)=ast::declcode(nullptr,(yyvsp[-1].f7_),&(yyloc));
 }
    break;

  case 9: /* decl: "%code" "?id?" "%{" xcode '}'  */
                                        {
	#line 233 "caio.caio"
                                             (yyval.f2_)=ast::declcode((yyvsp[-3].f1_),(yyvsp[-1].f7_),&(yyloc));
 }
    break;

  case 10: /* type1: type2  */
                {(yyval.f1_)=(yyvsp[0].f1_);
 }
    break;

  case 11: /* type1: type2 '?'  */
                        {
	#line 236 "caio.caio"
                                             (yyval.f1_)=std::string((yyvsp[-1].f1_)+"?"s);
 ast::destroy((yyvsp[-1].f1_)); }
    break;

  case 12: /* type1: type2 '<' type2 '>'  */
                                {
	#line 237 "caio.caio"
                                             (yyval.f1_)=std::string((yyvsp[-3].f1_)+"<"s+(yyvsp[-1].f1_)+">"s);
 ast::destroy((yyvsp[-3].f1_)); ast::destroy((yyvsp[-1].f1_)); }
    break;

  case 13: /* type1: type2 '*'  */
                        {
	#line 238 "caio.caio"
                                             (yyval.f1_)=std::string((yyvsp[-1].f1_)+"*"s);
 ast::destroy((yyvsp[-1].f1_)); }
    break;

  case 14: /* type1: type2 '<' type2 '>' '*'  */
                                        {
	#line 239 "caio.caio"
                                             (yyval.f1_)=std::string((yyvsp[-4].f1_)+"<"s+(yyvsp[-2].f1_)+">*"s);
 ast::destroy((yyvsp[-4].f1_)); ast::destroy((yyvsp[-2].f1_)); }
    break;

  case 15: /* type2: "?id?"  */
                        {
	#line 241 "caio.caio"
                                             (yyval.f1_)=std::string(((yyvsp[0].f1_)=="string"s)?"std::string"s:(yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 16: /* type2: "?id?" ':' ':' "?id?"  */
                                {
	#line 242 "caio.caio"
                                             (yyval.f1_)=std::string((yyvsp[-3].f1_)+"::"s+(yyvsp[0].f1_));
 ast::destroy((yyvsp[-3].f1_)); ast::destroy((yyvsp[0].f1_)); }
    break;

  case 17: /* symbol: "?terminal?"  */
                        {
	#line 244 "caio.caio"
                                             (yyval.f9_)=ast::terminal((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 18: /* symbol: "?id?"  */
                        {
	#line 245 "caio.caio"
                                             (yyval.f9_)=ast::ident((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 19: /* symbol: "?id?" '(' g_27 ')'  */
                                {
	#line 247 "caio.caio"
                                             (yyval.f9_)=ast::node((yyvsp[-3].f1_),(yyvsp[-1].f10_),&(yyloc));
 ast::destroy((yyvsp[-3].f1_)); }
    break;

  case 20: /* initcode: "%{" xcode '}' '\n'  */
                                        {
	#line 249 "caio.caio"
                                             (yyval.f15_)=ast::lexinit((yyvsp[-2].f7_),&(yyloc));
 }
    break;

  case 21: /* lrule: g_31 "?re?" lcode  */
                                {
	#line 255 "caio.caio"
                                             (yyval.f15_)=ast::lexrule((yyvsp[-2].f10_),(yyvsp[-1].f1_),(yyvsp[0].f23_),&(yyloc));
 ast::destroy((yyvsp[-1].f1_)); }
    break;

  case 22: /* term: type2 '(' g_34 ')'  */
                                {
	#line 258 "caio.caio"
                                             (yyval.f13_)=ast::tnode((yyvsp[-3].f1_),(yyvsp[-1].f10_),&(yyloc));
 ast::destroy((yyvsp[-3].f1_)); }
    break;

  case 23: /* term: "?const?"  */
                        {
	#line 259 "caio.caio"
                                             (yyval.f13_)=ast::snode((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 24: /* term: type2  */
                {
	#line 260 "caio.caio"
                                             (yyval.f13_)=ast::snode((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 25: /* term: "?ref?"  */
                        {
	#line 261 "caio.caio"
                                             (yyval.f13_)=ast::snode((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 26: /* lcode: g_35 g_36  */
                        {
	#line 263 "caio.caio"
                                             (yyval.f23_)=ast::lterm((yyvsp[-1].f12_),(yyvsp[0].f13_),&(yyloc));
 }
    break;

  case 27: /* lcode: ';'  */
                {
	#line 264 "caio.caio"
                                             (yyval.f23_)=ast::lskip(&(yyloc));
 }
    break;

  case 28: /* lcode: '|'  */
                {
	#line 265 "caio.caio"
                                             (yyval.f23_)=ast::lnext(&(yyloc));
 }
    break;

  case 29: /* lcode: "%{" xcode '}'  */
                                {
	#line 266 "caio.caio"
                                             (yyval.f23_)=ast::lcode((yyvsp[-1].f7_),&(yyloc));
 }
    break;

  case 30: /* alist: lelem  */
                {
	#line 268 "caio.caio"
                                                 string s; for(auto x:(yyvsp[0].f10_)) s+=x; (yyval.f1_)=s;  }
    break;

  case 31: /* alist: alist lelem  */
                        {
	#line 269 "caio.caio"
                                                 string s; for(auto x:(yyvsp[0].f10_)) s+=x; (yyval.f1_)=(yyvsp[-1].f1_)+s;  }
    break;

  case 32: /* grule: "?id?" g_37 erule  */
                                {
	#line 272 "caio.caio"
                                             (yyval.f5_)=ast::grmrule((yyvsp[-2].f1_),(yyvsp[0].f4_),&(yyloc));
 ast::destroy((yyvsp[-2].f1_)); }
    break;

  case 33: /* erule: xrule g_38  */
                        {
	#line 274 "caio.caio"
                                             (yyval.f4_)=ast::cons((yyvsp[-1].f14_),(yyvsp[0].f4_));
 }
    break;

  case 34: /* xrule: g_41 rcode  */
                        {
	#line 276 "caio.caio"
                                             (yyval.f14_)=ast::xrule((yyvsp[-1].f16_),(yyvsp[0].f26_),&(yyloc));
 }
    break;

  case 35: /* lblelem: "?id?" ':' elem  */
                                {
	#line 278 "caio.caio"
                                                 (yyval.f3_)=replace_altid((yyvsp[0].f3_),(yyvsp[-2].f1_));  }
    break;

  case 36: /* lblelem: elem  */
                {(yyval.f3_)=(yyvsp[0].f3_);
 }
    break;

  case 37: /* rcode: %empty  */
                {
	#line 281 "caio.caio"
                                             (yyval.f26_)=ast::gempty(&(yyloc));
 }
    break;

  case 38: /* rcode: '<' term '>'  */
                        {
	#line 282 "caio.caio"
                                             (yyval.f26_)=ast::gterm((yyvsp[-1].f13_),&(yyloc));
 }
    break;

  case 39: /* rcode: "%{" xcode '}'  */
                                {
	#line 283 "caio.caio"
                                             (yyval.f26_)=ast::gcode((yyvsp[-1].f7_),&(yyloc));
 }
    break;

  case 40: /* elem: "?terminal?"  */
                        {
	#line 285 "caio.caio"
                                             (yyval.f3_)=ast::trmelem((yyvsp[0].f1_),"",&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 41: /* elem: "?id?"  */
                        {
	#line 286 "caio.caio"
                                             (yyval.f3_)=ast::symelem((yyvsp[0].f1_),"",&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 42: /* elem: '(' erule ')'  */
                        {
	#line 287 "caio.caio"
                                             (yyval.f3_)=ast::varelem((yyvsp[-1].f4_),"",&(yyloc));
 }
    break;

  case 43: /* elem: '(' erule ')' '*'  */
                                {
	#line 288 "caio.caio"
                                             (yyval.f3_)=ast::repelem0((yyvsp[-2].f4_),"",&(yyloc));
 }
    break;

  case 44: /* elem: '{' erule '}'  */
                        {
	#line 289 "caio.caio"
                                             (yyval.f3_)=ast::repelem0((yyvsp[-1].f4_),"",&(yyloc));
 }
    break;

  case 45: /* elem: '(' erule ')' '+'  */
                                {
	#line 290 "caio.caio"
                                             (yyval.f3_)=ast::repelem1((yyvsp[-2].f4_),"",&(yyloc));
 }
    break;

  case 46: /* elem: '{' erule '}' '-'  */
                                {
	#line 291 "caio.caio"
                                             (yyval.f3_)=ast::repelem1((yyvsp[-2].f4_),"",&(yyloc));
 }
    break;

  case 47: /* elem: '(' erule ')' '?'  */
                                {
	#line 292 "caio.caio"
                                             (yyval.f3_)=ast::optelem((yyvsp[-2].f4_),"",&(yyloc));
 }
    break;

  case 48: /* elem: '[' erule ']'  */
                        {
	#line 293 "caio.caio"
                                             (yyval.f3_)=ast::optelem((yyvsp[-1].f4_),"",&(yyloc));
 }
    break;

  case 49: /* xcode: g_44  */
                {(yyval.f7_)=(yyvsp[0].f7_);
 }
    break;

  case 50: /* ncode: g_46  */
                {(yyval.f7_)=(yyvsp[0].f7_);
 }
    break;

  case 51: /* xelem: "?lexem?"  */
                        {
	#line 301 "caio.caio"
                                             (yyval.f17_)=ast::lexem((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 52: /* xelem: "?const?"  */
                        {
	#line 302 "caio.caio"
                                             (yyval.f17_)=ast::lexem((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 53: /* xelem: "?id?"  */
                        {
	#line 303 "caio.caio"
                                             (yyval.f17_)=ast::lexem((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 54: /* xelem: ':'  */
                {
	#line 304 "caio.caio"
                                             (yyval.f17_)=ast::lexem(":"s,&(yyloc));
 }
    break;

  case 55: /* xelem: "?ref?"  */
                        {
	#line 305 "caio.caio"
                                             (yyval.f17_)=ast::lexem((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 56: /* xelem: "?spaces?"  */
                        {
	#line 306 "caio.caio"
                                             (yyval.f17_)=ast::lexem((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 57: /* xelem: '{' xcode '}'  */
                        {
	#line 307 "caio.caio"
                                             (yyval.f17_)=ast::pcode((yyvsp[-1].f7_),&(yyloc));
 }
    break;

  case 58: /* xelem: "match" list '{' g_48 g_53 '}'  */
                                                {
	#line 314 "caio.caio"
                                             (yyval.f17_)=ast::mcode((yyvsp[-4].f10_),(yyvsp[-1].f18_),&(yyloc));
 }
    break;

  case 59: /* xelem: "visitor" "?id?" '<' "?id?" ',' "?id?" '>' '{' xcode g_54 '}'  */
                                                                        {
	#line 318 "caio.caio"
                                             (yyval.f17_)=ast::vcode((yyvsp[-9].f1_),(yyvsp[-7].f1_),(yyvsp[-5].f1_),(yyvsp[-2].f7_),(yyvsp[-1].f20_),&(yyloc));
 ast::destroy((yyvsp[-9].f1_)); ast::destroy((yyvsp[-7].f1_)); ast::destroy((yyvsp[-5].f1_)); }
    break;

  case 60: /* xelem: "?terminal?"  */
                        {
	#line 319 "caio.caio"
                                             (yyval.f17_)=ast::token((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 61: /* mrule: "rule" node ':' ncode  */
                                {
	#line 321 "caio.caio"
                                             (yyval.f19_)=ast::mrule((yyvsp[-2].f24_),(yyvsp[0].f7_),&(yyloc));
 }
    break;

  case 62: /* vrule: "visit" node ':' ncode  */
                                        {
	#line 323 "caio.caio"
                                             (yyval.f21_)=ast::vrule((yyvsp[-2].f24_),(yyvsp[0].f7_),&(yyloc));
 }
    break;

  case 63: /* list: lelem g_57  */
                        {
	#line 326 "caio.caio"
                                             (yyval.f10_)=ast::cons((yyvsp[-1].f10_),(yyvsp[0].f10_));
 }
    break;

  case 64: /* lelem: "?lexem?"  */
                        {
	#line 328 "caio.caio"
                                             (yyval.f10_)=ast::cons((yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 65: /* lelem: "?ref?"  */
                        {
	#line 329 "caio.caio"
                                             (yyval.f10_)=ast::cons((yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 66: /* lelem: "?id?"  */
                        {
	#line 330 "caio.caio"
                                             (yyval.f10_)=ast::cons((yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 67: /* lelem: "?const?"  */
                        {
	#line 331 "caio.caio"
                                             (yyval.f10_)=ast::cons((yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 68: /* lelem: '(' list ')'  */
                        {
	#line 332 "caio.caio"
                                             (yyval.f10_)=ast::cons(cons("("s,(yyvsp[-1].f10_)),")"s);
 }
    break;

  case 69: /* node: "?id?" '(' g_61 ')'  */
                                {
	#line 335 "caio.caio"
                                             (yyval.f24_)=ast::node2((yyvsp[-3].f1_),(yyvsp[-1].f10_),&(yyloc));
 ast::destroy((yyvsp[-3].f1_)); }
    break;

  case 70: /* node: "?id?"  */
                        {
	#line 336 "caio.caio"
                                             (yyval.f24_)=ast::node1((yyvsp[0].f1_),&(yyloc));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 72: /* g_1: decl  */
                {(yyval.f2_)=(yyvsp[0].f2_);
 }
    break;

  case 73: /* g_3: g_1 '\n'  */
                        {(yyval.f2_)=(yyvsp[-1].f2_);
 }
    break;

  case 75: /* g_2: g_2 g_3  */
                        {(yyval.f11_)=ast::cons((yyvsp[-1].f11_),(yyvsp[0].f2_));
 }
    break;

  case 77: /* g_4: initcode  */
                        {(yyval.f15_)=(yyvsp[0].f15_);
 }
    break;

  case 79: /* g_5: lrule  */
                {(yyval.f15_)=(yyvsp[0].f15_);
 }
    break;

  case 80: /* g_7: g_5 '\n'  */
                        {(yyval.f15_)=(yyvsp[-1].f15_);
 }
    break;

  case 82: /* g_6: g_6 g_7  */
                        {(yyval.f22_)=ast::cons((yyvsp[-1].f22_),(yyvsp[0].f15_));
 }
    break;

  case 84: /* g_8: "?%%lex?" g_4 g_6  */
                                {
	#line 220 "caio.caio"
                                                (yyval.f22_)=ast::cons((yyvsp[-1].f15_),(yyvsp[0].f22_));
 }
    break;

  case 85: /* g_10: grule ';'  */
                        {(yyval.f5_)=(yyvsp[-1].f5_);
 }
    break;

  case 87: /* g_9: g_9 g_10  */
                        {(yyval.f6_)=ast::cons((yyvsp[-1].f6_),(yyvsp[0].f5_));
 }
    break;

  case 89: /* g_11: "?%%grm?" g_9  */
                        {(yyval.f6_)=(yyvsp[0].f6_);
 }
    break;

  case 91: /* g_12: "?%%code?" xcode  */
                                {(yyval.f7_)=(yyvsp[0].f7_);
 }
    break;

  case 92: /* g_14: symbol  */
                        {(yyval.f9_)=(yyvsp[0].f9_);
 }
    break;

  case 94: /* g_13: g_13 g_14  */
                        {(yyval.f8_)=ast::cons((yyvsp[-1].f8_),(yyvsp[0].f9_));
 }
    break;

  case 95: /* g_15: "?number?"  */
                        {(yyval.f1_)=(yyvsp[0].f1_);
 }
    break;

  case 96: /* g_15: "?id?"  */
                        {(yyval.f1_)=(yyvsp[0].f1_);
 }
    break;

  case 97: /* g_16: "?id?" '(' g_15 ')'  */
                                {
	#line 225 "caio.caio"
                                                    (yyval.f1_)=std::string((yyvsp[-3].f1_)+"="s+(yyvsp[-1].f1_));
 ast::destroy((yyvsp[-3].f1_)); ast::destroy((yyvsp[-1].f1_)); }
    break;

  case 98: /* g_16: "?id?"  */
                        {(yyval.f1_)=(yyvsp[0].f1_);
 }
    break;

  case 99: /* g_18: g_16  */
                {(yyval.f1_)=(yyvsp[0].f1_);
 }
    break;

  case 100: /* g_17: g_18  */
                {(yyval.f10_)=ast::cons((yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 101: /* g_17: g_17 g_18  */
                        {(yyval.f10_)=ast::cons((yyvsp[-1].f10_),(yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 102: /* g_20: "?id?"  */
                        {(yyval.f1_)=(yyvsp[0].f1_);
 }
    break;

  case 103: /* g_19: g_20  */
                {(yyval.f10_)=ast::cons((yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 104: /* g_19: g_19 g_20  */
                        {(yyval.f10_)=ast::cons((yyvsp[-1].f10_),(yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 105: /* g_22: "?terminal?"  */
                        {(yyval.f1_)=(yyvsp[0].f1_);
 }
    break;

  case 106: /* g_21: g_22  */
                {(yyval.f10_)=ast::cons((yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 107: /* g_21: g_21 g_22  */
                        {(yyval.f10_)=ast::cons((yyvsp[-1].f10_),(yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 108: /* g_24: '<' "?id?" '>' g_21  */
                                {
	#line 229 "caio.caio"
                                             (yyval.f10_)=ast::cons((yyvsp[-2].f1_),(yyvsp[0].f10_));
 ast::destroy((yyvsp[-2].f1_)); }
    break;

  case 109: /* g_23: g_24  */
                {(yyval.f10_)=ast::cons((yyvsp[0].f10_));
 }
    break;

  case 110: /* g_23: g_23 g_24  */
                        {(yyval.f10_)=ast::cons((yyvsp[-1].f10_),(yyvsp[0].f10_));
 }
    break;

  case 111: /* g_26: ',' type1  */
                        {(yyval.f1_)=(yyvsp[0].f1_);
 }
    break;

  case 113: /* g_25: g_25 g_26  */
                        {(yyval.f10_)=ast::cons((yyvsp[-1].f10_),(yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 115: /* g_27: type1 g_25  */
                        {
	#line 246 "caio.caio"
                                             (yyval.f10_)=ast::cons((yyvsp[-1].f1_),(yyvsp[0].f10_));
 ast::destroy((yyvsp[-1].f1_)); }
    break;

  case 116: /* g_29: ',' "?id?"  */
                        {(yyval.f1_)=(yyvsp[0].f1_);
 }
    break;

  case 118: /* g_28: g_28 g_29  */
                        {(yyval.f10_)=ast::cons((yyvsp[-1].f10_),(yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 119: /* g_30: '*'  */
                {
	#line 251 "caio.caio"
                                             (yyval.f10_)=ast::cons("*"s);
 }
    break;

  case 120: /* g_30: "?id?" g_28  */
                        {
	#line 252 "caio.caio"
                                             (yyval.f10_)=ast::cons((yyvsp[-1].f1_),(yyvsp[0].f10_));
 ast::destroy((yyvsp[-1].f1_)); }
    break;

  case 122: /* g_31: '<' g_30 '>'  */
                        {(yyval.f10_)=(yyvsp[-1].f10_);
 }
    break;

  case 123: /* g_33: ',' alist  */
                        {(yyval.f1_)=(yyvsp[0].f1_);
 }
    break;

  case 125: /* g_32: g_32 g_33  */
                        {(yyval.f10_)=ast::cons((yyvsp[-1].f10_),(yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 127: /* g_34: alist g_32  */
                        {
	#line 257 "caio.caio"
                                             (yyval.f10_)=ast::cons((yyvsp[-1].f1_),(yyvsp[0].f10_));
 ast::destroy((yyvsp[-1].f1_)); }
    break;

  case 129: /* g_35: "?terminal?"  */
                        {(yyval.f12_)=(yyvsp[0].f1_);
 }
    break;

  case 131: /* g_36: '<' term '>'  */
                        {(yyval.f13_)=(yyvsp[-1].f13_);
 }
    break;

  case 134: /* g_39: '|' xrule  */
                        {(yyval.f14_)=(yyvsp[0].f14_);
 }
    break;

  case 136: /* g_38: g_38 g_39  */
                        {(yyval.f4_)=ast::cons((yyvsp[-1].f4_),(yyvsp[0].f14_));
 }
    break;

  case 139: /* g_42: lblelem g_40  */
                        {(yyval.f3_)=(yyvsp[-1].f3_);
 }
    break;

  case 141: /* g_41: g_41 g_42  */
                        {(yyval.f16_)=ast::cons((yyvsp[-1].f16_),(yyvsp[0].f3_));
 }
    break;

  case 142: /* g_43: xelem  */
                {(yyval.f17_)=(yyvsp[0].f17_);
 }
    break;

  case 143: /* g_43: "default"  */
                        {
	#line 296 "caio.caio"
                                             (yyval.f17_)=ast::lexem("default"s,&(yyloc));
 }
    break;

  case 144: /* g_45: g_43  */
                {(yyval.f17_)=(yyvsp[0].f17_);
 }
    break;

  case 146: /* g_44: g_44 g_45  */
                        {(yyval.f7_)=ast::cons((yyvsp[-1].f7_),(yyvsp[0].f17_));
 }
    break;

  case 147: /* g_47: xelem  */
                {(yyval.f17_)=(yyvsp[0].f17_);
 }
    break;

  case 149: /* g_46: g_46 g_47  */
                        {(yyval.f7_)=ast::cons((yyvsp[-1].f7_),(yyvsp[0].f17_));
 }
    break;

  case 153: /* g_51: mrule  */
                {(yyval.f19_)=(yyvsp[0].f19_);
 }
    break;

  case 154: /* g_50: g_51  */
                {(yyval.f18_)=ast::cons((yyvsp[0].f19_));
 }
    break;

  case 155: /* g_50: g_50 g_51  */
                        {(yyval.f18_)=ast::cons((yyvsp[-1].f18_),(yyvsp[0].f19_));
 }
    break;

  case 157: /* g_52: "default" ':' ncode  */
                                {
	#line 311 "caio.caio"
                                             (yyval.f19_)=ast::mrule(nullptr,(yyvsp[0].f7_),&(yyloc));
 }
    break;

  case 158: /* g_53: g_50 g_52  */
                        {
	#line 312 "caio.caio"
                                             (yyval.f18_)=ast::cons((yyvsp[-1].f18_),(yyvsp[0].f19_));
 }
    break;

  case 159: /* g_55: vrule  */
                {(yyval.f21_)=(yyvsp[0].f21_);
 }
    break;

  case 160: /* g_54: g_55  */
                {(yyval.f20_)=ast::cons((yyvsp[0].f21_));
 }
    break;

  case 161: /* g_54: g_54 g_55  */
                        {(yyval.f20_)=ast::cons((yyvsp[-1].f20_),(yyvsp[0].f21_));
 }
    break;

  case 162: /* g_56: lelem  */
                {(yyval.f10_)=(yyvsp[0].f10_);
 }
    break;

  case 163: /* g_56: ','  */
                {
	#line 325 "caio.caio"
                                             (yyval.f10_)=ast::cons(","s);
 }
    break;

  case 164: /* g_58: g_56  */
                {(yyval.f10_)=(yyvsp[0].f10_);
 }
    break;

  case 166: /* g_57: g_57 g_58  */
                        {(yyval.f10_)=ast::cons((yyvsp[-1].f10_),(yyvsp[0].f10_));
 }
    break;

  case 167: /* g_60: ',' "?id?"  */
                        {(yyval.f1_)=(yyvsp[0].f1_);
 }
    break;

  case 169: /* g_59: g_59 g_60  */
                        {(yyval.f10_)=ast::cons((yyvsp[-1].f10_),(yyvsp[0].f1_));
 ast::destroy((yyvsp[0].f1_)); }
    break;

  case 171: /* g_61: "?id?" g_59  */
                        {
	#line 334 "caio.caio"
                                             (yyval.f10_)=ast::cons((yyvsp[-1].f1_),(yyvsp[0].f10_));
 ast::destroy((yyvsp[-1].f1_)); }
    break;



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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, scanner);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}


