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

int LookupVariableAt(const char* name, SymbolTableNode* symbol_table_node, Type* type, int layer) {
    if (symbol_table_node == NULL) return 0;    //  not defined
    if (strcmp(symbol_table_node->name, name) == 0) {
        //  already defined in current scope
        if (symbol_table_node->layer_node->layer == layer) {
            *type = symbol_table_node->type;
            return 1;
        }
        //  defined in outer scopes
        assert(symbol_table_node->layer_node->layer < layer);
        *type = symbol_table_node->type;
        return 2;
    }
    return LookupVariableAt(name, symbol_table_node->next, type, layer);
}

int LookupVariable(const char* name, Type* type, int layer) {
    unsigned int val = hash_pjw(name);
    return LookupVariableAt(name, symbol_table[val], type, layer);
}

int TypeConsistent(Type type_ori, Type type_now) {
    if (!type_ori || !type_now) return 0;
    if (type_ori->kind != type_now->kind) return 0;
    switch (type_ori->kind) {
        case kBASIC: 
            return type_ori->u.basic == type_now->u.basic;
        case kARRAY: 
            return TypeConsistent(type_ori->u.array.elem, type_now->u.array.elem)
                        && type_ori->u.array.size == type_now->u.array.size;
        case kSTRUCTURE: 
            return TypeConsistentFieldList(type_ori->u.structure.field_list, 
                                            type_now->u.structure.field_list);
    }
}

int TypeConsistentBasic(Type type_1, Type type_2) {
    return type_1 && type_2 
            && type_1->kind == kBASIC && type_2->kind == kBASIC
            && type_1->u.basic == type_2->u.basic;
}

int TypeConsistentFieldList(FieldList field_list_1, FieldList field_list_2) {
    if (!field_list_1 && !field_list_2) return 1;
    if (!field_list_1 || !field_list_2
         || !TypeConsistent(field_list_1->type, field_list_2->type)) return 0;
    return TypeConsistentFieldList(field_list_1->tail, field_list_2->tail);
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
    Type* type, ParamList param_list, FunctionOpType function_op) {
    if (symbol_table_node == NULL) return 0;    //  neither defined nor declared yet
    if (strcmp(symbol_table_node->name, name) == 0) {
        if (symbol_table_node->type->kind != kFUNCTION) return -1;   //  not a function
        switch (function_op) {
            case kCALL: {
                if (!TypeConsistentParamList(
                    param_list, 
                    symbol_table_node->type->u.function.param_list)) {
                    return 1;   /*  Type inconsistent   */
                } else {
                    *type = symbol_table_node->type->u.function.type_ret;
                    return 2;   /*  Type consistent   */
                }
            }
            case kCHECK: {
                if (symbol_table_node->type->u.function.defined) {
                    return 1;   /*  function defined    */
                } else {
                    return 2;   /*  only declared but not defined   */
                }
            }
            case kDEFINE: {
                if (symbol_table_node->type->u.function.defined) {
                    return 1;   /*  function defined    */
                }
            }
            case kDECLARE: {
                if (!TypeConsistentFunction(
                    symbol_table_node->type->u.function.type_ret,
                    *type,
                    symbol_table_node->type->u.function.param_list,
                    param_list)) {
                    return 2;  /*  Type inconsistent    */
                } else {
                    return 3;   /*  Type consistent     */
                }
            }
        }
    }
    return LookupFunctionAt(name, symbol_table_node->next, type, param_list, function_op);
}

void UpdateFunctionStatusAt(const char* name, SymbolTableNode* symbol_table_node) {
    assert(symbol_table_node);
    if (strcmp(symbol_table_node->name, name) == 0) {
        symbol_table_node->type->u.function.defined = 1;
        return;
    }
    UpdateFunctionStatusAt(name, symbol_table_node->next);
}

void UpdateFunctionStatus(const char* name) {
    unsigned int val = hash_pjw(name);
    UpdateFunctionStatusAt(name, symbol_table[val]);
}

int LookupFunction(const char* name, Type* type, ParamList param_list, FunctionOpType function_op) {
    unsigned int val = hash_pjw(name);
    return LookupFunctionAt(name, symbol_table[val], type, param_list, function_op);
}

int LookupStructAt(const char* name, SymbolTableNode* symbol_table_node, 
                            Type* type, int layer, StructOpType struct_op) {
    if (symbol_table_node == NULL) return 0;    //  not defined
    if (strcmp(symbol_table_node->name, name) == 0) {
        assert(symbol_table_node->layer_node->layer <= layer);

        switch (struct_op) {
            case kStructDefine: return 1;
            case kStructDeclare:
                if (symbol_table_node->type->kind == kSTRUCTURE) {
                    //  type consistent
                    *type = symbol_table_node->type;
                    return 1;
                } else {
                    //  mistake other varialbe name as struct definition
                    return 2;
                }
        }
    }
    return LookupStructAt(name, symbol_table_node->next, type, layer, struct_op);
}

int LookupStruct(const char* name, Type* type, int layer, StructOpType struct_op) {
    unsigned int val = hash_pjw(name);
    return LookupStructAt(name, symbol_table[val], type, layer, struct_op);
}

//  TODO: think about whether exists a better structure so that 
//  filed in struct can also be positioned in a hash table
int LookupFieldInStruct(const char* name, Type type_struct, Type* type_field) {
    FieldList field_list = type_struct->u.structure.field_list;
    while (1) {
        if (!field_list) return 0;
        if (strcmp(field_list->name, name) == 0) {
            *type_field = field_list->type;
            return 1;
        }
        field_list = field_list->tail;
    }
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