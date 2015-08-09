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

#define TRUE 1
#define FALSE 0
#define LIGNE 10
#define COLONNE 10
#define MATCH_NUL 'N'
#define MATCH_END 'E'
#define YES 1
#define NO 0
#define MULTI 1
#define SOLO 2

char tab[LIGNE][COLONNE];
sauve sov;
grille g;
char X ='X';
char O ='O';

char ordi[20] = "Ordinateur";
int tour, count = 0;

int last = 0;

int duree;
int mode;
int isGameReloaded = NO;
	
time_t debut, fin;
unsigned int score_joueur1 = 0;
unsigned int score_joueur2 = 0;

/* Choisir le mode de jeu MULTI pour deux humains et SOLO pour humain contre ordinateur */
void menuJeu(void)
{
	int tmp = 0;
	tmp = choseGameType();
	printf("tmp = %d\n", tmp);
	if(tmp == 1)
	{
		printf("MODE MULTI ");
		mode = MULTI;
	}
	else if(tmp == 2)
	{
		printf("MODE SOLO ");
        mode = SOLO;
	}
	else
	{
		printf("\nLire sauvegarde from main\n");
		sov = lireSauvegarde();
		strncpy(g.joueur, sov.nom, strlen(sov.nom));
		mode = sov.mode;

		score_joueur2 = (uintptr_t)(sov.score - '0');
		isGameReloaded = YES;
		printf("mode: %d\n", sov.mode);
		printf("score: %d\n", score_joueur2);
		printf("nom: %s\n", sov.nom);
		printf("coups: %s\n", sov.coups);
	}
}
 
/* Choisir le nom des joeurs */
void menuJoueur(void)
{
	char joueur1[26];
	char joueur2[26];
	printf("Entrer le nom des joueurs\n\n");
	printf("mode = %d\n", mode);
	printf("Nom du Joueur1?\n");

	do {
		fgets(joueur1, 26, stdin);
		memset(g.joueur1, '\0', sizeof (g.joueur1));
		strncpy(g.joueur1, joueur1, sizeof (g.joueur1));
		createFile(joueur1, 0, 0, mode, 0);
		printf("mode = %s\n", joueur1);
	}while(joueur1 == NULL);
	printf("mode = %d\n", mode);
	if(mode == MULTI) {
		printf("Nom du Joueur2?\n");
		fgets(joueur2, 26, stdin);
		strncpy(g.joueur2, joueur2, sizeof (joueur2));
		createFile(joueur2, 0, 1, mode, 0);
	} else if( mode == SOLO){
		createFile("computer", 0, 1, mode, 0);
	} else {

	}
	printf("g.joueur1 after create: %s\n", g.joueur1);
}



/* Mise à jour des sccores */
void misAJourScore(int result)
{
	if(result == 1) {
		printf("Bravo Joueur %s, a vous avez gagner 1 point\nAppuyer sur Entrée pour continuer la partie", g.joueur);
		/*scanf("%s", next); */
		if(tour == 0) {
			score_joueur1 = score_joueur1 + 1;
		} else {
			score_joueur2 = score_joueur2 + 1; 
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
		if (score_joueur1 == score_joueur2){
			g.statut = MATCH_NUL;
			printf("Match nul !\n Le match a duré %d", duree);
			getchar();
		} else 	{
			g.statut = MATCH_END;
			if(tour == 0) 
				score = (uintptr_t)g.score_joueur1;
			else 
				score = (uintptr_t)g.score_joueur2;
			printf("Le joueur %s gagne avec %d points!\n, %c \n Le match a duré %d", g.joueur, score, g.statut, duree);
			getchar();
		}	
	}
	else {
		afficher_grille(tab, score_joueur1, score_joueur2);
		if(tour == 0) {
			tour = 1;
			strncpy(g.joueur, g.joueur2, sizeof (g.joueur));

		} else {
			tour = 0;
			strncpy(g.joueur, g.joueur1, sizeof (g.joueur));
			
		}
	}	
}

void exitGame(void)
{
	printf("REAL EXIT FUNCTION");
}

/* ordinateur joue un coup */
void ordijouer(void)
{
	int ligne, col;
	int correctAnswer = 0;
	do {
		ligne = getComputerCoord();
		col = getComputerCoord();
		if(tab[col][ligne] != '.')
			correctAnswer = 1;
	} while(correctAnswer == 1);
	sauvegardeCoups(ligne, col, tour);
	tab[col][ligne] = 'X';
}

/* joueur humain joue un coup */
int jouer(int tour)
{
	int ligne, col;
	int correctAnswer = 0;
	printf("tour :: %d\n\n", tour);
	do {
		ligne = saisie_donnee("Ligne : ");

		if(ligne == 27) {
			printf("EXIT !!! ");
			last = 1;
			exitGame();
			return 0;
		}
		col = saisie_donnee("Colonne : ");
		if(tab[col][ligne] != '.')
			correctAnswer = 1;
	} while(correctAnswer == 1);
	
	if(tour == 0) {
		tab[col][ligne] = 'O';
		sauvegardeCoups(ligne, col, tour);
	}else{
		tab[col][ligne] = 'X';
		sauvegardeCoups(ligne, col, tour);
	}
	return 0;
}

int main (){
	
	int result = 0;
	menuJeu();
	printf("mode %d |", mode);
	printf("isGameReloaded %c |", isGameReloaded);
	g = generer_grille(tab);
	if(isGameReloaded == NO) {
		menuJoueur();
	}
	time(&debut);
	afficher_grille(tab, score_joueur1, score_joueur2);
	strncpy(g.joueur, g.joueur1, sizeof (g.joueur));
	while (g.statut == VIDE && last == 0)
	{
		printf("last %d, !\n", last);
		printf("Joueur %s, a vous de jouer !\n", g.joueur);
		if(mode == MULTI) {
			jouer(tour);
		} else {
			if(tour == 0) {
				jouer(tour);
			} else {
				ordijouer();	
			}
		}
		g.nb_vide--;
		/* Test si 3 pions sont allignés */
		result = verifier_grille(tab);
		misAJourScore(result);
		/* Vérifie si la partie est finie */
		verifierFinPartie();
	}
	return 0;
}