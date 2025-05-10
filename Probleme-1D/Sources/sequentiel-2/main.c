# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>

# include "../../Librairies/sequentiel-2.h"

# define SORTIE 1

// ======================================================
// Déclarations des variables globales
// ======================================================
int N;
int nb_pt;

int main(int argc, char **argv){

    // ======================================================
    // Déclarations des variables
    // ======================================================
    // Temps
    struct timeval temps_debut;
    struct timeval temps_fin;
    double temps;
    // Buffers
    // Résultats
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
    // 
    // ======================================================
    int n = 5;
    double h = 1.0 / (n + 1);
    double alpha = 2.0 / (h * h);
    double beta = - 1.0 / (h * h);
    struct mat_2bandes L;
    calculer_cholesky_tridiag(alpha, beta, n, &L);
    printf("n = %d, h = %f, alpha = %f, beta = %f\n", n, h, alpha, beta);
    afficher_mat_2bandes(&L); printf("\n");
    afficher_mat_2bandes_totale(&L);
    free(L.diag);
    free(L.sous_diag);



    // ======================================================
    // 
    // ======================================================
    gettimeofday(&temps_debut, NULL);
    // Calcul
    gettimeofday(&temps_fin, NULL);
    temps = (temps_fin.tv_sec - temps_debut.tv_sec) + (temps_fin.tv_usec - temps_debut.tv_usec) / (double)1000000;



    // ======================================================
    // Affichage d'autres informations
    // ======================================================
    # ifdef SORTIE
    # endif



    // ======================================================
    // Sauvegarde de u dans un fichier
    // ======================================================



    // ======================================================
    // Libérations de la mémoire
    // ======================================================



    // ======================================================
    // Fermeture
    // ======================================================
    # ifdef SORTIE
    printf("Éxecution terminée\n");
    printf("------------------------------------------------------------\n");
    # endif
    
    return 0;
    
}