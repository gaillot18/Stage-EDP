# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <float.h>
# include <limits.h>

# include "../../Librairies/sequentiel-1.h"

# define pi 3.14159265358979323846
# define IDX(i, j) ((j) * (nb_pt) + (i))
//# define ECRITURE



static inline __attribute__((always_inline)) double f_source(double x, double y, double t){

    double res = (-lambda + 2 * a * pow(pi, 2)) * sin(pi * x) * sin(pi * y) * exp(-lambda * t);

    return res;

}



double u_1(double x, double y, double t){

    double res = sin(pi * x) * sin(pi * y) * exp(-lambda * t);

    return res;

}



void calculer_u_exact(double (*fonction)(double, double, double), double *u, int k){

    for (int j = 0 ; j < nb_pt ; j ++){
        for (int i = 0 ; i < nb_pt ; i ++){
            u[IDX(i, j)] = fonction(i * h, j * h, k * h_t);
        }
    }

}



double u_zero(double x, double y){

    double res = sin(pi * x) * sin(pi * y);

    return res;

}



void init_u_zero(double (*fonction)(double, double), double **u_anc){

    *u_anc = (double *)malloc(nb_pt * nb_pt * sizeof(double));

    for (int j = 0 ; j < nb_pt ; j ++){
        for (int i = 0 ; i < nb_pt ; i ++){
            (*u_anc)[IDX(i, j)] = fonction(i * h, j * h);
        }
    }

}



static inline __attribute__((always_inline)) double schema(double f, double *u_anc, int i, int j, int k){

    double res = alpha * u_anc[IDX(i, j)]
    + beta * (u_anc[IDX(i - 1, j)] + u_anc[IDX(i, j - 1)] + u_anc[IDX(i + 1, j)] + u_anc[IDX(i, j + 1)])
    + h_t * f;

    return res;

}



void terminaison(double **permut, double **u, double **u_anc){

    if (N_t % 2 != 0){
        *permut = *u; *u = *u_anc; *u_anc = *permut;
    }

    free(*u_anc);

}



// Calculer u
void calculer_u(double *u){

    double *u_anc; double *permut;
    init_u_zero(u_zero, &u_anc);

    for (int k = 1 ; k <= N_t ; k ++){

        for (int j = 1 ; j < nb_pt - 1 ; j ++){
            for (int i = 1 ; i < nb_pt - 1 ; i ++){
                double f = f_source(i * h, j * h, k * h_t);
                u[IDX(i, j)] = schema(f, u_anc, i, j, k);
            }
        }

        # ifdef ECRITURE
        ecrire_double("Textes/parallele-1/resultats.bin", u, nb_pt * nb_pt);
        # endif
        permut = u; u = u_anc; u_anc = permut;

    }

    terminaison(&permut, &u, &u_anc);

}



// Calculer u et u_exact en même temps pour avoir l'erreur à chaque itération
double calculer_u_u_exact(double *u){

    double *u_exact = (double *)malloc(nb_pt * nb_pt * sizeof(double));
    double erreur_infty_k; double erreur_infty = 0.0;
    double *u_anc; double *permut;
    init_u_zero(u_zero, &u_anc);

    for (int k = 1 ; k <= N_t ; k ++){

        for (int j = 1 ; j < nb_pt - 1 ; j ++){
            for (int i = 1 ; i < nb_pt - 1 ; i ++){
                double f = f_source(i * h, j * h, k * h_t);
                u[IDX(i, j)] = schema(f, u_anc, i, j, k);
            }
        }

        calculer_u_exact(u_1, u_exact, k);
        erreur_infty_k = norme_infty_diff(u_exact, u, nb_pt * nb_pt);
        if (erreur_infty_k > erreur_infty){
            erreur_infty = erreur_infty_k;
        }

        permut = u; u = u_anc; u_anc = permut;

    }

    terminaison(&permut, &u, &u_anc);
    free(u_exact);
    
    return erreur_infty;

}