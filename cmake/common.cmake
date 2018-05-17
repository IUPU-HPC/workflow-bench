if(CMAKE_BUILD_TYPE MATCHES Debug)
  message("-- ${CMAKE_CURRENT_SOURCE_DIR} > Debug build.")

elseif(CMAKE_BUILD_TYPE MATCHES Release)
  message("-- ${CMAKE_CURRENT_SOURCE_DIR} > Release build.")

elseif(CMAKE_BUILD_TYPE STREQUAL Stampede)
  message("-- ${CMAKE_CURRENT_SOURCE_DIR} > Stampede uninstructed build")
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


elseif(CMAKE_BUILD_TYPE STREQUAL Deb_Stam)
  message("-- ${CMAKE_CURRENT_SOURCE_DIR} > Stampede debug  build")
  set(CMAKE_C_COMPILER  icc)
  set(CMAKE_CXX_COMPILER  icpc)
  set(TRANSPORT_LIB "$ENV{WORK}/envs/transports_icc_impi" CACHE PATH "The path to transport libs.")
  set(CMAKE_C_FLAGS "-O0  -Wall -Wextra -g -DDEBUG_f${ADD_FLAGS} -fPIC" CACHE STRING "cflags")
  set(LAMMPS_INCLUDE_DIR "/work/04446/tg837458/stampede2/software/lammps-16Feb16/src" CACHE PATH "lammps include path")
  set(LAMMPS_LIBRARY "/work/04446/tg837458/stampede2/software/lammps-16Feb16-lib/src/liblammps.so" CACHE PATH "lammps library path")
  set(LAMMPS_LIBRARY_STATIC "/work/04446/tg837458/stampede2/software/lammps-16Feb16-lib/src/static_libs_feng/liblammps.a" CACHE PATH "lammps library path")
  set(DECAF_PREFIX "$ENV{WORK}/software/install" CACHE PATH "decaf path")


elseif(CMAKE_BUILD_TYPE STREQUAL Stampede_TAU)
  message("-- ${CMAKE_CURRENT_SOURCE_DIR} > Stampede instructed build")

  set(CMAKE_C_COMPILER  tau_cc.sh)
  set(CMAKE_CXX_COMPILER  tau_cxx.sh)
  set(TRANSPORT_LIB "$ENV{WORK}/envs/transports_icc_impi" CACHE PATH "The path to transport libs.")
  set(CMAKE_C_FLAGS "-O3 -Wall -Wextra -xCORE-AVX2 -axMIC-AVX512 -fPIC" CACHE STRING "cflags")
  set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -xCORE-AVX2 -axMIC-AVX512 -fPIC" CACHE STRING "cxxflags")
  set(LAMMPS_INCLUDE_DIR "/work/04446/tg837458/stampede2/software/lammps-16Feb16/src" CACHE PATH "lammps include path")
  set(LAMMPS_LIBRARY "/work/04446/tg837458/stampede2/software/lammps-16Feb16-lib/src/liblammps.so" CACHE PATH "lammps library path")
  set(LAMMPS_LIBRARY_STATIC "/work/04446/tg837458/stampede2/software/lammps-16Feb16-lib/src/static_libs_feng/liblammps.a" CACHE PATH "lammps library path")
  set(DECAF_PREFIX "$ENV{WORK}/software/install" CACHE PATH "decaf path")

  #set(TRANSPORT_LIB "$ENV{WORK}/envs/transports_icc_impi_tau" CACHE PATH "The path to transport libs.")

elseif(CMAKE_BUILD_TYPE STREQUAL Bridges)
#  set(CMAKE_C_COMPILER  icc)
  #set(CMAKE_CXX_COMPILER  icpc)
  message("-- ${CMAKE_CURRENT_SOURCE_DIR} > Bridges uninstructed build")
  set(TRANSPORT_LIB "$ENV{WORK}/envs/gcc_mvapich" CACHE PATH "The path to transport libs")
  set(CMAKE_C_FLAGS "-O3")
  set(CMAKE_CXX_FLAGS "-O3")
  set(BOOST_ROOT "$ENV{WORK}/software/install" CACHE PATH "Boost path")
  set(DECAF_PREFIX "$ENV{WORK}/software/install" CACHE PATH "decaf path")

elseif(CMAKE_BUILD_TYPE STREQUAL Bridges_TAU)
  message("-- ${CMAKE_CURRENT_SOURCE_DIR} > Bridges instructed build with tau")
  set(CMAKE_C_COMPILER  tau_cc.sh)
  set(CMAKE_CXX_COMPILER  tau_cxx.sh)
  set(TRANSPORT_LIB "$ENV{WORK}/envs/gcc_mvapich" CACHE PATH "The path to transport libs")
  set(CMAKE_C_FLAGS "-fPIC ${ADD_FLAGS}" CACHE STRING "cflags")
  set(CMAKE_CXX_FLAGS "-fPIC ${ADD_FLAGS}" CACHE STRING "cxxflags")
  set(BOOST_ROOT "$ENV{WORK}/software/install" CACHE PATH "Boost path")
  set(DECAF_PREFIX "$ENV{WORK}/software/install_tau" CACHE PATH "decaf path")

endif()
 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("-- Including transport method in ${TRANSPORT_LIB} is loaded...")
 

#set(CMAKE_CXX_STANDARD 14)
#set(GCC_COVERAGE_COMPILE_FLAGS "-fPIC -msse3")

#set(CMAKE_CXX_FLAGS_DEBUG "-O2 -g")
#set(CMAKE_C_FLAGS_DEBUG "-O2 -g")
