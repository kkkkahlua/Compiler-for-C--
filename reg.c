#include "reg.h"

Reg regs[32] = {
    {"$zero", kTypeNull, -1},   //  0: constant 0
    {"$at", kTypeNull, -1},     //  1: *** cannot be used
    {"$v0", kTypeNull, -1},     //  2-3: function return value
    {"$v1", kTypeNull, -1},
    {"$a0", kTypeNull, -1},     //  4-7: function first 4 parameter 
    {"$a1", kTypeNull, -1},
    {"$a2", kTypeNull, -1},
    {"$a3", kTypeNull, -1},
    {"$t0", kTypeNull, -1},     //  8-15: (t0-t7) caller preserve
    {"$t1", kTypeNull, -1},
    {"$t2", kTypeNull, -1},
    {"$t3", kTypeNull, -1},
    {"$t4", kTypeNull, -1},
    {"$t5", kTypeNull, -1},
    {"$t6", kTypeNull, -1},
    {"$t7", kTypeNull, -1},
    {"$s0", kTypeNull, -1},     //  16-23: (s0-s7) callee preserve
    {"$s1", kTypeNull, -1},
    {"$s2", kTypeNull, -1},
    {"$s3", kTypeNull, -1},
    {"$s4", kTypeNull, -1},
    {"$s5", kTypeNull, -1},
    {"$s6", kTypeNull, -1},
    {"$s7", kTypeNull, -1},
    {"$t8", kTypeNull, -1},     //  24-25: (t8-t9) caller preserve
    {"$t9", kTypeNull, -1},
    {"$k0", kTypeNull, -1},     //  26-27: *** cannot be used
    {"$k1", kTypeNull, -1},
    {"$gp", kTypeNull, -1},
    {"$sp", kTypeNull, -1},
    {"$fp", kTypeNull, -1},
    {"$ra", kTypeNull, -1},
};