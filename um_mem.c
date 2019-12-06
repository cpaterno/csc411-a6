#include <stdlib.h>
#include "mem.h"
#include "assert.h"
#include "um_mem.h"

// allocate a new segment with size and return the new segment's ID
umword allocate(SegMem_T pool, umword size) {
    //assert(pool);
    // Handle 12th Fail State: Resource Exhaustion aka maximum number
    // of segments is 2^(num bits in umword) - 1, if this is true
    // then we can allocate memory
    // Must be a checked run-time error 
    assert((umword)Seq_length(pool->mem) < (umword)-1);
    umword idx = 0;
    // no holes case
    if (Stack_empty(pool->hole_idxs)) {
        // allocate new segment at the end
        idx = Seq_length(pool->mem);
        Seq_addhi(pool->mem, arr_new(size));
    // holes case
    } else {
        // allocate new segment at the latest hole index
        idx = (uintptr_t)Stack_pop(pool->hole_idxs);
        Seq_put(pool->mem, idx, arr_new(size)); 
    }
    return idx;
}

// deallocate a segment, at id
void deallocate(SegMem_T pool, umword id) {
    //assert(pool);
    umword *seg = (umword *)Seq_get(pool->mem, id);
    // 8th Fail State: 
    // attempting to unmap a segment which is not mapped
    assert(seg);
    arr_free(seg);
    // put NULL, our representation of an unmapped segment,
    // into the Seq at id
    Seq_put(pool->mem, id, NULL);
    // add hole index to the stack
    Stack_push(pool->hole_idxs, (void *)(uintptr_t)id);
}
