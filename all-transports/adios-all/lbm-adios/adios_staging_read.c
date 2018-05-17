/* 
 * ADIOS is freely available under the terms of the BSD license described
 * in the COPYING file in the top level directory of this source distribution.  *
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

#define CLOG_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#include "adios_read.h"
#include "adios_error.h"
#include "adios_adaptor.h"
#include <assert.h>
#include "transports.h"

#include "utility.h"
#include "nmoments-anal/run_analysis.h"
static transport_method_t transport;

#ifdef V_T
#include <VT.h>
int class_id;
int analysis_id;
#endif



//#define DEBUG_Feng


int main (int argc, char ** argv) 
{
     /*
     * @input
     * @param NSTOP
     * @param FILESIZE2PRODUCE
     */
    if(argc !=1){
        printf("more argumetns than expected\n");
        exit(-1);
    }

    int lp = N_LP;

    double sum_vx[NMOMENT], sum_vy[NMOMENT];

    /******************** configuration stop ***********/

#ifdef ENABLE_TIMING
    double t1, t2, t3, t4;
    double t_read_1, t_read_2, t_analy;
    t_read_1 = 0;
    t_read_2 = 0;
    t_analy = 0;
#endif


    int         rank, nprocs;
    MPI_Comm    comm = MPI_COMM_WORLD;

    int has_keep=0;

    //enum ADIOS_READ_METHOD method = ADIOS_READ_METHOD_DIMES;
    //enum ADIOS_READ_METHOD method = ADIOS_READ_METHOD_BP;
    ADIOS_SELECTION * sel;
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

    char *filepath = getenv("BP_DIR");
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
    assert(transport_major == ADIOS_STAGING);

    enum ADIOS_READ_METHOD method;
    if(transport_minor == DSPACES)
        method = ADIOS_READ_METHOD_DATASPACES;

    else if(transport_minor == DIMES)
        method = ADIOS_READ_METHOD_DIMES;

    else if(transport_minor == FLEXPATH)
        method = ADIOS_READ_METHOD_FLEXPATH;
    else{
        method = ADIOS_READ_METHOD_BP;
    }


    if(adios_read_init_method (method, comm, "verbose=3") !=0){
        PINF("ERROR: rank %d: adios init err with %d\n", rank, method);
        exit(-1);
    }
    else{
        PINF("adios read method init complete with %d\n", method);
    }

    char * env_string; //input from user
    if((env_string = getenv("HAS_KEEP")) != NULL){
        if(strcmp(env_string, "1") == 0){
            PINF("adios read method init complete with %d\n", method);
            has_keep=1;
        }
    }
    if(has_keep ==1){
        if(transport_minor == DSPACES){
            adios_init ("adios_xmls/dbroker_dataspaces.xml", comm);
        }

        else if(transport_minor == DIMES){
            adios_init ("adios_xmls/dbroker_dimes.xml", comm);
        }

        else if(transport_minor == FLEXPATH){
            adios_init ("adios_xmls/dbroker_flexpath.xml", comm);
        }
        else{
            printf("rank %d: adios init complete restart file\n", rank);
            MPI_Abort(comm, -2);
        }
        PINF("rank %d: adios init complete restart file\n", rank);
    }



/*
#ifdef HAS_KEEP
#if defined(USE_DATASPACES)
  adios_init ("adios_xmls/dbroker_dataspaces.xml", comm);
  if(rank ==0)
    PINF("rank %d: adios init complete with dataspaces\n", rank);
#elif defined(USE_DIMES)
  adios_init ("adios_xmls/dbroker_dimes.xml", comm);
    PINF("rank %d: adios init complete with dimes\n", rank);
#elif defined(USE_FLEXPATH)
  adios_init ("adios_xmls/dbroker_flexpath.xml", comm);
    PINF("rank %d: adios init complete with flexpath\n", rank);

#else 
#error("define stating transport method");
#endif
#endif
*/

    int timestep = 0;

    char filename[256];

    // append file name
    sprintf(filename,"%s/%s.bp", filepath, "atom");
    ADIOS_FILE * f = adios_read_open (filename, method, comm, ADIOS_LOCKMODE_CURRENT, -1);
    //ADIOS_FILE * f = adios_read_open (filename, method, comm, ADIOS_LOCKMODE_NONE, 0);

     if (f == NULL)
    {
        printf ("rank %d, %s\n",rank, adios_errmsg());
        return -1;
    }

    ADIOS_VARINFO * v = adios_inq_var (f, "atom");
    
    if(rank ==0)
        PINF("reader opened the stream, dims = %ld, %ld\n", v->dims[0], v->dims[1]);


    /* Using less readers to read the global array back, i.e., non-uniform */
    uint64_t slice_size = v->dims[0]/nprocs;
    start[0] = slice_size * rank;
    if (rank == nprocs-1) /* last rank may read more lines */
        slice_size = slice_size + v->dims[0]%nprocs;
    count[0] = slice_size;

    start[1] = 0;
    count[1] = v->dims[1];
    PINF("rank %d: start: (%ld, %ld), count:( %ld, %ld)\n", rank, start[0], start[1], count[0], count[1]);
       

    data = malloc (slice_size * v->dims[1]* sizeof (double));
    if (data == NULL)
    {

        size_t allc_size=slice_size * v->dims[1]* sizeof (double);
        PERR("malloc failed with %ld bytes", allc_size);
        MPI_Abort(comm, -1);
    }

    sel = adios_selection_boundingbox (v->ndim, start, count);

    //PINF("rank %d: adios init complete\n", rank);

    // get read status, before perform mpiio!, so streaming steps are not affected
    int errno_streaming_read = adios_errno;
    //for(timestep = 0; timestep < 10;){
    while(errno_streaming_read != err_end_of_stream){
        PINF("rank %d: Step %d start\n", rank, timestep);
           /* Read a subset of the temperature array */
        // 0:not used for strea; 1: must be set in stream
        adios_schedule_read (f, sel, "atom", 0, 1, data);
        t1 = MPI_Wtime();

        // block until read complete
        adios_perform_reads (f, 1);

        PDBG("    [DEBUG]:read is performed");
        t2 = MPI_Wtime();
        t_read_1 += t2-t1;

        adios_release_step(f);

        t3 = MPI_Wtime();

        t_read_2 += t3-t2;

        /*
        for (i = 0; i < slice_size; i++) {
            if(* ((double *)data + i * v->dims[1])  -0 < 0.001){
                printf("ERROR: rank %d get zero lines in slice %d \n", rank, i);
                exit(-1);
            }
        }
        */

#ifdef DEBUG_Feng
        for (i = 0; i < slice_size; i++) {
            printf ("rank %d: [%" PRIu64 ",%d:%" PRIu64 "]", rank, start[0]+i, 0, slice_size);
            for (j = 0; j < v->dims[1]; j++){
                printf (" %6.6g", * ((double *)data + i * v->dims[1]  + j ));
            }
            printf("|");
            printf ("\n");
        }
#endif
        //printf("rank %d: Step %d read\n", rank, timestep);


        if(has_keep == 1){
            if(timestep == 0)
                insert_into_adios(filepath, "restart",-1, slice_size, v->dims[1], data,"w", &comm);
            else
                insert_into_adios(filepath, "restart", -1, slice_size, v->dims[1], data,"a", &comm);

            if(rank ==0)
                PINF("Step %d data kept\n", timestep);
        }

        // analysis
#ifdef V_T
      VT_begin(analysis_id);
#endif
        run_analysis(data, slice_size, lp, sum_vx,sum_vy);
#ifdef V_T
      VT_end(analysis_id);
#endif
        t4 = MPI_Wtime();
        t_analy += t4-t3;

        PDBG("previous step released");
        // advance to (1)the next availibale step (2)blocked if not unavailble
        adios_advance_step(f, 0, -1);
        errno_streaming_read = adios_errno;

        PDBG("successfully step into next available step");


        if(rank == 0)
            PINF("rank %d: Step %d moments calculated, t_read %lf, t_advance %lf, t_analy %lf\n", rank, timestep, t2-t1, t3-t2, t4-t3);
        timestep ++;
    }

#ifdef ENABLE_TIMING
    printf("[rank %d]:analysis_time %.3lf \n", rank, t_analy);
  MPI_Barrier(comm);
  double t_end = MPI_Wtime();


  double global_t_analy=0;

  MPI_Reduce(&t_analy, &global_t_analy, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
  if(rank == 0){
      PINF("stat:Consumer end  at %lf \n", t_end);
      PINF("stat:max time for analyst %f s\n",global_t_analy);
  }
#endif 
    free (data);
    adios_selection_delete (sel);
    adios_free_varinfo (v);
    adios_read_close (f);

    MPI_Barrier (comm);
    adios_read_finalize_method (method);
    PINF("adios read finalized");

    /*
     * finalize restart writing
     */
    /*if(has_keep == 1){*/
      /*adios_finalize (rank);*/
      /*if(rank == 0)*/
      /*PINF("adiod finalized");*/
    /*}*/

    /*
    * close logger
    */

    MPI_Finalize ();
    printf("rank %d: exit\n", rank);

    return 0;
}
