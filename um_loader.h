#ifndef __UM_LOADER__
#define __UM_LOADER__

// Module that loads an UM program from a file
// Exports 1 function
#include <stdio.h>
#include <string.h>
#include "um_rep.h"
#include "arr.h" 

// given a file pointer return an Array_T of instruction words,
// user will have to free Array_T
static inline umword *loader(FILE *fp) {
    assert(fp);
    size_t size = sizeof(umword);
    // initialize instruction array
    int len = 0;
    umword *instruct = arr_new(len);
    umword *tmp = NULL;
    umword buf = 0;
    umword *elem = NULL;
    int i = 0;
    // keep reading file, until there is not enough bytes yet for an umword
    while (fread(&buf, 1, size, fp) == size) {
        // Array needs to be resized
        if (i == len) {
            // C++ vector growth algorithm
            if (len != 0) {
                len *= 2;
            } else {
                len = 1;
            }
            tmp = instruct;
            instruct = arr_clone(instruct, len);
            arr_free(tmp);
        }
        // put buf into instruct
        elem = arr_at(instruct, i++);
        // Specialized bit swap for 32 bit words, courtesy of GCC
        buf = __builtin_bswap32(buf);
        memcpy(elem, &buf, size);
    }
    // Remove extra space
    tmp = instruct;
    instruct = arr_clone(instruct, i);
    arr_free(tmp);
    return instruct;
}
#endif
