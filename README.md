Benchmarking I/O transport libraries with in-situ workflows.

This repository includes code/scripts used in our HPDC18 paper[1] to configure, launch, instrument, evaluate in-situ workflows.

Some highlights are:
* Different transport libraries such as MPI-IO, FlexPath, ADIOS, DataSpaces, DIMES and Decaf are compared.
* Two insitu workfow setups (both simulation and analysis application are MPI-based parallel applications):
  - LBM (Lattice Boltzmann method) + n-th moments analysis.
  - LAMMPS + MSD (mean squared displacement) analysis
* TAU and Intel ITAC are used to instrument both simulation and analysis code and generate traces.
* Slurm job scripts to launch experiments on PSC Bridges and TACC Stampede2. 

[1] Yuankun Fu, Feng Li, Fengguang Song, and Zizhong Chen. 2018. Performance analysis and optimization of in-situ integration of simulation with data analysis: zipping applications up. In Proceedings of the 27th International Symposium on High-Performance Parallel and Distributed Computing (HPDC '18). Association for Computing Machinery, New York, NY, USA, 192–205. DOI:https://doi.org/10.1145/3208040.3208049

More detailed compiled documentation can be seen at [here](http://iupu-hpc.github.io/workflow-bench). If you find this repository useful, please consider citing our work above.
