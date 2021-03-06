#include "../header/translate.h"

#include "../header/tree.h"
#include "../header/type.h"
#include "../header/SymbolTable.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern int layer;
extern InterCodeIterator iter;
extern int temp_no;
extern int in_fundef;
extern FILE* stream;

void TranslateAssign(Operand* dst_op, Operand src_op);

void TranslateDereference(enum DereferenceType dereference_type,
                        Operand* op_dst, Operand op_src);

Operand ArithCalc(BinOpType bin_op_type, Operand op_1, Operand op_2) {
    Operand op_res = (Operand)malloc(sizeof(Operand_));
    op_res->kind = op_1->kind;
    if (op_res->kind == kConstantInt) {
        switch (bin_op_type) {
            case kArithAdd:
                op_res->u.int_value = op_1->u.int_value + op_2->u.int_value;
                break;
            case kArithSub:
                op_res->u.int_value = op_1->u.int_value - op_2->u.int_value;
                break;
            case kArithMul:
                op_res->u.int_value = op_1->u.int_value * op_2->u.int_value;
                break;
            case kArithDiv:
                op_res->u.int_value = op_1->u.int_value / op_2->u.int_value;
        }
    } else {
        switch (bin_op_type) {
            case kArithAdd:
                op_res->u.float_value = op_1->u.float_value + op_2->u.float_value;
                break;
            case kArithSub:
                op_res->u.float_value = op_1->u.float_value - op_2->u.float_value;
                break;
            case kArithMul:
                op_res->u.float_value = op_1->u.float_value * op_2->u.float_value;
                break;
            case kArithDiv:
                op_res->u.float_value = op_1->u.float_value / op_2->u.float_value;
        }
    }
    return op_res;
}

void TranslateParam(const char* name) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kParam;
    Operand op_param;
    int lookup_status = LookupVariable(name, NULL, layer, 
                                    kVariableDeclare, &op_param);
    assert(lookup_status == 1);                                    
    code->u.param.op = op_param;
    AddCodeToCodes(code);
}

void TranslateFunDef(const char* name, DefList param_list) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kFunction;
    code->u.function.func_name = name;
    AddCodeToCodes(code);

    while (1) {
        if (!param_list) {
            --layer;
            in_fundef = 0;
            return;
        }
        TranslateParam(param_list->name);
        param_list = param_list->tail;
    }
}

void TranslateAssign(Operand* dst_op, Operand src_op) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kAssign;
    code->u.assign.op_left = *dst_op;
    code->u.assign.op_right = src_op;
    AddCodeToCodes(code);
}

void TranslateAddressOf(Operand dst_op, Operand src_op) {
    if (!dst_op) return;
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kAddressOf;
    code->u.address_of.op_left = dst_op;
    code->u.address_of.op_right = src_op;
    AddCodeToCodes(code);
}

void TranslateArg(Operand op) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kArg;
    code->u.arg.op = op;
    AddCodeToCodes(code);
}

void TranslateFunCall(Operand* dst_op, const char* name) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kCall;
    code->u.call.func_name = name;
    code->u.call.op_result = dst_op ? *dst_op : NewOperandTemporary();
    AddCodeToCodes(code);
}

void TranslateRead(Operand* op_dst) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kIO;
    code->u.io.type = kRead;
    code->u.io.op = *op_dst;
    AddCodeToCodes(code);
}

void TranslateWrite(Operand* op_dst) {
    InterCode code = iter->end->code;
    code->kind = kIO;
    code->u.io.type = kWrite;
}

void TranslateAssignOrReplace(Operand* op_dst, Operand op_src) {
    if (!op_dst) return;
    if ((*op_dst)->kind == kTemporary && (*op_dst)->u.temp_no == 39) {
        fprintf(stream, "qaq");
        OutputOperand(*op_dst, 0);
        OutputOperand(op_src, 0);
        fprintf(stream, "\n");
        TranslateAssign(op_dst, op_src);
    }
    if ((*op_dst)->kind == kVariable
        || (*op_dst)->kind == kTemporaryPointer
        || (*op_dst)->kind == kVariablePointer) {
        //  assign
        TranslateAssign(op_dst, op_src);
    } else {    /*  == kTemporary   */
        //  change 
        TranslateReplace(op_dst, op_src);
    }
}

void TranslateRightDereferenceOrReplace(Operand* op_dst, Operand op_src) {
    if ((*op_dst)->kind == kVariable) {
        //  assign
        TranslateDereference(kRightDereference, op_dst, op_src);
    } else {    /*  == kTemporary   */
        //  change 

        TranslateReplacePointer(op_dst, op_src);
    }
}

void swap(Operand* op_1, Operand* op_2) {
    Operand temp = *op_1;
    *op_1 = *op_2;
    *op_2 = temp;
}

void SwapOperandType(OperandType* type_1, OperandType* type_2) {
    OperandType temp = *type_1;
    *type_1 = *type_2;
    *type_2 = temp;
}

void TranslateBinOpType(BinOpType bin_op_type, Operand* op_result, Operand op_l, Operand op_r) {
    if (!op_result) return;
    if ((op_l->kind == kConstantInt && op_r->kind == kConstantInt)
        || (op_l->kind == kConstantFloat && op_r->kind == kConstantFloat)) {
        Operand op_res = ArithCalc(bin_op_type, op_l, op_r);
        TranslateAssignOrReplace(op_result, op_res);
        return;
    }
    if (op_l->kind == kConstantInt || op_r->kind == kConstantInt) {
        switch(bin_op_type) {
            case kArithAdd:
            case kArithMul:
                if (op_r->kind == kConstantInt) swap(&op_l, &op_r);
                assert(op_l->kind == kConstantInt);
                if ((bin_op_type == kArithAdd && op_l->u.int_value == 0)) {
                    //|| (bin_op_type == kArithMul && op_l->u.int_value == 1)) {
                    TranslateAssignOrReplace(op_result, op_r);
                    return;
                }
                if (bin_op_type == kArithMul && op_l->u.int_value == 0) {
                    TranslateAssignOrReplace(op_result, 
                                            NewOperandConstantInt(0));
                    return;
                }
                break;
            case kArithSub:
                if (op_r->kind == kConstantInt && op_r->u.int_value == 0) {
                    TranslateAssignOrReplace(op_result, op_l);
                    return;
                }
                break;
            case kArithDiv:
                if (op_l->kind == kConstantInt && op_l->u.int_value == 0) {
                    TranslateAssignOrReplace(op_result, 
                                            NewOperandConstantInt(0));
                    return;
                }
                if (op_r->kind == kConstantInt && op_r->u.int_value == 1) {
                    TranslateAssignOrReplace(op_result, op_l);
                    return;
                }
                break;
        }
    }
    if (op_l->kind == kConstantFloat || op_r->kind == kConstantFloat) {
        switch(bin_op_type) {
            case kArithAdd:
            case kArithMul:
                if (op_r->kind == kConstantFloat) swap(&op_l, &op_r);
                if ((bin_op_type == kArithAdd && op_l->u.float_value == 0)
                    || (bin_op_type == kArithMul && op_l->u.float_value == 1)) {
                    TranslateAssignOrReplace(op_result, op_r);
                    return;
                }
                if (bin_op_type == kArithMul && op_l->u.float_value == 0) {
                    TranslateAssignOrReplace(op_result, 
                                            NewOperandConstantFloat(0));
                    return;
                }
                break;
            case kArithSub:
                if (op_r->kind == kConstantFloat && op_r->u.float_value == 0) {
                    TranslateAssignOrReplace(op_result, op_l);
                    return;
                }
                break;
            case kArithDiv:
                if (op_l->kind == kConstantFloat && op_l->u.float_value == 0) {
                    TranslateAssignOrReplace(op_result, 
                                            NewOperandConstantFloat(0));
                    return;
                }
                if (op_r->kind == kConstantFloat && op_r->u.float_value == 1) {
                    TranslateAssignOrReplace(op_result, op_l);
                    return;
                }
                break;
        }
    }
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kBinOp;
    code->u.bin_op.type = bin_op_type;
    code->u.bin_op.op_result = *op_result;
    code->u.bin_op.op_1 = op_l;
    code->u.bin_op.op_2 = op_r;
    AddCodeToCodes(code);
}

void TranslateBinOp(TreeNode* bin_op, Operand* op_result, Operand op_l, Operand op_r) {
    if (!op_result) return;
    BinOpType bin_op_type;
    if (bin_op->type = kSYMBOL) {
        if (strcmp(bin_op->val.ValString, "PLUS") == 0) {
            bin_op_type = kArithAdd;
        } else if (strcmp(bin_op->val.ValString, "MINUS") == 0) {
            bin_op_type = kArithSub;
        } else if (strcmp(bin_op->val.ValString, "STAR") == 0) {
            bin_op_type = kArithMul;
        } else if (strcmp(bin_op->val.ValString, "DIV") == 0) {
            bin_op_type = kArithDiv;
        }
    }
    TranslateBinOpType(bin_op_type, op_result, op_l, op_r);
}

Type TranslateCond(TreeNode* exp, Operand label_true, Operand label_false) {
    TreeNode* exp_1 = exp->son;
    if (exp_1->type == kSYMBOL && strcmp(exp_1->val.ValString, "NOT") == 0) {
        return TranslateCond(exp_1->bro, label_false, label_true);
    }
    if (!exp_1->bro 
        || (exp_1->bro->type != kRELOP 
            && !CheckSymbolName(exp_1->bro, "AND")
            && !CheckSymbolName(exp_1->bro, "OR"))) {
        Operand op = NewOperandVariable();
        TranslateDeclare(op, 4);
        MoveDeclareForward();
        Type type = ProcessExp(exp, &op);
        TranslateConditionalJump(op, NewOperandConstantInt(0), label_true, kNE);
        TranslateGoto(label_false);
        return type;
    }
    TreeNode* op = exp_1->bro,
            * exp_2 = op->bro;
    if (op->type == kRELOP) {
        Operand op_1 = NewOperandTemporary();
        Type type_1 = ProcessExp(exp_1, &op_1);
        Operand op_2 = NewOperandTemporary();
        Type type_2 = ProcessExp(exp_2, &op_2);

        if (!TypeConsistentBasic(type_1, type_2)) {
            //  Error 7: type mismatch
            OutputSemanticErrorMsg(7, exp_1->lineno, "Type mismatched for operands");
            return NULL;
        } else {
            TranslateConditionalJump(op_1, op_2, label_true, op->val.ValRelop);
            TranslateGoto(label_false);
            return NewTypeBasic(0);
        }
    }
    if (CheckSymbolName(op, "AND")) {
        Operand label_1 = NewOperandLabel();
        Type type_1 = TranslateCond(exp_1, label_1, label_false);
        TranslateLabel(label_1);
        Type type_2 = TranslateCond(exp_2, label_true, label_false);

        if (!TypeConsistentBasic(type_1, type_2)) {
            //  Error 7: type mismatch
            OutputSemanticErrorMsg(7, exp_1->lineno, "Type mismatched for operands");
            return NULL;
        } else {
            return type_1;
        }
    }
    if (CheckSymbolName(op, "OR")) {
        Operand label_1 = NewOperandLabel();
        Type type_1 = TranslateCond(exp_1, label_true, label_1);
        TranslateLabel(label_1);
        Type type_2 = TranslateCond(exp_2, label_true, label_false);

        if (!TypeConsistentBasic(type_1, type_2)) {
            //  Error 7: type mismatch
            OutputSemanticErrorMsg(7, exp_1->lineno, "Type mismatched for operands");
            return NULL;
        } else {
            return type_1;
        }
    }
    assert(0);
}

void TranslateLabel(Operand label) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kLabel;
    code->u.label.op = label;
    AddCodeToCodes(code);
}

extern FILE* stream;

void TranslateConditionalJump(Operand op_1, Operand op_2, Operand op_label, RelopType relop_type) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kConditionalJump;
    code->u.conditional_jump.op_1 = op_1;
    code->u.conditional_jump.op_2 = op_2;
    code->u.conditional_jump.op_label = op_label;
    code->u.conditional_jump.relop_type = relop_type;
    AddCodeToCodes(code);
}

void TranslateGoto(Operand op_label) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kGoto;
    code->u.go_to.op = op_label;
    AddCodeToCodes(code);
}

void TranslateReturn(Operand op) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kReturn;
    code->u.ret.op = op;
    AddCodeToCodes(code);
}

void TranslateReplace(Operand* op_dst, Operand op_src) {
    *op_dst = op_src;
}

void TranslateReplacePointer(Operand* op_dst, Operand op_src) {
    // TODO: consider the problem of pointer
    if (!op_dst) return;
    switch (op_src->kind) {
        case kVariable:
        case kTemporary:
            *op_dst = ToOperandPointer(op_src);
            break;
        case kVariableAddress:
            *op_dst = ToOperandVariable(op_src);
            break;
        default:
            assert(0);
    }
}

void TranslateFunEnd() {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kFunEnd;
    AddCodeToCodes(code);
}

void TranslateDereference(enum DereferenceType dereference_type,
                        Operand* op_dst, Operand op_src) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kDereference;
    code->u.dereference.type = dereference_type;
    code->u.dereference.op_left = *op_dst;
    code->u.dereference.op_right = op_src;
    AddCodeToCodes(code);
}

void TranslateDeclare(Operand op, int size) {
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kDeclare;
    code->u.declare.op = op;
    code->u.declare.size = size;
    AddCodeToCodes(code);
}