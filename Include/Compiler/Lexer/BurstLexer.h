//
// Burst
// Include/Compiler/Lexer/BurstLexer.h
//
#ifndef __BURST_LEXER_H__
#define __BURST_LEXER_H__

#include <stdio.h>
#include <stdlib.h>

#include "BurstToken.h"
#include "BurstTokenRegistry.h"

#define BURST_LEXER_GOOD 0x00
#define BURST_LEXER_BAD  0x01

typedef struct
{
    FILE *pFile;
    
    BurstTokenList *pTokenList;
    BurstTokenRegistry *pTokenRegistry;
} BurstLexer;

BurstLexer *lexer_create
(
    FILE *pFile
);

int lexer_setup
(
    BurstLexer *pLexer
);

int lexer_run
(
    BurstLexer *pLexer
);

int lexer_tokenize
(
    BurstLexer *pLexer
);

int lexer_analyze
(
    BurstLexer *pLexer
);

void lexer_destroy
(
    BurstLexer *pLexer
);

#endif