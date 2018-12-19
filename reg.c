#include "reg.h"

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

Info GetInfoForValue(Operand op) {
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
    return info;
}

int GetReg(Operand op) {
    Info info = GetInfoForValue(op);

    // OutputOperand(op, 1);
    // printf(" %d\n", info->reg_no);

    if (info->reg_no != -1) {
        // already in some register
        return info->reg_no;
    }

    int reg_no = AllocateReg(info, op, kOccupyValue);

    // TODO: lw op from memory to reg_no

    return info->reg_no;
}

int AllocateReg(Info info, Operand op, RegStatus status) {
    for (int i = 8; i < 26; ++i) {
        if (regs[i].status == kAvailable) {
            FillInReg(info, i, op, status);
            // puts("in allocate:");
            // OutputOperand(op, 1);
            // printf(" %d\n", i);
            return i;
        }
    }
    int idx = -1;
    for (int i = 8; i < 26; ++i) {
        if (regs[i].status == kOccupyValue && 
            (idx == -1 || regs[i].op->active_lineno > regs[idx].op->active_lineno)) {
            idx = i;
        }
    }
    // TODO: 1. store content in regs[idx] into memory or stack

    // 2. store op in regs[idx]
    FillInReg(info, idx, op, status);

    return idx;
}

int GetRegForTemporary() {
    return AllocateReg(NULL, NULL, kOccupyTemporary);
}

int GetRegForDefinition(Operand op) {
    return AllocateReg(GetInfoForValue(op), op, kOccupyValue);
}

void FreeReg(Info info, int idx) {
    printf("----------------------free %d\n", idx);
    if (info) info->reg_no = -1;
    regs[idx].status = kAvailable;
    regs[idx].op = NULL;
}

void FreeRegForTemporary(int idx) {
    FreeReg(NULL, idx);
}

void FreeRegForValue(Operand op) {
    Info info = GetInfoForValue(op);
    assert(info);
    int idx = info->reg_no;
    assert(regs[idx].status == kOccupyValue);

    if (regs[idx].op->active_lineno == -1) {
        FreeReg(info, idx);
    }
}

void FillInReg(Info info, int idx, Operand op, RegStatus status) {
    regs[idx].status = status;
    regs[idx].op = op;
    if (info) info->reg_no = idx;
}

void SetReg(int idx, Operand op) {
    FillInReg(GetInfoForValue(op), idx, op, kOccupyValue);
}