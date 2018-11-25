#include "InterCode.h"

#include <stdio.h>
#include <stdlib.h>

Operand NewOperandVariable(int var_no) {
    Operand operand = (Operand)malloc(sizeof(Operand_));
    operand->kind = kVARIABLE;
    operand->u.var_no = var_no;
    return operand;
}

void AddCodeToCodes(InterCode code, InterCodes codes, InterCodeIterator* iter) {
    InterCodes cur_code = (InterCodes)malloc(sizeof(InterCodes_));
    cur_code->code = code;
    cur_code->next = NULL;
    cur_code->prev = codes;
    if (!codes) {
        iter->begin = iter->end = codes;
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
        kVARIABLE: printf("v_%d", op->u.var_no); break;
        kTEMPORARY: printf("t_%d", op->u.temp_no); break;
        kCONSTANT: printf("#%d", op->u.value); break;
    }
}

void OutputInterCode(InterCode code) {
    switch (code->kind) {
        case kLabel: printf("LABLE label_%d :", code->u.label.label_no); break;
        case kFunction: printf("FUNCTION %s :", code->u.function.func_name); break;
        case kAssign: {
            OutputOperand(code->u.assign.op_left);
            printf(" := ");
            OutputOperand(code->u.assign.op_right);
            break;
        }
        case kArithmetic: {
            OutputOperand(code->u.arithmetic.op_result);
            printf(" := ");
            OutputOperand(code->u.arithmetic.op_1);
            switch (code->u.arithmetic.type) {
                case kADD: printf(" + "); break;
                case kSUB: printf(" - "); break;
                case kMUL: printf(" * "); break;
                case kDIV: printf(" / "); break;
            }
            OutputOperand(code->u.arithmetic.op_2);
            break;
        }
        case kAddressOf: {
            OutputOperand(code->u.address_of.op_left);
            printf(" := &");
            OutputOperand(code->u.address_of.op_right);
            break;
        }
        case kDereference: {
            if (code->u.dereference.type == kLeftDereference) printf("*");
            OutputOperand(code->u.dereference.op_left);
            printf(" := ");
            if (code->u.dereference.type == kRightDereference) printf("*");
            OutputOperand(code->u.dereference.op_right);
            break;
        }
        case kGoto: printf("GOTO label_%d", code->u.go_to.label_no); break;
        case kConditionalJump: {
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
            printf(" GOTO label_%d", code->u.conditional_jump.label_no);
            break;
        }
        case kReturn: {
            printf("RETURN ");
            OutputOperand(code->u.ret.op);
            break;
        }
        case kDeclare: {
            printf("DEC: ");
            OutputOperand(code->u.declare.op);
            printf(" %d", code->u.declare.size);
            break;
        }
        case kArg: {
            printf("ARG: ");
            OutputOperand(code->u.arg.op);
            break;
        }
        case kCall: {
            OutputOperand(code->u.call.op_result);
            printf(" := CALL %s", code->u.call.func_name);
            break;
        }
        case kParam: {
            printf("PARAM: ");
            OutputOperand(code->u.param.op);
            break;
        }
        case kIO: {
            switch (code->u.io.type) {
                case kRead: printf("READ ");
                case kWrite: printf("WRITE: ");
            }
            OutputOperand(code->u.io.op);
            break;
        }
    }
    puts("");
}