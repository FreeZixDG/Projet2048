#include "BOB.h"
using namespace std;

int choose_random_move(bool g, bool d, bool h, bool b)
{
    
    int c;
    do
    {
        c = rand() % 4 + 1;
    } while( !(
        (c == GAUCHE and g)
     or (c == DROITE and d)
     or (c == HAUT and h)
     or (c == BAS and b) )
     );
    return c;
}

/* plays a games staring with the first_direction move, and plays randomly until it loses
 * @param plateau Plateau, the starting plateau
 * @param first_direction int, the first direction
 * @return the end score
*/
int play_game(Plateau plateau, int first_direction, int moves_ahead)
{
    int direction = first_direction;
    Grille old_grille;
    bool g = 1;
    bool d = 1;
    bool h = 1;
    bool b = 1;
    int c = 0;
    do
    {
        old_grille = plateau.grille;
        plateau = deplacement(plateau, direction);
        //au prochain coup, on interdit d'aller dans la direction qui n'est pas valide
        if (old_grille == plateau.grille)
        {
            switch (direction)
            {
            case GAUCHE:
                g = 0;
                break;
            
            case DROITE:
                d = 0;
                break;
            
            case HAUT:
                h = 0;
                break;
            
            case BAS:
                b = 0;
                break;
            }
            moves_ahead++;
        }
        
        // si tout va bien, on ajoute une tuile, et on autorise toutes les direction au prochain coup
        else
        {
            plateau = ajouteTuile(plateau);
            g = 1;d = 1;h = 1;b = 1;
        }
        // si bloqué, on arrete
        if (!(g or d or h or b)) break;

        direction = choose_random_move(g, d, h, b);
        moves_ahead--;
    } while (moves_ahead != 0);

    return plateau.score;
}


char strat_brute(Plateau plateau, int number_of_games, int moves_ahead)
{
    int moyenne_G = 0;
    int moyenne_D = 0;
    int moyenne_H = 0;
    int moyenne_B = 0;

    /*ignore the invalid starting position*/
    if (deplacementGauche(plateau).grille == plateau.grille) moyenne_G = -1;
    if (deplacementDroite(plateau).grille == plateau.grille) moyenne_D = -1;
    if (deplacementHaut(plateau).grille == plateau.grille) moyenne_H = -1;
    if (deplacementBas(plateau).grille == plateau.grille) moyenne_B = -1;

    for (int k = 0; k < number_of_games / 4; k++)
    {
        if (moyenne_G != -1) moyenne_G += play_game(plateau, GAUCHE, moves_ahead);
        if (moyenne_D != -1) moyenne_D += play_game(plateau, DROITE, moves_ahead);
        if (moyenne_H != -1) moyenne_H += play_game(plateau, HAUT, moves_ahead);
        if (moyenne_B != -1) moyenne_B += play_game(plateau, BAS, moves_ahead);
    } 

    int max_score = max(max(moyenne_G, moyenne_D), max(moyenne_H, moyenne_B));

    if (max_score == moyenne_G) return 'G';
    if (max_score == moyenne_D) return 'D';
    if (max_score == moyenne_H) return 'H';
    if (max_score == moyenne_B) return 'B';
    else return -1;
}