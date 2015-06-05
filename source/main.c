#define NO_MAIN_WRAPPER
#include "libc.h"

char* errstr = nil;

static int exitcode(void)
{
    return errstr ? 1 : errno;
}

void exits(char* estr)
{
    if (estr)
        errstr = estr;
    exit(exitcode());
}

int main(int argc, char** argv)
{
    user_main(argc, argv);
    exits(errstr);
    return -1;
}

