#ifndef __FINALCODE_H_INCLUDED_
#define __FINALCODE_H_INCLUDED_

#include "InterCode.h"

// TODO: 
// 1. static variable
typedef struct FinalCode_* FinalCode;

typedef struct FinalCodes_* FinalCodes;

typedef enum LabelType { kLabelLabel, kLabelFunc } LabelType;

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
        kFinalJr,
        kFinalJc
    } kind;
    union {
        struct { const char* name; } label;
        struct { int reg_no; int intermediate; } li;
        struct { int reg_dst, reg_src; } move;
        struct { int reg_res, reg_1; int intermediate; } addi;
        struct {
            BinOpType type;
            int reg_res, reg_1, reg_2;    
        } binop;
        struct { int reg_1, reg_2, reg_3; } divv;
        struct { int reg_1, reg_2; } lw;
        struct { int reg_1, reg_2; } sw;
        struct { const char* name; } j;
        struct { const char* name; } jal;
        struct { int reg_no; } ret;
        struct {
            RelopType type;
            int reg_1, reg_2;
            const char* name;
        } jc;
    } u;
} FinalCode_;

typedef struct FinalCodes_ {
    FinalCode code;
    FinalCodes next;
} FinalCodes_;

void AddFinalCodeToFinalCodes(FinalCode code);

FinalCode NewFinalCodeAddi(int reg_res, int reg_1, int intermediate);

FinalCode NewFinalCodeBinop(BinOpType type, int reg_res, int reg_1, int reg_2);

FinalCode NewFinalCodeJ(const char* name);

FinalCode NewFinalCodeJal(const char* name);

FinalCode NewFinalCodeJr();

FinalCode NewFinalCodeLi(int reg_no, int intermediate);

FinalCode NewFinalCodeLw(int reg_1, int reg_2);

FinalCode NewFinalCodeMove(int reg_1, int reg_2);

FinalCode NewFinalCodeSw(int reg_1, int reg_2);

#endif