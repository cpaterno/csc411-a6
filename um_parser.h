#ifndef __UM_PARSER__
#define __UM_PARSER__

// This module exports six functions which extract
// the important parts from an um instruction

#include "bitpack.h"
#include "um_rep.h"

// takes word and extracts opcode
extern umword opcode(umword word);

// takes word and extracts the three register for a
extern umword a_three(umword word);

// takes word and extracts the three register for b
extern umword b_three(umword word);

// takes word and extracts the three register for c
extern umword c_three(umword word);

// takes word and extracts the other register for a
extern umword a_other(umword word);

// takes word and extracts the other register for val
extern umword val_other(umword word);


#endif

