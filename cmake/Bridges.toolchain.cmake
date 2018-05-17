# module load intel
set(FWORK "/pylon5/ac561jp/fli5/from_pylon2" CACHE PATH "ffeng's work dir")
set(TRANSPORT_LIB "${FWORK}/envs/gcc_mvapich" CACHE PATH "The path to transport libs")
set(CMAKE_C_FLAGS "-O3" CACHE STRING "")
set(CMAKE_CXX_FLAGS "-O3" CACHE STRING "")
set(BOOST_ROOT "${FWORK}/software/install" CACHE PATH "Boost path")
set(DECAF_PREFIX "${FWORK}/software/install" CACHE PATH "decaf path")
