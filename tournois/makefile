OBJ = DUMBOB.o modele.o utils.o Plateau.o BOB.o
CC = g++
INCLUDES = -I "../*.h"

program: $(OBJ)
	$(CC) -o program $(OBJ)

DUMBOB.o: DUMBOB.cpp
	$(CC) -c DUMBOB.cpp

BOB.o: BOB.cpp
	$(CC) -c BOB.cpp