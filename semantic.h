#ifndef __SEMANTIC_H_INCLUDED_
#define __SEMANTIC_H_INCLUDED_

#include "tree.h"

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct ParamList_* ParamList;

struct Type_ {
    enum { kBASIC, kARRAY, kSTRUCTURE, kFUNCTION } kind;
    union {
        int basic;      //  0: int; 1: float;
        struct { Type elem; int size; } array;
        struct { char* name; FieldList field_list; } structure;
        struct { Type ret; ParamList param_list; } function;
    } u;
};

struct ParamList_ {
    Type type;
    ParamList tail;
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