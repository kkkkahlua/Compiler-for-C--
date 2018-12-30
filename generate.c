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

int param_dec_no = 0;
int code_read = 0;
int code_write = 0;
int frame_size = 0;
int frame_offset = 0;
int clean = 0;

FuncInfo func_info_head = NULL;
FuncInfo func_info_tail = NULL;

extern FinalCodeIterator final_code_iter_head;
extern FinalCodeIterator final_code_iter_tail;

extern int var_no;
extern int temp_no;
extern int line_no;
extern InterCodeIterator iter;
extern void swap(Operand* op_1, Operand* op_2);

void GenerateFinalCode(InterCodes codes) {
    variable_info = NewInfo(var_no+1);
    temporary_info = NewInfo(temp_no+1);

    ConstructBasicBlock(codes);
    
    // RetrieveActiveInfo();

    // OutputBlockInfo();

    TranslateToFinalCodes();

    AppendIO();

    OutputFinalCodes();
}

Info NewInfo(int num) {
    Info info = (Info)malloc(sizeof(Info_) * num);
    for (int i = 0; i < num; ++i) {
        info[i].reg_no = info[i].offset = -1;
    }
    return info;
}

void InitializeInfo(Info info, int num) {
    for (int i = 0; i < num; ++i) info[i].reg_no = -1;
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

void RetrieveActiveInfo(InterCodeIterator block_iter) {
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

void OutputBlockInfo() {
    for (InterCodeIterator iter = basic_block_head; iter; iter = iter->next) {
        fprintf(stream, "block\n");
        for (InterCodes codes = iter->begin; codes != iter->end; codes = codes->next) {
            OutputInterCode(codes->code, 1);
        }
        fprintf(stream, "\n");
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
            AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_1, reg_2, 0));
        } else if (type_right == kPointer) {
            int reg_2 = GetReg(op_right);
            int reg_1 = GetRegForTemporary();
            FreeRegForValue(op_right);
            AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_1, reg_2, 0));
            int reg_0 = GetRegForDefinition(op_left);
            FreeRegForTemporary(reg_1);
            AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_1, reg_0, 0));
        } else if (type_right == kIntermediate) {
            int intermediate = op_right->u.int_value;
            int reg_no = GetRegForTemporary();
            AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_no, intermediate));
            int reg_2 = GetRegForDefinition(op_left);
            FreeRegForTemporary(reg_no);
            AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_no, reg_2, 0));
        } else {
            assert(type_right == kAddress);
            int reg_temp = GetRegForTemporary();
            GetStackAddress(reg_temp, op_right);
            int reg_res = GetRegForDefinition(op_left);
            FreeRegForValue(op_right);
            FreeRegForTemporary(reg_temp);
            AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res, 0));
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
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_0, reg_res, 0));
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
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res, 0));
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
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res, 0));
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
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_0, reg_res, 0));
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
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res, 0));
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
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res, 0));
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

void SaveRegisterOnStack(int reg_no) {
    frame_offset += 4;
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -4));
    AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_no, 29, 0));
}

void PopRegisterFromStack(int reg_no) {
    frame_offset -= 4;
    AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_no, 29, 0));
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, 4));
}

void GenerateCleanUp() {
    if (frame_size) {
        AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, frame_size));
    }
    if (strcmp(func_info_tail->name, "read") 
            && strcmp(func_info_tail->name, "write")
            && strcmp(func_info_tail->name, "main")) {
        for (int i = 23; i >= 16; --i) {
            PopRegisterFromStack(i);
        }
    }
    if (param_dec_no) {
        func_info_tail->param_num = param_dec_no;
        param_dec_no = 0;
    }
    clean = 1;
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
    GenerateCleanUp();
    AddFinalCodeToFinalCodes(NewFinalCodeJr());
}

int GetParamNum(const char* name) {
    for (FuncInfo info = func_info_head; info; info = info->next) {
        if (!strcmp(info->name, name)) return info->param_num;
    }
}

void GenerateFuncCall(Operand op, const char* name) {
    // addi $sp, $sp, -4
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -4));
    // sw $fp, 0($sp)
    AddFinalCodeToFinalCodes(NewFinalCodeSw(30, 29, 0));
    // addi $sp, $sp, -4
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -4));
    // sw $ra, 0($sp)
    AddFinalCodeToFinalCodes(NewFinalCodeSw(31, 29, 0));
    // move $fp, $sp
    AddFinalCodeToFinalCodes(NewFinalCodeMove(30, 29));
    // caller save register
    if (strcmp(name, "read") && strcmp(name, "write")) {
        for (int reg_no = 8; reg_no <= 15; ++reg_no) {
            SaveRegisterOnStack(reg_no);
        }
        for (int reg_no = 24; reg_no <= 25; ++reg_no) {
            SaveRegisterOnStack(reg_no);
        }
    }
    // jal func_name
    AddFinalCodeToFinalCodes(NewFinalCodeJal(name));
    // caller recover register
    if (strcmp(name, "read") && strcmp(name, "write")) {
        for (int reg_no = 25; reg_no >= 24; --reg_no) {
            PopRegisterFromStack(reg_no);
        }
        for (int reg_no = 15; reg_no >= 8; --reg_no) {
            PopRegisterFromStack(reg_no);
        }
    }
    // lw $ra, 0($sp)
    AddFinalCodeToFinalCodes(NewFinalCodeLw(31, 29, 0));
    // addi $sp, $sp, 4
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, 4));
    // lw $fp, 0($sp)
    AddFinalCodeToFinalCodes(NewFinalCodeLw(30, 29, 0));
    // addi $sp, $sp, 4
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, 4));

    int arg_size = GetParamNum(name) * 4;
    if (arg_size) {
        // addi $sp, $sp, arg_size
        AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, arg_size));
        arg_size = 0;
    }

    if (op) {
        OperandType type = GetOperandType(op);
        int reg_no = GetRegForDefinition(op);
        switch (type) {
            case kValue:
                AddFinalCodeToFinalCodes(NewFinalCodeMove(reg_no, 2));
                break;
            case kPointer:
                AddFinalCodeToFinalCodes(NewFinalCodeSw(2, reg_no, 0));
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
    SetStackAddress(op, param_dec_no * 4 + 8);
    ++param_dec_no;
}

void PushOnStack(int reg_no) {
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -4));
    AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_no, 29, 0));
}

void GenerateArg(Operand op) {
    OperandType type = GetOperandType(op);
    switch (type) {
        case kValue: {
            int reg_no = GetReg(op);
            FreeRegForValue(op);
            PushOnStack(reg_no);
            break;
        }
        case kPointer: {
            int reg_no = GetReg(op);
            int reg_temp = GetRegForTemporary();
            FreeRegForValue(op);
            FreeRegForTemporary(reg_temp);
            AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_temp, reg_no, 0));
            PushOnStack(reg_temp);
            break;
        }
        case kAddress: {
            int reg_temp = GetRegForTemporary();
            GetStackAddress(reg_temp, op);
            FreeRegForTemporary(reg_temp);
            PushOnStack(reg_temp);
            break;
        }
        case kIntermediate: {
            int reg_temp = GetRegForTemporary();
            AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_temp, op->u.int_value));
            FreeRegForTemporary(reg_temp);
            PushOnStack(reg_temp);
            break;
        }
    }
}

void GenerateIO(InterCode code) {
    Operand op = code->u.io.op;
    if (code->u.io.type == kRead) {
        code_read = 1;
        GenerateFuncCall(op, "read");
    } else {
        code_write = 1;

        AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -4));
        AddFinalCodeToFinalCodes(NewFinalCodeSw(/*a0*/4, 29, 0));

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
        // restore previous a0 value
        AddFinalCodeToFinalCodes(NewFinalCodeLw(4, 29, 0));
        AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, 4));
    }
}

void GenerateFunEnd() {
    if (!clean) GenerateCleanUp();
    AddFinalCodeToFinalCodes(NewFinalCodeFunEnd());
}

void GenerateDeclare(InterCode code) {
    Info info = GetOperandInfo(code->u.declare.op);
    frame_size += code->u.declare.size;
    frame_offset += code->u.declare.size;
    info->offset = -frame_offset;
    AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -code->u.declare.size));
}

void GenerateFunction(InterCode code) {
    frame_size = frame_offset = clean = 0;
    FuncInfo func = (FuncInfo)malloc(sizeof(FuncInfo_));
    func->name = code->u.function.func_name;
    func->param_num = 0;
    func->next = NULL;
    if (!func_info_head) {
        func_info_head = func_info_tail = func;
    } else {
        func_info_tail->next = func;
        func_info_tail = func;
    }
    GenerateLabel(code->u.function.func_name);
    if (strcmp(code->u.function.func_name, "read") 
        && strcmp(code->u.function.func_name, "write")
        && strcmp(code->u.function.func_name, "main")) {
        for (int reg_no = 16; reg_no <= 23; ++reg_no) {
            SaveRegisterOnStack(reg_no);
        }
    }
}

void TranslateToFinalCode(InterCode code) {
    OutputInterCode(code, 1);
    switch (code->kind) {
        case kLabel:
            GenerateLabel(GetLabelName(code->u.label.op));
            break;
        case kFunction: {
            GenerateFunction(code);
            break;
        }
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
            // GenerateFunEnd();
            break;
    }
}

void SaveVariablesOnStack() {
    for (int i = 1; i <= var_no; ++i) {
        Info info = variable_info + i;
        if (info->reg_no == -1) continue;
        if (info->offset == -1) {
            AddFinalCodeToFinalCodes(NewFinalCodeAddi(29, 29, -4));
            AddFinalCodeToFinalCodes(NewFinalCodeSw(info->reg_no, 29, 0));
            frame_size += 4;
            frame_offset += 4;
            info->offset = -frame_offset;
            info->reg_no = -1;
        } else {
            AddFinalCodeToFinalCodes(NewFinalCodeSw(info->reg_no, 30, info->offset));
            info->reg_no = -1;
        }
    }
}

void TranslateToFinalCodes() {
    for (InterCodeIterator block_iter = basic_block_head; block_iter; 
                                            block_iter = block_iter->next) {
        // translate blocks one by one
        FinalCodeIterator final_iter = NewFinalCodeIterator();
        if (!final_code_iter_head) {
            final_code_iter_head = final_code_iter_tail = final_iter;
        } else {
            final_code_iter_tail->next = final_iter;
            final_code_iter_tail = final_iter;
        }

        // initialize at the beginning of each basic block
        InitializeInfo(variable_info, var_no+1);
        InitializeInfo(temporary_info, temp_no+1);
        RetrieveActiveInfo(block_iter);
        InitializeRegs();

        for (InterCodes codes = block_iter->begin; codes != block_iter->end; 
                                                            codes = codes->next) {
            TranslateToFinalCode(codes->code);
        }
        SaveVariablesOnStack();
        InterCodes rbegin = block_iter->end ? block_iter->end->prev : iter->end;
        switch (rbegin->code->kind) {
            case kFunEnd:
            case kConditionalJump:
            case kGoto:
            case kReturn:
                PostponeJump();
        }
        if (rbegin->code->kind == kFunEnd) {
            AddFinalCodeToFinalCodes(NewFinalCodeFunEnd());
        }
        fprintf(stream, "\n");
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