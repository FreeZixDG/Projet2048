OBJ = 2048.o modele.o utils.o Plateau.o
CC = g++
LFLAGS = -lncurses
INCLUDES = -I "C:/msys64/mingw64/include/ncursesw"

program: $(OBJ)
	$(CC) -o program $(OBJ) $(LFLAGS)

2048.o: 2048.cpp
	$(CC) -c 2048.cpp $(INCLUDES)

modele.o: modele.cpp modele.h
	$(CC) -c modele.cpp

utils.o: utils.cpp utils.h
	$(CC) -c utils.cpp

Plateau.o: Plateau.cpp Plateau.h
	$(CC) -c Plateau.cpp

