#ifndef __UM_LOADER__
#define __UM_LOADER__

// Module that loads an UM program from a file
// Exports 1 function
#include <stdio.h>
#include "array.h"

// given a file pointer return an Array_T of instruction words,
// user will have to free Array_T
extern Array_T loader(FILE *fp);
#endif
