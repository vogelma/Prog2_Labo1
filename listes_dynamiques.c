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

#include <stdlib.h>
#include <stdio.h>
#include "listes_dynamiques.h"

//true si vide, false si pas la même taille
bool sontEgales(const Liste* liste1, const Liste* liste2) {
    if (estVide(liste1) && estVide(liste2))
        return true;
    if (longueur(liste1) != longueur(liste2))
        return false;

    Element* suivant1 = liste1->tete;
    Element* suivant2 = liste2->tete;

    while (suivant1 != NULL) {
        if (suivant1->info != suivant2->info)
            return false;
        suivant1 = suivant1->suivant;
        suivant2 = suivant2->suivant;
    }

    return true;
}

Status insererEnTete(Liste* liste, const Info *info) {

    Element* newElement = malloc(sizeof(Element));
    if(newElement == NULL)
        return MEMOIRE_INSUFFISANTE;

    //ajout des attribut de l'élèment
    newElement->info = info;
    newElement->precedent = NULL;


    //si un élèment est déjà dans la liste
    if(!estVide(liste)) {
        newElement->suivant = liste->tete;
        liste->tete->precedent = newElement;
    }
    else {
        newElement->suivant = NULL;
        liste->queue = newElement;
    }
    //maj de la tete de la liste
    liste->tete = newElement;

    return OK;
}

Status insererEnQueue(Liste* liste, const Info *info) {

    Element* newElement = malloc(sizeof(Element));
    if(!newElement)
        return MEMOIRE_INSUFFISANTE;

    //ajout des attribut de l'élèment
    newElement->info = info;
    newElement->precedent = liste->queue;
    newElement->suivant = NULL;

    //si un élèment est déjà dans la liste
    if(!estVide(liste)) {
        newElement->precedent = liste->queue;
        liste->queue->suivant = newElement;
    }
    else {
        newElement->precedent = NULL;
        liste->tete = newElement;

    }
    //maj de la queue de la liste
    liste->queue = newElement;

    return OK;

}

void vider(Liste* liste, size_t position) {

    //rien est fait si la position se trouve après la fin de la liste
    if(position < longueur(liste)) {

        Info tmp = 0;
        //supprime la queue jusqu'à atteindre la position
        for(size_t i = longueur(liste); i > position ; --i){
            supprimerEnQueue(liste, &tmp);
        }
    }

}

Liste* initialiser() {
    Liste *liste = malloc(sizeof(Liste));

    liste->tete = NULL;
    liste->queue = NULL;

    return liste;
}

size_t longueur(const Liste *liste) {
    if (estVide(liste)) return 0;

    size_t longueur = 0;
    Element* suivant = liste->tete;

    //incrémente tant qu'il y a un suivant
    while (suivant != NULL) {
        ++longueur;
        suivant = suivant->suivant;
    }

    return longueur;
}

void supprimerSelonCritere(Liste *liste, bool (*critere)(size_t, const Info* )) {
    if (!estVide(liste)) {

        size_t position = 0;
        Element* precedent = NULL;
        Element* element = liste->tete;
        Element* suivant = NULL;

        while (element != NULL) {
            precedent = element->precedent;
            suivant = element->suivant;
            if (critere(position, &(element->info))) {
                if (precedent != NULL) {
                    precedent->suivant = suivant;
                }
                if (suivant != NULL) {
                    suivant->precedent = precedent;
                }
                //si la tete ou la queue est supprimée il faut mettre à jour la liste
                if (element == liste->queue){
                    liste->queue = precedent;
                }
                if (element == liste->tete){
                    liste->tete = suivant;
                }

                free(element);
            }
            element = suivant;
            ++position;
        }
    }
}

bool estVide(const Liste *liste) {
    return (!(liste->tete));

}

void afficher(const Liste* liste, Mode mode) {
    Element* elemActuel;

    printf("[");
    if (!estVide(liste)) {
        if (mode == FORWARD) {
            elemActuel = liste->tete;
            while (elemActuel != NULL) {
                printf("%d", elemActuel->info);
                if (elemActuel != liste->queue)
                    printf(", ");
                elemActuel = elemActuel->suivant;
            }
        } else if (mode == BACKWARD) {
            elemActuel = liste->queue;
            while (elemActuel != NULL) {
                printf("%d", elemActuel->info);
                if (elemActuel != liste->tete)
                    printf(", ");
                elemActuel = elemActuel->precedent;
            }
        }
    }
    printf("]\n");
}

Status supprimerEnTete(Liste* liste, Info* info) {
    if (estVide(liste))
        return LISTE_VIDE;

    // Renvoie de l'élément stocké en tête
    *info = liste->tete->info;


    Element* tmp =  liste->tete;
    if (longueur(liste) != 1) {
        liste->tete = liste->tete->suivant;
        liste->tete->precedent = NULL;
    } else {
        // on vient de supprimer le dernier élèment
        liste->tete = NULL;
        liste->queue = NULL;
    }

    free(tmp);

    return OK;
}

Status supprimerEnQueue(Liste* liste, Info* info) {
    if (estVide(liste))
        return LISTE_VIDE;

    // Renvoie de l'élément stocké en queue
    *info = liste->queue->info;

    Element* tmp =  liste->queue;

    if (longueur(liste) != 1) {
        liste->queue = liste->queue->precedent;
        liste->queue->suivant = NULL;
    } else {
        liste->tete = NULL;
        liste->queue = NULL;
    }

    free(tmp);

    return OK;
}