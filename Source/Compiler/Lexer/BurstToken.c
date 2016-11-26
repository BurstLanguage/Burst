//
// Burst
// Source/Compiler/Lexer/BurstToken.c
//
#include "Compiler/Lexer/BurstToken.h"

BurstToken *token_create
(
    int tokenType,
    char *pTokenValue
)
{
    BurstToken *pToken = NULL;
    
    if (NULL == pTokenValue)
        return NULL;
    
    if (NULL == (pToken = (BurstToken *) malloc(sizeof(BurstToken))))
        return NULL;
    
    pToken->type   = tokenType;
    pToken->pValue = strdup(pTokenValue);
    
    return pToken;
}

void token_destroy
(
    BurstToken *pToken
)
{
    if (NULL == pToken)
        return;
    
    if (NULL != pToken->pValue)
        free(pToken->pValue);
    
    free(pToken);
}

BurstTokenList *token_list_create
(
)
{
    BurstTokenList *pTokenList = (BurstTokenList *) malloc(sizeof(
        BurstTokenList
    ));
    
    if (NULL == pTokenList)
        return NULL;
    
    pTokenList->length   = 0x0;
    pTokenList->ppTokens = (BurstToken **) malloc(0x0);
    
    return pTokenList;
}

int token_list_add
(
    BurstToken *pToken,
    BurstTokenList *pTokenList
)
{
    if (NULL == pToken || NULL == pTokenList)
        return BURST_TOKEN_LIST_BAD;
    
    if (NULL == pTokenList->ppTokens)
        return BURST_TOKEN_LIST_BAD;
    
    pTokenList->ppTokens = (BurstToken **) realloc(
        pTokenList->ppTokens,
        sizeof(BurstToken *) * (pTokenList->length + 1)
    );
    *(pTokenList->ppTokens + pTokenList->length) = (
        pToken
    );
    pTokenList->length++;
    
    return BURST_TOKEN_LIST_GOOD;
}

BurstToken *token_list_at
(
    int index,
    BurstTokenList *pTokenList
)
{
    if (NULL == pTokenList)
        return NULL;
    
    // index out of bounds
    if (0 > index || pTokenList->length <= index)
        return NULL;
    
    return *(pTokenList->ppTokens + index);
}

void token_list_destroy
(
    BurstTokenList *pTokenList
)
{
    if (NULL == pTokenList)
        return;
    
    if (NULL == pTokenList->ppTokens)
        return;
    
    for (int tokenIndex = 0x0; tokenIndex < pTokenList->length; ++tokenIndex)
    {
        BurstToken *pToken = *(pTokenList->ppTokens + tokenIndex);
        
        if (NULL != pToken)
            free(pToken);
    }
    
    free(pTokenList->ppTokens);
}