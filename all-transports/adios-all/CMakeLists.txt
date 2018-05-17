# written by Feng Li
## setting  adios 
option(DEBUG_adaptor "debug option for dsadator and adios adaptor" OFF)
if(DEBUG_adaptor)
add_definitions(-DDEBUG)
endif(DEBUG_adaptor)

set(DS_DIR "${TRANSPORT_LIB}/Dataspacesroot" CACHE PATH "The path to dataspaces.")
set(ADIOS_DIR "${TRANSPORT_LIB}/ADIOSroot" CACHE PATH "The path to adios.")
set(FLEXPATH_DIR "${TRANSPORT_LIB}/Flexpath" CACHE PATH "The path to flexpath.")

include_directories(${DS_DIR}/include ${ADIOS_DIR}/include ${FLEXPATH_DIR}/include)

find_library(DSPACES dspaces ${DS_DIR}/lib)
find_library(DSCOMMON dscommon ${DS_DIR}/lib) 
find_library(DART dart ${DS_DIR}/lib) 
find_library(ADIOS adios ${ADIOS_DIR}/lib)

find_library(EVPATH evpath ${FLEXPATH_DIR}/lib)
find_library(FFS ffs ${FLEXPATH_DIR}/lib)
find_library(ATL atl ${FLEXPATH_DIR}/lib)
find_library(DILL dill ${FLEXPATH_DIR}/lib)
find_library(CERCS_ENV cercs_env ${FLEXPATH_DIR}/lib)

set(ADIOS_LIB ${ADIOS} ${DSPACES} ${DSCOMMON} ${DART} ${EVPATH} ${FFS} ${ATL} ${DILL} ${CERCS_ENV})

#include_directories("${CMAKE_SOURCE_DIR}/src")     

add_library(adaptor adios_adaptor.c ds_adaptor.c)
target_link_libraries(adaptor ${ADIOS_LIB})

# add libm if using gcc
target_link_libraries(adaptor  pthread rt rdmacm ibverbs)

include_directories(.)

add_subdirectory(lbm-adios)

if(LAMMPS_INCLUDE_DIR)
    add_subdirectory(lammps-adios)
endif()


