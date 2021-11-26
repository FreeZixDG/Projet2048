#include "Grille.h"

int Grille::m_brute_score(int n)
{
    if (n < 4 or n & n-1 != 0) {return 0;}
        
    if (n == 4) {
        return 4;
    }

    return n + 2 * m_brute_score(n / 2);
}

void Grille::plateau(Plateau plateau)
{
    m_plateau = plateau;
    m_score = score(m_plateau);
}

int Grille::score(Plateau plateau)
{
    int result = 0;

    for (auto i: plateau) {
        for (int j: i) {
            if (j >= 4) {
                result += m_brute_score(j);
            }
        }
    }

    return result - 4 * m_nbFourSpawned; // On ne compte pas les tuiles "4" qui sont apparues d'elles mêmes.
}