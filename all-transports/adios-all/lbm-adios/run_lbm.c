#include "run_lbm.h"        

//#include "adios_write_global.h"
#include "adios_adaptor.h"
#include "adios_error.h"
#include "ds_adaptor.h"

#include "transports.h"

#include "lbm.h"
#include "lbm_buffer.h"
//#include "run_analysis.h"
#include "utility.h"

#ifndef SIZE_ONE
#define SIZE_ONE (2)
#endif

#ifdef V_T
#include <VT.h>
int class_id, class_id2;
int advance_step_id, get_buffer_id, put_buffer_id;
int analysis_id;
#endif

static transport_method_t transport;

#define debug

/*
 * Native staging need to use these
 */
static char var_name[STRING_LENGTH];
static size_t elem_size=sizeof(double);
static char * module_name="lbm_driver";
 

/*
 * run lbm for nsteps
 */

status_t run_lbm_adios(char *filepath, int nsteps, MPI_Comm comm){
    //int nsteps;
    int rank; //TODO
    int timestep;

	/*those are all the information io libaray need to know about*/

	int nlocal; //nlines processed by each process
	int size_one = SIZE_ONE; // each line stores 2 doubles
	double *buffer; // buffer address
    double t_start, t_end;

    int dims_cube[3] = {filesize2produce/4,filesize2produce/4,filesize2produce};
#ifdef V_T
      
      //VT_initialize(NULL, NULL);
      PINF("[%s]: trace enabled and initialized\n", module_name);
      VT_classdef( "Computation", &class_id );
      VT_funcdef("ADVSTEP", class_id, &advance_step_id);
      VT_funcdef("GETBUF", class_id, &get_buffer_id);
      VT_funcdef("PUT", class_id, &put_buffer_id);
#endif


    t_start = MPI_Wtime();

    /* prepare */
	nlocal = dims_cube[0]*dims_cube[1]*dims_cube[2];
	lbm_alloc_buffer(&comm, nlocal, size_one, &buffer);

    if( S_FAIL == lbm_init(&comm, nsteps)){
		printf("[lbm]: init not success, now exit\n");
		goto cleanup;
	}

    MPI_Comm_rank(comm,&rank);
    
    PINF("producer start, I am rank %d\n", rank);


    uint8_t transport_major = get_major(transport);
    uint8_t transport_minor = get_minor(transport);

    //MPI_Barrier(comm);

    for (timestep = 0; timestep < nsteps; timestep++)
    {

#ifdef V_T
      VT_begin(advance_step_id);
#endif
        if(S_OK != lbm_advance_step(&comm)){
			fprintf(stderr, "[lbm]: err when process step %d\n", timestep);
		}
#ifdef V_T
      VT_end(advance_step_id);
#endif
	
		// get the buffer
#ifdef V_T
      VT_begin(get_buffer_id);
#endif
		if(S_OK != lbm_get_buffer(buffer)){
			fprintf(stderr, "[lbm]: err when updated buffer at step %d\n", timestep);
		}

#ifdef V_T
      VT_end(get_buffer_id);
#endif


#ifdef V_T
      VT_begin(put_buffer_id);
#endif

      /*
       * adios inserting
       */

    if(transport_major == ADIOS_STAGING){
        // for staging, each time write to same file
        //insert_into_adios(filepath, "atom",-1, n, SIZE_ONE , buffer,"w", &comm);
        
        if(timestep ==0){
            insert_into_adios(filepath, "atom",-1, nlocal, size_one , buffer,"w", &comm);
        }
        else{

            insert_into_adios(filepath, "atom",-1, nlocal, SIZE_ONE , buffer,"a", &comm);
        }
        
    }
    else if(transport_major == ADIOS_DISK){
        // for mpiio, each time write different files
        insert_into_adios(filepath, "atom", timestep, nlocal, size_one , buffer,"w", &comm);
        /**** use index file to keep track of current step *****/
        char step_index_file[256];
        sprintf(step_index_file, "%s/stamp.file", filepath);

        if(S_OK != adios_adaptor_update_avail_version(comm, step_index_file, timestep, nsteps)){
            PERR("index file not found");
            TRACE();
            MPI_Abort(comm, -1);
        }
    }

    else if(transport_major == NATIVE_STAGING){
        uint64_t bounds[6] = {0};
        double time_comm;

        // xmin
        bounds[1]=EVAL(nlocal)*EVAL(rank);
        // ymin
        bounds[0]=0;

        // xmax
        bounds[4]=EVAL(nlocal)*(EVAL(rank)+1)-1 ;
        // ymax
        bounds[3]= EVAL(size_one)-1;

        put_common_buffer(transport_minor, timestep,2, bounds,rank , var_name, (void **)&buffer, elem_size, &time_comm);
        //t_put+=time_comm;
    }

        

#ifdef V_T
      VT_end(put_buffer_id);
#endif
    }

    if(S_OK != lbm_finalize(&comm)){
		fprintf(stderr, "[lbm]: err when finalized\n");
	}
	if(S_OK != lbm_free_buffer(&comm, buffer)){
		fprintf(stderr, "[lbm]: err when free and summarize\n");
	}

    //MPI_Barrier(comm);
    t_end = MPI_Wtime();
    printf("total-start-end %.3f %.3f %.3f\n", t_end- t_start, t_start, t_end);

    // terminate the task (mandatory) by sending a quit message to the rest of the workflow
cleanup:
    if(rank == 0){
        fprintf(stderr, "producer exit\n");
    }

#ifdef V_T
    //VT_finalize();
    PINF("[%s]: trace finalized", module_name);
#endif

    return S_OK;
}

int main(int argc, char * argv[]){

    /*
     * @input
     * @param NSTOP
     */
    if(argc !=2){
        printf("run_lbm nstop\n");
        exit(-1);
    }

    PDBG("producer started!");

    int nstop; //run how many steps

    nstop = atoi(argv[1]);


	MPI_Init(&argc, &argv);

    MPI_Comm comm = MPI_COMM_WORLD;
    int         rank, nprocs;
    MPI_Comm_rank (comm, &rank);
    MPI_Comm_size (comm, &nprocs);

    char nodename[256];
    int nodename_length;
    MPI_Get_processor_name(nodename, &nodename_length );


    char *filepath = getenv("BP_DIR");
    if(filepath == NULL){
        fprintf(stderr, "scratch dir is not set!\n");
    }

    /*
     * get transport method from env variable
     */
    transport = get_current_transport();
    uint8_t transport_major = get_major(transport);
    uint8_t transport_minor = get_minor(transport);
    PINF("%s:I am rank %d of %d, tranport code %x-%x\n",
            nodename, rank, nprocs,
            get_major(transport), get_minor(transport) );
    if(rank == 0){
      PINF("stat: Producer start at %lf \n", MPI_Wtime());
    }


  if(transport_major == ADIOS_DISK || transport_major == ADIOS_STAGING){

      char xmlfile[256], trans_method[256];

      if(transport_major == ADIOS_DISK){
        strcpy(trans_method, "mpiio");
      }
      else{
          if(transport_minor == DSPACES)
               strcpy(trans_method, "dataspaces");
          else if(transport_minor == DIMES) strcpy(trans_method, "dimes");

          else if(transport_minor == FLEXPATH)
               strcpy(trans_method, "flexpath");
      }

      sprintf(xmlfile,"adios_xmls/dbroker_%s.xml", trans_method);
      PINF("[r%d] try to init with %s\n", rank, xmlfile);

      if(S_OK != adios_adaptor_init_client(xmlfile, comm)){
          TRACE();
          MPI_Abort(comm, -1);
      }
      
      MPI_Barrier(comm);
  } //use ADIOS_DISK or ADIOS_STAGING

  else  if(transport_major == NATIVE_STAGING){
      if(S_OK != ds_adaptor_init_client(nprocs, 1, &comm, NULL)){
            TRACE();
            MPI_Abort(comm, -1);
        }

        sprintf(var_name, "atom");

   }



  if(rank == 0 ){
      PINF("output will be saved in %s\n", filepath);
  }

  MPI_Barrier(comm);

  run_lbm_adios(filepath, nstop, comm);


    if(transport_major == ADIOS_DISK || transport_major == ADIOS_STAGING){
      adios_finalize (rank);
      PINF("rank %d: adios finalize complete\n", rank); 
    }

    else if(transport_major == NATIVE_STAGING){
        /* dimes needs to flush last step */
        if(transport_minor == DIMES){
            ds_adaptor_flush_dimes(var_name, comm, nstop);
        }

        double t_end = MPI_Wtime();
          if(rank == 0){
              PINF("stat:Simulation stop at %lf \n", t_end);
          }


        dspaces_finalize();
  }

  MPI_Finalize();
  PINF("rank %d: exit\n", rank);
  return 0;
}

