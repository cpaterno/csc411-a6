#ifndef __SQ_H__
#define __SQ_H__

#include <stdint.h>
#include "mem.h"
#include "assert.h"

#define DEF_SIZE 1000

typedef struct SQ {
    void **seq;
    uint32_t len;
    uint32_t cap;
} *SQ;

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

static inline void sq_free(SQ sq) {
    assert(sq);
    FREE(sq->seq);
    FREE(sq);
}

static inline uint32_t sq_len(SQ sq) {
    assert(sq);
    return sq->len;
}

static inline uint32_t sq_cap(SQ sq) {
    assert(sq);
    return sq->cap;
}

static inline void *sq_at(SQ sq, uint32_t i) {
    // side effect of asserting sq
    assert(i < sq_len(sq));
    return sq->seq[i];
}

static inline void sq_append(SQ sq, void *e) {
    // side effect of asserting sq
    uint32_t len = sq_len(sq);
    if (len == sq->cap) {
        sq->cap *= 2;
        RESIZE(sq->seq, sq->cap * sizeof(void *));
    }
    (sq->len)++;
    sq->seq[len] = e;
}
#endif
