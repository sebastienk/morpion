/**
 *  Grille.c
 *  
 *
 **/
#include <stdio.h>
#include <stdlib.h>

#include "grille.h"

char* values = "abcdefghij";

void ClearScreen()
{
	printf( "\n" );
}


grille generer_grille (char tab[][COLONNE])
{ 
	grille g;
	int m, n;
	for (m = 0; m < LIGNE; m++){
		for (n = 0; n < COLONNE; n++){
			tab[n][m] = '.';
	    }
	}
	g.nb_vide = 100;
	g.statut = VIDE;
	return g;
}

void afficher_grille (char tab[][COLONNE], int score1, int score2)
{
	int i,j;
	ClearScreen();
	printf(" joueur1 : %d   -   joueur2 : %d  \n", score1, score2);
	printf("\n");
	printf("_____________________________________________\n");
	printf("|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |\n");
	printf("|---|---|---|---|---|---|---|---|---|---|---|\n");
	for(i=0; i<COLONNE; i++){
		printf("|");
		for(j=0; j<LIGNE+1; j++){
			if(j == 0) 
			{
				printf(" %d |", i);
			} else {
				printf(" %c |", tab[j-1][i]);
			}
		}
		printf("\n");
		printf("|---|---|---|---|---|---|---|---|---|---|---|\n");
	}
	printf("|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |\n\n\n");
	
	return;
}

int verifier_grille()
{
   return 0;
}	

