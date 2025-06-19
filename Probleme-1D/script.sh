#!/bin/bash

BIN="./Binaires"

# Compilation

make all

# Exécution

echo " "
echo "EXECUTIONS POUR PROBLEME-1D"
echo " "
sleep 1

for size in 5 10 50 100 300 500 700 1500; do
    $BIN/base $size

    $BIN/sequentiel-1 $size

    for n in 1 2 4 6 8; do
        OMP_NUM_THREADS=$n $BIN/parallele-1 $size
    done

    for n in 1 2 4; do
        mpiexec -n $n $BIN/parallele-2 $size
    done

    $BIN/sequentiel-2 $size
done