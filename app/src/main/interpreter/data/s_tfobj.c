#include "s_tfobj.h"
#include "../utils.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../debug.h"

/* ===== Internal ===== */

static s_tfobj *tfobjCreate(e_tfobj_type type) {
    s_tfobj *o = xmalloc(sizeof(*o));
    o->type = type;
    o->ref_count = 1;
    return o;
}

/* ===== Lifetime ===== */

void tfobjRetain(s_tfobj *o) {
    o->ref_count++;
}

void tfobjRelease(s_tfobj *o) {
    assert(o->ref_count > 0);
    if (--o->ref_count == 0)
        tfobjFree(o);
}

void tfobjFree(s_tfobj *o) {
    switch (o->type) {
        case LIST:
            for (size_t i = 0; i < o->list.len; ++i)
                tfobjRelease(o->list.ele[i]);
            free(o->list.ele);
            break;

        case SYMBOL:
        case STR:
            free(o->str.ptr);
            break;

        default:
            break;
    }
    free(o);
}


/* ===== Utilities ==== */

// Compares two string objects and returns their comparison state:
// SAME_MEMBER   -> strings are identical
// MAJOR_MEMBER_1 -> 'a' is greater than 'b'
// MAJOR_MEMBER_2 -> 'a' is less than 'b'
e_comparison_state tfobjCompareString(s_tfobj *a, s_tfobj *b) {
    assert(a!=NULL && b!=NULL);

    const unsigned long long min_len = a->str.len < b->str.len ? a->str.len : b->str.len;

    // Comparo solo la parte comune ( scorre con min_len progressivamenre)
    const int cmp = memcmp(a->str.ptr, b->str.ptr, min_len);

    if (cmp == 0) {
        if (a->str.len == b->str.len)return SAME_MEMBER;
        if (a->str.len > b->str.len) return MAJOR_MEMBER_1;
        return MAJOR_MEMBER_2;
    }
    if (cmp < 0) return MAJOR_MEMBER_2;
    return MAJOR_MEMBER_1;
}

/* ===== Creation ===== */

s_tfobj *tfobjCreateString(const char *s, unsigned long long len) {
    s_tfobj *o = tfobjCreate(STR);
    o->str.ptr = xmalloc(len + 1);
    memcpy(o->str.ptr, s, len);
    o->str.ptr[len] = 0;
    o->str.len = len;
    return o;
}

s_tfobj *tfobjCreateSymbol(const char *s, unsigned long long len) {
    s_tfobj *o = tfobjCreateString(s, len);
    o->type = SYMBOL;
    return o;
}

s_tfobj *tfobjCreateInt(int value) {
    s_tfobj *o = tfobjCreate(INT);
    o->i = value;
    return o;
}


s_tfobj *tfobjCreateList(void) {
    s_tfobj *o = tfobjCreate(LIST);
    o->list.ele = NULL;
    o->list.len = 0;
    return o;
}

/* ===== List ===== */

void tfobjListPush(s_tfobj *l, s_tfobj *ele) {
    l->list.ele = xrealloc(l->list.ele, sizeof(s_tfobj *) * (l->list.len + 1));
    l->list.ele[l->list.len++] = ele;
}

/* ===== Debug ===== */

void tfobjDump(const s_tfobj *program) {
    if(program==NULL || program->list.ele==NULL || program->type!=LIST) return;
    LOG_I("[");
    for (size_t i = 0; i < program->list.len; ++i) {
        const s_tfobj *o = program->list.ele[i];
        if(o==NULL) continue;
        switch (o->type) {
            case INT: LOG_I("%d", o->i);
                break;
            case SYMBOL: if(o->str.ptr!=NULL) LOG_I("%s", o->str.ptr);
                break;
            case LIST: tfobjDump(o);
                break;
            default: LOG_I("?");
                break;
        }
        if (i < program->list.len - 1)LOG_I(" ");  // LINT
    }
    LOG_I("]\n");
}

char * tfobjToString(const s_tfobj *program){
    if(program==NULL || program->list.ele==NULL || program->type!=LIST) return "";

    char *ret = calloc(256, 1);
    if (!ret) return NULL;

    for (size_t i = 0; i < program->list.len; ++i) {
        const s_tfobj *o = program->list.ele[i];
        if(o==NULL) continue;
        switch (o->type) {
            case INT: {
                // parsing e concatena
                snprintf(ret + strlen(ret),
                        sizeof(ret) - strlen(ret),
                        "%d", o->i);
                break;
            }
            case SYMBOL: if(o->str.ptr!=NULL) strcat(ret,o->str.ptr);
                break;
            case LIST: tfobjDump(o);
                break;
            default:
                strcat(ret,"?");
                break;
        }
    }
    return ret;
}
