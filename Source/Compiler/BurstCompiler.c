//
// Burst
// Source/Compiler/BurstCompiler.c
//
#include "Compiler/BurstCompiler.h"

BurstCompiler *compiler_create
(
    const char *pFilePath
)
{
    // Welcome to the "constructor" for the 'BurstCompiler' type. This function
    //  is tasked with allocating any and all memory immediately required by the
    //  compiler, such as the memory required for the lexer and parser.
    //
    // Once all the required memory has been allocated, and all the initial
    //  values have been set, we'll return a pointer to the caller. They can
    //  then use it to play with the compiler.
    //
    // It should be noted that if something goes wrong in this function, we
    //  return 'NULL'. we *do not* free any memory that might've already been
    //  allocated. This is most likely going to cause a memory leak, so let's
    //  hope this doesn't break.
    BurstCompiler *pCompiler = NULL;
    FILE *pFile              = NULL;
    
    if (NULL == pFilePath)
        return NULL;
    
    // Here we're just making sure memory allocation for the 'BurstCompiler'
    //  struct went okay. If it didn't: www.downloadmoreram.com
    if (NULL == (pCompiler = (BurstCompiler *) malloc(sizeof(BurstCompiler))))
        return NULL;
    
    // If we can't open the file at the specified path, then, once again, it's
    //  not our problem. That's most likely a user error. I can't fix stupidity.
    if (NULL == (pFile = fopen(pFilePath, "r")))
        return NULL;
    
    pCompiler->pFile     = pFile;
    pCompiler->pFilePath = pFilePath;
    
    return pCompiler;
}

int compiler_run
(
    BurstCompiler *pCompiler
)
{
    BurstLexer *pLexer   = NULL;
    BurstParser *pParser = NULL;
    
    if (NULL == pCompiler || NULL == pCompiler->pFile)
        return BURST_COMPILER_BAD;
    
    pLexer = lexer_create(pCompiler->pFile);
    
    if (BURST_LEXER_GOOD != lexer_setup(pLexer) ||
        BURST_LEXER_GOOD != lexer_run(pLexer))
    {
        printf("Compilation failed. Reason: lexer error.\n");
        
        return BURST_COMPILER_BAD;
    }
    
    pParser = parser_create(pLexer->pTokenList);
    
    if (BURST_PARSER_GOOD != parser_run(pParser))
    {
        printf("Compilation failed. Reason: parser error.\n");
        
        return BURST_COMPILER_BAD;
    }
    
    // TODO: Codegen
    
    lexer_destroy(pLexer);
    parser_destroy(pParser);
    
    return BURST_COMPILER_GOOD;
}

void compiler_destroy
(
    BurstCompiler *pCompiler
)
{
    // Welcome to the "destructor" for the 'BurstCompiler' type. This function,
    //  much [un]like the 'compiler_create' function, is tasked with
    //  deallocating any and all memory that was allocated for use by the
    //  compiler. This includes the compiler itself.
    
    if (NULL == pCompiler)
        return;
    
    if (NULL != pCompiler->pFile)
        fclose(pCompiler->pFile);
    
    free(pCompiler);
}