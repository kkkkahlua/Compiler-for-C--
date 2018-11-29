#include "optimize.h"

#include <stdio.h>
#include <stdlib.h>

void OptimizeAdjacentLabel(InterCodes codes);
void OptimizeAssign(InterCodes codes);
void OptimizeUselessCodes(InterCodes codes);

void optimize(InterCodes codes) {
    OptimizeAdjacentLabel(codes);
    OptimizeUselessCodes(codes);
    OptimizeAssign(codes);
}

void RemoveCurCode(InterCodes pre_code, InterCodes cur_code) {
    InterCodes nxt_code = cur_code->next;
    pre_code->next = nxt_code;
    if (nxt_code) nxt_code->prev = pre_code;
}

void OptimizeAdjacentLabel(InterCodes codes) {
    InterCodes pre_code = codes, cur_code = pre_code->next;
    while (1) {
        if (!cur_code) return;
        if (pre_code->code->kind == kLabel 
            && cur_code->code->kind == kLabel) {
            *cur_code->code->u.label.op = *pre_code->code->u.label.op;
            RemoveCurCode(pre_code, cur_code);
            cur_code = cur_code->next;
        } else {
            pre_code = cur_code;
            cur_code = cur_code->next;
        }
    }
}

void OptimizeUselessCodes(InterCodes codes) {
    InterCodes pre_code = codes, cur_code = pre_code->next;
    int see_return = 0;
    while (1) {
        if (!cur_code) return;
        if (pre_code->code->kind == kReturn) see_return = 1;
        if (cur_code->code->kind == kFunEnd
            || cur_code->code->kind == kLabel) see_return = 0;
        if (see_return == 1) {
            RemoveCurCode(pre_code, cur_code);
            cur_code = cur_code->next;
        } else {
            pre_code = cur_code;
            cur_code = cur_code->next;
        }
    }    
}

void OptimizeAssign(InterCodes codes) {
    InterCodes pre_code = codes, cur_code = pre_code->next;
    while (1) {
        if (!cur_code) return;
        if (cur_code->code->kind == kAssign
            && cur_code->code->u.assign.op_left->kind == kVariable
            && cur_code->code->u.assign.op_right->kind == kTemporary) {
            switch (pre_code->code->kind) {
                case kAssign:
                    if (pre_code->code->u.assign.op_left
                        == cur_code->code->u.assign.op_right) {
                        pre_code->code->u.assign.op_left
                            = cur_code->code->u.assign.op_left;
                        RemoveCurCode(pre_code, cur_code);
                        cur_code = cur_code->next;
                        continue;
                    }
                    break;
                case kBinOp:
                    if (pre_code->code->u.bin_op.op_result
                        == cur_code->code->u.assign.op_right) {
                        pre_code->code->u.bin_op.op_result
                            = cur_code->code->u.assign.op_left;
                        RemoveCurCode(pre_code, cur_code);
                        cur_code = cur_code->next;
                        continue;
                    }
                    break;
                case kCall:
                    if (pre_code->code->u.call.op_result
                        == cur_code->code->u.assign.op_right) {
                        pre_code->code->u.call.op_result
                            = cur_code->code->u.assign.op_left;
                        RemoveCurCode(pre_code, cur_code);
                        cur_code = cur_code->next;
                        continue;
                    }
                    break;
            }
        }
        pre_code = cur_code;
        cur_code = cur_code->next;
    }
}