#ifndef __ST_H__
#define __ST_H__

#include <stddef.h>
#include <stdint.h>
#include "mem.h"
#include "assert.h"

typedef struct Node {
    uint32_t data;
    struct Node *next;
} *Node;

typedef struct ST {
    Node head;
} *ST;


static inline ST st_new(void) {
    ST st;
    NEW0(st);
    return st;
}

static inline void st_free(ST st) {
    Node tmp = NULL;
    while (st->head) {
        tmp = st->head;
        st->head = st->head->next;
        FREE(tmp);
    }
    FREE(st);
}

static inline uint32_t st_empty(ST st) {
    assert(st);
    return st->head == NULL;
}

static inline void st_push(ST st, uint32_t i) {
    assert(st);
    Node tmp;
    NEW(tmp);
    tmp->data = i;
    tmp->next = st->head;
    st->head = tmp;
}

static inline uint32_t st_pop(ST st) {
    // side effect of asserting st
    assert(!st_empty(st));
    uint32_t data = st->head->data;
    Node tmp = st->head;
    st->head = tmp->next;
    FREE(tmp);
    return data;
}
#endif
