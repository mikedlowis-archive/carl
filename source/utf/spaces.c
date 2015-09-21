#include <libc.h>

static Rune singles[6] = {
    0x85,
    0xa0,
    0x1680,
    0x202f,
    0x205f,
    0x3000
};

static Rune ranges[4][2] = {
    { 0x9, 0xd },
    { 0x1c, 0x20 },
    { 0x2000, 0x200a },
    { 0x2028, 0x2029 }
};

extern int runeinrange(const void* a, const void* b);

bool isspacerune(Rune ch) {
    return ((NULL != bsearch(&ch, singles, 6, sizeof(Rune), &runeinrange)) || 
            (NULL != bsearch(&ch, ranges, 4, 2 * sizeof(Rune), &runeinrange)));
}
