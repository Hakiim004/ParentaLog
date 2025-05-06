#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure d'un nœud de l'arbre
typedef struct Noeud {
    char nom[50];
    char nom_parent1[50];
    char nom_parent2[50];
    struct Noeud* gauche;
    struct Noeud* droit;
} Noeud;

// Crée un nouveau nœud avec un nom donné et les noms de ses parents
Noeud* creer_noeud(const char* nom, const char* nom_parent1, const char* nom_parent2) {
    Noeud* nouveau_noeud = (Noeud*)malloc(sizeof(Noeud));
    strcpy(nouveau_noeud->nom, nom);
    strcpy(nouveau_noeud->nom_parent1, nom_parent1);
    strcpy(nouveau_noeud->nom_parent2, nom_parent2);
    nouveau_noeud->gauche = NULL;
    nouveau_noeud->droit = NULL;
    return nouveau_noeud;
}

// Insertion d'un nœud dans l'arbre
void inserer_noeud(Noeud** arbre, const char* nom, const char* nom_parent1, const char* nom_parent2) {
    if (*arbre == NULL) {
        *arbre = creer_noeud(nom, nom_parent1, nom_parent2);
    }
    else {
        printf("Impossible d'ajouter un nouveau nœud à un nœud existant.\n");
    }
}

// Affichage de l'arbre en ordre croissant (parcours infixé)
void afficher_arbre_infixe(Noeud* arbre) {
    if (arbre != NULL) {
        afficher_arbre_infixe(arbre->gauche);
        printf("Nom : %s, Nom du parent 1 : %s, Nom du parent 2 : %s\n", arbre->nom, arbre->nom_parent1, arbre->nom_parent2);
        afficher_arbre_infixe(arbre->droit);
    }
}

// Affichage de l'arbre en préfixé
void afficher_arbre_prefixe(Noeud* arbre) {
    if (arbre != NULL) {
        printf("Nom : %s, Nom du parent 1 : %s, Nom du parent 2 : %s\n", arbre->nom, arbre->nom_parent1, arbre->nom_parent2);
        afficher_arbre_prefixe(arbre->gauche);
        afficher_arbre_prefixe(arbre->droit);
    }
}

// Affichage de l'arbre en postfixé
void afficher_arbre_postfixe(Noeud* arbre) {
    if (arbre != NULL) {
        afficher_arbre_postfixe(arbre->gauche);
        afficher_arbre_postfixe(arbre->droit);
        printf("Nom : %s, Nom du parent 1 : %s, Nom du parent 2 : %s\n", arbre->nom, arbre->nom_parent1, arbre->nom_parent2);
    }
}

// Recherche d'un élément dans l'arbre
Noeud* rechercher_element(Noeud* arbre, const char* nom) {
    if (arbre == NULL) {
        return NULL;
    }
    if (strcmp(arbre->nom, nom) == 0) {
        return arbre;
    }
    Noeud* gauche = rechercher_element(arbre->gauche, nom);
    if (gauche != NULL) {
        return gauche;
    }
    Noeud* droit = rechercher_element(arbre->droit, nom);
    return droit;
}

// Calcul de la hauteur de l'arbre
int hauteur_arbre(Noeud* arbre) {
    if (arbre == NULL) {
        return 0;
    }
    int hauteur_gauche = hauteur_arbre(arbre->gauche);
    int hauteur_droit = hauteur_arbre(arbre->droit);
    return 1 + (hauteur_gauche > hauteur_droit ? hauteur_gauche : hauteur_droit);
}

// Parcours en largeur de l'arbre
void parcours_largeur_arbre(Noeud* arbre) {
    if (arbre == NULL) {
        return;
    }

    // File pour stocker les nœuds à traiter
    Noeud* file[100];
    int debut = 0;
    int fin = 0;

    // Ajouter le nœud racine à la file
    file[fin++] = arbre;

    while (debut < fin) {
        // Récupérer le nœud en tête de file
        Noeud* noeud = file[debut++];
        printf("Nom : %s, Nom du parent 1 : %s, Nom du parent 2 : %s\n", noeud->nom, noeud->nom_parent1, noeud->nom_parent2);

        // Ajouter les enfants du nœud à la file
        if (noeud->gauche != NULL) {
            file[fin++] = noeud->gauche;
        }
        if (noeud->droit != NULL) {
            file[fin++] = noeud->droit;
        }
    }
}

int main() {
    Noeud* arbre = NULL;
    char nom[50], nom_parent1[50], nom_parent2[50];
    char continuer;
    int choix;

    do {
        printf("\033[1;34m\n=================== Menu ===================\n");
        printf("1. Insert a node\n");
        printf("2. Display the tree in ascending order (in-order traversal)\n");
        printf("3. Display the tree in prefix order (pre-order traversal)\n");
        printf("4. Display the tree in postfix order (post-order traversal)\n");
        printf("5. Search for an element in the tree\n");
        printf("6. Calculate the height of the tree\n");
        printf("7. Traverse the tree in breadth-first order\n");
        printf("8. Exit\n");
        printf("============================================\n\033[0m");

        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
        case 1:
            printf("Entrez le nom du nouveau nœud : ");
            scanf("%s", nom);
            printf("Entrez le nom du parent 1 : ");
            scanf("%s", nom_parent1);
            printf("Entrez le nom du parent 2 : ");
            scanf("%s", nom_parent2);
            inserer_noeud(&arbre, nom, nom_parent1, nom_parent2);
            break;
        case 2:
            printf("\033[1;34m\nAffichage de l'arbre en ordre croissant (infixe) :\n\033[0m");
            afficher_arbre_infixe(arbre);
            break;
        case 3:
            printf("\033[1;34m\nAffichage de l'arbre en préfixé :\n\033[0m");
            afficher_arbre_prefixe(arbre);
            break;
        case 4:
            printf("\033[1;34m\nAffichage de l'arbre en postfixé :\n\033[0m");
            afficher_arbre_postfixe(arbre);
            break;
        case 5:
            printf("\033[1;34m\nRecherche d'un élément dans l'arbre :\n\033[0m");
            printf("Entrez le nom de l'élément à rechercher : ");
            scanf("%s", nom);
            Noeud* resultat = rechercher_element(arbre, nom);
            if (resultat != NULL) {
                printf("\033[1;32mElément trouvé - Nom : %s, Nom du parent 1 : %s, Nom du parent 2 : %s\n\033[0m", resultat->nom, resultat->nom_parent1, resultat->nom_parent2);
            }
            else {
                printf("\033[1;31mElément non trouvé dans l'arbre.\n\033[0m");
            }
            break;
        case 6:
            printf("\033[1;34m\nHauteur de l'arbre : %d\n\033[0m", hauteur_arbre(arbre));
            break;
        case 7:
            printf("\033[1;34m\nParcours en largeur de l'arbre :\n\033[0m");
            parcours_largeur_arbre(arbre);
            break;
        case 8:
            printf("\033[1;34m\nAu revoir !\n\033[0m");
            break;
        default:
            printf("\033[1;31m\nChoix invalide.\n\033[0m");
        }

        if (choix != 8) {
            printf("\n\033[1;34mVoulez-vous continuer (O/N) ? \033[0m");
            scanf(" %c", &continuer);
        }

    } while (choix != 8 && (continuer == 'O' || continuer == 'o'));

    return 0;
}

