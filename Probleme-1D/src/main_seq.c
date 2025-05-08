# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>

# include "../lib/lib0.h"

int rang;
static int nb_rang;
# pragma omp threadprivate(rang)

int main(int argc, char **argv){

    srand(time(NULL));

    # pragma omp parallel
    {
        # ifdef _OPENMP
        nb_rang = omp_get_num_threads();
        rang = omp_get_thread_num();
        # endif
    }

    //int n = atoi(argv[1]);

    struct timeval t_elapsed_0, t_elapsed_1;
    double t_elapsed;

    /* Début de la préparation des données */

    int N = 30;
    int nb_pt = N + 1;
    double *f = (double *)malloc(nb_pt * sizeof(double));
    f_0(N, f);
    double *u = (double *)malloc(nb_pt * sizeof(double));

    double *u_exact = (double *)malloc(nb_pt * sizeof(double));
    calculer_u_exact(N, u_0, u_exact);

    //double *A = (double *)malloc(8 * 8 * sizeof(double));
    //generer_A(6, A);
    //afficher_matrice(A, 4);

    /* Fin de la préparation des données */

    gettimeofday(&t_elapsed_0, NULL);

    /* Début du calcul */

    calculer_u_jacobi(f, N, u);
    double erreur_L2 = norme_L2(u, u_exact, nb_pt);
    if (N < 1000){
        printf("Solution approchée :\n"); afficher_vecteur(u, nb_pt);
        printf("Solution exacte :\n"); afficher_vecteur(u_exact, nb_pt);
    }
    printf("Norme L2 de l'erreur = %f\n", erreur_L2);

    /* Fin du calcul */

    gettimeofday(&t_elapsed_1, NULL);
    t_elapsed = (t_elapsed_1.tv_sec - t_elapsed_0.tv_sec) + (t_elapsed_1.tv_usec - t_elapsed_0.tv_usec) / (double)1000000;
    printf("Temps : %f sec\n", t_elapsed);

    //free(A);
    free(f);
    free(u_exact);
    free(u);
    
    return 0;
}