#ifndef __INTERCODE_H_INCLUDED_
#define __INTERCODE_H_INCLUDED_

#include "tree.h"

typedef struct Operand_* Operand;
typedef struct InterCodes_* InterCodes;
typedef struct InterCode_* InterCode;
typedef struct InterCodeIterator_* InterCodeIterator;

typedef struct Operand_ {
    enum { kVariable, kTemporary, kConstantInt, kConstantFloat } kind;
    union {
        int var_no;
        int temp_no;
        int int_value;
        float float_value;
    } u;
} Operand_;

typedef struct InterCode_ {
    enum { 
        kLabel,
        kFunction,
        kAssign,
        kBinOp,
        kAddressOf,
        kDereference,
        kGoto,
        kConditionalJump,
        kReturn,
        kDeclare,
        kArg,
        kCall,
        kParam,
        kIO  
    } kind;
    union {
        struct { int label_no; } label;
        struct { const char* func_name; } function;
        struct { Operand op_right, op_left; } assign;
        struct { 
            Operand op_result, op_1, op_2;
            enum { kArithAdd, kArithSub, kArithMul, kArithDiv, kLogicAnd, kLogicOr, kRelopLT, kRelopLE, kRelopGT, kRelopGE, kRelopEQ, kRelopNE } type;
        } bin_op;
        struct { Operand op_right, op_left; } address_of;
        struct {
            Operand op_right, op_left; 
            enum { kLeftDereference, kRightDereference } type;
        } dereference;
        struct { int label_no; } go_to;
        struct {
            Operand op_1, op_2;
            int label_no;
            RelopType relop_type;
        } conditional_jump;
        struct { Operand op; } ret;
        struct { Operand op; int size; } declare;
        struct { Operand op; } arg;
        struct { Operand op_result; const char* func_name; } call;
        struct { Operand op; } param;
        struct { 
            Operand op;
            enum { kRead, kWrite } type;
        } io;
    } u;
} InterCode_;

typedef struct InterCodes_ {
    InterCode code;
    InterCodes prev, next;
} InterCodes_;

typedef struct InterCodeIterator_ {
    InterCodes begin;
    InterCodes end;
} InterCodeIterator_;

Operand NewOperandVariable();

Operand NewOperandTemporary();

Operand NewOperandConstantInt(int val);

Operand NewOperandConstantFloat(float val);

#endif