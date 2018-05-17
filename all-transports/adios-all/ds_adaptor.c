/*
 * @author Feng Li, IUPUI
 * @date   2017
 */

#include "ds_adaptor.h"
#include "utility.h"
#include "config.h"

#ifdef V_T
#include <VT.h>
int class_id;
int ds_lock_id, ds_unlock_id, ds_put_id, ds_get_id;
#endif

static char *module_name = "ds_adaptor";




// logger indentifier
extern const int MY_LOGGER;

/* 
 * this is a wrapper of adios_init for trace init
 */
status_t ds_adaptor_init_client(int nprocs, int appid, MPI_Comm * pcomm, const char * param)
{
    /*
     * trace init
     */
#ifdef V_T
      #warning "VT enabled in ds_adaptor"
      //VT_initialize(NULL, NULL);
      PINF("[%s]: trace enabled and initialized", module_name );
      VT_classdef( "DSPACES-DIMES", &class_id );
      VT_funcdef("DS-LOCK", class_id, &ds_lock_id);
      VT_funcdef("DS-UNLOCK", class_id, &ds_unlock_id);
      VT_funcdef("DS-PUT", class_id, &ds_put_id);
      VT_funcdef("DS-GET", class_id, &ds_get_id);
#endif

    int ret = -1;
    PINF("[%s]: trying init dspaces for %d process\n",module_name, nprocs);
    ret = dspaces_init(nprocs, appid, pcomm, param);

    if(ret == 0){
        PINF( "dataspaces init successfully");
        return S_OK;
    }else{
        PERR( "dataspaces init error");
        TRACE();
        return S_FAIL;
    }


}


#define debug_1
status_t get_common_buffer(uint8_t transport_minor,int timestep,int ndim, uint64_t bounds[6], int rank, char * var_name, void **p_buffer,size_t elem_size, double *p_time_used){

    PDBG("\n ** prepare to get, ndim = %d\n", ndim);
    // how many number of elements are actually written
    //int num_elems;
    char msg[STRING_LENGTH];
    double t1, t2;
    int ret_get = -1;

    int num_points;
    
    uint64_t lb[3] = {0}, ub[3] = {0};
    /*
    lb[0] = 0;
    ub[0] = num_points - 1;
    */
    lb[0] = bounds[0]; //ymin
    lb[1] = bounds[1]; //xmin
    lb[2] = bounds[2]; //0

    ub[0] = bounds[3]; //ymax
    ub[1] = bounds[4]; //xmax
    ub[2] = bounds[5]; //0

    num_points = (bounds[3]-bounds[0]+1)*(bounds[4]- bounds[1]+1)*(bounds[5]- bounds[2]+1);

    // Define the dimensionality of the data to be received 
    //int ndim = 3;

    char lock_name[STRING_LENGTH];
    int part = rank;
    //MPI_Comm row_comm = MPI_COMM_SELF;
    //MPI_Comm_split(MPI_COMM_WORLD, part, rank, &row_comm);
    MPI_Comm row_comm = MPI_COMM_WORLD;


#ifdef USE_SAME_LOCK
    snprintf(lock_name, STRING_LENGTH, "%s_lock", var_name);
#else
    //snprintf(lock_name, STRING_LENGTH, "%s_lock_t_%d",var_name, timestep%20);
    //snprintf(lock_name, STRING_LENGTH, "%s_lock_p_%d_t_%d",var_name,part, timestep%(DS_MAX_VERSION));
    snprintf(lock_name, STRING_LENGTH, "%s_lock_t_%d",var_name, timestep%(DS_MAX_VERSION));
    //snprintf(lock_name, STRING_LENGTH, "%s_lock_t_%d",var_name, timestep);
#endif

#ifdef debug_1
    PDBG("lb: (%lu, %lu  %lu), hb(%lu, %lu, %lu), elem_size %zu bytes\n", bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5], elem_size);
#endif

    PDBG( "try to acquired the read lock %s for step %d", lock_name, timestep);

    
#ifdef V_T
      VT_begin(ds_lock_id);
#endif
    dspaces_lock_on_read(lock_name, &row_comm);
#ifdef V_T
      VT_end(ds_lock_id);
#endif

    PDBG( "get the read lock %s for step %d", lock_name, timestep);

    // read all regions in once
    //
#ifdef V_T
    VT_begin(ds_get_id);
#endif
    t1 = MPI_Wtime();
    if(transport_minor == DIMES){
        ret_get = dimes_get(var_name, timestep, elem_size, ndim, lb, ub, *p_buffer);
    }
    //calculation took more time?
    else{
        ret_get = dspaces_get(var_name, timestep, elem_size, ndim, lb, ub, *p_buffer);
    }

#ifdef V_T
    VT_end(ds_get_id);
#endif
//#else
//#error("either dspaces or dimes")
    t2 = MPI_Wtime();

    PDBG( "try to unlock the read lock %s for step %d", lock_name, timestep);


    // now we can release region lock
#ifdef V_T
    VT_begin(ds_unlock_id);
#endif
    dspaces_unlock_on_read(lock_name, &row_comm);
#ifdef V_T
    VT_end(ds_unlock_id);
#endif
    PDBG( "release the read lock %s for step %d ", lock_name, timestep);

    if(ret_get != 0){

        PDBG( "get varaible %s err in step %d ,  error number %d \n", var_name, timestep, ret_get);
        TRACE();
        return(S_FAIL);
    }else{
        PDBG( "read %d elem from dspaces, each has %zu bytes", num_points, elem_size);
    }

    *p_time_used = t2-t1;
    return S_OK;
    //MPI_Comm_free(&row_comm);
    
}

status_t put_common_buffer(uint8_t transport_minor, int timestep,int ndim, uint64_t bounds[6], int rank,char * var_name, void  **p_buffer,size_t elem_size, double *p_time_used){

    PDBG("\n ** prepare to put, ndim = %d\n", ndim);
    // how many number of elements are actually written
    //int num_elems;
    char msg[STRING_LENGTH];
    double t1, t2;
    int ret_put = -1;

    int num_points;
    
    uint64_t lb[3] = {0}, ub[3] = {0};
    /*
    lb[0] = 0;
    ub[0] = num_points - 1;
    */
    lb[0] = bounds[0];
    lb[1] = bounds[1];
    lb[2] = bounds[2];
    //y
    ub[0] = bounds[3];
    //x
    ub[1] = bounds[4];
    ub[2] = bounds[5];

    num_points = (bounds[3]-bounds[0]+1)*(bounds[4]- bounds[1]+1)*(bounds[5]- bounds[2]+1);

    char lock_name[STRING_LENGTH];
    unsigned int part = rank/2;
    /*MPI_Comm row_comm;*/
    /*MPI_Comm_split(MPI_COMM_WORLD, part, rank, &row_comm);*/

    MPI_Comm row_comm = MPI_COMM_WORLD;

#ifdef USE_SAME_LOCK
    snprintf(lock_name, STRING_LENGTH, "%s_lock", var_name);
#else
    //snprintf(lock_name, STRING_LENGTH, "%s_lock_t_%d",var_name, timestep%20);
    //snprintf(lock_name, STRING_LENGTH, "%s_lock_p_%d_t_%d",var_name,part, timestep%(DS_MAX_VERSION));
    snprintf(lock_name, STRING_LENGTH, "%s_lock_t_%d",var_name, timestep%(DS_MAX_VERSION));
#endif

#ifdef debug_1
    PDBG("lb: (%lu, %lu  %lu), hb(%lu, %lu, %lu), elem_size %zu bytes\n", bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5], elem_size);
#endif

    PDBG( "try to acquired the write lock %s for step %d", lock_name, timestep);


#ifdef V_T
      VT_begin(ds_lock_id);
#endif
    dspaces_lock_on_write(lock_name, &row_comm);
#ifdef V_T
      VT_end(ds_lock_id);
#endif

    

    PDBG( "get the write lock %s for step %d", lock_name, timestep);

    int sync_ok = -1;

    // write all data in once
    t1 = MPI_Wtime();

#ifdef V_T
      VT_begin(ds_put_id);
#endif
    if(transport_minor == DIMES){
        //if(timestep%(DS_MAX_VERSION)==0 && timestep>0){
            // this will free  previous buffer
            if(S_OK != dimes_put_sync_group(lock_name, 0)){
                PERR("put_sync error");
                TRACE(); 
                return S_FAIL;
            }
            if(S_OK != dimes_put_set_group(lock_name, 0)){
                PERR("put_set_group error");
                TRACE(); 
                return S_FAIL;
            } 
/*#ifdef USE_SAME_LOCK*/
            /*sync_ok = dimes_put_sync_all();*/
            /*if(sync_ok != 0){*/
                /*perror("put err:");*/
                /*TRACE();*/
                /*return S_FAIL;*/
            /*}*/
/*#endif*/

            PDBG( "freed tmp buffer at step at step %d", timestep);
        //}
        ret_put = dimes_put(var_name, timestep, elem_size, ndim, lb, ub, *p_buffer);
    }
    else{
        ret_put = dspaces_put(var_name, timestep, elem_size, ndim, lb, ub, *p_buffer);


    }
#ifdef V_T
      VT_end(ds_put_id);
#endif
    t2 = MPI_Wtime();

    // now we can release region lock
#ifdef V_T
      VT_begin(ds_unlock_id);
#endif
    dspaces_unlock_on_write(lock_name, &row_comm);
#ifdef V_T
      VT_end(ds_unlock_id);
#endif
    PDBG( "release the write lock %s for step %d ", lock_name, timestep);

    if(ret_put != 0){
        PERR("put varaible %s err,  error number %d \n", var_name, ret_put);
        TRACE();
        return S_FAIL;
    }
    else{
        PDBG( "write %d elem to dspaces, each has %zu bytes", num_points, elem_size);
    }
    *p_time_used = t2-t1;
    //MPI_Comm_free(&row_comm);
    return S_OK;
}

/* dimes needs to flush last step
         */
status_t ds_adaptor_flush_dimes(char * var_name, MPI_Comm comm, int nsteps){
   
    char lock_name[STRING_LENGTH];
#ifdef USE_SAME_LOCK
    snprintf(lock_name, STRING_LENGTH, "%s_lock", var_name);
    dspaces_lock_on_write(lock_name, &comm);
    dimes_put_sync_all();
    dspaces_unlock_on_write(lock_name, &comm);
    //PINF("rank %d: step %d last step flushed\n");
#else
    int i;
    for(i = 0 ; i< DS_MAX_VERSION; i++){ // make sure bufferd values are flushed!
        snprintf(lock_name, STRING_LENGTH, "%s_lock_t_%d",var_name, (i+nsteps)%(DS_MAX_VERSION));
        dspaces_lock_on_write(lock_name, &comm);
        if(S_OK != dimes_put_sync_group(lock_name, 0)){
                PERR("put_sync error");
                TRACE(); 
                return S_FAIL;
        }

        dspaces_unlock_on_write(lock_name, &comm);
    }
#endif
    return S_OK;
}
