//
// Burst
// Source/Compiler/Parser/AST/BurstAST.c
//
#include "Compiler/Parser/AST/BurstAST.h"

BurstAST *ast_create
(
)
{
    BurstAST *pAST = NULL;
    
    if (NULL == (pAST = (BurstAST *) malloc(sizeof(BurstAST))))
        return NULL;
    
    pAST->nodeCount = 0x0;
    pAST->ppNodes   = (BurstASTNode **) malloc(0x0);
    
    return pAST;
}

int ast_add
(
    BurstASTNode *pNode,
    BurstAST *pAST
)
{
    if (NULL == pAST || NULL == pNode)
        return BURST_AST_BAD;
    
    pAST->ppNodes = (BurstASTNode **) realloc(pAST->ppNodes, (
        sizeof(BurstASTNode *) * (pAST->nodeCount + 1)
    ));
    *(pAST->ppNodes + pAST->nodeCount) = pNode;
    ++pAST->nodeCount;
    
    return BURST_AST_GOOD;
}

void ast_destroy
(
    BurstAST *pAST
)
{
    if (NULL == pAST)
        return;
    
    if (NULL != pAST->ppNodes)
    {
        for (int node = 0x0; node < pAST->nodeCount; ++node)
            ast_node_destroy(*(pAST->ppNodes + node));
        
        free(pAST->ppNodes);
    }
    
    free(pAST);
}