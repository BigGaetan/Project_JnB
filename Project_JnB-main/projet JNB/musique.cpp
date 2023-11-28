#include "musique.h"

Musique::Musique() {
    // Chargez votre musique depuis un fichier MP3
    if (!music.openFromFile("musique/musique.wav")) {
        // Gérez l'erreur si la musique ne peut pas être chargée
    }
}

void Musique::playMusic() {
    music.play();
}

void Musique::stopMusic() {
    music.stop();
}
