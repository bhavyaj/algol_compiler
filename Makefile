LEX = lex
YACC = yacc
CC = gcc
algol: y.tab.o lex.yy.o 
	$(CC) -o algol y.tab.o lex.yy.o -ly -lfl
y.tab.c y.tab.h: parser.y
	$(YACC) -d parser.y
y.tab.o: y.tab.c
	$(CC) -c y.tab.c
lex.yy.o: y.tab.h lex.yy.c
	$(CC) -c lex.yy.c
lex.yy.c: lexer.l
	$(LEX) lexer.l
clean:
	rm *.o
	rm *.c


