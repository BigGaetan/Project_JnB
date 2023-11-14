
#include <SFML/Graphics.hpp>
#include "JnB.h"
#include "carte.h"
#include <unordered_map>
#include <iostream>

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
int main() {
// attenttion a modifier plus tard premier terme correspond au tileset et le second a la carte
/////ATTENTION LE FORMAT DE L'IMAGE DU TILESET DOIT etre .PNG
    sf::RenderWindow window(sf::VideoMode(1920, 780), "SFML Window");
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
    JnB jnb;

    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        jnb.update(collisionMap);

        window.clear();
        carte.dessiner(window);
        //décomenter pour que les collision s'affiche /!\ temps de calcule long, frizz le jeu
        //drawCollisionMap(window, collisionMap, 1);
        jnb.draw(window);

        window.display();
    }

    return 0;
}
