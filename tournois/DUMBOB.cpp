#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
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

int main()
{
    int actual_try = 0;
    int tries;
    int score;
    Plateau plateau = readInfo("configuration.txt", tries, score);

    if (tries == actual_try)
    {
        writeMove("mouvement.txt", "BOB", tries, 'H');
        actual_try++;
    }

    cout << tries << endl;
    cout << score << endl;
    cout << dessine(plateau);

    return 0;
}