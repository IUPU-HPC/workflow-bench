set(CMAKE_SYSTEM_NAME Linux)

# message("-- stampede tau toolchain used")

#set(CMAKE_SYSROOT /home/devel/rasp-pi-rootfs)
#set(CMAKE_STAGING_PREFIX /home/devel/stage)

set(tools /work/04446/tg837458/stampede2/envs/tau_bundle_2_27/tau_opempi_pthread/x86_64/)
set(CMAKE_C_COMPILER ${tools}/bin/tau_cc.sh)
set(CMAKE_CXX_COMPILER ${tools}/bin/tau_cxx.sh)

set(TRANSPORT_LIB "$ENV{WORK}/envs/transports_icc_impi" CACHE PATH "The path to transport libs.")
  set(CMAKE_C_FLAGS "-O3 -Wall -Wextra -xCORE-AVX2 -axMIC-AVX512 -fPIC" CACHE STRING "cflags")
  set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -xCORE-AVX2 -axMIC-AVX512 -fPIC" CACHE STRING "cxxflags")
  set(LAMMPS_INCLUDE_DIR "/work/04446/tg837458/stampede2/software/lammps-16Feb16/src" CACHE PATH "lammps include path")
  set(LAMMPS_LIBRARY "/work/04446/tg837458/stampede2/software/lammps-16Feb16-lib/src/liblammps.so" CACHE PATH "lammps library path")
  set(LAMMPS_LIBRARY_STATIC "/work/04446/tg837458/stampede2/software/lammps-16Feb16-lib/src/static_libs_feng/liblammps.a" CACHE PATH "lammps library path")
  set(DECAF_PREFIX "$ENV{WORK}/software/install" CACHE PATH "decaf path")

 

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

  
