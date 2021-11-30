#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include "../modele.h"
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

char Strat_HDBG(Plateau plateau, char prev_move)
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

char priority_strat(Plateau plateau)
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
    else if (deplacementDroite(plateau).grille == plateau.grille)
    {
        response = 'D';
    }
    else
    {
        response = 'B';
    }
    
    return response;
}



int main()
{
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
        } while(tries != actual_try);

        if (tries == actual_try)
        {
            cout << endl;
            char rep = Strat_HDBG(plateau, prev_move);
            prev_move = rep;
            writeMove("mouvements.txt", "BOB", tries, rep);
            cout << "updated!" << endl;
            cout << "Wrote movement " << rep << endl;
            actual_try++;
        }


        cout << tries << " " << score << endl;
        cout << dessine(plateau);
    }

    return 0;
}