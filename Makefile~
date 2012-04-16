LEX = lex
YACC = yacc
CC = gcc
algol: y.tab.o lex.yy.o 
	$(CC) -w y.tab.o lex.yy.o
y.tab.c y.tab.h: parser.y
	$(YACC) -v -d parser.y
y.tab.o: y.tab.c
	$(CC) -w -c y.tab.c
lex.yy.o: y.tab.h lex.yy.c
	$(CC) -w -c lex.yy.c
lex.yy.c: lexer.l
	$(LEX) -w lexer.l
clean:
	rm *.o

