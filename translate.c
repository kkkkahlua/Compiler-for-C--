#include "translate.h"

#include "type.h"
#include "SymbolTable.h"

extern int layer;

void TranslateFunDef(const char* name, DefList param_list) {
    ++layer;

    InterCode code;
    code->kind = kFunction;
    code->u.function.func_name = NewString(name);
    AddCodeToCodes(code);

    while (1) {
        if (!param_list) return iter;
        InterCode code;
        code->kind = kParam;

        Operand param_op;
        int lookup_status = LookupVariable(param_list->name, NULL, layer, kVariableDeclare, &param_op);
        assert(lookup_status == 1);

        code->u.param.op = param_op;

        AddCodeToCodes(code);
        
        param_list = param_list->tail;
    }
    --layer;
}

void TranslateAssign(Operand dst_op, Operand src_op) {
    if (!dst_op) return;
    InterCode code;
    code->kind = kAssign;
    code->u.assign.op_left = dst_op;
    code->u.assign.op_right = src_op;
    AddCodeToCodes(code);
}

void TranslateAddressOf(Operand dst_op, Operand src_op) {
    if (!dst_op) return;
    InterCode code;
    code->kind = kAddressOf;
    code->u.address_of.op_left = dst_op;
    code->u.address_of.op_right = src_op;
    AddCodeToCodes(code);
}

void TranslateArg(Operand op) {
    InterCode code;
    code->kind = kArg;
    code->u.arg.op = op;
    AddCodeToCodes(code);
}

void TranslateFunCall(Operand dst_op, const char* name) {
    if (!dst_op) return;
    InterCode code;
    code->kind = kCall;
    code->u.call.func_name = name;
    code->u.call.op_result = dst_op;
    AddCodeToCodes(code);
}

void TranslateBinOpType(BinOpType bin_op_type, Operand op_result, Operand op_l, Operand op_r) {
    if (!op_result) return;
    InterCode code;
    code->kind = kBinOp;
    code->u.bin_op.type = bin_op_type;
    code->u.bin_op.op_result = op_result;
    code->u.bin_op.op_1 = op_l;
    code->u.bin_op.op_2 = op_r;
    AddCodeToCodes(code);
}

void TranslateBinOp(TreeNode* bin_op, Operand op_result, Operand op_l, Operand op_r) {
    if (!op_result) return;
    BinOpType bin_op_type;
    if (bin_op->type = kSYMBOL) {
        if (strcmp(bin_op->val.valstring, "PLUS") == 0) {
            bin_op_type = kArithAdd;
        } else if (strcmp(bin_op->val.valstring, "MINUS") == 0) {
            bin_op_type = kArithSub;
        } else if (strcmp(bin_op->val.valstring, "STAR") == 0) {
            bin_op_type = kArithMul;
        } else if (strcmp(bin_op->val.valstring, "DIV") == 0) {
            bin_op_type = kArithDiv;
        } else if (strcmp(bin_op->val.valstring, "AND") == 0) {
            bin_op_type = kLogicAnd;
        } else if (strcmp(bin_op->val.valstring, "OR") == 0) {
            bin_op_type = kLogicOr;
        }
    } else {
        assert(bin_op->type == kRELOP);
        switch (bin_op->val.ValRelop) {
            case kLT: bin_op_type = kRelopLT; break;
            case kLE: bin_op_type = kRelopLE; break;
            case kGT: bin_op_type = kRelopGT; break;
            case kGE: bin_op_type = kRelopGE; break;
            case kEQ: bin_op_type = kRelopEQ; break;
            case kNE: bin_op_type = kRelopNE; break;
        }
    }
    TranslateBinOpType(bin_op_type, op_result, op_l, op_r);
}

void TranslateCond

void TranslateCond(TreeNode* exp_1, Operand op_dst, Operand op_true, Operand op_false) {
    TreeNode* exp_2 = exp_1->bro->bro,
            * op = exp_1->bro;
    if (op->type == kRELOP) {
        Operand op_1 = NewOperandTemporary();
        Type type_1 = ProcessExp(exp_1, op_1);
        Operand op_2 = NewOperandTemporary();
        Type type_2 = ProcessExp(exp_2, op_2);
        TranslateRelop(op_1, op_2, op_true);
        TranslateGoto(op_false);
    }
}

void TranslateLabel(Operand label) {
    InterCode code;
    code->kind = kLabel;
    code->u.label = label;
    AddCodeToCodes(code);
}