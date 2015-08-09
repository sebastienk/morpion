//
// Created by sebastienk on 8/9/2015.
//
#ifndef __GAME_H_ /* include guard */
#define __GAME_H_
typedef struct Coup Coup;
struct Coup
{
    char player[26];
    int ligne;
    int colonne;
    Coup *suivant;
};

typedef struct Game Game;
struct Game
{
    int mode;
    int scoreJoueur1;
    int scoreJoueur2;
    int temps;
    char nomJoueur1[26];
    char nomJoueur2[26];
} ;

typedef struct Liste Liste;
struct Liste {
    int nbCoup;
    Coup *premier;
};

Liste *initialisation();
void insertion(Liste *liste, Coup *coup);
void afficherListe(Liste *liste);
#endif /* __GAME_H_ */