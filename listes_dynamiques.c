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

Liste* initialiser() {
    Liste* liste = malloc(sizeof(Liste));

    liste->tete = NULL;
    liste->queue = NULL;

    return liste;
}

bool estVide(const Liste* liste) {
    return (!(liste->tete));
}

size_t longueur(const Liste* liste) {
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

void afficher(const Liste* liste, Mode mode) {
    Element* element;

    printf("[");

    if (!estVide(liste)) {
        if (mode == FORWARD) {
            element = liste->tete;
        } else {
            element = liste->queue;
        }

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
    }
    printf("]\n");
}

Status insererEnTete(Liste* liste, const Info* info) {
    Element* element = malloc(sizeof(Element));
    if(!element) return MEMOIRE_INSUFFISANTE;

    //ajout des attributs de l'élément
    element->info = *info;
    element->precedent = NULL;

    //si un élément est déjà dans la liste
    if(!estVide(liste)) {
        element->suivant = liste->tete;
        liste->tete->precedent = element;
    } else {
        element->suivant = NULL;
        liste->queue = element;
    }
    //maj de la tête de la liste
    liste->tete = element;

    return OK;
}

Status insererEnQueue(Liste* liste, const Info* info) {
    Element* element = malloc(sizeof(Element));
    if(!element) return MEMOIRE_INSUFFISANTE;

    //ajout des attributs de l'élément
    element->info = *info;
    element->suivant = NULL;

    //si un élément est déjà dans la liste
    if(!estVide(liste)) {
        element->precedent = liste->queue;
        liste->queue->suivant = element;
    } else {
        element->precedent = NULL;
        liste->tete = element;
    }
    //mise à jour de la queue de la liste
    liste->queue = element;

    return OK;
}

Status supprimerEnTete(Liste* liste, Info* info) {
    if (estVide(liste)) return LISTE_VIDE;

    //renvoie de l'élément stocké en tête
    *info = liste->tete->info;
    Element* tmp =  liste->tete;

    //mise à jour de la tête
    if (longueur(liste) != 1) {
        liste->tete = liste->tete->suivant;
        liste->tete->precedent = NULL;
    } else {
        //on vient de supprimer le dernier élément
        //donc la liste est vide
        liste->tete = NULL;
        liste->queue = NULL;
    }

    free(tmp);
    return OK;
}

Status supprimerEnQueue(Liste* liste, Info* info) {
    if (estVide(liste)) return LISTE_VIDE;

    //renvoie de l'élément stocké en queue
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

void supprimerSelonCritere(Liste* liste, bool (*critere)(size_t, const Info* )) {
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
                //si la tête ou la queue est supprimée il faut mettre à jour la liste
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

void vider(Liste* liste, size_t position) {
    //rien n'est fait si la position se trouve après la fin de la liste
    if(position < longueur(liste)) {

        Info tmp = 0;
        //supprime la queue jusqu'à atteindre la position
        for(size_t i = longueur(liste); i > position ; --i){
            supprimerEnQueue(liste, &tmp);
        }
    }
}


bool sontEgales(const Liste* liste1, const Liste* liste2) {
    //true si vide, false si pas de la même taille
    if (estVide(liste1) && estVide(liste2)) return true;
    if (longueur(liste1) != longueur(liste2)) return false;

    Element* elem1 = liste1->tete;
    Element* elem2 = liste2->tete;

    while (elem1 != NULL) {
        if (elem1->info != elem2->info) return false;
        elem1 = elem1->suivant;
        elem2 = elem2->suivant;
    }
    return true;
}