OBJ = 2048.o modele.o
CC = g++
LFLAGS = -lncurses

program: $(OBJ)
	$(CC) -o program $(OBJ) $(LFLAGS)

2048.o: 2048.cpp
	$(CC) -c 2048.cpp

modele.o: modele.cpp modele.h
	$(CC) -c modele.cpp