#!/bin/bash

BIN="./Binaires"

# Compilation

make all

# Exécution

echo " "
echo "EXECUTIONS POUR PROBLEME-CHALEUR"
echo " "
sleep 1

for size in 1; do
    #$BIN/base $size

    $BIN/sequentiel-1 0 1 200 1 160000

    for n in 1 2 4 6 8; do
        OMP_NUM_THREADS=$n $BIN/parallele-1 0 1 200 1 160000
    done

    #for n in 1 2 4 6 8; do
        #mpiexec -n $n $BIN/parallele-2 $size
    #done

    #for n in 1 2 4 6 8; do
        #mpiexec -n $n $BIN/parallele-3 $size
    #done

    #$BIN/sequentiel-2 $size

    #$BIN/sequentiel-3 $size
done