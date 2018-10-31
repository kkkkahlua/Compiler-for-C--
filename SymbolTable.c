#include "SymbolTable.h"

#include <string.h>

unsigned int hash_pjw(const char* name) {
    unsigned int val = 0, i;
    for (; *name; ++name) {
        val = (val << 2) + *name;
        if (i == val & ~0x3fff) val = (val ^ (i >> 12)) & 0x3fff;
    }
    return val;
}

int LookupVariableAt(const char* name, SymbolTableNode* symbol_table_node) {
    if (symbol_table_node == NULL) return 0;
    if (strcmp(symbol_table_node->name, name) == 0) return 1;
    return LookupVariableAt(name, symbol_table_node->next);
}

int LookupVariable(const char* name) {
    unsigned int val = hash_pjw(name);
    return LookupVariableAt(name, symbol_table[val]);
}

int TypeConsistent(Type type_ori, Type type_now) {
    if (type_ori->kind != type_now->kind) return 0;
    switch (type_ori->kind) {
        case kBASIC: return type_ori->u.basic == type_now->u.basic;
        case kARRAY: return TypeConsistent(type_ori->u.array.elem, type_now->u.array.elem);
        case kSTRUCTURE: return strcmp(type_ori->u.structure.name, type_now->u.structure.name) == 0;
    }
}

int TypeConsistentParamList(ParamList param_list_ori, ParamList param_list_now) {
    if (param_list_ori == NULL && param_list_now == NULL) return 1;
    if (param_list_ori == NULL
         || param_list_now == NULL
         || !TypeConsistent(param_list_ori->type, param_list_now->type)) {
        return 0;
    }
    return TypeConsistentParamList(param_list_ori->tail, param_list_now->tail);
}

int TypeConsistentFunction(
    Type type_ori, Type type_now, 
    ParamList param_list_ori, ParamList param_list_now) {
    return TypeConsistent(type_ori, type_now) 
        && TypeConsistentParamList(param_list_ori, param_list_now);
}

int LookupFunctionAt(
    const char* name, SymbolTableNode* symbol_table_node, 
    Type type, ParamList param_list, int is_define) {
    if (symbol_table_node == NULL) return 0;    //  neither definede nor declared yet
    if (strcmp(symbol_table_node->name, name) == 0) {

        if (!TypeConsistentFunction(
            symbol_table_node->type->u.function.type_ret,
            type,
            symbol_table_node->type->u.function.param_list,
            param_list)) {
                return -1;  //  Type inconsistent
        }
        if (is_define && symbol_table_node->type->u.function.defined) {
            return -2;  //  Redefinition
        }
        return 1;
    }
}

int LookupFunction(const char* name, Type type, ParamList param_list, int is_define) {
    unsigned int val = hash_pjw(name);
    return LookupFunctionAt(name, symbol_table[val], type, param_list, is_define);
}

void InsertAt(const char* name, SymbolTableNode* symbol_table_node, Type type, int layer) {
    if (strcmp(symbol_table_node->name, name) == 0) {
        LayerNode* layer_node = (LayerNode*)malloc(sizeof(LayerNode));
        layer_node->layer = layer;
        layer_node->up = symbol_table_node->layer_node;
        symbol_table_node->layer_node = layer_node;
        return;
    }
    if (symbol_table_node == NULL) {
        symbol_table_node = (SymbolTableNode*)malloc(sizeof(SymbolTableNode));
        symbol_table_node->name = name;
        symbol_table_node->type = type;

        LayerNode* layer_node = (LayerNode*)malloc(sizeof(LayerNode));
        layer_node->layer = layer;
        layer_node->up = NULL;
        symbol_table_node->layer_node = layer_node;

        symbol_table_node->next = NULL;
        return;
    }
    InsertAt(name, symbol_table_node->next, type, layer);
}

void insert(const char* name, Type type, int layer) {
    unsigned int val = hash_pjw(name);
    InsertAt(name, symbol_table[val], type, layer);
}