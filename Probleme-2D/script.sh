#!/bin/bash

BIN="./Binaires"

# Compilation

make all

# Éxecution

echo "EXECUTIONS POUR PROBLEME-2D"
echo " "
sleep 2

for size in 5 10 50 100 300; do
    $BIN/sequentiel-1 $size
    sleep 2

    for n in 1 2 4 6 8; do
        mpiexec -n $n $BIN/parallele-1 $size
        sleep 2
    done
done