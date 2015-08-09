all: mrproper morpion clean

#Génère le fichier morpion.exe
morpion: grille.o player.o sauvegarde.o main.o
	gcc -o morpion grille.o player.o sauvegarde.o main.o

#Génère le fichier temporaire grille.o
grille.o: grille.c
	gcc -o grille.o -c grille.c -W -Wall -Wextra -pedantic

#Génère le fichier temporaire player.o
player.o: player.c
	gcc -o player.o -c player.c -W -Wall -Wextra -pedantic

#Génère le fichier temporaire sauvegarde.o
sauvegarde.o: sauvegarde.c
	gcc -o sauvegarde.o -c sauvegarde.c -W -Wall -Wextra -pedantic

#Génère le fichier temporaire main.o
main.o: main.c grille.h player.h sauvegarde.h
	gcc -o main.o -c main.c -W -Wall -Wextra -pedantic

#Efface tous les fichiers temporaires avec l'extention .o
clean:
	rm -rf *.o

#Efface le fichier morpion.exe
mrproper: clean
	rm -rf morpion