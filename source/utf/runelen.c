#include <carl.h>

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

