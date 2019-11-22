#include <stdio.h>
#include "assert.h"
#include "um_parser.h"
#include "um_rep.h"

int main(int argc, char *argv[]) {
    /*
    // one command line argument only
    assert(argc == 2);
    FILE *instream = fopen(argv[1], "rb");
    assert(instream);
    fclose(instream);
    */
    (void)argc;
    (void)argv;
    umword inst = 1879048464;
    printf("%u %u %u %u\n", opcode(inst), a_three(inst), b_three(inst), c_three(inst));
    inst = 3539992575;
    printf("%u %u %u\n", opcode(inst), a_other(inst), val_other(inst));
    return 0;
}
