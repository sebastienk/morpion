#	Script de compilation
#	-o  ---> output
#	-c  ---> compile
#	-rm ---> remove
#	-rf ---> remove force
#	*.o ---> tous les fichiers avec l'extention .o

CC=gcc
PARAMS=-W -Wall -Wextra -std=c99

all: mrproper morpion clean

#Génère le fichier morpion.exe
morpion: create-grille.o create-player.o create-sauvegarde.o create-game.o create-main.o
	$(CC) -o morpion grille.o player.o sauvegarde.o game.o main.o

#Génère le fichier temporaire grille.o
create-grille.o: grille.c
	$(CC) -o grille.o -c grille.c $(PARAMS)

#Génère le fichier temporaire player.o
create-player.o: player.c
	$(CC) -o player.o -c player.c $(PARAMS)

#Génère le fichier temporaire sauvegarde.o
create-sauvegarde.o: sauvegarde.c
	$(CC) -o sauvegarde.o -c sauvegarde.c $(PARAMS)

#Génère le fichier temporaire game.o
create-game.o: sauvegarde.c
	$(CC) -o Game.o -c Game.c $(PARAMS)

#Génère le fichier temporaire main.o
create-main.o: main.c grille.h player.h sauvegarde.h
	$(CC) -o main.o -c main.c $(PARAMS)

#Efface tous les fichiers temporaires avec l'extention .o
clean:
	rm -rf *.o

#Efface le fichier morpion.exe
mrproper: clean
	rm -rf morpion