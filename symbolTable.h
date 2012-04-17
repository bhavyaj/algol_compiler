#include <stdbool.h>
typedef struct{
	char *lexeme;
	int token;
	int value;
	float realValue;
	int type;
	bool boolean;
	int offset;
	int dim;
	int procNumParam;
	int lowerBound[20];
	int upperBound[20]; 
	struct Symbol *next;
}Symbol;
	
typedef struct{
	Symbol *head;
	Symbol *currentSymbol;
	Symbol *tail;
	int parent;
	int arrayOffset;
	int currentOffset;
	int newTempOffset;
}SymbolTable;
