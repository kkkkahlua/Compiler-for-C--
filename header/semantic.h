#ifndef __SEMANTIC_H_INCLUDED_
#define __SEMANTIC_H_INCLUDED_

#include "tree.h"
#include "type.h"

void OutputSemanticErrorMsg(int error_type, int lineno, const char* error_msg);

void ProcessProgram(TreeNode* root);

void ProcessExtDefList(TreeNode* root);

void ProcessExtDecList(TreeNode* ext_dec_list, Type type);

DefList ProcessParamDec(TreeNode* param_dec);

DefList GetVarList(TreeNode* var_list);

void ProcessFunDef(TreeNode* fun_def, Type type_ret);

void ProcessFunDec(TreeNode* fun_def, Type type_ret);

void ProcessExtDef(TreeNode* root);

char* GetTagName(TreeNode* root);

Type ProcessVarDec(TreeNode* var_dec, char** name, Type type_base);

DefList FillDefListIntoDefList(TreeNode* def_list, int* space);

void RemoveStructElement(Type type);

Type ProcessExp(TreeNode* exp, Operand* dst_op);

void ProcessStmtList(TreeNode* stmt_list, Type type);

void ProcessStmt(TreeNode* stmt, Type type);

void ProcessCompSt(TreeNode* comp_st, Type type);

void OutputDefList(DefList param_list, int indent);

int CheckSymbolName(TreeNode* node, const char* name);

#endif