//
// Burst
// Source/Entry.c
//
#include <stdio.h>

#include "Compiler/BurstCompiler.h"

// Welcome to Burst, a [probably crappy] compiler for a [really subpar]
//  language. Burst is a language that was inspired by C. Naturally, because
//  of this, the Burst compiler is implemented in C.

int main(int argc, const char **argv)
{
    // This is the entry point for the Burst compiler. Here, we'll process any
    //  arguments that were passed to the application via the command-line. The
    //  arguments we receive, are mostly likely to be [paths to] files that
    //  we're supposed to compile, but some of them could be compiler flags as
    //  well.
    //
    // Once we've processed the command-line arguments, we'll launch the actual
    //  compiler. When we do this, we'll pass paths to our input files, so the
    //  compiler can do its "thing" with them.
    
    // At the very minimum, we require at least one [additional] argument
    //  be passed to our program.
    if (2 > argc)
    {
        printf("Minimum number of arguments (1) not met\n");
        
        return 1;
    }
    
    // If you can't read (and understand) the following line, you should
    //  probably leave. Now.
    while ((*++argv))
    {
        // TODO: Process flags passed via the command-line.
        BurstCompiler *pCompiler = compiler_create((*argv));
        
        if (NULL == pCompiler)
        {
            printf("An error occurred while attempting to compile '%s'\n",
                (*argv));
            
            continue;
        }
        
        if (BURST_COMPILER_GOOD != compiler_run(pCompiler))
            return 1;
        
        compiler_destroy(pCompiler);
    }
    
    return 0;
}