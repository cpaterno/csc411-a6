#ifndef __UM__
#define __UM__

// This module exports 3 functions which manage the Universal Machine
#include <stdlib.h>
#include "assert.h"
#include "mem.h"
#include "um_rep.h"
#include "um_parser.h"
#include "um_instructions.h"

static inline void UM_free(UM_T *ump);

// I don't feel like defining 14 constants
enum instruction {
    CMOV, SEG_LOAD, SEG_STORE, ADD, 
    MUL, DIV, NAND, HALT, MAP, UNMAP,
    OUT, IN, LOAD_PROG, LOAD_VAL
};

// initialize a UM with a loaded program, prog is freed when UM is freed
static inline UM_T UM_init(umword *prog) {
    //assert(prog);
    UM_T um;
    // Calloc all parts of the struct
    NEW0(um);
    // initialize segment sequence
    um->memory.mem = Seq_new(0);
    // add loaded program
    Seq_addhi(um->memory.mem, prog);
    // initialize stack of hole indexes
    um->memory.hole_idxs = Stack_new();
    // current program
    um->prog = prog;
    return um;
}

// run an intialized Universal machine
static inline void UM_run(UM_T um) {
    umword *instp = 0;
    umword op = 0;
    umword inst = 0;
    // run the machine
    while (1) {
        // get current word
        // Array_get handles the 1st Fail State: 
        // Program Count out of bounds of $m[0]
        instp = arr_at(um->prog, um->prog_count);
        // get opcode
        inst = *instp;
        op = opcode(inst);
        // parse opcode
        switch (op) {
            case CMOV:
                cmov(um, a_three(inst), b_three(inst), c_three(inst));
                break;
            case SEG_LOAD:
                seg_load(um, a_three(inst), 
                         b_three(inst), c_three(inst));
                break;
            case SEG_STORE:
                seg_store(um, a_three(inst), 
                          b_three(inst), c_three(inst));
                break;
            case ADD:
                add(um, a_three(inst), b_three(inst), c_three(inst));
                break;
            case MUL:
                multiply(um, a_three(inst), 
                         b_three(inst), c_three(inst));
                break;
            case DIV:
                divide(um, a_three(inst), b_three(inst), c_three(inst));
                break;
            case NAND:
                nand(um, a_three(inst), b_three(inst), c_three(inst));
                break;
            // successfully exit the machine
            case HALT:
                UM_free(&um);
                exit(EXIT_SUCCESS);
                break;
            case MAP:
                map(um, b_three(inst), c_three(inst));
                break;
            case UNMAP:
                unmap(um, c_three(inst));
                break;
            case OUT:
                output(um, c_three(inst));
                break;
            case IN:
                input(um, c_three(inst));
                break;
            case LOAD_PROG:
                load_prog(um, b_three(inst), c_three(inst));
                break;
            case LOAD_VAL:
                load_val(um, a_other(inst), val_other(inst));
                break;
            // 2nd Fail State: Invalid Instruction (aka invalid opcode)
            default:
                exit(EXIT_FAILURE);
        }
    }
}

// cleanup the UM's resources
static inline void UM_free(UM_T *ump) {
    //assert(ump && *ump);
    // alias for the UM's sequence
    Seq_T s = (*ump)->memory.mem;
    // free all segments in the sequence
    umword *e = NULL;
    for (int i = Seq_length(s) - 1; i--; ) {
        e = (umword *)Seq_get(s, i);
        arr_free(e);
    }
    // free the sequence itself
    Seq_free(&s);
    // free the stack itself
    Stack_free(&((*ump)->memory.hole_idxs));
    // free the UM struct
    FREE(*ump);
}
#endif
