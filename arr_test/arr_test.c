#include <stdio.h>
#include "arr.h"
#include "assert.h"
int main() {
    uint32_t *a = arr_new(5);
    assert(sizeof(a[0]) == sizeof(uint32_t));
    assert(arr_len(a) == 5);
    arr_free(a);
    uint32_t *tmp = arr_new(0);
    uint32_t *b = arr_clone(tmp, 200);
    arr_free(tmp);
    assert(arr_len(b) == 200);
    uint32_t *e = NULL;
    for (int i = 0; i < 200; ++i) {
        e = arr_at(b, i);
        *e = i;
    }
    uint32_t *c = arr_clone(b, 100);
    assert(arr_len(c) != arr_len(b));
    uint32_t *f = NULL;
    for (int i = 0; i < 100; ++i) {
        e = arr_at(b, i);
        f = arr_at(c, i);
        assert(*e == *f);
    }
    uint32_t *b2 = arr_clone(b, 100);
    assert(arr_len(c) == arr_len(b2));
    arr_free(b);
    for (int i = 0; i < 100; ++i) {
        e = arr_at(b2, i);
        f = arr_at(c, i);
        assert(*e == *f);
    } 
    arr_free(b2);
    arr_free(c);
    return 0;
}
