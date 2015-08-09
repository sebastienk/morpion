#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#define LIGNE 10
#define COLONNE 10
#define JOUEUR1 'O'
#define JOUEUR2 'X'
#define VIDE '.'

typedef struct grille grille;
typedef struct sauve sauve;

struct sauve {
  char coups[50];
  char nom[10];
  char score[5];
  int mode;
  int temps;
} sov;

struct grille {
  char tab[LIGNE][COLONNE];
  char joueur1[26];
  char joueur2[26];
  char joueur[26];
  char score_joueur1[5];
  char score_joueur2[5];
  int nb_vide;
  char statut;
} g;

grille generer_grille (char tab[][COLONNE]);

void afficher_grille (char tab[][COLONNE], int score1, int score2);

int verifier_grille();

void ClearScreen (void);


#endif