/*
 -----------------------------------------------------------------------------------
 Nom du fichier : mainTest.h
 Auteur(s)      : Pascal Perrenoud, Pablo Urizar, Maëlle Vogel
 Date creation  : 22.04.2021

 Description    : programme de test de  la librairie

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "listes_dynamiques.h"

bool est_pair(size_t position, const Info *info) {
    return !(*info % 2);
}

int main() {

    printf("-----------TEST-INITIALISATION-INSERTION-AFFICHAGE-------------\n\n");
    Liste *ma_liste = initialiser();
    Info info = 0;

    // Doit afficher "La liste est vide !"
    if (estVide(ma_liste)) {
        printf("La liste est vide !\n");
    } else {
        printf("La liste contient %zu element(s)\n", longueur(ma_liste));
    }

    // Remplit la liste avec les valeurs [1 à 10]
    for (Info i = 1; i <= 10; ++i) {
        info = i;
        insererEnQueue(ma_liste, info);
    }

    // Doit afficher "Longueur : 10"
    printf("Longueur de la premiere liste : %zu\n", longueur(ma_liste));

    printf("premiere liste de tete a queue: ");
    // Doit afficher "[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]"
    afficher(ma_liste, FORWARD);

    printf("premiere liste de queue a tete: ");
    // Doit afficher "[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]"
    afficher(ma_liste, BACKWARD);

    printf("\n-----------TEST-SUPPRESSION-------------\n\n");


    // Supprime les valeurs paires
    supprimerSelonCritere(ma_liste, est_pair);

    printf("premiere liste apres suppression des nombres pairs: ");
    afficher(ma_liste, FORWARD);


    // Supprime un élément en tête de liste
    supprimerEnTete(ma_liste, info); // Supprime 1
    if (info != 1) {
        printf("Info aurait dû valoir 1 ! Et non pas %d\n", info);
    }

    // Supprime un élément en queue de liste
    supprimerEnQueue(ma_liste, info); // Supprime 9
    if (info != 9) {
        printf("Info aurait du valoir 9 ! Et non pas %d\n", info);
    }

    printf("premiere liste apres suppression de deux elements: ");
    afficher(ma_liste, FORWARD);

    // Insère un élément en tête de liste
    info = 0;
    insererEnTete(ma_liste, info);

    printf("premiere liste de queue a tete: ");
    // Doit afficher "[7, 5, 3, 0]"
    afficher(ma_liste, BACKWARD);

    // Doit afficher "Longueur : 4"
    printf("Longueur : %zu\n", longueur(ma_liste));

    printf("\n-----------TEST-EGAUX-------------\n\n");
    // Ajoute les nombres impairs jusqu'à 7 pour tester l'équalité des listes
    Liste *ma_deuxieme_liste = initialiser();
    info = 0;
    insererEnQueue(ma_deuxieme_liste, info);
    info = 3;
    insererEnQueue(ma_deuxieme_liste, info);
    info = 5;
    insererEnQueue(ma_deuxieme_liste, info);
    info = 7;
    insererEnQueue(ma_deuxieme_liste, info);

    printf("Est ce que les deux listes suivantes sont équales?\n");
    afficher(ma_liste, BACKWARD);
    afficher(ma_deuxieme_liste, FORWARD);
    // Doit afficher "Les deux listes sont egales"
    if (sontEgales(ma_liste, ma_deuxieme_liste)) {
        printf("Les deux listes sont egales\n");
        info = 9;
        insererEnTete(ma_deuxieme_liste, info);
    } else {
        printf("Les deux listes ne sont  pas egales\n");
    }

    printf("\nEst ce que les deux listes suivantes sont équales après l'ajout d'un nouveaux élèment?\n");
    if (sontEgales(ma_liste, ma_deuxieme_liste)) {
        printf("Les deux listes sont egales\n");
    } else {
        printf("Les deux listes ne sont  pas egales\n");
    }

    printf("\n-----------TEST-VIDER-------------\n\n");

    printf("deuxieme liste avant suppression: ");
    afficher(ma_deuxieme_liste, FORWARD);
    vider(ma_deuxieme_liste, 2);
    printf("deuxieme liste apres suppression partielle: ");
    afficher(ma_deuxieme_liste, FORWARD);

    vider(ma_liste, 0);
    vider(ma_deuxieme_liste, 0);

    printf("\n-------suppression complete--------\n");
    printf("les deux listes apres suppression complete: \n");

    // Doit afficher "[]"
    afficher(ma_liste, FORWARD);

    // Doit afficher "[]"
    afficher(ma_deuxieme_liste, FORWARD);

    free(ma_liste);
    free(ma_deuxieme_liste);

    printf("\n-----------FIN-TEST-------------");

    return 0;
}

//    Info* infoTest = 0;
//    supprimerEnTete(ma_liste, infoTest);

    /*
 * Output prévu :
 *
La liste est vide !
Longueur : 10
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
[7, 5, 3, 0]
Longueur : 4
Les deux listes sont egales
[0, 3, 5, 7]
[0, 3]
[]
[]
 *
 */
