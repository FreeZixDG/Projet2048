#include <fstream>
#include <iostream>
#include <typeinfo>
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

Plateau get_plateau(string path, int &tries, int &score)
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

        g[i] = c;
        
    }

    return g;
}

int main() {

    int tries;
    int score;

    Plateau t = get_plateau("configuration.txt", tries, score);
    cout << tries << endl;
    cout << score << endl;
    cout << dessine(t);

    return 0;
}