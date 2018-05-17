#ifndef RUN_LBM_H
#define RUN_LBM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>
#include <mpi.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>



// this must be included
/*
 * this is moved to main function arguments
#define TOTAL_FILE2PRODUCE_1GB 256 
#define nx TOTAL_FILE2PRODUCE_1GB/4
#define ny TOTAL_FILE2PRODUCE_1GB/4
#define nz TOTAL_FILE2PRODUCE_1GB
*/

/*
 * insert buffer into adios
 * input
 *      n: lines of data, each line contains two double
 *      buf: address of buffer
 *      pcomm: group communicator
 */
void insert_into_Adios(char *filepath, int n, double * buf, MPI_Comm *pcomm);

// run lbm 
// input:
//      step_stop 
//      dims_cube(number of element in each dimension of a cube)
// data layout
//      there will be  X*Y*Z cubes each has cubex*cubey*cube z elememts,
//      each cell will have two double values
//      data is send once for each cube
void run_lbm(char *filepath, int step_stop, int dims_cube[3], MPI_Comm * pcomm);

#endif
