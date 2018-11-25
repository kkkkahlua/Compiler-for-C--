#ifndef __TRANSLATE_H_INCLUDED
#define __TRANSLATE_H_INCLUDED

#include "InterCode.h"

#include "semantic.h"

//  TODO: whether to use DAG in processing

InterCodeIterator TranslateFunDef(const char* name, DefList param_list) {
    InterCodes codes = NULL;
    InterCodeIterator iter;

    InterCode code;
    code->kind = kFunction;
    code->u.function.func_name = NewString(name);
    AddCodeToCodes(code, codes, &iterator);

    while (1) {
        if (!param_list) return iter;
        InterCode code;
        code->kind = kParam;
        code->u.param.op = NewOperandVariable(param_list->type->var_no);
        AddCodeToCodes(code, codes, &iterator);
        
        param_list = param_list->tail;
    }
}

#endif