#ifndef my_gestion_function
#define my_gestion_function
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

//definition des constantes
#define size_max 30
#define nombre_max_d_etudiant 100
  //definition de l'enregistrement date
typedef struct{
        int jour;
        int mois;
        int annee;
    }date;
    
//definition de l'enregistrement etudiant    
typedef struct {
    char matricule[size_max];
    char nom[size_max];
    char prenom[size_max];
    date date_naissance;
    char filiere[size_max];
    char departement[size_max];
    char sexe;
    char region_origine[size_max];
} etudiant;
//structure qui me permet de generer les statistiques de l'ecole
typedef struct {
    char label[size_max];
    int compteur;
} StatItem;
    //definition des variables globales
extern etudiant bairo[nombre_max_d_etudiant];
extern int nombre_etudiant ;

//declaration des fonctions
void vider_buffer();
void effacer_ecran();
void pause();
void nettoyer_buffer_fgets(char *chaine);
date extraction_date();
void afficher_menu_principal();
void sauvegarder_dans_fichier(etudiant e);
void charger_donnees();
void actualiser_fichier(); 
void affiche_liste_etudiant(); 
void tri_alphabetique();
void tri_departement();
void ajouter_un_etudiant();
void modifier_etudiant();
void suppression_etudiant();
void recherche();
int recherche_par_matricule(char mat[], etudiant *res);
int recherche_dichotomique(char matrecher[], etudiant *res);
void calcul_age();
void tri();
void tri_filiere();
void afficher_stats_generique(char *type) ;
void editer_donnees_etudiant(etudiant *e);
void statistiques_ecole();
#endif
