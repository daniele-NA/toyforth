#include "runtime.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../debug.h"
#include "../data/s_tfobj.h"

/* Register basic math functions in the context */
void basicMathFunctions(s_tfcontext *ctx, char *name) {
//    if (!tfcontextCheckStackMinLen(ctx, 2)) return;
    int result = 0;

    /* Pop the top of the stack */
    s_tfobj *b = tfcontextPop(ctx, INT);

    /* Short operators (single character) */
    if (strlen(name) == 1) {

        /* Note: Pop order is LIFO */
        s_tfobj *a = tfcontextPop(ctx, INT); // Under the top

        if (a == NULL || b == NULL) return; // Safety check

        switch (name[0]) {
            case '+':result = a->i + b->i;break;
            case '-':result = a->i - b->i;break;
            case '*':result = a->i * b->i;break;
            case '/':result = (int) (a->i / b->i);break;
        }

        tfobjRelease(a);
    }
        /* Long operators (multi-character) */
    else {
        LOG_E("Long operator");
        if (strcmp(name, "pow") == 0) {
            result = b->i * b->i;
        } else if (strcmp(name, "dup") == 0) {
            result = b->i * 2;
        } else if (strcmp(name, "abs") == 0) {
            result = abs(b->i);
        }
    }

    tfobjRelease(b);

    tfcontextPush(ctx, tfobjCreateInt(result));
}

/* Execute a symbol from the function table; return true if found */
bool runSymbol(s_tfcontext *ctx, s_tfobj *word) {
    LOG_I("Running symbol\n");
    s_function_table_entry *entry = tfcontextGetFunction(ctx, word);
    if (entry == NULL) return false;

    if (entry->user_func) {
        return false; // FIXME: user-defined function not implemented
    } else {
        LOG_I("Executing callback\n");
        entry->callback(ctx, entry->name->str.ptr);
    }

    return true;
}

/* Execute a compiled Forth object */
void exec(s_tfcontext *ctx, const s_tfobj *obj) {
    assert(obj->type == LIST);
    LOG_I("Passed exec assertion\n");
    for (size_t i = 0; i < obj->list.len; ++i) {
        s_tfobj *word = obj->list.ele[i];
        switch (word->type) {
            case SYMBOL:
                if (runSymbol(ctx, word) == false) {
                    LOG_I("Exec Error\n");
                    tfobjDump(word);
                }
                break;
            default: /* If not a symbol, push it to the stack */
                tfcontextPush(ctx, word);
                tfobjRetain(word);
                break;
        }
    }
}
