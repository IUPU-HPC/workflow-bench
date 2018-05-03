Installation guide for general methods
****************************************

Environments
============================

PSC Bridges, see `here
<https://www.psc.edu/bridges>`_


TACC Stampde2, see `here
<https://portal.tacc.utexas.edu/user-guides/stampede2>`_



Modules
============================
Modules in Bridges::

Modules in Stampede2::
    Currently Loaded Modules:
      1) intel/17.0.4   2) impi/17.0.3   3) git/2.9.0   4) autotools/1.1   5) python/2.7.13   6) xalt/1.7.7   7) TACC   8) cmake/3.10.2   9) remora/1.8.1  10) boost/1.64  11) phdf5/1.8.16  12) itac/17.0.3


Install transport methods
============================

Dataspaces/Dimes
------------------

DataSpaces/Dimes 1.6.2 is used by us.

.. code-block:: shell

    wget http://personal.cac.rutgers.edu/TASSL/projects/data/downloads/dataspaces-latest.tar.gz

.. note:: 

    This may lead to newer versions than 1.6.2, which we may not have tested

    
DataSpaces can be configured using the scripts:

.. literalinclude:: /../../configs/Dataspaces.runconf

.. todo::
    
    it can be better if files can be viewed as external links

ADIOS
------------------

ADIOS can be obtained  by

.. code-block:: shell
    
    wget wget http://users.nccs.gov/~pnorbert/adios-1.13.0.tar.gz

It can be configured using the script:

.. literalinclude:: /../../configs/Adios.runconf



Flexpath
------------------

First obtain the package ::
    
     mkdir flexpath_adios_1_13 && cd flexpath_adios_1_13
     wget http://www.cc.gatech.edu/systems/projects/EVPath/chaos_bootstrap.pl

Bootstrap::

    perl chaos_bootstrap.pl adios-1.13 $WORK/envs/Flexpath &> config.lifen.log &

build and install::

    perl chaos_build.pl  -c ~/Workspaces/General_Data_Broker/lbm_adios/configs/Flexpath_build_config &> make.log &

.. todo::

    add links for flexpath conf in bridges/stampede

Decaf
-------------------------
We use decaf, commit number: 637eb58
The decaf project is `here
<https://bitbucket.org/tpeterka1/decaf>`_

Users can follow the instructions to compelete installation. 
We also provide installation scripts for bridges:

.. literalinclude:: /../../configs/decaf_install.bridges

and for stampede2: 

.. literalinclude:: /../../configs/decaf_install.stampede

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




    


    
    
    
    

