#ifndef __ARR_H__
#define __ARR_H__

// Length stored in first array element, therefore 
// allocated space is length + 1
#include <stdint.h>
#include <string.h>
#include "mem.h"
#include "assert.h"

// This is my array class, it is a single header library so every thing
// is inlined

// make new arr
static inline uint32_t *arr_new(uint32_t len) {
    uint32_t *arr = CALLOC(len + 1, sizeof(uint32_t));
    arr[0] = len;
    return arr;
}

// free it
static inline void arr_free(uint32_t *arr) {
    FREE(arr);
}

// get its length
static inline uint32_t arr_len(uint32_t *arr) {
    assert(arr);
    return arr[0];
}

// get a pointer to a specific element
static inline uint32_t *arr_at(uint32_t *arr, uint32_t i) {
    assert(i < arr_len(arr));
    return arr + i + 1;
}

// copy up to len length of an existing arr
// useful for copying and resizing
static inline uint32_t *arr_clone(uint32_t *arr, uint32_t len) {
    uint32_t *new_arr = arr_new(len);
    // side effect of asserting arr
    uint32_t old_len = arr_len(arr);
    uint32_t cpy_len = (old_len < len) ? old_len : len;
    memcpy(new_arr + 1, arr + 1, cpy_len * sizeof(uint32_t));
    return new_arr;
}
#endif
