# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>
# include <mpi.h>

# include "../../Librairies/sequentiel-1.h"

# define SORTIE 1

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
    struct timeval temps_debut;
    struct timeval temps_fin;
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
    double erreur_L2;
    nb_iterations = 0;
    // Fichiers
    char *nom_fichier_data;
    char *nom_fichier_txt;
    // Paramètres
    N = 100;
    nb_pt = N + 1;


    // ======================================================
    // Initialisation
    // ======================================================
    # ifdef SORTIE
    printf("------------------------------------------------------------\n");
    printf("Exécution séquentielle de : sequentiel-1\n");
    # endif



    // ======================================================
    // Calcul de f et u_exact
    // ======================================================
    //f_1(&f);
    //u = (double *)malloc(nb_pt * nb_pt * sizeof(double));
    //u_exact = (double *)malloc(nb_pt * nb_pt * sizeof(double));
    //calculer_u_exact(u_1, u_exact);



    // ======================================================
    // Calcul de u avec mesure de temps
    // ======================================================
    gettimeofday(&temps_debut, NULL);
    //calculer_u_jacobi(f, u);
    gettimeofday(&temps_fin, NULL);
    temps = (temps_fin.tv_sec - temps_debut.tv_sec) + (temps_fin.tv_usec - temps_debut.tv_usec) / (double)1000000;



    // ======================================================
    // Affichage d'autres informations
    // ======================================================
    //erreur_L2 = norme_L2_diff(u, u_exact, nb_pt * nb_pt);
    # ifdef SORTIE
    if (nb_pt <= 10){
        //afficher_matrice_carre_double(u_exact, nb_pt); printf("\n");
        //afficher_matrice_carre_double(u, nb_pt);
    }
    //printf("N = %d\nnb_pt * nb_pt = %d\nnb_iterations = %d, erreur_L2 = %f\ntemps = %f sec\n", N, nb_pt * nb_pt, nb_iterations, erreur_L2, temps);
    # endif



    // ======================================================
    // Sauvegarde de u dans un fichier
    // ======================================================
    /*
    nom_fichier_data = (char *)malloc(128 * sizeof(char));
    nom_fichier_txt = (char *)malloc(128 * sizeof(char));
    sprintf(nom_fichier_data, "./Textes/sequentiel-1/resultats0.data");
    sprintf(nom_fichier_txt, "./Textes/sequentiel-1/resultats0.txt");
    ecrire_double(nom_fichier_data, nom_fichier_txt, u, nb_pt);*/



    // ======================================================
    // Libérations de la mémoire
    // ======================================================
    //free(nom_fichier_data);
    //free(nom_fichier_txt);
    //free(f);
    //ree(u_exact);
    //free(u);



    // ======================================================
    // Fermeture
    // ======================================================
    # ifdef SORTIE
    printf("Éxecution terminée\n");
    printf("------------------------------------------------------------\n");
    # endif
    
    return 0;
    
}