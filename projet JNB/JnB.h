#ifndef JNB_H_INCLUDED
#define JNB_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Bullet.h"
#include "Enemy.h"







// Définition de la classe JnB
class JnB {
public:
    JnB();
    void draw(sf::RenderWindow& window);
    void update(const std::vector<std::vector<int>>& ,sf::RenderWindow& window);
    void shoot(float angle);

    void updateBullets();
    void takeDamage(int damage);

    void checkCollisionsWithEnemies(std::vector<Enemy>& enemies);

private:
    float x, y;
    float speed;
    int currentFrame;
    int frameCount;
    float pistolScale;
    float pistolDistance;
    float pistolAngle;
    float bulletSpeed;
    int bulletCount;
    int health;

    std::vector<sf::Texture> characterTextures;
    std::vector<sf::Texture> characterTexturesLeft;
    sf::Sprite character;
    int frameWidth;
    sf::Texture pistolTexture;
    sf::Texture pistolLeftTexture;
    sf::Sprite pistol;

    std::vector<Bullet> bullets;

    void updatePistolPosition();
    void drawBullets(sf::RenderWindow& window);
};
#endif // JNB_H_INCLUDED
