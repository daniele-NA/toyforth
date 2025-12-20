#pragma once

#include <stdbool.h>

#include "s_tfobj.h"

#define MAX_NUM_LEN 128

typedef struct s_tfparser{
    char *prg; // Program to compile
    char *p;   // Next token to parse
} s_tfparser;

/* ===== Helpers ===== */

/* Check if a character is a valid symbol */
bool tfparserIsSymbol(char c);

/* Skip spaces in the parser */
void tfparserParseSpaces(s_tfparser *parser);

/* ===== Parsing ===== */

/* Parse a number from the parser */
s_tfobj *tfparserParseNumber(s_tfparser *parser);

/* Parse a symbol from the parser */
s_tfobj *tfparserParseSymbol(s_tfparser *parser);
