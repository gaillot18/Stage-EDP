BIN="./binaire"

# Compilation

make clean
make sequentiel
make parallele

# Éxecution

$BIN/exe-sequentiel
sleep 3
mpiexec -n 1 $BIN/exe-parallele
sleep 3
mpiexec -n 2 $BIN/exe-parallele
sleep 3
mpiexec -n 4 $BIN/exe-parallele
sleep 3
mpiexec -n 6 $BIN/exe-parallele
sleep 3
mpiexec -n 8 $BIN/exe-parallele
sleep 3
