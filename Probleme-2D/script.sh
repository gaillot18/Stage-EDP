#!/bin/bash

BIN="./Binaires"

# Compilation

make all

# Exécution

echo " "
echo "EXECUTIONS POUR PROBLEME-2D"
echo " "
sleep 1

for size in 1000 1500 2000 2500 3000 3500 4000 4500 5000 5500; do
    #$BIN/sequentiel-1 $size
    #sleep 1

    #for n in 1 2 4 6 8; do
        #OMP_NUM_THREADS=$n $BIN/parallele-1 $size
        #sleep 1
    #done

    #for n in 1 2 4 6 8; do
        #mpiexec -n $n $BIN/parallele-2 $size
        #sleep 1
    #done

    #for n in 1 2 4 6 8; do
        #mpiexec -n $n $BIN/parallele-3 $size
        #sleep 1
    #done

    #$BIN/sequentiel-2 $size
    #sleep 1

    $BIN/sequentiel-3 $size
    #sleep 1
done