CC=gcc
NAME=game
CFLAGS = -Wall -Wextra -Werror

$(NAME): main.c affichage.o cheval.o jeu.o joueur.o plateau.o sauvegarde.o
	$(CC) $(CFLAGS) main.c affichage.o cheval.o jeu.o joueur.o plateau.o sauvegarde.o -o $(NAME)

affichage.o: affichage.c affichage.h
	$(CC) $(CFLAGS) -c affichage.c

cheval.o: cheval.c cheval.h
	$(CC) $(CFLAGS) -c cheval.c

jeu.o: jeu.c jeu.h
	$(CC) $(CFLAGS) -c jeu.c

joueur.o: joueur.c joueur.h
	$(CC) $(CFLAGS) -c joueur.c

plateau.o: plateau.c plateau.h
	$(CC) $(CFLAGS) -c plateau.c

sauvegarde.o: sauvegarde.c sauvegarde.h
	$(CC) $(CFLAGS) -c sauvegarde.c

clean:
	rm *.o

run:
	make
	./$(NAME)

runc:
	make run
	make clean

cc:
	rm *.o; make
	
doc:
	doxygen Doxyfile
	doxygen DoxyfileClassic