OBJ = DUMBOB.o ../modele.o ../utils.o ../Plateau.o
CC = g++
INCLUDES = -I "../*.h"

program: $(OBJ)
	$(CC) -o program $(OBJ)

DUMBOB.o: DUMBOB.cpp
	$(CC) -c DUMBOB.cpp $(INCLUDES)

../modele.o: ../modele.cpp ../modele.h
	$(CC) -c ../modele.cpp $(INCLUDES)
	mv modele.o ../

../utils.o: ../utils.cpp ../utils.h
	$(CC) -c ../utils.cpp $(INCLUDES)
	mv utils.o ../

../Plateau.o: ../Plateau.cpp ../Plateau.h
	$(CC) -c ../Plateau.cpp $(INCLUDES)
	mv Plateau.o ../