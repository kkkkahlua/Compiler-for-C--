#include "semantic.h"

#include "SymbolTable.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int layer = 0;

const int kErrorMsgLen = 100;

FunctionList function_list = NULL;

int CheckSymbolName(TreeNode* node, const char* name) {
    return node->type != kRELOP && strcmp(node->val.ValString, name) == 0;
}

void AnalyzeProgram(TreeNode* root) {
    AnalyzeExtDefList(root->son);
    CheckFunctionDefinition();
}

void AnalyzeExtDefList(TreeNode* ext_def_list) {
    while (1) {
        AnalyzeExtDef(ext_def_list->son);
        ext_def_list = ext_def_list->son->bro;
        if (!ext_def_list) return;
    }
}

void CheckFunctionDefinition() {
    while (1) {
        if (!function_list) return;
        switch (LookupFunction(function_list->name, NULL, NULL, kCHECK)) {
            case -1:    /*  function name conflict with variable name, checked before   */
                break;
            case 0:     /*  won't happen    */
                break;
            case 1:
                break;  /*  decleared and defined, as expected  */
            case 2: {
                //  Error 18: function declared but not defined
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "Undefined function \"%s\"", function_list->name);
                OutputSemanticErrorMsg(18, function_list->lineno, error_msg);
                free(error_msg);
            }
        }
        function_list = function_list->tail;
    }
}

void ProcessExtDecList(TreeNode* ext_dec_list, Type type) {
    while (1) {
        char* name;
        Type type_comp = AnalyzeVarDec(ext_dec_list->son, &name, type);

        if (LookupVariable(name, NULL, layer, kVariableDefine) == 1) {
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
    char* name = NULL;
    Type type_comp = AnalyzeVarDec(var_dec, &name, type);
   
    ParamList param = (ParamList)malloc(sizeof(ParamList_));
    param->name = name;
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
    type->u.function.defined = 0;
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

int CheckLvalue(TreeNode* exp) {
    return (exp->son->type == kID && !exp->son->bro) ||
        (exp->son->bro && (CheckSymbolName(exp->son->bro, "LB")
                        || CheckSymbolName(exp->son->bro, "DOT")));
}

Type ProcessExp(TreeNode* exp) {
    if (exp->son->type == kID) {
        TreeNode* id = exp->son;
        if (!id->bro) {   /*  Exp -> ID   */
            Type type = NULL;
            if (!LookupVariable(exp->son->val.ValString, &type, layer, kVariableUse)) {
                //  Error 1: undefined variable
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "Undefined variable \"%s\"", id->val.ValString);
                OutputSemanticErrorMsg(1, id->lineno, error_msg);
                free(error_msg);
            }
            return type;
        } else {        /*  function call   */
            ParamList param_list = NULL;
            if (CheckSymbolName(id->bro->bro, "Args")) {
                param_list = FillArgsIntoParamList(id->bro->bro);
            }
            Type type_ret = NULL;
            switch (LookupFunction(id->val.ValString, &type_ret, param_list, kCALL)) {
                case -1: {
                    //  Error 11: "()" applied to non-function variable
                    OutputSemanticErrorMsg(11, id->lineno, "\"()\" applied to a non-function variable");
                    break;
                }
                case 0: {
                    //  Error 2: undefined function
                    char* error_msg = (char*)malloc(kErrorMsgLen);
                    sprintf(error_msg, "Undefined function \"%s\"", id->val.ValString);
                    OutputSemanticErrorMsg(2, id->lineno, error_msg);
                    free(error_msg);
                    break;
                }
                case 1: {
                    //  Error 9: function param inconsistent
                    char* error_msg = (char*)malloc(kErrorMsgLen);
                    sprintf(error_msg, "Function \"%s\" is not applicable to function call", id->val.ValString);
                    OutputSemanticErrorMsg(9, id->lineno, error_msg);
                    free(error_msg);    
                    break;
                }
                case 2: 
                    break;
            }
            return type_ret;
        }
    }

    if (exp->son->type == kINT || exp->son->type == kFLOAT) {
        Type type = (Type)malloc(sizeof(Type_));
        type->kind = kBASIC;
        type->u.basic = exp->son->type == kINT ? 0 : 1;
        return type;
    }

    if (CheckSymbolName(exp->son, "Exp")) {
        TreeNode* exp_1 = exp->son;
        if (CheckSymbolName(exp_1->bro, "ASSIGNOP")) {
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
                //  Error 5: type mismatch
                OutputSemanticErrorMsg(5, exp_1->lineno, "Type mismatched for assignment");
            }
            return type_l;
        }
        if (CheckSymbolName(exp_1->bro, "LB")) {
            Type type_base = ProcessExp(exp_1),
                type_idx = ProcessExp(exp_1->bro->bro);
            if (type_base->kind != kARRAY) {
                //  Error 10: [ ] applied to a non-array variable
                OutputSemanticErrorMsg(10, exp_1->son->lineno, "[] applied to non-array variable");
                return NULL;
            } else {
                //  TODO: test a[2][3][4]
                return type_base->u.array.elem;
            }
            if (!(type_idx->kind == kBASIC && type_idx->u.basic == 0)) {
                //  Error 12: array index not an integer
                OutputSemanticErrorMsg(12, exp_1->bro->bro->lineno, "Array index not an integer");
                return NULL;
            }
        }
        if (CheckSymbolName(exp_1->bro, "DOT")) {
            Type type_base = ProcessExp(exp_1);
            if (!type_base || type_base->kind != kSTRUCTURE) {
                //  Error 13: "." applied to a non-struct variable
                OutputSemanticErrorMsg(13, exp_1->lineno, "\".\" applied to a non-struct variable");
                return NULL;
            }
            TreeNode* id = exp_1->bro->bro;
            assert(id->type == kID);

            Type type = NULL;
            //  TODO: think about a.b.c.e
            if (!LookupFieldInStruct(id->val.ValString, type_base, &type)) {
                //  Error 14: non-existent filed
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "Non-existent field \"%s\"", id->val.ValString);
                OutputSemanticErrorMsg(14, id->lineno, error_msg);
                free(error_msg);
                return NULL;
            }
            return type;
        }
        Type type_l = ProcessExp(exp_1),
            type_r = ProcessExp(exp_1->bro->bro);

        if (!TypeConsistentBasic(type_l, type_r)) {
            //  Error 7: type mismatch
            OutputSemanticErrorMsg(7, exp_1->lineno, "Type mismatched for operands");
            return NULL;
        }
        return type_l;  
    } 
    
    ProcessExp(exp->son->bro);
}

Type AnalyzeDec(TreeNode* dec, char** name, Type type) {
    Type type_comp = AnalyzeVarDec(dec->son, name, type);
    if (!dec->son->bro) return type_comp;
    ProcessExp(dec->son->bro->bro);
}

void AddCompStDefToCompStDefList(const char* name, CompStDefList comp_st_def_list) {
    CompStDefList comp_st_def = (CompStDefList)malloc(sizeof(CompStDefList_));
    comp_st_def->name = name;
    comp_st_def->tail = comp_st_def_list;
    comp_st_def_list = comp_st_def;
}

void ProcessDecList(TreeNode* dec_list, Type type, CompStDefList comp_st_def_list) {
    while (1) {
        char* name;
        Type type_comp = AnalyzeDec(dec_list->son, &name, type);
        if (LookupVariable(name, NULL, layer, kVariableDefine) == 1) {
            //  Error 3: redefinition in variable
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "Redefined variable \"%s\"", name);
            OutputSemanticErrorMsg(3, dec_list->son->lineno, error_msg);
            free(error_msg);
        } else {
            //  add to symbol table
            insert(name, type_comp, layer);
        }

        AddCompStDefToCompStDefList(name, comp_st_def_list);

        if (!dec_list->son->bro) return;
        dec_list = dec_list->son->bro->bro;
    }
}

void ProcessDef(TreeNode* def, CompStDefList comp_st_def_list) {
    Type type = GetType(def->son);
    return ProcessDecList(def->son->bro, type, comp_st_def_list);    
}

void ProcessDefList(TreeNode* def_list, CompStDefList comp_st_def_list) {
    if (!def_list) return;

    while (1) {
        ProcessDef(def_list->son, comp_st_def_list);
        def_list = def_list->son->bro;
        if (!def_list) return;
    }
}

void ProcessStmt(TreeNode* stmt, Type type_ret_func) {
    if (CheckSymbolName(stmt->son, "Exp")) {
        ProcessExp(stmt->son);
        return;
    }
    if (CheckSymbolName(stmt->son, "CompSt")) {
        ProcessCompSt(stmt->son, type_ret_func);
        return;
    }
    if (CheckSymbolName(stmt->son, "IF")) {
        TreeNode* exp = stmt->son->bro->bro,
                * stmt_1 = exp->bro->bro;
        ProcessExp(exp);
        ProcessStmt(stmt_1, type_ret_func);
        if (stmt_1->bro) {
            TreeNode* stmt_2 = stmt_1->bro->bro;
            ProcessStmt(stmt_2, type_ret_func);
        }
        return;
    }
    //  TODO: what if no return?
    if (CheckSymbolName(stmt->son, "RETURN")) {
        Type type_ret_stmt = ProcessExp(stmt->son->bro);
        if (!TypeConsistent(type_ret_func, type_ret_stmt)) {
            //  Error 8: return type misamtch
            OutputSemanticErrorMsg(8, stmt->son->bro->lineno, "Type mismatched for return");
        }
        return;
    }
    assert(CheckSymbolName(stmt->son, "WHILE"));
    TreeNode* exp = stmt->son->bro->bro,
            * stmt_1 = exp->bro->bro;
    ProcessExp(exp);
    ProcessStmt(stmt_1, type_ret_func);
}

void ProcessStmtList(TreeNode* stmt_list, Type type_ret) {
    while (1) {
        if (!stmt_list) return;
        ProcessStmt(stmt_list->son, type_ret);
        stmt_list = stmt_list->son->bro;
    }
}

void RemoveCompStDef(CompStDefList comp_st_def_list) {
    while (1) {
        if (!comp_st_def_list) return;
        RemoveVariable(comp_st_def_list->name, layer);
        CompStDefList pre_comp_st_def = comp_st_def_list;
        comp_st_def_list = comp_st_def_list->tail;
        free(pre_comp_st_def);
    }
}

void ProcessCompSt(TreeNode* comp_st, Type type_ret) {
    ++layer;
    TreeNode* def_list = NULL,
            * stmt_list = NULL;
    if (CheckSymbolName(comp_st->son->bro, "DefList")) {
        def_list = comp_st->son->bro;
        if (CheckSymbolName(def_list->bro, "StmtList")) {
            stmt_list = def_list->bro;
        }
    } else if (CheckSymbolName(comp_st->son->bro, "StmtList")) {
        stmt_list = comp_st->son->bro;
    }

    CompStDefList comp_st_def_list = NULL;
    ProcessDefList(def_list, comp_st_def_list);
    // puts("def_list");
    ProcessStmtList(stmt_list, type_ret);
    // puts("stmt_list");
    RemoveCompStDef(comp_st_def_list);
    // puts("remove");
    --layer;
}

void AddFormalParameterToSymbolTable(ParamList param_list) {
    ++layer;
    while (1) {
        if (!param_list) {
            --layer;
            return;
        }
        insert(param_list->name, param_list->type, layer);
        param_list = param_list->tail;
    }
}

void RemoveFormalParameterFromSymbolTable(ParamList param_list) {
    ++layer;
    while (1) {
        if (!param_list) {
            --layer;
            return;
        }
        RemoveVariable(param_list->name, layer);
        param_list = param_list->tail;
    }
}

void ProcessFunDef(TreeNode* fun_def, Type type_ret) {
    Type type = GetTypeFunction(fun_def, type_ret);
    switch (LookupFunction(type->u.function.name, &type_ret, type->u.function.param_list, kDEFINE)) {
        case -1: {
            //  TODO: which type?
            //  Error -1: function name conflict with variable name
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "function \"%s\" has been defined as another variable", type->u.function.name);
            OutputSemanticErrorMsg(-1, fun_def->lineno, error_msg);
            free(error_msg);
            break;
        }
        case 0: //  function neither defined nor declared
            type->u.function.defined = 1;
            insert(type->u.function.name, type, layer);
            break;
        case 1: {//  Error 19, multiple definition
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "multiple definition of function \"%s\"", type->u.function.name);
            OutputSemanticErrorMsg(19, fun_def->lineno, error_msg);
            free(error_msg);
            break;
        }
        case 2: {//  Error 19, type conflict
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "Inconsistent declaration/definition of function \"%s\"", type->u.function.name);
            OutputSemanticErrorMsg(19, fun_def->lineno, error_msg);
            free(error_msg);
            break;
        }
        case 3: //  function already declared but not yet defined
            UpdateFunctionStatus(type->u.function.name);
            break;
    }

    //  add formal parameter to symbol table
    AddFormalParameterToSymbolTable(type->u.function.param_list);
    TreeNode* comp_st = fun_def->bro;
    ProcessCompSt(comp_st, type_ret);
    //  remove formal parameter from symbol table
    RemoveFormalParameterFromSymbolTable(type->u.function.param_list);
}

void AddFuncToFunctionList(const char* name, int lineno) {
    FunctionList function = (FunctionList)malloc(sizeof(FunctionList_));
    function->name = name;
    function->lineno = lineno;
    function->tail = function_list;
    function_list = function;
}

void ProcessFunDec(TreeNode* fun_def, Type type_ret) {
    Type type = GetTypeFunction(fun_def, type_ret);
    switch (LookupFunction(type->u.function.name, &type_ret, type->u.function.param_list, kDECLARE)) {
        case -1: {
            //  TODO: which type?
            //  Error -1: function name conflict with variable name
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "function \"%s\" has been defined as another variable", type->u.function.name);
            OutputSemanticErrorMsg(-1, fun_def->lineno, error_msg);
            free(error_msg);
            break;
        }
        case 0: //  neither defined nor declared
            type->u.function.defined = 0;
            insert(type->u.function.name, type, layer);
            break;
        case 2: {//  Error 19, type conflict
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "Inconsistent declaration/definition of function \"%s\"", type->u.function.name);
            OutputSemanticErrorMsg(19, fun_def->lineno, error_msg);
            free(error_msg);
            break;
        }
        case 3:
            break;
    }
    AddFuncToFunctionList(type->u.function.name, fun_def->lineno);
}

void AnalyzeExtDef(TreeNode* ext_def) {
    TreeNode* specifier = ext_def->son;
    Type type = GetType(specifier);
    TreeNode* next = specifier->bro;

    if (CheckSymbolName(next, "SEMI")) {
        //  3. check type consistent in semantic or symbol table (function)?
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
            *name = var_dec->son->val.ValString;
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
    if (LookupVariable(name, NULL, layer, kVariableDefine) == 1) {
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
        if (LookupStruct(type->u.structure.name, NULL, layer, kStructDefine)) {  /*  redefinition of struct  */
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "Duplicated name \"%s\"", type->u.structure.name);
            OutputSemanticErrorMsg(16, tag->lineno, error_msg);
            free(error_msg);
        } else {
            insert(type->u.structure.name, type, layer);
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