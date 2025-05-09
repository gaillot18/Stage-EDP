# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <mpi.h>

# include "../../librairie/parallele.h"

# define SORTIE

# define TAILLE_buffer_print 8192

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

char *buffer_print;
MPI_File descripteur;

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

    char *nom_fichier_data;
    char *nom_fichier_txt;

    N = 30;
    nb_pt = N + 1;

    # ifdef SORTIE
    buffer_print = (char *)malloc(TAILLE_buffer_print * sizeof(char));
    # endif

    /* —————————————————————————————————————————————————— */
    // Initialisation de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_cpu);

    # ifdef SORTIE
    nom_fichier_data = (char *)malloc(128 * sizeof(char));
    nom_fichier_txt = (char *)malloc(128 * sizeof(char));
    sprintf(nom_fichier_data, "./texte/resultats%d.data", nb_cpu);
    sprintf(nom_fichier_txt, "./texte/resultats%d.txt", nb_cpu);
    MPI_File_open(MPI_COMM_WORLD, nom_fichier_txt, MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &descripteur);
    if (rang == 0){
        sprintf(buffer_print, "------------------------------------------------------------\n"); printf("%s", buffer_print);
        MPI_File_write(descripteur, buffer_print, strlen(buffer_print), MPI_CHAR, MPI_STATUS_IGNORE);
        sprintf(buffer_print, "Execution parallèle pour %d processus\n", nb_cpu); printf("%s", buffer_print);
        MPI_File_write(descripteur, buffer_print, strlen(buffer_print), MPI_CHAR, MPI_STATUS_IGNORE);
    }
    # endif
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
    # ifdef SORTIE
    sprintf(buffer_print, "rang = %d, voisin_gauche = %d, voisin_droite = %d, cpu_bord = %d, nb_pt_divise = %d, i_debut = %d, i_fin = %d\n", rang, voisin_gauche, voisin_droite, cpu_bord, nb_pt_divise, i_debut, i_fin); printf("%s", buffer_print);
    MPI_File_write_ordered(descripteur, buffer_print, strlen(buffer_print), MPI_CHAR, MPI_STATUS_IGNORE);
    # endif
    //
    /* —————————————————————————————————————————————————— */
    /* —————————————————————————————————————————————————— */
    // Initialiser les buffers et calculer la solution exacte
    f_0(&f_divise);
    u_divise = (double *)malloc(nb_pt_divise * sizeof(double));

    if (rang == 0){
        u = (double *)malloc(nb_pt * sizeof(double));
        u_exact = (double *)malloc(nb_pt * sizeof(double));
        calculer_u_exact(u_0, u_exact);
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
    if (rang == 0){
        erreur_L2 = norme_L2_diff(u, u_exact, nb_pt);
    }
    # ifdef SORTIE
    if (N < 1000){
        char message[] = "solution approchée partielle";
        affichage_ordonne(u_divise, message);
        if (rang == 0){
            printf("rang = %d, solution approchée :\n", rang); afficher_vecteur(u, nb_pt);
        }
    }
    if (rang == 0){
        sprintf(buffer_print, "erreur_L2 = %f\ntemps = %f sec \n", erreur_L2, temps); printf("%s", buffer_print);
        MPI_File_write(descripteur, buffer_print, strlen(buffer_print), MPI_CHAR, MPI_STATUS_IGNORE);
    }
    # endif
    //
    /* —————————————————————————————————————————————————— */
    /* —————————————————————————————————————————————————— */
    // Libération de mémoire et fermeture de MPI
    # ifdef SORTIE
    if (rang == 0){
        sprintf(buffer_print, "Éxecution terminée\n"); printf("%s", buffer_print);
        MPI_File_write(descripteur, buffer_print, strlen(buffer_print), MPI_CHAR, MPI_STATUS_IGNORE);
        sprintf(buffer_print, "------------------------------------------------------------\n"); printf("%s", buffer_print);
        MPI_File_write(descripteur, buffer_print, strlen(buffer_print), MPI_CHAR, MPI_STATUS_IGNORE);
    }
    # endif
    MPI_Barrier(MPI_COMM_WORLD);
    free(u_divise);
    free(f_divise);
    if (rang == 0){
        free(u);
        free(u_exact);
        free(nb_elements_recus);
        free(deplacements);
    }
    # ifdef SORTIE
    free(buffer_print);
    if (rang == 0){
        //data_to_txt(nom_fichier_data, nom_fichier_txt);
    }
    free(nom_fichier_data);
    free(nom_fichier_txt);
    MPI_File_close(&descripteur);
    # endif
    MPI_Finalize();
    //
    /* —————————————————————————————————————————————————— */
    
    return 0;

}