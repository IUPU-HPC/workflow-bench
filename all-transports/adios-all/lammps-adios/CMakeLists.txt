if(LAMMPS_INCLUDE_DIR)
    #add_definitions("-DPRECISE")

    include_directories       (${LAMMPS_INCLUDE_DIR})

    add_executable            (lammps_adios_prod        lammps_adios_prod.cpp )
    add_executable            (lammps_adios_con     lammps_adios_con.cpp lammps_select.cpp)
    add_executable            (lammps_mpiio_con     lammps_mpiio_con.cpp lammps_select.cpp)
    target_link_libraries     (lammps_adios_prod
                                ${LAMMPS_LIBRARY_STATIC}
                                msd_analysis
                                adaptor
                                ${common_library})

    target_link_libraries     (lammps_adios_con
                                ${LAMMPS_LIBRARY_STATIC}
                                msd_analysis
                                adaptor
                                ${common_library})
        # ${bredala_transports} bredala_datamodel manala decaf)

    target_link_libraries     (lammps_mpiio_con
                                msd_analysis
                                adaptor
                                ${common_library})




endif()



