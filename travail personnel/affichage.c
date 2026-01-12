#include<stdio.h>
#include "etudiant.h"

void afficherEtudiants() {
    FILE *f = fopen("etudiant.txt", "r");
    if (f == NULL) {
        printf("Aucun etudiant enregistre.\n");
        return;
    }

    Etudiant e;

    printf("\n------------------------------------------------------------------------------------------\n");
    printf("| %-12s | %-10s | %-10s | %-10s | %-12s | %-10s | %-10s |\n",
           "Matricule", "Nom", "Prenom", "Naissance", "Departement", "Filiere", "Region");
    printf("------------------------------------------------------------------------------------------\n");

    while (fscanf(f,
        "%19s\t%19s\t%19s\t%d/%d/%d\t%19s\t%19s\t%19s",
        e.matricule,
        e.nom,
        e.prenom,
        &e.dateNaissance.jour,
        &e.dateNaissance.mois,
        &e.dateNaissance.annee,
        e.departement,
        e.filiere,
        e.region) == 9) {
//affichage etudiant
        printf("| %-12s | %-10s | %-10s | %02d/%02d/%04d | %-12s | %-10s | %-10s |\n",
               e.matricule,
               e.nom,
               e.prenom,
               e.dateNaissance.jour,
               e.dateNaissance.mois,
               e.dateNaissance.annee,
               e.departement,
               e.filiere,
               e.region);
        }

    printf("------------------------------------------------------------------------------------------\n");
    fclose(f);
}