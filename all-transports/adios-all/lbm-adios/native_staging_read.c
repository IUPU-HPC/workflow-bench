/* 
 * ADIOS is freely available under the terms of the BSD license described
 * in the COPYING file in the top level directory of this source distribution.
 *
 * Copyright (c) 2008 - 2009.  UT-BATTELLE, LLC. All rights reserved.
 */

/* ADIOS C Example: read global arrays from a BP file
 *
 * This code is using the generic read API, which can read in
 * arbitrary slices of an array and thus we can read in an array
 * on arbitrary number of processes (provided our code is smart 
 * enough to do the domain decomposition).
 *
 * Run this example after adios_global, which generates 
 * adios_global.bp. Run this example on equal or less 
 * number of processes since we decompose only on one 
 * dimension of the global array here. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#include "adios_read.h"
#include "adios_error.h"
//#include "adios_read_global.h"
#include "ds_adaptor.h"
#include "assert.h"
#include "utility.h"
#include "transports.h"
#include "nmoments-anal/run_analysis.h"
static transport_method_t transport;

#ifdef V_T
#include <VT.h>
int class_id;
int analysis_id;
#endif

//#ifdef RAW_DSPACES
static char var_name[STRING_LENGTH];
static size_t elem_size=sizeof(double);
//#endif
//
static char * module_name="native_staging_reader";
        

#define DEBUG_Feng

int main (int argc, char ** argv) 
{
    /*
     * @input
     *
     * @param NSTOP
     * @FILESIZE2PRODCE
     * @PROCS_PRODUCER
     */
    if(argc !=4){
        printf("need to specify timstop total_file_size scratch procs_prod\n");
        exit(-1);
    }

    PDBG("consumer started!");
    int nstop;
    int filesize2produce;
    int nprocs_producer;

    nstop= atoi(argv[1]);
    filesize2produce = atoi(argv[2]);
    nprocs_producer= atoi(argv[3]);
    

    int lp = N_LP;

    double sum_vx[NMOMENT], sum_vy[NMOMENT];

    /******************** configuration stop ***********/
#ifdef ENABLE_TIMING
    double t1, t2, t3;
    double t_read_1, t_read_2, t_analy;
    t_read_1 = 0;
    t_read_2 = 0;
    t_analy = 0;
#endif


    int         rank, nprocs;
    MPI_Comm    comm = MPI_COMM_WORLD;
    void * data = NULL;
    uint64_t start[2], count[2];

    MPI_Init (&argc, &argv);
    MPI_Comm_rank (comm, &rank);
    MPI_Comm_size (comm, &nprocs);

    char nodename[256];
    int nodename_length;
    MPI_Get_processor_name(nodename, &nodename_length );

    /*
     * define the trace
     */

#ifdef V_T
     VT_classdef( "Analysis", &class_id );
     VT_funcdef("ANL", class_id, &analysis_id);
#endif
 
    
    int r;

    char *filepath = getenv("SCRATCH_DIR");
    if(filepath == NULL){
        fprintf(stderr, "scratch dir is not set!\n");
    }

    /*
     * get transport method
     */
    transport = get_current_transport();
    uint8_t transport_major = get_major(transport);
    uint8_t transport_minor = get_minor(transport);
    PINF("%s:I am rank %d of %d, tranport code %x-%x\n",
            nodename, rank, nprocs,
            get_major(transport), get_minor(transport) );
    
    if(rank == 0){
      PINF("stat: Consumer start at %lf \n", MPI_Wtime());
    }
    
    
    assert(transport_major ==  NATIVE_STAGING);


    int timestep;
    
    /**** use index file to keep track of current step *****/
    MPI_Barrier(comm);

//#ifdef RAW_DSPACES
    if(S_OK != ds_adaptor_init_client(nprocs, 2, &comm, NULL)){
        TRACE();
        MPI_Abort(comm, -1);
    }

    /*
    * set bounds and dspaces variables
    */
    sprintf(var_name, "atom");

    int dims_cube[3] = {filesize2produce/4,filesize2produce/4,filesize2produce};
    // each producer process 
    int n = dims_cube[0]*dims_cube[1]*dims_cube[2];
    // how many lines in global
    int global_size= n*nprocs_producer;
    //uint64_t gdims[2] = {2, global_size};
    //dspaces_define_gdim(var_name, 2,gdims);
    uint64_t slice_size;
               
    slice_size = (global_size)/nprocs;

    data = malloc (slice_size * SIZE_ONE* sizeof (double));
    if (data == NULL)
    {
        size_t allc_size=slice_size * SIZE_ONE* sizeof (double) ;
        PERR("malloc failed with %ld bytes", allc_size);
        TRACE();
        MPI_Abort(comm, -1);
    }

    start[0] = slice_size * rank;
    if (rank == nprocs-1) /* last rank may read more lines */
        slice_size = slice_size + global_size%nprocs;
    count[0] = slice_size;

    start[1] = 0;
    count[1] = 2;
    PINF("start: (%ld, %ld), count:( %ld, %ld)\n", start[0], start[1], count[0], count[1]);

    uint64_t bounds[6] = {0};
    double time_comm = 0;;
    bounds[0]=start[1]; //ymin
    bounds[1]=start[0]; //xmin
    bounds[3]=start[1]+count[1]-1; //ymax
    bounds[4]=start[0]+count[0]-1; //xmax
//#endif
//#endif

    for(timestep=0; timestep < nstop; timestep++){

//#ifdef RAW_DSPACES
        t1 =MPI_Wtime(); 
        if(S_OK != get_common_buffer(transport_minor, timestep,2, bounds,rank, var_name, (void **)&data, elem_size, &time_comm)){
          TRACE();
          MPI_Abort(comm, -1);
        }
        t2 =MPI_Wtime(); 
        // all time spent by get_common_buffer
        t_read_1 += t2-t1;
        // actual communication time
        t_read_2 += time_comm;
//#endif
        if(rank ==0)
            PINF("Step %d read\n", timestep);
        // analysis
#ifdef V_T
      VT_begin(analysis_id);
#endif
        run_analysis(data, slice_size, lp, sum_vx,sum_vy);
      PINF("[%s]: %lu points analyzed in step %d\n", module_name,slice_size,timestep);
#ifdef V_T
      VT_end(analysis_id);
#endif


        t3 =MPI_Wtime(); 
        t_analy += t3-t2;

        //if(rank ==0)
            PINF("Step %d moments calculated, t_read %lf, t_advance %lf, t_analy %lf\n", timestep, t2-t1, time_comm, t3-t2);

    }

    printf("[rank %d]:analysis_time %.3lf \n", rank, t_analy);

    free (data); MPI_Barrier(comm);
    double t_end = MPI_Wtime();

        double global_t_cal=0;
        double global_t_read=0;
        double global_t_get=0;
        MPI_Reduce(&t_analy, &global_t_cal, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
        MPI_Reduce(&t_read_1, &global_t_read, 1, MPI_DOUBLE, MPI_SUM, 0, comm);
        MPI_Reduce(&t_read_2, &global_t_get, 1, MPI_DOUBLE, MPI_SUM, 0, comm);
    if(rank == 0){
      PINF("stat:Consumer end  at %lf \n", t_end);
      PINF("stat:time for read %f s; time for ds_get %f s; max time for analyst %f s\n", global_t_read/nprocs, global_t_get/nprocs, global_t_cal);
    }


//#ifdef RAW_DSPACES
    dspaces_finalize();
//#endif

    PINF("rank %d: exit\n", rank);

    MPI_Finalize ();
    return 0;
}
