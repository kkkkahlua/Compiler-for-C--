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

int LookupVariable(const char* name, Type* type, int layer);

int LookupStructDefinition(const char* name, Type* type, int layer);

int LookupFunction(const char* name, Type* type_ret, ParamList* param_list, int is_call);

int LookupFieldInStruct(const char* name, Type type_struct, Type* type_field);

void insert(const char* name, Type type, int layer);

void RemoveVariable(const char* name, int layer);

void OutputLayerNode(const char* name, LayerNode* layer_node);

void UpdateFunctionStatus(const char* name);

int TypeConsistentParamList(ParamList param_list_ori, ParamList param_list_now);

int TypeConsistent(Type type_ori, Type type_now);



#endif