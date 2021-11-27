#include <vector>

typedef std::vector<std::vector<int>> Grille;

class Plateau
{
    public:
        Plateau();
        Plateau(Grille g, int s = 0);
        Grille grille;
        int score;
};