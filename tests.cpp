#include "modele.h"
#include "utils.h"
#include "tests.h"
#include <curses.h>
#define CHECK(test) if (!(test)) printw("Test failed in function '%s' line %d : %s\n", __FUNCTION__, __LINE__, #test)


void testlen() {
    int a = 45641;
    int b_base2 = 5; // 5 base 10 == 101 base 2
    int c = 9;

    CHECK(len(a) == 5);
    CHECK(len(b_base2, 2) == 3);
    CHECK(len(c) == 1);
}

void teststrip() {
    vector<int> g = {4, 0, 8, 0};
    vector<int> g2 = {0, 0, 8, 0};
    vector<int> g3 = {0, 0, 0, 0};

    CHECK( strip(g) == vector<int>({4, 8}) );
    CHECK( strip(g2) == vector<int>({8}) );
    CHECK( strip(g3) == vector<int>({}) );
};

void testmaximumOf() {

    Grille g = {
        {0, 0, 4, 2},
        {4, 2, 0, 8},
        {16, 2, 128, 64},
        {2, 4, 0, 8}
    };

    Grille g2 = {
        {0, 0, 4, 2},
        {4, 2, 0, 8},
        {16, 2, 8, 64},
        {2, 4, 0, 8}
    };

    Grille g3 = {
        {0, 256, 4, 2},
        {4, 2, 0, 8},
        {16, 256, 8, 64},
        {2, 4, 0, 8}
    };

    CHECK( maximumOf(g) == 128 );
    CHECK( maximumOf(g2) == 64 );
    CHECK( maximumOf(g3) == 256 );

}

void testplateauVide() {
    Plateau g({
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    });

    CHECK( plateauVide().grille == g.grille );
}


void testtireDeuxOuQuatre() {
    int a;

    for ( int i = 0; i < 1000; i++ ) {
        a = tireDeuxOuQuatre();
        CHECK( a == 2 or a == 4 );
    }

}


void testplateauInitial() {
    Plateau g = plateauInitial();

    int how_many_zeros = 0;

    for (auto i: g.grille) {
        for (auto j: i) {
            if(j == 0){
                how_many_zeros++;
            }
        }
    }

    CHECK(g.grille.size() == H and g.grille[0].size() == W);
    CHECK(H*W == how_many_zeros + 1);
}

void testajouteTuile() {
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

void testdessine() {
    if (W == 4 and H == 4) {

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
}

void testTranspose() {
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

void testCombine() {
    Plateau g({
        {4, 2, 2, 0},
        {4, 0, 8, 8},
        {2, 0, 2, 0},
        {4, 8, 0, 0},
    });

    Plateau r({
        {4, 4, 0, 0},
        {4, 0, 16, 0},
        {2, 0, 2, 0},
        {4, 8, 0, 0},
    });

    CHECK(Combine_gauche(g).grille == r.grille);

}

void testbouge() {

    Plateau g({
        {4, 2, 2, 0},
        {4, 0, 2, 8},
        {2, 0, 2, 0},
        {4, 8, 2, 4},
        {0, 0, 0, 0},
    });

    Plateau r_gauche({
        {4, 2, 2, 0},
        {4, 2, 8, 0},
        {2, 2, 0, 0},
        {4, 8, 2, 4},
        {0, 0, 0, 0}
    });

    Plateau r_droite({
        {0, 4, 2, 2},
        {0, 4, 2, 8},
        {0, 0, 2, 2},
        {4, 8, 2, 4},
        {0, 0, 0, 0}
    });

    CHECK(bougeGauche(g).grille == r_gauche.grille);
    CHECK(bougeDroite(g).grille == r_droite.grille);

}

void testdeplacements() {
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

void testestTermine() {
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

void testall() {

    testlen();
    teststrip();
    testmaximumOf();
    testplateauVide();
    testtireDeuxOuQuatre();
    testplateauInitial();
    testajouteTuile();
    testdessine();
    testTranspose();
    testCombine();
    testbouge();
    testdeplacements();
    testestTermine();

}