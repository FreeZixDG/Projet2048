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
    vector<int> t = {4, 0, 8, 0};
    vector<int> t2 = {0, 0, 8, 0};
    vector<int> t3 = {0, 0, 0, 0};

    CHECK( strip(t) == vector<int>({4, 8}) );
    CHECK( strip(t2) == vector<int>({8}) );
    CHECK( strip(t3) == vector<int>({}) );
};

void testmaximumOf() {

    Plateau t = {
        {0, 0, 4, 2},
        {4, 2, 0, 8},
        {16, 2, 128, 64},
        {2, 4, 0, 8}
    };

    Plateau t2 = {
        {0, 0, 4, 2},
        {4, 2, 0, 8},
        {16, 2, 8, 64},
        {2, 4, 0, 8}
    };

    Plateau t3 = {
        {0, 256, 4, 2},
        {4, 2, 0, 8},
        {16, 256, 8, 64},
        {2, 4, 0, 8}
    };

    CHECK( maximumOf(t) == 128 );
    CHECK( maximumOf(t2) == 64 );
    CHECK( maximumOf(t3) == 256 );

}

void testplateauVide() {
    Plateau t = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    CHECK( plateauVide() == t );
}


void testtireDeuxOuQuatre() {
    int a;

    for ( int i = 0; i < 1000; i++ ) {
        a = tireDeuxOuQuatre();
        CHECK( a == 2 or a == 4 );
    }

};


void testplateauInitial() {
    Plateau t = plateauInitial();
    int how_many_zeros = 0;

    for (auto i: t) {
        for (auto j: i) {
            if(j == 0){
                how_many_zeros++;
            }
        }
    }

    CHECK(t.size() == H and t[0].size() == W);
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

    CHECK(Combine(g) == r);

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
}