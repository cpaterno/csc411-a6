#ifndef __ST_H__
#define __ST_H__

#include <stddef.h>
#include <stdint.h>
#include "mem.h"
#include "assert.h"

// Module represents our Stack data structure, this is a single header
// library so all functions are inlined

typedef struct Node {
    struct Node *next;
    uint32_t data;
} *Node;

typedef struct ST {
    Node head;
} *ST;

// make new Stack
static inline ST st_new(void) {
    ST st;
    NEW0(st);
    return st;
}

// free it
static inline void st_free(ST st) {
    Node tmp = NULL;
    // free each node
    while (st->head) {
        tmp = st->head;
        st->head = st->head->next;
        FREE(tmp);
    }
    // free stack struct
    FREE(st);
}

// determine if stack is empty
static inline uint32_t st_empty(ST st) {
    assert(st);
    return st->head == NULL;
}

// push something to stack
static inline void st_push(ST st, uint32_t i) {
    assert(st);
    Node tmp;
    NEW(tmp);
    tmp->data = i;
    tmp->next = st->head;
    st->head = tmp;
}

// remove something from stack
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
