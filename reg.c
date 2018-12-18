#include "reg.h"

#include "generate.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

extern Info variable_info;
extern Info temporary_info;

Reg regs[32] = {
    {"$zero", kAvailable, NULL},   //  0: constant 0
    {"$at", kAvailable, NULL},     //  1: *** cannot be used
    /*  --- */
    {"$v0", kAvailable, NULL},     //  2-3: function return value
    {"$v1", kAvailable, NULL},
    {"$a0", kAvailable, NULL},     //  4-7: function first 4 parameter 
    {"$a1", kAvailable, NULL},
    {"$a2", kAvailable, NULL},
    {"$a3", kAvailable, NULL},
    {"$t0", kAvailable, NULL},     //  8-15: (t0-t7) caller preserve
    {"$t1", kAvailable, NULL},
    {"$t2", kAvailable, NULL},
    {"$t3", kAvailable, NULL},
    {"$t4", kAvailable, NULL},
    {"$t5", kAvailable, NULL},
    {"$t6", kAvailable, NULL},
    {"$t7", kAvailable, NULL},
    {"$s0", kAvailable, NULL},     //  16-23: (s0-s7) callee preserve
    {"$s1", kAvailable, NULL},
    {"$s2", kAvailable, NULL},
    {"$s3", kAvailable, NULL},
    {"$s4", kAvailable, NULL},
    {"$s5", kAvailable, NULL},
    {"$s6", kAvailable, NULL},
    {"$s7", kAvailable, NULL},
    {"$t8", kAvailable, NULL},     //  24-25: (t8-t9) caller preserve
    {"$t9", kAvailable, NULL},
    /*  --- */
    {"$k0", kAvailable, NULL},     //  26-27: *** cannot be used
    {"$k1", kAvailable, NULL},
    {"$gp", kAvailable, NULL},
    {"$sp", kAvailable, NULL},
    {"$fp", kAvailable, NULL},
    {"$ra", kAvailable, NULL},
};

int GetReg(Operand op) {
    Info info;
    switch (op->kind) {
        case kVariable:
        case kVariablePointer:
        case kVariableAddress:
            info = variable_info + op->u.var_no;
            break;
        case kTemporary:
        case kTemporaryPointer:
        case kTemporaryAddress:
            info = temporary_info + op->u.temp_no;
            break;
        default:
            assert(0);
    }

    if (info->reg_no != -1) {
        // already in some register
        return info->reg_no;
    }

    info->reg_no = AllocateReg(op);
    // TODO: lw op from memory to reg_no
}

int AllocateReg(Operand op) {
    for (int i = 2; i < 26; ++i) {
        if (regs[i].status == kAvailable) return i;
    }
    int idx = -1;
    for (int i = 2; i < 26; ++i) {
        if (idx == -1 || 
            (regs[i].status != kOccupyTemporary &&
            regs[i].op->active_info.lineno > regs[idx].op->active_info.lineno)) {
            idx = i;
        }
    }
    // TODO: 
    // 1. store content in regs[idx] into memory or stack
    // 2. store op in regs[idx]
    return idx;
}

int GetRegForTemporary() {
    return 0;
}

void FreeReg(int idx) {
    regs[idx].status = kAvailable;
    regs[idx].op = NULL;
}