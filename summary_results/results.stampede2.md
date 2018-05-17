## April 11
* mpiio with lammps
```
1097021 68v34: 281s
1097114 68v34 282s
```
* flexpath with lammps
```
1097141: long time
```

## April 8
* [mpiio with no dependency... running together]
```
   1080457  68v34
   1080476  68v34

136v68
   1080505 136v68
   1080506 136v68
   1080508 136v68

272:136:
   1080511
   1080513
   1080514
   
   (new)
    1083039
    1083044
    1083046
    1083047
    1083048
    1083050
    1083052


544:272
   1080516
   1080517
   1080518

1088v544
   1080519
   1080520
   1080522
   1082516 new)
   1082524 (new)
   1082526 (new)

2176v1088:
    1082760 (malloc error, fixed)
test:
    1085629
    1085721
stable:
    1085726 (196s)
    1085733
    1085734

4376v2176:
    1085738 (303s)
    1085740
    1085741
    1085742
    1085743

    
```

## April 6
[results]:
* 1073073:
    aggregator 17 for 136v768: 160s (instead of 500)

## April 6
[JOBS]:
* 1072677
lammps-sim-only: 220s, same as before
* 1072672
lammps with disk-io, seems very slow..
## April 3
[JOBS]:
* 1050178
    MPIIO 68v32 with Barrier 5min finishes  78 steps(slower than before)
* 1051208
    MPIIO 68v32 without Barrier 5min finishes 78 steps
[code];
flexpath\_lbm is fine 1052341.
flexpath\_lammps?
## April 2
[JOBS]:
after reorganize
* 1047966:
    lbm-mpiio ok
*  1047968
    lammps-flexpath no
    

## Jan 28
[Verify Results]:

#### 136v48 for lbm
1. 1011311 mpiio(TODO)

#### 136v48 for lammps:
1. 1080813 decaf-lammps: 136v68: 236s, ok
2. 1010792 flexpath-lammps: 136: 28min 50steps. I think for lammps I used another source tree
3.
# jan 23
 637680[results]
    flexpath 68v34 1 process per node
        46.0s
# jan 22
 flexpath 2176v1088 after change NX to uint64t
# Jan 20
627434
    flexpath_lammps 272v136
627436
    flexpath_lammps 544v272
    

-------------------------------------------------------------
starting flexpath_lammpsgenerate results

626429: error
626396: flexpath with estimated lines, "remove gathering and reduce"
626177: flexpath with itac

626008: 4362 decaf with only partial proceses
625980: [results] modualized flexpath, 63s for 10steps
# Jan 19
should also look at the funciton time
621424:[results] lammps_decaf 68, withno mpiscatter

621426:[results] lammps_decaf 1088, with mpiscatter
621486:[results] lammps_decaf 4352, load trace too slow!

start to add specific mpi funciton into trace
------------------------------------------

#

# Jan 18
regenerate trace files
620119:[results]: lbm_decaf
617308:[results]: lbm_sim_only
617503:[results]: lammps_decaf 4352 (this seems ok)


# Jan 17
613479
    [results]: lammps_decaf 4356 with trace, 50.1s
613455
    [results]: lammps_sim_only 4356 with trace, 27.0
613444
    [results]: sim_only 1088, end2end 26.6s
613116
    [result]: get the 1088 lammps trace if disable mpi trace, end2end time 28.5s for 10 steps
613048
    lbm_decaf 1088 same problem, trace file to large: due to too many mpi messages?
612886
    lammps_decaf 1088, stuck at
        [0] [0 Wed Jan 17 13:01:34 2018] Intel(R) Trace Collector INFO: "write header": done
        log shows there will be 5G trace data, but only 1.9G is filled. then just wait there
612854(compare with 612845)
    decaf_lammps with with LD_PRELOAD=VT.so, shared link
612845
    decaf_lammps wiout LD_PRELOAD., shared link
612795
    decaf_lammps in build, with incorrect .so
        only producer launched
    
612104
    did the same for decaf_lammps 
        err
612008, removed -fpic (also the library in module libraries, put mpi in the end)
    lbm_sim_only, ok
    612107 run again with removing LD_PRELOAD,  ok. 
611042 manually built of test_lbm works with static libs
    mpicc, place mpi lirary =lrt -ldl in the end
611990
    use static vt libs, lbm_decaf fault
611992
    use static vt libr, lbm_sim_only seg fault (try to manually build sim_only_lbm, see what's different)
        mpicc -trace -o test_lbm lbm_buffer.c lbm.c test_lbm.c
611931
    lbm_sim_only
611934
   lbm_decaf
---------------------------------
can be a problem of "PUT" trace id(no)
611883
    lammps_sim_only with VERBOSE-3, lammps_decaf stops at the first line
    [0] [0 Wed Jan 17 09:47:06 2018] Intel(R) Trace Collector INFO: wall clock: 1.516204e+09s - 1.516204e+09s since Epoch
    [0] [0 Wed Jan 17 09:47:06 2018] Intel(R) Trace Collector INFO: maximum number of events on the same clock tick was 4: insufficient clock resolution

611831
    lammps_decaf with VERBOSE=3
    this can be a problem: lammps_sim_only is built with lammps.a, lammps_decaf is built using lammps.so
609967
    lammps_sim_only also built with shared libs
# Jan 16 
 *609967
    lammps_only
 *609922
    lbm_decaf 68, can stop 
 *609917
    lammps now 68 cannot stop
 * 606762
    [result not checked]: lammps_sim_only 4352v2176
 * 606913
    [result]: lammps_decaf 1088v544
        failed run: 606753, timeup for traces (8mins)
    
 * 606748
    [result]: lammps_decaf 68v34
 * 606746
    [result]: lammps_sim_only 68v34
 * 606586
    [result]: trace with decaf, total end2end 5.5
        streaming time 0.11~0.68
 * 606533 
    trace with decaf: total end2end
        1. add common_library in the end of target_link_library)
        2. export LD_PRELOAD=libVT.so
 * 606383
    trace with decaf, not trace output?
        see docs/itac.md note 8
 * 606310
    [result] more detailed lbm traces
        0.072~0.544 streaming time
# jan 15
 * serial program gets trace
    see tmp/a.out
 *605578
    [results] for sim_only
 * 604068
    trace of lbm_only
 * 603317
    build with itac but not run with -trace, ok
# jan 12 
 * 594604
    self built tau: pdt need to compile with icpc?
 * 590610
    self built tau: trace fo lbm only
    
 * 590563
     now 7.3G traces
# Jan 11
 * 588209
        set both tau_select file and tau_optioln, still large traces
 * 587809
        add tau_select, and now can completedly compile with cmake 2.8
 * 587424
        lbm-only trace 68v34, 40s, trace 46M, transfered to dell desktop
 * 587326
        10 steps, stampede lbm trace, 60G in, 147s, boost too many calls?
 * 587201
        stampede lbm trace, 8min too short for 100 steps, 30+ steps trace generated, but already 40G
 * 586758
    not fully built vector2nodes, ok

# Jan 10
 * 584474
        lammps-only 4352v2176, 221s

 * JOBS:
    584131(583981 5 min too slow), again(584474)
        lammps-decaf 4352v2176  528.37
    583891
        lammps-decaf 2176v1088 297.72
    583874
        lammps-decaf 1088v544 294.54
    583865
        lammps-decaf 544v272 240.41
    583857
        LAMMPS-DECAF 272v136 232.03
    583832
        lammps-decaf 136v68 232.47
    583810
        lammps-decaf 68v34 232.08
    583056
        lammps with decaf
        
# Jan 6
570598
    lammps with decaf run with "pre no post no"
    225.3
    
570591
    test_lammps(lammps_only) now run with "pre no post no"
    225s
570514
    no post and pre,waltime 3:45, the same
570505 
    add pre no and post yes, walltime 3:44s for 100 steps
570351
    100x" run 1 "in lammps binary
    70 steps in 8 min
570306
    use lammmps binary
        2:41 for 100 steps, reasonable
570194
    lammps_only sim_only also 6.9s per step using static libary
    run lammps directly?
570044
    lammps_only simulationi 6.9s per step
    plan to try static linked lammps
569931
    decaf_lammps job,stil slow as expected.
    should try lammps only
# Jan 5
567135
    decaf 68v34 run 100 steps, add timer to see end2end time
    8min only run 71 steps
567094
    now lammps works with yuankuan's input file, each consumer get 102400 atoms, correct
567027 use extrac_atoms success
566851
    without dump
566782
    with dump, id type(1) x y z
# Jan 4
564921
    136v68
564919
    272v136
564916
    544v272
564313(again in 564355)
    2176v1088, terminate
        [0] terminate called after throwing an instance of 'std::length_error'
        [0]   what():  vector::_M_range_insert
564228
    1088v1024v544 decaf, 79.9
564100 
    use test_lbm to build lbm_only, time 36.1~36.4, stream time 0.7~1.8
564087, also build lbm as static(16 link processes)
    lbm 37.4~47.6 , end2end 58.3s, analysis 22.0~23.8(unchanged), sendrecv 2.9~13.4.
564075, run again
    lbm 36.8~46.1 , end2end 58.45s, analysis 21.6~21.9(unchanged), sendrecv 1.3~11.0.
564067, analysis is still static, now try decaf
    lbm 37.8~49.7 , end2end 60.22s, analysis 21.6~21.9, sendrecv 2.6~11.
564038, if using static link, flexpath use 21.7~28.5 analysis time
564032, analysis code is slower because I use dynamic link
# jan 2
  JOBS 
562423
    decaf 68v16v34 nmoments=4

    lbm 38~48.9 , end2end 61.5s, analysis 40.6~43.6, sendrecv 2.9~14.4
562415
    decaf 68v8v34 noments=4,
    lbm 35.6~50.4, end2end 64.5s, analysisa40.6~43.0, sendrecv 1.0~15.9
562280
    flexpath 68v34, nmoments=4

562251
    use 68v4v34, nmoment=4
    max end2end 80.5s, lbm 34.96~64.1 analysis 40.6~42.1, sendrecv 0.7~30.2
----------------------------------------------------------------
below using 64v32
562244
    resubmit nmoments= 4, 78s
562101
    pur_lbm
    simulation only all around37.0, communcation time 0.9~3s
562068
    decaf-lbm: send_receive time has 0.8~27.5s
561906
    changed to noments=4
    end2end 75.5s , max analysis 40.83, sim: 34.2~61.3
561906
    now with optimized on, 100 steps 78s, max analysis 42s, end2end time, sim time 35.2~50.8s, nmoments=3
---------------------------------------------------------------
below not optimzed
561859
    tried to compile analysis as so, analysis code is slower, 7s per step. row back
561069:
    decaf with lbm: 
        100 steps68v34 87s,lbm time ranges fromm (47s~72s), analysis just print

 add streaming/colliion/boundry
    same execuation time
 
# Dec 18
  528094:
        50G free mem (reason, in flexpath_debu use two nodes instead of 3)
        need to check
  528080:
        out of memory again
    2176v1088
## Dec 15
    consumer only?
        518908 flex_skel, consumer no output
        518928 adios_lbm, consumer
        
        
    how about luanch producer only?
        517570 flex_skel get blocked
        517588 lbm? man in the middle
        
    517224, rm flexpath queue_size, producer not blocked..
    517218, malloc inside the loop no effect,
    517144, use avx
## Dec 14
    514835, adios_1_13, stopped?
    514818, adios_1_12, ok
## Dec 9
    ~/Workspaces/LaucherTest/launcher_simple.job
## Dec 8
    497798
        use sim_only for 2176v1088, see memory usage
    497792
        sim_only 68v34
 try 68 v34: why use so much memory
        flexpath_version =10    
    496665
        2176v1088, with queue_size=10
        producer crash at step 10
    496657
        increase (back)the walltime to 20  mins, more steps use more memory?
                not, 2176 crash in the beginnnig
    496621
        nstop=100 again, now the queue size seems useful, consumer is after 10 steps
        54G 50 steps.
    496593, 496581 
        nstops=10, no memory usage shown
    496555
        nstops=100
            46G
## Dec 7
JOBS 
    496520
        print the dims
    496474
        use LOCK_MODE_CURRENT
        read_open_timeout changed to -1
        read side num_of_lines corrupted
            grep 'count':
                count:( 16954728007073792, 2)
    494391

    494380
        lock mode all
        queeu_size 1
    494187
        1088 again with -lm
        sim start3223, sim stop 3415, con stop: 3927
    494003
    flexpath 1088v544, 96G memory, same as 342994
        700s+, not linked with -m
    494049
        2096v1088


## Nov 27
JOBS
    460462
        use minimal dspaces configurations
## Nov 13
JOBS 
   424429
    move all applications in one node
   424386
    reproduce the dspaces problem in normal queue
    
    
## Oct 26
    flexpath queue_size?
   494330
    change queueu size to 1
        
   165316
       in normal queue, still rdma binding erro
       
	361833
	rerun flexpath with 2176vs1088 with LBM
		consumer malloc failed.
    xml interger?

## Oct 17
JOBS
    344553
    traces

## Oct 19
    355964
        16v8 with trace
## Oct 16
JOBS
-------------------------------------------------------
    343476
        343476, using 2 node for 8 server with 16vs8, erro
    343471
        8vs4 ok
    343468
        16vs8 err
    343466
        24vs12 native dspaces, err

    342994
        2176vs1088 again
    342100
        rerun
    342042
        flexpath with IMPI  respect placement, flexpath error, remove this
    272vs136 544vs272 are running together, should run applications separatedly
flexpath experiments
    340403
        flexpath 136vs68 with ib0 impi
    
    flexpath with greg's suggestion
    
    stick with socket+ib0
--------------------------------------------------------
retry libfabric
    34175
        memory corruption in fabric, not portable enough

    340164
        remove interface=ib0
        still with blocking
    340154
        with impi, rerun transport=ib and interface=ib0
            CMSelect blocking select


------------------------------------
    those are using mvapich, i should use impi!
    rerun CM_INTERFACE=ib0 with 272vs136
    340130
        use CMTransport=fabric with libfabric library, memory corruption ; use CM_INTERFACE=ib0, segmentation fault..
    340013
        use CM_INTERFACE=ib0, rerun 68vs34, faster then default, 542s for 68vs34
    340000
        CM_INTERFACE=ib0
        works!

## Oct 13
    333392
        68vs34, ib, cannot start

    333397
        68vs34, this is using fabric, back to socket
-----------------------------------------
    332778
        8vs4 with CM_NETWORK=ib0
    332636
        CMTransport=nonsense
        can detect
    332609
        CMTransport=ib
        now sockets seem load ib module
    332595
        CMTransport=nnti
        cm nnti not found back to default

   332667
        CMTransport=fabric
        cannot find library
        error is libpsm_infinipath.so.1: cannot open shared object file: No such file or directory

--------------------------------------------
        
   332067
        flexpath with verbose info
## Oct 12
tweak tranport
    332740
        fabric, 
    332743
        ib
experiment
    328792
        flexpath with 272vs136, stopped at step 97, see consumer_32.clog
    328263
        use stripe size=-1, and rerun 68vs34 mpiio
JOBS
    327488
        development queue with env variables in env_dev.log
    327475
        normal queue with envriables output in env_normal.log
## Oct 11
JOBS
    use idev interactive session:
        *. dev queue
            1. run the server with
                mpiexec.hydra  -n 4 /work/04446/tg837458/stampede2/envs/Dataspacesroot/bin/dataspaces_server -s 4 -c 48 &> results/dev_server.log &
            2. run writer with
                mpiexec.hydra  -n 32 /work/04446/tg837458/stampede2/envs/Dataspacesroot/bin/test_writer DATASPACES 32 3 2 4 4 128 64 64 10 1 &> results/dev_writer.log  &
            3. run the reader with
                mpiexec.hydra  -n 16 /work/04446/tg837458/stampede2/envs/Dataspacesroot/bin/test_reader DATASPACES 16  3 2 2 4 128 128 64 10 2 &> results/dev_reader.log &
        * compute queue, run the server with 
            mpiexec.hydra  -n 4 /work/04446/tg837458/stampede2/envs/Dataspacesroot/bin/dataspaces_server -s 4 -c 48 &> results/compute_server.log &
                rdma_bind_addr error imediately 

    324279:
       development queue with output ldd info
    324337:
        normal queue with output ldd info
    
## Oct 10
# conclusion
    1. rpc_bind_addr always happens in normal queue
    2. 
continue address the normal queue
    321133
        ds-test-tense with 8 nodes, each with 64 procs, normal, rdma_bind_addr err in server!
    321122
        ds-test-tense with 8 nodes, each with 64 procs, rpc_connect error, development
   

NOTE: same  scripts of ds-test.skel, sometimes with rpc_connect erro
    321035
        development with 3 nodes, 
    320983
        development queue, fine
    320997
        normal queue, rdma err
## Oct 8
JOBS libfabrics

    318997
        flexpath, slower than disk!!
    
    318996
        mpiio
    ------------------------------------------------
    above has 512/256, see google doc for more details

	318948
		flexpath 196
	318892
		flexpath now use same adios_staging with dspaces
		correct

    
## Oct 6
JOBS
    311613
        development queue can run

    311586
        normal queue cannot run

    using impi again
    --------------------------------------
    311147
    dataspaces shipped test program, with 8 server nodes, rdma_bind_addr
    310980
    run native-adios 196 with mvapich dspaces built, still has rdma_bind_addr
    
    310961
    using mvapich in stampded with with-infiband-interface=ib0
        app cp is full.
        'dsrpc_cn_register()' failed with -12.
    * solved: add DATASPACES as an auument

## Oct 5
JOBS
    310262
        196vs98 with native_dspace, rdma_bind_addr err
    310256
        8vs4 with native_dspaces

    above starts using new lanucher with machinefile
    --------------------------------
    
    309374
        8vs4 with mpiio
        correctly run
    
    
    309206
        196vs98 dspaces_nokeep
        server cannot init:
            rdma_bind_addr -1 in rpc_server_init.
            'rpc_server_init()': failed with -1.

    309158
        8vs4 dspaces_nokeep
        use new machinefile layout
    
    308648
        196vs98
        process layout
        server procs(28*4 procs are packed into two nodes)
## Oct 2
JOBS
    303418 native staging  196vs 98, rpc bind err

    303396 adios_staging of dspaces works
    303356 native_staging of dpsaces, works
    303350 mpiio successfully run, works

