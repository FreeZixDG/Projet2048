#include <fstream>
#include <iostream>
#include <thread>
#include "BOB.h"
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

Plateau readInfo(string path, int &tries, int &score, int match)
{
    ifstream fichier;
    fichier.open(path);
    Plateau plateau;
    fichier >> tries;

    if (tries != match) return Plateau({{},{},{},{}});

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

    if (deplacementHaut(plateau).grille != plateau.grille) response = 'H';
    else if (deplacementGauche(plateau).grille != plateau.grille) response = 'G';
    else if (deplacementDroite(plateau).grille != plateau.grille) response = 'D';
    else response = 'B';

    
    return response;
}









int main()
{
    const int MAX = 999999;
    int nb_games;
    int nb_moves;
    srand(time(NULL));
    int actual_try = 0;
    char prev_move = '\0';
    char rep;
    int tries;
    int score;
    Plateau plateau;
    int nb_tiles;
    string mode;
    int won = 0;

    while (1)
    { 
        do
        {
            printf("\rWaiting for game update n°%d", actual_try);
            fflush(stdout);
            this_thread::sleep_for(chrono::milliseconds(30));
            plateau = readInfo("configuration.txt", tries, score, actual_try);
        }
        while( tries != actual_try or plateau.grille == Grille{{},{},{},{}} ); //plateau.grille != Grille({{},{},{},{}}) est au cas ou le fichier n'a pas pu lire

        system("clear");
        if (!won)
        {
            if (estGagnant(plateau)) won = actual_try;
        }

        if(nb_games <= 300) mode = "Easy";
        else if (nb_games >= 3000) mode = "Extreme";
        else mode = "Custom";

        printf("Plateau n°%d: (%s mode (%d:%d))\n", actual_try, mode.c_str(), nb_games, nb_moves);
        printf("%s", dessine(plateau).c_str());

        if (estTermine(plateau))
        {
            printf("\nGame over.\n");
            break;
        }

        if (tries == actual_try)
        {
            printf("\n");

            if (plateau.score >= 34000 and plateau.score <= 42000)
                {nb_games = 3000; nb_moves = MAX;}

            else
                {nb_games = 300; nb_moves = 10;}


            // Calcul du meilleur coup selon BOB
            rep = strat_brute(plateau, nb_games, nb_moves);
            // fin calcul

            writeMove("mouvements.txt", "BOB", tries, rep);
            printf("updated!\n");
            printf("Wrote movement %c\n", rep);
            actual_try++;
        }


        printf("score: %d\n", score);
    }

    ofstream result;

    result.open("resultats.txt", fstream::app);
    result << "Mode: " << nb_games << " " << nb_moves << " | Score final: " << plateau.score << " | 2048 obtenu au coup: " << won << endl;

    printf("Score final: %d\n", plateau.score);
    if (won) printf("A obtenu un 2048 au coup n°%d\n", won);
    else printf("N'a pas obtenu de 2048.\n");

    return 0;
}