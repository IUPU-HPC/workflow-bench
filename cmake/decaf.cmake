
option                      (transport_mpi      "Build Decaf with MPI transport layer"          ON)
option                      (transport_cci      "Build Decaf with CCI transport layer"          OFF)
option                      (transport_file     "Build Decaf with file transport layer"         OFF)
option                      (tess_dense         "Build tessellation density estimator example"  OFF)
option                      (build_bredala      "Build Bredala libraries and examples"          ON)
option                      (build_manala       "Build Manala libraries and examples"           ON)
option                      (build_decaf        "Build the Decaf workflow system"               ON)
option                      (build_tests        "Build the tests examples"                      ON)
set                         (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

if(build_manala)
    set                     (build_bredala  true)
endif(build_manala)
if(build_decaf)
    set                     (build_bredala  true)
    set                     (build_manala   true)
endif(build_decaf)

# C++11
set                         (CMAKE_CXX_STANDARD        11)
set                         (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
message("----cxx flags changed to ${CMAKE_CXX_FLAGS}")

# MPI
if                          (transport_mpi)
  find_package              (MPI REQUIRED)
  if                        (NOT bgq)
    set                     (transport_libraries    ${transport_libraries} ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES})
  endif                     ()
  add_definitions           (-DTRANSPORT_MPI)
  set                       (TRANSPORT_MPI ON)
endif                       (transport_mpi)

#CCI
if                          (transport_cci)
  find_package              (MPI REQUIRED)
  find_package              (CCI REQUIRED)
  set                       (transport_libraries    ${transport_libraries} ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES} ${CCI_LIBRARY})
  include_directories       (${CCI_INCLUDE_DIR})
  add_definitions           (-DTRANSPORT_CCI)
  set                       (TRANSPORT_CCI ON)
endif                       (transport_cci)

#FILE
#Should be used with the variable HDF5_PREFER_PARALLEL set to true
if                          (transport_file)
  find_package              (HDF5 REQUIRED)
  include_directories       (${HDF5_INCLUDE_DIR})
  set                       (transport_libraries    ${transport_libraries} ${HDF5_LIBRARIES})
  add_definitions           (-DTRANSPORT_FILE)
  set                       (TRANSPORT_FILE ON)
endif                       (transport_file)


# decaf, added by feng
find_package                (Decaf REQUIRED)
if (DECAF_FOUND)
    include_directories       (${DECAF_CXX_INCLUDE} 
                               ${DECAF_CXX_INCLUDE_DIR})
    set                       (transport_libraries    
                                ${transport_libraries} 
                                ${DECAF_CXX_DATA_MODEL_LIBRARY} 
                                ${DECAF_CXX_TRANSPORT_LIBRARY} 
                                ${DECAF_CXX_RUNTIME_LIBRARY})

                            #message("fulltransport libray is ${transport_libraries}")
else()
    message("Decaf not found, set DecafPrefix")
endif(DECAF_FOUND)

# Boost
find_package                (Boost 1.64.0 COMPONENTS serialization REQUIRED)
message                     (STATUS "Boost libraries: " ${Boost_LIBRARIES})
    include_directories         (${Boost_INCLUDE_DIRS})
    set                       (transport_libraries    
                                ${transport_libraries} 
                                ${Boost_LIBRARIES})

# Set include directories
set                         (CMAKE_INCLUDE_SYSTEM_FLAG_CXX "-isystem")
include_directories         (${CMAKE_CURRENT_BINARY_DIR}
                             ${CMAKE_CURRENT_SOURCE_DIR}
                             ${CMAKE_CURRENT_SOURCE_DIR}/include
                             SYSTEM ${MPI_INCLUDE_PATH})

# Set libraries
set                         (libraries
                             ${libraries}
                             ${transport_libraries})
                         #${CMAKE_DL_LIBS})

set (CMAKE_LINKER_FLAGS ${CMAKE_LINKER_FLAGS} "-Wl,--export-dynamic -dynamic")
