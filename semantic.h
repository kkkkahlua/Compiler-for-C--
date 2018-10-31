#ifndef __SEMANTIC_H_INCLUDED_
#define __SEMANTIC_H_INCLUDED_

#include "tree.h"

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct ParamList_* ParamList;

typedef struct Type_ {
    enum { kBASIC, kARRAY, kSTRUCTURE, kFUNCTION } kind;
    union {
        int basic;      //  0: int; 1: float;
        struct { Type elem; int size; } array;
        struct { char* name; FieldList field_list; } structure;
        struct { Type type_ret; ParamList param_list; int defined; } function;
    } u;
} Type_;

typedef struct ParamList_ {
    Type type;
    ParamList tail;
} ParamList_;

typedef struct FieldList_ {
    char* name;
    Type type;
    FieldList tail;
} FieldList_;

void AnalyzeProgram(TreeNode* root);

void AnalyzeExtDefList(TreeNode* root);

void ProcessExtDecList(TreeNode* ext_dec_list, Type type);

void FillParamDecIntoParam(TreeNode* param_dec, ParamList param);

void GetVarList(TreeNode* var_list, ParamList param_list);

Type GetTypeFunction(TreeNode* fun_def, Type type_ret);

void ProcessFunDef(TreeNode* fun_def, Type type_ret);

void ProcessFunDec(TreeNode* fun_def, Type type_ret);

void AnalyzeExtDef(TreeNode* root);

Type GetTypeBasic(TreeNode* root);

char* GetTagName(TreeNode* root);

void AnalyzeVarDec(TreeNode* var_dec, char* name, Type type);

void ProcessDec(TreeNode* dec, Type type, FieldList field_list);

void ProcessDecList(TreeNode* dec_list, Type type, FieldList field_list);

void FillDefIntoField(TreeNode* def, FieldList field_list);

void FillDefListIntoFieldList(TreeNode* def_list, FieldList field_list);

Type GetTypeStructure(TreeNode* root);

Type GetType(TreeNode* root);

#endif