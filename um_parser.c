#include "um_parser.h"

#define OP_WIDTH 4
#define REG_WIDTH 3
#define VAL_WIDTH 25
#define OP_LSB 28
#define A_3_LSB 6
#define B_3_LSB 3
#define C_3_LSB 0
#define A_OTHER_LSB 25
#define VAL_LSB 0


// takes word and extracts opcode
umword opcode(umword word) {
    return Bitpack_getu(word, OP_WIDTH, OP_LSB);
}

// takes word and extracts the three register for a
umword a_three(umword word) {
    return Bitpack_getu(word, REG_WIDTH, A_3_LSB);
}

// takes word and extracts the three register for b
umword b_three(umword word) {
    return Bitpack_getu(word, REG_WIDTH, B_3_LSB);
}

// takes word and extracts the three register for c
umword c_three(umword word) {
    return Bitpack_getu(word, REG_WIDTH, C_3_LSB);
}

// takes word and extracts the other register for a
umword a_other(umword word) {
    return Bitpack_getu(word, REG_WIDTH, A_OTHER_LSB);
}

// takes word and extracts the other register for val
umword val_other(umword word) {
    return Bitpack_getu(word, VAL_WIDTH, VAL_LSB);
}

