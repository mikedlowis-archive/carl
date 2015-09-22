#include <carl.h>

static Rune singles[14] = {
    0xad,
    0x61c,
    0x6dd,
    0x70f,
    0x180e,
    0xd800,
    0xf8ff,
    0xfeff,
    0x110bd,
    0xe0001,
    0xf0000,
    0xffffd,
    0x100000,
    0x10fffd
};

static Rune ranges[12][2] = {
    { 0x600, 0x605 },
    { 0x200b, 0x200f },
    { 0x202a, 0x202e },
    { 0x2060, 0x2064 },
    { 0x2066, 0x206f },
    { 0xdb7f, 0xdb80 },
    { 0xdbff, 0xdc00 },
    { 0xdfff, 0xe000 },
    { 0xfff9, 0xfffb },
    { 0x1bca0, 0x1bca3 },
    { 0x1d173, 0x1d17a },
    { 0xe0020, 0xe007f }
};

extern int runeinrange(const void* a, const void* b);

bool isotherrune(Rune ch) {
    return ((NULL != bsearch(&ch, singles, 14, sizeof(Rune), &runeinrange)) || 
            (NULL != bsearch(&ch, ranges, 12, 2 * sizeof(Rune), &runeinrange)));
}
