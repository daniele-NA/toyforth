#include "s_tfparser.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool tfparserIsSymbol(char c) {
    const char sym_chars[] = "+-*/";
    return isalpha((unsigned char)c) || strchr(sym_chars, c) != NULL;
}

void tfparserParseSpaces(s_tfparser *parser) {
    while (isspace((unsigned char)parser->p[0]))
        parser->p++;
}

s_tfobj *tfparserParseNumber(s_tfparser *parser) {
    char buf[MAX_NUM_LEN];
    const char *start = parser->p;

    if (parser->p[0] == '-')
        parser->p++; // numero negativo

    while (parser->p[0] && isdigit((unsigned char)parser->p[0]))
        parser->p++;

    int num_len = parser->p - start;
    if (num_len <= 0 || num_len >= MAX_NUM_LEN)
        return NULL;

    memcpy(buf, start, num_len);
    buf[num_len] = 0;

    return tfobjCreateInt(atoi(buf));
}

s_tfobj *tfparserParseSymbol(s_tfparser *parser) {
    const char *start = parser->p;

    while (parser->p[0] && tfparserIsSymbol(parser->p[0]))
        parser->p++;

    const int len = parser->p - start;
    if (len <= 0)
        return NULL;

    return tfobjCreateSymbol(start, len);
}
