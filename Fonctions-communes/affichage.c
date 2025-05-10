# include <stdio.h>
# ifdef USE_MPI
# include <mpi.h>
# endif

// Afficher une matrice carré de doubles
void afficher_matrice_carre_double(double *t, int n){
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            printf("%10.6f ", t[i * n + j]);
        }
        printf("\n");
    }
}

// Afficher une matrice carré d'int
void afficher_matrice_carre_int(int *t, int n){
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            printf("%d ", t[i * n + j]);
        }
        printf("\n");
    }
}

// Afficher un vecteur de doubles
void afficher_vecteur_double(double *t, int n){
    for (int i = 0 ; i < n ; i ++){
        printf("%10.6f ", t[i]);
    }
    printf("\n");
}

// Afficher un vecteur d'int
void afficher_vecteur_int(int *t, int n){
    for (int i = 0 ; i < n ; i ++){
        printf("%d ", t[i]);
    }
    printf("\n");
}