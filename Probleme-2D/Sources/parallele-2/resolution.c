# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>
# include <math.h>
# include <float.h>
# include <limits.h>

# include "../../Librairies/parallele-2.h"

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



void init_u_anc(double **u_anc){

    *u_anc = (double *)malloc(nb_pt * nb_pt * sizeof(double));

    for (int i = 0 ; i < nb_pt * nb_pt ; i ++){
        (*u_anc)[i] = 0.0;
    }

}



void calculer_u_jacobi(double *f, double *u){

    double h_carre = 1.0 / (N * N);
    int nb_iteration_max = INT_MAX;
    double norme = DBL_MAX;
    double *u_anc;

    // Vecteur de départ
    init_u_anc(&u_anc);

    // Itérations
    for (int iteration = 0 ; iteration < nb_iteration_max && norme > 1e-10 ; iteration ++){

        // Schéma
        # pragma omp parallel for schedule(runtime)
        for (int j = 1 ; j < nb_pt - 1 ; j ++){
            for (int i = 1 ; i < nb_pt - 1 ; i ++){
                u[j * nb_pt + i] = 0.25 * (u_anc[j * nb_pt + i - 1] + u_anc[(j - 1) * nb_pt + i] + u_anc[j * nb_pt + i + 1] + u_anc[(j + 1) * nb_pt + i] + h_carre * f[j * nb_pt + i]);
            }
        }

        // Test d'arrêt
        double norme_diff = norme_infty_diff(u, u_anc, nb_pt * nb_pt);
        double norme_anc = norme_infty(u_anc, nb_pt * nb_pt);
        norme = norme_diff / norme_anc;
        //printf("norme = %f\n", norme);
        

        // Copie
        for (int i = 0 ; i < nb_pt * nb_pt ; i ++){
            u_anc[i] = u[i];
        }
        nb_iterations ++;
    }

    free(u_anc);

}