//
// Burst
// Source/BurstUtilities.c
//
#include "BurstUtilities.h"

long atod
(
    char *pASCII,
    bool bDebug
)
{
    int x = strlen(pASCII) - 1;
    long value = 0x0;
    
    if (NULL == pASCII)
        return 0x0;
    
    for (int i = 0x0; i < strlen(pASCII); ++i)
    {
        int num = 0x0;
        
        switch (*(pASCII + i))
        {
            case '0': num = 0; break;
            case '1': num = 1; break;
            case '2': num = 2; break;
            case '3': num = 3; break;
            case '4': num = 4; break;
            case '5': num = 5; break;
            case '6': num = 6; break;
            case '7': num = 7; break;
            case '8': num = 8; break;
            case '9': num = 9; break;
        }
        
        if (bDebug)
            printf("%d * (10 ^ %d) = %f\n", num, x - i, num * pow(10, x - i));
        
        value += num * pow(10, x - i);
    }
    
    return value;
}