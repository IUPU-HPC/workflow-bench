#ifndef RUN_ANALYSIS_H
#define RUN_ANALYSIS_H
#ifdef __cplusplus
extern "C"{
#endif


#include "mpi.h"

double ** init_msd(int nsteps, int size_one);

int free_msd(double **msd,int size_one);

void calc_msd(double **msd, double * buffer, int nlines, int size_one, int step);
void perform_msd_reduce(double **msd, int nsteps, MPI_Comm mycomm);
#ifdef __cplusplus
}
#endif
#endif
