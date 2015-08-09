/**
 *  Sauvegarde.c
 *  
 *
 **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "grille.h"
#include "sauvegarde.h"


void
writeData (Liste *liste, Game *game) {

	/* Open file or create it */
	FILE *wfile = fopen("fichier.bin", "wb");
	/* Init data container */
	Coup wtabcoup[liste->nbCoup];
	Game wtabgame[1];
	/* prepare Liste Coup data to be written */
	Coup *actuel = liste->premier;
	int i = 0;
	while (actuel != NULL)
	{
		printf("%s -> ", actuel->player);
		strcpy(wtabcoup[i].player, actuel->player);
		wtabcoup[i].ligne = actuel->ligne;
		wtabcoup[i].colonne = actuel->colonne;
		wtabcoup[i].suivant = actuel->suivant;
		actuel = actuel->suivant;
		i++;
	}
	/* prepare Game data to be written */
	strcpy(wtabgame[0].nomJoueur1, game->nomJoueur1);
	strcpy(wtabgame[0].nomJoueur2, game->nomJoueur2);
	wtabgame[0].mode = game->mode;
	wtabgame[0].scoreJoueur1 = game->scoreJoueur1;
	wtabgame[0].scoreJoueur2 = game->scoreJoueur2;
	wtabgame[0].temps = game->temps;

	/* Write file */
	if (wfile != NULL) {
		fwrite(wtabgame, sizeof(Game), 1, wfile);
		fwrite(wtabcoup, liste->nbCoup * sizeof(Coup), 2, wfile);
		fclose(wfile);
	} else {
		printf("fichier n''existe pas...");
	}
	printf("fin");
	readData();
}


void
readData() {
	FILE *rfile;
	Game rtab_game[1];
	Coup rtab_coup[2];

	rfile = fopen("fichier.bin", "rb");


	printf("file opened\n\n");
	fread(rtab_game, sizeof(Game), 1, rfile);
	fread(rtab_coup, sizeof(Coup), 2, rfile);

	printf("Game 1 - joueur1 : %s \n", rtab_game[0].nomJoueur1);
	printf("Game 1 - joueur2 : %s \n", rtab_game[0].nomJoueur2);
	printf("Game 1 - mode : %d \n", rtab_game[0].mode);
	printf("Game 1 - temps : %d \n", rtab_game[0].temps);
	printf("Game 1 - scoreJoueur1 : %d \n", rtab_game[0].scoreJoueur1);
	printf("Game 1 - scoreJoueur2 : %d \n", rtab_game[0].scoreJoueur2);

	printf("\n\n\n");

	printf("Coup 1 - nom : %s \n", rtab_coup[0].player);
	printf("Coup 1 - score : %d \n", rtab_coup[0].ligne);
	printf("Coup 1 - temps : %d \n", rtab_coup[0].colonne);
	printf("\n");
	printf("Coup 1 - nom : %s \n", rtab_coup[1].player);
	printf("Coup 1 - score : %d \n", rtab_coup[1].ligne);
	printf("Coup 1 - temps : %d \n", rtab_coup[1].colonne);

	fclose(rfile);

	char test = getchar();
	printf("test: %c ", test);
}

