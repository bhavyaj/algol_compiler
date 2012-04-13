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
		printf("Error in lexical scoping %d", scope);
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
		if (entry->track != NULL)	
			printf("track: %s\n",entry->track);
		if (entry->type || entry->type==0)	
			printf("type: %d\n",entry->type);
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
	if(node->track != NULL){
		printf("Track: %d",node->track);}
}
 
int yywrap()
{
        return 1;
}


/* Line 268 of yacc.c  */
#line 234 "y.tab.c"

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
#line 420 "y.tab.c"

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
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   335

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  86
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNRULES -- Number of states.  */
#define YYNSTATES  243

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
       0,     0,     3,     4,     8,    12,    16,    18,    21,    24,
      26,    28,    30,    32,    33,    37,    39,    42,    45,    49,
      51,    53,    55,    57,    59,    63,    65,    69,    71,    76,
      80,    82,    86,    89,    93,    95,    97,    99,   104,   106,
     109,   112,   116,   120,   122,   126,   130,   132,   136,   138,
     140,   144,   146,   148,   150,   152,   154,   156,   158,   163,
     165,   169,   171,   173,   175,   177,   181,   183,   187,   189,
     193,   195,   199,   201,   204,   206,   208,   210,   214,   216,
     220,   222,   224,   226,   227,   232,   234,   236,   238,   241,
     243,   245,   247,   249,   251,   256,   259,   262,   265,   269,
     271,   274,   276,   278,   279,   283,   285,   288,   292,   296,
     307,   308,   311,   313,   315,   319,   321,   325,   327,   329,
     334,   336,   338,   340,   343,   345,   347,   348,   353,   355,
     356,   361,   363,   367,   371,   373,   375,   378,   380,   382,
     385,   387,   389,   393,   398,   399,   400,   408,   410,   414
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      80,     0,    -1,    -1,     5,    75,    85,    -1,    74,    64,
      85,    -1,    74,    64,    84,    -1,    76,    -1,    78,    77,
      -1,    79,    28,    -1,   108,    -1,   102,    -1,    83,    -1,
      77,    -1,    -1,     5,    82,    84,    -1,    81,    -1,    78,
      83,    -1,   143,     6,    -1,   143,    64,    84,    -1,   123,
      -1,    93,    -1,   158,    -1,    95,    -1,    95,    -1,    86,
      28,    87,    -1,    88,    -1,    89,    16,    88,    -1,   108,
      -1,    90,    23,    89,    24,    -1,    90,    16,    91,    -1,
      91,    -1,    92,    16,    91,    -1,    62,    92,    -1,   122,
      62,    92,    -1,    95,    -1,   109,    -1,    96,    -1,   128,
      96,    48,    95,    -1,    97,    -1,    11,    97,    -1,    12,
      97,    -1,    96,    11,    97,    -1,    96,    12,    97,    -1,
      98,    -1,    97,    15,    98,    -1,    97,    13,    98,    -1,
      99,    -1,    98,    14,    99,    -1,   100,    -1,   104,    -1,
      21,    95,    22,    -1,   101,    -1,   102,    -1,    26,    -1,
      27,    -1,   124,    -1,   103,    -1,   105,    -1,    90,    23,
     106,    24,    -1,   107,    -1,   106,    16,   107,    -1,    95,
      -1,     4,    -1,   110,    -1,   111,    -1,   110,    36,   111,
      -1,   112,    -1,   111,    63,   112,    -1,   113,    -1,   112,
      38,   113,    -1,   114,    -1,   113,    37,   114,    -1,   115,
      -1,    39,   115,    -1,   116,    -1,   118,    -1,   117,    -1,
      21,   109,    22,    -1,     7,    -1,    96,   119,    96,    -1,
     104,    -1,    29,    -1,   124,    -1,    -1,   120,    16,   121,
     124,    -1,    54,    -1,    53,    -1,    55,    -1,   122,   120,
      -1,   108,    -1,   129,    -1,    83,    -1,    77,    -1,   127,
      -1,   128,   125,    48,   143,    -1,   128,   135,    -1,    78,
     126,    -1,   128,   125,    -1,    46,   109,    47,    -1,   130,
      -1,    79,   129,    -1,   134,    -1,   132,    -1,    -1,   137,
     131,   133,    -1,   136,    -1,    66,    94,    -1,   104,    70,
      95,    -1,   104,    70,   109,    -1,    41,   104,    70,    95,
      44,    95,    45,    95,    42,   143,    -1,    -1,   138,   139,
      -1,   108,    -1,   136,    -1,    21,   140,    22,    -1,   141,
      -1,   140,   142,   141,    -1,    94,    -1,    16,    -1,    24,
     108,    28,    23,    -1,   125,    -1,   126,    -1,   135,    -1,
       3,    94,    -1,   108,    -1,   144,    -1,    -1,   145,   142,
     146,   144,    -1,   136,    -1,    -1,    21,   148,   145,    22,
      -1,   108,    -1,   149,    16,   108,    -1,    50,   149,    64,
      -1,   136,    -1,   122,    -1,   122,    62,    -1,    60,    -1,
      49,    -1,   122,    10,    -1,   136,    -1,   153,    -1,   151,
     149,    64,    -1,   153,   151,   149,    64,    -1,    -1,    -1,
     138,   155,   147,    64,   156,   150,   152,    -1,   143,    -1,
      10,   154,   157,    -1,   122,    10,   154,   157,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   285,   285,   284,   293,   300,   309,   317,   349,   352,
     353,   357,   364,   375,   375,   387,   389,   395,   403,   414,
     419,   428,   435,   453,   471,   491,   504,   526,   539,   553,
     557,   574,   593,   595,   602,   612,   628,   642,   662,   675,
     678,   683,   721,   753,   766,   796,   833,   847,   872,   889,
     911,   925,   938,   952,   963,   975,   990,  1004,  1020,  1047,
    1063,  1082,  1094,  1109,  1145,  1157,  1168,  1179,  1198,  1208,
    1226,  1236,  1254,  1264,  1281,  1292,  1304,  1314,  1325,  1339,
    1420,  1444,  1453,  1477,  1476,  1497,  1507,  1518,  1537,  1545,
    1561,  1575,  1586,  1601,  1613,  1633,  1658,  1662,  1685,  1704,
    1719,  1723,  1736,  1751,  1750,  1769,  1773,  1790,  1819,  2023,
    2071,  2079,  2108,  2120,  2121,  2134,  2148,  2171,  2182,  2183,
    2186,  2194,  2203,  2220,  2237,  2252,  2253,  2253,  2260,  2263,
    2263,  2268,  2274,  2278,  2281,  2283,  2284,  2285,  2286,  2287,
    2289,  2290,  2292,  2296,  2299,  2310,  2299,  2331,  2341,  2358
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
  "TOKEN_RELOP", "$accept", "blockHead", "$@1", "unlabelledBlock", "block",
  "tlabel", "label", "program", "unlabelledCompound", "$@2",
  "compoundStatement", "compoundTail", "declaration", "lowerBound",
  "upperBound", "boundPair", "boundPairList", "arrayIdentifier",
  "arraySegment", "arrayList", "arrayDeclaration", "expression",
  "arithmeticExpression", "simpleArithmeticExpression", "term", "factor",
  "primary", "unsignedNumber", "realNumber", "integer", "simpleVariable",
  "variable", "subscriptedVariable", "subscriptList",
  "subscriptExpression", "identifier", "booleanExpression",
  "simpleBoolean", "implication", "booleanTerm", "booleanFactor",
  "booleanSecondary", "booleanPrimary", "logicalValue", "relation",
  "boolVariable", "relationalOperator", "listType", "@3", "type",
  "typeDeclaration", "varIdentifier", "unconditionalStatement",
  "conditionalStatement", "ifStatement", "ifClause", "basicStatement",
  "unlabelledBasicStatement", "@4", "dummyStatement", "returnStatement",
  "assignmentStatement", "forStatement", "empty", "procedureStatement",
  "procedureIdentifier", "actualParameterPart", "actualParameterList",
  "actualParameter", "parameterDelimiter", "statement", "formalParameter",
  "formalParameterList", "$@5", "formalParameterPart", "$@6",
  "identifierList", "valuePart", "specifier", "specificationPart",
  "specificationIdentifierList", "procedureHeading", "@7", "$@8",
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
       0,    73,    75,    74,    74,    76,    77,    77,    78,    79,
      79,    80,    80,    82,    81,    83,    83,    84,    84,    85,
      85,    85,    86,    87,    88,    89,    89,    90,    91,    91,
      92,    92,    93,    93,    94,    94,    95,    95,    96,    96,
      96,    96,    96,    97,    97,    97,    98,    98,    99,    99,
      99,   100,   100,   101,   102,   103,   104,   104,   105,   106,
     106,   107,   108,   109,   110,   110,   111,   111,   112,   112,
     113,   113,   114,   114,   115,   115,   115,   115,   116,   117,
     118,   119,   120,   121,   120,   122,   122,   122,   123,   124,
     125,   125,   125,   126,   126,   126,   126,   127,   128,   129,
     129,   130,   130,   131,   130,   132,   133,   134,   134,   135,
     136,   137,   138,   139,   139,   140,   140,   141,   142,   142,
     143,   143,   143,   143,   144,   145,   146,   145,   147,   148,
     147,   149,   149,   150,   150,   151,   151,   151,   151,   151,
     152,   152,   153,   153,   155,   156,   154,   157,   158,   158
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     3,     1,     2,     2,     1,
       1,     1,     1,     0,     3,     1,     2,     2,     3,     1,
       1,     1,     1,     1,     3,     1,     3,     1,     4,     3,
       1,     3,     2,     3,     1,     1,     1,     4,     1,     2,
       2,     3,     3,     1,     3,     3,     1,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     4,     1,
       3,     1,     1,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     2,     1,     1,     1,     3,     1,     3,
       1,     1,     1,     0,     4,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     4,     2,     2,     2,     3,     1,
       2,     1,     1,     0,     3,     1,     2,     3,     3,    10,
       0,     2,     1,     1,     3,     1,     3,     1,     1,     4,
       1,     1,     1,     2,     1,     1,     0,     4,     1,     0,
       4,     1,     3,     3,     1,     1,     2,     1,     1,     2,
       1,     1,     3,     4,     0,     0,     7,     1,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    62,    13,    54,     0,     6,    12,     0,     0,     0,
      15,    11,    10,     9,     0,   110,   110,     7,    16,     8,
       1,     0,    86,    85,    87,     0,     3,    20,     0,    19,
      21,     0,     0,     0,    92,     0,   110,    91,    14,     0,
      56,     0,    57,     9,    55,   120,   121,    93,   110,    90,
      99,   102,   101,   122,   105,   103,   110,     0,     5,     4,
     112,   144,   110,     0,    30,    32,    27,     0,     0,    89,
      88,    82,    78,     0,     0,     0,    53,     0,   123,    34,
      36,    38,    43,    46,    48,    51,    52,    49,    89,    35,
      63,    64,    66,    68,    70,    72,    74,    76,    75,     0,
       0,     0,     0,    96,   110,   100,     0,     0,    97,    95,
       0,     0,   113,   111,    17,   110,   110,   147,   148,     0,
       0,     0,   110,    33,    83,     0,    39,    49,    40,     0,
       0,    73,     0,     0,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    98,    61,    36,     0,    59,
     107,   108,   110,     0,   104,   117,     0,   115,    18,   129,
     128,     0,    29,     0,    25,     0,    22,    31,   149,     0,
      50,    77,    41,    42,    79,    45,    44,    47,    65,    67,
      69,    71,     0,     0,     0,    58,    94,   106,   118,   114,
       0,     0,     0,   145,     0,     0,    28,    84,    37,     0,
      60,     0,   116,   124,   125,     0,   110,    24,    23,    26,
       0,     0,   130,   126,     0,   134,   110,     0,   119,     0,
     131,     0,   138,   137,   135,   140,     0,   146,   141,     0,
     127,     0,   133,   139,   136,     0,     0,   110,   132,   142,
       0,   109,   143
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    14,     5,    34,    35,    36,     9,    10,    15,
      37,    38,    26,   163,   207,   164,   165,    39,    64,    65,
      27,   155,    79,   147,    81,    82,    83,    84,    85,    86,
      40,   127,    42,   148,   149,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,   135,    70,   169,    28,
      29,    44,    45,    46,    47,    99,    49,    50,   110,    51,
     154,    52,    53,    54,    55,    56,   113,   156,   157,   191,
      57,   204,   205,   219,   161,   192,   221,   216,   226,   227,
     228,    62,   116,   206,   118,    30
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -119
static const yytype_int16 yypact[] =
{
     213,  -119,    39,  -119,    -7,  -119,  -119,   213,    67,   108,
    -119,  -119,  -119,  -119,   119,   183,   203,  -119,  -119,  -119,
    -119,   114,  -119,  -119,  -119,   114,  -119,  -119,    35,  -119,
    -119,   248,   114,   274,  -119,   107,    55,  -119,  -119,   109,
    -119,    92,  -119,    33,  -119,  -119,  -119,  -119,   153,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,   143,     5,  -119,  -119,
    -119,  -119,   183,   120,  -119,   152,  -119,   114,   114,  -119,
     159,  -119,  -119,   157,   157,   248,  -119,   295,  -119,  -119,
     221,   132,   168,  -119,  -119,  -119,  -119,   164,   176,  -119,
     187,   162,   190,   197,  -119,  -119,  -119,  -119,  -119,   293,
     173,   221,   199,  -119,    28,  -119,   250,   248,   200,  -119,
     185,   248,  -119,  -119,  -119,   183,   232,  -119,  -119,   114,
     250,   114,   183,   152,  -119,   250,   132,  -119,   132,   241,
     242,  -119,   157,   157,  -119,   293,   157,   157,   157,   274,
     274,   274,   274,    30,   250,  -119,  -119,   210,   169,  -119,
    -119,  -119,   183,   248,  -119,  -119,   155,  -119,  -119,  -119,
    -119,   202,  -119,   239,  -119,   188,  -119,  -119,  -119,   114,
    -119,  -119,   132,   132,   210,   168,   168,  -119,   162,   190,
     197,  -119,   250,   224,   250,  -119,  -119,  -119,  -119,  -119,
     114,   248,   114,  -119,   250,   250,  -119,  -119,  -119,   250,
    -119,   244,  -119,  -119,  -119,   266,   220,  -119,  -119,  -119,
     228,   256,  -119,  -119,   114,  -119,   275,   250,  -119,   114,
    -119,   -11,  -119,  -119,     9,  -119,   114,  -119,   275,   238,
    -119,   114,  -119,  -119,  -119,    17,   114,   183,  -119,  -119,
      61,  -119,  -119
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -119,  -119,  -119,  -119,    65,    40,    44,  -119,  -119,  -119,
     135,    -8,   267,  -119,  -119,    89,  -119,    -5,   -45,   223,
    -119,   -27,    21,    56,   -47,   105,   151,  -119,  -119,     2,
    -119,    -2,  -119,  -119,   124,     0,   -23,  -119,   154,   158,
     170,   150,   226,  -119,  -119,  -119,  -119,  -119,  -119,  -118,
    -119,   -25,   261,   277,  -119,     8,   -14,  -119,  -119,  -119,
    -119,  -119,   262,   -50,  -119,    -9,  -119,  -119,   126,   110,
     -61,    99,  -119,  -119,  -119,  -119,   -77,  -119,    95,  -119,
    -119,   258,  -119,  -119,   204,  -119
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -113
static const yytype_int16 yytable[] =
{
      13,   117,    12,    71,    78,   231,   112,    13,    58,    12,
     102,   114,    61,    41,    41,    43,    43,    12,    12,   233,
      63,    60,   105,    48,    48,    66,   126,   128,    69,    87,
     100,    87,     1,   231,    41,    13,    43,    12,    12,     1,
       7,   132,   133,    48,     8,    67,    41,     7,    43,    -2,
      12,     8,   130,   232,  -112,     3,   -27,    16,    61,     1,
      41,   117,    43,    63,    12,     6,   160,    60,    66,   115,
      48,   234,    17,    87,   162,    87,   167,   231,   182,     8,
     104,   239,     3,    19,   151,   172,   173,    80,     7,   101,
     105,   186,    -2,    -2,    -2,    19,   129,    68,   224,  -112,
      17,    -2,    41,   -89,    43,    87,    12,   158,    20,    87,
     224,     1,     2,    41,    63,    43,    63,    12,     1,    66,
      41,    66,    43,    48,    12,   242,   187,   146,   150,    21,
      48,    80,   106,   101,     3,    11,   119,    87,    87,    87,
      87,   166,    18,   120,   197,   136,   129,   137,   104,   235,
      41,    87,    43,    33,    12,   143,   215,     1,     2,   240,
      48,     1,   107,    80,   111,   183,   225,    80,   121,    69,
      18,   188,    22,    23,    24,   124,   241,   189,   125,   190,
       3,    25,   138,    76,     3,   184,    31,     1,     2,    87,
     201,   174,   203,   185,    32,   101,   101,   101,   101,   -27,
     -80,   -80,   -80,   198,   195,   146,    31,     1,     2,    80,
       3,   -80,   196,    21,   220,   208,   166,     1,     2,   203,
     210,   132,   133,   139,    32,   140,   220,   -80,   141,    33,
       3,   238,   132,   133,   142,    41,   220,    43,   229,    12,
       3,   175,   176,   144,    32,    48,   145,    80,   152,    33,
     134,   153,     1,   159,     1,    72,    22,    23,    24,    73,
      74,    73,    74,   170,   171,    25,   193,   194,   199,    75,
     214,   125,   211,   217,    76,     3,    76,     3,     1,   218,
     237,    72,   188,    59,   209,    73,    74,    77,   212,   177,
     190,   123,   181,   178,    33,    75,    33,     1,   179,     1,
      76,     3,    72,   131,    73,    74,    73,    74,   200,   108,
     109,   180,   103,    77,   125,   213,    75,   202,   230,    76,
       3,    76,     3,   236,   222,   122,   168,     0,    22,    23,
      24,     0,     0,     0,     0,   223
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-119))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    62,     0,    28,    31,    16,    56,     7,    16,     7,
      33,     6,    21,    15,    16,    15,    16,    15,    16,    10,
      25,    21,    36,    15,    16,    25,    73,    74,    28,    31,
      32,    33,     4,    16,    36,    35,    36,    35,    36,     4,
       0,    11,    12,    35,     0,    10,    48,     7,    48,    10,
      48,     7,    75,    64,    21,    27,    23,    64,    67,     4,
      62,   122,    62,    68,    62,     0,   116,    67,    68,    64,
      62,    62,     7,    75,   119,    77,   121,    16,    48,    35,
      36,    64,    27,    28,   107,   132,   133,    31,    48,    33,
     104,   152,    53,    54,    55,    28,    75,    62,   216,    66,
      35,    62,   104,    70,   104,   107,   104,   115,     0,   111,
     228,     4,     5,   115,   119,   115,   121,   115,     4,   119,
     122,   121,   122,   115,   122,    64,   153,   106,   107,    10,
     122,    75,    23,    77,    27,     0,    16,   139,   140,   141,
     142,   120,     7,    23,   169,    13,   125,    15,   104,   226,
     152,   153,   152,    46,   152,    99,   206,     4,     5,   236,
     152,     4,    70,   107,    21,   144,   216,   111,    16,   169,
      35,    16,    53,    54,    55,    16,   237,    22,    21,    24,
      27,    62,    14,    26,    27,    16,     3,     4,     5,   191,
     190,   135,   192,    24,    41,   139,   140,   141,   142,    23,
      36,    37,    38,   182,    16,   184,     3,     4,     5,   153,
      27,    47,    24,    10,   214,   194,   195,     4,     5,   219,
     199,    11,    12,    36,    41,    63,   226,    63,    38,    46,
      27,   231,    11,    12,    37,   237,   236,   237,   217,   237,
      27,   136,   137,    70,    41,   237,    47,   191,    48,    46,
      29,    66,     4,    21,     4,     7,    53,    54,    55,    11,
      12,    11,    12,    22,    22,    62,    64,    28,    44,    21,
      50,    21,    28,    45,    26,    27,    26,    27,     4,    23,
      42,     7,    16,    16,   195,    11,    12,    39,    22,   138,
      24,    68,   142,   139,    46,    21,    46,     4,   140,     4,
      26,    27,     7,    77,    11,    12,    11,    12,   184,    48,
      48,   141,    35,    39,    21,   205,    21,   191,   219,    26,
      27,    26,    27,   228,    49,    67,   122,    -1,    53,    54,
      55,    -1,    -1,    -1,    -1,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    27,    74,    76,    77,    78,    79,    80,
      81,    83,   102,   108,    75,    82,    64,    77,    83,    28,
       0,    10,    53,    54,    55,    62,    85,    93,   122,   123,
     158,     3,    41,    46,    77,    78,    79,    83,    84,    90,
     103,   104,   105,   108,   124,   125,   126,   127,   128,   129,
     130,   132,   134,   135,   136,   137,   138,   143,    84,    85,
     108,   138,   154,    90,    91,    92,   108,    10,    62,   108,
     120,   124,     7,    11,    12,    21,    26,    39,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   104,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   128,
     104,    96,   109,   126,    79,   129,    23,    70,   125,   135,
     131,    21,   136,   139,     6,    64,   155,   143,   157,    16,
      23,    16,   154,    92,    16,    21,    97,   104,    97,    95,
     109,   115,    11,    12,    29,   119,    13,    15,    14,    36,
      63,    38,    37,    96,    70,    47,    95,    96,   106,   107,
      95,   109,    48,    66,   133,    94,   140,   141,    84,    21,
     136,   147,    91,    86,    88,    89,    95,    91,   157,   121,
      22,    22,    97,    97,    96,    98,    98,    99,   111,   112,
     113,   114,    48,    95,    16,    24,   143,    94,    16,    22,
      24,   142,   148,    64,    28,    16,    24,   124,    95,    44,
     107,   108,   141,   108,   144,   145,   156,    87,    95,    88,
      95,    28,    22,   142,    50,   136,   150,    45,    23,   146,
     108,   149,    49,    60,   122,   136,   151,   152,   153,    95,
     144,    16,    64,    10,    62,   149,   151,    42,   108,    64,
     149,   143,    64
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
#line 285 "parser.y"
    {
		currentScope++;
		printf("current Scope = %d\n",currentScope);
	}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 290 "parser.y"
    {
		printf("blockHead\n");
	}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 294 "parser.y"
    {
		printf("blockHead\n");
	}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 301 "parser.y"
    {
		Node* newNode = createNode();
		Node* tempNode =(Node*) (yyvsp[(3) - (3)]);
		newNode->pt0 = (Node*) (yyvsp[(3) - (3)]);
		(yyval) = newNode;
	}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 310 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (1)]);
		(yyval) = newNode;
		printf("unlabelled block\n");
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 326 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(2) - (2)]);						// $2
		(yyval) = newNode;
		printf("labelled block\n");
	}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 358 "parser.y"
    {
		printf("compoundStatement\n");
		symbolTableDisplay(0);
		symbolTableDisplay(1);
	}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 365 "parser.y"
    {
		printf("block\n");
		symbolTableDisplay(0);
		symbolTableDisplay(1);
	}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 375 "parser.y"
    {
		currentScope++;
		printf("current Scope = %d\n",currentScope);
	}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 379 "parser.y"
    {
		printf("unlabelled compound\n");
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 389 "parser.y"
    {
		printf("labelled compoundstatement\n");
	}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 396 "parser.y"
    {
		printf("compound tail\n");
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (2)]);
		(yyval) = newNode;
	}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 404 "parser.y"
    {
		Node *newNode = createNode();
		newNode->pt0 = (yyvsp[(1) - (3)]);
		(yyval) = newNode;
	}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 415 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 420 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 429 "parser.y"
    {
		(yyval)=(yyvsp[(1) - (1)]);
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 436 "parser.y"
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

  case 23:

/* Line 1806 of yacc.c  */
#line 454 "parser.y"
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

  case 24:

/* Line 1806 of yacc.c  */
#line 472 "parser.y"
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

  case 25:

/* Line 1806 of yacc.c  */
#line 492 "parser.y"
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

  case 26:

/* Line 1806 of yacc.c  */
#line 505 "parser.y"
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
		printf("boundPairList->boundPairList , boundPair\n");
	}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 527 "parser.y"
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

  case 28:

/* Line 1806 of yacc.c  */
#line 540 "parser.y"
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
		printf("arraySegment->arrayIdentifier [ boundPairList ]\n");
	}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 558 "parser.y"
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
		printf("arrayList->arraySegment\n");
	}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 575 "parser.y"
    {
		Node* tempNode0=(yyvsp[(1) - (3)]);
		Node* tempNode1=(yyvsp[(3) - (3)]);
		Symbol* symbolEntry=lookUpInCurrentScope(tempNode1->identLex);
		if (symbolEntry!=NULL){
			return 0;
		}
		else{
			symbolEntry = addEntry(tempNode1->identLex);
			symbolTable[currentScope].currentSymbol->type=tempNode1->semTypeDef;
			symbolTable[currentScope].currentSymbol->track=tempNode1->track;
			(yyval)=(yyvsp[(0) - (3)]);
		}
		printf("arrayList->arrayList , arraySegment\n");
	}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 596 "parser.y"
    {printf("here\n");}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 603 "parser.y"
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
#line 613 "parser.y"
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

/* Line 1806 of yacc.c  */
#line 629 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = arithmeticExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		//remember to check type
		newNode->realValue = tempNode->realValue;
		newNode->intValue = tempNode->intValue;
		newNode->semTypeDef = tempNode->semTypeDef;
		printf("arithmetic->simplearithmetic, intval = %d,realval=%f\n",newNode->intValue,newNode->realValue);		
		(yyval) = newNode;
	}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 643 "parser.y"
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

/* Line 1806 of yacc.c  */
#line 663 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = simpleArithmeticExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef ; 
		(yyval) = newNode;
		printf("simplearithmetic->term, intval = %d\n",newNode->intValue);
		
	}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 676 "parser.y"
    {
	}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 679 "parser.y"
    {
	}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 684 "parser.y"
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
			printf("if belu reached\n");			
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
			printf("else belu reached");				
			newNode->semTypeDef = storeInteger ;  
			newNode->intValue = tempNode0->intValue  +  tempNode2->intValue ;  

		}
		printf("simplearithmetic->simplearithmetic + term, realval = %f\n",newNode->realValue);
		(yyval) = newNode;
	}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 722 "parser.y"
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
	}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 754 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		printf("term->factor, intval = %d\n",newNode->intValue);
		(yyval) = newNode;
	}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 767 "parser.y"
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
				}  
				(yyval) = newNode;
		}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 797 "parser.y"
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

/* Line 1806 of yacc.c  */
#line 834 "parser.y"
    {
		Node* newNode = createNode();
		
		newNode->type = factor;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef ;  
		printf("factor->primary, intval = %d\n",newNode->intValue);
		(yyval) = newNode;
	}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 848 "parser.y"
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

/* Line 1806 of yacc.c  */
#line 873 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
		printf("primary->unsignedNumber");	
	
	}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 890 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (Node*)(yyvsp[(1) - (1)]);
		printf("primary->variable, int value=%d\n",newNode->intValue);
// do type checking and proper lookup
		Symbol* foundEntry = lookUp(tempNode->identLex,currentScope);
		if (foundEntry)
		{	
			newNode->intValue =  foundEntry->value;
			newNode->realValue = foundEntry->realValue;		
			newNode->semTypeDef= foundEntry->type ;	
		}
		else
			printf("error belu");		
		(yyval) = newNode;

		
	}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 912 "parser.y"
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

/* Line 1806 of yacc.c  */
#line 926 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = unsignedNumber;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=storeReal;
		(yyval) = newNode;
		printf("unsignedNumber->real, realval = %f\n",newNode->realValue);	
	}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 939 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->type = unsignedNumber;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node *tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=storeInteger;
		(yyval) = newNode;
		printf("unsignedNumber->integer, intval = %d\n",newNode->intValue);
	}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 953 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = realNumber;
		newNode->realValue = atof(yytext);
		newNode->semTypeDef=storeReal;
		(yyval) = newNode;
	}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 964 "parser.y"
    {
		Node *newNode = createNode();
		
		newNode->type = integer;
		newNode->intValue = atoi(yytext);
		printf("integer-> TOKEN_INTEGER %d\n",newNode->intValue);
		newNode->semTypeDef=storeInteger;  
		(yyval) = newNode;
	}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 976 "parser.y"
    {	
		Node *new = createNode();		
		new->type = simpleVariable;
		new->pt0 = (yyvsp[(1) - (1)]);
		Node* temp = (Node*)(yyvsp[(1) - (1)]);			
		new->realValue=temp->realValue;		
		new->intValue=temp->intValue;
		new->boolValue=temp->boolValue;
		strcpy(new->identLex, temp->identLex);
		printf("simplevariable->varIdentifier");			
		(yyval) = new;
	}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 991 "parser.y"
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

  case 57:

/* Line 1806 of yacc.c  */
#line 1005 "parser.y"
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

  case 58:

/* Line 1806 of yacc.c  */
#line 1021 "parser.y"
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

  case 59:

/* Line 1806 of yacc.c  */
#line 1048 "parser.y"
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

  case 60:

/* Line 1806 of yacc.c  */
#line 1064 "parser.y"
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

  case 61:

/* Line 1806 of yacc.c  */
#line 1083 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = subscriptExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->intValue = tempNode->intValue;
		(yyval) = newNode;
		printf("subscriptedExpression->arithmeticExpression\n");
	}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 1095 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = identifier;
		printf("yytext: %s\n",yytext);
		strcpy(newNode->identLex,yytext);
		
		if(!lookUp(newNode->identLex, currentScope)){
			printf("belu laude, declare to kar");
		}
		printf("TOKEN_IDENTIFIER\n");		
		(yyval) = newNode;
	}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 1110 "parser.y"
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
		printf("booleanExpression->simpleBoolean\n");
	}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 1146 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->boolValue = tempNode->boolValue;
		newNode->semTypeDef = tempNode->semTypeDef;
		(yyval) = newNode;
		printf("simpleBoolean->implication\n");
	}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 1158 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		newNode->pt2 = (yyvsp[(3) - (3)]);
		(yyval) = newNode;
		printf("simpleBoolean->simple = implication\n");
	}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 1169 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = implication;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;  
		printf("implication->booleanterm\n");
	}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 1180 "parser.y"
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

  case 68:

/* Line 1806 of yacc.c  */
#line 1199 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanTerm;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 1209 "parser.y"
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

  case 70:

/* Line 1806 of yacc.c  */
#line 1227 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 1237 "parser.y"
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

  case 72:

/* Line 1806 of yacc.c  */
#line 1255 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanSecondary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
	}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 1265 "parser.y"
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

  case 74:

/* Line 1806 of yacc.c  */
#line 1282 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval) = newNode;
		
	}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 1293 "parser.y"
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

  case 76:

/* Line 1806 of yacc.c  */
#line 1305 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (yyvsp[(1) - (1)]);
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval)=newNode;
	}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1315 "parser.y"
    {
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = (yyvsp[(1) - (3)]);
		Node* tempNode = (yyvsp[(1) - (3)]);  
		newNode->semTypeDef=tempNode->semTypeDef;
		(yyval)=newNode;
	}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 1326 "parser.y"
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

  case 79:

/* Line 1806 of yacc.c  */
#line 1340 "parser.y"
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

  case 80:

/* Line 1806 of yacc.c  */
#line 1421 "parser.y"
    {
		Node* newNode = createNode();
		newNode->type = boolVariable;
		newNode->pt0 = (yyvsp[(1) - (1)]);
		Node* tempNode = (Node*)(yyvsp[(1) - (1)]);
		newNode->boolValue = tempNode->boolValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		strcpy(newNode->identLex, tempNode->identLex);
		(yyval) = newNode;
		printf("Boolvariable->simpleVariable\n");
	}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1445 "parser.y"
    {	
		Node *newNode = createNode();
		newNode->type = relationalOperator;
		strcpy(newNode->identLex, yytext);
		(yyval) = newNode;
	}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1454 "parser.y"
    {

		Node *temp2=(yyvsp[(0) - (1)]);

		Node *temp1=(yyvsp[(1) - (1)]);
		printf("belu listType\n");
		if (lookUpInCurrentScope(temp1->identLex)!=NULL){
			printf("belu if\n");
			return 0;
		}
		else{
			printf("belu else\n");			
			Symbol *newEntry=addEntry(temp1->identLex);
			newEntry->type=temp2->semTypeDef;
			printf("belu semtypedef : %d", newEntry->type);	
			(yyval)=(yyvsp[(0) - (1)]);			


		}

	}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1477 "parser.y"
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

  case 85:

/* Line 1806 of yacc.c  */
#line 1498 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef = storeReal;
		printf("Token_real\n");		
		(yyval) = new;

	}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1508 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeInteger;
		printf("Token_integer\n");
		(yyval) = new;	

	}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1519 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeBoolean;
		(yyval) = new;



	}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1538 "parser.y"
    {
	printf("typeDeclaration\n");

	}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1546 "parser.y"
    {
		Node *new = createNode();		
		new->type = varIdentifier;
		new->pt0 = (yyvsp[(1) - (1)]);
		Node* temp = (Node*)(yyvsp[(1) - (1)]);			
		new->realValue=temp->realValue;		
		new->intValue=temp->intValue;
		new->boolValue=temp->boolValue;
		strcpy(new->identLex, temp->identLex);
		printf("varIdentifier");			
		(yyval) = new;
	}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1562 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		(yyval) = new;



	
	}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1575 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		(yyval) = new;

	}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1586 "parser.y"
    {

		Node *new = createNode();
        	new->type = unconditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp1 = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp1->semTypeDef;
		(yyval) = new;


	}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1602 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = conditionalStatement;
        	new->pt0 = (yyvsp[(1) - (1)]);
		Node *temp = (yyvsp[(1) - (1)]);
		new->semTypeDef=temp->semTypeDef;
		(yyval) = new;
	}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1614 "parser.y"
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

  case 95:

/* Line 1806 of yacc.c  */
#line 1634 "parser.y"
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

  case 97:

/* Line 1806 of yacc.c  */
#line 1663 "parser.y"
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

  case 98:

/* Line 1806 of yacc.c  */
#line 1686 "parser.y"
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

  case 99:

/* Line 1806 of yacc.c  */
#line 1704 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = basicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  

		(yyval) = new;

	}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1724 "parser.y"
    {		
		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement; 
        	new->pt0 = (yyvsp[(1) - (1)]) ; 
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  
		(yyval) = new;

	}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1737 "parser.y"
    {

		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  

		new->semTypeDef=temp->semTypeDef ;  

		(yyval) = new;

	}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1751 "parser.y"
    {
			
		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = (yyvsp[(1) - (1)]) ;  
		Node *temp = (yyvsp[(1) - (1)]) ;  
		new->semTypeDef=temp->semTypeDef ;  
		(yyval) = new;

	}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1763 "parser.y"
    {
		(yyval) = (yyvsp[(1) - (3)]);
	}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1774 "parser.y"
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

  case 107:

/* Line 1806 of yacc.c  */
#line 1791 "parser.y"
    {
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = (yyvsp[(1) - (3)]);
		new->pt2 = (yyvsp[(3) - (3)]);
		Symbol *symbol1;	
		Node *tmp1=(yyvsp[(1) - (3)]);
		Node *tmp2=(yyvsp[(3) - (3)]);
		new->semTypeDef=storeVoid;		
  		symbol1=lookUp(tmp1->identLex, currentScope);
		if (symbol1==NULL){
			new->semTypeDef=storeError;
		}
		else{
			if (symbol1->type==storeInteger && tmp2->semTypeDef==storeInteger) 				{								
				// SYMBOL1>TYPE IS INTEGER  
				symbol1->value=tmp2->intValue;
			}
			else if (symbol1->type==storeReal && tmp2->semTypeDef==storeReal) 				{								
				// SYMBOL1>TYPE IS Real
		  		symbol1->realValue=tmp2->realValue;
				printf("assignmentStatement->identifier:= arithmeticexpression, realValue= %f,,%f\n",tmp2->realValue,symbol1->realValue);		
			}
		
		}
		(yyval) = new;
	}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1820 "parser.y"
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

  case 109:

/* Line 1806 of yacc.c  */
#line 2024 "parser.y"
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

  case 110:

/* Line 1806 of yacc.c  */
#line 2071 "parser.y"
    {	
		printf("empty reached\n");
		Node *new = createNode();         	            	  
        	new->type =empty;
		(yyval) = new;
	}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 2079 "parser.y"
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

  case 112:

/* Line 1806 of yacc.c  */
#line 2109 "parser.y"
    {
		Node *new = createNode(); 
		new->type = procedureIdentifier;
		new->pt0 = (yyvsp[(1) - (1)]);
	
		Node *temp=(yyvsp[(1) - (1)]);

		(yyval) = new;
	}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 2122 "parser.y"
    {
		(yyval)=(yyvsp[(2) - (3)]);
		Node *temp = (yyvsp[(2) - (3)]);
		if(temp->semTypeDef != storeError)
		{		
			temp->semTypeDef == storeVoid;
		}
		
	}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 2135 "parser.y"
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

  case 116:

/* Line 1806 of yacc.c  */
#line 2149 "parser.y"
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

  case 117:

/* Line 1806 of yacc.c  */
#line 2172 "parser.y"
    {
		Node *new = createNode(); 
		Node *temp = (yyvsp[(1) - (1)]); 
		new->type = actualParameter;
		new->semTypeDef = temp->semTypeDef;
		new->pt0 = (yyvsp[(1) - (1)]);

		(yyval) = new;
	}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 2187 "parser.y"
    {
		Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (1)]);
//		Node *temp2=$3;
		(yyval)=new;
	}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 2195 "parser.y"
    {
		Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (1)]);
//		Node *temp2=$3;
		(yyval)=new;

	}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 2204 "parser.y"
    {	Node* new=createNode();
		Node *temp1=(yyvsp[(1) - (1)]);
//		Node *temp2=$3;
		(yyval)=new;
	}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 2221 "parser.y"
    {
		Node* new=createNode();
		Node* temp=(yyvsp[(2) - (2)]);

		(yyval)=new;
	}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 2238 "parser.y"
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

  case 126:

/* Line 1806 of yacc.c  */
#line 2253 "parser.y"
    {   ////check/////
		(yyvsp[(1) - (2)]) = (yyvsp[(0) - (2)]); 
		(yyvsp[(2) - (2)]) = (yyvsp[(0) - (2)]);
	}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 2260 "parser.y"
    {
		(yyval) = (yyvsp[(0) - (1)]);
	}
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 2263 "parser.y"
    {
		(yyvsp[(1) - (1)]) = (yyvsp[(0) - (1)]);
	}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 2268 "parser.y"
    {
		Node *node1 = (yyvsp[(0) - (1)]);
		Node *node2 = (yyvsp[(1) - (1)]);
		Symbol *symbol = lookUp(node2->identLex,currentScope);
		symbol->type = node1->semTypeDef;
	}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 2274 "parser.y"
    {
		(yyvsp[(2) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 2278 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
	}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 2292 "parser.y"
    {
		(yyvsp[(3) - (3)]) = (yyvsp[(0) - (3)]);
		Node *node1 = (yyvsp[(1) - (3)]);
	}
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 2299 "parser.y"
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

  case 145:

/* Line 1806 of yacc.c  */
#line 2310 "parser.y"
    {
		(yyvsp[(3) - (4)]) = (yyvsp[(1) - (4)]);
	}
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 2331 "parser.y"
    {
		Node *new = createNode();
		
		new->type = procedureBody;
		Node *temp = (yyvsp[(1) - (1)]);
		new->semTypeDef = temp->semTypeDef;
		(yyval) = new;
	}
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 2341 "parser.y"
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

  case 149:

/* Line 1806 of yacc.c  */
#line 2359 "parser.y"
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
#line 4091 "y.tab.c"
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
#line 2379 "parser.y"

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


