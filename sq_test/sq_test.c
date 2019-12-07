#include <stdio.h>
#include <stdlib.h> 
#include "sq.h"

int main() {
    SQ s = sq_new(0);
    assert(sq_len(s) == 0);
    assert(sq_cap(s) == DEF_SIZE);
    uint32_t *x = NULL;
    for (uint32_t i = 0; i < 100 * DEF_SIZE; ++i) {
        NEW(x);
        *x = i;
        sq_append(s, x);
    }
    assert(sq_len(s) == 100 * DEF_SIZE);
    for (uint32_t i = 100 * DEF_SIZE; i--; ) {
        x = sq_get(s, i);
        assert(*x == i);
        *x = 0;
        x = sq_get(s, i);
        assert(*x == 0);
        FREE(x);
    }
    sq_free(s);
    return 0;
}
