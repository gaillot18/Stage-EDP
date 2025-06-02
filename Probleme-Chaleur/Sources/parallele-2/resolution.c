# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include <mpi.h>

# include "../../Librairies/parallele-2.h"

# define pi 3.14159265358979323846
# define IDX(i, j) ((j) * (nb_pt_div_i + 2) + (i))
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
            u[j * nb_pt + i] = fonction(i * h, j * h, k * h_t);
        }
    }

}



double u_zero(double x, double y){

    double res = sin(pi * x) * sin(pi * y);

    return res;

}



void init_u_zero(double (*fonction)(double, double), double **u_div_anc){

    *u_div_anc = (double *)malloc((nb_pt_div_i + 2) * (nb_pt_div_j + 2) * sizeof(double));
    for (int i = 0 ; i < (nb_pt_div_i + 2) * (nb_pt_div_j + 2) ; i ++){
        (*u_div_anc)[i] = 0.0;
    }

    int j_reel = j_debut;
    for (int j = 1 ; j < nb_pt_div_j + 1 ; j ++){
        int i_reel = i_debut;
        for (int i = 1 ; i < nb_pt_div_i + 1 ; i ++){
            (*u_div_anc)[IDX(i, j)] = fonction(i_reel * h, j_reel * h);
            i_reel ++;
        }
        j_reel ++;
    }

}



static inline __attribute__((always_inline)) double schema(double f, double *u_div_anc, int i, int j, int k){

    double res = alpha * u_div_anc[IDX(i, j)]
    + beta * (u_div_anc[IDX(i - 1, j)] + u_div_anc[IDX(i, j - 1)] + u_div_anc[IDX(i + 1, j)] + u_div_anc[IDX(i, j + 1)])
    + h_t * f;

    return res;

}



static inline __attribute__((always_inline)) void ecrire_double_iteration(double *u, int k){

    MPI_Offset offset = (MPI_Offset)(k * nb_pt * nb_pt) * sizeof(double);

    int tailles_globales[2] = {nb_pt, nb_pt};
    int tailles_locales[2]  = {nb_pt_div_j, nb_pt_div_i};
    int starts[2] = {j_debut, i_debut};

    MPI_Datatype vue_fichier;
    MPI_Type_create_subarray(2, tailles_globales, tailles_locales, starts, MPI_ORDER_C, MPI_DOUBLE, &vue_fichier);
    MPI_Type_commit(&vue_fichier);

    MPI_File_set_view(descripteur, offset, MPI_DOUBLE, vue_fichier, "native", MPI_INFO_NULL);

    MPI_File_write_all(descripteur, u, 1, bloc_send, MPI_STATUS_IGNORE);

    MPI_Type_free(&vue_fichier);

}



void terminaison(double **permut, double **u, double **u_anc){

    if (N_t % 2 != 0){
        *permut = *u; *u = *u_anc; *u_anc = *permut;
    }

    free(*u_anc);

}



// Calculer u_div
void calculer_u(double *u_div){

    int i_boucle_debut; int j_boucle_debut;
    int i_boucle_fin; int j_boucle_fin;
    double *u_div_anc; double *permut;

    init_u_zero(u_zero, &u_div_anc);
    for (int i = 0 ; i < (nb_pt_div_i + 2) * (nb_pt_div_j + 2) ; i ++){
        u_div[i] = 0.0;
    }

    infos_bornes_boucles(&i_boucle_debut, &j_boucle_debut, &i_boucle_fin, &j_boucle_fin);

    for (int k = 1 ; k <= N_t ; k ++){

        # ifdef ECRITURE
        ecrire_double_iteration(u_div_anc, k - 1);
        # endif

        echanger_halos(u_div_anc);

        for (int j = j_boucle_debut ; j < j_boucle_fin ; j ++){
            for (int i = i_boucle_debut ; i < i_boucle_fin ; i ++){
                int i_reel = i_debut + (i - 1);
                int j_reel = j_debut + (j - 1);
                double f = f_source(i_reel * h, j_reel * h, k * h_t);
                u_div[IDX(i, j)] = schema(f, u_div_anc, i, j, k);
            }
        }

        
        permut = u_div; u_div = u_div_anc; u_div_anc = permut;

    }

    # ifdef ECRITURE
    ecrire_double_iteration(u_div, N_t);
    # endif

    terminaison(&permut, &u_div, &u_div_anc);

}



// Calculer u_div et u_div_exact en même temps pour avoir l'erreur à chaque itération
__attribute__((unused)) double calculer_u_u_exact(double *u_div){

    double *u = (double *)malloc(nb_pt * nb_pt * sizeof(double));
    double *u_exact = (double *)malloc(nb_pt * nb_pt * sizeof(double));
    double erreur_infty_k; double erreur_infty = 0.0;
    int i_boucle_debut; int j_boucle_debut;
    int i_boucle_fin; int j_boucle_fin;
    double *u_div_anc; double *permut;

    init_u_zero(u_zero, &u_div_anc);
    for (int i = 0 ; i < (nb_pt_div_i + 2) * (nb_pt_div_j + 2) ; i ++){
        u_div[i] = 0.0;
    }
    
    infos_bornes_boucles(&i_boucle_debut, &j_boucle_debut, &i_boucle_fin, &j_boucle_fin);

    for (int k = 1 ; k <= N_t ; k ++){

        echanger_halos(u_div_anc);
        
        for (int j = j_boucle_debut ; j < j_boucle_fin ; j ++){
            for (int i = i_boucle_debut ; i < i_boucle_fin ; i ++){
                int i_reel = i_debut + (i - 1);
                int j_reel = j_debut + (j - 1);
                double f = f_source(i_reel * h, j_reel * h, k * h_t);
                u_div[IDX(i, j)] = schema(f, u_div_anc, i, j, k);
            }
        }

        regrouper_u(u_div, u);
        if (rang == 0){
            calculer_u_exact(u_1, u_exact, k);
            erreur_infty_k = norme_infty_diff(u_exact, u, nb_pt * nb_pt);
            if (erreur_infty_k > erreur_infty){
                erreur_infty = erreur_infty_k;
            }
        }

        permut = u_div; u_div = u_div_anc; u_div_anc = permut;

    }

    terminaison(&permut, &u_div, &u_div_anc);

    MPI_Bcast(&erreur_infty, 1, MPI_DOUBLE, 0, comm_2D);
    
    return erreur_infty;

}