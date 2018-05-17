cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project("lbm_adios")


if(TRANSPORT_LIB)
    message("-- Including transport method in ${TRANSPORT_LIB} is loaded...")
else()
    message(FATAL_ERROR "-- should either specify build type or toolchain file")
endif()

message("----current cxx flags is ${CMAKE_CXX_FLAGS}")

option(all_transports "build all transports" ON)
option(use_itac "build with itac" OFF)
option(build_zipper "build zipper runtim" OFF)

option(USE_SAME_LOCK "Use same lock in dspaces" OFF)
option(BARRIER_STAMP "barrier after broadcast version in consumer" ON)

if(NOT USE_SAME_LOCK)
    set(DS_MAX_VERSION "3")
endif()

configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
     @ONLY
    )

include_directories("${PROJECT_BINARY_DIR}")
include_directories(include)


set(common_library "m")

#itac
if(use_itac)
    add_definitions(-DV_T)
    set(VT_ROOT $ENV{VT_ROOT} CACHE PATH "The path vt")
    message("itac enabled! with ${VT_ROOT}")
    include_directories(${VT_ROOT}/include)
    ### see VT_ADD_LIBS
    #set(vt_library ${INTEL_VT}  $ENV{VT_ADD_LIBS})
    set(vt_library "-L$ENV{VT_SLIB_DIR} -lVT $ENV{VT_ADD_LIBS}" CACHE STRING "itac link flags")
    set(common_library ${common_library} ${vt_library})
   #set(common_library ${common_library} "-L/opt/intel/itac/2017.3.030/intel64/lib -lVT -ldwarf -lelf -lvtunwind" )
endif(use_itac)

# mpi
find_package(MPI REQUIRED)
set(common_library ${common_library} ${MPI_C_LIBRARIES})



add_definitions ("-DENABLE_TIMING")
#add_definitions ("-DUSE_DATASPACES -DENABLE_TIMING -Wall -Wextra")
#add_definitions ("-DUSE_DATASPACES -DHAS_KEEP -DENABLE_TIMING -Wall -Wextra")
#add_definitions ("-DUSE_DIMES -DENABLE_TIMING -Wall -Wextra")
#add_definitions ("-DUSE_DIMES -DHAS_KEEP -DENABLE_TIMING -Wall -Wextra") 


include_directories(${MPI_INCLUDE_PATH} ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/analysis ${CMAKE_SOURCE_DIR}/msd ${CMAKE_SOURCE_DIR}/lbm)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

## lbm-nmoments
add_subdirectory(lbm)
add_subdirectory(nmoments-anal)


## lammps-msd
if(LAMMPS_INCLUDE_DIR)
    add_subdirectory(msd-anal)
endif()

## bind different transports to applications
if(all_transports)
    add_subdirectory(all-transports)
endif(all_transports)

## zipper
if(build_zipper)
    add_subdirectory(zipper)
endif(build_zipper)


## tests
add_subdirectory(tests)


