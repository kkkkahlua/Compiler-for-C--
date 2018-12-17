#ifndef __REG_H_INCLUDED_
#define __REG_H_INCLUDED_

typedef struct Reg {
    const char* name;
    enum { kTypeVariable, kTypeTemporary, kTypeNull } type;
    int idx;
} Reg;

#endif