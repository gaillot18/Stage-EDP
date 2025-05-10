# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>
# include <math.h>
# include <float.h>

# include "../../Librairie/sequentiel-2.h"

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

void 