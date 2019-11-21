#include "assert.h"
#include "load_prog.h"
#include "um_rep.h"

// Unfortunately I am on a little endian machine, so this is necessary
void endian_switch(unsigned char *buf, unsigned len) {
    assert(buf);
    char temp = 0;
    for (unsigned i = 0; i < len / 2; ++i) {
        temp = buf[i];
        buf[i] = buf[len - 1 - i];
        buf[len - 1 - i] = temp;
    }
}

int main(int argc, char *argv[]) {
    // one command line argument only
    assert(argc == 2);
    FILE *instream = fopen(argv[1], "rb");
    assert(instream);
    // test code begins here
    FILE *fp = fopen("out.test", "wb");
    Array_T instruct = load_prog(instream);
    umword *e = NULL;
    for (int i = 0; i < Array_length(instruct); ++i) {
        e = Array_get(instruct, i);
        endian_switch((unsigned char *)e, sizeof(umword));
        fwrite(e, 1, sizeof(umword), fp);
    }
    Array_free(&instruct);
    fclose(fp);
    // end of test code
    fclose(instream);
    return 0;
}
