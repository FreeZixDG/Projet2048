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

/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 **/
Plateau plateauVide();

/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 **/
Plateau plateauInitial();

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre();

/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
Plateau deplacementGauche(Plateau plateau);

/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la droite
 **/
Plateau deplacementDroite(Plateau plateau);

/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
Plateau deplacementHaut(Plateau plateau);

/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le bas
 **/
Plateau deplacementBas(Plateau plateau);

/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le Plateau
 *  @param direction la direction
 *  @return le Plateau déplacé dans la direction
 **/
Plateau deplacement(Plateau plateau, int direction);

/** affiche un Plateau
 * @param p le Plateau
 **/
string dessine(Plateau g);

/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si la partie est terminée (aucun mouvement ne modifie le plateau), false sinon.
 **/
bool estTermine(Plateau plateau);

/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau);


int score(Plateau plateau);

/* ajouteTuile
 * @param plateau Plateau
 * @return Le meme plateau auquel on ajouté une tuile (2 ou 4) dans un espace disponible aléatoire.
*/
Plateau ajouteTuile(Plateau plateau);

/* Transpose
 * @param t Plateau
 * @return un Plateau ou chaque ligne correspond à chaque colone de t
*/
Plateau Transpose(Plateau plateau);

/* Combine_gauche
 * @param t Plateau
 * @return le plateau t auquel on a fait fusionne (et additione) vers la gauche les elements de meme valeur.
 * 
 * Exemple avec un Plateau t = {{2, 2, 8, 4}, {4, 4, 4, 16}} renvoie {{4, 0, 8, 4}, {8, 0, 4, 16}}
*/
Plateau Combine_gauche(Plateau t);

/* Combine_droite
 * @param t Plateau
 * @return le plateau t auquel on a fait fusionne (et additione) vers la gauche les elements de meme valeur.
 * 
 * Exemple avec un Plateau t = {{2, 2, 8, 4}, {4, 4, 4, 16}} renvoie {{0, 4, 8, 4}, {0, 4, 8, 16}}
*/
Plateau Combine_droite(Plateau t);

/* bougeGauche
 * @param t Plateau
 * @return une copie de t auquel on a décalé tous les éléments non nul à gauche.
 */
Plateau bougeGauche(Plateau t);
Plateau bougeDroite(Plateau t);
int brute_score(int n);