#include <iostream>
#include "../headers/utils.h"
using namespace std;

/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

void testlen()
{
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

    CHECK( strip(g, 0) == vector<int>({4, 8}) );
    CHECK( strip(g2, 0) == vector<int>({8}) );
    CHECK( strip(g3, 0) == vector<int>({}) );
};

void testmaximumOf() {

    vector<vector<int>> g = {
        {0, 0, 4, 2},
        {4, 2, 0, 8},
        {16, 2, 128, 64},
        {2, 4, 0, 8}
    };

    vector<vector<int>> g2 = {
        {0, 0, 4, 2},
        {4, 2, 0, 8},
        {16, 2, 8, 64},
        {2, 4, 0, 8}
    };

    vector<vector<int>> g3 = {
        {0, 256, 4, 2},
        {4, 2, 0, 8},
        {16, 256, 8, 64},
        {2, 4, 0, 8}
    };

    CHECK( maximumOf(g) == 128 );
    CHECK( maximumOf(g2) == 64 );
    CHECK( maximumOf(g3) == 256 );

}

int main()
{
    testlen();
    teststrip();
    testmaximumOf();
    return 0;
}