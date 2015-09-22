#include <carl.h>

static Rune ranges[2][2] = {
    { 0x0, 0x1f },
    { 0x7f, 0x9f }
};

extern int runecmp(const void* a, const void* b);

extern int runeinrange(const void* a, const void* b);

bool iscontrolrune(Rune ch) {
    return (NULL != bsearch(&ch, ranges, 2, 2 * sizeof(Rune), &runeinrange));
}
