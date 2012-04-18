%{
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
		symbolTable[num].parent = currentScope;
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
%} 
 

////////////TOKEN DEFINITIONS/////////////

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
%token TOKEN_UNDERSCORE
%token TOKEN_SPECIFIER
%token TOKEN_LIBRARY
%token TOKEN_BRACKET
%token TOKEN_OPEN_BRACKET
%token TOKEN_CLOSE_BRACKET
%token TOKEN_OPEN_SQUARE_BRACKET
%token TOKEN_CLOSE_SQUARE_BRACKET
%token TOKEN_OPEN_CURLY_BRACKET                  //added support for belu curly brackets
%token TOKEN_CLOSE_CURLY_BRACKET		//belup
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
//%token TOKEN_TINTEGER
//%token TOKEN_TREAL
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
%left	TOKEN_REL_OP
%left	TOKEN_PLUS TOKEN_MINUS
%right	TOKEN_POWER

%start  program

//%union {
//	//float fvalue;
//	int integerVal; 		/* integer value */
//	char* symbolIndex; 		/* symbol table index */
//	Node *pt; 			/* node pointer */
//};


/*
%type <tree> program block unlabelledBlock
%type <tree> unlabelledBasicStatement compoundStatement unlabelledCompound compoundTail
%type <tree> basicStatement unconditionalStatement
%type <tree> statement conditionalStatement forStatement gotoStatement assignmentStatement
%type <tree> ifStatement tlabel procedureStatement procedureBody

%type <sym> declaration typeDeclaration arrayDeclaration switchDeclaration procedureDeclaration listType
%type <sym> procedureHeading formalParameterPart formalParameterList identifierList formalParameter
%type <sym> valuePart specificationPart specificationIdentifierList
%type <sym> arraySegment arrayList

%type <typ> type 

%type <expr> arithmeticExpression simpleArithmeticExpression
%type <expr> subscriptedExpression relation booleanExpression functionDesigntor
%type <expr> designationExpression simpleDesigntionalExpression 
%type <expr> ifClause actualParameterPart actualParameterList actualParameter

%type <bound> boundPair boundPairList 
%type <mindex> subscriptedList
*/

%%


blockHead :
	TOKEN_BEGIN declaration
	{
		currentScope = scopeStack[scopeStackTop-1];
		printf("current Scope = %d\n",currentScope);
		Node* newNode = createNode();
		Node* tempNode = $2;
		strcpy(newNode->code,tempNode->code);
		$$=newNode;
		printf("blockHead\n");
	}
	|blockHead TOKEN_SEMICOLON declaration
	{
		Node* newNode = createNode();
		Node* tempNode1 = $1;
		Node* tempNode2 = $3;
		sprintf(newNode->code,"%s%s",tempNode1->code,tempNode2->code);
		$$=newNode;
		printf("blockHead\n");
	}
	;

unlabelledBlock :
	blockHead TOKEN_SEMICOLON compoundTail
	{
		Node* newNode = createNode();
		Node* tempNode1 = $1;
		Node* tempNode2 = $3;
		newNode->pt0 = $3;
		sprintf(newNode->code,"%s%s",tempNode1->code,tempNode2->code);
		$$ = newNode;
	};

block :
	unlabelledBlock 
	{
		Node *newNode = createNode();
		newNode->pt0 = $1;
		Node* tempNode = $1;
		sprintf(newNode->code,tempNode->code);
		$$ = newNode;
		printf("unlabelled block\n");
	}
	|
	tlabel
	/*{
		Node* newNode = createNode();
		newNode->pt0 = $1;
		Node *tempNode = $1;
		strcpy(newNode->identLex, tempNode->identLex);
		$$ = newNode;
	}
	TOKEN_COLON*/ block
	{
		Node *newNode = createNode();
		newNode->pt0 = $2;
		Node* tempNode2 = $2;
		Node* tempNode1 = $1;
		strcpy(newNode->identLex,tempNode1->identLex);
		//No need to get a new label
		int label = getNewLabel();
		sprintf(newNode->code,"b\tlabel%d\n%s:\n%slabel%d:\n",label, tempNode1->identLex, tempNode2->code,label);
		$$ = newNode;
		printf("labelled block\n");
	}
	/*|
	error
	{
		printf("Syntax error in block containing line num %d\n",lineNo);
	}*/
	;

/*label :    ////check////
	TOKEN_LABEL_IDENTIFIER
	{
		Node *new = createNode();         	
                new->type = label;
		strcpy(new->identLex, yytext);
		$$ = new;
	};
*/

tlabel : label TOKEN_COLON
	{
		Node* newNode = createNode();
		Node* tempNode = $1;
		strcpy(newNode->identLex,tempNode->identLex);
		$$=newNode;
	};

label :
	identifier
	{
		Node* newNode = createNode();
		Node* tempNode = $1;
		strcpy(newNode->identLex,tempNode->identLex);
		$$=newNode;
	}
	| integer
	{
		Node* newNode = createNode();
		Node* tempNode = $1;
		strcpy(newNode->identLex,atoi(tempNode->intValue));
		$$=newNode;
	}
	;

program :
	compoundStatement
	{
		printf("compoundStatement\n");
		Node* newNode = createNode();
		Node* tempNode = $1;
		strcpy(newNode->code,tempNode->code);
		strcpy(code,newNode->code);
		int i;
		for(i=0; i <= globalLevel; i++){
			symbolTableDisplay(i);
		}
		$$=newNode;
	}
	
	| block
	{
		printf("block\n");
		Node* newNode = createNode();
		Node* tempNode = $1;
		strcpy(newNode->code,tempNode->code);
		strcpy(code,newNode->code);
		int i;
		for(i=0; i <= globalLevel; i++){
			symbolTableDisplay(i);
		}
		$$=newNode;
	}
	
	
	;

unlabelledCompound :
	TOKEN_BEGIN compoundTail{
		currentScope = scopeStack[scopeStackTop-1];
		printf("current Scope = %d\n",currentScope);
		Node* newNode = createNode();
		Node* tempNode = $2;
		strcpy(newNode->code,tempNode->code);
		printf("unlabelled compound\n");
		$$=newNode;	
	}
	;

compoundStatement :
	unlabelledCompound
	{
		Node* newNode = createNode();
		Node* tempNode = $1;
		strcpy(newNode->code,tempNode->code);
		printf("cmpndStatement->unlabelledCompnd\n");
		$$=newNode;	
	}
	|
	tlabel /*TOKEN_COLON*/ compoundStatement
	{			/////check/////
		Node* newNode = createNode();
		Node* tempNode1 = $1;
		Node* tempNode2 = $2;
		int label = getNewLabel();
		sprintf(newNode->code,"b\tlabel%d\n%s:\n%slabel%d:\n",label,tempNode1->identLex,tempNode2->code,label);
		$$=newNode;	
		printf("labelled compoundstatement\n");
	}
	;

compoundTail :
	statement TOKEN_END
	{
		Node *newNode = createNode();
		newNode->pt0 = $1;
		Node* tempNode = $1;
		strcpy(newNode->code, tempNode->code);
		currentScope = scopeStack[scopeStackTop-1];
		$$ = newNode;
	}	
	|
	statement TOKEN_SEMICOLON compoundTail
	{	
		Node *newNode = createNode();
		newNode->pt0 = $1;
		Node* tempNode1=$1;
		Node* tempNode2=$3;
		sprintf(newNode->code,"%s%s",tempNode1->code,tempNode2->code);
		$$ = newNode;
	}
	
	
	;

declaration : 
	typeDeclaration
	{
		Node* newNode = createNode();
		//Node* tempNode = $1;
		strcpy(newNode->code,"");
		$$=newNode;
	}	 
	|
	arrayDeclaration
	{
		Node* newNode = createNode();
		//Node* tempNode = $1;
		strcpy(newNode->code,"");
		$$=newNode;
	}
	|
	switchDeclaration{
		Node* newNode = createNode();
		//Node* tempNode = $1;
		strcpy(newNode->code,"");
		$$=newNode;
	}
	|
	procedureDeclaration
	{
		Node* newNode = createNode();
		Node* tempNode = $1;
		strcpy(newNode->code,tempNode->code);
		$$=newNode;
	};


lowerBound:
	arithmeticExpression
	{
		Node *newNode = createNode();
		newNode->type = lowerBound;
		newNode->pt0 = $1;
		Node *tempNode = $1;
		newNode->place = tempNode->place;
		strcpy(newNode->code,tempNode->code);
		if(tempNode->semTypeDef==storeInteger){
			newNode->semTypeDef = storeInteger;
			newNode->intValue = tempNode->intValue;
		}
		else{
			printf("error in array declaration-> lowerbound should be integer\n");
		}
		$$=newNode;
		printf("lowerBound->arithmeticExpression\n");
	};

upperBound:
	arithmeticExpression
	{
		Node *newNode = createNode();
		newNode->type = upperBound;
		newNode->pt0 = $1;
		Node *tempNode = $1;
		newNode->place = tempNode->place;
		strcpy(newNode->code,tempNode->code);
		if(tempNode->semTypeDef==storeInteger){
			newNode->semTypeDef = storeInteger;
			newNode->intValue = tempNode->intValue;
		}
		else{
			printf("error in array declaration-> lowerbound should be integer\n");
		}
		$$=newNode;
		printf("upperBound->arithmeticExpression\n");
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
		
		if (tempNodeOne->semTypeDef==storeInteger && tempNodeTwo->semTypeDef==storeInteger && tempNodeOne->intValue <= tempNodeTwo->intValue){
			newNode->semTypeDef=storeBoundPairList;
			sprintf(newNode->code,"%s%s",tempNodeOne->code,tempNodeTwo->code);
			newNode->lowerBound[0] = tempNodeOne->intValue;
			newNode->upperBound[0] = tempNodeTwo->intValue;
		}
		else {
			
		}
		$$ = newNode;
		printf("boundPair->lowerBound : upperBound\n");
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
			newNode->dim = 1;
			newNode->lowerBound[newNode->dim-1] = tempNode->lowerBound[0];
			newNode->upperBound[newNode->dim-1] = tempNode->upperBound[0];
		}
		$$ = newNode;
		printf("boundPairList->boundPair\n");
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
		
		$$ = newNode;
		printf("boundPairList->boundPairList , boundPair\n");
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
		printf("arrayIdentifier->identifier\n");
	}
	;

arraySegment :
	arrayIdentifier TOKEN_OPEN_SQUARE_BRACKET boundPairList TOKEN_CLOSE_SQUARE_BRACKET
	{
		Node* newNode = createNode();
		newNode->type = arraySegment;
		newNode->pt0 = $1;
		newNode->pt2 = $3;
		Node *tempNodeOne = $1;
		Node *tempNodeTwo = $3;
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
		
		$$ = newNode;
		printf("arraySegment->arrayIdentifier [ boundPairList ]\n");
	}
	| arrayIdentifier TOKEN_COMMA arraySegment
	{	
		Node* newNode = createNode();
		newNode->type = arraySegment;
		newNode->pt0 = $1;
		newNode->pt2 = $3;
		Node *tempNodeOne = $1;
		Node *tempNodeTwo = $3;
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
		
				
		$$ = newNode;
		
	}////check////
	;

arrayList :
	arraySegment 
	{
				
		Node* tempNode0=$-1;
		Node* tempNode1=$1;
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
					 
		$$=$-1; ////check////
		
	}
	|
	arrayList TOKEN_COMMA arraySegment////check////  
	{
		Node* tempNode0=$1;
		Node* tempNode1=$3;
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
		$$=$1; ////check////
		printf("arrayList->arrayList , arraySegment\n");
	}
	;

arrayDeclaration :
	type TOKEN_ARRAY arrayList
	{
		//$$=$3;
	}
	;


expression :
	arithmeticExpression
	{
		Node *newNode = createNode();
		newNode->type = expression;
		newNode->pt0 = $1;
		Node *tempNode = $1;
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
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
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		$$ = newNode;
	}
	|
	designationalExpression////check////
	{
			
	};

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
		newNode->place = tempNode->place;
		strcpy(newNode->code,tempNode->code);
		printf("arithmetic->simplearithmetic, intval = %d,realval=%f\n",newNode->intValue,newNode->realValue);		
		$$ = newNode;
	}
	/*|
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
	}*///since it appears in unconditional statement
	;

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
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		$$ = newNode;
		printf("simplearithmetic->term, intval = %d\n",newNode->intValue);
		
	}
	| TOKEN_PLUS term ////check////
	{
		Node *newNode = createNode();
		newNode->type = simpleArithmeticExpression;
		newNode->pt0 = $2;
		Node* tempNode = (Node*)$2;
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef ;
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		$$ = newNode;
		printf("simplearithmetic->term, intval = %d\n",newNode->intValue);

	}
	| TOKEN_MINUS term ////check////
	{
		Node *newNode = createNode();
		newNode->type = simpleArithmeticExpression;
		newNode->pt0 = $2;
		Node* tempNode = (Node*)$2;
		newNode->intValue = 0-tempNode->intValue;
		newNode->realValue = 0.0-tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef ;
		newNode->place=getNewTemp();
		//strcpy(newNode->code,tempNode->code);
		if(tempNode->semTypeDef == storeReal){
			sprintf(newNode->code,"%s\nli.s\t$f0,0.0\nl.s\t$f1,%d($sp)\nsub\t$f2,$f0,$f1\ns.s\t$f2,%d($sp)\n",tempNode->code,tempNode->place,newNode->place);
		}
		else{
			sprintf(newNode->code,"%s\nli\t$t0,0\nlw\t$t1,%d($sp)\nsub\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",tempNode->code,tempNode->place,newNode->place);
		}
		$$ = newNode;
		printf("simplearithmetic->term, intval = %d\n",newNode->intValue);

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
		sprintf(newNode->code,"%s%s",tempNode0->code,tempNode2->code);
		if (tempNode0->semTypeDef==storeReal  || tempNode2->semTypeDef==storeReal)
		{			
			newNode->semTypeDef = storeReal ;  
			if (tempNode0->semTypeDef==storeInteger) {  
				tempNode0->realValue = 1.00*tempNode0->intValue;  
				tempNode0->semTypeDef==storeReal;
				sprintf(newNode->code,"%slw\t$t0,%d($sp)\nmtc1\t$t0,$f0\ncvt.s.w\t$f0,$f0\ns.s\t$f0,%d($sp)\n",newNode->code,tempNode0->place,tempNode0->place);
				
			}
			else if (tempNode2->semTypeDef==storeInteger) {  
				tempNode2->realValue = 1.00*tempNode2->intValue;  
				tempNode2->semTypeDef==storeReal;
				sprintf(newNode->code,"%slw\t$t0,%d($sp)\nmtc1\t$t0,$f0\ncvt.s.w\t$f0,$f0\ns.s\t$f0,%d($sp)\n",newNode->code,tempNode2->place,tempNode2->place);
			}

			newNode->realValue=tempNode0->realValue  +  tempNode2->realValue;
			printf("tempnoderealval: %f\n",tempNode2->realValue);	
			sprintf(newNode->code,"%sl.s\t$f0,%d($sp)\nl.s\t$f1,%d($sp)\nadd.s\t$f2,$f0,$f1\ns.s\t$f2,%d($sp)\n",newNode->code,tempNode0->place,tempNode2->place,tempNode0->place);
			newNode->place = tempNode0->place;	
		}
		else {  			
			newNode->semTypeDef = storeInteger ;  
			newNode->intValue = tempNode0->intValue  +  tempNode2->intValue ;
			//newNode->place=getNewTemp(); 
			sprintf(newNode->code,"%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nadd\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",newNode->code,tempNode0->place,tempNode2->place,tempNode0->place);
			newNode->place=tempNode0->place;
		}
		printf("simplearithmetic->simplearithmetic + term, realval = %f\n",newNode->realValue);
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
		sprintf(newNode->code,"%s%s",tempNode0->code,tempNode2->code);
		if (tempNode0->semTypeDef==storeReal  || tempNode2->semTypeDef==storeReal) {  
			newNode->semTypeDef = storeReal ;  
			if (tempNode0->semTypeDef==storeInteger) {  
				tempNode0->realValue = 1.00*tempNode0->intValue;  
				tempNode0->semTypeDef==storeReal;
				sprintf(newNode->code,"%slw\t$t0,%d($sp)\nmtc1\t$t0,$f0\ncvt.s.w\t$f0,$f0\ns.s\t$f0,%d($sp)\n",newNode->code,tempNode0->place,tempNode0->place);
			}
			else if (tempNode2->semTypeDef==storeInteger) {  
				tempNode2->realValue = 1.00*tempNode2->intValue ;  
				tempNode2->semTypeDef==storeReal;
				sprintf(newNode->code,"%slw\t$t0,%d($sp)\nmtc1\t$t0,$f0\ncvt.s.w\t$f0,$f0\ns.s\t$f0,%d($sp)\n",newNode->code,tempNode2->place,tempNode2->place);
			}
			newNode->realValue=tempNode0->realValue  -  tempNode2->realValue ;
			sprintf(newNode->code,"%sl.s\t$f0,%d($sp)\nl.s\t$f1,%d($sp)\nsub.s\t$f2,$f0,$f1\ns.s\t$f2,%d($sp)\n",newNode->code,tempNode0->place,tempNode2->place,tempNode0->place);
			newNode->place = tempNode0->place;
		}
		else {  
			newNode->semTypeDef = storeInteger ;  
			newNode->intValue = tempNode0->intValue - tempNode2->intValue ; 
			//newNode->place=getNewTemp(); 
			sprintf(newNode->code,"%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nsub\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",newNode->code,tempNode0->place,tempNode2->place,tempNode0->place);
			newNode->place=tempNode0->place;
		}
		$$ = newNode;
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
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		printf("term->factor, intval = %d\n",newNode->intValue);
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
		sprintf(newNode->code,"%s%s",tempNode0->code,tempNode2->code);
			if (tempNode0->semTypeDef==storeReal  || tempNode2->semTypeDef==storeReal) {  
				newNode->semTypeDef = storeReal ;  
				if (tempNode0->semTypeDef==storeInteger) {     
					tempNode0->realValue = 1.00*tempNode0->intValue ;  
					tempNode0->semTypeDef==storeReal;
					sprintf(newNode->code,"%slw\t$t0,%d($sp)\nmtc1\t$t0,$f0\ncvt.s.w\t$f0,$f0\ns.s\t$f0,%d($sp)\n",newNode->code,tempNode0->place,tempNode0->place);
				}
				else if (tempNode2->semTypeDef==storeInteger) {  
					tempNode2->realValue = 1.00*tempNode2->intValue ;  
					tempNode2->semTypeDef==storeReal;
					sprintf(newNode->code,"%slw\t$t0,%d($sp)\nmtc1\t$t0,$f0\ncvt.s.w\t$f0,$f0\ns.s\t$f0,%d($sp)\n",newNode->code,tempNode2->place,tempNode2->place);
				}

					newNode->realValue=tempNode0->realValue  *  tempNode2->realValue;
					sprintf(newNode->code,"%sl.s\t$f0,%d($sp)\nl.s\t$f1,%d($sp)\nmul.s\t$f0,$f0,$f1\ns.s\t$f0,%d($sp)\n",newNode->code,tempNode0->place,tempNode2->place,tempNode0->place);
			}
			else {  
				newNode->semTypeDef = storeInteger ;  
				newNode->intValue = tempNode0->intValue*tempNode2->intValue ;
				//newNode->place=getNewTemp;
				sprintf(newNode->code,"%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nmult\t$t0,$t1\nmflo\t$t0\nsw\t$t0,%d($sp)\n",newNode->code,tempNode0->place,tempNode2->place,tempNode0->place);
			}
			newNode->place=tempNode0->place;
			$$ = newNode;
		}
		|
		term TOKEN_DIVIDE factor
		{
		
			Node *newNode = createNode();			//check declaration here...
			Node* tempNode0 = (Node*)$1;
			Node* tempNode1 = (Node*)$2;
			Node* tempNode2 = (Node*)$3;
			sprintf(newNode->code,"%s%s",tempNode0->code,tempNode2->code);
			if (tempNode0->semTypeDef==storeReal  || tempNode2->semTypeDef==storeReal) {  
				newNode->semTypeDef = storeReal ;  
				if (tempNode0->semTypeDef==storeInteger){
					tempNode0->realValue = 1.00*tempNode0->intValue ;  
					tempNode0->semTypeDef==storeReal;
					sprintf(newNode->code,"%slw\t$t0,%d($sp)\nmtc1\t$t0,$f0\ncvt.s.w\t$f0,$f0\ns.s\t$f0,%d($sp)\n",newNode->code,tempNode0->place,tempNode0->place);
				}
				else if (tempNode2->semTypeDef==storeInteger) {
					tempNode2->realValue = 1.00*tempNode2->intValue;
					tempNode2->semTypeDef==storeReal;
					sprintf(newNode->code,"%slw\t$t0,%d($sp)\nmtc1\t$t0,$f0\ncvt.s.w\t$f0,$f0\ns.s\t$f0,%d($sp)\n",newNode->code,tempNode2->place,tempNode2->place);
				}

				if (tempNode2->realValue==0.00){
					exit(0);
				}
				else {
					newNode->realValue=tempNode0->realValue/tempNode2->realValue;
					sprintf(newNode->code,"%sl.s\t$f0,%d($sp)\nl.s\t$f1,%d($sp)\ndiv.s\t$f1,$f0,$f1\ns.s\t$f1,%d($sp)\n",newNode->code, tempNode0->place, tempNode2->place, tempNode0->place);
					newNode->place = tempNode0->place;
				}
			}
			else {  
				newNode->semTypeDef = storeInteger;
				if (tempNode2->intValue==0){
							exit(0);
				}
				else {
					newNode->intValue = tempNode0->intValue/tempNode2->intValue;
					//newNode->place=getNewTemp();
					sprintf(newNode->code,"%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\ndiv\t$t0,$t1\nmflo\t$t1\nsw\t$t1,%d($sp)\n",newNode->code, tempNode0->place, tempNode2->place, tempNode0->place);
					newNode->place=tempNode0->place;
				}
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
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef ; 
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code); 
		//printf("factor->primary, intval = %d\n",newNode->intValue);
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
	/*| ////check////
	procedureStatement
	{
		Node *newNode = createNode();
		Node* tempNode = (Node*)$1;
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place = tempNode->place;
		strcpy(newNode->code,tempNode->code);
		$$ = newNode;
	}*/;

primary :
	unsignedNumber
	{
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = $1;
		Node *tempNode = (Node*)$1;
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		$$ = newNode;
		printf("primary->unsignedNumber");	
	
	}
	|	
	functionDesignator{
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = $1;
		Node *tempNode = (Node*)$1;
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		$$ = newNode;
		printf("primary->unsignedNumber");
	}
	|
	variable
	{
		Node *newNode = createNode();
		newNode->type = primary;
		newNode->pt0 = $1;
		Node *tempNode = (Node*)$1;
		//printf("primary->variable, int value=%d\n",newNode->intValue);
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
			if(foundEntry->type==storeReal){
				sprintf(newNode->code,"%sl.s\t$f0,%d($sp)\ns.s\t$f0,%d($sp)\n",tempNode->code,offset,newNode->place);	
			}
			else{
				sprintf(newNode->code,"%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",tempNode->code,offset,newNode->place);	
			}
		}
		else
			printf("error belu\n");		
		$$ = newNode;

		
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
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		$$ = newNode;
	};

unsignedNumber :
	realNumber
	{
		Node *newNode = createNode();
		newNode->type = unsignedNumber;
		newNode->pt0 = $1;
		Node *tempNode = (Node*)$1;
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=storeReal;
		newNode->place=getNewTemp();
		sprintf(newNode->code,"li.s\t$f0,%f\ns.s\t$f0,%d($sp)\n",newNode->realValue,newNode->place);
		$$ = newNode;
		//printf("unsignedNumber->real, realval = %f\n",newNode->realValue);	
	}
	|
	integer
	{	
		Node *newNode = createNode();
		newNode->type = unsignedNumber;
		newNode->pt0 = $1;
		Node *tempNode = (Node*)$1;
		newNode->intValue = tempNode->intValue;
		newNode->realValue = tempNode->realValue;
		newNode->semTypeDef=storeInteger;
		newNode->place=getNewTemp();
		sprintf(newNode->code,"li\t$t0,%d\nsw\t$t0,%d($sp)\n",newNode->intValue,newNode->place);
		$$ = newNode;
		//printf("unsignedNumber->integer, intval = %d\n",newNode->intValue);
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
		printf("integer-> TOKEN_INTEGER %d\n",newNode->intValue);
		newNode->semTypeDef=storeInteger;  
		$$ = newNode;
	};

simpleVariable :
	varIdentifier
	{	
		Node *new = createNode();		
		new->type = simpleVariable;
		new->pt0 = $1;
		Node* temp = (Node*)$1;			
		new->realValue=temp->realValue;		
		new->intValue=temp->intValue;
		new->boolValue=temp->boolValue;
		new->semTypeDef=temp->semTypeDef;
		strcpy(new->identLex, temp->identLex);
		new->place=temp->place;
		strcpy(new->code,temp->code);
		printf("simplevariable->varIdentifier");			
		$$ = new;
	};

variable : 
	simpleVariable
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
		newNode->place=tempNode->place;
		strcpy(newNode->code,tempNode->code);
		$$ = newNode;
	}
	|
	subscriptedVariable
	{
		Node *newNode = createNode();
		newNode->isArray = 1;
		newNode->type = variable;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		newNode->boolValue = tempNode->boolValue;
		newNode->intValue = tempNode->intValue;
		newNode->realValue=tempNode->realValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place = tempNode->place;
		strcpy(newNode->code,tempNode->code);
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
				int i;

				int offset = foundEntry->offset - (tempNode1->lowerBound[tempNode1->dim-1]-foundEntry->lowerBound[tempNode1->dim-1])*4;
				for(i=foundEntry->dim-1;i>0;i--){
					if(tempNode1->lowerBound[i-1] <= foundEntry->upperBound[i-1] && tempNode1->lowerBound[i-1] >= foundEntry->lowerBound[i-1]){
						offset-=(foundEntry->upperBound[i]-foundEntry->lowerBound[i])*4*(tempNode1->lowerBound[i-1]-foundEntry->lowerBound[i-1]);
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
		$$ = newNode;
	}
	;

subscriptList:
	subscriptExpression
	{
		Node* newNode = createNode();
		newNode->type = subscriptList;
		Node* tempNode = $1;
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->pt0 = $1;
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
		newNode->semTypeDef = tempNode2->semTypeDef;
		sprintf(newNode->code,"%s%s",tempNode1->code,tempNode2->code);
		if(tempNode2->semTypeDef == storeInteger){
			newNode->semTypeDef = tempNode2->semTypeDef;
			int i;
			for(i=tempNode1->dim-1;i>=0;i--){
				newNode->lowerBound[i] = tempNode1->lowerBound[i];
			}
			newNode->dim = tempNode1->dim+1;
			newNode->lowerBound[newNode->dim-1] = tempNode2->intValue;
		}
		else {
			newNode->semTypeDef = storeError;
		}
		$$ = newNode;
	};

subscriptExpression :
	arithmeticExpression
	{
		Node* newNode = createNode();
		newNode->type = subscriptExpression;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->intValue = tempNode->intValue;
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		$$ = newNode;
		printf("subscriptedExpression->arithmeticExpression\n");
	};

identifier :
	TOKEN_IDENTIFIER
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
		$$ = newNode;
	};

booleanExpression :
	simpleBoolean
	{
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		if(tempNode->semTypeDef == storeBoolean){
			newNode->semTypeDef = tempNode->semTypeDef;
		}
		else{
			newNode->semTypeDef = storeError;
		}
		$$ = newNode;
		printf("booleanExpression->simpleBoolean\n");
	}
	/*|   ////check////
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
	}*/;

simpleBoolean:
	implication
	{
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		newNode->boolValue = tempNode->boolValue;
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		$$ = newNode;
		printf("simpleBoolean->implication\n");
	}
	|
	simpleBoolean TOKEN_EQUIV implication
	{
		Node* newNode = createNode();
		newNode->type = booleanExpression;
		newNode->pt0 = $1;
		newNode->pt2 = $3;
		Node* tempNode1 = $1;
		Node* tempNode2 = $3;
		int label1 = getNewLabel;
		int label2 = getNewLabel;
		sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nbeq\t$t0,$t1,label%d\nli\t$t2,0\nb\tlabel%d\nlabel%d:\nli\t$t2,1\nlabel%d:\nsw\t$t2,%d($sp)\n",tempNode1->code,tempNode2->code,tempNode1->place,tempNode2->place,label1,label2,label1,label2,tempNode1->place);
		newNode->place = tempNode1->place;

		$$ = newNode;
		printf("simpleBoolean->simple = implication\n");
	};

implication : 
	booleanTerm
	{
		Node *newNode = createNode();
		newNode->type = implication;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		$$ = newNode;  
		printf("implication->booleanterm\n");
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
		int label1=getNewLabel();
		int label2=getNewLabel();
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
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
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
		sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nor\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",tempNode1->code,tempNode2->code,tempNode1->place,tempNode2->place, tempNode1->place);
		newNode->place = tempNode1->place;
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
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
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
		sprintf(newNode->code,"%s%slw\t$t0,%d($sp)\nlw\t$t1,%d($sp)\nand\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",tempNode1->code,tempNode2->code,tempNode1->place,tempNode2->place, tempNode1->place);
		newNode->place = tempNode1->place;
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
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		$$ = newNode;
	}
	|
	TOKEN_NOT_OP booleanPrimary
	{
		Node *newNode = createNode();
		newNode->type = booleanSecondary;
		newNode->pt1 = $2;
		Node* tempNode = $2;
		newNode->place = getNewTemp();
		sprintf(newNode->code,"%sli\t$t0,1\nlw\t$t1,%d($sp)\nsub\t$t2,$t0,$t1\nsw\t$t2,%d($sp)\n",tempNode->code,tempNode->place,newNode->place);
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
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		$$ = newNode;
		
	}
	/*|    ////check////
	variable
	{
		Node *newNode = createNode();
		newNode->type = variable;
		newNode->pt0 = $1;
		Node *tempNode=$1;
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* entry = lookUp(tempNode->identLex,currentScope);
		tempNode->semTypeDef = entry->type;
		newNode->semTypeDef = tempNode->semTypeDef;
		$$=newNode;
	}*/
	|
	relation
	{
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = $1;
		Node* tempNode = $1;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		$$=newNode;
	}
	|
	TOKEN_OPEN_BRACKET booleanExpression TOKEN_CLOSE_BRACKET
	{
		Node *newNode = createNode();
		newNode->type = booleanPrimary;
		newNode->pt0 = $2;
		Node* tempNode = $2;  
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place ;  
		strcpy(newNode->code, tempNode->code);
		$$=newNode;
	};

logicalValue:
	TOKEN_LOGICAL_VALUE
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
		$$=newNode;
	};
	        
/*boolVariable : variable    ////check////
	{
		Node* newNode = createNode();
		newNode->type = boolVariable;
		newNode->pt0 = $1;
		Node* tempNode = (Node*)$1;
		newNode->boolValue = tempNode->boolValue;
		newNode->semTypeDef=tempNode->semTypeDef;
		strcpy(newNode->identLex, tempNode->identLex);
		$$ = newNode;
		printf("Boolvariable->simpleVariable\n");
	}; //{printf("Variable Parsed \n");}
/*
boolSimpleVariable :
	TOKEN_BOOL_IDENTIFIER
	{
		Node *newNode = createNode();
		newNode->type = boolSimpleVariable;
		strcpy(newNode->identLex, yytext);
		$$ = newNode;
	} {////printf("Identifier parsed\n");}
	;
*/
relationalOperator :
	TOKEN_REL_OP			//check important
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
			$$=$0;
		}
	}
	|
	listType TOKEN_COMMA varIdentifier ////check////
	{
		Node *temp2=$0;
		Node *temp0=$1;
		Node *temp1=$3;
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
		$$=$0;	
	}
	;


type :
	TOKEN_TYPE_REAL
	{
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef = storeReal;
		printf("Token_real\n");		
		$$ = new;

	}
	|
	TOKEN_TYPE_INTEGER
	{
		Node *new = createNode();         	
        	new->type = type;
        	new->semTypeDef=storeInteger;
		printf("Token_integer\n");
		$$ = new;	

	}

	|
	TOKEN_TYPE_BOOLEAN
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
	printf("typeDeclaration\n");
	//$$=$2;
	}
	;

varIdentifier :
	identifier
	{
		Node *new = createNode();		
		new->type = varIdentifier;
		new->pt0 = $1;
		Node* temp = (Node*)$1;			
		new->realValue=temp->realValue;		
		new->intValue=temp->intValue;
		new->boolValue=temp->boolValue;
		new->semTypeDef = temp->semTypeDef;
		strcpy(new->identLex, temp->identLex);
		new->place=temp->place;
		strcpy(new->code,temp->code);
		printf("varIdentifier");			
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
		strcpy(new->code,temp1->code);
		$$ = new;
		printf("unconditional -> basic\n");
	}
	|
        compoundStatement {

		Node *new = createNode();         	
        	new->type = unconditionalStatement;
        	new->pt0 = $1;
		Node *temp1 = $1;
		new->semTypeDef=temp1->semTypeDef;
		strcpy(new->code,temp1->code);
		$$ = new;
	}
	|
	block {

		Node *new = createNode();
        	new->type = unconditionalStatement;
        	new->pt0 = $1;
		Node *temp1 = $1;
		new->semTypeDef=temp1->semTypeDef;
		strcpy(new->code,temp1->code);
		$$ = new;
	}
	;

conditionalStatement :
	ifStatement
	{
		Node *newNode = createNode();         	
        	newNode->type = conditionalStatement;
        	newNode->pt0 = $1;
		Node *tempNode = $1;
		newNode->semTypeDef=tempNode->semTypeDef;
		newNode->place=tempNode->place;
		sprintf(newNode->code,"%slabel%d:\n",tempNode->code,tempNode->intValue);
		$$ = newNode;
		printf("conditionalStatement -> ifStatement\n");
	}
	|
        ifStatement TOKEN_ELSE statement	{
		Node *newNode = createNode();         	
        	newNode->type = conditionalStatement;
        	newNode->pt0 = $1 ;  
		newNode->pt2 = $3 ;  
		Node *tempNode1 = $1 ;  
		Node *tempNode2 = $3 ;
		int label=getNewLabel();
		//int label2=getNewLabel();
		sprintf(newNode->code,"%sb\tlabel%d\nlabel%d:\n%slabel%d:\n",tempNode1->code,label,tempNode1->intValue,tempNode2->code,label);
		if (tempNode1->semTypeDef==storeVoid && tempNode2->semTypeDef==storeVoid ) {  
			newNode->semTypeDef=storeVoid ;  
		}
		printf("conditionalStatement -> ifstatement ELSE statement\n");
		$$ = newNode;
	}
	|
        ifClause forStatement
	{
		Node *newNode = createNode();         	
		newNode->type = conditionalStatement;
		newNode->pt0 = $1 ;  
		newNode->pt1 = $2 ;  
		Node *tempNode1=$1;
		Node *tempNode2=$2;
		int label = getNewLabel();
		if (tempNode1->semTypeDef==storeBoolean && tempNode2->semTypeDef==storeVoid ) {  
			newNode->semTypeDef==storeVoid ;  
			sprintf(newNode->code,"%sli\t$t0,0\nlw\t$t1,%d($sp)\nbeq\t$t1,$t0,label%d\n%slabel%d:\n",tempNode1->code,tempNode1->place,label,tempNode2->code,label) ;
		}
		else{
			newNode->semTypeDef==storeError ;
		}
		
		$$=newNode;
	}
	|
	tlabel /*TOKEN_COLON*/ conditionalStatement////check////
	{
		Node* newNode = createNode();
		Node* tempNode1 = $1;
		Node* tempNode2 = $2;
		//sprintf(newNode->code,"%s:\n%s\n",tempNode1->identLex,tempNode2->code);
		int label = getNewLabel();
		sprintf(newNode->code,"b\tlabel%d\n%s:\n%slabel%d:\n",label,tempNode1->identLex,tempNode2->code,label);
		$$=newNode;	
	}		
	;

ifStatement :
	ifClause unconditionalStatement 
	{
		Node *newNode = createNode();         	
        	newNode->type = ifStatement;
        	newNode->pt0 = $1;
		newNode->pt1 = $2;
		Node *tempNode1 = $1;
		Node *tempNode2 = $2;
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
		
		$$ = newNode;
		printf("ifStatement -> ifClause unconditionalStatement\n");
	}
	;

ifClause :
	TOKEN_IF booleanExpression TOKEN_THEN
	{
		Node *newNode = createNode();
        	newNode->type = ifClause;
        	newNode->pt1 = $2;
                Node* tempNode = (Node*)$2;
		newNode->place = tempNode->place ;
		strcpy(newNode->code,tempNode->code);
		if (tempNode->semTypeDef==storeBoolean) {  
			newNode->semTypeDef=storeBoolean ;  
		}
		else {  
			newNode->semTypeDef=storeError ;  
		}
		printf("ifClause -> IF booleanExpression THEN\n");
		$$ = newNode;  
	}
	;


basicStatement :
	unlabelledBasicStatement {

		Node *new = createNode();         	
        	new->type = basicStatement;
        	new->pt0 = $1 ;  
		Node *temp = $1 ;  
		new->semTypeDef=temp->semTypeDef ;
		strcpy(new->code,temp->code);  
		printf("basic -> unlabbasic\n");
		$$ = new;

	}
	|
        tlabel basicStatement ////check////
	{
		Node* newNode = createNode();
		Node* tempNode1 = $1;
		Node* tempNode2 = $2;
		int label = getNewLabel();
		sprintf(newNode->code,"b\tlabel%d\n%s:\n%slabel%d:\n",label,tempNode1->identLex,tempNode2->code,label);
		$$=newNode;	
	}
	;

unlabelledBasicStatement :
	assignmentStatement
	{		
		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement; 
        	new->pt0 = $1 ; 
		Node *temp = $1 ;  
		new->semTypeDef=temp->semTypeDef ;
		strcpy(new->code,temp->code);
		$$ = new;
	}
	| ////check//////
	dummyStatement
	{

		Node *new = createNode();         	
        	new->type = unlabelledBasicStatement;
        	new->pt0 = $1 ;  
		Node *temp = $1 ;  
		strcpy(new->code,"");
		new->semTypeDef=temp->semTypeDef ;  
		printf("unlabelledstatement->dummystatement\n");
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
		strcpy(new->code,temp->code);
		$$ = new;
		printf("unlabelledbasicstmt -> procstmt\n");

	}
	|
	returnStatement
	{
		Node* newNode = createNode();
		Node *tempNode = $1;
		strcpy(newNode->code,tempNode->code);
		$$ = $1;
	}
	|
	gotoStatement
	{
		Node* newNode = createNode();
		Node* tempNode = $1;
		strcpy(newNode->code,tempNode->code);
	}
	;
dummyStatement :	///check////
	empty
	;
	
returnStatement :
	TOKEN_RETURN expression
	{
		Node *newNode = createNode();
                newNode->type = returnStatement;
		Node *tempNode = $2 ;
		sprintf(newNode->code,"%slw\t$v0,%d($sp)\njr\t$ra\n",tempNode->code,tempNode->place);
		if(tempNode->semTypeDef==storeError)
		{
			newNode->semTypeDef=storeError;
		}
		else
		{
			newNode->semTypeDef = tempNode->semTypeDef;
		}
		$$ = newNode;
	};

assignmentStatement :
	variable TOKEN_ASSIGN arithmeticExpression  
	{
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = $1;
		new->pt2 = $3;
		Symbol *symbol1;	
		Node *tmp1=$1;
		Node *tmp2=$3;
		new->semTypeDef=storeVoid;
		currentScope = scopeStack[scopeStackTop-1];	
  		symbol1=lookUp(tmp1->identLex, currentScope);
		printf("################### scope parent = %d,current scope=%d and sybol lexeme =  #####################\n",symbolTable[currentScope].parent,currentScope);
		printf("################### symbol lexeme = %s #####################\n",symbol1->lexeme);	
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
				//printf("assignmentStatement->identifier:= arithmeticexpression, realValue= %f,,%f\n",tmp2->realValue,symbol1->realValue);
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
				sprintf(new->code,"%s%slw\t$t0,%d($sp)\nmtc1\t$t0,$f0\ncvt.s.w\t$f0,$f0\ns.s\t$f0,%d($sp)\n",tmp1->code,tmp2->code,tmp2->place,offset);
				
			}
			else{	
				printf("inconsistent Types in assignment\n");
				new->semTypeDef = storeError;
			}
		}
		$$ = new;
	}
	|
	variable TOKEN_ASSIGN booleanExpression
	{
		Node *new = createNode();         	
        	new->type = assignmentStatement;
        	new->pt0 = $1;
		new->pt2 = $3;
		
	
		Node *temp1=$1;
		Node *temp2=$3;
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
		$$ = new;
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
	TOKEN_FOR variable TOKEN_ASSIGN arithmeticExpression TOKEN_STEP arithmeticExpression TOKEN_UNTIL arithmeticExpression TOKEN_DO statement
	{  
		Node *new = createNode();
		Node *temp = $2;
		Node *temp2 = $4;
		Node *temp3 = $6;
		Node *temp4 = $8;
		Node *temp5 = $10;
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
			$$ = new;
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
			$$=new;
		}
	}
	;

empty :	
	{	
		printf("empty reached\n");
		Node *new = createNode();         	            	  
        new->type =empty;
		$$ = new;
	}
	;
procedureStatement :
	procedureIdentifier actualParameterPart {
		Node *new = createNode();
		Node *temp1 = $1;
		Node *temp2 = $2;
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
		strcpy(new->identLex,temp->identLex);
		$$ = new;
	}
	;
actualParameterPart :
	TOKEN_OPEN_BRACKET TOKEN_CLOSE_BRACKET
	| TOKEN_OPEN_BRACKET actualParameterList TOKEN_CLOSE_BRACKET
	{

		Node *temp = $2;
		if(temp->semTypeDef != storeError)
		{		
			temp->semTypeDef == storeVoid;
		}
		printf("actparampart -> ( act param list )\n");
		$$=$2;
	}
	;

actualParameterList :
	actualParameter
	{
		Node *temp = $-1;
		Node *temp1 = $1;
		currentScope = scopeStack[scopeStackTop-1];
		Symbol* symbol= lookUp(temp1->identLex,currentScope);
		Node *new = createNode();
		new->dim = 0;
		sprintf(new->code,"%slw\t$t0,%d($sp)\nsw\t$t0,%d($sp)\n",temp1->code,temp1->place,-100-4* new->dim);
		new->semTypeDef = storeVoid;
		
		$$ = new;
		printf("actual parameter list -> actual parameter\n");
	}
	|
        actualParameterList parameterDelimiter actualParameter  
	{
		Node *temp = $-1;
		Node *temp3 = $1;
		Node *temp1 = $3;
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
		$$ = new;

	}
	;

actualParameter :
	expression
	{
		Node *newNode = createNode(); 
		Node *tempNode = $1; 
		newNode->type = actualParameter;
		newNode->semTypeDef = tempNode->semTypeDef;
		newNode->pt0 = $1;
		newNode->place = tempNode->place;
		strcpy(newNode->code, tempNode->code);
		printf("actual parameter -> expression\n");
		$$ = newNode;
	}
	;

parameterDelimiter : TOKEN_COMMA
	| TOKEN_CLOSE_BRACKET identifier TOKEN_COLON TOKEN_OPEN_BRACKET;

functionDesignator :
	procedureIdentifier actualParameterPart
	{
		Node *new = createNode();
		Node *temp1 = $1;
		Node *temp2 = $2;
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

		$$ = new; 
		

	}
	;

statement :
	unconditionalStatement
	{
		Node* newNode=createNode();
		Node *tempNode=$1;
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		$$=newNode;
		printf("stmt -> unconditionalstmt\n");
	}
	|
        conditionalStatement
	{
		Node* newNode=createNode();
		Node *tempNode=$1;
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		$$=newNode;

	}
	|
	forStatement
	{	Node* newNode=createNode();
		Node *tempNode=$1;
		newNode->semTypeDef = tempNode->semTypeDef;
		strcpy(newNode->code,tempNode->code);
		$$=newNode;
	}
	|
	TOKEN_PRINT expression
	{
		Node* newNode=createNode();
		Node* tempNode=$2;
		newNode->semTypeDef = tempNode->semTypeDef;
		if(newNode->semTypeDef==storeReal){
			sprintf(newNode->code,"%sli\t$v0,4\nla\t$a0, MSG\nsyscall\nl.s\t$f10,%d($sp)\nmov.s\t$f12,$f10\nli\t$v0,2\nsyscall\n",tempNode->code,tempNode->place);
		}
		else{
			sprintf(newNode->code,"%sli\t$v0,4\nla\t$a0, MSG\nsyscall\nlw\t$t0,%d($sp)\nli\t$v0,1\nmove\t$a0,$t0\nsyscall\n",tempNode->code,tempNode->place);
		}
		$$=newNode;
	}
/*	|
	dummyStatement
	{
		Node* newNode=createNode();
		$$=newNode;
	}*/
	;


formalParameter :
	identifier
	{
		$0=$-1;
		Node *node0 = $0;
		Node *node1 = $1;
		
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
		$$ = $0;
		paramBelu++;
	};
	
formalParameterList :
	formalParameter
	| formalParameterList parameterDelimiter formalParameter{   ////check/////
		$1=$0;
		$2=$0;
		printf("formalParmeterlist->formalParmeter\n");	
	}
	;

formalParameterPart :
	empty {
		$$ = $0;
	}
	| TOKEN_OPEN_BRACKET {
		$1 = $0;
	} formalParameterList TOKEN_CLOSE_BRACKET{
		printf("formalParmeterpart->(formalParmeterlist)\n");
	};

identifierList :
	identifier {
		Node *node1 = $0;
		Node *node2 = $1;
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
		$$ = node1;
		
	}

	| identifierList TOKEN_COMMA identifier{
		Node *node1 = $1;
		Node *node2 = $3;
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
		$$ = node1;

	};

valuePart :  TOKEN_VALUE identifierList TOKEN_SEMICOLON{
		$3 = $0;
	}
	| empty;
specifier :
	type{
		printf("specifier->type\n"); 
	}
	| type TOKEN_ARRAY
	| TOKEN_TYPE_LABEL 
	| TOKEN_SWITCH 
	| type TOKEN_PROCEDURE;

specificationPart : empty
	| specificationIdentifierList;

specificationIdentifierList : specifier identifierList TOKEN_SEMICOLON{
		Node *node1 = $1;
		printf("specificationidentlist->specifier identlist ;\n");

	}
	| specificationIdentifierList specifier identifierList TOKEN_SEMICOLON
	{
		printf("specificationidentlist->specificationidentlist specifier identlist ;\n");

	};

procedureHeading :
	procedureIdentifier {
		Node *node = createNode();
		node->type = procedureHeading;
		node->pt0 = $1;
		Node *node1 = $1;
		node1->parent = node;
		strcpy(node->identLex, node1->identLex);
		currentScope = scopeStack[scopeStackTop-1];
		if (lookUpInCurrentScope(node1->identLex) == NULL){
			Symbol * entry = addEntry(node1->identLex);
			entry->procNumParam = 0;
		}
		$$ = node;
	} formalParameterPart TOKEN_SEMICOLON {
		printf("the belu number of parameters defined is %d\n",paramBelu);
		$3 = $1;
	} valuePart specificationPart{
		printf("the belu number of parameters defined is %d\n",paramBelu);
	}
	;

procedureBody :
	statement{//changed 16th april

		Node *new = createNode();
		new->type = procedureBody;
		Node *temp = $1;
		new->semTypeDef = temp->semTypeDef;
		strcpy(new->code,temp->code);
		$$ = new;
		printf("proc body -> stmt\n");
	};

procedureDeclaration : 
	TOKEN_PROCEDURE procedureHeading procedureBody {
		Node *node1 = $2;
		Node *node2 = $3;
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
		$$ = node;
		printf("procedureDeclaration -> procedure heading body");
		if (paramBelu != 0)
			printf("Error. too many or too few specifications\n");
		paramBelu = 0;
	}
	| type TOKEN_PROCEDURE procedureHeading procedureBody
	{
		Node *node1 = $3;
		Node *node2 = $4;
		Node *node3 = $1;
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
		$$ = node;
		printf("proceduredeclaration -> type procedure heading body\n");
		if (paramBelu != 0)
			printf("Error. too many or too few specifications\n");
		paramBelu = 0;
	};

gotoStatement :
	TOKEN_GOTO designationalExpression
	{
		Node* newNode=createNode();
		Node* tempNode = $2;
		sprintf(newNode->code,"b\t%s\n",tempNode->identLex);
		$$=newNode;
	};

switchDeclaration :
	TOKEN_SWITCH switchIdentifier TOKEN_ASSIGN switchList;

switchList :
	designationalExpression
	| switchList TOKEN_COMMA designationalExpression
	;

switchIdentifier :
	identifier{
		Node *newNode = createNode();
		newNode->type= switchIdentifier;
		newNode->pt0=$1;
		Node* tempNode = $1;
		strcpy(newNode->identLex,tempNode->identLex);

		$$=newNode;
		printf("switchIdent->Identifier\n");
	}
	;

designationalExpression :
	simpleDesignationalExpression
	{
		Node* newNode=createNode();
		Node* tempNode = $1;
		strcpy(newNode->identLex,tempNode->identLex);
		$$=newNode;
	}
	| ifClause simpleDesignationalExpression TOKEN_ELSE designationalExpression;

simpleDesignationalExpression : 
	tlabel
	{
		Node* newNode=createNode();
		Node* tempNode = $1;
		strcpy(newNode->identLex,tempNode->identLex);
		$$=newNode;
	}
	| switchDesignator
	| TOKEN_OPEN_BRACKET designationalExpression TOKEN_CLOSE_BRACKET;

switchDesignator :
	switchIdentifier TOKEN_OPEN_CURLY_BRACKET subscriptExpression TOKEN_CLOSE_CURLY_BRACKET ;

%%
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
	//check while merging the codes
	char * code1[99999];
	strcpy(code1,"b\tmain\n");
	strcat(code1,code);
	strcat(code1,"jr\t$ra");
	strcat(code1,"\n\n\t.data\nMSG:\t.asciiz \"\\n OUTPUT = \"");
	//printf("%s",code);
	FILE* fp1 = fopen("code1.asm","w");
	fprintf(fp1,"%s",code1);
	return 0;
}

