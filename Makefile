OBJ_ALL = 2048.o 2048_IA.o modele.o utils.o Plateau.o BOB.o modele-test.o utils-test.o
OBJ_2048 = 2048.o modele.o utils.o Plateau.o BOB.o
OBJ_2048_IA = modele.o utils.o Plateau.o BOB.o 2048_IA.o
OBJ_MODELE_TEST = modele.o utils.o Plateau.o modele-test.o
OBJ_UTILS_TEST = utils.o utils-test.o

CC = g++
LFLAGS = -lncurses
INCLUDES = -I "D:/cygwin64/usr/include/ncursesw"

2048: $(OBJ_ALL)
	$(CC) $(OBJ_2048) $(LFLAGS) -o bin/2048
	$(CC) $(OBJ_2048_IA) -o bin/2048_IA
	$(CC) $(OBJ_MODELE_TEST) -o bin/modele-test
	$(CC) $(OBJ_UTILS_TEST) -o bin/utils-test

2048.o: src/2048.cpp
	$(CC) $(INCLUDES) -c src/2048.cpp

2048_IA.o: src/2048_IA.cpp
	$(CC) -c src/2048_IA.cpp

modele-test.o: src/modele-test.cpp
	$(CC) -c src/modele-test.cpp

modele.o: src/modele.cpp headers/modele.h
	$(CC) -c src/modele.cpp

utils.o: src/utils.cpp headers/utils.h
	$(CC) -c src/utils.cpp

utils-test.o: src/utils-test.cpp
	$(CC) -c src/utils-test.cpp

Plateau.o: src/Plateau.cpp headers/Plateau.h
	$(CC) -c src/Plateau.cpp

BOB.o: src/BOB.cpp
	$(CC) -c src/BOB.cpp
