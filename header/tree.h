#ifndef __TREE_H_INCLUDED
#define __TREE_H_INCLUDED

extern int yylineno;

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

TreeNode* NewTreeNode(NodeType type, NodeVal val);

TreeNode* NewNumberTreeNode(const char* s, int base);

TreeNode* NewSymbolTreeNode(const char* s);

TreeNode* NewIDTreeNode(const char* s);

TreeNode* NewTypeTreeNode(const char* s);

TreeNode* NewRelopTreeNode(RelopType type);

TreeNode* CreateInternalTreeNode(const char* s, int n, ...);

void OutputTree(TreeNode* root, int indent);

#endif