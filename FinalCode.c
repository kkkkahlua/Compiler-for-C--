#include "FinalCode.h"

#include "reg.h"

#include <stdio.h>
#include <stdlib.h>

FinalCodes final_codes_head;
FinalCodes final_codes_tail;

extern FILE* stream_ir;
extern FILE* stream;
extern char** output_files;
extern Reg regs[32];
extern int code_read;
extern int code_write;

void OutputFinalCode(FinalCode code) {
    if (code->kind != kFinalLabel) {
        fprintf(stream, "  ");
    }
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
        case kFinalLw: 
            fprintf(stream, "lw %s, %d(%s)", regs[code->u.lw.reg_1].name,
                                            code->u.lw.offset, 
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
        case kFinalFunEnd:
            break;
        case kFinalLa:
            fprintf(stream, "la %s, %s", regs[code->u.la.reg_des].name, 
                                        code->u.la.name);
            break;
        case kFinalSyscall:
            fprintf(stream, "syscall");
            break;
        case kFinalMflo:
            fprintf(stream, "mflo %s", regs[code->u.mflo.reg_no].name);
            break;
        case kFinalDiv:
            fprintf(stream, "div %s %s", regs[code->u.divv.reg_1].name,
                                        regs[code->u.divv.reg_2].name);
            break;
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

FinalCode NewFinalCodeLa(int reg_des, const char* name) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalLa;
    code->u.la.reg_des = reg_des;
    code->u.la.name = name;
    return code;
}

FinalCode NewFinalCodeSyscall() {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalSyscall;
    return code;
}

FinalCode NewFinalCodeLw(int reg_1, int reg_2, int offset) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalLw;
    code->u.lw.reg_1 = reg_1;
    code->u.lw.reg_2 = reg_2;
    code->u.lw.offset = offset;
    return code;
}

FinalCode NewFinalCodeLabel(const char* name) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalLabel;
    code->u.label.name = name;
    return code;    
}

FinalCode NewFinalCodeSw(int reg_1, int reg_2) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalSw;
    code->u.sw.reg_1 = reg_1;
    code->u.sw.reg_2 = reg_2;
    return code;
}

FinalCode NewFinalCodeDiv(int reg_1, int reg_2) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalDiv;
    code->u.divv.reg_1 = reg_1;
    code->u.divv.reg_2 = reg_2;
    return code;
}

FinalCode NewFinalCodeMflo(int reg_no) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalMflo;
    code->u.mflo.reg_no = reg_no;
    return code;
}

FinalCode NewFinalCodeBinop(BinOpType type, int reg_res, int reg_1, int reg_2) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
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

FinalCode NewFinalCodeJc(RelopType type, int reg_1, int reg_2, const char* name) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalJc;
    code->u.jc.type = type;
    code->u.jc.name = name;
    code->u.jc.reg_1 = reg_1;
    code->u.jc.reg_2 = reg_2;
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

FinalCode NewFinalCodeFunEnd() {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalFunEnd;
    return code;
}

void OutputFinalCodes() {
    fclose(stream);
    stream = fopen(output_files[1], "w");
    if (code_read || code_write) {
        fprintf(stream, ".data\n");
        if (code_read) {
            fprintf(stream, "_prompt: .asciiz \"Enter an integer:\"\n");
        }
        if (code_write) {
            fprintf(stream, "_ret: .asciiz \"\\n\"\n");
        }
        fprintf(stream, ".globl main\n");
        fprintf(stream, ".text\n");
    }

    for (FinalCodes it = final_codes_head; it; it = it->next) {
        OutputFinalCode(it->code);
    }
}