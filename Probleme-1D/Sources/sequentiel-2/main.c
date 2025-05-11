# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>

# include "../../Librairies/sequentiel-2.h"

# define SORTIE 1
# define EXEMPLE 1

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
    double *f;
    double *u;
    double *u_exact;
    // Autres résultats
    double erreur_L2 = 0;
    // Fichiers
    char *nom_fichier_data;
    char *nom_fichier_txt;
    // Paramètres
    N = 1000;
    nb_pt = N + 1;


    // ======================================================
    // Initialisation
    // ======================================================
    # ifdef SORTIE
    printf("------------------------------------------------------------\n");
    printf("Éxecution séquentielle\n");
    # endif


    // ======================================================
    // Illustration de la structure mat_2bandes
    // ======================================================
    # ifdef EXEMPLE
    {
        printf("\n-------------------------\n");
        printf("Illustration de la structure mat_2bandes (exemple pour N petit) :\n");
        int N = 5;
        int nb_pt = N + 1;
        double h = 1.0 / (nb_pt + 1 - 2);
        double alpha = 2.0 / (h * h);
        double beta = - 1.0 / (h * h);
        struct mat_2bandes L;

        calculer_cholesky_tridiag(alpha, beta, nb_pt - 2, &L);

        printf("alpha = %10.6f, beta = %10.6f\n", alpha, beta);
        printf("\nStructure mat2_bandes :\n");
        afficher_mat_2bandes(&L);

        double *A;
        mat_2bandes_vers_mat(&L, &A);
        printf("\nMatrice réelle correspondante :\n");
        afficher_matrice_carre_double(A, nb_pt - 2);

        free(A);
        free(L.diag);
        free(L.sous_diag);
        printf("-------------------------\n\n");

    }
    # endif


    // ======================================================
    // Calcul de f et u_exact
    // ======================================================
    f_1(&f);
    u = (double *)malloc(nb_pt * sizeof(double));
    u_exact = (double *)malloc(nb_pt * sizeof(double));
    calculer_u_exact(u_1, u_exact);


    // ======================================================
    // Calcul de u avec mesure de temps
    // ======================================================
    gettimeofday(&temps_debut, NULL);
    resoudre_cholesky(f, u);
    gettimeofday(&temps_fin, NULL);
    temps = (temps_fin.tv_sec - temps_debut.tv_sec) + (temps_fin.tv_usec - temps_debut.tv_usec) / (double)1000000;


    // ======================================================
    // Affichage d'autres informations
    // ======================================================
    erreur_L2 = norme_L2_diff(u, u_exact, nb_pt);
    # ifdef SORTIE
    if (nb_pt <= 100){
        afficher_vecteur_double(u, nb_pt);
    }
    printf("erreur_L2 = %f\ntemps = %f sec\n", erreur_L2, temps);
    # endif



    // ======================================================
    // Sauvegarde de u dans un fichier
    // ======================================================
    nom_fichier_data = (char *)malloc(128 * sizeof(char));
    nom_fichier_txt = (char *)malloc(128 * sizeof(char));
    sprintf(nom_fichier_data, "./Textes/sequentiel-2/resultats0.data");
    sprintf(nom_fichier_txt, "./Textes/sequentiel-2/resultats0.txt");
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