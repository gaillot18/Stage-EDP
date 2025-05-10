# include <stdio.h>

# include "../../Librairies/sequentiel-2.h"

// Afficher une structure mat_2bandes (compressée)
void afficher_mat_2bandes(struct mat_2bandes *A){
    
    printf("%d\n", A -> n);

    int n = A -> n;
    for (int i = 0 ; i < n ; i ++){
        printf("%10.6f ", (A -> diag)[i]);
    }
    printf("\n");

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