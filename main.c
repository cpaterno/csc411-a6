#include "assert.h"
#include "loader.h"
#include "um.h"

int main(int argc, char *argv[]) {
    // one command line argument only
    assert(argc == 2);
    FILE *instream = fopen(argv[1], "rb");
    assert(instream);
    // load program
    Array_T instruct = loader(instream);
    // cleanup file pointer
    fclose(instream);
    // init um
    UM_T um = UM_init(instruct);
    // run um, it cleans up itself 😊 
    UM_run(um);
    return 0;
}
