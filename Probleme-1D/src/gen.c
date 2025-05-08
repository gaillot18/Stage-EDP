# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# ifdef USE_MPI
# include <mpi.h>
# endif

# include "../lib/lib0.h"

void afficher_matrice(double *t, int n){
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            printf("%f ", t[i * n + j]);
        }
        printf("\n");
    }
}

void afficher_vecteur(double *t, int n){
    for (int i = 0 ; i < n ; i ++){
        printf("%f ", t[i]);
    }
    printf("\n");
}

void generer(int *t, int n){
    for (int i = 0 ; i < n ; i ++){
        t[i] = rand() % 10000;
    }
}