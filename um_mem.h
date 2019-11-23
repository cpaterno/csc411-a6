#ifndef __UM_MEM__
#define __UM_MEM__

// This module exports 2 functions which allocate and deallocate 
// memory in a UM's segmented memory pool
// All functions in this module modify the pool by reference 
#include "um_rep.h"

// allocate a new segment with size and return the new segment's ID
extern umword allocate(SegMem_T pool, umword size);
// deallocate a segment
extern void deallocate(SegMem_T pool, umword id);
#endif
