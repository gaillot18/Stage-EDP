# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>
# include <math.h>
# include <float.h>
# include <limits.h>

# include "../../Librairies/sequentiel-1.h"

# define pi 3.14159265358979323846
# define IDX(i, j) ((j) * (nb_pt) + (i))

double h_carre;



double f_source(double x, double y, double t){

    return 0;

}



void calculer_f_source(double (*fonction)(double, double, double), double *f, int k){

    for (int i = 0 ; i < nb_pt ; i ++){
        for (int j = 0 ; j < nb_pt ; j ++){
            f[IDX(i, j)] = fonction(i * h, j * h, k * h_t);
        }
    }

}



double u_1(double x, double y, double t){

    double res = sin(pi * x) * sin(pi * y) * exp(-2 * a * pow(pi, 2) * t);

    return res;

}



void calculer_u_exact(double (*fonction)(double, double, double), double *u, int k){

    for (int i = 0 ; i < nb_pt ; i ++){
        for (int j = 0 ; j < nb_pt ; j ++){
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

    for (int i = 0 ; i < nb_pt ; i ++){
        for (int j = 0 ; j < nb_pt ; j ++){
            (*u_anc)[IDX(i, j)] = fonction(i * h, j * h);
        }
    }

}



static inline __attribute__((always_inline)) double schema(double *f, double *u, double *u_anc, int i, int j, int k){

    double res = alpha * u_anc[IDX(i, j)]
    + beta * (u_anc[IDX(i - 1, j)] + u_anc[IDX(i, j - 1)] + u_anc[IDX(i + 1, j)] + u_anc[IDX(i, j + 1)])
    + h_t * f[IDX(i, j)];

    return res;

}



static inline __attribute__((always_inline)) double norme_infty_iteration(double *u, double *u_anc){

    double norme_nume = 0.0;
    double norme_deno = 0.0;
    double norme;

    for (int i = 0 ; i < nb_pt * nb_pt ; i ++){
        double diff = fabs(u[i] - u_anc[i]);
        if (diff > norme_nume){
            norme_nume = diff;
        }
        if (fabs(u_anc[i]) > norme_deno){
            norme_deno = fabs(u_anc[i]);
        }
    }

    norme = norme_nume / norme_deno;

    return norme;

}



void terminaison(double **permut, double **u, double **u_anc){

    if (N_t % 2 != 0){
        *permut = *u; *u = *u_anc; *u_anc = *permut;
    }

    free(*u_anc);

}



void calculer_u(double (*fonction)(double, double, double), double *u){

    double *u_exact = (double *)malloc(nb_pt * nb_pt * sizeof(double)); // !
    double erreur_infty; // !
    double *u_anc; double *permut;
    double *f = (double *)malloc(nb_pt * nb_pt * sizeof(double));
    init_u_zero(u_zero, &u_anc);

    for (int k = 1 ; k <= N_t ; k ++){

        calculer_f_source(fonction, f, k);
        for (int i = 1 ; i < nb_pt - 1 ; i ++){
            for (int j = 1 ; j < nb_pt - 1 ; j++){
                schema(f, u, u_anc, i, j, k);
            }
        }

        calculer_u_exact(u_1, u_exact, k); // !
        erreur_infty = norme_infty_diff(u_exact, u, nb_pt * nb_pt); // !
        printf("k = %d, temps = %f, erreur_infty = %f\n", k, k * h_t, erreur_infty); // !

        permut = u; u = u_anc; u_anc = permut;

    }

    free(f);
    terminaison(&permut, &u, &u_anc);
    free(u_exact); // !

}