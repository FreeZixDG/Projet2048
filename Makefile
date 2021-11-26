OBJ = 2048.o modele.o tests.o utils.o
CC = g++
LFLAGS = -lncurses
INCLUDES = -I "C:/msys64/mingw64/include/ncursesw"

program: $(OBJ)
	$(CC) -o program $(OBJ) $(LFLAGS)

2048.o: 2048.cpp
	$(CC) -c 2048.cpp $(INCLUDES)

modele.o: modele.cpp modele.h
	$(CC) -c modele.cpp

tests.o: tests.cpp tests.h
	$(CC) -c tests.cpp $(INCLUDES)

utils.o: utils.cpp utils.h
	$(CC) -c utils.cpp

