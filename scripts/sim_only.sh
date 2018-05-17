#export  I_MPI_JOB_RESPECT_PROCESS_PLACEMENT=0

env|grep '^HAS' # trace enabled?
module list
echo "case=$CASE_NAME datasize=$FILESIZE2PRODUCE nstops=$NSTOP"
echo "procs is \[ ${procs_this_app[*]}\], nodes is \[${nodes_this_app[*]}\]"

if [ x"$HAS_TRACE" = "x" ];then
    BUILD_DIR=${PBS_O_WORKDIR}/build
    DS_SERVER=${WORK}/envs/gcc_mvapich/Dataspacesroot/bin/dataspaces_server

elif [ x"$HAS_TRACE" = "xitac" ]; then
    #export LD_PRELOAD=libVT.so
    NSTOP=10
    echo "itac ENABLED, use 10 steps"
    export BUILD_DIR=${PBS_O_WORKDIR}/build_itac
    echo "use itac"
    export VT_LOGFILE_PREFIX=${SCRATCH_DIR}/trace 
    export VT_VERBOSE=3
    mkdir -pv $VT_LOGFILE_PREFIX
else
    echo "TRACE ENABLED, use 10 steps"
    export BUILD_DIR=${PBS_O_WORKDIR}/build_tau
    DS_SERVER=${WORK}/envs/Dataspacesroot_tau/bin/dataspaces_server
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

fi


#BIN_PRODUCER=${BUILD_DIR}/bin/lbm;

#This job runs with 3 nodes  
#ibrun in verbose mode will give binding detail  
#BUILD=${PBS_O_WORKDIR}/build_dspaces/bin
PBS_RESULTDIR=${SCRATCH_DIR}/results 


mkdir -pv ${PBS_RESULTDIR}
tune_stripe_count=-1
lfs setstripe --stripe-size 1m --stripe-count ${tune_stripe_count} ${PBS_RESULTDIR}
mkdir -pv ${SCRATCH_DIR}

cd ${SCRATCH_DIR}

cp ${BUILD_DIR}/config.h  ${SCRATCH_DIR}


## Create dataspaces configuration file
# note that we now have 400 regions


# this scripts is avaliable at
GENERATE_HOST_SCRIPT=${HOME}/Workspaces/General_Data_Broker/lbm_adios/scripts/generate_hosts.sh
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
        echo "now use intel mpi"
        export I_MPI_JOB_RESPECT_PROCESS_PLACEMENT=0
        export I_MPI_SHM_LMT=shm
    else
        echo "now use mvapich mpi"
        export MV2_ENABLE_AFFINITY=0
        export MV2_USE_BLOCKING=1
    fi
fi


LAUNCHER="mpirun -l"
cmd="$BUILD_DIR/bin/lbm $NSTOP"
#cmd="$BUILD_DIR/bin/tmp_lbm $NSTOP"


#Use ibrun to run the MPI job. It will detect the MPI, generate the hostfile
# and doing the right binding. With no options ibrun will use all cores.
#export OMP_NUM_THREADS=1
CMD_PRODUCER="$LAUNCHER -genv TRACEDIR=${ALL_TRACES}/app0 -machinefile $HOST_DIR/machinefile-app0 -np ${procs_this_app[0]} $cmd"
$CMD_PRODUCER  &> ${PBS_RESULTDIR}/producer.log &
echo "producer applciation lauched: $CMD_PRODUCER"

wait
