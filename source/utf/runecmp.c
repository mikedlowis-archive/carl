#include <carl.h>

/* Used by rune type checking functions to find the rune in the type tables */
int runecmp(const void* a, const void* b) {
    Rune* ra  = (Rune*)a;
    Rune* rb = (Rune*)b;
    return *ra - *rb;
}

