%{
#define YYSTYPE TreeNode*
#define YYERROR_VERBOSE 1

#include "lex.yy.c"

#include <stdio.h>

extern int error_lex;
extern int yylineno;

TreeNode* root;
%}
%token			SEMI COMMA
%token			LC RC
%token			TYPE
%token 			ID INT FLOAT
%token			RETURN IF WHILE STRUCT
%left			ASSIGNOP
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
;
ExtDecList:	VarDec						{ $$ = CreateInternalTreeNode("ExtDecList", 1, $1); }
	|		VarDec COMMA ExtDecList		{ $$ = CreateInternalTreeNode("ExtDecList", 3, $1, $2, $3); }
;

//	Specifiers
Specifier:	TYPE						{ $$ = CreateInternalTreeNode("Specifier", 1, $1); }
	|		StructSpecifier				{ $$ = CreateInternalTreeNode("Specifier", 1, $1); }
;
StructSpecifier:	STRUCT OptTag LC DefList RC	{ $$ = CreateInternalTreeNode("StructSpecifier", 5, $1, $2, $3, $4, $5); }
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
;
StmtList:	Stmt StmtList				{ $$ = CreateInternalTreeNode("StmtList", 2, $1, $2); }
	|		/*	empty	*/				{ $$ = CreateInternalTreeNode("StmtList", 0); }
;
Stmt:		Exp SEMI					{ $$ = CreateInternalTreeNode("Stmt", 2, $1, $2); }
	|		CompSt						{ $$ = CreateInternalTreeNode("Stmt", 1, $1); }
	|		RETURN Exp SEMI				{ $$ = CreateInternalTreeNode("Stmt", 3, $1, $2, $3); }
	|		IF LP Exp RP Stmt	%prec LOWER_THAN_ELSE	{ $$ = CreateInternalTreeNode("Stmt", 5, $1, $2, $3, $4, $5); }
	|		IF LP Exp RP Stmt ELSE Stmt	{ $$ = CreateInternalTreeNode("Stmt", 7, $1, $2, $3, $4, $5, $6, $7); }
	|		WHILE LP Exp RP Stmt		{ $$ = CreateInternalTreeNode("Stmt", 5, $1, $2, $3, $4, $5); }
;

//	Local Definitions
DefList: 	Def DefList					{ $$ = CreateInternalTreeNode("DefList", 2, $1, $2); }
	|		/*	empty	*/				{ $$ = CreateInternalTreeNode("DefList", 0); }
;
Def:		Specifier DecList SEMI		{ $$ = CreateInternalTreeNode("Def", 3, $1, $2, $3); }
;
DecList:	Dec							{ $$ = CreateInternalTreeNode("DecList", 1, $1); }
	|		Dec COMMA DecList			{ $$ = CreateInternalTreeNode("DecList", 3, $1, $2, $3); }
;
Dec: 		VarDec						{ $$ = CreateInternalTreeNode("Dec", 1, $1); }
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
	}
	yyparse();

	if (error_lex == 1) return 0;

	OutputTree(root, 0);
	return 0;
}
yyerror(char* msg) {
	printf("Error Type B at line %d: %s.\n", yylineno, msg);
}