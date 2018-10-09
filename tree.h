#ifndef __TREE_H
#define __TREE_H

typedef enum NodeType {
    kINTERNAL,
    kINT,
    kFLOAT,
    kID,
    kSYMBOL,
    kRELOP,
    kTYPE
} NodeType;

typedef enum RelopType {
    kGT,
    kLT,
    kGE,
    kLE,
    kEQ,
    kNE
} RelopType;

typedef union NodeVal {
    int ValInt;
    float ValFloat;
    char* ValString;
    RelopType ValRelop;
} NodeVal;

typedef struct TreeNode {
    NodeType    type;
    NodeVal     val;
    int         lineno;
    struct TreeNode* son;
    struct TreeNode* bro;
} TreeNode;

TreeNode* NewTreeNode(NodeType type, NodeVal val, int lineno);

TreeNode* NewNumberTreeNode(const char* s, int base, int lineno);

TreeNode* NewSymbolTreeNode(const char* s, int lineno);

TreeNode* NewIDTreeNode(const char* s, int lineno);

TreeNode* NewTypeTreeNode(const char* s, int lineno);

TreeNode* NewRelopTreeNode(RelopType type, int lineno);

TreeNode* CreateInternalTreeNode(const char* s, int n, ...);

void OutputTree(TreeNode* root, int indent);

#endif