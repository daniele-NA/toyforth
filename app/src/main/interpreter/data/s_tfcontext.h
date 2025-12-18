#pragma once
#include "s_tfobj.h"
#include "../runtime/runtime.h"

// FIXME : Circular dependency workaround
typedef struct s_function_table_entry s_function_table_entry ;

typedef struct s_tfcontext s_tfcontext;

s_tfcontext *tfcontextCreate(void);

// avoid circular dependencies


s_function_table_entry* tfcontextGetFunction(s_tfcontext *ctx, s_tfobj *name);

// Helper
s_tfobj* tfcontextGetStack(s_tfcontext *ctx);


bool tfcontextCheckStackMinLen(s_tfcontext *ctx,int required_len);

/**
 * pop the element from the interpreter main stack, assuming it
 * will match enum 'type' , otherwise NULL si returned (also if the stack is empty)
 */
s_tfobj* tfcontextPop(s_tfcontext *ctx,e_tfobj_type type);
void tfcontextPush(s_tfcontext *ctx, s_tfobj *obj);

/*
 push a new function entry into the context,It's up to the caller to set
 either the C callback or the list representing the user defined function
*/
s_function_table_entry* tfcontextNewFunction(s_tfcontext *ctx,s_tfobj *name);
void tfcontextNewCFunction(s_tfcontext *ctx, char *name,void (*callback)(s_tfcontext *ctx, char *name));
