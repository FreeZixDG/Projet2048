#include "modele.h"
#include "utils.h"

using namespace std;


int len(int n, int base) {
    unsigned int number_of_digits = 0;

    do {
        ++number_of_digits;
        n /= base;
    } while(n);

    return number_of_digits;
}


vector<int> strip(vector<int> t, int k) {

    t.erase(remove(t.begin(), t.end(), k), t.end());
    return t;

}



int maximumOf(Grille t) {
    int r = 0;

    for (auto i: t) {
        for (int j: i) {
            if (r < j) {
                r = j;
            }
        }
    }

    return r;
}


vector<string> split(const string txt, char ch)
{
    vector<string> strs;
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != string::npos )
    {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, min( pos, txt.size() ) - initialPos + 1 ) );

    return strs;
}