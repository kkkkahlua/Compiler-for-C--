#include "type.h"

#include "semantic.h"
#include "SymbolTable.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int layer;
extern const int kErrorMsgLen;

Type GetTypeBasic(TreeNode* root);

Type GetTypeStructure(TreeNode* root);

int SizeOfType(Type type) {
    switch (type->kind) {
        case kBASIC: return 4;
        case kARRAY: return type->u.array.space * type->u.array.size;
        case kSTRUCTURE: return type->u.structure.space;
        default: assert(0);
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

Type GetTypeStructure(TreeNode* struct_specifier) {
    Type type = (Type)malloc(sizeof(Type_));

    type->kind = kSTRUCTURE;

    TreeNode* tag = struct_specifier->son->bro;

    type->u.structure.name = GetTagName(tag);

    if (strcmp(tag->val.ValString, "OptTag") == 0) {    //  definition
        TreeNode* lc = tag->bro;
        assert(lc->type == kSYMBOL && strcmp(lc->val.ValString, "LC") == 0);
        TreeNode* def_list = lc->bro;

        ++layer;
        int space;
        type->u.structure.field_list = FillDefListIntoDefList(def_list, &space);
        type->u.structure.space = space;
        RemoveStructElement(type);
        --layer;
        switch (LookupStruct(type->u.structure.name, NULL, layer, kStructDefine)) {
            case 1: {
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "Duplicated name \"%s\"", type->u.structure.name);
                OutputSemanticErrorMsg(16, tag->lineno, error_msg);
                free(error_msg);
                break;
            }
            case 0:
            case 2:
                insert(type->u.function.name, type);
                break;
        }
    } else {    //  declaration
        switch (LookupStruct(type->u.structure.name, &type, layer, kStructDeclare)) {
            case 0: {    /* Error 17: struct type not defined  */
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "Undefined structure \"%s\"", type->u.structure.name);
                OutputSemanticErrorMsg(17, tag->lineno, error_msg);
                free(error_msg);
                break;
            }
            case 1: {   /*  consistent, legal */
                break;
            }
            case 2: {   /*  Error 16: struct type duplicated    */
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "Duplicated name \"%s\"", type->u.structure.name);
                OutputSemanticErrorMsg(16, tag->lineno, error_msg);
                free(error_msg);
                break;
            }
        }
    }
    return type;
}

Type GetTypeFunction(TreeNode* fun_def, Type type_ret) {
    Type type = (Type)malloc(sizeof(Type_));
    type->kind = kFUNCTION;
    type->u.function.name = fun_def->son->val.ValString;
    type->u.function.type_ret = type_ret;
    type->u.function.param_list = NULL;
    TreeNode* var_list = fun_def->son->bro->bro;
    if (CheckSymbolName(var_list, "VarList")) {
        type->u.function.param_list = GetVarList(var_list);
    }
    type->u.function.defined = 0;
    return type;
}

Type GetTypeBasic(TreeNode* root) {
    return NewTypeBasic(strcmp(root->val.ValString, "int") == 0 ? 0 : 1);
}

void OutputType(Type type, int indent) {
    if (!type) return;
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
            OutputDefList(type->u.structure.field_list, indent+2);
            break;
        case kFUNCTION:
            printf("function: %d\n", type->u.function.defined);
            puts("  ret_type:");
            OutputType(type->u.function.type_ret, indent+4);
            puts("  param_list:");
            OutputDefList(type->u.function.param_list, indent+4);
    }
}

Type NewTypeBasic(int basic) {
    Type type = (Type)malloc(sizeof(Type_));
    type->kind = kBASIC;
    type->u.basic = basic;
    return type;
}

Type NewTypeFunction(const char* name, Type type_ret, DefList param_list, int defined) {
    Type type = (Type)malloc(sizeof(Type_));
    type->kind = kFUNCTION;
    type->u.function.name = NewString(name);
    type->u.function.type_ret = type_ret;
    type->u.function.param_list = param_list;
    type->u.function.defined = defined;
    return type;
}

char* NewString(const char* str) {
    char* p = (char*)malloc(sizeof(str) + 1);
    strcpy(p, str);
    return p;
}