#include "compiler.h"

#include <ctype.h>

#include "../debug.h"
#include "../data/s_tfparser.h"
#include "../utils.h"


s_tfobj *compile(char *prg) {
    s_tfparser *parser = xmalloc(sizeof(s_tfparser));
    parser->prg = prg;
    parser->p = prg;

    s_tfobj *parsed = tfobjCreateList(); // empty list
    while (parser->p[0] != 0) {
        s_tfobj *obj = NULL;
        char *token_start = parser->p;

        tfparserParseSpaces(parser);
        if (parser->p[0] == 0) break; // arrivato al null-term


        // number (20)  or    sign & number (-20)
        if (isdigit(parser->p[0]) || (parser->p[0] == '-' && isdigit(parser->p[1]))) {
            obj = tfparserParseNumber(parser);
        } else if (tfparserIsSymbol(parser->p[0])) {
            obj = tfparserParseSymbol(parser);
        }

        if (!obj) {
            LOG_I("Syntax error near: %32s ...\n", token_start);
            break;
        }
        tfobjListPush(parsed, obj);
    }

    free(parser);
    return parsed;
}