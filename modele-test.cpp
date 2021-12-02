#include <iostream>
#include "modele.h"
using namespace std;

/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

void testplateauVide()
{
    Plateau g({
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    });

    CHECK( plateauVide().grille == g.grille );
}

void testtireDeuxOuQuatre()
{
    int a;

    for ( int i = 0; i < 1000; i++ )
    {
        a = tireDeuxOuQuatre();
        CHECK( a == 2 or a == 4 );
    }

}

void testplateauInitial()
{
    Plateau g = plateauInitial();

    int how_many_zeros = 0;

    for (auto i: g.grille)
    {
        for (auto j: i)
        {
            if(j == 0)
            {
                how_many_zeros++;
            }
        }
    }

    CHECK(g.grille.size() == 4 and g.grille[0].size() == 4);
    CHECK(how_many_zeros == 14);
}

void testajouteTuile()
{
    Plateau r({
        {4, 8, 0, 2},
        {4, 2, 2, 8},
        {16, 0, 2, 8},
        {4, 2, 8, 4}
    });

    r = ajouteTuile(r);

    CHECK(
        ((r.grille[0][2] == 2 or r.grille[0][2] == 4) and r.grille[2][1] == 0)
        or ((r.grille[2][1] == 2 or r.grille[2][1] == 4) and r.grille[0][2] == 0)
    );
}

void testdessine()
{

    Plateau g;
    g.grille[0][1] = 2;
    g.grille[1][0] = 4;
    
    string plateau_affiche = dessine(g);

    g.grille[3][2] = 16;

    string plateau_affiche_16 = dessine(g);


    string r = (
        "*****************\n"
        "*   * 2 *   *   * \n"
        "*****************\n"
        "* 4 *   *   *   * \n"
        "*****************\n"
        "*   *   *   *   * \n"
        "*****************\n"
        "*   *   *   *   * \n"
        "*****************\n"
    );

    string r16 = (
        "*********************\n"
        "*    * 2  *    *    * \n"
        "*********************\n"
        "* 4  *    *    *    * \n"
        "*********************\n"
        "*    *    *    *    * \n"
        "*********************\n"
        "*    *    * 16 *    * \n"
        "*********************\n"
    );

    CHECK(plateau_affiche == r);
    CHECK(plateau_affiche_16 == r16);

}

void testTranspose()
{
    Plateau g({
        {4, 2, 2, 0},
        {4, 2, 8, 16},
        {0, 0, 2, 0}
    });

    Plateau r({
        {4, 4, 0},
        {2, 2, 0},
        {2, 8, 2},
        {0, 16, 0}
    });

    CHECK(Transpose(g).grille == r.grille);
}


void testdeplacements()
{
    Plateau g({
        {4, 2, 2, 0},
        {4, 0, 2, 8},
        {2, 0, 2, 0},
        {4, 8, 2, 8},
        {2, 2, 8, 8},
        {0, 4, 4, 4},
        {0, 0, 0, 0}
    });

    Plateau r_gauche({
        {4, 4, 0, 0},
        {4, 2, 8, 0},
        {4, 0, 0, 0},
        {4, 8, 2, 8},
        {4, 16, 0, 0},
        {8, 4, 0, 0},
        {0, 0, 0, 0}
    });

    Plateau r_droite({
        {0, 0, 4, 4},
        {0, 4, 2, 8},
        {0, 0, 0, 4},
        {4, 8, 2, 8},
        {0, 0, 4, 16},
        {0, 0, 4, 8},
        {0, 0, 0, 0}
    });

    Plateau r_haut({
        {8, 2, 4, 16},
        {2, 8, 4, 8},
        {4, 2, 8, 4},
        {2, 4, 4, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    });

    Plateau r_bas({
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {8, 2, 4, 0},
        {2, 8, 4, 8},
        {4, 2, 8, 16},
        {2, 4, 4, 4}
    });

    CHECK(deplacementGauche(g).grille == r_gauche.grille);
    CHECK(deplacementDroite(g).grille == r_droite.grille);
    CHECK(deplacementHaut(g).grille == r_haut.grille);
    CHECK(deplacementBas(g).grille == r_bas.grille);
}


void testestTermine()
{
    Plateau non({
        {2, 2, 8, 2},
        {4, 8, 16, 4},
        {2, 32, 64, 2},
        {16, 128, 16, 4}
    });

    Plateau oui({
        {2, 8, 64, 8},
        {8, 2, 16, 2},
        {4, 32, 256, 8},
        {2, 4, 8, 2}
    });

    CHECK(!estTermine( plateauVide() ));
    CHECK(!estTermine( plateauInitial() ));
    CHECK(!estTermine( non ));
    CHECK(estTermine( oui ));
}

int main()
{
    testplateauVide();
    testtireDeuxOuQuatre();
    testplateauInitial();
    testajouteTuile();
    testdessine();
    testTranspose();
    testdeplacements();
    testestTermine();
    return 0;
}
