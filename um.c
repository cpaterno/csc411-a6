#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "mem.h"
#include "um.h"
#include "um_parser.h"
#include "um_instructions.h"

// I don't feel like defining 14 constants
enum instruction {
    CMOV, SEG_LOAD, SEG_STORE, ADD, 
    MUL, DIV, NAND, HALT, MAP, UNMAP,
    OUT, IN, LOAD_PROG, LOAD_VAL
};


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
    umword *instp = 0;
    umword op = 0;
    Array_T prog = NULL; 
    // run the machine
    while (1) {
        // load program's segment
        prog = (Array_T)Seq_get(um->memory.mem, 0);
        // get current word
        instp = (umword *)Array_get(prog, um->prog_count);
        // get opcode
        op = opcode(*instp);
        // parse opcode
        switch (op) {
            case CMOV:
                cmov(um, a_three(*instp), b_three(*instp), c_three(*instp));
                break;
            case SEG_LOAD:
                seg_load(um, a_three(*instp), 
                         b_three(*instp), c_three(*instp));
                break;
            case SEG_STORE:
                seg_store(um, a_three(*instp), 
                          b_three(*instp), c_three(*instp));
                break;
            case ADD:
                add(um, a_three(*instp), b_three(*instp), c_three(*instp));
                break;
            case MUL:
                multiply(um, a_three(*instp), 
                         b_three(*instp), c_three(*instp));
                break;
            case DIV:
                divide(um, a_three(*instp), b_three(*instp), c_three(*instp));
                break;
            case NAND:
                nand(um, a_three(*instp), b_three(*instp), c_three(*instp));
                break;
            // successfully exit the machine
            case HALT:
                UM_free(&um);
                exit(EXIT_SUCCESS);
                break;
            case MAP:
                map(um, b_three(*instp), c_three(*instp));
                break;
            case UNMAP:
                unmap(um, c_three(*instp));
                break;
            case OUT:
                output(um, c_three(*instp));
                break;
            case IN:
                input(um, c_three(*instp));
                break;
            case LOAD_PROG:
                load_prog(um, b_three(*instp), c_three(*instp));
                break;
            case LOAD_VAL:
                load_val(um, a_other(*instp), val_other(*instp));
                break;
            // invalid opcode
            default:
                exit(EXIT_FAILURE);
        }
        // if this fails, out of instructions
        assert(um->prog_count < (umword)Array_length(prog));
    }
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
