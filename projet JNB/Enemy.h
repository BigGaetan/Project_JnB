#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Enemy {
public:
    Enemy(float x, float y, float speed, float bulletSpeed);
    void update();
    void draw(sf::RenderWindow& window) const;
    void shoot(float targetX, float targetY);
    void takeDamage(int damage);

    bool isDead() const;
    sf::FloatRect getCollisionBox() const;

private:
    float x, y;
    float speed;
    float bulletSpeed;
    sf::Sprite enemySprite;
    sf::Texture enemyTexture;
    int health;
};



