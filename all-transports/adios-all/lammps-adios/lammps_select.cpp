/*
 * create selection for lammps consumer app
 *
 * TODO: this should be put in lammps fold
 */

//#include "adios_adaptor.h"
#include "adios_read.h"
#include "adios_error.h"
#include "adios.h"
#include "utility.h"

#include "adios_adaptor.h"



/*
 * slice in dimension y
 */
static void
slice(uint64_t length, uint64_t *s, uint64_t *e, int rank, int mpisize)
{

    uint64_t start = 0;
    uint64_t end = 0;
    uint64_t rem = length % mpisize;

    start = length/mpisize * rank;
    end = length/mpisize * (rank+1);
    *s = start;
    *e = end;
    
    /* If our MPI size is greater
       than the number of y dimensions,
       then read the whole thing. */
    if (mpisize > length) {
	*e = length;
	*s = 0;
	return;\
    }
    if (end > length) {
        end = length;
        *e = end;
        return;
    }
    if (rank == mpisize-1) {
        end += rem;
        *e = end;
    }
}



status_t query_select_lammps(ADIOS_FILE * afile, int rank, int nprocs, ADIOS_SELECTION ** sel, size_t *p_nelem){
   // ADIOS_SELECTION *global_range_select = *sel;

    int         NX, NY, NZ; 

        ADIOS_VARINFO *nx_info = adios_inq_var(afile, "/scalar/dim/NX");
        ADIOS_VARINFO *ny_info = adios_inq_var(afile, "/scalar/dim/NY");
	ADIOS_VARINFO *nz_info = adios_inq_var(afile, "/scalar/dim/NZ");

	ADIOS_VARINFO *arry = adios_inq_var( afile, "var_2d_array");
    //ADIOS_VARINFO * v = adios_inq_var (f, "array");
    /* Using less readers to read the global array back, i.e., non-uniform */

	uint64_t my_ystart, my_yend;
	slice(arry->dims[1], &my_ystart, &my_yend, rank, nprocs);

	/* printf("rank: %d my_ystart: %d, my_yend: %d\n", */
	/*        rank, (int)my_ystart, (int)my_yend); */

	uint64_t xcount = arry->dims[0];
	uint64_t ycount = my_yend - my_ystart;
	uint64_t zcount = arry->dims[2];

	uint64_t starts[] = {0, my_ystart, 0};
	uint64_t counts[] = {xcount, ycount, zcount};

	/* printf("rank: %d starts: %d %d %d. counts: %d %d %d\n", */
	/*        rank, */
	/*        (int)starts[0], (int)starts[1], (int)starts[2], */
	/*        (int)counts[0], (int)counts[1], (int)counts[2]); */

	*sel = adios_selection_boundingbox(arry->ndim, starts, counts);

	*p_nelem = xcount*ycount*zcount;

        if(nx_info->value) {
            NX = *((int *)nx_info->value);
        }
        if(ny_info->value){
            NY= *((int*)ny_info->value);
        }
        if(nz_info->value){
            NZ= *((int*)nz_info->value);
        }
    
	if(rank == 0){
	    int n;
	    //printf("[%.2f]:adios global dim(column based)step %d, dims: [ ",MPI_Wtime(), ii);
	    for(n=0; n<arry->ndim; n++){
		printf("%d ", (int)arry->dims[n]);
	    }
	    printf("]\n");
	}
    return S_OK;
}
    
 
