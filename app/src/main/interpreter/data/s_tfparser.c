#include "s_tfparser.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* Check if a character is a valid symbol (letters or operator characters) */
bool tfparserIsSymbol(char c) {
    const char sym_chars[] = "+-*/powdupabs";  // Supported multi-char symbols
    return isalpha((unsigned char)c) || strchr(sym_chars, c) != NULL;
}

/* Skip whitespace characters in the parser */
void tfparserParseSpaces(s_tfparser *parser) {
    while (isspace((unsigned char)parser->p[0]))
        parser->p++;
}

/* Parse an integer number from the parser */
s_tfobj *tfparserParseNumber(s_tfparser *parser) {
    char buf[MAX_NUM_LEN];
    const char *start = parser->p;

    if (parser->p[0] == '-')
        parser->p++; // Negative number

    while (parser->p[0] && isdigit((unsigned char)parser->p[0]))
        parser->p++;

    int num_len = parser->p - start;
    if (num_len <= 0 || num_len >= MAX_NUM_LEN)
        return NULL;

    memcpy(buf, start, num_len);
    buf[num_len] = 0;

    return tfobjCreateInt(atoi(buf));
}

/* Parse a symbol from the parser */
s_tfobj *tfparserParseSymbol(s_tfparser *parser) {
    const char *start = parser->p;

    while (parser->p[0] && tfparserIsSymbol(parser->p[0]))
        parser->p++;

    const int len = parser->p - start;
    if (len <= 0)
        return NULL;

    return tfobjCreateSymbol(start, len);
}
