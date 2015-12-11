// Unit Test Framework Includes
#include "atf.h"

// File To Test
#include <carl.h>

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(RuneFns) {
    TEST(Verify runecmp returns -1 when b is less than a) {
        CHECK(-1 == runecmp('a','b'));
    }

    TEST(Verify runecmp returns 1 when a is less than b) {
    }

    TEST(Verify runecmp returns 0 when two runes are equal) {
    }
}
