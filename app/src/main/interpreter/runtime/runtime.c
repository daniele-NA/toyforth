#include "runtime.h"
#include <assert.h>
#include <stdbool.h>

#include "../debug.h"
#include "../data/s_tfobj.h"


// Cambia bool in void
void basicMathFunctions(s_tfcontext *ctx, char *name) {
    if (!tfcontextCheckStackMinLen(ctx, 2)) return;

    // Nota: L'ordine di pop è inverso (LIFO).
    s_tfobj *b = tfcontextPop(ctx, INT); // Top dello stack
    s_tfobj *a = tfcontextPop(ctx, INT); // Sotto il top

    if (a == NULL || b == NULL) return; // Controllo sicurezza

    int result = 0;
    switch(name[0]) {
        case '+': result = a->i + b->i; break;
        case '-': result = a->i - b->i; break;
        case '*': result = a->i * b->i; break;
        case '/': {
            result = (int)(a->i / b->i); break;
        }
    }
    tfobjRelease(a);
    tfobjRelease(b);

    tfcontextPush(ctx, tfobjCreateInt(result));
}

bool runSymbol(s_tfcontext *ctx, s_tfobj *word) {
    LOG_I("Running symbol");
    s_function_table_entry *entry = tfcontextGetFunction(ctx, word);
    if (entry == NULL) return false;

    if (entry->user_func) {
        return false; // fixme to implement
    }else {
        LOG_I("Executing callback");
        entry->callback(ctx,entry->name->str.ptr);
    }

    return true;
}

void exec(s_tfcontext *ctx, const s_tfobj *obj) {
    assert(obj->type == LIST);
    LOG_I("Passed exec assertion");
    for (size_t i = 0; i < obj->list.len; ++i) {
        s_tfobj *word = obj->list.ele[i];
        switch (word->type) {
            case SYMBOL:
                if(runSymbol(ctx,word)==false) {
                    LOG_I("Exec Error\n");
                    tfobjDump(word);
                }
                break;
            default: // Se non è un simbolo,allora va nello stack
                tfcontextPush(ctx, word);
                tfobjRetain(word);
                break;
        }
    }
}
