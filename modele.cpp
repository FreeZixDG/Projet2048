#include <math.h>
#include <iostream>
#include <tuple>

#include "modele.h"
#include "utils.h"

using namespace std;


Plateau plateauVide()
{
    Plateau plateau;
    return plateau;
}


int tireDeuxOuQuatre()
{
    return rand() % 100 + 1 <= 10 ? 4: 2;
}



Plateau ajouteTuile(Plateau plateau)
{

    /*list_of_index
     * @param value int
     * @return un tableau de tuple (i, j) étant les coordonnées dans le plateau correspondant à la valeur "value".
    */
    auto list_of_index = [plateau](int value)
    {
        vector<tuple<int, int>> result;

        for (int i = 0; i < plateau.grille.size(); i++) {
            for (int j = 0; j < plateau.grille[0].size(); j++) {
                if (plateau.grille[i][j] == value) {

                    result.push_back(make_tuple(i, j));

                }
            }
        }

        return result;

    };

    vector<tuple<int, int>> emplacement_of_zeros = list_of_index(0);

    int index = rand() % emplacement_of_zeros.size();

    int i = get<0>(emplacement_of_zeros[index]);
    int j = get<1>(emplacement_of_zeros[index]);

    int val = tireDeuxOuQuatre();

    plateau.grille[i][j] = val;

    return plateau;
}


Plateau plateauInitial()
{
    Plateau plateau;

    plateau = ajouteTuile(plateau);
    plateau = ajouteTuile(plateau);

    return plateau;
}


string dessine(Plateau g)
{

    string result = "";
    int max_number = maximumOf(g.grille);
    int lenght_max = len(max_number);

    /* affiche_bord
     * @param t Plateau
     * @param lenght_max int, la longeur du plus grand entier dans t.
     * Ajoute à result une série de '*' pour faire le bords horizontal du plateau
    */
    auto affiche_bord = [&result](Plateau t, int lenght_max)
    {
        for (int k = 0; k < t.grille[0].size(); k++)
        {
            for (int l = 0; l < (3 + lenght_max); l++)
            {
                result += "*";
            }
        }
        result += "*\n";
    };

    /* set_middle_width
     * @param expr string
     * @param weight int, la largeur totale souhaitée
     * Ajoute à result la valeur "expr" en ajoutant des espace à gauche et
    à droite pour correspondre à la largeur "weight" souhaitée.
    */
    auto set_middle_width = [&result](string expr, int weight)
    {
        for (int k = 0; k < floor( (weight - expr.size()) / 2. ); k++)
        {
            result += ' ';
        }
        result += expr;
        for (int k = 0; k < ceil( (weight - expr.size()) / 2. ); k++)
        {
            result += ' ';
        }
    };

    for (int i = 0; i < g.grille.size(); i++)
    {
        affiche_bord(g, lenght_max);
        
        result += "* ";
        for (int j = 0; j < g.grille[i].size(); j++)
        {
            string expression = g.grille[i][j] == 0 ? " " : to_string(g.grille[i][j]);
            set_middle_width(expression, lenght_max);
            result += " * ";
        }
        result += "\n";
    }

    affiche_bord(g, lenght_max);
    return result;
}


Plateau Transpose(Plateau t)
{
    Grille result(t.grille[0].size(), vector<int>(t.grille.size()));


    for (int i = 0; i < t.grille.size(); i++)
    {
        for (int j = 0; j < t.grille[0].size(); j++)
        {
            result[j][i] = t.grille[i][j];
        }
    }

    t.grille = result;
    
    return t;
}

Plateau deplacementGauche(Plateau plateau)
{
    int size;
    int taille = 4;
    // Pour chaque ligne
    for (auto &i: plateau.grille)
    {
        // on enleve les 0
        i = strip(i, 0);

        // on combine si possible
        size = i.size();
        for (int elem = 0; elem < size - 1; elem++)
        {
            if (i[elem] == i[elem + 1])
            {
                i[elem] = 2 * i[elem];
                plateau.score += i[elem];
                i[elem + 1] = 0;
            }
        }

        // on re enleve les 0 (car en combinant on a laissé des "trou")
        i = strip(i, 0);

        size = i.size();

        //on rajoute les 0 au debut
        for (int k = 0; k < taille - size; k++)
        {
            i.push_back(0);
        }
    }

    return plateau;
}


Plateau deplacementDroite(Plateau plateau)
{
    int size;
    int taille = 4;
    // Pour chaque ligne
    for (auto &i: plateau.grille)
    {
        // on enleve les 0
        i = strip(i, 0);

        // on combine si possible
        for (int elem = i.size() - 1; elem > 0; elem--)
        {
            if (i[elem] == i[elem - 1])
            {
                i[elem] = 2 * i[elem];
                plateau.score += i[elem];
                i[elem - 1] = 0;
            }
        }

        // on re enleve les 0 (car en combinant on a laissé des "trou")
        i = strip(i, 0);

        size = i.size();

        //on rajoute les 0 au debut
        for (int k = 0; k < taille - size; k++)
        {
            i.insert(i.begin(), 0);
        }
    }

    return plateau;
}


Plateau deplacementBas(Plateau plateau)
{
    plateau = Transpose(plateau);
    plateau = deplacementDroite(plateau);
    plateau = Transpose(plateau);
    return plateau;
}


Plateau deplacementHaut(Plateau plateau)
{
    plateau = Transpose(plateau);
    plateau = deplacementGauche(plateau);
    plateau = Transpose(plateau);
    return plateau;
}


bool estTermine(Plateau plateau)
{
    plateau = deplacementGauche(plateau);
    plateau = deplacementDroite(plateau);
    plateau = deplacementHaut(plateau);
    plateau = deplacementBas(plateau);

    for (auto &i: plateau.grille)
    {
        for (auto &j: i)
        {
            if (j == 0)
            {
                return false;
            }
        }
    }
    return true;;
}

bool estGagnant(Plateau plateau)
{
    bool est_gagnant = false;
    for (auto i: plateau.grille)
    {
        for (auto j: i)
        {
            if (j >= 2048)
            {
                est_gagnant = true;
            }
        }
    }
    return est_gagnant;
}

/* deplacement
 * @param t Plateau
 * @param direction int, une direction (haut, gauche, droite ou bas)
 * @return une copie de t auquel on a effectué un déplacement dans une direction dans les règles du jeu 2048.
*/
Plateau deplacement(Plateau plateau, int direction)
{
    Plateau old_plateau = plateau;
    switch (direction)
    {
    case DROITE:
        plateau = deplacementDroite(plateau);
        break;
    case GAUCHE:
        plateau =  deplacementGauche(plateau);
        break;
    case HAUT:
        plateau =  deplacementHaut(plateau);
        break;
    case BAS:
        plateau =  deplacementBas(plateau);
        break;
    default:
        cerr << "Deplacement non-autorise!" << endl;
        exit(-1);
    }

    if (old_plateau.grille != plateau.grille) {
        plateau = ajouteTuile(plateau);
    }
    
    return plateau;
}

