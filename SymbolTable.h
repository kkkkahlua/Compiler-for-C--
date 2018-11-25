#ifndef __SYMBOLTABLE_H_INCLUDED
#define __SYMBOLTABLE_H_INCLUDED

#include "semantic.h"

typedef struct LayerNode LayerNode;
typedef struct SymbolTableNode SymbolTableNode;

typedef struct SymbolTableNode {
    const char* name;
    LayerNode* layer_node;
    SymbolTableNode* next;
} SymbolTableNode;

typedef struct LayerNode {
    int layer;
    Operand op;
    Type type;
    LayerNode* up;
} LayerNode;

typedef enum FunctionOpType {
    kDECLARE,
    kDEFINE,
    kCALL,
    kCHECK
} FunctionOpType;

typedef enum StructOpType {
    kStructDefine,
    kStructDeclare
} StructOpType;

typedef enum VariableOpType {
    kVariableDefine,
    kVariableUse,
    kVariableDeclare
} VariableOpType;

SymbolTableNode* symbol_table[16384];

unsigned int hash_pjw(const char* name);

int LookupVariable(const char* name, Type* type, int layer, VariableOpType variable_op, Operand* var_op);

int LookupStruct(const char* name, Type* type, int layer, StructOpType struct_op);

int LookupFunction(const char* name, Type* type_ret, DefList param_list, FunctionOpType function_op);

int LookupFieldInStruct(const char* name, Type type_struct, Type* type_field);

int insert(const char* name, Type type);

void Remove(DefList def_list, int layer);

void OutputLayerNode(const char* name, LayerNode* layer_node);

void UpdateFunctionStatus(const char* name);

int TypeConsistent(Type type_ori, Type type_now);

int TypeConsistentBasic(Type type_1, Type type_2);

int TypeConsistentDefList(DefList field_list_1, DefList field_list_2);

#endif