#ifndef __TRANSLATE_H_INCLUDED
#define __TRANSLATE_H_INCLUDED

#include "InterCode.h"

#include "semantic.h"
#include "SymbolTable.h"

Operand ArithCalc(const char* op_arith, Operand op_1, Operand op_2);

void TranslateAddressOf(Operand dst_op, Operand src_op);

void TranslateArg(Operand op);

void TranslateAssign(Operand* dst_op, Operand src_op);

void TranslateBinOp(TreeNode* bin_op, Operand* op_result, Operand op_l, Operand op_r);

void TranslateBinOpType(BinOpType bin_op_type, Operand* op_result, Operand op_l, Operand op_r);

Type TranslateCond(TreeNode* exp_1, Operand label_true, Operand label_false);

void TranslateConditionalJump(Operand op_1, Operand op_2, Operand op_label, RelopType relop_type);

void TranslateExp(TreeNode* exp, int dec_var_no, Type* type);

void TranslateFunCall(Operand* dst_op, const char* name);

void TranslateFunDef(const char* name, DefList param_list);

void TranslateGoto(Operand op_label);

void TranslateTemporary(Operand* op_dst, Operand op_src);

void TranslateLabel(Operand label);

void TranslateRead(Operand* op_dst);

void TranslateReturn(Operand op);

void TranslateWrite();

#endif