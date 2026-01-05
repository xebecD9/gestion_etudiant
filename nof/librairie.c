#include "librairie.h"

etudiant bairo[nombre_max_d_etudiant];
int nombre_etudiant = 0 ;



/* =========================================================
   🎓 SYSTEME DE GESTION DES ETUDIANTS - ENSPM 🎓
   ========================================================= */



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

/* =========================================================
   💾 GESTION DES FICHIERS
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
}void charger_donnees() {
    FILE *f = fopen("etudiants.txt", "r");
    if (f == NULL) return; 

    nombre_etudiant = 0;
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


/*==========================================================
   👥 GESTION DES ETUDIANTS
  ==========================================================*/

void ajouter_un_etudiant() {
    if (nombre_etudiant >= nombre_max_d_etudiant) {
        printf("\n⚠️  [Erreur] Capacité maximale atteinte.\n");
        return;
    }

    etudiant n;
    printf("\n--- 📝 FORMULAIRE D'INSCRIPTION ---\n");
    printf("🆔 Matricule        : "); 
    fgets(n.matricule, size_max, stdin); 
    nettoyer_buffer_fgets(n.matricule);

    printf("👤 Nom              : "); 
    fgets(n.nom, size_max, stdin); 
    nettoyer_buffer_fgets(n.nom);

    printf("👤 Prénom           : "); 
    fgets(n.prenom, size_max, stdin); 
    nettoyer_buffer_fgets(n.prenom);

    printf("🏢 Département      : "); 
    fgets(n.departement, size_max, stdin); 
    nettoyer_buffer_fgets(n.departement);

    printf("📚 Filière          : "); 
    fgets(n.filiere, size_max, stdin); 
    nettoyer_buffer_fgets(n.filiere);

    printf("🌍 Région d'origine : "); 
    fgets(n.region_origine, size_max, stdin); 
    nettoyer_buffer_fgets(n.region_origine);

    printf("🚻 Sexe (M/F)       : ");
    scanf(" %c", &n.sexe); 
    vider_buffer();

    printf("📅 Date de Naissance (JJ MM AAAA) : ");
    scanf("%d %d %d", &n.date_naissance.jour, &n.date_naissance.mois, &n.date_naissance.annee);
    vider_buffer(); 

    bairo[nombre_etudiant] = n;
    nombre_etudiant++;
    sauvegarder_dans_fichier(n);

    printf("\n✅ [Succès] Étudiant ajouté avec succès !\n");
}
void editer_donnees_etudiant(etudiant *e) {
    int choix;
    printf("\n--- 🛠️  MODIFICATION DE : %s %s ---\n", e->nom, e->prenom);
    printf("Quelle information souhaitez-vous modifier ?\n");
    printf(" 1. Nom          4. Filiere      7. Date de naissance\n");
    printf(" 2. Prenom       5. Region       8. TOUT MODIFIER\n");
    printf(" 3. Departement  6. Sexe\n");
    printf("👉 Entrez votre choix : ");
    scanf("%d", &choix); 
    vider_buffer();

    printf("✨ Entrez la nouvelle information : ");
    switch(choix) {
        case 1: fgets(e->nom, size_max, stdin); nettoyer_buffer_fgets(e->nom); break;
        case 2: fgets(e->prenom, size_max, stdin); nettoyer_buffer_fgets(e->prenom); break;
        case 3: fgets(e->departement, size_max, stdin); nettoyer_buffer_fgets(e->departement); break;
        case 4: fgets(e->filiere, size_max, stdin); nettoyer_buffer_fgets(e->filiere); break;
        case 5: fgets(e->region_origine, size_max, stdin); nettoyer_buffer_fgets(e->region_origine); break;
        case 6: printf("(M/F) : "); scanf(" %c", &e->sexe); vider_buffer(); break;
        case 7: 
            printf("(JJ MM AAAA) : ");
            scanf("%d %d %d", &e->date_naissance.jour, &e->date_naissance.mois, &e->date_naissance.annee);
            vider_buffer();
            break;
        case 8:{

            printf("\n--- 📝 MODIFICATION COMPLETE ---\n");
            printf("👤 Nom : "); 
            fgets(e->nom, size_max, stdin); 
            nettoyer_buffer_fgets(e->nom);
            printf("👤 Prénom : "); 
            fgets(e->prenom, size_max, stdin); 
            nettoyer_buffer_fgets(e->prenom);
            printf("🏢 Département : "); 
            fgets(e->departement, size_max, stdin); 
            nettoyer_buffer_fgets(e->departement);
            printf("📚 Filière : "); 
            fgets(e->filiere, size_max, stdin); 
            nettoyer_buffer_fgets(e->filiere);
            printf("🌍 Région : "); 
            fgets(e->region_origine, size_max, stdin); 
            nettoyer_buffer_fgets(e->region_origine);
            printf("🚻 Sexe (M/F) : "); 
            scanf(" %c", &e->sexe); 
            vider_buffer();
            printf("📅 Date (JJ MM AAAA) : "); 
            scanf("%d %d %d", &e->date_naissance.jour, &e->date_naissance.mois, &e->date_naissance.annee);
            vider_buffer();
            break;
        }

        default: 
        printf("⚠️ Choix invalide.\n");
    }
}
void modifier_une_information_de_l_etudiant() {
    char mat[size_max];
    printf("\n--- 🔍 RECHERCHE POUR MODIFICATION ---\n");
    printf("Entrez le matricule : ");
    fgets(mat, size_max, stdin); 
    nettoyer_buffer_fgets(mat);

    int b=0;
    for(int i = 0; i < nombre_etudiant; i++) {
        if (strcmp(bairo[i].matricule, mat) == 0) {
            
            printf("\n--- ✏️ MODIFICATION DES INFORMATIONS DE L'ÉTUDIANT ---\n");
            editer_donnees_etudiant(&bairo[i]); 
            
            actualiser_fichier(); 
            printf("✅ [Succès] Informations mises à jour.\n");
            b = 1;
            break; 
        }
    }

    if(!b) { 
        printf("❌ [Erreur] Aucun étudiant trouvé avec le matricule : %s\n", mat); 
    }
}

void calcul_age() {
    char mat[size_max];
    etudiant e;
    printf("\n--- 🎂 CALCUL D'ÂGE ---\n");
    printf("🔍 Matricule de l'étudiant : ");
    fgets(mat, size_max, stdin); 
    nettoyer_buffer_fgets(mat);

    if (recherche_par_matricule(mat, &e)) {
        date d = extraction_date();
        int age = d.annee - e.date_naissance.annee;
        if (d.mois < e.date_naissance.mois || (d.mois == e.date_naissance.mois && d.jour < e.date_naissance.jour))
            age--;
        printf("💡 L'étudiant %s %s a %d ans.\n", e.prenom, e.nom, age);
    } else {
        printf("❌ Étudiant introuvable.\n");
    }
}
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


    fprintf(f, "=========================================================================================================================\n");
    fprintf(f, "                                                 LISTE DES ETUDIANTS - ENSPM                                            \n");
    fprintf(f, "=========================================================================================================================\n\n");

    
    fprintf(f, "%-4s | %-12s | %-15s | %-15s | %-12s | %-4s | %-15s\n", 
            "N°", "MATRICULE", "NOM", "PRENOM", "NAISSANCE", "SEXE", "FILIERE","DEPARTEMENT","REGION D'ORIGINE");
    fprintf(f, "---------------------------------------------------------------------------------------------------------------------------\n");

    
    for (int i = 0; i < nombre_etudiant; i++) {
        fprintf(f, "%-4d | %-12s | %-15s | %-15s | %02d/%02d/%04d | %-4c | %-15s|%-15s|%-15s\n", 
                i + 1, 
                bairo[i].matricule, 
                bairo[i].nom, 
                bairo[i].prenom,
                bairo[i].date_naissance.jour, 
                bairo[i].date_naissance.mois, 
                bairo[i].date_naissance.annee,
                bairo[i].sexe, 
                bairo[i].filiere,
                bairo[i].departement,
                bairo[i].region_origine
            );
    }

    fprintf(f, "--------------------------------------------------------------------------------------------------------------------------------\n");
    

    fclose(f);
    printf("\n[Succes] La liste des etudiants a ete generee dans 'liste des etudiants.txt'.\n");
}
void tri_departement(){
    if(nombre_etudiant == 0){
        printf("\n[Error]aucun etudiant en memoire.\n");
        return;
    }
     for(int i = 0; i < nombre_etudiant - 1; i++) {
        for(int j = i + 1; j < nombre_etudiant; j++) {
            if(strcmp(bairo[i].departement, bairo[j].departement) > 0) {
                etudiant tempo = bairo[i];
                bairo[i] = bairo[j];
                bairo[j] = tempo;
            }
        }
    }
        char departement_ok[size_max] = "";
    for(int i = 0; i < nombre_etudiant; i++) {
        if(strcmp(departement_ok, bairo[i].departement) != 0) {
            strcpy(departement_ok, bairo[i].departement);
            printf("\n\n>>> DEPARTEMENT: %-20s\n", departement_ok);
            printf("-----------------------------------------------------------------------------------------------------------\n");
            printf("%-12s | %-15s | %-15s | %-10s |%-12s| %-4s | %-15s\n", "MATRICULE", "NOM", "PRENOM", "NAISSANCE","FILIERE", "SEXE", "REGION");
            printf("-----------------------------------------------------------------------------------------------------------\n");
        }
        printf("%-12s | %-15s | %-15s | %02d/%02d/%-4d |%-12s| %-4c | %-15s\n", 
               bairo[i].matricule, bairo[i].nom, bairo[i].prenom,
               bairo[i].date_naissance.jour, bairo[i].date_naissance.mois, bairo[i].date_naissance.annee,bairo[i].filiere,
               bairo[i].sexe, bairo[i].region_origine);
    }
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
void suppression_etudiant() {
    char mat[size_max];
    
    printf("Entrer le matricule de l'etudiant a supprimer: ");
    fgets(mat, size_max, stdin); 
    nettoyer_buffer_fgets(mat);

    for (int i = 0; i < nombre_etudiant; i++) {
        if (strcmp(bairo[i].matricule, mat) == 0) {
            for (int j = i; j < nombre_etudiant - 1; j++) bairo[j] = bairo[j+1];
            nombre_etudiant--;
            actualiser_fichier();
            printf("Etudiant supprime 🗑️.\n");
            return;
        }
    }
    printf("Non trouve.\n");
}


int recherche_dichotomique(char matrecher[], etudiant *res) {
    int debut = 0, fin = nombre_etudiant - 1;
    
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

void statistiques_ecole() {
    charger_donnees();
    if (nombre_etudiant == 0) {
        printf("\n⚠️  [Erreur] Aucune donnée disponible pour les statistiques.\n");
        return;
    }

    
    StatItem stats_region[nombre_max_d_etudiant]; 
    StatItem stats_fil[nombre_max_d_etudiant]; 
    StatItem stats_dept[nombre_max_d_etudiant];
    int nb_reg = 0, nb_fil = 0, nb_dep = 0;
    int filles = 0, garcons = 0;

    for (int i = 0; i < nombre_etudiant; i++) {
        
        if (bairo[i].sexe == 'F' || bairo[i].sexe == 'f') filles++;
        else if (bairo[i].sexe == 'M' || bairo[i].sexe == 'm') garcons++;


        int trouve_region = 0;
        for (int j = 0; j < nb_reg; j++) {
            if (strcmp(bairo[i].region_origine, stats_region[j].label) == 0) {
                stats_region[j].compteur++; 
                trouve_region = 1; 
                break;
            }
        }
        if (!trouve_region && nb_reg < nombre_max_d_etudiant) { 
            strcpy(stats_region[nb_reg].label, bairo[i].region_origine); 
            stats_region[nb_reg].compteur = 1; 
            nb_reg++; }


        int trouve_filiere = 0;    
        for (int j = 0; j < nb_fil; j++) {
            if (strcmp(bairo[i].filiere, stats_fil[j].label) == 0) {
                stats_fil[j].compteur++; trouve_filiere = 1; break;
            }
        }
        if (!trouve_filiere && nb_fil < nombre_max_d_etudiant) { 
            strcpy(stats_fil[nb_fil].label, bairo[i].filiere); 
            stats_fil[nb_fil].compteur = 1; 
            nb_fil++; 
        }


        int trouve_departement = 0;
        for (int j = 0; j < nb_dep; j++) {
            if (strcmp(bairo[i].departement, stats_dept[j].label) == 0) {
                stats_dept[j].compteur++; 
                trouve_departement = 1;
                break;
            }
        }
        if (!trouve_departement && nb_dep < nombre_max_d_etudiant) { 
            strcpy(stats_dept[nb_dep].label, bairo[i].departement); 
            stats_dept[nb_dep].compteur = 1; 
            nb_dep++; 
        }
    }

    // Affichage des résultats
    printf("\n=====================================================\n");
    printf("📊       RAPPORT STATISTIQUE GLOBAL - ENSPM        📊\n");
    printf("=====================================================\n");
    printf("👥 Effectif Total : %d étudiants\n", nombre_etudiant);
    
    printf("\n🔹 RÉPARTITION PAR GENRE 🚻\n");
    printf("   👩 Filles  : %d (%.1f%%)\n", filles, (filles * 100.0) / nombre_etudiant);
    printf("   👨 Garçons : %d (%.1f%%)\n", garcons, (garcons * 100.0) / nombre_etudiant);

    printf("\n🔹 RÉPARTITION PAR DÉPARTEMENT 🏢\n");
    for (int i = 0; i < nb_dep; i++) printf("   📍 %-15s : %d\n", stats_dept[i].label, stats_dept[i].compteur);

     printf("\n🔹 RÉPARTITION PAR FILIÈRE 📚\n");
    for (int i = 0; i < nb_fil; i++) printf("   🎓 %-15s : %d\n", stats_fil[i].label, stats_fil[i].compteur);

    printf("\n🔹 RÉPARTITION PAR RÉGION 🌍\n");
    for (int i = 0; i < nb_reg; i++) printf("   🌍 %-15s : %d\n", stats_region[i].label, stats_region[i].compteur);
    printf("=====================================================\n");
}
/* =========================================================
   📱 INTERFACE UTILISATEUR (MENU)
   ========================================================= */

void afficher_menu() {
    printf("\n");
    printf("    ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("    ┃      🎓 GESTION DES ÉTUDIANTS - ENSPM      ┃\n");
    printf("    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("    1.  ➕ Ajouter un étudiant\n");
    printf("    2.  🔍 Recherche par Matricule\n");
    printf("    3.  ⚡ Recherche rapide (Dichotomie)\n");
    printf("    4.  🎂 Calculer l'âge\n");
    printf("    5.  ⚙️  Modifier un étudiant\n");
    printf("    6.  🗑️  Supprimer un étudiant\n");
    printf("    7.  🔤 Tri Alphabétique\n");
    printf("    8.  📂 Tri par Filière\n");
    printf("    9.  🏢 Tri par Département\n");
    printf("    10. 📄 Générer la liste des etudiants\n");
    printf("    11. 📊 Voir les statistiques de l'ecole\n");
    printf("    12. 🚪 Quitter le programme\n");
    printf("    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
}