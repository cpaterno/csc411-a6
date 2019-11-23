#ifndef __UM_INSTRUCTIONS__
#define __UM_INSTRUCTIONS__

// This module exports 13 functions representing
// all instructions that a Universal Machine can do,
// excluding HALT
// All functions in this module modify the UM by reference
#include "um_rep.h"

// conditional move overwrites register a with the value in register b if 
// the value in register c is not 0
extern void cmov(UM_T um, umword a, umword b, umword c);
// segmented load overwrites register a with the memory block represented 
// by the values at register b and register c
extern void seg_load(UM_T um, umword a, umword b, umword c);
// segmented store overwrites the memory block  represented by the values 
// at register a and register b with the value in register c 
extern void seg_store(UM_T um, umword a, umword b, umword c);
// add the values in register b and c, put the result in register a 
extern void add(UM_T um, umword a, umword b, umword c);
// multiply the values in register b and c, put the result in register a
extern void multiply(UM_T um, umword a, umword b, umword c);
// divide the values in register b and c, put the result in register a
extern void divide(UM_T um, umword a, umword b, umword c);
// bitwise not and on the values in register b and c, 
// put the result in register a 
extern void nand(UM_T um, umword a, umword b, umword c);
// map a new segment of memory with equal to whats in register c and store 
// the segment ID in register b
extern void map(UM_T um, umword b, umword c);
// unmap a segment of memory with its segment ID in register c
extern void unmap(UM_T um, umword c);
// output a character to the IO device, based on the value of register c
extern void output(UM_T um, umword c);
// input a character to register c
extern void input(UM_T um, umword c);
// load a new program into the 0 segment from the memory segment ID 
// represented by the value of register b, if that value is 0 then 
// this is a jump
extern void load_prog(UM_T um, umword b, umword c);
// overwrite the value in register a with value
extern void load_val(UM_T um, umword a, umword val);
#endif
