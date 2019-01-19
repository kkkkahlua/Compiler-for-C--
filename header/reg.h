#ifndef __REG_H_INCLUDED_
#define __REG_H_INCLUDED_

#include "InterCode.h"
#include "generate.h"

typedef enum RegStatus { kOccupyTemporary, kOccupyValue, kAvailable } RegStatus;

typedef struct Reg {
    const char* name;
    RegStatus status;
    Operand op;
} Reg;

int AllocateReg(Info info, Operand op, RegStatus status);

void FillInReg(Info info, int idx, Operand op, RegStatus status);

void FreeRegForTemporary(int idx);

void FreeRegForValue(Operand op);

int GetReg(Operand op);

int GetRegForDefinition(Operand op);

int GetRegForTemporary();

void InitializeRegs();

void SetReg(int idx, Operand op);

#endif