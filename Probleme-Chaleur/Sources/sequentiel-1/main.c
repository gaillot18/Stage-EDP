# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>

# include "../../Librairies/sequentiel-1.h"

// ======================================================
// Déclarations des variables globales
// ======================================================
int N;
double h;
double T;
int N_t;
double h_t;
int nb_pt;
double a = 1.0;
double alpha;
double beta;



int main(int argc, char **argv){

    // ======================================================
    // Déclarations des variables
    // ======================================================
    // Temps
    //struct timeval temps_debut;
    //struct timeval temps_fin;
    //double temps;
    // Buffers
    //double *f;
    double *u;
    //double *u_exact;
    // Autres résultats
    //double erreur_infty;
    // Fichiers
    //const char *entete;
    //double resultats[6];
    //const char *nom_fichier_txt;
    // Paramètres
    if (argc > 3){
        N = atoi(argv[1]);
        T = atoi(argv[2]);
        N_t = atoi(argv[3]);
    }
    else{
        N = 10;
        T = 10;
        N_t = 10;
    }
    nb_pt = N + 1;
    h = 1.0 / N;
    h_t = T / N_t;
    alpha = 1.0 + (4 * a * h_t / pow(h, 2));
    beta = a * h_t / pow(h, 2);


    // ======================================================
    // Initialisation
    // ======================================================
    printf("------------------------------------------------------------\n");
    printf("Exécution séquentielle de : sequentiel-1 (version 1 - schéma explicite - séquentiel)\n");



    // ======================================================
    // Calcul de f et u_exact
    // ======================================================
    //f_1(&f);
    u = (double *)malloc(nb_pt * nb_pt * sizeof(double));
    calculer_u(f_source, u);
    //u_exact = (double *)malloc(nb_pt * nb_pt * sizeof(double));
    //calculer_u_exact(u_1, u_exact);



    // ======================================================
    // Calcul de u avec mesure de temps
    // ======================================================
    //gettimeofday(&temps_debut, NULL);
    //
    //gettimeofday(&temps_fin, NULL);
    //temps = (temps_fin.tv_sec - temps_debut.tv_sec) + (temps_fin.tv_usec - temps_debut.tv_usec) / (double)1000000;



    // ======================================================
    // Affichage d'autres informations
    // ======================================================
    //erreur_infty = norme_infty_diff(u, u_exact, nb_pt * nb_pt);
    printf("N = %d\nN_t = %d\nnb_pt * nb_pt = %d\n", N, N_t, nb_pt * nb_pt);



    // ======================================================
    // Sauvegarde des résultats dans un fichier
    // ======================================================
    //nom_fichier_txt = "./Textes/resultats.txt";
    //entete = "version nb_cpu N nb_iteration erreur_infty temps";
    //resultats[0] = 1.0; resultats[1] = -1.0; resultats[2] = (double)N; resultats[3] = -1.0; resultats[4] = erreur_infty; resultats[5] = temps;
    //ecrire_resultats(resultats, entete, 6, nom_fichier_txt);



    // ======================================================
    // Libérations de la mémoire
    // ======================================================
    //free(f);
    //free(u_exact);
    free(u);



    // ======================================================
    // Fermeture
    // ======================================================
    printf("Exécution terminée\n");
    printf("------------------------------------------------------------\n");
    
    return 0;
    
}