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

void TranslateToFinalCode(InterCode code) {
    switch (code->kind) {
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