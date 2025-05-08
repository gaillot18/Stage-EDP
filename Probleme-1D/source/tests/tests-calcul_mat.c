# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>

# define N 2
# define INT_MAX 2147483647 // = 2^31 - 1

# define AFFICHAGE 0

# define TEST_init_matrice_carre_zero 0
# define TEST_somme_matrice_carre 0
# define TEST_produit_matrice_carre 1

int rang;
static int nb_rang;
# pragma omp threadprivate(rang)

int main(int argc, char **argv){

    struct timeval temps_debut, temps_fin;
    double temps_total;

    # pragma omp parallel
    {
        # ifdef _OPENMP
        nb_rang = omp_get_num_threads();
        rang = omp_get_thread_num();
        # endif
    }

    srand(50);
    double *A;
    double *B;
    double *C;

    /* Test de init_matrice_carre_zero */

    # if (TEST_init_matrice_carre_zero == 1)

    A = (double *)malloc(N * N * sizeof(double));

    init_matrice_carre_zero(N, A);

    # if (AFFICHAGE == 1)
    afficher_matrice(A, N);
    # endif
    free(A);

    # endif

    /* Test de somme_matrice_carre */

    # if (TEST_somme_matrice_carre == 1)

    A = (double *)malloc(N * N * sizeof(double));
    B = (double *)malloc(N * N * sizeof(double));
    C = (double *)malloc(N * N * sizeof(double));
    for (int i = 0 ; i < N * N ; i ++){
        A[i] = rand() / (double)INT_MAX;
        B[i] = rand() / (double)INT_MAX;
    }

    somme_matrice_carre(2, A, 0.5, B, N, C);

    # if (AFFICHAGE == 1)
    afficher_matrice(A, N);
    printf("\n");
    afficher_matrice(B, N);
    printf("\n");
    afficher_matrice(C, N);
    # endif
    free(A);
    free(B);
    free(C);
    
    # endif

    /* Test de produit_matrice_carre */

    # if (TEST_produit_matrice_carre == 1)

    A = (double *)malloc(N * N * sizeof(double));
    B = (double *)malloc(N * N * sizeof(double));
    C = (double *)malloc(N * N * sizeof(double));
    for (int i = 0 ; i < N * N ; i ++){
        A[i] = rand() / (double)INT_MAX;
        B[i] = rand() / (double)INT_MAX;
    }

    gettimeofday(&temps_debut, NULL);

    produit_matrice_carre(1, A, B, N, C);

    gettimeofday(&temps_fin, NULL);
    temps_total = (temps_fin.tv_sec - temps_debut.tv_sec) + (temps_fin.tv_usec - temps_debut.tv_usec) / (double)1000000;

    # if (AFFICHAGE == 0)
    if (N <= 4){
        afficher_matrice(A, N); printf("\n");
        afficher_matrice(B, N); printf("\n");
        afficher_matrice(C, N); printf("\n");
    }
    printf("Temps : %f sec\n", temps_total);
    # endif
    free(A);
    free(B);
    free(C);

    # endif
    
    return 0;
}