#include "modele.h"
#include "utils.h"

/* len
 * @param n int, le nombre.
 * @param base int, la base dans laquelle le nombre va etre convertit. (default = 10)
 * @return int, le nombre de chiffre dans le nombre convertit en base "base".
*/
int len(int n, int base) {
    unsigned int number_of_digits = 0;

    do {
        ++number_of_digits;
        n /= base;
    } while(n);

    return number_of_digits;
}

/* strip
 * @param t tableau d'entier
 * @param k int, la valeur qu on veut enlever de t. (default = 0)
 * @return le tableau t auquel on a enlever tous les element valant k.
*/
vector<int> strip(vector<int> t, int k) {

    t.erase(remove(t.begin(), t.end(), k), t.end());
    return t;

}


/*
 * @param t Plateau
 * @return int, La plus grande valeur du Plateau t.
*/
int maximumOf(Plateau t) {
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