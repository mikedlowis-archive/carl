#include <carl.h>

static Rune singles[14] = {
    0x20,
    0x85,
    0xa0,
    0x1680,
    0x1680,
    0x2000,
    0x200a,
    0x2028,
    0x2029,
    0x202f,
    0x205f,
    0x205f,
    0x3000,
    0x3000
};

static Rune ranges[13][2] = {
    { 0x9, 0xd },
    { 0x1c, 0x20 },
    { 0x2000, 0x2001 },
    { 0x2001, 0x2002 },
    { 0x2002, 0x2003 },
    { 0x2003, 0x2004 },
    { 0x2004, 0x2005 },
    { 0x2005, 0x2006 },
    { 0x2006, 0x2007 },
    { 0x2007, 0x2008 },
    { 0x2008, 0x2009 },
    { 0x2009, 0x200a },
    { 0x2028, 0x2029 }
};

extern int runecmp(const void* a, const void* b);

extern int runeinrange(const void* a, const void* b);

bool isspacerune(Rune ch) {
    return ((NULL != bsearch(&ch, singles, 14, sizeof(Rune), &runecmp)) || 
            (NULL != bsearch(&ch, ranges, 13, 2 * sizeof(Rune), &runeinrange)));
}
