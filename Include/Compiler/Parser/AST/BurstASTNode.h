//
// Burst
// Include/Compiler/Parser/AST/BurstASTNode.h
//
#ifndef __BURST_AST_NODE_H__
#define __BURST_AST_NODE_H__

#include <stdlib.h>

#define BURST_UNKNOWN              0x00
#define BURST_VARIABLE_DECLARATION 0x01

typedef struct
{
    int nodeType;
    void *pNode;
} BurstASTNode;

typedef struct
{
    char *pType;
    char *pIdentifier;
    
    union
    {
        long integerValue;
    };
} BurstVariableDeclaration;

BurstASTNode *ast_node_create
(
    int nodeType,
    void *pNode
);

void ast_node_destroy
(
    BurstASTNode *pASTNode
);

#endif