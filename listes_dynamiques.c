/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      :
 Date creation  : 22.04.2021

 Description    :

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include "listes_dynamiques.h"

Liste *initialiser() { // Pascal
    Liste* liste = malloc(sizeof(Liste));

    liste->tete = NULL;
    liste->queue = NULL;

    return liste;
}

size_t longueur(const Liste *liste) { // Pascal
    // if (estVide(liste)) return 0;

    size_t longueur = 0;
    Element* suivant = liste->tete;

    while (suivant != NULL) {
        ++longueur;
        suivant = suivant->suivant;
    }

    return longueur;
}

void supprimerSelonCritere(Liste *liste, bool (*critere)(size_t, const Info *)) { // Pascal

}

// ------------------------------------------------------------------------------
// Renvoie true si liste est vide, false sinon.
bool estVide(const Liste* liste) {
    if(liste->tete == NULL)
        return true;
    else
        return false;
}
// ------------------------------------------------------------------------------
