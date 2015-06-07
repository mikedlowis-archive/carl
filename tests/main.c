#include "atf.h"
#include "libc.h"

void main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    RUN_EXTERN_TEST_SUITE(RefCount);
    exit(PRINT_TEST_RESULTS());
}
