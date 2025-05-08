# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <mpi.h>

# include "../lib/lib.h"

# define DEBUG 0

int rang;
int nb_cpu;
int quotient;
int reste;
int nb_pt_divise;
int i_debut;
int i_fin;
int cpu_bord;
int voisin_gauche;
int voisin_droite;

int main(int argc, char **argv){

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_cpu);

    double temps_debut;
    double temps_fin;
    double temps;

    srand(time(NULL));

    /* Début de la préparation des données */

    int N = 1000;
    int nb_pt = N + 1;
    double erreur_L2 = 0;

    /* —————————————————————————————————————————————————— */
    /* Partager le travail */
    quotient = nb_pt / nb_cpu;
    reste = nb_pt % nb_cpu;
    
    if (rang < reste){
        nb_pt_divise = quotient + 1;
        i_debut = rang * nb_pt_divise;
    }
    else{
        nb_pt_divise = quotient;
        i_debut = reste * (quotient + 1) + (rang - reste) * quotient;
    }
    i_fin = i_debut + nb_pt_divise - 1;

    if (nb_cpu != 1){
        if (rang == 0){
            cpu_bord = -1;
        }
        else if (rang == nb_cpu - 1){
            cpu_bord = 1;
        }
        else{
            cpu_bord = 0;
        }
    }
    else{
        cpu_bord = 2;
    }

    voisin_gauche = (rang + (nb_cpu - 1)) % nb_cpu;
    voisin_droite = (rang + 1) % nb_cpu;

    int *nb_elements_recus = NULL;
    int *deplacements = NULL;
    int offset = 0;
    if (rang == 0){
        nb_elements_recus = (int *)malloc(nb_cpu * sizeof(int));
        deplacements = (int *)malloc(nb_cpu * sizeof(int));
        for (int i = 0 ; i < nb_cpu ; i++) {
            if (i < reste){
                nb_elements_recus[i] = quotient + 1;
            }
            else{
                nb_elements_recus[i] = quotient;
            }
            deplacements[i] = offset;
            offset += nb_elements_recus[i];
        }
        # if (DEBUG == 1)
        printf("nb_elements_recu = \n"); afficher_vecteur_int(nb_elements_recus, nb_cpu);
        printf("deplacements = \n"); afficher_vecteur_int(deplacements, nb_cpu);
        # endif
    }

    # if (DEBUG == 1)
    printf("rang = %d, voisin_gauche = %d, voisin_droite = %d, cpu_bord = %d, nb_pt_divise = %d, i_debut = %d, i_fin = %d\n", rang, voisin_gauche, voisin_droite, cpu_bord, nb_pt_divise, i_debut, i_fin);
    # endif

    MPI_Barrier(MPI_COMM_WORLD);
    /* —————————————————————————————————————————————————— */

    /* —————————————————————————————————————————————————— */
    /* Pour chaque processus : initialiser sa partie de f et de u */
    double *f_divise = (double *)malloc(nb_pt_divise * sizeof(double));
    f_1(N, f_divise);
    double *u_divise = (double *)malloc(nb_pt_divise * sizeof(double));
    double *u = NULL;
    if (rang == 0){
        u = (double *)malloc(nb_pt * sizeof(double));
    }

    double *u_exact = NULL;
    if (rang == 0){
        u_exact = (double *)malloc(nb_pt * sizeof(double));
        calculer_u_exact(N, u_1, u_exact);
    }

    /* Fin de la préparation des données */

    /* Début du calcul */

    temps_debut = MPI_Wtime();
    calculer_u_jacobi(f_divise, N, u_divise);
    MPI_Gatherv(u_divise, nb_pt_divise, MPI_DOUBLE, u, nb_elements_recus, deplacements, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    temps_fin = MPI_Wtime();
    temps = temps_fin - temps_debut;

    # if (DEBUG == 1)
    if (N < 1000){
        for (int i = 0 ; i < nb_cpu ; i ++){
            if (rang == i){
                printf("rang = %d, solution approchée partielle :\n", rang); afficher_vecteur(u_divise, nb_pt_divise);
            }
            MPI_Barrier(MPI_COMM_WORLD);
        }
        //printf("Solution exacte :\n"); afficher_vecteur(u_exact, nb_pt);
    }
    # endif
    MPI_Barrier(MPI_COMM_WORLD);

    if (rang == 0){
        if (N < 1000){
            printf("rang = %d, solution approchée :\n", rang); afficher_vecteur(u, nb_pt);
        }
        erreur_L2 = norme_L2_diff(u, u_exact, nb_pt);
        printf("Norme L2 de l'erreur = %f\n", erreur_L2);
        printf("Temps : %f sec\n", temps);
    }

    /* Fin du calcul */

    /*free(A);
    free(f);
    free(u_exact);
    free(u);
    */

    free(u_divise);
    if (rang == 0){
        free(u);
    }
    free(f_divise);

    MPI_Finalize();
    
    return 0;

}