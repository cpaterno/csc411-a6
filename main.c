#include "assert.h"
#include "load_prog.h"
#include "um_rep.h"

int main(int argc, char *argv[]) {
    // one command line argument only
    assert(argc == 2);
    FILE *instream = fopen(argv[1], "rb");
    assert(instream);
    // test code begins here
    FILE *fp = fopen("out.test", "wb");
    Array_T instruct = load_prog(instream);
    for (int i = 0; i < Array_length(instruct); ++i) {
        fwrite(Array_get(instruct, i), 1, sizeof(umword), fp);
    }
    Array_free(&instruct);
    fclose(fp);
    // end of test code
    fclose(instream);
    return 0;
}
