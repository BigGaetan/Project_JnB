#include <SFML/Graphics.hpp>
#include "JnB.h"
#include "Bullet.h"
#include "Enemy.h"

const float PI = 3.14159265f;
const float X_THRESHOLD = 100.0f;
const float SCREEN_WIDTH = 800.0f;
const float SCREEN_HEIGHT = 600.0f;
const int MAX_BULLETS = 1;

int main() {
    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mon Jeu");

    // Création de l'instance du personnage principal (JnB)
    JnB player;

    // Création d'un vecteur d'ennemis
    std::vector<Enemy> enemies;

    // Boucle principale du jeu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Mise à jour de JnB (le joueur)
        player.update(window);

        // Mise à jour des ennemis
        for (Enemy& enemy : enemies) {
            enemy.update();
        }

        // Vérification des collisions entre les balles et les ennemis
        player.checkCollisionsWithEnemies(enemies);

        // Suppression des ennemis morts
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
            return enemy.isDead();
        }), enemies.end());

        // Dessin de tout
        window.clear();
        player.draw(window);
        for (const Enemy& enemy : enemies) {
            enemy.draw(window);
        }
        window.display();
    }

    return 0;
}
