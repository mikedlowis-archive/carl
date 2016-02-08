#include "atf.h"
#include <carl.h>
#include <time.h>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    uint seed = (uint)time(NULL);
    srand(seed);
    printf("Random Number Generation Seed: %u\n", seed);
    RUN_EXTERN_TEST_SUITE(RefCount);
    RUN_EXTERN_TEST_SUITE(SList);
    RUN_EXTERN_TEST_SUITE(List);
    RUN_EXTERN_TEST_SUITE(BSTree);
    RUN_EXTERN_TEST_SUITE(Hash);
    RUN_EXTERN_TEST_SUITE(UnicodeData);
    RUN_EXTERN_TEST_SUITE(Runes);
    return (PRINT_TEST_RESULTS());
}
