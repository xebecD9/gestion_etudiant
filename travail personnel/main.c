#include "librairie.h"
#include <windows.h>

int main(){
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
int choix;
  do{  
    charger_donnees();
    effacer_ecran();
    afficher_menu_principal();
    printf("👉Veuillez entrer votre choix : ");
   if (scanf("%d", &choix) != 1) { 
        printf("\n⚠️  Erreur : Veuillez entrer un nombre valide.\n");
        vider_buffer(); // Nettoie les lettres saisies par erreur
        pause();        // Laisse le temps de lire le message d'erreur
        continue;     // Quitte le programme avec un code d'erreur
    }
    vider_buffer();

    switch(choix){
        case 1:
            effacer_ecran();
            ajouter_un_etudiant();
            pause();
            break;
        case 2:
            effacer_ecran();
            recherche();
            pause();
            break;
        case 3:
            effacer_ecran();
            calcul_age();
            pause();
            break;
        case 4:
            effacer_ecran();    
            modifier_etudiant();
            pause();
            break;
        case 5:
            effacer_ecran();
            suppression_etudiant();
            pause();
            break;
        case 6:
            effacer_ecran();
            tri();
            pause();
            break;
        case 7:
            effacer_ecran();    
            affiche_liste_etudiant();
            pause();
            break;
        case 8:
            effacer_ecran();
            statistiques_ecole();
               
            break;

        case 0:
            printf("Merci d'avoir utilisé le système de gestion ENSPM. Au revoir !\n");
            break;
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
            break;
    }
  }while(choix != 0);

    return 0;
}