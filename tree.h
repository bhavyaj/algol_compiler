# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
enum tag{TOKEN_ID,//TOKEN_SEPARATOR,
	lowerBound,
	upperBound,
	boundPair,
	semTypeDef,
	storeInteger,
	storeBoundPairList,
	storeReal,
	storeBoolean,
	storeVoid,
	storeError,
	boundPairList,
	arrayIdentifier,
	expression,
	arithmeticExpression,
	simpleExpression,
	booleanExpression,
	term,
	subscriptExpression,
	label,
	addingOperator,
	multiplyingOperator,
	factor,
	primary,
	realNumber,
	integer,
	variable,
	subscriptedVariable,
	simpleArithmeticExpression,
	subscriptList,
	identifier,
	implication,
	booleanTerm,
	booleanFactor,
	booleanSecondary,
	booleanPrimary,
	logicalValue,
	relation,
	relationalOperator,
	varIdentifier,
	unconditionalStatement,
	conditionalStatement,
	type,
	returnStatement,
	ifStatement,
	ifClause,
	basicStatement,
	unlabelledBasicStatement,
	assignmentStatement,
	empty,
	procedureIdentifier,
	procedureBody,
	procedureDeclaration,
	actualParameter,
	procedureHeading

};
typedef struct{
	enum tag type;
	struct Node* parent;
	int intValue;
	float realValue;
	bool boolValue;
	char *identLex;
	int semTypeDef;
	int track;	// to keep track of dimension in grammar definition
	struct Node* pt0;
	struct Node* pt1;
	struct Node* pt2;
	struct Node* pt3;
}Node;

