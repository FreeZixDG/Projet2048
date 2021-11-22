#include <stdexcept>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <conio.h>

using namespace std;

const int GAUCHE = 7, DROITE = 4, HAUT = 8, BAS = 2;
const int W = 4;
const int H = 4;
typedef vector<vector<int>> Plateau;

Plateau plateauVide();
Plateau plateauInitial();
int tireDeuxOuQuatre();

Plateau deplacementGauche(Plateau plateau);
Plateau deplacementDroite(Plateau plateau);
Plateau deplacementHaut(Plateau plateau);
Plateau deplacementBas(Plateau plateau);
Plateau deplacement(Plateau plateau, int direction);
string dessine(Plateau g);
bool estTermine(Plateau plateau);
bool estGagnant(Plateau plateau);
int score(Plateau plateau);


Plateau ajouteTuile(Plateau plateau);