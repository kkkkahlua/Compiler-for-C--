#include "InterCode.h"

#include <stdio.h>
#include <stdlib.h>

extern InterCodeIterator iter;
int var_no = 0;
int temp_no = 0;
int label_no = 0;

Operand NewOperandVariable() {
    Operand operand = (Operand)malloc(sizeof(Operand_));
    operand->kind = kVariable;
    operand->u.var_no = var_no++;
    return operand;
}

Operand NewOperandPointer() {
    Operand operand = (Operand)malloc(sizeof(Operand_));
    operand->kind = kPointer;
    operand->u.var_no = var_no++;
    return operand;
}

Operand NewOperandTemporary() {
    Operand operand = (Operand)malloc(sizeof(Operand_));
    operand->kind = kTemporary;
    operand->u.temp_no = temp_no++;
    return operand;
}

Operand NewOperandLabel() {
    Operand operand = (Operand)malloc(sizeof(Operand_));
    operand->kind = kLabel;
    operand->u.label_no = label_no++;
    return operand;
}

Operand NewOperandConstantInt(int val) {
    Operand operand = (Operand)malloc(sizeof(Operand_));
    operand->kind = kConstantInt;
    operand->u.int_value = val;
    return operand;
}

Operand NewOperandConstantFloat(float val) {
    Operand operand = (Operand)malloc(sizeof(Operand_));
    operand->kind = kConstantFloat;
    operand->u.float_value = val;
    return operand;
}

void AddCodeToCodes(InterCode code) {
    InterCodes cur_code = (InterCodes)malloc(sizeof(InterCodes_));
    cur_code->code = code;
    cur_code->next = NULL;
    cur_code->prev = iter->end;
    if (!iter->begin) {
        iter->begin = iter->end = cur_code;
    } else {
        iter->end->next = cur_code;
        iter->end = cur_code;
    }
}

void OutputInterCode(InterCode code);

void OutputInterCodes(InterCodes codes) {
    while (1) {
        if (!codes) return;
        OutputInterCode(codes->code);
        codes = codes->next;
    }
}

void OutputOperand(Operand op) {
    switch (op->kind) {
        kVariable: printf("v_%d", op->u.var_no); break;
        kTemporary: printf("t_%d", op->u.temp_no); break;
        kLabel: printf("label_%d", op->u.label_no); break;
        kConstantInt: printf("#%d", op->u.int_value); break;
        kConstantFloat: printf("#%f", op->u.float_value); break;
    }
}

void OutputInterCode(InterCode code) {
    switch (code->kind) {
        case kLabel: 
            printf("LABEL ");
            OutputOperand(code->u.label.op);
            printf(" :");
            break;
        case kFunction: printf("FUNCTION %s :", code->u.function.func_name); break;
        case kAssign:
            OutputOperand(code->u.assign.op_left);
            printf(" := ");
            OutputOperand(code->u.assign.op_right);
            break;
        case kBinOp:
            OutputOperand(code->u.bin_op.op_result);
            printf(" := ");
            OutputOperand(code->u.bin_op.op_1);
            switch (code->u.bin_op.type) {
                case kArithAdd: printf(" + "); break;
                case kArithSub: printf(" - "); break;
                case kArithMul: printf(" * "); break;
                case kArithDiv: printf(" / "); break;
                case kLogicAnd: printf(" && "); break;
                case kLogicOr: printf(" || "); break;
                case kRelopLT: printf(" < "); break;
                case kRelopLE: printf(" <= "); break;
                case kRelopGT: printf(" > "); break;
                case kRelopGE: printf(" >= "); break;
                case kRelopEQ: printf(" == "); break;
                case kRelopNE: printf(" != "); break;
            }
            OutputOperand(code->u.bin_op.op_2);
            break;
        case kAddressOf:
            OutputOperand(code->u.address_of.op_left);
            printf(" := &");
            OutputOperand(code->u.address_of.op_right);
            break;
        case kDereference:
            if (code->u.dereference.type == kLeftDereference) printf("*");
            OutputOperand(code->u.dereference.op_left);
            printf(" := ");
            if (code->u.dereference.type == kRightDereference) printf("*");
            OutputOperand(code->u.dereference.op_right);
            break;
        case kGoto: 
            printf("GOTO ");
            OutputOperand(code->u.go_to.op);
            break;
        case kConditionalJump:
            printf("IF ");
            OutputOperand(code->u.conditional_jump.op_1);
            switch (code->u.conditional_jump.relop_type) {
                case kGT: printf(" > "); break;
                case kGE: printf(" >= "); break;
                case kLT: printf(" < "); break;
                case kLE: printf(" <= "); break;
                case kEQ: printf(" == "); break;
                case kNE: printf(" != "); break;
            }
            OutputOperand(code->u.conditional_jump.op_2);
            printf(" GOTO ");
            OutputOperand(code->u.conditional_jump.op_label);
            break;
        case kReturn:
            printf("RETURN ");
            OutputOperand(code->u.ret.op);
            break;
        case kDeclare:
            printf("DEC: ");
            OutputOperand(code->u.declare.op);
            printf(" %d", code->u.declare.size);
            break;
        case kArg:
            printf("ARG: ");
            OutputOperand(code->u.arg.op);
            break;
        case kCall:
            OutputOperand(code->u.call.op_result);
            printf(" := CALL %s", code->u.call.func_name);
            break;
        case kParam:
            printf("PARAM: ");
            OutputOperand(code->u.param.op);
            break;
        case kIO:
            switch (code->u.io.type) {
                case kRead: printf("READ ");
                case kWrite: printf("WRITE: ");
            }
            OutputOperand(code->u.io.op);
            break;
    }
    puts("");
}