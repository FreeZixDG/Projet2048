#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

#include "primitives.h"

int main()
{
    // Crée une fenêtre de taille 640x480
    RenderWindow window(VideoMode(640, 480), "Ma super fenêtre");

    // Remplit la fenêtre de blanc
    window.clear(Color::White);

    draw_point(window, {120, 5}, Color::Red);

    // Actualise la fenêtre
    window.display();

    // Load a music to play
    Music music;
    if (!music.openFromFile("song.ogg"))
        return -1;
    // Play the music
    music.play();

    // Attend 10 secondes
    sleep(seconds(10));

    return 0;
}

