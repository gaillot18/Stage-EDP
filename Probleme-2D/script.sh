#!/bin/bash

BIN="./Binaires"

# Compilation

make all

# Exécution

echo " "
echo "EXECUTIONS POUR PROBLEME-2D"
echo " "
sleep 1

for size in 300 500 700; do
    $BIN/base $size

    $BIN/sequentiel-1 $size

    for n in 1 2 4 6 8; do
        OMP_NUM_THREADS=$n $BIN/parallele-1 $size
    done

    for n in 1 2 4 6 8; do
        mpiexec -n $n $BIN/parallele-2 $size
    done

    for n in 1 2 4 6 8; do
        mpiexec -n $n $BIN/parallele-3 $size
    done

    $BIN/sequentiel-2 $size

    $BIN/sequentiel-3 $size
done