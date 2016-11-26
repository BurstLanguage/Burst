//
// Burst
// Source/Compiler/Parser/AST/BurstASTNode.c
//
#include "Compiler/Parser/AST/BurstASTNode.h"

BurstASTNode *ast_node_create
(
    int nodeType,
    void *pNode
)
{
    BurstASTNode *pASTNode = NULL;
    
    if (NULL == pNode)
        return NULL;
    
    if (NULL == (pASTNode = (BurstASTNode *) malloc(sizeof(BurstASTNode))))
        return NULL;
    
    pASTNode->nodeType = nodeType;
    pASTNode->pNode    = pNode;
    
    return pASTNode;
}

void ast_node_destroy
(
    BurstASTNode *pASTNode
)
{
    if (NULL == pASTNode)
        return;
    
    switch (pASTNode->nodeType)
    {
        case BURST_VARIABLE_DECLARATION:
        {
            BurstVariableDeclaration *pNode = (
                (BurstVariableDeclaration *) pASTNode->pNode
            );
            
            if (NULL == pNode)
                break;
            
            if (NULL != pNode->pType)
                free(pNode->pType);
            
            if (NULL != pNode->pIdentifier)
                free(pNode->pIdentifier);
            
            free(pNode);
            
            break;
        }
        
        case BURST_UNKNOWN:
        default:
        {
            free(pASTNode->pNode);
            
            break;
        }
    }
    
    free(pASTNode);
}