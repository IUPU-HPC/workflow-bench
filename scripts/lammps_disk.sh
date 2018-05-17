#export  I_MPI_JOB_RESPECT_PROCESS_PLACEMENT=0

# tmp folder for io
export BP_DIR="${SCRATCH_DIR}/bp-dir"
mkdir ${BP_DIR} -pv

env|grep '^HAS' # trace enabled?
module list
echo "case=$CASE_NAME datasize=$FILESIZE2PRODUCE nstops=$NSTOP"
echo "procs is \[ ${procs_this_app[*]}\], nodes is \[${nodes_this_app[*]}\]"

echo "procs is \[ ${procs_this_app[*]}\], nodes is \[${nodes_this_app[*]}\]"
if [ x"$HAS_TRACE" == "x" ];then
    BUILD_DIR=${PBS_O_WORKDIR}/build
    DS_SERVER=${WORK}/envs/gcc_mvapich/Dataspacesroot/bin/dataspaces_server

elif [ x"$HAS_TRACE" = "xitac" ]; then
    export LD_PRELOAD=libVT.so
    NSTOP=10
    echo "itac ENABLED, use 10 steps"
    export BUILD_DIR=${PBS_O_WORKDIR}/build_itac
    DS_SERVER=${WORK}/envs/gcc_mvapich/Dataspacesroot/bin/dataspaces_server
    echo "use itac"
    export VT_LOGFILE_PREFIX=${SCRATCH_DIR}/trace 
    export VT_VERBOSE=3
    #export export VT_CONFIG=${PBS_O_WORKDIR}/configs/vt.lammps.conf
    mkdir -pv $VT_LOGFILE_PREFIX
    env|grep '^VT' # trace enabled?

else
    echo "TRACE ENABLED"
    BUILD_DIR=${PBS_O_WORKDIR}/build_tau
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

BIN_PRODUCER=${BUILD_DIR}/bin/lammps_adios_prod;
BIN_CONSUMER=${BUILD_DIR}/bin/lammps_mpiio_con;

#This job runs with 3 nodes  
#ibrun in verbose mode will give binding detail  
#BUILD=${PBS_O_WORKDIR}/build_dspaces/bin
PBS_RESULTDIR=${SCRATCH_DIR}/results 


mkdir -pv ${PBS_RESULTDIR}
tune_stripe_count=-1
lfs setstripe --stripe-size 1m --stripe-count ${tune_stripe_count} ${PBS_RESULTDIR}
mkdir -pv ${SCRATCH_DIR}

cd ${SCRATCH_DIR}
cp -R ${PBS_O_WORKDIR}/all-transports/adios-all/lammps-adios/xmls ${SCRATCH_DIR}


# this scripts is avaliable at
#GENERATE_HOST_SCRIPT=${HOME}/Workspaces/General_Data_Broker/lbm_adios/scripts/generate_hosts.sh
GENERATE_HOST_SCRIPT=${PBS_O_WORKDIR}/scripts/generate_hosts.sh
#GENERATE_HOST_SCRIPT=${HOME}/Downloads/LaucherTest/generate_hosts.sh
if [ -a $GENERATE_HOST_SCRIPT ]; then
    source $GENERATE_HOST_SCRIPT
else
    echo "generate_hosts.sh should downloaded from:"
    echo "https://github.iu.edu/lifen/LaucherTest/blob/master/generate_hosts.sh"
fi

LAUNCHER="mpirun -l"

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


cp ${PBS_O_WORKDIR}/scripts/lammps_input/$infile ./$infile

#Use ibrun to run the MPI job. It will detect the MPI, generate the hostfile
# and doing the right binding. With no options ibrun will use all cores.
#export OMP_NUM_THREADS=1
CMD_PRODUCER="$LAUNCHER -np ${procs_this_app[0]} -machinefile $HOST_DIR/machinefile-app0  ${BIN_PRODUCER} ${NSTOP} $infile"
$CMD_PRODUCER  &> ${PBS_RESULTDIR}/producer.log &
echo "producer applciation lauched: $CMD_PRODUCER"

CMD_CONSUMER="$LAUNCHER -np ${procs_this_app[1]} -machinefile $HOST_DIR/machinefile-app1 ${BIN_CONSUMER} ${NSTOP}"
$CMD_CONSUMER  &> ${PBS_RESULTDIR}/consumer.log &
echo " consumer applciation lauched $CMD_CONSUMER"

## Wait for the entire workflow to finish
wait
