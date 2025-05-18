#!/bin/bash

BIN="./Binaires"

# Compilation

make all

# Exécution

echo "EXECUTIONS POUR PROBLEME-1D"
echo " "
sleep 1

for size in 5 10 50 100 300 500; do
    $BIN/sequentiel-1 $size
    sleep 1

    for n in 1 2 4 6 8; do
        mpiexec -n $n $BIN/parallele-1 $size
        sleep 1
    done

    $BIN/sequentiel-2 $size
    sleep 1
done