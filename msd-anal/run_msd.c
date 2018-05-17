#include <stdio.h>
#include <stdlib.h>
#include "run_msd.h"
/*
 * this use 2d array from yuankun's code, I prefer 1D
 * @param steps dump steps
 * @param size_one 5
 *
 * @return the msd matrix for this block
 */
double ** init_msd(int nsteps, int size_one){

  int i, j;
  double **msd; // a flat array of nlinesx5
    
  msd = (double**)malloc(sizeof(double*)*size_one);

  for(i=0; i<5; i++){
    msd[i] = (double*)malloc(sizeof(double)*(nsteps));
    for(j=0; j < nsteps; j++)
      msd[i][j]=0.0;
  }
  return msd;
}

/*
 * @brief free the  msd
 *
 * @param msd
 * @param size_one
 *
 * @return 1 on success
 */
int free_msd(double **msd,int size_one){

    int i, j;
    for(i=0; i<size_one; i++){
        if(msd[i]){
            free(msd[i]);
        }
    }
    if(msd){
        free(msd);
    }
    printf("msd freed");
    return 1;
}



/*
 * run msd analysis
 *
 * @param msd 
 * @param buf data buffer 
 * @param nlines how much data lines this rank will wirte
 * @param size_one 5 numbers in this case
 * @param step current step
 */

void calc_msd(double **msd, double * buf, int nlines, int size_one, int step){
    int i;
    double atom_id, type;
    double dx, dy, dz;

    for (i = 0; i < nlines; i++){
        /*for(j = 0; j<SIZE_ONE; j++){*/
            ////t[i*SIZE_ONE + j] = 100*timestep + rank*NX + i + 0.1*j;
            //t[i*SIZE_ONE + j] = buf[i*SIZE_ONE +j];
        /*}*/
        atom_id = buf[i*size_one];
        type = buf[i*size_one+1];
        dx = buf[i*size_one+2];
        dy = buf[i*size_one+3];
        dz = buf[i*size_one+4];

        msd[0][step] += dx*dx;
        msd[1][step] += dy*dy;
        msd[2][step] += dz*dz;
        msd[3][step] += dx*dx + dy*dy + dz*dz;
    }
    
}

/*
 * msd reduce
 *
 * @param msd
 * @param nsteps total dump steps
 * @param mycomm
 */
void perform_msd_reduce(double **msd, int nsteps, MPI_Comm mycomm){
  MPI_Status status;
  // ana_rk_end   = gv->compute_process_num + gv->analysis_process_num - 1;

  // printf("Ana%d Consumer: Lammps+DataBroker enter perform_msd_reduce\n", gv->rank[0]);
  // fflush(stdout);

   MPI_Reduce(msd[3], msd[4], nsteps, MPI_DOUBLE, MPI_SUM, 0, mycomm);

}
