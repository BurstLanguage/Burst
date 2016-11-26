//
// Burst
// Include/Compiler/Parser/AST/BurstAST.h
//
#ifndef __BURST_AST_H__
#define __BURST_AST_H__

#include <stdlib.h>

#include "BurstASTNode.h"

#define BURST_AST_GOOD 0x00
#define BURST_AST_BAD  0x01

typedef struct
{
    int nodeCount;
    BurstASTNode **ppNodes;
} BurstAST;

BurstAST *ast_create
(
);

int ast_add
(
    BurstASTNode *pNode,
    BurstAST *pAST
);

void ast_destroy
(
    BurstAST *pAST
);

#endif