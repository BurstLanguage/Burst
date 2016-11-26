//
// Burst
// Include/Compiler/Parser/BurstParser.h
//
#ifndef __BURST_PARSER_H__
#define __BURST_PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "BurstUtilities.h"
#include "AST/BurstAST.h"
#include "Compiler/Lexer/BurstToken.h"

#define BURST_PARSER_GOOD 0x00
#define BURST_PARSER_BAD  0x01

typedef struct
{
    BurstAST *pAST;
    
    int currentTokenIndex;
    BurstTokenList *pTokens;
} BurstParser;

BurstParser *parser_create
(
    BurstTokenList *pTokenList
);

int parser_run
(
    BurstParser *pParser
);

BurstToken *parser_get
(
    BurstParser *pParser
);

bool parser_sees
(
    int desiredType,
    BurstParser *pParser
);

void parser_advance
(
    BurstParser *pParser
);

void parser_destroy
(
    BurstParser *pParser
);

#endif