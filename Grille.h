#ifndef DEF_GRILLE
#define DEF_GRILLE
#include "modele.h"

class Grille
{

    public:
        int score(Plateau plateau);
        void plateau(Plateau plateau);

    private:
        Plateau m_plateau;
        int m_score;
        
        int m_nbFourSpawned;
        int m_brute_score(int n);
};
#endif
