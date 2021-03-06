#ifndef __INTERCODE_H_INCLUDED_
#define __INTERCODE_H_INCLUDED_

#include "tree.h"

typedef struct Operand_* Operand;
typedef struct InterCodes_* InterCodes;
typedef struct InterCode_* InterCode;
typedef struct InterCodeIterator_* InterCodeIterator;

typedef struct Operand_ {
    enum { 
        kVariable, kTemporary, 
        kVariablePointer, kTemporaryPointer,
        kVariableAddress, kTemporaryAddress,
        kConstantInt, kConstantFloat, 
        kLABEL 
    } kind;
    union {
        int var_no;
        int temp_no;
        int int_value;
        float float_value;
        int label_no;
    } u;
    int active_lineno;
} Operand_;

typedef enum OperandType { kValue, kPointer, kAddress, kIntermediate } OperandType;

typedef enum BinOpType {
    kArithAdd, kArithSub, kArithMul, kArithDiv, 
} BinOpType;

typedef enum DereferenceType {
    kLeftDereference, kRightDereference
} DereferenceType;

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
        kIO,
        kFunEnd
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
            DereferenceType type;
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
            enum IOType { kRead, kWrite } type;
        } io;
    } u;
} InterCode_;

typedef struct InterCodes_ {
    InterCode code;
    int start_of_block;
    int lineno;
    InterCodes prev, next;
} InterCodes_;

typedef struct InterCodeIterator_ {
    InterCodes begin;
    InterCodes end;
    InterCodeIterator next;
} InterCodeIterator_;

void AddCodeToCodes(InterCode code);

char* GetLabelName(Operand op);

OperandType GetOperandType(Operand op);

void MoveDeclareForward();

Operand NewOperandConstantInt(int val);

Operand NewOperandConstantFloat(float val);

Operand NewOperandLabel();

Operand NewOperandTemporary();

Operand NewOperandVariable();

Operand NewOperandVariableAddress();

Operand NewOperandVariablePointer();

Operand NewOperandTemporaryPointer();

Operand ToOperand(Operand operand);

Operand ToOperandAddress(Operand operand);

Operand ToOperandPointer(Operand operand);

Operand ToOperandTemporary(Operand op);

Operand ToOperandTemporaryAddress(Operand operand);

Operand ToOperandTemporaryPointer(Operand op_temp);

Operand ToOperandVariable(Operand operand_pointer);

Operand ToOperandVariableAddress(Operand operand);

Operand ToOperandVariablePointer(Operand operand);

void OutputInterCode(InterCode code, int flag);

void OutputInterCodes(InterCodes codes, int flag);

void OutputOperand(Operand op, int flag);

#endif