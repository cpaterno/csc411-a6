#include <string.h>
#include "mem.h"
#include "assert.h"
#include "um_rep.h"
#include "um_loader.h"

// given a file pointer return an Array_T of instruction words,
// user will have to free Array_T
Array_T loader(FILE *fp) {
    assert(fp);
    size_t size = sizeof(umword);
    // initialize instruction array
    int len = 0;
    Array_T instruct = Array_new(len, size);
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
            Array_resize(instruct, len);
        }
        // put buf into instruct
        elem = (umword *)Array_get(instruct, i++);
        // Specialized bit swap for 32 bit words, courtesy of GCC
        buf = __builtin_bswap32(buf);
        memcpy(elem, &buf, size);
    }
    // Remove extra space
    Array_resize(instruct, i);
    return instruct;
}
