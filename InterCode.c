#include "InterCode.h"

#include <stdio.h>
#include <stdlib.h>

extern InterCodeIterator iter;
extern FILE* stream;
int var_no = 0;
int temp_no = 0;
int label_no = 0;

Operand NewOperandVariable() {
    Operand operand = (Operand)malloc(sizeof(Operand_));
    operand->kind = kVariable;
    operand->u.var_no = ++var_no;
    return operand;
}

Operand NewOperandPointer() {
    Operand operand = (Operand)malloc(sizeof(Operand_));
    operand->kind = kVariablePointer;
    operand->u.var_no = ++var_no;
    return operand;
}

Operand NewOperandTemporary() {
    Operand operand = (Operand)malloc(sizeof(Operand_));
    operand->kind = kTemporary;
    operand->u.temp_no = ++temp_no;
    return operand;
}

Operand NewOperandLabel() {
    Operand operand = (Operand)malloc(sizeof(Operand_));
    operand->kind = kLABEL;
    operand->u.label_no = ++label_no;
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
    // OutputInterCode(code);
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
        case kVariable: fprintf(stream, "v%d", op->u.var_no); break;
        case kVariablePointer: fprintf(stream, "*v%d", op->u.var_no); break;
        case kTemporary: fprintf(stream, "t%d", op->u.temp_no); break;
        case kTemporaryPointer: fprintf(stream, "*t%d", op->u.temp_no); break;
        case kLABEL: fprintf(stream, "label%d", op->u.label_no); break;
        case kConstantInt: fprintf(stream, "#%d", op->u.int_value); break;
        case kConstantFloat: fprintf(stream, "#%f", op->u.float_value); break;
    }
}

void OutputInterCode(InterCode code) {
    switch (code->kind) {
        case kLabel: 
            fprintf(stream, "LABEL ");
            OutputOperand(code->u.label.op);
            fprintf(stream, " :");
            break;
        case kFunction: 
            fprintf(stream, "FUNCTION %s :", code->u.function.func_name); 
            break;
        case kAssign:
            OutputOperand(code->u.assign.op_left);
            fprintf(stream, " := ");
            OutputOperand(code->u.assign.op_right);
            break;
        case kBinOp:
            OutputOperand(code->u.bin_op.op_result);
            fprintf(stream, " := ");
            OutputOperand(code->u.bin_op.op_1);
            switch (code->u.bin_op.type) {
                case kArithAdd: fprintf(stream, " + "); break;
                case kArithSub: fprintf(stream, " - "); break;
                case kArithMul: fprintf(stream, " * "); break;
                case kArithDiv: fprintf(stream, " / "); break;
            }
            OutputOperand(code->u.bin_op.op_2);
            break;
        case kAddressOf:
            OutputOperand(code->u.address_of.op_left);
            fprintf(stream, " := &");
            OutputOperand(code->u.address_of.op_right);
            break;
        case kDereference:
            if (code->u.dereference.type == kLeftDereference) fprintf(stream, "*");
            OutputOperand(code->u.dereference.op_left);
            fprintf(stream, " := ");
            if (code->u.dereference.type == kRightDereference) fprintf(stream, "*");
            OutputOperand(code->u.dereference.op_right);
            break;
        case kGoto: 
            fprintf(stream, "GOTO ");
            OutputOperand(code->u.go_to.op);
            break;
        case kConditionalJump:
            fprintf(stream, "IF ");
            OutputOperand(code->u.conditional_jump.op_1);
            switch (code->u.conditional_jump.relop_type) {
                case kGT: fprintf(stream, " > "); break;
                case kGE: fprintf(stream, " >= "); break;
                case kLT: fprintf(stream, " < "); break;
                case kLE: fprintf(stream, " <= "); break;
                case kEQ: fprintf(stream, " == "); break;
                case kNE: fprintf(stream, " != "); break;
            }
            OutputOperand(code->u.conditional_jump.op_2);
            fprintf(stream, " GOTO ");
            OutputOperand(code->u.conditional_jump.op_label);
            break;
        case kReturn:
            fprintf(stream, "RETURN ");
            OutputOperand(code->u.ret.op);
            break;
        case kDeclare:
            fprintf(stream, "DEC ");
            OutputOperand(code->u.declare.op);
            fprintf(stream, " %d", code->u.declare.size);
            break;
        case kArg:
            fprintf(stream, "ARG ");
            OutputOperand(code->u.arg.op);
            break;
        case kCall:
            if (code->u.call.op_result) {
                OutputOperand(code->u.call.op_result);
                fprintf(stream, " := CALL %s", code->u.call.func_name);
            } else {
                fprintf(stream, "CALL %s", code->u.call.func_name);
            }
            break;
        case kParam:
            fprintf(stream, "PARAM: ");
            OutputOperand(code->u.param.op);
            break;
        case kIO:
            switch (code->u.io.type) {
                case kRead: fprintf(stream, "READ "); break;
                case kWrite: fprintf(stream, "WRITE ");
            }
            OutputOperand(code->u.io.op);
            break;
        case kFunEnd:
            break;
    }
    puts("");
}