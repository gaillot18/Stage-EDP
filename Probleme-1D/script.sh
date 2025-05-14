BIN="./Binaires"

# Compilation

make all

# Éxecution

echo EXECUTIONS POUR PROBLEME-1D
sleep 3
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
$BIN/sequentiel-2
sleep 1
$BIN/sequentiel-2 2
sleep 1
$BIN/sequentiel-2 3
sleep 1
$BIN/sequentiel-2 4
sleep 1
$BIN/sequentiel-2 5
sleep 1
$BIN/sequentiel-2 10
sleep 1
$BIN/sequentiel-2 50
sleep 1
$BIN/sequentiel-2 100
sleep 1
$BIN/sequentiel-2 1000