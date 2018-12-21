#ifndef __GENERATE_H_INCLUDED_
#define __GENERATE_H_INCLUDED_

#include "InterCode.h"

typedef struct Info_* Info;

typedef struct Info_ {
    int reg_no;
    int offset;
    int active_lineno;
} Info_;

void AppendIO();

void ConstructBasicBlock(InterCodes codes);

void GenerateFinalCode(InterCodes codes);

Info GetOperandInfo(Operand op);

void GetStackAddress(int reg_no, Operand op);

Info InitializeInfo(int num);

void OutputBlockInfo();

void RetrieveActiveInfo();

void TranslateToFinalCode(InterCode code);

void TranslateToFinalCodes();

#endif