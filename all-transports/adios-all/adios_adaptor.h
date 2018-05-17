/*
 * @author Feng Li, IUPUI
 * @date   2017
 */

#ifndef ADIOS_ADAPTOR_H
#define ADIOS_ADAPTOR_H
#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include "time.h"
#include <unistd.h>
#include "utility.h"

#include "adios_read.h"
#include "adios_error.h"
#include "adios.h"


status_t query_select_lammps(ADIOS_FILE * afile, int rank, int nprocs, ADIOS_SELECTION **global_range_select, size_t *p_nelem);


status_t adios_adaptor_update_avail_version(MPI_Comm comm, char * step_index_file, int timestep, int nsteps);


status_t adios_adaptor_get_avail_version(MPI_Comm comm, char *step_index_file, int *p_max_version, int nstop);
status_t adios_adaptor_init_client(char *xmlfile, MPI_Comm comm);

/* 
 * @brief adios writting wrapper
 *
 * @param file_path file_path to write data to(not applicable to )
 * @param var_name  varable names for stating 
 * @param timestep  streaming write(-1) or current timesteps(mpiio write data into different files)
 * @param n         number of lines(data records)
 * @param size_one  number of elements in each line(record)
 * @param buffer    data buffer
 * @param mode      write mode, restart file is written is append mode
 * @param pcomm     communicator
 */
void insert_into_adios(char * file_path, char *var_name, int timestep, int n, int size_one, double * buf, const char * mode, MPI_Comm *pcomm);

status_t adios_adaptor_init_client(char *xmlfile, MPI_Comm comm);

#ifdef __cplusplus
}
#endif
#endif
