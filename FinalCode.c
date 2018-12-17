#include "FinalCode.h"

#include "reg.h"

#include <stdio.h>
#include <stdlib.h>

int* variable_reg;
int* temporary_reg;
extern int var_no;
extern int temp_no;

void InitializeReg();
void TranslateToFinalCode(InterCode code);

void TranslateToFinalCodes(InterCodes codes) {
    InitializeReg();

    ConstructBasicBlock(codes);

    while (1) {
        if (!codes) return;
        TranslateToFinalCode(codes->code);
        codes = codes->next;
    }
}

void TranslateToFinalCode(InterCode code) {
    // switch (code->kind) {
    //     case kLabel:
    //         fprintf(stdout, code->u.label.op->u.)
    // }
}

void InitializeReg() {
    variable_reg = (int*)malloc(4 * (var_no+1));
    temporary_reg = (int*)malloc(4 * (temp_no+1));
    for (int i = 0; i < var_no+1; ++i) variable_reg[i] = -1;
    for (int i = 0; i < temp_no+1; ++i) temporary_reg[i] = -1;
}