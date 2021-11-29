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
    Plateau g = plateauVide();



    fichier >> tries;
    fichier >> score;

    string line; 

    for (int i = 0; i < 4; i++)
    {
        fichier >> line;
        vector<int> c = extract_numbers(line);

        g.grille[i] = c;
        
    }

    fichier.close();

    return g;
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

char move()
{
    return 'H';
}



int main()
{
    int actual_try = 0;
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
            char rep = move();
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