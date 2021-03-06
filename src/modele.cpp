#include <math.h>
#include <iostream>
#include <tuple>

#include "../headers/modele.h"
#include "../headers/utils.h"

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
    int lenght_max = len( maximumOf(g.grille) );

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
    Plateau result( Grille(t.grille[0].size(), vector<int>(t.grille.size())), t.score );


    for (int i = 0; i < t.grille.size(); i++)
    {
        for (int j = 0; j < t.grille[0].size(); j++)
        {
            result.grille[j][i] = t.grille[i][j];
        }
    }
    
    return result;
}

/*Plateau deplacementGauche(Plateau plateau)
{
    int size;
    int taille = plateau.TAILLE;
    // Pour chaque ligne
    for (auto &i: plateau.grille)
    {
        // on enleve les 0
        i.erase(remove(i.begin(), i.end(), 0), i.end());

        // on combine si possible
        size = i.size();
        for (int elem = 0; elem < size - 1; elem++)
        {
            if (i[elem] == i[elem + 1])
            {
                i[elem] *= 2;
                plateau.score += i[elem];
                i[elem + 1] = 0;
            }
        }

        // on re enleve les 0 (car en combinant on a laissé des "trou")
        i.erase(remove(i.begin(), i.end(), 0), i.end());

        size = i.size();

        //on rajoute les 0 au debut
        for (int k = 0; k < taille - size; k++)
        {
            i.push_back(0);
        }
    }

    return plateau;
}*/

Plateau deplacementGauche(Plateau plateau)
{
    int nb_zeros;
    int last_elem_checked;

    for (auto &line: plateau.grille)
    {
        nb_zeros = 0;
        last_elem_checked = 0;

        for (int i = 0; i < line.size(); i++) // du 1er jusque l'avant-dernier elem
        {
            if (line[i] == 0)
            {
                nb_zeros++;
            }

            else
            {
                if (line[i] == last_elem_checked)
                {
                    line[i - nb_zeros - 1] *= 2;
                    plateau.score += line[i - nb_zeros - 1];
                    last_elem_checked = 0;
                    line[i] = 0;
                    nb_zeros++;
                }

                else
                {
                    if (nb_zeros)
                    {
                        line[i - nb_zeros] = line[i];
                        last_elem_checked = line[i];
                        line[i] = 0;
                    }
                    else 
                    {
                        last_elem_checked = line[i];
                    }
                }

                
            }
        }
    }

    return plateau;
}

Plateau deplacementDroite(Plateau plateau)
{
    int nb_zeros;
    int last_elem_checked;

    for (auto &line: plateau.grille)
    {
        nb_zeros = 0;
        last_elem_checked = 0;

        for (int i = line.size() - 1; i >= 0; i--) // du 1er jusque l'avant-dernier elem
        {
            if (line[i] == 0)
            {
                nb_zeros++;
            }

            else
            {
                if (line[i] == last_elem_checked)
                {
                    line[i + nb_zeros + 1] *= 2;
                    plateau.score += line[i + nb_zeros + 1];
                    last_elem_checked = 0;
                    line[i] = 0;
                    nb_zeros++;
                }

                else
                {
                    if (nb_zeros)
                    {
                        line[i + nb_zeros] = line[i];
                        last_elem_checked = line[i];
                        line[i] = 0;
                    }
                    else
                    {
                        last_elem_checked = line[i];
                    }
                }
                
            }
        }
    }

    return plateau;
}

/*Plateau deplacementDroite(Plateau plateau)
{
    int size;
    int taille = plateau.TAILLE;
    // Pour chaque ligne
    for (auto &i: plateau.grille)
    {
        // on enleve les 0
        i.erase(remove(i.begin(), i.end(), 0), i.end());

        size = i.size();

        // on combine si possible
        for (int elem = size - 1; elem > 0; elem--)
        {
            if (i[elem] == i[elem - 1])
            {
                i[elem] *= 2;
                plateau.score += i[elem];
                i[elem - 1] = 0;
            }
        }

        // on re enleve les 0 (car en combinant on a laissé des "trou")
        i.erase(remove(i.begin(), i.end(), 0), i.end());

        size = i.size();

        //on rajoute les 0 au debut
        for (int k = 0; k < taille - size; k++)
        {
            i.insert(i.begin(), 0);
        }
    }

    return plateau;
}*/


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

