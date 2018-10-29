#include "semantic.h"

#include <stdlib.h>

void AnalyzeProgram(TreeNode* root) {
    AnalyzeExtDefList(root->son);
}

void AnalyzeExtDefList(TreeNode* root) {
    if (root == NULL) return;
    AnalyzeExtDef(root->son);
}

void ProcessExtDecList(TreeNode* ext_dec_list, Type type) {
    Type* type_ori = (Type)malloc(Type_);
    *type_ori = *type;
    char* name;
    AnalyzeVarDec(ext_dec_list->son, name, type);
    if (ext_dec_list->son->bro != NULL) {
        ProcessExtDecList(ext_dec_list->son->bro->bro, type_ori);
    }
}

void AnalyzeExtDef(TreeNode* ext_def) {
    //  TODO: AnalyzeExtDef
    TreeNode* specifier = ext_def->son;
    Type type = GetType(specifier);
    TreeNode* next = specifier->bro;
    if (next->type == kSYMBOL && strcmp(next->val.ValString, "SEMI") == 0) {
        //  Struct Definition
        //  TODO: 
        //  check duplication in struct element definition
        //  insert into symbol table
        return;
    }
    assert(next->type == kINTERNAL);
    if (strcmp(next->val.ValString, "ExtDecList") == 0) {
        ProcessExtDecList(next, type);
        return;
    }
    assert(strcmp(next->val.ValString, "FunDec") == 0);
    
}

Type GetTypeBasic(TreeNode* root) {
    Type type = (Type)malloc(sizeof(Type_));
    type->kind = kBASIC;
    if (strcmp(root->val.ValString, "int") == 0) {
        type->u.basic = 0;
    } else {    //  float
        type->u.basic = 1;
    }
    return type;
}

char* GetTagName(TreeNode* root) {
    char* name;
    if (root->son == NULL) {
        name = (char*)malloc(1);
        strcpy(name, "\0");
    } else {
        TreeNode* id = root->son;
        assert(id->type == kID);
        name = (char*)malloc(sizeof(id->val.ValString) + 1);
        strcpy(name, id->val.ValString);
    }
    return name;
}

void AnalyzeVarDec(TreeNode* var_dec, char* name, Type type) {
    if (var_dec->son->type == kID) {
        name = (char*)malloc(sizeof(var_dec->son->val.ValString) + 1);
        //  TODO: In ExtDecList, check name duplication
        strcpy(name, var_dec->son->val.ValString);
        return;
    }
    Type type_next = (Type)malloc(sizoef(Type_));
    *type_next = *type;

    TreeNode* var_dec_next = var_dec->son;

    type->kind = kARRAY;
    type->u.array.size = var_dec_next->bro->bro->val.ValInt;
    AnalyzeVarDec(var_dec_next, name, type_next);
    type->u.array.elem = type_next;

    if (var_dec->bro != NULL) {
        TreeNode* exp = var_dec->bro->bro;
        //  TODO: check whether expression is legal
    }
}

void ProcessDec(TreeNode* dec, Type type, FieldList field_list) {
    Type type_ori = (Type)malloc(sizeof(Type_));
    *type_ori = *type;
    char* name;
    AnalyzeVarDec(dec->son, name, type);
    field_list = (FieldList)malloc(sizeof(FieldList_));
    field_list->name = name;
    field_list->type = type;
    field_list->tail = NULL;
    if (dec->bro != NULL) {
        ProcessDecList(dec->bro->bro, type_ori, field_list->tail);
        //  move field_list to the end of this dec_list
        field_list = field_list->tail;
    }
}

void ProcessDecList(TreeNode* dec_list, Type type, FieldList field_list) {
    ProcessDec(dec_list->son, type, field_list);
}

void FillDefIntoField(TreeNode* def, FieldList field_list) {
    Type type = GetType(def->son);
    ProcessDecList(def->son->bro, type, field_list);
    FillDefListIntoFieldList(def->bro, field_list->tail);
}

void FillDefListIntoFieldList(TreeNode* def_list, FieldList field_list) {
    if (def_list == NULL) return;
    FillDefIntoField(def_list->son, field_list);
}

Type GetTypeStructure(TreeNode* root) {
    Type type = (Type)malloc(sizeof(Type_));
    FieldList field_list = type->u.structure;

    type->kind = kSTRUCTURE;

    TreeNode* tag = root->bro;

    char* struct_name = GetTagName(tag);

    if (strcmp(tag->val.ValString, "OptTag") == 0) {    //  definition
        TreeNode* lc = tag->bro;
        assert(lc->type == kSYMBOL && strcmp(lc->val.ValString, "LC") == 0);
        TreeNode* def_list = lc->bro;
        FillDefListIntoFieldList(def_list, field_list);
    } else {    //  declaration
        //  TODO: check whether the struct has been defined or not
    }
}

Type GetType(TreeNode* root) {
    Type type;
    TreeNode* specifier = root->son;
    if (specifier->type == kTYPE) {
        type = GetTypeBasic(specifier);
    } else {
        type = GetTypeStructure(specifier);
    }
    return type;
}