#ifndef __LOAD_PROG__
#define __LOAD_PROG__

// Module that loads an UM program from a file
// Exports 1 function
#include <stdio.h>
#include "array.h"

// given a file pointer return an Array_T of instruction words
extern Array_T load_prog(FILE *fp);

#endif
