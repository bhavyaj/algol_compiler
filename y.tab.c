
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
//extern "C" int yylex();
//extern "C" int yyparse();
//extern "C" FILE *yyin
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
		//printf("Scope stack is empty\n");
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


/* Line 189 of yacc.c  */
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
     TOKEN_TINTEGER = 321,
     TOKEN_TREAL = 322,
     TOKEN_RETURN = 323,
     TOKEN_ASSIGN_IDENTIFIER = 324,
     TOKEN_LABEL_IDENTIFIER = 325,
     TOKEN_BOOL_IDENTIFIER = 326,
     TOKEN_ASSIGN = 327,
     TOKEN_NOT_EQUAL = 328,
     TOKEN_RELOP = 329
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
#define TOKEN_TINTEGER 321
#define TOKEN_TREAL 322
#define TOKEN_RETURN 323
#define TOKEN_ASSIGN_IDENTIFIER 324
#define TOKEN_LABEL_IDENTIFIER 325
#define TOKEN_BOOL_IDENTIFIER 326
#define TOKEN_ASSIGN 327
#define TOKEN_NOT_EQUAL 328
#define TOKEN_RELOP 329




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 396 "y.tab.c"

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
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   289

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  144
/* YYNRULES -- Number of states.  */
#define YYNSTATES  236

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   329

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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,    10,    14,    16,    19,    22,    24,
      26,    28,    30,    33,    35,    37,    40,    43,    47,    49,
      51,    53,    55,    57,    61,    63,    67,    69,    74,    78,
      80,    81,    86,    89,    93,    95,    97,    99,   104,   106,
     109,   112,   116,   120,   122,   126,   130,   132,   136,   138,
     140,   144,   146,   148,   150,   152,   157,   159,   163,   165,
     167,   169,   171,   175,   177,   181,   183,   187,   189,   193,
     195,   198,   200,   202,   206,   208,   212,   214,   216,   217,
     222,   224,   226,   228,   231,   233,   235,   237,   239,   241,
     246,   249,   252,   255,   259,   261,   264,   266,   268,   269,
     273,   275,   278,   281,   284,   295,   296,   299,   301,   303,
     307,   309,   313,   315,   317,   322,   324,   326,   328,   331,
     333,   335,   336,   341,   343,   344,   349,   351,   355,   359,
     361,   363,   366,   368,   370,   373,   375,   377,   381,   386,
     387,   388,   396,   398,   402
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      81,     0,    -1,    83,    86,    -1,    76,    64,    86,    -1,
      76,    64,    85,    -1,    77,    -1,    79,    78,    -1,    80,
      28,    -1,   108,    -1,   103,    -1,    84,    -1,    78,    -1,
       5,    85,    -1,     5,    -1,    82,    -1,    79,    84,    -1,
     142,     6,    -1,   142,    64,    85,    -1,   122,    -1,    95,
      -1,   157,    -1,    97,    -1,    97,    -1,    87,    28,    88,
      -1,    89,    -1,    90,    16,    89,    -1,   108,    -1,    91,
      23,    90,    24,    -1,    91,    16,    92,    -1,    92,    -1,
      -1,    93,    16,    94,    92,    -1,    62,    93,    -1,   121,
      62,    93,    -1,    97,    -1,   109,    -1,    98,    -1,   127,
      98,    48,    97,    -1,    99,    -1,    11,    99,    -1,    12,
      99,    -1,    98,    11,    99,    -1,    98,    12,    99,    -1,
     100,    -1,    99,    15,   100,    -1,    99,    13,   100,    -1,
     101,    -1,   100,    14,   101,    -1,   102,    -1,   103,    -1,
      21,    97,    22,    -1,    26,    -1,    27,    -1,   108,    -1,
     105,    -1,    91,    23,   106,    24,    -1,   107,    -1,   106,
      16,   107,    -1,    97,    -1,     4,    -1,   110,    -1,   111,
      -1,   110,    36,   111,    -1,   112,    -1,   111,    63,   112,
      -1,   113,    -1,   112,    38,   113,    -1,   114,    -1,   113,
      37,   114,    -1,   115,    -1,    39,   115,    -1,   116,    -1,
     117,    -1,    21,   109,    22,    -1,     7,    -1,    98,   118,
      98,    -1,    29,    -1,   123,    -1,    -1,   119,    16,   120,
     123,    -1,    67,    -1,    66,    -1,    51,    -1,   121,   119,
      -1,   108,    -1,   128,    -1,    84,    -1,    78,    -1,   126,
      -1,   127,   124,    48,   142,    -1,   127,   134,    -1,    79,
     125,    -1,   127,   124,    -1,    46,   109,    47,    -1,   129,
      -1,    80,   128,    -1,   133,    -1,   131,    -1,    -1,   136,
     130,   132,    -1,   135,    -1,    68,    96,    -1,    69,    97,
      -1,    69,   109,    -1,    41,   104,    72,    97,    44,    97,
      45,    97,    42,   142,    -1,    -1,   137,   138,    -1,   108,
      -1,   135,    -1,    21,   139,    22,    -1,   140,    -1,   139,
     141,   140,    -1,    96,    -1,    16,    -1,    24,   108,    28,
      23,    -1,   124,    -1,   125,    -1,   134,    -1,     3,    96,
      -1,   108,    -1,   143,    -1,    -1,   144,   141,   145,   143,
      -1,   135,    -1,    -1,    21,   147,   144,    22,    -1,   108,
      -1,   148,    16,   108,    -1,    50,   148,    64,    -1,   135,
      -1,   121,    -1,   121,    62,    -1,    60,    -1,    49,    -1,
     121,    10,    -1,   135,    -1,   152,    -1,   150,   148,    64,
      -1,   152,   150,   148,    64,    -1,    -1,    -1,   137,   154,
     146,    64,   155,   149,   151,    -1,   142,    -1,    10,   153,
     156,    -1,   121,    10,   153,   156,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   248,   248,   252,   262,   271,   278,   309,   312,   313,
     317,   322,   331,   336,   339,   341,   345,   353,   364,   369,
     378,   385,   402,   419,   438,   450,   471,   483,   496,   500,
     517,   516,   534,   536,   542,   552,   568,   581,   601,   612,
     615,   619,   653,   686,   698,   728,   765,   777,   802,   814,
     837,   851,   862,   873,   888,   904,   931,   947,   966,   977,
     986,  1021,  1032,  1042,  1052,  1070,  1080,  1098,  1108,  1126,
    1136,  1153,  1175,  1185,  1196,  1210,  1314,  1323,  1346,  1345,
    1366,  1375,  1386,  1405,  1413,  1428,  1442,  1453,  1468,  1480,
    1500,  1525,  1529,  1552,  1571,  1586,  1590,  1603,  1618,  1617,
    1636,  1640,  1657,  1680,  1884,  1932,  1940,  1969,  1981,  1982,
    1995,  2009,  2032,  2043,  2044,  2047,  2055,  2064,  2081,  2098,
    2113,  2114,  2114,  2121,  2124,  2124,  2129,  2135,  2139,  2142,
    2144,  2145,  2146,  2147,  2148,  2150,  2151,  2153,  2157,  2160,
    2171,  2160,  2192,  2202,  2219
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
  "TOKEN_TINTEGER", "TOKEN_TREAL", "TOKEN_RETURN",
  "TOKEN_ASSIGN_IDENTIFIER", "TOKEN_LABEL_IDENTIFIER",
  "TOKEN_BOOL_IDENTIFIER", "TOKEN_ASSIGN", "TOKEN_NOT_EQUAL",
  "TOKEN_RELOP", "$accept", "blockHead", "unlabelledBlock", "block",
  "tlabel", "label", "program", "unlabelledCompound", "tbegin",
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
  "unlabelledBasicStatement", "@3", "dummyStatement", "returnStatement",
  "assignmentStatement", "forStatement", "empty", "procedureStatement",
  "procedureIdentifier", "actualParameterPart", "actualParameterList",
  "actualParameter", "parameterDelimiter", "statement", "formalParameter",
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
     325,   326,   327,   328,   329
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    76,    77,    78,    78,    79,    80,    80,
      81,    81,    82,    83,    84,    84,    85,    85,    86,    86,
      86,    87,    88,    89,    90,    90,    91,    92,    92,    93,
      94,    93,    95,    95,    96,    96,    97,    97,    98,    98,
      98,    98,    98,    99,    99,    99,   100,   100,   101,   101,
     101,   102,   103,   104,   104,   105,   106,   106,   107,   108,
     109,   110,   110,   111,   111,   112,   112,   113,   113,   114,
     114,   115,   115,   115,   116,   117,   118,   119,   120,   119,
     121,   121,   121,   122,   123,   124,   124,   124,   125,   125,
     125,   125,   126,   127,   128,   128,   129,   129,   130,   129,
     131,   132,   133,   133,   134,   135,   136,   137,   138,   138,
     139,   139,   140,   141,   141,   142,   142,   142,   142,   143,
     144,   145,   144,   146,   147,   146,   148,   148,   149,   149,
     150,   150,   150,   150,   150,   151,   151,   152,   152,   154,
     155,   153,   156,   157,   157
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     3,     1,     2,     2,     1,     1,
       1,     1,     2,     1,     1,     2,     2,     3,     1,     1,
       1,     1,     1,     3,     1,     3,     1,     4,     3,     1,
       0,     4,     2,     3,     1,     1,     1,     4,     1,     2,
       2,     3,     3,     1,     3,     3,     1,     3,     1,     1,
       3,     1,     1,     1,     1,     4,     1,     3,     1,     1,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     1,     1,     3,     1,     3,     1,     1,     0,     4,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     4,
       2,     2,     2,     3,     1,     2,     1,     1,     0,     3,
       1,     2,     2,     2,    10,     0,     2,     1,     1,     3,
       1,     3,     1,     1,     4,     1,     1,     1,     2,     1,
       1,     0,     4,     1,     0,     4,     1,     3,     3,     1,
       1,     2,     1,     1,     2,     1,     1,     3,     4,     0,
       0,     7,     1,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    59,    13,    52,     0,     5,    11,     0,     0,     0,
      14,     0,    10,     9,     8,     0,     0,     0,     0,    87,
       0,   105,    86,    12,     8,   115,   116,    88,   105,    85,
      94,    97,    96,   117,   100,    98,   105,     0,   105,     6,
      15,     7,     1,     0,    82,     0,    81,    80,     2,    19,
       0,    18,    20,    74,     0,     0,     0,    51,     0,   118,
      34,    36,    38,    43,    46,    48,    49,    35,    60,    61,
      63,    65,    67,    69,    71,    72,     0,     0,     0,    54,
      26,     0,     0,   102,   103,    91,   105,    95,    92,    90,
       0,     0,   108,   106,    16,   105,     4,     3,   107,   139,
     105,     0,    29,    32,    26,     0,     0,    84,    83,    77,
       0,    39,    40,     0,     0,    70,     0,     0,    76,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,   105,     0,    99,   112,     0,   110,    17,   105,   142,
     143,     0,     0,    30,   105,    33,    78,    36,    50,    73,
      41,    42,    75,    45,    44,    47,    62,    64,    66,    68,
       0,    58,     0,    56,     0,    89,   101,   113,   109,     0,
       0,   124,   123,     0,    28,     0,    24,     0,    21,     0,
     144,     0,    37,     0,    55,     0,     0,   111,     0,   140,
       0,     0,    27,    31,    79,    57,     0,     0,   119,   120,
       0,   105,    23,    22,    25,     0,   114,   125,   121,     0,
     129,   105,     0,     0,   126,     0,   133,   132,   130,   135,
       0,   141,   136,   105,   122,     0,   128,   134,   131,     0,
       0,   104,   127,   137,     0,   138
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    19,    20,    21,     9,    10,    11,    22,
      23,    48,   175,   202,   176,   177,   101,   102,   103,   179,
      49,   134,    60,   147,    62,    63,    64,    65,    66,    78,
      79,   162,   163,    24,    67,    68,    69,    70,    71,    72,
      73,    74,    75,   119,   108,   181,    50,    51,   109,    25,
      26,    27,    76,    29,    30,    90,    31,   133,    32,    33,
      34,    35,    36,    93,   135,   136,   170,    37,   199,   200,
     213,   173,   188,   215,   211,   220,   221,   222,   100,   138,
     201,   140,    52
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -174
static const yytype_int16 yypact[] =
{
     155,  -174,    31,  -174,   -40,  -174,  -174,   155,    94,    28,
    -174,    89,  -174,  -174,  -174,   195,   120,   224,   195,  -174,
     149,    40,  -174,  -174,    21,  -174,  -174,  -174,    43,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,   107,     9,   134,  -174,
    -174,  -174,  -174,   120,  -174,   120,  -174,  -174,  -174,  -174,
      51,  -174,  -174,  -174,   178,   178,   195,  -174,   232,  -174,
    -174,    63,    41,   117,  -174,  -174,  -174,  -174,   112,    99,
     130,   136,  -174,  -174,  -174,  -174,   249,   154,   115,  -174,
     119,    63,   146,  -174,  -174,  -174,    13,  -174,   141,  -174,
     140,   195,  -174,  -174,  -174,    61,  -174,  -174,  -174,  -174,
      61,    36,  -174,   198,  -174,   120,   120,  -174,   199,  -174,
     206,    41,    41,   197,   201,  -174,   178,   178,  -174,   249,
     178,   178,   178,   224,   224,   224,   224,   104,   206,   206,
    -174,    61,   195,  -174,  -174,   142,  -174,  -174,   207,  -174,
    -174,   120,   206,  -174,    61,   198,  -174,   160,  -174,  -174,
      41,    41,   160,   117,   117,  -174,    99,   130,   136,  -174,
     206,  -174,    69,  -174,   185,  -174,  -174,  -174,  -174,   120,
     195,  -174,  -174,   173,  -174,   214,  -174,   170,  -174,   120,
    -174,   120,  -174,   206,  -174,   206,   218,  -174,   120,  -174,
     206,   206,  -174,  -174,  -174,  -174,   202,   225,  -174,  -174,
     250,   204,  -174,  -174,  -174,   206,  -174,  -174,  -174,   120,
    -174,   189,   215,   120,  -174,    14,  -174,  -174,    17,  -174,
     120,  -174,   189,    61,  -174,   120,  -174,  -174,  -174,    44,
     120,  -174,  -174,  -174,    46,  -174
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -174,  -174,  -174,   126,   150,    11,  -174,  -174,  -174,   163,
     -12,   226,  -174,  -174,    71,  -174,   251,  -122,   159,  -174,
    -174,    -9,     7,    -5,    26,    90,   147,  -174,     1,  -174,
    -174,  -174,    85,     0,    73,  -174,   148,   153,   156,   152,
     221,  -174,  -174,  -174,  -174,  -174,  -173,  -174,    92,   252,
     262,  -174,     3,   -17,  -174,  -174,  -174,  -174,  -174,   255,
     -27,  -174,   -29,  -174,  -174,   114,    86,   -98,    72,  -174,
    -174,  -174,  -174,  -126,  -174,    65,  -174,  -174,   183,  -174,
    -174,   145,  -174
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -108
static const yytype_int16 yytable[] =
{
      14,    13,   139,    13,    87,    28,    59,    14,    13,    92,
      61,     8,    81,    61,    99,    94,    80,     1,     8,   174,
      14,    13,    13,    28,    38,    83,    96,   227,    42,    13,
     225,     8,    86,   165,    15,     1,     2,  -105,   218,    13,
       3,    28,  -107,    98,     1,   104,   139,     1,     2,   218,
     107,    61,   141,    81,   120,     1,   121,   193,     3,   142,
     225,   105,   225,   113,    15,     1,     2,     3,    41,    87,
       3,   127,    16,    95,   116,   117,    99,    17,   226,   228,
     111,   112,    18,   137,    16,   183,    61,    13,     3,  -107,
      82,    84,   118,   184,   229,  -105,    13,    86,    28,    43,
      18,    13,    16,    28,   234,    98,   104,    17,   233,    18,
     235,   172,    18,   106,   152,   116,   117,   113,    81,    81,
      81,    81,    41,   166,     1,   231,     6,    61,    91,   114,
      18,   122,    13,    39,    28,   161,   164,    15,     1,     2,
      44,   104,   150,   151,    43,    13,    39,    28,   123,   178,
       7,    45,   160,     1,     2,    46,    47,     7,   167,     1,
       2,     3,   124,    12,   168,    61,   169,   182,   125,   186,
      40,   116,   117,   126,   210,    16,     3,   128,     7,   104,
      17,   107,     3,    40,   219,    44,   191,   129,   198,   131,
     161,   -53,   196,   130,   192,    17,    45,   203,   178,   110,
      46,    47,    53,    18,    57,     3,    54,    55,   132,   214,
     153,   154,   212,   198,   143,   146,    56,    54,    55,   148,
     214,    57,     3,   149,    13,   232,    28,   110,   171,   185,
     214,    53,    57,     3,    58,    54,    55,   189,   216,    53,
      44,    17,   190,    54,    55,    56,   197,   205,   206,   217,
      57,     3,    17,    56,   209,    46,    47,   223,    57,     3,
      54,    55,   204,    58,    97,   145,   167,    77,   195,   155,
     110,   156,   207,   194,   169,    57,     3,   157,   159,   115,
      88,   158,    85,    89,   187,   224,   208,   230,   144,   180
};

static const yytype_uint8 yycheck[] =
{
       0,     0,   100,     2,    21,     2,    15,     7,     7,    36,
      15,     0,    17,    18,    43,     6,    16,     4,     7,   141,
      20,    20,    21,    20,    64,    18,    38,    10,     0,    28,
      16,    20,    21,   131,     3,     4,     5,     6,   211,    38,
      27,    38,    21,    43,     4,    45,   144,     4,     5,   222,
      50,    56,    16,    58,    13,     4,    15,   179,    27,    23,
      16,    10,    16,    56,     3,     4,     5,    27,    28,    86,
      27,    76,    41,    64,    11,    12,   105,    46,    64,    62,
      54,    55,    69,    95,    41,    16,    91,    86,    27,    68,
      17,    18,    29,    24,   220,    64,    95,    86,    95,    10,
      69,   100,    41,   100,   230,   105,   106,    46,    64,    69,
      64,   138,    69,    62,   119,    11,    12,   110,   123,   124,
     125,   126,    28,   132,     4,   223,     0,   132,    21,    56,
      69,    14,   131,     7,   131,   128,   129,     3,     4,     5,
      51,   141,   116,   117,    10,   144,    20,   144,    36,   142,
       0,    62,    48,     4,     5,    66,    67,     7,    16,     4,
       5,    27,    63,     0,    22,   170,    24,   160,    38,   169,
       7,    11,    12,    37,   201,    41,    27,    23,    28,   179,
      46,   181,    27,    20,   211,    51,    16,    72,   188,    48,
     183,    72,   185,    47,    24,    46,    62,   190,   191,    21,
      66,    67,     7,    69,    26,    27,    11,    12,    68,   209,
     120,   121,   205,   213,    16,    16,    21,    11,    12,    22,
     220,    26,    27,    22,   223,   225,   223,    21,    21,    44,
     230,     7,    26,    27,    39,    11,    12,    64,    49,     7,
      51,    46,    28,    11,    12,    21,    28,    45,    23,    60,
      26,    27,    46,    21,    50,    66,    67,    42,    26,    27,
      11,    12,   191,    39,    38,   106,    16,    16,   183,   122,
      21,   123,    22,   181,    24,    26,    27,   124,   126,    58,
      28,   125,    20,    28,   170,   213,   200,   222,   105,   144
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    27,    76,    77,    78,    79,    80,    81,
      82,    83,    84,   103,   108,     3,    41,    46,    69,    78,
      79,    80,    84,    85,   108,   124,   125,   126,   127,   128,
     129,   131,   133,   134,   135,   136,   137,   142,    64,    78,
      84,    28,     0,    10,    51,    62,    66,    67,    86,    95,
     121,   122,   157,     7,    11,    12,    21,    26,    39,    96,
      97,    98,    99,   100,   101,   102,   103,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   127,    91,   104,   105,
     108,    98,   109,    97,   109,   125,    80,   128,   124,   134,
     130,    21,   135,   138,     6,    64,    85,    86,   108,   137,
     153,    91,    92,    93,   108,    10,    62,   108,   119,   123,
      21,    99,    99,    97,   109,   115,    11,    12,    29,   118,
      13,    15,    14,    36,    63,    38,    37,    98,    23,    72,
      47,    48,    68,   132,    96,   139,   140,    85,   154,   142,
     156,    16,    23,    16,   153,    93,    16,    98,    22,    22,
      99,    99,    98,   100,   100,   101,   111,   112,   113,   114,
      48,    97,   106,   107,    97,   142,    96,    16,    22,    24,
     141,    21,   135,   146,    92,    87,    89,    90,    97,    94,
     156,   120,    97,    16,    24,    44,   108,   140,   147,    64,
      28,    16,    24,    92,   123,   107,    97,    28,   108,   143,
     144,   155,    88,    97,    89,    45,    23,    22,   141,    50,
     135,   149,    97,   145,   108,   148,    49,    60,   121,   135,
     150,   151,   152,    42,   143,    16,    64,    10,    62,   148,
     150,   142,   108,    64,   148,    64
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
        case 2:

/* Line 1455 of yacc.c  */
#line 249 "parser.y"
    {
		printf("block");
	}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 253 "parser.y"
    {
		printf("block");
	}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 263 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode =(Node*) (yyvsp[(3) - (3)]);
		newNode->pt0 = (Node*) (yyvsp[(3) - (3)]);
		(yyval) = newNode;
	}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 272 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (1)]);
		(yyval) = newNode;
	}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 287 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(2) - (2)]);						// $2
		(yyval) = newNode;
	}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 318 "parser.y"
    {
		printf("compundStatement\n");
	}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 323 "parser.y"
    {
		printf("blockhead belu\n");
	}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 331 "parser.y"
    {
		printf("unlabelled compund belu");
	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 346 "parser.y"
    {
		printf("compound tail belu");
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (2)]);
		(yyval) = newNode;
	}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 354 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (3)]);
		(yyval) = newNode;
	}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 365 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 370 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 379 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 386 "parser.y"
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

  case 22:

/* Line 1455 of yacc.c  */
#line 403 "parser.y"
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

  case 23:

/* Line 1455 of yacc.c  */
#line 420 "parser.y"
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

  case 24:

/* Line 1455 of yacc.c  */
#line 439 "parser.y"
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

  case 25:

/* Line 1455 of yacc.c  */
#line 451 "parser.y"
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

  case 26:

/* Line 1455 of yacc.c  */
#line 472 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = arrayIdentifier;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex, tempNode->identLex);
		(yyval) = newNode;
	}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 484 "parser.y"
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

  case 29:

/* Line 1455 of yacc.c  */
#line 501 "parser.y"
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

  case 30:

/* Line 1455 of yacc.c  */
#line 517 "parser.y"
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

  case 34:

/* Line 1455 of yacc.c  */
#line 543 "parser.y"
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

/* Line 1455 of yacc.c  */
#line 553 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = expression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 569 "parser.y"
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

  case 37:

/* Line 1455 of yacc.c  */
#line 582 "parser.y"
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

  case 38:

/* Line 1455 of yacc.c  */
#line 602 "parser.y"
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

  case 39:

/* Line 1455 of yacc.c  */
#line 613 "parser.y"
    {
	}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 616 "parser.y"
    {
	}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 620 "parser.y"
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

  case 42:

/* Line 1455 of yacc.c  */
#line 654 "parser.y"
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

  case 43:

/* Line 1455 of yacc.c  */
#line 687 "parser.y"
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

  case 44:

/* Line 1455 of yacc.c  */
#line 699 "parser.y"
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

  case 45:

/* Line 1455 of yacc.c  */
#line 729 "parser.y"
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

  case 46:

/* Line 1455 of yacc.c  */
#line 766 "parser.y"
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

  case 47:

/* Line 1455 of yacc.c  */
#line 778 "parser.y"
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

  case 48:

/* Line 1455 of yacc.c  */
#line 803 "parser.y"
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

  case 49:

/* Line 1455 of yacc.c  */
#line 815 "parser.y"
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

  case 50:

/* Line 1455 of yacc.c  */
#line 838 "parser.y"
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

  case 51:

/* Line 1455 of yacc.c  */
#line 852 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = realNumber;
		newNode->realValue = atof(yytext);
		newNode->semTypeDef=storeReal;
		(yyval) = newNode;
	}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 863 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = integer;
		newNode->intValue = atoi(yytext);
		newNode->semTypeDef=storeInteger;  
		(yyval) = newNode;
	}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 874 "parser.y"
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

  case 54:

/* Line 1455 of yacc.c  */
#line 889 "parser.y"
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

  case 55:

/* Line 1455 of yacc.c  */
#line 905 "parser.y"
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

  case 56:

/* Line 1455 of yacc.c  */
#line 932 "parser.y"
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

  case 57:

/* Line 1455 of yacc.c  */
#line 948 "parser.y"
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

  case 58:

/* Line 1455 of yacc.c  */
#line 967 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = subscriptExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		(yyval) = newNode;
	}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 978 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = identifier;
		strcpy(newNode->identLex,yytext);
		(yyval) = newNode;
	}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 987 "parser.y"
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

  case 61:

/* Line 1455 of yacc.c  */
#line 1022 "parser.y"
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

  case 62:

/* Line 1455 of yacc.c  */
#line 1033 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		(yyval) = newNode;
	}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 1043 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = implication;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;  
	}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1053 "parser.y"
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

  case 65:

/* Line 1455 of yacc.c  */
#line 1071 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanTerm;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1081 "parser.y"
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

  case 67:

/* Line 1455 of yacc.c  */
#line 1099 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1109 "parser.y"
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

  case 69:

/* Line 1455 of yacc.c  */
#line 1127 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanSecondary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1137 "parser.y"
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

  case 71:

/* Line 1455 of yacc.c  */
#line 1154 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1176 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval)=newNode;
	}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1186 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		Node* tempNode = (yyvsp[(1) - (3)]);  
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval)=newNode;
	}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1197 "parser.y"
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

  case 75:

/* Line 1455 of yacc.c  */
#line 1211 "parser.y"
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

  case 76:

/* Line 1455 of yacc.c  */
#line 1315 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->type = relationalOperator;
		strcpy(newNode->identLex, yytext);
		(yyval) = newNode;
	}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1324 "parser.y"
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

  case 78:

/* Line 1455 of yacc.c  */
#line 1346 "parser.y"
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

  case 80:

/* Line 1455 of yacc.c  */
#line 1367 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef = storeReal;
		(yyval) = new;

	}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1376 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeInteger;
		(yyval) = new;

		

	}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1387 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeBoolean;
		(yyval) = new;



	}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1406 "parser.y"
    {
	

	}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1414 "parser.y"
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

  case 85:

/* Line 1455 of yacc.c  */
#line 1429 "parser.y"
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

/* Line 1455 of yacc.c  */
#line 1442 "parser.y"
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

/* Line 1455 of yacc.c  */
#line 1453 "parser.y"
    {

		Node *new = createNode();
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		(yyval) = new;


	}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1469 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = conditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp->semTypeDef;
		(yyval) = new;
	}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1481 "parser.y"
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

  case 90:

/* Line 1455 of yacc.c  */
#line 1501 "parser.y"
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

  case 92:

/* Line 1455 of yacc.c  */
#line 1530 "parser.y"
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

  case 93:

/* Line 1455 of yacc.c  */
#line 1553 "parser.y"
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

  case 94:

/* Line 1455 of yacc.c  */
#line 1571 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = basicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  

		(yyval) = new;

	}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1591 "parser.y"
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

/* Line 1455 of yacc.c  */
#line 1604 "parser.y"
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

/* Line 1455 of yacc.c  */
#line 1618 "parser.y"
    {
			
		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  
		(yyval) = new;

	}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1630 "parser.y"
    {
		(yyval) = (yyvsp[(1) - (3)]);
	}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1641 "parser.y"
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

  case 102:

/* Line 1455 of yacc.c  */
#line 1658 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = (yyvsp[(1) - (2)]);
		new->pt2 = (yyvsp[(2) - (2)]);
		(yyval) = new;
		Symbol *symbol1;	
		Node *tmp1=(yyvsp[(1) - (2)]);
		Node *tmp2=(yyvsp[(2) - (2)]);
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

  case 103:

/* Line 1455 of yacc.c  */
#line 1681 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = (yyvsp[(1) - (2)]);
		new->pt2 = (yyvsp[(2) - (2)]);
		(yyval) = new;
	
		Node *temp1=(yyvsp[(1) - (2)]);
		Node *temp2=(yyvsp[(2) - (2)]);
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

  case 104:

/* Line 1455 of yacc.c  */
#line 1885 "parser.y"
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

  case 105:

/* Line 1455 of yacc.c  */
#line 1932 "parser.y"
    {	
		printf("empty reached");
		Node *new = createNode();         	            	  
        	new->type =empty;
		(yyval) = new;
	}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1940 "parser.y"
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

  case 107:

/* Line 1455 of yacc.c  */
#line 1970 "parser.y"
    {
		Node *new = createNode(); 
		new->type = procedureIdentifier;
		new->pt0 = (yyvsp[(1) - (1)]);
	
		Node *temp=(yyvsp[(1) - (1)]);

		(yyval) = new;
	}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1983 "parser.y"
    {
		(yyval)=(yyvsp[(2) - (3)]);
		Node *temp = (yyvsp[(2) - (3)]);
		if(temp->semTypeDef != storeError)
		{		
			temp->semTypeDef == storeVoid;
		}
		
	}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1996 "parser.y"
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

  case 111:

/* Line 1455 of yacc.c  */
#line 2010 "parser.y"
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

  case 112:

/* Line 1455 of yacc.c  */
#line 2033 "parser.y"
    {
		Node *new = createNode(); 
		Node *temp = (yyvsp[(1) - (1)]); 
		new->type = actualParameter;
		new->semTypeDef = temp->semTypeDef;
		new->pt0 = (yyvsp[(1) - (1)]);

		(yyval) = new;
	}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 2048 "parser.y"
    {
		Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (1)]);
//		Node *temp2=$3;
		(yyval)=new;
	}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 2056 "parser.y"
    {
		Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (1)]);
//		Node *temp2=$3;
		(yyval)=new;

	}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 2065 "parser.y"
    {	Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (1)]);
//		Node *temp2=$3;
		(yyval)=new;
	}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 2082 "parser.y"
    {
		Node* new=createNode();
		Node* temp=(yyvsp[(2) - (2)]);

		(yyval)=new;
	}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 2099 "parser.y"
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

  case 121:

/* Line 1455 of yacc.c  */
#line 2114 "parser.y"
    {   ////check/////
		(yyvsp[(1) - (2)]) = (yyvsp[(0) - (2)]); 
		(yyvsp[(2) - (2)]) = (yyvsp[(0) - (2)]);
	}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 2121 "parser.y"
    {
		(yyval) = (yyvsp[(0) - (1)]);
	}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 2124 "parser.y"
    {
		(yyvsp[(1) - (1)]) = (yyvsp[(0) - (1)]);
	}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 2129 "parser.y"
    {
		Node *node1 = (yyvsp[(0) - (1)]);
		Node *node2 = (yyvsp[(1) - (1)]);
		Symbol *symbol = lookUp(node2->identLex,currentScope);
		symbol->type = node1->semTypeDef;
	}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 2135 "parser.y"
    {
		(yyvsp[(2) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 2139 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 2153 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
		Node *node1 = (yyvsp[(1) - (3)]);
	}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 2160 "parser.y"
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

  case 140:

/* Line 1455 of yacc.c  */
#line 2171 "parser.y"
    {
		(yyvsp[(3) - (4)]) = (yyvsp[(1) - (4)]);
	}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 2192 "parser.y"
    {
		Node *new = createNode();
		
		new->type = procedureBody;
		Node *temp = (yyvsp[(1) - (1)]);
		new->semTypeDef = temp->semTypeDef;
		(yyval) = new;
	}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 2202 "parser.y"
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

  case 144:

/* Line 1455 of yacc.c  */
#line 2220 "parser.y"
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
#line 3843 "y.tab.c"
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
#line 2240 "parser.y"

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


