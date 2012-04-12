/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

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

/* Line 268 of yacc.c  */
#line 1 "parser.y"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "tree.c"
#include <stdbool.h>
#include "symbolTable.h"
int globalLevel=0;
extern int yylval;
extern char* yytext;
int numOfErrors=0;

int scopeStack[100];
int scopeStackTop = 0;

int scopeId = 0;
int tableStackTop=0;		// scope label


void push(int num){
	if(scopeStackTop<100){
		scopeStackTop = num;
		scopeStackTop++;
	}
	else{
		printf("Scope stack overflow\n");
	}
}

int pop(){
	if(scopeStackTop){
		scopeStackTop--;
		return scopeStack[tableStackTop];
	}
	else{
		return -1;
	}
}

extern int yylex();

extern int lineNo ; 
int yylval;
extern char* yytext;
SymbolTable symbolTable[1000];		// array of symbol tables for different scopes
int tempNodeScope;
int currentScope;
extern FILE *yyin;


void yyerror(const char *str)
{
        fprintf(stderr,"error: encountered on this token->%s\n",yytext);
}



Symbol* lookUp(char *lexm,int scope){
	Symbol *symbolEntry = symbolTable[scope].head;
	while(symbolEntry!=symbolTable[scope].tail){
		if(strcmp(lexm,symbolEntry->lexeme)==0){
			tempNodeScope = scope;
			return symbolEntry;
		}
		else
			symbolEntry = symbolEntry->next; 
	}
	if(scope == 1 || scope==0){
		printf("Error in lexical scoping");
		tempNodeScope = -1;
		return NULL;
	}
	else
		return lookUp(lexm,symbolTable[scope].parent);
}


Symbol* lookUpInCurrentScope(char *lexm){
	Symbol* symbolEntry = symbolTable[currentScope].head;
	while(symbolEntry!=symbolTable[currentScope].tail){
		if(strcmp(lexm,symbolEntry->lexeme)==0){
			tempNodeScope = scopeId;
			return symbolEntry;
		}
		else 
			symbolEntry = symbolEntry->next; 
	}
	return NULL;
}
Symbol* addEntry(char *lexm){
	Symbol *symbolEntry = symbolTable[currentScope].head;
	if(symbolEntry == NULL){
		Symbol *newNodeEntry = (Symbol*)malloc(sizeof(Symbol));
		newNodeEntry->lexeme = malloc(strlen(lexm)+1);
		newNodeEntry->token = TOKEN_ID;
		symbolTable[currentScope].head = newNodeEntry;
		symbolTable[currentScope].head->next = symbolTable[currentScope].tail;
		symbolTable[currentScope].currentSymbol = symbolTable[currentScope].head;
		return newNodeEntry;
	}
	Symbol *newNodeEntry = (Symbol*)malloc(sizeof(Symbol));
	newNodeEntry->lexeme = malloc(strlen(lexm)+1);
	newNodeEntry->token = TOKEN_ID;
	symbolTable[currentScope].tail = newNodeEntry;
	symbolTable[currentScope].tail = symbolTable[currentScope].tail->next;
	symbolTable[currentScope].currentSymbol->next = newNodeEntry;
	symbolTable[currentScope].currentSymbol = newNodeEntry;
	return newNodeEntry;
}

void displayNode(Node *node){
	printf("PRINTING Node:\n");
	printf("LEXEME: %s",node->identLex);
	if(node->semTypeDef != NULL){
		printf("SEMTYPEDEF: %d",node->semTypeDef);}
	if(node->intValue != NULL){
		printf("INTEGER VALUE: %d",node->intValue);}
	if(!(node->realValue)){
		printf("REAL VALUE: %f",node->realValue);}
	if(node->boolValue){
		printf("BOOLVALUE: TRUE");}
	if(node->type != NULL){
		printf("TYPE: %d",node->type);}
	if(node->track != NULL){
		printf("Track: %d",node->track);}
}
 
int yywrap()
{
        return 1;
}


/* Line 268 of yacc.c  */
#line 206 "y.tab.c"

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
     TOKEN_PRINT = 258,
     TOKEN_IDENTIFIER = 259,
     TOKEN_BEGIN = 260,
     TOKEN_END = 261,
     TOKEN_LOGICAL_VALUE = 262,
     TOKEN_OPERATOR = 263,
     TOKEN_OR = 264,
     TOKEN_PROCEDURE = 265,
     TOKEN_PLUS = 266,
     TOKEN_MINUS = 267,
     TOKEN_DIVIDE = 268,
     TOKEN_POWER = 269,
     TOKEN_MULTIPLY = 270,
     TOKEN_COMMA = 271,
     TOKEN_UNDERSCORE = 272,
     TOKEN_SPECIFIER = 273,
     TOKEN_LIBRARY = 274,
     TOKEN_BRACKET = 275,
     TOKEN_OPEN_BRACKET = 276,
     TOKEN_CLOSE_BRACKET = 277,
     TOKEN_OPEN_SQUARE_BRACKET = 278,
     TOKEN_CLOSE_SQUARE_BRACKET = 279,
     TOKEN_CONTINUE = 280,
     TOKEN_REAL_NUM = 281,
     TOKEN_INTEGER = 282,
     TOKEN_COLON = 283,
     TOKEN_REL_OP = 284,
     TOKEN_LESS_EQUAL = 285,
     TOKEN_GREATER = 286,
     TOKEN_GREATER_EQUAL = 287,
     TOKEN_EQUAL = 288,
     TOKEN_LESS = 289,
     TOKEN_NOTEQUAL = 290,
     TOKEN_EQUIV = 291,
     TOKEN_AND_OP = 292,
     TOKEN_OR_OP = 293,
     TOKEN_NOT_OP = 294,
     TOKEN_GOTO = 295,
     TOKEN_FOR = 296,
     TOKEN_DO = 297,
     TOKEN_WHILE = 298,
     TOKEN_STEP = 299,
     TOKEN_UNTIL = 300,
     TOKEN_IF = 301,
     TOKEN_THEN = 302,
     TOKEN_ELSE = 303,
     TOKEN_SWITCH = 304,
     TOKEN_VALUE = 305,
     TOKEN_BOOLEAN = 306,
     TOKEN_TYPE_OWN = 307,
     TOKEN_TYPE_INTEGER = 308,
     TOKEN_TYPE_REAL = 309,
     TOKEN_TYPE_BOOLEAN = 310,
     TOKEN_TYPE_ARRAY = 311,
     TOKEN_TYPE_SWITCH = 312,
     TOKEN_TYPE_PROCEDURE = 313,
     TOKEN_TYPE_STRING = 314,
     TOKEN_TYPE_LABEL = 315,
     TOKEN_TYPE_VALUE = 316,
     TOKEN_ARRAY = 317,
     TOKEN_IMPLY = 318,
     TOKEN_SEMICOLON = 319,
     TOKEN_LTRSTRING = 320,
     TOKEN_RETURN = 321,
     TOKEN_ASSIGN_IDENTIFIER = 322,
     TOKEN_LABEL_IDENTIFIER = 323,
     TOKEN_BOOL_IDENTIFIER = 324,
     TOKEN_ASSIGN = 325,
     TOKEN_NOT_EQUAL = 326,
     TOKEN_RELOP = 327
   };
#endif
/* Tokens.  */
#define TOKEN_PRINT 258
#define TOKEN_IDENTIFIER 259
#define TOKEN_BEGIN 260
#define TOKEN_END 261
#define TOKEN_LOGICAL_VALUE 262
#define TOKEN_OPERATOR 263
#define TOKEN_OR 264
#define TOKEN_PROCEDURE 265
#define TOKEN_PLUS 266
#define TOKEN_MINUS 267
#define TOKEN_DIVIDE 268
#define TOKEN_POWER 269
#define TOKEN_MULTIPLY 270
#define TOKEN_COMMA 271
#define TOKEN_UNDERSCORE 272
#define TOKEN_SPECIFIER 273
#define TOKEN_LIBRARY 274
#define TOKEN_BRACKET 275
#define TOKEN_OPEN_BRACKET 276
#define TOKEN_CLOSE_BRACKET 277
#define TOKEN_OPEN_SQUARE_BRACKET 278
#define TOKEN_CLOSE_SQUARE_BRACKET 279
#define TOKEN_CONTINUE 280
#define TOKEN_REAL_NUM 281
#define TOKEN_INTEGER 282
#define TOKEN_COLON 283
#define TOKEN_REL_OP 284
#define TOKEN_LESS_EQUAL 285
#define TOKEN_GREATER 286
#define TOKEN_GREATER_EQUAL 287
#define TOKEN_EQUAL 288
#define TOKEN_LESS 289
#define TOKEN_NOTEQUAL 290
#define TOKEN_EQUIV 291
#define TOKEN_AND_OP 292
#define TOKEN_OR_OP 293
#define TOKEN_NOT_OP 294
#define TOKEN_GOTO 295
#define TOKEN_FOR 296
#define TOKEN_DO 297
#define TOKEN_WHILE 298
#define TOKEN_STEP 299
#define TOKEN_UNTIL 300
#define TOKEN_IF 301
#define TOKEN_THEN 302
#define TOKEN_ELSE 303
#define TOKEN_SWITCH 304
#define TOKEN_VALUE 305
#define TOKEN_BOOLEAN 306
#define TOKEN_TYPE_OWN 307
#define TOKEN_TYPE_INTEGER 308
#define TOKEN_TYPE_REAL 309
#define TOKEN_TYPE_BOOLEAN 310
#define TOKEN_TYPE_ARRAY 311
#define TOKEN_TYPE_SWITCH 312
#define TOKEN_TYPE_PROCEDURE 313
#define TOKEN_TYPE_STRING 314
#define TOKEN_TYPE_LABEL 315
#define TOKEN_TYPE_VALUE 316
#define TOKEN_ARRAY 317
#define TOKEN_IMPLY 318
#define TOKEN_SEMICOLON 319
#define TOKEN_LTRSTRING 320
#define TOKEN_RETURN 321
#define TOKEN_ASSIGN_IDENTIFIER 322
#define TOKEN_LABEL_IDENTIFIER 323
#define TOKEN_BOOL_IDENTIFIER 324
#define TOKEN_ASSIGN 325
#define TOKEN_NOT_EQUAL 326
#define TOKEN_RELOP 327




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 392 "y.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   271

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  82
/* YYNRULES -- Number of rules.  */
#define YYNRULES  143
/* YYNRULES -- Number of states.  */
#define YYNSTATES  235

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,    10,    14,    16,    19,    22,    24,
      26,    28,    30,    33,    35,    38,    41,    45,    47,    49,
      51,    53,    55,    59,    61,    65,    67,    72,    76,    78,
      79,    84,    87,    91,    93,    95,    97,   102,   104,   107,
     110,   114,   118,   120,   124,   128,   130,   134,   136,   138,
     142,   144,   146,   148,   150,   155,   157,   161,   163,   165,
     167,   169,   173,   175,   179,   181,   185,   187,   191,   193,
     196,   198,   200,   204,   206,   210,   212,   214,   215,   220,
     222,   224,   226,   229,   231,   233,   235,   237,   239,   244,
     247,   250,   253,   257,   259,   262,   264,   266,   267,   271,
     273,   276,   280,   284,   295,   296,   299,   301,   303,   307,
     309,   313,   315,   317,   322,   324,   326,   328,   331,   333,
     335,   336,   341,   343,   344,   349,   351,   355,   359,   361,
     363,   366,   368,   370,   373,   375,   377,   381,   386,   387,
     388,   396,   398,   402
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      79,     0,    -1,     5,    83,    -1,    74,    64,    83,    -1,
      74,    64,    82,    -1,    75,    -1,    77,    76,    -1,    78,
      28,    -1,   105,    -1,   100,    -1,    81,    -1,    76,    -1,
       5,    82,    -1,    80,    -1,    77,    81,    -1,   139,     6,
      -1,   139,    64,    82,    -1,   119,    -1,    92,    -1,   154,
      -1,    94,    -1,    94,    -1,    84,    28,    85,    -1,    86,
      -1,    87,    16,    86,    -1,   105,    -1,    88,    23,    87,
      24,    -1,    88,    16,    89,    -1,    89,    -1,    -1,    90,
      16,    91,    89,    -1,    62,    90,    -1,   118,    62,    90,
      -1,    94,    -1,   106,    -1,    95,    -1,   124,    95,    48,
      94,    -1,    96,    -1,    11,    96,    -1,    12,    96,    -1,
      95,    11,    96,    -1,    95,    12,    96,    -1,    97,    -1,
      96,    15,    97,    -1,    96,    13,    97,    -1,    98,    -1,
      97,    14,    98,    -1,    99,    -1,   100,    -1,    21,    94,
      22,    -1,    26,    -1,    27,    -1,   105,    -1,   102,    -1,
      88,    23,   103,    24,    -1,   104,    -1,   103,    16,   104,
      -1,    94,    -1,     4,    -1,   107,    -1,   108,    -1,   107,
      36,   108,    -1,   109,    -1,   108,    63,   109,    -1,   110,
      -1,   109,    38,   110,    -1,   111,    -1,   110,    37,   111,
      -1,   112,    -1,    39,   112,    -1,   113,    -1,   114,    -1,
      21,   106,    22,    -1,     7,    -1,    95,   115,    95,    -1,
      29,    -1,   120,    -1,    -1,   116,    16,   117,   120,    -1,
      54,    -1,    53,    -1,    55,    -1,   118,   116,    -1,   105,
      -1,   125,    -1,    81,    -1,    76,    -1,   123,    -1,   124,
     121,    48,   139,    -1,   124,   131,    -1,    77,   122,    -1,
     124,   121,    -1,    46,   106,    47,    -1,   126,    -1,    78,
     125,    -1,   130,    -1,   128,    -1,    -1,   133,   127,   129,
      -1,   132,    -1,    66,    93,    -1,   105,    70,    94,    -1,
     105,    70,   106,    -1,    41,   101,    70,    94,    44,    94,
      45,    94,    42,   139,    -1,    -1,   134,   135,    -1,   105,
      -1,   132,    -1,    21,   136,    22,    -1,   137,    -1,   136,
     138,   137,    -1,    93,    -1,    16,    -1,    24,   105,    28,
      23,    -1,   121,    -1,   122,    -1,   131,    -1,     3,    93,
      -1,   105,    -1,   140,    -1,    -1,   141,   138,   142,   140,
      -1,   132,    -1,    -1,    21,   144,   141,    22,    -1,   105,
      -1,   145,    16,   105,    -1,    50,   145,    64,    -1,   132,
      -1,   118,    -1,   118,    62,    -1,    60,    -1,    49,    -1,
     118,    10,    -1,   132,    -1,   149,    -1,   147,   145,    64,
      -1,   149,   147,   145,    64,    -1,    -1,    -1,   134,   151,
     143,    64,   152,   146,   148,    -1,   139,    -1,    10,   150,
     153,    -1,   118,    10,   150,   153,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   256,   256,   260,   267,   276,   284,   316,   319,   320,
     324,   329,   338,   346,   348,   354,   362,   373,   378,   387,
     394,   411,   428,   447,   459,   480,   492,   505,   509,   526,
     525,   543,   545,   551,   561,   577,   590,   610,   621,   624,
     628,   662,   695,   707,   737,   774,   786,   811,   823,   846,
     860,   871,   882,   897,   913,   940,   956,   975,   986,   995,
    1030,  1041,  1051,  1061,  1079,  1089,  1107,  1117,  1135,  1145,
    1162,  1184,  1194,  1205,  1219,  1323,  1332,  1355,  1354,  1375,
    1384,  1395,  1414,  1422,  1437,  1451,  1462,  1477,  1489,  1509,
    1534,  1538,  1561,  1580,  1595,  1599,  1612,  1627,  1626,  1645,
    1649,  1666,  1690,  1894,  1942,  1950,  1979,  1991,  1992,  2005,
    2019,  2042,  2053,  2054,  2057,  2065,  2074,  2091,  2108,  2123,
    2124,  2124,  2131,  2134,  2134,  2139,  2145,  2149,  2152,  2154,
    2155,  2156,  2157,  2158,  2160,  2161,  2163,  2167,  2170,  2181,
    2170,  2202,  2212,  2229
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_PRINT", "TOKEN_IDENTIFIER",
  "TOKEN_BEGIN", "TOKEN_END", "TOKEN_LOGICAL_VALUE", "TOKEN_OPERATOR",
  "TOKEN_OR", "TOKEN_PROCEDURE", "TOKEN_PLUS", "TOKEN_MINUS",
  "TOKEN_DIVIDE", "TOKEN_POWER", "TOKEN_MULTIPLY", "TOKEN_COMMA",
  "TOKEN_UNDERSCORE", "TOKEN_SPECIFIER", "TOKEN_LIBRARY", "TOKEN_BRACKET",
  "TOKEN_OPEN_BRACKET", "TOKEN_CLOSE_BRACKET", "TOKEN_OPEN_SQUARE_BRACKET",
  "TOKEN_CLOSE_SQUARE_BRACKET", "TOKEN_CONTINUE", "TOKEN_REAL_NUM",
  "TOKEN_INTEGER", "TOKEN_COLON", "TOKEN_REL_OP", "TOKEN_LESS_EQUAL",
  "TOKEN_GREATER", "TOKEN_GREATER_EQUAL", "TOKEN_EQUAL", "TOKEN_LESS",
  "TOKEN_NOTEQUAL", "TOKEN_EQUIV", "TOKEN_AND_OP", "TOKEN_OR_OP",
  "TOKEN_NOT_OP", "TOKEN_GOTO", "TOKEN_FOR", "TOKEN_DO", "TOKEN_WHILE",
  "TOKEN_STEP", "TOKEN_UNTIL", "TOKEN_IF", "TOKEN_THEN", "TOKEN_ELSE",
  "TOKEN_SWITCH", "TOKEN_VALUE", "TOKEN_BOOLEAN", "TOKEN_TYPE_OWN",
  "TOKEN_TYPE_INTEGER", "TOKEN_TYPE_REAL", "TOKEN_TYPE_BOOLEAN",
  "TOKEN_TYPE_ARRAY", "TOKEN_TYPE_SWITCH", "TOKEN_TYPE_PROCEDURE",
  "TOKEN_TYPE_STRING", "TOKEN_TYPE_LABEL", "TOKEN_TYPE_VALUE",
  "TOKEN_ARRAY", "TOKEN_IMPLY", "TOKEN_SEMICOLON", "TOKEN_LTRSTRING",
  "TOKEN_RETURN", "TOKEN_ASSIGN_IDENTIFIER", "TOKEN_LABEL_IDENTIFIER",
  "TOKEN_BOOL_IDENTIFIER", "TOKEN_ASSIGN", "TOKEN_NOT_EQUAL",
  "TOKEN_RELOP", "$accept", "blockHead", "unlabelledBlock", "block",
  "tlabel", "label", "program", "unlabelledCompound", "compoundStatement",
  "compoundTail", "declaration", "lowerBound", "upperBound", "boundPair",
  "boundPairList", "arrayIdentifier", "arraySegment", "arrayList", "@1",
  "arrayDeclaration", "expression", "arithmeticExpression",
  "simpleArithmeticExpression", "term", "factor", "primary", "realNumber",
  "integer", "variable", "subscriptedVariable", "subscriptList",
  "subscriptExpression", "identifier", "booleanExpression",
  "simpleBoolean", "implication", "booleanTerm", "booleanFactor",
  "booleanSecondary", "booleanPrimary", "logicalValue", "relation",
  "relationalOperator", "listType", "@2", "type", "typeDeclaration",
  "varIdentifier", "unconditionalStatement", "conditionalStatement",
  "ifStatement", "ifClause", "basicStatement", "unlabelledBasicStatement",
  "@3", "dummyStatement", "returnStatement", "assignmentStatement",
  "forStatement", "empty", "procedureStatement", "procedureIdentifier",
  "actualParameterPart", "actualParameterList", "actualParameter",
  "parameterDelimiter", "statement", "formalParameter",
  "formalParameterList", "$@4", "formalParameterPart", "$@5",
  "identifierList", "valuePart", "specifier", "specificationPart",
  "specificationIdentifierList", "procedureHeading", "@6", "$@7",
  "procedureBody", "procedureDeclaration", 0
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
     325,   326,   327
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    74,    75,    76,    76,    77,    78,    78,
      79,    79,    80,    81,    81,    82,    82,    83,    83,    83,
      84,    85,    86,    87,    87,    88,    89,    89,    90,    91,
      90,    92,    92,    93,    93,    94,    94,    95,    95,    95,
      95,    95,    96,    96,    96,    97,    97,    98,    98,    98,
      99,   100,   101,   101,   102,   103,   103,   104,   105,   106,
     107,   107,   108,   108,   109,   109,   110,   110,   111,   111,
     112,   112,   112,   113,   114,   115,   116,   117,   116,   118,
     118,   118,   119,   120,   121,   121,   121,   122,   122,   122,
     122,   123,   124,   125,   125,   126,   126,   127,   126,   128,
     129,   130,   130,   131,   132,   133,   134,   135,   135,   136,
     136,   137,   138,   138,   139,   139,   139,   139,   140,   141,
     142,   141,   143,   144,   143,   145,   145,   146,   146,   147,
     147,   147,   147,   147,   148,   148,   149,   149,   151,   152,
     150,   153,   154,   154
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     3,     1,     2,     2,     1,     1,
       1,     1,     2,     1,     2,     2,     3,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     4,     3,     1,     0,
       4,     2,     3,     1,     1,     1,     4,     1,     2,     2,
       3,     3,     1,     3,     3,     1,     3,     1,     1,     3,
       1,     1,     1,     1,     4,     1,     3,     1,     1,     1,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     2,
       1,     1,     3,     1,     3,     1,     1,     0,     4,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     4,     2,
       2,     2,     3,     1,     2,     1,     1,     0,     3,     1,
       2,     3,     3,    10,     0,     2,     1,     1,     3,     1,
       3,     1,     1,     4,     1,     1,     1,     2,     1,     1,
       0,     4,     1,     0,     4,     1,     3,     3,     1,     1,
       2,     1,     1,     2,     1,     1,     3,     4,     0,     0,
       7,     1,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    58,   104,    51,     0,     5,    11,     0,     0,     0,
      13,    10,     9,     8,     0,     0,     0,     0,    80,    79,
      81,     0,    86,     0,   104,    85,    12,     2,    18,     8,
       0,    17,   114,   115,    87,   104,    84,    93,    96,    95,
     116,    99,    97,   104,     0,    19,   104,     6,    14,     7,
       1,    73,     0,     0,     0,    50,     0,   117,    33,    35,
      37,    42,    45,    47,    48,    34,    59,    60,    62,    64,
      66,    68,    70,    71,     0,   106,   138,   104,     0,     0,
      53,    25,     0,     0,     0,    28,    31,    25,    90,   104,
      94,     0,     0,     0,    83,    82,    76,    91,    89,     0,
       0,   107,   105,    15,   104,     4,     3,     0,    38,    39,
       0,     0,    69,     0,     0,    75,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   104,   141,   142,     0,     0,
      92,     0,     0,    29,   101,   102,   104,    32,    77,   104,
       0,    98,   111,     0,   109,    16,    35,    49,    72,    40,
      41,    74,    44,    43,    46,    61,    63,    65,    67,     0,
     123,   122,     0,    57,     0,    55,     0,    27,     0,    23,
       0,    20,     0,   143,     0,    88,   100,   112,   108,     0,
       0,    36,     0,   139,     0,    54,     0,     0,     0,    26,
      30,    78,     0,   110,   118,   119,     0,   104,    56,     0,
      22,    21,    24,     0,   124,   120,     0,   128,   104,     0,
     113,     0,   125,     0,   132,   131,   129,   134,     0,   140,
     135,     0,   121,     0,   127,   133,   130,     0,     0,   104,
     126,   136,     0,   103,   137
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    22,    23,    24,     9,    10,    25,    26,
      27,   168,   200,   169,   170,    84,    85,    86,   172,    28,
     142,    58,   146,    60,    61,    62,    63,    64,    79,    80,
     164,   165,    29,    65,    66,    67,    68,    69,    70,    71,
      72,    73,   116,    95,   174,    30,    31,    96,    32,    33,
      34,    74,    36,    37,    99,    38,   141,    39,    40,    41,
      42,    43,   102,   143,   144,   180,    44,   195,   196,   211,
     162,   182,   213,   208,   218,   219,   220,    77,   125,   197,
     127,    45
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -170
static const yytype_int16 yypact[] =
{
     123,  -170,   144,  -170,   -48,  -170,  -170,   123,    -6,    67,
    -170,  -170,  -170,  -170,   148,    32,    32,   207,  -170,  -170,
    -170,    32,  -170,    45,   116,  -170,  -170,  -170,  -170,    -4,
      22,  -170,  -170,  -170,  -170,    89,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,    20,     7,  -170,   144,  -170,  -170,  -170,
    -170,  -170,   182,   182,   148,  -170,   230,  -170,  -170,    36,
      41,    55,  -170,  -170,  -170,  -170,    46,    10,    62,    81,
    -170,  -170,  -170,  -170,   227,  -170,  -170,   110,   109,    64,
    -170,    70,    36,    99,    96,  -170,   142,  -170,  -170,   125,
    -170,   148,    32,    32,  -170,   146,  -170,   131,  -170,    98,
     148,  -170,  -170,  -170,   110,  -170,  -170,   190,    41,    41,
     151,   160,  -170,   182,   182,  -170,   227,   182,   182,   182,
     207,   207,   207,   207,    47,   163,  -170,  -170,   190,   190,
    -170,    32,   190,  -170,  -170,  -170,   110,   142,  -170,   110,
     148,  -170,  -170,   228,  -170,  -170,    87,  -170,  -170,    41,
      41,    87,    55,    55,  -170,    10,    62,    81,  -170,   190,
    -170,  -170,   132,  -170,    37,  -170,   145,  -170,   167,  -170,
     156,  -170,    32,  -170,    32,  -170,  -170,  -170,  -170,    32,
     148,  -170,    32,  -170,   190,  -170,   190,   190,   190,  -170,
    -170,  -170,   172,  -170,  -170,  -170,   239,   154,  -170,   162,
    -170,  -170,  -170,   189,  -170,  -170,    32,  -170,   171,   190,
    -170,    32,  -170,    12,  -170,  -170,     2,  -170,    32,  -170,
     171,   179,  -170,    32,  -170,  -170,  -170,    15,    32,   110,
    -170,  -170,    26,  -170,  -170
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -170,  -170,  -170,   102,   126,    14,  -170,  -170,   170,   -16,
     159,  -170,  -170,    25,  -170,   214,   -91,   130,  -170,  -170,
      -9,   -21,     1,    -8,    74,   121,  -170,     0,  -170,  -170,
    -170,    59,     4,   -11,  -170,   127,   124,   136,   137,   193,
    -170,  -170,  -170,  -170,  -170,  -169,  -170,    85,   229,   242,
    -170,     6,   -15,  -170,  -170,  -170,  -170,  -170,   231,   -40,
    -170,    -5,  -170,  -170,    82,    71,   -76,    57,  -170,  -170,
    -170,  -170,  -150,  -170,    49,  -170,  -170,   178,  -170,  -170,
     135,  -170
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -107
static const yytype_int16 yytable[] =
{
      12,   126,    12,   101,    13,    57,    83,    12,    35,    90,
      76,    13,   225,   103,     8,    59,    46,  -106,    82,    75,
      81,     8,    49,    12,    12,    87,     1,    13,   223,    35,
     105,   223,    92,   110,    94,    12,     1,     8,    89,   216,
     167,   100,   223,   111,   108,   109,    12,   113,   114,     1,
       2,   216,    35,   184,   117,    59,   118,    82,   113,   114,
     126,   185,  -106,   175,   226,   115,    91,    50,   227,   119,
     134,   104,     3,   121,    90,   124,   224,    12,   232,   231,
     135,   190,   120,    35,    93,   161,   110,    76,   145,    12,
     234,    17,    59,     1,     2,   159,    75,    87,   113,   114,
     122,    59,     6,    89,    12,   149,   150,   163,   166,    47,
      35,   171,   131,    14,     1,     2,     3,   151,   123,   132,
       1,    82,    82,    82,    82,    47,     7,     1,     2,     1,
      16,   176,   128,     7,   129,    87,    12,     3,   181,    12,
     -52,    59,    35,     3,    49,    35,   130,    14,     1,     2,
       3,    16,     3,   233,    15,    51,    17,   207,   133,    52,
      53,     7,   138,   163,   140,   199,   201,   171,   217,    54,
      11,     3,   188,   147,    55,     3,    87,    48,    94,   139,
     189,    59,   148,   192,   160,    16,   194,    56,   221,   186,
      17,   152,   153,    48,    17,   187,   183,    18,    19,    20,
     203,    52,    53,   107,   206,   106,    21,   209,    55,     3,
     212,   107,   210,   202,    51,   194,    55,     3,    52,    53,
     214,   229,   212,   137,    18,    19,    20,   230,    54,    12,
      78,   215,   212,    55,     3,    35,    17,    51,    52,    53,
     154,    52,    53,   198,   177,   156,    56,   155,   107,   112,
     178,    54,   179,    55,     3,   177,    55,     3,   157,   191,
     158,   204,   193,   179,    97,    88,    98,   205,   222,   228,
     136,   173
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-170))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
       0,    77,     2,    43,     0,    14,    17,     7,     2,    24,
      15,     7,    10,     6,     0,    14,    64,    21,    17,    15,
      16,     7,    28,    23,    24,    21,     4,    23,    16,    23,
      46,    16,    10,    54,    30,    35,     4,    23,    24,   208,
     131,    21,    16,    54,    52,    53,    46,    11,    12,     4,
       5,   220,    46,    16,    13,    54,    15,    56,    11,    12,
     136,    24,    66,   139,    62,    29,    70,     0,   218,    14,
      91,    64,    27,    63,    89,    74,    64,    77,   228,    64,
      91,   172,    36,    77,    62,   125,   107,    92,   104,    89,
      64,    46,    91,     4,     5,    48,    92,    93,    11,    12,
      38,   100,     0,    89,   104,   113,   114,   128,   129,     7,
     104,   132,    16,     3,     4,     5,    27,   116,    37,    23,
       4,   120,   121,   122,   123,    23,     0,     4,     5,     4,
      41,   140,    23,     7,    70,   131,   136,    27,   159,   139,
      70,   140,   136,    27,    28,   139,    47,     3,     4,     5,
      27,    41,    27,   229,    10,     7,    46,   197,    16,    11,
      12,    35,    16,   184,    66,   186,   187,   188,   208,    21,
       0,    27,    16,    22,    26,    27,   172,     7,   174,    48,
      24,   180,    22,   179,    21,    41,   182,    39,   209,    44,
      46,   117,   118,    23,    46,    28,    64,    53,    54,    55,
      28,    11,    12,    21,    50,    46,    62,    45,    26,    27,
     206,    21,    23,   188,     7,   211,    26,    27,    11,    12,
      49,    42,   218,    93,    53,    54,    55,   223,    21,   229,
      16,    60,   228,    26,    27,   229,    46,     7,    11,    12,
     119,    11,    12,   184,    16,   121,    39,   120,    21,    56,
      22,    21,    24,    26,    27,    16,    26,    27,   122,   174,
     123,    22,   180,    24,    35,    23,    35,   196,   211,   220,
      92,   136
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    27,    74,    75,    76,    77,    78,    79,
      80,    81,   100,   105,     3,    10,    41,    46,    53,    54,
      55,    62,    76,    77,    78,    81,    82,    83,    92,   105,
     118,   119,   121,   122,   123,   124,   125,   126,   128,   130,
     131,   132,   133,   134,   139,   154,    64,    76,    81,    28,
       0,     7,    11,    12,    21,    26,    39,    93,    94,    95,
      96,    97,    98,    99,   100,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   124,   105,   134,   150,    88,   101,
     102,   105,    95,   106,    88,    89,    90,   105,   122,    78,
     125,    70,    10,    62,   105,   116,   120,   121,   131,   127,
      21,   132,   135,     6,    64,    82,    83,    21,    96,    96,
      94,   106,   112,    11,    12,    29,   115,    13,    15,    14,
      36,    63,    38,    37,    95,   151,   139,   153,    23,    70,
      47,    16,    23,    16,    94,   106,   150,    90,    16,    48,
      66,   129,    93,   136,   137,    82,    95,    22,    22,    96,
      96,    95,    97,    97,    98,   108,   109,   110,   111,    48,
      21,   132,   143,    94,   103,   104,    94,    89,    84,    86,
      87,    94,    91,   153,   117,   139,    93,    16,    22,    24,
     138,    94,   144,    64,    16,    24,    44,    28,    16,    24,
      89,   120,   105,   137,   105,   140,   141,   152,   104,    94,
      85,    94,    86,    28,    22,   138,    50,   132,   146,    45,
      23,   142,   105,   145,    49,    60,   118,   132,   147,   148,
     149,    94,   140,    16,    64,    10,    62,   145,   147,    42,
     105,    64,   145,   139,    64
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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


/*----------.
| yyparse.  |
`----------*/

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
  if (yypact_value_is_default (yyn))
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
        case 2:

/* Line 1806 of yacc.c  */
#line 257 "parser.y"
    {
		printf("blockHead\n");
	}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 261 "parser.y"
    {
		printf("blockHead\n");
	}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 268 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode =(Node*) (yyvsp[(3) - (3)]);
		newNode->pt0 = (Node*) (yyvsp[(3) - (3)]);
		(yyval) = newNode;
	}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 277 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (1)]);
		(yyval) = newNode;
		printf("unlabelled block\n");
	}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 293 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(2) - (2)]);						// $2
		(yyval) = newNode;
		printf("labelled block\n");
	}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 325 "parser.y"
    {
		printf("compoundStatement\n");
	}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 330 "parser.y"
    {
		printf("block\n");
	}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 338 "parser.y"
    {
		printf("unlabelled compound\n");
	}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 348 "parser.y"
    {
		printf("labelled compoundstatement\n");
	}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 355 "parser.y"
    {
		printf("compound tail\n");
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (2)]);
		(yyval) = newNode;
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 363 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (3)]);
		(yyval) = newNode;
	}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 374 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 379 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 388 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 395 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = lowerBound;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		if(tempNode->semTypeDef==storeInteger){
			newNode->semTypeDef = storeInteger;
			newNode->intValue = tempNode->intValue;
		}
		else{
		
		}
		(yyval)=newNode;
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 412 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = upperBound;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		if(tempNode->semTypeDef==storeInteger){
			newNode->semTypeDef = storeInteger;
			newNode->intValue = tempNode->intValue;
		}
		else{
	
		}
		(yyval)=newNode;
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 429 "parser.y"
    {
		Node* newNode = createNode();         	  
    		newNode->type = boundPair;
    		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNodeOne = (yyvsp[(1) - (3)]);
		Node* tempNodeTwo = (yyvsp[(3) - (3)]);
	
		if (tempNodeOne->semTypeDef==storeInteger && tempNodeTwo->semTypeDef==storeInteger ){
			newNode->semTypeDef=storeBoundPairList;			
		}
		else {
			
		}
		(yyval) = newNode;
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 448 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boundPairList;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		if (tempNode->semTypeDef==storeBoundPairList) {  
			newNode->semTypeDef=tempNode->semTypeDef;
		}
		(yyval) = newNode;
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 460 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boundPairList;
        	newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNodeOne = (yyvsp[(1) - (3)]);
		Node* tempNodeTwo = (yyvsp[(3) - (3)]);
	
		if (tempNodeOne->semTypeDef==storeBoundPairList && tempNodeTwo->semTypeDef==storeBoundPairList ){
			newNode->semTypeDef=storeBoundPairList;			
		}
		else {
			
		}
		
		newNode->track = tempNodeOne->track + 1 ;  	
		(yyval) = newNode;
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 481 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = arrayIdentifier;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex, tempNode->identLex);
		(yyval) = newNode;
	}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 493 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boundPair;
		newNode->pt0 = (yyvsp[(1) - (4)]);
		newNode->pt2 = (yyvsp[(3) - (4)]);

		Node *tempNodeOne = (yyvsp[(1) - (4)]);
		Node *tempNodeTwo = (yyvsp[(3) - (4)]);
		newNode->track = tempNodeTwo->track;
		newNode->identLex = tempNodeOne->identLex;
		(yyval) = newNode;
	}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 510 "parser.y"
    {
		Node* tempNode0=(yyvsp[(0) - (1)]);
		Node* tempNode1=(yyvsp[(1) - (1)]);
		Symbol* symbolEntry=lookUpInCurrentScope(tempNode1->identLex);
		if (symbolEntry!=NULL){
			return 0;
		}
		else{
			symbolEntry = addEntry(tempNode1->identLex);
			symbolTable[currentScope].currentSymbol->type=tempNode1->semTypeDef;
			symbolTable[currentScope].currentSymbol->track=tempNode1->track;
			(yyval)=(yyvsp[(0) - (1)]);
		}
	}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 526 "parser.y"
    {
		Node* tempNode0=(yyvsp[(0) - (2)]);
		Node* tempNode1=(yyvsp[(1) - (2)]);
		Symbol* symbolEntry=lookUpInCurrentScope(tempNode1->identLex);
		if (symbolEntry!=NULL){
			return 0;
		}
		else{
			symbolEntry = addEntry(tempNode1->identLex);
			symbolTable[currentScope].currentSymbol->type=tempNode1->semTypeDef;
			symbolTable[currentScope].currentSymbol->track=tempNode1->track;
			(yyval)=(yyvsp[(0) - (2)]);
		}
	}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 552 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = expression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 562 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = expression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 578 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = arithmeticExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		//remember to check type
		newNode->realValue = tempNode->realValue;
		newNode->intValue = tempNode->intValue;
		newNode->semTypeDef = tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 591 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = arithmeticExpression;
		newNode->pt0 = (yyvsp[(1) - (4)]);
		newNode->pt1 = (yyvsp[(2) - (4)]);
		newNode->pt3 = (yyvsp[(4) - (4)]);
		Node* tempNode2 = (Node*)(yyvsp[(2) - (4)]);
		Node* tempNode4 = (Node*)(yyvsp[(4) - (4)]);
		if(tempNode2->semTypeDef == storeInteger )
		{
			if(tempNode4->semTypeDef == storeInteger)
			{
				newNode->semTypeDef=storeInteger ;  		
			}
		}
		(yyval) = newNode;
	}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 611 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = simpleArithmeticExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef ; 
		(yyval) = newNode;
	}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 622 "parser.y"
    {
	}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 625 "parser.y"
    {
	}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 629 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt1 = (yyvsp[(2) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode0 = (Node*)(yyvsp[(1) - (3)]);
		Node* tempNode1 = (Node*)(yyvsp[(2) - (3)]);
		Node* tempNode2 = (Node*)(yyvsp[(3) - (3)]);

		  
			if (tempNode0->semTypeDef  | tempNode2->semTypeDef) {  
				newNode->semTypeDef = storeReal ;  
				if (tempNode0->semTypeDef==storeInteger) {  
					tempNode0->realValue = 1.00*tempNode0->intValue;  
					tempNode0->semTypeDef==storeReal;
				}
				else if (tempNode2->semTypeDef==storeInteger) {  
					tempNode2->realValue = 1.00*tempNode2->intValue;  
					tempNode2->semTypeDef==storeReal;
				}

				newNode->realValue=tempNode0->realValue  +  tempNode2->realValue;
			}
			else {  
				newNode->semTypeDef = storeInteger ;  
				newNode->intValue = tempNode0->intValue  +  tempNode2->intValue ;  

			}
	
			(yyval) = newNode;
		}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 663 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt1 = (yyvsp[(2) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode0 = (Node*)(yyvsp[(1) - (3)]);
		Node* tempNode1 = (Node*)(yyvsp[(2) - (3)]);
		Node* tempNode2 = (Node*)(yyvsp[(3) - (3)]);
		  
			if (tempNode0->semTypeDef  | tempNode2->semTypeDef) {  
				newNode->semTypeDef = storeReal ;  
				if (tempNode0->semTypeDef==storeInteger) {  
					tempNode0->realValue = 1.00*tempNode0->intValue;  
					tempNode0->semTypeDef==storeReal;
				}
				else if (tempNode2->semTypeDef==storeInteger) {  
					tempNode2->realValue = 1.00*tempNode2->intValue ;  
					tempNode2->semTypeDef==storeReal;
				}
				newNode->realValue=tempNode0->realValue  -  tempNode2->realValue ;  
			}
			else {  
				newNode->semTypeDef = storeInteger ;  
				newNode->intValue = tempNode0->intValue  -  tempNode2->intValue ; 
			}
			(yyval) = newNode;
		//}
	}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 696 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 708 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt1 = (yyvsp[(2) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode0 = (Node*)(yyvsp[(1) - (3)]);
		Node* tempNode1 = (Node*)(yyvsp[(2) - (3)]);
		Node* tempNode2 = (Node*)(yyvsp[(3) - (3)]);
		
			if (tempNode0->semTypeDef  | tempNode2->semTypeDef) {  
				newNode->semTypeDef = storeReal ;  
				if (tempNode0->semTypeDef==storeInteger) {     
					tempNode0->realValue = 1.00*tempNode0->intValue ;  
					tempNode0->semTypeDef==storeReal;
				}
				else if (tempNode2->semTypeDef==storeInteger) {  
					tempNode2->realValue = 1.00*tempNode2->intValue ;  
					tempNode2->semTypeDef==storeReal;					}

					newNode->realValue=tempNode0->realValue  *  tempNode2->realValue;
				}
				else {  
					newNode->semTypeDef = storeInteger ;  
					newNode->intValue = tempNode0->intValue*tempNode2->intValue ;
				}  
				(yyval) = newNode;
		}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 738 "parser.y"
    {
		
			Node *newNode = createNode();			//check declaration here...
			Node* tempNode0 = (Node*)(yyvsp[(1) - (3)]);
			Node* tempNode1 = (Node*)(yyvsp[(2) - (3)]);
			Node* tempNode2 = (Node*)(yyvsp[(3) - (3)]);
			if (tempNode0->semTypeDef  | tempNode2->semTypeDef) {  
				newNode->semTypeDef = storeReal ;  
				if (tempNode0->semTypeDef==storeInteger){
					tempNode0->realValue = 1.00*tempNode0->intValue ;  
					tempNode0->semTypeDef==storeReal;
				}
				else if (tempNode2->semTypeDef==storeInteger) {
					tempNode2->realValue = 1.00*tempNode2->intValue;
					tempNode2->semTypeDef==storeReal;
				}

				if (tempNode2->realValue==0.00){
					exit(0);
				}
				else newNode->realValue=tempNode0->realValue/tempNode2->realValue;
			}
			else {  
				newNode->semTypeDef = storeInteger;
				if (tempNode2->intValue==0){
							exit(0);
				}
				else newNode->intValue = tempNode0->intValue/tempNode2->intValue;
			}
			(yyval) = newNode;
		//}
		
	}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 775 "parser.y"
    {
		Node* newNode = createNode();
		
		newNode->type = factor;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->semTypeDef=tempNode->semTypeDef ;  
		(yyval) = newNode;
	}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 787 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = factor;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode0 = (Node*)(yyvsp[(1) - (3)]);
		Node* tempNode1 = (Node*)(yyvsp[(3) - (3)]);
		
		(yyval) = newNode;
		
	}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 812 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=storeReal;
		(yyval) = newNode;
	}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 824 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=storeInteger;
		(yyval) = newNode;
	}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 847 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = primary;
		newNode->pt1 = (yyvsp[(2) - (3)]);
		Node *tempNode = (Node*)(yyvsp[(2) - (3)]);  
		newNode->intValue = tempNode->intValue;
		newNode->realValue=tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 861 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = realNumber;
		newNode->realValue = atof(yytext);
		newNode->semTypeDef=storeReal;
		(yyval) = newNode;
	}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 872 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = integer;
		newNode->intValue = atoi(yytext);
		newNode->semTypeDef=storeInteger;  
		(yyval) = newNode;
	}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 883 "parser.y"
    {
		Node* newNode = createNode();
		
		newNode->type = variable;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->boolValue = tempNode->boolValue;
		newNode->intValue = tempNode->intValue;
		newNode->realValue=tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		strcpy(newNode->identLex,tempNode->identLex);
		(yyval) = newNode;
	}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 898 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = variable;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->boolValue = tempNode->boolValue;
		newNode->intValue = tempNode->intValue;
		newNode->realValue=tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		strcpy(newNode->identLex, tempNode->identLex);
		(yyval) = newNode;
	}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 914 "parser.y"
    {
		Node* newNode = createNode();
		               	  
		newNode->type = subscriptedVariable;
		newNode->pt0 = (yyvsp[(1) - (4)]);
		newNode->pt2 = (yyvsp[(3) - (4)]);
		Node* tempNode0 = (yyvsp[(1) - (4)]);
		Node* tempNode1 = (yyvsp[(3) - (4)]);
		strcpy(newNode->identLex, tempNode0->identLex);
		Symbol* foundEntry = lookUp(tempNode0->identLex,currentScope);
		if(tempNode0 == -1)
		{
			newNode->semTypeDef = storeError;
		}
		else
		{
		
				newNode->semTypeDef = foundEntry->type;
		
		
		}	
		(yyval) = newNode;
	}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 941 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = subscriptList;
	
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->pt0 = (yyvsp[(1) - (1)]);
		if(tempNode->semTypeDef==storeInteger){
			newNode->semTypeDef = tempNode->semTypeDef;
		}
		else {
			newNode->semTypeDef = storeError;
		}
		(yyval) = newNode;
	}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 957 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = subscriptList;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt1 = (yyvsp[(3) - (3)]);
		Node* tempNode1 = (yyvsp[(1) - (3)]);
		Node* tempNode2 = (yyvsp[(3) - (3)]);
	
		if(tempNode2->semTypeDef == storeInteger){
			newNode->semTypeDef = tempNode2->semTypeDef;
		}
		else {
			newNode->semTypeDef = storeError;
		}
		(yyval) = newNode;
	}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 976 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = subscriptExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		(yyval) = newNode;
	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 987 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = identifier;
		strcpy(newNode->identLex,yytext);
		(yyval) = newNode;
	}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 996 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		if(tempNode->semTypeDef == storeBoolean){
			newNode->semTypeDef = tempNode->semTypeDef;
		}
		else{
			newNode->semTypeDef = storeError;
		}
		(yyval) = newNode;
	}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 1031 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->boolValue = tempNode->boolValue;
		newNode->semTypeDef = tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 1042 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		(yyval) = newNode;
	}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 1052 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = implication;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;  
	}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 1062 "parser.y"
    {
		Node *newNode = createNode();         		
		newNode->type = implication;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode1 = (yyvsp[(1) - (3)]);
		Node* tempNode2 = (yyvsp[(3) - (3)]);
		if (tempNode1->semTypeDef==storeBoolean && tempNode2->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean ;  
		}
		else {  
			newNode->semTypeDef=storeError;
		}
		(yyval) = newNode; 
	}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 1080 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanTerm;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 1090 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode1 = (Node*)(yyvsp[(1) - (3)]);
		Node* tempNode2 = (Node*)(yyvsp[(3) - (3)]);
		if (tempNode1->semTypeDef==storeBoolean && tempNode2->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean;
		}
		else {
			newNode->semTypeDef=storeError ;  
		}
		(yyval) = newNode;  
	}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 1108 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 1118 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode1 = (Node*)(yyvsp[(1) - (3)]);
		Node* tempNode2 = (Node*)(yyvsp[(3) - (3)]);
		if (tempNode1->semTypeDef==storeBoolean && tempNode2->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean ;  
		}
		else {  
			newNode->semTypeDef=storeError ;  
		}
		(yyval) = newNode;  
	}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 1136 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanSecondary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 1146 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanSecondary;
		newNode->pt1 = (yyvsp[(2) - (2)]);
		Node* tempNode = (yyvsp[(2) - (2)]);
		if (tempNode->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean ;  
		}
		else {  
			newNode->semTypeDef=storeError ;  
		}
		(yyval) = newNode;
	}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 1163 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 1185 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval)=newNode;
	}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 1195 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		Node* tempNode = (yyvsp[(1) - (3)]);  
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval)=newNode;
	}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 1206 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = logicalValue;
		if (strcmp("true",yytext)==0){
			newNode->boolValue = true;
		}
		else{
			newNode->boolValue = false;
		}
		(yyval) = newNode;
	}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 1220 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = relation;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt1 = (yyvsp[(2) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode0 = (yyvsp[(1) - (3)]);
		Node* tempNode1 = (yyvsp[(2) - (3)]);
		Node* tempNode2 = (yyvsp[(3) - (3)]);
		if(strcmp(tempNode1->identLex,">") == 0) 
		{
			if(tempNode0->intValue > tempNode2->intValue)
			{
				newNode->boolValue = true;
			}
			else
			{
				newNode->boolValue = false;
			}
		}
		else if(strcmp(tempNode1->identLex,"<") == 0) 
		{	if(tempNode0->intValue < tempNode2->intValue)
			{
				newNode->boolValue = true;
			}
			else
			{
				newNode->boolValue = false;
			}
		}

		else if(strcmp(tempNode1->identLex,"<=") == 0) 
		{
			if(tempNode0->intValue <= tempNode2->intValue)
			{
				newNode->boolValue = true;
			}
			else
			{
				newNode->boolValue = false;
			}
		}
		else if(strcmp(tempNode1->identLex,">=") == 0) 
		{
			if(tempNode0->intValue >= tempNode2->intValue)
			{
				newNode->boolValue = true;
			}
			else
			{
				newNode->boolValue = false;
			}
		}
		else if(strcmp(tempNode1->identLex,"<>") == 0) 
		{
			if(tempNode0->intValue != tempNode2->intValue)
			{
				newNode->boolValue = true;
			}
			else
			{
				newNode->boolValue = false;
			}
		}
		else if(strcmp(tempNode1->identLex,"=") == 0)          	
        	{
        		if(tempNode0->intValue == tempNode2->intValue)
        		{
        			newNode->boolValue = true;
 			}
 			else
			{
				newNode->boolValue = false;
			}
		     
		}
		newNode->semTypeDef = storeBoolean ;  
		(yyval)=newNode;
	}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 1324 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->type = relationalOperator;
		strcpy(newNode->identLex, yytext);
		(yyval) = newNode;
	}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 1333 "parser.y"
    {

		Node *temp2=(yyvsp[(0) - (1)]);

		Node *temp1=(yyvsp[(1) - (1)]);

		if (lookUpInCurrentScope(temp1->identLex)!=NULL){

			return 0;
		}
		else{
			Symbol *newEntry=addEntry(temp1->identLex);
			
			newEntry->type=temp2->semTypeDef;
			(yyval)=(yyvsp[(0) - (1)]);			


		}

	}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1355 "parser.y"
    {
		Node *temp2=(yyvsp[(0) - (2)]);
		Node *temp1=(yyvsp[(1) - (2)]);
		if (lookUpInCurrentScope(temp1->identLex)!=NULL){
		}
		else{
			Symbol *newEntry=addEntry(temp1->identLex);
			
			newEntry->type=temp2->semTypeDef;			
		}
		(yyval)=(yyvsp[(0) - (2)]);

		
	}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1376 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef = storeReal;
		(yyval) = new;

	}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1385 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeInteger;
		(yyval) = new;

		

	}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1396 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeBoolean;
		(yyval) = new;



	}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1415 "parser.y"
    {
	

	}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1423 "parser.y"
    {
		Node *new = createNode();		new->type = varIdentifier;
		new->pt0 = (yyvsp[(1) - (1)]);
		Node* temp = (Node*)(yyvsp[(1) - (1)]);
			
		new->realValue=temp->realValue;		
		new->intValue=temp->intValue;
		new->boolValue=temp->boolValue;
		strcpy(new->identLex, temp->identLex);
		(yyval) = new;
	}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1438 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		(yyval) = new;



	
	}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1451 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		(yyval) = new;

	}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1462 "parser.y"
    {

		Node *new = createNode();
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		(yyval) = new;


	}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1478 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = conditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp->semTypeDef;
		(yyval) = new;
	}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1490 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = conditionalStatement;
        	new->pt0 = (yyvsp[(1) - (4)]) ;  
		new->pt2 = (yyvsp[(3) - (4)]) ;  
		Node *temp1 = (yyvsp[(1) - (4)]) ;  
		Node *temp2 = (yyvsp[(2) - (4)]) ;  
		if (temp1->semTypeDef==storeVoid && temp2->semTypeDef==storeVoid ) {  
		new->semTypeDef=storeVoid ;  
		}


		(yyval) = new;

	}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1510 "parser.y"
    {
		
		Node *new = createNode();         	
		new->type = conditionalStatement;
		new->pt0 = (yyvsp[(1) - (2)]) ;  
		new->pt1 = (yyvsp[(2) - (2)]) ;  
		Node *temp1=(yyvsp[(1) - (2)]);
		Node *temp2=(yyvsp[(2) - (2)]);
		
		if (temp1->semTypeDef==storeBoolean && temp2->semTypeDef==storeVoid ) {  
			new->semTypeDef==storeVoid ;  
		
	
		}
		else{
			new->semTypeDef==storeError ;  

		}
		
		(yyval)=new;
	}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1539 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = ifStatement;
        	new->pt0 = (yyvsp[(1) - (2)]);
		new->pt1 = (yyvsp[(2) - (2)]);
		Node *temp = (yyvsp[(1) - (2)]);
		Node *temp2 = (yyvsp[(2) - (2)]);
		
		if (temp->semTypeDef==storeBoolean) {  
			new->semTypeDef=temp2->semTypeDef;
		}
		else {
			new->semTypeDef=storeError;
		}
		
		(yyval) = new;


	}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1562 "parser.y"
    {
		Node *new = createNode();
        	new->type = ifClause;
        	new->pt1 = (yyvsp[(2) - (3)]);
                Node* temp = (Node*)(yyvsp[(2) - (3)]);
		if (temp->semTypeDef==storeBoolean) {  
			new->semTypeDef=storeBoolean ;  
		}
		else {  
			new->semTypeDef=storeError ;  
		}
		
		(yyval) = new;  
	}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1580 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = basicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  

		(yyval) = new;

	}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1600 "parser.y"
    {		
		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement; 
        	new->pt0 = (yyvsp[(1) - (1)]) ; 
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  
		(yyval) = new;

	}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 1613 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  

		new->semTypeDef=temp->semTypeDef ;  

		(yyval) = new;

	}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1627 "parser.y"
    {
			
		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  
		(yyval) = new;

	}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1639 "parser.y"
    {
		(yyval) = (yyvsp[(1) - (3)]);
	}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1650 "parser.y"
    {
		Node *new = createNode();
                new->type = returnStatement;
		Node *temp = (yyvsp[(2) - (2)]) ;
		if(temp->semTypeDef==storeError)
		{
			new->semTypeDef=storeError;
		}
		else
		{
			new->semTypeDef = temp->semTypeDef;
		}
		(yyval) = new;
	}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1667 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = (yyvsp[(1) - (3)]);
		new->pt2 = (yyvsp[(2) - (3)]);
		(yyval) = new;
		Symbol *symbol1;	
		Node *tmp1=(yyvsp[(1) - (3)]);
		Node *tmp2=(yyvsp[(2) - (3)]);
		new->semTypeDef=storeVoid;		
  		symbol1=lookUp(tmp1->identLex,currentScope);
		if (symbol1==NULL){
			new->semTypeDef=storeError;
		}
		else{
			if (symbol1->type==storeInteger && tmp2->semTypeDef==storeInteger) 				{								
				// SYMBOL1>TYPE IS INTEGER  
				symbol1->value=tmp2->intValue;
			}
		
		}
	}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1691 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = (yyvsp[(1) - (3)]);
		new->pt2 = (yyvsp[(2) - (3)]);
		(yyval) = new;
	
		Node *temp1=(yyvsp[(1) - (3)]);
		Node *temp2=(yyvsp[(2) - (3)]);
		Symbol *symbol2=lookUp(temp1->identLex,currentScope);
		new->semTypeDef=storeVoid ;  
		


		if (symbol2==NULL){
			new->semTypeDef=storeError;  
		
		}
		else{
			if (symbol2->type==storeBoolean==storeBoolean && temp2->semTypeDef==storeBoolean) {  
				symbol2->boolean=temp2->boolValue;
			}
		}
	}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1895 "parser.y"
    {  
		Node *new = createNode();
		Node *temp = (yyvsp[(2) - (10)]);
		Symbol *symbol2=lookUp(temp->identLex,currentScope);
		if (symbol2 == NULL) {  
			temp->semTypeDef=storeError;
		
		}
		else {  
			if (symbol2->type==storeInteger || symbol2->type==storeReal){
				temp->semTypeDef=storeError;
			}
		}

		if (temp->semTypeDef==storeError){  
			new->semTypeDef==storeError;
			(yyval) = new;
		}
		else
		{

			Node *temp2 = (yyvsp[(4) - (10)]);
			Node *temp3 = (yyvsp[(6) - (10)]);
			Node *temp4 = (yyvsp[(8) - (10)]);
			Node *temp5 = (yyvsp[(10) - (10)]);
			if (temp2->semTypeDef == temp->semTypeDef && temp3->semTypeDef == temp->semTypeDef && temp4->semTypeDef == temp->semTypeDef) {  

			}
			else {
				if(temp->semTypeDef == storeInteger)
				{
					new->semTypeDef = storeError;
				}
				else
				{
					new->semTypeDef = storeError;
				}
				
			}
			(yyval)=new;
		}
	}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1942 "parser.y"
    {	
		printf("empty reached\n");
		Node *new = createNode();         	            	  
        	new->type =empty;
		(yyval) = new;
	}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1950 "parser.y"
    {
		Node *new = createNode();
		Node *temp1 = (yyvsp[(1) - (2)]);
		Symbol *symbol= lookUp(temp1->identLex,currentScope);

		if(symbol == NULL)
		{

			new->semTypeDef = storeError;
		}
		else
		{
			Node *temp2 = (yyvsp[(2) - (2)]);
			if(temp2->semTypeDef==storeError)
			{
				new->semTypeDef =storeError;
		}
		else
		{
			new->semTypeDef = symbol->type;

		}
	}

		(yyval) = new; 
	}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1980 "parser.y"
    {
		Node *new = createNode(); 
		new->type = procedureIdentifier;
		new->pt0 = (yyvsp[(1) - (1)]);
	
		Node *temp=(yyvsp[(1) - (1)]);

		(yyval) = new;
	}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1993 "parser.y"
    {
		(yyval)=(yyvsp[(2) - (3)]);
		Node *temp = (yyvsp[(2) - (3)]);
		if(temp->semTypeDef != storeError)
		{		
			temp->semTypeDef == storeVoid;
		}
		
	}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 2006 "parser.y"
    {
		Node *temp = (yyvsp[(-1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		
		Symbol* symbol= lookUp(temp1->identLex,currentScope);
		Node *new = createNode();
		new->intValue = 0;
		
		new->semTypeDef = storeVoid;
		
		(yyval) = new;
	}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 2020 "parser.y"
    {
		Node *temp = (yyvsp[(-1) - (3)]);
		Node *temp3 = (yyvsp[(1) - (3)]);
		Node *temp1 = (yyvsp[(3) - (3)]);

		Symbol* symbol= lookUp(temp->identLex,currentScope);
		
		Node *new = createNode();
		new->intValue = 1 + temp3->intValue;
		if(temp3->semTypeDef == storeError)
			new->semTypeDef = storeError;
		else
		{new->semTypeDef = storeVoid;
			
			
		}	
		(yyval) = new;

	}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 2043 "parser.y"
    {
		Node *new = createNode(); 
		Node *temp = (yyvsp[(1) - (1)]); 
		new->type = actualParameter;
		new->semTypeDef = temp->semTypeDef;
		new->pt0 = (yyvsp[(1) - (1)]);

		(yyval) = new;
	}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 2058 "parser.y"
    {
		Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (1)]);
//		Node *temp2=$3;
		(yyval)=new;
	}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 2066 "parser.y"
    {
		Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (1)]);
//		Node *temp2=$3;
		(yyval)=new;

	}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 2075 "parser.y"
    {	Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (1)]);
//		Node *temp2=$3;
		(yyval)=new;
	}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 2092 "parser.y"
    {
		Node* new=createNode();
		Node* temp=(yyvsp[(2) - (2)]);

		(yyval)=new;
	}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 2109 "parser.y"
    {
		(yyvsp[(0) - (1)])=(yyvsp[(-1) - (1)]);
		Node *node1 = (yyvsp[(1) - (1)]);
		
		int oldScope = currentScope;
		currentScope = globalLevel + 1;

		if (lookUpInCurrentScope(node1->identLex) == NULL){
			Symbol * index = addEntry(node1->identLex);
		}
		currentScope = oldScope;
	}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 2124 "parser.y"
    {   ////check/////
		(yyvsp[(1) - (2)]) = (yyvsp[(0) - (2)]); 
		(yyvsp[(2) - (2)]) = (yyvsp[(0) - (2)]);
	}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 2131 "parser.y"
    {
		(yyval) = (yyvsp[(0) - (1)]);
	}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 2134 "parser.y"
    {
		(yyvsp[(1) - (1)]) = (yyvsp[(0) - (1)]);
	}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 2139 "parser.y"
    {
		Node *node1 = (yyvsp[(0) - (1)]);
		Node *node2 = (yyvsp[(1) - (1)]);
		Symbol *symbol = lookUp(node2->identLex,currentScope);
		symbol->type = node1->semTypeDef;
	}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 2145 "parser.y"
    {
		(yyvsp[(2) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 2149 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 2163 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
		Node *node1 = (yyvsp[(1) - (3)]);
	}
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 2170 "parser.y"
    {
		Node *node = createNode();
		node->type = procedureHeading;
		node->pt0 = (yyvsp[(1) - (1)]);
		Node *node1 = (yyvsp[(1) - (1)]);
		node1->parent = node;
		strcpy(node->identLex, node1->identLex);
		if (lookUpInCurrentScope(node1->identLex) == NULL){
			Symbol * index = addEntry(node1->identLex);
		}
		(yyval) = node;
	}
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 2181 "parser.y"
    {
		(yyvsp[(3) - (4)]) = (yyvsp[(1) - (4)]);
	}
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 2202 "parser.y"
    {
		Node *new = createNode();
		
		new->type = procedureBody;
		Node *temp = (yyvsp[(1) - (1)]);
		new->semTypeDef = temp->semTypeDef;
		(yyval) = new;
	}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 2212 "parser.y"
    {
		Node *node1 = (yyvsp[(2) - (3)]);
		Node *node2 = (yyvsp[(3) - (3)]);

		Symbol* symbol = lookUpInCurrentScope(node1->identLex);
		symbol->type = storeVoid;

		Node *node = createNode();
                
        	node->type = procedureDeclaration;

		if (node1->semTypeDef == storeVoid && node2->semTypeDef == storeVoid)
			node->semTypeDef = storeVoid;
		else
			node->semTypeDef = storeError;
		(yyval) = node;
	}
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 2230 "parser.y"
    {
		Node *node1 = (yyvsp[(3) - (4)]);
		Node *node2 = (yyvsp[(1) - (4)]);
		Node *node3 = (yyvsp[(4) - (4)]);

		Symbol* symbol = lookUpInCurrentScope(node1->identLex);
		symbol->type = node2->semTypeDef;

		Node *node = createNode();
                
        	node->type = procedureDeclaration;

		if (node1->semTypeDef == storeVoid && node3->semTypeDef == storeVoid)
			node->semTypeDef = node2->semTypeDef;
		else
			node->semTypeDef = storeError;
		(yyval) = node;
	}
    break;



/* Line 1806 of yacc.c  */
#line 3880 "y.tab.c"
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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



/* Line 2067 of yacc.c  */
#line 2250 "parser.y"

int main(int argc, char* argv[])
{
   	int i = 1;
	for(i=1;i<argc;i++)
	{
	    FILE* fp;
	    fp = fopen(argv[i], "r");
	    yyin = fp;
	    while(yyparse() != 0)
		;
	}
	return 0;
}


