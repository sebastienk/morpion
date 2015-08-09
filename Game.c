//
// Created by sebastienk on 8/9/2015.
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Game.h"

Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Coup *tour = malloc(sizeof(*tour));
    if (liste == NULL || tour == NULL)
    {
        exit(EXIT_FAILURE);
    }
    liste->nbCoup = 0;
    tour->suivant = NULL;
    liste->premier = tour;
    return liste;
}

void insertion(Liste *liste, Coup *coup)
{
    /* Création du nouvel élément */
    Coup *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    strncpy(nouveau->player, coup->player, sizeof (nouveau->player));
    nouveau->ligne = coup->ligne;
    nouveau->colonne = coup->colonne;

    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}