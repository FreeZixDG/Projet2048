#include <SFML/Graphics.hpp>
#include <cmath>
#include "primitives.h"
using namespace sf;
using namespace std;  // Pour les exceptions dans la version distribuée

int main()
{
    int delai = 1;
    RenderWindow window(VideoMode(900, 480), "Ma super fenêtre");
    window.clear(Color::Green);

    // Dessine un point noir de coordonnées (418, 143)
    draw_point(window, {418, 143}, Color::Black );            //Correction
                                                            //FinCorrection
    window.display();
    sleep(seconds(delai));

    // Dessine un segment blanc entre les points (100,200) et (200,200)
    // À faire
    
    window.display();
    sleep(seconds(delai));

    // Dessine un segment rouge entre les points (200,300) et (200,400)
    // À faire

    window.display();
    sleep(seconds(delai));

    // Dessine un rectangle horizontal vide de sommets diagonaux (200,200) et (400,300) et de contour rouge
    // À faire

    window.display();
    sleep(seconds(delai));

    // Dessine un rectangle horizontal plein noir de sommets diagonaux (400,150) et (500,200)
    // À faire

    window.display();
    sleep(seconds(delai));

    // Dessine un segment rouge entre les points (400,300) et (500,400)
    // À faire

    window.display();
    sleep(seconds(delai));

    // Dessine un cercle noir de centre (415,145) et de rayon 10
    // À faire

    window.display();
    sleep(seconds(delai));

    // Dessine un disque jaune de centre (700, 100) et de rayon 50
    // À faire

    window.display();
    sleep(seconds(10*delai));
    return 0;
}
