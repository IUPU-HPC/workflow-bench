set(CMAKE_C_COMPILER  icc)
set(CMAKE_CXX_COMPILER  icpc)
set(FWORK "/work/04446/tg837458/stampede2" CACHE PATH "ffeng's work dir")
set(TRANSPORT_LIB "${FWORK}/envs/transports_icc_impi" CACHE PATH "The path to transport libs.")
set(CMAKE_C_FLAGS "-O3 -Wall -Wextra -xCORE-AVX2 -axMIC-AVX512" CACHE STRING "cflags")
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -xCORE-AVX2 -axMIC-AVX512" CACHE STRING "cxxflags")
set(LAMMPS_INCLUDE_DIR "/work/04446/tg837458/stampede2/software/lammps-16Feb16/src" CACHE PATH "lammps include path")
set(LAMMPS_LIBRARY "/work/04446/tg837458/stampede2/software/lammps-16Feb16-lib/src/liblammps.so" CACHE PATH "lammps library path")
set(LAMMPS_LIBRARY_STATIC "/work/04446/tg837458/stampede2/software/lammps-16Feb16-lib/src/static_libs_feng/liblammps.a" CACHE PATH "lammps library path")
set(DECAF_PREFIX "${FWORK}/software/install" CACHE PATH "decaf path")



