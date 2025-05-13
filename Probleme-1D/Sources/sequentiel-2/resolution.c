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
    (L -> sous_diag)[0] = beta / (L -> diag)[0];

    for (int i = 1 ; i < n - 1 ; i ++){
        (L -> diag)[i] = sqrt(alpha - pow((L -> sous_diag[i - 1]), 2));
        (L -> sous_diag)[i] = beta / (L -> diag[i]);
    }

    (L -> diag)[n - 1] = sqrt(alpha - pow((L -> sous_diag[n - 2]), 2));

}


// Résoudre Ly = f (descente)
void resoudre_cholesky_descente(struct mat_2bandes *L, double *f, double *y){

    int n = L -> n;

    y[0] = f[0] / (L -> diag)[0];

    for (int i = 1 ; i < n ; i ++){
        y[i] = (f[i] - (L -> sous_diag)[i - 1] * y[i - 1]) / (L -> diag)[i];
    }

}


// Résoudre L^{T}u = y (remontée)
void resoudre_cholesky_remontee(struct mat_2bandes *L, double *y, double *u){

    int n = L -> n;
    
    u[n - 1] = y[n - 1] / (L -> diag)[n - 1];

    for (int i = n - 2 ; i > - 1 ; i --){
        u[i] = (y[i] - (L -> sous_diag)[i] * u[i + 1]) / (L -> diag)[i];
    }

}


// Résoudre Au = f avec les conditions aux bords
void resoudre_cholesky(double *f, double *u){
    
    u[0] = 0;
    u[nb_pt - 1] = 0;

    double h = 1.0 / (nb_pt + 1 - 2);
    double alpha = 2.0 / (h * h);
    double beta = - 1.0 / (h * h);
    struct mat_2bandes L;
    calculer_cholesky_tridiag(alpha, beta, nb_pt - 2, &L);

    double *y = (double *)malloc((nb_pt - 2) * sizeof(double));
    resoudre_cholesky_descente(&L, &(f[1]), y); // Laisser f[0] pour le bord
    resoudre_cholesky_remontee(&L, y, &(u[1])); // Laisser u[0] pour le bord

    free(L.diag);
    free(L.sous_diag);
    free(y);

}