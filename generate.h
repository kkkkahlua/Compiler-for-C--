#ifndef __GENERATE_H_INCLUDED_
#define __GENERATE_H_INCLUDED_

#include "InterCode.h"

typedef struct Info_* Info;

typedef struct Info_ {
    int reg_no;
    int active_lineno;
} Info_;

void ConstructBasicBlock(InterCodes codes);

void GenerateFinalCode(InterCodes codes);

Info InitializeInfo(int num);

void OutputBlockInfo();

void RetrieveActiveInfo();

void TranslateToFinalCode(InterCode code);

void TranslateToFinalCodes();

#endif