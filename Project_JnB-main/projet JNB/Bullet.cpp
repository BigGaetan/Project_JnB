#include "Bullet.h"
#include <cmath>
#include <SFML/Graphics.hpp>

const float PI = 3.14159265f;
const float X_THRESHOLD = 100.0f;
const float SCREEN_WIDTH = 800.0f;
const float SCREEN_HEIGHT = 600.0f;
const int MAX_BULLETS = 1;



Bullet::Bullet(float x, float y, float speed, float angle) : x(x), y(y), speed(speed), angle(angle) {
    // Charger la texture de la balle
    if (bulletTexture.loadFromFile("/home/seatech/Bureau/projet JNB/image/bullet1.png")) {
        bulletTexture.setSmooth(true);
        bulletSprite.setTexture(bulletTexture);
    }

    bulletSprite.setPosition(x, y);
    float scaleFactor = 0.01f; // Vous pouvez ajuster cette échelle selon vos besoins
    bulletSprite.setScale(scaleFactor, scaleFactor);


    largeurDeLaBalle = bulletTexture.getSize().x;
    hauteurDeLaBalle = bulletTexture.getSize().y;
}

void Bullet::update() {
    float radians = angle * PI / 180.0f;
    x += speed * std::cos(radians);
    y += speed * std::sin(radians);
    bulletSprite.setPosition(x, y);
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(bulletSprite);
}

bool Bullet::isOutOfBounds() const {
    return (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT);
}

float Bullet::largeurDeLaBalle = 0.0f; // Initialisée plus tard après avoir obtenu la largeur de la texture
float Bullet::hauteurDeLaBalle = 0.0f; // Initialisée plus tard après avoir obtenu la hauteur de la texture

sf::FloatRect Bullet::getCollisionBox() const {
    return sf::FloatRect(x, y, largeurDeLaBalle, hauteurDeLaBalle);
}
