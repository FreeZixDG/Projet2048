#include <math.h>
#include <iostream>
#include <tuple>

#include "modele.h"
#include "utils.h"

using namespace std;


Plateau plateauVide() {

    Plateau plateau;
    return plateau;

}


int tireDeuxOuQuatre() {
    return rand() % 100 + 1 <= 10 ? 4: 2;
}



Plateau ajouteTuile(Plateau plateau) {

    /*list_of_index
     * @param value int
     * @return un tableau de tuple (i, j) étant les coordonnées dans le plateau correspondant à la valeur "value".
    */
    auto list_of_index = [plateau](int value){
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


Plateau plateauInitial() {
    Plateau plateau;

    plateau = ajouteTuile(plateau);
    plateau = ajouteTuile(plateau);

    return plateau;
}


string dessine(Plateau g) {

    string result = "";
    int max_number = maximumOf(g.grille);
    int lenght_max = len(max_number);

    /* affiche_bord
     * @param t Plateau
     * @param lenght_max int, la longeur du plus grand entier dans t.
     * Ajoute à result une série de '*' pour faire le bords horizontal du plateau
    */
    auto affiche_bord = [&result](Plateau t, int lenght_max) {
        for (int k = 0; k < t.grille[0].size(); k++) {
            for (int l = 0; l < (3 + lenght_max); l++) {
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
    auto set_middle_width = [&result](string expr, int weight){

        for (int k = 0; k < floor( (weight - expr.size()) / 2. ); k++) {

                result += ' ';
            }

            result += expr;

            for (int k = 0; k < ceil( (weight - expr.size()) / 2. ); k++) {
                result += ' ';

            }


    };

    for (int i = 0; i < g.grille.size(); i++) {
        affiche_bord(g, lenght_max);
        
        result += "* ";
        for (int j = 0; j < g.grille[i].size(); j++) {

            string expression = g.grille[i][j] == 0 ? " " : to_string(g.grille[i][j]);

            set_middle_width(expression, lenght_max);

 
            result += " * ";
        }
        result += "\n";
    }

    affiche_bord(g, lenght_max);

    return result;

}


Plateau Transpose(Plateau t) {
    Grille result(t.grille[0].size(), vector<int>(t.grille.size()));


    for (int i = 0; i < t.grille.size(); i++) {
        for (int j = 0; j < t.grille[0].size(); j++) {
            result[j][i] = t.grille[i][j];
        }
    }

    t.grille = result;
    
    return t;
}


Plateau Combine_gauche(Plateau plateau) {

    auto combine_line = [&plateau](vector<int> t) {

        for (int i = 0; i < t.size() - 1; i++) {

            if (t[i] == t[i + 1]) {

                t[i] = 2 * t[i];
                plateau.score += t[i];
                t[i + 1] = 0;

                

            }
            
        }

        return t;

    };

    for (int i = 0; i < plateau.grille.size(); i++) {
        plateau.grille[i] = combine_line(plateau.grille[i]);
    }

    return plateau;
}

Plateau Combine_droite(Plateau plateau) {

    auto combine_line = [&plateau](vector<int> t) {

        for (int i = t.size() - 1; i > 0; i--) {

            if (t[i] == t[i - 1]) {

                t[i] = 2 * t[i];
                plateau.score += t[i];
                t[i - 1] = 0;

            }
            
        }

        return t;

    };

    for (int i = 0; i < plateau.grille.size(); i++) {
        plateau.grille[i] = combine_line(plateau.grille[i]);
    }

    return plateau;
}


Plateau bougeGauche(Plateau t) {

    Grille result = t.grille;
    
    for (auto &i : result) {
        i = strip(i);
        int number_of_zeros = t.grille[0].size() - i.size();


        for (int k = 0; k < number_of_zeros; k++) {
            i.push_back(0);
        }
    }

    t.grille = result;
    
    return t;
}


Plateau bougeDroite(Plateau t) {
    
    Grille result = t.grille;
    
    for (auto &i: result) {
        i = strip(i);
        int number_of_zeros = t.grille[0].size() - i.size();

        for (int k = 0; k < number_of_zeros; k++){
            i.insert(i.begin(), 0);
        }
    }

    t.grille = result;
    
    return t;
}


Plateau deplacementGauche(Plateau t) {

    t = bougeGauche(t);
    t = Combine_gauche(t);
    t = bougeGauche(t);

    return t;
}


Plateau deplacementDroite(Plateau t) {
    
    t = bougeDroite(t);
    t = Combine_droite(t);
    t = bougeDroite(t);

    return t;
}


Plateau deplacementBas(Plateau t) {

    t = Transpose(t);
    t = deplacementDroite(t);
    t = Transpose(t);
    
    return t;
}


Plateau deplacementHaut(Plateau t) {

    t = Transpose(t);
    t = deplacementGauche(t);
    t = Transpose(t);
    
    return t;
}


bool estTermine(Plateau plateau) {
    bool est_termine = true;
    plateau = deplacementGauche(plateau);
    plateau = deplacementDroite(plateau);
    plateau = deplacementHaut(plateau);
    plateau = deplacementBas(plateau);

    for (auto i: plateau.grille) {
        for (auto j: i) {
            if (j == 0) {
                est_termine = false;
                break;
            }
        }
    }

    return est_termine;
}

bool estGagnant(Plateau plateau) {
    bool est_gagnant = false;

    for (auto i: plateau.grille) {
        for (auto j: i) {
            if (j >= 2048) {
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
Plateau deplacement(Plateau plateau, int direction) {

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

