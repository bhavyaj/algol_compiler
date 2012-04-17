
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
#include <stdlib.h>
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
#line 261 "y.tab.c"

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
#line 449 "y.tab.c"

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
#define YYFINAL  59
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   367

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
      26,    28,    30,    33,    35,    38,    41,    45,    47,    49,
      51,    53,    55,    57,    61,    63,    67,    69,    74,    78,
      80,    84,    88,    90,    92,    94,    96,    98,   101,   104,
     108,   112,   114,   118,   122,   124,   128,   130,   132,   134,
     138,   140,   142,   144,   146,   148,   150,   152,   157,   159,
     163,   165,   167,   169,   171,   175,   177,   181,   183,   187,
     189,   193,   195,   198,   200,   202,   206,   208,   212,   214,
     216,   220,   222,   224,   226,   229,   231,   233,   235,   237,
     239,   243,   246,   249,   252,   256,   258,   261,   263,   265,
     267,   269,   271,   273,   276,   280,   284,   295,   296,   299,
     301,   304,   308,   310,   314,   316,   318,   323,   326,   328,
     330,   332,   335,   337,   339,   343,   345,   346,   351,   353,
     357,   361,   363,   365,   368,   370,   372,   375,   377,   379,
     383,   388,   389,   390,   398,   400,   404,   409,   412,   417,
     419,   423,   425,   427,   432,   435,   437,   441
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      80,     0,    -1,     5,    84,    -1,    75,    66,    84,    -1,
      75,    66,    83,    -1,    76,    -1,    78,    77,    -1,    79,
      30,    -1,   107,    -1,   101,    -1,    82,    -1,    77,    -1,
       5,    83,    -1,    81,    -1,    78,    82,    -1,   140,     6,
      -1,   140,    66,    83,    -1,   120,    -1,    92,    -1,   156,
      -1,   154,    -1,    94,    -1,    94,    -1,    85,    30,    86,
      -1,    87,    -1,    88,    16,    87,    -1,   107,    -1,    89,
      23,    88,    24,    -1,    89,    16,    90,    -1,    90,    -1,
      91,    16,    90,    -1,   119,    64,    91,    -1,    94,    -1,
     108,    -1,   159,    -1,    95,    -1,    96,    -1,    11,    96,
      -1,    12,    96,    -1,    95,    11,    96,    -1,    95,    12,
      96,    -1,    97,    -1,    96,    15,    97,    -1,    96,    13,
      97,    -1,    98,    -1,    97,    14,    98,    -1,    99,    -1,
     139,    -1,   103,    -1,    21,    94,    22,    -1,   100,    -1,
     101,    -1,    28,    -1,    29,    -1,   121,    -1,   102,    -1,
     104,    -1,    89,    23,   105,    24,    -1,   106,    -1,   105,
      16,   106,    -1,    94,    -1,     4,    -1,   109,    -1,   110,
      -1,   109,    38,   110,    -1,   111,    -1,   110,    65,   111,
      -1,   112,    -1,   111,    40,   112,    -1,   113,    -1,   112,
      39,   113,    -1,   114,    -1,    41,   114,    -1,   115,    -1,
     116,    -1,    21,   108,    22,    -1,     7,    -1,    95,   117,
      95,    -1,    31,    -1,   121,    -1,   118,    16,   121,    -1,
      56,    -1,    55,    -1,    57,    -1,   119,   118,    -1,   107,
      -1,   126,    -1,    82,    -1,    77,    -1,   124,    -1,   124,
      50,   140,    -1,   125,   131,    -1,    78,   123,    -1,   125,
     122,    -1,    48,   108,    49,    -1,   127,    -1,    78,   126,
      -1,   130,    -1,   128,    -1,   133,    -1,   129,    -1,   155,
      -1,   132,    -1,    68,    93,    -1,   103,    72,    94,    -1,
     103,    72,   108,    -1,    43,   103,    72,    94,    46,    94,
      47,    94,    44,   140,    -1,    -1,   134,   135,    -1,   107,
      -1,    21,    22,    -1,    21,   136,    22,    -1,   137,    -1,
     136,   138,   137,    -1,    93,    -1,    16,    -1,    22,   107,
      30,    21,    -1,   134,   135,    -1,   122,    -1,   123,    -1,
     131,    -1,     3,    93,    -1,   107,    -1,   141,    -1,   142,
     138,   141,    -1,   132,    -1,    -1,    21,   144,   142,    22,
      -1,   107,    -1,   145,    16,   107,    -1,    52,   145,    66,
      -1,   132,    -1,   119,    -1,   119,    64,    -1,    62,    -1,
      51,    -1,   119,    10,    -1,   132,    -1,   149,    -1,   147,
     145,    66,    -1,   149,   147,   145,    66,    -1,    -1,    -1,
     134,   151,   143,    66,   152,   146,   148,    -1,   140,    -1,
      10,   150,   153,    -1,   119,    10,   150,   153,    -1,    42,
     159,    -1,    51,   158,    72,   157,    -1,   159,    -1,   157,
      16,   159,    -1,   107,    -1,   160,    -1,   125,   160,    50,
     159,    -1,    30,    79,    -1,   161,    -1,    21,   159,    22,
      -1,   158,    25,   106,    26,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   311,   311,   321,   333,   344,   354,   390,   399,   406,
     416,   430,   448,   460,   469,   481,   491,   505,   513,   521,
     528,   538,   558,   578,   601,   617,   645,   658,   689,   729,
     757,   777,   785,   797,   809,   815,   852,   867,   882,   900,
     940,   976,   991,  1024,  1066,  1082,  1109,  1125,  1139,  1171,
    1187,  1202,  1218,  1229,  1241,  1259,  1275,  1293,  1336,  1356,
    1378,  1393,  1411,  1449,  1463,  1481,  1494,  1515,  1527,  1547,
    1559,  1579,  1591,  1610,  1636,  1648,  1661,  1678,  1793,  1802,
    1831,  1857,  1867,  1878,  1888,  1896,  1915,  1927,  1938,  1951,
    1964,  1981,  2001,  2005,  2030,  2051,  2064,  2068,  2079,  2093,
    2107,  2115,  2123,  2127,  2145,  2206,  2417,  2458,  2466,  2497,
    2508,  2509,  2523,  2538,  2561,  2575,  2576,  2579,  2613,  2623,
    2633,  2641,  2659,  2688,  2689,  2697,  2700,  2700,  2707,  2728,
    2750,  2753,  2755,  2758,  2759,  2760,  2761,  2763,  2764,  2766,
    2771,  2778,  2791,  2778,  2800,  2812,  2836,  2864,  2873,  2876,
    2877,  2881,  2894,  2901,  2904,  2911,  2912,  2915
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
  "unlabelledCompound", "compoundStatement", "compoundTail", "declaration",
  "lowerBound", "upperBound", "boundPair", "boundPairList",
  "arrayIdentifier", "arraySegment", "arrayList", "arrayDeclaration",
  "expression", "arithmeticExpression", "simpleArithmeticExpression",
  "term", "factor", "primary", "unsignedNumber", "realNumber", "integer",
  "simpleVariable", "variable", "subscriptedVariable", "subscriptList",
  "subscriptExpression", "identifier", "booleanExpression",
  "simpleBoolean", "implication", "booleanTerm", "booleanFactor",
  "booleanSecondary", "booleanPrimary", "logicalValue", "relation",
  "relationalOperator", "listType", "type", "typeDeclaration",
  "varIdentifier", "unconditionalStatement", "conditionalStatement",
  "ifStatement", "ifClause", "basicStatement", "unlabelledBasicStatement",
  "dummyStatement", "returnStatement", "assignmentStatement",
  "forStatement", "empty", "procedureStatement", "procedureIdentifier",
  "actualParameterPart", "actualParameterList", "actualParameter",
  "parameterDelimiter", "functionDesignator", "statement",
  "formalParameter", "formalParameterList", "formalParameterPart", "$@1",
  "identifierList", "valuePart", "specifier", "specificationPart",
  "specificationIdentifierList", "procedureHeading", "@2", "$@3",
  "procedureBody", "procedureDeclaration", "gotoStatement",
  "switchDeclaration", "switchList", "switchIdentifier",
  "designationalExpression", "simpleDesignationalExpression",
  "switchDesignator", 0
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
      80,    80,    81,    82,    82,    83,    83,    84,    84,    84,
      84,    85,    86,    87,    88,    88,    89,    90,    90,    91,
      91,    92,    93,    93,    93,    94,    95,    95,    95,    95,
      95,    96,    96,    96,    97,    97,    98,    98,    98,    98,
      99,    99,   100,   101,   102,   103,   103,   104,   105,   105,
     106,   107,   108,   109,   109,   110,   110,   111,   111,   112,
     112,   113,   113,   114,   114,   114,   115,   116,   117,   118,
     118,   119,   119,   119,   120,   121,   122,   122,   122,   123,
     123,   123,   123,   124,   125,   126,   126,   127,   127,   127,
     127,   127,   128,   129,   130,   130,   131,   132,   133,   134,
     135,   135,   136,   136,   137,   138,   138,   139,   140,   140,
     140,   140,   141,   142,   142,   143,   144,   143,   145,   145,
     146,   146,   147,   147,   147,   147,   147,   148,   148,   149,
     149,   151,   152,   150,   153,   154,   154,   155,   156,   157,
     157,   158,   159,   159,   160,   160,   160,   161
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     3,     1,     2,     2,     1,     1,
       1,     1,     2,     1,     2,     2,     3,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     1,     4,     3,     1,
       3,     3,     1,     1,     1,     1,     1,     2,     2,     3,
       3,     1,     3,     3,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     3,
       1,     1,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     2,     1,     1,     3,     1,     3,     1,     1,
       3,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       3,     2,     2,     2,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     2,     3,     3,    10,     0,     2,     1,
       2,     3,     1,     3,     1,     1,     4,     2,     1,     1,
       1,     2,     1,     1,     3,     1,     0,     4,     1,     3,
       3,     1,     1,     2,     1,     1,     2,     1,     1,     3,
       4,     0,     0,     7,     1,     3,     4,     2,     4,     1,
       3,     1,     1,     4,     2,     1,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    61,   107,    53,     0,     5,    11,     0,     0,     0,
      13,    10,     9,     8,     0,     0,     0,     0,     0,     0,
      82,    81,    83,     0,    88,   107,    87,    12,     2,     0,
      18,    55,     0,    56,     8,     0,    17,    54,   118,   119,
      89,   107,    86,    95,    98,   100,    97,   120,   102,    99,
       0,     0,    20,   101,    19,   107,     6,    14,     7,     1,
      76,     0,     0,     0,    52,     0,     0,   121,    32,    35,
      36,    41,    44,    46,    50,    51,    48,    85,    33,    62,
      63,    65,    67,    69,    71,    73,    74,     0,     0,    47,
       0,    34,   152,   155,   109,   141,   107,     0,   151,   147,
       0,    26,     0,     0,    85,     0,     0,   103,    92,    96,
       0,     0,     0,     0,    85,    84,    79,   107,   107,    93,
      91,     0,   108,    15,   107,     4,     3,     0,    37,    38,
       0,     0,     0,   154,    72,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,     0,   107,
     144,   145,     0,    94,     0,    60,    35,     0,    58,   104,
     105,   107,     0,    29,    31,    26,     0,    90,   110,   114,
       0,   112,    16,    49,    75,   156,    39,    40,    77,    43,
      42,    45,    64,    66,    68,    70,     0,     0,   126,   125,
       0,     0,   148,   149,     0,    57,   146,     0,     0,     0,
      80,   115,   111,     0,   153,   157,     0,   142,     0,     0,
      59,    28,     0,    24,     0,    21,    30,     0,   113,   122,
     123,     0,   107,     0,   150,     0,     0,    27,     0,   127,
       0,     0,   131,   107,     0,    23,    22,    25,   116,   124,
     128,     0,   135,   134,   132,   137,     0,   143,   138,     0,
       0,   130,   136,   133,     0,     0,   107,   129,   139,     0,
     106,   140
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    24,    25,     8,     9,    10,    26,    27,
      28,   212,   235,   213,   214,    29,   163,   164,    30,   169,
      68,   156,    70,    71,    72,    73,    74,    75,    31,    76,
      33,   157,   158,   104,    78,    79,    80,    81,    82,    83,
      84,    85,    86,   138,   115,    35,    36,    37,    38,    39,
      40,    87,    42,    43,    44,    45,    46,    47,    48,    49,
      88,   122,   170,   171,   203,    89,    51,   220,   221,   190,
     206,   241,   233,   246,   247,   248,    96,   149,   222,   151,
      52,    53,    54,   192,    90,    91,    92,    93
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -202
static const yytype_int16 yypact[] =
{
      76,  -202,   231,  -202,   -17,  -202,  -202,    76,    39,   127,
    -202,  -202,  -202,  -202,   319,    97,   134,    97,   204,    97,
    -202,  -202,  -202,   319,  -202,   128,  -202,  -202,  -202,   135,
    -202,  -202,    95,  -202,    70,    58,  -202,  -202,  -202,  -202,
     125,   249,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
     167,    22,  -202,  -202,  -202,   231,  -202,  -202,  -202,  -202,
    -202,   255,   255,   319,  -202,    35,   334,  -202,  -202,    99,
     101,   179,  -202,  -202,  -202,  -202,  -202,   160,  -202,   162,
     140,   170,   178,  -202,  -202,  -202,  -202,   144,   167,  -202,
     196,  -202,  -202,  -202,  -202,  -202,   209,   134,  -202,  -202,
     154,   171,   204,    99,   129,   193,   172,  -202,  -202,  -202,
     291,   204,    97,    97,  -202,   232,  -202,   209,   276,  -202,
    -202,   286,  -202,  -202,   209,  -202,  -202,   291,   101,   101,
     227,   239,   240,  -202,  -202,   255,   255,  -202,   291,   255,
     255,   255,   204,   204,   204,   204,   213,  -202,   291,   244,
    -202,  -202,   291,  -202,   134,  -202,   212,    37,  -202,  -202,
    -202,   209,   146,  -202,   250,  -202,    97,  -202,  -202,  -202,
      21,  -202,  -202,  -202,  -202,  -202,   101,   101,   212,   179,
     179,  -202,   140,   170,   178,  -202,   134,   246,  -202,  -202,
     223,   248,   280,  -202,   291,  -202,  -202,    97,   291,    97,
    -202,  -202,    97,   319,  -202,  -202,    97,  -202,   291,   134,
    -202,  -202,   270,  -202,    51,  -202,  -202,   271,  -202,  -202,
    -202,    55,   252,   259,  -202,   291,   291,  -202,   288,    97,
      97,    97,  -202,   122,   291,  -202,  -202,  -202,  -202,  -202,
    -202,    26,  -202,  -202,    14,  -202,    97,  -202,   122,   266,
      97,  -202,  -202,  -202,    34,    97,   209,  -202,  -202,    43,
    -202,  -202
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -202,  -202,  -202,     5,    38,   256,  -202,  -202,    33,   -35,
     258,  -202,  -202,    85,  -202,   -91,    23,  -202,  -202,   181,
      -7,   126,    24,   100,   183,  -202,  -202,    11,  -202,    29,
    -202,  -202,  -122,     0,   -12,  -202,   180,   182,   184,   187,
     267,  -202,  -202,  -202,  -202,  -201,  -202,   -32,   294,   311,
    -202,     2,   -16,  -202,  -202,  -202,  -202,   296,  -139,  -202,
      19,   251,  -202,   139,   130,  -202,   -88,   113,  -202,  -202,
    -202,   -48,  -202,   102,  -202,  -202,   241,  -202,  -202,   191,
    -202,  -202,  -202,  -202,   335,   -15,   269,  -202
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -152
static const yytype_int16 yytable[] =
{
      13,    99,    34,   116,    41,     6,   105,    13,   150,   109,
     189,    12,    56,    12,    77,    94,    98,   101,    12,    98,
     125,    50,   162,    77,   252,    34,   187,    41,   123,   167,
      56,    32,   244,    11,    95,   114,    12,   201,     7,     1,
      57,    34,   250,   202,    50,     7,   100,   244,   132,    55,
     250,   131,    12,   194,    32,    34,   130,    41,    57,   250,
      50,   195,     1,    77,     3,    13,    12,   226,   112,    58,
      32,   201,   210,   150,    50,   227,    12,   229,   253,   118,
       1,     2,   132,   232,    32,   128,   129,    98,   124,   172,
     131,  -109,   251,   -26,   245,   130,    34,    98,    41,   160,
     258,     1,   109,   155,   159,     3,   162,    12,   162,   261,
     135,   136,    94,   165,   139,    50,   140,    34,    34,    41,
     130,    77,   113,    56,    34,    32,    41,    59,    12,    12,
     137,    95,     1,     2,   200,    12,    50,    50,     1,   193,
      69,   155,   -85,    50,   103,   191,    32,    32,     1,    69,
    -109,    57,   -26,    32,    98,    97,   118,     3,   110,   176,
     177,    34,   197,    41,    65,    97,   114,   111,   260,   198,
      16,   204,    12,   242,    65,   117,    18,    20,    21,    22,
      50,  -109,    18,   -26,   243,  -151,    98,   155,   121,    69,
      32,   215,   103,   141,   224,    67,    23,   165,   254,   165,
     142,   223,   217,    77,   107,   143,   219,   259,     1,    98,
     144,    60,    14,     1,     2,    61,    62,   145,   236,   215,
     211,   148,   216,   135,   136,   102,   152,   249,    69,   217,
     219,   240,    64,     3,    14,     1,     2,    69,     3,   179,
     180,    15,   153,   -85,   154,    66,   240,    69,   166,   173,
     257,    16,    17,     1,     2,   240,    34,    18,    41,     1,
       3,   174,   175,   186,   178,   188,   199,    12,   103,   103,
     103,   103,   205,    16,    17,    50,   127,    23,     3,    18,
       1,     2,    19,    64,     3,    32,    20,    21,    22,   207,
       1,    16,    17,    60,   208,     1,   209,    61,    62,    23,
     225,   228,    61,    62,   231,     3,   234,    63,   168,   238,
     256,   237,   127,   126,    64,     3,    65,    23,    16,    64,
       3,   133,   182,     1,   181,   183,    60,    66,   184,    69,
      61,    62,   185,   134,    18,   119,   108,   120,     1,   147,
      63,    60,   218,   239,    23,    61,    62,    64,     3,    65,
     255,   230,   196,   161,   106,   102,   146,     0,     0,     0,
      66,     0,    64,     3,     0,     0,     0,    18
};

static const yytype_int16 yycheck[] =
{
       0,    16,     2,    35,     2,     0,    18,     7,    96,    25,
     149,     0,     7,     2,    14,    15,    16,    17,     7,    19,
      55,     2,   113,    23,    10,    25,   148,    25,     6,   117,
      25,     2,   233,     0,    15,    35,    25,    16,     0,     4,
       7,    41,    16,    22,    25,     7,    17,   248,    63,    66,
      16,    63,    41,    16,    25,    55,    63,    55,    25,    16,
      41,    24,     4,    63,    29,    65,    55,    16,    10,    30,
      41,    16,   194,   161,    55,    24,    65,    22,    64,    41,
       4,     5,    97,   222,    55,    61,    62,    87,    66,   124,
     102,    21,    66,    23,   233,   102,    96,    97,    96,   111,
      66,     4,   118,   110,   111,    29,   197,    96,   199,    66,
      11,    12,   112,   113,    13,    96,    15,   117,   118,   117,
     127,   121,    64,   118,   124,    96,   124,     0,   117,   118,
      31,   112,     4,     5,   166,   124,   117,   118,     4,   154,
      14,   148,    72,   124,    18,   152,   117,   118,     4,    23,
      21,   118,    23,   124,   154,    21,   118,    29,    23,   135,
     136,   161,    16,   161,    30,    21,   166,    72,   256,    23,
      42,   186,   161,    51,    30,    50,    48,    55,    56,    57,
     161,    21,    48,    23,    62,    25,   186,   194,    21,    63,
     161,   198,    66,    14,   209,    14,    68,   197,   246,   199,
      38,   208,   202,   203,    23,    65,   206,   255,     4,   209,
      40,     7,     3,     4,     5,    11,    12,    39,   225,   226,
     197,    25,   199,    11,    12,    21,    72,   234,   102,   229,
     230,   231,    28,    29,     3,     4,     5,   111,    29,   139,
     140,    10,    49,    72,    72,    41,   246,   121,    16,    22,
     250,    42,    43,     4,     5,   255,   256,    48,   256,     4,
      29,    22,    22,    50,   138,    21,    16,   256,   142,   143,
     144,   145,    26,    42,    43,   256,    21,    68,    29,    48,
       4,     5,    51,    28,    29,   256,    55,    56,    57,    66,
       4,    42,    43,     7,    46,     4,    16,    11,    12,    68,
      30,    30,    11,    12,    52,    29,    47,    21,    22,    21,
      44,   226,    21,    55,    28,    29,    30,    68,    42,    28,
      29,    65,   142,     4,   141,   143,     7,    41,   144,   203,
      11,    12,   145,    66,    48,    41,    25,    41,     4,    88,
      21,     7,   203,   230,    68,    11,    12,    28,    29,    30,
     248,   221,   161,   112,    19,    21,    87,    -1,    -1,    -1,
      41,    -1,    28,    29,    -1,    -1,    -1,    48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    29,    75,    76,    77,    78,    79,    80,
      81,    82,   101,   107,     3,    10,    42,    43,    48,    51,
      55,    56,    57,    68,    77,    78,    82,    83,    84,    89,
      92,   102,   103,   104,   107,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   140,   154,   155,   156,    66,    77,    82,    30,     0,
       7,    11,    12,    21,    28,    30,    41,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   103,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   125,   134,   139,
     158,   159,   160,   161,   107,   134,   150,    21,   107,   159,
     103,   107,    21,    95,   107,   108,   158,    93,   123,   126,
      23,    72,    10,    64,   107,   118,   121,    50,    78,   122,
     131,    21,   135,     6,    66,    83,    84,    21,    96,    96,
      94,   108,   159,    79,   114,    11,    12,    31,   117,    13,
      15,    14,    38,    65,    40,    39,   160,   135,    25,   151,
     140,   153,    72,    49,    72,    94,    95,   105,   106,    94,
     108,   150,    89,    90,    91,   107,    16,   140,    22,    93,
     136,   137,    83,    22,    22,    22,    96,    96,    95,    97,
      97,    98,   110,   111,   112,   113,    50,   106,    21,   132,
     143,    94,   157,   159,    16,    24,   153,    16,    23,    16,
     121,    16,    22,   138,   159,    26,   144,    66,    46,    16,
     106,    90,    85,    87,    88,    94,    90,   107,   137,   107,
     141,   142,   152,    94,   159,    30,    16,    24,    30,    22,
     138,    52,   132,   146,    47,    86,    94,    87,    21,   141,
     107,   145,    51,    62,   119,   132,   147,   148,   149,    94,
      16,    66,    10,    64,   145,   147,    44,   107,    66,   145,
     140,    66
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
#line 312 "parser.y"
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
#line 322 "parser.y"
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
#line 334 "parser.y"
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
#line 345 "parser.y"
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
#line 363 "parser.y"
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
#line 391 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (2)]);
		strcpy(newNode->identLex,tempNode->identLex);
		(yyval)=newNode;
	}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 400 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex,tempNode->identLex);
		(yyval)=newNode;
	}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 407 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex,atoi(tempNode->intValue));
		(yyval)=newNode;
	}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 417 "parser.y"
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
#line 431 "parser.y"
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
#line 448 "parser.y"
    {
		currentScope = scopeStack[scopeStackTop-1];
		printf("current Scope = %d\n",currentScope);
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(2) - (2)]);
		strcpy(newNode->code,tempNode->code);
		printf("unlabelled compound\n");
		(yyval)=newNode;	
	}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 461 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);
		printf("cmpndStatement->unlabelledCompnd\n");
		(yyval)=newNode;	
	}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 470 "parser.y"
    {			/////check/////
		Node* newNode = createNode();
		Node* tempNode1 = (yyvsp[(1) - (2)]);
		Node* tempNode2 = (yyvsp[(2) - (2)]);
		sprintf(newNode->code,"%s:\n%s",tempNode1->identLex,tempNode2->code);
		(yyval)=newNode;	
		printf("labelled compoundstatement\n");
	}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 482 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (2)]);
		Node* tempNode = (yyvsp[(1) - (2)]);
		strcpy(newNode->code, tempNode->code);
		currentScope = scopeStack[scopeStackTop-1];
		(yyval) = newNode;
	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 492 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (3)]);
		Node* tempNode1=(yyvsp[(1) - (3)]);
		Node* tempNode2=(yyvsp[(3) - (3)]);
		sprintf(newNode->code,"%s%s",tempNode1->code,tempNode2->code);
		(yyval) = newNode;
	}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 506 "parser.y"
    {
		Node* newNode = createNode();
		//Node* tempNode = $1;
		strcpy(newNode->code,"");
		(yyval)=newNode;
	}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 514 "parser.y"
    {
		Node* newNode = createNode();
		//Node* tempNode = $1;
		strcpy(newNode->code,"");
		(yyval)=newNode;
	}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 521 "parser.y"
    {
		Node* newNode = createNode();
		//Node* tempNode = $1;
		strcpy(newNode->code,"");
		(yyval)=newNode;
	}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 529 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;
	}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 539 "parser.y"
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

  case 22:

/* Line 1455 of yacc.c  */
#line 559 "parser.y"
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

  case 23:

/* Line 1455 of yacc.c  */
#line 579 "parser.y"
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

  case 24:

/* Line 1455 of yacc.c  */
#line 602 "parser.y"
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

  case 25:

/* Line 1455 of yacc.c  */
#line 618 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boundPairList;
        newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node* tempNodeOne = (yyvsp[(1) - (3)]);
		Node* tempNodeTwo = (yyvsp[(3) - (3)]);
		int i;
		if (tempNodeOne->semTypeDef==storeBoundPairList && tempNodeTwo->semTypeDef==storeBoundPairList ){
			newNode->semTypeDef=storeBoundPairList;
			for(i=tempNodeOne->dim-1;i>=0;i--){
				newNode->lowerBound[i] = tempNodeOne->lowerBound[i];
				newNode->upperBound[i] = tempNodeOne->upperBound[i];
			}
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

  case 26:

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

  case 27:

/* Line 1455 of yacc.c  */
#line 659 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = arraySegment;
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
		for(i=tempNodeTwo->dim-1;i>=0;i--){
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

  case 28:

/* Line 1455 of yacc.c  */
#line 690 "parser.y"
    {	
		Node* newNode = createNode();
		newNode->type = arraySegment;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		Node *tempNodeOne = (yyvsp[(1) - (3)]);
		Node *tempNodeTwo = (yyvsp[(3) - (3)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* entry = lookUpInCurrentScope(tempNodeOne->identLex);
		if(entry==NULL){
			entry = addEntry(tempNodeOne->identLex);			
		}
		//Symbol *entry1=lookUpInCurrentScope(tempNodeTwo->identLex);
		int size =1;
		entry->dim = tempNodeTwo->dim;
		newNode->dim = tempNodeTwo->dim;
		int i;
		
		for(i=tempNodeTwo->dim-1;i>=0;i--){
			entry->lowerBound[i] = tempNodeTwo->lowerBound[i];
			entry->upperBound[i] = tempNodeTwo->upperBound[i];
			newNode->lowerBound[i] = tempNodeTwo->lowerBound[i];
			newNode->upperBound[i] = tempNodeTwo->upperBound[i];
			size = size*(tempNodeTwo->upperBound[i]-tempNodeTwo->lowerBound[i]+1);
		}
		entry->offset = symbolTable[currentScope].arrayOffset;
		symbolTable[currentScope].arrayOffset-=size*4;
		newNode->identLex=tempNodeTwo->identLex;
		strcat(newNode->identLex,",");		
		strcat(newNode->identLex,tempNodeOne->identLex);
		printf("arraySegment->arrayIdentifier,arraysegment== %s\n",newNode->identLex);		
		
				
		(yyval) = newNode;
		
	}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 730 "parser.y"
    {
				
		Node* tempNode0=(yyvsp[(-1) - (1)]);
		Node* tempNode1=(yyvsp[(1) - (1)]);
		currentScope = scopeStack[scopeStackTop-1];
		printf("\n\n%s recieved\n\n",tempNode1->identLex);
		printf("arrayList->arraySegment\n");
		char* pch;
		pch = strtok (tempNode1->identLex,",");
  		while (pch != NULL)
  		{
  			Symbol* symbolEntry=lookUpInCurrentScope(pch);
			if (symbolEntry!=NULL){
				symbolEntry->type=tempNode0->semTypeDef;//return 0;
			}
			else{
				symbolEntry = addEntry(pch);
				symbolEntry->type=tempNode0->semTypeDef;
				symbolEntry->dim=tempNode1->dim;
			}
  			pch = strtok (NULL, ",");
 		}
					 
		(yyval)=(yyvsp[(-1) - (1)]); ////check////
		
	}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 758 "parser.y"
    {
		Node* tempNode0=(yyvsp[(1) - (3)]);
		Node* tempNode1=(yyvsp[(3) - (3)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbolEntry=lookUpInCurrentScope(tempNode1->identLex);
		if (symbolEntry!=NULL){
			symbolEntry->type=tempNode0->semTypeDef;//return 0;
		}
		else{
			symbolEntry = addEntry(tempNode1->identLex);
			symbolEntry->type=tempNode0->semTypeDef;
			symbolEntry->dim=tempNode1->dim;
		}
		(yyval)=(yyvsp[(1) - (3)]); ////check////
		printf("arrayList->arrayList , arraySegment\n");
	}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 778 "parser.y"
    {
		//$$=$3;
	}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 786 "parser.y"
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

  case 33:

/* Line 1455 of yacc.c  */
#line 798 "parser.y"
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

  case 34:

/* Line 1455 of yacc.c  */
#line 810 "parser.y"
    {
				
	}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 816 "parser.y"
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

  case 36:

/* Line 1455 of yacc.c  */
#line 853 "parser.y"
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

  case 37:

/* Line 1455 of yacc.c  */
#line 868 "parser.y"
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

  case 38:

/* Line 1455 of yacc.c  */
#line 883 "parser.y"
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

  case 39:

/* Line 1455 of yacc.c  */
#line 901 "parser.y"
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
			sprintf(newNode->code,"%s%sl.s\t$f0,%d($sp)\nl.s\t$f1,%d($sp)\nadd\t$f2,$f0,$f1\ns.s\t$f2,%d($sp)\n",tempNode0->code,tempNode2->code,tempNode0->place,tempNode2->place,tempNode0->place);	
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

  case 40:

/* Line 1455 of yacc.c  */
#line 941 "parser.y"
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
			sprintf(newNode->code,"%s%sl.s\t$f0,%d($sp)\nl.s\t$f1,%d($sp)\nsub\t$f2,$f0,$f1\ns.s\t$f2,%d($sp)\n",tempNode0->code,tempNode2->code,tempNode0->place,tempNode2->place,tempNode0->place);
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

  case 41:

/* Line 1455 of yacc.c  */
#line 977 "parser.y"
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

  case 42:

/* Line 1455 of yacc.c  */
#line 992 "parser.y"
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

  case 43:

/* Line 1455 of yacc.c  */
#line 1025 "parser.y"
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

  case 44:

/* Line 1455 of yacc.c  */
#line 1067 "parser.y"
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

  case 45:

/* Line 1455 of yacc.c  */
#line 1083 "parser.y"
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

  case 46:

/* Line 1455 of yacc.c  */
#line 1110 "parser.y"
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

  case 47:

/* Line 1455 of yacc.c  */
#line 1125 "parser.y"
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

  case 48:

/* Line 1455 of yacc.c  */
#line 1140 "parser.y"
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

  case 49:

/* Line 1455 of yacc.c  */
#line 1172 "parser.y"
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

  case 50:

/* Line 1455 of yacc.c  */
#line 1188 "parser.y"
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

  case 51:

/* Line 1455 of yacc.c  */
#line 1203 "parser.y"
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

  case 52:

/* Line 1455 of yacc.c  */
#line 1219 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = realNumber;
		newNode->realValue = atof(yytext);
		newNode->semTypeDef=storeReal;
		(yyval) = newNode;
	}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1230 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = integer;
		newNode->intValue = atoi(yytext);
		printf("integer-> TOKEN_INTEGER %d\n",newNode->intValue);
		newNode->semTypeDef=storeInteger;  
		(yyval) = newNode;
	}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1242 "parser.y"
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

  case 55:

/* Line 1455 of yacc.c  */
#line 1260 "parser.y"
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

  case 56:

/* Line 1455 of yacc.c  */
#line 1276 "parser.y"
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

  case 57:

/* Line 1455 of yacc.c  */
#line 1294 "parser.y"
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

  case 58:

/* Line 1455 of yacc.c  */
#line 1337 "parser.y"
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

  case 59:

/* Line 1455 of yacc.c  */
#line 1357 "parser.y"
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

  case 60:

/* Line 1455 of yacc.c  */
#line 1379 "parser.y"
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

  case 61:

/* Line 1455 of yacc.c  */
#line 1394 "parser.y"
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

  case 62:

/* Line 1455 of yacc.c  */
#line 1412 "parser.y"
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

  case 63:

/* Line 1455 of yacc.c  */
#line 1450 "parser.y"
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

  case 64:

/* Line 1455 of yacc.c  */
#line 1464 "parser.y"
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

  case 65:

/* Line 1455 of yacc.c  */
#line 1482 "parser.y"
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

  case 66:

/* Line 1455 of yacc.c  */
#line 1495 "parser.y"
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

  case 67:

/* Line 1455 of yacc.c  */
#line 1516 "parser.y"
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

  case 68:

/* Line 1455 of yacc.c  */
#line 1528 "parser.y"
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

  case 69:

/* Line 1455 of yacc.c  */
#line 1548 "parser.y"
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

  case 70:

/* Line 1455 of yacc.c  */
#line 1560 "parser.y"
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

  case 71:

/* Line 1455 of yacc.c  */
#line 1580 "parser.y"
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

  case 72:

/* Line 1455 of yacc.c  */
#line 1592 "parser.y"
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

  case 73:

/* Line 1455 of yacc.c  */
#line 1611 "parser.y"
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

  case 74:

/* Line 1455 of yacc.c  */
#line 1637 "parser.y"
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

  case 75:

/* Line 1455 of yacc.c  */
#line 1649 "parser.y"
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

  case 76:

/* Line 1455 of yacc.c  */
#line 1662 "parser.y"
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

  case 77:

/* Line 1455 of yacc.c  */
#line 1679 "parser.y"
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

  case 78:

/* Line 1455 of yacc.c  */
#line 1794 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->type = relationalOperator;
		strcpy(newNode->identLex, yytext);
		(yyval) = newNode;
	}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1803 "parser.y"
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

  case 80:

/* Line 1455 of yacc.c  */
#line 1832 "parser.y"
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

  case 81:

/* Line 1455 of yacc.c  */
#line 1858 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef = storeReal;
		printf("Token_real\n");		
		(yyval) = new;

	}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1868 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeInteger;
		printf("Token_integer\n");
		(yyval) = new;	

	}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1879 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeBoolean;
		(yyval) = new;
	}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1889 "parser.y"
    {
	printf("typeDeclaration\n");
	//$$=$2;
	}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1897 "parser.y"
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

  case 86:

/* Line 1455 of yacc.c  */
#line 1916 "parser.y"
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

  case 87:

/* Line 1455 of yacc.c  */
#line 1927 "parser.y"
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

  case 88:

/* Line 1455 of yacc.c  */
#line 1938 "parser.y"
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

  case 89:

/* Line 1455 of yacc.c  */
#line 1952 "parser.y"
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

  case 90:

/* Line 1455 of yacc.c  */
#line 1964 "parser.y"
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

  case 91:

/* Line 1455 of yacc.c  */
#line 1982 "parser.y"
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

  case 93:

/* Line 1455 of yacc.c  */
#line 2006 "parser.y"
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

  case 94:

/* Line 1455 of yacc.c  */
#line 2031 "parser.y"
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

  case 95:

/* Line 1455 of yacc.c  */
#line 2051 "parser.y"
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

  case 97:

/* Line 1455 of yacc.c  */
#line 2069 "parser.y"
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

  case 98:

/* Line 1455 of yacc.c  */
#line 2080 "parser.y"
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

  case 99:

/* Line 1455 of yacc.c  */
#line 2094 "parser.y"
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

  case 100:

/* Line 1455 of yacc.c  */
#line 2108 "parser.y"
    {
		Node* newNode = createNode();
		Node *tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);
		(yyval) = (yyvsp[(1) - (1)]);
	}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 2116 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);
	}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 2128 "parser.y"
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

  case 104:

/* Line 1455 of yacc.c  */
#line 2146 "parser.y"
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
			if (symbol1->type==storeInteger && tmp2->semTypeDef==storeInteger){								
				// SYMBOL1>TYPE IS INTEGER  
				symbol1->value = tmp2->intValue;
				int offset;
				if(tmp1->isArray==1){
					offset = tmp1->place;
				}
				else{
					offset = symbol1->offset;
				}
				sprintf(new->code,"%s%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",tmp1->code,tmp2->code,tmp2->place,offset);
			}
			else if (symbol1->type==storeReal && tmp2->semTypeDef==storeReal){								
				// SYMBOL1>TYPE IS Real
		  		symbol1->realValue=tmp2->realValue;
				printf("assignmentStatement->identifier:= arithmeticexpression, realValue= %f,,%f\n",tmp2->realValue,symbol1->realValue);
				int offset;
				if(tmp1->isArray==1){
					offset = tmp1->place;
				}
				else{
					offset = symbol1->offset;
				}
				sprintf(new->code,"%s%sl.s\t$f0,%d($sp)\ns.s\t$f0,%d($sp)\n",tmp1->code,tmp2->code,tmp2->place,offset);
						
			}
			else if(symbol1->type==storeReal && tmp2->semTypeDef==storeInteger){
				symbol1->realValue = (tmp2->intValue)*1.0;
				int offset;
				if(tmp1->isArray==1){
					offset = tmp1->place;
				}
				else{
					offset = symbol1->offset;
				}
				sprintf(new->code,"%s%sl.s\t$f0,%d($sp)\ns.s\t$f0,%d($sp)\n",tmp1->code,tmp2->code,tmp2->place,offset);
			}
			else{	
				printf("inconsistent Types in assignment\n");
				new->semTypeDef = storeError;
			}
		}
		(yyval) = new;
	}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 2207 "parser.y"
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
			if (symbol2->type==storeBoolean==storeBoolean && temp2->semTypeDef==storeBoolean) {  
				symbol2->boolean=temp2->boolValue;
				int offset;
				if(temp1->isArray==1){
					offset = temp1->place;
				}
				else{
					offset = symbol2->offset;
				}
				sprintf(new->code,"%s%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",temp1->code,temp2->code,temp2->place,offset);
			}
		}
		(yyval) = new;
	}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 2418 "parser.y"
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

  case 107:

/* Line 1455 of yacc.c  */
#line 2458 "parser.y"
    {	
		printf("empty reached\n");
		Node *new = createNode();         	            	  
        	new->type =empty;
		(yyval) = new;
	}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 2466 "parser.y"
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

  case 109:

/* Line 1455 of yacc.c  */
#line 2498 "parser.y"
    {
		Node *new = createNode(); 
		new->type = procedureIdentifier;
		new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp=(yyvsp[(1) - (1)]);
		strcpy(new->identLex,temp->identLex);
		(yyval) = new;
	}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 2510 "parser.y"
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

  case 112:

/* Line 1455 of yacc.c  */
#line 2524 "parser.y"
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

  case 113:

/* Line 1455 of yacc.c  */
#line 2539 "parser.y"
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

  case 114:

/* Line 1455 of yacc.c  */
#line 2562 "parser.y"
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

  case 117:

/* Line 1455 of yacc.c  */
#line 2580 "parser.y"
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

  case 118:

/* Line 1455 of yacc.c  */
#line 2614 "parser.y"
    {
		Node* newNode=createNode();
		Node *tempNode=(yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;
		printf("stmt -> unconditionalstmt\n");
	}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 2624 "parser.y"
    {
		Node* newNode=createNode();
		Node *tempNode=(yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;

	}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 2634 "parser.y"
    {	Node* newNode=createNode();
		Node *tempNode=(yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;
	}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 2642 "parser.y"
    {
		Node* newNode=createNode();
		Node* tempNode=(yyvsp[(2) - (2)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		sprintf(newNode->code,"%sli\t$v0,4\nla\t$a0, MSG\nsyscall\nlw\t$t0,%d($sp)\nli\t$v0,1\nmove\t$a0,$t0\nsyscall\n",tempNode->code,tempNode->place);
		(yyval)=newNode;
	}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 2660 "parser.y"
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

  case 124:

/* Line 1455 of yacc.c  */
#line 2689 "parser.y"
    {   ////check/////
		(yyvsp[(1) - (3)])=(yyvsp[(0) - (3)]);
		(yyvsp[(2) - (3)])=(yyvsp[(0) - (3)]);
		printf("formalParmeterlist->formalParmeter\n");	
	}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 2697 "parser.y"
    {
		(yyval) = (yyvsp[(0) - (1)]);
	}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 2700 "parser.y"
    {
		(yyvsp[(1) - (1)]) = (yyvsp[(0) - (1)]);
	}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 2702 "parser.y"
    {
		printf("formalParmeterpart->(formalParmeterlist)\n");
	}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 2707 "parser.y"
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

  case 129:

/* Line 1455 of yacc.c  */
#line 2728 "parser.y"
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

  case 130:

/* Line 1455 of yacc.c  */
#line 2750 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 2755 "parser.y"
    {
		printf("specifier->type\n"); 
	}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 2766 "parser.y"
    {
		Node *node1 = (yyvsp[(1) - (3)]);
		printf("specificationidentlist->specifier identlist ;\n");

	}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 2772 "parser.y"
    {
		printf("specificationidentlist->specificationidentlist specifier identlist ;\n");

	}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 2778 "parser.y"
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

  case 142:

/* Line 1455 of yacc.c  */
#line 2791 "parser.y"
    {
		printf("the belu number of parameters defined is %d\n",paramBelu);
		(yyvsp[(3) - (4)]) = (yyvsp[(1) - (4)]);
	}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 2794 "parser.y"
    {
		printf("the belu number of parameters defined is %d\n",paramBelu);
	}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 2800 "parser.y"
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

  case 145:

/* Line 1455 of yacc.c  */
#line 2812 "parser.y"
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

  case 146:

/* Line 1455 of yacc.c  */
#line 2837 "parser.y"
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

  case 147:

/* Line 1455 of yacc.c  */
#line 2865 "parser.y"
    {
		Node* newNode=createNode();
		Node* tempNode = (yyvsp[(2) - (2)]);
		sprintf(newNode->code,"b\t%s\n",tempNode->identLex);
		(yyval)=newNode;
	}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 2881 "parser.y"
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

  case 152:

/* Line 1455 of yacc.c  */
#line 2895 "parser.y"
    {
		Node* newNode=createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex,tempNode->identLex);
		(yyval)=newNode;
	}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 2905 "parser.y"
    {
		Node* newNode=createNode();
		Node* tempNode = (yyvsp[(2) - (2)]);
		strcpy(newNode->identLex,tempNode->identLex);
		(yyval)=newNode;
	}
    break;



/* Line 1455 of yacc.c  */
#line 4693 "y.tab.c"
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
#line 2917 "parser.y"

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
	//printf("%s",code);
	FILE* fp1 = fopen("code1.asm","w");
	fprintf(fp1,"%s",code);
	return 0;
}


