BIN="./binaire"

# Compilation

make clean
make sequentiel
make parallele

# Éxecution

$BIN/exe-sequentiel
mpiexec -n 1 $BIN/exe-parallele
mpiexec -n 2 $BIN/exe-parallele
mpiexec -n 4 $BIN/exe-parallele
mpiexec -n 6 $BIN/exe-parallele
mpiexec -n 8 $BIN/exe-parallele

make clean


