#!/bin/bash

BIN="./Binaires"

# Compilation

make all

# Exécution

echo " "
echo "EXECUTIONS POUR PROBLEME-CHALEUR (calcul des erreurs)"
echo " "
sleep 1

for h in 0.1 0.05 0.02 0.01 0.005; do
    for h_t in 0.0001 0.00005 0.00002 0.00001 0.000005; do
        $BIN/sequentiel-2 1 1 $h 1 $h_t
    done
done