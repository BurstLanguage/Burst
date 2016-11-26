//
// Burst
// Source/Compiler/Parser/BurstParser.c
//
#include "Compiler/Parser/BurstParser.h"

BurstParser *parser_create
(
    BurstTokenList *pTokenList
)
{
    BurstParser *pParser = NULL;
    
    if (NULL == pTokenList)
        return NULL;
    
    if (NULL == (pParser = (BurstParser *) malloc(sizeof(BurstParser))))
        return NULL;
    
    pParser->pAST = ast_create();
    pParser->currentTokenIndex = 0x0;
    pParser->pTokens = pTokenList;
    
    return pParser;
}

int parser_run
(
    BurstParser *pParser
)
{
    if (NULL == pParser || NULL == pParser->pTokens || NULL == pParser->pAST)
        return BURST_PARSER_BAD;
    
    while (true)
    {
        if (parser_sees(BURST_KEYWORD_TOKEN, pParser))
        {
            BurstToken *pTypeToken = parser_get(pParser);
            parser_advance(pParser);
            
            if (parser_sees(BURST_IDENTIFIER_TOKEN, pParser))
            {
                BurstToken *pIdentifierToken = parser_get(pParser);
                BurstToken *pValueToken      = NULL;
                
                parser_advance(pParser);
                
                if (parser_sees(BURST_ASSIGNMENT_OPERATOR, pParser))
                {
                    parser_advance(pParser);
                    
                    if (parser_sees(BURST_NUMBER_TOKEN, pParser))
                    {
                        pValueToken = parser_get(pParser);
                        parser_advance(pParser);
                    }
                    else
                    {
                        // TODO (Giga): Support non-integer values.
                    }
                }
                
                BurstVariableDeclaration *pVarDecl = (
                    (BurstVariableDeclaration *) malloc(sizeof(
                        BurstVariableDeclaration)
                    )
                );
                
                if (NULL == pVarDecl)
                    return BURST_PARSER_BAD;
                
                pVarDecl->pType = pTypeToken->pValue;
                pVarDecl->pIdentifier = pIdentifierToken->pValue;
                
                if (NULL != pValueToken)
                    pVarDecl->integerValue = atod(pValueToken->pValue, false);
                else
                    pVarDecl->integerValue = 0x0;
                
                // TEST: Print variable information
                printf("Variable:\n");
                printf(" Type: %s\n", pVarDecl->pType);
                printf(" Name: %s\n", pVarDecl->pIdentifier);
                printf(" Value: %ld\n", pVarDecl->integerValue);
                
                ast_add(ast_node_create(BURST_VARIABLE_DECLARATION, pVarDecl),
                    pParser->pAST);
                
                if (!parser_sees(BURST_SEMICOLON_TOKEN, pParser))
                {
                    printf("ERROR: Expected semicolon!\n");
                    
                    return BURST_PARSER_BAD;
                }
                else
                {
                    parser_advance(pParser);
                }
            }
        }
        else
        {
            break;
        }
    }
    
    return BURST_PARSER_GOOD;
}

BurstToken *parser_get
(
    BurstParser *pParser
)
{
    if (NULL == pParser || NULL == pParser->pTokens)
        return NULL;
    
    return token_list_at(pParser->currentTokenIndex, pParser->pTokens);
}

bool parser_sees
(
    int desiredType,
    BurstParser *pParser
)
{
    BurstToken *pToken = NULL;
    
    if (NULL == pParser || NULL == pParser->pTokens)
        return false;
    
    if (NULL == (pToken = parser_get(pParser)))
        return false;
    
    return (pToken->type == desiredType);
}

void parser_advance
(
    BurstParser *pParser
)
{
    if (NULL != pParser)
        ++pParser->currentTokenIndex;
}

void parser_destroy
(
    BurstParser *pParser
)
{
    if (NULL == pParser)
        return;
    
    free(pParser);
}