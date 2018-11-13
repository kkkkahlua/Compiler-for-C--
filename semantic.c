#include "semantic.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CheckSymbolName(TreeNode* node, const char* name) {
    return strcmp(node->val.ValString, name) == 0;
}

void AnalyzeProgram(TreeNode* root) {
    AnalyzeExtDefList(root->son);
}

void AnalyzeExtDefList(TreeNode* ext_def_list) {
    while (1) {
        AnalyzeExtDef(ext_def_list->son);
        ext_def_list = ext_def_list->son->bro;
        if (!ext_def_list) return;
    }
}

void ProcessExtDecList(TreeNode* ext_dec_list, Type type) {
    while (1) {
        char* name;
        Type type_comp = AnalyzeVarDec(ext_dec_list->son, name, type);
        //  TODO: 
        //  1. check variable duplication
        //  2. add to symbol table

        if (!ext_dec_list->son->bro) return;
        ext_dec_list = ext_dec_list->son->bro->bro;
    }
}

void FillParamDecIntoParam(TreeNode* param_dec, ParamList param) {
    TreeNode* specifier = param_dec->son;
    assert(CheckSymbolName(specifier, "Specifier"));
    TreeNode* var_dec = specifier->bro;
    assert(CheckSymbolName(var_dec, "VarDec"));

    Type type = GetType(specifier);
    char* name;
    Type type_comp = AnalyzeVarDec(var_dec, name, type);
    
    param = (ParamList)malloc(sizeof(ParamList_));
    param->type = type_comp;
    param->tail = NULL;
    //  TODO: add function definition into symbol table
}

void GetVarList(TreeNode* var_list, ParamList param_list) {
    TreeNode* param_dec = var_list->son;
    assert(CheckSymbolName(param_dec, "ParamDec"));
    FillParamDecIntoParam(param_dec, param_list);
    if (param_dec->bro == NULL) return;
    GetVarList(param_dec->bro->bro, param_list->tail);
}

Type GetTypeFunction(TreeNode* fun_def, Type type_ret) {
    Type type = (Type)malloc(sizeof(Type_));
    type->kind = kFUNCTION;
    type->u.function.type_ret = type_ret;
    type->u.function.param_list = NULL;
    TreeNode* var_list = fun_def->son->bro->bro;
    if (CheckSymbolName(var_list, "VarList")) {
        GetVarList(var_list, type->u.function.param_list);
    }
    return type;
}

void ProcessFunDef(TreeNode* fun_def, Type type_ret) {
    Type type = GetTypeFunction(fun_def, type_ret);
    TreeNode* comp_st = fun_def->bro;
}

void ProcessFunDec(TreeNode* fun_def, Type type_ret) {
    Type type = GetTypeFunction(fun_def, type_ret);
}

void AnalyzeExtDef(TreeNode* ext_def) {
    //  TODO: AnalyzeExtDef
    TreeNode* specifier = ext_def->son;
    Type type = GetType(specifier);
    TreeNode* next = specifier->bro;
    if (CheckSymbolName(next, "SEMI")) {
        //  Struct Definition
        //  TODO: 
        //  check duplication in struct element definition
        //  insert into symbol table
        return;
    }

    assert(next->type == kINTERNAL);
    if (CheckSymbolName(next, "ExtDecList")) {
        //  Global Variable
        ProcessExtDecList(next, type);
        return;
    }

    //  Function
    TreeNode* fun_dec = next;
    assert(CheckSymbolName(fun_dec, "FunDec"));

    if (CheckSymbolName(fun_dec->bro, "SEMI")) {
        //  TODO: Function Declaration
        ProcessFunDec(fun_dec, type);
        return;
    }
    //  Function Definition
    assert(CheckSymbolName(fun_dec->bro, "CompSt"));
    ProcessFunDef(fun_dec, type);
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
        return NULL;
    } else {
        TreeNode* id = root->son;
        assert(id->type == kID);
        name = (char*)malloc(sizeof(id->val.ValString) + 1);
        strcpy(name, id->val.ValString);
    }
    return name;
}

Type AnalyzeVarDec(TreeNode* var_dec, char* name, Type type_base) {
    Type type_comp = (Type)malloc(sizeof(Type_));
    *type_comp = *type_base;
    while (1) {
        if (var_dec->son->type == kID) {
            name = (char*)malloc(sizeof(var_dec->son->val.ValString) + 1);
        
            //  TODO: In ExtDecList, check name duplication
            strcpy(name, var_dec->son->val.ValString);
            printf("name = %s\n", name);
            OutputType(type_comp, 0);
            return type_comp;
        }
        type_base = type_comp;
        type_comp = (Type)malloc(sizeof(Type_));
        type_comp->kind = kARRAY;
        type_comp->u.array.size = var_dec->son->bro->bro->val.ValInt;
        type_comp->u.array.elem = type_base;

        var_dec = var_dec->son;
    }
}

FieldList ProcessDec(TreeNode* dec, Type type) {
    char* name;
    Type type_comp = AnalyzeVarDec(dec->son, name, type);
    // puts("ProcessDec-begin");
    // OutputType(type_comp, 0);
    // puts("ProcessDec-end");
    FieldList field_list = (FieldList)malloc(sizeof(FieldList_));
    field_list->name = name;
    field_list->type = type_comp;
    field_list->tail = NULL;

    //  TODO: Dec -> VarDec ASSIGNOP Exp
    return field_list;
}

FieldList ProcessDecList(TreeNode* dec_list, Type type) {
    FieldList field_list = ProcessDec(dec_list->son, type),
            pre_field = field_list;
    int dec = 0;
    while (1) {
        if (!dec_list->son->bro) return field_list;
        dec_list = dec_list->son->bro->bro;

        FieldList cur_field = ProcessDec(dec_list->son, type);
        pre_field->tail = cur_field;
        pre_field = cur_field;
    };
}

FieldList FillDefIntoField(TreeNode* def) {
    Type type = GetType(def->son);
    return ProcessDecList(def->son->bro, type);
}

FieldList LastField(FieldList field_list) {
    FieldList field = field_list;
    while (1) {
        FieldList nxt_field = field->tail;
        if (!nxt_field) return field;
        field = nxt_field;
    }
}

int def_list_cnt = 0;
FieldList FillDefListIntoFieldList(TreeNode* def_list) {
    if (!def_list) return NULL;

    FieldList field_list = FillDefIntoField(def_list->son),
            pre_field = LastField(field_list);
    while (1) {
        def_list = def_list->son->bro;
        if (!def_list) return field_list;

        FieldList cur_field = FillDefIntoField(def_list->son);
        pre_field->tail = cur_field;
        pre_field = LastField(cur_field);
    }
}

Type GetTypeStructure(TreeNode* struct_specifier) {
    Type type = (Type)malloc(sizeof(Type_));

    type->kind = kSTRUCTURE;

    TreeNode* tag = struct_specifier->son->bro;

    type->u.structure.name = GetTagName(tag);
    //  TODO: combine struct_name with the definition of struct

    if (strcmp(tag->val.ValString, "OptTag") == 0) {    //  definition
        TreeNode* lc = tag->bro;
        assert(lc->type == kSYMBOL && strcmp(lc->val.ValString, "LC") == 0);
        TreeNode* def_list = lc->bro;
        type->u.structure.field_list = FillDefListIntoFieldList(def_list);
        OutputType(type, 0);
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

void OutputFieldList(FieldList field_list, int indent) {
    if (field_list == NULL) return;
    for (int i = 0; i < indent; ++i) printf(" ");
    printf("%s\n", field_list->name);
    OutputType(field_list->type, indent+2);
    OutputFieldList(field_list->tail, indent);
}

void OutputType(Type type, int indent) {
    for (int i = 0; i < indent; ++i) printf(" ");
    switch (type->kind) {
        case kBASIC:
            printf("basic: %s\n", type->u.basic ? "float" : "int");
            break;
        case kARRAY:
            printf("array: %d\n", type->u.array.size);
            OutputType(type->u.array.elem, indent+2);
            break;
        case kSTRUCTURE:
            printf("structure: %s\n", type->u.structure.name);
            OutputFieldList(type->u.structure.field_list, indent+2);
            break;
        case kFUNCTION:
            puts("function here");
    }
}