#include <stdio.h>
#include <stdlib.h> 
#include "st.h"

int main() {
    ST s = st_new();
    assert(st_empty(s));
    for (uint32_t i = 0; i < 10000; ++i) {
        st_push(s, i);
    }
    for (uint32_t i = 10000 - 1; i > 5000 - 1; --i) {
        assert(st_pop(s) == i);   
    } 
    assert(!st_empty(s));
    st_free(s);
    return 0;
}
