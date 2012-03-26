
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
#line 6 "parser.y"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "tree.c"
#include <stdbool.h>
#include "symbolTable.h"

int globalLevel=0;
int yylval;
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
		//printf("Scope stack is empty\n");
		return -1;
	}
}

extern int lineNo ; 
int yylval;
extern char* yytext;

SymbolTable symbolTable[1000];		// array of symbol tables for different scopes
int tempNodeScope;
int currentScope;
extern FILE *yyin;
void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
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
		printf("INTERGER VALUE: %d",node->intValue);}
	if(!(node->realValue)){
		printf("REAL VALUE: %f",node->realValue);}
	if(node->boolValue){
		printf("BOOLVALUE: TRUE");}
	if(node->type != NULL){
		printf("TYPE: %d",node->type);}
	if(node->track != NULL){
		printf("Track: %d",node->track);}
}
/* 
int yywrap()
{
        return 1;
} */
 
main(int argc, char* argv[])
{
    FILE *fp;
    int i;
    
    for(i=1;i < argc;i++)
    {
		if (argc > 1){
			fp = fopen(argv[i], "r");
			yyrestart(fp);
			yylex();
		}
		else printf("please enter a file in the argument....\n USAGE :>> ./algolLexer test");
	}
    return 0;
/*       do
	{
		
		yyparse();
	}
	while(!feof(yyin));*/
} 
 




/* Line 189 of yacc.c  */
#line 228 "y.tab.c"

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
     TOKEN_OPEN_BRACKET = 272,
     TOKEN_CLOSE_BRACKET = 273,
     TOKEN_OPEN_SQUARE_BRACKET = 274,
     TOKEN_CLOSE_SQUARE_BRACKET = 275,
     TOKEN_CONTINUE = 276,
     TOKEN_REAL_NUM = 277,
     TOKEN_INTEGER = 278,
     TOKEN_COLON = 279,
     TOKEN_REL_OP = 280,
     TOKEN_LESS_EQUAL = 281,
     TOKEN_GREATER = 282,
     TOKEN_GREATER_EQUAL = 283,
     TOKEN_EQUAL = 284,
     TOKEN_LESS = 285,
     TOKEN_NOTEQUAL = 286,
     TOKEN_EQUIV = 287,
     TOKEN_AND_OP = 288,
     TOKEN_OR_OP = 289,
     TOKEN_NOT_OP = 290,
     TOKEN_GOTO = 291,
     TOKEN_FOR = 292,
     TOKEN_DO = 293,
     TOKEN_WHILE = 294,
     TOKEN_STEP = 295,
     TOKEN_UNTIL = 296,
     TOKEN_IF = 297,
     TOKEN_THEN = 298,
     TOKEN_ELSE = 299,
     TOKEN_SWITCH = 300,
     TOKEN_VALUE = 301,
     TOKEN_BOOLEAN = 302,
     TOKEN_LABEL = 303,
     TOKEN_TYPE_OWN = 304,
     TOKEN_TYPE_INTEGER = 305,
     TOKEN_TYPE_REAL = 306,
     TOKEN_TYPE_BOOLEAN = 307,
     TOKEN_TYPE_ARRAY = 308,
     TOKEN_TYPE_SWITCH = 309,
     TOKEN_TYPE_PROCEDURE = 310,
     TOKEN_TYPE_STRING = 311,
     TOKEN_TYPE_LABEL = 312,
     TOKEN_TYPE_VALUE = 313,
     TOKEN_ARRAY = 314,
     TOKEN_IMPLY = 315,
     TOKEN_SEMICOLON = 316,
     TOKEN_LTRSTRING = 317,
     TOKEN_TINTEGER = 318,
     TOKEN_TREAL = 319,
     TOKEN_RETURN = 320,
     TOKEN_ASSIGN = 321,
     TOKEN_NOT_EQUAL = 322,
     TOKEN_RELOP = 323
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
#define TOKEN_OPEN_BRACKET 272
#define TOKEN_CLOSE_BRACKET 273
#define TOKEN_OPEN_SQUARE_BRACKET 274
#define TOKEN_CLOSE_SQUARE_BRACKET 275
#define TOKEN_CONTINUE 276
#define TOKEN_REAL_NUM 277
#define TOKEN_INTEGER 278
#define TOKEN_COLON 279
#define TOKEN_REL_OP 280
#define TOKEN_LESS_EQUAL 281
#define TOKEN_GREATER 282
#define TOKEN_GREATER_EQUAL 283
#define TOKEN_EQUAL 284
#define TOKEN_LESS 285
#define TOKEN_NOTEQUAL 286
#define TOKEN_EQUIV 287
#define TOKEN_AND_OP 288
#define TOKEN_OR_OP 289
#define TOKEN_NOT_OP 290
#define TOKEN_GOTO 291
#define TOKEN_FOR 292
#define TOKEN_DO 293
#define TOKEN_WHILE 294
#define TOKEN_STEP 295
#define TOKEN_UNTIL 296
#define TOKEN_IF 297
#define TOKEN_THEN 298
#define TOKEN_ELSE 299
#define TOKEN_SWITCH 300
#define TOKEN_VALUE 301
#define TOKEN_BOOLEAN 302
#define TOKEN_LABEL 303
#define TOKEN_TYPE_OWN 304
#define TOKEN_TYPE_INTEGER 305
#define TOKEN_TYPE_REAL 306
#define TOKEN_TYPE_BOOLEAN 307
#define TOKEN_TYPE_ARRAY 308
#define TOKEN_TYPE_SWITCH 309
#define TOKEN_TYPE_PROCEDURE 310
#define TOKEN_TYPE_STRING 311
#define TOKEN_TYPE_LABEL 312
#define TOKEN_TYPE_VALUE 313
#define TOKEN_ARRAY 314
#define TOKEN_IMPLY 315
#define TOKEN_SEMICOLON 316
#define TOKEN_LTRSTRING 317
#define TOKEN_TINTEGER 318
#define TOKEN_TREAL 319
#define TOKEN_RETURN 320
#define TOKEN_ASSIGN 321
#define TOKEN_NOT_EQUAL 322
#define TOKEN_RELOP 323




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 406 "y.tab.c"

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   492

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  81
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNRULES -- Number of states.  */
#define YYNSTATES  246

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   323

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
      65,    66,    67,    68
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     9,    13,    15,    17,    19,    22,
      24,    28,    31,    35,    37,    39,    41,    43,    45,    49,
      51,    55,    57,    62,    64,    65,    70,    74,    76,    78,
      80,    85,    87,    91,    95,    97,   101,   105,   107,   111,
     113,   115,   117,   119,   123,   125,   127,   129,   131,   136,
     138,   142,   144,   146,   148,   153,   155,   159,   161,   165,
     167,   171,   173,   177,   179,   182,   184,   186,   188,   192,
     194,   198,   200,   202,   203,   208,   210,   212,   214,   217,
     219,   221,   223,   225,   227,   229,   234,   237,   240,   244,
     246,   248,   250,   252,   254,   256,   259,   263,   266,   270,
     281,   282,   285,   287,   291,   293,   297,   299,   301,   305,
     309,   313,   317,   321,   324,   326,   328,   330,   331,   336,
     338,   339,   344,   346,   350,   352,   356,   358,   361,   363,
     365,   368,   372,   377,   378,   379,   387,   388,   389,   396,
     397,   403,   407
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      70,     0,    -1,     5,    -1,    70,    61,    77,    -1,    70,
      61,    76,    -1,    71,    -1,     1,    -1,    62,    -1,     5,
      76,    -1,    74,    -1,    73,    24,    75,    -1,   132,     6,
      -1,   132,    61,    76,    -1,   113,    -1,    86,    -1,   149,
      -1,    88,    -1,    88,    -1,    78,    24,    79,    -1,    80,
      -1,    81,    16,    80,    -1,    99,    -1,    82,    19,    81,
      20,    -1,    83,    -1,    -1,    83,    16,    85,    84,    -1,
     112,    59,    84,    -1,    88,    -1,   100,    -1,    89,    -1,
     118,    89,    44,    88,    -1,    90,    -1,    89,    11,    90,
      -1,    89,    12,    90,    -1,    91,    -1,    90,    15,    91,
      -1,    90,    13,    91,    -1,    92,    -1,    91,    14,    92,
      -1,   126,    -1,    93,    -1,    94,    -1,    95,    -1,    17,
      88,    18,    -1,    22,    -1,    23,    -1,    99,    -1,    96,
      -1,    82,    19,    97,    20,    -1,    98,    -1,    97,    16,
      98,    -1,    88,    -1,     4,    -1,   101,    -1,   118,   101,
      44,   100,    -1,   102,    -1,   101,    32,   102,    -1,   103,
      -1,   102,    60,   103,    -1,   104,    -1,   103,    34,   104,
      -1,   105,    -1,   104,    33,   105,    -1,   106,    -1,    35,
     106,    -1,   107,    -1,    95,    -1,   108,    -1,    17,   100,
      18,    -1,     7,    -1,    89,   109,    89,    -1,    25,    -1,
     114,    -1,    -1,   114,    16,   111,   110,    -1,    64,    -1,
      63,    -1,    47,    -1,   112,   110,    -1,    99,    -1,     4,
      -1,   119,    -1,    75,    -1,    72,    -1,   117,    -1,   118,
     115,    44,   132,    -1,   118,   124,    -1,   118,   115,    -1,
      42,   100,    43,    -1,   120,    -1,   123,    -1,   121,    -1,
     126,    -1,   122,    -1,   125,    -1,    65,    87,    -1,    95,
      66,    88,    -1,    95,    88,    -1,    95,    66,   100,    -1,
      37,    95,    66,    88,    40,    88,    41,    88,    38,   132,
      -1,    -1,   127,   128,    -1,    99,    -1,    17,   129,    18,
      -1,   130,    -1,   129,   131,   130,    -1,    87,    -1,    16,
      -1,   115,    61,   132,    -1,   116,    61,   132,    -1,   124,
      61,   132,    -1,    77,    61,   132,    -1,    87,    61,   132,
      -1,     3,    87,    -1,   125,    -1,    99,    -1,   133,    -1,
      -1,   133,    16,   135,   134,    -1,   125,    -1,    -1,    17,
     137,   134,    18,    -1,    99,    -1,   138,    16,    99,    -1,
     125,    -1,    46,   138,    61,    -1,   112,    -1,   112,    59,
      -1,    48,    -1,    45,    -1,   112,    10,    -1,   140,   138,
      61,    -1,   141,   140,   138,    61,    -1,    -1,    -1,   127,
     143,   136,    61,   144,   139,   141,    -1,    -1,    -1,   127,
     145,   136,    61,   146,   139,    -1,    -1,     5,    61,   132,
     148,     6,    -1,    10,   142,   147,    -1,   112,    10,   142,
     147,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   237,   237,   238,   241,   250,   272,   279,   294,   298,
     300,   304,   311,   322,   327,   332,   339,   356,   373,   392,
     404,   425,   437,   452,   469,   468,   488,   494,   504,   515,
     528,   548,   560,   594,   627,   639,   669,   702,   714,   728,
     739,   751,   763,   771,   785,   796,   807,   822,   838,   865,
     881,   900,   911,   920,   935,   955,   966,   976,   986,  1004,
    1014,  1032,  1042,  1060,  1070,  1087,  1097,  1109,  1119,  1130,
    1144,  1228,  1237,  1260,  1259,  1280,  1289,  1300,  1319,  1327,
    1342,  1359,  1373,  1384,  1399,  1411,  1431,  1460,  1483,  1502,
    1521,  1534,  1548,  1560,  1568,  1572,  1589,  1612,  1618,  1822,
    1870,  1877,  1906,  1918,  1931,  1945,  1968,  1979,  1982,  1989,
    1998,  2005,  2013,  2015,  2023,  2032,  2047,  2048,  2048,  2055,
    2058,  2058,  2063,  2069,  2073,  2073,  2077,  2078,  2079,  2080,
    2081,  2082,  2086,  2089,  2101,  2089,  2104,  2116,  2104,  2121,
    2121,  2131,  2148
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
  "TOKEN_OPEN_BRACKET", "TOKEN_CLOSE_BRACKET", "TOKEN_OPEN_SQUARE_BRACKET",
  "TOKEN_CLOSE_SQUARE_BRACKET", "TOKEN_CONTINUE", "TOKEN_REAL_NUM",
  "TOKEN_INTEGER", "TOKEN_COLON", "TOKEN_REL_OP", "TOKEN_LESS_EQUAL",
  "TOKEN_GREATER", "TOKEN_GREATER_EQUAL", "TOKEN_EQUAL", "TOKEN_LESS",
  "TOKEN_NOTEQUAL", "TOKEN_EQUIV", "TOKEN_AND_OP", "TOKEN_OR_OP",
  "TOKEN_NOT_OP", "TOKEN_GOTO", "TOKEN_FOR", "TOKEN_DO", "TOKEN_WHILE",
  "TOKEN_STEP", "TOKEN_UNTIL", "TOKEN_IF", "TOKEN_THEN", "TOKEN_ELSE",
  "TOKEN_SWITCH", "TOKEN_VALUE", "TOKEN_BOOLEAN", "TOKEN_LABEL",
  "TOKEN_TYPE_OWN", "TOKEN_TYPE_INTEGER", "TOKEN_TYPE_REAL",
  "TOKEN_TYPE_BOOLEAN", "TOKEN_TYPE_ARRAY", "TOKEN_TYPE_SWITCH",
  "TOKEN_TYPE_PROCEDURE", "TOKEN_TYPE_STRING", "TOKEN_TYPE_LABEL",
  "TOKEN_TYPE_VALUE", "TOKEN_ARRAY", "TOKEN_IMPLY", "TOKEN_SEMICOLON",
  "TOKEN_LTRSTRING", "TOKEN_TINTEGER", "TOKEN_TREAL", "TOKEN_RETURN",
  "TOKEN_ASSIGN", "TOKEN_NOT_EQUAL", "TOKEN_RELOP", "$accept", "blockHead",
  "unlabelledBlock", "block", "label", "unlabelledCompound",
  "compoundStatement", "compoundTail", "declaration", "lowerBound",
  "upperBound", "boundPair", "boundPairList", "arrayIdentifier",
  "arraySegment", "arrayList", "@1", "arrayDeclaration", "expression",
  "arithmeticExpression", "simpleArithmeticExpression", "term", "factor",
  "primary", "realNumber", "integer", "variable", "subscriptedVariable",
  "subscriptList", "subscriptExpression", "identifier",
  "booleanExpression", "simpleBoolean", "implication", "booleanTerm",
  "booleanFactor", "booleanSecondary", "booleanPrimary", "logicalValue",
  "relation", "relationalOperator", "listType", "@2", "type",
  "typeDeclaration", "varIdentifier", "unconditionalStatement",
  "conditionalStatement", "ifStatement", "ifClause", "basicStatement",
  "unlabelledBasicStatement", "dummyStatement", "returnStatement",
  "assignmentStatement", "forStatement", "empty", "procedureStatement",
  "procedureIdentifier", "actualParameterPart", "actualParameterList",
  "actualParameter", "parameterDelimiter", "statement", "formalParameter",
  "formalParameterList", "$@3", "formalParameterPart", "$@4",
  "identifierList", "valuePart", "specifier", "specificationPart",
  "procedureHeading", "@5", "$@6", "@7", "$@8", "procedureBody", "@9",
  "procedureDeclaration", 0
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
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    70,    71,    72,    72,    73,    74,    75,
      75,    76,    76,    77,    77,    77,    78,    79,    80,    81,
      81,    82,    83,    84,    85,    84,    86,    87,    87,    88,
      88,    89,    89,    89,    90,    90,    90,    91,    91,    91,
      92,    92,    92,    92,    93,    94,    95,    95,    96,    97,
      97,    98,    99,   100,   100,   101,   101,   102,   102,   103,
     103,   104,   104,   105,   105,   106,   106,   106,   106,   107,
     108,   109,   110,   111,   110,   112,   112,   112,   113,   114,
      99,   115,   115,   115,   116,   116,   116,   117,   118,   119,
     120,   120,   120,   120,   121,   122,   123,   123,   123,   124,
     125,   126,   127,   128,   129,   129,   130,   131,   132,   132,
     132,   132,   132,   132,   132,   133,   134,   135,   134,   136,
     137,   136,   138,   138,   139,   139,   140,   140,   140,   140,
     140,   141,   141,   143,   144,   142,   145,   146,   142,   148,
     147,   149,   149
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     3,     1,     1,     1,     2,     1,
       3,     2,     3,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     4,     1,     0,     4,     3,     1,     1,     1,
       4,     1,     3,     3,     1,     3,     3,     1,     3,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     4,     1,
       3,     1,     1,     1,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     2,     1,     1,     1,     3,     1,
       3,     1,     1,     0,     4,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     4,     2,     2,     3,     1,
       1,     1,     1,     1,     1,     2,     3,     2,     3,    10,
       0,     2,     1,     3,     1,     3,     1,     1,     3,     3,
       3,     3,     3,     2,     1,     1,     1,     0,     4,     1,
       0,     4,     1,     3,     1,     3,     1,     2,     1,     1,
       2,     3,     4,     0,     0,     7,     0,     0,     6,     0,
       5,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     2,     0,     1,     0,     0,    77,    76,    75,     3,
      14,     0,    13,    15,    52,   102,   133,     0,     0,     0,
      79,    78,    72,   100,   100,     0,   141,     0,     0,    23,
      26,    21,    73,   120,   119,     0,     0,     0,   142,     0,
      24,     0,     0,   134,   137,     6,     0,     0,    69,     0,
      44,    45,     0,     0,     0,     7,     0,     0,     5,    83,
       0,     9,    82,     0,     0,     0,    27,    29,    31,    34,
      37,    40,    41,    42,    47,    46,    28,    53,    55,    57,
      59,    61,    63,    65,    67,     0,     0,    84,     0,    81,
      89,    91,    93,    90,     0,    94,    39,     0,   139,     0,
       0,    19,     0,    16,    29,    42,     0,    39,     0,    74,
     115,   116,     0,   100,   100,   113,    42,     0,     8,     0,
       0,     0,     0,    64,     0,    46,     0,     0,    95,     0,
       0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,    97,     0,     0,     0,     0,     0,     0,     0,
       0,    87,    86,    94,     0,     0,   101,     0,     0,     0,
      22,     0,    25,   117,   121,     0,   124,     0,   138,    11,
       0,    43,    68,     0,    88,     4,     0,     0,    10,   111,
      51,     0,    49,   112,    32,    33,    70,    36,    35,    38,
      96,    98,    56,    58,    60,    62,   108,   109,     0,     0,
       0,   110,   106,     0,   104,   140,    18,    17,    20,     0,
     122,     0,   129,   128,   126,     0,   135,    12,     0,     0,
      48,    30,    54,    85,   107,   103,     0,   118,     0,   125,
     130,   127,     0,     0,     0,    50,   105,   123,   131,     0,
       0,   132,     0,     0,     0,    99
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    57,    58,    59,    60,    61,    62,   118,    63,   100,
     206,   101,   102,    64,    29,    30,   108,    10,    65,    66,
      67,    68,    69,    70,    71,    72,   105,    74,   181,   182,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
     137,    21,    41,    11,    12,    22,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,   107,    97,   156,
     203,   204,   226,   119,   111,   112,   209,    35,    42,   211,
     167,   215,   216,    17,    23,   113,    24,   114,    26,   157,
      13
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -182
static const yytype_int16 yypact[] =
{
      36,  -182,     5,  -182,    11,    40,  -182,  -182,  -182,  -182,
    -182,    25,  -182,  -182,  -182,  -182,  -182,    60,    40,    40,
    -182,  -182,    97,   106,   106,    31,  -182,    60,   115,   124,
    -182,  -182,  -182,  -182,  -182,    81,    90,   354,  -182,   178,
    -182,    40,    40,  -182,  -182,  -182,   150,   362,  -182,   150,
    -182,  -182,   222,    40,   150,  -182,   150,    92,  -182,  -182,
     112,  -182,  -182,   102,   118,   114,  -182,    84,    76,   144,
    -182,  -182,  -182,   254,  -182,   165,  -182,   154,   127,   156,
     161,  -182,  -182,  -182,  -182,   142,   147,  -182,    46,  -182,
    -182,  -182,  -182,  -182,   163,   205,  -182,   208,  -182,   178,
     198,  -182,    23,  -182,   119,  -182,   277,  -182,    40,  -182,
    -182,   215,   214,   187,   187,  -182,   145,   195,  -182,     3,
     216,   218,    84,  -182,   172,   165,   200,   195,  -182,   354,
      14,   354,   178,   354,   277,   277,  -182,   277,   277,   277,
     277,   150,  -182,   195,   195,   195,   195,   354,   354,   121,
      -2,   197,  -182,  -182,   354,   150,  -182,   242,   178,   178,
    -182,    34,  -182,  -182,  -182,    40,  -182,     9,  -182,  -182,
     354,  -182,  -182,   178,  -182,  -182,   102,   354,  -182,  -182,
    -182,    66,  -182,  -182,    76,    76,   119,   144,   144,  -182,
    -182,  -182,   127,   156,   161,  -182,  -182,  -182,   178,   150,
     427,  -182,  -182,    83,  -182,  -182,  -182,  -182,  -182,    40,
    -182,    -6,  -182,  -182,     2,    40,     9,  -182,   209,   178,
    -182,  -182,  -182,  -182,  -182,  -182,   150,  -182,    40,  -182,
    -182,  -182,    16,    40,   178,  -182,  -182,  -182,  -182,    24,
     210,  -182,   178,   212,   427,  -182
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -182,   257,  -182,  -182,  -182,  -182,   129,  -103,    -1,  -182,
    -182,   101,  -182,   -15,  -182,   155,  -182,  -182,   -45,    48,
     110,    21,    75,   122,  -182,  -182,   -29,  -182,  -182,    45,
      -5,   -47,   -57,   123,   126,   128,   134,   213,  -182,  -182,
    -182,   231,  -182,  -145,  -182,  -182,   186,  -182,  -182,   120,
    -182,  -182,  -182,  -182,  -182,   196,    -8,    -9,    44,  -182,
    -182,    59,  -182,    -4,  -182,    80,  -182,   267,  -182,  -181,
     181,    82,  -182,   274,  -182,  -182,  -182,  -182,   270,  -182,
    -182
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -115
static const yytype_int16 yytable[] =
{
      15,   115,   121,     9,    28,     3,    20,   126,    73,   169,
     228,   128,   230,    15,    31,    34,    34,   116,    73,   177,
     116,     5,   214,   116,   124,   116,   175,   116,    96,    14,
     143,   150,   228,    98,   232,    18,    20,   110,    96,   159,
     228,     1,   199,   160,    14,   134,   135,    45,   125,    16,
      14,    47,   239,    48,   212,   229,     6,   213,     6,    73,
     150,   231,    16,    49,   170,    25,     4,   217,    50,    51,
     150,   214,     7,     8,     7,     8,    55,   238,   198,    96,
     153,    52,   219,    53,    19,   241,   220,   103,   116,   138,
    -100,   139,    37,    28,   191,   134,   135,   120,   116,   224,
      73,   225,    73,    31,    73,   166,   166,  -100,    55,   136,
     202,    56,   116,    32,   116,   116,   116,   116,    73,    73,
      96,   142,    96,    33,    96,    73,   116,   179,   176,   183,
     134,   135,   134,   135,    39,   125,   130,   132,    96,    96,
      40,    73,    43,   196,   197,    96,   136,   120,    73,   104,
     201,    44,   222,   129,    14,   184,   185,    48,   140,   106,
     210,    96,   122,   131,   122,   198,   117,    49,    96,   117,
     116,    73,    50,    51,   127,   133,   117,   -66,   -66,   -66,
     180,   202,    14,   104,   -21,    52,   143,   144,   -66,   190,
     145,    96,    54,   106,   146,    99,   223,   116,   149,    14,
      50,    51,    48,   147,   110,   -66,   207,   103,   148,   104,
     210,  -114,    49,   187,   188,    73,   161,    50,    51,   106,
      54,   218,   158,   237,   154,   155,    14,   149,   210,    48,
      52,   163,   164,   165,   171,    96,   172,   122,   173,    49,
     245,   200,   104,   174,    50,    51,   221,   186,   205,   234,
     244,   242,   106,   122,   122,   122,   122,     2,    14,   178,
     208,   117,   189,   162,   235,   123,   192,   180,   104,   104,
     193,    99,   109,   194,   151,   117,    50,    51,   106,   106,
     195,    14,   240,   104,   152,   236,   -66,   -66,   -66,   227,
     243,    36,    27,   106,    99,   168,    54,    38,   233,    50,
      51,     0,     0,     0,     0,     0,     0,     0,   104,   122,
       0,     0,     0,     0,   -66,     0,     0,     0,   106,   127,
     141,     0,     0,     0,     0,     0,     0,     0,     0,   104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   106,
       0,     0,     0,     0,   104,     0,   117,     0,     0,     0,
       0,     0,   104,     0,   106,    45,     0,    46,    14,    47,
    -100,    48,   106,    45,     5,    46,    14,    47,  -100,    48,
       0,    49,     5,     0,     0,     0,    50,    51,     0,    49,
       0,     0,     0,     0,    50,    51,     0,     0,     0,    52,
       0,    53,     0,     0,     0,     0,    54,    52,     0,    53,
       0,     6,     0,     0,    54,     0,     0,     0,     0,     6,
       0,     0,     0,     0,     0,  -100,    55,     7,     8,    56,
       0,     0,     0,    -2,    55,     7,     8,    56,    45,     0,
      46,    14,    47,     0,    48,     0,     0,     5,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,     0,    50,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    52,     0,    53,     0,     0,     0,     0,    54,
       0,     0,     0,     0,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -100,    55,
       7,     8,    56
};

static const yytype_int16 yycheck[] =
{
       5,    46,    49,     4,    19,     0,    11,    54,    37,     6,
      16,    56,    10,    18,    19,    23,    24,    46,    47,     5,
      49,    10,   167,    52,    53,    54,   129,    56,    37,     4,
      32,    88,    16,    37,   215,    10,    41,    42,    47,    16,
      16,     5,    44,    20,     4,    11,    12,     1,    53,     5,
       4,     5,   233,     7,    45,    61,    47,    48,    47,    88,
     117,    59,    18,    17,    61,     5,    61,   170,    22,    23,
     127,   216,    63,    64,    63,    64,    62,    61,    44,    88,
      88,    35,    16,    37,    59,    61,    20,    39,   117,    13,
      44,    15,    61,   108,   141,    11,    12,    49,   127,    16,
     129,    18,   131,   108,   133,   113,   114,    61,    62,    25,
     155,    65,   141,    16,   143,   144,   145,   146,   147,   148,
     129,    73,   131,    17,   133,   154,   155,   131,   129,   133,
      11,    12,    11,    12,    19,   140,    24,    19,   147,   148,
      16,   170,    61,   147,   148,   154,    25,    99,   177,    39,
     154,    61,   199,    61,     4,   134,   135,     7,    14,    39,
     165,   170,    52,    61,    54,    44,    46,    17,   177,    49,
     199,   200,    22,    23,    54,    61,    56,    32,    33,    34,
     132,   226,     4,    73,    19,    35,    32,    60,    43,   141,
      34,   200,    42,    73,    33,    17,   200,   226,    88,     4,
      22,    23,     7,    61,   209,    60,   158,   159,    61,    99,
     215,     6,    17,   138,   139,   244,   106,    22,    23,    99,
      42,   173,    24,   228,    61,    17,     4,   117,   233,     7,
      35,    16,    18,    46,    18,   244,    18,   127,    66,    17,
     244,    44,   132,    43,    22,    23,   198,   137,     6,    40,
      38,    41,   132,   143,   144,   145,   146,     0,     4,   130,
     159,   141,   140,   108,   219,    52,   143,   219,   158,   159,
     144,    17,    41,   145,    88,   155,    22,    23,   158,   159,
     146,     4,   234,   173,    88,   226,    32,    33,    34,   209,
     242,    24,    18,   173,    17,   114,    42,    27,   216,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,   199,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,   198,   199,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   219,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   219,
      -1,    -1,    -1,    -1,   234,    -1,   226,    -1,    -1,    -1,
      -1,    -1,   242,    -1,   234,     1,    -1,     3,     4,     5,
       6,     7,   242,     1,    10,     3,     4,     5,     6,     7,
      -1,    17,    10,    -1,    -1,    -1,    22,    23,    -1,    17,
      -1,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    35,
      -1,    37,    -1,    -1,    -1,    -1,    42,    35,    -1,    37,
      -1,    47,    -1,    -1,    42,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    61,    62,    63,    64,    65,     1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    37,    -1,    -1,    -1,    -1,    42,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      63,    64,    65
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    70,     0,    61,    10,    47,    63,    64,    77,
      86,   112,   113,   149,     4,    99,   127,   142,    10,    59,
      99,   110,   114,   143,   145,     5,   147,   142,    82,    83,
      84,    99,    16,    17,   125,   136,   136,    61,   147,    19,
      16,   111,   137,    61,    61,     1,     3,     5,     7,    17,
      22,    23,    35,    37,    42,    62,    65,    70,    71,    72,
      73,    74,    75,    77,    82,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   132,    17,
      78,    80,    81,    88,    89,    95,   118,   126,    85,   110,
      99,   133,   134,   144,   146,    87,    95,   118,    76,   132,
      88,   100,    89,   106,    95,    99,   100,   118,    87,    61,
      24,    61,    19,    61,    11,    12,    25,   109,    13,    15,
      14,    66,    88,    32,    60,    34,    33,    61,    61,    89,
     101,   115,   124,   125,    61,    17,   128,   148,    24,    16,
      20,    89,    84,    16,    18,    46,   125,   139,   139,     6,
      61,    18,    18,    66,    43,    76,    77,     5,    75,   132,
      88,    97,    98,   132,    90,    90,    89,    91,    91,    92,
      88,   100,   102,   103,   104,   105,   132,   132,    44,    44,
      44,   132,    87,   129,   130,     6,    79,    88,    80,   135,
      99,   138,    45,    48,   112,   140,   141,    76,    88,    16,
      20,    88,   100,   132,    16,    18,   131,   134,    16,    61,
      10,    59,   138,   140,    40,    98,   130,    99,    61,   138,
      88,    61,    41,    88,    38,   132
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
#line 242 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode =(Node*) (yyvsp[(3) - (3)]);
		newNode->pt0 = (Node*) (yyvsp[(3) - (3)]);
		(yyval) = newNode;
	}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 251 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (1)]);
		(yyval) = newNode;
	}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 273 "parser.y"
    {
		printf("Syntax error in block containing line num %d\n",lineNo);
	}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 280 "parser.y"
    {
		Node *new = createNode();         	
                new->type = label;
		strcpy(new->identLex, yytext);
		(yyval) = new;
	}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 305 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (2)]);
		(yyval) = newNode;
	}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 312 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (3)]);
		(yyval) = newNode;
	}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 323 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 328 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 333 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 340 "parser.y"
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

  case 17:

/* Line 1455 of yacc.c  */
#line 357 "parser.y"
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

  case 18:

/* Line 1455 of yacc.c  */
#line 374 "parser.y"
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

  case 19:

/* Line 1455 of yacc.c  */
#line 393 "parser.y"
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

  case 20:

/* Line 1455 of yacc.c  */
#line 405 "parser.y"
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

  case 21:

/* Line 1455 of yacc.c  */
#line 426 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = arrayIdentifier;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex, tempNode->identLex);
		(yyval) = newNode;
	}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 438 "parser.y"
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

  case 23:

/* Line 1455 of yacc.c  */
#line 453 "parser.y"
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

  case 24:

/* Line 1455 of yacc.c  */
#line 469 "parser.y"
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

  case 27:

/* Line 1455 of yacc.c  */
#line 495 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = expression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 505 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = expression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		(yyval) = newNode;
}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 516 "parser.y"
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

  case 30:

/* Line 1455 of yacc.c  */
#line 529 "parser.y"
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

  case 31:

/* Line 1455 of yacc.c  */
#line 549 "parser.y"
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

  case 32:

/* Line 1455 of yacc.c  */
#line 561 "parser.y"
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
					tempNode0->semDefType==storeReal;
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

  case 33:

/* Line 1455 of yacc.c  */
#line 595 "parser.y"
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
					tempNode2->real = 1.00*tempNode2->intValue ;  
					tempNode2->semTypeDef==storeReal;
				}
				newNode->real=tempNode0->real  -  tempNode2->real ;  
			}
			else {  
				newNode->semTypeDef = storeInteger ;  
				newNode->intValue = tempNode0->intValue  -  tempNode2->intValue ; 
			}
			(yyval) = newNode;
		//}
	}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 628 "parser.y"
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

  case 35:

/* Line 1455 of yacc.c  */
#line 640 "parser.y"
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

  case 36:

/* Line 1455 of yacc.c  */
#line 670 "parser.y"
    {
		
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

				if (tempNode2->real==0.00){
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

  case 37:

/* Line 1455 of yacc.c  */
#line 703 "parser.y"
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

  case 38:

/* Line 1455 of yacc.c  */
#line 715 "parser.y"
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

  case 39:

/* Line 1455 of yacc.c  */
#line 729 "parser.y"
    {
		Node *newNode = createNode();
		
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 740 "parser.y"
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

  case 41:

/* Line 1455 of yacc.c  */
#line 752 "parser.y"
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

  case 42:

/* Line 1455 of yacc.c  */
#line 764 "parser.y"
    {
		Node *tempNode=(yyvsp[(1) - (1)]);
		Symbol* foundEntry = lookUp(tempNode->identLex,currentScope);
		tempNode->semTypeDef=foundEntry->type ;
		(yyval)=tempNode;	
	}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 772 "parser.y"
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

  case 44:

/* Line 1455 of yacc.c  */
#line 786 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = realNumber;
		newNode->realValue = atof(yytext);
		newNode->semTypeDef=storeReal;
		(yyval) = newNode;
	}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 797 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = integer;
		newNode->intValue = atoi(yytext);
		newNode->semTypeDef=storeInteger;  
		(yyval) = newNode;
	}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 808 "parser.y"
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

  case 47:

/* Line 1455 of yacc.c  */
#line 823 "parser.y"
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

  case 48:

/* Line 1455 of yacc.c  */
#line 839 "parser.y"
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

  case 49:

/* Line 1455 of yacc.c  */
#line 866 "parser.y"
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

  case 50:

/* Line 1455 of yacc.c  */
#line 882 "parser.y"
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

  case 51:

/* Line 1455 of yacc.c  */
#line 901 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = subscriptExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		(yyval) = newNode;
	}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 912 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = identifier;
		strcpy(newNode->identLex,yytext);
		(yyval) = newNode;
	}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 921 "parser.y"
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

  case 54:

/* Line 1455 of yacc.c  */
#line 936 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = (yyvsp[(1) - (4)]);
		newNode->pt1 = (yyvsp[(2) - (4)]);
		newNode->pt2 = (yyvsp[(4) - (4)]);
		Node* tempNode1 = (yyvsp[(1) - (4)]);
		Node* tempNode2 = (yyvsp[(2) - (4)]);
		Node* tempNode3 = (yyvsp[(4) - (4)]);
		if(tempNode1->semTypeDef == storeBoolean && tempNode2->semTypeDef == storeBoolean && tempNode3->semTypeDef == storeBoolean){
			newNode->semTypeDef = tempNode3->semTypeDef;
		}
		else{
			newNode->semTypeDef = storeError;
		}
		(yyval) = newNode;
	}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 956 "parser.y"
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

  case 56:

/* Line 1455 of yacc.c  */
#line 967 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		(yyval) = newNode;
	}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 977 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = implication;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;  
	}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 987 "parser.y"
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

  case 59:

/* Line 1455 of yacc.c  */
#line 1005 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanTerm;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1015 "parser.y"
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

  case 61:

/* Line 1455 of yacc.c  */
#line 1033 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1043 "parser.y"
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

  case 63:

/* Line 1455 of yacc.c  */
#line 1061 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanSecondary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1071 "parser.y"
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

  case 65:

/* Line 1455 of yacc.c  */
#line 1088 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1098 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode=(yyvsp[(1) - (1)]);
		Symbol* entry = lookUp(tempNode->identLex,currentScope);
		tempNode->semTypeDef = entry->type;
		newNode->semTypeDef = tempNode->semTypeDef;
		(yyval)=newNode;
	}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1110 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval)=newNode;
	}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1120 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		Node* tempNode = (yyvsp[(1) - (3)]);  
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval)=newNode;
	}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1131 "parser.y"
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

  case 70:

/* Line 1455 of yacc.c  */
#line 1145 "parser.y"
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

  case 71:

/* Line 1455 of yacc.c  */
#line 1229 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->type = relationalOperator;
		strcpy(newNode->identLex, yytext);
		(yyval) = newNode;
	}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1238 "parser.y"
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

  case 73:

/* Line 1455 of yacc.c  */
#line 1260 "parser.y"
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

  case 75:

/* Line 1455 of yacc.c  */
#line 1281 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef = storeReal;
		(yyval) = new;

	}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1290 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeInteger;
		(yyval) = new;

		

	}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1301 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeBoolean;
		(yyval) = new;



	}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1320 "parser.y"
    {
	

	}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1328 "parser.y"
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

  case 80:

/* Line 1455 of yacc.c  */
#line 1343 "parser.y"
    {
		Node *new = createNode();
		new->type = identifier;
		strcpy(new->identLex, yytext);
		(yyval) = new;
	}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1360 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		(yyval) = new;



	
	}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1373 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		(yyval) = new;

	}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1384 "parser.y"
    {

		Node *new = createNode();
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		(yyval) = new;


	}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1400 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = conditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp->semTypeDef;
		(yyval) = new;
	}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1412 "parser.y"
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

  case 86:

/* Line 1455 of yacc.c  */
#line 1432 "parser.y"
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

  case 87:

/* Line 1455 of yacc.c  */
#line 1461 "parser.y"
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

  case 88:

/* Line 1455 of yacc.c  */
#line 1484 "parser.y"
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

  case 89:

/* Line 1455 of yacc.c  */
#line 1502 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = basicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  

		(yyval) = new;

	}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1522 "parser.y"
    {		
		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement; 
        	new->pt0 = (yyvsp[(1) - (1)]) ; 
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  
		(yyval) = new;

	}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1535 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  

		new->semTypeDef=temp->semTypeDef ;  

		(yyval) = new;

	}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1549 "parser.y"
    {
			
		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  
		(yyval) = new;

	}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1561 "parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1573 "parser.y"
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

  case 96:

/* Line 1455 of yacc.c  */
#line 1590 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = (yyvsp[(1) - (3)]);
		new->pt2 = (yyvsp[(3) - (3)]);
		(yyval) = new;
		Symbol *symbol1;	
		Node *tmp1=(yyvsp[(1) - (3)]);
		Node *tmp2=(yyvsp[(3) - (3)]);
		new->semTypeDef=storeVoid;		
  		symbol1=lookUp(tmp1->identLex,currentScope);
		if (symbol1==NULL){
			new->semTypeDef=storeError;
		}
		else{
			if (symbol1->type==storeInteger && tmp2->semTypeDef==storeInteger) {								// SYMBOL1>TYPE IS INTEGER  
				symbol1->value=tmp2->intValue;
			}
		
		}
	}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1613 "parser.y"
    {

	}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1619 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = (yyvsp[(1) - (3)]);
		new->pt2 = (yyvsp[(3) - (3)]);
		(yyval) = new;
	
		Node *temp1=(yyvsp[(1) - (3)]);
		Node *temp2=(yyvsp[(3) - (3)]);
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

  case 99:

/* Line 1455 of yacc.c  */
#line 1823 "parser.y"
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

  case 100:

/* Line 1455 of yacc.c  */
#line 1870 "parser.y"
    {	
		Node *new = createNode();         	            	  
        	new->type =empty;
		(yyval) = new;
	}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1877 "parser.y"
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

  case 102:

/* Line 1455 of yacc.c  */
#line 1907 "parser.y"
    {
		Node *new = createNode(); 
		new->type = procedureIdentifier;
		new->pt0 = (yyvsp[(1) - (1)]);
	
		Node *temp=(yyvsp[(1) - (1)]);

		(yyval) = new;
	}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1919 "parser.y"
    {
		(yyval)=(yyvsp[(2) - (3)]);
		Node *temp = (yyvsp[(2) - (3)]);
		if(temp->semTypeDef != storeError)
		{		
			temp->semTypeDef == storeVoid;
		}
		
	}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1932 "parser.y"
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

  case 105:

/* Line 1455 of yacc.c  */
#line 1946 "parser.y"
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

  case 106:

/* Line 1455 of yacc.c  */
#line 1969 "parser.y"
    {
		Node *new = createNode(); 
		Node *temp = (yyvsp[(1) - (1)]); 
		new->type = actualParameter;
		new->semTypeDef = temp->semTypeDef;
		new->pt0 = (yyvsp[(1) - (1)]);

		(yyval) = new;
	}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1982 "parser.y"
    {
		Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (3)]);
		Node *temp2=(yyvsp[(3) - (3)]);
		(yyval)=new;
	}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1990 "parser.y"
    {
		Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (3)]);
		Node *temp2=(yyvsp[(3) - (3)]);
		(yyval)=new;

	}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1999 "parser.y"
    {	Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (3)]);
		Node *temp2=(yyvsp[(3) - (3)]);
		(yyval)=new;
	}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 2006 "parser.y"
    {
		Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (3)]);
		Node *temp2=(yyvsp[(3) - (3)]);
		(yyval)=new;
	}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 2016 "parser.y"
    {
		Node* new=createNode();
		Node* temp=(yyvsp[(2) - (2)]);

		(yyval)=new;
	}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 2024 "parser.y"
    {
		Node* new=createNode();
		(yyval)=new;
	}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 2033 "parser.y"
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

  case 117:

/* Line 1455 of yacc.c  */
#line 2048 "parser.y"
    {
		(yyvsp[(1) - (2)]) = (yyvsp[(0) - (2)]);
		(yyvsp[(2) - (2)]) = (yyvsp[(0) - (2)]);
	}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 2055 "parser.y"
    {
		(yyval) = (yyvsp[(0) - (1)]);
	}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 2058 "parser.y"
    {
		(yyvsp[(1) - (1)]) = (yyvsp[(0) - (1)]);
	}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 2063 "parser.y"
    {
		Node *node1 = (yyvsp[(0) - (1)]);
		Node *node2 = (yyvsp[(1) - (1)]);
		Symbol *symbol = lookUp(node2->identLex,currentScope);
		symbol->type = node1->semTypeDef;
	}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 2069 "parser.y"
    {
		(yyvsp[(2) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 2073 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 2082 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
		Node *node1 = (yyvsp[(1) - (3)]);
	}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 2089 "parser.y"
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

  case 134:

/* Line 1455 of yacc.c  */
#line 2101 "parser.y"
    {
		(yyvsp[(3) - (4)]) = (yyvsp[(1) - (4)]);
	}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 2104 "parser.y"
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

  case 137:

/* Line 1455 of yacc.c  */
#line 2116 "parser.y"
    {
		(yyvsp[(3) - (4)]) = (yyvsp[(1) - (4)]);
	}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 2121 "parser.y"
    {
		Node *new = createNode();
		
		new->type = procedureBody;
		Node *temp = (yyvsp[(3) - (3)]);
		new->semTypeDef = temp->semTypeDef;
		(yyval) = new;
	}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 2131 "parser.y"
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

  case 142:

/* Line 1455 of yacc.c  */
#line 2149 "parser.y"
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



/* Line 1455 of yacc.c  */
#line 3973 "y.tab.c"
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
#line 2169 "parser.y"



