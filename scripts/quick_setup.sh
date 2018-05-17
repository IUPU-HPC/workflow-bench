#!/bin/bash

## quick setup for envs for inteactive jobs
## to use it just source 
export SCRATCH_DIR=${SCRATCH}/data_broker_adios/${SLURM_JOBID}
export MyTransport=ADIOS_STAGING_FLEXPATH
export OMP_NUM_THREADS=4
export CM_INTERFACE=ib0
export PBS_RESULTDIR=${SCRATCH_DIR}/results
mkdir -pv ${PBS_RESULTDIR}

echo "env set finished"

