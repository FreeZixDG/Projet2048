GRAPHIC_PROGS=$(wildcard exemple-graphisme*.cpp segment*.cpp cercle*.cpp premier-dessin*.cpp disque*.cpp souris*.cpp)

PROGS=$(GRAPHIC_PROGS)
TARGET=$(PROGS:%.cpp=%)

# -NDEBUG pour tester comme dans l'environnement conda où elle est définie
CXXFLAGS+=-std=c++11 -Wall -Wno-narrowing -pedantic -DNDEBUG

all: $(TARGET)

%.o: %.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

$(GRAPHIC_PROGS:%.cpp=%): %: %.o primitives.o
	g++ $(CXXFLAGS) $(LDFLAGS) $^ -o $@ -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio

clean:
	-rm -rf $(TARGET) *.o
