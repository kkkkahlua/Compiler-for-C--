%{
#include "tree.h"
#define YYSTYPE TreeNode*

#include "syntax.tab.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

extern TreeNode* yylval;
int error_lex = 0;

void CheckNumber(int base);
void IgnoreBlockComment();
void IgnoreLineComment();
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
regular_float			{dec_digit}+{dot}{dec_digit}*|{dot}{dec_digit}+
base					{regular_float}
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
comment_line            "//"
comment_block_begin     "/*"
comment_block_end       "*/"
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
{oct_number}			{   CheckNumber(8); return INT; }
{dec_number}			{	CheckNumber(10); return INT; }
{hex_number}			{	CheckNumber(16); return INT; }
{FLOAT}					{	CheckNumber(0); return FLOAT; }
{comment_block_begin}   {   IgnoreBlockComment(); }
{SEMI}					{	yylval = NewSymbolTreeNode("SEMI"); return SEMI; }
{COMMA}					{	yylval = NewSymbolTreeNode("COMMA"); return COMMA; }
{ge}					{	yylval = NewRelopTreeNode(kGE); return RELOP; }
{gt}					{	yylval = NewRelopTreeNode(kGT); return RELOP; }
{le}					{	yylval = NewRelopTreeNode(kLE); return RELOP; }
{lt}					{	yylval = NewRelopTreeNode(kLT); return RELOP; }
{eq}					{	yylval = NewRelopTreeNode(kEQ); return RELOP; }
{ne}					{	yylval = NewRelopTreeNode(kNE); return RELOP; }
{ASSIGNOP}				{	yylval = NewSymbolTreeNode("ASSIGNOP"); return ASSIGNOP; }
{PLUS}					{	yylval = NewSymbolTreeNode("PLUS"); return PLUS; }
{MINUS}					{	yylval = NewSymbolTreeNode("MINUS"); return MINUS; }
{STAR}					{	yylval = NewSymbolTreeNode("STAR"); return STAR; }
{comment_line}          {   IgnoreLineComment(); }
{DIV}					{	yylval = NewSymbolTreeNode("DIV"); return DIV; }
{AND}					{	yylval = NewSymbolTreeNode("AND"); return AND; }
{OR}					{	yylval = NewSymbolTreeNode("OR"); return OR; }
{DOT}					{	yylval = NewSymbolTreeNode("DOT"); return DOT; }
{NOT}					{	yylval = NewSymbolTreeNode("NOT"); return NOT; }
{int}					{	yylval = NewTypeTreeNode("int"); return TYPE; }
{float}					{	yylval = NewTypeTreeNode("float"); return TYPE; }
{LP}					{	yylval = NewSymbolTreeNode("LP"); return LP; }
{RP}					{	yylval = NewSymbolTreeNode("RP"); return RP; }
{LB}					{	yylval = NewSymbolTreeNode("LB"); return LB; }
{RB}					{	yylval = NewSymbolTreeNode("RB"); return RB; }
{LC}					{	yylval = NewSymbolTreeNode("LC"); return LC; }
{RC}					{	yylval = NewSymbolTreeNode("RC"); return RC; }
{STRUCT}				{	yylval = NewSymbolTreeNode("STRUCT"); return STRUCT; }
{RETURN}				{	yylval = NewSymbolTreeNode("RETURN"); return RETURN; }
{IF}					{	yylval = NewSymbolTreeNode("IF"); return IF; }
{ELSE}					{	yylval = NewSymbolTreeNode("ELSE"); return ELSE; }
{WHILE}					{	yylval = NewSymbolTreeNode("WHILE"); return WHILE; }
{ID}					{	yylval = NewIDTreeNode(yytext); return ID; }
.						{	printf("Error type A at Line %d: Mysterious characters \'%s\'.\n", yylineno, yytext); error_lex = 1; }
%%

void IgnoreBlockComment() {
    char c1 = input(), c2;
    int cnt = 0;
    while (1) {
        while (c1 != '\0' && c1 != '*') c1 = input();
        if (c1 == '\0') {
            printf("Error type B at Line %d: syntax error, unclosed comment.\n", yylineno);
            break;
        }
        c2 = input();
        if (c2 == '/') break;
        c1 = c2;
    }
}

void IgnoreLineComment() {
    char c = input();
    while (c != '\n') c = input();
}

void ReadAll(char* text, char c, int base) {
    while (isalnum(c) || c == '_' || c == '.') {
        *text++ = c;
        c = input();
    }
    unput(c);
    *text++ = '\0';
}

void OutputErrorMsg(const char* type, const char* content) {
    printf("Error type A at Line %d: Illegal %s number '%s'.\n", yylineno, type, content);
}

int CheckIllegalFloat(char c) {
    if (c == '.' || c == 'e' || c == 'E') return 1;
    if (isalpha(c) || c == '_') return 1;
    return 0;
}

int CheckIllegalOct(char c) {
    return ('8' <= c && c <= '9') || isalpha(c) || c == '_';
}

int CheckIllegalDec(char c) {
    return isalpha(c) || c == '_';
}

int CheckIllegalHex(char c) {
    return ('g' <= c && c <= 'z') || ('G' <= c && c <= 'Z') || c == '_' || c == '.';
}

void CheckNumber(int base) {
    int len_valid = strlen(yytext);

    int error_int = 0;
    char c = input();
    switch (base) {
        case 0: error_int = CheckIllegalFloat(c); break;
        case 8: error_int = CheckIllegalOct(c); break;
        case 10: {
            if (len_valid == 1 && yytext[0] == '0') { base = 8; error_int = CheckIllegalOct(c); }
            else if (c == '.' || c == 'e' || c == 'E') { base = 0; error_int = CheckIllegalFloat(c); }
            else error_int = CheckIllegalDec(c);
            break;
        }
        case 16: error_int = CheckIllegalHex(c); break;
    }

    if (error_int == 1) {
        error_lex = 1;
        ReadAll(yytext+len_valid, c, base);
        OutputErrorMsg(base == 0 ? "floating point" :
                        (base == 8 ? "octal" : 
                            (base == 10 ? "decimal" : "hexadecimal")),
                       yytext);
        yylval = NewNumberTreeNode("0", base);
        return;
    }
    unput(c);
    yytext[len_valid] = '\0';

    if (len_valid == 1 && yytext[0] == '0') base = 10;
    yylval = NewNumberTreeNode(yytext, base);
}
