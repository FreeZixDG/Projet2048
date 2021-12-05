#include "../modele.h"
/*choose_random_move
 * @return char, H B G ou D a proba égale (1/4)
*/
int choose_random_move(bool g, bool d, bool h, bool b);

/* plays a games staring with the first_direction move, and plays randomly until it loses
 * @param plateau Plateau, the starting plateau
 * @param first_direction int, the first direction
 * @return the end score
*/
int play_game(Plateau plateau, int first_direction, int moves_ahead);


/*Gives the in opinion best move given a Plateau
 * @param plateau Plateau
 * @param number_of_games int, the number of games the IA will simulate
 * @param moves_ahead int, the number of moves the IA will make before playing the next game
*/
char strat_brute(Plateau plateau, int number_of_games, int moves_ahead);