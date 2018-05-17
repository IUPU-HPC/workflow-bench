BUILD:
    cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/stampede_tau.toolchain.cmake ..

export TAU_OPTIONS="-optRevert -optTauSelectFile=/home1/04446/tg837458/Workspaces/General_Data_Broker/lbm_adios/configs/select.tau"
export TAU_SELECT_FILE=/home1/04446/tg837458/Workspaces/General_Data_Broker/lbm_adios/configs/select.tau
