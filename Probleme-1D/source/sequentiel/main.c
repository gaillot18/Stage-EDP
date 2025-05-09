# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>

# include "../../librairie/sequentiel.h"

int N;
int nb_pt;

int main(int argc, char **argv){

    setvbuf(stdout, NULL, _IONBF, 0);

    printf("——————————————————————————————————————————————————\n");
    printf("Éxecution séquentielle\n");

    struct timeval t_elapsed_0, t_elapsed_1;
    double t_elapsed;

    /* Début de la préparation des données */

    N = 30;
    nb_pt = N + 1;
    double *f;
    f_0_seq(&f);
    double *u = (double *)malloc(nb_pt * sizeof(double));

    double *u_exact = (double *)malloc(nb_pt * sizeof(double));
    calculer_u_exact_seq(u_0_seq, u_exact);

    /* Fin de la préparation des données */

    gettimeofday(&t_elapsed_0, NULL);

    /* Début du calcul */

    calculer_u_jacobi_seq(f, u);
    double erreur_L2 = norme_L2_diff(u, u_exact, nb_pt);
    if (N < 1000){
        printf("Solution approchée :\n"); afficher_vecteur(u, nb_pt);
        printf("Solution exacte :\n"); afficher_vecteur(u_exact, nb_pt);
    }
    printf("erreur_L2 = %f\n", erreur_L2);

    /* Fin du calcul */

    gettimeofday(&t_elapsed_1, NULL);
    t_elapsed = (t_elapsed_1.tv_sec - t_elapsed_0.tv_sec) + (t_elapsed_1.tv_usec - t_elapsed_0.tv_usec) / (double)1000000;
    printf("temps : %f sec\n", t_elapsed);

    free(f);
    free(u_exact);
    free(u);

    printf("Éxecution terminée\n");
    printf("——————————————————————————————————————————————————\n");
    
    return 0;
}