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

SymbolTableNode* symbol_table[16384];

unsigned int hash_pjw(const char* name);

int LookupVariable(const char* name, Type* type, int layer);

int LookupStruct(const char* name, Type* type, int layer, StructOpType struct_op);

int LookupFunction(const char* name, Type* type_ret, ParamList param_list, FunctionOpType function_op);

int LookupFieldInStruct(const char* name, Type type_struct, Type* type_field);

void insert(const char* name, Type type, int layer);

void RemoveVariable(const char* name, int layer);

void OutputLayerNode(const char* name, LayerNode* layer_node);

void UpdateFunctionStatus(const char* name);

int TypeConsistent(Type type_ori, Type type_now);

int TypeConsistentBasic(Type type_1, Type type_2);

int TypeConsistentFieldList(FieldList field_list_1, FieldList field_list_2);

int TypeConsistentParamList(ParamList param_list_ori, ParamList param_list_now);



#endif