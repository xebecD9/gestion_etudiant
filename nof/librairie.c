#include "librairie.h"

etudiant bairo[nombre_max_d_etudiant];
int nombre_etudiant = 0;
            /*FONCTIONS UTILITAIRES*/

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

            /* FONCTION DE GESTION DU FICHIER*/
//permet de sauvegarder un etudiant dans le fichier
void sauvegarder_dans_fichier(etudiant e) {
    FILE *f = fopen("etudiants.txt", "a"); 
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier !\n");
        return;
    }
    fprintf(f, "%s %s %s %d %d %d %s %s %c %s\n", 
            e.matricule, e.nom, e.prenom, 
            e.date_naissance.jour, e.date_naissance.mois, e.date_naissance.annee, 
            e.filiere, e.departement, e.sexe, e.region_origine);
    fclose(f);
}
//permet de charger les etudiants depuis le fichier au demarrage du programme
void charger_depuis_fichier() {
    FILE *f = fopen("etudiants.txt", "r");
    if (f == NULL) return;

    nombre_etudiant = 0;
    while (nombre_etudiant < nombre_max_d_etudiant && 
           fscanf(f, "%s %s %s %d %d %d %s %s %c %s", 
                  bairo[nombre_etudiant].matricule, 
                  bairo[nombre_etudiant].nom, 
                  bairo[nombre_etudiant].prenom, 
                  &bairo[nombre_etudiant].date_naissance.jour, 
                  &bairo[nombre_etudiant].date_naissance.mois, 
                  &bairo[nombre_etudiant].date_naissance.annee, 
                  bairo[nombre_etudiant].filiere, 
                  bairo[nombre_etudiant].departement, 
                  &bairo[nombre_etudiant].sexe, 
                  bairo[nombre_etudiant].region_origine) != EOF) {
        nombre_etudiant++;
    }
    fclose(f);
}

//permet de mettre a jour le fichier apres une suppression ou une modification 
void actualiser_fichier() {
    FILE *f = fopen("etudiants.txt", "w");
    if (f == NULL) return;
    for (int i = 0; i < nombre_etudiant; i++) {
        fprintf(f, "%s %s %s %d %d %d %s %s %c %s\n", 
                bairo[i].matricule, bairo[i].nom, bairo[i].prenom, 
                bairo[i].date_naissance.jour, bairo[i].date_naissance.mois, bairo[i].date_naissance.annee, 
                bairo[i].filiere, bairo[i].departement, bairo[i].sexe, bairo[i].region_origine);
    }
    fclose(f);
}

            /*FONCTIONS PRINCIPALES*/
void tri_filiere() {
    if (nombre_etudiant == 0) {
        printf("Aucun etudiant en memoire.\n");
        return;
    }

    etudiant tempo;
   
    for(int i = 0; i < nombre_etudiant - 1; i++) {
        for(int j = i + 1; j < nombre_etudiant; j++) {
            if(strcmp(bairo[i].filiere, bairo[j].filiere) > 0) {
                tempo = bairo[i];
                bairo[i] = bairo[j];
                bairo[j] = tempo;
            }
        }
    }

    printf("\nLISTE DES ETUDIANTS (ORDRE DE FILIERE)\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < nombre_etudiant; i++) {
        printf("%-10s %-12s %-12s %02d/%02d/%-4d %-10s %c\n", 
               bairo[i].matricule, bairo[i].nom, bairo[i].prenom,
               bairo[i].date_naissance.jour, bairo[i].date_naissance.mois, bairo[i].date_naissance.annee,
               bairo[i].filiere, bairo[i].sexe);
    }
}
void tri_alphabetique() {
    if (nombre_etudiant == 0) {
        printf("Aucun etudiant en memoire.\n");
        return;
    }

    etudiant tempo;
   
    for(int i = 0; i < nombre_etudiant - 1; i++) {
        for(int j = i + 1; j < nombre_etudiant; j++) {
            if(strcmp(bairo[i].nom, bairo[j].nom) > 0) {
                tempo = bairo[i];
                bairo[i] = bairo[j];
                bairo[j] = tempo;
            }
            else if(strcmp(bairo[i].nom, bairo[j].nom) == 0 && strcmp(bairo[i].prenom, bairo[j].prenom) > 0) {
                tempo = bairo[i];
                bairo[i] = bairo[j];
                bairo[j] = tempo;
            }
        }
    }

    printf("\nLISTE DES ETUDIANTS (ORDRE ALPHABETIQUE)\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < nombre_etudiant; i++) {
        printf("%-10s %-12s %-12s %02d/%02d/%-4d %-10s %c\n", 
               bairo[i].matricule, bairo[i].nom, bairo[i].prenom,
               bairo[i].date_naissance.jour, bairo[i].date_naissance.mois, bairo[i].date_naissance.annee,
               bairo[i].filiere, bairo[i].sexe);
    }
}
/* Fonction pour ajouter un etudiant */
void ajouter_un_etudiant() {
    if (nombre_etudiant >= nombre_max_d_etudiant) {
        printf("Limite atteinte.\n");
        return;
    }

    etudiant n;
    printf("\n--- AJOUT ETUDIANT ---\n");
    printf("Matricule : "); 
    fgets(n.matricule, size_max, stdin); 
    nettoyer_buffer_fgets(n.matricule);
    printf("Nom : "); 
    fgets(n.nom, size_max, stdin); 
    nettoyer_buffer_fgets(n.nom);
    printf("Prenom : "); 
    fgets(n.prenom, size_max, stdin); 
    nettoyer_buffer_fgets(n.prenom);
    printf("Departement : "); 
    fgets(n.departement, size_max, stdin); 
    nettoyer_buffer_fgets(n.departement);
    printf("Filiere : "); 
    fgets(n.filiere, size_max, stdin); 
    nettoyer_buffer_fgets(n.filiere);
    printf("Region : "); 
    fgets(n.region_origine, size_max, stdin); 
    nettoyer_buffer_fgets(n.region_origine);
    printf("Sexe (M/F) : "); 
    scanf(" %c", &n.sexe);
    printf("Date (JJ MM AAAA) : ");
    scanf("%d %d %d", &n.date_naissance.jour, &n.date_naissance.mois, &n.date_naissance.annee);
    vider_buffer();

    bairo[nombre_etudiant++] = n;
    sauvegarder_dans_fichier(n);
    printf("Etudiant ajouté avec succes !\n");
}
/* Fonction pour modifier les informations d'un etudiant */
void modifier_une_information_de_l_etudiant() {
    char matricule[size_max];
    int choix;
    int index_trouve = -1;

    printf("\n--- MODIFICATION DES INFORMATIONS D'UN ETUDIANT ---\n");
    printf("Entrer le matricule de l'etudiant dont vous souhaitez modifier les informations: ");
    fgets(matricule, size_max, stdin);
    nettoyer_buffer_fgets(matricule);  
    for(int i = 0; i < nombre_etudiant; i++) {
        if (strcmp(bairo[i].matricule, matricule) == 0) {
            index_trouve = i;
            break;
        }
    }

    if(index_trouve != -1) {
        printf("\nEtudiant  %s %s trouve\n", bairo[index_trouve].nom, bairo[index_trouve].prenom);
        printf("Quelle information voulez-vous modifier ?\n");
        printf("1. Nom\n2. Prenom\n3. Departement\n4. Filiere\n5. Region d'origine\n6. Sexe\n7. Date de naissance\n");
        printf("Entrer le numero de l'information que vous voulez modifier : ");
        scanf("%d", &choix);
        vider_buffer(); // Crucial après un scanf

        switch (choix) {
            case 1:
                printf("Nouveau Nom : ");
                fgets(bairo[index_trouve].nom, size_max, stdin);
                nettoyer_buffer_fgets(bairo[index_trouve].nom);
                break;
            case 2:
                printf("Nouveau Prenom : ");
                fgets(bairo[index_trouve].prenom, size_max, stdin);
                nettoyer_buffer_fgets(bairo[index_trouve].prenom);
                break;
            case 3:
                printf("Nouveau Departement : ");
                fgets(bairo[index_trouve].departement, size_max, stdin);
                nettoyer_buffer_fgets(bairo[index_trouve].departement);
                break;
            case 4:
                printf("Nouvelle Filiere : ");
                fgets(bairo[index_trouve].filiere, size_max, stdin);
                nettoyer_buffer_fgets(bairo[index_trouve].filiere);
                break;
            case 5:
                printf("Nouvelle Region : ");
                fgets(bairo[index_trouve].region_origine, size_max, stdin);
                nettoyer_buffer_fgets(bairo[index_trouve].region_origine);
                break;
            case 6:
                printf("Nouveau Sexe (M/F) : ");
                scanf(" %c", &bairo[index_trouve].sexe);
                vider_buffer();
                break;
            case 7:
                printf("Nouvelle Date (jj mm aaaa) : ");
                scanf("%d %d %d", &bairo[index_trouve].date_naissance.jour, 
                                  &bairo[index_trouve].date_naissance.mois, 
                                  &bairo[index_trouve].date_naissance.annee);
                vider_buffer();
                break;
            default:
                printf("Choix invalide.\n");
                return;
        }

    
        FILE *f = fopen("etudiants.txt", "w"); 
        if (f == NULL) {
            printf("Erreur d'ouverture du fichier pour sauvegarde.\n");
            return;
        }

        for (int i = 0; i < nombre_etudiant; i++) {
            
            fprintf(f, "%s %s %s %d %d %d %s %s %c %s\n", 
                    bairo[i].matricule, 
                    bairo[i].nom, 
                    bairo[i].prenom, 
                    bairo[i].date_naissance.jour, 
                    bairo[i].date_naissance.mois, 
                    bairo[i].date_naissance.annee, 
                    bairo[i].filiere, 
                    bairo[i].departement, 
                    bairo[i].sexe, 
                    bairo[i].region_origine);
        }
        fclose(f);
        printf("\n[Succes] Toutes les modifications ont ete enregistrees dans 'etudiants.txt'.\n");

    } else {    
        printf("\n[Erreur] Matricule '%s' introuvable dans la base actuelle.\n", matricule);
    }       
}
/*fonction de recherche par matricule*/
int recherche_par_matricule(char mat[], etudiant *res) {
    for (int i = 0; i < nombre_etudiant; i++) {
        if (strcmp(bairo[i].matricule, mat) == 0) {
            *res = bairo[i];
            return 1;
        }
    }
    return 0;
}
/* Fonction pour supprimer un etudiant */
void suppression_etudiant() {
    char mat[size_max];
    printf("Entrer le Matricule de l'etudiant a supprimer : ");
    fgets(mat, size_max, stdin);
    nettoyer_buffer_fgets(mat);

    int trouve = -1;
    for (int i = 0; i < nombre_etudiant; i++) {
        if (strcmp(bairo[i].matricule, mat) == 0) {
            trouve = i;
            break;
        }
    }

    if (trouve != -1) {
        for (int i = trouve; i < nombre_etudiant - 1; i++) {
            bairo[i] = bairo[i+1];
        }
        nombre_etudiant--;
        actualiser_fichier();
        printf("Suppression effectuee.\n");
    } else {
        printf("Etudiant non trouve.\n");
    }
}
/* Fonction pour calculer l'age d'un etudiant */
void calcul_age() {
    char mat[size_max];
    etudiant e;
    printf("Entrer le matricule de l'etudiant dont vous souhaitez calculer l'age : ");
    fgets(mat, size_max, stdin);
    nettoyer_buffer_fgets(mat);

    if (recherche_par_matricule(mat, &e)) {
        date d = extraction_date();
        int age = d.annee - e.date_naissance.annee;
        if (d.mois < e.date_naissance.mois || (d.mois == e.date_naissance.mois && d.jour < e.date_naissance.jour))
            age--;
        printf("L'etudiant a %d ans.\n", age);
    } else {
        printf("Introuvable.\n");
    }
}
/* Fonction pour afficher le menu principal */
void afficher_menu() {
    printf("\n=== SYSTEME DE GESTION DES ETUDIANTS DE L'ENSPM ===\n");
    printf("Voici un ensemble d'operations que vous pouvez effectuer :\n");
    printf("1. Ajouter un etudiant\n");
    printf("2. Rechercher un etudiant en utilisant son matricule\n");
    printf("3. Calculer Age d'un etudiant\n");
    printf("4. Modifier les informations d'un etudiant\n");
    printf("5. Supprimer un etudiant\n");
    printf("6. Tri Alphabetique des etudiants\n");
    printf("7. Tri par ordre de filiere des etudiants\n");
    printf("8. Quitter\n");
    printf("Entrer l'operation que vous souhaitez effectuer : ");
}
