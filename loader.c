#include <string.h>
#include "mem.h"
#include "assert.h"
#include "um_rep.h"
#include "loader.h"

// Unfortunately I am on a little endian machine, so this is necessary
static inline void endian_switch(uint8_t *buf, unsigned len) {
    assert(buf);
    uint8_t temp = 0;
    for (unsigned i = 0; i < len / 2; ++i) {
        temp = buf[i];
        buf[i] = buf[len - 1 - i];
        buf[len - 1 - i] = temp;
    }
}

// given a file pointer return an Array_T of instruction words
Array_T loader(FILE *fp) {
    assert(fp);
    Array_T instruct = Array_new(0, sizeof(umword));
    size_t size = Array_size(instruct);
    int len = Array_length(instruct);
    uint8_t buf[size];
    umword *elem = NULL;
    int i = 0;
    while (fread(buf, 1, size, fp) == size) {
        // Array needs to be resized
        if (i == len) {
            if (len != 0) {
                len *= 2;
            } else {
                len = 1;
            }
            Array_resize(instruct, len);
        }
        elem = (umword *)Array_get(instruct, i++);
        assert(sizeof(*elem) == size);
        endian_switch(buf, size);
        memcpy(elem, buf, size);
    }
    // Remove extra space
    Array_resize(instruct, i);
    return instruct;
}
