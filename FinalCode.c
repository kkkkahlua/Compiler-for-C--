#include "FinalCode.h"

#include <stdlib.h>

FinalCodes final_codes_head;
FinalCodes final_codes_tail;

void AddFinalCodeToFinalCodes(FinalCode code) {
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