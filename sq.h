#ifndef __SQ_H__
#define __SQ_H__

#include <stdint.h>
#include "mem.h"
#include "assert.h"

#define DEF_SIZE 1000
// Module represents my Sequence data structure, this is a single header
// library so all functions are inlined


// representation of SQ
typedef struct SQ {
    // NULL is unmapped segment, not null is mapped
    void **seq;
    uint32_t len;
    uint32_t cap;
} *SQ;

// make a new SQ
static inline SQ sq_new(uint32_t len) {
    SQ sq;
    NEW(sq);
    if (!len) {
        len = DEF_SIZE;
    }
    sq->cap = len;
    sq->len = 0;
    sq->seq = CALLOC(len, sizeof(void *));
    return sq;
}

// free it
static inline void sq_free(SQ sq) {
    assert(sq);
    FREE(sq->seq);
    FREE(sq);
}

// get its length
static inline uint32_t sq_len(SQ sq) {
    assert(sq);
    return sq->len;
}

// get its capacity
static inline uint32_t sq_cap(SQ sq) {
    assert(sq);
    return sq->cap;
}

// get ith element of an SQ
static inline void *sq_get(SQ sq, uint32_t i) {
    // side effect of asserting sq
    assert(i < sq_len(sq));
    return sq->seq[i];
}

// put something in an SQ 
static inline void sq_put(SQ sq, uint32_t i, void *e) {
    // side effect of asserting sq
    assert(i < sq_len(sq));
    sq->seq[i] = e;
}

// append something to an SQ
static inline void sq_append(SQ sq, void *e) {
    // side effect of asserting sq
    uint32_t len = sq_len(sq);
    // grow case
    if (len == sq->cap) {
        sq->cap *= 2;
        RESIZE(sq->seq, sq->cap * sizeof(void *));
    }
    (sq->len)++;
    sq->seq[len] = e;
}
#endif
