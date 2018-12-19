#include "FinalCode.h"

#include "reg.h"

#include <stdio.h>
#include <stdlib.h>

FinalCodes final_codes_head;
FinalCodes final_codes_tail;

extern FILE* stream;
extern Reg regs[32];

void OutputFinalCode(FinalCode code) {
    switch (code->kind) {
        case kFinalLabel:
            fprintf(stream, "%s:", code->u.label.name);
            break;
        case kFinalLi:
            fprintf(stream, "li %s, %d", regs[code->u.li.reg_no].name, 
                                        code->u.li.intermediate);
            break;
        case kFinalMove:
            fprintf(stream, "move %s, %s", regs[code->u.move.reg_dst].name,
                                        regs[code->u.move.reg_src].name);
            break;
        case kFinalAddi:
            fprintf(stream, "addi %s, %s, %d", regs[code->u.addi.reg_res].name,
                                            regs[code->u.addi.reg_1].name,
                                            code->u.addi.intermediate);
            break;
        case kFinalBinop: {
            const char* op_name;
            switch (code->u.binop.type) {
                case kArithAdd: op_name = "add"; break;
                case kArithSub: op_name = "sub"; break;
                case kArithMul: op_name = "mul"; break;
            }
            fprintf(stream, "%s %s, %s, %s", op_name,
                                        regs[code->u.binop.reg_res].name,
                                        regs[code->u.binop.reg_1].name,
                                        regs[code->u.binop.reg_2].name);
            break;
        }
        case kFinalDiv: {
            // TODO:
        }
        case kFinalLw: 
            fprintf(stream, "lw %s, 0(%s)", regs[code->u.lw.reg_1].name, 
                                            regs[code->u.lw.reg_2].name);
            break;
        case kFinalSw:
            fprintf(stream, "sw %s, 0(%s)", regs[code->u.lw.reg_1].name, 
                                            regs[code->u.lw.reg_2].name);
            break;
        case kFinalJ:
            fprintf(stream, "j %s", code->u.j.name);
            break;
        case kFinalJal:
            fprintf(stream, "jal %s", code->u.jal.name);
            break;
        case kFinalJr:
            fprintf(stream, "jr $ra");
            break;
        case kFinalJc: {
            const char* rel_name;
            switch (code->u.jc.type) {
                case kGT: rel_name = "bgt"; break;
                case kGE: rel_name = "bge"; break;
                case kLT: rel_name = "blt"; break;
                case kLE: rel_name = "ble"; break;
                case kEQ: rel_name = "beq"; break;
                case kNE: rel_name = "bne"; break;
            }
            fprintf(stream, "%s %s, %s, %s", rel_name,
                                            regs[code->u.jc.reg_1].name,
                                            regs[code->u.jc.reg_2].name,
                                            code->u.jc.name);
            break;
        }
    }
    fprintf(stream, "\n");
}

void AddFinalCodeToFinalCodes(FinalCode code) {
    OutputFinalCode(code);
    FinalCodes cur_code = (FinalCodes)malloc(sizeof(FinalCodes_));
    cur_code->code = code;
    cur_code->next = NULL;
    if (!final_codes_head) {
        final_codes_head = final_codes_tail = cur_code;
    } else {
        final_codes_tail->next = cur_code;
        final_codes_tail = cur_code;
    }
}

FinalCode NewFinalCodeLw(int reg_1, int reg_2) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalLw;
    code->u.lw.reg_1 = reg_1;
    code->u.lw.reg_2 = reg_2;
    return code;
}

FinalCode NewFinalCodeSw(int reg_1, int reg_2) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalSw;
    code->u.sw.reg_1 = reg_1;
    code->u.sw.reg_2 = reg_2;
    return code;
}

FinalCode NewFinalCodeBinop(BinOpType type, int reg_res, int reg_1, int reg_2) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode));
    code->kind = kFinalBinop;
    code->u.binop.type = type;
    code->u.binop.reg_res = reg_res;
    code->u.binop.reg_1 = reg_1;
    code->u.binop.reg_2 = reg_2;
    return code;
}

FinalCode NewFinalCodeLi(int reg_no, int intermediate) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalLi;
    code->u.li.reg_no = reg_no;
    code->u.li.intermediate = intermediate;
    return code;
}

FinalCode NewFinalCodeMove(int reg_1, int reg_2) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalMove;
    code->u.move.reg_dst = reg_1;
    code->u.move.reg_src = reg_2;
    return code;
}

FinalCode NewFinalCodeJr() {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalJr;
    return code;
}

FinalCode NewFinalCodeJal(const char* name) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalJal;
    code->u.jal.name = name;
    return code;
}

FinalCode NewFinalCodeJ(const char* name) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalJ;
    code->u.j.name = name;
    return code;
}

FinalCode NewFinalCodeAddi(int reg_res, int reg_1, int intermediate) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalAddi;
    code->u.addi.reg_res = reg_res;
    code->u.addi.reg_1 = reg_1;
    code->u.addi.intermediate = intermediate;
    return code;
}