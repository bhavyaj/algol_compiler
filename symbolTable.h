#include <stdbool.h>
typedef struct{
	char *lexeme;
	int token;
	int value;
	int type;
	bool boolean;
	int track; 
	struct Symbol *next;
}Symbol;
	
typedef struct{
	Symbol *head;
	Symbol *currentSymbol;
	Symbol *tail;
	int parent;
}SymbolTable;
