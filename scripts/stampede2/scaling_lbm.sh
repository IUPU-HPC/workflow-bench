#! /bin/bash
#export GEN_TRACE=1
if [ x"$GEN_TRACE" == "x" ]; then
    launch_cmd="sbatch"
else
    launch_cmd="HAS_TRACE=itac sbatch"
fi

if [ ! -z "$1" ]; then
    PRE_RUN="--dependency=afterany:$1"
    echo "will run after ${PRE_RUN}"
fi
#USE_RES="--reservation=fli5"
unset USE_RES # do not use reservation
# first job - no dependencies
CaseName="scripts/stampede2/scaling_exp/lbm_mpiio"

if [ x"$GEN_TRACE" == "x" ]; then
    echo "no trace 100 steps!"
    jid1=$(${launch_cmd} ${USE_RES}  ${PRE_RUN} ${CaseName}/68vs34.job|awk '{print $NF}')

    jid2=$(${launch_cmd} ${USE_RES} --dependency=afterany:$jid1 ${CaseName}/136vs68.job|awk '{print $NF}')
   

    jid3=$(${launch_cmd} ${USE_RES} --dependency=afterany:$jid2 ${CaseName}/272vs136.job|awk '{print $NF}')

    jid4=$(${launch_cmd} ${USE_RES} --dependency=afterany:$jid3 ${CaseName}/544vs272.job|awk '{print $NF}')

    jid5=$(${launch_cmd} ${USE_RES} --dependency=afterany:$jid4 ${CaseName}/1088vs544.job|awk '{print $NF}')
fi


# show dependencies in squeue output:
squeue -u $USER -o "%.8A %.4C %.10m %.20E"

