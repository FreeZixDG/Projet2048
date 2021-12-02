#include "Plateau.h"
using namespace std;

Plateau::Plateau(Grille g, int s): grille(g), score(s), TAILLE(grille[0].size())
{

}

Plateau::Plateau(): grille(Grille(4, vector<int>(4))), score(0), TAILLE(grille[0].size())
{

}