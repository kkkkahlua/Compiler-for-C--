#ifndef __SYMBOLTABLE_H_INCLUDED
#define __SYMBOLTABLE_H_INCLUDED

#include "semantic.h"

typedef struct LayerNode LayerNode;
typedef struct SymbolTableNode SymbolTableNode;

typedef struct SymbolTableNode {
    const char* name;
    Type type;
    LayerNode* layer_node;
    SymbolTableNode* next;
} SymbolTableNode;

typedef struct LayerNode {
    int layer;
    LayerNode* up;
} LayerNode;

SymbolTableNode* symbol_table[16384];

unsigned int hash_pjw(const char* name);

int LookupVariable(const char* name);

int LookupFunction(const char* name, Type type_ret, ParamList param_list, int is_define);

#endif