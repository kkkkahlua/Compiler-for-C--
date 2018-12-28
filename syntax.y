%{
#define YYSTYPE TreeNode*
#define YYERROR_VERBOSE 1

#include "lex.yy.c"
#include "semantic.h"

#include <stdio.h>

extern int error_lex;
extern int yylineno;

char** output_files;
int error_syntax = 0;
int yyerror(const char* msg);
FILE* stream;

TreeNode* root;
%}
%token			SEMI COMMA
%token			LC RC
%token			TYPE
%token 			ID INT FLOAT
%token			RETURN IF WHILE STRUCT
%right			ASSIGNOP
%left			OR
%left			AND
%left			RELOP
%left			PLUS MINUS			//	minus here
%left 			STAR DIV
%right			/*MINUS*/ NOT			//	neg here
%left			LP RP LB RB DOT

%nonassoc		LOWER_THAN_ELSE
%nonassoc		ELSE
%%
//	High-level definitions
Program:	ExtDefList					{ root = CreateInternalTreeNode("Program", 1, $1); }
;
ExtDefList:	ExtDef ExtDefList			{ $$ = CreateInternalTreeNode("ExtDefList", 2, $1, $2); }
	|		/*	empty	*/				{ $$ = CreateInternalTreeNode("ExtDefList", 0); }
;
ExtDef:		Specifier ExtDecList SEMI	{ $$ = CreateInternalTreeNode("ExtDef", 3, $1, $2, $3); }
	|		Specifier SEMI				{ $$ = CreateInternalTreeNode("ExtDef", 2, $1, $2); }
	|		Specifier FunDec CompSt		{ $$ = CreateInternalTreeNode("ExtDef", 3, $1, $2, $3); }
	|		Specifier FunDec SEMI		{ $$ = CreateInternalTreeNode("ExtDef", 3, $1, $2, $3); }
	|		Specifier error SEMI		{ yyerrok; }
	|		error SEMI					{ yyerrok; }
;
ExtDecList:	VarDec						{ $$ = CreateInternalTreeNode("ExtDecList", 1, $1); }
	|		VarDec COMMA ExtDecList		{ $$ = CreateInternalTreeNode("ExtDecList", 3, $1, $2, $3); }
;

//	Specifiers
Specifier:	TYPE						{ $$ = CreateInternalTreeNode("Specifier", 1, $1); }
	|		StructSpecifier				{ $$ = CreateInternalTreeNode("Specifier", 1, $1); }
;
StructSpecifier:	STRUCT OptTag LC DefList RC	{ $$ = CreateInternalTreeNode("StructSpecifier", 5, $1, $2, $3, $4, $5); }
	|				STRUCT OptTag LC error RC	{ yyerrok; }
	|				STRUCT Tag					{ $$ = CreateInternalTreeNode("StructSpecifier", 2, $1, $2); }
;
OptTag:		ID							{ $$ = CreateInternalTreeNode("OptTag", 1, $1); }
	|		/*	empty	*/				{ $$ = CreateInternalTreeNode("OptTag", 0); }
;
Tag:		ID							{ $$ = CreateInternalTreeNode("Tag", 1, $1); }
;

//	Declarators
VarDec:		ID							{ $$ = CreateInternalTreeNode("VarDec", 1, $1); }
	|		VarDec LB INT RB			{ $$ = CreateInternalTreeNode("VarDec", 4, $1, $2, $3, $4); }
	|		VarDec LB error RB			{ yyerrok; }
;
FunDec:		ID LP VarList RP			{ $$ = CreateInternalTreeNode("FunDec", 4, $1, $2, $3, $4); }
	|		ID LP RP					{ $$ = CreateInternalTreeNode("FunDec", 3, $1, $2, $3); }
;
VarList: 	ParamDec COMMA VarList		{ $$ = CreateInternalTreeNode("VarList", 3, $1, $2, $3); }
	|		ParamDec					{ $$ = CreateInternalTreeNode("VarList", 1, $1); }
;
ParamDec:	Specifier VarDec			{ $$ = CreateInternalTreeNode("ParamDec", 2, $1, $2); }
;

//	Statements
CompSt:		LC DefList StmtList RC		{ $$ = CreateInternalTreeNode("CompSt", 4, $1, $2, $3, $4); }
	|		LC DefList StmtList			{ yyerror("syntax error, expecting RC"); yyerrok; }
	|		LC error RC					{ yyerrok; }
;
StmtList:	Stmt StmtList				{ $$ = CreateInternalTreeNode("StmtList", 2, $1, $2); }
	|		/*	empty	*/				{ $$ = CreateInternalTreeNode("StmtList", 0); }
;
Stmt:		Exp SEMI					{ $$ = CreateInternalTreeNode("Stmt", 2, $1, $2); }
	|		Exp							{ yyerror("syntax error, expecting SEMI"); yyerrok; }
	|		CompSt						{ $$ = CreateInternalTreeNode("Stmt", 1, $1); }
	|		RETURN Exp SEMI				{ $$ = CreateInternalTreeNode("Stmt", 3, $1, $2, $3); }
	|		RETURN error SEMI			{ yyerrok; }
	|		IF LP Exp RP Stmt	%prec LOWER_THAN_ELSE	{ $$ = CreateInternalTreeNode("Stmt", 5, $1, $2, $3, $4, $5); }
	|		IF LP Exp RP Stmt ELSE Stmt	{ $$ = CreateInternalTreeNode("Stmt", 7, $1, $2, $3, $4, $5, $6, $7); }
	|		IF LP Exp RP RedundantRP Stmt	{ yyerrok; }
	|		WHILE LP Exp RP Stmt		{ $$ = CreateInternalTreeNode("Stmt", 5, $1, $2, $3, $4, $5); }
	|		WHILE LP Exp RP RedundantRP Stmt	{ }
	|		WHILE Exp RedundantRP Stmt		{ yyerrok; }
	|		WHILE LP error RP Stmt			{ yyerrok; }
	|		IF LP error RP Stmt				{ yyerrok; }
	|		IF LP error RP Stmt ELSE Stmt	{ yyerrok; }
	|		IF LP Exp RP error ELSE Stmt	{ yyerrok; }
	|		IF LP error RP error ELSE Stmt	{ yyerrok; }
;
RedundantRP:	RP 							{ yyerror("syntax error, redundant RP"); yyerrok; }
	|			RP RedundantRP				{}
;

//	Local Definitions
DefList: 	Def DefList					{ $$ = CreateInternalTreeNode("DefList", 2, $1, $2); }
	|		/*	empty	*/				{ $$ = CreateInternalTreeNode("DefList", 0); }
;
Def:		Specifier DecList SEMI		{ $$ = CreateInternalTreeNode("Def", 3, $1, $2, $3); }
	|		Specifier DecList error SEMI	{ yyerrok; }
;
DecList:	Dec							{ $$ = CreateInternalTreeNode("DecList", 1, $1); }
	|		Dec COMMA DecList			{ $$ = CreateInternalTreeNode("DecList", 3, $1, $2, $3); }
;
Dec: 		VarDec						{ $$ = CreateInternalTreeNode("Dec", 1, $1); }
	|		INT							{ yyerror("syntax error, unexpected INT, expecting ID"); yyerrok; }
	|		FLOAT						{ yyerror("syntax error, unexpected FLOAT, expecting ID"); yyerrok; }
	|		VarDec ASSIGNOP Exp			{ $$ = CreateInternalTreeNode("Dec", 3, $1, $2, $3); }	
;

//	Expressions
Exp:		Exp ASSIGNOP Exp			{ $$ = CreateInternalTreeNode("Exp", 3, $1, $2, $3); }
	|		Exp AND Exp					{ $$ = CreateInternalTreeNode("Exp", 3, $1, $2, $3); }
	|		Exp OR Exp					{ $$ = CreateInternalTreeNode("Exp", 3, $1, $2, $3); }
	|		Exp RELOP Exp				{ $$ = CreateInternalTreeNode("Exp", 3, $1, $2, $3); }
	|		Exp PLUS Exp				{ $$ = CreateInternalTreeNode("Exp", 3, $1, $2, $3); }
	|		Exp MINUS Exp				{ $$ = CreateInternalTreeNode("Exp", 3, $1, $2, $3); }
	|		Exp STAR Exp				{ $$ = CreateInternalTreeNode("Exp", 3, $1, $2, $3); }
	|		Exp DIV Exp					{ $$ = CreateInternalTreeNode("Exp", 3, $1, $2, $3); }
	|		LP Exp RP					{ $$ = CreateInternalTreeNode("Exp", 3, $1, $2, $3); }
	|		MINUS Exp					{ $$ = CreateInternalTreeNode("Exp", 2, $1, $2); }
	|		NOT Exp						{ $$ = CreateInternalTreeNode("Exp", 2, $1, $2); }
	|		ID LP Args RP				{ $$ = CreateInternalTreeNode("Exp", 4, $1, $2, $3, $4); }
	|		ID LP RP					{ $$ = CreateInternalTreeNode("Exp", 3, $1, $2, $3); }
	|		Exp LB Exp RB				{ $$ = CreateInternalTreeNode("Exp", 4, $1, $2, $3, $4); }
	|		Exp DOT ID					{ $$ = CreateInternalTreeNode("Exp", 3, $1, $2, $3); }
	|		ID							{ $$ = CreateInternalTreeNode("Exp", 1, $1); }
	|		INT							{ $$ = CreateInternalTreeNode("Exp", 1, $1); }
	|		FLOAT						{ $$ = CreateInternalTreeNode("Exp", 1, $1); }
	|		LP error RP					{ yyerrok; }
	|		ID LP error RP				{ yyerrok; }
	|		Exp LB error RB				{ yyerrok; }
	|		error ID					{ yyerrok; }
;
Args:		Exp COMMA Args				{ $$ = CreateInternalTreeNode("Args", 3, $1, $2, $3); }
	|		Exp							{ $$ = CreateInternalTreeNode("Args", 1, $1); }
;
%%

int main(int argc, char** argv) {
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			perror(argv[1]);
			return 1;
		}
		if (argc == 2) stream = stdout;
		else stream = fopen(argv[2], "w");
		output_files = argv + 2;
	}
	yyparse();

	if (error_lex == 1 || error_syntax == 1) return 0;

	// OutputTree(root, 0);

	ProcessProgram(root);

	return 0;
}
int yyerror(const char* msg) {
	printf("Error Type B at Line %d: %s.\n", yylineno, msg);
	error_syntax = 1;
}