# Change Log
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](http://keepachangelog.com/) 
and this project adheres to [Semantic Versioning](http://semver.org/).
TODO
	see github log
	* redesigned flexpath
	* new version of adios

	0. use environment variable instead of preprocessor
	1. nnti in flexpath, not usable.
	2. dspaces hanging
	3. ENABLE_TESTING in flexpath conf, enabled

## April 12 
[testst]:
1. tested in Bridges the code modified in stampede
## April 11
[added]:
1. fix reoganized lbm-mpiio: every proc need update has_more 
2. fix lammps-mpiio: inconsistent xml files
3. DEBUG_adaptor is the debug info for both adios and dspaces adaptor
## April 9
[fixed]:
1. now use uint64_t as the type for global dimension
2. mpiio works with 2176, 43xx should be fine too
3. flexpath might work, need to test later

## April 3
[CHANGED]:
1. use bp-dir for adios output
2. modulize the version control in mpiio
## April 2
[TODO]:
1. reorganize:
2. rerun flexpath?

## Jan 21
	* flexpath dimension:
			see flexpath_skel/global_range_select, for 3d dimension, there
			seems a reversed dimension
## Jan 20
	* flexpath slow:
		all reduce and all gather
	* flexpath crash 2074\*1000000 > int_max
## Jan 19
	* flexpath, why it is slow
	* decaf, why it crashes at large scale?
	* regenerate trace in lbm-decaf in adios_perf
## Jan 18
	* better trace record organization

## Jan 17
	* to static build with VT, link mpi after VT libraries, as the mpicc -show
	-trace does
	* after disable all MPI functions, now I have 1088 trace for lammps

## Jan 16
	* now sim_only trace looks good
	* lbm_decaf trace generated, end2end time is 4.3s for 10 steps

## Jan 15
	* itac:
		-tcollect not work, try manually instruction
		only need the include directory and -libVT.so library
	* Computation not shown


## Jan 12
	* newly added:
		zipper code is added to source tree, see README for how to build
		
	* problems:
		self build tau with function name filter. trc file smaller but edf file
	still have boost
## Jan 11
New:
	self built tau
		haven't work yet
--------------
	traces in stampede .. 
		-- build_tau cannot use 3.7(use select file to fileter out .so makes
		3.7 works)
			stuck at "C compiler features", use 2.8 instead
		-- using 2.8 decaf not found: reason should use DECAF_FOUND(not
		Decaf_FOUND) in version
		-- now can built
	decaf generate too much traces
		- boost? /scratch/04446/tg837458/decaf_skel/587326/trace/app0less
		events.61.edf
		- all boost related have TAU_DEFAULT, how to disable it
## Jan 10
	* lammps scaling experiments, time is almost the same as lammps library
	* tau broken
	* decaf timer: 
		it's okay end2end time is valued in consumerside
	* question:
		why lbm cannot run large scale but lammps can
			I tried the example, if one dimension is larger than 100000, crash
			happens


## Jan 6
	* lammps runs slow, 6~7s per step in 68v34 case, extract is fast
	* tried static library, as slow
	* tried lammps binary, 2:43s,
	* run 100 vs run 1*100 times:
		by default it's slower, try to set pre/post for run cmd, quite useful
		for coupling processes, see lammps doc:run
		even with this, library lammps use 3:45s for 100 steps
	* decaf+ lammps vs lammps only
		225s for both case, analysis too simple and simulation too long?

## Jan 5
	* lammps need to build as shared libary, other wise:
	/opt/apps/gcc/5.4.0/bin/ld:
	/work/04446/tg837458/stampede2/software/lammps-16Feb16/src/liblammps.a(library.o):
	relocation R_X86_64_32 against `.rodata.str1.4' can not be used when
	making a shared object; recompil
	e with -fPIC
	* progress
		now lammps correctly run with a input file passed from slurm script

## Jan 4
	* problem fix:
		- longer analysis time in stampede: run_analysis is compiled as
		dynamic library to accomadate decaf
		- now all use static librarys(lbm and analysis)
	* parameter:
		- how many link processes should be used, see decaf/REAMDE for a small
		experiments, 64 procs per node
	* problem:
		- 2176v1088 crashed
	* new results:
		decaf_scaling: statistics of 68v34- 1088v544(52.9~79.9s)

## Jan 3
	* question: analysis time is longer than yuankun's 40s v 20s
	* end2end time is 60s+ if using more link processes 
	* decaf is linked with lbm, end2end time  78s for 64v32, now use nmoments
	=4
	* decaf is connected with lbm and 100 steps runs for 87s(not using
	optimizing flags)
	* decaf added to the source tree, cmake files are now in cmake/
	* buffer operation is now in seperate objects, also 38s per step

## Jan 2
	now buffer is seperated from lbm
## Dec 30
	Use valgrind to debug
	valgrind --leak-check=yes ./lbm 1 10 &> run.log
	grep -R run.log Invalid, will tell segmenta fault

## Dec 29
	Doing
		modulize
	* Lammps and lBM should have been better integrated:
	- the decaf examples/C/lammps for example:
		* it uses the lammps library interface
		* the input file doesn't call "run" and "dump"
		* this examples gatter all atoms, however it can be better, see
		lammps_gather_atoms for more
		details.(https://github.com/lammps/lammps/blob/master/src/lammps.h\c)
		
	- lbm code can also be replaced with better architecture.


## Dec 18
	flexpath fixed: remove data description, otherwise seg fault(didn't happen
	in 1.12)
		see flex_debug2 to see more details
	todo:
		1. use 3d dimension and sliced 
		2. try skeleton code check timing, 400s!
## Dec 16
	new commit:
		* add avx wall flags, consistent with yuankun's exp
		* clean anaylsis code
		* add flexpath debug

## Dec 15
	need to use ddt to look into :
		https://software.intel.com/en-us/forums/intel-clusters-and-hpc-technology/topic/329053
	use flexpath_debug

## Dec 14
	using flexpath 1.13 fixing memory usage
	but integrating 1.13 with my app, consumer had issue

## Oct 28
		cm_blocking read
		INT_CMstart_read_thread
		use_read_thread
## Oct 27
	366616
		rerun flexpthpath 34v17, 
	365308
		8vs4 development, correct
## Oct 16
add trace support
	HAS_TRACE=1 then submit jobs
	343400 is an example
	
This version generates the results for performance comparsion(8vs4)
	adios_dspaces:137.4
	adios_dimes:111.2
	adios_mpiio:96.38
	adios_flexpath:43.95
	native_dspaces:80.52
	native_dimes:51.27
	zipper:34.8
	lbm only: 33.5

	flexpath has much better performance when there are less processes in each
	node:
	using 3 node, if the processes are
	8vs4: 43.95s
	34vs17 220.76s
	68vs34 511.4s

## Oct 12
	stripe size=-1 not obvious 
	flexpath is slow at first but has good scalibility
## Oct 10
	stampede2 is not stable in stampede2.
## Oct 8
	flexpath/mpiio 512vs256
## Oct 6
#### added
	dspaces test added in project, dspaces server has rdma_bind_addr err with
	4 server nodes


## Oct 5
#### info
- now use mpiexec.hydra with new process layouts
- ibrun info
	export TACC_IBRUN_DEBUG=1
	less /home1/04446/tg837458/Downloads/LaucherTest/results/308504/app2.log
	less ~/.slurm/job.308504.hostlist.Vri26bxz

## Oct 3
	* stampded maintainance, will come back to bridges
	* dsexample cannot run multiple applications with intel mpirun, 1814068:
		run: Job step creation temporarily disabled, retrying
	* try launchertest:
		mpirun has only output for only one app



## Oct 2
#### added
- dspace example now runs in stampede2, results to verify
- dspace/flexpath/adios installed. Note withouth avx flags!

#### exp
	small experiments can run,
	larger experiment need specifiy layout, 


