#pragma once
#include <stdlib.h>
#include "debug.h"


/* ============== Allocation Wrappers ============== */
/* Safe memory allocation wrappers */

/* Safely allocate memory. Exits if malloc fails. */
static void *xmalloc(const unsigned long long size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        LOG_E("Out of memory allocating %llu bytes\n", size);
        exit(1);
    }
    return ptr;
}

/* Safely reallocate memory. Exits if realloc fails. */
static void *xrealloc(void *old_ptr,const unsigned long long size) {
    void *ptr = realloc(old_ptr,size);
    if (ptr == NULL) {
        LOG_E("Out of memory reallocation %llu bytes\n", size);
        exit(1);
    }
    return ptr;
}
