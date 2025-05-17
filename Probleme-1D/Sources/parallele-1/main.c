# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <mpi.h>

# include "../../Librairies/parallele-1.h"

# define SORTIE

// ======================================================
// Déclarations des variables globales
// ======================================================
// Variable selon le rang
int rang;
int nb_cpu;

int nb_pt_divise;
int i_debut;
int i_fin;

int cpu_bord;
int voisin_gauche;
int voisin_droite;

// Variable égale pour chaque rang
int N;
int nb_pt;
int nb_iterations;



int main(int argc, char **argv){

    // ======================================================
    // Déclarations des variables
    // ======================================================
    // Temps
    double temps_debut;
    double temps_fin;
    double temps;
    // Informations MPI
    int *nb_elements_recus = NULL;
    int *deplacements = NULL;
    // Buffers MPI
    double *f_divise;
    double *u_divise;
    // Buffers rang 0
    double *u = NULL;
    double *u_exact = NULL;
    // Autres résultats
    double erreur_infty;
    // Fichiers
    const char *entete;
    double resultats[6];
    const char *nom_fichier_txt;
    // Paramètres
    if (argc > 1){
        N = atoi(argv[1]);
    }
    else{
        N = 10;
    }
    nb_pt = N + 1;



    // ======================================================
    // Initialisation de MPI
    // ======================================================
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_cpu);

    # ifdef SORTIE
    if (rang == 0){
        printf("------------------------------------------------------------\n");
        printf("Exécution parallèle (pour %d processus) de : parallele-1\n", nb_cpu);
    }
    # endif

    

    // ======================================================
    // Récupération des informations de chaque processus
    // ======================================================
    infos_processus();
    infos_topologie();
    if (rang == 0){
        infos_gather(&deplacements, &nb_elements_recus);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    # ifdef SORTIE
    if (rang == 0){
        printf("nb_elements_recu = "); afficher_vecteur_int(nb_elements_recus, nb_cpu);
        printf("deplacements = "); afficher_vecteur_int(deplacements, nb_cpu);
    }
    printf("rang = %d, voisin_gauche = %d, voisin_droite = %d, cpu_bord = %d, nb_pt_divise = %d, i_debut = %d, i_fin = %d\n", rang, voisin_gauche, voisin_droite, cpu_bord, nb_pt_divise, i_debut, i_fin);
    # endif
    
    

    // ======================================================
    // Calcul de f_divise, u_divise et u_exact
    // ======================================================
    f_0(&f_divise);
    u_divise = (double *)malloc(nb_pt_divise * sizeof(double));

    if (rang == 0){
        u_exact = (double *)malloc(nb_pt * sizeof(double));
        calculer_u_exact(u_0, u_exact);
    }
    


    // ======================================================
    // Calcul de u_divise et u avec mesure de temps
    // ======================================================
    temps_debut = MPI_Wtime();
    calculer_u_jacobi(f_divise, u_divise);
    if (rang == 0){
        u = (double *)malloc(nb_pt * sizeof(double));
    }
    MPI_Gatherv(u_divise, nb_pt_divise, MPI_DOUBLE, u, nb_elements_recus, deplacements, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    temps_fin = MPI_Wtime();
    temps = temps_fin - temps_debut;
    


    // ======================================================
    // Affichage d'autres informations
    // ======================================================
    if (rang == 0){
        erreur_infty = norme_infty_diff(u, u_exact, nb_pt);
        printf("N = %d\nnb_iterations, %d, erreur_L2 = %f\ntemps = %f sec\n", N, nb_iterations, erreur_infty, temps);
    }
    

    
    // ======================================================
    // Sauvegarde des résultats dans un fichier
    // ======================================================
    if (rang == 0){
        nom_fichier_txt = "./Textes/resultats.txt";
        entete = "version nb_cpu N nb_iterations erreur_infty temps";
        resultats[0] = 2.0; resultats[1] = (double)nb_cpu; resultats[2] = (double)N; resultats[3] = (double)nb_iterations; resultats[4] = erreur_infty; resultats[5] = temps;
        ecrire_resultats(resultats, entete, 6, nom_fichier_txt);
    }



    // ======================================================
    // Libérations de la mémoire
    // ======================================================
    free(u_divise);
    free(f_divise);
    if (rang == 0){
        free(u);
        free(u_exact);
        free(nb_elements_recus);
        free(deplacements);
    }



    // ======================================================
    // Fermeture de MPI
    // ======================================================
    # ifdef SORTIE
    if (rang == 0){
        printf("Éxecution terminée\n");
        printf("------------------------------------------------------------\n");
    }
    # endif
    MPI_Finalize();

    return 0;

}