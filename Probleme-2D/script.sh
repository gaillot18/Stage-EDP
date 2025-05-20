#!/bin/bash

BIN="./Binaires"

# Compilation

make all

# Exécution

echo " "
echo "EXECUTIONS POUR PROBLEME-2D"
echo " "
sleep 1

for size in 5 10 50 100 300 500 700; do
    $BIN/sequentiel-1 $size
    #sleep 1

    for n in 1 2 4 6 8; do
        OMP_NUM_THREADS=$n $BIN/parallele-1 $size
        #sleep 1
    done

    for n in 1 2 4 6 8; do
        mpiexec -n $n $BIN/parallele-2 $size
        #sleep 1
    done

    for n in 1 2 4 6 8; do
        mpiexec -n $n $BIN/parallele-3 $size
        #sleep 1
    done
done