#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

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

void afficher_grille (char tab[][COLONNE], int score1, int score2);

int verifier_grille();

void ClearScreen (void);


#endif