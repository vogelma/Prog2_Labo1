/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      : Pascal Perrenoud, Pablo Urizar, Maëlle Vogel
 Date creation  : 22.04.2021

 Description    : implémentation de l'librairie permettant la gestion de
                  listes doublement chaînées non circulaires

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>
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

    //ajout des attribut de l'élèment
    newElement->info = info;
    newElement->precedent = NULL;


    //si un élèment est déjà dans la liste
    if(!estVide(liste)) {
        newElement->suivant = liste->tete;
        liste->tete->precedent = newElement;
    }
    else{
        newElement->suivant = NULL;
        liste->queue = newElement;
    }
    //maj de la tete de la liste
    liste->tete = newElement;

    return OK;
}

Status insererEnQueue(Liste *liste, const Info *info) {

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

void vider(Liste *liste, size_t position) {

    //rien est fait si la position se trouve après la fin de la liste
    if(position < longueur(liste)) {
        Element *suivant = liste->tete;

        //avance sur la bonne position
        if (position != 0) {
            for (size_t i = 0; i < position - 1; ++i) {
                suivant = suivant->suivant;
            }

            //variable temporel qui stocke le dernier élèment de la liste
            Element *tmp = suivant;

            //premier élèment à supprimer
            suivant = suivant->suivant;
            //efface le pointeur sur le prochain élèment qui sera effacé plus tard
            tmp->suivant = NULL;
            //update la queue de la liste
            liste->queue = tmp;

        }

        while (suivant != NULL) {
            Element *tmp = suivant;
            suivant = suivant->suivant;
            free(tmp);
        }

        if(position == 0){
            liste->tete = NULL;
            liste->queue = NULL;
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

bool estVide(const Liste *liste) {
    return (liste->tete == NULL);

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

    // Renvoie de l'élément stocké à l'en-tête
    *info = liste->tete->info;

    // Plusieurs éléments
    /*
    if (liste->tete) {
        liste->tete = NULL;
        liste->queue = NULL;
    } else
        liste->queue = NULL;
    */

    if (longueur(liste) != 1) {
        liste->tete = liste->tete->suivant;
        liste->tete->precedent = NULL;
    } else {
        // Un seul élément
        liste->tete = NULL;
        liste->queue = NULL;
    }

    free(liste->tete);

    return OK;
}

Status supprimerEnQueue(Liste* liste, Info* info) {
    if (estVide(liste))
        return LISTE_VIDE;

    // Renvoie de l'élément stocké à l'en-queue
    *info = liste->queue->info;

    // Plusieurs éléments
    /*
    if (liste->queue) {
        liste->tete = NULL;
        liste->queue = NULL;
    } else
        liste->tete = NULL;
    */

    if (longueur(liste) != 1) {
        liste->queue = liste->queue->precedent;
        liste->queue->suivant = NULL;
    } else {
        // Un seul élément
        liste->tete = NULL;
        liste->queue = NULL;
    }

    free(liste->queue);

    return OK;
}