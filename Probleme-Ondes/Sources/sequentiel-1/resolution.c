# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <float.h>
# include <limits.h>

# include "../../Librairies/sequentiel-1.h"

# define pi 3.14159265358979323846
# define IDX(i, j) ((j) * (nb_pt) + (i))

double const_1;



double u_0(double x){

    double res = 0.0;

    return res;

}



double u_1(double x){

    double res = sin(pi * x);

    return res;

}



double u_e(double x, double t){

    double res = cos(pi * t) * sin(pi * x);

    return res;
    
}



void calculer_u_exact(double (*fonction)(double, double), double *u, int k){

    for (int i = 0 ; i < nb_pt ; i ++){
        u[i] = fonction(i * h, k * h_t);
    }

}



void init_u_init(double (*fonction)(double), double **u_anc){

    *u_anc = (double *)malloc(nb_pt * sizeof(double));

    for (int i = 0 ; i < nb_pt ; i ++){
        (*u_anc)[i] = fonction(i * h);
    }

}



static inline __attribute__((always_inline)) double schema(double *u_anc_0, double *u_anc_1, int i, int k){

    // const_1 = pow(c, 2) * pow(h_t, 2) / pow(h, 2)
    double res = -u_anc_1[i] + 2 * (1 - const_1) * u_anc_0[i] + const_1 * (u_anc_0[i - 1] + u_anc_0[i + 1]);

    return res;

}



// Écrire dans le fichier
static inline __attribute__((always_inline, unused)) void ecrire_double_iteration(double *u){

    fwrite(u, sizeof(double), nb_pt, descripteur);

}



void terminaison(double **u, double **u_anc_0, double **u_anc_1){

    if (N_t % 3 == 1){
        *u_anc_1 = *u_anc_0; *u_anc_0 = *u; *u = *u_anc_1;
        *u_anc_1 = *u_anc_0; *u_anc_0 = *u; *u = *u_anc_1;
    }
    else if (N_t % 3 == 2){
        *u_anc_1 = *u_anc_0; *u_anc_0 = *u; *u = *u_anc_1;
    }

    free(*u_anc_0); free(*u_anc_1);

}



// Calculer u
void calculer_u(double *u){

    const_1 = pow(c, 2) * pow(h_t, 2) / pow(h, 2);
    double *u_anc_0; double *u_anc_1;
    init_u_init(u_0, &u_anc_1); init_u_init(u_1, &u_anc_0);
    for (int i = 0 ; i < nb_pt ; i ++){
        u[i] = 0.0;
    }

    for (int k = 1 ; k <= N_t ; k ++){

        # ifdef ECRITURE
        ecrire_double_iteration(u_anc);
        # endif

        for (int i = 1 ; i < nb_pt - 1 ; i ++){
            u[i] = schema(u_anc_0, u_anc_1, i, k);
        }

        u_anc_1 = u_anc_0; u_anc_0 = u; u = u_anc_1;

    }

    # ifdef ECRITURE
    ecrire_double_iteration(u);
    # endif

    terminaison(&u, &u_anc_0, &u_anc_1);

}



// Calculer u et u_exact en même temps pour avoir l'erreur à chaque itération
double calculer_u_u_exact(double *u){

    double *u_exact = (double *)malloc(nb_pt * sizeof(double));
    double erreur_infty_k; double erreur_infty = 0.0;

    const_1 = pow(c, 2) * pow(h_t, 2) / pow(h, 2);
    double *u_anc_0; double *u_anc_1;
    init_u_init(u_0, &u_anc_1); init_u_init(u_1, &u_anc_0);
    for (int i = 0 ; i < nb_pt ; i ++){
        u[i] = 0.0;
    }

    for (int k = 1 ; k <= N_t ; k ++){

        for (int i = 1 ; i < nb_pt - 1 ; i ++){
            u[i] = schema(u_anc_0, u_anc_1, i, k);
        }
        
        calculer_u_exact(u_e, u_exact, k);
        erreur_infty_k = norme_infty_diff(u_exact, u, nb_pt);
        if (erreur_infty_k > erreur_infty){
            erreur_infty = erreur_infty_k;
        }

        u_anc_1 = u_anc_0; u_anc_0 = u; u = u_anc_1;

    }

    terminaison(&u, &u_anc_0, &u_anc_1);
    free(u_exact);
    
    return erreur_infty;

}