//globalLevel
//%token %left %right
// remove--redn, dimension


%{
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
 


%}
%token TOKEN_PRINT
%token TOKEN_IDENTIFIER
%token TOKEN_BEGIN 
%token TOKEN_END		
%token TOKEN_LOGICAL_VALUE	
%token TOKEN_OPERATOR 	
%token TOKEN_OR	
%token TOKEN_PROCEDURE  	
%token TOKEN_PLUS		
%token TOKEN_MINUS		
%token TOKEN_DIVIDE		
%token TOKEN_POWER		
%token TOKEN_MULTIPLY		
%token TOKEN_COMMA
%token TOKEN_OPEN_BRACKET
%token TOKEN_CLOSE_BRACKET
%token TOKEN_OPEN_SQUARE_BRACKET
%token TOKEN_CLOSE_SQUARE_BRACKET
%token TOKEN_CONTINUE	
%token TOKEN_REAL_NUM		
%token TOKEN_INTEGER	
%token TOKEN_COLON		
%token TOKEN_REL_OP
%token TOKEN_LESS_EQUAL
%token TOKEN_GREATER
%token TOKEN_GREATER_EQUAL
%token TOKEN_EQUAL
%token TOKEN_LESS
%token TOKEN_NOTEQUAL		
%token TOKEN_EQUIV		
%token TOKEN_AND_OP		
%token TOKEN_OR_OP		
%token TOKEN_NOT_OP	
%token TOKEN_GOTO
%token TOKEN_FOR
%token TOKEN_DO
%token TOKEN_WHILE
%token TOKEN_STEP
%token TOKEN_UNTIL
%token TOKEN_IF
%token TOKEN_THEN
%token TOKEN_ELSE
%token TOKEN_SWITCH
%token TOKEN_VALUE
%token TOKEN_BOOLEAN
%token TOKEN_TYPE_OWN
%token TOKEN_TYPE_INTEGER
%token TOKEN_TYPE_REAL
%token TOKEN_TYPE_BOOLEAN
%token TOKEN_TYPE_ARRAY
%token TOKEN_TYPE_SWITCH
%token TOKEN_TYPE_PROCEDURE
%token TOKEN_TYPE_STRING
%token TOKEN_TYPE_LABEL
%token TOKEN_TYPE_VALUE
%token TOKEN_ARRAY
%token TOKEN_IMPLY
%token TOKEN_SEMICOLON
%token TOKEN_LTRSTRING
%token TOKEN_TINTEGER
%token TOKEN_TREAL
%token TOKEN_RETURN
%token TOKEN_ASSIGN_IDENTIFIER
%token TOKEN_LABEL_IDENTIFIER
%token TOKEN_BOOL_IDENTIFIER
%right	TOKEN_ASSIGN
%left	TOKEN_EQUIV
%left	TOKEN_EQUAL
%left	TOKEN_IMPLY
%left	TOKEN_OR_OP
%left	TOKEN_AND_OP
%left	TOKEN_NOT_OP
%left	TOKEN_LESS TOKEN_GREATER TOKEN_LESS_EQUAL TOKEN_GREATER_EQUAL TOKEN_NOT_EQUAL
%left	TOKEN_RELOP
%left	TOKEN_PLUS TOKEN_MINUS
%right	TOKEN_POWER

%%

blockHead :
	TOKEN_BEGIN declaration
	|blockHead TOKEN_SEMICOLON declaration;

unlabelledBlock :
	blockHead TOKEN_SEMICOLON compoundTail
	{
		Node* newNode = createNode();
		Node* tempNode =(Node*) $3;
		newNode->pt0 = (Node*) $3;
		$$ = newNode;
	};

block :
	unlabelledBlock 
	{
		Node *newNode = createNode();
		newNode->pt0 = $1;
		$$ = newNode;
	}
	|
	label
	{
		Node* newNode = createNode();
		newNode->pt0 = $1;
		Node *tempNode = $1;
		strcpy(newNode->identLex, tempNode->identLex);
		$$ = newNode;
	}
	/*TOKEN_COLON*/ block 
	{
		Node *newNode = createNode();
		newNode->pt0 = $3;
		$$ = newNode;
	}
	|
	error
	{
		printf("Syntax error in block containing line num %d\n",lineNo);
	}
	;

label : 
	TOKEN_LABEL_IDENTIFIER
	{
		Node *new = createNode();         	
                new->type = label;
		strcpy(new->identLex, yytext);
		$$ = new;
	};
/*
program :
	block
	|
	compoundStatement
	;
*/
unlabelledCompound :
	TOKEN_BEGIN compoundTail
	;

compoundStatement :
	unlabelledCompound
//	|
//	label /*TOKEN_COLON*/ compoundStatement
	;

compoundTail :
	statement TOKEN_END
	{
		Node *newNode = createNode();
		newNode->pt0 = $1;
		$$ = newNode;
	}	
	|
	statement TOKEN_SEMICOLON compoundTail
	{
		Node *newNode = createNode();
		newNode->pt0 = $1;
		$$ = newNode;
	}
	
	
	;

declaration : 
	typeDeclaration
	{
		$$=$1;
	}	 
	|
	arrayDeclaration
	{
		$$=$1;
	}
	|
	procedureDeclaration
	{
		$$=$1;
	};


lowerBound:
	arithmeticExpression
	{
		Node *newNode = createNode();
		newNode->type = lowerBound;
		newNode->pt0 = $1;
		Node *tempNode = $1;
		if(tempNode->semTypeDef==storeInteger){
			newNode->semTypeDef = storeInteger;
			newNode->intValue = tempNode->intValue;
		}
		else{
		
		}
		$$=newNode;
	};

upperBound:
	arithmeticExpression
	{
		Node *newNode = createNode();
		newNode->type = upperBound;
		newNode->pt0 = $1;
		Node *tempNode = $1;
		if(tempNode->semTypeDef==storeInteger){
			newNode->semTypeDef = storeInteger;
			newNode->intValue = tempNode->intValue;
		}
		else{
	
		}
		$$=newNode;
	};

boundPair :
	lowerBound TOKEN_COLON upperBound
	{
		Node* newNode = createNode();         	  
    	newNode->type = boundPair;
    	newNode->pt0 = $1;
		newNode->pt2 = $3;
		Node* tempNodeOne = $1;
		Node* tempNodeTwo = $3;
	
		if (tempNodeOne->semTypeDef==storeInteger && tempNodeTwo->semTypeDef==storeInteger ){
			newNode->semTypeDef=storeBoundPairList;			
		}
		else {
			
		}
		$$ = newNode;
	};

boundPairList :
	boundPair
	{
		Node* newNode = createNode();
		newNode->type = boundPairList;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		if (tempNode->semTypeDef==storeBoundPairList) {  
			newNode->semTypeDef=tempNode->semTypeDef;
		}
		$$ = newNode;
	}
	|
	boundPairList TOKEN_COMMA boundPair
	{
		Node* newNode = createNode();
		newNode->type = boundPairList;
        	newNode->pt0 = $1;
		newNode->pt2 = $3;
		Node* tempNodeOne = $1;
		Node* tempNodeTwo = $3;
	
		if (tempNodeOne->semTypeDef==storeBoundPairList && tempNodeTwo->semTypeDef==storeBoundPairList ){
			newNode->semTypeDef=storeBoundPairList;			
		}
		else {
			
		}
		
		newNode->track = tempNodeOne->track + 1 ;  	
		$$ = newNode;
	};

arrayIdentifier :
	identifier
	{
		Node* newNode = createNode();
		newNode->type = arrayIdentifier;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		strcpy(newNode->identLex, tempNode->identLex);
		$$ = newNode;
	}
	;

arraySegment :
	arrayIdentifier TOKEN_OPEN_SQUARE_BRACKET boundPairList TOKEN_CLOSE_SQUARE_BRACKET
	{
		Node* newNode = createNode();
		newNode->type = boundPair;
		newNode->pt0 = $1;
		newNode->pt2 = $3;

		Node *tempNodeOne = $1;
		Node *tempNodeTwo = $3;
		newNode->track = tempNodeTwo->track;
		newNode->identLex = tempNodeOne->identLex;
		$$ = newNode;
	};

arrayList :
	arraySegment 
	{
		Node* tempNode0=$0;
		Node* tempNode1=$1;
		Symbol* symbolEntry=lookUpInCurrentScope(tempNode1->identLex);
		if (symbolEntry!=NULL){
			return 0;
		}
		else{
			symbolEntry = addEntry(tempNode1->identLex);
			symbolTable[currentScope].currentSymbol->type=tempNode1->semTypeDef;
			symbolTable[currentScope].currentSymbol->track=tempNode1->track;
			$$=$0;
		}
	}
	|
	arraySegment TOKEN_COMMA  
	{
		Node* tempNode0=$0;
		Node* tempNode1=$1;
		Symbol* symbolEntry=lookUpInCurrentScope(tempNode1->identLex);
		if (symbolEntry!=NULL){
			return 0;
		}
		else{
			symbolEntry = addEntry(tempNode1->identLex);
			symbolTable[currentScope].currentSymbol->type=tempNode1->semTypeDef;
			symbolTable[currentScope].currentSymbol->track=tempNode1->track;
			$$=$0;
		}
	}
	arrayList;

arrayDeclaration :
//	TOKEN_ARRAY arrayList
//	|
	type TOKEN_ARRAY arrayList
	;

//////////////////////////// Expression Parsing

expression :
	arithmeticExpression
	{
		Node *newNode = createNode();
		newNode->type = expression;
		newNode->pt0 = $1;
		Node *tempNode = $1;
		newNode->semTypeDef = tempNode->semTypeDef;
		$$ = newNode;
	}
	|
	booleanExpression
	{
		Node *newNode = createNode();
		newNode->type = expression;
		newNode->pt0 = $1;
		Node *tempNode = $1;
		newNode->semTypeDef = tempNode->semTypeDef;
		$$ = newNode;
} ;

arithmeticExpression :
	simpleArithmeticExpression
	{
		Node *newNode = createNode();
		newNode->type = arithmeticExpression;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		//remember to check type
		newNode->realValue = tempNode->realValue;
		newNode->intValue = tempNode->intValue;
		newNode->semTypeDef = tempNode->semTypeDef;
		$$ = newNode;
	}
	|
	ifClause simpleArithmeticExpression TOKEN_ELSE arithmeticExpression 
	{
		Node *newNode = createNode();
		newNode->type = arithmeticExpression;
		newNode->pt0 = $1;
		newNode->pt1 = $2;
		newNode->pt3 = $4;
		Node* tempNode2 = (Node*)$2;
		Node* tempNode4 = (Node*)$4;
		if(tempNode2->semTypeDef == storeInteger )
		{
			if(tempNode4->semTypeDef == storeInteger)
			{
				newNode->semTypeDef=storeInteger ;  		
			}
		}
		$$ = newNode;
	};

simpleArithmeticExpression :
	term
	{
		Node *newNode = createNode();
		newNode->type = simpleArithmeticExpression;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef ; 
		$$ = newNode;
	}
	|
	simpleArithmeticExpression TOKEN_PLUS term
	{
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = $1;
		newNode->pt1 = $2;
		newNode->pt2 = $3;
		Node* tempNode0 = (Node*)$1;
		Node* tempNode1 = (Node*)$2;
		Node* tempNode2 = (Node*)$3;

		  
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
	
			$$ = newNode;
		}
		|
		simpleArithmeticExpression TOKEN_MINUS term
		{
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = $1;
		newNode->pt1 = $2;
		newNode->pt2 = $3;
		Node* tempNode0 = (Node*)$1;
		Node* tempNode1 = (Node*)$2;
		Node* tempNode2 = (Node*)$3;
		  
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
			$$ = newNode;
		//}
	}
	 ;

term :	
	factor 	
	{
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		$$ = newNode;
	}
	|
	term TOKEN_MULTIPLY factor
	{
		Node *newNode = createNode();
		newNode->type = term;
		newNode->pt0 = $1;
		newNode->pt1 = $2;
		newNode->pt2 = $3;
		Node* tempNode0 = (Node*)$1;
		Node* tempNode1 = (Node*)$2;
		Node* tempNode2 = (Node*)$3;
		
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
				$$ = newNode;
		}
		|
		term TOKEN_DIVIDE factor
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
			$$ = newNode;
		//}
		
	};


factor : 
	primary
	{
		Node* newNode = createNode();
		
		newNode->type = factor;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		newNode->intValue = tempNode->intValue;
		newNode->semTypeDef=tempNode->semTypeDef ;  
		$$ = newNode;
	}
	|
	factor TOKEN_POWER primary
	{
		Node *newNode = createNode();
		
		newNode->type = factor;
		newNode->pt0 = $1;
		newNode->pt2 = $3;
		Node* tempNode0 = (Node*)$1;
		Node* tempNode1 = (Node*)$3;
		
		$$ = newNode;
		
	}
	|
	procedureStatement
	{
		Node *newNode = createNode();
		
		Node* tempNode = (Node*)$1;
		newNode->intValue = tempNode->intValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		$$ = newNode;
	};

primary :
	realNumber
	{
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = $1;
		Node *tempNode = (Node*)$1;
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=storeReal;
		$$ = newNode;
	}
	|
	integer
	{	
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = $1;
		Node *tempNode = (Node*)$1;
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=storeInteger;
		$$ = newNode;
	}
	|
	variable
	{
		Node *tempNode=$1;
		Symbol* foundEntry = lookUp(tempNode->identLex,currentScope);
		tempNode->semTypeDef=foundEntry->type ;
		$$=tempNode;	
	}
	|
	TOKEN_OPEN_BRACKET arithmeticExpression TOKEN_CLOSE_BRACKET
	{
		Node *newNode = createNode();
		
		newNode->type = primary;
		newNode->pt1 = $2;
		Node *tempNode = (Node*)$2;  
		newNode->intValue = tempNode->intValue;
		newNode->realValue=tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		$$ = newNode;
	};

realNumber :  
	TOKEN_REAL_NUM
	{
		Node *newNode = createNode();
		
		newNode->type = realNumber;
		newNode->realValue = atof(yytext);
		newNode->semTypeDef=storeReal;
		$$ = newNode;
	};

integer :
	TOKEN_INTEGER
	{
		Node *newNode = createNode();
		
		newNode->type = integer;
		newNode->intValue = atoi(yytext);
		newNode->semTypeDef=storeInteger;  
		$$ = newNode;
	};

variable : 
	identifier
	{
		Node* newNode = createNode();
		
		newNode->type = variable;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		newNode->boolValue = tempNode->boolValue;
		newNode->intValue = tempNode->intValue;
		newNode->realValue=tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		strcpy(newNode->identLex,tempNode->identLex);
		$$ = newNode;
	}
	|
	subscriptedVariable
	{
		Node *newNode = createNode();
		
		newNode->type = variable;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		newNode->boolValue = tempNode->boolValue;
		newNode->intValue = tempNode->intValue;
		newNode->realValue=tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		strcpy(newNode->identLex, tempNode->identLex);
		$$ = newNode;
	};	

subscriptedVariable :
	arrayIdentifier TOKEN_OPEN_SQUARE_BRACKET subscriptList TOKEN_CLOSE_SQUARE_BRACKET
	{
		Node* newNode = createNode();
		               	  
		newNode->type = subscriptedVariable;
		newNode->pt0 = $1;
		newNode->pt2 = $3;
		Node* tempNode0 = $1;
		Node* tempNode1 = $3;
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
		$$ = newNode;
	}
	;

subscriptList:
	subscriptExpression
	{
		Node* newNode = createNode();
		newNode->type = subscriptList;
	
		Node* tempNode = $1;
		newNode->pt0 = $1;
		if(tempNode->semTypeDef==storeInteger){
			newNode->semTypeDef = tempNode->semTypeDef;
		}
		else {
			newNode->semTypeDef = storeError;
		}
		$$ = newNode;
	}
	|
	subscriptList TOKEN_COMMA subscriptExpression
	{
		Node* newNode = createNode();
		newNode->type = subscriptList;
		newNode->pt0 = $1;
		newNode->pt1 = $3;
		Node* tempNode1 = $1;
		Node* tempNode2 = $3;
	
		if(tempNode2->semTypeDef == storeInteger){
			newNode->semTypeDef = tempNode2->semTypeDef;
		}
		else {
			newNode->semTypeDef = storeError;
		}
		$$ = newNode;
	};

subscriptExpression:
	arithmeticExpression
	{
		Node* newNode = createNode();
		newNode->type = subscriptExpression;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		newNode->intValue = tempNode->intValue;
		$$ = newNode;
	};

identifier:
	TOKEN_IDENTIFIER
	{
		Node* newNode = createNode();
		newNode->type = identifier;
		strcpy(newNode->identLex,yytext);
		$$ = newNode;
	};

booleanExpression:
	simpleBoolean
	{
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		if(tempNode->semTypeDef == storeBoolean){
			newNode->semTypeDef = tempNode->semTypeDef;
		}
		else{
			newNode->semTypeDef = storeError;
		}
		$$ = newNode;
	}
	|
	ifClause simpleBoolean TOKEN_ELSE booleanExpression
	{
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = $1;
		newNode->pt1 = $2;
		newNode->pt2 = $4;
		Node* tempNode1 = $1;
		Node* tempNode2 = $2;
		Node* tempNode3 = $4;
		if(tempNode1->semTypeDef == storeBoolean && tempNode2->semTypeDef == storeBoolean && tempNode3->semTypeDef == storeBoolean){
			newNode->semTypeDef = tempNode3->semTypeDef;
		}
		else{
			newNode->semTypeDef = storeError;
		}
		$$ = newNode;
	};

simpleBoolean:
	implication
	{
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		newNode->boolValue = tempNode->boolValue;
		newNode->semTypeDef = tempNode->semTypeDef;
		$$ = newNode;
	}
	|
	simpleBoolean TOKEN_EQUIV implication
	{
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = $1;
		newNode->pt2 = $3;
		$$ = newNode;
	};

implication : 
	booleanTerm
	{
		Node *newNode = createNode();
		newNode->type = implication;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		newNode->semTypeDef=tempNode->semTypeDef;
		$$ = newNode;  
	}
	|
	implication TOKEN_IMPLY booleanTerm
	{
		Node *newNode = createNode();         		
		newNode->type = implication;
		newNode->pt0 = $1;
		newNode->pt2 = $3;
		Node* tempNode1 = $1;
		Node* tempNode2 = $3;
		if (tempNode1->semTypeDef==storeBoolean && tempNode2->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean ;  
		}
		else {  
			newNode->semTypeDef=storeError;
		}
		$$ = newNode; 
	};

booleanTerm :
	booleanFactor
	{
		Node *newNode = createNode();
		newNode->type = booleanTerm;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		newNode->semTypeDef=tempNode->semTypeDef;
		$$ = newNode;
	}
	|
	booleanTerm TOKEN_OR_OP booleanFactor
	{
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = $1;
		newNode->pt2 = $3;
		Node* tempNode1 = (Node*)$1;
		Node* tempNode2 = (Node*)$3;
		if (tempNode1->semTypeDef==storeBoolean && tempNode2->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean;
		}
		else {
			newNode->semTypeDef=storeError ;  
		}
		$$ = newNode;  
	};

booleanFactor :
	booleanSecondary
	{
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		newNode->semTypeDef=tempNode->semTypeDef;
		$$ = newNode;
	}
	|
	booleanFactor TOKEN_AND_OP booleanSecondary
	{
		Node *newNode = createNode();
		newNode->type = booleanFactor;
		newNode->pt0 = $1;
		newNode->pt2 = $3;
		Node* tempNode1 = (Node*)$1;
		Node* tempNode2 = (Node*)$3;
		if (tempNode1->semTypeDef==storeBoolean && tempNode2->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean ;  
		}
		else {  
			newNode->semTypeDef=storeError ;  
		}
		$$ = newNode;  
	};

booleanSecondary :
	booleanPrimary 
	{
		Node *newNode = createNode();
		newNode->type = booleanSecondary;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		newNode->semTypeDef=tempNode->semTypeDef;
		$$ = newNode;
	}
	|
	TOKEN_NOT_OP booleanPrimary
	{
		Node *newNode = createNode();
		newNode->type = booleanSecondary;
		newNode->pt1 = $2;
		Node* tempNode = $2;
		if (tempNode->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean ;  
		}
		else {  
			newNode->semTypeDef=storeError ;  
		}
		$$ = newNode;
	}
	;

booleanPrimary :
	logicalValue
	{
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		newNode->semTypeDef=tempNode->semTypeDef;
		$$ = newNode;
	}
	|
	boolVariable
	{
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = $1;
		Node *tempNode=$1;
		Symbol* entry = lookUp(tempNode->identLex,currentScope);
		tempNode->semTypeDef = entry->type;
		newNode->semTypeDef = tempNode->semTypeDef;
		$$=newNode;
	}
	|
	relation
	{
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		newNode->semTypeDef=tempNode->semTypeDef;
		$$=newNode;
	}
	|
	TOKEN_OPEN_BRACKET booleanExpression TOKEN_CLOSE_BRACKET
	{
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = $1;
		Node* tempNode = $1;  
		newNode->semTypeDef=tempNode->semTypeDef;
		$$=newNode;
	};

logicalValue:
	TOKEN_LOGICAL_VALUE
	{
		Node* newNode = createNode();
		newNode->type = logicalValue;
		if (strcmp("true",yytext)==0){
			newNode->boolValue = true;
		}
		else{
			newNode->boolValue = false;
		}
		$$ = newNode;
	};

relation : 
	simpleArithmeticExpression relationalOperator simpleArithmeticExpression
	{
		Node *newNode = createNode();
		newNode->type = relation;
		newNode->pt0 = $1;
		newNode->pt1 = $2;
		newNode->pt2 = $3;
		Node* tempNode0 = $1;
		Node* tempNode1 = $2;
		Node* tempNode2 = $3;
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
		$$=newNode;
	};
	        
boolVariable : boolSimpleVariable
	{
		Node* newNode = createNode();
		newNode->type = boolVariable;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		newNode->boolValue = tempNode->boolValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		strcpy(newNode->identLex, tempNode->identLex);
		$$ = newNode;
	}; /*{////printf("Variable Parsed \n");}*/

boolSimpleVariable :
	TOKEN_BOOL_IDENTIFIER
	{
		Node *newNode = createNode();
		newNode->type = boolSimpleVariable;
		strcpy(newNode->identLex, yytext);
		$$ = newNode;
	} /*{////printf("Identifier parsed\n");}*/
	;

relationalOperator :
	TOKEN_REL_OP
	{	
		Node *newNode = createNode();
		newNode->type = relationalOperator;
		strcpy(newNode->identLex, yytext);
		$$ = newNode;
	};

listType :
	varIdentifier
	{

		Node *temp2=$0;

		Node *temp1=$1;

		if (lookUpInCurrentScope(temp1->identLex)!=NULL){

			return 0;
		}
		else{
			Symbol *newEntry=addEntry(temp1->identLex);
			
			newEntry->type=temp2->semTypeDef;
			$$=$0;			


		}

	}
	|
	varIdentifier TOKEN_COMMA 
	{
		Node *temp2=$0;
		Node *temp1=$1;
		if (lookUpInCurrentScope(temp1->identLex)!=NULL){
		}
		else{
			Symbol *newEntry=addEntry(temp1->identLex);
			
			newEntry->type=temp2->semTypeDef;			
		}
		$$=$0;

		
	}
	listType	

	;


type :
	TOKEN_TREAL
	{
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef = storeReal;
		$$ = new;

	}
	|
	TOKEN_TINTEGER
	{
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeInteger;
		$$ = new;

		

	}
	|
	TOKEN_BOOLEAN
	{
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeBoolean;
		$$ = new;



	}


	;





typeDeclaration :
	type listType
	{
	

	}
	;

varIdentifier :
	identifier
	{
		Node *new = createNode();		new->type = varIdentifier;
		new->pt0 = $1;
		Node* temp = (Node*)$1;
			
		new->realValue=temp->realValue;		
		new->intValue=temp->intValue;
		new->boolValue=temp->boolValue;
		strcpy(new->identLex, temp->identLex);
		$$ = new;
	}
	;

unconditionalStatement :
	basicStatement
	{
		Node *new = createNode();         	
        	new->type = unconditionalStatement;
        	new->pt0 = $1;
		Node *temp1 = $1;
		new->semTypeDef=temp1->semTypeDef;
		$$ = new;



	
	}
	|
        compoundStatement {

		Node *new = createNode();         	
        	new->type = unconditionalStatement;
        	new->pt0 = $1;
		Node *temp1 = $1;
		new->semTypeDef=temp1->semTypeDef;
		$$ = new;

	}
	|
	block {

		Node *new = createNode();
        	new->type = unconditionalStatement;
        	new->pt0 = $1;
		Node *temp1 = $1;
		new->semTypeDef=temp1->semTypeDef;
		$$ = new;


	}

	;

conditionalStatement :
	ifStatement
	{
		Node *new = createNode();         	
        	new->type = conditionalStatement;
        	new->pt0 = $1;
		Node *temp = $1;
		new->semTypeDef=temp->semTypeDef;
		$$ = new;
	}

	|

        ifClause unconditionalStatement TOKEN_ELSE statement
	{
		Node *new = createNode();         	
        	new->type = conditionalStatement;
        	new->pt0 = $1 ;  
		new->pt2 = $3 ;  
		Node *temp1 = $1 ;  
		Node *temp2 = $2 ;  
		if (temp1->semTypeDef==storeVoid && temp2->semTypeDef==storeVoid ) {  
		new->semTypeDef=storeVoid ;  
		}


		$$ = new;

	}



	|
        ifClause forStatement
	{
		
		Node *new = createNode();         	
		new->type = conditionalStatement;
		new->pt0 = $1 ;  
		new->pt1 = $2 ;  
		Node *temp1=$1;
		Node *temp2=$2;
		
		if (temp1->semTypeDef==storeBoolean && temp2->semTypeDef==storeVoid ) {  
			new->semTypeDef==storeVoid ;  
		
	
		}
		else{
			new->semTypeDef==storeError ;  

		}
		
		$$=new;
	}


	/*|
        label TCOLON conditional_statement*/
	;

ifStatement :
	ifClause unconditionalStatement 
	{
		Node *new = createNode();         	
        	new->type = ifStatement;
        	new->pt0 = $1;
		new->pt1 = $2;
		Node *temp = $1;
		Node *temp2 = $2;
		
		if (temp->semTypeDef==storeBoolean) {  
			new->semTypeDef=temp2->semTypeDef;
		}
		else {
			new->semTypeDef=storeError;
		}
		
		$$ = new;


	}
	;

ifClause :
	TOKEN_IF booleanExpression TOKEN_THEN
	{
		Node *new = createNode();
        	new->type = ifClause;
        	new->pt1 = $2;
                Node* temp = (Node*)$2;
		if (temp->semTypeDef==storeBoolean) {  
			new->semTypeDef=storeBoolean ;  
		}
		else {  
			new->semTypeDef=storeError ;  
		}
		
		$$ = new;  
	}
	;


basicStatement :
	unlabelledBasicStatement {

		Node *new = createNode();         	
        	new->type = basicStatement;
        	new->pt0 = $1 ;  
		Node *temp = $1 ;  
		new->semTypeDef=temp->semTypeDef ;  

		$$ = new;

	}



	//|
    //    label /*TCOLON*/ basicStatement
	;

unlabelledBasicStatement :
	assignmentStatement
	{		
		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement; 
        	new->pt0 = $1 ; 
		Node *temp = $1 ;  
		new->semTypeDef=temp->semTypeDef ;  
		$$ = new;

	}


	|
	dummyStatement
	{

		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = $1 ;  
		Node *temp = $1 ;  

		new->semTypeDef=temp->semTypeDef ;  

		$$ = new;

	}
	|
        procedureStatement
	{
			
		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = $1 ;  
		Node *temp = $1 ;  
		new->semTypeDef=temp->semTypeDef ;  
		$$ = new;

	}
	|
	returnStatement
	{
		$$ = $1;
	}

	;

dummyStatement :
	empty
	;
	
returnStatement :
	TOKEN_RETURN expression
	{
		Node *new = createNode();
                new->type = returnStatement;
		Node *temp = $2 ;
		if(temp->semTypeDef==storeError)
		{
			new->semTypeDef=storeError;
		}
		else
		{
			new->semTypeDef = temp->semTypeDef;
		}
		$$ = new;
	};

assignmentStatement :
	TOKEN_ASSIGN_IDENTIFIER arithmeticExpression  
	{
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = $1;
		new->pt2 = $2;
		$$ = new;
		Symbol *symbol1;	
		Node *tmp1=$1;
		Node *tmp2=$2;
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
	|
	TOKEN_ASSIGN_IDENTIFIER booleanExpression
	{
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = $1;
		new->pt2 = $2;
		$$ = new;
	
		Node *temp1=$1;
		Node *temp2=$2;
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

	;
/*

forListElement :
	arithmeticExpression
	{
		Node *temp = $-2;
		//////printf("%p\n",temp);
		//////printf("\t\t\t\t\t\t\t\t a as %d\n", temp->type);
	

		if (!(temp->semTypeDef==storeInteger || temp->semTypeDef==storeReal)) {  
			temp->semTypeDef=storeError ;  
		}
		else {	Symbol *symbol2=lookUp(temp->identLex,currentScope);
			//int tableindex=lookUp(temp->identifier,current_scope);
			//int type_variable = table[temp_scope].entry[tableindex].type ;
			//////printf("\t\t\t\t\t\t\t\twith a as %d\n", type_variable);
			
			//type cast
			Node *temp1 = $1;
			if (temp1->semTypeDef == symbol2->type) {  
				temp->semTypeDef=storeVoid ;  
				//good case
				//////printf("\t\t\t\t\t\t\t\tgood case with a as %d\n", type_variable);

// This is not required to be done REDUNDANT

				if (symbol2->type==streInteger) {  
					symbol2->value=temp1->intValue;
				}
				else {  
					//table[current_scope].entry[tableindex].floatvalue=temp1->real;					//check here
				}



			}
			else {  
				if (symbol2->type == storeInteger) {  
					//////printf("Loss of precision in for statement\n");	
					//error
				}
			
				else {  

//POSSIBLY REDUNDANT !!!!!!!!!!!!!

					//table[tableindex].floatvalue=1.00*temp1->integer;
					//Have to do type casting in code generation stage
					//////printf("%s now been type cast to value %f\n",temp->identifier,table[tableindex].floatvalue);
				}

			}
			//////printf("%s yabba\n",temp->identifier);
			
		}
		$$=$-2;
	}
	|
	arithmeticExpression TOKEN_STEP arithmeticExpression TOKEN_UNTIL arithmeticExpression {  

		Node *temp = $-2;
		Symbol *symbol2=lookUp(temp->identLex,currentScope);

		//int tableindex=lookUp(temp->identifier,current_scope);
		//int type_variable = table[temp_scope].entry[tableindex].type ;

		if (!(temp->semTypeDef==storeInteger || temp->semTypeDef==storeReal)) {  
			temp->semTypeDef=storeError ;  
		}
		else
		{

			//type cast
	
			Node *temp1 = $1;
			Node *temp2 = $3;
			Node *temp3 = $5;
			if (temp1->semTypeDef == symbol2->type && temp2->semTypeDef == symbol2->type && temp1->semTypeDef == symbol2->type) {  
				
				//good case
			}
			else {  
				//error
				if(symbol2->type == storeInteger)
				{
					//error
				}
				else
				{
					//TYPE CASTING TO BE DONE DURING CODE GENERATION
				}
				
			}
			//////printf("%s yabba\n",temp->identifier);
		}
		$$=$-2;
	}
	|
        arithmeticExpression TOKEN_WHILE booleanExpression	{
		Node *temp = $-2;
		Symbol *symbol2=lookUp(temp->identLex,currentScope)
		//////printf("%sBOOLEAN rtrtyabba\n",temp->identifier);
		//int tableindex=lookUp(temp->identifier,current_scope);
		//int type_variable = table[temp_scope].entry[tableindex].type ;
		//type cast

		if (!(temp->semTypeDef==storeInteger || temp->semTypeDef==storeReal)) {  
			temp->semTypeDef=storeError ;  
		}
		else
		{

			Node *temp1 = $1;
			if (temp1->semTypeDef == storeVariable) {  
				
				//good case
	
	
			}
			else {  
				//error
				//Check for error in Boolean Expression
			}
			//////printf("%sBOOLEAN yabba\n",temp->identifier);
		}
		$$=$-2;
	}
	;


forList :
	forListElement
	|
	forListElement TOKEN_COMMA {
		Node *temp1 = $-1;
		Node *temp2 = $0;
		//Node *temp3 = $1;
		//////printf("R says %p\n",temp1);
		//////printf("R says %p\n",temp2);
		//////printf("R says %p\n",temp3);

		//$1=$-1;
		
		//$$=$0;
	} forList 
	;



forClause :
	TOKEN_FOR variable 
	{
		Node *temp = $2;
		Symbol *symbol2=lookUp(temp->identLex,currentScope);
		if (symbol2 == NULL) {  
			temp->semTypeDef=storeError;		
		}
		else {  
			if (symbol2->type==storeInteger || symbol2->type==storeReal)){
				temp->semTypeDef=storeError;
			}
		}

		$$=$2;
		

	}

 TOKEN_ASSIGN forList TOKEN_DO
	{
		
	};*/

forStatement :
	/*for_clause statement
	|*/
	TOKEN_FOR variable TOKEN_ASSIGN arithmeticExpression TOKEN_STEP arithmeticExpression TOKEN_UNTIL arithmeticExpression TOKEN_DO  statement
	{  
		Node *new = createNode();
		Node *temp = $2;
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
			$$ = new;
		}
		else
		{

			Node *temp2 = $4;
			Node *temp3 = $6;
			Node *temp4 = $8;
			Node *temp5 = $10;
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
			$$=new;
		}
	}
	/*|
        label TCOLON for_statement*/
	;

empty :	
	{	
		Node *new = createNode();         	            	  
        	new->type =empty;
		$$ = new;
	}
	 ;
procedureStatement :
	procedureIdentifier actualParameterPart {
		Node *new = createNode();
		Node *temp1 = $1;
		Symbol *symbol= lookUp(temp1->identLex,currentScope);

		if(symbol == NULL)
		{

			new->semTypeDef = storeError;
		}
		else
		{
			Node *temp2 = $2;
			if(temp2->semTypeDef==storeError)
			{
				new->semTypeDef =storeError;
		}
		else
		{
			new->semTypeDef = symbol->type;

		}
	}

		$$ = new; 
	}
	;

procedureIdentifier :
	identifier
	{
		Node *new = createNode(); 
		new->type = procedureIdentifier;
		new->pt0 = $1;
	
		Node *temp=$1;

		$$ = new;
	}
	;
actualParameterPart :
	TOKEN_OPEN_BRACKET actualParameterList TOKEN_CLOSE_BRACKET
	{
		$$=$2;
		Node *temp = $2;
		if(temp->semTypeDef != storeError)
		{		
			temp->semTypeDef == storeVoid;
		}
		
	}
	;

actualParameterList :
	actualParameter
	{
		Node *temp = $-1;
		Node *temp1 = $1;
		
		Symbol* symbol= lookUp(temp1->identLex,currentScope);
		Node *new = createNode();
		new->intValue = 0;
		
		new->semTypeDef = storeVoid;
		
		$$ = new;
	}
	|
        actualParameterList parameterDelimiter actualParameter  
	{
		Node *temp = $-1;
		Node *temp3 = $1;
		Node *temp1 = $3;

		Symbol* symbol= lookUp(temp->identLex,currentScope);
		
		Node *new = createNode();
		new->intValue = 1 + temp3->intValue;
		if(temp3->semTypeDef == storeError)
			new->semTypeDef = storeError;
		else
		{new->semTypeDef = storeVoid;
			
			
		}	
		$$ = new;

	}
	;

actualParameter :
	expression
	{
		Node *new = createNode(); 
		Node *temp = $1; 
		new->type = actualParameter;
		new->semTypeDef = temp->semTypeDef;
		new->pt0 = $1;

		$$ = new;
	};

parameterDelimiter : TOKEN_COMMA;

statement :
	unconditionalStatement //TOKEN_SEMICOLON statement 
	{
		Node* new=createNode();
		Node *temp1=$1;
//		Node *temp2=$3;
		$$=new;
	}
	|
        conditionalStatement //TOKEN_SEMICOLON statement 
	{
		Node* new=createNode();
		Node *temp1=$1;
//		Node *temp2=$3;
		$$=new;

	}
	|
	forStatement //TOKEN_SEMICOLON statement
	{	Node* new=createNode();
		Node *temp1=$1;
//		Node *temp2=$3;
		$$=new;
	}
	|
/*	declaration //TOKEN_SEMICOLON statement
	{
		Node* new=createNode();
		Node *temp1=$1;
//		Node *temp2=$3;
		$$=new;
	}
	|*/
//	expression //TOKEN_SEMICOLON statement 
//	|
	TOKEN_PRINT expression
	{
		Node* new=createNode();
		Node* temp=$2;

		$$=new;
	}
/*	|
	dummyStatement
	{
		Node* new=createNode();
		$$=new;
	}*/
	;


formalParameter :
	identifier
	{
		$0=$-1;
		Node *node1 = $1;
		
		int oldScope = currentScope;
		currentScope = globalLevel + 1;

		if (lookUpInCurrentScope(node1->identLex) == NULL){
			Symbol * index = addEntry(node1->identLex);
		}
		currentScope = oldScope;
	};
	
formalParameterList :
	formalParameter
	| formalParameter TOKEN_COMMA{
		$1 = $0;
		$2 = $0;
	}
	formalParameterList;

formalParameterPart :
	empty {
		$$ = $0;
	}
	| TOKEN_OPEN_BRACKET {
		$1 = $0;
	} formalParameterList TOKEN_CLOSE_BRACKET;

identifierList :
	identifier {
		Node *node1 = $0;
		Node *node2 = $1;
		Symbol *symbol = lookUp(node2->identLex,currentScope);
		symbol->type = node1->semTypeDef;
	}
	| identifierList TOKEN_COMMA identifier{
		$2 = $0;
	};

valuePart : empty | TOKEN_VALUE identifierList TOKEN_SEMICOLON{
		$3 = $0;
	};
specifier :
	type 
	| type TOKEN_ARRAY
	| TOKEN_TYPE_LABEL 
	| TOKEN_SWITCH 
	| type TOKEN_PROCEDURE;
specificationPart : specifier identifierList TOKEN_SEMICOLON{
		$3 = $0;
		Node *node1 = $1;
	}
	| specificationPart specifier identifierList TOKEN_SEMICOLON;

procedureHeading :
	procedureIdentifier {
		Node *node = createNode();
		node->type = procedureHeading;
		node->pt0 = $1;
		Node *node1 = $1;
		node1->parent = node;
		strcpy(node->identLex, node1->identLex);
		if (lookUpInCurrentScope(node1->identLex) == NULL){
			Symbol * index = addEntry(node1->identLex);
		}
		$$ = node;
	}
	formalParameterPart TOKEN_SEMICOLON {
		$3 = $1;
	} valuePart specificationPart
	/*| procedureIdentifier {
		Node *node = createNode();
		node->type = procedureHeading;
		node->pt0 = $1;
		Node *node1 = $1;
		node1->parent = node;
		strcpy(node->identLex, node1->identLex);
		if (lookUpInCurrentScope(node1->identLex) == NULL){
			Symbol * index = addEntry(node1->identLex);
		}
		$$ = node;
	}
	formalParameterPart TOKEN_SEMICOLON {
		$3 = $1;
	} valuePart*/;

procedureBody :
	TOKEN_BEGIN TOKEN_SEMICOLON statement{
		Node *new = createNode();
		
		new->type = procedureBody;
		Node *temp = $3;
		new->semTypeDef = temp->semTypeDef;
		$$ = new;
	} TOKEN_END;

procedureDeclaration : 
	TOKEN_PROCEDURE procedureHeading procedureBody {
		Node *node1 = $2;
		Node *node2 = $3;

		Symbol* symbol = lookUpInCurrentScope(node1->identLex);
		symbol->type = storeVoid;

		Node *node = createNode();
                
        	node->type = procedureDeclaration;

		if (node1->semTypeDef == storeVoid && node2->semTypeDef == storeVoid)
			node->semTypeDef = storeVoid;
		else
			node->semTypeDef = storeError;
		$$ = node;
	}
	| type TOKEN_PROCEDURE procedureHeading procedureBody
	{
		Node *node1 = $3;
		Node *node2 = $1;
		Node *node3 = $4;

		Symbol* symbol = lookUpInCurrentScope(node1->identLex);
		symbol->type = node2->semTypeDef;

		Node *node = createNode();
                
        	node->type = procedureDeclaration;

		if (node1->semTypeDef == storeVoid && node3->semTypeDef == storeVoid)
			node->semTypeDef = node2->semTypeDef;
		else
			node->semTypeDef = storeError;
		$$ = node;
	};


%%

