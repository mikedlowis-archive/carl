#include "libc.h"

Rune tolowerrune(Rune ch)
{
    (void)ch;
    return 0;
}

Rune totitlerune(Rune ch)
{
    (void)ch;
    return 0;
}

Rune toupperrune(Rune ch)
{
    (void)ch;
    return 0;
}

Rune tobaserune(Rune ch)
{
    (void)ch;
    return 0;
}




bool isalpharune(Rune ch)
{
    return (isupperrune(ch) || islowerrune(ch));
}

bool isbaserune(Rune ch)
{
    (void)ch;
    return false;
}

bool isdigitrune(Rune ch)
{
    (void)ch;
    return false;
}

