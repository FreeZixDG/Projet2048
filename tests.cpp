#include "modele.h"
#include "utils.h"
#include "tests.h"



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

    Plateau g = {
        {0, 0, 4, 2},
        {4, 2, 0, 8},
        {16, 2, 128, 64},
        {2, 4, 0, 8}
    };

    Plateau g2 = {
        {0, 0, 4, 2},
        {4, 2, 0, 8},
        {16, 2, 8, 64},
        {2, 4, 0, 8}
    };

    Plateau g3 = {
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
    Plateau g = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    CHECK( plateauVide() == g );
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

    for (auto i: g) {
        for (auto j: i) {
            if(j == 0){
                how_many_zeros++;
            }
        }
    }

    CHECK(g.size() == H and g[0].size() == W);
    CHECK(H*W == how_many_zeros + 1);
}

void testajouteTuile() {
    Plateau r = {
        {4, 8, 0, 2},
        {4, 2, 2, 8},
        {16, 0, 2, 8},
        {4, 2, 8, 4}
    };

    r = ajouteTuile(r);

    CHECK(
        ((r[0][2] == 2 or r[0][2] == 4) and r[2][1] == 0)
        or ((r[2][1] == 2 or r[2][1] == 4) and r[0][2] == 0)
    );
}

void testdessine() {
    if (W == 4 and H == 4) {

        Plateau g = plateauVide();
        g[0][1] = 2;
        g[1][0] = 4;
        
        string plateau_affiche = dessine(g);

        g[3][2] = 16;

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
    Plateau g = {
        {4, 2, 2, 0},
        {4, 2, 8, 16},
        {0, 0, 2, 0}
    };

    Plateau r = {
        {4, 4, 0},
        {2, 2, 0},
        {2, 8, 2},
        {0, 16, 0}
    };

    CHECK(Transpose(g) == r);
}

void testCombine() {
    Plateau g = {
        {4, 2, 2, 0},
        {4, 0, 8, 8},
        {2, 0, 2, 0},
        {4, 8, 0, 0},
    };

    Plateau r = {
        {4, 4, 0, 0},
        {4, 0, 16, 0},
        {2, 0, 2, 0},
        {4, 8, 0, 0},
    };

    CHECK(Combine_gauche(g) == r);

}

void testbouge() {

    Plateau g = {
        {4, 2, 2, 0},
        {4, 0, 2, 8},
        {2, 0, 2, 0},
        {4, 8, 2, 4},
        {0, 0, 0, 0},
    };

    Plateau r_gauche = {
        {4, 2, 2, 0},
        {4, 2, 8, 0},
        {2, 2, 0, 0},
        {4, 8, 2, 4},
        {0, 0, 0, 0}
    };

    Plateau r_droite = {
        {0, 4, 2, 2},
        {0, 4, 2, 8},
        {0, 0, 2, 2},
        {4, 8, 2, 4},
        {0, 0, 0, 0}
    };

    CHECK(bougeGauche(g) == r_gauche);
    CHECK(bougeDroite(g) == r_droite);

}

void testdeplacements() {
    Plateau g = {
        {4, 2, 2, 0},
        {4, 0, 2, 8},
        {2, 0, 2, 0},
        {4, 8, 2, 8},
        {2, 2, 8, 8},
        {0, 4, 4, 4},
        {0, 0, 0, 0}
    };

    Plateau r_gauche = {
        {4, 4, 0, 0},
        {4, 2, 8, 0},
        {4, 0, 0, 0},
        {4, 8, 2, 8},
        {4, 16, 0, 0},
        {8, 4, 0, 0},
        {0, 0, 0, 0}
    };

    Plateau r_droite = {
        {0, 0, 4, 4},
        {0, 4, 2, 8},
        {0, 0, 0, 4},
        {4, 8, 2, 8},
        {0, 0, 4, 16},
        {0, 0, 4, 8},
        {0, 0, 0, 0}
    };

    Plateau r_haut = {
        {8, 2, 4, 16},
        {2, 8, 4, 8},
        {4, 2, 8, 4},
        {2, 4, 4, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    Plateau r_bas = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {8, 2, 4, 0},
        {2, 8, 4, 8},
        {4, 2, 8, 16},
        {2, 4, 4, 4}
    };

    CHECK(deplacementGauche(g) == r_gauche);
    CHECK(deplacementDroite(g) == r_droite);
    CHECK(deplacementHaut(g) == r_haut);
    CHECK(deplacementBas(g) == r_bas);
}

void testestTermine() {
    Plateau non = {
        {2, 2, 8, 2},
        {4, 8, 16, 4},
        {2, 32, 64, 2},
        {16, 128, 16, 4}
    };

    Plateau oui = {
        {2, 8, 64, 8},
        {8, 2, 16, 2},
        {4, 32, 256, 8},
        {2, 4, 8, 2}
    };

    CHECK(!estTermine( plateauVide() ));
    CHECK(!estTermine( plateauInitial() ));
    CHECK(!estTermine( non ));
    CHECK(estTermine( oui ));
}

void testbrute_score() {

    /*Invalid arguments return 0*/
    CHECK(brute_score(-1) == 0);
    CHECK(brute_score(0) == 0);
    CHECK(brute_score(1) == 0);
    CHECK(brute_score(2) == 0);
    CHECK(brute_score(3) == 0);
    CHECK(brute_score(5) == 0);
    CHECK(brute_score(47) == 0);
    CHECK(brute_score(264) == 0);
    CHECK(brute_score(4862) == 0);
    CHECK(brute_score(4867) == 0);
    /*---------------------------*/

    CHECK(brute_score(4) == 4);
    CHECK(brute_score(8) == 16);
    CHECK(brute_score(16) == 48);
    CHECK(brute_score(32) == 128);
    CHECK(brute_score(64) == 320);

}

void testscore() {
    Plateau g = {
        {0, 0, 2, 0}, // 0 pts
        {0, 0, 4, 4}, // 8 pts
        {0, 8, 0, 0}, // 16 pts
        {0, 0, 0, 0}, // 0 pts
    };

    printw("%d", score(g));

    CHECK(score(g) == 24);
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
    //testbrute_score();
    testscore();

}