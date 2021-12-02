OBJ = DUMBOB.o modele.o utils.o Plateau.o
CC = g++
INCLUDES = -I "../*.h"

program: $(OBJ)
	$(CC) -o program $(OBJ)

DUMBOB.o: DUMBOB.cpp
	$(CC) -c DUMBOB.cpp

modele.o: ../modele.cpp ../modele.h
	$(CC) -c ../modele.cpp

utils.o: ../utils.cpp ../utils.h
	$(CC) -c ../utils.cpp

Plateau.o: ../Plateau.cpp ../Plateau.h
	$(CC) -c ../Plateau.cpp