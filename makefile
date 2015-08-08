all: mrproper morpion clean

morpion: grille.o player.o sauvegarde.o main.o
	gcc -o morpion grille.o player.o sauvegarde.o main.o 
	
player.o: player.c
	gcc -o player.o -c player.c -W -Wall -Wextra -pedantic
	
grille.o: grille.c
	gcc -o grille.o -c grille.c -W -Wall -Wextra -pedantic

sauvegarde.o: sauvegarde.c
	gcc -o sauvegarde.o -c sauvegarde.c -W -Wall -Wextra -pedantic
	
main.o: main.c grille.h player.h sauvegarde.h
	gcc -o main.o -c main.c -W -Wall -Wextra -pedantic

clean:
	rm -rf *.o

mrproper: clean
	rm -rf morpion