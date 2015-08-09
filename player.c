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
      printf ("%s", invite);
	  value = getchar();
	  printf("value %c ", value);
	  value -= '0';
     /* scanf ("%d",&valeur);*/
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
void ordijouer(char tab[LIGNE][COLONNE], struct Coup coup)
{
	int ligne, col;
	int correctAnswer = 0;
	do {
		ligne = getComputerCoord();
		col = getComputerCoord();
		if(tab[col][ligne] != '.')
			correctAnswer = 1;
	} while(correctAnswer == 1);
	coup.ligne = ligne;
	coup.colonne = col;
	strncpy(coup.player, "Computer", PLAYER_NAME_SIZE);
	/*return coup;*/
}