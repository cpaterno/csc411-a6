#include <stdlib.h>
#include "mem.h"
#include "assert.h"
#include "array.h"
#include "um_mem.h"

// allocate a new segment with size and return the new segment's ID
umword allocate(SegMem_T pool, umword size) {
    assert(pool);
    // make sure we are not out of resources
    assert((umword)Seq_length(pool->mem) < UINT32_MAX);
    // no holes case
    umword idx = 0;
    if (Stack_empty(pool->hole_idxs)) {
        idx = Seq_length(pool->mem);
        Seq_addhi(pool->mem, Array_new(size, sizeof(umword)));
    // holes case
    } else {
        umword *idxp = Stack_pop(pool->hole_idxs);
        idx = *idxp;
        FREE(idxp);
        Seq_put(pool->mem, idx, Array_new(size, sizeof(umword))); 
    }
    return idx;
}

// deallocate a segment
void deallocate(SegMem_T pool, umword id) {
    assert(pool);
    Array_T seg = (Array_T)Seq_get(pool->mem, id);
    Array_free(&seg);
    Seq_put(pool->mem, id, NULL);
    umword *idxp;
    NEW(idxp);
    *idxp = id;
    Stack_push(pool->hole_idxs, idxp);
}
