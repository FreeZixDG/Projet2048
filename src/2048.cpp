#include <curses.h>
#include "../headers/utils.h"
#include "../headers/BOB.h"

using namespace std;


void affiche_en_couleur(string s)
{

    vector<string> v = split(s);


    for (auto i: v)
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
    bool OPTION_IA_HELP = 0;
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
    keypad(stdscr, true);
    attron(COLOR_PAIR(0));

    int c;

MENU:
    do
    {
        clear();
        printw("Bienvenue dans le jeu 2048 !\n");
        printw("[1] Jouer\n");
        printw("[2] Options\n");
        printw("[0] Quitter\n");
        c = getch();

        switch (c)
        {
        case 48:
            exit(0);
        
        case 49:
            goto JEU;
            break;

        case 50:
            printw("option");
            break;
        
        default:
            break;
        }
        
        


    } while (c < 48 or c > 50); // echap

OPTIONS:
    do
    {
        
        clear();
        printw("Options:\n");
        printw("[1] Aide de BOB (il est fort) (%s)\n", OPTION_IA_HELP ? "ON": "OFF");
        printw("[0] Retour\n");
        c = getch();

        switch (c)
        {
        case 48:
            goto MENU;
        
        case 49:
            OPTION_IA_HELP = !OPTION_IA_HELP;
            goto OPTIONS;
            break;
        
        default:
            break;
        }
        
    } while (c < 48 or c > 49); // echap
    
JEU:
    Plateau plateau = plateauInitial();
    Plateau old_plateau;
    int tries = 0;
    bool REVEAL = 0;
    bool AUTO_PLAY = 0;
    char ch;
    clear();
    affiche_en_couleur( dessine(plateau) );
    printw("\tScore: %d\n", plateau.score);

    if (OPTION_IA_HELP)
        {
            printw("L'aide est active !\n");
            printw("Appuies sur R pour reveler ou cacher les indices que te donne BOB.\n");
            printw("Appuies sur P pour laisser BOB jouer a ta place! (tu peux reprendre la main quand tu veux)");
        }
    
    do
    {
        c = getch();
        old_plateau = plateau;

        switch (c)
            {
            case KEY_LEFT: // fleche de gauche
                plateau = deplacement(plateau, GAUCHE);
                break;

            case KEY_RIGHT: // fleche de droite
                plateau = deplacement(plateau, DROITE);
                break;

            case KEY_UP: // fleche du haut
                plateau = deplacement(plateau, HAUT);
                break;

            case KEY_DOWN: // fleche du bas
                plateau = deplacement(plateau, BAS);
                break;

            case 'r':
                if (OPTION_IA_HELP)
                {
                    REVEAL = !REVEAL;
                    break;
                }
            case 'p':
                if (OPTION_IA_HELP)
                {
                    ch = strat_brute(plateau, 200, 10);
                    switch (ch)
                    {
                    case 'G': plateau = deplacement(plateau, GAUCHE); break;
                    case 'D': plateau = deplacement(plateau, DROITE); break;
                    case 'H': plateau = deplacement(plateau, HAUT); break;
                    case 'B': plateau = deplacement(plateau, BAS); break;
                    default: break;
                    }
                    break;
                }
            default:
                break;
            }

        if (old_plateau.grille != plateau.grille)
        {
            tries++;

            if (estTermine(plateau))
            {
                break;
            }

            clear();
            affiche_en_couleur( dessine(plateau) );
            printw("\tScore: %d\n", plateau.score);
            
            if (estGagnant(plateau))
            {
                printw("Wow! Tu as obtenu un 2048! (essaie d'aller encore plus loin... :p)\n");
            }
        
        }
        if (REVEAL)
        {
            printw("\rBOB pense: %c\n", strat_brute(plateau, 300, 20));
        }

    } while (c != 27); // echap

    clear();

    affiche_en_couleur( dessine(plateau) );

    printw("\tJeu termine!\n");
    printw("Votre score est de: %d\n", plateau.score);

    printw("Veux tu rejouer [1] ou retourner au menu [0] ?");
    do
    {
        c = getch();
        switch (c)
        {
        case 48:
            goto MENU;
            break;
        
        case 49:
            goto JEU;
            break;
        
        default:
            break;
        }
    } while(c != 27);

    endwin();
    return 0;
}
