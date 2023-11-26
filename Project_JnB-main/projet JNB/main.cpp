#include <SFML/Graphics.hpp>
#include "JnB.h"
#include "Bullet.h"
#include "Enemy.h"
#include "carte.h"
#include <unordered_map>
#include <iostream>

const float PI = 3.14159265f;
const float X_THRESHOLD = 100.0f;
const float SCREEN_WIDTH = 800.0f;
const float SCREEN_HEIGHT = 600.0f;
const int MAX_BULLETS = 1;
// code pour creer les collision
void drawCollisionMap(sf::RenderWindow& window, const std::vector<std::vector<int>>& collisionMap, int tileSize) {
    for (size_t i = 0; i < collisionMap.size(); ++i) {
        for (size_t j = 0; j < collisionMap[i].size(); ++j) {
            if (collisionMap[i][j] == 1) {
                sf::RectangleShape rectangle(sf::Vector2f(tileSize, tileSize));
                rectangle.setPosition(j * tileSize, i * tileSize);
                rectangle.setFillColor(sf::Color::Red); // Couleur de la collision
                window.draw(rectangle);
            }
            else{
                sf::RectangleShape rectangle(sf::Vector2f(tileSize, tileSize));
                rectangle.setPosition(j * tileSize, i * tileSize);
                rectangle.setFillColor(sf::Color::Green); // Couleur de la collision
                window.draw(rectangle);
            }
        }
    }
}

//boucle main
int main() {
    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(1920, 780), "Mon Jeu");

    // Création de l'instance du personnage principal (JnB)
    JnB player;
	player.resizeCharacter(0.5,0.5);
    // Création d'un vecteur d'ennemis
    std::vector<Enemy> enemies;

  
    Carte carte("maps/carte2.png","maps/carte3.txt");
        std::vector<std::vector<int>> tileMap = createTileMapFromFile("maps/carte3.txt");
        
        // Chargez le masque de collision
        std::unordered_map<int, std::vector<std::vector<int>>> collisionMasks = createCollisionMasks();
        std::vector<std::vector<int>> collisionMap = createTileMapCollision(tileMap);

         // Affichage de la carte de collision résultante
        /*for (const std::vector<int>& row : collisionMap) {
            for (const int &value : row) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }*/
      // Boucle principale du jeu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Mise à jour de JnB (le joueur)
        player.update(collisionMap, window);

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
        carte.dessiner(window);
        player.draw(window);
	drawBullets(window);
        for (const Enemy& enemy : enemies) {
            enemy.draw(window);
        }
        window.display();
    }

    return 0;
}
