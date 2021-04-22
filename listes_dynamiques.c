/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      :
 Date creation  : 22.04.2021

 Description    : Librairie permettant la gestion de listes doublement chaînées
                  non circulaires

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include "listes_dynamiques.h"

//true si vide, false si pas la même taille
bool sontEgales(const Liste *liste1, const Liste *liste2) {
    if (estVide(liste1) && estVide(liste2))
        return true;
    if (longueur(liste1) != longueur(liste2))
        return false;

    Element *suivant1 = liste1->tete;
    Element *suivant2 = liste2->tete;

    while (suivant1 != NULL) {
        if (suivant1->info != suivant2->info)
            return false;
        suivant1 = suivant1->suivant;
        suivant2 = suivant2->suivant;
    }

    return true;
}

Status insererEnTete(Liste *liste, const Info *info) {

    Element* newElement = malloc(sizeof(Element));
    if(newElement == NULL)
        return MEMOIRE_INSUFFISANTE;

    //stocke le dernier élèment de la liste
    Element *premier = liste->tete;
    //pointe sur le nouveau élèment
    liste->tete->precedent = newElement;
    liste->tete = newElement;
    liste->tete->info = info;

    //fait le lien avec le dernier élèment
    liste->tete->suivant = premier;

    return OK;
}

Status insererEnQueue(Liste *liste, const Info *info) {

    Element* newElement = malloc(sizeof(Element));
    if(newElement == NULL)
        return MEMOIRE_INSUFFISANTE;

    //stocke le dernier élèment de la liste
    Element *dernier = liste->queue;
    //pointe sur le nouveau élèment
    liste->queue->suivant = newElement;
    liste->queue = newElement;
    liste->queue->info = info;

    //fait le lien avec le dernier élèment
    liste->queue->precedent = dernier;

    return OK;

}

void vider(Liste *liste, size_t position) {

    if(position < longueur(liste)) {
        Element *suivant = liste->tete;

        if (position != 0) {
            for (size_t i = 0; i > position - 1; ++i) {
                suivant = suivant->suivant;
            }
            //efface le pointeur sur le prochain élèment qui sera effacé plus tard
            suivant->suivant = NULL;
            //update la queue de la liste
            liste->queue = suivant;
            //premier élèment à supprimer
            suivant = suivant->suivant;
        }


        while (suivant != NULL) {
            suivant = suivant->suivant;
            free(suivant->precedent);
        }
    }

}


Liste* initialiser() { // Pascal
    Liste *liste = malloc(sizeof(Liste));

    liste->tete = NULL;
    liste->queue = NULL;

    return liste;
}

size_t longueur(const Liste *liste) {
    if (estVide(liste)) return 0;

    size_t longueur = 0;
    Element* suivant = liste->tete;

    while (suivant != NULL) {
        ++longueur;
        suivant = suivant->suivant;
    }

    return longueur;
}

void supprimerSelonCritere(Liste *liste, bool (*critere)(size_t, const Info *)) {
    if (estVide(liste)) return;

    size_t position = 0;
    Element* precedent = NULL;
    Element* element = liste->tete;
    Element* suivant = NULL;

    while (element != NULL) {
        precedent = element->precedent;
        suivant = element->suivant;
        if (critere(position, &(element->info))) {
            free(element);
            if (precedent != NULL) {
                precedent->suivant = suivant;
            }
            if (suivant != NULL) {
                suivant->precedent = precedent;
            }
        }
        element = suivant;
        ++position;
    }
}


// Renvoie true si liste est vide, false sinon.
bool estVide(const Liste *liste) {
    return (liste->tete == NULL);

}

