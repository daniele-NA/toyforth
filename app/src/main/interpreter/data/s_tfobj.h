#pragma once
#include <stdbool.h>

/* ===== Types ===== */

typedef enum {
    INT, STR, SYMBOL, LIST
} e_tfobj_type;

typedef enum {
    SAME_MEMBER,
    MAJOR_MEMBER_1,
    MAJOR_MEMBER_2
} e_comparison_state;

typedef struct s_tfobj {
    int ref_count;
    e_tfobj_type type; // int, string, list, ecc.
    union {
        int i;
        struct {
            char *ptr;
            unsigned long long len;
        } str;
        struct {
            struct s_tfobj **ele;
            unsigned long long len;
        } list;
    };
} s_tfobj;

/* ===== Lifetime ===== */

void tfobjRetain(s_tfobj *o);
void tfobjRelease(s_tfobj *o);
void tfobjFree(s_tfobj *o);

/* ===== Utilities ===== */

e_comparison_state tfobjCompareString(s_tfobj *a,s_tfobj *b);

/* ===== Creation ===== */

s_tfobj *tfobjCreateInt(int value);
s_tfobj *tfobjCreateBool(int value);
s_tfobj *tfobjCreateString(const char *s, unsigned long long len);
s_tfobj *tfobjCreateSymbol(const char *s, unsigned long long len);
s_tfobj *tfobjCreateList(void);

/* ===== List ===== */

/* It is up to the caller to retain the element if needed */
void tfobjListPush(s_tfobj *list, s_tfobj *ele);

/* ===== Debug ===== */

void tfobjDump(const s_tfobj *program);
char * tfobjToString(const s_tfobj *program);
