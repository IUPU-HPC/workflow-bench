Decaf integration

suggestions from Matatthieua:
    use new overflow version of decf to enable large global size: see 
        decaf_examples/my_skelless scripts/vector_skel_2176v1088.overflow.job
    use ArrayField instead of Vector
    use "proc" distribution instead of "count"


now I only tried mpi tranpsort
cci might be different

#### performance when using different link procsses in single node
* 68v34 in stampede, using different number of link processes in one link node(as of Jan 4)
    link_processes  jobid   end2endtime
    4   564150  80.6s
    8   564147  68.5s
    16  565087  58.3s
    32  564146  56.2s
    64  564152  52.9s
    68  564157  53.2s


#### performance when using different link procsses in single node at bridges
    8 82.3s


1. vectot_skel.job
    need set path, decaf_prefix in bash file
    

#### configuration in bridges
all the operations are done in $WORK/software, where WORK is pointed to the scratch directory in Bridges
1. build boost(system default boost with with intel)
    * get source
    ```shell
    cd software
    wget https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.gz
    ```
    * build

    ```shell
    tar -xf boost_1_64_0.tar.gz
    cd boost_1_64_0
    ./bootstrap.sh --prefix=$WORK/software/install/
    ./b2 install
    ```
2. networkx
    ```shell
    pip install --user networkx
    ```

3. build cci
    ```shell
    cd software
    wget http://cci-forum.com/wp-content/uploads/2017/05/cci-2.1.tar.gz
    tar -xf cci-2.1.tar.gz
    cd cci-2.1
    ./configure CFLAGS='-O3' --prefix=$WORK/software/install &>config.lifen.log
    ```

4. build decaf
    ```
    cd software
    git clone https://bitbucket.org/tpeterka1/decaf.git
    mkdir build
    cd build
    sh path_to_project/configs/decaf_install.bridges # there is also a build without -O3 build_slow
    # make takes very long in bridges
    make 
    make install

    # set env variable
    export WORK=/pylon2/ac561jp/fli5
    export PATH=$WORK/software/install/include:$WORK/software/install/bin:$PATH
    export LD_LIBRARY_PATH=$WORK/software/install/lib:$LD_LIBRARY_PATH

    export DECAF_PREFIX=$WORK/software/install
    ```
  


