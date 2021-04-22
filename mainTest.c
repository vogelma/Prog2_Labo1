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
#include "listes_dynamiques.h"

int main() {
    Liste* ma_liste = initialiser();

    printf("Longueur : %ld\n", longueur(ma_liste));

    return 0;
}
