message("building standalone analsis")

#add_executable(lbm lbm.c lbm_buffer.c lbm_test.c)
add_library(nmoments_analysis run_analysis.c)

#target_link_libraries(lbm ${LIBRARIES})
#target_link_libraries(mod_lbm ${LIBRARIES})

foreach(item nmoments_analysis)

    #target_link_libraries(${item} ${MPI_LIBRARIES})

    if(MPI_COMPILE_FLAGS)
        set_target_properties(${item} PROPERTIES COMPILE_FLAGS "${MPI_C_COMPILE_FLAGS}")
    endif()

    if(MPI_LINK_FLAGS)
        set_target_properties(${item} PROPERTIES LINK_FLAGS "${MPI_C_LINK_FLAGS}")
    endif()
endforeach(item)

