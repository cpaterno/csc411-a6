#ifndef __UM_PARSER__
#define __UM_PARSER__

// This module exports six functions which extract
// the important parts from an um instruction
#include "bitpack.h"
#include "um_rep.h"

// takes word and extracts opcode
extern umword opcode(umword word);
// takes word, a three register instruction, and extracts register a
extern umword a_three(umword word);
// takes word, a three register instruction, and extracts register b
extern umword b_three(umword word);
// takes word, a three register instruction, and extracts register c
extern umword c_three(umword word);
// takes word, an ther instruction, and extracts register a
extern umword a_other(umword word);
// takes word, an other instruction, and extracts value
extern umword val_other(umword word);


#endif

