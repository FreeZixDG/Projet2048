
#include <ncurses/ncurses.h>
#define CHECK(test) if (!(test)) printw("Test failed in function '%s' line %d : %s\n", __FUNCTION__, __LINE__, #test)


void testLen();
void testStrip();
void testMaximumOf();

void testPlateauVide();
void testTireDeuxOuQuatre();
void testAll();