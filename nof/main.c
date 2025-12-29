#include "librairie.h"

int main() {
    int choix;
    charger_donnees(); // Charger les données du fichier au lancement
    
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
                ajouter_un_etudiant(); 
                break;
            case 2: {
                char mat1[size_max]; etudiant m;
                printf("Veuillez le matricule de l'etudiant que vous rechercher : ");
                fgets(mat1, size_max, stdin); 
                nettoyer_buffer_fgets(mat1);
                if(recherche_par_matricule(mat1, &m)) printf("Trouve : %s %s\n", m.nom, m.prenom);
                else printf("[error]Aucun etudiant trouve.\n");
                break;
            }
            case 3:{
                char mat2[size_max]; etudiant d;
                printf("Veuillez le matricule de l'etudiant que vous rechercher : ");
                fgets(mat2, size_max, stdin); nettoyer_buffer_fgets(mat2);
                if(recherche_dichotomique(mat2, &d)) printf("Trouve : %s %s\n", d.nom, d.prenom);
                else printf("[Error]Etudiant aucun etudiant trouve.\n");
            }
            case 4: 
                calcul_age(); 
                break;
            case 5:
                modifier_une_information_de_l_etudiant(); 
                break;
            case 6: 
                suppression_etudiant(); 
                break;
            case 7: 
                tri_alphabetique(); 
                break;
            case 8: 
                tri_filiere(); 
                break;
                
            case 9: 
                affiche_liste_etudiant(); 
                break;
            case 10: 
                printf("Au revoir !\n"); 
                break;
        }
    } while (choix != 10);
    return 0;
}