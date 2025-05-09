/* convert.c */

int data_to_txt(const char *nom_fichier_binaire, const char *nom_fichier_txt);
int txt_to_data(const char *nom_fichier_txt, const char *nom_fichier_binaire);
void clear_file(const char *filename);

/* gen.c */

void afficher_matrice(double *t, int n);
void afficher_vecteur_int(int *t, int n);
void afficher_vecteur(double *t, int n);
void generer(int *t, int n);

/* parallele.c */

void affichage_ordonne(double *u_divise, char *message);
void infos_processus(int nb_pt, int *nb_pt_divise, int *i_debut, int *i_fin);
void infos_topologie(int *cpu_bord, int *voisin_gauche, int *voisin_droite);
void infos_gather(int **deplacements, int **nb_elements_recus);

/* resolution.c */

void f_0(double **f);
void f_1(double **f);
double u_0(double x);
double u_1(double x);
void calculer_u_exact(double (*fonction)(double), double *u);
void generer_A(double *A);
void generer_f(void (*fonction)(double *, int), double *f);
void calculer_u_jacobi(double *f, double *u);
void calculer_u_gaussseidel(double *f, double *u);

/* calcul_mat.c */

void init_matrice_carre_zero(int N, double *A);
void somme_matrice_carre(double alpha, double *A, double beta, double *B, int N, double *C);
void produit_matrice_carre(double alpha, double *A, double *B, int N, double *C);
double norme_L2_diff(double *u, double *v, int n);
double norme_L2(double *u, int n);

/* Variables globales */

extern int N;
extern int nb_pt;

extern int rang;
extern int nb_cpu;
extern int nb_pt_divise;
extern int i_debut;
extern int i_fin;
extern int cpu_bord;
extern int voisin_gauche;
extern int voisin_droite;

extern char *buffer_print;
extern MPI_File descripteur;
