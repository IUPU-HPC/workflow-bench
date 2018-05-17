#################################################### 

export OMP_NUM_THREADS=4

env|grep '^HAS' # trace enabled?
env|grep '^OMP' # trace enabled?

#module load remora

#module load libfabric
module list

echo "procs is \[ ${procs_this_app[*]}\], nodes is \[${nodes_this_app[*]}\]"
echo "will run $NSTOP steps and using inputfile $infile"

#export BUILD_DIR=${PBS_O_WORKDIR}/build
if [ x"$HAS_TRACE" == "x" ];then
    export BUILD_DIR=${PBS_O_WORKDIR}/build
    #DS_SERVER=${WORK}/envs/gcc_mvapich/Dataspacesroot/bin/dataspaces_server
    export DECAF_PREFIX=$WORK/software/install
elif [ x"$HAS_TRACE" = "xitac" ]; then
    export LD_PRELOAD=libVT.so
    NSTOP=10
    echo "itac ENABLED, use 10 steps"
    export BUILD_DIR=${PBS_O_WORKDIR}/build_itac
    echo "use itac"
    export VT_LOGFILE_PREFIX=${SCRATCH_DIR}/trace 
    export VT_VERBOSE=3
    export export VT_CONFIG=${PBS_O_WORKDIR}/configs/vt.lammps.conf
    mkdir -pv $VT_LOGFILE_PREFIX
    env|grep '^VT' # trace enabled?



else
    echo "TRACE ENABLED"
    export BUILD_DIR=${PBS_O_WORKDIR}/build_tau
    #DS_SERVER=${WORK}/envs/Dataspacesroot_tau/bin/dataspaces_server
    #enable trace
    export TAU_TRACE=1
    # set trace dir
    export ALL_TRACES=${SCRATCH_DIR}/trace
    mkdir -pv $ALL_TRACES/app0
    mkdir -pv $ALL_TRACES/app1
    mkdir -pv $ALL_TRACES/app2

    if [ -z $TAU_MAKEFILE ]; then
        module load tau
        echo "LOAD TAU!"
    fi

    export DECAF_PREFIX=$WORK/software/install_tau

fi

env|grep '^DECAF' # trace enabled?

#export BUILD_DIR=${PBS_O_WORKDIR}/build

#This job runs with 3 nodes  
#ibrun in verbose mode will give binding detail  #BUILD=${PBS_O_WORKDIR}/build_dspaces/bin
PBS_RESULTDIR=${SCRATCH_DIR}/results



mkdir -pv ${PBS_RESULTDIR}
tune_stripe_count=-1
lfs setstripe --stripe-size 1m --stripe-count ${tune_stripe_count} ${PBS_RESULTDIR}
mkdir -pv ${SCRATCH_DIR}
cd ${SCRATCH_DIR}
#cp -R ${PBS_O_WORKDIR}/global_range_select/arrays.xml ${SCRATCH_DIR}
cp ${BUILD_DIR}/config.h  ${SCRATCH_DIR}


# this scrWorkspaces/General_Data_Broker/lbm_adios/scripts
GENERATE_HOST_SCRIPT=${PBS_O_WORKDIR}/scripts/generate_hosts.sh
#GENERATE_HOST_SCRIPT=${HOME}/Downloads/LaucherTest/generate_hosts.sh
if [ -a $GENERATE_HOST_SCRIPT ]; then
    source $GENERATE_HOST_SCRIPT
else
    echo "generate_hosts.sh should downloaded from:"
    echo "https://github.iu.edu/lifen/LaucherTest/blob/master/generate_hosts.sh"
fi

if [[ `hostname` == *"bridges"* ]];then
    if [ x`which mpicc|grep mvapich` = "x" ]; then

        # itac by default load impi
        export I_MPI_JOB_RESPECT_PROCESS_PLACEMENT=0
        export I_MPI_SHM_LMT=shm
    else
        export MV2_ENABLE_AFFINITY=0
        export MV2_USE_BLOCKING=1
    fi
fi

export procs_prod=${procs_this_app[0]}
export procs_link=${procs_this_app[1]}
export procs_con=${procs_this_app[2]}

procs_all=$((procs_prod + procs_con + procs_link))

# generate graph
PYTHON_RUN="python $PBS_O_WORKDIR/all-transports/decaf/lammps_decaf.py --np ${procs_all} --hostfile ${HOST_DIR}/machinefile-all"
$PYTHON_RUN &> python.log
echo "python run $PYTHON_RUN"

# copy input file
#infile=in.melt
cp ${PBS_O_WORKDIR}/scripts/lammps_input/$infile ./$infile

cmd="$BUILD_DIR/bin/lammps_decaf $NSTOP $infile"

## order is prod/link/consumer
MPI_CMD="mpirun -l  --machinefile ${HOST_DIR}/machinefile-all -np ${procs_prod} $cmd : -np ${procs_link} $cmd : -np ${procs_con} $cmd"
echo launch mpi with cmd $MPI_CMD

$MPI_CMD

## Wait for the entire workflow to finish
wait
