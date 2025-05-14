# include <math.h>
# ifdef USE_MPI
# include <mpi.h>
# endif



// Initialiser une matrice carré à 0
void init_matrice_carre_zero(int n, double *A){

    for (int i = 0 ; i < n * n ; i ++){
        A[i] = 0;
    }

}



// Somme de matrices
void somme_matrice_carre(double alpha, double *A, double beta, double *B, int n, double *C){

    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            C[i * n + j] = alpha * A[i * n + j] + beta * B[i * n + j];
        }
    }

}



// Produit de matrices
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



// Norme L2 de la différence de deux vecteurs
double norme_L2_diff(double *u, double *v, int n){

    double res = 0;

    for (int i = 0 ; i < n ; i ++){
        double diff = u[i] - v[i];
        res += diff * diff;
    }
    
    res = sqrt(res);

    return res;

}



// Norme infinie de la différence de deux vecteurs
double norme_infty_diff(double *u, double *v, int n){

    double res = 0;

    for (int i = 0 ; i < n ; i ++){
        double diff = fabs(u[i] - v[i]);
        if (diff > res){
            res = diff;
        }
    }

    return res;

}



// Carré de la norme L2 de la différence de deux vecteurs
double carre_norme_L2_diff(double *u, double *v, int n){

    double res = 0;

    for (int i = 0 ; i < n ; i ++){
        double diff = u[i] - v[i];
        res += diff * diff;
    }

    return res;

}



// Norme L2 d'un vecteur
double norme_L2(double *u, int n){

    double res = 0;

    for (int i = 0 ; i < n ; i ++){
        res += u[i] * u[i];
    }
    
    res = sqrt(res);

    return res;

}



// Carré de la norme L2 d'un vecteur
double carre_norme_L2(double *u, int n){

    double res = 0;

    for (int i = 0 ; i < n ; i ++){
        res += u[i] * u[i];
    }

    return res;

}