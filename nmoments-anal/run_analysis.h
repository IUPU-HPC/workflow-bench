#ifndef RUN_ANALYSIS_H
#define RUN_ANALYSIS_H
#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include "time.h"
#include <math.h>
#include <unistd.h>
#define USE_ADIOS


#define N_LP (4) //nmoment
#define SIZE_ONE (2)

// maximum moments?
#define NMOMENT 8



/*
 * calculate moment of given block
 * 
 * @param nlocal number of positions(each position will have two double values)
 * @param lp number of moments
 * @param sum_vx output
 * @param sum_vy output
 *
 */
void run_analysis(double* buf_blk, int nlocal ,int lp,double *sum_vx, double *sum_vy);


#ifdef __cplusplus
}
#endif
#endif
