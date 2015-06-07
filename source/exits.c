#include "libc.h"

char* errstr = nil;

static int exitcode(void)
{
    return errstr ? 1 : errno;
}

void exits(char* estr)
{
    errstr = estr;
    exit(exitcode());
}

