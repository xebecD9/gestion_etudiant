#include "librairie.h"


etudiant bairo[nombre_max_d_etudiant];
int nombre_etudiant = 0;

/* =========================================================
   🛠️ FONCTIONS UTILITAIRES
   ========================================================= */

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void nettoyer_buffer_fgets(char *chaine) {
    chaine[strcspn(chaine, "\n")] = 0;
}

date extraction_date() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    date d;
    d.jour = tm->tm_mday;
    d.mois = tm->tm_mon + 1;
    d.annee = tm->tm_year + 1900;
    return d;
}
void pause() {
    printf("\nAppuyez sur [Entree] pour continuer...");
    getchar(); 
}
void effacer_ecran() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/* =========================================================
   💾 GESTION DES FICHIERS (PERSISTENCE)
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

void charger_donnees() {
    FILE *f = fopen("etudiants.txt", "r");
    if (f == NULL) return; 
    nombre_etudiant = 0;
    while (nombre_etudiant < nombre_max_d_etudiant && 
           fscanf(f, " %[^;];%[^;];%[^;];%d/%d/%d;%[^;];%[^;]; %c;%[^\n]", 
           bairo[nombre_etudiant].matricule, bairo[nombre_etudiant].nom, bairo[nombre_etudiant].prenom,
           &bairo[nombre_etudiant].date_naissance.jour, &bairo[nombre_etudiant].date_naissance.mois, &bairo[nombre_etudiant].date_naissance.annee,
           bairo[nombre_etudiant].departement, bairo[nombre_etudiant].filiere, 
           &bairo[nombre_etudiant].sexe, bairo[nombre_etudiant].region_origine) == 10) {
        nombre_etudiant++;
    }
    fclose(f);
}

/* =========================================================
   👥 GESTION ADMINISTRATIVE
   ========================================================= */

void ajouter_un_etudiant() {
    
    printf("┌──────────────────────────────────────────┐\n");
    printf("│      📝 NOUVELLE INSCRIPTION ENSPM       │\n");
    printf("└──────────────────────────────────────────┘\n");
    
    if (nombre_etudiant >= nombre_max_d_etudiant) {
        printf("⚠️ [Erreur] Capacité maximale atteinte.\n");
        return;
    }

    etudiant n;
    printf("🆔 Matricule        : "); fgets(n.matricule, size_max, stdin); nettoyer_buffer_fgets(n.matricule);
    printf("👤 Nom              : "); fgets(n.nom, size_max, stdin); nettoyer_buffer_fgets(n.nom);
    printf("👤 Prénom           : "); fgets(n.prenom, size_max, stdin); nettoyer_buffer_fgets(n.prenom);
    printf("🏢 Département      : "); fgets(n.departement, size_max, stdin); nettoyer_buffer_fgets(n.departement);
    printf("📚 Filière          : "); fgets(n.filiere, size_max, stdin); nettoyer_buffer_fgets(n.filiere);
    printf("🌍 Région d'origine : "); fgets(n.region_origine, size_max, stdin); nettoyer_buffer_fgets(n.region_origine);
    printf("🚻 Sexe (M/F)       : "); scanf(" %c", &n.sexe); vider_buffer();
    printf("📅 Date Naissance (JJ MM AAAA) : "); scanf("%d %d %d", &n.date_naissance.jour, &n.date_naissance.mois, &n.date_naissance.annee); vider_buffer(); 

    bairo[nombre_etudiant++] = n;
    sauvegarder_dans_fichier(n);
    printf("\n✅ Étudiant ajouté avec succès !\n");
}

void editer_donnees_etudiant(etudiant *e) {
    int choix;
    printf("\n--- 🛠️  MODIFICATION : %s %s ---\n", e->nom, e->prenom);
    printf(" 1. Nom        4. Filière      7. Date de naissance\n");
    printf(" 2. Prénom     5. Région       8. [TOUT MODIFIER]\n");
    printf(" 3. Dépt       6. Sexe\n");
    printf("👉 Choix : ");
    scanf("%d", &choix); vider_buffer();

    switch(choix) {
        case 1: printf("Nouveau Nom : "); fgets(e->nom, size_max, stdin); nettoyer_buffer_fgets(e->nom); break;
        case 2: printf("Nouveau Prénom : "); fgets(e->prenom, size_max, stdin); nettoyer_buffer_fgets(e->prenom); break;
        case 3: printf("Nouveau Dépt : "); fgets(e->departement, size_max, stdin); nettoyer_buffer_fgets(e->departement); break;
        case 4: printf("Nouvelle Filière : "); fgets(e->filiere, size_max, stdin); nettoyer_buffer_fgets(e->filiere); break;
        case 5: printf("Nouvelle Région : "); fgets(e->region_origine, size_max, stdin); nettoyer_buffer_fgets(e->region_origine); break;
        case 6: printf("Nouveau Sexe (M/F) : "); scanf(" %c", &e->sexe); vider_buffer(); break;
        case 7: printf("Nouvelle Date (JJ MM AAAA) : "); scanf("%d %d %d", &e->date_naissance.jour, &e->date_naissance.mois, &e->date_naissance.annee); vider_buffer(); break;
        case 8: ajouter_un_etudiant(); break; // Réutilise la logique d'ajout pour tout réécrire
        default: printf("⚠️ Choix invalide.\n");
    }
}

void modifier_etudiant() {
    char mat[size_max];
    printf("┌──────────────────────────────────────────────────┐\n");   
    printf("│ ⚙️  MODIFICATION DES INFORMATIONS ÉTUDIANT      │\n");
    printf("└──────────────────────────────────────────────────┘\n");
    printf("\n🔍 Entrez le matricule de l'étudiant dont on veut modifier les informations : ");
    fgets(mat, size_max, stdin); nettoyer_buffer_fgets(mat);

    for(int i = 0; i < nombre_etudiant; i++) {
        if (strcmp(bairo[i].matricule, mat) == 0) {
            editer_donnees_etudiant(&bairo[i]); 
            actualiser_fichier(); 
            printf("✅ Mise à jour effectuée.\n");
            return;
        }
    }
    printf("❌ Aucun étudiant trouvé avec ce matricule.\n");
}

void suppression_etudiant() {
    char mat[size_max];
    printf("\n🗑️  Matricule de l'étudiant à supprimer : ");
    fgets(mat, size_max, stdin); nettoyer_buffer_fgets(mat);

    for (int i = 0; i < nombre_etudiant; i++) {
        if (strcmp(bairo[i].matricule, mat) == 0) {
            for (int j = i; j < nombre_etudiant - 1; j++) bairo[j] = bairo[j+1];
            nombre_etudiant--;
            actualiser_fichier();
            printf("✅ Étudiant supprimé de la base.\n");
            return;
        }
    }
    printf("❌ Matricule introuvable.\n");
}

/* =========================================================
   🔍 RECHERCHE & ANALYSE
   ========================================================= */

void recherche() {
    int choice;
    printf("BIENVENUE DANS LE MODULE DE RECHERCHE DES ÉTUDIANTS\n");    
    do {
        printf("\n┌──────────────────────────────────────────┐\n");
        printf("│         🔍 MODULE DE RECHERCHE           │\n");
        printf("└──────────────────────────────────────────┘\n");
        printf(" 1. Recherche par comparaison simple\n");
        printf(" 2. Recherche dichotomique (Rapide)\n");
        printf(" 3. Retour au menu\n");
        printf("👉 Choix : ");
        scanf("%d", &choice); vider_buffer();

        char mat[size_max];
        etudiant res;
        if (choice == 1 || choice == 2) {
            printf("Matricule recherché : ");
            fgets(mat, size_max, stdin); nettoyer_buffer_fgets(mat);
            
            int trouve = (choice == 1) ? recherche_par_matricule(mat, &res) : recherche_dichotomique(mat, &res);
            
            if (trouve) printf("✅ TROUVÉ : %s %s (%s)\n", res.nom, res.prenom, res.filiere);
            else printf("❌ Aucun étudiant correspondant.\n");
        }
    } while(choice != 3);
}

int recherche_dichotomique(char matrecher[], etudiant *res) {
    int debut = 0, fin = nombre_etudiant - 1;
    while (debut <= fin) {
        int milieu = (debut + fin) / 2;
        int cmp = strcmp(bairo[milieu].matricule, matrecher);
        if (cmp == 0) { *res = bairo[milieu]; return 1; }
        else if (cmp < 0) debut = milieu + 1;
        else fin = milieu - 1;
    }
    return 0; 
}

int recherche_par_matricule(char mat[], etudiant *res) {
    for (int i = 0; i < nombre_etudiant; i++) {
        if (strcmp(bairo[i].matricule, mat) == 0) { *res = bairo[i]; return 1; }
    }
    return 0;
}

void calcul_age() {
    char mat[size_max];
    etudiant e;
    printf("┌──────────────────────────────────────────┐\n");
    printf("│        🎂 CALCUL DE L'ÂGE ÉTUDIANT       │\n");
    printf("└──────────────────────────────────────────┘\n");
    printf("\nEntrez matricule de l'étudiant dont on veut calculer l'age : ");
    fgets(mat, size_max, stdin); nettoyer_buffer_fgets(mat);

    if (recherche_par_matricule(mat, &e)) {
        date d = extraction_date();
        int age = d.annee - e.date_naissance.annee;
        if (d.mois < e.date_naissance.mois || (d.mois == e.date_naissance.mois && d.jour < e.date_naissance.jour)) age--;
        printf("💡 L'étudiant %s %s a %d ans.\n", e.prenom, e.nom, age);
    } else printf("❌ Étudiant introuvable.\n");
}

/* =========================================================
   📊 TRI & STATISTIQUES
   ========================================================= */
void apercu_tri(char* titre_tri) {
    effacer_ecran();
    printf("\n   >>> %s <<<\n", titre_tri);
    printf(" ┌──────┬────────────┬──────────────────────┬──────────┬───────────────────┐\n");
    printf(" │  N°  │ MATRICULE  │ NOM ET PRENOM        │ FILIÈRE  │DEPARTEMENT       │\n");
    printf(" ├──────┼────────────┼──────────────────────┼──────────┼───────────────────┤\n");

    for (int i = 0; i < nombre_etudiant; i++) {
        char nom_complet[size_max * 2];
        sprintf(nom_complet, "%s %s", bairo[i].nom, bairo[i].prenom);
        
        
        printf(" │ %-4d │ %-10s │ %-20s │ %-20s │%-20s\n", 
                i + 1, bairo[i].matricule, nom_complet, bairo[i].filiere, bairo[i].departement);
    }
    printf(" └──────┴────────────┴──────────────────────┴──────────────────────┘\n");
    printf("\n ✅ Tri appliqué avec succès.");
    pause();
}
void tri() {
    int choice;
    printf("BIENVENUE DANS LE MODULE DE TRI DES ÉTUDIANTS\n");
    do {
        printf("\n┌──────────────────────────────────────────┐\n");
        printf("│           📂 GESTION DES TRIS            │\n");
        printf("└──────────────────────────────────────────┘\n");
        printf(" 1. Par ordre alphabétique\n");
        printf(" 2. Par filière\n");
        printf(" 3. Par département\n");
        printf(" 4. Retour\n");
        printf("Enter l'option de tri souhaiter : ");
        scanf("%d", &choice); vider_buffer();

        switch(choice) {
            case 1: tri_alphabetique(); 
            break;
            case 2: tri_filiere(); break;
            case 3: tri_departement(); break;
        }
    } while(choice != 4);
}

void tri_alphabetique() {
    for(int i = 0; i < nombre_etudiant - 1; i++) {
        for(int j = i + 1; j < nombre_etudiant; j++) {
            if(strcmp(bairo[i].nom, bairo[j].nom) > 0) {
                etudiant tempo = bairo[i]; bairo[i] = bairo[j]; bairo[j] = tempo;
            }
        }
    }
    printf("✅ Liste triée par nom.\n");
    apercu_tri("TRI PAR ORDRE ALPHABÉTIQUE");
    
}

void tri_filiere() {
    // Logique de tri identique par champ filière
    for(int i = 0; i < nombre_etudiant - 1; i++) {
        for(int j = i + 1; j < nombre_etudiant; j++) {
            if(strcmp(bairo[i].filiere, bairo[j].filiere) > 0) {
                etudiant tempo = bairo[i]; bairo[i] = bairo[j]; bairo[j] = tempo;
            }
        }
    }
    printf("✅ Liste triée par filière.\n");
    apercu_tri("TRI PAR FILIÈRE");    
}

void tri_departement() {
    for(int i = 0; i < nombre_etudiant - 1; i++) {
        for(int j = i + 1; j < nombre_etudiant; j++) {
            if(strcmp(bairo[i].departement, bairo[j].departement) > 0) {
                etudiant tempo = bairo[i]; bairo[i] = bairo[j]; bairo[j] = tempo;
            }
        }
    }
    printf("✅ Liste triée par département.\n");
    apercu_tri("TRI PAR DÉPARTEMENT");

}

void statistiques_ecole() {
    
    charger_donnees();
    printf("BIENVENUE DANS LE MODULE DE STATISTIQUES DE L'ENSPM\n");

    if (nombre_etudiant == 0) {
        printf("\n⚠️  [Info] La base de données est vide. Aucune statistique à afficher.\n");
        return;
    }

    // --- 1. VARIABLES POUR LE SEXE ---
    int filles = 0, garcons = 0;

    // --- 2. STRUCTURES POUR LES AUTRES CATEGORIES ---
    // On utilise tes structures StatItem pour compter les occurrences
    StatItem stats_reg[nombre_max_d_etudiant]; 
    StatItem stats_fil[nombre_max_d_etudiant]; 
    StatItem stats_dept[nombre_max_d_etudiant];
    
    int nb_reg = 0, nb_fil = 0, nb_dep = 0;

    for (int i = 0; i < nombre_etudiant; i++) {
        // Comptage Sexe
        if (bairo[i].sexe == 'F' || bairo[i].sexe == 'f') filles++;
        else garcons++;

        // Comptage Régions
        int trouve = 0;
        for (int j = 0; j < nb_reg; j++) {
            if (strcmp(bairo[i].region_origine, stats_reg[j].label) == 0) {
                stats_reg[j].compteur++; trouve = 1; break;
            }
        }
        if (!trouve) { 
            strcpy(stats_reg[nb_reg].label, bairo[i].region_origine); 
            stats_reg[nb_reg].compteur = 1; nb_reg++; 
        }

        // Comptage Départements
        trouve = 0;
        for (int j = 0; j < nb_dep; j++) {
            if (strcmp(bairo[i].departement, stats_dept[j].label) == 0) {
                stats_dept[j].compteur++; trouve = 1; break;
            }
        }
        if (!trouve) { 
            strcpy(stats_dept[nb_dep].label, bairo[i].departement); 
            stats_dept[nb_dep].compteur = 1; nb_dep++; 
        }

        // Comptage Filières
        trouve = 0;
        for (int j = 0; j < nb_fil; j++) {
            if (strcmp(bairo[i].filiere, stats_fil[j].label) == 0) {
                stats_fil[j].compteur++; trouve = 1; break;
            }
        }
        if (!trouve) { 
            strcpy(stats_fil[nb_fil].label, bairo[i].filiere); 
            stats_fil[nb_fil].compteur = 1; nb_fil++; 
        }
    }

    // --- AFFICHAGE DU RAPPORT GLOBAL ---
    printf("\n┌────────────────────────────────────────────────────────┐\n");
    printf("│        📊  RAPPORT STATISTIQUE GLOBAL - ENSPM          │\n");
    printf("└────────────────────────────────────────────────────────┘\n");
    printf("  👥 Effectif Total : %d étudiants\n", nombre_etudiant);

    printf("\n🔹 RÉPARTITION PAR GENRE 🚻\n");
    printf("  • 👩 Filles  : %d (%.1f%%)\n", filles, (filles * 100.0) / nombre_etudiant);
    printf("  • 👨 Garçons : %d (%.1f%%)\n", garcons, (garcons * 100.0) / nombre_etudiant);

    printf("\n🔹 RÉPARTITION PAR DÉPARTEMENT 🏢\n");
    for (int i = 0; i < nb_dep; i++) {
        printf("  • %-20s : %d étudiants\n", stats_dept[i].label, stats_dept[i].compteur);
    }

    printf("\n🔹 RÉPARTITION PAR FILIÈRE 📚\n");
    for (int i = 0; i < nb_fil; i++) {
        printf("  • %-20s : %d étudiants\n", stats_fil[i].label, stats_fil[i].compteur);
    }

    printf("\n🔹 RÉPARTITION PAR RÉGION 🌍\n");
    for (int i = 0; i < nb_reg; i++) {
        printf("  • %-20s : %d étudiants\n", stats_reg[i].label, stats_reg[i].compteur);
    
    }

    printf("\n──────────────────────────────────────────────────────────\n");
    printf("Appuyez sur une touche pour revenir au menu...");
    getchar();
}

/* =========================================================
   📄 AFFICHAGE & EXPORT
   ========================================================= */
void affiche_liste_etudiant() {
    if (nombre_etudiant == 0) {
        printf("\n⚠️  La base de données est vide. Rien à exporter.\n");
        return;
    }

    FILE *f = fopen("liste des etudiants.txt", "w");
    if (f == NULL) {
        printf("❌ Erreur lors de la création du fichier.\n");
        return;
    }

    // --- EN-TÊTE DU FICHIER ---
    fprintf(f, "                      📄  LISTE OFFICIELLE DES ETUDIANTS (ENSPM) 📄 \n");
    fprintf(f, "┌──────┬────────────┬──────────────────────┬──────────────────────┬─────────────────┬───────────────┐\n");
    fprintf(f, "│  N°  │ MATRICULE  │ NOM ET PRENOM        │ FILIERE              │ DEPARTEMENT     │   REGION      │\n");
    fprintf(f, "├──────┼────────────┼──────────────────────┼──────────────────────┼─────────────────┼───────────────┤\n");

    // --- EN-TÊTE CONSOLE ---
    effacer_ecran();
    printf("\n   >>> APERÇU COMPLET DE LA LISTE DES ETUDIANTS <<<\n\n");
    printf(" %-4s | %-10s | %-20s | %-15s | %-12s | %-10s | %-6s\n", "N°", "MATRICULE", "NOM COMPLET", "FILIERE", "DEPARTEMENT", "REGION","SEXE");
    printf(" ------------------------------------------------------------------------------------------------------\n");

    // --- BOUCLE DE REMPLISSAGE (Uniquement pour les lignes) ---
    for (int i = 0; i < nombre_etudiant; i++) {
        char nom_complet[size_max * 2]; 
        sprintf(nom_complet, "%s %s", bairo[i].nom, bairo[i].prenom);

        // Ecriture dans le fichier
        fprintf(f, "│ %-4d │ %-10s │ %-20s │ %-20s │ %-15s │ %-13s │%4c\n", 
                i + 1, bairo[i].matricule, nom_complet, bairo[i].filiere, bairo[i].departement, bairo[i].region_origine, bairo[i].sexe);

        // Affichage à l'écran
        printf(" %-4d | %-10s | %-20s | %-15s | %-12s | %-10s | %c\n", 
                i + 1, bairo[i].matricule, nom_complet, bairo[i].filiere, bairo[i].departement, bairo[i].region_origine, bairo[i].sexe); 
    } 

    
    fprintf(f, "└──────┴────────────┴──────────────────────┴──────────────────────┴─────────────────┴───────────────┘\n");
    fprintf(f, "\nTotal : %d etudiants enregistres.\n", nombre_etudiant);

    fclose(f);

    printf("\n------------------------------------------------------------------------------------------------------\n");
    printf("✅ Liste générée dans 'liste des etudiants.txt'\n");
    
}
/* =========================================================
   📱 MENU PRINCIPAL
   ========================================================= */

void afficher_menu_principal() {
    printf("  ┌──────────────────────────────────────────────────┐\n");
    printf("  │      🎓 GESTION ÉTUDIANTS ENSPM🎓               │\n");
    printf("  └──────────────────────────────────────────────────┘\n");
    printf("    1.  ➕ Ajouter un étudiant\n");
    printf("    2.  🔍 Recherche & Filtres\n");
    printf("    3.  🎂 Calculer l'âge\n");
    printf("    4.  ⚙️ Modifier les informations d'un étudiant\n");
    printf("    5.  🗑️ Supprimer un étudiant\n");
    printf("    6.  📂 Trier des étudiants\n");
    printf("    7.  📄 Generer la liste des etudiants(.txt)\n");
    printf("    8.  📊 Statistiques globales\n");
    printf("    0.  🚪 Quitter le programme\n");
    printf("  ──────────────────────────────────────────────\n");

}