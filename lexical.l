%{ 
#include "tree.h"
#define YYSTYPE TreeNode*

#include "syntax.tab.h"

#include <stdio.h>

extern TreeNode* yylval;

NodeVal node_val;

// int yycolumn = 1;
// #define YY_USER_ACTION \
// 	yylloc.first_line = yylloc.last_line = yylineno;
// 	yylloc.first_column = yycolumn;
// 	yylloc.last_column = yycolumn + yyleng - 1;
// 	yycolumn += yyleng;
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
ge						>=
gt						>
le 						<=
lt						<
eq						==
ne						!=
RELOP					{ge}|{gt}|{le}|{lt}|{eq}|{ne}
ASSIGNOP				=
PLUS					"+"
MINUS					"-"
STAR					"*"
DIV						"/"
AND						&&
OR						"||"
DOT 					{dot}
NOT						!
int                     int
float                   float
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
blank					[ \n\t]
%%
\n						{   }
{blank}					{	}
{oct_number}			{	yylval = NewNumberTreeNode(yytext, 8, yylineno); return INT; }
{dec_number}			{	yylval = NewNumberTreeNode(yytext, 10, yylineno); return INT; }
{hex_number}			{	yylval = NewNumberTreeNode(yytext, 16, yylineno); return INT; }
{FLOAT}					{	printf("%s\n", yytext); yylval = NewNumberTreeNode(yytext, 0, yylineno); return FLOAT; }
{SEMI}					{	yylval = NewSymbolTreeNode("SEMI", yylineno); return SEMI; }
{COMMA}					{	yylval = NewSymbolTreeNode("COMMA", yylineno); return COMMA; }
{ge}					{	yylval = NewRelopTreeNode(kGE, yylineno); return RELOP; }
{gt}					{	yylval = NewRelopTreeNode(kGT, yylineno); return RELOP; }
{le}					{	yylval = NewRelopTreeNode(kLE, yylineno); return RELOP; }
{lt}					{	yylval = NewRelopTreeNode(kLT, yylineno); return RELOP; }
{eq}					{	yylval = NewRelopTreeNode(kEQ, yylineno); return RELOP; }
{ne}					{	yylval = NewRelopTreeNode(kNE, yylineno); return RELOP; }
{ASSIGNOP}				{	yylval = NewSymbolTreeNode("ASSIGNOP", yylineno); return ASSIGNOP; }
{PLUS}					{	yylval = NewSymbolTreeNode("PLUS", yylineno); return PLUS; }
{MINUS}					{	yylval = NewSymbolTreeNode("MINUS", yylineno); return MINUS; }
{STAR}					{	yylval = NewSymbolTreeNode("STAR", yylineno); return STAR; }
{DIV}					{	yylval = NewSymbolTreeNode("DIV", yylineno); return DIV; }
{AND}					{	yylval = NewSymbolTreeNode("AND", yylineno); return AND; }
{OR}					{	yylval = NewSymbolTreeNode("OR", yylineno); return OR; }
{DOT}					{	yylval = NewSymbolTreeNode("DOT", yylineno); return DOT; }
{NOT}					{	yylval = NewSymbolTreeNode("NOT", yylineno); return NOT; }
{int}					{	yylval = NewTypeTreeNode("int", yylineno); return TYPE; }
{float}					{	yylval = NewTypeTreeNode("float", yylineno); return TYPE; }
{LP}					{	yylval = NewSymbolTreeNode("LP", yylineno); return LP; }
{RP}					{	yylval = NewSymbolTreeNode("RP", yylineno); return RP; }
{LB}					{	yylval = NewSymbolTreeNode("LB", yylineno); return LB; }
{RB}					{	yylval = NewSymbolTreeNode("RB", yylineno); return RB; }
{LC}					{	yylval = NewSymbolTreeNode("LC", yylineno); return LC; }
{RC}					{	yylval = NewSymbolTreeNode("RC", yylineno); return RC; }
{STRUCT}				{	yylval = NewSymbolTreeNode("STRUCT", yylineno); return STRUCT; }
{RETURN}				{	yylval = NewSymbolTreeNode("RETURN", yylineno); return RETURN; }
{IF}					{	yylval = NewSymbolTreeNode("IF", yylineno); return IF; }
{ELSE}					{	yylval = NewSymbolTreeNode("ELSE", yylineno); return ELSE; }
{WHILE}					{	yylval = NewSymbolTreeNode("WHILE", yylineno); return WHILE; }
{ID}					{	yylval = NewIDTreeNode(yytext, yylineno); return ID; }
.						{	printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext); }
%%