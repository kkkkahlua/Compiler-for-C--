#include "SymbolTable.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

unsigned int hash_pjw(const char* name) {
    unsigned int val = 0, i;
    for (; *name; ++name) {
        val = (val << 2) + *name;
        if (i = val & ~0x3fff) val = (val ^ (i >> 12)) & 0x3fff;
    }
    return val;
}

int LookupVariableAt(const char* name, SymbolTableNode* symbol_table_node, int layer) {
    if (symbol_table_node == NULL) return 0;    //  not defined
    if (strcmp(symbol_table_node->name, name) == 0) {
        //  already defined in current scope
        if (symbol_table_node->layer_node->layer == layer) {
            return 1;
        }
        //  defined in outer scopes
        assert(symbol_table_node->layer_node->layer < layer);
        return 2;
    }
    return LookupVariableAt(name, symbol_table_node->next, layer);
}

int LookupVariable(const char* name, int layer) {
    unsigned int val = hash_pjw(name);
    // printf("lookup: name = %s\n", name);
    return LookupVariableAt(name, symbol_table[val], layer);
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
    if (symbol_table_node == NULL) return 0;    //  neither defined nor declared yet
    if (strcmp(symbol_table_node->name, name) == 0) {
        if (!TypeConsistentFunction(
            symbol_table_node->type->u.function.type_ret,
            type,
            symbol_table_node->type->u.function.param_list,
            param_list)) {
            return 2;  //  Type inconsistent
        }
        if (is_define && symbol_table_node->type->u.function.defined) {
            return 3;  //  Redefinition
        }
        return 1;
    }
    return LookupFunctionAt(name, symbol_table_node->next, type, param_list, is_define);
}

int LookupFunction(const char* name, Type type, ParamList param_list, int is_define) {
    unsigned int val = hash_pjw(name);
    return LookupFunctionAt(name, symbol_table[val], type, param_list, is_define);
}

int LookupStructDefinitionAt(const char* name, SymbolTableNode* symbol_table_node, Type type, int layer) {
    if (symbol_table_node == NULL) return 0;    //  not defined
    if (strcmp(symbol_table_node->name, name) == 0) {
        assert(symbol_table_node->layer_node->layer <= layer);

        //  Type consistent
        if (symbol_table_node->type->kind == kSTRUCTURE) {
            *type = *symbol_table_node->type;
            return 1;
        }

        //  Type mismatch
        return 2;
    }
    return LookupVariableAt(name, symbol_table_node->next, layer);   
}

int LookupStructDefinition(const char* name, Type type, int layer) {
    unsigned int val = hash_pjw(name);
    return LookupStructDefinitionAt(name, symbol_table[val], type, layer);
}

SymbolTableNode* CreateSymbolTableNode(const char* name, Type type, int layer) {
    SymbolTableNode* symbol_table_node = (SymbolTableNode*)malloc(sizeof(SymbolTableNode));
    symbol_table_node->name = name;
    symbol_table_node->type = type;

    LayerNode* layer_node = (LayerNode*)malloc(sizeof(LayerNode));
    layer_node->layer = layer;
    layer_node->up = NULL;
    symbol_table_node->layer_node = layer_node;
    symbol_table_node->next = NULL;
    return symbol_table_node;
}

void InsertAt(const char* name, int idx, Type type, int layer) {
    if (!symbol_table[idx]) {
        symbol_table[idx] = CreateSymbolTableNode(name, type, layer);
        return;
    }
    SymbolTableNode* symbol_table_node = symbol_table[idx],
                    * pre_symbol_table_node = NULL;
    while (1) {
        if (!symbol_table_node) {
            symbol_table_node = CreateSymbolTableNode(name, type, layer);
            pre_symbol_table_node->next = symbol_table_node;
            return;
        }

        if (strcmp(symbol_table_node->name, name) == 0) {
            LayerNode* layer_node = (LayerNode*)malloc(sizeof(LayerNode));

            layer_node->layer = layer;
            layer_node->up = symbol_table_node->layer_node;
            symbol_table_node->layer_node = layer_node;

            return;
        }

        pre_symbol_table_node = symbol_table_node;
        symbol_table_node = symbol_table_node->next;
    }
}

void insert(const char* name, Type type, int layer) {
    unsigned int val = hash_pjw(name);
    // printf("insert: name = %s, layer = %d\n", name, layer);
    InsertAt(name, val, type, layer);
}

void RemoveAt(const char* name, int idx, int layer) {
    SymbolTableNode* symbol_table_node = symbol_table[idx],
                    * pre_symbol_table_node = NULL;
    while (1) {

        //  happen only when removing the duplicate variable
        //  which has already been removed before
        if (!symbol_table_node) return;

        if (strcmp(symbol_table_node->name, name) == 0) {
            LayerNode* layer_node = symbol_table_node->layer_node;
            //  Always eliminate the innnerst layer
            assert(layer_node->layer == layer);
            symbol_table_node->layer_node = layer_node->up;
            free(layer_node);

            if (!symbol_table_node->layer_node) {
                if (!pre_symbol_table_node) {
                    symbol_table[idx] = symbol_table_node->next;
                } else {
                    pre_symbol_table_node->next = symbol_table_node->next;
                }
                free(symbol_table_node);
            }
            return;
        } else {
            pre_symbol_table_node = symbol_table_node;
            symbol_table_node = symbol_table_node->next;
        }
    }
}

void RemoveVariable(const char* name, int layer) {
    unsigned int val = hash_pjw(name);
    RemoveAt(name, val, layer);
}

void OutputLayerNode(const char* name, LayerNode* layer_node) {
    printf("%s: \n", name);
    while (1) {
        printf("%d ", layer_node);
        layer_node = layer_node->up;
        if (!layer_node) return;
    }
}