//
// Burst
// Include/Compiler/BurstCompiler.h
//
#ifndef __BURST_COMPILER_H__
#define __BURST_COMPILER_H__

#include <stdio.h>
#include <stdlib.h>

#include "Lexer/BurstLexer.h"
#include "Parser/BurstParser.h"

#define BURST_COMPILER_GOOD 0x00
#define BURST_COMPILER_BAD  0x01

typedef struct
{
    FILE *pFile;
    const char *pFilePath;
    
    // BurstLexer *pLexer;
    // BurstParser *pParser;
} BurstCompiler;

BurstCompiler *compiler_create
(
    const char *pFilePath
);

int compiler_run
(
    BurstCompiler *pCompiler
);

void compiler_destroy
(
    BurstCompiler *pCompiler
);

#endif