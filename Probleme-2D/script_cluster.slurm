#!/bin/bash
#SBATCH --job-name=Probleme-2D
#SBATCH --output=/home/etu-f_chps_m1-08/scratch/Probleme-2D/result_%j.out
#SBATCH --error=/home/etu-f_chps_m1-08/scratch/Probleme-2D/result_%j.err
#SBATCH --ntasks=4
#SBATCH --time=00:15:00
#SBATCH --partition=standard

# module load gcc
# module load openmpi
# module load cwipi/gcc-7.5.0/0.11.1

srun ./script.sh