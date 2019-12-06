#include "assert.h"
#include "um_loader.h"
#include "um.h"

int main(int argc, char *argv[]) {
    // one command line argument only
    assert(argc == 2);
    FILE *instream = fopen(argv[1], "rb");
    // load program, checks to see if file is open
    umword *instruct = loader(instream);
    fclose(instream);
    // init um
    UM_T um = UM_init(instruct);
    // run um, it cleans up itself and the loaded program 😊
    UM_run(um);
    return 0;
}
