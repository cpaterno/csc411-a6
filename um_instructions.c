#include <stdio.h>
#include "assert.h"
#include "array.h"
#include "um_instructions.h"
#include "um_mem.h"

// make sure reg index is in bounds
static inline void ok_reg(umword r) {
    assert(r < NUM_REGS);
}

// conditional move overwrites register a with the value in register b if
// the value in register c is not 0
void cmov(UM_T um, umword a, umword b, umword c) {
    assert(um);
    ok_reg(a);
    ok_reg(b);
    ok_reg(c);
    if (um->regs[c]) {
        um->regs[a] = um->regs[b];
    }
    // move program counter
    ++(um->prog_count);    
}

// segmented load overwrites register a with the memory block represented
// by the values at register b and register c
void seg_load(UM_T um, umword a, umword b, umword c) {
    assert(um);
    ok_reg(a);
    ok_reg(b);
    ok_reg(c);
    // Array_get handles the 5th Fail State: SegLoad accesses something 
    // out of bounds of the memory pool or out of bounds of the segment 
    Array_T seg = (Array_T)Seq_get(um->memory.mem, um->regs[b]);
    // Array_get also handles the 3rd Fail State: SegLoad refers to unmapped (NULL)
    umword *e = (umword *)Array_get(seg, um->regs[c]);
    um->regs[a] = *e;
    // move program counter
    ++(um->prog_count);    
}

// segmented store overwrites the memory block  represented by the values
// at register a and register b with the value in register c
void seg_store(UM_T um, umword a, umword b, umword c) {
    assert(um);
    ok_reg(a);
    ok_reg(b);
    ok_reg(c);
    // Array_get handles the 6th Fail State: SegStore accesses something 
    // out of bounds of the memory pool or out of bounds of the segment 
    Array_T seg = (Array_T)Seq_get(um->memory.mem, um->regs[a]);
    // Array_get handles the 4th Fail State: SegStore refers to unmapped (NULL)
    umword *e = (umword *)Array_get(seg, um->regs[b]);
    *e = um->regs[c];
    // move program counter
    ++(um->prog_count);    
}

// add the values in register b and c, put the result in register a
void add(UM_T um, umword a, umword b, umword c) {
    assert(um);
    ok_reg(a);
    ok_reg(b);
    ok_reg(c);
    um->regs[a] = (um->regs[b] + um->regs[c]);
    // move program counter
    ++(um->prog_count);    
}

// multiply the values in register b and c, put the result in register a
void multiply(UM_T um, umword a, umword b, umword c) {
    assert(um);
    ok_reg(a);
    ok_reg(b);
    ok_reg(c);
    um->regs[a] = (um->regs[b] * um->regs[c]);
    // move program counter
    ++(um->prog_count);    
}

// divide the values in register b and c, put the result in register a
void divide(UM_T um, umword a, umword b, umword c) {
    assert(um);
    ok_reg(a);
    ok_reg(b);
    ok_reg(c);
    // Handle 9th Fail State: Division by 0
    assert(um->regs[c]);
    um->regs[a] = (um->regs[b] / um->regs[c]);
    // move program counter
    ++(um->prog_count);    
}

// bitwise not and on the values in register b and c,
// put the result in register a
void nand(UM_T um, umword a, umword b, umword c) {
    assert(um);
    ok_reg(a);
    ok_reg(b);
    ok_reg(c);
    um->regs[a] = ~((um->regs[b]) & (um->regs[c]));
    // move program counter
    ++(um->prog_count);    
}

// map a new segment of memory with size equal to whats in register c 
// and store the segment ID in register b
void map(UM_T um, umword b, umword c) {
    assert(um);
    ok_reg(b);
    ok_reg(c);
    um->regs[b] = allocate(&(um->memory), um->regs[c]);
    // move program counter
    ++(um->prog_count);    
}

// unmap a segment of memory with its segment ID in register c
void unmap(UM_T um, umword c) {
    assert(um);
    ok_reg(c);
    // 7th Fail State: Can't unmap segment 0
    assert(um->regs[c]);
    deallocate(&(um->memory), um->regs[c]);
    // move program counter
    ++(um->prog_count);    
}

// output a character to the IO device, based on the value of register c
void output(UM_T um, umword c) {
    assert(um);
    ok_reg(c);
    // Handle 11th Fail State: Print invalid character
    // Valid characters are [0, 255]
    assert(um->regs[c] <= UINT8_MAX);
    putchar(um->regs[c]);
    // move program counter
    ++(um->prog_count);    
}

// input a character, using the IO device, to register c
void input(UM_T um, umword c) {
    assert(um);
    ok_reg(c);
    um->regs[c] = getchar();
    // char is between [0, 255] or EOF
    assert(um->regs[c] <= UINT8_MAX || um->regs[c] == (umword)EOF);
    // move program counter
    ++(um->prog_count);    
}

// load a new program into the 0 segment from the memory segment ID
// represented by the value of register b, if that value is 0 then
// this is a jump
void load_prog(UM_T um, umword b, umword c) {
    assert(um);
    ok_reg(b);
    ok_reg(c);
    if (um->regs[b]) {
        // free currently loaded program
        Array_T prog = (Array_T)Seq_get(um->memory.mem, 0);
        Array_free(&prog);
        // get new program to load into segment 0
        Array_T seg = (Array_T)Seq_get(um->memory.mem, um->regs[b]);
        // Array_copy handles 10th Fail State: 
        // Loading an unmapped segment as a program
        Seq_put(um->memory.mem, 0, Array_copy(seg, Array_length(seg)));
    }
    // move the program counter
    um->prog_count = um->regs[c];
}

// overwrite the value in register a with value
void load_val(UM_T um, umword a, umword val) {
    assert(um);
    ok_reg(a);
    um->regs[a] = val;
    // move program counter
    ++(um->prog_count);    
}
