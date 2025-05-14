# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>
# include <math.h>
# include <float.h>

# include "../../Librairies/sequentiel-1.h"

# define pi 3.14159265358979323846



void f_0(double **f){

    *f = (double *)malloc(nb_pt * sizeof(double));
    for (int i = 0 ; i < nb_pt ; i ++){
        (*f)[i] = 1;
    }

}



void f_1(double **f){

    *f = (double *)malloc(nb_pt* sizeof(double));
    double h = 1.0 / N;
    for (int i = 0 ; i < nb_pt ; i ++){
        (*f)[i] = pi * pi * sin(pi * i * h);
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



void calculer_u_jacobi(double *f, double *u){

    int nb_pt = N + 1;
    double h_carre = 1.0 / (N * N);
    int nb_iteration_max = 500000;
    double norme = DBL_MAX;
    u[0] = 0;
    u[nb_pt - 1] = 0;

    // Vecteur de départ 

    double *u_anc = (double *)malloc(nb_pt * sizeof(double));
    u_anc[0] = 0;
    for (int i = 1 ; i < nb_pt - 1 ; i ++){
        u_anc[i] = 0.5;
    }
    u[nb_pt - 1] = 0;

    // Itérations
    for (int iteration = 0 ; iteration < nb_iteration_max && norme > 1e-10 ; iteration ++){

        // Schéma
        for (int i = 1 ; i < nb_pt - 1 ; i ++){
            //printf("i = %d, rang = %d\n", i, rang);
            u[i] = 0.5 * ((u_anc[i - 1] + u_anc[i + 1]) + h_carre * f[i]);
        }

        // Test d'arrêt
        norme = norme_L2_diff(u, u_anc, nb_pt) / norme_L2(u_anc, nb_pt);

        // Copie
        for (int i = 1 ; i < nb_pt - 1 ; i ++){
            u_anc[i] = u[i];
        }
        nb_iterations ++;
    }

    free(u_anc);

}



// Test de Gauss-Seidel sans calcul de la norme
void calculer_u_gaussseidel(double *f, double *u){

    int nb_pt = N + 1;
    double h_carre = 1.0 / (N * N);
    int nb_iteration_max = 50000;
    u[0] = 0;
    u[nb_pt - 1] = 0;

    // Vecteur de départ 
    double *u_anc = (double *)malloc(nb_pt * sizeof(double));
    for (int i = 0 ; i < nb_pt ; i ++){
        u_anc[i] = 0;
    }

    // Itérations
    for (int iteration = 0 ; iteration < nb_iteration_max ; iteration ++){

        // Schéma
        for (int i = 1 ; i < nb_pt - 1 ; i ++){
            u[i] = 0.5 * (u[i - 1] + u_anc[i + 1] + h_carre * f[i]);
        }

        // Copie
        for (int i = 1 ; i < nb_pt - 1 ; i ++){
            u_anc[i] = u[i];
        }

    }
    nb_iterations = nb_iteration_max;

    free(u_anc);

}