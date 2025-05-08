#include <stdio.h>
#include <stdlib.h>

int data_to_txt(const char *nom_fichier_binaire, const char *nom_fichier_txt){
    FILE *fichier_binaire = fopen(nom_fichier_binaire, "rb");  // Fichier binaire à lire
    FILE *fichier_txt = fopen(nom_fichier_txt, "w");  // Fichier texte à écrire

    if (fichier_binaire == NULL || fichier_txt == NULL) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    int valeur;
    // Lire chaque entier du fichier binaire et l'écrire dans le fichier texte
    while (fread(&valeur, sizeof(int), 1, fichier_binaire) == 1) {
        fprintf(fichier_txt, "%d\n", valeur);  // Écriture en texte
    }

    fclose(fichier_binaire);
    fclose(fichier_txt);

    //printf("Fichier texte créé avec succès.\n");
    return 0;
}

int txt_to_data(const char *nom_fichier_txt, const char *nom_fichier_binaire){
    FILE *fichier_txt = fopen(nom_fichier_txt, "r");  // Fichier texte à lire
    FILE *fichier_binaire = fopen(nom_fichier_binaire, "wb");  // Fichier binaire à écrire

    if (fichier_txt == NULL || fichier_binaire == NULL) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    int valeur;
    // Lire chaque entier du fichier texte et l'écrire dans le fichier binaire
    while (fscanf(fichier_txt, "%d", &valeur) == 1) {
        fwrite(&valeur, sizeof(int), 1, fichier_binaire);  // Écriture en binaire
    }

    fclose(fichier_txt);
    fclose(fichier_binaire);

    //printf("Fichier binaire créé avec succès.\n");
    return 0;
}

void clear_file(const char *filename){
    FILE *file = fopen(filename, "w"); // Ouvre en mode écriture, ce qui écrase le contenu
    if (file) {
        fclose(file);
    }
}