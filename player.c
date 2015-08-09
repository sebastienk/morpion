/**
 *  Player.c
 *  
 *
 **/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "grille.h"
#include "player.h"


int saisie_donnee (char * invite) {
   int value;
	do {
      printf (" %s", invite);
	  value = getchar();
	  value -= '0';
   }while((value<0) || (value >9));
   return value;
}

int getComputerCoord(void)
{
	int nb;
	nb = rand() % 10;
	return nb;
}

int choseGameType(void)
{
	int value;
	printf("Choisissez votre mode de jeu\n");
	printf("_____________________________\n\n");
	printf("1.  Joueur contre Joueur.\n\n");
	printf("2.  Joueur contre Ordinateur.\n\n");
	printf("3.  Charger la partie sauvegardée.\n\n\n");
    do{
		value = getchar();
		value -= '0';
    }
	while((value > 3));
	return value;
}

/* ordinateur joue un coup */
struct Coup ordijouer(char tab[][COLONNE])
{
	int ligne, col;
	int correctAnswer = 0;
	do {
		ligne = getComputerCoord();
		col = getComputerCoord();
		if(tab[col][ligne] != '.')
			correctAnswer = 1;

	} while(correctAnswer == 1);
	struct Coup coup;
	coup.ligne = ligne;
	coup.colonne = col;
	/*strncpy(coup.player, "Computer", 8);*/
	printf("after set coup.ligne : %d\n ", coup.ligne);
	return coup;
}