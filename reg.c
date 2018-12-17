#include "reg.h"

#include <stdio.h>
#include <stdlib.h>

Reg regs[32] = {
    {"$zero", NULL},   //  0: constant 0
    {"$at", NULL},     //  1: *** cannot be used
    {"$v0", NULL},     //  2-3: function return value
    {"$v1", NULL},
    {"$a0", NULL},     //  4-7: function first 4 parameter 
    {"$a1", NULL},
    {"$a2", NULL},
    {"$a3", NULL},
    {"$t0", NULL},     //  8-15: (t0-t7) caller preserve
    {"$t1", NULL},
    {"$t2", NULL},
    {"$t3", NULL},
    {"$t4", NULL},
    {"$t5", NULL},
    {"$t6", NULL},
    {"$t7", NULL},
    {"$s0", NULL},     //  16-23: (s0-s7) callee preserve
    {"$s1", NULL},
    {"$s2", NULL},
    {"$s3", NULL},
    {"$s4", NULL},
    {"$s5", NULL},
    {"$s6", NULL},
    {"$s7", NULL},
    {"$t8", NULL},     //  24-25: (t8-t9) caller preserve
    {"$t9", NULL},
    {"$k0", NULL},     //  26-27: *** cannot be used
    {"$k1", NULL},
    {"$gp", NULL},
    {"$sp", NULL},
    {"$fp", NULL},
    {"$ra", NULL},
};