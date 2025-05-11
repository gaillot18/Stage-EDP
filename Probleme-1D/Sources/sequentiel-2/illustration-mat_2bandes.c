# include <stdio.h>

# include "../../Librairies/sequentiel-2.h"

int main(){

    int N = 4;
    int nb_pt = N + 1;
    double h = 1.0 / (nb_pt + 1 - 2);
    double alpha = 2.0 / (h * h);
    double beta = - 1.0 / (h * h);
    struct mat_2bandes L;

    calculer_cholesky_tridiag(alpha, beta, nb_pt - 2, &L);

    printf("N = %d, nb_pt = %d, alpha = %10.6f, beta = %10.6f\n", N, nb_pt, alpha, beta);
    afficher_mat_2bandes(&L);

    free(L.diag);
    free(L.sous_diag);

    return 0;

}