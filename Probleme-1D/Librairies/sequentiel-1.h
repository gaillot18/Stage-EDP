// ======================================================
// ../../Fonctions-communes/affichage.c
// ======================================================
void afficher_matrice_carre_double(double *t, int n);
void afficher_matrice_carre_int(int *t, int n);
void afficher_vecteur_double(double *t, int n);
void afficher_vecteur_int(int *t, int n);


// ======================================================
// ../../Fonctions-communes/calcul_mat.c
// ======================================================
void init_matrice_carre_zero(int N, double *A);
void somme_matrice_carre(double alpha, double *A, double beta, double *B, int N, double *C);
void produit_matrice_carre(double alpha, double *A, double *B, int N, double *C);
double norme_L2_diff(double *u, double *v, int n);
double norme_L2(double *u, int n);


// ======================================================
// ../../Fonctions-communes/convert.c
// ======================================================
void convertir_data_vers_txt(const char *nom_fichier_data, const char *nom_fichier_txt);
void ecrire_double(char *nom_fichier_data, char *nom_fichier_txt, double *t, int n);


// ======================================================
// ../../Sources/Fonctions-numeriques/fonctions.c
// ======================================================
void f_0(double **f);
void f_1(double **f);
double u_0(double x);
double u_1(double x);
void calculer_u_exact(double (*fonction)(double), double *u);
void generer_f(void (*fonction)(double *, int), double *f);


// ======================================================
// ../Source/Parallele/resolution.c
// ======================================================
void calculer_u_jacobi(double *f, double *u);
void calculer_u_gaussseidel(double *f, double *u);


// ======================================================
// Variables globales
// ======================================================
extern int N;
extern int nb_pt;
extern int nb_iterations;