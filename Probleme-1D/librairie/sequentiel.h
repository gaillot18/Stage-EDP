/* convert.c */

void convertir_data_vers_txt(const char *nom_fichier_data, const char *nom_fichier_txt);
void ecrire_double(char *nom_fichier_data, char *nom_fichier_txt, double *t, int n);

/* gen.c */

void afficher_matrice(double *t, int n);
void afficher_vecteur(double *t, int n);
void generer(int *t, int n);

/* resolution_seq.c */

void f_0(double **f);
void f_1(double **f);
double u_0(double x);
double u_1(double x);
void calculer_u_exact( double (*fonction)(double), double *u);
void generer_f(void (*fonction)(double *, int), double *f);
void calculer_u_jacobi(double *f, double *u);
void calculer_u_gaussseidel(double *f, double *u);

/* calcul_mat.c */

void init_matrice_carre_zero(int N, double *A);
void somme_matrice_carre(double alpha, double *A, double beta, double *B, int N, double *C);
void produit_matrice_carre(double alpha, double *A, double *B, int N, double *C);
double norme_L2_diff(double *u, double *v, int n);
double norme_L2(double *u, int n);

/* Variables globales statiques */

extern int N;
extern int nb_pt;
extern int nb_iterations;