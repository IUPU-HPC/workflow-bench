# Change Log
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](http://keepachangelog.com/) 
and this project adheres to [Semantic Versioning](http://semver.org/).

-------------------------------------------------------------------------------
versions
	adios is configured in 
		~/Downloads/adios/adios-1.12-gcc-mvapich-taufull
		instructed dspaces cannot recognized
	flexpath_gcc_mvapich:~/Downloads/flexpath/flexpath_adios_1_12_gnu_mvapich
		~/Downloads/flexpath/flexpath_adios_1_12_gnu_mvapich_tauperl chaos_bootstrap.pl adios-1.12 $HOME/envs/Flexpath_gcc_mvapich_tau &> config.lifen.log
	raw_dspacesraw_gcc_mvapich
----------------------------------------------------------------------------------
## April 2
[Doubt]:
1. in DataSpaces README, 16G each process, why need 5 server instead of 10 instead of 20
2. what does ds\_unlock\_on\_read do, does it wait until data is ready?
    answer: dcg_lock_on_read will check whether data is ready to fetch or not,
            both dcg_lock_on_read and dcg_lock_on_write has a barrier in the end
3. increase the server process help?
4. DIMES; sync\_all:(I sent a email to Rutgers)
    *. how the buffers are freed?
    *. there is a dimes_put_sync_all
5. reason why it crashes at step 7: producer end in advance!
[Target]:
0. need to add analysis trace
1. dspaces multilock: more server>?
2. dspaces : why consumer 0 is slower
[Fixed]:
1. dimes fetch error: the last cached version is not protected, add on more loop to of ds\_lock\_on\_write to protect


## April 1
[new]:
1. for native dspaces, there is a barrier, could be ds_lock_on_write
1. trace is now also added in ds_adaptor
1. the reason of multi-steps don't help is the slow consumer(dimes is the same)
## Mar 31
[TODO]:
1. reorganize code for  lbm adios/dspaces/mpiio (done)
2. trace (done)
[CHANGES]:
1. remove FILE2PRODUCE in scripts(I still need them, since consumer need to now the dimension in some of the transports)

[TODO]:
1. reorganize code for lammps mpiio

## Mar 30
[Conclusion]:
1. native dimes,end2end time not stable
[TODO]:
1. lbm-adios need to use the lib-lbm(done)
2. get the itac trace(done)
[results]:
1. two locks doen't help with 8v4 an 64v32; 256v32 crashes sometimes
[dspaces]:
1. how buffer is managed, version? how dsspaces allocate sufficient buffer(max version only for data indexing or buffer allocation)
2. how unblocking io works(each time alloc allocate a buffer and call rpc\_send), how the bufer is freed(a callback function is added in the message)
3. in the conf it didn't specify variable size(how to allocate sizse)
4. in the README file, dimes doesn't support max_version in configuration(how about now?)
5. multiversion/failure with hash version2?
## Mar 29
[changed]:
1. reorganized
2. clog is removed
[multi-locks]:
1. I should also set the max-version in dspaces.conf
[dspaces]:
1. where is the installation dir?
[Notes]:
1. Use toolchain file instead of BuildType. This will make sure flags are
	also updated in Cache
2. where did we use the standard-alone lbm?
    * only in the decaf-lbm and lbm-sim-only
    * TODO: i need to wrap the all the adios one in a sepearte directory(transport/adios),
3. where adios is used?
    * seems only in LBM in bridges
4. lammps-flexpath result in scaling?
    * it's in adios/prod.cpp and adios_con.cpp 
5. seems like we are using the MPIIO data (lammps scaling) from IPDPS
6. TODO: i need give a table of trasports/apps/machine/
## Jan 22
	flexpath with lammps, using 1 proc in each node, 218s v 219(zipper)s
## Jan 18
	switched to intel/impi:
		need set following

        export I_MPI_JOB_RESPECT_PROCESS_PLACEMENT=0
        export I_MPI_SHM_LMT=shm

	with decaf now analysis run very slow in some procs
## Jan 10
	* finds:
		32v16 not good for dimes, I may generate traces using 256v128
	* work left:
		traces for 256v128
	* plan:
		work on stampede first
## Jan 9
	* trace in comformance comparison
		use 32v16, I want to keep consistent with
## Jan 8
	* results:
	decaf 256v128 86.36s, 8 procs per link node
	* TODO build decaf using TAU
	* build
		decaf_tau build at software/install_tau

## Dec 12
	fixed:
		adios staging longer analysis time: 

## Dec 1
	now updated 64v32 diagram

## Nov 30 use dependency list

## Nov 28
#### Note
	- 28v14 using two server procs, seg fault in server
	- 64v32 max rss is  105G, producer max page fault 166k, consumer 153k
	- 196v98 max rss is 131G, producer max fault is 263k, consumer max page fault 505k
	

	create seperate fork
	Q: large memory use:
		1. tools to detect
		2. clog dynamic?
		3. use LM

## Oct 22
	don't laod default tau module in bridges,
	added trace support for simonly
## Oct 20
	https://github.iu.edu/IUPUI-CS-HPC/data_broker_lammps/wiki/compile&linking

tau with adios and dataspaces
	now use old version in 
	$ENV{WORK}/envs/Dataspacesroot_tau, install from
	/home/fli5/Downloads/dataspaces/dataspaces-1.6.2-gcc-mvapich-tau
	$ENV{WORK}/envs/backup/ADIOSroot_tau_1.11

## Oct 10
	build flexpath
## Oct 8
	impi works, using bridges default, use intel packages for all softwares
	i can also use more processes pernode
	all scripts/CMakeLists use new path with _intel

## Oct 14
	https://software.intel.com/en-us/forums/intel-clusters-and-hpc-technology/topic/702213

	
## Oct 2
#### fixing:
	1. comment out dataspaces locktype specification in adios_staging, as it
	does in adios staging example. (then type 1 lock will be used)
	2. use 2-d dimesions as in native dspaces?
	3. add timeout for adios_read_open, reader applications will try multiple
	times until stream is available.

	adios_dspaces with 1 server process: 230s
	adios_dimes with 1 server process: 155.54s
#### changed:
	now adios_staging use 4 server processes

## Oct 1 
	should try adios_staging skeletopn code
	1810216
		adios_staging with separate output
			consumer read is not performed

## Sep 29
	todo:
	adios_staging:
		Sep 27, else if fixed, but get blocked:
		check adios open mode, should it be opened in each step?(w in first step,
	and a in succeding steps, as in examples/staging/..genarray_stream)
## Sep 28
	todo
		adios_staging
		larger native_dimes

## Sep 27
	changes: 
		filename(scripts scripts and reader name
	fixing: adios reader initialization
## Sep 26
	dimes:
		sync before each step,
		also sync after the last step
		1798513: native dimes has 63.43 s for 100 steps!, fastest transport
## Sep 25
	changes:
		* add transports method, now differnet transport is chosen by
		Environment Variables.
	
	experiment:
		each node has 14 proccess
		
		56 nodes for producer
		28 nodes for consumer

## Sep 22
	in evpath_mpi/results/socket.log & evpath_mpi/results/enet.log
	enet also uses socket, I need to see how libsocket is implemented
	-------------------------------
	before meeting


	NEW version of ADIOS add support for redesigned flexpath!
	see changelog of adios-1-12: robust flexpath!
	transpormation us sz!
	if set flexpath version_tag = adios_1_12, nnti is no longer provided!

	evpath/cmnnti.c

	nnti/nnti.c available_tranport
	nnti_ib.cpp:
		setup_request_channel/setup_data_channel
		ibv_create_comp_channel_wrapper
		ibv_create_comp_channel
## Sep 21
	enet: timeout
	exp:
		with CMTransportVerbose, evpath_mpi can give verbose output of
		tranport method
	
## Sep 19
## experiment
	1773803
		1-lock-per-step with comm_world
		second step is still slow.
	1772582
	run with  MPI_COMM_WORLD communicator
	1771861
	use 2-procs group in producer, 1-group in consumer
	only run 5 steps of instructed dspaces
	previous optimization on dspaces:
		separate comunicators in consumer
		2 ranks use same communicators
		maxversion
## Sep 18
## experiment
	1768693
	with tau-enabled dspaces
	traces/instructed_raw_dspaces..
	are traces aligned?
	
	1767680, with dspaces_origin built
	raw dataspaces with lbm, to be checked
	one trace per proc!(because I used the original dspaces built?, dspaces is
	not tau-instructed..))
	traces/raw_dspaces_pro/consumer.slog2

	1769997
	minmax with 10 steps
	traces/ex3_10_steps.slog2
	bouned by consumer, as exepected.
	two traces per proc

## Sep 17
	ldrdmacm libvers is required when building adios
	adios recompile with adios is slow...
	should try multiple steps with raw dspaces first..
## Sep 15
	see scripts_bridges/lbm_dataspace_nokeep_tau_8 for tau-attached jobs
## Sep 14
	get the traces for dspaces, see dspaces_ex3.slog2 in my laptop, rank has
	longest unlock_on_read time

	fortran  is disabled

	in ADIOS config.lifen.log, nnti??
		FP_LIBS =  -levpath -lffs -latl -ldill -lcercs_env
	Update: nnti is dynamically loaded using dlopen, see greg's email for more
	details


## [0.3.0] Sep 13
## fixed
	dspaces and tau are installed and functionally properly in bridges
## to do
	pthread is not found when compiling evpath
 	see:
		/home/fli5/Downloads/flexpath/build_area/evpath/linux/CMakeFiles/CMakeError.log
	

## problems
	
## [0.2.7] Mar 9 2017
#### added  
- Barrier in mpiio_read timestep Bcast
- Bcast is blocking but not synchronzied:
	http://stackoverflow.com/questions/39550649/is-mpi-bcast-blocking/39551033#39551033
#### dataspaces built
= struct rpc_cmd not recoganized: config.h not read!

## [0.2.6] Mar 7 2017
#### tried
- sleep in consumers
#### added
	detailed time info in producer/consumer,
	producer and consumer can finish 200 steps in same time


## [0.2.5] Mar 6 2017
#### changed
Dataspaces
	small guantity locks, add part into in lock name,
	still use max_20 locks
	use split communicators
Dimes
	not enough space
	use put_sync every 20 steps

## [0.2.4] Mar 5 2017
#### added
add avg in breakdown timer in raw_dspaces_read, mpiio_read, run_lbm
#### changed
dspaces lock removed-> error, consumer need to know when data is avaiblable

## [0.2.3] mar 4 2017
#### added
- use more server instances decrease the consumer time.
- add timer in mpiio version
- rebuild dspaces with --with-dimes-rdma-buffer-size=1024
#### changed
- dspaces max version is limited to 20
- ds_adaptor changed correspondingly
#### thoughts:
- too many versions take too much memory, instead limit max version to smaller
number , and use mod of version number as lock name

## [0.2.2] May 2 2017
#### added 
- dimes added
- job file of dimes added

## [0.2.1] May 1 2017
#### changed
#### working version
	no gdim_define in code
	with 2 dimensions in jobfile
	seems reading takes sometime


## [0.2.0] April 28 2017
#### moved back to bridges
#### changes
#### note
	all timer in a job should be average

## [0.1.21] April 25 2017
#### Qestion:
	how to deal with different nlines in various processes?
	erase the warning flags?
	PMI error comes from number of arguments!
	-g option ?
	mpirun_rsh problem?(apply to ds_exmaple, see what happens)
		~/ds_examples/ex1_putget correct executed for 1:1
#### changes
	malloc-free in in the loop of raw_dspaces_read
	consumer need to know how many procs in producer
#### issues
	raw dspaces has rpc_connect error:9036590/results/consumer.log
#### trials
	run ds_examples/: works
	add -g flag, see output(need to roll back), same problem
	1:1 mpiio works, but very slow 5s per step writing time
	in bridges, writting time for 1:1 is much smaller:less .3s
	/pylon5/cc4s86p/fli5/data_broker_adios/1019183/results/producer.log
#### this PMI error happened before (Mar 30), then project was immigrated to
bridges

## [0.1.20] April 24 2017
#### changed
- project moved to comet
- flexpath configured
- in ADIOS removed the -g option, rebuilt
- do I need remove -g option in all libraries?
#### problems
- in comet, dataspaces nokeep has PMI error, 9024518
- in bridges, dspaces only one step, 103192, new: 1032015: move back to
'5bf287a81', try again
#### added
- raw dspaces added


-----------------------------------------------------------------------
moved on comet on April 24
## [0.1.19] 2017 April 24
#### added
	breakdown-timer in consumer side
#### Question
	adios_perform reads, use nonblock instead?


## [0.1.18] 2017 April 21
#### trials
- ADIOS_LOCKMODE_NONE doesn't work for dataspaces
#### to do
- flexpath use lock-non?
	no effect
- use lock-non but increase queue size to 100
---- better writting time, but longer gap between simulation stops and
analysis finishes(90s)
rank 0, t_prepare:0.096157 s, t_cal 74.112131 s,t_buffer = 0.378756, t_write 18.409973 s

## [0.1.17] 2017 April 20
#### Questions
	mpiio-io write when does it return?
		write into buffer then return immediately?
#### 2v1
		mpiio	flexpath	dataspaces	dimes
		41.84	48.276		148.33		
#### fixed
		dataspaces configuration
		DS_LIMIT should be timed with nprocs_producer
#### trying(need to roll back)
	2v2 blocked in second step
	add buffer size and group size back, job pending(1022958)
	still  same
	change lockmode to ADIOS_LOCKMODE_NONE
	

## [0.1.16] 2017 April 19
#### using producer:consumer= 1:1
	writing time 0.1s for each step(instead of 1.x s for 8vs4)
	writing time for 100 timesteps
		mpiio	flexpath	dataspaces	dimes
		35.61s	13.14s		59.30s		59.11s


## [0.1.15] 2017 April 18
#### changes
	remove get_group_size
	remov buffer max-size

## [0.1.14] 2017 April 17
#### buffersizese
buffersize for each process or nodes or global size?
is the reason that the first write takes more time?
group_size is nozero, if using staging, total_size is zero

#### removed the barrier in 


## [0.1.13] 2017 April 11
#### use flexpath 
-flexpath
	longer calculation time?
	t_prepare:0.099268 s, t_cal 42.772855 s,t_buffer = 0.388137, t_write 149.501805 s


## [0.1.12] 2017 April 6
#### Q
- what if only has dspaces write?
- is the fist step has the smallest writting time?
	989971
- cannot run producer without consumer
	989835
	

## [0.1.11] 2017 April 4 #### upon submission
- maxversion =5
- analysis is commented
#### try
- use larger buffer size in adios
	buffer size increased to 100M, no effect
- get analysis time
	stat:time for read 53.557231 s; time for advancing step 76.971237 s; time for analyst 39.008861 s

- use more servers
	same nodes, use 4 procs for server will reduce writting time from 150s to
	120s
	two nodes, with 4 procs, 114s
- doubts
	if disable analysis, why writting time is decreased?(985141& 989763)
	

#### MPIIO more tests


## [0.1.10] 2017 April 3
#### change
- extract the common part in job files
- results of 8vs4 is completed 
#### issues
- mpiio is faster then dspaces
- reason: 
	dspaces operation is strictly synchronized(cannot start next iteration if
	previous data is not consumered)
- analysis:
	is each transport method blocking or unblocking?
- break down the time
- blocking writes?
	disable analysis
	
## [0.1.9] 2017 April 2
#### change
- mpiio version lock fixed
- use scratch dir as working dir
## [0.1.8] 2017 Mar 31
#### change
- use -O3 now sim-only can finish 100 steps in 33.6s
- add error checking for adios init
- add has_more flag to indicate when producer finishes
## [0.1.7] 2017 Mar 30
#### done
- moved to bridges, correctly run with seprated nodes 
- tested 8v4
### to do
- test 48v24

## [0.1.6] 2017 Mar 29
#### added
- now run in separate nodes, but PMI erroj
## [0.1.5] 2017 mar 28
#### issues
- run job, but output not output to corresponding folder
kjjjj

## [0.1.4] 2017 Mar 27
#### added
- timer added in the begining of first simulation and at the end of last step
of analysis
- starting experiment in comet of staging method
- now different configurations are generated in different builds
- now all scripts are in scripts/(simulation_only version added)


## [0.1.3] 2017 mar 26
#### modified
- save errno of streaming read, so receiver will stop correctly
- add parameter 'mode' to insert_into_adios(), for keep, "a"(append) mode will
be used(first iteration use "w" to creat the file)
be used

#### added
- xml files are splited for different transport methods in xmls dir
- run_lbm will select different xml based on preprocessor

## [0.1.2] 2017 mar 25
#### fixed
mpiio need to use scratch path explicitly
#### Notes:
- for mppio:
	1. use scratch path explicitly for adios variable
	2. buffer size in xml should be larger than groupsize
	3. for a application with both MPI-io and staging read, init_read_method
	first than init_adios
#### changed
add kep using mpiio, now new ads_adaptor.c/h is created
## [0.1.1] 2017 Mar 24
#### Notes
- most data generated by lbm is 0
- testes 1 proc, correct
#### ADD
- add analysis component

## [0.1.0] 2017 Mar 23
#### Changed
- removed blocks, now each process need to prepare contiguous buffer for adios
#### To do
- use small size, verify the correctness of data read

