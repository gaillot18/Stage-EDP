# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>
# include <math.h>
# include <float.h>

# include "../../Librairies/sequentiel-2.h"

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

void generer_f(void (*fonction)(double *, int), double *f){

    int N_i = N - 2;
    fonction(f, N_i);

}

// Construire la matrice creuse (buffer 1D) de la décomposition de Cholesky d'une matrice tridiagonale
// alpha, beta, gamma sont les coefficients des diagonales (pour le problème 1D : alpha = 2 / h^2, beta = -1 / h^2)
void calculer_cholesky_tridiag(double alpha, double beta, int n, struct mat_2bandes *L){

    L -> n = n;
    L -> diag = (double *)malloc(n * sizeof(double));
    L -> sous_diag = (double *)malloc((n - 1) * sizeof(double));

    (L -> diag)[0] = sqrt(alpha);
    (L -> sous_diag)[0] = 1.0 / (L -> diag)[0] * beta;

    for (int i = 1 ; i < (n - 1) ; i ++){
        (L -> diag)[i] = sqrt(alpha - pow((L -> sous_diag[i - 1]), 2));
        (L -> sous_diag)[i] = 1.0 / (L -> diag[i]) * beta;
    }

    (L -> diag)[n - 1] = sqrt(alpha - pow((L -> sous_diag[n - 2]), 2));

}