%{ 
#include <stdio.h>
%}
%option yylineno 
letter					[a-zA-Z]
zero					0
dec_digit				[0-9]
dec_digit_no_zero		[1-9]
oct_digit				[0-7]
oct_prefix				{zero}
hex_prefix				0[xX]
hex_digit				[0-9a-fA-F]
dec_number				{zero}|{dec_digit_no_zero}{dec_digit}*
hex_number				{hex_prefix}{hex_digit}+
oct_number				{oct_prefix}{oct_digit}+
INT						{dec_number}|{oct_number}|{hex_number}

dot 					\.
regular_float			{dec_digit}+{dot}{dec_digit}+
base					{dec_digit}+{dot}{dec_digit}*|{dot}{dec_digit}+
exponent_sign			[eE]
exponent 				[+-]?{dec_digit}+
scientific_float		{base}{exponent_sign}{exponent}
FLOAT					{regular_float}|{scientific_float}

underscore				_
letters					{letter}|{dec_digit}|{underscore}
ID						{underscore}{letters}*|{letter}{letters}*

SEMI					;
COMMA					,
ASSIGNOP				=
RELOP					>|<|>=|<=|==|!=
PLUS					"+"
MINUS					"-"
STAR					"*"
DIV						"/"
AND						&&
OR						"||"
DOT 					{dot}
NOT						!
TYPE					{int}|{float}
LP						"("
RP 						")"
LB						"["
RB						"]"
LC						"{"
RC						"}"
STRUCT					struct
RETURN					return
IF 						if
ELSE 					else
WHILE 					while
%%
{oct_number}			{	printf("oct: %s -> %d\n", yytext, strtol(yytext, NULL, 8)); }
{dec_number}			{	printf("dec: %s -> %d\n", yytext, strtol(yytext, NULL, 10)); }
{hex_number}			{	printf("hex: %s -> %d\n", yytext, strtol(yytext, NULL, 16)); }
{ID}					{	printf("identifier: %s\n", yytext); }
{PLUS}					{	puts("PLUS_2"); }
{AND}					{	puts("AND"); }
{OR}					{	puts("OR"); }
.						{	printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext); }
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
