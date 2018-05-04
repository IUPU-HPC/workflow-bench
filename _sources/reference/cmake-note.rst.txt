.. _zipper_cmake:

notes for using CMake
======================

1. all cmake files are stored in cmake/


find package
-------------

less /opt/apps/cmake/3.8.2/share/cmake-3.8/Modules/FindMPI.cmake

show mpicc contents
----------------------

mpicc can be tricky, you can compare the cmake generated flags with the system-default mpicc::

    mpiicc -show -trace -I$VT_ROOT/include no_mpi_test.c  &>1.log
        icc '-I/opt/intel/itac/2017.3.030/include' 'no_mpi_test.c' -I/opt/intel/compilers_and_libraries_2017.4.196/linux/mpi/intel64/include -L/opt/intel/compilers_and_libraries_2017.4.196/linux/mpi/intel64/lib/release_mt -L/opt/intel/compilers_and_libraries_2017.4.196/linux/mpi/intel64/lib -Xlinker --enable-new-dtags -Xlinker -rpath -Xlinker /opt/intel/compilers_and_libraries_2017.4.196/linux/mpi/intel64/lib/release_mt -Xlinker -rpath -Xlinker /opt/intel/compilers_and_libraries_2017.4.196/linux/mpi/intel64/lib -Xlinker -rpath -Xlinker /opt/intel/mpi-rt/2017.0.0/intel64/lib/release_mt -Xlinker -rpath -Xlinker /opt/intel/mpi-rt/2017.0.0/intel64/lib -L/opt/intel/itac/2017.3.030/intel64/lib -lVT -ldwarf -lelf -lvtunwind -lm -lpthread -lmpifort -lmpi -lmpigi -ldl -lrt -lpthread

.. note::

    if build library, don't link mpi and vt, link them at last stage
