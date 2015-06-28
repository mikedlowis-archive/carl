#include "libc.h"

int runetochar(char* s, Rune* r)
{
    (void)s;
    (void)r;
    return 0;
}

int chartorune(Rune* r, char* s)
{
    (void)r;
    (void)s;
    return 0;
}

int runelen(long r)
{
    if(r <= 0x7F)
        return 1;
    else if(r <= 0x07FF)
        return 2;
    else if(r <= 0xD7FF)
        return 3;
    else if(r <= 0xDFFF)
        return 0; /* surrogate character */
    else if(r <= 0xFFFD)
        return 3;
    else if(r <= 0xFFFF)
        return 0; /* illegal character */
    else if(r <= Runemax)
        return 4;
    else
        return 0; /* rune too large */
}

int runenlen(Rune* r, int num)
{
    size_t i, n = 0;
    for(i = 0; i < num; i++)
        n += runelen(r[i]);
    return n;
}

bool fullrune(char* s, int n)
{
    return false;
}

