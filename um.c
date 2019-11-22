#include <string.h>
#include "assert.h"
#include "mem.h"
#include "um.h"
#include "um_parser.h"
#include "um_instructions.h"
#include "um_mem.h"

// initialize a UM with a program
UM_T UM_init(Array_T prog) {
    assert(prog);
    UM_T um;
    NEW(um);
    memset(um->regs, 0, NUM_REGS * sizeof(umword));
    um->prog_count = 0;
    um->memory.mem = Seq_new(0);
    um->memory.hole_count = 0;
    Seq_addhi(um->memory.mem, prog);
    return um;
}

// run an intialized Universal machine
void UM_run(UM_T um) {
    (void)um;
}

// cleanup the UM's resources
void UM_free(UM_T *ump) {
    assert(ump && *ump);
    // alias for the UM's sequence
    Seq_T s = (*ump)->memory.mem;
    // free all segments in the sequence
    Array_T e = NULL;
    for (int i = 0; i < Seq_length(s); ++i) {
        e = (Array_T)Seq_get(s, i);
        if (e) {
            Array_free(&e);
        }
    }
    // free the sequence itself
    Seq_free(&s);
    // free the UM struct
    FREE(*ump);
}
