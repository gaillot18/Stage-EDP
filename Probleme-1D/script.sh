BIN="./Binaires"

# Compilation

make clean
make sequentiel-1
make parallele-1

# Éxecution

$BIN/sequentiel-1
sleep 3
mpiexec -n 1 $BIN/parallele-1
sleep 3
mpiexec -n 2 $BIN/parallele-1
sleep 3
mpiexec -n 4 $BIN/parallele-1
sleep 3
mpiexec -n 6 $BIN/parallele-1
sleep 3
mpiexec -n 8 $BIN/parallele-1
sleep 3
