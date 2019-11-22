#ifndef __UM__
#define __UM__

// This module exports 3 functions which manage the Universal Machine

// export a pointer to be consistent with Hanson's interface style 
#define T UM_T
typedef struct T *T;

// initialize a UM with a program
extern T UM_init(Array_T prog);
// run an intialized Universal machine
extern void UM_run(T um);
// cleanup the UM's resources
extern void UM_free(T *ump);
#endif
