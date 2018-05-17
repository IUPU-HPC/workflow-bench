// modified by Feng Li


//---------------------------------------------------------------------------
//
// lammps example
//
// 4-node workflow
//
//          print (1 proc)
//        /
//    lammps (4 procs)
//        \
//          print2 (1 proc) - print (1 proc)
//
//  entire workflow takes 10 procs (1 dataflow proc between each producer consumer pair)
//
// Tom Peterka
// Argonne National Laboratory
// 9700 S. Cass Ave.
// Argonne, IL 60439
// tpeterka@mcs.anl.gov
//
//--------------------------------------------------------------------------
#include <decaf/decaf.hpp>
#include <bredala/data_model/pconstructtype.h>
#include <bredala/data_model/vectorfield.hpp>
#include <bredala/data_model/boost_macros.h>

#include <assert.h>
#include <math.h>
#include <mpi.h>
#include <string.h>
#include <utility>
#include <map>

#include "lbm.h"
#include "lbm_buffer.h"
#include "nmoments-anal/run_analysis.h"

/*#ifndef NLINES*/
//#define NLINES (256*256*16) // each proc write 10 lines
/*#endif*/

#ifndef SIZE_ONE
#define SIZE_ONE (2)
#endif

#ifdef V_T
#include <VT.h>
int class_id, class_id2;
int advance_step_id, get_buffer_id, put_buffer_id;
int analysis_id;
#endif



/*// lammps includes*/
//#include "lammps.h"
//#include "input.h"
//#include "atom.h"
/*#include "library.h"*/

using namespace decaf;
//using namespace LAMMPS_NS;
using namespace std;

// rank 0 will generate all the data
// runs lammps and puts the atom positions to the dataflow at the consumer intervals
//void prod(Decaf* decaf, int nsteps, int analysis_interval, string infile)
void prod(Decaf* decaf, int nsteps)
{
    //int nsteps;
    int rank;


	/*those are all the information io libaray need to know about*/
    MPI_Comm comm;
	int nlocal; //nlines processed by each process
	int size_one = SIZE_ONE; // each line stores 2 doubles
	double *buffer; // buffer address
    double t_start, t_end;

    int dims_cube[3] = {filesize2produce/4,filesize2produce/4,filesize2produce};
#ifdef V_T
      
      //VT_initialize(NULL, NULL);
      printf("[decaf]: trace enabled and initialized\n");
      VT_classdef( "Computation", &class_id );
      VT_funcdef("ADVSTEP", class_id, &advance_step_id);
      VT_funcdef("GETBUF", class_id, &get_buffer_id);
      VT_funcdef("PUT", class_id, &put_buffer_id);
#endif


    t_start = MPI_Wtime();

    /* prepare */
    comm = decaf->prod_comm_handle();
	nlocal = dims_cube[0]*dims_cube[1]*dims_cube[2];
	lbm_alloc_buffer(&comm, nlocal, size_one, &buffer);

    if( S_FAIL == lbm_init(&comm, nsteps)){
		printf("[lbm]: init not success, now exit\n");
		goto cleanup;
	}

    rank = decaf->prod_comm()->rank();
    cout << "producer start, I am rank " << rank <<endl;


    //MPI_Barrier(comm);

    for (int timestep = 0; timestep < nsteps; timestep++)
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
        
        /* decaf put */
        if (1)
        {
            pConstructData container;

            // lammps gathered all positions to rank 0
            //if (decaf->prod_comm()->rank() == 0)
            if (rank == 0)
            {
                fprintf(stderr, "lbm producing time step %d with %d lines\n",
                        timestep, nlocal);

            }
                // debug
                //         for (int i = 0; i < 10; i++)         // print first few atoms
                //           fprintf(stderr, "%.3lf %.3lf %.3lf\n",
                // x[3 * i], x[3 * i + 1], x[3 * i + 2]);

            VectorFliedd data(buffer, size_one * nlocal, size_one);

            container->appendData("pos", data,
                                      DECAF_NOFLAG, DECAF_PRIVATE,
                                      DECAF_SPLIT_DEFAULT, DECAF_MERGE_DEFAULT);
            /*else*/
            //{
                //vector<double> pos;
                //VectorFliedd data(pos, 3);
                //container->appendData("pos", data,
                                      //DECAF_NOFLAG, DECAF_PRIVATE,
                                      //DECAF_SPLIT_DEFAULT, DECAF_MERGE_DEFAULT);
            /*}*/

            decaf->put(container);
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

    decaf->terminate();
#ifdef V_T
    //VT_finalize();
    printf("[decaf]: trace finalized\n");
#endif



}

// gets the atom positions and prints them
void print_skel(Decaf* decaf)
{
    vector< pConstructData > in_data;

    int step = 0;;

//#ifdef DEBUG
    double a, b;
    a = 0, b = 0;
//#endif

    double t_start = MPI_Wtime();
    while (decaf->get(in_data))
    {
        // get the values
        for (size_t i = 0; i < in_data.size(); i++)
        {
            VectorFliedd pos = in_data[i]->getFieldData<VectorFliedd>("pos");
            if (pos)
            {
                // debug
                fprintf(stderr, "[lbm]: consumer printing %d atoms at step %d\n",
                        pos.getNbItems(),
                        step);
                for (int i = 0; i < pos.getNbItems(); i++){           // print first few atoms
/*                    fprintf(stderr, "%.3lf %.3lf\n",*/
                            //pos.getVector()[SIZE_ONE * i],
                            /*pos.getVector()[SIZE_ONE * i + 1]);*/
                            //pos.getVector()[3 * i + 2]);
                    a+= pos.getVector()[SIZE_ONE * i];
                    b+= pos.getVector()[SIZE_ONE * i+1];
                }

#ifdef DEBUG
                printf("first (%.3lf,%.3lf), last (%.3lf, %.3lf)\n",
                            pos.getVector()[0],
                            pos.getVector()[1],
                            pos.getVector()[SIZE_ONE *pos.getNbItems() -2],
                            pos.getVector()[SIZE_ONE *pos.getNbItems() -1]);

#endif

            }
            else
                fprintf(stderr, "[lbm]: Error: null pointer in node2\n");
        }
        step +=1;
    }
    double t_end = MPI_Wtime();
    printf("[lbm]: total-start-end %.3f %.3f %.3f\n", t_end- t_start, t_start, t_end);

    // terminate the task (mandatory) by sending a quit message to the rest of the workflow
    fprintf(stderr, "[lbm]: print terminating\n");


//#ifdef DEBUG
    printf("[lbm]: with summary a= %.3f b = %.3f\n", a, b);
//#endif
    decaf->terminate();
}

// gets the atom positions and prints them
void con(Decaf* decaf)
{

    /* data structure for analysis */
    int lp = N_LP;
    double sum_vx[NMOMENT], sum_vy[NMOMENT];
    double global_t_analy = 0, t_analy = 0;
    double t1, t2;
    int slice_size = 0;
    double *buffer;
    MPI_Comm comm;
    int rank;
    int step;

#ifdef V_T
     VT_classdef( "Analysis", &class_id2 );
     VT_funcdef("ANL", class_id2, &analysis_id);
#endif

    comm = decaf->con_comm_handle();
    rank = decaf->con_comm()->rank();

    vector< pConstructData > in_data;

    step = 0;


    if(rank == 0){
        printf("[noments]: application starts\n");
    }

    //MPI_Barrier(comm);
    double t_start = MPI_Wtime();
    while (decaf->get(in_data))
    {
        // get the values
        for (size_t i = 0; i < in_data.size(); i++)
        {
            VectorFliedd pos = in_data[i]->getFieldData<VectorFliedd>("pos");
            if (pos)
            {
                // debug
                slice_size = pos.getNbItems();

                if(rank == 0){
                    fprintf(stderr, "[nmoments]: consumer processing %d atoms at step %d\n",
                        slice_size,
                        step);
                }


                buffer = &pos.getVector()[0];

                t1 =MPI_Wtime(); 


#ifdef V_T
      VT_begin(analysis_id);
#endif
                run_analysis(buffer, slice_size, lp, sum_vx,sum_vy);

#ifdef V_T
      VT_end(analysis_id);
#endif

                t2 =MPI_Wtime(); 
                t_analy += t2-t1;

            }
            else
                fprintf(stderr, "[noments]: Error: null pointer in node2\n");
        }

        //printf("[nmoments]: Step %d,t_analy %lf\n", step, t2-t1);

        step +=1;
    }

   printf("[nmoments]: t_analy %lf\n", t_analy);
    //MPI_Barrier(comm);
    double t_end = MPI_Wtime();

    MPI_Reduce(&t_analy, &global_t_analy, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
    printf("[noments]: total-start-end %.3f %.3f %.3f\n", t_end- t_start, t_start, t_end);

    // terminate the task (mandatory) by sending a quit message to the rest of the workflow
    if(rank == 0){
		printf("[nmoments]: max t_analysis %.3f s,now terminates\n", global_t_analy);
	}


    decaf->terminate();
}

// forwards the atom positions in this example
// in a more realistic example, could filter them and only forward some subset of them
void print2(Decaf* decaf)
{
    vector< pConstructData > in_data;
while (decaf->get(in_data))
    {

        // get the values and add them
        for (size_t i = 0; i < in_data.size(); i++)
        {
            fprintf(stderr, "print2 forwarding positions\n");
            decaf->put(in_data[i]);
        }
    }

    // terminate the task (mandatory) by sending a quit message to the rest of the workflow
    fprintf(stderr, "print2 terminating\n");
    decaf->terminate();
}

extern "C"
{
    // dataflow just forwards everything that comes its way in this example
    void dflow(void* args,                          // arguments to the callback
               Dataflow* dataflow,                  // dataflow
               pConstructData in_data)   // input data
    {
        dataflow->put(in_data, DECAF_LINK);
    }
} // extern "C"

void run(Workflow& workflow,         // workflow
        int nsteps
        )
     /*    int lammps_nsteps,                  // number of lammps timesteps to execute*/
         //int analysis_interval,              // number of lammps timesteps to skip analyzing
         /*string infile)        */              // lammps input config file
{
    MPI_Init(NULL, NULL);

    

    Decaf* decaf = new Decaf(MPI_COMM_WORLD, workflow);

    // run workflow node tasks
    // decaf simply tells the user whether this rank belongs to a workflow node
    // how the tasks are called is entirely up to the user
    // e.g., if they overlap in rank, it is up to the user to call them in an order that makes
    // sense (threaded, alternting, etc.)
    // also, the user can define any function signature she wants
    if (decaf->my_node("prod"))
        prod(decaf, nsteps);
    if (decaf->my_node("con"))
        con(decaf);
    if (decaf->my_node("print2"))
        print2(decaf);

    // MPI_Barrier(MPI_COMM_WORLD);

    // cleanup
    delete decaf;

    MPI_Finalize();
}

// test driver for debugging purposes
// normal entry point is run(), called by python
#if 1
int main(int argc,
         char** argv)
{
    Workflow workflow;
    Workflow::make_wflow_from_json(workflow, "lbm_decaf.json");

    if(argc != 2){
        fprintf(stderr, "[lbm]: need steps\n");
        return -1;
    }
    int nsteps = atoi(argv[1]);

    // run decaf
    run(workflow, nsteps);

    return 0;

    /*int lammps_nsteps     = 1;*/
    //int analysis_interval = 1;
    //char * prefix         = getenv("DECAF_PREFIX");
    //if (prefix == NULL)
    //{
        //fprintf(stderr, "ERROR: environment variable DECAF_PREFIX not defined. Please export "
                //"DECAF_PREFIX to point to the root of your decaf install directory.\n");
        //exit(1);
    //}
    //string path = string(prefix , strlen(prefix));
    //path.append(string("./mod_vector_2nodes.so"));
    //string infile = argv[1];


    //// fill workflow nodes
    //WorkflowNode node;
    //node.in_links.push_back(1);              // print1
    //node.start_proc = 5;
    //node.nprocs = 1;
    //node.func = "print";
    //workflow.nodes.push_back(node);

    //node.out_links.clear();
    //node.in_links.clear();
    //node.in_links.push_back(0);              // print3
    //node.start_proc = 9;
    //node.nprocs = 1;
    //node.func = "print";
    //workflow.nodes.push_back(node);

    //node.out_links.clear();
    //node.in_links.clear();
    //node.out_links.push_back(0);             // print2
    //node.in_links.push_back(2);
    //node.start_proc = 7;
    //node.nprocs = 1;
    //node.func = "print2";
    //workflow.nodes.push_back(node);

    //node.out_links.clear();
    //node.in_links.clear();
    //node.out_links.push_back(1);             // lammps
    //node.out_links.push_back(2);
    //node.start_proc = 0;
    //node.nprocs = 4;
    //node.func = "prod";
    //workflow.nodes.push_back(node);

    //// fill workflow links
    //WorkflowLink link;
    //link.prod = 2;                           // print2 - print3
    //link.con = 1;
    //link.start_proc = 8;
    //link.nprocs = 1;
    //link.func = "dflow";
    //link.path = path;
    //link.prod_dflow_redist = "count";
    //link.dflow_con_redist = "count";
    //workflow.links.push_back(link);

    //link.prod = 3;                           // lammps - print1
    //link.con = 0;
    //link.start_proc = 4;
    //link.nprocs = 1;
    //link.func = "dflow";
    //link.path = path;
    //link.prod_dflow_redist = "count";
    //link.dflow_con_redist = "count";
    //workflow.links.push_back(link);

    //link.prod = 3;                           // lammps - print2
    //link.con = 2;
    //link.start_proc = 6;
    //link.nprocs = 1;
    //link.func = "dflow";
    //link.path = path;
    //link.prod_dflow_redist = "count";
    //link.dflow_con_redist = "count";
    //workflow.links.push_back(link);

    //// run decaf
    //run(workflow, lammps_nsteps, analysis_interval, infile);

    /*return 0;*/
}
#endif
