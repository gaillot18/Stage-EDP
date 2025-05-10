# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>

# include "../../Librairie/sequentiel-2.h"

# define SORTIE 1

// ======================================================
// Déclarations des variables globales
// ======================================================

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



    // ======================================================
    // Calcul de u avec mesure de temps
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