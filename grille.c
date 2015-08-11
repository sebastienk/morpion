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

void afficher_grille (char tab[][COLONNE], Game *g)
{
	int i,j;
	ClearScreen();
	printf(" %s : %d   -   %s : %d  \n", g->nomJoueur1, g->scoreJoueur1, g->nomJoueur2, g->scoreJoueur2);
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
	for(int i=0; i<1; i++){
       /* temp1 = combienHorizontalChar(tab, i, c);
        temp1 = (temp1 < 3) ? 0 : temp1;
        if(temp1 > 0)
            valueh = valueh + temp1;*/
        temp2 = combienVertitalChar(tab, i, c);
        //temp2 = (temp2 <3) ? 0 : temp2;
        if(temp2 > 0)
            valuev = valuev + temp2;
    }
    int valuedg = combienDiagonalGaucheHautChar(tab, 0, c);
    int valuedd = combienDiagonalGaucheBasChar(tab, 0, c);

    printf("\nvalueh %d \n", valueh);
    printf("\nvaluev %d \n", valuev);
    printf("\nvaluedg %d \n", valuedg);
    printf("\nvaluedd %d \n", valuedd);
    int total = valueh + valuev + valuedg + valuedd;
    printf("\ntotal %d \n", total);
    return total;
}

int combienHorizontalChar(char tab[][COLONNE], int index, char c)
{
    int value = 0;
   /* printf("\n############################## HORIZONTAL ######## carctère attendu %c ############################################\n", c);*/
    for(int i=0; i<COLONNE; i++){
       /* printf("%d - %d (%c) ",index, i, tab[i][index]);*/
        if(tab[i][index] == c) {
            if(value < 3 && tab[i+1][index] != c) {
                value = 0;
            } else {
                value++;
            }
        }
    }
    /*printf("\n carctère attendu %c --- HORIZONTAL --> %d\n", c, value);*/
    return value;
}


int combienVertitalChar(char tab[][COLONNE], int index, char c)
{
    int value, value_tmp = 0;
    printf("\n############################## VERTICAL ######## caractere attendu %c ############################################\n", c);
    for(int i=0; i<COLONNE; i++){
        if(tab[index][i] == c) {
            value_tmp++;
            if(value_tmp >2) {
                value = value + 1;
            }
            printf(" i = %d -- tab[index][i-1]+%c isRESET? ", i, tab[index][i-1]);
            if(i != 0 && tab[index][i-1] != c) {
                printf("YES \n");
                value_tmp = 0;
            } else {
                printf("NO \n");
            }
        } else {
         value_tmp = 0;
        }
        printf("i=%d -- value_tmp = %d tab[index][i] = (%c) # ", i, value_tmp, tab[index][i]);
        printf("  value_tmp : %d -- tab[index][i-1]: %c\n ", value_tmp, tab[index][i-1]);
    }
    if(c = 'O') printf("\n caractere attendu %c --- VERTICAL --> %d\n", c, value);
    return value;
}

int combienDiagonalGaucheHautChar(char tab[][COLONNE], int index, char c)
{
    int value = 0;
    int value_tmp = 0;
    printf("\n############################## dia gauche haut ######## carctère attendu %c ############################################\n", c);
    int a, b, n, p = 0;
    while(a < 8) {
        n = a;
        p = 0;
        b = 0;
       printf(":: %d -- %d = %d  --->  ", a, b, value);
        value_tmp = 0;
        while(b < LIGNE - a) {
          printf("%d - %d (%c) ",n, p, tab[n][p]);
            if(tab[n][p] == c)
                value_tmp++;
            n++;
            p++;
            b++;
        }
        
        printf(" ### %d  ** ", value_tmp);
        if(value_tmp > 2)
            value = value + (value_tmp-2);
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
    printf("\n############################# dia gauche bas ######## caractère attendu : %c #################################\n", c);
    int a = 1;
    int b,n,p = 0;
    while(a < 8) {
        n = 0;
        b = 0;
        p = a;
        printf(":: %d -- %d = %d  --->  ", a, b, value);
        value_tmp = 0;
        while(b < LIGNE - a) {
            printf("%d - %d (%c) ",n, p, tab[n][p]);
            if (tab[n][p] == c)
                value_tmp++;
            n++;
            p++;
            b++;
        }
        printf(" ### %d ** ", value_tmp);
        if(value_tmp >2)
            value = value + (value_tmp-2);
        printf("\n");
        a++;
    }
    printf("\n##################################### %d ##########################################\n", value);
    return value;
}

