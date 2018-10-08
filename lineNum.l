%{
	int chars = 0;
	int words = 0;
	int lines = 0;
%}
%option yylineno 
letter	[a-zA-Z]
%%
\n		ECHO;
^.*$	printf("%d\t%s", yylineno, yytext);
%%
int main(int argc, char** argv) {
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			perror(argv[1]);
			return 1;
		}
	}
	puts("yes");
	yylex();
	printf("%8d%8d%8d\n", lines, words, chars);
	return 0;
}
