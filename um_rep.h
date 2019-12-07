#ifndef __UM_REP__
#define __UM_REP__

// This module exports all the shared secrets that each UM module needs
#include <stdint.h>
#include "st.h"
#include "sq.h"
#include "arr.h"

/* INVARIANTS
 * 
 * Segments are represented by an Array_T
 * A segment is unmapped if the pointer representing the Array_T is NULL
 * A segment is mapped if the pointer representing the Array_T is not NULL
 *
 * Holes in the segmented memory are represented by a Stack_T
 * An empty Stack_T represents a segmented memory without any holes.
 * If the stack is not empty, each heap allocated integer in the stack
 * represents the index of the segmented memory which has 
 * its Segment represented as NULL.
*/

// The first secret is that each umword is actually a uint32_t
#define umword uint32_t
// The second shared secret is that there are 8 registers
#define NUM_REGS 8

// The third shared secret is the representation of a segmented memory,
// which is represented as a struct SegMem_T 
// This data structure is exported as a pointer 
// to follow Hanson's interface style
typedef struct SegMem_T {
    // sequence of memory segments, segments are Array_Ts
    // therefore they need to be freed
    SQ mem;
    // indices of the holes in the sequence,
    // Hanson's stack is a boxed ADT, therefore the elements 
    // of the stack need to be freed
    ST hole_idxs;
} *SegMem_T;

// The fourth shared secret is our representation of the Universal Machine, 
// which is represented as a struct UM_T
// This data structure is exported as a pointer 
// to follow Hanson's interface style
typedef struct UM_T {
    // um segemented memory
    struct SegMem_T memory;
    // array of registers
    umword regs[NUM_REGS];
    // copy of prog pointer for locality
    umword *prog;
    // index of current instruction
    umword prog_count;
} *UM_T;
#endif
