# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>

# include "../../Librairie/sequentiel.h"

# define SORTIE 1

// ======================================================
// Déclarations des variables globales
// ======================================================
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
    // Buffers
    double *f;
    double *u;
    double *u_exact;
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
    // Initialisation
    // ======================================================
    # ifdef SORTIE
    printf("------------------------------------------------------------\n");
    printf("Éxecution séquentielle\n");
    # endif



    // ======================================================
    // Calcul de f_divise, u_divise et u_exact
    // ======================================================
    f_0(&f);
    u = (double *)malloc(nb_pt * sizeof(double));
    u_exact = (double *)malloc(nb_pt * sizeof(double));
    calculer_u_exact(u_0, u_exact);



    // ======================================================
    // Calcul de u avec mesure de temps
    // ======================================================
    gettimeofday(&temps_debut, NULL);
    calculer_u_jacobi(f, u);
    gettimeofday(&temps_fin, NULL);
    temps = (temps_fin.tv_sec - temps_debut.tv_sec) + (temps_fin.tv_usec - temps_debut.tv_usec) / (double)1000000;



    // ======================================================
    // Affichage d'autres informations
    // ======================================================
    erreur_L2 = norme_L2_diff(u, u_exact, nb_pt);
    # ifdef SORTIE
    afficher_vecteur_double(u, nb_pt);
    printf("nb_iterations, %d, erreur_L2 = %f\ntemps = %f sec\n", nb_iterations, erreur_L2, temps);
    # endif



    // ======================================================
    // Sauvegarde de u dans un fichier
    // ======================================================
    nom_fichier_data = (char *)malloc(128 * sizeof(char));
    nom_fichier_txt = (char *)malloc(128 * sizeof(char));
    sprintf(nom_fichier_data, "./texte/resultats0.data");
    sprintf(nom_fichier_txt, "./texte/resultats0.txt");
    ecrire_double(nom_fichier_data, nom_fichier_txt, u, nb_pt);



    // ======================================================
    // Libérations de la mémoire
    // ======================================================
    free(nom_fichier_data);
    free(nom_fichier_txt);
    free(f);
    free(u_exact);
    free(u);



    // ======================================================
    // Fermeture
    // ======================================================
    # ifdef SORTIE
    printf("Éxecution terminée\n");
    printf("------------------------------------------------------------\n");
    # endif
    
    return 0;
    
}