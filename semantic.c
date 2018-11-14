#include "semantic.h"

#include "SymbolTable.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int layer = 0;

const int kErrorMsgLen = 100;

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
        Type type_comp = AnalyzeVarDec(ext_dec_list->son, &name, type);

        if (LookupVariable(name, &type_comp, layer) == 1) {
            //  Error 3: redefinition in global variable
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "Redefined variable \"%s\"", name);
            OutputSemanticErrorMsg(3, ext_dec_list->son->lineno, error_msg);
            free(error_msg);
        } else {
            //  add to symbol table
            insert(name, type_comp, layer);
        }

        if (!ext_dec_list->son->bro) return;
        ext_dec_list = ext_dec_list->son->bro->bro;
    }
}

ParamList ProcessParamDec(TreeNode* param_dec) {
    TreeNode* specifier = param_dec->son;
    assert(CheckSymbolName(specifier, "Specifier"));
    TreeNode* var_dec = specifier->bro;
    assert(CheckSymbolName(var_dec, "VarDec"));

    Type type = GetType(specifier);
    char* name;
    Type type_comp = AnalyzeVarDec(var_dec, &name, type);
    
    ParamList param = (ParamList)malloc(sizeof(ParamList_));
    param->type = type_comp;
    param->tail = NULL;
    return param;
}

ParamList GetVarList(TreeNode* var_list) {
    ParamList param_list = ProcessParamDec(var_list->son),
            pre_param = param_list;
    while (1) {
        if (!var_list->son->bro) return param_list;
        var_list = var_list->son->bro->bro;

        ParamList cur_param = ProcessParamDec(var_list->son);
        pre_param->tail = cur_param;
        pre_param = cur_param;
    };
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
    // OutputType(type, 0);
    return type;
}

ParamList FillArgIntoParam(TreeNode* exp) {
    ParamList param_list = (ParamList)malloc(sizeof(ParamList_));
    param_list->type = ProcessExp(exp);
    param_list->tail = NULL;
    return param_list;
}

ParamList FillArgsIntoParamList(TreeNode* args) {
    ParamList param_list = FillArgIntoParam(args->son),
            pre_param = param_list;
    while (1) {
        if (!args->son->bro) return param_list;
        args = args->son->bro->bro;

        ParamList cur_param = FillArgIntoParam(args->son);
        pre_param->tail = cur_param;
        pre_param = cur_param;
    };
}

Type ProcessExp(TreeNode* exp) {
    if (exp->son->type == kID) {
        TreeNode* id = exp->son;
        if (!id->bro) {   /*  Exp -> ID   */
            Type type = NULL;
            if (!LookupVariable(exp->son->val.ValString, &type, layer)) {
                //  Error 1: undefined variable
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "Undefined variable \"%s\"", id->val.ValString);
                OutputSemanticErrorMsg(1, id->lineno, error_msg);
                free(error_msg);
            }
            return type;
        } else {        /*  function call   */
            Type type_ret = NULL;
            ParamList parma_list = NULL;
            if (LookupFunction(id->val.ValString, type_ret, parma_list, 1)) {
                ParamList cur_param_list = NULL;
                if (CheckSymbolName(id->bro->bro, "Args") {
                    parma_list = FillArgsIntoParamList(id->bro->bro);
                }
                if (!TypeConsistentParamList(param_list, cur_param_list)) {
                    //  Error 9: function param inconsistent
                    char* error_msg = (char*)malloc(kErrorMsgLen);
                    sprintf(error_msg, "Function \"%s\" is not applicable to function call", id->val.ValString);
                    OutputSemanticErrorMsg(9, id->lineno, error_msg);
                    free(error_msg);    
                }
            } else {
                //  Error 2: undefined function
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "Undefined function \"%s\"", id->val.ValString);
                OutputSemanticErrorMsg(2, id->lineno, error_msg);
                free(error_msg);
            }
            return type_ret;
        }
    }
    if (exp->type == kINT || exp->type == kFLOAT) {
        Type type = (Type)malloc(sizeof(Type_));
        type->kind = kBASIC;
        type->u.basic = exp->type == kINT ? 0 : 1;
        return type;
    }

    if (CheckSymbolName(exp->son, "Exp")) {
        TreeNode* exp_1 = exp->son;
        if (CheckSymbolName(exp_1->bro), "ASSIGNOP") {
            if (!CheckLvalue(exp_1)) {
                //  Error 6: rvalue on the left-hand side of an assignment
                OutputSemanticErrorMsg(6, exp_1->lineno, "The left-hand side of an assignment must be a variable");
            }
            //  TODO: 
            //  consider whether to continue processing or not 
            //  when the left side is not an lvalue
            Type type_r = ProcessExp(exp_1->bro->bro),
                type_l = ProcessExp(exp_1);
            
            if (!TypeConsistent(type_r, type_l)) {
                OutputSemanticErrorMsg(6, exp_1->lineno, "Type mismatched for assignment");
            }
            return type_l;
        } else if (CheckSymbolName(exp_1->bro, "LB")) {
            Type type_base = ProcessExp(exp_1->bro),
                type_idx = ProcessExp(exp_1->bro->bro);
            if (type_base->kind != kARRAY) {
                //  Error 10: [ ] operated on a non-array variable
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "\"%s\" is not an array", );
                OutputSemanticErrorMsg(3, dec_list->son->lineno, error_msg);
                free(error_msg);
            }
        }
            /*if (CheckSymbolName(exp_1->bro, "AND")
                || CheckSymbolName(exp_1->bro, "OR")
                || CheckSymbolName(exp_1->bro, "PLUS")
                || CheckSymbolName(exp_1->bro, "MINUS")
                || CheckSymbolName(exp_1->bro, "STAR")
                || CheckSymbolName(exp_1->bro, "DIV")
                || exp_1->bro->type == kRELOP)*/ {
            Type type_l_base = ProcessExp(exp_1),
                type_r_base = ProcessExp(exp_1->bro->bro);
            if (!CheckTypeBaseConsistent(type_l_base, type_r_base)) {
                OutputSemanticErrorMsg(6, exp_1->lineno, "Type mismatched for operands");
            }
            return type_l_base;    
        }
    } else if (CheckSymbolName(exp->son, "LP")) {
        ProcessExp(exp->son->bro);
    } else if ()

}

void AnalyzeDec(TreeNode* dec, char** name, Type type) {
    Type type_comp = AnalyzeVarDec(dec->son, name, type);
    jif (!dec->son->bro) return;
    ProcessExp(dec->son->bro->bro);
}

void ProcessDecList(TreeNode* dec_list, Type type) {
    while (1) {
        char* name;
        Type type_comp = AnalyzeDec(dec_list->son, &name, type);

        if (LookupVariable(name, &type_comp, layer) == 1) {
            //  Error 3: redefinition in variable
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "Redefined variable \"%s\"", name);
            OutputSemanticErrorMsg(3, dec_list->son->lineno, error_msg);
            free(error_msg);
        } else {
            //  add to symbol table
            insert(name, type_comp, layer);
        }

        if (!dec_list->son->bro) return;
        dec_list = dec_list->son->bro->bro;
    }
}

void ProcessDef(TreeNode* def) {
    Type type = GetType(def->son);
    return ProcessDecList(def->son->bro, type);    
}

void ProcessDefList(TreeNode* def_list) {
    if (!def_list) return NULL;

    while (1) {
        def_list = def_list->son->bro;
        if (!def_list) return;
        ProcessDef(def_list->son);
    }
}

void ProcessCompSt(TreeNode* comp_st) {
    ++layer;
    TreeNode* def_list = comp_st->son->bro,
            * stmt_list = def_list->bro;
    ProcessDefList(def_list);
    --layer;
}

void ProcessFunDef(TreeNode* fun_def, Type type_ret) {
    Type type = GetTypeFunction(fun_def, type_ret);
    switch (LookupFunction(type->u.function.name, &type_ret, &(type->u.function.param_list), 0)) {
        case 0: //  function neither defined nor declared
            type->u.function.defined = 1;
            insert(type->u.function.name, type, layer);
            break;
        case 1: //  function already declared but not yet defined
            UpdateFunctionStatus(type->u.function.name);
            break;
        case 2: {//  Error 19, type conflict
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "Inconsistent declaration/definition of function \"%s\"", type->u.function.name);
            OutputSemanticErrorMsg(19, fun_def->lineno, error_msg);
            free(error_msg);
            break;
        }
        case 3: {//  Error 19, multiple definition
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "multiple definition of function \"%s\"", type->u.function.name);
            OutputSemanticErrorMsg(19, fun_def->lineno, error_msg);
            free(error_msg);
            break;
        }
    }

    TreeNode* comp_st = fun_def->bro;
    ProcessCompSt(comp_st);
    //  TODO: analyze the function body
}

void ProcessFunDec(TreeNode* fun_def, Type type_ret) {
    Type type = GetTypeFunction(fun_def, type_ret);
    switch (LookupFunction(type->u.function.name, &type_ret, &(type->u.function.param_list), 0)) {
        case 0: //  neither defined nor declared
            type->u.function.defined = 0;
            insert(type->u.function.name, type, layer);
            break;
        case 1: //  function already declared but not yet defined
            break;
        case 2: {//  Error 19, type conflict
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "Inconsistent declaration/definition of function \"%s\"", type->u.function.name);
            OutputSemanticErrorMsg(19, fun_def->lineno, error_msg);
            free(error_msg);
            break;
        }
        case 3: //  already defined
            break;
    }
}

void AnalyzeExtDef(TreeNode* ext_def) {
    TreeNode* specifier = ext_def->son;
    Type type = GetType(specifier);
    TreeNode* next = specifier->bro;

    if (CheckSymbolName(next, "SEMI")) {
        //  Struct Definition
        insert(type->u.structure.name, type, layer);
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

    //  Function Declaration
    if (CheckSymbolName(fun_dec->bro, "SEMI")) {
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

Type AnalyzeVarDec(TreeNode* var_dec, char** name, Type type_base) {
    Type type_comp = (Type)malloc(sizeof(Type_));
    *type_comp = *type_base;
    while (1) {
        if (var_dec->son->type == kID) {
            *name = (char*)malloc(sizeof(var_dec->son->val.ValString) + 1);
        
            strcpy(*name, var_dec->son->val.ValString);
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

FieldList FillDecIntoField(TreeNode* dec, Type type) {
    char* name;
    Type type_comp = AnalyzeVarDec(dec->son, &name, type);

    //  Error 15: redefinition in struct field
    if (LookupVariable(name, &type_comp, layer) == 1) {
        char* error_msg = (char*)malloc(kErrorMsgLen);
        sprintf(error_msg, "Redefined field \"%s\"", name);
        OutputSemanticErrorMsg(15, dec->son->lineno, error_msg);
        free(error_msg);
    } else {
        insert(name, type_comp, layer);
    }

    FieldList field_list = (FieldList)malloc(sizeof(FieldList_));
    field_list->name = name;
    field_list->type = type_comp;
    field_list->tail = NULL;

    //  Error 15: assignment in sturct definition
    if (dec->son->bro) {
        OutputSemanticErrorMsg(15, dec->son->bro->lineno, "Assignment in struct definition");
    }
    return field_list;
}

FieldList FillDecListIntoFieldList(TreeNode* dec_list, Type type) {
    FieldList field_list = FillDecIntoField(dec_list->son, type),
            pre_field = field_list;
    while (1) {
        if (!dec_list->son->bro) return field_list;
        dec_list = dec_list->son->bro->bro;

        FieldList cur_field = FillDecIntoField(dec_list->son, type);
        pre_field->tail = cur_field;
        pre_field = cur_field;
    };
}

FieldList FillDefIntoFieldList(TreeNode* def) {
    Type type = GetType(def->son);
    return FillDecListIntoFieldList(def->son->bro, type);
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

    FieldList field_list = FillDefIntoFieldList(def_list->son),
            pre_field = LastField(field_list);
    while (1) {
        def_list = def_list->son->bro;
        if (!def_list) return field_list;

        FieldList cur_field = FillDefIntoFieldList(def_list->son);
        pre_field->tail = cur_field;
        pre_field = LastField(cur_field);
    }
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
        type->u.structure.field_list = FillDefListIntoFieldList(def_list);
        RemoveStructElement(type);
        --layer;
    } else {    //  declaration
        switch (LookupStructDefinition(type->u.structure.name, &type, layer)) {
            case 0: {    /* Error 17: struct type not defined  */
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "Undefined structure \"%s\"", type->u.structure.name);
                OutputSemanticErrorMsg(17, tag->lineno, error_msg);
                free(error_msg);
                break;
            }
            case 1: {   /*  consistent, to be added to symbol table */
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

void RemoveStructElement(Type type) {
    assert(type->kind == kSTRUCTURE);
    FieldList field_list = type->u.structure.field_list;
    while (1) {
        if (!field_list) return;
        RemoveVariable(field_list->name, layer);
        field_list = field_list->tail;
    }
}

Type GetType(TreeNode* root) {
    Type type;
    TreeNode* specifier = root->son;
    if (specifier->type == kTYPE) {
        type = GetTypeBasic(specifier);
    } else {
        type = GetTypeStructure(specifier);
        // OutputType(type, 0);
    }
    return type;
}

void OutputFieldList(FieldList field_list, int indent) {
    if (!field_list) return;
    for (int i = 0; i < indent; ++i) printf(" ");
    printf("%s\n", field_list->name);
    OutputType(field_list->type, indent);
    OutputFieldList(field_list->tail, indent);
}

void OutputParamList(ParamList param_list, int indent) {
    if (!param_list) return;
    for (int i = 0; i < indent; ++i) printf(" ");
    OutputType(param_list->type, indent);
    OutputParamList(param_list->tail, indent);
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
            printf("function: %d\n", type->u.function.defined);
            puts("  ret_type:");
            OutputType(type->u.function.type_ret, indent+4);
            puts("  param_list:");
            OutputParamList(type->u.function.param_list, indent+4);
    }
}

void OutputSemanticErrorMsg(int error_type, int lineno, const char* error_msg) {
    printf("Error type %d at Line %d: %s.\n", error_type, lineno, error_msg);
}