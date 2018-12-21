#include "generate.h"

#include "FinalCode.h"
#include "reg.h"
#include "translate.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE* stream;

Info variable_info;
Info temporary_info;

InterCodeIterator basic_block_head;
InterCodeIterator basic_block_tail;

int arg_no = 0;
int param_no = 0;
int param_dec_no = 0;
int code_read = 0;
int code_write = 0;
int frame_size = 0;
int arg_size = 0;

extern int var_no;
extern int temp_no;
extern int line_no;
extern InterCodeIterator iter;
extern void swap(Operand* op_1, Operand* op_2);

void GenerateFinalCode(InterCodes codes) {
    variable_info = InitializeInfo(var_no+1);
    temporary_info = InitializeInfo(temp_no+1);

    ConstructBasicBlock(codes);

    RetrieveActiveInfo();

    OutputBlockInfo();

    TranslateToFinalCodes();

    AppendIO();

    OutputFinalCodes();
}

Info InitializeInfo(int num) {
    Info info = (Info)malloc(sizeof(Info_) * num);
    for (int i = 0; i < num; ++i) {
        info[i].reg_no = -1;
        info[i].offset = -1;
        info[i].active_lineno = -1;
    }
    return info;
}

void MarkBegin(InterCodes codes) {
    InterCode code = codes->code;
    switch (code->kind) {
        case kLabel:
        case kFunction:
            codes->start_of_block = 1;
            break;
        case kGoto:
        case kConditionalJump:
        case kReturn:
            if (codes->next && codes->next->code->kind != kFunEnd) {
                codes->next->start_of_block = 1;
            }
            break;
    }
}

void AddIterToBasicBlock(InterCodeIterator iter) {
    if (!basic_block_head) {
        basic_block_head = basic_block_tail = iter;
    } else {
        basic_block_tail->next = iter;
        basic_block_tail = iter;
    }
}

void ConstructBasicBlock(InterCodes codes) {
    InterCodes temp = codes;
    codes->start_of_block = 1;
    while (1) {
        if (!codes) break;
        MarkBegin(codes);
        codes = codes->next;
    }

    codes = temp;
    InterCodeIterator iter = NULL;
    while (1) {
        if (!codes) {
            AddIterToBasicBlock(iter);
            break;
        }
        if (codes->start_of_block) {
            if (iter) {
                iter->end = codes;
                AddIterToBasicBlock(iter);
            }
            iter = (InterCodeIterator)malloc(sizeof(InterCodeIterator_));
            iter->begin = codes;
            iter->end = NULL;
            iter->next = NULL;
        }
        codes = codes->next;
    }
}

void InitializeActiveInfo(Info info, int num, int lineno) {
    for (int i = 0; i < num; ++i) info[i].active_lineno = lineno;
}

Info GetOperandInfo(Operand op) {
    Info info = NULL;
    switch (op->kind) {
        case kVariable:
        case kVariablePointer:
        case kVariableAddress:
            info = variable_info + op->u.var_no;
            break;
        case kTemporary:
        case kTemporaryPointer:
        case kTemporaryAddress:
            info = temporary_info + op->u.temp_no;
            break;
    }
    return info;
}

void RenewOperand(Operand* op) {
    switch ((*op)->kind) {
        case kVariable:
            *op = ToOperandVariable(*op);
            break;
        case kVariablePointer:
            *op = ToOperandVariablePointer(*op);
            break;
        case kVariableAddress:
            *op = ToOperandVariableAddress(*op);
            break;
        case kTemporary:
            *op = ToOperandTemporary(*op);
            break;
        case kTemporaryPointer:
            *op = ToOperandTemporaryPointer(*op);
            break;
        case kTemporaryAddress:
            *op = ToOperandTemporaryAddress(*op);
            break;
    }
}

// connect operand in current code with later use info
void AssociateOperandWithCode(Operand op) {  
    Info info = GetOperandInfo(op);
    if (info) {
        op->active_lineno = info->active_lineno;
    }
}

// update info of current code for previous reference       
void UpdateActiveInfo(Operand op, int lineno, int active) {
    Info info = GetOperandInfo(op);
    if (info) {
        if (active) {
            info->active_lineno = lineno;
        } else {
            info->active_lineno = -1;
        }
    }
}

void RetrieveActiveInfo() {
    for (InterCodeIterator block_iter = basic_block_head; block_iter; block_iter = block_iter->next) {
        InitializeActiveInfo(variable_info, var_no+1,
                            block_iter->end ? block_iter->end->lineno : line_no+1);
        InitializeActiveInfo(temporary_info, temp_no+1, -1);

        InterCodes rbegin = block_iter->end ? block_iter->end->prev : iter->end,
                    rend = block_iter->begin->prev;
        for (InterCodes codes = rbegin; codes != rend; codes = codes->prev) {
            InterCode code = codes->code;
            switch (code->kind) {
                case kLabel:
                case kFunction:
                case kGoto:
                    break;
                case kAssign:
                    RenewOperand(&code->u.assign.op_left);
                    RenewOperand(&code->u.assign.op_right);
                    AssociateOperandWithCode(code->u.assign.op_left);
                    AssociateOperandWithCode(code->u.assign.op_right);
                    UpdateActiveInfo(code->u.assign.op_left, codes->lineno, 0);
                    UpdateActiveInfo(code->u.assign.op_right, codes->lineno, 1);
                    break;
                case kBinOp:
                    RenewOperand(&code->u.bin_op.op_result);
                    RenewOperand(&code->u.bin_op.op_1);
                    RenewOperand(&code->u.bin_op.op_2);
                    AssociateOperandWithCode(code->u.bin_op.op_result);
                    AssociateOperandWithCode(code->u.bin_op.op_1);
                    AssociateOperandWithCode(code->u.bin_op.op_2);
                    UpdateActiveInfo(code->u.bin_op.op_result, codes->lineno, 0);
                    UpdateActiveInfo(code->u.bin_op.op_1, codes->lineno, 1);
                    UpdateActiveInfo(code->u.bin_op.op_2, codes->lineno, 1);
                    break;
                case kConditionalJump:
                    RenewOperand(&code->u.conditional_jump.op_1);
                    RenewOperand(&code->u.conditional_jump.op_2);
                    AssociateOperandWithCode(code->u.conditional_jump.op_1);
                    AssociateOperandWithCode(code->u.conditional_jump.op_2);
                    UpdateActiveInfo(code->u.conditional_jump.op_1, codes->lineno, 1);
                    UpdateActiveInfo(code->u.conditional_jump.op_2, codes->lineno, 1);
                    break;
                case kReturn:
                    RenewOperand(&code->u.ret.op);
                    AssociateOperandWithCode(code->u.ret.op);
                    UpdateActiveInfo(code->u.ret.op, codes->lineno, 1);
                    break;
                case kDeclare:
                    RenewOperand(&code->u.declare.op);
                    AssociateOperandWithCode(code->u.declare.op);
                    UpdateActiveInfo(code->u.declare.op, codes->lineno, 0);
                    break;
                case kArg:
                    RenewOperand(&code->u.arg.op);
                    AssociateOperandWithCode(code->u.arg.op);
                    UpdateActiveInfo(code->u.arg.op, codes->lineno, 1);
                    break;
                case kCall:
                    RenewOperand(&code->u.call.op_result);
                    AssociateOperandWithCode(code->u.call.op_result);
                    UpdateActiveInfo(code->u.call.op_result, codes->lineno, 0);
                    break;
                case kParam:
                    RenewOperand(&code->u.param.op);
                    AssociateOperandWithCode(code->u.param.op);
                    UpdateActiveInfo(code->u.param.op, codes->lineno, 0);
                    break;
                case kIO:
                    RenewOperand(&code->u.io.op);
                    AssociateOperandWithCode(code->u.io.op);
                    UpdateActiveInfo(code->u.io.op, codes->lineno, code->u.io.type == kRead ? 0 : 1);
                    break;
            }
        }
    }
}

void OutputBlockInfo() {
    for (InterCodeIterator iter = basic_block_head; iter; iter = iter->next) {
        fprintf(stream, "block\n");
        for (InterCodes codes = iter->begin; codes != iter->end; codes = codes->next) {
            OutputInterCode(codes->code, 1);
        }
        puts("");
    }    
}

void GenerateAssign(InterCode inter_code) {
    Operand op_left = inter_code->u.assign.op_left,
            op_right = inter_code->u.assign.op_right;
    OperandType type_left = GetOperandType(op_left),
            type_right = GetOperandType(op_right);
    if (type_left == kValue) {
        if (type_right == kValue) {
            int reg_dst = GetRegForDefinition(op_left);
            int reg_src = GetReg(op_right);
            printf("%d %d\n", reg_dst, reg_src);
            FreeRegForValue(op_right);
            AddFinalCodeToFinalCodes(NewFinalCodeMove(reg_dst, reg_src));
        } else if (type_right == kPointer) {
            int reg_1 = GetRegForDefinition(op_left);
            int reg_2 = GetReg(op_right);
            FreeRegForValue(op_right);
            AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_1, reg_2, 0));
        } else if (type_right == kIntermediate) {
            int intermediate = op_right->u.int_value;
            int reg_no = GetRegForDefinition(op_left);
            AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_no, intermediate));
        } else {
            assert(type_right == kAddress);
            int reg_temp = GetRegForTemporary();
            GetStackAddress(reg_temp, op_right);
            int reg_res = GetRegForDefinition(op_left);
            FreeRegForValue(op_right);
            FreeRegForTemporary(reg_temp);
            AddFinalCodeToFinalCodes(NewFinalCodeMove(reg_res, reg_temp));
        }
    } else {
        assert(type_left == kPointer);
        if (type_right == kValue) {
            int reg_1 = GetReg(op_right);
            int reg_2 = GetRegForDefinition(op_left);
            FreeRegForValue(op_right);
            AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_1, reg_2));
        } else if (type_right == kPointer) {
            int reg_2 = GetReg(op_right);
            int reg_1 = GetRegForTemporary();
            FreeRegForValue(op_right);
            AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_1, reg_2, 0));
            int reg_0 = GetRegForDefinition(op_left);
            FreeRegForTemporary(reg_1);
            AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_1, reg_0));
        } else if (type_right == kIntermediate) {
            int intermediate = op_right->u.int_value;
            int reg_no = GetRegForTemporary();
            AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_no, intermediate));
            int reg_2 = GetRegForDefinition(op_left);
            FreeRegForTemporary(reg_no);
            AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_no, reg_2));
        } else {
            assert(type_right == kAddress);
            int reg_temp = GetRegForTemporary();
            GetStackAddress(reg_temp, op_right);
            int reg_res = GetRegForDefinition(op_left);
            FreeRegForValue(op_right);
            FreeRegForTemporary(reg_temp);
            AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res));
        }
    }
}

void GenerateFinalCodeBinOp(BinOpType type, int reg_res, int reg_1, int reg_2) {
    if (type == kArithDiv) {
        AddFinalCodeToFinalCodes(NewFinalCodeDiv(reg_1, reg_2));
        AddFinalCodeToFinalCodes(NewFinalCodeMflo(reg_res));
    } else {
        AddFinalCodeToFinalCodes(NewFinalCodeBinop(type, reg_res, reg_1, reg_2));
    }
}

void GetStackAddress(int reg_no, Operand op) {
    assert(op->kind == kVariableAddress || op->kind == kTemporaryAddress);
    Info info = GetOperandInfo(op);
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(reg_no, 30, info->offset));
}

void GenerateBinOp(InterCode inter_code) {
    Operand op_res = inter_code->u.bin_op.op_result,
            op_1 = inter_code->u.bin_op.op_1,
            op_2 = inter_code->u.bin_op.op_2;
    OperandType type_res = GetOperandType(op_res),
                type_1 = GetOperandType(op_1),
                type_2 = GetOperandType(op_2);
    BinOpType op_type = inter_code->u.bin_op.type;

    if ((type_1 == kPointer && type_2 == kValue)
        || (type_1 == kIntermediate && type_2 == kValue)
        || (type_1 == kIntermediate && type_2 == kPointer)
        || (type_1 == kAddress && type_2 == kValue)
        || (type_1 == kAddress && type_2 == kPointer)) {
        swap(&op_1, &op_2);
        SwapOperandType(&type_1, &type_2);
    }
    if (type_res == kValue) {
        if (type_1 == kValue) {
            if (type_2 == kValue) {
                int reg_1 = GetReg(op_1);
                int reg_2 = GetReg(op_2);
                int reg_res = GetRegForDefinition(op_res);
                FreeRegForValue(op_1);
                FreeRegForValue(op_2);
                GenerateFinalCodeBinOp(op_type, reg_res, reg_1, reg_2);
            } else if (type_2 == kPointer) {
                int reg_2 = GetReg(op_2);
                int reg_0 = GetRegForTemporary();
                FreeRegForValue(op_2);
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_0, reg_2, 0));
                int reg_1 = GetReg(op_1);
                int reg_res = GetRegForDefinition(op_res);
                FreeRegForValue(op_1);
                FreeRegForTemporary(reg_0);
                GenerateFinalCodeBinOp(op_type, reg_res, reg_1, reg_0);
            } else if (type_2 == kIntermediate) {
                int intermediate = op_2->u.int_value;
                int reg_1 = GetReg(op_1);
                if (op_type == kArithAdd) {
                    int reg_res = GetRegForDefinition(op_res);
                    AddFinalCodeToFinalCodes(
                        NewFinalCodeAddi(reg_res, reg_1, intermediate));
                } else {
                    int reg_temp = GetRegForTemporary();
                    AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_temp, intermediate));
                    int reg_res = GetRegForDefinition(op_res);
                    FreeRegForTemporary(reg_temp);
                    GenerateFinalCodeBinOp(op_type, reg_res, reg_1, reg_temp);
                }
                FreeRegForValue(op_1);
            } else {
                assert(type_2 == kAddress);
                int reg_temp = GetRegForTemporary();
                GetStackAddress(reg_temp, op_2);
                int reg_1 = GetReg(op_1);
                int reg_res = GetRegForDefinition(op_res);
                FreeRegForValue(op_1);
                FreeRegForTemporary(reg_temp);
                GenerateFinalCodeBinOp(op_type, reg_res, reg_1, reg_temp);
            }
        } else {
            assert(type_1 == kPointer);
            if (type_2 == kPointer) {
                int reg_1 = GetReg(op_1);
                int reg_10 = GetRegForTemporary();
                FreeRegForValue(op_1);
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_10, reg_1, 0));
                int reg_2 = GetReg(op_2);
                int reg_20 = GetRegForTemporary();
                FreeRegForValue(op_2);
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_20, reg_2, 0));
                int reg_res = GetRegForDefinition(op_res);
                FreeRegForTemporary(reg_10);
                FreeRegForTemporary(reg_20);
                GenerateFinalCodeBinOp(op_type, reg_res, reg_10, reg_20);
            } else {
                assert(type_2 == kIntermediate);
                int reg_1 = GetReg(op_1);
                int reg_10 = GetRegForTemporary();
                FreeRegForValue(op_1);
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_10, reg_1, 0));
                int intermediate = op_2->u.int_value;
                if (op_type == kArithAdd) {
                    int reg_res = GetRegForDefinition(op_res);
                    AddFinalCodeToFinalCodes(NewFinalCodeAddi(reg_res, reg_10, intermediate));
                } else {
                    int reg_temp = GetRegForTemporary();
                    AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_temp, intermediate));
                    int reg_res = GetRegForDefinition(op_res);
                    FreeRegForTemporary(reg_temp);
                    GenerateFinalCodeBinOp(op_type, reg_res, reg_10, reg_temp);
                }
                FreeRegForTemporary(reg_10);
            }
        } 
    } else {
        assert(type_res == kPointer);
        if (type_1 == kValue) {
            if (type_2 == kValue) {
                FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
                int reg_1 = GetReg(op_1);
                int reg_2 = GetReg(op_2);
                int reg_0 = GetRegForTemporary();
                FreeRegForValue(op_1);
                FreeRegForValue(op_2);
                GenerateFinalCodeBinOp(op_type, reg_0, reg_1, reg_2);
                int reg_res = GetRegForDefinition(op_res);
                FreeRegForTemporary(reg_0);
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_0, reg_res));
            } else if (type_2 == kPointer) {
                int reg_2 = GetReg(op_2);
                int reg_0 = GetRegForTemporary();
                FreeRegForValue(op_2);
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_0, reg_2, 0));
                int reg_1 = GetReg(op_1);
                int reg_temp = GetRegForTemporary();
                FreeRegForValue(op_1);
                GenerateFinalCodeBinOp(op_type, reg_temp, reg_1, reg_0);
                int reg_res = GetRegForDefinition(op_res);
                FreeRegForTemporary(reg_0);
                FreeRegForTemporary(reg_temp);
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res));
            } else if (type_2 == kIntermediate) {
                int intermediate = op_2->u.int_value;
                int reg_1 = GetReg(op_1);
                int reg_temp;
                if (op_type == kArithAdd) {
                    reg_temp = GetRegForTemporary();
                    AddFinalCodeToFinalCodes(
                        NewFinalCodeAddi(reg_temp, reg_1, intermediate));
                } else {
                    int reg_inter_temp = GetRegForTemporary();
                    AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_inter_temp, intermediate));
                    reg_temp = GetRegForTemporary();
                    FreeRegForTemporary(reg_inter_temp);
                    GenerateFinalCodeBinOp(op_type, reg_temp, reg_1, reg_inter_temp);
                }
                FreeRegForValue(op_1);

                int reg_res = GetRegForDefinition(op_res);
                FreeRegForTemporary(reg_temp);
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res));
            } else {
                assert(type_2 == kAddress);
                int reg_temp = GetRegForTemporary();
                GetStackAddress(reg_temp, op_2);
                int reg_1 = GetReg(op_1);
                int reg_0 = GetRegForTemporary();
                FreeRegForValue(op_1);
                FreeRegForTemporary(reg_temp);
                GenerateFinalCodeBinOp(op_type, reg_0, reg_1, reg_temp);
                int reg_res = GetRegForDefinition(op_res);
                FreeRegForTemporary(reg_0);
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_0, reg_res));
            }
        } else {
            assert(type_1 == kPointer);
            if (type_2 == kPointer) {
                int reg_1 = GetReg(op_1);
                int reg_10 = GetRegForTemporary();
                FreeRegForValue(op_1);
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_10, reg_1, 0));
                int reg_2 = GetReg(op_2);
                int reg_20 = GetRegForTemporary();
                FreeRegForValue(op_2);
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_20, reg_2, 0));
                int reg_temp = GetRegForTemporary();
                GenerateFinalCodeBinOp(op_type, reg_temp, reg_10, reg_20);
                int reg_res = GetRegForDefinition(op_res);
                FreeRegForTemporary(reg_temp);
                FreeRegForTemporary(reg_10);
                FreeRegForTemporary(reg_20);
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res));
            } else {
                assert(type_2 == kIntermediate);
                int reg_1 = GetReg(op_1);
                int reg_10 = GetRegForTemporary();
                FreeRegForValue(op_1);
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_10, reg_1, 0));
                int intermediate = op_2->u.int_value;
                int reg_temp;
                if (op_type == kArithAdd) {
                    reg_temp = GetRegForTemporary();
                    AddFinalCodeToFinalCodes(
                        NewFinalCodeAddi(reg_temp, reg_10, intermediate));
                } else {
                    int reg_inter_temp = GetRegForTemporary();
                    AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_inter_temp, intermediate));
                    reg_temp = GetRegForTemporary();
                    FreeRegForTemporary(reg_inter_temp);
                    GenerateFinalCodeBinOp(op_type, reg_temp, reg_10, reg_inter_temp);
                }
                FreeRegForTemporary(reg_10);

                int reg_res = GetRegForDefinition(op_res);
                FreeRegForTemporary(reg_temp);
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res));
            }
        }         
    }
}

void GenerateLabel(const char* name) {
    AddFinalCodeToFinalCodes(NewFinalCodeLabel(name));
    if (strcmp(name, "main") == 0) {
        AddFinalCodeToFinalCodes(NewFinalCodeMove(30, 29));
    }
}

void GenerateJc(InterCode inter_code) {
    RelopType type = inter_code->u.conditional_jump.relop_type;
    Operand op_1 = inter_code->u.conditional_jump.op_1;
    Operand op_2 = inter_code->u.conditional_jump.op_2;
    
    const char* name = GetLabelName(inter_code->u.conditional_jump.op_label);
    OperandType type_1 = GetOperandType(op_1);
    OperandType type_2 = GetOperandType(op_2);
    if (type_1 == kValue) {
        int reg_1 = GetReg(op_1);
        if (type_2 == kValue) {
            int reg_2 = GetReg(op_2);
            FreeRegForValue(op_2);
            AddFinalCodeToFinalCodes(NewFinalCodeJc(type, reg_1, reg_2, name));
        } else if (type_2 == kIntermediate) {
            int intermediate = op_2->u.int_value;
            int reg_temp = GetRegForTemporary();
            AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_temp, intermediate));
            FreeRegForTemporary(reg_temp);
            AddFinalCodeToFinalCodes(NewFinalCodeJc(type, reg_1, reg_temp, name));
        } else if (type_2 == kPointer) {
            int reg_2 = GetReg(op_2);
            int reg_temp = GetRegForTemporary();
            FreeRegForValue(op_2);
            FreeRegForTemporary(reg_temp);
            AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_temp, reg_2, 0));
            AddFinalCodeToFinalCodes(NewFinalCodeJc(type, reg_1, reg_temp, name));
        }
        FreeRegForValue(op_1);
    } else {
        assert(type_1 == kPointer);
        int reg_1 = GetReg(op_1);
        int reg_10 = GetRegForTemporary();
        AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_10, reg_1, 0));
        if (type_2 == kValue) {
            int reg_2 = GetReg(op_2);
            FreeRegForValue(op_2);
            AddFinalCodeToFinalCodes(NewFinalCodeJc(type, reg_10, reg_2, name));
        } else if (type_2 == kIntermediate) {
            int intermediate = op_2->u.int_value;
            int reg_temp = GetRegForTemporary();
            AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_temp, intermediate));
            FreeRegForTemporary(reg_temp);
            AddFinalCodeToFinalCodes(NewFinalCodeJc(type, reg_10, reg_temp, name));
        } else if (type_2 == kPointer) {
            int reg_2 = GetReg(op_2);
            int reg_temp = GetRegForTemporary();
            FreeRegForValue(op_2);
            FreeRegForTemporary(reg_temp);
            AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_temp, reg_2, 0));
            AddFinalCodeToFinalCodes(NewFinalCodeJc(type, reg_10, reg_temp, name));
        }
        FreeRegForValue(op_1);
        FreeRegForTemporary(reg_10);
    }
}

void GenerateReturn(Operand op) {
    OperandType type = GetOperandType(op);
    switch (type) {
        case kValue: {
            // move
            int reg_no = GetReg(op);
            AddFinalCodeToFinalCodes(NewFinalCodeMove(/*v_0*/ 2, reg_no));
            break;
        }
        case kPointer: {
            // lw
            int reg_no = GetReg(op);
            AddFinalCodeToFinalCodes(NewFinalCodeLw(2, reg_no, 0));
            break;
        }
        case kIntermediate: {
            // li
            int intermediate = op->u.int_value;
            AddFinalCodeToFinalCodes(NewFinalCodeLi(2, intermediate));
            break;
        }
    }
    AddFinalCodeToFinalCodes(NewFinalCodeJr());
}

int min(int a, int b) { return a < b ? a : b; }

void GenerateFuncCall(Operand op, const char* name) {
    // addi $sp, $sp, -4
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -4));
    // sw $fp, 0($sp)
    AddFinalCodeToFinalCodes(NewFinalCodeSw(30, 29));
    // addi $sp, $sp, -4
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -4));
    // sw $ra, 0($sp)
    AddFinalCodeToFinalCodes(NewFinalCodeSw(31, 29));
    // move $fp, $sp
    AddFinalCodeToFinalCodes(NewFinalCodeMove(30, 29));
    // jal func_name
    AddFinalCodeToFinalCodes(NewFinalCodeJal(name));
    // lw $ra, 0($sp)
    AddFinalCodeToFinalCodes(NewFinalCodeLw(31, 29, 0));
    // addi $sp, $sp, 4
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, 4));
    // lw $fp, 0($sp)
    AddFinalCodeToFinalCodes(NewFinalCodeLw(30, 29, 0));
    // addi $sp, $sp, 4
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, 4));
    if (arg_size) {
        // addi $sp, $sp, arg_size
        AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, arg_size));
    }
    // restore previous function call parameter
    for (int i = min(4, arg_no)-1; i >= 0; --i) {
        AddFinalCodeToFinalCodes(NewFinalCodeLw(/*a0*/4+i, 29, 0));
        AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, 4));
    }
    arg_no = 0;

    if (op) {
        OperandType type = GetOperandType(op);
        int reg_no = GetReg(op);
        switch (type) {
            case kValue:
                AddFinalCodeToFinalCodes(NewFinalCodeMove(reg_no, 2));
                break;
            case kPointer:
                AddFinalCodeToFinalCodes(NewFinalCodeSw(2, reg_no));
                break;
            default:
                assert(0);
        }
    }
}

void GenerateCall(InterCode code) {
    GenerateFuncCall(code->u.call.op_result, code->u.call.func_name);
}

void GenerateGoto(Operand op) {
    AddFinalCodeToFinalCodes(NewFinalCodeJ(GetLabelName(op)));
}

void SetStackAddress(Operand op, int offset) {
    Info info = GetOperandInfo(op);
    info->offset = offset;
}

void GenerateParam(Operand op) {
    if (param_no <= 4) {
        SetReg(param_no+4-1, op);
    } else {
        SetStackAddress(op, param_dec_no * 4 + 8);
    }
    --param_no;
    ++param_dec_no;
}

void PlaceInRegOrStack(int reg_no) {
    if (arg_no < 4) {
        // save previous value to stack for later recovery
        AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -4));
        AddFinalCodeToFinalCodes(NewFinalCodeSw(/*a0*/4+arg_no, 29));
        AddFinalCodeToFinalCodes(NewFinalCodeMove(/*a0*/4+arg_no, reg_no));
    } else {
        arg_size += 4;
        AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -4));
        AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_no, 29));
    }
}

void GenerateArg(Operand op) {
    OperandType type = GetOperandType(op);
    switch (type) {
        case kValue: {
            int reg_no = GetReg(op);
            FreeRegForValue(op);
            PlaceInRegOrStack(reg_no);
            break;
        }
        case kPointer: {
            int reg_no = GetReg(op);
            int reg_temp = GetRegForTemporary();
            FreeRegForValue(op);
            FreeRegForTemporary(reg_temp);
            AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_temp, reg_no, 0));
            PlaceInRegOrStack(reg_temp);
            break;
        }
        case kAddress: {
            int reg_temp = GetRegForTemporary();
            GetStackAddress(reg_temp, op);
            FreeRegForTemporary(reg_temp);
            PlaceInRegOrStack(reg_temp);
            break;
        }
    }
    ++arg_no;
}

void GenerateIO(InterCode code) {
    Operand op = code->u.io.op;
    if (code->u.io.type == kRead) {
        code_read = 1;
        GenerateFuncCall(op, "read");
    } else {
        code_write = 1;

        arg_no = 1;
        AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -4));
        AddFinalCodeToFinalCodes(NewFinalCodeSw(/*a0*/4, 29));

        Operand op = code->u.io.op;
        OperandType type = GetOperandType(op);
        switch (type) {
            case kValue: {
                int reg_no = GetReg(op);
                FreeRegForValue(op);
                AddFinalCodeToFinalCodes(NewFinalCodeMove(/*a0*/4, reg_no));
                break;
            }
            case kPointer: {
                int reg_no = GetReg(op);
                int reg_temp = GetRegForTemporary();
                FreeRegForValue(op);
                FreeRegForTemporary(reg_temp);
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_temp, reg_no, 0));
                AddFinalCodeToFinalCodes(NewFinalCodeMove(/*a0*/4, reg_temp));
                break;
            }
            case kIntermediate: {
                int intermediate = op->u.int_value;
                int reg_temp = GetRegForTemporary();
                FreeRegForTemporary(reg_temp);
                AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_temp, intermediate));
                AddFinalCodeToFinalCodes(NewFinalCodeMove(/*a0*/4, reg_temp));
                break;
            }
            default:
                assert(0);
        }
        GenerateFuncCall(NULL, "write");
    }
}

void GenerateFunEnd() {
    param_dec_no = 0;
    if (frame_size) {
        AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, frame_size));
        frame_size = 0;
    }
    AddFinalCodeToFinalCodes(NewFinalCodeFunEnd());
}

void GenerateDeclare(InterCode code) {
    Info info = GetOperandInfo(code->u.declare.op);
    info->offset = -(frame_size += code->u.declare.size);
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -code->u.declare.size));
}

void TranslateToFinalCode(InterCode code) {
    OutputInterCode(code, 1);
    switch (code->kind) {
        case kLabel:
            GenerateLabel(GetLabelName(code->u.label.op));
            break;
        case kFunction:
            GenerateLabel(code->u.function.func_name);
            break;
        case kAssign:
            GenerateAssign(code);
            break;
        case kBinOp:
            GenerateBinOp(code);
            break;
        case kGoto:
            GenerateGoto(code->u.go_to.op);
            break;
        case kConditionalJump:
            GenerateJc(code);
            break;
        case kReturn:
            GenerateReturn(code->u.ret.op);
            break;
        case kDeclare:
            GenerateDeclare(code);
            break;
        case kArg:
            GenerateArg(code->u.arg.op);
            break;
        case kCall:
            GenerateCall(code);
            break;
        case kParam:
            GenerateParam(code->u.param.op);
            break;
        case kIO:
            GenerateIO(code);
            break;
        case kFunEnd:
            GenerateFunEnd();
            break;
    }
}

void TranslateToFinalCodes() {
    for (InterCodeIterator iter = basic_block_head; iter; iter = iter->next) {
        // translate blocks one by one
        for (InterCodes codes = iter->begin; codes != iter->end; codes = codes->next) {
            if (param_no == 0 && codes->code->kind == kParam) {
                for (InterCodes param_code = codes; param_code != iter->end; param_code = param_code->next) {
                    if (param_code->code->kind != kParam) break;
                    ++param_no;
                }
            }
            TranslateToFinalCode(codes->code);
        }
        // write all variables back into memory
        puts("");
    }
}

void AppendRead() {
    AddFinalCodeToFinalCodes(NewFinalCodeLabel("read"));
    AddFinalCodeToFinalCodes(NewFinalCodeLi(2, 4));
    AddFinalCodeToFinalCodes(NewFinalCodeLa(4, "_prompt"));
    AddFinalCodeToFinalCodes(NewFinalCodeSyscall());
    AddFinalCodeToFinalCodes(NewFinalCodeLi(2, 5));
    AddFinalCodeToFinalCodes(NewFinalCodeSyscall());
    AddFinalCodeToFinalCodes(NewFinalCodeJr());
    AddFinalCodeToFinalCodes(NewFinalCodeFunEnd());
}

void AppendWrite() {
    AddFinalCodeToFinalCodes(NewFinalCodeLabel("write"));
    AddFinalCodeToFinalCodes(NewFinalCodeLi(2, 1));
    AddFinalCodeToFinalCodes(NewFinalCodeSyscall());
    AddFinalCodeToFinalCodes(NewFinalCodeLi(2, 4));
    AddFinalCodeToFinalCodes(NewFinalCodeLa(4, "_ret"));
    AddFinalCodeToFinalCodes(NewFinalCodeSyscall());
    AddFinalCodeToFinalCodes(NewFinalCodeMove(2, 0));
    AddFinalCodeToFinalCodes(NewFinalCodeJr());
    AddFinalCodeToFinalCodes(NewFinalCodeFunEnd());
}

void AppendIO() {
    if (code_read) AppendRead();
    if (code_write) AppendWrite();
}