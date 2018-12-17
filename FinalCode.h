#ifndef __FINALCODE_H_INCLUDED_
#define __FINALCODE_H_INCLUDED_

#include "InterCode.h"

// TODO: 
// 1. static variable
typedef struct Info_* Info;

typedef struct Info_ {
    int reg_no[3];  // 0: basic; 1: pointer; 2: address
    struct {
        InterCodes code;
        int lineno;
    } active_info;
} Info_;

typedef struct FinalCode_ {
    enum {
        kFinalLabel,
        kFinalLi,
        kFinalMove,
        kFinalAddi,
        kFinalBinop, // add sub mul
        kFinalDiv,
        kFinalLw,
        kFinalSw,
        kFinalJ,
        kFinalJal,
        kFinalRet,
        kFinalJc
    } kind;
    union {
        struct { const char* name; } label;
        struct { int reg_no; int constant; } li;
        struct { int reg_dst, reg_src; } move;
        struct { int reg_dst, reg_src; int constant; } addi;
        struct {
            enum { kFinalAdd, kFinalSub, kFinalMul } type;  
            int reg_res, reg_1, reg_2;    
        } binop;
        struct { int reg_1, reg_2, reg_3; } divv;
        struct { int reg_1, reg_2; } lw;
        struct { int reg_1, reg_2; } sw;
        struct { const char* name; } j;
        struct { const char* name; int reg_no; } jal;
        struct { int reg_no; } ret;
        struct {
            enum { kFinalEQ, kFinalNE, kFinalGT, kFinalLT, kFinalGE, kFinalLE } jc_type;
            int reg_1, reg_2;
        } jc;
    } u;
} FinalCode_;

void ConstructBasicBlock(InterCodes codes);

void GenerateFinalCode(InterCodes codes);

Info InitializeInfo(int num);

void OutputBlockInfo();

void TranslateToFinalCodes();

#endif