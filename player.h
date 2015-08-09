#include "Game.h"

#define PLAYER_NAME_SIZE 26

int saisie_donnee (char * invite);
int getComputerCoord(void);
int choseGameType(void);
void ordijouer(char tab[LIGNE][COLONNE], struct Coup coup);