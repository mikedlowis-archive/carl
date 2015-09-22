#include "atf.h"
#include <carl.h>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    RUN_EXTERN_TEST_SUITE(RefCount);
    RUN_EXTERN_TEST_SUITE(SList);
    RUN_EXTERN_TEST_SUITE(BSTree);
    RUN_EXTERN_TEST_SUITE(UnicodeData);
    return (PRINT_TEST_RESULTS());
}
