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
    InterCode code;
    code->kind = kAssign;
    code->u.assign.op_left = dst_op;
    code->u.assign.op_right = src_op;
    AddCodeToCodes(code);
}

void TranslateArg(Operand op) {
    InterCode code;
    code->kind = kArg;
    code->u.arg.op = op;
    AddCodeToCodes(code);
}

void TranslateFunCall(Operand dst_op, const char* name) {
    InterCode code;
    code->kind = kCall;
    code->u.call.func_name = name;
    code->u.call.op_result = dst_op;
    AddCodeToCodes(code);
}

void TranslateBinOp(TreeNode* bin_op, Operand op_result, Operand op_l, Operand op_r) {
    InterCode code;
    code->kind = kBinOp;
    if (bin_op->type == kSYMBOL) {
        if (strcmp(bin_op->val.valstring, "PLUS") == 0) {
            code->u.kind.bin_op.type = kArithAdd;
        } else if (strcmp(bin_op->val.valstring, "MINUS") == 0) {
            code->u.kind.bin_op.type = kArithSub;
        } else if (strcmp(bin_op->val.valstring, "STAR") == 0) {
            code->u.kind.bin_op.type = kArithMul;
        } else if (strcmp(bin_op->val.valstring, "DIV") == 0) {
            code->u.kind.bin_op.type = kArithDiv;
        } else if (strcmp(bin_op->val.valstring, "AND") == 0) {
            code->u.kind.bin_op.type = kLogicAnd;
        } else if (strcmp(bin_op->val.valstring, "OR") == 0) {
            code->u.kind.bin_op.type = kLogicOr;
        }
    } else {
        assert(bin_op->type == kRELOP);
        code->u.kind.bin_op.type = 
        switch (bin_op->val.ValRelop) {
            case kLT: code->u.kind.bin_op.type = kRelopLT; break;
            case kLE: code->u.kind.bin_op.type = kRelopLE; break;
            case kGT: code->u.kind.bin_op.type = kRelopGT; break;
            case kGE: code->u.kind.bin_op.type = kRelopGE; break;
            case kEQ: code->u.kind.bin_op.type = kRelopEQ; break;
            case kNE: code->u.kind.bin_op.type = kRelopNE; break;
        }
    }
    code->u.kind.bin_op.op_result = op_result;
    code->u.kind.bin_op.op_l = op_l;
    code->u.kind.bin_op.op_r = op_r;
    AddCodeToCodes(code);
}