#!/bin/bash
# Feng Li, Oct 2017, IUPUI

# generate hostfile/machine file for mpiexec.hydra
# see https://github.iu.edu/lifen/LaucherTest/blob/master/launcher_stampede2.job for example

#@input num_apps number of applications
#@input procs_this_app process slots of each app
#@input nodes_this_app node for each app
#@input $PBS_RESULTDIR directory to output the machine files

#@output $PBS_RESULTDIR/hosts/machiefile-app0..app1...app2 generated machine files


# check input 
if [ -z ${num_apps} -o -z ${procs_this_app} -o -z ${nodes_this_app} ]; then
    echo "should define num_apps, procs_this_app and nodes_this_app"
    exit -1
fi

# validation
for i in `seq 0 ${num_apps}`; do
    if ((procs_this_app % nodes_this_app)); then
        echo "proc number $procs_this_app cannot be divided by $nodes_this_app"
        exit -1
    fi
done

if [ -z $PBS_RESULTDIR ]; then
    echo "should specify result dir"
    exit -1
fi

if [ -z $SLURM_NODELIST ]; then
    echo "should use slurm"
    exit -1
fi


## generate host/machine files, modified from ibrun
HOST_DIR=$PBS_RESULTDIR/hosts
mkdir -pv $HOST_DIR

nodes=(`scontrol show hostname $SLURM_NODELIST`)
echo "${nodes[*]}" > $HOST_DIR/hostfile-all 

idx=0
# Put first $num_nodes_server to hostfile-server

for ((j=0;j<$num_apps;j++))
do
    # first decide ppn in this app
    ppn_this_app=$((procs_this_app[j]/nodes_this_app[j]))
    echo "ppn in this app = $ppn_this_app"

    # than assign nodes to it
    for ((i=0;i<${nodes_this_app[j]};i++)) 
    do
        for ((k=0;k<${ppn_this_app};k++)) 
        do
            echo "${nodes[$idx]}" >> $HOST_DIR"/machinefile-app"${j}
            echo "${nodes[$idx]}" >> $HOST_DIR"/machinefile-all"
        done
        echo "node in app ${j} +1"
        let "idx=idx+1"
    done
done







