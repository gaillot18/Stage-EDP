# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <mpi.h>

# include "../../Librairie/parallele.h"

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
    // Résultats
    double erreur_L2 = 0;
    nb_iterations = 0;
    // Fichiers
    FILE *descripteur;
    char *nom_fichier_data;
    char *nom_fichier_txt;
    // Paramètres
    N = 30;
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
        printf("Éxecution parallèle pour %d processus\n", nb_cpu);
    }
    # endif

    

    // ======================================================
    // Récupération des informations de chaque processus
    // ======================================================
    infos_processus(nb_pt, &nb_pt_divise, &i_debut, &i_fin);
    infos_topologie(&cpu_bord, &voisin_gauche, &voisin_droite);
    infos_gather(&deplacements, &nb_elements_recus);
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
    # ifdef SORTIE
    if (rang == 0){
        erreur_L2 = norme_L2_diff(u, u_exact, nb_pt);
        afficher_vecteur_double(u, nb_pt);
        printf("nb_iterations, %d, erreur_L2 = %f\ntemps = %f sec\n", nb_iterations, erreur_L2, temps);
    }
    # endif
    

    
    // ======================================================
    // Sauvegarde de u dans un fichier
    // ======================================================
    if (rang == 0){
        nom_fichier_data = (char *)malloc(128 * sizeof(char));
        nom_fichier_txt = (char *)malloc(128 * sizeof(char));
        sprintf(nom_fichier_data, "./texte/resultats%d.data", nb_cpu);
        sprintf(nom_fichier_txt, "./texte/resultats%d.txt", nb_cpu);
        ecrire_double(nom_fichier_data, nom_fichier_txt, u, nb_pt);
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
        free(nom_fichier_data);
        free(nom_fichier_txt);
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