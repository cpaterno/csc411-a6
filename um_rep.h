#ifndef __UM_REP__
#define __UM_REP__

// This module exports all the shared secrets that each UM module needs
#include <stdint.h>
#include "seq.h"
#include "stack.h"

// The first secret is that each umword is actually a uint32_t
#define umword uint32_t 
#define NUM_REGS 8

// The second secret is the representation of a segmented memory, 
// which is represented as a struct SegMem_T 
// This data structure is exported as a pointer 
// to follow Hanson's interface formula
typedef struct SegMem_T {
    // sequence of memory segments
    Seq_T mem;
    // indices of the holes in the sequence
    Stack_T hole_idxs;
} *SegMem_T;

// The third secret is our representation of the Universal Machine, 
// which is represented as a struct UM_T
// This data structure is exported as a pointer 
// to follow Hanson's interface formula
typedef struct UM_T {
    // array of registers
    umword regs[NUM_REGS];
    // index of current instruction
    umword prog_count;
    // um segemented memory
    struct SegMem_T memory;
} *UM_T;
#endif
