/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      : Pascal Perrenoud, Pablo Urizar, Maëlle Vogel
 Date creation  : 22.04.2021

 Description    : implémentation de la librairie permettant la gestion de
                  listes doublement chaînées non circulaires

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include <stdlib.h>
#include <stdio.h>

Liste *initialiser() {
    Liste* liste = malloc(sizeof(Liste));

    liste->tete = NULL;
    liste->queue = NULL;

    return liste;
}

bool estVide(const Liste *liste) {
    return (liste->tete == NULL);
}

size_t longueur(const Liste *liste) {
    size_t taille = 0;

    Element* element = liste->tete;

    while (element) {
        element = element->suivant;
        ++taille;
    }

    return taille;
}

Status insererEnQueue(Liste *liste, const Info *info) { // TODO : 0 ou 1 élément + 1 ?
    Element* element = malloc(sizeof(Element));
    if (!element) return MEMOIRE_INSUFFISANTE;

    element->info = *info;
    element->suivant = NULL;

    if (estVide(liste)) {
        liste->tete = element;
        liste->queue = element;
        element->precedent = NULL;
    } else {
        element->precedent = liste->queue;
        liste->queue->suivant = element;
        liste->queue = element;
    }

    return OK;
}

void afficher(const Liste *liste, Mode mode) {
    Element* element;

    if (mode == FORWARD) {
        element = liste->tete;
    } else {
        element = liste->queue;
    }

    printf("[");

    while(element) {
        printf("%d", element->info);

        if (mode == FORWARD) {
            element = element->suivant;
        } else {
            element = element->precedent;
        }

        if (element) {
            printf(", ");
        }
    }

    printf("]\n");
}

void supprimerSelonCritere(Liste *liste, bool (*critere)(size_t, const Info *)) { // TODO : Vérifier comportement quand on passe de 2 à 1 et 1 à 0
    if (estVide(liste)) return;

    size_t pos = 0;
    Element* element = liste->tete;

    while(element) {
        if(critere(pos, &(element->info))) {
            if (element->precedent) {
                element->precedent->suivant = element->suivant;
            } else {
                liste->tete = liste->tete->suivant;
            }

            if (element->suivant) {
                element->suivant->precedent = element->precedent;
            } else {
                liste->queue = liste->queue->precedent;
            }

            Element* a_suppr = element;
            element = element->suivant;
            free(a_suppr);
        } else {
            element = element->suivant;
        }
    }
}

Status supprimerEnTete(Liste *liste, Info *info) { // TODO : Vérifier comportement quand on passe de 2 à 1 et 1 à 0
    if (estVide(liste)) return LISTE_VIDE;

    *info = liste->tete->info;

    if (liste->tete->suivant == NULL) {
        free(liste->tete);
    } else {
        liste->tete->suivant->precedent = NULL;
        Element* a_suppr = liste->tete;
        liste->tete = liste->tete->suivant;
        free(a_suppr);
    }

    return OK;
}

Status supprimerEnQueue(Liste *liste, Info *info) { // TODO : Vérifier comportement quand on passe de 2 à 1 et 1 à 0
    if (estVide(liste)) return LISTE_VIDE;

    *info = liste->queue->info;

    if (liste->queue->precedent == NULL) {
        free(liste->queue);
    } else {
        liste->queue->precedent->suivant = NULL;
        Element* a_suppr = liste->queue;
        liste->queue = liste->queue->precedent;
        free(a_suppr);
    }

    return OK;
}

Status insererEnTete(Liste *liste, const Info *info) { // TODO : Comportement quand 0 ou 1 élément correct ?
    Element* nouveau = malloc(sizeof(Element));

    if (nouveau == NULL) {
        return MEMOIRE_INSUFFISANTE;
    }

    nouveau->info = *info;
    nouveau->precedent = NULL;
    nouveau->suivant = NULL;

    if (estVide(liste)) {
        liste->queue = nouveau;
    } else {
        liste->tete->precedent = nouveau;
        nouveau->suivant = liste->tete;
    }

    liste->tete = nouveau;

    return OK;
}

bool sontEgales(const Liste *liste1, const Liste *liste2) {
    Element* elem1 = liste1->tete;
    Element* elem2 = liste2->tete;

    while (elem1) {
        if (!elem2) return false;
        if (elem1->info != elem2->info) return false;
        elem1 = elem1->suivant;
        elem2 = elem2->suivant;
    }

    return true;
}

void vider(Liste *liste, size_t position) { // TODO : Check extensif du comportement
    if (estVide(liste)) return;

    size_t pos = 0;
    Element* element = liste->tete;

    while (element && pos < position) {
        element = element->suivant;
        ++pos;
    }

    if (!element) return; // Empêche de supprimer après la fin

    if (liste->tete == element) { // Si on vide la liste
        liste->tete = NULL;
        liste->queue = NULL;
    } else {
        liste->queue = element->precedent;
        liste->queue->suivant = NULL;
    }


    Element* a_supprimer;
    while (element) {
        a_supprimer = element;
        element = element->suivant;
        free(a_supprimer);
    }
}
