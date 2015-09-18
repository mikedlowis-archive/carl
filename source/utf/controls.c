#include <libc.h>

static Rune controls[4][2] = {
    { 0x0, 0x8 },
    { 0xe, 0x1b },
    { 0x7f, 0x84 },
    { 0x86, 0x9f }
};

extern int runeinrange(const void* a, const void* b);
bool iscontrolrune(Rune ch) {
    return (NULL != bsearch(&ch, controls, 4, 2 * sizeof(Rune), &runeinrange));
}
