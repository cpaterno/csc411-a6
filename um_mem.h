#ifndef __UM_MEM__
#define __UM_MEM__

// This module exports 2 functions which allocate and deallocate
// memory in a UM's segmented memory pool
// All functions in this module modify the pool by reference
#include <stdlib.h>
#include "mem.h"
#include "assert.h"
#include "um_rep.h"

// allocate a new segment with size and return the new segment's ID
static inline umword allocate(SegMem_T pool, umword size) {
    umword idx = 0;
    // no holes case
    if (st_empty(pool->hole_idxs)) {
        // Handle 12th Fail State: Resource Exhaustion aka maximum number
        // of segments is 2^(num bits in umword) - 1, if this is true
        // then we can allocate memory
        // Must be a checked run-time error 
        idx = sq_len(pool->mem);
        assert(idx < (umword)-1);
        // allocate new segment at the end
        sq_append(pool->mem, arr_new(size));
    // holes case
    } else {
        // allocate new segment at the latest hole index
        idx = st_pop(pool->hole_idxs);
        sq_put(pool->mem, idx, arr_new(size)); 
    }
    return idx;
}

// deallocate a segment, at id
static inline void deallocate(SegMem_T pool, umword id) {
    umword *seg = sq_get(pool->mem, id);
    // 8th Fail State: 
    // attempting to unmap a segment which is not mapped
    assert(seg);
    arr_free(seg);
    // put NULL, our representation of an unmapped segment,
    // into the Seq at id
    sq_put(pool->mem, id, NULL);
    // add hole index to the stack
    st_push(pool->hole_idxs, id);
}
#endif
