%{ 
#include <stdio.h>
%}
%option yylineno
digit [0-9]
letter [_a-zA-Z]
num16 0[xX][0-9a-fA-F]+
num10 0|([1-9]{digit}*)
num8 0[0-7]+
int {decNum}|{octNum}|{hexNum}
sciFloat (({digit}*\.?{digit}+)|({digit}+\.))[eE][\+-]?{digit}+
normalFloat {digit}+\.{digit}+
float {sciFloat}|{normalFloat}
id {letter}({letter}|{digit})*
space [ \t\n]
%%
{int} { puts("yes"); }
{num10} {
	TreeNode *p = newTreeNode("INT");
	p->intValue = atoi(yytext);
	yylval = p;
	return INT;
}
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
	return 0;
}