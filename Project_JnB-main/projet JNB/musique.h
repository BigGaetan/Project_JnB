#ifndef MUSIQUE_H
#define MUSIQUE_H

#include <SFML/Audio.hpp>

class Musique {
public:
    Musique();
    void playMusic();
    void stopMusic();

private:
    sf::Music music;
};

#endif // MUSIQUE_H
