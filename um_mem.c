#include <stdlib.h>
#include "assert.h"
#include "array.h"
#include "um_mem.h"

// allocate a new segment with size and return the new segment's ID
umword allocate(SegMem_T pool, umword size) {
    assert(pool);
    // make sure we are not out of resources
    assert((umword)Seq_length(pool->mem) < UINT32_MAX);
    int idx = -1;
    // no holes case
    if (!(pool->hole_count)) {
        idx = Seq_length(pool->mem);
        Seq_addhi(pool->mem, Array_new(size, sizeof(umword)));
    // holes case
    } else {
        Array_T e = NULL;
        // loop until hole is found
        for (int i = 0; i < Seq_length(pool->mem); ++i) {
            e = (Array_T)Seq_get(pool->mem, i);
            if (!e) {
                Seq_put(pool->mem, i, Array_new(size, sizeof(umword)));
                idx = i;
                --(pool->hole_count);
                break;
            }
        }
        assert(idx > -1);
    }
    return idx;
}
// deallocate a segment
void deallocate(SegMem_T pool, umword id) {
    assert(pool);
    Array_T seg = (Array_T)Seq_get(pool->mem, id);
    Array_free(&seg);
    Seq_put(pool->mem, id, NULL);
    ++(pool->hole_count);
}
