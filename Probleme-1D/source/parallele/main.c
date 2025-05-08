# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <mpi.h>

# include "../../librairie/parallele.h"

# define DEBUG 1

int rang;
int nb_cpu;

int nb_pt_divise;
int i_debut;
int i_fin;

int cpu_bord;
int voisin_gauche;
int voisin_droite;

int N;
int nb_pt;

int main(int argc, char **argv){

    double temps_debut;
    double temps_fin;
    double temps;

    int *nb_elements_recus = NULL;
    int *deplacements = NULL;

    double *f_divise;
    double *u_divise;
    double *u = NULL;
    double *u_exact = NULL;

    double erreur_L2 = 0;

    N = 1000;
    nb_pt = N + 1;

    /* —————————————————————————————————————————————————— */
    // Initialisation de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_cpu);

    if (rang == 0){
        printf("——————————————————————————————————————————————————\n");
        printf("Éxecution parallèle pour %d processus\n", nb_cpu);
    }
    //
    /* —————————————————————————————————————————————————— */
    /* —————————————————————————————————————————————————— */
    // Récupérer les informations sur le partage
    infos_processus(nb_pt, &nb_pt_divise, &i_debut, &i_fin);
    infos_topologie(&cpu_bord, &voisin_gauche, &voisin_droite);
    infos_gather(&deplacements, &nb_elements_recus);
    //
    /* —————————————————————————————————————————————————— */
    /* —————————————————————————————————————————————————— */
    // Afficher des informations
    # if (DEBUG == 1)
    printf("rang = %d, voisin_gauche = %d, voisin_droite = %d, cpu_bord = %d, nb_pt_divise = %d, i_debut = %d, i_fin = %d\n", rang, voisin_gauche, voisin_droite, cpu_bord, nb_pt_divise, i_debut, i_fin);
    # endif
    //
    /* —————————————————————————————————————————————————— */
    /* —————————————————————————————————————————————————— */
    // Initialiser les buffers et calculer la solution exacte
    f_1(&f_divise);
    u_divise = (double *)malloc(nb_pt_divise * sizeof(double));

    if (rang == 0){
        u = (double *)malloc(nb_pt * sizeof(double));
        u_exact = (double *)malloc(nb_pt * sizeof(double));
        calculer_u_exact(u_1, u_exact);
    }
    //
    /* —————————————————————————————————————————————————— */
    /* —————————————————————————————————————————————————— */
    // Calculs partiels et fusion des résultats avec prise de temps
    temps_debut = MPI_Wtime();
    calculer_u_jacobi(f_divise, u_divise);
    MPI_Gatherv(u_divise, nb_pt_divise, MPI_DOUBLE, u, nb_elements_recus, deplacements, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    temps_fin = MPI_Wtime();
    temps = temps_fin - temps_debut;
    //
    /* —————————————————————————————————————————————————— */
    /* —————————————————————————————————————————————————— */
    // Affichage des résultats
    # if (DEBUG == 1)
    if (N < 1000){
        char message[] = "solution approchée partielle";
        affichage_ordonne(u_divise, nb_pt_divise, message);
        if (rang == 0){
            printf("rang = %d, solution approchée :\n", rang); afficher_vecteur(u, nb_pt);
        }
    }
    if (rang == 0){
        erreur_L2 = norme_L2_diff(u, u_exact, nb_pt);
        printf("Norme L2 de l'erreur = %f\n", erreur_L2);
        printf("Temps : %f sec\n", temps);
    }
    # endif
    //
    /* —————————————————————————————————————————————————— */
    /* —————————————————————————————————————————————————— */
    // Libération de mémoire et fermeture de MPI
    if (rang == 0){
        printf("Éxecution terminée\n");
        printf("——————————————————————————————————————————————————\n");
    }
    free(u_divise);
    if (rang == 0){
        free(u);
        free(u_exact);
    }
    free(f_divise);
    MPI_Finalize();
    //
    /* —————————————————————————————————————————————————— */
    
    return 0;

}