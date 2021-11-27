#include "Plateau.h"
using namespace std;

Plateau::Plateau(Grille g, int s): grille(g), score(s)
{

}

Plateau::Plateau(): grille(Grille(4, vector<int>(4))), score(0)
{

}