#include <libc.h>

static Rune spaces[10][2] = {
    { 0x9, 0xd },
    { 0x1c, 0x20 },
    { 0x85, 0x85 },
    { 0xa0, 0xa0 },
    { 0x1680, 0x1680 },
    { 0x2000, 0x200a },
    { 0x2028, 0x2029 },
    { 0x202f, 0x202f },
    { 0x205f, 0x205f },
    { 0x3000, 0x3000 }
};

extern int runeinrange(const void* a, const void* b);

bool isspacerune(Rune ch) {
    return (NULL != bsearch(&ch, spaces, 10, 2 * sizeof(Rune), &runeinrange));
}
