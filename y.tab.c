
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

int currentGlobalOffset=0;/////check////////

int paramBelu = 0;

int scopeStack[100];
int scopeStackTop = 0;
SymbolTable symbolTable[1000];
int tempNodeScope;
int currentScope;
int currentLabel = 0;
char code[99999];
int scopeId = 0;
int tableStackTop=0;

void push(int num){
	if(scopeStackTop<100){
		scopeStack[scopeStackTop] = num;
		scopeStackTop++;
		symbolTable[scopeStackTop].parent = currentScope;
	}
	else{
		printf("Scope stack overflow\n");
	}
}

int pop(){
	if(scopeStackTop){
		scopeStackTop--;
		return scopeStack[scopeStackTop];
	}
	else{
		return -1;
	}
}

extern int yylex();

extern int lineNo ; 
int yylval;
extern char* yytext;

extern FILE *yyin;


void yyerror(const char *str)
{
        fprintf(stderr,"error: encountered on this token->%s\n",yytext);
}



Symbol* lookUp(char *lexm,int scope){
	Symbol *symbolEntry = symbolTable[scope].head;
	//symbolTableDisplay(scope);
	while(symbolEntry!=NULL){
		if(strcmp(lexm,symbolEntry->lexeme)==0){
			tempNodeScope = scope;
			return symbolEntry;
		}
		else
			symbolEntry = symbolEntry->next; 
	}
	if(scope==0){
		printf("Error in lexical scoping %d\n", scope);
		tempNodeScope = -1;
		return NULL;
	}
	else{
		return lookUp(lexm,symbolTable[scope].parent);
	}
}


Symbol* lookUpInCurrentScope(char *lexm){
	Symbol* symbolEntry = symbolTable[currentScope].head;
	while(symbolEntry != NULL){
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
	//symbolTableDisplay(currentScope);
	Symbol *symbolEntry = symbolTable[currentScope].head;
	if(symbolEntry == NULL){
		Symbol *newNodeEntry = (Symbol*)malloc(sizeof(Symbol));
		newNodeEntry->lexeme = malloc(strlen(lexm)+1);
		strcpy(newNodeEntry->lexeme, lexm);
		newNodeEntry->token = TOKEN_ID;
		symbolTable[currentScope].head = newNodeEntry;
		symbolTable[currentScope].head->next = symbolTable[currentScope].tail;
		symbolTable[currentScope].currentSymbol = symbolTable[currentScope].head;
		return newNodeEntry;
	}
	Symbol *newNodeEntry = (Symbol*)malloc(sizeof(Symbol));
	newNodeEntry->lexeme = malloc(strlen(lexm)+1);
	strcpy(newNodeEntry->lexeme, lexm);
	newNodeEntry->token = TOKEN_ID;
	symbolTable[currentScope].tail = newNodeEntry;
	symbolTable[currentScope].tail = symbolTable[currentScope].tail->next;
	symbolTable[currentScope].currentSymbol->next = newNodeEntry;
	symbolTable[currentScope].currentSymbol = newNodeEntry;
	//symbolTableDisplay(currentScope);
	return newNodeEntry;
}
void symbolTableDisplay(int scope){
	Symbol *entry = symbolTable[scope].head;
	int i;
	printf("Symbol Table Scope %d\n",scope);
	while (entry !=NULL){
		if (entry->lexeme != NULL)	
			printf("lexeme: %s\n",entry->lexeme);
		if (entry->token != NULL)	
			printf("token :%d\n",entry->token);
		if (entry->value || entry->value==0)	
			printf("value: %d\n",entry->value);
		if (entry->realValue || entry->realValue==0.0)				
		{
			printf("belu1\n");			
			printf("realValue belu: %f \n",entry->realValue);
		}
		if (entry->boolean != NULL)	
			printf("boolean: %d\n",entry->boolean); 
		if (entry->dim != NULL)	
			printf("dim: %d\n",entry->dim);
			for(i=0;i<entry->dim;i++){
				printf("lower: %d, upper: %d\n",entry->lowerBound[i],entry->upperBound[i]);
			}
		if (entry->type || entry->type==0)	
			printf("type: %d\n",entry->type);
		if (entry->offset || entry->offset==0)	
			printf("offset: %d\n",entry->offset);
		entry = entry->next;
	}
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
	if(node->dim != NULL){
		printf("Track: %d",node->dim);}
}

int getNewLabel(){
	currentLabel++;
	return currentLabel;
}

int getNewTemp(){
	symbolTable[currentScope].newTempOffset-=4;
	return symbolTable[currentScope].newTempOffset+4;
}

int yywrap()
{
        return 1;
}


/* Line 189 of yacc.c  */
#line 260 "y.tab.c"

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
     TOKEN_OPEN_CURLY_BRACKET = 280,
     TOKEN_CLOSE_CURLY_BRACKET = 281,
     TOKEN_CONTINUE = 282,
     TOKEN_REAL_NUM = 283,
     TOKEN_INTEGER = 284,
     TOKEN_COLON = 285,
     TOKEN_REL_OP = 286,
     TOKEN_LESS_EQUAL = 287,
     TOKEN_GREATER = 288,
     TOKEN_GREATER_EQUAL = 289,
     TOKEN_EQUAL = 290,
     TOKEN_LESS = 291,
     TOKEN_NOTEQUAL = 292,
     TOKEN_EQUIV = 293,
     TOKEN_AND_OP = 294,
     TOKEN_OR_OP = 295,
     TOKEN_NOT_OP = 296,
     TOKEN_GOTO = 297,
     TOKEN_FOR = 298,
     TOKEN_DO = 299,
     TOKEN_WHILE = 300,
     TOKEN_STEP = 301,
     TOKEN_UNTIL = 302,
     TOKEN_IF = 303,
     TOKEN_THEN = 304,
     TOKEN_ELSE = 305,
     TOKEN_SWITCH = 306,
     TOKEN_VALUE = 307,
     TOKEN_BOOLEAN = 308,
     TOKEN_TYPE_OWN = 309,
     TOKEN_TYPE_INTEGER = 310,
     TOKEN_TYPE_REAL = 311,
     TOKEN_TYPE_BOOLEAN = 312,
     TOKEN_TYPE_ARRAY = 313,
     TOKEN_TYPE_SWITCH = 314,
     TOKEN_TYPE_PROCEDURE = 315,
     TOKEN_TYPE_STRING = 316,
     TOKEN_TYPE_LABEL = 317,
     TOKEN_TYPE_VALUE = 318,
     TOKEN_ARRAY = 319,
     TOKEN_IMPLY = 320,
     TOKEN_SEMICOLON = 321,
     TOKEN_LTRSTRING = 322,
     TOKEN_RETURN = 323,
     TOKEN_ASSIGN_IDENTIFIER = 324,
     TOKEN_LABEL_IDENTIFIER = 325,
     TOKEN_BOOL_IDENTIFIER = 326,
     TOKEN_ASSIGN = 327,
     TOKEN_NOT_EQUAL = 328
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
#define TOKEN_OPEN_CURLY_BRACKET 280
#define TOKEN_CLOSE_CURLY_BRACKET 281
#define TOKEN_CONTINUE 282
#define TOKEN_REAL_NUM 283
#define TOKEN_INTEGER 284
#define TOKEN_COLON 285
#define TOKEN_REL_OP 286
#define TOKEN_LESS_EQUAL 287
#define TOKEN_GREATER 288
#define TOKEN_GREATER_EQUAL 289
#define TOKEN_EQUAL 290
#define TOKEN_LESS 291
#define TOKEN_NOTEQUAL 292
#define TOKEN_EQUIV 293
#define TOKEN_AND_OP 294
#define TOKEN_OR_OP 295
#define TOKEN_NOT_OP 296
#define TOKEN_GOTO 297
#define TOKEN_FOR 298
#define TOKEN_DO 299
#define TOKEN_WHILE 300
#define TOKEN_STEP 301
#define TOKEN_UNTIL 302
#define TOKEN_IF 303
#define TOKEN_THEN 304
#define TOKEN_ELSE 305
#define TOKEN_SWITCH 306
#define TOKEN_VALUE 307
#define TOKEN_BOOLEAN 308
#define TOKEN_TYPE_OWN 309
#define TOKEN_TYPE_INTEGER 310
#define TOKEN_TYPE_REAL 311
#define TOKEN_TYPE_BOOLEAN 312
#define TOKEN_TYPE_ARRAY 313
#define TOKEN_TYPE_SWITCH 314
#define TOKEN_TYPE_PROCEDURE 315
#define TOKEN_TYPE_STRING 316
#define TOKEN_TYPE_LABEL 317
#define TOKEN_TYPE_VALUE 318
#define TOKEN_ARRAY 319
#define TOKEN_IMPLY 320
#define TOKEN_SEMICOLON 321
#define TOKEN_LTRSTRING 322
#define TOKEN_RETURN 323
#define TOKEN_ASSIGN_IDENTIFIER 324
#define TOKEN_LABEL_IDENTIFIER 325
#define TOKEN_BOOL_IDENTIFIER 326
#define TOKEN_ASSIGN 327
#define TOKEN_NOT_EQUAL 328




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 448 "y.tab.c"

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
#define YYFINAL  31
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   375

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  88
/* YYNRULES -- Number of rules.  */
#define YYNRULES  157
/* YYNRULES -- Number of states.  */
#define YYNSTATES  262

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   328

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
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,    10,    14,    16,    19,    22,    24,
      26,    28,    30,    31,    34,    36,    39,    42,    46,    48,
      50,    52,    54,    56,    58,    62,    67,    69,    73,    75,
      79,    81,    86,    90,    92,    96,    99,   103,   105,   107,
     109,   111,   116,   118,   120,   124,   126,   131,   133,   135,
     138,   141,   145,   149,   151,   155,   159,   161,   165,   167,
     169,   171,   175,   177,   179,   181,   183,   185,   187,   189,
     194,   196,   200,   202,   204,   206,   208,   212,   214,   218,
     220,   224,   226,   230,   232,   235,   237,   239,   243,   245,
     249,   251,   253,   257,   259,   261,   263,   266,   268,   270,
     272,   274,   276,   280,   283,   286,   289,   293,   295,   298,
     300,   302,   304,   306,   308,   311,   315,   319,   330,   331,
     334,   336,   339,   343,   345,   349,   351,   353,   358,   361,
     363,   365,   367,   370,   372,   374,   378,   380,   381,   386,
     388,   392,   396,   398,   400,   403,   405,   407,   410,   412,
     414,   418,   423,   424,   425,   433,   435,   439
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      80,     0,    -1,     5,    85,    -1,    75,    66,    85,    -1,
      75,    66,    84,    -1,    76,    -1,    78,    77,    -1,    79,
      30,    -1,   114,    -1,   108,    -1,    83,    -1,    77,    -1,
      -1,     5,    82,    -1,    81,    -1,    78,    83,    -1,   147,
       6,    -1,   147,    66,    84,    -1,   127,    -1,    95,    -1,
      88,    -1,   161,    -1,   101,    -1,   100,    -1,    87,    16,
     100,    -1,    51,    97,    72,    87,    -1,   101,    -1,    86,
      30,    89,    -1,    90,    -1,    91,    16,    90,    -1,   114,
      -1,    92,    23,    91,    24,    -1,    92,    16,    93,    -1,
      93,    -1,    94,    16,    93,    -1,    64,    94,    -1,   126,
      64,    94,    -1,   101,    -1,   115,    -1,   100,    -1,   114,
      -1,    97,    25,   113,    26,    -1,    78,    -1,    98,    -1,
      21,   100,    22,    -1,    99,    -1,   132,    99,    50,   100,
      -1,   102,    -1,   103,    -1,    11,   103,    -1,    12,   103,
      -1,   102,    11,   103,    -1,   102,    12,   103,    -1,   104,
      -1,   103,    15,   104,    -1,   103,    13,   104,    -1,   105,
      -1,   104,    14,   105,    -1,   106,    -1,   146,    -1,   110,
      -1,    21,   101,    22,    -1,   107,    -1,   108,    -1,    28,
      -1,    29,    -1,   128,    -1,   109,    -1,   111,    -1,    92,
      23,   112,    24,    -1,   113,    -1,   112,    16,   113,    -1,
     101,    -1,     4,    -1,   116,    -1,   117,    -1,   116,    38,
     117,    -1,   118,    -1,   117,    65,   118,    -1,   119,    -1,
     118,    40,   119,    -1,   120,    -1,   119,    39,   120,    -1,
     121,    -1,    41,   121,    -1,   122,    -1,   123,    -1,    21,
     115,    22,    -1,     7,    -1,   102,   124,   102,    -1,    31,
      -1,   128,    -1,   125,    16,   128,    -1,    56,    -1,    55,
      -1,    57,    -1,   126,   125,    -1,   114,    -1,   133,    -1,
      83,    -1,    77,    -1,   131,    -1,   131,    50,   147,    -1,
     132,   138,    -1,    78,   130,    -1,   132,   129,    -1,    48,
     115,    49,    -1,   134,    -1,    78,   133,    -1,   137,    -1,
     135,    -1,   140,    -1,   136,    -1,   139,    -1,    68,    96,
      -1,   110,    72,   101,    -1,   110,    72,   115,    -1,    43,
     110,    72,   101,    46,   101,    47,   101,    44,   147,    -1,
      -1,   141,   142,    -1,   114,    -1,    21,    22,    -1,    21,
     143,    22,    -1,   144,    -1,   143,   145,   144,    -1,    96,
      -1,    16,    -1,    22,   114,    30,    21,    -1,   141,   142,
      -1,   129,    -1,   130,    -1,   138,    -1,     3,    96,    -1,
     114,    -1,   148,    -1,   149,   145,   148,    -1,   139,    -1,
      -1,    21,   151,   149,    22,    -1,   114,    -1,   152,    16,
     114,    -1,    52,   152,    66,    -1,   139,    -1,   126,    -1,
     126,    64,    -1,    62,    -1,    51,    -1,   126,    10,    -1,
     139,    -1,   156,    -1,   154,   152,    66,    -1,   156,   154,
     152,    66,    -1,    -1,    -1,   141,   158,   150,    66,   159,
     153,   155,    -1,   147,    -1,    10,   157,   160,    -1,   126,
      10,   157,   160,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   310,   310,   320,   332,   343,   353,   389,   398,   405,
     415,   429,   447,   447,   461,   470,   476,   487,   501,   509,
     517,   524,   534,   554,   555,   559,   562,   582,   605,   621,
     645,   658,   689,   723,   742,   762,   767,   775,   787,   799,
     805,   818,   821,   822,   823,   826,   827,   830,   867,   882,
     897,   915,   954,   989,  1004,  1037,  1079,  1095,  1122,  1138,
    1152,  1184,  1200,  1215,  1231,  1242,  1254,  1272,  1288,  1306,
    1349,  1369,  1391,  1406,  1424,  1462,  1476,  1494,  1507,  1528,
    1540,  1560,  1572,  1592,  1604,  1623,  1649,  1661,  1674,  1691,
    1806,  1815,  1844,  1870,  1880,  1891,  1901,  1909,  1928,  1940,
    1951,  1964,  1977,  1994,  2014,  2018,  2043,  2064,  2077,  2081,
    2092,  2106,  2120,  2130,  2134,  2152,  2190,  2401,  2442,  2450,
    2481,  2492,  2493,  2507,  2522,  2545,  2559,  2560,  2563,  2597,
    2607,  2617,  2625,  2643,  2672,  2673,  2681,  2684,  2684,  2691,
    2712,  2734,  2737,  2739,  2742,  2743,  2744,  2745,  2747,  2748,
    2750,  2755,  2762,  2775,  2762,  2784,  2796,  2820
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
  "TOKEN_CLOSE_SQUARE_BRACKET", "TOKEN_OPEN_CURLY_BRACKET",
  "TOKEN_CLOSE_CURLY_BRACKET", "TOKEN_CONTINUE", "TOKEN_REAL_NUM",
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
  "TOKEN_BOOL_IDENTIFIER", "TOKEN_ASSIGN", "TOKEN_NOT_EQUAL", "$accept",
  "blockHead", "unlabelledBlock", "block", "tlabel", "label", "program",
  "unlabelledCompound", "@1", "compoundStatement", "compoundTail",
  "declaration", "lowerBound", "switchList", "switchDeclaration",
  "upperBound", "boundPair", "boundPairList", "arrayIdentifier",
  "arraySegment", "arrayList", "arrayDeclaration", "expression",
  "switchIdentifier", "switchDesignator", "simpleDesignationalExpression",
  "designationalExpression", "arithmeticExpression",
  "simpleArithmeticExpression", "term", "factor", "primary",
  "unsignedNumber", "realNumber", "integer", "simpleVariable", "variable",
  "subscriptedVariable", "subscriptList", "subscriptExpression",
  "identifier", "booleanExpression", "simpleBoolean", "implication",
  "booleanTerm", "booleanFactor", "booleanSecondary", "booleanPrimary",
  "logicalValue", "relation", "relationalOperator", "listType", "type",
  "typeDeclaration", "varIdentifier", "unconditionalStatement",
  "conditionalStatement", "ifStatement", "ifClause", "basicStatement",
  "unlabelledBasicStatement", "dummyStatement", "returnStatement",
  "assignmentStatement", "forStatement", "empty", "procedureStatement",
  "procedureIdentifier", "actualParameterPart", "actualParameterList",
  "actualParameter", "parameterDelimiter", "functionDesignator",
  "statement", "formalParameter", "formalParameterList",
  "formalParameterPart", "$@2", "identifierList", "valuePart", "specifier",
  "specificationPart", "specificationIdentifierList", "procedureHeading",
  "@3", "$@4", "procedureBody", "procedureDeclaration", 0
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
     325,   326,   327,   328
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    76,    77,    77,    78,    79,    79,
      80,    80,    82,    81,    83,    83,    84,    84,    85,    85,
      85,    85,    86,    87,    87,    88,    89,    90,    91,    91,
      92,    93,    93,    94,    94,    95,    95,    96,    96,    96,
      97,    98,    99,    99,    99,   100,   100,   101,   102,   102,
     102,   102,   102,   103,   103,   103,   104,   104,   105,   105,
     105,   105,   106,   106,   107,   108,   109,   110,   110,   111,
     112,   112,   113,   114,   115,   116,   116,   117,   117,   118,
     118,   119,   119,   120,   120,   121,   121,   121,   122,   123,
     124,   125,   125,   126,   126,   126,   127,   128,   129,   129,
     129,   130,   130,   130,   130,   131,   132,   133,   133,   134,
     134,   134,   134,   135,   136,   137,   137,   138,   139,   140,
     141,   142,   142,   143,   143,   144,   145,   145,   146,   147,
     147,   147,   147,   148,   149,   149,   150,   151,   150,   152,
     152,   153,   153,   154,   154,   154,   154,   154,   155,   155,
     156,   156,   158,   159,   157,   160,   161,   161
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     3,     1,     2,     2,     1,     1,
       1,     1,     0,     2,     1,     2,     2,     3,     1,     1,
       1,     1,     1,     1,     3,     4,     1,     3,     1,     3,
       1,     4,     3,     1,     3,     2,     3,     1,     1,     1,
       1,     4,     1,     1,     3,     1,     4,     1,     1,     2,
       2,     3,     3,     1,     3,     3,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     1,     1,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     2,     1,     1,     3,     1,     3,
       1,     1,     3,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     3,     2,     2,     2,     3,     1,     2,     1,
       1,     1,     1,     1,     2,     3,     3,    10,     0,     2,
       1,     2,     3,     1,     3,     1,     1,     4,     2,     1,
       1,     1,     2,     1,     1,     3,     1,     0,     4,     1,
       3,     3,     1,     1,     2,     1,     1,     2,     1,     1,
       3,     4,     0,     0,     7,     1,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    73,    12,    65,     0,     5,    11,     0,     0,     0,
      14,    10,     9,     8,     0,     0,    94,    93,    95,     0,
      13,     2,    20,    19,     0,    18,    21,   118,     6,    15,
       7,     1,   120,   152,   118,     0,    40,     0,    33,    35,
      30,     0,     0,    97,    96,    91,     0,     0,     0,     0,
     100,   118,    99,     4,     3,     0,    67,     0,    68,     8,
      66,   129,   130,   101,   118,    98,   107,   110,   112,   109,
     131,   113,   111,     0,     0,   118,   155,   156,     0,     0,
       0,     0,   118,    36,     0,    88,     0,     0,     0,    64,
       0,    42,   132,     0,    43,    45,    39,    37,    47,    48,
      53,    56,    58,    62,    63,    60,    97,    38,    74,    75,
      77,    79,    81,    83,    85,    86,     0,     0,    59,     0,
      30,     0,     0,    63,    97,     0,   114,   104,   108,     0,
       0,   118,   118,   105,   103,     0,   119,    16,   118,   137,
     136,     0,     0,    25,    23,     8,    32,     0,     0,    28,
       0,    22,    47,    34,   157,    92,    49,    50,     0,     0,
       0,    84,     0,     0,     0,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,     0,   106,    72,     0,
      70,   115,   116,   102,   121,   125,     0,   123,    17,     0,
     153,     0,     0,     0,    31,    44,    61,    87,     0,    51,
      52,    89,    55,    54,    57,    76,    78,    80,    82,     0,
       0,     0,    69,   126,   122,     0,   133,   134,     0,   118,
      24,    27,    26,    29,    41,    46,     0,    71,     0,   124,
     138,     0,     0,   142,   118,     0,     0,   135,   139,     0,
     146,   145,   143,   148,     0,   154,   149,     0,   127,     0,
     141,   147,   144,     0,     0,     0,   140,   150,     0,   118,
     151,   117
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    50,    91,     8,     9,    10,    20,    52,
      53,    21,   148,   143,    22,   221,   149,   150,    55,    38,
      39,    23,   185,    93,    94,    95,    96,    97,   152,    99,
     100,   101,   102,   103,   123,    56,   105,    58,   179,   180,
     124,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     166,    44,    24,    25,    60,    61,    62,    63,   116,    65,
      66,    67,    68,    69,    70,    71,    72,   117,   136,   186,
     187,   215,   118,    74,   217,   218,   141,   189,   239,   234,
     244,   245,   246,    34,    75,   219,    77,    26
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -190
static const yytype_int16 yypact[] =
{
     176,  -190,   111,  -190,   -65,  -190,  -190,   176,   -20,    26,
    -190,  -190,  -190,  -190,    27,    27,  -190,  -190,  -190,    27,
    -190,  -190,  -190,  -190,    44,  -190,  -190,   243,  -190,  -190,
    -190,  -190,  -190,  -190,   145,   -28,  -190,   163,  -190,    37,
    -190,    27,    27,  -190,    51,  -190,   306,    27,   321,   306,
    -190,   193,  -190,  -190,  -190,    69,  -190,    58,  -190,   105,
    -190,  -190,  -190,    46,   234,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,   118,    -3,   143,  -190,  -190,   276,    27,
     344,    27,   145,    37,    27,  -190,   178,   178,   306,  -190,
     332,  -190,  -190,   144,  -190,  -190,  -190,  -190,   205,   181,
     173,  -190,  -190,  -190,   172,  -190,   345,  -190,   170,   147,
     189,   195,  -190,  -190,  -190,  -190,   108,   118,  -190,   192,
     197,   321,   205,  -190,   219,   186,  -190,  -190,  -190,   344,
     321,   145,   155,  -190,  -190,   267,  -190,  -190,   145,  -190,
    -190,   184,   276,   249,  -190,   242,  -190,   344,   245,  -190,
     103,  -190,    -6,  -190,  -190,  -190,   181,   181,   251,   254,
     259,  -190,   344,   178,   178,  -190,   344,   178,   178,   178,
     321,   321,   321,   321,   235,  -190,   344,  -190,  -190,   149,
    -190,  -190,  -190,  -190,  -190,  -190,    98,  -190,  -190,    27,
    -190,   276,   344,   344,  -190,  -190,  -190,  -190,   261,   181,
     181,    -6,   173,   173,  -190,   147,   189,   195,  -190,   276,
     244,   344,  -190,  -190,    27,   306,  -190,  -190,   136,   240,
    -190,  -190,  -190,  -190,  -190,  -190,   344,  -190,   263,  -190,
      27,    27,    27,  -190,   200,   256,   283,  -190,  -190,    -4,
    -190,  -190,    29,  -190,    27,  -190,   200,   344,  -190,    27,
    -190,  -190,  -190,    24,    27,   262,  -190,  -190,    67,   145,
    -190,  -190
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -190,  -190,  -190,    21,    25,  -190,  -190,  -190,  -190,    23,
     171,   285,  -190,  -190,  -190,  -190,   121,  -190,    19,   179,
     277,  -190,   146,   305,  -190,   206,    -8,    90,    55,     8,
     -58,   152,  -190,  -190,     9,  -190,   -14,  -190,  -190,  -140,
       0,   -19,  -190,   153,   158,   154,   157,   248,  -190,  -190,
    -190,  -190,  -189,  -190,    -7,   281,   289,  -190,   -16,   -47,
    -190,  -190,  -190,  -190,   282,   -73,  -190,    72,   224,  -190,
     137,   133,  -190,   -26,   126,  -190,  -190,  -190,  -179,  -190,
     112,  -190,  -190,   318,  -190,  -190,   287,  -190
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -121
static const yytype_int16 yytable[] =
{
      13,    27,   140,   137,   128,   163,   164,    13,    76,    12,
      30,    64,   249,    57,    32,    36,    12,    45,    64,    40,
      57,     6,   198,    11,    43,     7,    31,    59,    28,   125,
      29,     1,     7,   119,    59,    64,    12,    57,    37,   251,
     249,    32,    40,    12,    78,   242,   106,   120,     1,   106,
      57,    59,    51,    81,    41,   104,    76,   242,   104,    51,
      12,    37,   250,   138,    59,   253,    64,    84,    57,   160,
     144,   227,    28,    12,    29,   258,    51,   155,   145,    40,
     158,    40,    59,   249,    43,   128,    33,    12,   106,   132,
     257,    12,   129,   252,   156,   157,   131,   104,    37,    73,
      37,    98,   160,   122,    98,   183,    73,    51,    42,   202,
     203,   182,     1,    33,   213,    64,   145,    57,    57,   193,
     214,    14,    64,    73,    57,    12,  -120,   194,   -30,   142,
     130,    59,    59,   260,   158,   106,    73,     3,    59,   135,
      12,    12,   145,    98,   104,   122,   233,    12,    46,     1,
       2,    12,   213,    28,    73,    29,    51,   132,   230,     1,
       2,   243,    15,    51,   139,   211,    16,    17,    18,   162,
     151,   199,   200,   212,     3,    19,    98,   -97,   159,    79,
       1,     2,     1,   220,     3,    98,    80,   169,    47,   216,
      98,   145,    92,    48,   167,   126,   168,     1,     2,   147,
      12,   225,    -9,    73,    73,     3,    89,     3,   170,   145,
      73,   159,   171,    49,   228,   106,   163,   164,    12,   178,
     181,   201,     3,    49,   104,   122,   122,   122,   122,   172,
     228,   216,   238,   261,   173,   177,   165,   159,     1,     2,
    -120,    48,   -30,    64,   238,    57,    46,     1,     2,   256,
     190,   240,   178,    14,   238,    16,    17,    18,   146,    59,
     153,    49,   241,     3,   176,   191,   210,   -40,    12,   -97,
      98,     1,     3,   195,    85,   192,   196,    47,    86,    87,
       1,   197,   222,   151,    51,   209,    47,   224,    88,   184,
     226,    48,   232,   236,    15,    89,     3,   142,    16,    17,
      18,   178,    49,   247,   248,     3,   259,    19,    90,   188,
       1,    49,    54,    85,   223,    48,   235,    86,    87,    83,
      35,   204,   174,   205,    48,     1,   207,    88,    85,   206,
     208,    73,    86,    87,    89,     3,     1,   255,   161,    85,
     127,   175,   121,    86,    87,   133,   134,    90,     1,    89,
       3,   231,   229,   121,    48,    86,    87,   237,   254,    82,
      89,     3,    90,     0,     0,   147,  -120,     0,   -30,   154,
     -40,     0,    89,     3,     0,    -8
};

static const yytype_int16 yycheck[] =
{
       0,    66,    75,     6,    51,    11,    12,     7,    34,     0,
      30,    27,    16,    27,    14,    15,     7,    24,    34,    19,
      34,     0,   162,     0,    24,     0,     0,    27,     7,    48,
       7,     4,     7,    47,    34,    51,    27,    51,    19,    10,
      16,    41,    42,    34,    72,   234,    46,    47,     4,    49,
      64,    51,    27,    16,    10,    46,    82,   246,    49,    34,
      51,    42,    66,    66,    64,   244,    82,    16,    82,    88,
      78,   211,    51,    64,    51,   254,    51,    84,    78,    79,
      88,    81,    82,    16,    84,   132,    14,    78,    88,    64,
      66,    82,    23,    64,    86,    87,    50,    88,    79,    27,
      81,    46,   121,    48,    49,   131,    34,    82,    64,   167,
     168,   130,     4,    41,    16,   131,   116,   131,   132,    16,
      22,    10,   138,    51,   138,   116,    21,    24,    23,    21,
      72,   131,   132,    66,   142,   135,    64,    29,   138,    21,
     131,   132,   142,    88,   135,    90,   219,   138,     3,     4,
       5,   142,    16,   132,    82,   132,   131,   132,    22,     4,
       5,   234,    51,   138,    21,    16,    55,    56,    57,    25,
      80,   163,   164,    24,    29,    64,   121,    72,    88,    16,
       4,     5,     4,   191,    29,   130,    23,    14,    43,   189,
     135,   191,    46,    48,    13,    49,    15,     4,     5,    21,
     191,   209,    30,   131,   132,    29,    28,    29,    38,   209,
     138,   121,    65,    68,   214,   215,    11,    12,   209,   129,
     130,   166,    29,    68,   215,   170,   171,   172,   173,    40,
     230,   231,   232,   259,    39,    49,    31,   147,     4,     5,
      21,    48,    23,   259,   244,   259,     3,     4,     5,   249,
      66,    51,   162,    10,   254,    55,    56,    57,    79,   259,
      81,    68,    62,    29,    72,    16,   176,    25,   259,    72,
     215,     4,    29,    22,     7,    30,    22,    43,    11,    12,
       4,    22,   192,   193,   259,    50,    43,    26,    21,    22,
      46,    48,    52,    30,    51,    28,    29,    21,    55,    56,
      57,   211,    68,    47,    21,    29,    44,    64,    41,   138,
       4,    68,    27,     7,   193,    48,   226,    11,    12,    42,
      15,   169,   116,   170,    48,     4,   172,    21,     7,   171,
     173,   259,    11,    12,    28,    29,     4,   247,    90,     7,
      51,   117,    21,    11,    12,    64,    64,    41,     4,    28,
      29,   218,   215,    21,    48,    11,    12,   231,   246,    41,
      28,    29,    41,    -1,    -1,    21,    21,    -1,    23,    82,
      25,    -1,    28,    29,    -1,    30
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    29,    75,    76,    77,    78,    79,    80,
      81,    83,   108,   114,    10,    51,    55,    56,    57,    64,
      82,    85,    88,    95,   126,   127,   161,    66,    77,    83,
      30,     0,   114,   141,   157,    97,   114,    92,    93,    94,
     114,    10,    64,   114,   125,   128,     3,    43,    48,    68,
      77,    78,    83,    84,    85,    92,   109,   110,   111,   114,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   147,   158,   147,   160,    72,    16,
      23,    16,   157,    94,    16,     7,    11,    12,    21,    28,
      41,    78,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   110,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   132,   141,   146,   110,
     114,    21,   102,   108,   114,   115,    96,   130,   133,    23,
      72,    50,    78,   129,   138,    21,   142,     6,    66,    21,
     139,   150,    21,    87,   100,   114,    93,    21,    86,    90,
      91,   101,   102,    93,   160,   128,   103,   103,   100,   101,
     115,   121,    25,    11,    12,    31,   124,    13,    15,    14,
      38,    65,    40,    39,    99,   142,    72,    49,   101,   112,
     113,   101,   115,   147,    22,    96,   143,   144,    84,   151,
      66,    16,    30,    16,    24,    22,    22,    22,   113,   103,
     103,   102,   104,   104,   105,   117,   118,   119,   120,    50,
     101,    16,    24,    16,    22,   145,   114,   148,   149,   159,
     100,    89,   101,    90,    26,   100,    46,   113,   114,   144,
      22,   145,    52,   139,   153,   101,    30,   148,   114,   152,
      51,    62,   126,   139,   154,   155,   156,    47,    21,    16,
      66,    10,    64,   152,   154,   101,   114,    66,   152,    44,
      66,   147
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
#line 311 "parser.y"
    {
		currentScope = scopeStack[scopeStackTop-1];
		printf("current Scope = %d\n",currentScope);
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(2) - (2)]);
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;
		printf("blockHead\n");
	}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 321 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode1 = (yyvsp[(1) - (3)]);
		Node* tempNode2 = (yyvsp[(3) - (3)]);
		sprintf(newNode->code,"%s%s",tempNode1->code,tempNode2->code);
		(yyval)=newNode;
		printf("blockHead\n");
	}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 333 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode1 = (yyvsp[(1) - (3)]);
		Node* tempNode2 = (yyvsp[(3) - (3)]);
		newNode->pt0 = (yyvsp[(3) - (3)]);
		sprintf(newNode->code,"%s%s",tempNode1->code,tempNode2->code);
		(yyval) = newNode;
	}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 344 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		sprintf(newNode->code,tempNode->code);
		(yyval) = newNode;
		printf("unlabelled block\n");
	}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 362 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(2) - (2)]);
		Node* tempNode2 = (yyvsp[(2) - (2)]);
		Node* tempNode1 = (yyvsp[(1) - (2)]);
		strcpy(newNode->identLex,tempNode1->identLex);
		sprintf(newNode->code,"%s:\n%s", tempNode1->identLex, tempNode2->code);
		(yyval) = newNode;
		printf("labelled block\n");
	}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 390 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (2)]);
		strcpy(newNode->identLex,tempNode->identLex);
		(yyval)=newNode;
	}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 399 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex,tempNode->identLex);
		(yyval)=newNode;
	}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 406 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex,atoi(tempNode->intValue));
		(yyval)=newNode;
	}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 416 "parser.y"
    {
		printf("compoundStatement\n");
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);
		strcpy(code,newNode->code);
		int i;
		for(i=0; i <= globalLevel; i++){
			symbolTableDisplay(i);
		}
		(yyval)=newNode;
	}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 430 "parser.y"
    {
		printf("block\n");
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);
		strcpy(code,newNode->code);
		int i;
		for(i=0; i <= globalLevel; i++){
			symbolTableDisplay(i);
		}
		(yyval)=newNode;
	}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 447 "parser.y"
    {
		currentScope = scopeStack[scopeStackTop-1];
		printf("current Scope = %d\n",currentScope);
	}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 451 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(2) - (2)]);
		strcpy(newNode->code,tempNode->code);
		printf("unlabelled compound\n");
		(yyval)=newNode;	
	}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 462 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);
		printf("cmpndStatement->unlabelledCompnd\n");
		(yyval)=newNode;	
	}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 470 "parser.y"
    {			/////check/////
		printf("labelled compoundstatement\n");
	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 477 "parser.y"
    {
		printf("compound tail -> statement\n");
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (2)]);
		Node* tempNode = (yyvsp[(1) - (2)]);
		strcpy(newNode->code, tempNode->code);
		currentScope = scopeStack[scopeStackTop-1];
		(yyval) = newNode;
	}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 488 "parser.y"
    {	printf("compound tail -> statement compound tail\n "); 
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (3)]);
		Node* tempNode1=(yyvsp[(1) - (3)]);
		Node* tempNode2=(yyvsp[(3) - (3)]);
		sprintf(newNode->code,"%s%s",tempNode1->code,tempNode2->code);
		(yyval) = newNode;
	}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 502 "parser.y"
    {
		Node* newNode = createNode();
		//Node* tempNode = $1;
		strcpy(newNode->code,"");
		(yyval)=newNode;
	}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 510 "parser.y"
    {
		Node* newNode = createNode();
		//Node* tempNode = $1;
		strcpy(newNode->code,"");
		(yyval)=newNode;
	}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 517 "parser.y"
    {
		Node* newNode = createNode();
		//Node* tempNode = $1;
		strcpy(newNode->code,"");
		(yyval)=newNode;
	}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 525 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;
	}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 535 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = lowerBound;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		newNode->place = tempNode->place;
		strcpy(newNode->code,tempNode->code);
		if(tempNode->semTypeDef==storeInteger){
			newNode->semTypeDef = storeInteger;
			newNode->intValue = tempNode->intValue;
		}
		else{
			printf("error in array declaration-> lowerbound should be integer\n");
		}
		(yyval)=newNode;
		printf("lowerBound->arithmeticExpression\n");
	}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 563 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = upperBound;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		newNode->place = tempNode->place;
		strcpy(newNode->code,tempNode->code);
		if(tempNode->semTypeDef==storeInteger){
			newNode->semTypeDef = storeInteger;
			newNode->intValue = tempNode->intValue;
		}
		else{
			printf("error in array declaration-> lowerbound should be integer\n");
		}
		(yyval)=newNode;
		printf("upperBound->arithmeticExpression\n");
	}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 583 "parser.y"
    {
		Node* newNode = createNode();         	  
    	newNode->type = boundPair;
    	newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNodeOne = (yyvsp[(1) - (3)]);
		Node* tempNodeTwo = (yyvsp[(3) - (3)]);
		
		if (tempNodeOne->semTypeDef==storeInteger && tempNodeTwo->semTypeDef==storeInteger && tempNodeOne->intValue <= tempNodeTwo->intValue){
			newNode->semTypeDef=storeBoundPairList;
			sprintf(newNode->code,"%s%s",tempNodeOne->code,tempNodeTwo->code);
			newNode->lowerBound[0] = tempNodeOne->intValue;
			newNode->upperBound[0] = tempNodeTwo->intValue;
		}
		else {
			
		}
		(yyval) = newNode;
		printf("boundPair->lowerBound : upperBound\n");
	}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 606 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boundPairList;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		if (tempNode->semTypeDef==storeBoundPairList) {  
			newNode->semTypeDef=tempNode->semTypeDef;
			newNode->dim = 1;
			newNode->lowerBound[newNode->dim-1] = tempNode->lowerBound[0];
			newNode->upperBound[newNode->dim-1] = tempNode->upperBound[0];
		}
		(yyval) = newNode;
		printf("boundPairList->boundPair\n");
	}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 622 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boundPairList;
        newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNodeOne = (yyvsp[(1) - (3)]);
		Node* tempNodeTwo = (yyvsp[(3) - (3)]);
	
		if (tempNodeOne->semTypeDef==storeBoundPairList && tempNodeTwo->semTypeDef==storeBoundPairList ){
			newNode->semTypeDef=storeBoundPairList;
			newNode->dim = tempNodeOne->dim + 1 ;
			newNode->lowerBound[newNode->dim-1] = tempNodeTwo->lowerBound[0];
			newNode->upperBound[newNode->dim-1] = tempNodeTwo->upperBound[0]; 	
		}
		else {
			printf("error in boundpairlist semantic type definition\n");			
		}
		
		(yyval) = newNode;
		printf("boundPairList->boundPairList , boundPair\n");
	}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 646 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = arrayIdentifier;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex, tempNode->identLex);
		(yyval) = newNode;
		printf("arrayIdentifier->identifier\n");
	}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 659 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boundPair;
		newNode->pt0 = (yyvsp[(1) - (4)]);
		newNode->pt2 = (yyvsp[(3) - (4)]);
		Node *tempNodeOne = (yyvsp[(1) - (4)]);
		Node *tempNodeTwo = (yyvsp[(3) - (4)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* entry = lookUpInCurrentScope(tempNodeOne->identLex);
		if(entry==NULL){
			entry = addEntry(tempNodeOne->identLex);			
		}
		int size =1;
		entry->dim = tempNodeTwo->dim;
		newNode->dim = tempNodeTwo->dim;
		int i;
		for(i=0;i<tempNodeTwo->dim;i++){
			entry->lowerBound[i] = tempNodeTwo->lowerBound[i];
			entry->upperBound[i] = tempNodeTwo->upperBound[i];
			newNode->lowerBound[i] = tempNodeTwo->lowerBound[i];
			newNode->upperBound[i] = tempNodeTwo->upperBound[i];
			size = size*(tempNodeTwo->upperBound[i]-tempNodeTwo->lowerBound[i]+1);
		}
		entry->offset = symbolTable[currentScope].arrayOffset;
		symbolTable[currentScope].arrayOffset-=size*4;
		newNode->identLex = tempNodeOne->identLex;
		
		(yyval) = newNode;
		printf("arraySegment->arrayIdentifier [ boundPairList ]\n");
	}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 690 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boundPair;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node *tempNodeOne = (yyvsp[(1) - (3)]);
		Node *tempNodeTwo = (yyvsp[(3) - (3)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* entry = lookUpInCurrentScope(tempNodeOne->identLex);
		if(entry==NULL){
			entry = addEntry(tempNodeOne->identLex);			
		}
		int size =1;
		entry->dim = tempNodeTwo->dim;
		newNode->dim = tempNodeTwo->dim;
		int i;
		for(i=0;i<tempNodeTwo->dim;i++){
			entry->lowerBound[i] = tempNodeTwo->lowerBound[i];
			entry->upperBound[i] = tempNodeTwo->upperBound[i];
			newNode->lowerBound[i] = tempNodeTwo->lowerBound[i];
			newNode->upperBound[i] = tempNodeTwo->upperBound[i];
			size = size*(tempNodeTwo->upperBound[i]-tempNodeTwo->lowerBound[i]+1);
		}
		entry->offset = symbolTable[currentScope].arrayOffset;
		symbolTable[currentScope].arrayOffset-=size*4;
		newNode->identLex = tempNodeOne->identLex;
		
		(yyval) = newNode;
		printf("arraySegment->arrayIdentifier [ boundPairList ]\n");
	}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 724 "parser.y"
    {
		Node* tempNode0=(yyvsp[(0) - (1)]);
		Node* tempNode1=(yyvsp[(1) - (1)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbolEntry=lookUpInCurrentScope(tempNode1->identLex);
		if (symbolEntry!=NULL){
			symbolTable[currentScope].currentSymbol->type=tempNode1->semTypeDef;//return 0;
		}
		else{
			symbolEntry = addEntry(tempNode1->identLex);
			symbolTable[currentScope].currentSymbol->type=tempNode1->semTypeDef;
			symbolTable[currentScope].currentSymbol->dim=tempNode1->dim;
			
		}
		(yyval)=(yyvsp[(0) - (1)]); ////check////
		printf("arrayList->arraySegment\n");
	}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 743 "parser.y"
    {
		Node* tempNode0=(yyvsp[(1) - (3)]);
		Node* tempNode1=(yyvsp[(3) - (3)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbolEntry=lookUpInCurrentScope(tempNode1->identLex);
		if (symbolEntry!=NULL){
			symbolTable[currentScope].currentSymbol->type=tempNode1->semTypeDef;//return 0;
		}
		else{
			symbolEntry = addEntry(tempNode1->identLex);
			symbolTable[currentScope].currentSymbol->type=tempNode1->semTypeDef;
			symbolTable[currentScope].currentSymbol->dim=tempNode1->dim;
		}
		(yyval)=(yyvsp[(0) - (3)]); ////check////
		printf("arrayList->arrayList , arraySegment\n");
	}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 763 "parser.y"
    {
		//$$=$2;
	}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 768 "parser.y"
    {printf("here\n");
		//$$=$3;
	}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 776 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = expression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
	}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 788 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = expression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
	}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 800 "parser.y"
    {
				
	}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 805 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type= switchIdentifier;
		newNode->pt0=(yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex,tempNode->identLex);

		(yyval)=newNode;
		printf("switchIdent->Identifier\n");
	}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 831 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = arithmeticExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		//remember to check type
		newNode->realValue = tempNode->realValue;
		newNode->intValue = tempNode->intValue;
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->place = tempNode->place;
		strcpy(newNode->code,tempNode->code);
		printf("arithmetic->simplearithmetic, intval = %d,realval=%f\n",newNode->intValue,newNode->realValue);		
		(yyval) = newNode;
	}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 868 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = simpleArithmeticExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef ;
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
		printf("simplearithmetic->term, intval = %d\n",newNode->intValue);
		
	}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 883 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = simpleArithmeticExpression;
		newNode->pt0 = (yyvsp[(2) - (2)]);
		Node* tempNode = (Node*)(yyvsp[(2) - (2)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef ;
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
		printf("simplearithmetic->term, intval = %d\n",newNode->intValue);

	}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 898 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = simpleArithmeticExpression;
		newNode->pt0 = (yyvsp[(2) - (2)]);
		Node* tempNode = (Node*)(yyvsp[(2) - (2)]);
		newNode->intValue = 0-tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef ;
		newNode->place=getNewTemp();
		//strcpy(newNode->code,tempNode->code);
		sprintf(newNode->code,"%s\nli\t$t0,0\nlw\t$t1,%d($sp)\nsub\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",tempNode->code,tempNode->place,newNode->place);
		(yyval) = newNode;
		printf("simplearithmetic->term, intval = %d\n",newNode->intValue);

	}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 916 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt1 = (yyvsp[(2) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode0 = (Node*)(yyvsp[(1) - (3)]);
		Node* tempNode1 = (Node*)(yyvsp[(2) - (3)]);
		Node* tempNode2 = (Node*)(yyvsp[(3) - (3)]);

		  
		if (tempNode0->semTypeDef==storeReal  || tempNode2->semTypeDef==storeReal)
		{			
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
			printf("tempnoderealval: %f\n",tempNode2->realValue);		
		}
		else {  			
			newNode->semTypeDef = storeInteger ;  
			newNode->intValue = tempNode0->intValue  +  tempNode2->intValue ;
			//newNode->place=getNewTemp(); 
			sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nadd\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",tempNode0->code,tempNode2->code,tempNode0->place,tempNode2->place,tempNode0->place);
			newNode->place=tempNode0->place;
		}
		printf("simplearithmetic->simplearithmetic + term, realval = %f\n",newNode->realValue);
		(yyval) = newNode;
	}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 955 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt1 = (yyvsp[(2) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode0 = (Node*)(yyvsp[(1) - (3)]);
		Node* tempNode1 = (Node*)(yyvsp[(2) - (3)]);
		Node* tempNode2 = (Node*)(yyvsp[(3) - (3)]);
		  
		if (tempNode0->semTypeDef==storeReal  || tempNode2->semTypeDef==storeReal) {  
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
			newNode->intValue = tempNode0->intValue - tempNode2->intValue ; 
			//newNode->place=getNewTemp(); 
			sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nsub\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",tempNode0->code,tempNode2->code,tempNode0->place,tempNode2->place,tempNode0->place);
			newNode->place=tempNode0->place;
		}
		(yyval) = newNode;
	}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 990 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		printf("term->factor, intval = %d\n",newNode->intValue);
		(yyval) = newNode;
	}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1005 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt1 = (yyvsp[(2) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode0 = (Node*)(yyvsp[(1) - (3)]);
		Node* tempNode1 = (Node*)(yyvsp[(2) - (3)]);
		Node* tempNode2 = (Node*)(yyvsp[(3) - (3)]);
		
			if (tempNode0->semTypeDef==storeReal  || tempNode2->semTypeDef==storeReal) {  
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
					//newNode->place=getNewTemp;
					sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nmult\t$t0,$t1\nmflo\t$t0\nsw\t$t0,%d($sp)\n",tempNode0->code,tempNode2->code,tempNode0->place,tempNode2->place,tempNode0->place);
				}
				newNode->place=tempNode0->place;
				(yyval) = newNode;
		}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 1038 "parser.y"
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
				else {
					newNode->intValue = tempNode0->intValue/tempNode2->intValue;
					//newNode->place=getNewTemp();
					sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\ndiv\t$t0,$t1\nmflo\t$t1\nsw\t$t1,%d($sp)\n",tempNode0->code, tempNode2->code, tempNode0->place, tempNode2->place, tempNode0->place);
					newNode->place=tempNode0->place;
				}
			}
			(yyval) = newNode;
		//}
		
	}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 1080 "parser.y"
    {
		Node* newNode = createNode();
		
		newNode->type = factor;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef ; 
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code); 
		printf("factor->primary, intval = %d\n",newNode->intValue);
		(yyval) = newNode;
	}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 1096 "parser.y"
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

  case 58:

/* Line 1455 of yacc.c  */
#line 1123 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
		printf("primary->unsignedNumber");	
	
	}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 1138 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
		printf("primary->unsignedNumber");
	}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1153 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (Node*)(yyvsp[(1) - (1)]);
		printf("primary->variable, int value=%d\n",newNode->intValue);
// do type checking and proper lookup
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* foundEntry = lookUp(tempNode->identLex,currentScope);
		if (foundEntry)
		{	
			newNode->intValue =  foundEntry->value;
			newNode->realValue = foundEntry->realValue;		
			newNode->semTypeDef= foundEntry->type ;
			newNode->place=getNewTemp();
			int offset;
			if (tempNode->isArray == 1){
				offset = tempNode->place;
			}
			else{
				offset = foundEntry->offset;
			}
			sprintf(newNode->code,"%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",tempNode->code,offset,newNode->place);	
		}
		else
			printf("error belu\n");		
		(yyval) = newNode;

		
	}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 1185 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = primary;
		newNode->pt1 = (yyvsp[(2) - (3)]);
		Node *tempNode = (Node*)(yyvsp[(2) - (3)]);  
		newNode->intValue = tempNode->intValue;
		newNode->realValue=tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
	}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1201 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = unsignedNumber;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=storeReal;
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
		printf("unsignedNumber->real, realval = %f\n",newNode->realValue);	
	}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 1216 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->type = unsignedNumber;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=storeInteger;
		newNode->place=getNewTemp();
		sprintf(newNode->code,"li\t$t0,%d\nsw\t$t0,%d($sp)\n",newNode->intValue,newNode->place);
		(yyval) = newNode;
		printf("unsignedNumber->integer, intval = %d\n",newNode->intValue);
	}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1232 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = realNumber;
		newNode->realValue = atof(yytext);
		newNode->semTypeDef=storeReal;
		(yyval) = newNode;
	}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1243 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = integer;
		newNode->intValue = atoi(yytext);
		printf("integer-> TOKEN_INTEGER %d\n",newNode->intValue);
		newNode->semTypeDef=storeInteger;  
		(yyval) = newNode;
	}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1255 "parser.y"
    {	
		Node *new = createNode();		
		new->type = simpleVariable;
		new->pt0 = (yyvsp[(1) - (1)]);
		Node* temp = (Node*)(yyvsp[(1) - (1)]);			
		new->realValue=temp->realValue;		
		new->intValue=temp->intValue;
		new->boolValue=temp->boolValue;
		new->semTypeDef=temp->semTypeDef;
		strcpy(new->identLex, temp->identLex);
		new->place=temp->place;
		strcpy(new->code,temp->code);
		printf("simplevariable->varIdentifier");			
		(yyval) = new;
	}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1273 "parser.y"
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
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
	}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1289 "parser.y"
    {
		Node *newNode = createNode();
		newNode->isArray = 1;
		newNode->type = variable;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->boolValue = tempNode->boolValue;
		newNode->intValue = tempNode->intValue;
		newNode->realValue=tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place = tempNode->place;
		strcpy(newNode->code,tempNode->code);
		strcpy(newNode->identLex, tempNode->identLex);
		(yyval) = newNode;
	}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1307 "parser.y"
    {
		Node* newNode = createNode();
		               	  
		newNode->type = subscriptedVariable;
		newNode->pt0 = (yyvsp[(1) - (4)]);
		newNode->pt2 = (yyvsp[(3) - (4)]);
		Node* tempNode0 = (yyvsp[(1) - (4)]);
		Node* tempNode1 = (yyvsp[(3) - (4)]);
		//newNode->place = getNewTemp();
		strcpy(newNode->identLex, tempNode0->identLex);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* foundEntry = lookUp(tempNode0->identLex,currentScope);
		if(foundEntry==NULL)
		{
			newNode->semTypeDef = storeError;
		}
		else
		{	
			if(tempNode1->semTypeDef == storeInteger){		
				newNode->semTypeDef = foundEntry->type;
				int offset = foundEntry->offset-tempNode1->lowerBound[tempNode1->dim-1]*4;
				int i=0;
				for(i=foundEntry->dim-1;i>0;i--){
					if(tempNode1->lowerBound[i-1] <= foundEntry->upperBound[i-1] && tempNode1->lowerBound[i-1] >= foundEntry->lowerBound[i-1]){
						offset-=(foundEntry->upperBound[i]-foundEntry->lowerBound[i])*4*tempNode1->lowerBound[i-1];
					}
					else{
						printf("array dimension is out of range\n");
					}
				}
				newNode->place = offset;
				//sprintf(newNode->code, "%sli\t$t0,%d\nsw\t$t0,%d($sp)\n",offset, newNode->place);
				strcpy(newNode->code,tempNode1->code);
			}
		
		
		}	
		(yyval) = newNode;
	}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1350 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = subscriptList;
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		newNode->place = tempNode->place;
		strcpy(newNode->code,tempNode->code);
		if(tempNode->semTypeDef==storeInteger){
			newNode->semTypeDef = tempNode->semTypeDef;
			newNode->dim = 1;
			newNode->lowerBound[newNode->dim-1] = tempNode->intValue;
		}
		else {
			newNode->semTypeDef = storeError;
		}
		(yyval) = newNode;
	}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1370 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = subscriptList;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt1 = (yyvsp[(3) - (3)]);
		Node* tempNode1 = (yyvsp[(1) - (3)]);
		Node* tempNode2 = (yyvsp[(3) - (3)]);
		newNode->semTypeDef = tempNode2->semTypeDef;
		sprintf(newNode->code,"%s%s",tempNode1->code,tempNode2->code);
		if(tempNode2->semTypeDef == storeInteger){
			newNode->semTypeDef = tempNode2->semTypeDef;
			newNode->dim = tempNode1->dim+1;
			newNode->lowerBound[newNode->dim-1] = tempNode2->intValue;
		}
		else {
			newNode->semTypeDef = storeError;
		}
		(yyval) = newNode;
	}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1392 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = subscriptExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->intValue = tempNode->intValue;
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
		printf("subscriptedExpression->arithmeticExpression\n");
	}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1407 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = identifier;
		printf("yytext: %s\n",yytext);
		strcpy(newNode->identLex,yytext);
		currentScope = scopeStack[scopeStackTop-1];
		//Symbol* symbol = lookUp(newNode->identLex, currentScope);
		//if(symbol==NULL){
		//	printf("entry not declared \n");
		//}
		//newNode->semTypeDef = symbol->type;
		sprintf(newNode->code,"");
		printf("TOKEN_IDENTIFIER\n");		
		(yyval) = newNode;
	}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1425 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		if(tempNode->semTypeDef == storeBoolean){
			newNode->semTypeDef = tempNode->semTypeDef;
		}
		else{
			newNode->semTypeDef = storeError;
		}
		(yyval) = newNode;
		printf("booleanExpression->simpleBoolean\n");
	}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1463 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->boolValue = tempNode->boolValue;
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
		printf("simpleBoolean->implication\n");
	}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1477 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode1 = (yyvsp[(1) - (3)]);
		Node* tempNode2 = (yyvsp[(3) - (3)]);
		int label1 = getNewLabel;
		int label2 = getNewLabel;
		sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nbeq\t$t0,$t1,label%d\nli\t$t2,0\nb\tlabel%d\nlabel%d:\nli\t$t2,1\nlabel%d:\nsw\t$t2,%d($sp)\n",tempNode1->code,tempNode2->code,tempNode1->place,tempNode2->place,label1,label2,label1,label2,tempNode1->place);
		newNode->place = tempNode1->place;

		(yyval) = newNode;
		printf("simpleBoolean->simple = implication\n");
	}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1495 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = implication;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		(yyval) = newNode;  
		printf("implication->booleanterm\n");
	}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1508 "parser.y"
    {
		Node *newNode = createNode();         		
		newNode->type = implication;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode1 = (yyvsp[(1) - (3)]);
		Node* tempNode2 = (yyvsp[(3) - (3)]);
		int label1=getNewLabel();
		int label2=getNewLabel();
		if (tempNode1->semTypeDef==storeBoolean && tempNode2->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean ;
		}
		else {  
			newNode->semTypeDef=storeError;
		}
		(yyval) = newNode; 
		
	}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1529 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanTerm;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 1541 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode1 = (Node*)(yyvsp[(1) - (3)]);
		Node* tempNode2 = (Node*)(yyvsp[(3) - (3)]);
		sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nor\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",tempNode1->code,tempNode2->code,tempNode1->place,tempNode2->place, tempNode1->place);
		newNode->place = tempNode1->place;
		if (tempNode1->semTypeDef==storeBoolean && tempNode2->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean;	
		}
		else {
			newNode->semTypeDef=storeError ;  
		}
		(yyval) = newNode;  
	}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1561 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		(yyval) = newNode;
	}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1573 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode1 = (Node*)(yyvsp[(1) - (3)]);
		Node* tempNode2 = (Node*)(yyvsp[(3) - (3)]);
		sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nand\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",tempNode1->code,tempNode2->code,tempNode1->place,tempNode2->place, tempNode1->place);
		newNode->place = tempNode1->place;
		if (tempNode1->semTypeDef==storeBoolean && tempNode2->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean ;  
		}
		else {  
			newNode->semTypeDef=storeError ;  
		}
		(yyval) = newNode;  
	}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1593 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanSecondary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		(yyval) = newNode;
	}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1605 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanSecondary;
		newNode->pt1 = (yyvsp[(2) - (2)]);
		Node* tempNode = (yyvsp[(2) - (2)]);
		newNode->place = getNewTemp();
		sprintf(newNode->code,"%sli\t$t0,1\nlw\t$t1,%d($sp)\nsub\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",tempNode->code,tempNode->place,newNode->place);
		if (tempNode->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean ;  
		}
		else {  
			newNode->semTypeDef=storeError ;  
		}
		(yyval) = newNode;
	}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1624 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		(yyval) = newNode;
		
	}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1650 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		(yyval)=newNode;
	}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1662 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(2) - (3)]);
		Node* tempNode = (yyvsp[(2) - (3)]);  
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		(yyval)=newNode;
	}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1675 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = logicalValue;
		newNode->type = getNewTemp();
		if (strcmp("true",yytext)==0){
			newNode->boolValue = true;
			sprintf(newNode->code,"li\t$t0,1\nsw\t$t0,%d($sp)\n",newNode->place);
		}
		else{
			newNode->boolValue = false;
			sprintf(newNode->code,"li\t$t0,0\nsw\t$t0,%d($sp)\n",newNode->place);
		}
		(yyval) = newNode;
	}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1692 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = relation;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt1 = (yyvsp[(2) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNode0 = (yyvsp[(1) - (3)]);
		Node* tempNode1 = (yyvsp[(2) - (3)]);
		Node* tempNode2 = (yyvsp[(3) - (3)]);
		newNode->place = getNewTemp();
		int label1 = getNewLabel();
		int label2 = getNewLabel();
		if(strcmp(tempNode1->identLex,">") == 0) 
		{
			sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nbgt\t$t0,$t1,label%d\nli\t$t3,0\nsw\t$t3,%d($sp)\nb\tlabel%d\nlabel%d:\nli\t$t4,1\nsw\t$t4,%d($sp)\nlabel%d:\n",tempNode0->code,tempNode2->code,tempNode0->place,tempNode2->place,label1,newNode->place,label2,label1,newNode->place,label2);
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
		{
			sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nblt\t$t0,$t1,label%d\nli\t$t3,0\nsw\t$t3,%d($sp)\nb\tlabel%d\nlabel%d:\nli\t$t4,1\nsw\t$t4,%d($sp)\nlabel%d:\n",tempNode0->code,tempNode2->code,tempNode0->place,tempNode2->place,label1,newNode->place,label2,label1,newNode->place,label2);
			if(tempNode0->intValue < tempNode2->intValue)
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
			sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nble\t$t0,$t1,label%d\nli\t$t3,0\nsw\t$t3,%d($sp)\nb\tlabel%d\nlabel%d:\nli\t$t4,1\nsw\t$t4,%d($sp)\nlabel%d:\n",tempNode0->code,tempNode2->code,tempNode0->place,tempNode2->place,label1,newNode->place,label2,label1,newNode->place,label2);
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
			sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nbge\t$t0,$t1,label%d\nli\t$t3,0\nsw\t$t3,%d($sp)\nb\tlabel%d\nlabel%d:\nli\t$t4,1\nsw\t$t4,%d($sp)\nlabel%d:\n",tempNode0->code,tempNode2->code,tempNode0->place,tempNode2->place,label1,newNode->place,label2,label1,newNode->place,label2);
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
			sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nbne\t$t0,$t1,label%d\nli\t$t3,0\nsw\t$t3,%d($sp)\nb\tlabel%d\nlabel%d:\nli\t$t4,1\nsw\t$t4,%d($sp)\nlabel%d:\n",tempNode0->code,tempNode2->code,tempNode0->place,tempNode2->place,label1,newNode->place,label2,label1,newNode->place,label2);
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
			sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nbeq\t$t0,$t1,label%d\nli\t$t3,0\nsw\t$t3,%d($sp)\nb\tlabel%d\nlabel%d:\nli\t$t4,1\nsw\t$t4,%d($sp)\nlabel%d:\n",tempNode0->code,tempNode2->code,tempNode0->place,tempNode2->place,label1,newNode->place,label2,label1,newNode->place,label2);
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

  case 90:

/* Line 1455 of yacc.c  */
#line 1807 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->type = relationalOperator;
		strcpy(newNode->identLex, yytext);
		(yyval) = newNode;
	}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1816 "parser.y"
    {

		Node *temp2=(yyvsp[(0) - (1)]);

		Node *temp1=(yyvsp[(1) - (1)]);
		printf("belu listType\n");
		currentScope = scopeStack[scopeStackTop-1];
		if (lookUpInCurrentScope(temp1->identLex)!=NULL){
			printf("belu if\n");
			return 0;
		}
		else{
			printf("belu else\n");			
			Symbol *newEntry=addEntry(temp1->identLex);
			newEntry->type=temp2->semTypeDef;
			if(currentGlobalOffset <= symbolTable[currentScope].currentOffset){
				newEntry->offset=currentGlobalOffset;//symbolTable[currentScope].currentOffset;
				currentGlobalOffset-=4;//symbolTable[currentScope].currentOffset-=4;
			}
			else{
				newEntry->offset=symbolTable[currentScope].currentOffset;
				symbolTable[currentScope].currentOffset-=4;				
			}
			printf("belu semtypedef : %d\n", newEntry->type);	
			(yyval)=(yyvsp[(0) - (1)]);
		}
	}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1845 "parser.y"
    {
		Node *temp2=(yyvsp[(0) - (3)]);
		Node *temp0=(yyvsp[(1) - (3)]);
		Node *temp1=(yyvsp[(3) - (3)]);
		currentScope = scopeStack[scopeStackTop-1];
		if (lookUpInCurrentScope(temp1->identLex)!=NULL){
		}
		else{
			Symbol *newEntry=addEntry(temp1->identLex);
			newEntry->type=temp2->semTypeDef;
			if(currentGlobalOffset <= symbolTable[currentScope].currentOffset){
				newEntry->offset=currentGlobalOffset;//symbolTable[currentScope].currentOffset;
				currentGlobalOffset-=4;//symbolTable[currentScope].currentOffset-=4;
			}
			else{
				newEntry->offset=symbolTable[currentScope].currentOffset;
				symbolTable[currentScope].currentOffset-=4;				
			}
		}
		(yyval)=(yyvsp[(0) - (3)]);	
	}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1871 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef = storeReal;
		printf("Token_real\n");		
		(yyval) = new;

	}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1881 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeInteger;
		printf("Token_integer\n");
		(yyval) = new;	

	}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1892 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeBoolean;
		(yyval) = new;
	}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1902 "parser.y"
    {
	printf("typeDeclaration\n");
	//$$=$2;
	}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1910 "parser.y"
    {
		Node *new = createNode();		
		new->type = varIdentifier;
		new->pt0 = (yyvsp[(1) - (1)]);
		Node* temp = (Node*)(yyvsp[(1) - (1)]);			
		new->realValue=temp->realValue;		
		new->intValue=temp->intValue;
		new->boolValue=temp->boolValue;
		new->semTypeDef = temp->semTypeDef;
		strcpy(new->identLex, temp->identLex);
		new->place=temp->place;
		strcpy(new->code,temp->code);
		printf("varIdentifier");			
		(yyval) = new;
	}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1929 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		strcpy(new->code,temp1->code);
		(yyval) = new;
		printf("unconditional -> basic\n");
	}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1940 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		strcpy(new->code,temp1->code);
		(yyval) = new;
	}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1951 "parser.y"
    {

		Node *new = createNode();
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		strcpy(new->code,temp1->code);
		(yyval) = new;
	}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1965 "parser.y"
    {
		Node *newNode = createNode();         	
        	newNode->type = conditionalStatement;
        	newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place;
		sprintf(newNode->code,"%slabel%d:\n",tempNode->code,tempNode->intValue);
		(yyval) = newNode;
		printf("conditionalStatement -> ifStatement\n");
	}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1977 "parser.y"
    {
		Node *newNode = createNode();         	
        	newNode->type = conditionalStatement;
        	newNode->pt0 = (yyvsp[(1) - (3)]) ;  
		newNode->pt2 = (yyvsp[(3) - (3)]) ;  
		Node *tempNode1 = (yyvsp[(1) - (3)]) ;  
		Node *tempNode2 = (yyvsp[(3) - (3)]) ;
		int label=getNewLabel();
		//int label2=getNewLabel();
		sprintf(newNode->code,"%sb\tlabel%d\nlabel%d:\n%slabel%d:\n",tempNode1->code,label,tempNode1->intValue,tempNode2->code,label);
		if (tempNode1->semTypeDef==storeVoid && tempNode2->semTypeDef==storeVoid ) {  
			newNode->semTypeDef=storeVoid ;  
		}
		printf("conditionalStatement -> ifstatement ELSE statement\n");
		(yyval) = newNode;
	}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1995 "parser.y"
    {
		Node *newNode = createNode();         	
		newNode->type = conditionalStatement;
		newNode->pt0 = (yyvsp[(1) - (2)]) ;  
		newNode->pt1 = (yyvsp[(2) - (2)]) ;  
		Node *tempNode1=(yyvsp[(1) - (2)]);
		Node *tempNode2=(yyvsp[(2) - (2)]);
		int label = getNewLabel();
		if (tempNode1->semTypeDef==storeBoolean && tempNode2->semTypeDef==storeVoid ) {  
			newNode->semTypeDef==storeVoid ;  
			sprintf(newNode->code,"%sli\t$t0,0\nlw\t$t1,%d($sp)\nbeq\t$t1,$t0,label%d\n%slabel%d:\n",tempNode1->code,tempNode1->place,label,tempNode2->code,label) ;
		}
		else{
			newNode->semTypeDef==storeError ;
		}
		
		(yyval)=newNode;
	}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 2019 "parser.y"
    {
		Node *newNode = createNode();         	
        	newNode->type = ifStatement;
        	newNode->pt0 = (yyvsp[(1) - (2)]);
		newNode->pt1 = (yyvsp[(2) - (2)]);
		Node *tempNode1 = (yyvsp[(1) - (2)]);
		Node *tempNode2 = (yyvsp[(2) - (2)]);
		int label = getNewLabel();
		newNode->intValue = label;
		sprintf(newNode->code,"%sli\t$t0,0\nlw\t$t1,%d($sp)\nbeq\t$t1,$t0,label%d\n%s",tempNode1->code,tempNode1->place,label,tempNode2->code) ;  
		newNode->place = tempNode1->place;
		if (tempNode1->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=tempNode2->semTypeDef;
		}
		else {
			newNode->semTypeDef=storeError;
		}
		
		(yyval) = newNode;
		printf("ifStatement -> ifClause unconditionalStatement\n");
	}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 2044 "parser.y"
    {
		Node *newNode = createNode();
        	newNode->type = ifClause;
        	newNode->pt1 = (yyvsp[(2) - (3)]);
                Node* tempNode = (Node*)(yyvsp[(2) - (3)]);
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		if (tempNode->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean ;  
		}
		else {  
			newNode->semTypeDef=storeError ;  
		}
		printf("ifClause -> IF booleanExpression THEN\n");
		(yyval) = newNode;  
	}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 2064 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = basicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;
		strcpy(new->code,temp->code);  
		printf("basic -> unlabbasic\n");
		(yyval) = new;

	}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 2082 "parser.y"
    {		
		Node *new = createNode();         	
        new->type = unlabelledBasicStatement; 
        new->pt0 = (yyvsp[(1) - (1)]) ; 
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;
		strcpy(new->code,temp->code);
		(yyval) = new;
	}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 2093 "parser.y"
    {

		Node *new = createNode();         	
        new->type = unlabelledBasicStatement;
        new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  

		new->semTypeDef=temp->semTypeDef ;  
		printf("unlabelledstatement->dummystatement\n");
		(yyval) = new;

	}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 2107 "parser.y"
    {
			
		Node *new = createNode();         	
        new->type = unlabelledBasicStatement;
        new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  
		strcpy(new->code,temp->code);
		(yyval) = new;
		printf("unlabelledbasicstmt -> procstmt\n");

	}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 2121 "parser.y"
    {
		Node* newNode = createNode();
		Node *tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);
		(yyval) = (yyvsp[(1) - (1)]);
	}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 2135 "parser.y"
    {
		Node *newNode = createNode();
                newNode->type = returnStatement;
		Node *tempNode = (yyvsp[(2) - (2)]) ;
		sprintf(newNode->code,"%slw\t$v0,%d($sp)\njr\t$ra\n",tempNode->code,tempNode->place);
		if(tempNode->semTypeDef==storeError)
		{
			newNode->semTypeDef=storeError;
		}
		else
		{
			newNode->semTypeDef = tempNode->semTypeDef;
		}
		(yyval) = newNode;
	}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 2153 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = (yyvsp[(1) - (3)]);
		new->pt2 = (yyvsp[(3) - (3)]);
		Symbol *symbol1;	
		Node *tmp1=(yyvsp[(1) - (3)]);
		Node *tmp2=(yyvsp[(3) - (3)]);
		new->semTypeDef=storeVoid;
		currentScope = scopeStack[scopeStackTop-1];		
  		symbol1=lookUp(tmp1->identLex, currentScope);
		if (symbol1==NULL){
			new->semTypeDef=storeError;
		}
		else{
			//if (symbol1->type==storeInteger && tmp2->semTypeDef==storeInteger){								
				// SYMBOL1>TYPE IS INTEGER  
				symbol1->value=tmp2->intValue;
				int offset;
				if(tmp1->isArray==1){
					offset = tmp1->place;
				}
				else{
					offset = symbol1->offset;
				}
				sprintf(new->code,"%s%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",tmp1->code,tmp2->code,tmp2->place,offset);
			//}
			/*else*/ if (symbol1->type==storeReal && tmp2->semTypeDef==storeReal){								
				// SYMBOL1>TYPE IS Real
		  		symbol1->realValue=tmp2->realValue;
				printf("assignmentStatement->identifier:= arithmeticexpression, realValue= %f,,%f\n",tmp2->realValue,symbol1->realValue);		
			}
		
		}
		(yyval) = new;
	}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 2191 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = (yyvsp[(1) - (3)]);
		new->pt2 = (yyvsp[(3) - (3)]);
		
	
		Node *temp1=(yyvsp[(1) - (3)]);
		Node *temp2=(yyvsp[(3) - (3)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol *symbol2=lookUp(temp1->identLex,currentScope);
		new->semTypeDef=storeVoid ;  
		


		if (symbol2==NULL){
			new->semTypeDef=storeError;  
		
		}
		else{
			//if (symbol2->type==storeBoolean==storeBoolean && temp2->semTypeDef==storeBoolean) {  
				symbol2->boolean=temp2->boolValue;
				int offset;
				if(temp1->isArray==1){
					offset = temp1->place;
				}
				else{
					offset = symbol2->offset;
				}
				sprintf(new->code,"%s%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",temp1->code,temp2->code,temp2->place,offset);
			//}
		}
		(yyval) = new;
	}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 2402 "parser.y"
    {  
		Node *new = createNode();
		Node *temp = (yyvsp[(2) - (10)]);
		Node *temp2 = (yyvsp[(4) - (10)]);
		Node *temp3 = (yyvsp[(6) - (10)]);
		Node *temp4 = (yyvsp[(8) - (10)]);
		Node *temp5 = (yyvsp[(10) - (10)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol *symbol=lookUp(temp->identLex,currentScope);
		if (symbol == NULL) {  
			temp->semTypeDef=storeError;
		
		}
		else {
			if (!(symbol->type==storeInteger || symbol->type==storeReal)){
				temp->semTypeDef=storeError;
			}
		}

		if (temp->semTypeDef==storeError){  
			new->semTypeDef=storeError;
			(yyval) = new;
		}
		else{
			//if (temp2->semTypeDef == temp->semTypeDef && temp3->semTypeDef == temp->semTypeDef && temp4->semTypeDef == temp->semTypeDef) {
				int label1 = getNewLabel();
				int label2 = getNewLabel();
				int offset = symbol->offset;
				sprintf(new->code,"%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\nlabel%d:\n%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nbge\t$t0,$t1,label%d\n%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nadd\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\nb\tlabel%d\nlabel%d:\n",temp2->code,temp2->place,offset,label1,temp4->code,temp->place,temp4->place,label2,temp5->code,temp3->code,offset,temp3->place,offset,label1,label2);
			//printf("%s",new->code);
			//}
			//else {
			//	new->semTypeDef = storeError;		
			//}
			(yyval)=new;
		}
	}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 2442 "parser.y"
    {	
		printf("empty reached\n");
		Node *new = createNode();         	            	  
        	new->type =empty;
		(yyval) = new;
	}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 2450 "parser.y"
    {
		Node *new = createNode();
		Node *temp1 = (yyvsp[(1) - (2)]);
		Node *temp2 = (yyvsp[(2) - (2)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol *symbol= lookUp(temp1->identLex,currentScope);

		if(symbol == NULL)
		{
			new->semTypeDef = storeError;
		}
		else
		{
			/*if(temp2->semTypeDef==storeError)
			{
				new->semTypeDef =storeError;
			}
			else
			{*/
				new->semTypeDef = symbol->type;
				new->place = getNewTemp();
				sprintf(new->code, "sw\t$t0,-996($sp)\nsw\t$t1,-992($sp)\nsw\t$t2,-988($sp)\nsw\t$t3,-984($sp)\nsw\t$t4,-980($sp)\nsw\t$t5,-976($sp)\nsw\t$t6,-972($sp)\nsw\t$t7,-968($sp)\nsw\t$ra,-964($sp)\n%sli\t$t0,100\nsub\t$sp,$sp,$t0\njal\t%s\nli\t$t0,100\nadd\t$sp,$sp,$t0\nlw\t$t0,-996($sp)\nlw\t$t1,-992($sp)\nlw\t$t2,-988($sp)\nlw\t$t3,-984($sp)\nlw\t$t4,-980($sp)\nlw\t$t5,-976($sp)\nlw\t$t6,-972($sp)\nlw\t$t7,-968($sp)\nlw\t$ra,-964($sp)\nsw\t$v0,%d($sp)\n",temp2->code,temp1->identLex,new->place);

			//}
		}

		(yyval) = new; 
	}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 2482 "parser.y"
    {
		Node *new = createNode(); 
		new->type = procedureIdentifier;
		new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp=(yyvsp[(1) - (1)]);
		strcpy(new->identLex,temp->identLex);
		(yyval) = new;
	}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 2494 "parser.y"
    {

		Node *temp = (yyvsp[(2) - (3)]);
		if(temp->semTypeDef != storeError)
		{		
			temp->semTypeDef == storeVoid;
		}
		printf("actparampart -> ( act param list )\n");
		(yyval)=(yyvsp[(2) - (3)]);
	}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 2508 "parser.y"
    {
		Node *temp = (yyvsp[(-1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbol= lookUp(temp1->identLex,currentScope);
		Node *new = createNode();
		new->dim = 0;
		sprintf(new->code,"%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",temp1->code,temp1->place,-100-4* new->dim);
		new->semTypeDef = storeVoid;
		
		(yyval) = new;
		printf("actual parameter list -> actual parameter\n");
	}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 2523 "parser.y"
    {
		Node *temp = (yyvsp[(-1) - (3)]);
		Node *temp3 = (yyvsp[(1) - (3)]);
		Node *temp1 = (yyvsp[(3) - (3)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbol= lookUp(temp->identLex,currentScope);
		
		Node *new = createNode();
		new->dim = 1 + temp3->dim;
		if(temp3->semTypeDef == storeError)
			new->semTypeDef = storeError;
		else
		{
			new->semTypeDef = storeVoid;
			sprintf(new->code,"%s%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",temp3->code,temp1->code,temp1->place,-100-4* new->dim);			
		}	
		(yyval) = new;

	}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 2546 "parser.y"
    {
		Node *newNode = createNode(); 
		Node *tempNode = (yyvsp[(1) - (1)]); 
		newNode->type = actualParameter;
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		newNode->place = tempNode->place;
		strcpy(newNode->code, tempNode->code);
		printf("actual parameter -> expression\n");
		(yyval) = newNode;
	}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 2564 "parser.y"
    {
		Node *new = createNode();
		Node *temp1 = (yyvsp[(1) - (2)]);
		Node *temp2 = (yyvsp[(2) - (2)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol *symbol= lookUp(temp1->identLex,currentScope);

		if(symbol == NULL)
		{
			new->semTypeDef = storeError;
		}
		else
		{
			/*if(temp2->semTypeDef==storeError)
			{
				new->semTypeDef =storeError;
			}
			else
			{*/
				new->semTypeDef = symbol->type;
				new->place = getNewTemp();
				sprintf(new->code, "sw\t$t0,-996($sp)\nsw\t$t1,-992($sp)\nsw\t$t2,-988($sp)\nsw\t$t3,-984($sp)\nsw\t$t4,-980($sp)\nsw\t$t5,-976($sp)\nsw\t$t6,-972($sp)\nsw\t$t7,-968($sp)\nsw\t$ra,-964($sp)\n%sli\t$t0,100\nsub\t$sp,$sp,$t0\njal\t%s\nli\t$t0,100\nadd\t$sp,$sp,$t0\nlw\t$t0,-996($sp)\nlw\t$t1,-992($sp)\nlw\t$t2,-988($sp)\nlw\t$t3,-984($sp)\nlw\t$t4,-980($sp)\nlw\t$t5,-976($sp)\nlw\t$t6,-972($sp)\nlw\t$t7,-968($sp)\nlw\t$ra,-964($sp)\nsw\t$v0,%d($sp)\n",temp2->code,temp1->identLex,new->place);

			//}
		}

		(yyval) = new; 
		

	}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 2598 "parser.y"
    {
		Node* newNode=createNode();
		Node *tempNode=(yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;
		printf("stmt -> unconditionalstmt\n");
	}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 2608 "parser.y"
    {
		Node* newNode=createNode();
		Node *tempNode=(yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;

	}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 2618 "parser.y"
    {	Node* newNode=createNode();
		Node *tempNode=(yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;
	}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 2626 "parser.y"
    {
		Node* newNode=createNode();
		Node* tempNode=(yyvsp[(2) - (2)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		sprintf(newNode->code,"%sli\t$v0,4\nla\t$a0, MSG\nsyscall\nlw\t$t0,%d($sp)\nli\t$v0,1\nmove\t$a0,$t0\nsyscall\n",tempNode->code,tempNode->place);
		(yyval)=newNode;
	}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 2644 "parser.y"
    {
		(yyvsp[(0) - (1)])=(yyvsp[(-1) - (1)]);
		Node *node0 = (yyvsp[(0) - (1)]);
		Node *node1 = (yyvsp[(1) - (1)]);
		
		int oldScope = currentScope;
		currentScope = globalLevel + 1;

		if (lookUpInCurrentScope(node1->identLex) == NULL){
			Symbol * entry = addEntry(node1->identLex);
			entry->offset = symbolTable[currentScope].currentOffset;
			symbolTable[currentScope].currentOffset-=4;
		}
		else{
			printf("Error in paramaters,%s already defined\n",node1->identLex);
		}

		currentScope = oldScope;
		if (lookUpInCurrentScope(node0->identLex) == NULL){
			Symbol * entry = addEntry(node1->identLex);
			entry->procNumParam++;
		}
		printf("formalParmeter->identifer\n");
		(yyval) = (yyvsp[(0) - (1)]);
		paramBelu++;
	}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 2673 "parser.y"
    {   ////check/////
		(yyvsp[(1) - (3)])=(yyvsp[(0) - (3)]);
		(yyvsp[(2) - (3)])=(yyvsp[(0) - (3)]);
		printf("formalParmeterlist->formalParmeter\n");	
	}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 2681 "parser.y"
    {
		(yyval) = (yyvsp[(0) - (1)]);
	}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 2684 "parser.y"
    {
		(yyvsp[(1) - (1)]) = (yyvsp[(0) - (1)]);
	}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 2686 "parser.y"
    {
		printf("formalParmeterpart->(formalParmeterlist)\n");
	}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 2691 "parser.y"
    {
		Node *node1 = (yyvsp[(0) - (1)]);
		Node *node2 = (yyvsp[(1) - (1)]);
		int oldLevel = currentScope;
		currentScope = globalLevel + 1;
		printf("identlist->ident\n");
		Symbol *symbol1=lookUp(node2->identLex,currentScope);
		if(symbol1 != NULL)
		{
			symbol1->type=node1->semTypeDef;		
		}
		else{
			printf("error!%s is absent from formal paramater",node2->identLex);
			//symbol1->type = node1->semTypeDef;
		}
		currentScope = oldLevel;
		paramBelu--;
		(yyval) = node1;
		
	}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 2712 "parser.y"
    {
		Node *node1 = (yyvsp[(1) - (3)]);
		Node *node2 = (yyvsp[(3) - (3)]);
		int oldLevel = currentScope;
		currentScope = globalLevel + 1;
		printf("identlist->ident\n");
		Symbol *symbol1=lookUp(node2->identLex,currentScope);
		if(symbol1 != NULL)
		{
			symbol1->type=node1->semTypeDef;		
		}
		else{
			printf("error!%s is absent from formal paramater",node2->identLex);
			//symbol1->type = node1->semTypeDef;
		}
		currentScope = oldLevel;
		printf("identlist ->identlist , ident\n");
		paramBelu--;
		(yyval) = node1;

	}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 2734 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 2739 "parser.y"
    {
		printf("specifier->type\n"); 
	}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 2750 "parser.y"
    {
		Node *node1 = (yyvsp[(1) - (3)]);
		printf("specificationidentlist->specifier identlist ;\n");

	}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 2756 "parser.y"
    {
		printf("specificationidentlist->specificationidentlist specifier identlist ;\n");

	}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 2762 "parser.y"
    {
		Node *node = createNode();
		node->type = procedureHeading;
		node->pt0 = (yyvsp[(1) - (1)]);
		Node *node1 = (yyvsp[(1) - (1)]);
		node1->parent = node;
		strcpy(node->identLex, node1->identLex);
		currentScope = scopeStack[scopeStackTop-1];
		if (lookUpInCurrentScope(node1->identLex) == NULL){
			Symbol * entry = addEntry(node1->identLex);
			entry->procNumParam = 0;
		}
		(yyval) = node;
	}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 2775 "parser.y"
    {
		printf("the belu number of parameters defined is %d\n",paramBelu);
		(yyvsp[(3) - (4)]) = (yyvsp[(1) - (4)]);
	}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 2778 "parser.y"
    {
		printf("the belu number of parameters defined is %d\n",paramBelu);
	}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 2784 "parser.y"
    {//changed 16th april

		Node *new = createNode();
		new->type = procedureBody;
		Node *temp = (yyvsp[(1) - (1)]);
		new->semTypeDef = temp->semTypeDef;
		strcpy(new->code,temp->code);
		(yyval) = new;
		printf("proc body -> stmt\n");
	}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 2796 "parser.y"
    {
		Node *node1 = (yyvsp[(2) - (3)]);
		Node *node2 = (yyvsp[(3) - (3)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbol = lookUp(node1->identLex, currentScope);////check////
		symbol->type = storeVoid;

		Node *node = createNode();
		node->type = procedureDeclaration;

		if (node1->semTypeDef == storeVoid && node2->semTypeDef == storeVoid){
			node->semTypeDef = storeVoid;
		}
		else{
			node->semTypeDef = storeError;
		}
		int label = getNewLabel();
		sprintf(node->code,"b\tlabel%d\n%s:\n%s\njr $ra\nlabel%d:\n",label,node1->identLex,node2->code,label);		
		(yyval) = node;
		printf("procedureDeclaration -> procedure heading body");
		if (paramBelu != 0)
			printf("Error. too many or too few specifications\n");
		paramBelu = 0;
	}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 2821 "parser.y"
    {
		Node *node1 = (yyvsp[(3) - (4)]);
		Node *node2 = (yyvsp[(4) - (4)]);
		Node *node3 = (yyvsp[(1) - (4)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbol = lookUpInCurrentScope(node1->identLex);
		symbol->type = node3->semTypeDef;

		Node *node = createNode();
       	node->type = procedureDeclaration;

		if (node1->semTypeDef == storeVoid && node2->semTypeDef == storeVoid){
			node->semTypeDef = node3->semTypeDef;
		}
		else{
			node->semTypeDef = storeError;
		}
		int label = getNewLabel();
		sprintf(node->code,"b\tlabel%d\n%s:\n%s\njr $ra\nlabel%d:\n",label,node1->identLex,node2->code,label);		
		(yyval) = node;
		printf("proceduredeclaration -> type procedure heading body\n");
		if (paramBelu != 0)
			printf("Error. too many or too few specifications\n");
		paramBelu = 0;
	}
    break;



/* Line 1455 of yacc.c  */
#line 4615 "y.tab.c"
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
#line 2848 "parser.y"

int main(int argc, char* argv[])
{
	tempNodeScope = currentScope;
   	int i = 0;
	for(i=0;i<1000;i++){
		symbolTable[i].currentOffset=0;
		symbolTable[i].newTempOffset=-1000;
		symbolTable[i].arrayOffset=-700;
	}
	for(i=1;i<argc;i++)
	{
	    FILE* fp;
	    fp = fopen(argv[i], "r");
	    yyin = fp;
	    while(yyparse() != 0)
		;
	}
	strcat(code,"jr\t$ra");
	strcat(code,"\n\n\t.data\nMSG:\t.asciiz \"\\n OUTPUT = \"");
	printf("%s",code);
	FILE* fp1 = fopen("code1.asm","w");
	fprintf(fp1,"%s",code);
	return 0;
}


