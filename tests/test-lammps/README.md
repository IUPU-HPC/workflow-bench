Lammps 

#### Data
1. each produce can generate different number of atoms(around 512000), 19Mb
2. consumer will receive 2 times number of atoms(around 1024000)

#### Notes
1. lammps version: http://lammps.sandia.gov/tars/lammps-16Feb16.tar.gz
2. use lammps as a library: http://lammps.sandia.gov/doc/Section_howto.html#howto-19
3. extra_atoms and gather_atoms: http://lammps.sandia.gov/doc/Section_python.html#using-lammps-from-python
3. make stampede2 mod=lib


#### FILES
    test_lammps
    lammps_origin.job:
        use lammps executable file directly

Timing in Stampede
    run 100 in lammps excutable 2:43s
    run 100 in lammps libary (pre no post no) 3:45s
    

