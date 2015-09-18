#include "libc.h"

/* Used by rune type checking functions to find the rune in the type tables */
int runeinrange(const void* a, const void* b) {
    Rune* item  = (Rune*)a;
    Rune* range = (Rune*)b;
    if (*item < range[0])
        return -1;
    else if (*item > range[1])
        return 1;
    else
        return 0;
}

