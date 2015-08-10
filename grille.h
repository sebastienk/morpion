#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "Game.h"

#define LIGNE 10
#define COLONNE 10
#define JOUEUR1 'O'
#define JOUEUR2 'X'
#define VIDE '.'

typedef struct grille grille;
struct grille {
  char tab[LIGNE][COLONNE];
  int nb_vide;
  char statut;
} g;


grille generer_grille ();

void afficher_grille (char tab[][COLONNE], Game *g);

int verifier_grille(char tab[][COLONNE],char c);

void ClearScreen (void);

int combienHorizontalChar(char tab[][COLONNE], int index, char c);

int combienVertitalChar(char tab[][COLONNE], int index, char c);

int combienDiagonalGaucheHautChar(char tab[][COLONNE], int index, char c);

int combienDiagonalGaucheBasChar(char tab[][COLONNE], int index, char c);

#endif