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
        } else
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
char choose_random_move()
{
    int v = rand() % 4;

    switch (v)
    {
    case 0:
        return 'G';
    
    case 1:
        return 'D';
    
    case 2:
        return 'H';
    
    case 3:
        return 'B';
    
    default:
        return -1;
    }

}

int convertDirection(char v)
{
    switch (v)
    {
        case 'G': return GAUCHE;
        case 'D': return DROITE;
        case 'H': return HAUT;
        case 'B': return BAS;
        default: return -1;
    }
}

char strat_brute(Plateau plateau)
{
    vector<tuple<char, int>> vec;
    Plateau temp = plateau;
    char first_direction_c;
    char direction_c;
    int direction;

    for (int k = 0; k < 1000; k++)
    {
        first_direction_c = choose_random_move();
        direction_c = first_direction_c;
        int compteur = 10;

        do
        {
            direction = convertDirection(direction_c);
            temp = deplacement(temp, direction);
            direction_c = choose_random_move();
            compteur--;
        } while (!estTermine(temp) and compteur > 0);

        vec.push_back(make_tuple(first_direction_c, temp.score));
        temp = plateau;
    }

    // je prend le move qui est associé au plus grand score
    char move;
    for (auto i: vec)
    {
        int max_score = 0;
        if (get<1>(i) > max_score)
        {
            move = get<0>(i);
        }
    }

    return move;
}



int main()
{
    srand(time(NULL));
    int actual_try = 0;
    char prev_move = '\0';
    int tries;
    int score;
    Plateau plateau;
    

    while (1)
    {
        do
        {
            printf("\rWaiting for game update n°%d", actual_try);
            fflush(stdout);
            this_thread::sleep_for(chrono::milliseconds(100));
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
            char rep = strat_brute(plateau);
            prev_move = rep;
            writeMove("mouvements.txt", "BOB", tries, rep);
            printf("updated!\n");
            printf("Wrote movement %c\n", rep);
            actual_try++;
        }


        printf("try: %d\nscore: %d\n", tries, score);
        printf("%s", dessine(plateau).c_str());
    }

    return 0;
}