#ifndef __SEMANTIC_H_INCLUDED_
#define __SEMANTIC_H_INCLUDED_

#include "tree.h"

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;

struct Type_ {
    enum { kBASIC, kARRAY, kSTRUCTURE } kind;
    union {
        int basic;      //  0: int; 1: float;
        struct { Type elem; int size; } array;
        FieldList structure;
    } u;
};

struct FieldList_ {
    char* name;
    Type type;
    FieldList tail;
};

void AnalyzeProgram(TreeNode* root);

void AnalyzeExtDefList(TreeNode* root);

void AnalyzeExtDef(TreeNode* root);



#endif