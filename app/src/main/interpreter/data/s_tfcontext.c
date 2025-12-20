#include "s_tfcontext.h"

#include <string.h>

#include "../utils.h"

struct s_tfcontext {
    s_tfobj *stack;
    s_function_table table;
};

/* Create a new interpreter context and register basic math functions */
s_tfcontext *tfcontextCreate(void) {
    s_tfcontext *ctx = xmalloc(sizeof(*ctx));
    LOG_I("Context allocated");
    ctx->stack = tfobjCreateList();
    ctx->table.entries = NULL;
    ctx->table.count = 0;

    tfcontextNewCFunction(ctx, "+", basicMathFunctions);
    tfcontextNewCFunction(ctx, "-", basicMathFunctions);
    tfcontextNewCFunction(ctx, "*", basicMathFunctions);
    tfcontextNewCFunction(ctx, "/", basicMathFunctions);
    tfcontextNewCFunction(ctx, "pow", basicMathFunctions);
    tfcontextNewCFunction(ctx, "dup", basicMathFunctions);
    tfcontextNewCFunction(ctx, "abs", basicMathFunctions);

    return ctx;
}

/* Return the main stack of the context */
s_tfobj* tfcontextGetStack(s_tfcontext *ctx) {
    return ctx->stack;
}

/* Check if the stack has at least required_len elements */
bool tfcontextCheckStackMinLen(s_tfcontext *ctx, int required_len) {
    if (!ctx || !ctx->stack) return false;
    return ctx->stack->list.len >= required_len;
}

/* Pop an element of the given type from the stack; returns NULL if empty or type mismatch */
s_tfobj *tfcontextPop(s_tfcontext *ctx, e_tfobj_type type) {
    s_tfobj *stack = ctx->stack;
    if (stack->list.len == 0) return NULL;
    if (stack->list.ele[stack->list.len - 1]->type != type) return NULL;

    s_tfobj *obj_to_pop = stack->list.ele[stack->list.len - 1];
    stack->list.len--;

    if (stack->list.len == 0) {
        free(stack->list.ele);
        stack->list.ele = NULL;
    }

    stack->list.ele = xrealloc(stack->list.ele, sizeof(s_tfobj *) * stack->list.len);

    return obj_to_pop;
}

/* Push an object onto the stack */
void tfcontextPush(s_tfcontext *ctx, s_tfobj *obj) {
    tfobjListPush(ctx->stack, obj);
}

/* Get function entry by name */
s_function_table_entry *tfcontextGetFunction(s_tfcontext *ctx, s_tfobj *name) {
    for (int i = 0; i < ctx->table.count; ++i) {
        s_function_table_entry *entry = ctx->table.entries[i];
        e_comparison_state state = tfobjCompareString(entry->name, name);
        if (state == SAME_MEMBER) return entry;
    }
    return NULL;
}

/* Create a new function entry in the context */
s_function_table_entry *tfcontextNewFunction(s_tfcontext *ctx, s_tfobj *name) {
    ctx->table.entries = xrealloc(ctx->table.entries, sizeof(s_function_table_entry *) * (ctx->table.count + 1));

    s_function_table_entry *entry = xmalloc(sizeof(s_function_table_entry));
    ctx->table.entries[ctx->table.count] = entry;
    ctx->table.count++;
    entry->name = name;

    /* Increment reference count for name */
    tfobjRetain(name);

    entry->callback = NULL;
    entry->user_func = NULL;
    return entry;
}

/* Register a new C function in the context; overrides existing definitions */
void tfcontextNewCFunction(s_tfcontext *ctx, char *name, void (*callback)(s_tfcontext *ctx, char *name)) {
    s_function_table_entry *fte;
    s_tfobj *obj = tfobjCreateString(name, strlen(name));
    tfobjDump(obj);

    fte = tfcontextGetFunction(ctx, obj);
    if (fte != NULL) {
        /* If it was a user-defined function, release it */
        if (fte->user_func) {
            tfobjRelease(fte->user_func);
            fte->user_func = NULL;
        }
        fte->callback = callback;
    } else {
        fte = tfcontextNewFunction(ctx, obj);
        fte->callback = callback;
    }

    tfobjRelease(obj);
}
