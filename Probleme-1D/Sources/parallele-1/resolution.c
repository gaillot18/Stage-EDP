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



void f_0(double **f){

    *f = (double *)malloc((nb_pt_div + 2) * sizeof(double));
    for (int i = 1 ; i < nb_pt_div + 1 ; i ++){
        (*f)[i] = 1;
    }

}



void f_1(double **f){

    *f = (double *)malloc((nb_pt_div + 2) * sizeof(double));
    double h = 1.0 / N;
    int i_reel = i_debut;
    
    for (int i = 1 ; i < nb_pt_div + 1 ; i ++){
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



void init_u_div_anc(double **u_div_anc){

    *u_div_anc = (double *)malloc((nb_pt_div + 2) * sizeof(double));
    
    for (int i = 0 ; i < nb_pt_div + 2 ; i ++){
        (*u_div_anc)[i] = 0.0;
    }

}



double norme_infty_iteration(double *u_div, double *u_anc_div){

    double norme_nume_div = 0.0;
    double norme_deno_div = 0.0;
    double norme_nume;
    double norme_deno;
    double norme;

    for (int i = 1 ; i < nb_pt_div + 1 ; i ++){
        double diff = fabs(u_div[i] - u_anc_div[i]);
        if (diff > norme_nume_div){
            norme_nume_div = diff;
        }
        if (fabs(u_anc_div[i]) > norme_deno_div){
            norme_deno_div = fabs(u_anc_div[i]);
        }
    }

    MPI_Allreduce(&norme_nume_div, &norme_nume, 1, MPI_DOUBLE, MPI_MAX, comm_1D);
    MPI_Allreduce(&norme_deno_div, &norme_deno, 1, MPI_DOUBLE, MPI_MAX, comm_1D);
    norme = norme_nume / norme_deno;

    return norme;

}



void calculer_u_jacobi(double *f_div, double *u_div){

    nb_iterations = 0;
    double h_carre = 1.0 / (N * N);
    int nb_iteration_max = INT_MAX;
    double norme = DBL_MAX;
    double *u_div_anc;

    // Vecteur de départ
    init_u_div_anc(&u_div_anc);
    for (int i = 0 ; i < nb_pt_div + 2 ; i ++){
        u_div[i] = 0.0;
    }

    // Itérations
    for (int iteration = 0 ; iteration < nb_iteration_max && norme > 1e-10 ; iteration ++){

        // Communication
        echanger_halos(u_div_anc);

        int i_reel = i_debut;
        for (int i = 1 ; i < nb_pt_div + 1 ; i ++){
            if (i_reel > 0 && i_reel < nb_pt - 1){
                u_div[i] = 0.5 * ((u_div_anc[i - 1] + u_div_anc[i + 1]) + h_carre * f_div[i]);
            }
            i_reel ++;
        }

        // Test d'arrêt
        norme = norme_infty_iteration(u_div, u_div_anc);

        // Copie
        for (int i = 1 ; i < nb_pt_div + 1 ; i ++){
            u_div_anc[i] = u_div[i];
        }
        nb_iterations ++;

    }

    free(u_div_anc);

}