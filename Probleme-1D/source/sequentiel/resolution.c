# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>
# include <math.h>
# include <float.h>

# include "../../librairie/sequentiel.h"

# define pi 3.14159265358979323846

void f_0_seq(double **f){

    *f = (double *)malloc(nb_pt * sizeof(double));
    for (int i = 0 ; i < nb_pt ; i ++){
        (*f)[i] = 1;
    }

}

void f_1_seq(double **f){

    *f = (double *)malloc(nb_pt* sizeof(double));
    double h = 1.0 / N;
    for (int i = 0 ; i < nb_pt ; i ++){
        (*f)[i] = pi * pi * sin(pi * i * h);
    }

}

double u_0_seq(double x){

    double res = 0.5 * x * (1 - x);

    return res;

}

double u_1_seq(double x){

    double res = sin(pi * x);

    return res;

}

void calculer_u_exact_seq(double (*fonction)(double), double *u){

    double h = 1.0 / N;
    for (int i = 0 ; i < nb_pt ; i ++){
        u[i] = fonction(i * h);
    }

}

void generer_A_seq(double *A){

    int N_i = N - 2; // = N sans u_0 et u_N
    double coeff_1 = 2 * N * N; // = (1 / h^2) * 2
    double coeff_2 = - N * N; // = (1 / h^2) * (-1)

    // 1ère et dernière ligne

    A[0] = coeff_1;
    A[1] = coeff_2;
    A[N_i * N_i - 1] = coeff_1;
    A[N_i * N_i - 2] = coeff_2;

    // Autres lignes

    for (int i = 1 ; i < N_i - 1; i ++){
        A[i * N_i + i] = coeff_1;
        A[i * N_i + i - 1] = coeff_2;
        A[i * N_i + i + 1] = coeff_2;
    }

}

void generer_f_seq(void (*fonction)(double *, int), double *f){

    int N_i = N - 2;
    fonction(f, N_i);

}

void calculer_u_jacobi_seq(double *f, double *u){

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

    int count = 0;
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
        count++;
    }

    free(u_anc);
    printf("iteration = %d\n", count);

}

void calculer_u_gaussseidel_seq(double *f, double *u){

    int nb_pt = N + 1;
    double h_carre = 1.0 / (N * N);
    int nb_iteration_max = 0;
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

    free(u_anc);

}