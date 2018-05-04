.. _transport_install:

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



    


    
    
    
    

