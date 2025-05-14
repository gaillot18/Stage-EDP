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



void infos_processus(){

    int quotient = nb_pt / nb_cpu;
    int reste = nb_pt % nb_cpu;
    
    if (rang < reste){
        nb_pt_divise = quotient + 1;
        i_debut = rang * nb_pt_divise;
    }
    else{
        nb_pt_divise = quotient;
        i_debut = reste * (quotient + 1) + (rang - reste) * quotient;
    }
    i_fin = i_debut + nb_pt_divise - 1;

    MPI_Barrier(MPI_COMM_WORLD);

}



void infos_topologie(){

    if (nb_cpu != 1){
        if (rang == 0){
            cpu_bord = -1;
        }
        else if (rang == nb_cpu - 1){
            cpu_bord = 1;
        }
        else{
            cpu_bord = 0;
        }
    }
    else{
        cpu_bord = 2;
    }

    voisin_gauche = (rang + (nb_cpu - 1)) % nb_cpu;
    voisin_droite = (rang + 1) % nb_cpu;

    MPI_Barrier(MPI_COMM_WORLD);

}



void infos_gather(int **deplacements, int **nb_elements_recus){

    int quotient = nb_pt / nb_cpu;
    int reste = nb_pt % nb_cpu;
    int offset = 0;
    if (rang == 0){
        *nb_elements_recus = (int *)malloc(nb_cpu * sizeof(int));
        *deplacements = (int *)malloc(nb_cpu * sizeof(int));
        for (int i = 0 ; i < nb_cpu ; i++){
            if (i < reste){
                (*nb_elements_recus)[i] = quotient + 1;
            }
            else{
                (*nb_elements_recus)[i] = quotient;
            }
            (*deplacements)[i] = offset;
            offset += (*nb_elements_recus)[i];
        }
    }

}