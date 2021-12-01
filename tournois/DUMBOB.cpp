#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <tuple>
#include "../modele.h"
#include "../utils.h"
using namespace std;

// actual best: 27408 pts
// actual best: 35892 pts
// actual best: 36912 pts

vector<int> extract_numbers(string s)
{
    vector<char> t;
    vector<string> a;
    vector<int> result;

    // pushing every char in the vector<char> t
    for (auto i: s)
    {
        t.push_back(i);
    }

    // pushing numbers (str) in the vector<string> a
    string r = "";
    for (auto i: t)
    {
        
        if (isdigit(i))
        {
            r += i;
        }
        else if (r != "") // ligne permettant de corriger un bug dans le fichier tournoi-simulation
        {
            a.push_back(r);
            r = "";
        }

    }

    // converting string to int
    for (string i: a)
    {
        result.push_back(stoi(i));
    }

    return result;
}

Plateau readInfo(string path, int &tries, int &score)
{
    ifstream fichier;
    fichier.open(path);
    Plateau plateau = plateauVide();



    fichier >> tries;
    fichier >> score;

    plateau.score = score;

    string line; 

    for (int i = 0; i < 4; i++)
    {
        fichier >> line;
        vector<int> c = extract_numbers(line);

        plateau.grille[i] = c;
        
    }

    fichier.close();

    return plateau;
}

void writeMove(string path, string name, int tries, char move)
{
    ofstream fichier;

    if (tries == 0)
    {
        fichier.open(path);
        fichier << name << endl;
        fichier << tries << ' ' << move << endl;
        fichier.close();
        return;
    }
    else
    {
        fichier.open(path, fstream::app);
        fichier << tries << ' ' << move << endl;
        fichier.close();
    }
}

char strat_HBDG(Plateau plateau, char prev_move)
{
    char response;
    if (prev_move == '\0')
    {
        response = 'H';
        return response;
    }

    if (prev_move == 'H')
    {
        response = 'D';
    }
    else if (prev_move == 'D')
    {
        response = 'B';
    }
    else if (prev_move == 'B')
    {
        response = 'G';
    }
    else
    {
        response = 'H';
    }
    return response;
}

char strat_priority(Plateau plateau)
{
    char response;

    if (deplacementHaut(plateau).grille != plateau.grille)
    {
        response = 'H';
    }
    else if (deplacementGauche(plateau).grille != plateau.grille)
    {  
        response = 'G';
    }
    else if (deplacementDroite(plateau).grille != plateau.grille)
    {
        response = 'D';
    }
    else
    {
        response = 'B';
    }
    
    return response;
}

/*choose_random_move
 * @return char, H B G ou D a proba égale (1/4)
*/
int choose_random_move()
{
    return rand() % 4 + 1;
}

char convertDirection(int v)
{
    switch (v)
    {
        case GAUCHE: return 'G';
        case DROITE: return 'D';
        case HAUT: return 'H';
        case BAS: return 'B';
        default: return -1;
    }
}

/* plays a games staring with the first_direction move, and plays randomly until it loses
 * @param plateau Plateau, the starting plateau
 * @param first_direction int, the first direction
 * @return the end score
*/
int play_game(Plateau plateau, int first_direction, int moves_ahead)
{

    int direction = first_direction;
    do
    {
        plateau = deplacement(plateau, direction);
        direction = choose_random_move();
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

    /*test if the position is valid*/
    if (deplacement(plateau, GAUCHE).grille == plateau.grille) moyenne_G = -1;
    if (deplacement(plateau, DROITE).grille == plateau.grille) moyenne_D = -1;
    if (deplacement(plateau, HAUT).grille == plateau.grille) moyenne_H = -1;
    if (deplacement(plateau, BAS).grille == plateau.grille) moyenne_B = -1;

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



int main()
{
    srand(time(NULL));
    int actual_try = 0;
    char prev_move = '\0';
    char rep;
    int tries;
    int score;
    Plateau plateau;
    

    while (1)
    {
        
        do
        {
            printf("\rWaiting for game update n°%d", actual_try);
            fflush(stdout);
            this_thread::sleep_for(chrono::milliseconds(2));
            plateau = readInfo("configuration.txt", tries, score);
        }
        while(tries != actual_try);

        if (estTermine(plateau))
        {
            printf("\nGame over.\n");
            break;
        }

        if (tries == actual_try)
        {
            printf("\n");
            if (plateau.score < 10000) rep = strat_brute(plateau, 50, 10);
            else if (plateau.score < 15000) rep = strat_brute(plateau, 100, 10);
            else if (plateau.score < 25000) rep = strat_brute(plateau, 500, 20);
            else if (plateau.score < 30000) rep = strat_brute(plateau, 1000, 30);
            else rep = strat_brute(plateau, 2000, 50);
            
            writeMove("mouvements.txt", "BOB", tries, rep);
            printf("updated!\n");
            printf("Wrote movement %c\n", rep);
            actual_try++;
        }


        printf("try: %d\nscore: %d\n", tries, score);
        system("clear");
        printf("%s", dessine(plateau).c_str());
    }

    return 0;
}


/*int main()
{
    srand(time(NULL));
    

    Plateau plateau = plateauInitial();


    cout << strat_brute(plateau);

    return 0;
}*/