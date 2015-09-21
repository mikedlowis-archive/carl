#include <libc.h>

static Rune singles[7] = {
    0x1c5,
    0x1c8,
    0x1cb,
    0x1f2,
    0x1fbc,
    0x1fcc,
    0x1ffc
};

static Rune ranges[3][2] = {
    { 0x1f88, 0x1f8f },
    { 0x1f98, 0x1f9f },
    { 0x1fa8, 0x1faf }
};

extern int runeinrange(const void* a, const void* b);

bool istitlerune(Rune ch) {
    return ((NULL != bsearch(&ch, singles, 7, sizeof(Rune), &runeinrange)) || 
            (NULL != bsearch(&ch, ranges, 3, 2 * sizeof(Rune), &runeinrange)));
}
