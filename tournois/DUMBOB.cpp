#include <fstream>
#include <iostream>
//#include <string>
//#include <stdlib.h>
#include <thread>
//#include <chrono>

#include "../modele.h"
#include "../utils.h"
using namespace std;

// actual best: 27408
// actual best: 35892
// actual best: 36912
// actual best: 50000+
// actual best: 75948

vector<int> extract_numbers(string s)
{
    //printf("\nstring is: %s\n", s.c_str());
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
    
    return plateau;
}

/*choose_random_move
 * @return char, H B G ou D a proba égale (1/4)
*/
int choose_random_move(bool g, bool d, bool h, bool b)
{
    
    int c;
    do
    {
        c = rand() % 4 + 1;
    } while( !(
        (c == GAUCHE and g)
     or (c == DROITE and d)
     or (c == HAUT and h)
     or (c == BAS and b) )
     );
    return c;
}

/* plays a games staring with the first_direction move, and plays randomly until it loses
 * @param plateau Plateau, the starting plateau
 * @param first_direction int, the first direction
 * @return the end score
*/
int play_game(Plateau plateau, int first_direction, int moves_ahead)
{
    int direction = first_direction;
    Grille old_grille;
    bool g = 1;
    bool d = 1;
    bool h = 1;
    bool b = 1;
    int c = 0;
    do
    {
        old_grille = plateau.grille;
        plateau = deplacement(plateau, direction);
        //au prochain coup, on interdit d'aller dans la direction qui n'est pas valide
        if (old_grille == plateau.grille)
        {
            switch (direction)
            {
            case GAUCHE:
                g = 0;
                break;
            
            case DROITE:
                d = 0;
                break;
            
            case HAUT:
                h = 0;
                break;
            
            case BAS:
                b = 0;
                break;
            }
            moves_ahead++;
        }
        
        // si tout va bien, on ajoute une tuile, et on autorise toutes les direction au prochain coup
        else
        {
            plateau = ajouteTuile(plateau);
            g = 1;d = 1;h = 1;b = 1;
        }
        // si bloqué, on arrete
        if (!(g or d or h or b)) break;

        direction = choose_random_move(g, d, h, b);
        moves_ahead--;
    } while (moves_ahead != 0);

    return plateau.score;
}


char strat_brute(Plateau plateau, int number_of_games, int moves_ahead)
{
    int moyenne_G = 0;
    int moyenne_D = 0;
    int moyenne_H = 0;
    int moyenne_B = 0;

    /*ignore the invalid starting position*/
    if (deplacementGauche(plateau).grille == plateau.grille) moyenne_G = -1;
    if (deplacementDroite(plateau).grille == plateau.grille) moyenne_D = -1;
    if (deplacementHaut(plateau).grille == plateau.grille) moyenne_H = -1;
    if (deplacementBas(plateau).grille == plateau.grille) moyenne_B = -1;

    for (int k = 0; k < number_of_games / 4; k++)
    {
        if (moyenne_G != -1) moyenne_G += play_game(plateau, GAUCHE, moves_ahead);
        if (moyenne_D != -1) moyenne_D += play_game(plateau, DROITE, moves_ahead);
        if (moyenne_H != -1) moyenne_H += play_game(plateau, HAUT, moves_ahead);
        if (moyenne_B != -1) moyenne_B += play_game(plateau, BAS, moves_ahead);
    } 

    int max_score = max(max(moyenne_G, moyenne_D), max(moyenne_H, moyenne_B));

    if (max_score == moyenne_G) return 'G';
    if (max_score == moyenne_D) return 'D';
    if (max_score == moyenne_H) return 'H';
    if (max_score == moyenne_B) return 'B';
    else return -1;
}

int count_tiles(Grille grille)
{
    int r = 0;
    for (auto i: grille)
    {
        for (auto j: i)
        {
            if (j != 0) r++;
        }
    }
    return r;
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
            if (estGagnant(plateau))
            {
                won = actual_try;
            }
        }
        if(nb_games == 300) mode = "Easy";
        else if (nb_games == 3000) mode = "Extreme";
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