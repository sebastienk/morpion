#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <inttypes.h>
#include "grille.h"
#include "sauvegarde.h"
#include "player.h"

#define LIGNE 10
#define COLONNE 10
#define MATCH_NUL 'N'
#define MATCH_END 'E'

#define YES 1
#define NO 0

#define MULTI 1
#define SOLO 2
#define LOAD 3
#define EXIT 4

Game *game;
grille g;
Liste *liste;
time_t debut, fin;

char joueur[26];
char tab[LIGNE][COLONNE];
int tour, count = 0;
int last = 0;
int duree;
int isGameReloaded = NO;

void exitGame(void)
{
	printf("REAL EXIT FUNCTION");
}

void loadGame(void)
{
	isGameReloaded = YES;
	readData();
}

/* Choisir le mode de jeu MULTI pour deux humains et SOLO pour humain contre ordinateur */
void menuJeu(void)
{
	game = malloc(sizeof(*game));
	game->mode = choseGameType();
	game->scoreJoueur1 = 0;
	game->scoreJoueur2 = 0;
	printf("tmp = %d\n", game->mode);
	switch(game->mode)
	{
		case 1:
			game->mode = MULTI;
			break;
		case 2:
			game->mode = SOLO;
			break;
		case 3:
			game->mode = LOAD;
			loadGame();
			break;
		case 4:
			exitGame();
			break;
	}
}

/* Choisir le nom des joeurs */
void menuJoueur(void)
{
	char joueur1[26];
	char joueur2[26];
	printf("Entrer le nom des joueurs\n\n");
	printf("Entrer le nom du Joueur1?\t %s\n", game->nomJoueur1);
	scanf("%s", joueur1);
	strncpy(game->nomJoueur1, joueur1, PLAYER_NAME_SIZE);
	if(game->mode == MULTI) {
		printf("Entrer le nom du Joueur2?\n");
		scanf("%s", joueur2);
		strncpy(game->nomJoueur2, joueur2, PLAYER_NAME_SIZE);
	} else if( game->mode == SOLO){
		strncpy(game->nomJoueur2, "Computer", PLAYER_NAME_SIZE);
	}
}

/* Mise à jour des sccores */
void misAJourScore(int result)
{
	if(result == 1) {
		printf("Bravo Joueur %s, a vous avez gagner 1 point\nAppuyer sur Entrée pour continuer la partie", joueur);
		/*scanf("%s", next); */
		if(tour == 0) {
			game->scoreJoueur1 = game->scoreJoueur1 + result;
		} else {
			game->scoreJoueur2 = game->scoreJoueur2 + result;
		}
	}
}

/* Vérifie fin de partie */
void verifierFinPartie(void)
{
	int score;
	if(g.nb_vide == 0) {
		/* Calcule le temps en seconde de la partie */
		time(&fin);
		duree = difftime(fin, debut);
		printf("duree = %d\n", duree);

		/* Vérifie s'il y a un gagnant  */
		if (game->scoreJoueur1 == game->scoreJoueur2){
			g.statut = MATCH_NUL;
			printf("Match nul !\n Le match a duré %d", duree);

		} else 	{
			g.statut = MATCH_END;
			if(tour == 0) 
				score = game->scoreJoueur1;
			else 
				score = game->scoreJoueur2;
			printf("Le joueur %s gagne avec %d points!\n, %c \n Le match a duré %d", joueur, score, g.statut, duree);
		}	
	}
	else {
		afficher_grille(g.tab, game);
	/*	printf("game->scoreJoueur1 %d\n", game->scoreJoueur1);
		printf("game->scoreJoueur2 %d\n", game->scoreJoueur2);
	*/
		if(tour == 0) {
			tour = 1;
			strncpy(joueur, game->nomJoueur2, PLAYER_NAME_SIZE);
	/*		printf("game->nomJoueur2 %s\n", game->nomJoueur2);
			printf("joueur %s\n\n", joueur);
	*/

		} else {
			tour = 0;
			strncpy(joueur, game->nomJoueur1, PLAYER_NAME_SIZE);
	/*		printf("game->nomJoueur1 %s\n", game->nomJoueur1);
			printf("joueur %s\n\n", joueur);
	*/
		}
	}
}

/* joueur humain joue un coup */
int jouer(int tour)
{
	int ligne, col;
	int correctAnswer = 0;
	do {
		ligne = saisie_donnee("Ligne : ");
		col = saisie_donnee("Colonne : ");
		if(g.tab[col][ligne] != '.')
			correctAnswer = 1;
	} while(correctAnswer == 1);
	struct Coup *coup = malloc(sizeof(coup));
	if(tour == 0) {
		coup->ligne = ligne;
		coup->colonne = col;
		strncpy(coup->player, game->nomJoueur1, PLAYER_NAME_SIZE);
		insertion(liste, coup);
		g.tab[col][ligne] = 'O';
	}else {
		coup->ligne = ligne;
		coup->colonne = col;
		strncpy(coup->player, game->nomJoueur2, PLAYER_NAME_SIZE);
		insertion(liste, coup);
		g.tab[col][ligne] = 'X';
	}
	afficherListe(liste);
	return 0;
}

int
main ()
{

	menuJeu();
	g = generer_grille(g.tab);
	if(isGameReloaded == NO) {
		menuJoueur();
	}
	time(&debut);
	afficher_grille(g.tab, game);
	strncpy(joueur, game->nomJoueur1, PLAYER_NAME_SIZE);
	liste = initialisation();
	while (g.statut == VIDE)
	{
		printf("Joueur %s, a vous de jouer !\n", joueur);
		if(game->mode == MULTI) {
			jouer(tour);
		} else {
			if(tour == 0) {
				jouer(tour);
			} else {
				struct Coup coup = ordijouer(g.tab);
				g.tab[coup.ligne][coup.colonne] = 'X';
				/* TEST WRITE DATA
				   writeData(liste, game);*/
			}
		}
		g.nb_vide--;
		/* Test si 3 pions sont allignés */
		char signe = (tour == 0) ? 'O' : 'X';
		int result = verifier_grille(g.tab, signe);
		printf("\n----- result: %d\n ", result);
		misAJourScore(result);
		/* Vérifie si la partie est finie */
		verifierFinPartie();

	}
	return 0;
}