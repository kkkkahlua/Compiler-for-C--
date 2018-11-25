#ifndef __TRANSLATE_H_INCLUDED
#define __TRANSLATE_H_INCLUDED

#include "InterCode.h"

#include "semantic.h"
#include "SymbolTable.h"

void TranslateFunDef(const char* name, DefList param_list);

void TranslateExp(TreeNode* exp, int dec_var_no, Type* type);

void TranslateAssign(Operand dst_op, Operand src_op);

void TranslateFunCall(Operand dst_op, const char* name);

void TranslateBinOp(TreeNode* bin_op, Operand op_result, Operand op_l, Operand op_r);

#endif