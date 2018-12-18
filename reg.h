#ifndef __REG_H_INCLUDED_
#define __REG_H_INCLUDED_

#include "InterCode.h"

typedef struct Reg {
    const char* name;
    enum {
        kOccupyTemporary,
        kOccupyValue,
        kAvailable
    } status;
    Operand op;
} Reg;

int AllocateReg(Operand op);

void FreeReg(int idx);

int GetReg(Operand op);

int GetRegForTemporary();

#endif