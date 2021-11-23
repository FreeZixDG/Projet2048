#include "modele.h"
#include "utils.h"
#include "tests.h"



void testLen() {
    int a = 45641;
    int b_base2 = 5; // 5 base 10 == 101 base 2
    int c = 9;

    CHECK(len(a) == 5);
    CHECK(len(b_base2, 2) == 3);
    CHECK(len(c) == 1);
}

void testStrip() {
    vector<int> t = {4, 0, 8, 0};
    vector<int> t2 = {0, 0, 8, 0};
    vector<int> t3 = {0, 0, 0, 0};

    CHECK( strip(t) == vector<int>({4, 8}) );
    CHECK( strip(t2) == vector<int>({8}) );
    CHECK( strip(t3) == vector<int>({}) );
};

void testMaximumOf() {

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

void testPlateauVide() {
    Plateau t = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    CHECK( plateauVide() == t );
}


void testTireDeuxOuQuatre() {
    int a;

    for ( int i = 0; i < 1000; i++ ) {
        a = tireDeuxOuQuatre();
        CHECK( a == 2 or a == 4 );
    }

};

void testAll() {

    testLen();
    testStrip();
    testMaximumOf();
    testPlateauVide();
    testTireDeuxOuQuatre();
}