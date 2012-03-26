
#include <stdio.h>
#include <ctype.h>
#include <string.h>
extern int yylex();

int main(int argc, char** argv)
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
}
