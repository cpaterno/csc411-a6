#ifndef __UM__
#define __UM__

// This module exports 3 functions which manage the Universal Machine
#include "array.h"
#include "um_rep.h"

// initialize a UM with a loaded program, prog is freed when UM is freed
extern UM_T UM_init(Array_T prog);
// run an intialized Universal machine, this function also calls UM_free
extern void UM_run(UM_T um);
// cleanup the UM's resources
extern void UM_free(UM_T *ump);
#endif
