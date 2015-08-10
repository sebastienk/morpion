/**
 *  Grille.c
 *  
 *
 **/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "grille.h"

char* values = "abcdefghij";

void ClearScreen()
{
	printf( "\n" );
}

grille generer_grille ()
{ 
	grille g;
	//g.tab = tab[LIGNE][COLONNE];
	int m, n;
	for (m = 0; m < LIGNE; m++){
		for (n = 0; n < COLONNE; n++){
			g.tab[n][m] = '.';
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

int verifier_grille(char tab[][COLONNE], char c)
{
    // CHECK LIGNE
    int valueh = 0;
    int valuev = 0;
    int temp1, temp2;
	for(int i=0; i<LIGNE; i++){
        temp1 = combienHorizontalChar(tab, i, c);
        temp1 = (temp1 < 3) ? 0 : temp1;
        if(temp1 > 0)
            valueh = valueh + (temp1 - 2) + 1;
        temp2 = combienVertitalChar(tab, i, c);
        temp2 = (temp2 <3) ? 0 : temp2;
        if(temp2 > 0)
            valuev = valuev + (temp2 - 2);
    }
    int valuedg = combienDiagonalGaucheHautChar(tab, 0, c);
    int valuedd = combienDiagonalGaucheBasChar(tab, 0, c);

    printf("\nvalueh %d \n", valueh);
    printf("\nvaluev %d \n", valuev);
    printf("\nvaluedg %d \n", valuedg);
    printf("\nvaluedd %d \n", valuedd);
    int total = valueh + valuev + valuedg + valuedd;
    return total;
}

int combienVertitalChar(char tab[][COLONNE], int index, char c)
{
    int value = 0;
    for(int i=0; i<COLONNE; i++){
        if(tab[i][index] == c)
            value++;
    }
    printf("\ncombienVertitalChar %d - --> %d\n", index, value);
    return value;
}


int combienHorizontalChar(char tab[][COLONNE], int index, char c)
{
    int value = 0;
    for(int i=0; i<COLONNE; i++){
        if(tab[index][i] == c)
            value++;
    }
    printf("\ncombienHorizontalChar %d - --> %d\n", index, value);
    return value;
}

int combienDiagonalGaucheHautChar(char tab[][COLONNE], int index, char c)
{
    int value = 0;
    int value_tmp = 0;
    printf("\n##################################################################################\n");
    int a = 0;
    int b = 0;
    int j = 0;
    int n = 0;
    int p = 0;
    while(a < 8) {
        n = a - 0;
        p = 0;
        b = 0;
        j = LIGNE - a;
        printf(":: %d -- %d -- %d = %d  --->  ", a, b, j, value);
        value_tmp = 0;
        while(b < j) {
            printf("%d - %d (%c) ",n, p, tab[n][p]);
            if(tab[n][p] == c)
                value_tmp++;
            n += 1;
            p += 1;
            b++;
        }
        int reste = (value_tmp < 3) ? 0 : (value_tmp - 2);
        printf(" ### %d o/o3 %d  ** ", value_tmp, reste);
        value = value + reste;
        printf(" value after %d\n", value);
        printf("\n");
        a++;
    }
    printf("\n################################# %d  ################################################\n", value);
    return value;
}

int combienDiagonalGaucheBasChar(char tab[][COLONNE], int index, char c)
{
    int value = 0;
    int value_tmp = 0;
    printf("\n############################# dia droite #########################################\n");
    int a = 1;
    int b = 0;
    int j = 0;
    int n = 0;
    int p = 0;
    while(a < 8) {
        n = 0;
        p = a-0;
        b = 0;
        j = LIGNE - a;
        printf(":: %d -- %d -- %d = %d  --->  ", a, b, j, value);
        value_tmp = 0;
        while(b < j) {
            printf("%d - %d (%c) ",n, p, tab[n][p]);
            if (tab[n][p] == c)
                value_tmp++;
            n += 1;
            p += 1;
            b++;
        }
        int reste = (value_tmp < 3) ? 0 : (value_tmp - 2);
        printf(" ### %d o/o3 %d  ** ", value_tmp, reste);
        value = value + reste;
        printf("\n");
        a++;
    }
    printf("\n##################################### %d ##########################################\n", value);
    return value;
}

