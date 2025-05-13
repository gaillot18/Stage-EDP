# include <stdio.h>
# include <stdlib.h>

# include "../../Librairies/sequentiel-2.h"


// Afficher une structure mat_2bandes (compressée)
void afficher_mat_2bandes(struct mat_2bandes *A){
    
    printf("n = %d\n", A -> n);

    int n = A -> n;

    printf("diag      =");
    for (int i = 0 ; i < n ; i ++){
        printf("%10.6f ", (A -> diag)[i]);
    }
    printf("\n");

    printf("sous_diag =");
    for (int i = 0 ; i < n - 1 ; i ++){
        printf("%10.6f ", (A -> sous_diag)[i]);
    }
    printf("\n");

}


// Afficher une strucutre mat_2bandes (décompressée) (esthétique : pas utile pour les calculs)
void afficher_mat_2bandes_totale(struct mat_2bandes *A){

    int n = A -> n;
    double zero = 0.0;

    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            if (i == j){
                printf("%10.6f ", (A -> diag)[i]);
            }
            else if (i == j + 1){
                printf("%10.6f ", (A -> sous_diag)[j]);
            }
            else{
                printf("%10.6f ", zero);
            }
        }
        printf("\n");
    }
    printf("\n");

}


// Convertir une structure mat_2bandes en matrice carré
void mat_2bandes_vers_mat(struct mat_2bandes *A, double **B){

    int n = A -> n;
    double zero = 0.0;

    *B = (double *)malloc(n * n * sizeof(double));
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            if (i == j){
                (*B)[i * n + j] = (A -> diag)[i];
            }
            else if (i == j + 1){
                (*B)[i * n + j] = (A -> sous_diag)[j];
            }
            else{
                (*B)[i * n + j] = zero;
            }
        }
    }

}


// Convertir une structure mat_2bandes en matrice carré (transposée)
void mat_2bandes_vers_mat_trans(struct mat_2bandes *A, double **B){

    int n = A -> n;
    double zero = 0.0;

    *B = (double *)malloc(n * n * sizeof(double));
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            if (i == j){
                (*B)[i * n + j] = (A -> diag)[i];
            }
            else if (i == j + 1){
                (*B)[j * n + i] = (A -> sous_diag)[j];
            }
            else{
                (*B)[i * n + j] = zero;
            }
        }
    }

}