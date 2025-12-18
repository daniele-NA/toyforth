#pragma once

#include <stdbool.h>

#include "s_tfobj.h"

#define MAX_NUM_LEN 128

typedef struct s_tfparser{
    char *prg; // programma da compilare
    char *p;   // next token to parse
} s_tfparser;

/* ===== Helpers ===== */

bool tfparserIsSymbol(char c);
void tfparserParseSpaces(s_tfparser *parser);

/* ===== Parsing ===== */

s_tfobj *tfparserParseNumber(s_tfparser *parser);
s_tfobj *tfparserParseSymbol(s_tfparser *parser);
