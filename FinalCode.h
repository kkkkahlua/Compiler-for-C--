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

void ConstructBasicBlock(InterCodes codes);

Info InitializeInfo(int num);

void OutputBlockInfo();

void TranslateToFinalCodes(InterCodes codes);

#endif