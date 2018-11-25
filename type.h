#ifndef __TYPE_H_INCLUDED
#define __TYPE_H_INCLUDED

#include "tree.h"

typedef struct Type_* Type;
typedef struct DefList_* DefList;
typedef struct FunctionList_* FunctionList;

typedef struct Type_ {
    enum { kBASIC, kARRAY, kSTRUCTURE, kFUNCTION } kind;
    union {
        int basic;      //  0: int; 1: float;
        struct { Type elem; int size; } array;
        struct { char* name; DefList field_list; } structure;
        struct { char* name; Type type_ret; DefList param_list; int defined; } function;
    } u;
} Type_;

typedef struct DefList_ {
    const char* name;
    Type type;
    DefList tail;
} DefList_;

typedef struct FunctionList_ {
    const char* name;
    int lineno;
    FunctionList tail;
} FunctionList_;

void OutputType(Type type, int indent);

Type GetTypeFunction(TreeNode* fun_def, Type type_ret);

Type GetType(TreeNode* root);

Type NewTypeFunction(const char* name, Type type_ret, DefList param_list, int defined);

Type NewTypeBasic(int basic);

char* NewString(const char* str);

#endif