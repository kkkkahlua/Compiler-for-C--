#ifndef __GENERATE_H_INCLUDED_
#define __GENERATE_H_INCLUDED_

#include "InterCode.h"

typedef struct Info_* Info;
typedef struct FuncInfo_* FuncInfo;

typedef struct Info_ {
    int reg_no;
    int offset;
    int active_lineno;
} Info_;

typedef struct FuncInfo_ {
    const char* name;
    int param_num;
    FuncInfo next;
} FuncInfo_;

void AppendIO();

void ConstructBasicBlock(InterCodes codes);

void GenerateFinalCode(InterCodes codes);

Info GetOperandInfo(Operand op);

void GetStackAddress(int reg_no, Operand op);

void InitializeInfo(Info info, int num);

Info NewInfo(int num);

void OutputBlockInfo();

void RetrieveActiveInfo(InterCodeIterator block_iter);

void TranslateToFinalCode(InterCode code);

void TranslateToFinalCodes();

#endif