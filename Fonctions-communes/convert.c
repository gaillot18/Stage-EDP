# include <stdio.h>



// Convertir un fichier data contenant des double en fichier txt
void convertir_data_vers_txt(const char *nom_fichier_data, const char *nom_fichier_txt){

    FILE *fichier_data = fopen(nom_fichier_data, "rb");
    FILE *fichier_txt = fopen(nom_fichier_txt, "w");

    if (fichier_data == NULL || fichier_txt == NULL){
        perror("Erreur d'ouverture du fichier");
    }

    double valeur;
    while (fread(&valeur, sizeof(double), 1, fichier_data) == 1){
        fprintf(fichier_txt, "%f\n", valeur);
    }

    fclose(fichier_data);
    fclose(fichier_txt);

}



// Écrire un tableau de doubles dans un fichier data
void ecrire_double(char *nom_fichier_data, char *nom_fichier_txt, double *t, int n){

    FILE *descripteur;
    descripteur = fopen(nom_fichier_data, "wb");
    fwrite(t, sizeof(double), n, descripteur);
    fclose(descripteur);
    convertir_data_vers_txt(nom_fichier_data, nom_fichier_txt);

}