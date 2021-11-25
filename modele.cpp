#include "modele.h"
#include "utils.h"


//int COUNT_FOURS_SPAWNS = 0;



Plateau plateauVide() {
    Plateau plateau(H, vector<int>(W));

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

        for (int i = 0; i < plateau.size(); i++) {
            for (int j = 0; j < plateau[0].size(); j++) {
                if (plateau[i][j] == value) {

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

    plateau[i][j] = val;

    //if (val == 4) {COUNT_FOURS_SPAWNS++;}

    return plateau;
}


Plateau plateauInitial() {
    Plateau plateau = plateauVide();
    plateau = ajouteTuile(plateau);

    return plateau;
}


string dessine(Plateau g) {

    string result = "";
    int max_number = maximumOf(g);
    int lenght_max = len(max_number);

    /* affiche_bord
     * @param t Plateau
     * @param lenght_max int, la longeur du plus grand entier dans t.
     * Ajoute à result une série de '*' pour faire le bords horizontal du plateau
    */
    auto affiche_bord = [&result](Plateau t, int lenght_max) {
        for (int k = 0; k < t[0].size(); k++) {
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

    for (int i = 0; i < g.size(); i++) {
        affiche_bord(g, lenght_max);
        
        result += "* ";
        for (int j = 0; j < g[i].size(); j++) {

            string expression = g[i][j] == 0 ? " " : to_string(g[i][j]);

            set_middle_width(expression, lenght_max);

 
            result += " * ";
        }
        result += "\n";
    }

    affiche_bord(g, lenght_max);

    return result;

}


Plateau Transpose(Plateau t) {
    Plateau result(t[0].size(), vector<int>(t.size())); 

    for (int i = 0; i < t.size(); i++) {
        for (int j = 0; j < t[0].size(); j++) {
            result[j][i] = t[i][j];
        }
    }
    
    return result;
}


Plateau Combine_gauche(Plateau t) {

    auto combine_line = [](vector<int> t) {

        for (int i = 0; i < t.size() - 1; i++) {

            if (t[i] == t[i + 1]) {

                t[i] = 2 * t[i];
                t[i + 1] = 0;

            }
            
        }

        return t;

    };

    for (int i = 0; i < t.size(); i++) {
        t[i] = combine_line(t[i]);
    }

    return t;
}

Plateau Combine_droite(Plateau t) {

    auto combine_line = [](vector<int> t) {

        for (int i = t.size(); i > 0; i--) {

            if (t[i] == t[i - 1]) {

                t[i] = 2 * t[i];
                t[i - 1] = 0;

            }
            
        }

        return t;

    };

    for (int i = 0; i < t.size(); i++) {
        t[i] = combine_line(t[i]);
    }

    return t;
}


Plateau bougeGauche(Plateau t) {

    Plateau result = t;
    
    for (auto &i : result) {
        i = strip(i);
        int number_of_zeros = t[0].size() - i.size();


        for (int k = 0; k < number_of_zeros; k++) {
            i.push_back(0);
        }
    }
    
    return result;
}


Plateau bougeDroite(Plateau t) {
    
    Plateau result = t;
    
    for (auto &i: result) {
        i = strip(i);
        int number_of_zeros = t[0].size() - i.size();

        for (int k = 0; k < number_of_zeros; k++){
            i.insert(i.begin(), 0);
        }
    }
    
    return result;
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

    for (auto i: plateau) {
        for (auto j: i) {
            if (j == 0) {
                est_termine = false;
                break;
            }
        }
    }

    return est_termine;
}


int brute_score(int n) {
    if (n < 4 or n & n-1 != 0) {return 0;}
        
    if (n == 4) {
        return 4;
    }

    return n + 2 * brute_score(n / 2);

    
}


int score(Plateau plateau) {

    int result = 0;

    for (auto i: plateau) {
        for (int j: i) {
            if (j >= 4) {
                result += brute_score(j);
            }
        }
    }

    return result; // - 4 * COUNT_FOURS_SPAWNS; // On ne compte pas les tuiles "4" qui sont apparues d'elles mêmes.

}

