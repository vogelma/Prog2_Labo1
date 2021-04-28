/*
 -----------------------------------------------------------------------------------
 Nom du fichier : mainTest.h
 Auteur(s)      : Pascal Perrenoud, Pablo Urizar, Maëlle Vogel
 Date creation  : 22.04.2021

 Description    : programme de test de  la librairie

 Remarque(s)    : Le programme a le fonctionnement attendu.

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/
#include "listes_dynamiques.h"
#include <stdlib.h>
#include <stdio.h>

bool est_pair(size_t position, const Info* info) {
    return (*info % 2 == 0);
}

int main() {

    printf("-----------TEST-INITIALISATION-INSERTION-AFFICHAGE-------------\n\n");
    Liste* ma_liste = initialiser();
    Info info = 0;

    if (estVide(ma_liste)) {
        printf("La liste est vide !\n");
    } else {
        printf("La liste contient %llu element(s)\n", longueur(ma_liste));
    }

    //Remplit la liste avec les valeurs [1 à 10]
    for (Info i = 1; i <= 10; ++i) {
        info = i;
        insererEnQueue(ma_liste, &info);
    }


    printf("Longueur de la premiere liste : %llu\n", longueur(ma_liste));

    printf("premiere liste de tete a queue: ");
    afficher(ma_liste, FORWARD);

    printf("premiere liste de queue a tete: ");
    afficher(ma_liste, BACKWARD);

    printf("\n-----------TEST-SUPPRESSION------------------------------------\n\n");


    //Supprime les valeurs paires
    supprimerSelonCritere(ma_liste, est_pair);

    printf("premiere liste apres suppression des nombres pairs: ");
    afficher(ma_liste, FORWARD);


    //Supprime un élément en tête de liste
    supprimerEnTete(ma_liste, &info); //Supprime 1
    if (info != 1) {
        printf("Info aurait du valoir 1 ! Et non pas %d\n", info);
    }

    //Supprime un élément en queue de liste
    supprimerEnQueue(ma_liste, &info); //Supprime 9
    if (info != 9) {
        printf("Info aurait du valoir 9 ! Et non pas %d\n", info);
    }

    printf("premiere liste apres suppression de deux elements: ");
    afficher(ma_liste, FORWARD);

    //Insère un élément en tête de liste
    info = 0;
    insererEnTete(ma_liste, &info);

    printf("premiere liste de queue a tete apres l'ajout d'un zero: ");
    afficher(ma_liste, BACKWARD);

    printf("Longueur : %llu\n", longueur(ma_liste));

    printf("\n-----------TEST-EGAUX------------------------------------------\n\n");
    //Ajoute les nombres impairs jusqu'à 7 pour tester l'équalité des listes
    Liste *ma_deuxieme_liste = initialiser();
    info = 0;
    insererEnQueue(ma_deuxieme_liste, &info);
    info = 3;
    insererEnQueue(ma_deuxieme_liste, &info);
    info = 5;
    insererEnQueue(ma_deuxieme_liste, &info);
    info = 7;
    insererEnQueue(ma_deuxieme_liste, &info);

    printf("Est ce que les deux listes suivantes sont equales?\n");
    afficher(ma_liste, FORWARD);
    afficher(ma_deuxieme_liste, FORWARD);

    if (sontEgales(ma_liste, ma_deuxieme_liste)) {
        printf("Les deux listes sont egales\n");
        info = 9;
        insererEnTete(ma_deuxieme_liste, &info);
    } else {
        printf("Les deux listes ne sont  pas egales\n");
    }

    printf("\nEst ce que les deux listes suivantes sont équales après l'ajout d'un nouvel element?\n");
    afficher(ma_liste, BACKWARD);
    afficher(ma_deuxieme_liste, BACKWARD);

    if (sontEgales(ma_liste, ma_deuxieme_liste)) {
        printf("Les deux listes sont egales\n");
    } else {
        printf("Les deux listes ne sont  pas egales\n");
    }

    printf("\n-----------TEST-VIDER------------------------------------------\n\n");

    printf("deuxieme liste avant suppression: ");
    afficher(ma_deuxieme_liste, FORWARD);

    vider(ma_deuxieme_liste, 2);
    printf("deuxieme liste apres suppression depuis la position 2: ");
    afficher(ma_deuxieme_liste, FORWARD);

    vider(ma_liste, 0);
    vider(ma_deuxieme_liste, 0);

    printf("\n-------suppression-complete------------------------------------\n");
    printf("les deux listes apres suppression complete: \n");

    afficher(ma_liste, FORWARD);

    afficher(ma_deuxieme_liste, FORWARD);

    free(ma_liste);
    free(ma_deuxieme_liste);

    printf("\n-----------FIN-TEST-------------------------------------------");

    return 0;
}

