#pragma once
#include <stdbool.h>

#include "../data/s_tfcontext.h"
#include "../data/s_tfobj.h"

// FIXME : Circular dependency workaround
typedef struct s_tfcontext s_tfcontext;

// FunctionTableEntry :each entry is a symbol name with asociated callback
typedef struct s_function_table_entry {
    s_tfobj *name;
    void (*callback)(s_tfcontext *ctx, char *name);
    s_tfobj *user_func;
}s_function_table_entry;

typedef struct s_function_table {
    s_function_table_entry **entries;
    unsigned long long count;
}s_function_table;

void basicMathFunctions(s_tfcontext *ctx,char *name);

// torna true se il simbolo viene risolto,altrimenti falso
bool runSymbol(s_tfcontext *ctx, s_tfobj *word);

void exec(s_tfcontext *ctx, const s_tfobj *obj);

