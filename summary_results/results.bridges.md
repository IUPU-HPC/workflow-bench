## April 11
[rerun all perf comp after reorganize from stampede]:
```
2781214  896    123200M                      native dspace failed
 2781215  896    123200M     afterany:2781214  native dimes 114
 2781216  896    123200M     afterany:2781215 adios_dspaces 173s
 2781217  896    123200M     afterany:2781216 adios_dimes 148s
 2781218  672    123200M     afterany:2781217  mpiio 107(aggregator)
 2781219  672    123200M     afterany:2781218a flexpath  95s
 2781220  896    123200M     afterany:2781219  fixed
 2781221  448    123200M     afterany:2781220 mpiio

```
## April 5
[rerun experiments with MVAPICH (do not load intel module) #1]:
native dspaces 158, adios-dspaces 196s, adios-dimes;170: almost the same
```
2739421        RM native_d     fli5 PD       0:00     32 (Priority)
2739634        RM native_d     fli5 PD       0:00     32 (Dependency) 2739422 failed
2739423        RM adios_ds     fli5 PD       0:00     32 (Dependency)
2739424        RM adios_di     fli5 PD       0:00     32 (Dependency)
2739425        RM    mpiio     fli5 PD       0:00     24 (Dependency)
2739426        RM adios_fl     fli5 PD       0:00     24 (Dependency)
2739427        RM decaf_lb     fli5 PD       0:00     32 (Dependency)
2739428        RM sim_only     fli5 PD       0:00     16 (Dependency)
```

## April 2
performance experiments are launched by me, while collected by Yuankun.
Use module load intel
[repeat sim-only again removed buffer put]:
**now simulation runs faster**
```
2737055
2737057
2737058
2737059
2737060
2737061
2737062
2737063
2737064
2737065
```
[repeat sim-only]:
**simulation only has inconsistent end2end time**
conclusion: 
```
2732058
2732059
2732060
2732061
2732062
2732063
2732064
2732065
2732067
2732069
```

[trace with 1 locks, 256v128]: note:
note: **why the first three inserts happens so fast?**
```
2722422: native dimes  9.2s  **results**
2722427: native dimes  9.45s+
2722428: native dimes  9.45s+
```
[trace with 3 locks, 256v128]: 
```
2722654: native dimes 8.5s! 
2722656: native dimes 8.47
2722657: native dimes 7.2 **results**
2731865: 
```


[trace with 1 locks, 128v64]: 
```
2722256: native dimes  
2722259: native dimes 
2722289: native dimes
```
[trace with 3 locks 128v64]:
```
2721988: native dspaces  
2721994: native dspaces 
2721995: native dspaces

2722017: native dimes
2722018: native dimes
2722019: native dimes

2722020: mpiio 
2722022: mpiio 
2722023: mpiio 
```

[three locks in performance comp 10th]:
additional runs
```
2736906        RM native_d     fli5 PD       0:00     32 (Dependency) dspaces
2736908        RM native_d     fli5 PD       0:00     32 (Dependency) dimes 

```
```
 2736899  896    123200M     afterany:2722197 dspaces [2722200 failed]
 2736902  896    123200M     afterany:2722200 dimes [2722201 failed]
 2722202  896    123200M     afterany:2722201 adios-dspces
 2722203  896    123200M     afterany:2722202 adios-dimes
 2722204  672    123200M     afterany:2722203 mpiio
 2722205  672    123200M     afterany:2722204 flexpath
 2722206  896    123200M     afterany:2722205 decaf
 2722207  448    123200M     afterany:2722206 sim-only


```
[three locks in performance comp 9th]:
```
 2722190  896    123200M     afterany:2722189 dspaces
 2722191  896    123200M     afterany:2722190 dimes
 2722192  896    123200M     afterany:2722191 adios-dspaces
 2722193  896    123200M     afterany:2722192 adios-dimes
 2722194  672    123200M     afterany:2722193 mpiio
 2722195  672    123200M     afterany:2722194 flexpath
 2722196  896    123200M     afterany:2722195 decaf
 2722197  448    123200M     afterany:2722196 sim-only
```
[three locks in performance comp 8th]:
```
 2722182  896    123200M     afterany:2722181 dspaces
 2722183  896    123200M     afterany:2722182 dimes
 2722184  896    123200M     afterany:2722183 adios-dspaces
 2722185  896    123200M     afterany:2722184 adios-dimes
 2722186  672    123200M     afterany:2722185 mpiio
 2722187  672    123200M     afterany:2722186 flexpath
 2722188  896    123200M     afterany:2722187 decaf
 2722189  448    123200M     afterany:2722188 sim-only

```

[three locks in performance comp 7th]:
```
 2722174  896    123200M     afterany:2722169 dspaces
 2722175  896    123200M     afterany:2722174 dimes
 2722592  896    123200M     afterany:2722175 adios-dspaces [2722176 failed]
 2722177  896    123200M     afterany:2722176 adios-dimes
 2722178  672    123200M     afterany:2722177 mpiio
 2722179  672    123200M     afterany:2722178 flexpath
 2722180  896    123200M     afterany:2722179 decaf
 2722181  448    123200M     afterany:2722180 sim-only

```
[three locks in performance comp 6th]:
```
 2722162  896    123200M     afterany:2722158 dspaces
 2722163  896    123200M     afterany:2722162 dimes
 2722164  896    123200M     afterany:2722163 adios-dspaces
 2722165  896    123200M     afterany:2722164 adios-dimes
 2722166  672    123200M     afterany:2722165 mpiio
 2722167  672    123200M     afterany:2722166 flexpath
 2722168  896    123200M     afterany:2722167 decaf
 2722169  448    123200M     afterany:2722168 sim-only

```

[three locks in performance comp 5th]:
```
 2722151  896    123200M     afterany:2722149 dspaces
 2722152  896    123200M     afterany:2722151 dimes
 2722153  896    123200M     afterany:2722152 adios-dspaces
 2722154  896    123200M     afterany:2722153 adios-dimes
 2722155  672    123200M     afterany:2722154 mpiio
 2722156  672    123200M     afterany:2722155 flexpath
 2722157  896    123200M     afterany:2722156 decaf
 2722158  448    123200M     afterany:2722157 sim-only

```

[three locks in performance comperison 4st]:
```
 2722142  896    123200M                      dspaces
 2722143  896    123200M     afterany:2722142 dimes
 2722144  896    123200M     afterany:2722143 adios_dspaces
 2722145  896    123200M     afterany:2722144 adios_dimes
 2722146  672    123200M     afterany:2722145 mpiio
 2722147  672    123200M     afterany:2722146 adios_flexpath
 2722148  896    123200M     afterany:2722147 decaf
 2722149  448    123200M     afterany:2722148 sim-only
```


[mpiio is not stable, not run multi times]:
```
2720445        RM    mpiio     fli5 PD       0:00     24 (Dependency)
2720446        RM    mpiio     fli5 PD       0:00     24 (Dependency)
2720447        RM    mpiio     fli5 PD       0:00     24 (Dependency)
2720449        RM    mpiio     fli5 PD       0:00     24 (Dependency)
2720451        RM    mpiio     fli5 PD       0:00     24 (Dependency)
2720452        RM    mpiio     fli5 PD       0:00     24 (Dependency)
2720454        RM    mpiio     fli5 PD       0:00     24 (Dependency)
2720456        RM    mpiio     fli5 PD       0:00     24 (Dependency)

```
[three locks in performance comperison 1st]:
```
  JOBID CPUS MIN_MEMORY           DEPENDENCY
 2719621  896    123200M     dspaces/           dspaces     2714966failed
 2714967  896    123200M     afterany:2714966   dimes ok
 2714968  896    123200M     afterany:2714967   adios_dspaces
 2714969  896    123200M     afterany:2714968   adios_dimes
 2714977  672    123200M     afterany:2714969   adios_mpiio
 2714979  672    123200M     afterany:2714977   adios_flexpath
 2719656  decaf 
 2714980  448    123200M     afterany:2714979   simonly
```
[run 2st]
```
 2719700  896    123200M     afterany:2719656 dspaces
 2719830  896    123200M     afterany:2719700 dimes 2719701failed
 2719702  896    123200M     afterany:2719701 adios_dspaces
 2719703  896    123200M     afterany:2719702 adios_dimes
 2719704  672    123200M     afterany:2719703 adios_mpiio
 2719705  672    123200M     afterany:2719704 adios_flexpath
 2719706  896    123200M     afterany:2719705 decaf [WAITING]
 2719707  448    123200M     afterany:2719706 simonly

```
[run 3st]
```
2719797  896    123200M     afterany:2719707   dspaces 
 2719798  896    123200M     afterany:2719797  dimes
 2719799  896    123200M     afterany:2719798  adios_dspaces
 2719800  896    123200M     afterany:2719799  adios_dimes
 2719801  672    123200M     afterany:2719800  adios_mpiio
 2719802  672    123200M     afterany:2719801  adios_flexpath
 2719803  896    123200M     afterany:2719802 decaf
 2719804  448    123200M     afterany:2719803 sim-only
```



[JOBS for trace 256v128 with 3locks whenever possible]: **RESULTS**
1. 2698956: **WAIT** 27.5s
    * mpiio 
2. 2698960: **WAIT**
    native dimes : 7.4+4 = 11.4s
3. 2698962: **WAIT**
    native dspaces 10.94+5s = 15.94s

[JOBS for trace 256v128 with 3locks whenever possible]: **RESULTS**
1. native dimes 
2. native dspaces


[results]:
----------------------------------------------------
* 2686038: **result**
     dimes end2ed time 100 steps using 3locks: 100s
* 2685827: **result**
     dimes end2ed time 100 steps using 1locks: 102s

## Mar 31
[Result]:
1. bridges\_64\_dspaces\_3lock\_marked.png:
    3 lock produce combined with consumer: seems like consumer is slower than expected. produce only throw data into  buffer. consumer need time to consumer it.(consumer is the bound of overall end to end time)
    [to check]: what is lock_on_read do: check data is ready?
[JOBS]:

1. 2679149
    mpiio 64v32: no trace(137s intel mpi)

1. 2679209
    mpiio 64v32: with trace **WAITING** (adios operation not marked)
        there is a "MPI_Broadcast"
* above are mpiio:


-------------------------------------------------------------
2683164
    native dspaces 64v32(single lock)(130s with impi)

2683434
    native dspaces 64v32(single lock with 16 server procs in equal number of nodes)(135 s with impi)

2679467:
    native dspaces 64v32(3 lock)  , slice size printed(ans: they are the same!)

2685481: **results**
    native dimes 64v32(3 lock) using set group , 7s 
2685636: **results**
    native dimes 64v32(1 lock) using set group , 10s
2679064:[results?]
    native dspaces 64v32(3 lock) 
2678785:
    native dspaces 64v32 with 16 server procs in each node **WAITING**
    
* below are native dspaces/dimes:
1. 2683065
    dspaces 64v32, 1 lock with 16 server procs/node
    
1. 2674632
    native dspaces 256v128(1 lock) with itac **WAITING**
1. 2674759
    mpiio 64v32(1 lock) with itac **ERROR**
        what:undefined symbol: _ZTVN10__cxxabiv117__class_type_infoE**
        why: link to faulse mpi library

1. 2675280
    native dimes 64v32(1 lock) with itac
1. 2676682
    native dimes 64v32(3 lock) with itac // same pattern, receive is slower **ERR**
    cmd: 
        ```
        less /pylon5/ac561jp/fli5/data_broker_adios/2676682/results/consumer.log |grep  '\[31\]'|less
        ```
    error:
        ```
        [31] DEBUG get_common_buffer:get the read lock atom_lock_t_2 for step 8
        [31] dart_rdma_process_ibv_cq(): wc.status (5).
        [31] 'dart_rdma_process_ibv_cq()': failed with -5.
        [31] dart_rdma_process_ibv_cq(): wc.status (5).
        [31] 'dart_rdma_process_ibv_cq()': failed with -5.
        [31] 'all_fetch_done()': failed with -1.
        [31] 'dimes_fetch_data()': failed with -1.
        [31] dart_rdma_delete_read_tran(): read tran with id= 17 not complete!
        [31] dart_rdma_delete_read_tran(): read tran with id= 16 not complete!
        [31] 'dimes_obj_get()': failed with -1.
        [31] 'dimes_client_get()': failed with -1.
        [31] DEBUG get_common_buffer:try to unlock the read lock atom_lock_t_2 for step 8
        [31] DEBUG get_common_buffer:release the read lock atom_lock_t_2 for step 8 
        [31] DEBUG get_common_buffer:get varaible atom err in step 8 ,  error number -1 
        ```
    reason: put_sync_all?


1. 2675334
    native dspacs 64v32(1 lock) with itac 
1. 2675679
    native dspacs 64v32(3 lock) with itac // bounded by consumer!
1. 2675779
    native dspacs 64v32(10 lock) with itac // still bounded by consumer
1. 2675373
    native dspacs 64v32(1 lock) with itac, [results, clear]

1. 2674770
    flexpath 64v32 with itac **WAITING** 
    in this earlier version adios is not itac-traced


1. 2673834
    native dspaces 64v32(1 lock) with itac
        put function is delayed in processes other than proc 0, see bridges_64_dspaces_1lock_prod.png
        there is a long "MPIBarrier" time, **TODO**I need to wrap DSPACE_function with itac
1. 2671247
    native dspaces 64v32(1 lock) with itac **server path incorrect**
above use refactorized lbm
--------------------------------------------------
## Mar 30
[JOBS]:
-----------------------------------------------
* summary in Per\_comp\_xp\_data/ds-2lock tab
1. 2668643
    native dspaces 32v16(2 lock)  **ERROR** (crashes)
1. 2668570
    native dspaces 64v32(1 lock)
1. 2668521
    native dspaces 64v32(2 lock)
1. 2668717
    native dspaces 128v64(1 lock) 
1. 2668725
    native dspaces 128v64(1 lock) 
1. 2668728
    native dspaces 128v64(1 lock)
1. 2668666
    native dspaces 128v64(2 lock)
1. 2668703
    native dspaces 128v64(2 lock) 

1. 2668515
    native dspaces 256v128(1 lock) **175.8**
1. 2668743
    native dspaces 256v128(1 lock) **WAIT**
1. 2668584
    native dspaces 256v128(2 lock) **error**
1. 2668600
    native dspaces 256v128(2 lock) **ERROR** (rpc connection rejected)
1. 2668609
    native dspaces 256v128(2 lock) **FASTER!**
1. 2668688
    native dspaces 256v128(2 lock) **FASTER!**
1. 2668512
1. 2668512
    native dpspaces 8v4(8v4 1 lock)
1. 2668629
    native dspaces 8v4(2 lock)
------------------------------------------------
1. 2667696
    native dpsaces 3 consumers are not up
1. 2667672
    native dspaces: 32v16, one consumer is not up!
1. 2667425:
    dspaces with 2 locks
    while dimes server is in the trace
1. 2664216:
    dspaces using samelock

1. 2663284:
    native dspaces using same lock
## Mar 29
[todo]: put ds_max_version/use_one_block in config.h 
[JOBS]:
1. 2662941:
    dspaces using only 3 version
1. 2661466:
    dspaces using the config, err
1. 2660781
    setting: max_version =10, use %10 as lockname
1. 2660718
    found: also remove the put_sync_all for multi-locks:
    how to fix: now no error, but dspaces servers take forever to initialize
1. 2660303
    multi-version also added in dspaces.conf
1. 2659686
   **failed**(also confirmed in 2659948) : 256v128 with  native_dimes with multi locks, failed with
    reason: 
            sync_ok = dimes_put_sync_all();
1. 2658888:
256v128 with  native_dimes, t2s= 140.6s
1. 2657187:
256v128 adios\_dimes, t2s= 173.8s

## Jan 18
JOBS:
    2209189[results]
        sim_only with trace

    2209061[results]:
         flexpath with trace 32
        trace not added

    2208619
        lBM_DECAF trace
        trace also show P41 and P55 runs very slow

    2208516[results]
        lbm_32_sim_only

above switch to intel compiler/mpi
--------------------------------------------------------------

## Jan 10
[notes]: seems like 8v4, 256v128 works fine but 32v16 are not

commit  3cd150bf:
    2169859
        256v128 dimes

in commit eee3f8ccf:
    2168533
        256v128 dimes
            fine
    2168505/2168512
        32v16 with 16 server procs
        producer Reading from remote process' memory failed. Disabling CMA support
    2168483/2168521
        32v16 with 4 server procs, crashed

    2168478/2168568
        8v4 dimes
            works
    2168448
        32v16 dimes
             server crashed
2168162
    256v128 again, server crashed
2167732
    256v128 dimes rerun, 
    failed r052.pvt.bridges.psc.edu.14226run_lbm: Reading from remote process' memory failed. Disabling CMA support
## Jan 9

2162794
    no trace decaf, not ok
    [31] r051.pvt.bridges.psc.edu.2237vector_2nodes: Reading from remote process' memory failed. Disabling CMA support
2162788
    has_trace decaf, failed

2162879
    no_trace native_dimes, server crashed
2162780/2162846
    has_trace=1 native_dimes
2162776
    has_trace=1 flexpath
    fast, 16.34s
--------------------------------------------
all rebuilt above(build and build_tau)
2162667
    has_trace=1, now use one single env variable
2160249
    HAS_TRACE=1 sbatch scripts/bridges/32v16/decaf.job
    trace failed
2160246
    sbatch scripts/bridges/32v16/decaf.job
     can run without has_tau
2160222
    with traces
2160103
    256v128 not work anymore?, stoped at 1 step
    configuration files not correct
    
2160088
    32v16 decaf with traces in bridges
## Jan 8
JOBS

2157003
    bridges 256v128, end2end time 86.36

2156965
    adios_dimes 248s

2156993

    decaf 32v12v16, 12 link procs
    

2156990
    decaf add MV2 settings 32v8v16,
    end2end 82.3s
    
2156984
    decaf 32v4v16, 4 link procs, 89.4s

2156977
    decaf 32v8v16, 8 link procs
    end2end time 86.9

2156969
    decaf 32v24v16, 24 link procs
    end2end 93.8
2156491
    decaf 16 link procs, 32v16v16
    lbm 44.1~58.9 anlysis 41.6~82.7; stream 1.4~22.8, end2end 95.5

## Jan 4
Jobs
2136279
    256v128 nmoments 3, flexpath, analysis time 29.7~44.2
2136252(I need to compare with 2098326)
    256v128, noments 4, flexpath, analysis time 50~80.5
## Dec 29
#   use nmonent=3
fli5@br005:~/Workspaces/General_Data_Broker/lbm_adiossqueue -u $USER
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
           2120864        RM native_d     fli5 PD       0:00     32 (Priority)
           2120865        RM native_d     fli5 PD       0:00     32 (Dependency)
           2120866        RM adios_ds     fli5 PD       0:00     32 (Dependency)
           2120867        RM adios_di     fli5 PD       0:00     32 (Dependency)
           2120868        RM    mpiio     fli5 PD       0:00     24 (Dependency)
           2120869        RM adios_fl     fli5 PD       0:00     24 (Dependency)
           2120870        RM sim_only     fli5 PD       0:00     16 (Dependency)

## Dec 23
JOBS
    use nmonent=3 and use max time as sim and lbm time
            JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
           2098510(469)        RM native_d     fli5 PD       0:00     32 (Priority)
           2098521(470)        RM native_d     fli5 PD       0:00     32 (Dependency)
           2098524(471)       RM adios_ds     fli5 PD       0:00     32 (Dependency)
           2098472(failed)       RM adios_di     fli5 PD       0:00     32 (Dependency)
           2098473(r330)        RM    mpiio     fli5 PD       0:00     24 (Dependency)
           2098474        RM adios_fl     fli5 PD       0:00     24 (Dependency)
           2098475        RM sim_only     fli5 PD       0:00     16 (Dependency)

    2098326
        adios Flexpath
            lbm:41.5-52.3 avg 45.2
            analysis 47.9-78.9 
    2098321
        native dimes
            lbm: 40.13-43.76
            analy:48.5-78.9 avg 
    2098247
        analysis time of each procs
        lbm:
        max:
        min:

    analysis:
        min 50.1: 
        max:78.9
rereproduce the results

           2094223        RM native_d     fli5 PD       0:00     32 (Resources)
           2094224        RM native_d     fli5 PD       0:00     32 (Dependency)
           2094225        RM adios_ds     fli5 PD       0:00     32 (Dependency)
           2094226        RM adios_di     fli5 PD       0:00     32 (Dependency)
           2094227        RM    mpiio     fli5 PD       0:00     24 (Dependency)
           2094228        RM adios_fl     fli5 PD       0:00     24 (Dependency)
           2094229        RM sim_only     fli5 PD       0:00     16 (Dependency)

## Dec 20
    10 steps
    2080510 flexpath 8v4 8.9s
        flexpath  
    2082464 flexpath 24v12 15.7s
    2082476 flexpath 12v
256v128
5@br005:~/Workspaces/General_Data_Broker/lbm_adiossqueue -u $USER (nmoments =4)
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
           2080107        RM native_d     fli5 PD       0:00     32 (Resources), works
           2080108        RM native_d     fli5 PD       0:00     32 (Dependency)
           2080109        RM adios_ds     fli5 PD       0:00     32 (Dependency)
           2080110        RM adios_di     fli5 PD       0:00     32 (Dependency)
           2080111        RM    mpiio     fli5 PD       0:00     24 (Dependency)
           2080112        RM adios_fl     fli5 PD       0:00     24 (Dependency)
           2080113        RM sim_only     fli5 PD       0:00     16 (Dependency)

## Dec 18

512v256(srun)
@br005:~/Workspaces/General_Data_Broker/lbm_adiossqueue -u $USER
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
           2076355        RM native_d     fli5 PD       0:00     64 (Priority)
           2076356        RM native_d     fli5 PD       0:00     64 (Dependency)
           2076357        RM adios_ds     fli5 PD       0:00     64 (Dependency)
           2076358        RM adios_di     fli5 PD       0:00     64 (Dependency)
           2076359        RM    mpiio     fli5 PD       0:00     48 (Dependency)
           2076360        RM adios_fl     fli5 PD       0:00     48 (Dependency)
           2076361        RM sim_only     fli5 PD       0:00     32 (Dependency)

## Dec 14
Relaunch with fixing analysis
fli5@br005:~/Workspaces/General_Data_Broker/lbm_adiossqueue -u $USER
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
           2065830        RM native_d     fli5 PD       0:00     32 (None)
           2064053        RM native_d     fli5 PD       0:00     32 (Dependency)
           2064054        RM adios_ds     fli5 PD       0:00     32 (Dependency)
           2064055        RM adios_di     fli5 PD       0:00     32 (Dependency)
           2064056        RM    mpiio     fli5 PD       0:00     24 (Dependency)
           2067366        RM adios_fl     fli5 PD       0:00     24 (Dependency)
           2064058        RM sim_only     fli5 PD       0:00     16 (Dependency)


## Dec 13
Jobs
    2058252
        flexpath 64v32 in 6 nodes, with remora
        all see increasing memory usage
## Dec 12
#   need to check memory usage
#       64v32
    2056461
        flexpath

    2056462
        sim-only

## Dec 1
perhaps a problem with slurm?
    https://www.mail-archive.com/slurm-dev@schedmd.com/msg09223.html
tried to use 
    run: Warning: can't honor --ntasks-per-node set to 28 which doesn't match the requested tasks 32 with the number of requested nodes 32. Ignoring --ntasks-per-node 
2008410


ds_test 512v256-degbug

#### jobs submitted(512v256)
                  RM native_d     fli5 PD       0:00     32 (Priority), 
                    (2008384, remove --nnumtask, still error)
                    (2008355,srun warning )
           2008356        RM native_d     fli5 PD       0:00     32 (Dependency)
           2008357        RM adios_ds     fli5 PD       0:00     32 (Dependency)
           2008358        RM adios_di     fli5 PD       0:00     32 (Dependency)
           2008359        RM    mpiio     fli5 PD       0:00     24 (Dependency), works
           2008360        RM adios_fl     fli5 PD       0:00     24 (Dependency), works
           2008361        RM sim_only     fli5 PD       0:00     16 (Dependency), works



#### dspaces/dimes 128v64
           2008140        RM native_d     fli5 PD       0:00     16 (Priority), works
           2008141        RM native_d     fli5 PD       0:00     16 (Dependency), works
           2008142        RM adios_ds     fli5 PD       0:00     16 (Dependency), works
           2008165        RM adios_di     fli5 PD       0:00     16 (Dependency), works, (serv crash 2008143)
           2008144        RM    mpiio     fli5 PD       0:00     12 (Dependency) , works,
           2008145        RM adios_fl     fli5 PD       0:00     12 (Dependency), works
           2008146        RM sim_only     fli5 PD       0:00      8 (Dependency), works


dspaces/dimes  64v32 using  hash2
    2008071 dspaces, works,(server crashed: 2008051)
    2008053 dimes, works
    2008054 adios/dspaces, works
    2008072 adios/dimes,works (server crashed: 2008055)
    2008169 mpiio
    2008170 adios_flexpath
    2008171 sim only

#### jobs submitted(256v512)
           2008034        RM native_d     fli5 PD       0:00     32 (Priority),works
           2008194        RM native_d     fli5 PD       0:00     32 (Dependency)works, (serv crash 2008035)
           2008036        RM adios_ds     fli5 PD       0:00     32 (Dependency), works
           2008037        RM adios_di     fli5 PD       0:00     32 (Dependency), works
           2008038        RM    mpiio     fli5 PD       0:00     24 (Dependency), works
           2008039        RM adios_fl     fli5 PD       0:00     24 (Dependency), works
           2008040        RM sim_only     fli5 PD       0:00     16 (Dependency), works


    

## Nov 30
#### jobs submitted 64 nodes(512v256), not run, all canceled, later rerun using reservation.
    use dependency list
           2008346        RM native_d     fli5 PD       0:00     64 (Priority), 2006967,producer srun warning (canceled)
           2008347        RM native_d     fli5 PD       0:00     64 (Dependency) (2008968,canceled)
           2006969        RM adios_ds     fli5 PD       0:00     64 (Dependency)
           2006970        RM adios_di     fli5 PD       0:00     64 (Dependency)
           2006971        RM    mpiio     fli5 PD       0:00     48 (Dependency)
           2006972        RM adios_fl     fli5 PD       0:00     48 (Dependency)
           2006973        RM sim_only     fli5 PD       0:00     32 (Dependency)

a job left from dspaces_debug branch
    2005318
        512v256 ds_test
        Warning: can't honor --ntasks-per-node set to 28 which doesn't match the requested tasks 32 with the number of requested nodes 32, same as 2004217

    2005299
        256v128 ds_test


## Nov 28
#### jobs
 2000405
    * 64v32
        24840 max pages 
 2000326,
    * 28v14, give more time, still seg fault
    * 2000398, also tried 32v16, using 4 server procs, no luck
    * 2000428, 32v16, return 11

 2000282
    * 28v14
        only 2 server instances, timeout with segfault
    
 2000099
    * this is larger experiment, 196v98
        memory limitation: dspaces init alone uses all memory

    fli5@br005:~/Workspaces/General_Data_Broker/lbm_adiossacct -o JobID,ReqMem,MaxVMSize,MaxRSS,MaxRSSTask,State,NodeList,NNodes,MaxPages,AveVMSize,AvePages,AveRss -j 2000099
           JobID     ReqMem  MaxVMSize     MaxRSS MaxRSSTask      State        NodeList   NNodes MaxPages  AveVMSize   AvePages     AveRSS
    ------------ ---------- ---------- ---------- ---------- ---------- --------------- -------- -------- ---------- ---------- ----------
    2000099        123200Mn                                  CANCELLED+ r[121,127,129,+       28
    2000099.bat+   123200Mn   2769260K     26464K          0  CANCELLED            r121        1      11K   2769260K        11K     26464K
    2000099.ext+   123200Mn    157860K      1084K         24  COMPLETED r[121,127,129,+       28       4K    107892K      1.82K    584.14K
    2000099.0      123200Mn  85040108K  84322920K          6     FAILED r[121,127,129,+        7      64K   6890900K     58.57K 6173022.8+
    2000099.1      123200Mn 131367252K 127289904K          3     FAILED r[667,669-672,+        7     505K 108934906+       216K 105393809+
    2000099.2      123200Mn 131131520K 127176972K          9 CANCELLED+ r[159,167,175,+       14     263K 87040152.+    170.36K  83697796K

    * even with 64v32, a lot page fault happens:

    fli5@br005:~/Workspaces/General_Data_Broker/lbm_adiossacct -o JobID,ReqMem,MaxVMSize,MaxRSS,MaxRSSTask,State,NodeList,NNodes,MaxPages -j 2000081
           JobID     ReqMem  MaxVMSize     MaxRSS MaxRSSTask      State        NodeList   NNodes MaxPages 
    ------------ ---------- ---------- ---------- ---------- ---------- --------------- -------- -------- 
    2000081        123200Mn                                   COMPLETED r[037,040,045,+        8          
    2000081.bat+   123200Mn   1437220K     25504K          0  COMPLETED            r037        1      22K 
    2000081.ext+   123200Mn    158080K      1076K          0  COMPLETED r[037,040,045,+        8       4K 
    2000081.0      123200Mn  27237520K  26461676K          0  COMPLETED      r[037,040]        2      67K 
    2000081.1      123200Mn 105285972K 101686660K          0  COMPLETED r[045,051,054-+        4     166K 
    2000081.2      123200Mn 105270000K 101683368K          1  COMPLETED      r[057,060]        2     153K 


 2000081
    ** previously its correct, simulation starts is not producer starts(402s contains 190s )
    
 2000002
    relaunch 64v32 after module load intel in launching login node
        not compatible, should load intel  then mvapich
 1999830   
    relaunch 64v32
        402s, previously intel module is loaded
        diff results/1999830.out  results/1879747.out

## Nov 7
 1940009
    relaunch native dsaces with 96v48
 1941004
    relaunch native dspaces with 64v32
## Oct 20
    1878136
        relaunch dimes tau without tcp,

    1878061
        dimes with full traces, this is with I_MPI_FABRIC = tcp

     /pylon5/cc4s86p/fli5/data_broker_adios/1878061/trace/app1/merge.err
        tau2slog2 error:
                Reached end of trace file.
        Getting YMap, Maxnode: 7, Maxthread: 1
        java.lang.IllegalArgumentException: Comparison method violates its general contract!
                at java.util.TimSort.mergeLo(TimSort.java:777)
                at java.util.TimSort.mergeAt(TimSort.java:514)
                at java.util.TimSort.mergeForceCollapse(TimSort.java:457)
                at java.util.TimSort.sort(TimSort.java:254)
                at java.util.Arrays.sort(Arrays.java:1438)
                at base.drawable.Shadow.writeObject(Shadow.java:477)
                at logformat.slog2.BufForShadows.writeObject(BufForShadows.java:297)
                at logformat.slog2.output.TreeNode.writeObject(TreeNode.java:259)
                at logformat.slog2.output.OutputLog.writeTreeNode(OutputLog.java:126)
                at logformat.slog2.output.TreeTrunk.flushToFile(TreeTrunk.java:160)
                at edu.uoregon.tau.Tau2Slog2.main(Tau2Slog2.java:202)
        Exception in thread "main" java.lang.NullPointerException
                at logformat.slog2.LineIDMapList.writeObject(LineIDMapList.java:33)
                at logformat.slog2.output.OutputLog.writeFilePart(OutputLog.java:163)
                at logformat.slog2.output.OutputLog.writeLineIDMapList(OutputLog.java:192)
                at edu.uoregon.tau.Tau2Slog2.main(Tau2Slog2.java:213)

--------------------------------------------------
adios not instructed, dspaces instructed
---------------------------------------------

    1877032
       28v14 tcp
        'ds_boot_master()': all the peer are registered.44 42
        'ds_alloc()': init ok.
        rdma_resolve_addr -1 in rpc_connect.
        'rpc_connect()': failed with -1.

===================================================================================

    1876982
        28vs 14 native dspaces with shm:dapl
        ds_boot now sucess 
traces
    1876980
        dimes with traces, 8vs4
traces
    1876896
        flexpath with traces, 8v4
    

## Oct 14
JOBS
    1861851
        8vs4 dimes
    1861836
        8vs4 dspaces
    
    1861636
        8vs4 flexpath with ib0
    1861460
        server set to 2, rerun 28vs14

    1854240, intel mvapich


    1854126
    1853970,1853977
    1853466
        print by rank
    1853464
        1 server?
        
    1853449
        rerun dataspaces_gcc with dimes
    1853445
        rerun dataspaces_gcc with ds_test
    1853439
        run with dataspaces_gcc,, without cflags using gcc4.8 with impi

---------------------------
    this is using dsroot_mvapich_ by mistake
    1853958& 1853955
        export I_MPI, and use mpirun
        
    1853938
        run applications
    1853926
        add export=ALL
    1853483
        use 1.6.1 version, no luck
    1853365
        check why peer ip are different! in gcc/icc, I can try higher version of gcc!
        rerun dimes, rpc_connect(Connection Rejected peer# 0 (0.0.0.0)  to peer# 0 (0.0.0.0))
        1853449 with dataspace_gcc, (Connection Rejected peer# 0 (10.4.119.58)  to peer# 0 (10.4.119.58)., reproduce with 1853525, 1853546)
        1853543
    1853358
        dimes works
    1853290
        rerun ds-test.job, rpc_connect, random err?
    interactive jobs:
        rpc_connect error
    1853268
        relaunch ds-test.job
        works as usual
## Oct 12
JOBS
    1850818
        use mpiexec.mpirun_rsh
    interactive jobs: excede job mem slurmstepd: 
    error: Step 1849005.2 exceeded memory limit (4525508 > 4505600), being killed
    1848728
        change bin_dirtory to dataspaceroot_gnu_nvapich
    1848719
        disable mv_cpu_affinity and show binding details 
    1848678
        use gcc/mvapich intead, cpu affinity erro, 
    1848652
        ds_test with 28vs14, rpc connection error, use mvapich/gnu?, more waiting time
    1848615
        28vs14 with native_dspaces_nokeep, again
    to many logfiles?
    1848477
        mpiio  672vs 386 
    1848478
        flexpath 672vs386
## Oct 11
dimensions
JOBS
    1840361
        flexpath with 672vs386
    1847971
        mpiio 56vs28, 147.7s
    1847972
        flexpath 56vs28 72 steps
    
## Oct 10
JOBS: 
    1838800
        mppio with 672vs386
        330.73s, check consumer log
    1838801
        flexpath with 672vs386
    1832732
        mpiio 56vs28
            143.55s
    1832733
        flexpath
         56vs28
            5min 84step
            

------------------------meeting--------------------------------------
    1834262
        ds dim 16x16, all producer initialized, consumer none.
    1834218
        decrease dimension to 256x256, prod 0,3,12 not initialized, consumer all not init
    1834200
        use dimention=3 still same err
    1834184
        native_dspaces with 28 14, four node cannout initialize
    1834174
        dstests with 256vs128, all right
## Oct 8
    1830825(application should be built with icc), new 1834144
        native_dspaces_nokeep, 196
        cannot finish initialization
    1830826(application should be built with icc), new 1834145
        adios_dspaces_nokeep, 196
        canot finish initialization

## Oct 7
JOBS:
    cannot find evpath lib, add it to LD_LIBRARY_PATH
    fli5@br005:~/Workspaces/General_Data_Broker/lbm_adiossbatch scripts/bridges/196vs98/native_dspaces_nokeep.job
Submitted batch job 1828445
fli5@br005:~/Workspaces/General_Data_Broker/lbm_adiossbatch scripts/bridges/196vs98/adios_dspaces_nokeep.job
Submitted batch job 1828446

    
    1826779
       ds_test with 3nodes, intel compiler/mpi
    1826784 no problem: works!
        ds_test with 7 nodes, intel compiler/mpi
     
## Oct 3
    1814093
        launcher test with intel mpirun
        only 1 app has output!
    1814068
        ex3 with intel mpi/compiler
       run: Job step creation temporarily disabled, retrying
        srun: error: Unable to create job step: Job/step already completing or completed
        will keep using gnu/mvapich in bridgs
## Oct 2
JOBS  
    1812258
        lbm_dimes with 196vs98
    1812255
        lbm_dspaces_with 196vs98
    1812165
        lbm_dimes with 4 server proces
    1811963
        lbm_dspaces with 4 server procs
    
    1811831
        lbm_dimes, with dim=2 and num server proc =1, num_server_proc=1, 155.54s
    1811698
        lbm_dspaces correctly run: make dimension =2, num_server_proc=1, 230s
    1811622
        add timeout
    1810366
        type 1 lock, simulation can run, consumer error
## Oct 1
    1810195, lbm_dspaces
    1803867, revisit
      server log:obj_put_update_dht()': this should not happen, num_de == 0 ?!
## Sep 29
JOBS
    1804113
        native_dspaces with 196vs98
    1803867 adios_dataspaces,change adios_open mode to w(step 0), a(following steps)
        does this fix the blocking?-> no
    1803871
        adios_dimes, with same modifications
        73 steps
    
## Sep 28
    JOBS:
    1802199
        adios_mpiio, 196vs86,
    1802164
        adios_mpiio, 8vs4 , 72s, shorter than before.
    1801850
        adios_dspaces, err
    1801851
        adios_dimes,err
    1801798,  1802794
        nativedimes 196vs98: err
    1801744
        native_dspaces 80s
    1801747, new 1802776
        native_dimes, 63s
## Sep 27
    jobs
    1800352
        lbm_dspaces
    1800354
        lbm_dimes
    1799627
    see why adios dspaces/dimes not initialzed, else if !
## Sep 26
    Jobs
    1798513
        dimes with 100 steps, 63.4s!
    1798500, 
        evpath_mpi with infiniband ip address, see verbose log
        seems like mpirun_rsh will automatically choose infiniband,
        getent will show ipaddress 

    1796902,dimess with flushing last step , small test with 10 steps
        now raw dimes can run
## Sep 25
    rerun 8 vs 4 JOBS:
        1795474
            lbm_mpiio.job
        1795473
           raw_dimes_nokeep.job
            removew syncall , see results, 1796646
        1795472
            raw_dspaces_nokeep.job
        1795471
            lbm_dimes_nokeep.job
        1795469
            lbm_dataspaces_nokeep(4 server, single lock)
        1795468, correct
            lbm_flexpath_nokeep(4 server, single lock)
## Sep 23
    1793007
        raw dimes with 4 server procs 
    1790908
        lbm adios nokeep
## Sep 22
    using adios 1.12 and new flexpath with version tag adios-1.12, without compression
    1785704
        using socket
        194s
    
    1785702
        using enet
        303s
    
## Sep 21
	evpath_mpi
    1798300
        Sep 26, launch with mpirun_rsh
	1783440
		with nnti, with VERBOSE info
		
	1783441
		without nnti, with VERBOSE info
		
	1783426
		no ntti but with CMTransportVerbose, output shows it uses tcp/ip
		socket
	178426
		no nnti, without CMTransportVerbose, application info
	1782234
		-t nnti -v 
		same ibv_create_comp_channel
		should try nnti example
	lbm_dataspaces
	1781937, pending
		rerun with more debug info, see where is blocked.
	1781839
		still don't see the .bp file in scratch/ folder, reader cannot start
	lbm_flexpath
        1783455
            non-nnti, successufully run with verbose info
        1783450
            reorganize flexpath, and showed verbose CMTransport info of nnti
		1783281
			
		1781891
			try again if disable unset nnti
			end2end 182s.
		1781815
			export CMTransport=nnti
			consumer cannot find the bp file..
			1. it's using the same interface with dspaces, try dspaces
			2. unset nnti, try again?
## Sep 20
	evpath_mpi
		1781308
			unset CMTransport, ok, 
		1781301
			using ntti:
				ERROR [setup_request_channel:nnti_ib.cpp:3919:t18760]:
				ibv_create_comp_channel failed
				ERROR [setup_data_channel:nnti_ib.cpp:3982:t18760]:
				ibv_create_comp_channel failed

	
May 9
1125183
    300 dspaceswith maxversion 30
---------------------------------------------------------------
Mar 8
1122771
    200 with maxversion 20 again
        producer
        t_prepare:0.081731 s, t_cal 124.503945 s,t_buffer = 0.791463, t_write 52.432181 s, t_put 7.075397 s
        consumer
        stat:time for read 130.041873 s; time for ds_get 98.007580 s; time for analyst 57.226841 s
1122749
    300, also change maxsteps to 30
    wait for results
    error 11 again
    
    
1122744
    300, also change maxsteps to 30
    server is no up
    
1122631
    300 
    producer wait at:
        , time 1494262470.103147

         ** prepare to put, ndim = 2

         ** prepare to put, ndim = 2

         ** prepare to put, ndim = 2

         ** prepare to put, ndim = 2
    consumer wait at
        **rank 11: try to acquired the read lock atom_lock_p_11_t_19 for step 299

1122445
    200 steps consumer and producer finish same time
    
1122430
    print proc info for error 11
    
1122384
    error : get varaible atom err,  error number -11
        EAGAIN, non-blocking io, data not ready, try again later 
    try
    print error process and step, check whether data is prepared in producer side
1122277
    again in raw dspaces
    'dsgrpc_obj_get()': obj_descriptor = {
        .name = atom,
        .owner = 0,
        .version = 292
        .bb = {lb = {0, 6291456}, ub = {1, 7340031}}
}

1122144
    more info for raw dspaces
    connection refused in consumer
1121965
    raw dspaces with 16 server processes
    298 steps all finisheed fast, but cannot finish the final steps
    rank 2 is too slow!
        rank 1: Step 299 moments calculated, t_read 412.031851, t_advance 0.499659, t_analy 0.391790
        rank 6: Step 299 moments calculated, t_read 426.803720, t_advance 0.730462, t_analy 0.239048
        rank 0: Step 299 moments calculated, t_read 422.268981, t_advance 0.545566, t_analy 0.409425
        rank 9: Step 299 moments calculated, t_read 420.500582, t_advance 0.715367, t_analy 0.386848
        rank 2: Step 280 moments calculated, t_read 0.544884, t_advance 0.336426, t_analy 0.391006

    calculation took more time?
    the last step in producer takes too much time
    t_prepare:0.085854 s, t_cal 505.359575 s,t_buffer = 1.116890, t_write 197.967837 s, t_put 10.882837 s

May 7
1120228
    dimes
        only sync when step >0
    reader is faster, but can only run 20 steps(error when sync)
1120169
    rerun without sleep in consumer
    error, server is down
1120045
    sleep 3s in rank 0 of consumer
    more details of raw dspaces
1119022
    add sleep in before consumer  lock,
        add comm_free
        whether get read lock in the same time
        now rank 0 gets the lock later
    so why its so slow?
May 6
Note: use small granularity
1118595
    use smaller grnularity also use the splited communicator
    wait for results:
       producer get lock aynchronously
       reader still get lock in the same time


1118220
    dimes with small granularity& sync each 20 steps
    producer error in step 20
    consumer error in step 10

1118179
    dspaces with small granularity
    still very slow, readers seems to get the read lock in the same time
    change the communicator in lock routines


----------------------------------------------------------------------------------------
May 5
Note: timer added in now averaged
1116695
    24-12 300 version
    dspaces locks are removed
    ds_put fine, dspaces get error(data not avaible)
    try: after two producer process done, the mapped one consumer process get the lock

1115790
    24-12 dimes 20 max version
    wait resuts
    can run for 64step,(64*16=1024), not enough spaces in dimes
    solution: call sync



1115698
    24-12 300 mpiio with read timer
    wait results
    sum of breakdown is much less then time gap tetween producer and consumer
--------------------------------------------------------------------------------
May 4
1114840
    24-12 300 dimes with read timer
    with 8 sp in 4 nodes
    mode 20 in ds_adaptor
    wait for results
        server rpc connection error(node 73), so one server is not up

1114745
    24-12 300 mpiio with read timer
    wait for results
1114063
    24:12 dspaces with 16sp in 4 server node
    use 20 maxversion, lockname is associated with mode 20
    same end2end time, but only 20 max_version used in dspaces
        producer time increased(blocked when dspaces_lock_on_write)

1113082
    24:12 mpiio in 300 steps, 
    923s e2e time, 
    there is a pause in consumer at No.278 step 
1113054
    24:12 mpiio in 100 steps, consumer and producer finishs almost at the same time
    128s e2e time
    
    
1112967
    24:12 dspaces with 16 sp in 4 server node

1112935
    24:12 mpiio in 300 steps
1112767
    24:12 
    raw spaces with 8 sp in 2 server node
    900+ end2end
    
    
1112728
    24:12
    simulation only
    121s for 300 steps

    
Mar 3
1112615
    timestep changed to 300
    need more max_verion in configurations
1109252
    8 servers in two nodes
    producer
        t_prepare:0.078760 s, t_cal 31.777218 s,t_buffer = 0.369984, t_write 14.020842 s
    consumer 
        time for read 52.290949 s; time for ds_get 43.102167 s; time for analyst 37.557888 s

1108717
    8 servers in one node
    wait for results
    producer
        rank 0, t_prepare:0.072677 s, t_cal 31.705974 s,t_buffer = 0.334619, t_write 14.063485 s
    consumer
        stat:time for read 52.457892 s; time for ds_get 42.482243 s; time for analyst 36.992608 s
1108676
    four servers in one nodes
    wait for results
    producer:
        t_prepare:0.079526 s, t_cal 32.637577 s,t_buffer = 0.372480, t_write 15.397109 s
    consumer
        time for read 49.933296 s; time for ds_get 39.106010 s; time for analyst 37.426931 s
1108502
    try 1108484 again
    producer
        rank 0, t_prepare:0.076126 s, t_cal 31.894343 s,t_buffer = 0.340155, t_write 21.663085 s
    consumer
        stat:time for read 71.426228 s; time for ds_get 48.901551 s; time for analyst 37.309971 s
1108484
    configuration same as 1108421
    use 2 server processes
    note: need to roll back!
    wait for results
    producer
         is okay and even faster
    consumer
        stoped at the 47th step
    server info:
        Status (12) is not IBV_WC_SUCCESS.
        (__process_event): err (-12).
1108421
    1 server processes
    timer added in raw_dspaces version
    producer:
        rank 0, t_prepare:0.071743 s, t_cal 32.427348 s,t_buffer = 0.342315, t_write 31.190054 s
    consumer dominate the execution timer
        stat:time for read 80.504931 s; time for ds_get 54.705117 s; time for analyst 36.792386 s
May 2
1093155
    raw dimes version first submit
    wait for results
    dimes_memory_alloc(): ERROR: no sufficient RDMA memory for caching data with 16777216 bytes. Suggested fix: increase the value of '--with-dimes-rdma-buffer-size' at configuration
    default is 64M for each processes, can only 16M*4=64M, the fifth step will generate this error
1092629
    raw dspaces getting more info
    wait for results
    correct, just need to add timer to break down time
-------------------------------------------
-
1086067
    version changed to 5, cannot unlock in first reader iteration, producer is also slower

1085860
    working version of raw dspaces
    0.1~0.2s per step in writting

1085794
	remove gdimdefine functions
	global dims set to 2 in jobfile => pmi error

Q   
    gdim removed?
1084745
    only one process tried to release read lock, did others return?kh
1082998
    see what will happens if using same lock
    consumer still cannot read
    changed it back
1081962
    remove dspace_put_sync
    first serveral writes are very fast
    problem:consumer can get read lock but didn't take any action
1073688
    increase maxversion to 100
    still 5s/step
    problem:consumer can get read lock but didn't take any action
    

1072840
    dspaces is slow!
    5s/step
    maxversion =5
    problem:consumer can get read lock but didn't take any action



-------------------------------------------------------------------------------
recover:
    1. remove branch in insert_into_adios, still blocked at second step
    2. add max-buffer-size and group-size back

5bf287a8159489d335d6fccb6f0ffdbe7defd7fa works.
April 24: dspaces nokeep cannot start second step
--------------------------------------------------------------
1023888
    April 24
    queue size =30
    t_prepare:0.096793 s, t_cal 58.699383 s,t_buffer = 0.391298, t_write 67.074677 s
    stat:time for read 80.986417 s; time for advancing step 60.186810 s; time for analyst 42.728954 s
    
    
1023832
    only use queue size =100 use current
    similar to 1023483, when producer finishes, only 50 iteration are finished in consumer
1023284
    use ADIOS_LOCK_NONE for flexpath, and also use queue size =100
    writting time is  reduced but reading time and simulation time is increased
    rank 0: t_prepare:0.096157 s, t_cal 74.112131 s,t_buffer = 0.378756, t_write 18.409973 s
    consumer:
        read 95.798134 s; time for advancing step 55.317296 s; time for analyst 38.530918 s
    
    previous(1020273):
        rank 0, t_prepare:0.117190 s, t_cal 34.793658 s,t_buffer = 0.363246, t_write 48.276190 s
        time for read 31.993267 s; time for advancing step 13.858851 s; time for analyst 42.458436 s


1022954
    use ADIOS_LOCK_NONE for dataspaces, cannot start the second step
--------------------------------------------------------------------
2 vs 2
    2:2 for dataspaces
    can only run 1 step
        obj_put_update_dht()': this should not happen, num_de == 0 ?!
1020425
    2:2 for flexpath
    rank 0, t_prepare:0.100240 s, t_cal 36.241775 s,t_buffer = 0.352581, t_write 35.290532 s
1020431
    2:2 for mpiio
    rank 0, t_prepare:0.094998 s, t_cal 34.470667 s,t_buffer = 0.380254, t_write 41.995600 s

    
--------------------------------------------------------------------
2 vs 1
1020409
    2:1 for dataspacs
    much slower, write time, same as 8:4
    rank 1, t_prepare:0.090932 s, t_cal 35.855491 s,t_buffer = 0.694799, t_write 148.333942 s
1020273
    2:1 for flexpath
    t_prepare:0.117190 s, t_cal 34.793658 s,t_buffer = 0.363246, t_write 48.276190 s

1020351
    2:1 for mpiio
    rank 0, t_prepare:0.095643 s, t_cal 33.620270 s,t_buffer = 0.408753, t_write 41.847312 s


--------------------------------------------------------------------
1 vs 1
1020171
    April 20
    1 proc for producer /consumer in dimes
    rank 0, t_prepare:0.099800 s, t_cal 39.225544 s,t_buffer = 0.428297, t_write 59.117687 s
    
1019194
    April 19
    1 proc for producer /consumer in dataspaces
    rank 0, t_prepare:0.115774 s, t_cal 38.675447 s,t_buffer = 0.464524, t_write 59.304806 s
    
1019183
    April 19
    use 1 proc for producer/consumer in mpiio
    rank 0, t_prepare:0.102954 s, t_cal 29.752500 s,t_buffer = 0.337182, t_write 35.613051 s
1019177
    April 19
    use 1 proc for producer/consumer in flexpath
        writing time is much less(in each step only 0.1s+ needed instead 1s+)
        rank 0, t_prepare:0.112377 s, t_cal 37.403693 s,t_buffer = 0.418905, t_write 13.139727 s

    second try(1019213)
        rank 0, t_prepare:0.114158 s, t_cal 38.601449 s,t_buffer = 0.463431, t_write 11.460353 s


        
-------------------------------------------------------------------
1013543
    config
        export nnti
        QUEUE_SIZE=10
    
    first several iterations are very fast
    t_prepare:0.099772 s, t_cal 48.264999 s,t_buffer = 0.365479, t_write 122.166682 s
1000659
    flexpath again
    t_prepare:0.099056 s, t_cal 47.947185 s,t_buffer = 0.381423, t_write 133.391801 s
    
1000611
    dspaces nokeep 8:4 same as before, 33s cal, total 147s
1000598
    flexpath 8:4
    t_prepare:0.099268 s, t_cal 42.772855 s,t_buffer = 0.388137, t_write 149.501805 s(why calculation is longer?)
-------------------------------------------------------------------
990028
    mpiio for 768-384
989977
    1 step has writting time 10s
    2 step has 5s
    after that, each step is around 1.4s
989971
    print out the time spend in each step

985605
    2 server nodes with  8 processes
    t_prepare:0.070657 s, t_cal 33.336477 s, t_write 123.082560 s
    time for read 41.152115 s; time for advancing step 69.784354 s; time for analyst 38.104001 s
    
985462
    2 nodes with 4 server processes
    t_prepare:0.083320 s, t_cal 33.259625 s, t_write 114.416353 s(different with the experiment when run_analys is comment out!!)
    stat:time for read 31.125366 s; time for advancing step 69.925751 s; time for analyst 38.699015 s

985138
    Using 1 node with 4 server processes
    t_prepare:0.069294 s, t_cal 34.124658 s, t_write 121.832758 s
    stat:time for read 35.299027 s; time for advancing step 75.014883 s; time for analyst 38.248347 s
985141
    1 server node with 1 server process
    t_prepare:0.082188 s, t_cal 32.822827 s, t_write 147.587935 s(will decrease to 120 if disable analysis, 989763)
    stat:time for read 53.557231 s; time for advancing step 76.971237 s; time for analyst 39.008861 s

-------------------------------------------------------------------
run_analysis is commented since 982346()

##983952
##    use two nodes and 8 server procs
##    t_prepare:0.070522 s, t_cal 32.412648 s, t_write 85.629872 
##983941
##    mpiio for 192:96
##        correct
##        t_prepare:0.102406 s, t_cal 52.585197 s, t_write 188.630988 s
##983987
##    mpiio for 48:24
##    166s for 100 iterations
##
##----------------------------------------------------------------
##Dspace without keep 
##---------------------------------------------------------------
##983916
##    use two nodes and 4 server procs
##
##    t_prepare:0.072535 s, t_cal 33.617150 s, t_write 81.061058 s
##
##983887
##    Use 4 server procs in 1 node(885 for 2 procs, 889 for 8 procs)
##    producer
##        rank 0, t_prepare:0.073306 s, t_cal 32.921603 s, t_write 85.992348 s
##    consumer
##        stat:time for read 36.048645 s; time for advancing step 74.303108 s; time for analyst 0.000015 s 
##983861 
##    increase xml buffer size to 100M
##    producer
##        rank 0, t_prepare:0.072356 s, t_cal 33.428042 s, t_write 120.205607 s
##    consumer
##        stat:time for read 57.506153 s; time for advancing step 83.994528 s; time for analyst 0.000015 s
##982346
##    Producer 
##        rank 0, t_prepare:0.088599 s, t_cal 33.367076 s, t_write 119.299031 s
##    Consumer
##        stat:time for read 49.542193 s; time for advancing step 90.988737 s; time for analyst 0.000019 s
        
978592
    rank 0, t_prepare:0.071245 s, t_cal 33.226557 s, t_write 149.790138 s 
977946
    max_version =2;
    185s.

977829
    Previous using max_version=5
    now changed to 1
    April 3 12:30
    8 vs 4 
-------------------------------------
976485
    April 3 09:35
    8 vs 4 dimes w/o keep
    138s

976473
    April 3 08:59
    8 vs 4 sim_only 
    33s

876434
    April 3 08:56
    8 vs 4 dspaecs w/o keep
    179s

975029
    April 2 17:46
    8 vs 4 MPIIO
    98.8s
970196
    Mar 31 15:27
    Use -O3 can reduce running time significantly
-----------------------------------------------------------------
didn't use O3
966796
    Mar 30 15:51
    1 node for dspace servers, 48_24, max version 1
966766
    mar 30 14:44
    192 simulation procs only in 100 timesteps, 144.42s
965971
    Mar 30 13:36
    48 sim procs and 24 analysis procs with dspaces, 74 steps(increased from 41) in 5 min
    
965907
    Mar 30 12:24
    48 sim procs and 24 analysis procs with dimes, 87 steps in 5 min
    Q: does increase dspace server node help?
    
965855
    Mar 30 12:14
    48 sim procs only, 141.18s  
965780
    Mar 30 11:59
    48 sim procs and 24 analysis procs with dspaces, 41 steps in 5 min
    
965712
    Mar 30 11:37
    sim_only 121.81
965450
    Mar 30 11:06
    dimes with keep 172.6
964999
    Mar 30 10:31
    dimes with nokeep 171.40
964902
    Mar 30 10:07
    dspaces with keep 8:4, 197.65
964613
    Mar 30 00:30
    correctly get node list in bridges. continuous 100 timesteps in bridges with correct process layout
    185.69
8531205
    Mar 29
    node file fixed, now all application run in different nodes
8394708
    Mar 24
    1/1 proc correct, but most data is zero
8426008
    mar 25
    4/8for dspaces transport

8426034
    Mar 25
    4/8 for dimes transport
8439991
    Mar 25, 19:10
    use scrach for .pb file, now mpiio is okay!
8440002
    Mar 25 19;16
    if data size too large, need larger buffer to fit all data
8445129
    Mar 26 13:10
    if adding  keeping,(additional init_read_method() in reader application) reader no actions
8445202
    Mar 26 13:42
    move adios_init_read before adios_init, reader cannot stop(fixed by store errno of streaming read)
8445616
    mar 26 15:08
    keep written into same file, (mode "w")
8445921
    Mar 26 15:46
    keep only happens since second iteration

8522408
    Mar 29 09:50
    Use 
        CMD_SERVER="mpirun_rsh -hostfile $SLURM_NODEFILE -n $PROCS_SERVER ${DS_SERVER} -s $PROCS_SERVER -c $DS_CLIENT_PROCS"
        $CMD_SERVER  &> ${PBS_RESULTDIR}/server.log &
        echo "server applciation lauched: $CMD_SERVER" 
    server is launched, but doesn't generate conf file, so clinets cannot start

8522493
    Mar 29 09:57
    Use 
        # Run DataSpaces servers      
        LAUNCHER=ibrun                 
        CMD_SERVER="$LAUNCHER -hostfile $SLURM_NODEFILE -n $PROCS_SERVER ${DS_SERVER} -s $PROCS_SERVER -c $DS_CLIENT_PROCS"
        $CMD_SERVER  &> ${PBS_RESULTDIR}/server.log &
        echo "server applciation lauched: $CMD_SERVER"

    Result
        ibrun doesn't support hostfile option
        Unkown option hostfile
    To do 
        looking into ibrun scripts in /opt/sdsc/bin/ibrun


    
