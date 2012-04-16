
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

int scopeStack[100];
int scopeStackTop = 0;

int scopeId = 0;
int tableStackTop=0;

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
SymbolTable symbolTable[1000];
int tempNodeScope;
int currentScope;
int currentLabel = 0;
char code[10000];
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
	else
		return lookUp(lexm,symbolTable[scope].parent);
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
			printf("dim: %s\n",entry->dim);
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
#line 250 "y.tab.c"

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
#line 438 "y.tab.c"

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
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   397

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  90
/* YYNRULES -- Number of rules.  */
#define YYNRULES  159
/* YYNRULES -- Number of states.  */
#define YYNSTATES  268

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
       0,     0,     3,     4,     8,    12,    16,    18,    21,    24,
      26,    28,    30,    32,    33,    37,    39,    42,    45,    49,
      51,    53,    55,    57,    59,    61,    65,    70,    72,    76,
      78,    82,    84,    89,    93,    95,    99,   102,   106,   108,
     110,   112,   114,   119,   121,   123,   127,   129,   134,   136,
     138,   141,   144,   148,   152,   154,   158,   162,   164,   168,
     170,   172,   174,   178,   180,   182,   184,   186,   188,   190,
     192,   197,   199,   203,   205,   207,   209,   211,   215,   217,
     221,   223,   227,   229,   233,   235,   238,   240,   242,   246,
     248,   252,   254,   256,   260,   262,   264,   266,   269,   271,
     273,   275,   277,   279,   283,   286,   289,   292,   296,   298,
     301,   303,   305,   307,   309,   311,   314,   318,   322,   333,
     334,   337,   339,   342,   346,   348,   352,   354,   356,   361,
     364,   366,   368,   370,   373,   375,   377,   378,   383,   385,
     386,   391,   393,   397,   401,   403,   405,   408,   410,   412,
     415,   417,   419,   423,   428,   429,   430,   438,   443,   447
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      81,     0,    -1,    -1,     5,    76,    86,    -1,    75,    66,
      86,    -1,    75,    66,    85,    -1,    77,    -1,    79,    78,
      -1,    80,    30,    -1,   115,    -1,   109,    -1,    84,    -1,
      78,    -1,    -1,     5,    83,    85,    -1,    82,    -1,    79,
      84,    -1,   148,     6,    -1,   148,    66,    85,    -1,   128,
      -1,    96,    -1,    89,    -1,   163,    -1,   102,    -1,   101,
      -1,    88,    16,   101,    -1,    51,    98,    72,    88,    -1,
     102,    -1,    87,    30,    90,    -1,    91,    -1,    92,    16,
      91,    -1,   115,    -1,    93,    23,    92,    24,    -1,    93,
      16,    94,    -1,    94,    -1,    95,    16,    94,    -1,    64,
      95,    -1,   127,    64,    95,    -1,   102,    -1,   116,    -1,
     101,    -1,   115,    -1,    98,    25,   114,    26,    -1,    79,
      -1,    99,    -1,    21,   101,    22,    -1,   100,    -1,   133,
     100,    50,   101,    -1,   103,    -1,   104,    -1,    11,   104,
      -1,    12,   104,    -1,   103,    11,   104,    -1,   103,    12,
     104,    -1,   105,    -1,   104,    15,   105,    -1,   104,    13,
     105,    -1,   106,    -1,   105,    14,   106,    -1,   107,    -1,
     147,    -1,   111,    -1,    21,   102,    22,    -1,   108,    -1,
     109,    -1,    28,    -1,    29,    -1,   129,    -1,   110,    -1,
     112,    -1,    93,    23,   113,    24,    -1,   114,    -1,   113,
      16,   114,    -1,   102,    -1,     4,    -1,   117,    -1,   118,
      -1,   117,    38,   118,    -1,   119,    -1,   118,    65,   119,
      -1,   120,    -1,   119,    40,   120,    -1,   121,    -1,   120,
      39,   121,    -1,   122,    -1,    41,   122,    -1,   123,    -1,
     124,    -1,    21,   116,    22,    -1,     7,    -1,   103,   125,
     103,    -1,    31,    -1,   129,    -1,   126,    16,   129,    -1,
      56,    -1,    55,    -1,    57,    -1,   127,   126,    -1,   115,
      -1,   134,    -1,    84,    -1,    78,    -1,   132,    -1,   132,
      50,   148,    -1,   133,   139,    -1,    79,   131,    -1,   133,
     130,    -1,    48,   116,    49,    -1,   135,    -1,    79,   134,
      -1,   138,    -1,   136,    -1,   141,    -1,   137,    -1,   140,
      -1,    68,    97,    -1,   111,    72,   102,    -1,   111,    72,
     116,    -1,    43,   111,    72,   102,    46,   102,    47,   102,
      44,   148,    -1,    -1,   142,   143,    -1,   115,    -1,    21,
      22,    -1,    21,   144,    22,    -1,   145,    -1,   144,   146,
     145,    -1,    97,    -1,    16,    -1,    22,   115,    30,    21,
      -1,   142,   143,    -1,   130,    -1,   131,    -1,   139,    -1,
       3,    97,    -1,   115,    -1,   149,    -1,    -1,   150,   146,
     151,   149,    -1,   140,    -1,    -1,    21,   153,   150,    22,
      -1,   115,    -1,   154,    16,   115,    -1,    52,   154,    66,
      -1,   140,    -1,   127,    -1,   127,    64,    -1,    62,    -1,
      51,    -1,   127,    10,    -1,   140,    -1,   158,    -1,   156,
     154,    66,    -1,   158,   156,   154,    66,    -1,    -1,    -1,
     142,   160,   152,    66,   161,   155,   157,    -1,     5,    66,
     148,     6,    -1,    10,   159,   162,    -1,   127,    10,   159,
     162,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   301,   301,   300,   309,   316,   326,   336,   372,   380,
     386,   395,   407,   423,   423,   438,   445,   451,   461,   475,
     480,   485,   489,   496,   514,   515,   519,   522,   540,   560,
     573,   595,   608,   622,   639,   657,   677,   679,   686,   698,
     710,   716,   720,   723,   724,   725,   728,   729,   732,   769,
     784,   799,   817,   856,   891,   906,   939,   981,   997,  1022,
    1038,  1041,  1067,  1083,  1098,  1114,  1125,  1137,  1155,  1171,
    1187,  1215,  1231,  1250,  1264,  1282,  1320,  1334,  1352,  1365,
    1386,  1398,  1418,  1430,  1450,  1462,  1481,  1507,  1519,  1532,
    1549,  1664,  1673,  1699,  1723,  1733,  1744,  1763,  1771,  1790,
    1805,  1817,  1833,  1848,  1868,  1890,  1894,  1920,  1941,  1957,
    1961,  1975,  1989,  2002,  2009,  2013,  2031,  2063,  2269,  2310,
    2318,  2348,  2360,  2361,  2374,  2389,  2412,  2426,  2427,  2430,
    2433,  2443,  2453,  2461,  2479,  2494,  2495,  2495,  2502,  2505,
    2505,  2510,  2517,  2521,  2524,  2526,  2527,  2528,  2529,  2530,
    2532,  2533,  2535,  2539,  2542,  2554,  2542,  2559,  2571,  2589
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
  "blockHead", "$@1", "unlabelledBlock", "block", "tlabel", "label",
  "program", "unlabelledCompound", "@2", "compoundStatement",
  "compoundTail", "declaration", "lowerBound", "switchList",
  "switchDeclaration", "upperBound", "boundPair", "boundPairList",
  "arrayIdentifier", "arraySegment", "arrayList", "arrayDeclaration",
  "expression", "switchIdentifier", "switchDesignator",
  "simpleDesignationalExpression", "designationalExpression",
  "arithmeticExpression", "simpleArithmeticExpression", "term", "factor",
  "primary", "unsignedNumber", "realNumber", "integer", "simpleVariable",
  "variable", "subscriptedVariable", "subscriptList",
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
  "formalParameter", "formalParameterList", "$@3", "formalParameterPart",
  "$@4", "identifierList", "valuePart", "specifier", "specificationPart",
  "specificationIdentifierList", "procedureHeading", "@5", "$@6",
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
     325,   326,   327,   328
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    76,    75,    75,    77,    78,    78,    79,    80,
      80,    81,    81,    83,    82,    84,    84,    85,    85,    86,
      86,    86,    86,    87,    88,    88,    89,    90,    91,    92,
      92,    93,    94,    94,    95,    95,    96,    96,    97,    97,
      97,    98,    99,   100,   100,   100,   101,   101,   102,   103,
     103,   103,   103,   103,   104,   104,   104,   105,   105,   106,
     106,   106,   106,   107,   107,   108,   109,   110,   111,   111,
     112,   113,   113,   114,   115,   116,   117,   117,   118,   118,
     119,   119,   120,   120,   121,   121,   122,   122,   122,   123,
     124,   125,   126,   126,   127,   127,   127,   128,   129,   130,
     130,   130,   131,   131,   131,   131,   132,   133,   134,   134,
     135,   135,   135,   135,   136,   137,   138,   138,   139,   140,
     141,   142,   143,   143,   144,   144,   145,   146,   146,   147,
     148,   148,   148,   148,   149,   150,   151,   150,   152,   153,
     152,   154,   154,   155,   155,   156,   156,   156,   156,   156,
     157,   157,   158,   158,   160,   161,   159,   162,   163,   163
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     3,     1,     2,     2,     1,
       1,     1,     1,     0,     3,     1,     2,     2,     3,     1,
       1,     1,     1,     1,     1,     3,     4,     1,     3,     1,
       3,     1,     4,     3,     1,     3,     2,     3,     1,     1,
       1,     1,     4,     1,     1,     3,     1,     4,     1,     1,
       2,     2,     3,     3,     1,     3,     3,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     1,     1,     1,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     2,     1,     1,     3,     1,
       3,     1,     1,     3,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     3,     2,     2,     2,     3,     1,     2,
       1,     1,     1,     1,     1,     2,     3,     3,    10,     0,
       2,     1,     2,     3,     1,     3,     1,     1,     4,     2,
       1,     1,     1,     2,     1,     1,     0,     4,     1,     0,
       4,     1,     3,     3,     1,     1,     2,     1,     1,     2,
       1,     1,     3,     4,     0,     0,     7,     4,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    74,    13,    66,     0,     6,    12,     0,     0,     0,
      15,    11,    10,     9,     0,   119,   119,     7,    16,     8,
       1,     0,     0,    95,    94,    96,     0,     3,    21,    20,
       0,    19,    22,     0,     0,     0,     0,   101,   119,   100,
      14,     0,    68,     0,    69,     9,    67,   130,   131,   102,
     119,    99,   108,   111,   113,   110,   132,   114,   112,     0,
       0,     5,     4,   121,   154,     0,     0,    41,     0,    34,
      36,    31,     0,     0,    98,    97,    92,    89,     0,     0,
       0,    65,     0,    43,   133,     0,    44,    46,    40,    38,
      48,    49,    54,    57,    59,    63,    64,    61,    98,    39,
      75,    76,    78,    80,    82,    84,    86,    87,     0,     0,
      60,     0,    31,     0,     0,    64,    98,     0,   115,   105,
     109,     0,     0,   119,   119,   106,   104,     0,   120,    17,
     119,   119,     0,   158,     0,     0,     0,     0,     0,    37,
       0,     0,    50,    51,     0,     0,     0,    85,     0,     0,
       0,    91,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     9,   129,     0,   107,    73,    48,     0,    71,
     116,   117,   103,   122,   126,     0,   124,    18,   139,   138,
       0,   119,    26,    24,    33,     0,    29,     0,    23,    35,
     159,    93,    45,    62,    88,     0,    52,    53,    90,    56,
      55,    58,    77,    79,    81,    83,     0,     0,     0,    70,
     127,   123,     0,     0,   155,     0,     0,     0,     0,    32,
      42,    47,     0,    72,     0,   125,   134,   135,     0,   119,
     157,    25,    28,    27,    30,     0,     0,   140,   136,     0,
     144,   119,     0,   128,     0,   141,     0,   148,   147,   145,
     150,     0,   156,   151,     0,   137,     0,   143,   149,   146,
       0,     0,   119,   142,   152,     0,   118,   153
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    14,     5,    37,    83,     8,     9,    10,    15,
      39,    40,    27,   185,   182,    28,   232,   186,   187,    41,
      69,    70,    29,   174,    85,    86,    87,    88,    89,   167,
      91,    92,    93,    94,    95,   115,    42,    97,    44,   168,
     169,   116,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   152,    75,    30,    31,    46,    47,    48,    49,   108,
      51,    52,    53,    54,    55,    56,    57,    58,   109,   128,
     175,   176,   212,   110,    60,   227,   228,   244,   180,   213,
     246,   241,   251,   252,   253,    65,   131,   229,   133,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -193
static const yytype_int16 yypact[] =
{
     109,  -193,   134,  -193,   -52,  -193,  -193,   109,    -7,    32,
    -193,  -193,  -193,  -193,   245,   216,   263,  -193,  -193,  -193,
    -193,    43,    43,  -193,  -193,  -193,    43,  -193,  -193,  -193,
      75,  -193,  -193,   341,    43,   356,   341,  -193,    78,  -193,
    -193,    30,  -193,   -14,  -193,    31,  -193,  -193,  -193,    21,
     158,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,    46,
      11,  -193,  -193,  -193,  -193,   101,    22,  -193,    89,  -193,
     125,  -193,    43,    43,  -193,   143,  -193,  -193,   189,   189,
     341,  -193,   367,  -193,  -193,   157,  -193,  -193,  -193,  -193,
     164,   137,   174,  -193,  -193,  -193,   162,  -193,   260,  -193,
     159,   138,   169,   193,  -193,  -193,  -193,  -193,    72,    46,
    -193,   156,   163,   356,   164,  -193,   220,   199,  -193,  -193,
    -193,   242,   356,   216,    41,  -193,  -193,   318,  -193,  -193,
     216,   217,   186,  -193,   175,    43,   242,    43,   101,   125,
      43,   242,   137,   137,   235,   243,   247,  -193,   242,   189,
     189,  -193,   242,   189,   189,   189,   356,   356,   356,   356,
     175,   224,   255,  -193,   242,  -193,  -193,   203,   141,  -193,
    -193,  -193,  -193,  -193,  -193,    80,  -193,  -193,  -193,  -193,
     221,   216,   266,  -193,  -193,   258,  -193,   145,  -193,  -193,
    -193,  -193,  -193,  -193,  -193,   265,   137,   137,   203,   174,
     174,  -193,   138,   169,   193,  -193,   175,   249,   242,  -193,
    -193,    43,   341,    43,  -193,   283,   175,   242,   242,  -193,
    -193,  -193,   242,  -193,   267,  -193,  -193,  -193,   148,   241,
    -193,  -193,  -193,  -193,  -193,   251,   278,    43,  -193,    43,
    -193,   287,   242,  -193,    43,  -193,    53,  -193,  -193,    17,
    -193,    43,  -193,   287,   261,  -193,    43,  -193,  -193,  -193,
      59,    43,   216,  -193,  -193,    76,  -193,  -193
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -193,  -193,  -193,  -193,     4,    48,  -193,  -193,  -193,  -193,
       5,   -15,   291,  -193,  -193,  -193,  -193,    95,  -193,   -17,
     123,   244,  -193,   150,   293,  -193,   208,   -39,    86,   120,
     -59,    71,   166,  -193,  -193,    24,  -193,    50,  -193,  -193,
    -130,     0,     9,  -193,   167,   176,   168,   165,   252,  -193,
    -193,  -193,  -193,  -192,  -193,   -24,   285,   298,  -193,    13,
     -25,  -193,  -193,  -193,  -193,   300,   -96,  -193,   -13,   228,
    -193,   129,   126,  -193,  -113,   107,  -193,  -193,  -193,  -193,
    -164,  -193,   102,  -193,  -193,   284,  -193,  -193,   219,  -193
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -122
static const yytype_int16 yytable[] =
{
      13,    61,    59,    59,     6,    11,    76,    13,    64,    68,
     172,    17,    18,   120,    16,    45,    45,   129,   195,   142,
     143,    63,    67,    19,    12,    59,    71,   258,    50,    50,
      74,    12,    20,    98,   112,   179,    98,    59,    45,    12,
      12,   144,    17,    18,   117,     1,     2,     1,     7,   249,
      45,    50,  -121,   121,   -31,     7,    68,    96,   122,    64,
      96,   249,    12,    38,    38,    43,    43,   127,   215,   256,
       3,   123,    63,    71,    12,   256,     1,   130,   223,     1,
      98,   259,     1,     2,   111,    72,    38,   260,    43,   146,
     196,   197,   256,   160,   134,   183,   210,   265,   124,   120,
      43,     3,   211,   -98,    96,   135,   132,     3,   162,    36,
      59,    59,   136,     1,     2,   177,   191,    59,    68,   257,
      68,   144,   146,    45,    45,   264,    35,    98,    17,    18,
      45,   171,    12,   240,   162,    71,    50,    71,     3,    73,
      74,   137,   267,    50,    -2,   250,    36,    12,    12,   266,
     153,    96,   154,    90,    12,   114,    90,   208,    12,   140,
     162,   218,     1,     2,   210,   209,   145,   221,    59,   219,
     237,    38,   124,    43,    43,   149,   150,   231,    38,     1,
      43,    45,   148,    84,    12,    -2,   118,     3,   155,    -2,
      -2,    -2,   -10,     1,    50,   151,   160,   156,    -2,   145,
      90,    34,   114,   157,     3,    12,   162,   166,   170,   158,
     141,   224,    98,   226,   149,   150,   162,    81,     3,    33,
       1,     2,   188,    35,   199,   200,    36,   145,   164,    38,
      12,    43,   159,    90,   166,   -98,    96,   224,   178,   245,
      12,  -121,    90,   -31,   226,     3,     1,    90,   165,    59,
     207,   245,   181,    78,    79,    21,   263,   192,   184,    34,
     189,   245,    45,   141,    35,   193,    33,     1,     2,   194,
      81,     3,   198,    21,   206,    50,   114,   114,   114,   114,
     -41,  -121,   216,   -31,    36,   -41,    12,   214,   217,   230,
      -9,   220,     3,   239,   166,   222,    22,   236,   242,   243,
      23,    24,    25,   233,   188,   262,    34,    62,   235,    26,
      38,    35,    43,   234,    22,    66,   161,   139,    23,    24,
      25,   201,     1,   202,   205,    77,   204,    26,   254,    78,
      79,    36,    90,   203,   147,   125,   119,   163,   247,    80,
     173,   225,    23,    24,    25,     1,    81,     3,    77,   248,
     126,   255,    78,    79,   238,   261,   138,   190,     0,    82,
       1,     0,    80,    77,     0,     0,    35,    78,    79,    81,
       3,     1,     0,     0,    77,     0,     0,   113,    78,    79,
       0,     0,    82,     0,    81,     3,     0,     0,   113,    35,
       0,     0,     0,     0,     0,    81,     3,    82
};

static const yytype_int16 yycheck[] =
{
       0,    16,    15,    16,     0,     0,    30,     7,    21,    26,
     123,     7,     7,    38,    66,    15,    16,     6,   148,    78,
      79,    21,    22,    30,     0,    38,    26,    10,    15,    16,
      30,     7,     0,    33,    34,   131,    36,    50,    38,    15,
      16,    80,    38,    38,    35,     4,     5,     4,     0,   241,
      50,    38,    21,    23,    23,     7,    73,    33,    72,    72,
      36,   253,    38,    15,    16,    15,    16,    21,   181,    16,
      29,    50,    72,    73,    50,    16,     4,    66,   208,     4,
      80,    64,     4,     5,    34,    10,    38,   251,    38,    80,
     149,   150,    16,    21,    72,   134,    16,   261,    50,   124,
      50,    29,    22,    72,    80,    16,     5,    29,   108,    68,
     123,   124,    23,     4,     5,   130,   140,   130,   135,    66,
     137,   160,   113,   123,   124,    66,    48,   127,   124,   124,
     130,   122,   108,   229,   134,   135,   123,   137,    29,    64,
     140,    16,    66,   130,    10,   241,    68,   123,   124,   262,
      13,   127,    15,    33,   130,    35,    36,    16,   134,    16,
     160,    16,     4,     5,    16,    24,    80,   206,   181,    24,
      22,   123,   124,   123,   124,    11,    12,   216,   130,     4,
     130,   181,    25,    33,   160,    51,    36,    29,    14,    55,
      56,    57,    30,     4,   181,    31,    21,    38,    64,   113,
      80,    43,    82,    65,    29,   181,   206,   121,   122,    40,
      21,   211,   212,   213,    11,    12,   216,    28,    29,     3,
       4,     5,   136,    48,   153,   154,    68,   141,    72,   181,
     206,   181,    39,   113,   148,    72,   212,   237,    21,   239,
     216,    21,   122,    23,   244,    29,     4,   127,    49,   262,
     164,   251,    66,    11,    12,    10,   256,    22,   135,    43,
     137,   261,   262,    21,    48,    22,     3,     4,     5,    22,
      28,    29,   152,    10,    50,   262,   156,   157,   158,   159,
      25,    21,    16,    23,    68,    25,   262,    66,    30,     6,
      30,    26,    29,    52,   208,    46,    51,    30,    47,    21,
      55,    56,    57,   217,   218,    44,    43,    16,   222,    64,
     262,    48,   262,   218,    51,    22,   108,    73,    55,    56,
      57,   155,     4,   156,   159,     7,   158,    64,   242,    11,
      12,    68,   212,   157,    82,    50,    38,   109,    51,    21,
      22,   212,    55,    56,    57,     4,    28,    29,     7,    62,
      50,   244,    11,    12,   228,   253,    72,   138,    -1,    41,
       4,    -1,    21,     7,    -1,    -1,    48,    11,    12,    28,
      29,     4,    -1,    -1,     7,    -1,    -1,    21,    11,    12,
      -1,    -1,    41,    -1,    28,    29,    -1,    -1,    21,    48,
      -1,    -1,    -1,    -1,    -1,    28,    29,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    29,    75,    77,    78,    79,    80,    81,
      82,    84,   109,   115,    76,    83,    66,    78,    84,    30,
       0,    10,    51,    55,    56,    57,    64,    86,    89,    96,
     127,   128,   163,     3,    43,    48,    68,    78,    79,    84,
      85,    93,   110,   111,   112,   115,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     148,    85,    86,   115,   142,   159,    98,   115,    93,    94,
      95,   115,    10,    64,   115,   126,   129,     7,    11,    12,
      21,    28,    41,    79,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   111,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   133,   142,
     147,   111,   115,    21,   103,   109,   115,   116,    97,   131,
     134,    23,    72,    50,    79,   130,   139,    21,   143,     6,
      66,   160,     5,   162,    72,    16,    23,    16,   159,    95,
      16,    21,   104,   104,   101,   102,   116,   122,    25,    11,
      12,    31,   125,    13,    15,    14,    38,    65,    40,    39,
      21,   100,   115,   143,    72,    49,   102,   103,   113,   114,
     102,   116,   148,    22,    97,   144,   145,    85,    21,   140,
     152,    66,    88,   101,    94,    87,    91,    92,   102,    94,
     162,   129,    22,    22,    22,   114,   104,   104,   103,   105,
     105,   106,   118,   119,   120,   121,    50,   102,    16,    24,
      16,    22,   146,   153,    66,   148,    16,    30,    16,    24,
      26,   101,    46,   114,   115,   145,   115,   149,   150,   161,
       6,   101,    90,   102,    91,   102,    30,    22,   146,    52,
     140,   155,    47,    21,   151,   115,   154,    51,    62,   127,
     140,   156,   157,   158,   102,   149,    16,    66,    10,    64,
     154,   156,    44,   115,    66,   154,   148,    66
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
#line 301 "parser.y"
    {
		currentScope = scopeStack[scopeStackTop-1];
		printf("current Scope = %d\n",currentScope);
	}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 306 "parser.y"
    {
		printf("blockHead\n");
	}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 310 "parser.y"
    {
		printf("blockHead\n");
	}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 317 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode =(Node*) (yyvsp[(3) - (3)]);
		newNode->pt0 = (Node*) (yyvsp[(3) - (3)]);
		strcpy(newNode->code, tempNode->code);
		(yyval) = newNode;
	}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 327 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		sprintf(newNode->code,tempNode->code);
		(yyval) = newNode;
		printf("unlabelled block\n");
	}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 345 "parser.y"
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

  case 8:

/* Line 1455 of yacc.c  */
#line 373 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (2)]);
		strcpy(newNode->identLex,tempNode->identLex);
	}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 381 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex,tempNode->identLex);
	}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 387 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->identLex,atoi(tempNode->intValue));
	}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 396 "parser.y"
    {
		printf("compoundStatement\n");
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);
		strcpy(code,newNode->code);
		symbolTableDisplay(0);
		symbolTableDisplay(1);
		symbolTableDisplay(2);
	}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 408 "parser.y"
    {
		printf("block\n");
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);
		strcpy(code,newNode->code);
		symbolTableDisplay(0);
		symbolTableDisplay(1);
		symbolTableDisplay(2);
	}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 423 "parser.y"
    {
		currentScope = scopeStack[scopeStackTop-1];
		printf("current Scope = %d\n",currentScope);
	}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 427 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(2) - (3)]);
		strcpy(newNode->code,tempNode->code);
		printf("unlabelled compound\n");
	}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 439 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode = (yyvsp[(1) - (1)]);
		strcpy(newNode->code,tempNode->code);		
	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 445 "parser.y"
    {
		printf("labelled compoundstatement\n");
	}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 452 "parser.y"
    {
		printf("compound tail\n");
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (2)]);
		Node* tempNode = (yyvsp[(1) - (2)]);
		strcpy(newNode->code, tempNode->code);
		(yyval) = newNode;
	}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 462 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (3)]);
		Node* tempNode1=(yyvsp[(1) - (3)]);
		Node* tempNode2=(yyvsp[(3) - (3)]);
		sprintf(newNode->code,"%s%s",tempNode1->code,tempNode2->code);
		(yyval) = newNode;
	}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 476 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 481 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 485 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 490 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 497 "parser.y"
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
		printf("lowerBound->arithmeticExpression\n");
	}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 523 "parser.y"
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
		printf("upperBound->arithmeticExpression\n");
	}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 541 "parser.y"
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
		printf("boundPair->lowerBound : upperBound\n");
	}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 561 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boundPairList;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		if (tempNode->semTypeDef==storeBoundPairList) {  
			newNode->semTypeDef=tempNode->semTypeDef;
		}
		(yyval) = newNode;
		printf("boundPairList->boundPair\n");
	}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 574 "parser.y"
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
		
		newNode->dim = tempNodeOne->dim + 1 ;  	
		(yyval) = newNode;
		printf("boundPairList->boundPairList , boundPair\n");
	}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 596 "parser.y"
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

  case 32:

/* Line 1455 of yacc.c  */
#line 609 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boundPair;
		newNode->pt0 = (yyvsp[(1) - (4)]);
		newNode->pt2 = (yyvsp[(3) - (4)]);

		Node *tempNodeOne = (yyvsp[(1) - (4)]);
		Node *tempNodeTwo = (yyvsp[(3) - (4)]);
		newNode->dim = tempNodeTwo->dim;
		newNode->identLex = tempNodeOne->identLex;
		(yyval) = newNode;
		printf("arraySegment->arrayIdentifier [ boundPairList ]\n");
	}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 623 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boundPair;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);

		Node *tempNodeOne = (yyvsp[(1) - (3)]);
		Node *tempNodeTwo = (yyvsp[(3) - (3)]);
		newNode->dim = tempNodeTwo->dim;
		newNode->identLex = tempNodeOne->identLex;
		(yyval) = newNode;
		printf("arraySegment->arrayIdentifier [ boundPairList ]\n");
	}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 640 "parser.y"
    {
		Node* tempNode0=(yyvsp[(0) - (1)]);
		Node* tempNode1=(yyvsp[(1) - (1)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbolEntry=lookUpInCurrentScope(tempNode1->identLex);
		if (symbolEntry!=NULL){
			return 0;
		}
		else{
			symbolEntry = addEntry(tempNode1->identLex);
			symbolTable[currentScope].currentSymbol->type=tempNode1->semTypeDef;
			symbolTable[currentScope].currentSymbol->dim=tempNode1->dim;
			(yyval)=(yyvsp[(0) - (1)]);
		}
		printf("arrayList->arraySegment\n");
	}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 658 "parser.y"
    {
		Node* tempNode0=(yyvsp[(1) - (3)]);
		Node* tempNode1=(yyvsp[(3) - (3)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbolEntry=lookUpInCurrentScope(tempNode1->identLex);
		if (symbolEntry!=NULL){
			return 0;
		}
		else{
			symbolEntry = addEntry(tempNode1->identLex);
			symbolTable[currentScope].currentSymbol->type=tempNode1->semTypeDef;
			symbolTable[currentScope].currentSymbol->dim=tempNode1->dim;
			(yyval)=(yyvsp[(0) - (3)]);
		}
		printf("arrayList->arrayList , arraySegment\n");
	}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 680 "parser.y"
    {printf("here\n");}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 687 "parser.y"
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
#line 699 "parser.y"
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

  case 40:

/* Line 1455 of yacc.c  */
#line 711 "parser.y"
    {
				
	}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 733 "parser.y"
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

  case 49:

/* Line 1455 of yacc.c  */
#line 770 "parser.y"
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

  case 50:

/* Line 1455 of yacc.c  */
#line 785 "parser.y"
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

  case 51:

/* Line 1455 of yacc.c  */
#line 800 "parser.y"
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

  case 52:

/* Line 1455 of yacc.c  */
#line 818 "parser.y"
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

  case 53:

/* Line 1455 of yacc.c  */
#line 857 "parser.y"
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

  case 54:

/* Line 1455 of yacc.c  */
#line 892 "parser.y"
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

  case 55:

/* Line 1455 of yacc.c  */
#line 907 "parser.y"
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

  case 56:

/* Line 1455 of yacc.c  */
#line 940 "parser.y"
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

  case 57:

/* Line 1455 of yacc.c  */
#line 982 "parser.y"
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

  case 58:

/* Line 1455 of yacc.c  */
#line 998 "parser.y"
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

  case 59:

/* Line 1455 of yacc.c  */
#line 1023 "parser.y"
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
#line 1038 "parser.y"
    {
	}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 1042 "parser.y"
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
			int offset = foundEntry->offset;
			sprintf(newNode->code,"%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",tempNode->code,offset,newNode->place);	
		}
		else
			printf("error belu\n");		
		(yyval) = newNode;

		
	}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1068 "parser.y"
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

  case 63:

/* Line 1455 of yacc.c  */
#line 1084 "parser.y"
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

  case 64:

/* Line 1455 of yacc.c  */
#line 1099 "parser.y"
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

  case 65:

/* Line 1455 of yacc.c  */
#line 1115 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = realNumber;
		newNode->realValue = atof(yytext);
		newNode->semTypeDef=storeReal;
		(yyval) = newNode;
	}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1126 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = integer;
		newNode->intValue = atoi(yytext);
		printf("integer-> TOKEN_INTEGER %d\n",newNode->intValue);
		newNode->semTypeDef=storeInteger;  
		(yyval) = newNode;
	}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1138 "parser.y"
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

  case 68:

/* Line 1455 of yacc.c  */
#line 1156 "parser.y"
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

  case 69:

/* Line 1455 of yacc.c  */
#line 1172 "parser.y"
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

  case 70:

/* Line 1455 of yacc.c  */
#line 1188 "parser.y"
    {
		Node* newNode = createNode();
		               	  
		newNode->type = subscriptedVariable;
		newNode->pt0 = (yyvsp[(1) - (4)]);
		newNode->pt2 = (yyvsp[(3) - (4)]);
		Node* tempNode0 = (yyvsp[(1) - (4)]);
		Node* tempNode1 = (yyvsp[(3) - (4)]);
		strcpy(newNode->identLex, tempNode0->identLex);
		currentScope = scopeStack[scopeStackTop-1];
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

  case 71:

/* Line 1455 of yacc.c  */
#line 1216 "parser.y"
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

  case 72:

/* Line 1455 of yacc.c  */
#line 1232 "parser.y"
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

  case 73:

/* Line 1455 of yacc.c  */
#line 1251 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = subscriptExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		(yyval) = newNode;
		printf("subscriptedExpression->arithmeticExpression\n");
	}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1265 "parser.y"
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

  case 75:

/* Line 1455 of yacc.c  */
#line 1283 "parser.y"
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

  case 76:

/* Line 1455 of yacc.c  */
#line 1321 "parser.y"
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

  case 77:

/* Line 1455 of yacc.c  */
#line 1335 "parser.y"
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

  case 78:

/* Line 1455 of yacc.c  */
#line 1353 "parser.y"
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

  case 79:

/* Line 1455 of yacc.c  */
#line 1366 "parser.y"
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

  case 80:

/* Line 1455 of yacc.c  */
#line 1387 "parser.y"
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

  case 81:

/* Line 1455 of yacc.c  */
#line 1399 "parser.y"
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

  case 82:

/* Line 1455 of yacc.c  */
#line 1419 "parser.y"
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

  case 83:

/* Line 1455 of yacc.c  */
#line 1431 "parser.y"
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

  case 84:

/* Line 1455 of yacc.c  */
#line 1451 "parser.y"
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

  case 85:

/* Line 1455 of yacc.c  */
#line 1463 "parser.y"
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

  case 86:

/* Line 1455 of yacc.c  */
#line 1482 "parser.y"
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

  case 87:

/* Line 1455 of yacc.c  */
#line 1508 "parser.y"
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

  case 88:

/* Line 1455 of yacc.c  */
#line 1520 "parser.y"
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

  case 89:

/* Line 1455 of yacc.c  */
#line 1533 "parser.y"
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

  case 90:

/* Line 1455 of yacc.c  */
#line 1550 "parser.y"
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

  case 91:

/* Line 1455 of yacc.c  */
#line 1665 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->type = relationalOperator;
		strcpy(newNode->identLex, yytext);
		(yyval) = newNode;
	}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1674 "parser.y"
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
			newEntry->offset=symbolTable[currentScope].currentOffset;
			symbolTable[currentScope].currentOffset-=4;
			printf("belu semtypedef : %d\n", newEntry->type);	
			(yyval)=(yyvsp[(0) - (1)]);			


		}

	}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1700 "parser.y"
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
			newEntry->offset=symbolTable[currentScope].currentOffset;
			symbolTable[currentScope].currentOffset-=4;
		}
		(yyval)=(yyvsp[(0) - (3)]);

		
	}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1724 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef = storeReal;
		printf("Token_real\n");		
		(yyval) = new;

	}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1734 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeInteger;
		printf("Token_integer\n");
		(yyval) = new;	

	}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1745 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeBoolean;
		(yyval) = new;



	}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1764 "parser.y"
    {
	printf("typeDeclaration\n");

	}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1772 "parser.y"
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

  case 99:

/* Line 1455 of yacc.c  */
#line 1791 "parser.y"
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

  case 100:

/* Line 1455 of yacc.c  */
#line 1805 "parser.y"
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
#line 1817 "parser.y"
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

  case 102:

/* Line 1455 of yacc.c  */
#line 1834 "parser.y"
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

  case 103:

/* Line 1455 of yacc.c  */
#line 1849 "parser.y"
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

  case 104:

/* Line 1455 of yacc.c  */
#line 1869 "parser.y"
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

  case 106:

/* Line 1455 of yacc.c  */
#line 1895 "parser.y"
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

  case 107:

/* Line 1455 of yacc.c  */
#line 1921 "parser.y"
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

  case 108:

/* Line 1455 of yacc.c  */
#line 1941 "parser.y"
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

  case 110:

/* Line 1455 of yacc.c  */
#line 1962 "parser.y"
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

  case 111:

/* Line 1455 of yacc.c  */
#line 1976 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  

		new->semTypeDef=temp->semTypeDef ;  

		(yyval) = new;

	}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1990 "parser.y"
    {
			
		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  
		(yyval) = new;
		printf("unlabelledbasicstmt -> procstmt\n");

	}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 2003 "parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 2014 "parser.y"
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

  case 116:

/* Line 1455 of yacc.c  */
#line 2032 "parser.y"
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
				symbol1->value=tmp2->intValue;
				int offset = symbol1->offset;
				sprintf(new->code,"%s%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",tmp1->code,tmp2->code,tmp2->place,offset);
			}
			else if (symbol1->type==storeReal && tmp2->semTypeDef==storeReal){								
				// SYMBOL1>TYPE IS Real
		  		symbol1->realValue=tmp2->realValue;
				printf("assignmentStatement->identifier:= arithmeticexpression, realValue= %f,,%f\n",tmp2->realValue,symbol1->realValue);		
			}
		
		}
		(yyval) = new;
	}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 2064 "parser.y"
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
				int offset = symbol2->offset;
				sprintf(new->code,"%s%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",temp1->code,temp2->code,temp2->place,offset);
			}
		}
		(yyval) = new;
	}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 2270 "parser.y"
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

  case 119:

/* Line 1455 of yacc.c  */
#line 2310 "parser.y"
    {	
		printf("empty reached\n");
		Node *new = createNode();         	            	  
        	new->type =empty;
		(yyval) = new;
	}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 2318 "parser.y"
    {
		Node *new = createNode();
		Node *temp1 = (yyvsp[(1) - (2)]);
		currentScope = scopeStack[scopeStackTop-1];
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

  case 121:

/* Line 1455 of yacc.c  */
#line 2349 "parser.y"
    {
		Node *new = createNode(); 
		new->type = procedureIdentifier;
		new->pt0 = (yyvsp[(1) - (1)]);
	
		Node *temp=(yyvsp[(1) - (1)]);

		(yyval) = new;
	}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 2362 "parser.y"
    {
		(yyval)=(yyvsp[(2) - (3)]);
		Node *temp = (yyvsp[(2) - (3)]);
		if(temp->semTypeDef != storeError)
		{		
			temp->semTypeDef == storeVoid;
		}
		printf("actparampart -> ( act param list )\n");
	}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 2375 "parser.y"
    {
		Node *temp = (yyvsp[(-1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbol= lookUp(temp1->identLex,currentScope);
		Node *new = createNode();
		new->intValue = 0;
		
		new->semTypeDef = storeVoid;
		
		(yyval) = new;
		printf("actual parameter list -> actual parameter\n");
	}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 2390 "parser.y"
    {
		Node *temp = (yyvsp[(-1) - (3)]);
		Node *temp3 = (yyvsp[(1) - (3)]);
		Node *temp1 = (yyvsp[(3) - (3)]);
		currentScope = scopeStack[scopeStackTop-1];
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

  case 126:

/* Line 1455 of yacc.c  */
#line 2413 "parser.y"
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

  case 130:

/* Line 1455 of yacc.c  */
#line 2434 "parser.y"
    {
		Node* newNode=createNode();
		Node *tempNode=(yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;
		printf("stmt -> unconditionalstmt\n");
	}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 2444 "parser.y"
    {
		Node* newNode=createNode();
		Node *tempNode=(yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;

	}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 2454 "parser.y"
    {	Node* newNode=createNode();
		Node *tempNode=(yyvsp[(1) - (1)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		(yyval)=newNode;
	}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 2462 "parser.y"
    {
		Node* newNode=createNode();
		Node* tempNode=(yyvsp[(2) - (2)]);
		newNode->semTypeDef = tempNode->semTypeDef;
		sprintf(newNode->code,"%sli\t$v0,4\nla\t$a0, MSG\nsyscall\nlw\t$t0,%d($sp)\nli\t$v0,1\nmove\t$a0,$t0\nsyscall\n",tempNode->code,tempNode->place);
		(yyval)=newNode;
	}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 2480 "parser.y"
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

  case 136:

/* Line 1455 of yacc.c  */
#line 2495 "parser.y"
    {   ////check/////
		(yyvsp[(1) - (2)]) = (yyvsp[(0) - (2)]); 
		(yyvsp[(2) - (2)]) = (yyvsp[(0) - (2)]);
	}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 2502 "parser.y"
    {
		(yyval) = (yyvsp[(0) - (1)]);
	}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 2505 "parser.y"
    {
		(yyvsp[(1) - (1)]) = (yyvsp[(0) - (1)]);
	}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 2510 "parser.y"
    {
		Node *node1 = (yyvsp[(0) - (1)]);
		Node *node2 = (yyvsp[(1) - (1)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol *symbol = lookUp(node2->identLex,currentScope);
		symbol->type = node1->semTypeDef;
	}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 2517 "parser.y"
    {
		(yyvsp[(2) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 2521 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 2535 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
		Node *node1 = (yyvsp[(1) - (3)]);
	}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 2542 "parser.y"
    {
		Node *node = createNode();
		node->type = procedureHeading;
		node->pt0 = (yyvsp[(1) - (1)]);
		Node *node1 = (yyvsp[(1) - (1)]);
		node1->parent = node;
		strcpy(node->identLex, node1->identLex);
		currentScope = scopeStack[scopeStackTop-1];
		if (lookUpInCurrentScope(node1->identLex) == NULL){
			Symbol * index = addEntry(node1->identLex);
		}
		(yyval) = node;
	}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 2554 "parser.y"
    {
		(yyvsp[(3) - (4)]) = (yyvsp[(1) - (4)]);
	}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 2559 "parser.y"
    {//changed 16th april
		Node *new = createNode();
		
		new->type = procedureBody;
		Node *temp = (yyvsp[(1) - (4)]);
		new->semTypeDef = temp->semTypeDef;
		strcpy(new->code,temp->code);
		(yyval) = new;
		printf("proc body -> stmt\n");
	}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 2571 "parser.y"
    {
		Node *node1 = (yyvsp[(2) - (3)]);
		Node *node2 = (yyvsp[(3) - (3)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbol = lookUp(node1->identLex, currentScope);////check////
		symbol->type = storeVoid;

		Node *node = createNode();
                
        	node->type = procedureDeclaration;

		if (node1->semTypeDef == storeVoid && node2->semTypeDef == storeVoid)
			node->semTypeDef = storeVoid;
		else
			node->semTypeDef = storeError;
		(yyval) = node;
		printf("procedureDeclaration -> procedure heading body");
	}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 2590 "parser.y"
    {
		Node *node1 = (yyvsp[(3) - (4)]);
		Node *node2 = (yyvsp[(1) - (4)]);
		Node *node3 = (yyvsp[(4) - (4)]);
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbol = lookUpInCurrentScope(node1->identLex);
		symbol->type = node2->semTypeDef;

		Node *node = createNode();
                
        	node->type = procedureDeclaration;

		if (node1->semTypeDef == storeVoid && node3->semTypeDef == storeVoid)
			node->semTypeDef = node2->semTypeDef;
		else
			node->semTypeDef = storeError;
		(yyval) = node;
		printf("proceduredeclaration -> type procedure heading body\n");
	}
    break;



/* Line 1455 of yacc.c  */
#line 4325 "y.tab.c"
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
#line 2611 "parser.y"

int main(int argc, char* argv[])
{
	tempNodeScope = currentScope;
   	int i = 0;
	for(i=0;i<1000;i++){
		symbolTable[i].currentOffset=0;
		symbolTable[i].newTempOffset=-100;
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
	strcat(code,"\n\n\t.data\nMSG:\t.asciiz \"the result is = \"");
	printf("%s",code);
	FILE* fp1 = fopen("code1.asm","w");
	fprintf(fp1,"%s",code);
	return 0;
}


