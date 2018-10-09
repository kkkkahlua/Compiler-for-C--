#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

TreeNode* NewTreeNode(NodeType type, NodeVal val, int lineno) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = type;
    node->val = val;
    node->lineno = lineno;
    node->son = node->bro = NULL;
    return node;
}

TreeNode* NewNumberTreeNode(const char* s, int base, int lineno) {
    NodeVal node_val;
    if (base) {
        node_val.ValInt = strtol(s, NULL, base);
        return NewTreeNode(kINT, node_val, lineno);
    } else {
        node_val.ValFloat = strtof(s, NULL);
        return NewTreeNode(kFLOAT, node_val, lineno);
    }
}

TreeNode* NewSymbolTreeNode(const char* s, int lineno) {
    NodeVal node_val;
    node_val.ValString = (char*)malloc(strlen(s)+1);
    strcpy(node_val.ValString, s);
    return NewTreeNode(kSYMBOL, node_val, lineno);
}

TreeNode* NewIDTreeNode(const char* s, int lineno) {
    NodeVal node_val;
    node_val.ValString = (char*)malloc(strlen(s)+1);
    strcpy(node_val.ValString, s);
    return NewTreeNode(kID, node_val, lineno);
}

TreeNode* NewTypeTreeNode(const char* s, int lineno) {
    NodeVal node_val;
    node_val.ValString = (char*)malloc(strlen(s)+1);
    strcpy(node_val.ValString, s);
    return NewTreeNode(kTYPE, node_val, lineno);
}

TreeNode* NewRelopTreeNode(RelopType type, int lineno) {
    NodeVal node_val;
    node_val.ValRelop = type;
    return NewTreeNode(kRELOP, node_val, lineno);
}

TreeNode* CreateInternalTreeNode(const char* s, int n, ...) {
    if (n == 0) return NULL;
    va_list var_arg;
    va_start(var_arg, n);

    NodeVal node_val;
    node_val.ValString = (char*)malloc(strlen(s)+1);
    strcpy(node_val.ValString, s);
    TreeNode* root = NewTreeNode(kINTERNAL, node_val, -1);

    TreeNode* pre = va_arg(var_arg, TreeNode*);
    root->son = pre;
    root->lineno = pre->lineno;

    int i = 1;
    for (; i < n; ++i) {
        TreeNode* cur = va_arg(var_arg, TreeNode*);
        if (cur == NULL) continue;
        pre->bro = cur;
        pre = cur;
    }
    return root;
}

void OutputTree(TreeNode* root, int indent) {
    if (root == NULL) return;

    int i;
    for (i = 0; i < indent; ++i) putchar(' ');
    switch (root->type) {
        case kINT:              printf("INT: %d\n", root->val.ValInt); break;
        case kFLOAT:            printf("FLOAT: %f\n", root->val.ValFloat); break;
        case kTYPE:             printf("TYPE: %s\n", root->val.ValString); break;
        case kID:               printf("ID: %s\n", root->val.ValString); break;
        case kSYMBOL:           printf("%s\n", root->val.ValString); break;
        case kRELOP:            printf("RELOP\n");
        case kINTERNAL:         printf("%s (%d)\n", root->val.ValString, root->lineno); break;
    }
    OutputTree(root->son, indent+2);
    OutputTree(root->bro, indent);
}