# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include <mpi.h>
# include <float.h>
# include <limits.h>

# include "../../Librairies/parallele-1.h"

# define SORTIE

# define pi 3.14159265358979323846
# define IDX(i, j) ((j) * (nb_pt_div_i + 2) + (i))



void f_1(double **f){

    *f = (double *)malloc((nb_pt_div_i + 2) * (nb_pt_div_j + 2) * sizeof(double));
    double h = 1.0 / N;
    int j_reel = j_debut;
    int i_reel;

    for (int i = 0 ; i < (nb_pt_div_i + 2) * (nb_pt_div_j + 2) ; i ++){ // A améliorer
        (*f)[i] = 0.0;
    }
    
    for (int j = 1 ; j < nb_pt_div_j + 1 ; j ++){
        i_reel = i_debut;
        for (int i = 1 ; i < nb_pt_div_i + 1 ; i ++){
            (*f)[IDX(i, j)] = sin(2 * pi * i_reel * h) * sin(2 * pi * j_reel * h);
            i_reel ++;
        }
        j_reel ++;
    }

}



double u_1(double x, double y){

    double res = 1.0 / (8 * pow(pi, 2)) * sin(2 * pi * x) * sin(2 * pi * y);

    return res;

}



void calculer_u_exact(double (*fonction)(double, double), double *u){

    double h = 1.0 / N;
    for (int i = 0 ; i < nb_pt ; i ++){
        for (int j = 0 ; j < nb_pt ; j ++){
            u[j * nb_pt + i] = fonction(i * h, j * h);
        }
    }

}



void init_u_anc(double **u_anc_div){

    *u_anc_div = (double *)malloc((nb_pt_div_i + 2) * (nb_pt_div_j + 2) * sizeof(double));

    for (int i = 0 ; i < (nb_pt_div_i + 2) * (nb_pt_div_j + 2) ; i ++){
        (*u_anc_div)[i] = 0.0;
    }

}



double norme_infty_iteration(double *u_div, double *u_anc_div){

    double norme_nume_div = 0.0;
    double norme_deno_div = 0.0;
    double norme_nume;
    double norme_deno;
    double norme;

    for (int j = 1 ; j < nb_pt_div_j + 1 ; j ++){
        for (int i = 1 ; i < nb_pt_div_i + 1 ; i ++){
            double diff = fabs(u_div[IDX(i, j)] - u_anc_div[IDX(i, j)]);
            if (diff > norme_nume_div){
                norme_nume_div = diff;
            }
            if (fabs(u_anc_div[IDX(i, j)]) > norme_deno_div){
                norme_deno_div = fabs(u_anc_div[IDX(i, j)]);
            }
        }
    }

    MPI_Allreduce(&norme_nume_div, &norme_nume, 1, MPI_DOUBLE, MPI_MAX, comm_2D);
    MPI_Allreduce(&norme_deno_div, &norme_deno, 1, MPI_DOUBLE, MPI_MAX, comm_2D);
    norme = norme_nume / norme_deno;

    return norme;

}



void calculer_u_jacobi(double *f_div, double *u_div){

    double h_carre = 1.0 / (N * N);
    int nb_iteration_max = INT_MAX;
    double norme = DBL_MAX;
    double norme_diff = DBL_MAX;
    double *u_anc_div;

    // Vecteur de départ
    init_u_anc(&u_anc_div);
    for (int i = 0 ; i < (nb_pt_div_i + 2) * (nb_pt_div_j + 2) ; i ++){
        u_div[i] = 0.0;
    }

    // Itérations
    for (int iteration = 0 ; iteration < nb_iteration_max && norme > 1e-10 ; iteration ++){

        // Communication
        communiquer(u_anc_div);

        // Schéma
        int j_reel = j_debut;
        int i_reel;
        for (int j = 1 ; j < nb_pt_div_j + 1 ; j ++){
            if (j_reel > 0 && j_reel < nb_pt - 1){
                i_reel = i_debut;
                for (int i = 1 ; i < nb_pt_div_i + 1 ; i ++){
                    if (i_reel > 0 && i_reel < nb_pt - 1){
                        u_div[IDX(i, j)] = 0.25 * (
                        u_anc_div[IDX(i - 1, j)]
                        + u_anc_div[IDX(i, j - 1)]
                        + u_anc_div[IDX(i + 1, j)]
                        + u_anc_div[IDX(i, j + 1)]
                        + h_carre * f_div[IDX(i, j)]
                    );
                    }
                    i_reel ++;
                }
            }
            j_reel ++;
        }

        // Test d'arrêt
        norme = norme_infty_iteration(u_div, u_anc_div);

        // Copie
        for (int j = 1 ; j < nb_pt_div_j + 1 ; j ++){
            for (int i = 1 ; i < nb_pt_div_i + 1 ; i ++){
                u_anc_div[IDX(i, j)] = u_div[IDX(i, j)];
            }
        }
        nb_iterations ++;
        MPI_Barrier(comm_2D);
    }
    
    free(u_anc_div);

}