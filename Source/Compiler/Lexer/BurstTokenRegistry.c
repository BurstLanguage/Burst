//
// Burst
// Source/Compiler/Lexer/BurstTokenRegistry.c
//
#include "Compiler/Lexer/BurstTokenRegistry.h"

BurstTokenRegistry *token_registry_create
(
)
{
    BurstTokenRegistry *pRegistry = (BurstTokenRegistry *) malloc(sizeof(
        BurstTokenRegistry
    ));
    
    if (NULL == pRegistry)
        return NULL;
    
    pRegistry->pTokens = token_list_create();
    
    return pRegistry;
}

int token_registry_add_c
(
    char tokenValue,
    int tokenType,
    BurstTokenRegistry *pTokenRegistry
)
{
    char *pTokenValue = NULL;
    
    if (NULL == pTokenRegistry)
        return BURST_TOKEN_REGISTRY_BAD;
    
    pTokenValue = (char *) malloc(sizeof(char) * 0x2);
    
    *(pTokenValue + 0x0) = tokenValue;
    *(pTokenValue + 0x1) = '\0';
    
    return token_registry_add_s(pTokenValue, tokenType, pTokenRegistry);
}

int token_registry_add_s
(
    char *pTokenValue,
    int tokenType,
    BurstTokenRegistry *pTokenRegistry
)
{
    BurstToken *pToken = NULL;
    
    if (NULL == pTokenValue || NULL == pTokenRegistry)
        return BURST_TOKEN_REGISTRY_BAD;
    
    if (NULL == (pToken = token_create(tokenType, pTokenValue)))
        return BURST_TOKEN_REGISTRY_BAD;
    
    if (BURST_TOKEN_LIST_GOOD != token_list_add(pToken, pTokenRegistry->pTokens))
        return BURST_TOKEN_REGISTRY_BAD;
    
    return BURST_TOKEN_REGISTRY_GOOD;
}

BurstToken *token_registry_get_c
(
    char tokenValue,
    BurstTokenRegistry *pTokenRegistry
)
{
    char *pTokenValue  = NULL;
    BurstToken *pToken = NULL;
    
    if (NULL == pTokenRegistry || NULL == pTokenRegistry->pTokens)
        return NULL;
    
    if (NULL == (pTokenValue = (char *) malloc(sizeof(char) * 0x2)))
        return NULL;
    
    *(pTokenValue + 0x0) = tokenValue;
    *(pTokenValue + 0x1) = '\0';
    
    pToken = token_registry_get_s(pTokenValue, pTokenRegistry);
    
    free(pTokenValue);
    
    return pToken;
}

BurstToken *token_registry_get_s
(
    char *pTokenValue,
    BurstTokenRegistry *pTokenRegistry
)
{
    if (NULL == pTokenRegistry || NULL == pTokenRegistry->pTokens)
        return NULL;
    
    for (int ti = 0x0; ti < pTokenRegistry->pTokens->length; ++ti)
    {
        BurstToken *pCurrentToken = token_list_at(ti, pTokenRegistry->pTokens);
        
        if (!strcmp(pTokenValue, pCurrentToken->pValue))
            return pCurrentToken;
    }
    
    return NULL;
}

void token_registry_destroy
(
    BurstTokenRegistry *pTokenRegistry
)
{
    if (NULL == pTokenRegistry)
        return;
    
    if (NULL != pTokenRegistry->pTokens)
        token_list_destroy(pTokenRegistry->pTokens);
    
    free(pTokenRegistry);
}