//
// Burst
// Source/Compiler/Lexer/BurstLexer.c
//
#include "Compiler/Lexer/BurstLexer.h"

BurstLexer *lexer_create
(
    FILE *pFile
)
{
    BurstLexer *pLexer = NULL;
    
    // If we don't have a file, we don't have anything to lex. We'll check to
    //  make sure we have a valid file, here. If we don't, we won't worry about
    //  allocating any memory for the lexer.
    if (NULL == pFile)
        return NULL;
    
    if (NULL == (pLexer = (BurstLexer *) malloc(sizeof(BurstLexer))))
        return NULL;
    
    pLexer->pFile = pFile;
    pLexer->pTokenList = token_list_create();
    pLexer->pTokenRegistry = token_registry_create();
    
    return pLexer;
}

int lexer_setup
(
    BurstLexer *pLexer
)
{
    BurstTokenRegistry *pRegistry = NULL;
    
    if (NULL == pLexer || NULL == pLexer->pTokenRegistry)
        return BURST_LEXER_BAD;
    
    pRegistry = pLexer->pTokenRegistry;
    
    // XXX: DIRTY HACK #1
    for (int digit = '0'; digit <= '9'; ++digit)
        token_registry_add_c(digit, BURST_NUMBER_TOKEN, pRegistry);
    
    // XXX: DIRTY HACK #2
    for (int lAlpha = 'a'; lAlpha <= 'z'; ++lAlpha)
        token_registry_add_c(lAlpha, BURST_CHARACTER_TOKEN, pRegistry);
    
    // XXX: DIRTY HACK #3
    for (int uAlpha = 'A'; uAlpha <= 'Z'; ++uAlpha)
        token_registry_add_c(uAlpha, BURST_CHARACTER_TOKEN, pRegistry);
    
    token_registry_add_c('(', BURST_L_PAREN_TOKEN,   pRegistry);
    token_registry_add_c(')', BURST_R_PAREN_TOKEN,   pRegistry);
    token_registry_add_c(',', BURST_COMMA_TOKEN,     pRegistry);
    token_registry_add_c(';', BURST_SEMICOLON_TOKEN, pRegistry);
    
    token_registry_add_c('+', BURST_ADDITION_OPERATOR,       pRegistry);
    token_registry_add_c('-', BURST_SUBTRACTION_OPERATOR,    pRegistry);
    token_registry_add_c('*', BURST_MULTIPLICATION_OPERATOR, pRegistry);
    token_registry_add_c('/', BURST_DIVISION_OPERATOR,       pRegistry);
    token_registry_add_c('=', BURST_ASSIGNMENT_OPERATOR,     pRegistry);
    
    token_registry_add_c(' ',  BURST_WHITESPACE_TOKEN, pRegistry);
    token_registry_add_c('\t', BURST_WHITESPACE_TOKEN, pRegistry);
    token_registry_add_c('\n', BURST_WHITESPACE_TOKEN, pRegistry);
    
    // TODO: Keywords
    token_registry_add_s("int", BURST_KEYWORD_TOKEN, pRegistry);
    
    return BURST_LEXER_GOOD;
}

int lexer_run
(
    BurstLexer *pLexer
)
{
    if (NULL == pLexer)
        return BURST_LEXER_BAD;
    
    if (BURST_LEXER_GOOD != lexer_tokenize(pLexer) ||
        BURST_LEXER_GOOD != lexer_analyze(pLexer))
    {
        printf("An error occurred during lexing.\n");
        
        return BURST_LEXER_BAD;
    }
    
    // TEST: Print tokens
    for (int t = 0x0; t < pLexer->pTokenList->length; ++t)
    {
        BurstToken *pToken = token_list_at(t, pLexer->pTokenList);
        
        printf("%02x Token: %s\n", pToken->type, pToken->pValue);
    }
    
    return BURST_LEXER_GOOD;
}

int lexer_tokenize
(
    BurstLexer *pLexer
)
{
    char current = 0x0;
    
    if (NULL == pLexer || NULL == pLexer->pFile)
        return BURST_LEXER_BAD;
    
    if (NULL == pLexer->pTokenRegistry || NULL == pLexer->pTokenList)
        return BURST_LEXER_BAD;
    
    while (EOF != (current = fgetc(pLexer->pFile)))
    {
        BurstToken *pRegistryResult = token_registry_get_c(current,
            pLexer->pTokenRegistry);
        
        char *pTokenValue = NULL;
        
        if (NULL == pRegistryResult)
        {
            printf("Unknown token '%c'\n", current);
            
            return BURST_LEXER_BAD;
        }
        
        pTokenValue    = (char *) malloc(sizeof(char));
        (*pTokenValue) = current;
        
        token_list_add(token_create(pRegistryResult->type, pTokenValue),
            pLexer->pTokenList);
    }
    
    return BURST_LEXER_GOOD;
}

int lexer_analyze
(
    BurstLexer *pLexer
)
{
    BurstTokenList *pNewTokenList = NULL;
    
    BurstToken *pLastToken = NULL;
    BurstToken *pCurrentToken = NULL;
    BurstToken *pRegistryResult = NULL;
    
    char *pNewTokenValue = NULL;
    int newTokenValueLength = 0x1; // Yes, this is a lie.
    
    int lastTokenType = BURST_UNKNOWN_TOKEN;
    
    if (NULL == pLexer)
        return BURST_LEXER_BAD;
    
    if (NULL == pLexer->pTokenRegistry || NULL == pLexer->pTokenList)
        return BURST_LEXER_BAD;
    
    pNewTokenList  = token_list_create();
    pNewTokenValue = (char *) malloc(sizeof(char));
    
    if (NULL == pNewTokenValue)
        return BURST_LEXER_BAD;
    
    for (int ti = 0x0; ti < pLexer->pTokenList->length; ++ti)
    {
        pCurrentToken = token_list_at(ti, pLexer->pTokenList);
        
        if (NULL == pLastToken)
        {
            pLastToken = pCurrentToken;
            (*pNewTokenValue) = (*pCurrentToken->pValue);
            
            lastTokenType = pCurrentToken->type;
            
            continue;
        }
        
        if (pCurrentToken->type == pLastToken->type)
        {
            pNewTokenValue = (char *) realloc(pNewTokenValue, (
                sizeof(char) * (newTokenValueLength + 1)
            ));
        }
        else
        {
            BurstToken *pToken = NULL;
            
            pNewTokenValue = (char *) realloc(pNewTokenValue, (
                sizeof(char) * (newTokenValueLength + 1)
            ));
            *(pNewTokenValue + newTokenValueLength) = '\0';
            
            pRegistryResult = token_registry_get_s(pNewTokenValue,
                pLexer->pTokenRegistry);
            
            if (NULL == pRegistryResult)
            {
                switch (lastTokenType)
                {
                    case BURST_CHARACTER_TOKEN:
                    {
                        pToken = token_create(BURST_IDENTIFIER_TOKEN,
                            pNewTokenValue);
                        
                        break;
                    }
                    
                    case BURST_NUMBER_TOKEN:
                    {
                        pToken = token_create(BURST_NUMBER_TOKEN,
                            pNewTokenValue);
                        
                        break;
                    }
                    
                    default:
                    {
                        printf("Unknown token \"%s\"\n", pNewTokenValue);
                        
                        return BURST_LEXER_BAD;
                    }
                }
            }
            else
            {
                pToken = token_create(pRegistryResult->type, pNewTokenValue);
            }
            
            if (BURST_WHITESPACE_TOKEN != pToken->type)
                token_list_add(pToken, pNewTokenList);
            
            free(pNewTokenValue);
            
            pNewTokenValue = (char *) malloc(sizeof(char));
            newTokenValueLength = 0x0;
            
            lastTokenType = pCurrentToken->type;
        }
        
        *(pNewTokenValue + newTokenValueLength) = (*pCurrentToken->pValue);
        ++newTokenValueLength;
        
        pLastToken = pCurrentToken;
    }
    
    pNewTokenValue = (char *) realloc(pNewTokenValue, (
        sizeof(char) * (newTokenValueLength + 1)
    ));
    *(pNewTokenValue + newTokenValueLength) = '\0';
    
    pRegistryResult = token_registry_get_s(pNewTokenValue,
        pLexer->pTokenRegistry);
    
    if (NULL == pRegistryResult)
    {
        switch (lastTokenType)
        {
            case BURST_CHARACTER_TOKEN:
            {
                token_list_add(
                    token_create(BURST_IDENTIFIER_TOKEN, pNewTokenValue),
                    pNewTokenList
                );
                
                break;
            }
            
            case BURST_NUMBER_TOKEN:
            {
                token_list_add(
                    token_create(BURST_NUMBER_TOKEN, pNewTokenValue),
                    pNewTokenList
                );
                
                break;
            }
            
            default:
            {
                printf("Unknown token \"%s\"\n", pNewTokenValue);
            
                return BURST_LEXER_BAD;
            }
        }
    }
    else
    {
        if (BURST_WHITESPACE_TOKEN != pRegistryResult->type)
        {
            token_list_add(token_create(pRegistryResult->type, pNewTokenValue),
                pNewTokenList);
        }
    }
    
    free(pNewTokenValue);
    
    token_list_destroy(pLexer->pTokenList);
    pLexer->pTokenList = pNewTokenList;
    
    return BURST_LEXER_GOOD;
}

void lexer_destroy
(
    BurstLexer *pLexer
)
{
    if (NULL == pLexer)
        return;
    
    // NOTE (Giga): The file that the lexer is provided with, is opened in
    //  compiler's create routine ('compiler_create'), therefore we should
    //  probably let the compiler close it.
    // if (NULL != pLexer->pFile)
    //     fclose(pLexer->pFile);
    
    if (NULL != pLexer->pTokenList)
        token_list_destroy(pLexer->pTokenList);
    
    if (NULL != pLexer->pTokenRegistry)
        token_registry_destroy(pLexer->pTokenRegistry);
    
    free(pLexer);
}