#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int matricule;
    char nom[50];
    int age;
} Etudiant;

Etudiant tab[MAX];
int n = 0;

void ajouterEtudiant() {
    if (n == MAX) {
        printf("Tableau plein\n");
        return;
    }

    printf("Matricule : ");
    scanf("%d", &tab[n].matricule);

    printf("Nom : ");
    scanf("%s", tab[n].nom);

    printf("Age : ");
    scanf("%d", &tab[n].age);

    n++;
    printf("Etudiant ajoute avec succes\n");
}

void supprimerEtudiant() {
    int mat, i;

    printf("Matricule a supprimer : ");
    scanf("%d", &mat);

    for (i = 0; i < n; i++) {
        if (tab[i].matricule == mat) {
            break;
        }
    }

    if (i == n) {
        printf("Etudiant non trouve\n");
        return;
    }

    for (int j = i; j < n - 1; j++) {
        tab[j] = tab[j + 1];
    }

    n--;
    printf("Etudiant supprime avec succes\n");
}
int main() {
    int choix;

    do {
        printf("\n1. Ajouter");
        printf("\n2. Supprimer");
        printf("\n0. Quitter");
        printf("\nChoix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterEtudiant();
                break;
            case 2:
                supprimerEtudiant();
                break;
        }
    } while (choix != 0);

    return 0;
}