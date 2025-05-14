# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <mpi.h>

# include "../../Librairies/parallele-1.h"

# define SORTIE



void affichage_ordonne(double *u_divise, char *message){
    for (int i = 0 ; i < nb_cpu ; i ++){
            if (rang == i){
                printf("rang = %d, %s :\n", rang, message);
                afficher_vecteur_double(u_divise, nb_pt_divise);
            }
            MPI_Barrier(MPI_COMM_WORLD);
        }
}