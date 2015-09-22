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
    cp_table_t* types = &runetypes[0];
    while((*types).category) {
        if (0 == strcmp((*types).category, cp->gencat))
            return (*types).fntable;
        types++;
    }
    return NULL;
}

bool read_codepoint(codept_t* ch, FILE* db) {
    if (fgets(line, 1023, db)) {
        ch->value = strtoul(strtok(line, ";"), NULL, 16);
        strtok(NULL, ";"); // Description
        ch->gencat = strdup(strtok(NULL, ";")); // General Category
        strtok(NULL, ";"); // Class
        ch->bidircat = strdup(strtok(NULL, ";")); // Bidirectional Category
        strtok(NULL, ";"); // Decompositional Map
        strtok(NULL, ";"); // Decimal Value
        strtok(NULL, ";"); // Digit Value
        strtok(NULL, ";"); // Numeric Value
        strtok(NULL, ";"); // Mirrored
        strtok(NULL, ";"); // UTF 1.0 Name
        strtok(NULL, ";"); // Comment
        strtok(NULL, ";"); // To Upper
        strtok(NULL, ";"); // To Lower
        strtok(NULL, ";"); // To Title
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
    TEST(Verify_runetype_functions) {
        bool test_passing = true;
        codept_t cp;
        FILE* db = fopen(database, "r");
        while(test_passing && read_codepoint(&cp, db)) {
            isrune_fn_t* fns = lookup_codepoint(&cp);
            while(fns && *fns) {
                bool test_passing = (*fns)(cp.value);
                if (!test_passing) {
                    fprintf(stderr, "Failed to handle codepoint: %x\n", cp.value);
                    break;
                }
                fns++;
            }
            free_codepoint(&cp);
        }
        fclose(db);
    }
}
