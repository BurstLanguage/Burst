//
// Burst
// Include/Compiler/Lexer/BurstToken.h
//
#ifndef __BURST_TOKEN_H__
#define __BURST_TOKEN_H__

#include <stdlib.h>
#include <string.h>

#define BURST_TOKEN_LIST_GOOD 0x00
#define BURST_TOKEN_LIST_BAD  0x01

// General Tokens
#define BURST_UNKNOWN_TOKEN     0x00
#define BURST_NUMBER_TOKEN      0x01 // [0-9]
#define BURST_CHARACTER_TOKEN   0x02 // [A-Za-z]
#define BURST_L_PAREN_TOKEN     0x03 // (
#define BURST_R_PAREN_TOKEN     0x04 // )
#define BURST_COMMA_TOKEN       0x05 // ,
#define BURST_SEMICOLON_TOKEN   0x06 // ;
#define BURST_KEYWORD_TOKEN     0x07
#define BURST_IDENTIFIER_TOKEN  0x08
#define BURST_WHITESPACE_TOKEN  0x09

// Operator Tokens
#define BURST_ADDITION_OPERATOR       0x0A // +
#define BURST_SUBTRACTION_OPERATOR    0x0B // -
#define BURST_MULTIPLICATION_OPERATOR 0x0C // *
#define BURST_DIVISION_OPERATOR       0x0D // /
#define BURST_ASSIGNMENT_OPERATOR     0x0E // =

typedef struct
{
    int type;
    char *pValue;
} BurstToken;

typedef struct
{
    int length;
    BurstToken **ppTokens;
} BurstTokenList;

BurstToken *token_create
(
    int tokenType,
    char *pTokenValue
);

void token_destroy
(
    BurstToken *pToken
);

BurstTokenList *token_list_create
(
);

int token_list_add
(
    BurstToken *pToken,
    BurstTokenList *pTokenList
);

BurstToken *token_list_at
(
    int index,
    BurstTokenList *pTokenList
);

void token_list_destroy
(
    BurstTokenList *pTokenList
);

#endif