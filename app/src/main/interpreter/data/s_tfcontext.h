#pragma once
#include "s_tfobj.h"
#include "../runtime/runtime.h"

// FIXME: Circular dependency workaround
typedef struct s_function_table_entry s_function_table_entry;

typedef struct s_tfcontext s_tfcontext;

s_tfcontext *tfcontextCreate(void);
s_function_table_entry* tfcontextGetFunction(s_tfcontext *ctx, s_tfobj *name);

/* Helper: get the main stack of the context */
s_tfobj* tfcontextGetStack(s_tfcontext *ctx);


bool tfcontextCheckStackMinLen(s_tfcontext *ctx, int required_len);
s_tfobj* tfcontextPop(s_tfcontext *ctx, e_tfobj_type type);
void tfcontextPush(s_tfcontext *ctx, s_tfobj *obj);
s_function_table_entry* tfcontextNewFunction(s_tfcontext *ctx, s_tfobj *name);
void tfcontextNewCFunction(s_tfcontext *ctx, char *name, void (*callback)(s_tfcontext *ctx, char *name));
