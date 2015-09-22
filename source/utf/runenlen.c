#include <carl.h>

int runenlen(Rune* r, int num)
{
    int i = 0, n = 0;
    for(i = 0; i < num; i++)
        n += runelen(r[i]);
    return n;
}
