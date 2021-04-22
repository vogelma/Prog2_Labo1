/*
 -----------------------------------------------------------------------------------
 Nom du fichier : mainTest.h
 Auteur(s)      :
 Date creation  : 22.04.2021

 Description    :

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "listes_dynamiques.h"

bool est_pair(size_t position, const Info * info) {
    return !(*info % 2);
}

int main() {
    Liste* ma_liste = initialiser();
    Info* info = malloc(sizeof(Info));

    // Doit afficher "La liste est vide !"
    if (estVide(ma_liste)) {
        printf("La liste est vide !\n");
    } else {
        printf("La liste contient %ld élément(s)\n", longueur(ma_liste));
    }

    // Remplit la liste avec les valeurs [1 à 10]
    for (Info i = 1;i <= 10;++i) {
        *info = i;
        insererEnQueue(ma_liste, info);
    }

    // Doit afficher "Longueur : 10"
    printf("Longueur : %ld\n", longueur(ma_liste));

    // Doit afficher "[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]"
    afficher(ma_liste, FORWARD);

    // Supprime les valeurs paires
    supprimerSelonCritere(ma_liste, est_pair);

    // Supprime un élément en tête de liste
    supprimerEnTete(ma_liste, info); // Supprime 1
    if (*info != 1) {
        printf("Info aurait dû valoir 1 ! Et non pas %d\n", *info);
    }

    // Supprime un élément en queue de liste
    supprimerEnQueue(ma_liste, info); // Supprime 9
    if (*info != 9) {
        printf("Info aurait du valoir 9 ! Et non pas %d\n", *info);
    }

    // Insère un élément en tête de liste
    *info = 0;
    insererEnTete(ma_liste, info);

    // Doit afficher "[7, 5, 3, 0]"
    afficher(ma_liste, BACKWARD);

    // Doit afficher "Longueur : 4"
    printf("Longueur : %ld\n", longueur(ma_liste));

    Liste* ma_deuxieme_liste = initialiser();
    *info = 0;
    insererEnQueue(ma_deuxieme_liste, info);
    *info = 3;
    insererEnQueue(ma_deuxieme_liste, info);
    *info = 5;
    insererEnQueue(ma_deuxieme_liste, info);
    *info = 7;
    insererEnQueue(ma_deuxieme_liste, info);

    // Doit afficher "Les deux listes sont egales"
    if (sontEgales(ma_liste, ma_deuxieme_liste)) {
        printf("Les deux listes sont egales\n");
    }

    vider(ma_liste, 0);
    vider(ma_deuxieme_liste, 0);
    // Doit afficher "[]"
    afficher(ma_liste, FORWARD);
    // Doit afficher "[]"
    afficher(ma_deuxieme_liste, FORWARD);

    free(ma_liste);
    free(ma_deuxieme_liste);
    free(info);


    return 0;
}
