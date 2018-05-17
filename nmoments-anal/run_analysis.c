#include "run_analysis.h"

#define EACH_FLUID_NUM_DOUBLE (2)

void run_analysis(double * buf_blk, int block_size, int lp, double *sum_vx, double *sum_vy){
  char * buffer = (char *)buf_blk;

  //int check = *(int *)(buffer);
  double vx, vy;
  double vx_prime, vy_prime;
  double mean_vx=0, mean_vy=0;

  int i, j;
  int num_points = block_size;
  int num_double = EACH_FLUID_NUM_DOUBLE*num_points;


  //initialize
  for(i=1;i<=lp;i++){
    sum_vx[i-1]=0;
    sum_vy[i-1]=0;
    // sum_vz[i-1]=0;
  }

  //calc_mean
  for(i=0; i<num_double; i+=EACH_FLUID_NUM_DOUBLE){
    vx = ((double *)buffer)[i];
    vy = ((double *)buffer)[i+1];
    // vz = ((double *)buffer)[i+2];
    //rho = ((double *)buffer)[i+3];

    mean_vx += vx;
    mean_vy += vy;
    // mean_vz += vz;

  }
  mean_vx=mean_vx/num_points;
  mean_vy=mean_vy/num_points;
  // mean_vz=mean_vz/num_points;

  //calc_n_momnents

  for(i=0; i<num_double; i+=EACH_FLUID_NUM_DOUBLE){

    vx = ((double *)buffer)[i];
    vy = ((double *)buffer)[i+1];
    // vz = ((double *)buffer)[i+2];
    // rho = ((double *)buffer)[i+3];

    //compute Flutuation field (velocity - velocity_mean)
    vx_prime = vx - mean_vx;
    vy_prime = vy - mean_vy;
    // uz = rho * (vz - mean_vz);

    //power ^2 -- variance; power ^3 -- skewness; power ^4 -- flatness
    for(j=1;j<=lp;j++){
        sum_vx[j-1] += pow(vx_prime, j);
        sum_vy[j-1] += pow(vy_prime, j);
        // sum_vz[j-1] += pow(vz_prime, j);
    }
  }

  for(i=1;i<=lp;i++){
    sum_vx[i-1]=sum_vx[i-1]/num_points;
    sum_vy[i-1]=sum_vy[i-1]/num_points;
    // sum_uz[i-1]=sum_vz[i-1]/num_points;
  }
}

