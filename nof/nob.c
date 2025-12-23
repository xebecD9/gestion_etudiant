#include "librairie.h"

// --- FONCTIONS UTILITAIRES ---

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void nettoyer_buffer_fgets(char *chaine) {
    chaine[strcspn(chaine, "\n")] = 0;
}
//fonction pour extraire la date actuelle
date extraction_date() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    date d;
    d.jour = tm->tm_mday;
    d.mois = tm->tm_mon + 1;
    d.annee = tm->tm_year + 1900;
    return d;
}
//fonction de sauvegarde dans le fichier
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

void parcour_fichier(){
FILE *file= fopen("etudiants.txt","w");
if (file==NULL){
    printf("aucun fichier trouve");
    return;
}

fclose(file);
}
// --- FONCTIONS DE GESTION DES ETUDIANTS ---

//fonction ajouter_un_etudiant
void ajouter_un_etudiant() {
    if (nombre_etudiant >= nombre_max_d_etudiant) {
        printf("Nombre maximum d'eleves atteint.\n");
        return;
    }

    etudiant nouveau;
    printf("\n******************************************\n");
    printf("Entrez les informations du nouvel etudiant\n");
    printf("******************************************\n");

    printf("Matricule : ");
    fgets(nouveau.matricule, size_max, stdin);
    nettoyer_buffer_fgets(nouveau.matricule);

    printf("Nom : ");
    fgets(nouveau.nom, size_max, stdin);
    nettoyer_buffer_fgets(nouveau.nom);

    printf("Prenom : ");
    fgets(nouveau.prenom, size_max, stdin);
    nettoyer_buffer_fgets(nouveau.prenom);

    printf("Departement : ");
    fgets(nouveau.departement, size_max, stdin);
    nettoyer_buffer_fgets(nouveau.departement);

    printf("Filiere : ");
    fgets(nouveau.filiere, size_max, stdin);
    nettoyer_buffer_fgets(nouveau.filiere);

    printf("Region d'origine : ");
    fgets(nouveau.region_origine, size_max, stdin);
    nettoyer_buffer_fgets(nouveau.region_origine);

    printf("Sexe (M/F) : ");
    scanf(" %c", &nouveau.sexe);
    vider_buffer();

    printf("\nDate de Naissance (jj/mm/aaaa) :\n");
    printf(" - Jour : "); 
    scanf("%d", &nouveau.date_naissance.jour);
    printf(" - Mois : "); 
    scanf("%d", &nouveau.date_naissance.mois);
    printf(" - Annee : "); 
    scanf("%d", &nouveau.date_naissance.annee);
    vider_buffer();

    // Enregistrement en mémoire (Tableau)
    bairo[nombre_etudiant] = nouveau;
    nombre_etudiant++;

    // Enregistrement sur disque (Fichier) pour la recherche
    sauvegarder_dans_fichier(nouveau);

    printf("\nL'etudiant %s %s (Matricule: %s) a ete ajoute avec succes.\n", 
           nouveau.prenom, nouveau.nom, nouveau.matricule);
}
//fonction de modification d'un etudiant
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
        printf("\nEtudiant trouve : %s %s\n", bairo[index_trouve].nom, bairo[index_trouve].prenom);
        printf("Quelle information voulez-vous modifier ?\n");
        printf("1. Nom\n2. Prenom\n3. Departement\n4. Filiere\n5. Region d'origine\n6. Sexe\n7. Date de naissance\n");
        printf("Votre choix : ");
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
void charger_depuis_fichier() {
    FILE *f = fopen("etudiants.txt", "r");
    if (f == NULL) return;

    nombre_etudiant = 0;
    while (fscanf(f, "%s %s %s %d %d %d %s %s %c %s", 
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
int recherche_par_matricule(char matricule_cherche[], etudiant *etu_trouve) {
    FILE *f = fopen("etudiants.txt", "r");
    if (f == NULL) return 0;

    while (fscanf(f, "%s %s %s %d %d %d %s %s %c %s", 
                  etu_trouve->matricule, etu_trouve->nom, etu_trouve->prenom, 
                  &etu_trouve->date_naissance.jour, &etu_trouve->date_naissance.mois, 
                  &etu_trouve->date_naissance.annee, etu_trouve->filiere, 
                  etu_trouve->departement, &etu_trouve->sexe, etu_trouve->region_origine) != EOF) {
        
        if (strcmp(etu_trouve->matricule, matricule_cherche) == 0) {
            fclose(f);
            
            printf("\n===============================================\n");
            printf("         FICHE D'ENREGISTREMENT DE L'ETUDIANT      \n");
            printf("=================================================\n");
            printf(" MATRICULE        : %s\n", etu_trouve->matricule);
            printf(" NOM COMPLET      : %s %s\n", etu_trouve->nom, etu_trouve->prenom);
            printf(" SEXE             : %c\n", etu_trouve->sexe);
            printf(" DATE DE NAISSANCE: %02d/%02d/%d\n", etu_trouve->date_naissance.jour, 
                                                     etu_trouve->date_naissance.mois, 
                                                     etu_trouve->date_naissance.annee);
            printf(" FILIERE          : %s\n", etu_trouve->filiere);
            printf(" DEPARTEMENT      : %s\n", etu_trouve->departement);
            printf(" ORIGINE          : %s\n", etu_trouve->region_origine);
            printf("=====================================================\n");
            return 1;
        }
    }
    fclose(f);
    return 0;
}
//fonction de suppression des informations d'un etudiant
void suppression_etudiant(){
FILE *f = fopen("etudiants.txt","r");
    FILE *t=fopen("t.txt","w");
    char matricule_saisi[size_max];
    char ligne[nombre_max_d_etudiant];
    if (f==NULL||t==NULL){
        printf("Erreur d'ouvertures fichier introuvables\n");
        return;
    }
    printf("Entrer le matricule de l'etudiant que vous souhaitez supprimez:");
    fgets(matricule_saisi,sizeof(matricule_saisi),stdin);
    matricule_saisi[strcspn(matricule_saisi,"\n")]=0;
    while(fgets(ligne,sizeof(ligne),f)){
        if(strncmp(ligne,matricule_saisi,strlen(matricule_saisi))!=0){
            fputs(ligne,t);
        }
    }
    fclose(f);
    fclose(t);
    remove("etudiants.txt");
    rename("t.txt","etudiants.txt");
    printf("la suppression est effective");


}
//fonction calcul_age
void calcul_age() {
    char mat_saisi[size_max];
    etudiant e;
    date d_jour;
    int age;

    printf("Entrer le matricule de l'etudiant pour le calcul de l'age : ");
    fgets(mat_saisi, size_max, stdin);
    nettoyer_buffer_fgets(mat_saisi);

    if (recherche_par_matricule(mat_saisi, &e)) {
        d_jour = extraction_date();
        age = d_jour.annee - e.date_naissance.annee;

        if (d_jour.mois < e.date_naissance.mois || 
           (d_jour.mois == e.date_naissance.mois && d_jour.jour < e.date_naissance.jour)) {
            age--;
        }
        printf(">>> L'age de l'etudiant est de : %d ans.\n", age);
    } else {
        printf("\n[!] Erreur : Matricule %s introuvable.\n", mat_saisi);
    }
}
//fonction affichage_menu
void afficher_menu() {
    printf("\n*************************************************************\n");
    printf(" BIENVENUE DANS LE SYSTEME DE GESTION DES ETUDIANTS DE L'ENSPM ");
    printf("\n**************************************************************\n");
    printf("voici un ensemble d'operation que vous pouvez effectuer dans notre systeme de gestion\n");
    printf("1.  Ajouter un etudiant\n");
    printf("2.  Rechercher un etudiant en utilisant son matricule\n");
    printf("3.  Calculer l'age d'un etudiant\n");
    printf("4.  Modifier les informations d'un etudiant\n ");
    printf("5.  Supprimer un etudiant\n");
    printf("6.  Quitter\n");
    
}
int main(){
    charger_depuis_fichier();
    int choice;
   do {
        afficher_menu();
        printf("\nVeuillez choisir l'operation que vous souhaitez effectuer : ");

        
        if (scanf("%d", &choice) != 1) {
            printf("\n[!] Entree invalide. Veuillez saisir un nombre !!\n");
            vider_buffer();
            choice = 0; 
            continue; 
        } else {
            vider_buffer(); 
        }
        
        switch (choice){
       
        case 1:
            ajouter_un_etudiant();
            break;
            
        case 2: 
            {
            
            char matricule_saisi[size_max];
            etudiant etu_temp; 
            printf("Entrez le matricule de l'etudiant a rechercher : ");
            
            fgets(matricule_saisi, size_max, stdin);
            nettoyer_buffer_fgets(matricule_saisi);

            
            if (recherche_par_matricule(matricule_saisi, &etu_temp)) {
            
            printf("\n[Succes] L'etudiant a ete trouve et voici sa fiche d'enregistrement ci-dessus.\n");
            } else {
            // Si la fonction a renvoyé 0
            printf("\n[Erreur] Aucun etudiant ne porte le matricule : %s\n", matricule_saisi);
            }
    
            break;
            }
            case 3:
            calcul_age();
            break;
            case 4:
            etudiant etudiant_s;
            modifier_une_information_de_l_etudiant();
            break;
            case 5:
            suppression_etudiant();
            break;
            case 6:
            printf("aurevoir");
            choice=7;
            break;
            default:

            printf("entrer invalide\n");

            }

    
            } while (choice != 7); 
   
    return 0;
        }   


