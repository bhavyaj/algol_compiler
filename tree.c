#include "tree.h"

Node* createNode(){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->parent = NULL;
	newNode->pt0 = NULL;
	newNode->pt1 = NULL;
	newNode->pt2 = NULL;
	newNode->pt3 = NULL; 
	newNode->identLex = (char*)malloc(15*sizeof(char));
	return newNode;	
}
