OBJ = 2048_IA.o ../modele.o ../Plateau.o ../utils.o BOB.o
CC = g++
INCLUDES = -I "../*.h"

program: $(OBJ)
	$(CC) -o program $(OBJ)

2048_IA.o: 2048_IA.cpp
	$(CC) -c 2048_IA.cpp

BOB.o: BOB.cpp
	$(CC) -c BOB.cpp

Plateau.o: ../Plateau.cpp
	$(CC) -c ../Plateau.cpp

modele.o: ../modele.cpp
	$(CC) -c ../modele.cpp

utils.o: ../utils.cpp
	$(CC) -c ../utils.cpp