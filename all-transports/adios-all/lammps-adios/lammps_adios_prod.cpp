// lammps includes
#include <assert.h>
#include <math.h>
#include <mpi.h>
#include <string.h>
#include <utility>
#include <map>


#include "lammps.h"
#include "input.h"
#include "atom.h"
#include "library.h"
#define SIZE_ONE (5)

//#include "utility.h"

//#include "adios_adaptor.h"
//#include "adios_helper.h"
#include "adios.h"
#include "adios_error.h"
#include "adios_adaptor.h"
#include "ds_adaptor.h"

#include "transports.h"
#include "utility.h"
#include "msd-anal/run_msd.h"
static transport_method_t transport;

#ifdef V_T
#include <VT.h>
int class_id;
int advance_step_id, get_buffer_id, put_buffer_id;
//int analysis_id;
#endif




using namespace LAMMPS_NS;
using namespace std;

struct lammps_args_t                         // custom args for running lammps
{
    LAMMPS* lammps;
    string infile;
};

struct pos_args_t                            // custom args for atom positions
{
    int natoms;                              // number of atoms
    double* pos;                             // atom positions
};

/*
 * clog identifier
 */

/*
 * Native staging need to use these
 */
static char var_name[STRING_LENGTH];
    
int main(int argc, char * argv[]){

    /*
     * @input
     * @param NSTOP
     * @param FILESIZE2PRODUCE
     */
    if(argc !=3){
        printf("read argc = %d,lammps_adios_prod nstep inputfile\n",
                argc);
        exit(-1);
    }
    int nsteps; //run how many steps

    nsteps = atoi(argv[1]);
    string infile = argv[2];


	MPI_Init(&argc, &argv);

    MPI_Comm comm = MPI_COMM_WORLD;
    int         rank, nprocs;
    MPI_Comm_rank (comm, &rank);
    MPI_Comm_size (comm, &nprocs);

    char nodename[256];
    int nodename_length;
    MPI_Get_processor_name(nodename, &nodename_length);

    

    /*
     * get transport method from env variable
     */
    transport = get_current_transport();

    uint8_t transport_major = get_major(transport);
    uint8_t transport_minor = get_minor(transport);
    printf("%s:I am rank %d of %d, tranport code %x-%x\n",
            nodename, rank, nprocs,
            get_major(transport), get_minor(transport) );
    if(rank == 0){
      printf("stat: Producer start at %lf \n", MPI_Wtime());
    }


  if(transport_major == ADIOS_DISK || transport_major == ADIOS_STAGING){

      char xmlfile[256], trans_method[256];

      if(transport_major == ADIOS_DISK){
        strcpy(trans_method, "mpiio");
      }
      else{
          if(transport_minor == DSPACES)
               strcpy(trans_method, "dataspaces");
          else if(transport_minor == DIMES) 
              strcpy(trans_method, "dimes");

          else if(transport_minor == FLEXPATH)
               strcpy(trans_method, "flexpath");
      }

      //sprintf(xmlfile,"xmls/dbroker_%s.xml", trans_method);
      sprintf(xmlfile,"xmls/lammps_%s.xml", trans_method);
      if(rank == 0)
        printf("[r%d] try to init with %s\n", rank, xmlfile);

      if(adios_init (xmlfile, comm) != 0 ){
        fprintf( stderr, "[r%d] ERROR: adios init err with %s\n", rank, trans_method);
        fprintf(stderr, "[r%d] ERR: %s\n", rank, adios_get_last_errmsg());
        return -1;
      }
      else{
          //if(rank ==0)
           printf( "rank %d : adios init complete with %s\n", rank, trans_method);
      }
      MPI_Barrier(comm);
  } //use ADIOS_DISK or ADIOS_STAGING

  else  if(transport_major == NATIVE_STAGING){
        char msg[STRING_LENGTH];
        int ret = -1;
        printf("trying init dspaces for %d process\n", nprocs);
        ret = dspaces_init(nprocs, 1, &comm, NULL);

        printf("dspaces init successfuly \n");

        if(ret == 0){
            printf("dataspaces init successfully");
        }else{
            printf( "dataspaces init error");
            exit(-1);
        }

        sprintf(var_name, "atom");
   }


   /* 
   * lammps
   */
    int step;
    int line;
	int nlocal; //nlines processed by each process
	int size_one = SIZE_ONE; // each line stores 2 doubles
	double *buffer; // buffer address
    double **x;// all the atom values

#ifdef V_T
      
      //VT_initialize(NULL, NULL);
      printf("[decaf]: trace enabled and initialized\n");
      VT_classdef( "Computation", &class_id );
      VT_funcdef("ADVSTEP", class_id, &advance_step_id);
      VT_funcdef("GETBUF", class_id, &get_buffer_id);
      VT_funcdef("PUT", class_id, &put_buffer_id);
#endif




    LAMMPS* lps = new LAMMPS(0, NULL, comm);
    lps->input->file(infile.c_str());
    printf("prod lammps_decaf started with input %s\n", infile.c_str() );

    double t_start = MPI_Wtime();

    buffer = (double *)malloc(size_one * 521000 *sizeof(double));

    // output dir for adios
    char *filepath = getenv("BP_DIR");

    for (step = 0; step < nsteps; step++)
    {

#ifdef V_T
      VT_begin(advance_step_id);
#endif
       lps->input->one("run 1 pre no post no");
#ifdef V_T
      VT_end(advance_step_id);
#endif

#ifdef V_T
      VT_begin(get_buffer_id);
#endif
        x = (double **)(lammps_extract_atom(lps,(char *)"x"));

        nlocal = static_cast<int>(lps->atom->nlocal); // get the num of lines this rank have
        if(x == NULL){
            fprintf(stderr, "extract failed\n");
            break;
        }
        int natoms = static_cast<int>(lps->atom->natoms);
        int navg = natoms/nprocs; //avg atoms per proc
        
        // TODO: precise!
#ifdef PRECISE
        int line_buffer = nlocal; // how many lines for buffer
#else
        int line_buffer = navg;
        if(rank == 0)
            printf("[warning]: use estimate lines\n");
#endif

       // buffer = (double *)malloc(size_one * line_buffer*sizeof(double));

        if(rank == 0)
            printf("step %d i have %d lines\n",step, nlocal);
        for(line = 0; line < nlocal && line < line_buffer; line++){
            buffer[line*size_one] = line;
            buffer[line*size_one+1] = 1;
            buffer[line*size_one+2] = x[line][0];
            buffer[line*size_one+3] = x[line][1];
            buffer[line*size_one+4] = x[line][2];
        }

#ifdef V_T
      VT_end(get_buffer_id);
#endif

        /*
         * insert intto adios
         */



#ifdef V_T
      VT_begin(put_buffer_id);
#endif
	char        filename [256];
    int         offset, size_y;
    int         NX = size_one; // this is the longest dimension
    int         NY = 1;
    int         NZ = line_buffer;
    int64_t     adios_handle;

    offset = rank*NY;
    size_y = nprocs*NY;


  if(transport_major == ADIOS_DISK || transport_major == ADIOS_STAGING){
      if(transport_major == ADIOS_STAGING)
            sprintf(filename, "%s/atom.bp", filepath);
      else
	        sprintf(filename, "%s/atom_%d.bp", filepath, step);


        if(err_no_error != adios_open (&adios_handle, "temperature", filename, "w", comm)){
            PERR("cannot open");
            TRACE();
            MPI_Abort(comm, -1);

        }

        adios_write (adios_handle, "/scalar/dim/NX", &NX);
        adios_write (adios_handle, "/scalar/dim/NY", &NY);
        adios_write (adios_handle, "/scalar/dim/NZ", &NZ);
        //adios_write (adios_handle, "test_scalar", &test_scalar);
        adios_write (adios_handle, "size", &nprocs);
        adios_write (adios_handle, "rank", &rank);
        adios_write (adios_handle, "offset", &offset);
        adios_write (adios_handle, "size_y", &size_y);
        adios_write (adios_handle, "var_2d_array", buffer);
        
       if(err_no_error != adios_close (adios_handle)){
            PERR("cannot close");
            TRACE();
            MPI_Abort(comm, -1);
       }

      if(transport_major == ADIOS_DISK){
         /**** use index file to keep track of current step *****/
        char step_index_file[256];
        sprintf(step_index_file, "%s/stamp.file", filepath);

        if(S_OK != adios_adaptor_update_avail_version(comm, step_index_file, step, nsteps)){
            PERR("index file not found");
            TRACE();
            MPI_Abort(comm, -1);
        }
      }
  }
  else{
      PERR("transport %u:%u is not not supported", transport_major, transport_minor);
      TRACE();
      MPI_Abort(comm, -1);
  }



    /*// dimension sizexnlocalxsize_one*/
    //adios_open (&adios_handle, "atom", filename, "w", comm);

    //adios_write (adios_handle, "size", &nprocs);
    //adios_write (adios_handle, "rank", &rank);
    //adios_write (adios_handle, "nlocal", &const_nlocal);
    //adios_write (adios_handle, "size_one", &size_one);
    //adios_write (adios_handle, "array", buffer);

    //// end of gwrite_atom

    //adios_close (adios_handle);


       //insert_into_Adios(transport, var_name, step,nsteps, line_buffer, size_one, buffer,"w" , &comm);

#ifdef V_T
      VT_end(put_buffer_id);
#endif
  
    }
  free(buffer);

  double t_end = MPI_Wtime();
  printf("[lammps]:total-start-end %.3f %.3f %.3f\n", t_end- t_start, t_start, t_end);




  /*
   * finalize
   */
    if(transport_major == ADIOS_DISK || transport_major == ADIOS_STAGING){
      adios_finalize (rank);
      fprintf(stderr, "rank %d: adios finalize complete\n", rank); 
    }

    else if(transport_major == NATIVE_STAGING){
        dspaces_finalize();
    }

  MPI_Finalize();
  printf("rank %d: exit\n", rank);
  return 0;
}

