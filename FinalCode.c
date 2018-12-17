#include "FinalCode.h"

#include "reg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Info variable_info;
Info temporary_info;

InterCodeIterator basic_block_head;
InterCodeIterator basic_block_tail;

extern int var_no;
extern int temp_no;
extern int line_no;
extern InterCodeIterator iter;

void RetrieveActiveInfo();

void GenerateFinalCode(InterCodes codes) {
    variable_info = InitializeInfo(var_no+1);
    temporary_info = InitializeInfo(temp_no+1);

    ConstructBasicBlock(codes);

    RetrieveActiveInfo();

    OutputBlockInfo();

    TranslateToFinalCodes();
}

Info InitializeInfo(int num) {
    Info info = (Info)malloc(sizeof(Info_) * num);
    for (int i = 0; i < num; ++i) {
        info[i].reg_no[0] = info[i].reg_no[1] = info[i].reg_no[2] = -1;
        info[i].active_info.code = NULL;
        info[i].active_info.lineno = -1;
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
    for (int i = 0; i < num; ++i) info[i].active_info.lineno = lineno;
}

void AssociateOperandWithCode(Operand* op, InterCodes code, int active) {  
    Info info = NULL;
    switch ((*op)->kind) {
        case kVariable:
            *op = ToOperandVariable(*op);
            info = variable_info + (*op)->u.var_no;
            break;
        case kVariablePointer:
            *op = ToOperandVariablePointer(*op);
            info = variable_info + (*op)->u.var_no;
            break;
        case kVariableAddress:
            *op = ToOperandVariableAddress(*op);
            info = variable_info + (*op)->u.var_no;
            break;
        case kTemporary:
            *op = ToOperandTemporary(*op);
            info = temporary_info + (*op)->u.temp_no;
            break;
        case kTemporaryPointer:
            *op = ToOperandTemporaryPointer(*op);
            info = temporary_info + (*op)->u.temp_no;
            break;
        case kTemporaryAddress:
            *op = ToOperandTemporaryAddress(*op);
            info = temporary_info + (*op)->u.temp_no;
            break;
    }
    if (info) {
        // 1. connect operand in current code with later use info
        // 2. update info of current code for previous reference

        (*op)->active_info.lineno = info->active_info.lineno;
        (*op)->active_info.code = info->active_info.code;
        if (active) {
            info->active_info.lineno = code->lineno;
            info->active_info.code = code;
        } else {
            info->active_info.lineno = -1;
            info->active_info.code = NULL;
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
                    AssociateOperandWithCode(&code->u.assign.op_left, codes, 0);
                    AssociateOperandWithCode(&code->u.assign.op_right, codes, 1);
                    break;
                case kBinOp:
                    AssociateOperandWithCode(&code->u.bin_op.op_result, codes, 0);
                    AssociateOperandWithCode(&code->u.bin_op.op_1, codes, 1);
                    AssociateOperandWithCode(&code->u.bin_op.op_2, codes, 1);
                    break;
                case kConditionalJump:
                    AssociateOperandWithCode(&code->u.conditional_jump.op_1, codes, 1);
                    AssociateOperandWithCode(&code->u.conditional_jump.op_2, codes, 1);
                    break;
                case kReturn:
                    AssociateOperandWithCode(&code->u.ret.op, codes, 1);
                    break;
                case kDeclare:
                    AssociateOperandWithCode(&code->u.declare.op, codes, 0);
                    break;
                case kArg:
                    AssociateOperandWithCode(&code->u.arg.op, codes, 1);
                    break;
                case kCall:
                    AssociateOperandWithCode(&code->u.call.op_result, codes, 0);
                    break;
                case kParam:
                    AssociateOperandWithCode(&code->u.param.op, codes, 0);
                    break;
                case kIO:
                    AssociateOperandWithCode(&code->u.io.op, codes, 1);
                    break;
            }
        }
    }
}

void OutputBlockInfo() {
    for (InterCodeIterator iter = basic_block_head; iter; iter = iter->next) {
        puts("block");
        for (InterCodes codes = iter->begin; codes != iter->end; codes = codes->next) {
            OutputInterCode(codes->code, 1);
        }
        puts("");
    }    
}

void TranslateFinalAssign(InterCode inter_code) {
    Operand op_left = inter_code->u.assign.op_left,
            op_right = inter_code->u.assign.op_right;
    OperandType type_left = GetOperandType(op_left),
            type_right = GetOperandType(op_right);
    if (type_left == kValue) {
        if (type_right == kValue) {
            FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
            code->kind = kFinalMove;
            code->u.move.reg_dst = GetReg(op_left);
            code->u.move.reg_src = GetReg(op_right);
            AddFinalCodeToFinalCodes(code);
        } else if (type_right == kPointer) {
            FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
            code->kind = kFinalLw;
            code->u.lw.reg_1 = GetReg(op_left);
            code->u.lw.reg_2 = GetReg(op_right);
            AddFinalCodeToFinalCodes(code);
        } else if (type_right == kIntermediate) {
            int intermediate = op_right->u.int_value;
            int reg_no = GetReg(op_left);
            AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_no, intermediate));
        } else {
            assert(type_right == kAddress);
            // TODO: address
        }
    } else {
        assert(type_left == kPointer);
        if (type_right == kValue) {
            FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
            code->kind = kFinalSw;
            code->u.sw.reg_1 = GetReg(op_right);
            code->u.sw.reg_2 = GetReg(op_left);
            AddFinalCodeToFinalCodes(code);
        } else if (type_right == kPointer) {
            int reg_2 = GetReg(op_right);
            int reg_1 = GetRegForTemporary();
            FinalCode code1 = NewFinalCodeLw(reg_1, reg_2);
            AddFinalCodeToFinalCodes(code1);
            FinalCode code2 = (FinalCode)malloc(sizeof(FinalCode_));
            code2->kind = kFinalSw;
            code2->u.sw.reg_1 = code1->u.lw.reg_1;
            code2->u.sw.reg_2 = GetReg(op_left);
            AddFinalCodeToFinalCodes(code2);
        } else if (type_right == kIntermediate) {
            int intermediate = op_right->u.int_value;
            int reg_no = GetRegForTemporary();
            AddFinalCodeToFinalCodes(NewFinalCodeLi(reg_no, intermediate));
            int reg_2 = GetReg(op_left);
            AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_no, reg_2));
        } else {
            assert(type_right == kAddress);
            // TODO: address
        }
    }
}

FinalCode NewFinalCodeLw(int reg_1, int reg_2) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalLw;
    code->u.lw.reg_1 = reg_1;
    code->u.lw.reg_2 = reg_2;
    return code;
}

FinalCode NewFinalCodeSw(int reg_1, int reg_2) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalSw;
    code->u.sw.reg_1 = reg_1;
    code->u.sw.reg_2 = reg_2;
    return code;
}

FinalCode NewFinalCodeBinop(BinOpType type, int reg_res, int reg_1, int reg_2) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode));
    code->kind = kFinalBinop;
    code->u.binop.reg_res = reg_res;
    code->u.binop.reg_1 = reg_1;
    code->u.binop.reg_2 = reg_2;
    return code;
}

FinalCode NewFinalCodeLi(int reg_no, int intermediate) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode));
    code->kind = kFinalLi;
    code->u.li.reg_no = reg_no;
    code->u.li.intermediate = intermediate;
    return code;
}

void TranslateFinalBinOp(InterCode inter_code) {
    Operand op_res = inter_code->u.bin_op.op_result,
            op_1 = inter_code->u.bin_op.op_1,
            op_2 = inter_code->u.bin_op.op_2;
    OperandType type_res = GetOperandType(op_res),
                type_1 = GetOperandType(op_1),
                type_2 = GetOperandType(op_2);
    BinOpType op_type = inter_code->u.bin_op.type;

    if ((type_1 == kPointer && type_2 == kValue)
        || (type_1 == kIntermediate && type_2 == kValue)
        || (type_1 == kIntermediate && type_2 == kPointer)) {
        swap(&op_1, &op_2);
        SwapOperandType(&type_1, &type_2);
    }
    if (type_res == kValue) {
        if (type_1 == kValue) {
            if (type_2 == kValue) {
                FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
                int reg_1 = GetReg(op_1);
                int reg_2 = GetReg(op_2);
                int reg_res = GetReg(op_res);
                AddFinalCodeToFinalCodes(
                    NewFinalCodeBinop(op_type, reg_res, reg_1, reg_2));
            } else if (type_2 == kPointer) {
                int reg_2 = GetReg(op_2);
                int reg_0 = GetRegForTemporary();
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_0, reg_2));
                int reg_1 = GetReg(op_1);
                int reg_res = GetReg(op_res);
                AddFinalCodeToFinalCodes(
                    NewFinalCodeBinop(op_type, reg_res, reg_1, reg_0));
            } else if (type_2 == kIntermediate) {
                int intermediate = op_2->u.int_value;
                int reg_1 = GetReg(op_1);
                int reg_res = GetReg(op_res);
                AddFinalCodeToFinalCodes(
                    NewFinalCodeAddi(reg_res, reg_1, intermediate));
            } else {
                assert(type_2 == kAddress);
                // TODO: address
            }
        } else {
            assert(type_1 == kPointer);
            if (type_2 == kPointer) {
                int reg_1 = GetReg(op_1);
                int reg_10 = GetRegForTemporary();
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_10, reg_1));
                int reg_2 = GetReg(op_2);
                int reg_20 = GetRegForTemporary();
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_20, reg_2));
                int reg_res = GetReg(op_res);
                AddFinalCodeToFinalCodes(
                    NewFinalCodeBinop(op_type, reg_res, reg_10, reg_20));
            } else {
                assert(type_2 == kIntermediate);
                int reg_1 = GetReg(op_1);
                int reg_10 = GetRegForTemporary();
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_10, reg_1));
                int intermediate = op_2->u.int_value;
                int reg_res = GetReg(op_res);
                AddFinalCodeToFinalCodes(NewFinalCodeAddi(reg_res, reg_10, intermediate));
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
                AddFinalCodeToFinalCodes(
                    NewFinalCodeBinop(op_type, reg_0, reg_1, reg_2));
                int reg_res = GetReg(op_res);
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_0, reg_res));
            } else if (type_2 == kPointer) {
                int reg_2 = GetReg(op_2);
                int reg_0 = GetRegForTemporary();
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_0, reg_2));
                int reg_1 = GetReg(op_1);
                int reg_temp = GetRegForTemporary();
                AddFinalCodeToFinalCodes(
                    NewFinalCodeBinop(op_type, reg_temp, reg_1, reg_0));
                int reg_res = GetReg(op_res);
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res));
            } else if (type_2 == kIntermediate) {
                int intermediate = op_2->u.int_value;
                int reg_1 = GetReg(op_1);
                int reg_temp = GetRegForTemporary();
                AddFinalCodeToFinalCodes(
                    NewFinalCodeAddi(reg_temp, reg_1, intermediate));
                int reg_res = GetReg(op_res);
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res));
            } else {
                assert(type_2 == kAddress);
                // TODO: address
            }
        } else {
            assert(type_1 == kPointer);
            if (type_2 == kPointer) {
                int reg_1 = GetReg(op_1);
                int reg_10 = GetRegForTemporary();
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_10, reg_1));
                int reg_2 = GetReg(op_2);
                int reg_20 = GetRegForTemporary();
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_20, reg_2));
                int reg_temp = GetRegForTemporary();
                AddFinalCodeToFinalCodes(
                    NewFinalCodeBinop(op_type, reg_temp, reg_10, reg_20));
                int reg_res = GetReg(op_res);
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res));
            } else {
                assert(type_2 == kIntermediate);
                int reg_1 = GetReg(op_1);
                int reg_10 = GetRegForTemporary();
                AddFinalCodeToFinalCodes(NewFinalCodeLw(reg_10, reg_1));
                int intermediate = op_2->u.int_value;
                int reg_temp = GetRegForTemporary();
                AddFinalCodeToFinalCodes(
                    NewFinalCodeAddi(reg_temp, reg_10, intermediate));
                int reg_res = GetReg(op_res);
                AddFinalCodeToFinalCodes(NewFinalCodeSw(reg_temp, reg_res));
            }
        }         
    }
}

void TranslateFinalLabel(const char* name) {
    FinalCode code = (FinalCode)malloc(sizeof(FinalCode_));
    code->kind = kFinalLabel;
    code->u.label.name = name;
    AddFinalCodeToFinalCodes(code);
}

void TranslateToFinalCode(InterCode code) {
    switch (code->kind) {
        case kLabel:
            TranslateFinalLabel(GetOperandName(code->u.label.op));
            break;
        case kFunction:
            TranslateFinalLabel(code->u.function.func_name);
            break;
        case kAssign:
            TranslateFinalAssign(code);
            break;
        case kBinOp:
            // TODO: special case - div
            TranslateFinalBinOp(code);
            break;
    }
}

void TranslateToFinalCodes() {
    for (InterCodeIterator iter = basic_block_head; iter; iter = iter->next) {
        // translate blocks one by one
        for (InterCodes codes = iter->begin; codes != iter->end; codes = codes->next) {
            TranslateToFinalCode(codes->code);
        }
        // write all variables back into memory
        puts("");
    }
}