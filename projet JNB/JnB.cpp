#include "JnB.h"
#include <iostream>

JnB::JnB() : x(100), y(100), speed(01) {
    character.setSize(sf::Vector2f(16, 16)); // Taille du carré (à adapter selon vos besoins)
    character.setFillColor(sf::Color::White);
}

void JnB::draw(sf::RenderWindow &window) {
    character.setPosition(x, y);
    window.draw(character);
}

void JnB::update(const std::vector<std::vector<int>>& collisionMap) {
	//std::cerr << x << "  " << y << std::endl;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ( collisionMap[y][x - 1-8] != 1)) {
        x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ( collisionMap[y][x + 1+16] != 1)) {
        x += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ( collisionMap[y - 1-8][x+8] != 1)) {
        y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ( collisionMap[y + 1+16][x+16] != 1)) {
        y += speed;
    }
}

