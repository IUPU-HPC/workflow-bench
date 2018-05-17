
message("Building vector example")
set(transport_mpi on CACHE BOOL "enable mpi transport for decaf")
set(transport_cci on CACHE BOOL "enable cci transport for decaf")
#set(transport_file off CACHE BOOL "enable hdf5 file transport for decaf")
set(CCI_PREFIX "${FWORK}/software/install" CACHE PATH "cci path")
include(${CMAKE_SOURCE_DIR}/cmake/decaf.cmake)
#include_directories(${CMAKE_SOURCE_DIR}/lbm)

# lbm

add_executable            (lbm_decaf            lbm_decaf.cpp)
add_library               (mod_lbm_decaf MODULE lbm_decaf.cpp)
target_link_libraries     (lbm_decaf
                            mod_lbm
                            nmoments_analysis
                            ${libraries}
                            ${common_library})
    # ${bredala_transports} bredala_datamodel manala decaf)

target_link_libraries   (mod_lbm_decaf
                        ${libraries})
    #${bredala_transports} bredala_datamodel manala decaf)

# .SO file extension on Linux/Mac OS
set_target_properties(mod_lbm_decaf PROPERTIES SUFFIX ".so")

# Don't add a 'lib' prefix to the shared library
set_target_properties(mod_lbm_decaf PROPERTIES PREFIX "")


#lammps
#find_path                   (LAMMPS_INCLUDE_DIR		lammps.h)
#find_library                (LAMMPS_LIBRARY NAMES	lammps)


if(LAMMPS_INCLUDE_DIR)

    include_directories       (${LAMMPS_INCLUDE_DIR})

    add_executable            (lammps_decaf            lammps_decaf.cpp)
    add_library               (mod_lammps_decaf MODULE lammps_decaf.cpp)
    target_link_libraries     (lammps_decaf
        ${LAMMPS_LIBRARY_STATIC}
                                msd_analysis
                                ${libraries}
                                ${common_library})
        # ${bredala_transports} bredala_datamodel manala decaf)

    target_link_libraries   (mod_lammps_decaf
                            ${libraries})
        #${bredala_transports} bredala_datamodel manala decaf)

    # .SO file extension on Linux/Mac OS
    set_target_properties(mod_lammps_decaf PROPERTIES SUFFIX ".so")

    # Don't add a 'lib' prefix to the shared library
    set_target_properties(mod_lammps_decaf PROPERTIES PREFIX "")

endif()





