message("building standalone msd")

add_library(msd_analysis run_msd.c)

#target_link_libraries(mod_lbm ${LIBRARIES})
#target_link_libraries(mod_lbm ${LIBRARIES})

foreach(item msd_analysis)

    #target_link_libraries(${item} ${MPI_C_LIBRARIES})

    if(MPI_COMPILE_FLAGS)
        set_target_properties(${item} PROPERTIES COMPILE_FLAGS "${MPI_C_COMPILE_FLAGS}")
    endif()

    if(MPI_LINK_FLAGS)
        set_target_properties(${item} PROPERTIES LINK_FLAGS "${MPI_C_LINK_FLAGS}")
    endif()
endforeach(item)

#add_executable(lbm test_lbm.c)
#target_link_libraries(lbm mod_lbm)

