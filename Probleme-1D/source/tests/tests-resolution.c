# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <sys/time.h>

# define N 4
# define INT_MAX 2147483647 // = 2^31 - 1

# define AFFICHAGE 1

# define TEST_f_idt_1 1

int rang;
static int nb_rang;
# pragma omp threadprivate(rang)

int main(int argc, char **argv){

    struct timeval temps_debut, temps_fin;
    double temps_total;

    # pragma omp parallel
    {
        # ifdef _OPENMP
        nb_rang = omp_get_num_threads();
        rang = omp_get_thread_num();
        # endif
    }

    srand(50);
    double *A;
    double *B;
    double *C;
    
    return 0;
}