#include <stdio.h>
#include "assert.h"

int main(int argc, char *argv[]) {
    // one command line argument only
    assert(argc == 2);
    FILE *instream = fopen(argv[1], "rb");
    assert(instream);
    fclose(instream);
    return 0;
}
