#include <vector>
#include <algorithm>
#include <string>


/* len
 * @param n int, le nombre.
 * @param base int, la base dans laquelle le nombre va etre convertit. (default = 10)
 * @return int, le nombre de chiffre dans le nombre convertit en base "base".
*/
int len(int n, int base = 10);

/* strip
 * @param t tableau d'entier
 * @param k int, la valeur qu on veut enlever de t.
 * @return le tableau t auquel on a enlever tous les element valant k.
*/
std::vector<int> strip(std::vector<int> t, int k);

/* Renvoie la plus grande valeur d'une grille
 * @param t Grille
 * @return int, La plus grande valeur du Plateau t.
*/
int maximumOf(std::vector<std::vector<int>> t);

/* Renvoie un tableau contenant chaque partie de [txt], partie délimité à chaque caractère [ch]
 * (fonction trouvée sur internet (https://ideone.com/1RCZM8) puis légèrement modifiée)
 * @param txt const string
 * @param ch char, (default = ' ')
 * @return char, La plus grande valeur du Plateau t.
*/
std::vector<std::string> split(const std::string txt, char ch = ' ');