add_executable(run_lbm run_lbm.c)
target_link_libraries(run_lbm mod_lbm)
add_executable(adios_staging_read adios_staging_read.c)
add_executable(adios_disk_read adios_disk_read.c)

add_executable(native_staging_read native_staging_read.c)
#add_executable(adios_read_global adios_mpiio_read.c run_analysis.c adios_adaptor.c)
# add_executable(adios_write_global adios_write_global.c)

SET(myTARGET run_lbm adios_staging_read adios_disk_read native_staging_read)
foreach(item ${myTARGET})

    target_link_libraries(${item} ${common_library} adaptor nmoments_analysis)

    if(MPI_COMPILE_FLAGS)
        set_target_properties(${item} PROPERTIES COMPILE_FLAGS "${MPI_C_COMPILE_FLAGS}")
    endif()

    if(MPI_LINK_FLAGS)
        set_target_properties(${item} PROPERTIES LINK_FLAGS "${MPI_C_LINK_FLAGS}")
    endif()
endforeach(item)


