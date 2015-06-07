#define NO_MAIN_WRAPPER
#include "libc.h"

int main(int argc, char** argv)
{
    user_main(argc, argv);
    exits(errstr);
    return -1;
}

