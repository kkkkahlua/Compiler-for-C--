#include "semantic.h"

#include "FinalCode.h"
#include "InterCode.h"
#include "optimize.h"
#include "SymbolTable.h"
#include "translate.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int layer = 0;
int in_fundef = 0;
int error_semantic = 0;
const int kErrorMsgLen = 100;
FunctionList function_list = NULL;
InterCodeIterator iter = NULL;

DefList FillDefIntoDefList(TreeNode* def, int offset);

int CheckSymbolName(TreeNode* node, const char* name) {
    return node->type != kRELOP && strcmp(node->val.ValString, name) == 0;
}

void AddIOToSymbolTable();
void CheckFunctionDefinition();

void ProcessProgram(TreeNode* root) {
    AddIOToSymbolTable();
    iter = (InterCodeIterator)malloc(sizeof(InterCodeIterator_));
    iter->begin = iter->end = NULL;
    iter->next = NULL;
    ProcessExtDefList(root->son);
    CheckFunctionDefinition();
    if (!error_semantic) {
        optimize(iter->begin);
        OutputInterCodes(iter->begin, 0);
        // ConstructBasicBlock(iter->begin);
        GenerateFinalCode(iter->begin);
    }
}

void ProcessExtDefList(TreeNode* ext_def_list) {
    while (1) {
        ProcessExtDef(ext_def_list->son);
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
        Type type_comp = ProcessVarDec(ext_dec_list->son, &name, type);

        if (LookupVariable(name, NULL, layer, kVariableDefine, NULL) == 1) {
            //  Error 3: redefinition in global variable
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "Redefined variable \"%s\"", name);
            OutputSemanticErrorMsg(3, ext_dec_list->son->lineno, error_msg);
            free(error_msg);
        } else {
            //  add to symbol table
            insert(name, type_comp);
        }

        if (!ext_dec_list->son->bro) return;
        ext_dec_list = ext_dec_list->son->bro->bro;
    }
}

DefList ProcessParamDec(TreeNode* param_dec) {
    TreeNode* specifier = param_dec->son;
    assert(CheckSymbolName(specifier, "Specifier"));
    TreeNode* var_dec = specifier->bro;
    assert(CheckSymbolName(var_dec, "VarDec"));

    Type type = GetType(specifier);
    char* name = NULL;
    Type type_comp = ProcessVarDec(var_dec, &name, type);
   
    DefList param = (DefList)malloc(sizeof(DefList_));
    param->name = name;
    param->type = type_comp;
    param->tail = NULL;
    return param;
}

DefList GetVarList(TreeNode* var_list) {
    DefList param_list = ProcessParamDec(var_list->son),
            pre_param = param_list;
    while (1) {
        if (!var_list->son->bro) return param_list;
        var_list = var_list->son->bro->bro;

        DefList cur_param = ProcessParamDec(var_list->son);
        pre_param->tail = cur_param;
        pre_param = cur_param;
    };
}

DefList FillArgIntoParam(TreeNode* exp) {
    DefList param = (DefList)malloc(sizeof(DefList_));
    Operand op = NewOperandTemporary();
    param->type = ProcessExp(exp, &op);
    switch (param->type->kind) {
        case kBASIC: TranslateArg(op); break;
        case kSTRUCTURE:
        case kARRAY: 
            switch (op->kind) {
                case kTemporary:
                case kVariable:
                    TranslateArg(ToOperandAddress(op));
                    break;
                case kTemporaryPointer:
                case kVariablePointer:
                    TranslateArg(ToOperand(op));
                    break;
                default:
                    assert(0);
            }
    }
    param->tail = NULL;
    return param;
}

DefList FillArgsIntoDefList(TreeNode* args) {
    if (!args->son->bro) {
        return FillArgIntoParam(args->son);
    }
    DefList param_list = FillArgsIntoDefList(args->son->bro->bro);
    DefList param = FillArgIntoParam(args->son);
    param->tail = param_list;
    return param;
}

int CheckLvalue(TreeNode* exp) {
    return (exp->son->type == kID && !exp->son->bro) ||
        (exp->son->bro && (CheckSymbolName(exp->son->bro, "LB")
                        || CheckSymbolName(exp->son->bro, "DOT")));
}

Type ProcessCond(TreeNode* exp, Operand* op_dst) {
    Operand label_true = NewOperandLabel(),
            label_false = NewOperandLabel();
    TranslateAssignOrReplace(op_dst, NewOperandConstantInt(0));
    Type type = TranslateCond(exp, label_true, label_false);
    TranslateLabel(label_true);
    TranslateAssignOrReplace(op_dst, NewOperandConstantInt(1));
    TranslateLabel(label_false);
    return type;    
}

Type ProcessExp(TreeNode* exp, Operand* op_dst) {
    if (exp->son->type == kID) {
        TreeNode* id = exp->son;
        if (!id->bro) {   /*  Exp -> ID   */
            Type type = NULL;

            Operand id_op;
            if (!LookupVariable(exp->son->val.ValString, &type, 
                                layer, kVariableUse, &id_op)) {
                //  Error 1: undefined variable
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "Undefined variable \"%s\"", id->val.ValString);
                OutputSemanticErrorMsg(1, id->lineno, error_msg);
                free(error_msg);
            } else {
                //  translate id
                TranslateReplace(op_dst, id_op);
            }
            return type;
        } else {        /*  function call   */
            DefList param_list = NULL;
            if (CheckSymbolName(id->bro->bro, "Args")) {
                param_list = FillArgsIntoDefList(id->bro->bro);
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
                case 2: {
                    if (strcmp(id->val.ValString, "read") == 0) {
                        TranslateRead(op_dst);
                    } else if (strcmp(id->val.ValString, "write") == 0) {
                        TranslateWrite();
                    } else {
                        TranslateFunCall(op_dst, id->val.ValString);
                    }
                }
            }
            return type_ret;
        }
    }

    if (exp->son->type == kINT || exp->son->type == kFLOAT) {
        Type type = (Type)malloc(sizeof(Type_));
        type->kind = kBASIC;

        type->u.basic = exp->son->type == kINT ? 0 : 1;

        Operand op = exp->son->type == kINT
                    ? NewOperandConstantInt(exp->son->val.ValInt)
                    : NewOperandConstantFloat(exp->son->val.ValFloat);

        TranslateAssignOrReplace(op_dst, op);
        return type;
    }

    if (CheckSymbolName(exp->son, "Exp")) {
        TreeNode* exp_1 = exp->son;
        if (CheckSymbolName(exp_1->bro, "ASSIGNOP")) {
            //  EXP -> EXP ASSIGNOP EXP
            if (!CheckLvalue(exp_1)) {
                //  Error 6: rvalue on the left-hand side of an assignment
                OutputSemanticErrorMsg(6, exp_1->lineno, "The left-hand side of an assignment must be a variable");
            }

            Operand op_r = NewOperandTemporary();
            Type type_r = ProcessExp(exp_1->bro->bro, &op_r);
            
            Operand op_l = NewOperandTemporary();
            Type type_l = ProcessExp(exp_1, &op_l);

            if (!TypeConsistent(type_r, type_l)) {
                //  Error 5: type mismatch
                OutputSemanticErrorMsg(5, exp_1->lineno, "Type mismatched for assignment");
                return NULL;
            }

            TranslateAssignOrReplace(&op_l, op_r);
            TranslateAssignOrReplace(op_dst, op_l);

            return type_l;
        }
        if (CheckSymbolName(exp_1->bro, "LB")) {
            //  EXP -> EXP LB EXP RB
            Operand op_base_ptr = NewOperandTemporaryPointer();
            Type type_base = ProcessExp(exp_1, &op_base_ptr);

            Operand op_idx = NewOperandTemporary();
            Type type_idx = ProcessExp(exp_1->bro->bro, &op_idx);

            Type type_ret = NULL;

            if (type_base->kind != kARRAY) {
                //  Error 10: [ ] applied to a non-array variable
                OutputSemanticErrorMsg(10, exp_1->son->lineno, "[] applied to non-array variable");
            } else {
                type_ret = type_base->u.array.elem;
            }
            if (!(type_idx->kind == kBASIC && type_idx->u.basic == 0)) {
                //  Error 12: array index not an integer
                OutputSemanticErrorMsg(12, exp_1->bro->bro->lineno, "Array index not an integer");
            } else if (type_ret) {
                Operand op_offset = NewOperandTemporary();
                TranslateBinOpType(
                    kArithMul, &op_offset, op_idx, 
                    NewOperandConstantInt(type_base->u.array.space)
                );

                Operand op_base;

                switch (op_base_ptr->kind) {
                    case kTemporary:
                        op_base = ToOperandTemporaryAddress(op_base_ptr);
                    case kTemporaryPointer:
                        op_base = ToOperandTemporary(op_base_ptr);
                        break;
                    case kVariable:
                        op_base = ToOperandVariableAddress(op_base_ptr);
                        break;
                    case kVariablePointer:
                        op_base = ToOperandVariable(op_base_ptr);
                }

                Operand op_dst_temp = ToOperandTemporary(*op_dst);
                TranslateBinOpType(kArithAdd, &op_dst_temp,
                                    op_base, op_offset);

                if ((*op_dst)->kind != kTemporaryPointer) {
                    if (op_dst_temp->kind == kTemporary
                        || op_dst_temp->kind == kVariable) {
                        *op_dst = ToOperandPointer(op_dst_temp);
                    } else {
                        *op_dst = ToOperand(op_dst_temp);
                    }
                }

            }
            
            return type_ret;
        }
        if (CheckSymbolName(exp_1->bro, "DOT")) {
            //  EXP -> EXP DOT ID
            Operand op_base = NewOperandTemporary();
            Type type_base = ProcessExp(exp_1, &op_base);
            if (!type_base || type_base->kind != kSTRUCTURE) {
                //  Error 13: "." applied to a non-struct variable
                OutputSemanticErrorMsg(13, exp_1->lineno, "\".\" applied to a non-struct variable");
                return NULL;
            }
            TreeNode* id = exp_1->bro->bro;
            assert(id->type == kID);

            Type type = NULL;
            int offset;
            if (!LookupFieldInStruct(
                    id->val.ValString, type_base, &type, &offset)) {
                //  Error 14: non-existent filed
                char* error_msg = (char*)malloc(kErrorMsgLen);
                sprintf(error_msg, "Non-existent field \"%s\"", id->val.ValString);
                OutputSemanticErrorMsg(14, id->lineno, error_msg);
                free(error_msg);
                return NULL;
            } else {
                Operand op_addr = NewOperandTemporary();
                //  TODO: verify the correctness of the assumption
                //  type of op_base is either variable or variable_pointer

                // take value
                switch (op_base->kind) {
                    case kVariablePointer: 
                        op_base = ToOperandVariable(op_base);
                        break;
                    case kVariable:
                        op_base = ToOperandVariableAddress(op_base);
                        break;
                    default:
                        op_base = ToOperandTemporary(op_base);
                        break;
                }
                TranslateBinOpType(kArithAdd, &op_addr, op_base, 
                                        NewOperandConstantInt(offset));
                TranslateRightDereferenceOrReplace(op_dst, op_addr);
            }
            return type;
        }
        if (exp_1->bro->type == kRELOP
            || CheckSymbolName(exp_1->bro, "AND")
            || CheckSymbolName(exp_1->bro, "OR")) {
            //  EXP -> EXP AND EXP
            //      |  EXP OR EXP
            //      |  EXP RELOP EXP
            return ProcessCond(exp, op_dst);
        }

        //  EXP -> EXP BINOP EXP
        Operand op_l = NewOperandTemporary();
        Type type_l = ProcessExp(exp_1, &op_l);
        Operand op_r = NewOperandTemporary();
        Type type_r = ProcessExp(exp_1->bro->bro, &op_r);

        if (!TypeConsistentBasic(type_l, type_r)) {
            //  Error 7: type mismatch
            OutputSemanticErrorMsg(7, exp_1->lineno, "Type mismatched for operands");
            return NULL;
        }
        TranslateBinOp(exp_1->bro, op_dst, op_l, op_r);
        return type_l;
    } 
    
    if (CheckSymbolName(exp->son, "LP")) {
        //  EXP -> LP EXP RP
        return ProcessExp(exp->son->bro, op_dst);
    }

    if (CheckSymbolName(exp->son, "MINUS")) {
        //  EXP -> MINUS EXP
        Operand op = NewOperandTemporary();
        Type type = ProcessExp(exp->son->bro, &op);
        if (op->kind == kConstantInt || op->kind == kConstantFloat) {
            if (op->kind == kConstantInt) op->u.int_value = -op->u.int_value;
            else op->u.float_value = -op->u.float_value;
            TranslateAssignOrReplace(op_dst, op);
        } else {
            TranslateBinOpType(kArithSub, op_dst, NewOperandConstantInt(0), op);
        }
        return type;
    }

    //  EXP -> NOT EXP
    return ProcessCond(exp, op_dst);
}

Type ProcessDec(TreeNode* dec, char** name, Type type) {
    return ProcessVarDec(dec->son, name, type);
}

void AddCompStDefToDefList(const char* name, Type type, DefList* comp_st_def_list) {
    DefList comp_st_def = (DefList)malloc(sizeof(DefList_));
    comp_st_def->name = name;
    comp_st_def->type = type;
    comp_st_def->tail = *comp_st_def_list;
    *comp_st_def_list = comp_st_def;
}

void ProcessDecList(TreeNode* dec_list, Type type, DefList* comp_st_def_list) {
    while (1) {
        char* name;

        TreeNode* dec = dec_list->son;
        Type type_comp = ProcessDec(dec, &name, type);

        if (LookupVariable(name, NULL, layer, kVariableDefine, NULL) == 1) {
            //  Error 3: redefinition in variable
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "Redefined variable \"%s\"", name);
            OutputSemanticErrorMsg(3, dec_list->son->lineno, error_msg);
            free(error_msg);
        } else {
            //  add to symbol table
            Operand op_dec = insert(name, type_comp);

            if (type_comp->kind == kARRAY) {
                TranslateDeclare(
                    op_dec, 
                    type_comp->u.array.size * type_comp->u.array.space
                );
            } else if (type_comp->kind == kSTRUCTURE) {
                TranslateDeclare(op_dec, type_comp->u.structure.space);
            }

            AddCompStDefToDefList(name, type_comp, comp_st_def_list);

            if (dec->son->bro) {
                Operand op_temp = NewOperandTemporary();
                Type type_r = ProcessExp(dec->son->bro->bro, &op_temp);

                if (!TypeConsistent(type_r, type_comp)) {
                    //  Error 5: type mismatch for assignment
                    OutputSemanticErrorMsg(5, dec->lineno, "Type mismatched for assignment");
                }
                TranslateAssignOrReplace(&op_dec, op_temp);
            }
        }

        if (!dec_list->son->bro) return;
        dec_list = dec_list->son->bro->bro;
    }
}

void ProcessDef(TreeNode* def, DefList* comp_st_def_list) {
    Type type = GetType(def->son);
    return ProcessDecList(def->son->bro, type, comp_st_def_list);    
}

void ProcessDefList(TreeNode* def_list, DefList* comp_st_def_list) {
    if (!def_list) return;

    while (1) {
        ProcessDef(def_list->son, comp_st_def_list);
        def_list = def_list->son->bro;
        if (!def_list) return;
    }
}

void ProcessStmt(TreeNode* stmt, Type type_ret_func) {
    if (CheckSymbolName(stmt->son, "Exp")) {
        //  omit the assignment
        ProcessExp(stmt->son, NULL);
        return;
    }
    if (CheckSymbolName(stmt->son, "CompSt")) {
        ProcessCompSt(stmt->son, type_ret_func);
        return;
    }
    if (CheckSymbolName(stmt->son, "IF")) {
        TreeNode* exp = stmt->son->bro->bro,
                * stmt_1 = exp->bro->bro;
        Operand label_true = NewOperandLabel();
        Operand label_false = NewOperandLabel();
        TranslateCond(exp, label_true, label_false);
        TranslateLabel(label_true);
        ProcessStmt(stmt_1, type_ret_func);
        if (!stmt_1->bro) {
            TranslateLabel(label_false);
        } else {
            Operand label_end = NewOperandLabel();
            TranslateGoto(label_end);
            TranslateLabel(label_false);

            TreeNode* stmt_2 = stmt_1->bro->bro;
            ProcessStmt(stmt_2, type_ret_func);
            TranslateLabel(label_end);
        }
        return;
    }
    if (CheckSymbolName(stmt->son, "RETURN")) {
        Operand op_temp = NewOperandTemporary();
        Type type_ret_stmt = ProcessExp(stmt->son->bro, &op_temp);
        if (!TypeConsistent(type_ret_func, type_ret_stmt)) {
            //  Error 8: return type misamtch
            OutputSemanticErrorMsg(8, stmt->son->bro->lineno, "Type mismatched for return");
        } else {
            TranslateReturn(op_temp);
        }
        return;
    }

    assert(CheckSymbolName(stmt->son, "WHILE"));
    Operand label_begin = NewOperandLabel();
    TranslateLabel(label_begin);
    TreeNode* exp = stmt->son->bro->bro,
            * stmt_1 = exp->bro->bro;
    Operand label_true = NewOperandLabel(),
            label_false = NewOperandLabel();
    TranslateCond(exp, label_true, label_false);
    TranslateLabel(label_true);
    ProcessStmt(stmt_1, type_ret_func);
    TranslateGoto(label_begin);
    TranslateLabel(label_false);
}

void ProcessStmtList(TreeNode* stmt_list, Type type_ret) {
    while (1) {
        if (!stmt_list) return;
        ProcessStmt(stmt_list->son, type_ret);
        stmt_list = stmt_list->son->bro;
    }
}

void RemoveCompStDef(DefList comp_st_def_list) {
    while (1) {
        if (!comp_st_def_list) return;
        Remove(comp_st_def_list, layer);
        DefList pre_comp_st_def = comp_st_def_list;
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

    DefList comp_st_def_list = NULL;
    ProcessDefList(def_list, &comp_st_def_list);
    ProcessStmtList(stmt_list, type_ret);
    RemoveCompStDef(comp_st_def_list);
    --layer;
}

void AddFormalParameterToSymbolTable(DefList param_list) {
    ++layer;
    in_fundef = 1;
    while (1) {
        if (!param_list) {
            return;
        }
        insert(param_list->name, param_list->type);
        param_list = param_list->tail;
    }
}

void RemoveFormalParameterFromSymbolTable(DefList param_list) {
    ++layer;
    while (1) {
        if (!param_list) {
            --layer;
            return;
        }
        Remove(param_list, layer);
        param_list = param_list->tail;
    }
}

void AddIOToSymbolTable() {
    Type type_int = NewTypeBasic(0);

    insert("read",
            NewTypeFunction("read", type_int, NULL, 1));

    DefList param_list = (DefList)malloc(sizeof(DefList_));
    param_list->name = NewString("x");
    param_list->type = type_int;
    param_list->tail = NULL;
    insert("write",
            NewTypeFunction("write", type_int, param_list, 1));
}

void ProcessFunDef(TreeNode* fun_def, Type type_ret) {
    Type type = GetTypeFunction(fun_def, type_ret);
    switch (LookupFunction(type->u.function.name, &type_ret, type->u.function.param_list, kDEFINE)) {
        case -1: {
            //  Error 4: function name conflict with variable name
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "function name \"%s\" conflict with variable name", type->u.function.name);
            OutputSemanticErrorMsg(4, fun_def->lineno, error_msg);
            free(error_msg);
            break;
        }
        case 0: //  function neither defined nor declared
            type->u.function.defined = 1;
            insert(type->u.function.name, type);
            break;
        case 1: {//  Error 4: multiple definition
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "multiple definition of function \"%s\"", type->u.function.name);
            OutputSemanticErrorMsg(4, fun_def->lineno, error_msg);
            free(error_msg);
            break;
        }
        case 2: {//  Error 19: type conflict
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

    TranslateFunDef(type->u.function.name, type->u.function.param_list);

    TreeNode* comp_st = fun_def->bro;
    ProcessCompSt(comp_st, type_ret);
    //  remove formal parameter from symbol table
    RemoveFormalParameterFromSymbolTable(type->u.function.param_list);
    TranslateFunEnd();
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
            //  Error 4: function name conflict with variable name
            char* error_msg = (char*)malloc(kErrorMsgLen);
            sprintf(error_msg, "function name \"%s\" conflict with variable name", type->u.function.name);
            OutputSemanticErrorMsg(4, fun_def->lineno, error_msg);
            free(error_msg);
            break;
        }
        case 0: //  neither defined nor declared
            type->u.function.defined = 0;
            insert(type->u.function.name, type);
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

void ProcessExtDef(TreeNode* ext_def) {
    TreeNode* specifier = ext_def->son;
    Type type = GetType(specifier);
    TreeNode* next = specifier->bro;

    if (CheckSymbolName(next, "SEMI")) {
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

Type ProcessVarDec(TreeNode* var_dec, char** name, Type type_base) {
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
        type_comp->u.array.space = type_base->kind == kARRAY
                                    ? type_base->u.array.size * type_base->u.array.space
                                    : SizeOfType(type_base);
        type_comp->u.array.elem = type_base;

        var_dec = var_dec->son;
    }
}

DefList FillDecIntoField(TreeNode* dec, Type type, int offset) {
    char* name;
    Type type_comp = ProcessVarDec(dec->son, &name, type);

    //  Error 15: redefinition in struct field
    if (LookupVariable(name, NULL, layer, kVariableDefine, NULL) == 1) {
        char* error_msg = (char*)malloc(kErrorMsgLen);
        sprintf(error_msg, "Redefined field \"%s\"", name);
        OutputSemanticErrorMsg(15, dec->son->lineno, error_msg);
        free(error_msg);
    } else {
        insert(name, type_comp);
    }

    DefList field_list = (DefList)malloc(sizeof(DefList_));
    field_list->name = name;
    field_list->type = type_comp;
    field_list->offset = offset;
    field_list->tail = NULL;

    //  Error 15: assignment in sturct definition
    if (dec->son->bro) {
        OutputSemanticErrorMsg(15, dec->son->bro->lineno, "Assignment in struct definition");
    }
    return field_list;
}

DefList FillDecListIntoDefList(TreeNode* dec_list, Type type, int offset) {
    DefList field_list = FillDecIntoField(dec_list->son, type, offset),
            pre_field = field_list;
    offset += SizeOfType(field_list->type);
    while (1) {
        if (!dec_list->son->bro) return field_list;
        dec_list = dec_list->son->bro->bro;

        DefList cur_field = FillDecIntoField(dec_list->son, type, offset);
        offset += SizeOfType(cur_field->type);
        pre_field->tail = cur_field;
        pre_field = cur_field;
    };
}

DefList FillDefIntoDefList(TreeNode* def, int offset) {
    Type type = GetType(def->son);
    return FillDecListIntoDefList(def->son->bro, type, offset);
}

DefList LastField(DefList field_list) {
    DefList field = field_list;
    while (1) {
        DefList nxt_field = field->tail;
        if (!nxt_field) return field;
        field = nxt_field;
    }
}

DefList FillDefListIntoDefList(TreeNode* def_list, int* space) {
    if (!def_list) return NULL;

    DefList field_list = FillDefIntoDefList(def_list->son, 0),
            pre_field = LastField(field_list);
    while (1) {
        def_list = def_list->son->bro;
        if (!def_list) {
            *space = pre_field->offset + SizeOfType(pre_field->type);
            return field_list;
        }

        DefList cur_field = FillDefIntoDefList(
                                def_list->son, 
                                pre_field->offset + SizeOfType(pre_field->type)
                            );
        pre_field->tail = cur_field;
        pre_field = LastField(cur_field);
    }
}


void RemoveStructElement(Type type) {
    assert(type->kind == kSTRUCTURE);
    DefList field_list = type->u.structure.field_list;
    while (1) {
        if (!field_list) return;
        Remove(field_list, layer);
        field_list = field_list->tail;
    }
}

void OutputDefList(DefList def_list, int indent) {
    if (!def_list) return;
    for (int i = 0; i < indent; ++i) printf(" ");
    OutputType(def_list->type, indent);
    OutputDefList(def_list->tail, indent);
}

void OutputSemanticErrorMsg(int error_type, int lineno, const char* error_msg) {
    error_semantic = 1;
    printf("Error type %d at Line %d: %s.\n", error_type, lineno, error_msg);
}