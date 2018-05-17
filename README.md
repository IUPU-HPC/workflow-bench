# different transport support for parallel lbm code
# work submitted to IPDPS2018

see [this wiki](https://github.iu.edu/IUPUI-CS-HPC/data_broker_lammps/wiki) for more details

written by Feng Li at Fall 2017

[April 3]:
## list
1. what does advstep mean?
## What is new
[Mar 29]: 
    [Implementation guide line](https://docs.google.com/spreadsheets/d/1mh3oZP3dJtQG33AnLnTprAV3WpjBQC4bMWRFFy7HTgM/edit#gid=0)
[Mar 27]: 
* this version is the code in both machine(Stampede/Bridges) when we submit HPDC first version. (doesn't include the changes in zipper, which is not wrapped yet)
* See [version contrl](docs/version_control.md) for how different branches works
[Jan 16]: trace inteval: lbm use center 2, width 2, lammps use 10,10
[Jan 12]: now stampede tau build should be buit with
    
[Jan 11]: in stampede, need to use cmake 2.8 to build with taucc
[Jan 9]: in bridges, use 32v16 for traces
[Jan 5]; lammps example code added to the source tree and works
[Jan 4]: decaf works with lbm, using dynamic analysis library makes analysis code runs slower(40s vs 20s in stampede)
[Jan 2]: lbm reorganized in lbm/
[Dec18]: flexpath segfault, data description for group should be removed for v1.13 flexpath, see https://github.iu.edu/lifen/flexpath_skel/commit/59cea72ad6715c91220ac3bc4ab72aeb7a47b579
[Dec14]:  flexpath memory leak fixed in v1.13
[Dataspaces large memory footprint]: even the mpiio method use 40GB memory each node
[macro]: dont use $ in $(()), see dspaces_debug, though output look the same.
   *  use hash_version=2 in dataspaces to reduce memory usage, Nov29, see dspaces_debug branch
   * now all compiler/tranport library path is set automatically in cmake
    see mk/common.cmake and INSTALL:#build for more details
   

## What is done
    performace analysis
        traces collection for all transports in 8vs4
        performace collection for all transport in 64v32
    scalability test
        scalibility test in both mpiio/flexpath
        

## What is missing
Performance Anaylis(Bridges)
    need decaf results
    other transports need to use lbm and analysis library
    traces need to regenerate
Scaling(stampde)
    decaf with lammps library(lammps is only in scaling experiments)
        lammps is now built as shared lib
    2176 decaf is not working
    traces need to regenerate

-----------------------------------------------
before Jan 4
        traces:
            flexpath traces is not shown very clearly in performance analysis
            stampede traces and bridges flexpath traces show different behaviours
        mpiio
            didn't run the largest experiements, will take too long
        flexpath
            flexpath crashes in large experiments, need to fix
   

## Environment settings and Build
    se INSTALL for more details

## Important Note
 - use dependency-enabled job to submit all the tasks, record whether they are success in summary.txt
 - record all the results in exp_brideges.excel PerfBridges_Large
 - all end2end time is built with -O3, with traces-eabled are not, 




## Run 
    * Performance test experiments
        * uninstructed build(change 8vs4 to 64v32 to run 64v32 experiemnts for the performance comparison)
            sbatch scripts/bridges/8vs4/native_dimes_nokeep.job
        * instructed build, this will generate all traces in $SCRATCH/$jobid/traces/app0.1.2, respectively
            HAS_TRACE=1 sbatch scripts/bridges/8vs4/native_dimes_nokeep.job
    * scalibility test
       *  note: scalability test experiments(flexpath and native dimes) are performed in both Stampede2/bridges KNL node.I use default compiler at that experiment(icc+impi)
            
        * HOWTO:
            ```shell
            sbatch scripts/stampede2/scaling_exp/flexpath/272vs136.job

            # run with
            HAS_KEEP=1 sbatch scripts/stampede2/scaling_exp/flexpath/68vs34.job
            ```
            * switch stampede2 to bridges to use another machine
            * switch flexpath to mpiio to use different transport
            * 272v136, change to other avaible scripts for different size of experiments
