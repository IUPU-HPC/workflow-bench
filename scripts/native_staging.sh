####################################################
# common commands for all experiments
env|grep '^HAS' # trace enabled?
module list

#export  I_MPI_JOB_RESPECT_PROCESS_PLACEMENT=0

echo "case=$CASE_NAME datasize=$FILESIZE2PRODUCE nstops=$NSTOP, HASKEEP=${HAS_KEEP}"

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

BIN_PRODUCER=${BUILD_DIR}/bin/run_lbm;
BIN_CONSUMER=${BUILD_DIR}/bin/native_staging_read;

#This job runs with 3 nodes  
#ibrun in verbose mode will give binding detail  #BUILD=${PBS_O_WORKDIR}/build_dspaces/bin
PBS_RESULTDIR=${SCRATCH_DIR}/results

mkdir -pv ${PBS_RESULTDIR}
tune_stripe_count=-1
lfs setstripe --stripe-size 1m --stripe-count ${tune_stripe_count} ${PBS_RESULTDIR}
mkdir -pv ${SCRATCH_DIR}

## traces
SERVER_TRACE_DIR=${PBS_RESULTDIR}/server_trace
PRODUCER_TRACE_DIR=${PBS_RESULTDIR}/producer_trace
CONSUMER_TRACE_DIR=${PBS_RESULTDIR}/consumer_trace
mkdir -pv ${SERVER_TRACE_DIR}
mkdir -pv ${PRODUCER_TRACE_DIR}
mkdir -pv ${CONSUMER_TRACE_DIR}


cd ${SCRATCH_DIR}
cp -R ${PBS_O_WORKDIR}/adios_xmls ${SCRATCH_DIR}
cp ${BUILD_DIR}/config.h  ${SCRATCH_DIR}



## Clean up
rm -f conf *.log srv.lck
rm -f dataspaces.conf

## Create dataspaces configuration file
# note that we now have 400 regions

#dims = 5, 300000, 10
#dims = 2, 1500000, 1
# 64*64*256 will generate 1048576 lines
DS_LIMIT=$((FILESIZE2PRODUCE*FILESIZE2PRODUCE*FILESIZE2PRODUCE*procs_this_app[1]/16)) # make sure dspaces can hold all data


echo "total number of lines is $DS_LIMIT"

#dims = 16,16
echo "## Config file for DataSpaces
ndim = 2
dims = 2, $((DS_LIMIT))
hash_version = 2
max_versions = 3
max_readers = 1
lock_type = 2
" > dataspaces.conf
echo "DS_LIMIT= $DS_LIMIT"

# this scripts is avaliable at
GENERATE_HOST_SCRIPT=${HOME}/Workspaces/General_Data_Broker/lbm_adios/scripts/generate_hosts.sh
if [ -a $GENERATE_HOST_SCRIPT ]; then
    source $GENERATE_HOST_SCRIPT
else
    echo "generate_hosts.sh should downloaded from:"
    echo "https://github.iu.edu/lifen/LaucherTest/blob/master/generate_hosts.sh"
fi

if [ x"$HAS_TRACE" == "x" ];then
    LAUNCHER="mpiexec.hydra"
else
    #export LD_PRELOAD=libVT.so 
    #LAUNCHER="mpiexec.hydra -trace"
    LAUNCHER="mpirun -l"
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

#-env I_MPI_FABRICS tcp

env|grep '^I_MPI' # trace enabled?
env|grep '^MV2' # trace enabled?


## Run DataSpaces servers
CMD_SERVER="$LAUNCHER -np ${procs_this_app[0]} -machinefile $HOST_DIR/machinefile-app0 -env TRACEDIR=${ALL_TRACES}/app0 ${DS_SERVER} -s ${procs_this_app[0]} -c $((procs_this_app[1]+procs_this_app[2]))"
$CMD_SERVER  &> ${PBS_RESULTDIR}/server.log &
echo "server applciation lauched: $CMD_SERVER"
## Give some time for the servers to load and startup
while [ ! -f conf ]; do
    sleep 1s
done
sleep 5s  # wait server to fill up the conf file

CMD_PRODUCER="$LAUNCHER -np ${procs_this_app[1]} -machinefile $HOST_DIR/machinefile-app1 -env TRACEDIR=${ALL_TRACES}/app1 ${BIN_PRODUCER} ${NSTOP}"
$CMD_PRODUCER  &> ${PBS_RESULTDIR}/producer.log &
echo "producer applciation lauched: $CMD_PRODUCER"

CMD_CONSUMER="$LAUNCHER -np ${procs_this_app[2]} -machinefile $HOST_DIR/machinefile-app2 -env TRACEDIR=${ALL_TRACES}/app2 ${BIN_CONSUMER} ${NSTOP} ${FILESIZE2PRODUCE} ${procs_this_app[1]}"
$CMD_CONSUMER  &> ${PBS_RESULTDIR}/consumer.log &
echo " consumer applciation lauched $CMD_CONSUMER"

## Wait for the entire workflow to finish
wait

