#include "librairie.h"

etudiant bairo[nombre_max_d_etudiant];
int nombre_etudiant = 0 ;
/* =========================================================
   FONCTIONS UTILITAIRES
   ========================================================= */

// Vide le tampon d'entrée pour éviter les sauts de saisie (après un scanf)
void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Supprime le caractère '\n' ajouté par fgets à la fin des chaînes
void nettoyer_buffer_fgets(char *chaine) {
    chaine[strcspn(chaine, "\n")] = 0;
}

// Récupère la date système pour le calcul de l'âge
date extraction_date() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    date d;
    d.jour = tm->tm_mday;
    d.mois = tm->tm_mon + 1;
    d.annee = tm->tm_year + 1900;
    return d;
}

/* =========================================================
   FONCTIONS DE  GESTION DES FICHIERS 
   ========================================================= */



void sauvegarder_dans_fichier(etudiant e) {
    FILE *f = fopen("etudiants.txt", "a"); 
    if (f == NULL) return;
    
    fprintf(f, "%s;%s;%s;%02d/%02d/%04d;%s;%s;%c;%s\n", 
            e.matricule, e.nom, e.prenom, 
            e.date_naissance.jour, e.date_naissance.mois, e.date_naissance.annee, 
            e.departement, e.filiere, e.sexe, e.region_origine);
    fclose(f);
}

void actualiser_fichier() {
    FILE *f = fopen("etudiants.txt", "w");
    if (f == NULL) return;

    for (int i = 0; i < nombre_etudiant; i++) {
        fprintf(f, "%s;%s;%s;%02d/%02d/%04d;%s;%s;%c;%s\n", 
                bairo[i].matricule, bairo[i].nom, bairo[i].prenom, 
                bairo[i].date_naissance.jour, bairo[i].date_naissance.mois, bairo[i].date_naissance.annee, 
                bairo[i].departement, bairo[i].filiere, bairo[i].sexe, bairo[i].region_origine);
    }
    fclose(f);
}
// Charge les données du fichier vers la mémoire RAM au démarrage
void charger_donnees() {
    FILE *f = fopen("etudiants.txt", "r");
    if (f == NULL) return; 

    nombre_etudiant = 0;
    // On ajoute / entre les %d pour lire le format jj/mm/aaaa
    while (nombre_etudiant < nombre_max_d_etudiant && 
           fscanf(f, " %[^;];%[^;];%[^;];%d/%d/%d;%[^;];%[^;]; %c;%[^\n]", 
           bairo[nombre_etudiant].matricule, 
           bairo[nombre_etudiant].nom, 
           bairo[nombre_etudiant].prenom,
           &bairo[nombre_etudiant].date_naissance.jour, 
           &bairo[nombre_etudiant].date_naissance.mois, 
           &bairo[nombre_etudiant].date_naissance.annee,
           bairo[nombre_etudiant].departement, 
           bairo[nombre_etudiant].filiere, 
           &bairo[nombre_etudiant].sexe, 
           bairo[nombre_etudiant].region_origine) == 10) {
        nombre_etudiant++;
    }
    fclose(f);
}

/*FONCTION DES GESTIONS DES ETUDIANTS*/
void affiche_liste_etudiant() {
    if (nombre_etudiant == 0) {
        printf("Aucun etudiant a afficher.\n");
        return;
    }

    FILE *f = fopen("liste des etudiants.txt", "w");
    if (f == NULL) {
        printf("Erreur de creation de la liste des etudiants.\n");
        return;
    }


    fprintf(f, "========================================================================================================\n");
    fprintf(f, "                                 LISTE DES ETUDIANTS - ENSPM                                            \n");
    fprintf(f, "========================================================================================================\n\n");

    
    fprintf(f, "%-4s | %-12s | %-15s | %-15s | %-12s | %-4s | %-15s\n", 
            "N°", "MATRICULE", "NOM", "PRENOM", "NAISSANCE", "SEXE", "FILIERE");
    fprintf(f, "--------------------------------------------------------------------------------------------------------\n");

    
    for (int i = 0; i < nombre_etudiant; i++) {
        fprintf(f, "%-4d | %-12s | %-15s | %-15s | %02d/%02d/%04d | %-4c | %-15s\n", 
                i + 1, 
                bairo[i].matricule, 
                bairo[i].nom, 
                bairo[i].prenom,
                bairo[i].date_naissance.jour, 
                bairo[i].date_naissance.mois, 
                bairo[i].date_naissance.annee,
                bairo[i].sexe, 
                bairo[i].filiere);
    }

    fprintf(f, "--------------------------------------------------------------------------------------------------------\n");
    

    fclose(f);
    printf("\n[Succes] La liste des etudiants a ete generee dans 'liste des etudiants.txt'.\n");
}
// Affiche les étudiants groupés par filière
void tri_filiere() {
    if (nombre_etudiant == 0) {
        printf("\n[Error]Aucun etudiant en memoire.\n");
        return;
    }

    
    for(int i = 0; i < nombre_etudiant - 1; i++) {
        for(int j = i + 1; j < nombre_etudiant; j++) {
            if(strcmp(bairo[i].filiere, bairo[j].filiere) > 0) {
                etudiant tempo = bairo[i];
                bairo[i] = bairo[j];
                bairo[j] = tempo;
            }
        }
    }

    char filiere_actuelle[size_max] = "";
    for(int i = 0; i < nombre_etudiant; i++) {
        if(strcmp(filiere_actuelle, bairo[i].filiere) != 0) {
            strcpy(filiere_actuelle, bairo[i].filiere);
            printf("\n\n>>> FILIERE : %-20s\n", filiere_actuelle);
            printf("-----------------------------------------------------------------------------------------------------------\n");
            printf("%-12s | %-15s | %-15s | %-10s | %-4s | %-15s\n", "MATRICULE", "NOM", "PRENOM", "NAISSANCE", "SEXE", "REGION");
            printf("-----------------------------------------------------------------------------------------------------------\n");
        }
        printf("%-12s | %-15s | %-15s | %02d/%02d/%-4d | %-4c | %-15s\n", 
               bairo[i].matricule, bairo[i].nom, bairo[i].prenom,
               bairo[i].date_naissance.jour, bairo[i].date_naissance.mois, bairo[i].date_naissance.annee,
               bairo[i].sexe, bairo[i].region_origine);
    }
}

// Affiche les étudiants par ordre alphabétique 
void tri_alphabetique() {
    if (nombre_etudiant == 0) {
        printf("\n[Error] Aucun etudiant enregistre.\n");
        return;
    }

    for(int i = 0; i < nombre_etudiant - 1; i++) {
        for(int j = i + 1; j < nombre_etudiant; j++) {
            if(strcmp(bairo[i].nom, bairo[j].nom) > 0 || 
              (strcmp(bairo[i].nom, bairo[j].nom) == 0 && strcmp(bairo[i].prenom, bairo[j].prenom) > 0)) {
                etudiant tempo = bairo[i];
                bairo[i] = bairo[j];
                bairo[j] = tempo;
            }
        }
    }

    printf("\nLISTE ALPHABETIQUE DES ETUDIANTS\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("%-12s | %-15s | %-15s | %-15s | %-4s\n", "MATRICULE", "NOM", "PRENOM", "FILIERE", "SEXE");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < nombre_etudiant; i++) {
        printf("%-12s | %-15s | %-15s | %-15s | %-4c\n", 
               bairo[i].matricule, bairo[i].nom, bairo[i].prenom, bairo[i].filiere, bairo[i].sexe);
    }
}

void ajouter_un_etudiant() {
    if (nombre_etudiant >= nombre_max_d_etudiant) {
        printf("\n[Erreur] Capacite maximale atteinte.\n");
        return;
    }

    etudiant n;
    printf("\n--- AJOUT D' UN ETUDIANT ---\n");

    // Saisie des chaînes (fgets)
    printf("Matricule   : "); 
    fgets(n.matricule, size_max, stdin); 
    nettoyer_buffer_fgets(n.matricule);

    printf("Nom         : "); 
    fgets(n.nom, size_max, stdin); 
    nettoyer_buffer_fgets(n.nom);

    printf("Prenom      : "); 
    fgets(n.prenom, size_max, stdin); 
    nettoyer_buffer_fgets(n.prenom);

    printf("Departement : "); 
    fgets(n.departement, size_max, stdin); 
    nettoyer_buffer_fgets(n.departement);

    printf("Filiere     : "); 
    fgets(n.filiere, size_max, stdin); 
    nettoyer_buffer_fgets(n.filiere);

    printf("Region d'origine : "); 
    fgets(n.region_origine, size_max, stdin); 
    nettoyer_buffer_fgets(n.region_origine);

    // Saisie du Sexe
    printf("Sexe (M/F)  : ");
    scanf(" %c", &n.sexe); 
    vider_buffer();

    
    printf("--- Date de Naissance ---\n");
    printf("  Jour (JJ)  : "); scanf("%d", &n.date_naissance.jour);
    printf("  Mois (MM)  : "); scanf("%d", &n.date_naissance.mois);
    printf("  Annee (AAAA): "); scanf("%d", &n.date_naissance.annee);
    vider_buffer(); 

    // Stockage et sauvegarde
    bairo[nombre_etudiant] = n;
    nombre_etudiant++;

    sauvegarder_dans_fichier(n);

    printf("\n[Succes] Etudiant ajoute !\n");
}
void modifier_une_information_de_l_etudiant() {
    char mat[size_max];
    printf("\n=== MODIFICATION D'UNE INFORMATION D'UN ETUDIANT ===\n");
    printf("Entrez le matricule de l'etudiant : ");
    fgets(mat, size_max, stdin); 
    nettoyer_buffer_fgets(mat);

    int idx = -1;
    for(int i = 0; i < nombre_etudiant; i++) {
        if (strcmp(bairo[i].matricule, mat) == 0) { 
            idx = i; 
            break; 
        }
    }

    if(idx == -1) { 
        printf("Etudiant introuvable.\n"); 
        return; 
    }

    int choix;
    printf("\nVoici les informations que vous pouvez modifier:\n"); 
    printf("1.Nom\n");
    printf("2.Prenom\n");
    printf("3.departement\n");
    printf("4.filiere\n");
    printf("5.region d'origine\n");
    printf("6.sexe\n");
    printf("7.date de naissance\n"); 
    printf("Veuillez entrer le numero de l'information que vous souhaitez modifier:");
    scanf("%d", &choix); 
    vider_buffer();

    switch(choix) {
            case 1: printf("Nom : "); 
            fgets(bairo[idx].nom, size_max, stdin); 
            nettoyer_buffer_fgets(bairo[idx].nom); 
            break;
        case 2:
            printf("prenom :");
            fgets(bairo[idx].prenom, size_max, stdin);
            nettoyer_buffer_fgets(bairo[idx].prenom);  
        case 3: 
            printf("Departement : "); 
            fgets(bairo[idx].departement, size_max, stdin); 
            nettoyer_buffer_fgets(bairo[idx].departement); 
            break;
        case 4: 
            printf("Filiere : "); 
            fgets(bairo[idx].filiere, size_max, stdin); 
            nettoyer_buffer_fgets(bairo[idx].filiere); 
            break;
        case 5:
            printf("Region d'origine : "); 
            fgets(bairo[idx].region_origine, size_max, stdin); 
            nettoyer_buffer_fgets(bairo[idx].region_origine); 
            break;
        case 6: 
            printf("Sexe : "); 
            scanf(" %c", &bairo[idx].sexe); 
            vider_buffer(); 
            break;
        case 7: 
            printf("Date (JJ MM AAAA) : "); 
            scanf("%d %d %d", &bairo[idx].date_naissance.jour, &bairo[idx].date_naissance.mois, &bairo[idx].date_naissance.annee); 
            vider_buffer(); 
            break;
        default: 
            printf("Invalide.\n"); 
            return;
    }
actualiser_fichier();
printf("Mise a jour reussie.\n");
}

void suppression_etudiant() {
    char mat[size_max];
    printf("\n=== SUPPRESSION D'UN ETUDIANT ===\n");
    printf("Matricule a supprimer : ");
    fgets(mat, size_max, stdin); 
    nettoyer_buffer_fgets(mat);

    for (int i = 0; i < nombre_etudiant; i++) {
        if (strcmp(bairo[i].matricule, mat) == 0) {
            for (int j = i; j < nombre_etudiant - 1; j++) bairo[j] = bairo[j+1];
            nombre_etudiant--;
            actualiser_fichier();
            printf("Etudiant supprime.\n");
            return;
        }
    }
    printf("Non trouve.\n");
}


int recherche_dichotomique(char matrecher[], etudiant *res) {
    int debut = 0, fin = nombre_etudiant - 1;
    printf("\n=== RECHERCHE DICHOTOMIQUE D'UN ETUDIANT ===\n");
    while (debut <= fin) {
        int milieu = (debut + fin) / 2;
        int cmp = strcmp(bairo[milieu].matricule, matrecher);
        if (cmp == 0) {
            *res = bairo[milieu];
            return 1; 
        } else if (cmp < 0) {
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
        }
    }
    return 0; 
}
int recherche_par_matricule(char mat[], etudiant *res) {
    
    for (int i = 0; i < nombre_etudiant; i++) {
        if (strcmp(bairo[i].matricule, mat) == 0) {
            *res = bairo[i];
            return 1;
        }
    }
    return 0;
}

void calcul_age() {
    char mat[size_max];
    etudiant e;
    printf("\n=== CALCUL DE L'AGE D'UN ETUDIANT ===\n");
    printf("Veuillez entrer le matricule de l'etudiant dont vous voulez calculer l'age: ");
    fgets(mat, size_max, stdin); 
    nettoyer_buffer_fgets(mat);

    if (recherche_par_matricule(mat, &e)) {
        date d = extraction_date();
        int age = d.annee - e.date_naissance.annee;
        if (d.mois < e.date_naissance.mois || (d.mois == e.date_naissance.mois && d.jour < e.date_naissance.jour))
            age--;
        printf("L'etudiant %s a %d ans.\n", e.nom, age);
    } else printf("Introuvable.\n");
}

void afficher_menu() {
    printf("\n===============================================\n");
    printf("   SYSTEME DE GESTION DES ETUDIANTS - ENSPM   \n");
    printf("===============================================\n");
    printf("1. Ajouter un etudiant\n");
    printf("2. Rechercher un etudiant par son Matricule\n");
    printf("3. Rechercher un etudiant par dichotomie\n");
    printf("4. Calculer l'age d'un etudiant\n");
    printf("5. Modifier les informations d'un etudiant \n");
    printf("6. Supprimer un etudiant\n");
    printf("7. Tri Alphabetique des etudiants\n");
    printf("8. Tri par Filiere des etudiants\n");
    printf("9. Generer la liste des etudiants\n");
    printf("10. Quitter\n");
    
}

