#include "modele.h"
#include "utils.h"
#include <curses.h>

using namespace std;


void affiche_en_couleur(vector<string> s)
{
    for (auto i: s)
    {
        if (i == "2")
        {
            attron(COLOR_PAIR(1));
            addstr(i.c_str());
            attroff(COLOR_PAIR(1));
        }

        else if (i == "4")
        {
            attron(COLOR_PAIR(2));
            addstr(i.c_str());
            attroff(COLOR_PAIR(2));
        }
        
        else if (i == "8")
        {
            attron(COLOR_PAIR(3));
            addstr(i.c_str());
            attroff(COLOR_PAIR(3));
        }

        else if (i == "16")
        {
            attron(COLOR_PAIR(4));
            addstr(i.c_str());
            attroff(COLOR_PAIR(4));
        }

        else if (i == "32")
        {
            attron(COLOR_PAIR(5));
            addstr(i.c_str());
            attroff(COLOR_PAIR(5));
        }

        else if (i == "64")
        {
            attron(COLOR_PAIR(6));
            addstr(i.c_str());
            attroff(COLOR_PAIR(6));
        }

        else if (i == "128")
        {
            attron(COLOR_PAIR(1));
            addstr(i.c_str());
            attroff(COLOR_PAIR(1));
        }

        else if (i == "256")
        {
            attron(COLOR_PAIR(2));
            addstr(i.c_str());
            attroff(COLOR_PAIR(2));
        }

        else if (i == "512")
        {
            attron(COLOR_PAIR(3));
            addstr(i.c_str());
            attroff(COLOR_PAIR(3));
        }

        else if (i == "1024")
        {
            attron(COLOR_PAIR(4));
            addstr(i.c_str());
            attroff(COLOR_PAIR(4));
        }

        else if (i == "2048")
        {
            attron(COLOR_PAIR(5));
            addstr(i.c_str());
            attroff(COLOR_PAIR(5));
        }
        
        else
        {
            addstr(i.c_str());
        }
        addch(' ');
    }
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
        printw("Deplacement non-autorise!\n");
        exit(-1);
    }

    if (old_plateau.grille != plateau.grille) {
        plateau = ajouteTuile(plateau);
    }
    
    return plateau;
}

int main()
{
    srand(time(NULL));

    initscr();
    noecho();

    if(has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    
    //Plateau grille = plateauInitial();
    Plateau grille({
        {256, 4, 2, 0},
        {2, 16, 1024, 32},
        {4, 32, 64, 4},
        {32, 128, 8, 2}
    });
    Plateau old_grille;
    string jeu;
    jeu = dessine(grille);
    vector<string> v;
    int c;
    int tries = 0;
    

    keypad(stdscr, true);
    attron(COLOR_PAIR(0));

    v = split(jeu);
    affiche_en_couleur(v);//printw(jeu.c_str());
    
    do
    {

        c = getch();
        old_grille = grille;

        switch (c)
            {
            case KEY_LEFT: // fleche de gauche
                grille = deplacement(grille, GAUCHE);
                break;

            case KEY_RIGHT: // fleche de droite
                grille = deplacement(grille, DROITE);
                break;

            case KEY_UP: // fleche du haut
                grille = deplacement(grille, HAUT);
                break;

            case KEY_DOWN: // fleche du bas
                grille = deplacement(grille, BAS);
                break;
            
            default:
                break;
            }

        if (old_grille.grille != grille.grille)
        {
            tries++;

            if (estTermine(grille))
            {
                break;
            }

            clear();
            jeu = dessine(grille);
            v = split(jeu);
            affiche_en_couleur(v);
            printw("Score: %d\n", grille.score);
            
            if (estGagnant(grille))
            {
                printw("Wow! Tu as obtenu un 2048! (essaie d'aller encore plus loin... :p)");
            }
        }

    } while (c != 27); // Escape

    clear();
    jeu = dessine(grille);
    v = split(jeu);
    affiche_en_couleur(v);//printw(dessine(grille).c_str());
    printw("Jeu termine!\n");
    printw("Votre score est de: %d\n", grille.score);

    printw("Appuyer sur 'echap' pour quitter");
    do
    {
        c = getch();
    } while(c != 27);

    endwin();
    return 0;
}
