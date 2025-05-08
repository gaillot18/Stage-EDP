/* convert.c */

int data_to_txt(const char *nom_fichier_binaire, const char *nom_fichier_txt);
int txt_to_data(const char *nom_fichier_txt, const char *nom_fichier_binaire);
void clear_file(const char *filename);

/* gen.c */

void afficher_matrice(double *t, int n);
void afficher_vecteur(double *t, int n);
void generer(int *t, int n);

/* resolution_seq.c */

void f_0_seq(int N, double *f);
void f_1_seq(int N, double *f);
double u_0_seq(double x);
double u_1_seq(double x);
void calculer_u_exact_seq(int N, double (*fonction)(double), double *u);
void generer_A_seq(int N, double *A);
void generer_f_seq(int N, void (*fonction)(double *, int), double *f);
void calculer_u_jacobi_seq(double *f, int N, double *u);
void calculer_u_gaussseidel_seq(double *f, int N, double *u);

/* calcul_mat.c */

void init_matrice_carre_zero(int N, double *A);
void somme_matrice_carre(double alpha, double *A, double beta, double *B, int N, double *C);
void produit_matrice_carre(double alpha, double *A, double *B, int N, double *C);
double norme_L2_diff(double *u, double *v, int n);
double norme_L2(double *u, int n);
