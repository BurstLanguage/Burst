//
// Burst
// Include/Compiler/Lexer/BurstTokenRegistry.h
//
#ifndef __BURST_TOKEN_REGISTRY_H__
#define __BURST_TOKEN_REGISTRY_H__

#include <stdlib.h>
#include <string.h>

#include "BurstToken.h"

#define BURST_TOKEN_REGISTRY_GOOD 0x00
#define BURST_TOKEN_REGISTRY_BAD  0x01

typedef struct
{
    BurstTokenList *pTokens;
} BurstTokenRegistry;

BurstTokenRegistry *token_registry_create
(
);

int token_registry_add_c
(
    char tokenValue,
    int tokenType,
    BurstTokenRegistry *pTokenRegistry
);

int token_registry_add_s
(
    char *pTokenValue,
    int tokenType,
    BurstTokenRegistry *pTokenRegistry
);

BurstToken *token_registry_get_c
(
    char tokenValue,
    BurstTokenRegistry *pTokenRegistry
);

BurstToken *token_registry_get_s
(
    char *pTokenValue,
    BurstTokenRegistry *pTokenRegistry
);

void token_registry_destroy
(
    BurstTokenRegistry *pTokenRegistry
);

#endif