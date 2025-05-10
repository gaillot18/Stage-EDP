# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include <mpi.h>
# include <float.h>

# include "../../Librairie/parallele.h"

# define SORTIE

# define pi 3.14159265358979323846

void f_0(double **f){

    *f = (double *)malloc(nb_pt_divise * sizeof(double));
    for (int i = 0 ; i < nb_pt_divise ; i ++){
        (*f)[i] = 1;
    }

}

void f_1(double **f){

    *f = (double *)malloc(nb_pt_divise * sizeof(double));
    int nb_pt = N + 1;
    double h = 1.0 / N;
    int i_reel = i_debut;
    for (int i = 0 ; i < nb_pt_divise ; i ++){
        (*f)[i] = pi * pi * sin(pi * i_reel * h);
        i_reel ++;
    }

}

double u_0(double x){

    double res = 0.5 * x * (1 - x);

    return res;

}

double u_1(double x){

    double res = sin(pi * x);

    return res;

}

void calculer_u_exact(double (*fonction)(double), double *u){

    double h = 1.0 / N;
    for (int i = 0 ; i < nb_pt ; i ++){
        u[i] = fonction(i * h);
    }

}

void generer_f(void (*fonction)(double *, int), double *f){

    int N_i = N - 2;
    fonction(f, N_i);

}

void calculer_u_jacobi(double *f, double *u){

    double h_carre = 1.0 / (N * N);
    int nb_iteration_max = 500000;
    double norme = DBL_MAX;
    double norme_diff;
    double norme_master;
    double norme_diff_master;
    double buffer_fantome_gauche;
    double buffer_fantome_droite;
    int etiquettes[2] = {1, 2};
    MPI_Status statut;
    MPI_Status statuts[2];
    MPI_Request requetes[2];

    if (cpu_bord == -1){
        u[0] = 0;
    }
    else if (cpu_bord == 1){
        u[nb_pt_divise - 1] = 0;
    }

    // Vecteur de départ 
    double *u_anc = (double *)malloc(nb_pt_divise * sizeof(double));
    for (int i = 0 ; i < nb_pt_divise ; i ++){
        u_anc[i] = 0.5;
    }
    if (cpu_bord == -1 || cpu_bord == 2){
        u_anc[0] = 0;
    }
    if (cpu_bord == 1 || cpu_bord == 2){
        u_anc[nb_pt_divise - 1] = 0;
    }

    // Itérations
    for (int iteration = 0 ; iteration < nb_iteration_max && norme > 1e-10 ; iteration ++){

        // Communications : bloquante pour cellule gauche non bloquante pour cellule droite
        if (nb_cpu > 1){
            MPI_Sendrecv(&(u_anc[nb_pt_divise - 1]), 1, MPI_DOUBLE, voisin_droite, etiquettes[0], &buffer_fantome_gauche, 1, MPI_DOUBLE, voisin_gauche, etiquettes[0], MPI_COMM_WORLD, &statut);
            MPI_Isend(&(u_anc[0]), 1, MPI_DOUBLE, voisin_gauche, etiquettes[1], MPI_COMM_WORLD, &requetes[0]);
            MPI_Irecv(&buffer_fantome_droite, 1, MPI_DOUBLE, voisin_droite, etiquettes[1], MPI_COMM_WORLD, &requetes[1]);
        }

        // Schéma
        if (cpu_bord != -1 && cpu_bord != 2){
            u[0] = 0.5 * ((buffer_fantome_gauche + u_anc[1]) + h_carre * f[0]);
        }

        for (int i = 1 ; i < nb_pt_divise - 1 ; i ++){
            u[i] = 0.5 * ((u_anc[i - 1] + u_anc[i + 1]) + h_carre * f[i]);
        }

        if (nb_cpu > 1){
            MPI_Waitall(2, requetes, statuts);
        }

        if (cpu_bord != 1 && cpu_bord != 2){
            u[nb_pt_divise - 1] = 0.5 * ((u_anc[nb_pt_divise - 2] + buffer_fantome_droite) + h_carre * f[nb_pt_divise - 1]);
        }

        // Test d'arrêt
        norme_diff = norme_L2_diff(u, u_anc, nb_pt_divise) * norme_L2_diff(u, u_anc, nb_pt_divise);
        norme = norme_L2(u_anc, nb_pt_divise) * norme_L2(u_anc, nb_pt_divise);
        MPI_Reduce(&norme_diff, &norme_diff_master, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(&norme, &norme_master, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        if (rang == 0){
            norme = sqrt(norme_diff_master) / sqrt(norme_master);
        }
        MPI_Bcast(&norme, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Copie
        for (int i = 0 ; i < nb_pt_divise ; i ++){
            u_anc[i] = u[i];
        }
        nb_iterations ++;

    }

    free(u_anc);

}