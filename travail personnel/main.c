#include "librairie.h"

int main() {
    int choix;
    charger_donnees(); 
    
    do {
        afficher_menu();
        printf("Veuillez entrer le numero de l'operation que vous souhaitez effectuer:");
        if (scanf("%d", &choix) != 1) { 
            vider_buffer(); 
            continue; 
        }
        vider_buffer();

        switch(choix) {
            case 1: 
                printf("===AJOUT D'UN ETUDIANT===\n");
                ajouter_un_etudiant(); 
                break;
            case 2: {
                char mat1[size_max]; etudiant m;
                printf("===RECHERCHE PAR COMPARAISON DES MATRICULES===\n"); 
                printf("Veuillez le matricule de l'etudiant que vous rechercher : ");
                fgets(mat1, size_max, stdin); 
                nettoyer_buffer_fgets(mat1);
                if(recherche_par_matricule(mat1, &m)) printf("L'etudiant recherche s'appelle : %s %s\n", m.nom, m.prenom);
                else printf("[error]Aucun etudiant trouve.\n");
                break;
            }
            case 3:{
                char mat2[size_max]; etudiant d;
                printf("===RECHERCHE DICHOTOMIQUE===\n");
                printf("Veuillez le matricule de l'etudiant que vous rechercher : ");
                fgets(mat2, size_max, stdin); nettoyer_buffer_fgets(mat2);
                if(recherche_dichotomique(mat2, &d)) {
                printf("L'etudiant recherche s'appelle : %s %s\n", d.nom, d.prenom);
                printf("voici ces informations");
                }
                else {
                printf("[Error]Etudiant aucun etudiant trouve.\n");
                }
            break;
            }

            case 4: 
                printf("=== 🎂 CALCUL D'AGE  ===\n");
                calcul_age(); 
                break;
            case 5:
                printf("===  ⚙️MODIFICATION  ===\n");
                modifier_une_information_de_l_etudiant(); 
                break;
            case 6: 
                printf("===  SUPPRESSION  ===\n");
                suppression_etudiant(); 
                break;
            case 7: 
                printf("===  TRI ALPHABETIQUE  ===\n");
                tri_alphabetique(); 
                break;
            case 8: 
                printf("===  TRI PAR FILIERE  ===\n");
                tri_filiere(); 
                break;
            case 9:
                printf("===TRI PAR DEPARTEMENT===");
                tri_departement();
                break;    
            case 10: 
                printf("===AFFICHAGE DE LA LISTE DES ETUDIANTS===\n");
                affiche_liste_etudiant(); 
                break;
            
            case 11:
                printf("===STATISTIQUES DE L'ECOLE===\n");
                statistiques_ecole();
                break;
            case 12: 
                printf("Au revoir !\n"); 
                break;
        }
    } while (choix != 12);
    return 0;
}