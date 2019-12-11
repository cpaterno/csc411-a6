#ifndef __UM_PARSER__
#define __UM_PARSER__

// This module exports six functions which extract
// the important parts from an um instruction
#include "um_rep.h"

#define OP_WIDTH 4
#define REG_WIDTH 3
#define VAL_WIDTH 25
#define OP_LSB 28
#define A_3_LSB 6
#define B_3_LSB 3
#define C_3_LSB 0
#define A_OTHER_LSB 25
#define VAL_LSB 0
#define WSIZE 64

// Inlined version of getu from Bitpack
static inline uint64_t getu(uint64_t word, unsigned width, unsigned lsb) {
    return ((word << (WSIZE - (width + lsb))) >> (WSIZE - width));
}

// takes word and extracts opcode
static inline umword opcode(umword word) {
    return getu(word, OP_WIDTH, OP_LSB);
}

// takes word, a three register instruction, and extracts register a
static inline umword a_three(umword word) {
    return getu(word, REG_WIDTH, A_3_LSB);
}

// takes word, a three register instruction, and extracts register b
static inline umword b_three(umword word) {
    return getu(word, REG_WIDTH, B_3_LSB);
}

// takes word, a three register instruction, and extracts register c
static inline umword c_three(umword word) {
    return getu(word, REG_WIDTH, C_3_LSB);
}

// takes word, an other instruction, and extracts register a
static inline umword a_other(umword word) {
    return getu(word, REG_WIDTH, A_OTHER_LSB);
}

// takes word, an other instruction, and extracts value
static inline umword val_other(umword word) {
    return getu(word, VAL_WIDTH, VAL_LSB);
}
#endif
