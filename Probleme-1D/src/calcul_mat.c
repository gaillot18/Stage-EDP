# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# ifdef USE_MPI
# include <mpi.h>
# endif

# include "../lib/lib0.h"

void init_matrice_carre_zero(int n, double *A){

    for (int i = 0 ; i < n * n ; i ++){
        A[i] = 0;
    }

}

void somme_matrice_carre(double alpha, double *A, double beta, double *B, int n, double *C){

    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            C[i * n + j] = alpha * A[i * n + j] + beta * B[i * n + j];
        }
    }

}

void produit_matrice_carre(double alpha, double *A, double *B, int n, double *C){

    init_matrice_carre_zero(n, C);

    if (alpha == 1){
        for (int i = 0 ; i < n ; i ++){
            for (int k = 0 ; k < n ; k ++){
                for (int j = 0 ; j < n ; j ++){
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }
    }
    else{
        for (int i = 0 ; i < n ; i ++){
            for (int j = 0 ; j < n ; j ++){
                for (int k = 0 ; k < n ; k ++){
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
                C[i * n + j] *= alpha;
            }
        }
    }
   
}

double norme_L2(double *u, double *v, int n){

    double res = 0;

    for (int i = 0 ; i < n ; i ++){
        double dif = u[i] - v[i];
        res += dif * dif;
    }
    
    res = sqrt(res);

    return res;

}