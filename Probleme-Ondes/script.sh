#!/bin/bash

BIN="./Binaires"

# Compilation

make all

# Exécution

echo " "
echo "EXECUTIONS POUR PROBLEME-ONDES"
echo " "
sleep 1

for size in 100 300 500; do

    $BIN/sequentiel-1 $size

done