#include "librairie.h"

int main() {
    charger_depuis_fichier();
    int choice;
    do {
        afficher_menu();
        if (scanf("%d", &choice) != 1) {
            vider_buffer();
            continue;
        }
        vider_buffer();

        switch (choice) {
            case 1: ajouter_un_etudiant(); 
            break;
            case 2: {
                char m[size_max]; 
                etudiant e;
                printf("Entrer le matricule de l'etudiant que vous souhaitez rechercher : "); 
                fgets(m, size_max, stdin); 
                nettoyer_buffer_fgets(m);
                if(recherche_par_matricule(m, &e)){ 
                printf("etudiant %s %s trouve.\n", e.nom, e.prenom);}
                else{
                    printf("Non trouve.\n");
                } 
                break;
            }
            case 3: 
            calcul_age(); 
            break;
            case 4: {
            etudiant e;
            modifier_une_information_de_l_etudiant();
            break;
            }
            case 5: 
            suppression_etudiant(); 
            break;
            case 6: 
            tri_alphabetique(); 
            break;
            case 7: 
            tri_filiere(); 
            break;
            case 8: 
            printf("Au revoir !\n"); 
            break;
            choice = 9;
            default:    
            printf("Choix invalide.\n");
            break;  

        }
    } while (choice != 9);
    return 0;
}