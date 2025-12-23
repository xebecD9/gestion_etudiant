#ifndef my_gestion_function
#define my_gestion_function
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define size_max 30
#define nombre_max_d_etudiant 100
  //definition de l'enregistrement date
typedef struct{
        int jour;
        int mois;
        int annee;
    }date;
    //definition de l'enregistrement etudiant
 typedef struct{
       char matricule[size_max];
       char nom[size_max];
       char prenom[size_max];
       date date_naissance;
       char filiere[size_max];
       char departement[size_max];
       char sexe;
       char region_origine[size_max];
    }etudiant;
    //definition du tableau d'enregistrement
etudiant bairo[nombre_max_d_etudiant];
int nombre_etudiant=0;
void vider_buffer();

void nettoyer_buffer_fgets(char *chaine);
void afficher_menu();
void afficher_sous_menu();
void ajouter_un_etudiant();
void modifier_les_informations_d_un_etudiant();
void suppression_etudiant();
int recherche_par_matricule(char matricule_cherche[], etudiant *etu_trouve);
void tri_par_ordre_alphabetique();
void recherche_par_dichotomie();
void  calcul_age();
void tri_filiere();
void afficher_la_liste();

#endif
