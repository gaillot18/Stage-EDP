/* convert.c */

int data_to_txt(const char *nom_fichier_binaire, const char *nom_fichier_txt);
int txt_to_data(const char *nom_fichier_txt, const char *nom_fichier_binaire);
void clear_file(const char *filename);

/* gen.c */

void afficher_matrice(double *t, int n);
void afficher_vecteur(double *t, int n);
void generer(int *t, int n);

/* resolution.c */

void f_0(int nb_pt, double *f);
void f_1(int N, double *f);
double u_0(double x);
double u_1(double x);
void calculer_u_exact(int N, double (*fonction)(double), double *u);
void generer_A(int N, double *A);
void generer_f(int N, void (*fonction)(double *, int), double *f);
void calculer_u_jacobi(double *f, int N, double *u);
void calculer_u_gaussseidel(double *f, int N, double *u);

/* calcul_mat.c */

void init_matrice_carre_zero(int N, double *A);
void somme_matrice_carre(double alpha, double *A, double beta, double *B, int N, double *C);
void produit_matrice_carre(double alpha, double *A, double *B, int N, double *C);
double norme_L2(double *u, double *v, int n);

/* Variables globales pour arallèle */

extern int rang;
extern int nb_cpu;
extern int quotient;
extern int reste;
extern int nb_pt_divise;
extern int i_debut;
extern int i_fin;
extern int cpu_bord;
extern int voisin_gauche;
extern int voisin_droite;
