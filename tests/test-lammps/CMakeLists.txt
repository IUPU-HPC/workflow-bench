include_directories       (${LAMMPS_INCLUDE_DIR})

add_executable            (test_lammps            test_lammps.cpp)
target_link_libraries     (test_lammps
    ${LAMMPS_LIBRARY_STATIC})
                       

foreach(item test_lammps)

    target_link_libraries(${item} ${common_library})

    if(MPI_COMPILE_FLAGS)
        set_target_properties(${item} PROPERTIES COMPILE_FLAGS "${MPI_C_COMPILE_FLAGS}")
    endif()

    if(MPI_LINK_FLAGS)
        set_target_properties(${item} PROPERTIES LINK_FLAGS "${MPI_C_LINK_FLAGS}")
    endif()
endforeach(item)





