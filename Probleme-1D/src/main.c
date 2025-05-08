# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <mpi.h>

# include "../lib/lib0.h"

# define DEBUG 1

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

    int N = 300;
    int nb_pt = N + 1;

    /* —————————————————————————————————————————————————— */
    /* Partager le travail */
    quotient = nb_pt / nb_cpu;
    reste = nb_pt % nb_cpu;
    
    if (rang < reste) {
        nb_pt_divise = quotient + 1;
        i_debut = rang * nb_pt_divise;
    } else {
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

    # if (DEBUG == 1)
    printf("rang = %d, voisin_gauche = %d, voisin_droite = %d, cpu_bord = %d, nb_pt_divise = %d, i_debut = %d, i_fin = %d\n", rang, voisin_gauche, voisin_droite, cpu_bord, nb_pt_divise, i_debut, i_fin);
    # endif

    MPI_Barrier(MPI_COMM_WORLD);
    /* —————————————————————————————————————————————————— */

    /* —————————————————————————————————————————————————— */
    /* Pour chaque processus : initialiser sa partie de f et de u */
    double *f = (double *)malloc(nb_pt_divise * sizeof(double));
    f_0(nb_pt_divise, f);
    double *u = (double *)malloc(nb_pt_divise * sizeof(double));

    //double *u_exact = (double *)malloc(nb_pt * sizeof(double));
    //calculer_u_exact(N, u_0, u_exact);

    //double *A = (double *)malloc(8 * 8 * sizeof(double));
    //generer_A(6, A);
    //afficher_matrice(A, 4);

    /* Fin de la préparation des données */

    /* Début du calcul */

    temps_debut = MPI_Wtime();
    calculer_u_jacobi(f, N, u);
    temps_fin = MPI_Wtime();
    temps = temps_fin - temps_debut;
    //double erreur_L2 = norme_L2(u, u_exact, nb_pt);
    if (N < 1000){
        printf("rang = %d, solution approchée :\n", rang); afficher_vecteur(u, nb_pt_divise);
        //printf("Solution exacte :\n"); afficher_vecteur(u_exact, nb_pt);
    }
    //printf("Norme L2 de l'erreur = %f\n", erreur_L2);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rang == 0){
        printf("Temps : %f sec\n", temps);
    }

    /* Fin du calcul */

    /*free(A);
    free(f);
    free(u_exact);
    free(u);
    */

    MPI_Finalize();
    
    return 0;

}