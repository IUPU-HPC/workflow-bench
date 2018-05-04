.. _toolchain:

Toolchain settings
==============================

how to build
-----------------------

Different compiler settings are used using the cmake toochain
The build command will be like::

    cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/Bridges.toolchain.cmake  ..

For builds in Stampede 2::

    cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/Stampede2.toolchain.cmake  ..


control supported transports
------------------------------

If you don't have lammps/adios/dspaces/decaf installed, you should add the following argument in you cmake command::

    cmake .. \
        -DCMAKE_TOOLCHAIN_FILE=../cmake/Stampede2.toolchain.cmake \
        -Dall_transports=off

Build with ITAC traces
-------------------------------

To generate traces, the project should be built using::

    module load itac
    cd build_build_itac

    cmake .. \
        -DCMAKE_TOOLCHAIN_FILE=../cmake/Stampede2.toolchain.cmake  \
        -Duse_itac=on 

Build with tau trace
----------------------------------------------------------------------

.. note::
    depreciated, we use itac in newer versions

To add  support for TAU trace from Univ Oregon::

    mkdir build
    cmake -DCMAKE_BUILD_TYPE=Stampede_TAU ..
    make -j4 



