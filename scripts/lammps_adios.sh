# tmp folder for io
export BP_DIR="${SCRATCH_DIR}/bp-dir"
mkdir ${BP_DIR} -pv

#################################################### 
# common commands for all experiments 
#export  I_MPI_JOB_RESPECT_PROCESS_PLACEMENT=0
export OMP_NUM_THREADS=4

#export HAS_KEEP=0
#export CMTransport=fabric
export CM_INTERFACE=ib0
#export CMTransport=fabric
#export CMTransportVerbose=1

env|grep '^CM'
env|grep '^HAS' # trace enabled?
env|grep '^OMP' # trace enabled?

#module load libfabric
module list

echo "case=$CASE_NAME datasize=$FILESIZE2PRODUCE nstops=$NSTOP, HASKEEP=${HAS_KEEP}"
echo "procs is \[ ${procs_this_app[*]}\], nodes is \[${nodes_this_app[*]}\]"

if [ x"$HAS_TRACE" == "x" ];then
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


#This job runs with 3 nodes  
#ibrun in verbose mode will give binding detail  #BUILD=${PBS_O_WORKDIR}/build_dspaces/bin
PBS_RESULTDIR=${SCRATCH_DIR}/results



mkdir -pv ${PBS_RESULTDIR}
tune_stripe_count=-1
lfs setstripe --stripe-size 1m --stripe-count ${tune_stripe_count} ${PBS_RESULTDIR}
mkdir -pv ${SCRATCH_DIR}
cd ${SCRATCH_DIR}
#cp -R ${PBS_O_WORKDIR}/adios/xmls ${SCRATCH_DIR}

cp -R ${PBS_O_WORKDIR}/all-transports/adios-all/lammps-adios/xmls ${SCRATCH_DIR}
cp ${BUILD_DIR}/config.h  ${SCRATCH_DIR}


# this scrWorkspaces/General_Data_Broker/lbm_adios/scripts
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
        export I_MPI_JOB_RESPECT_PROCESS_PLACEMENT=0
        export I_MPI_SHM_LMT=shm
    else
        export MV2_ENABLE_AFFINITY=0
        export MV2_USE_BLOCKING=1
    fi
fi



echo "use transport method $CMTransport with CMTransportVerbose=$CMTransportVerbose"


export procs_prod=${procs_this_app[0]}
#export procs_link=${procs_this_app[1]}
export procs_con=${procs_this_app[1]}

cp ${PBS_O_WORKDIR}/scripts/lammps_input/$infile ./$infile

cmd_prod="$BUILD_DIR/bin/lammps_adios_prod $NSTOP $infile"
cmd_con="$BUILD_DIR/bin/lammps_adios_con $NSTOP"

## order is prod/link/consumer
MPI_CMD1="mpirun -l  --machinefile $HOST_DIR/machinefile-app0 -np ${procs_prod} $cmd_prod"

MPI_CMD2="mpirun -l  --machinefile $HOST_DIR/machinefile-app1 -np ${procs_con} $cmd_con"

$MPI_CMD1  & ${PBS_RESULTDIR}/producer.log &
$MPI_CMD2 &>${PBS_RESULTDIR}/consumer.log &

wait
