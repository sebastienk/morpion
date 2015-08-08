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

int sauvegardeCoups(int ligne, int col, int tour)
{
	char fileName[20];
	FILE *fichier;
	if(tour == 0) {
		strcpy(fileName, "joueur1.txt");
	} else  {
		strcpy(fileName, "joueur2.txt");
	}
	fichier=fopen(fileName, "a+");
	if(fichier==NULL){
	  printf("\nUnable to open file myfile.txt");
	  exit(1);
	}
    fprintf(fichier, "%d", ligne);
    fprintf(fichier, "%d", col);
	fclose(fichier);
    return 1;
}

int createFile(char nom[20], int score, int tour, int mode, int temps)
{
	char fileName[7];
	FILE *fichier;
	if(tour == 0) {
		strcpy(fileName, "joueur1.txt");
	} else  {
		strcpy(fileName, "joueur2.txt");
	}
	fichier = fopen(fileName, "w+");
	if(fichier == NULL){
	  printf("\nUnable to open file myfile.txt");
	  exit(1);
	}

	fprintf(fichier, "%d%s", score, "\r\n");
	fprintf(fichier, "%s%s", nom, "\r\n");
	fprintf(fichier, "%d%s", mode, "\r\n");
	fprintf(fichier, "%d%s", temps, "\r\n");
	fclose(fichier);
    return 1;
}

sauve lireSauvegarde(void)
{
	FILE *fichier;
	sauve sov;
	char line[256];
	int mode;
	char nom[20];
	char score[5];
	char coups[50];
	int count = 0;
    int temps;
	printf("lireSauvegardce ::\n\n");
	fichier = fopen("joueur2.txt", "r");
    while (fgets(line, sizeof(line), fichier)) {
		if(count == 0) {
			strncpy(score, line, strlen(line)-1);
		} else if (count == 1) {
			strncpy(nom, line, strlen(line)-1);
		} else if (count == 2) {
			mode = strlen(line)-1;
		}else  if (count == 3){
			temps = strlen(line)-1;
		}else  if (count == 4){
            strncpy(coups, line, strlen(line));
        }
		count++;  
    }

	printf("::mode: %d\n", mode);
	printf("::score: %s\n", score); 
    printf("::nom: %s\n", nom);
    printf("::temps: %d\n", temps);
    printf("::coups: %s\n\n", coups);

    sov.mode = mode;
	sov.temps = temps;
	strncpy(sov.score, score, strlen(score));
	strncpy(sov.nom, nom, strlen(nom));
    strncpy(sov.coups, coups, strlen(coups));
	
	printf("\n\n::mode: %d\n", sov.mode);
	printf("::score: %s\n", sov.score); 
    printf("::nom: %s\n", sov.nom);
    printf("::temps: %d\n", sov.temps);
    printf("::coups: %s\n\n\n", sov.coups); 

	return sov;
}

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}