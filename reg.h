#ifndef __REG_H_INCLUDED_
#define __REG_H_INCLUDED_

#include "InterCode.h"

typedef struct Reg {
    const char* name;
    enum RegStatus {
        kOccupyTemporary,
        kOccupyValue,
        kAvailable
    } status;
    Operand op;
} Reg;

int AllocateReg(Operand op, enum RegStatus status);

void FreeReg(int idx);

void FreeRegIfNoNeed(int idx);

int GetReg(Operand op);

int GetRegForDefinition(Operand op);

int GetRegForTemporary();

#endif