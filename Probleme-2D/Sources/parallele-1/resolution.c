# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include <mpi.h>
# include <float.h>

# include "../../Librairies/parallele-1.h"

# define SORTIE

# define pi 3.14159265358979323846



void f_1(double **f){

    *f = (double *)malloc(nb_pt * nb_pt * sizeof(double));
    double h = 1.0 / N;
    for (int i = 0 ; i < nb_pt ; i ++){
        for (int j = 0 ; j < nb_pt ; j ++){
            (*f)[j * nb_pt + i] = sin(2 * pi * i * h) * sin(2 * pi * j * h);
        }
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