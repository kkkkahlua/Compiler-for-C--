#ifndef __INTERCODE_H_INCLUDED_
#define __INTERCODE_H_INCLUDED_

#include "tree.h"

typedef struct Operand_* Operand;
typedef struct InterCodes_* InterCodes;
typedef struct InterCode_* InterCode;
typedef struct InterCodeIterator_* InterCodeIterator;

typedef struct Operand_ {
    enum { kVariable, kTemporary, kPointer, kConstantInt, kConstantFloat, kLABEL } kind;
    union {
        int var_no;
        int temp_no;
        int int_value;
        float float_value;
        int label_no;
    } u;
} Operand_;

typedef enum BinOpType {
    kArithAdd, kArithSub, kArithMul, kArithDiv, 
} BinOpType;

typedef struct InterCode_ {
    enum { 
        kLabel,
        kFunction,
        kAssign,
        kBinOp,
        kUnaOp,
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
        struct { Operand op; } label;
        struct { const char* func_name; } function;
        struct { Operand op_right, op_left; } assign;
        struct { 
            Operand op_result, op_1, op_2;
            BinOpType type;
        } bin_op;
        struct { Operand op_right, op_left; } address_of;
        struct {
            Operand op_right, op_left; 
            enum { kLeftDereference, kRightDereference } type;
        } dereference;
        struct { Operand op; } go_to;
        struct {
            Operand op_1, op_2, op_label;
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

void AddCodeToCodes(InterCode code);

Operand NewOperandConstantInt(int val);

Operand NewOperandConstantFloat(float val);

Operand NewOperandLabel();

Operand NewOperandPointer();

Operand NewOperandTemporary();

Operand NewOperandVariable();

#endif