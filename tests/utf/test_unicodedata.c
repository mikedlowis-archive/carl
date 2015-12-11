// Unit Test Framework Includes
#include "atf.h"

// File To Test
#include <carl.h>

const char database[] = "./tools/UnicodeData-8.0.0.txt";

char line[1024] = {0};

typedef struct {
    uint32_t value;
    char* gencat;
    char* bidircat;
    uint32_t tolower;
    uint32_t toupper;
    uint32_t totitle;
} codept_t;

typedef bool (*isrune_fn_t)(Rune);

typedef struct {
    char* category;
    isrune_fn_t* fntable;
} cp_table_t;

const cp_table_t runetypes[] = {
    { "Lu", (isrune_fn_t[]){ isalpharune, isupperrune, NULL } },
    { "Ll", (isrune_fn_t[]){ isalpharune, islowerrune, NULL } },
    { "Lt", (isrune_fn_t[]){ isalpharune, istitlerune, NULL } },
    { "LC", (isrune_fn_t[]){ isalpharune, isotherletterrune, NULL } },
    { "Lm", (isrune_fn_t[]){ isalpharune, isotherletterrune, NULL } },
    { "Lo", (isrune_fn_t[]){ isalpharune, isotherletterrune, NULL } },
    { "Mn", (isrune_fn_t[]){ ismarkrune, NULL } },
    { "Mc", (isrune_fn_t[]){ ismarkrune, NULL } },
    { "Me", (isrune_fn_t[]){ ismarkrune, NULL } },
    { "Nd", (isrune_fn_t[]){ isnumberrune, isdigitrune, NULL } },
    { "Nl", (isrune_fn_t[]){ isnumberrune, NULL } },
    { "No", (isrune_fn_t[]){ isnumberrune, NULL } },
    { "Pc", (isrune_fn_t[]){ ispunctuationrune, NULL } },
    { "Pd", (isrune_fn_t[]){ ispunctuationrune, NULL } },
    { "Ps", (isrune_fn_t[]){ ispunctuationrune, NULL } },
    { "Pe", (isrune_fn_t[]){ ispunctuationrune, NULL } },
    { "Pi", (isrune_fn_t[]){ ispunctuationrune, NULL } },
    { "Pf", (isrune_fn_t[]){ ispunctuationrune, NULL } },
    { "Po", (isrune_fn_t[]){ ispunctuationrune, NULL } },
    { "Sm", (isrune_fn_t[]){ issymbolrune, NULL } },
    { "Sc", (isrune_fn_t[]){ issymbolrune, NULL } },
    { "Sk", (isrune_fn_t[]){ issymbolrune, NULL } },
    { "So", (isrune_fn_t[]){ issymbolrune, NULL } },
    { "Zs", (isrune_fn_t[]){ isspacerune, NULL } },
    { "Zl", (isrune_fn_t[]){ isspacerune, NULL } },
    { "Zp", (isrune_fn_t[]){ isspacerune, NULL } },
    { "Cc", (isrune_fn_t[]){ iscontrolrune, NULL } },
    { "Cf", (isrune_fn_t[]){ isotherrune, NULL } },
    { "Cs", (isrune_fn_t[]){ isotherrune, NULL } },
    { "Co", (isrune_fn_t[]){ isotherrune, NULL } },
    { "Cn", (isrune_fn_t[]){ isotherrune, NULL } },
    { NULL, (isrune_fn_t[]){ isotherrune, NULL } }
};

isrune_fn_t* lookup_codepoint(codept_t* cp) {
    cp_table_t* types = (cp_table_t*)&runetypes[0];
    while((*types).category) {
        if (0 == strcmp((*types).category, cp->gencat))
            return (*types).fntable;
        types++;
    }
    return NULL;
}

char *strnxttok(char *s, const char *sep) {
    static char *p;
    if (!s && !(s = p)) return NULL;
    if (!*s) return p = 0;
    p = s + strcspn(s, sep);
    if (*p) *p++ = 0;
    else p = 0;
    return s;
}

bool read_codepoint(codept_t* ch, FILE* db) {
    if (fgets(line, 1023, db)) {
        // Base value
        char* tok = strnxttok(line, ";");
        ch->value = strtoul(tok, NULL, 16);

        // Unused
        tok = strnxttok(NULL, ";");

        // General Category
        tok = strnxttok(NULL, ";");
        ch->gencat = strdup(tok);

        // Unused
        tok = strnxttok(NULL, ";");

        // Bidirectional Category
        tok = strnxttok(NULL, ";");
        ch->bidircat = strdup(tok);

        // Skip irrelevant fields
        tok = strnxttok(NULL, ";");
        tok = strnxttok(NULL, ";");
        tok = strnxttok(NULL, ";");
        tok = strnxttok(NULL, ";");
        tok = strnxttok(NULL, ";");
        tok = strnxttok(NULL, ";");
        tok = strnxttok(NULL, ";");

        // Get the upper, lower, and title case of the rune
        ch->toupper = strtoul(strnxttok(NULL, ";"), NULL, 16);
        ch->tolower = strtoul(strnxttok(NULL, ";"), NULL, 16);
        ch->totitle = strtoul(strnxttok(NULL, ";"), NULL, 16);
        return true;
    }
    return false;
}

void free_codepoint(codept_t* cp) {
    free(cp->gencat);
    free(cp->bidircat);
}

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(UnicodeData) {
    TEST(Verify_generated_rune_functions) {
        codept_t cp;
        FILE* db = fopen(database, "r");
        while(read_codepoint(&cp, db)) {
            isrune_fn_t* fns = lookup_codepoint(&cp);
            /* Verify the type functions work as expected */
            while(fns && *fns) {
                CHECK((*fns)(cp.value));
                fns++;
            }
            /* Verify toupper works if necessary */
            if (cp.toupper > 0)
                CHECK( cp.toupper == toupperrune(cp.value) );
            /* Verify tolower works if necessary */
            if (cp.tolower > 0)
                CHECK( cp.tolower == tolowerrune(cp.value) );
            /* Verify toupper works if necessary */
            if (cp.totitle > 0)
                CHECK( cp.totitle == totitlerune(cp.value) );
            free_codepoint(&cp);
        }
        fclose(db);
    }
}
