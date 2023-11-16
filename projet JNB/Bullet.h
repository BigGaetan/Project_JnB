#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>


class Bullet {
public:
    Bullet(float x, float y, float speed, float angle);

    void update();
    void draw(sf::RenderWindow& window) const;
    bool isOutOfBounds() const;
    sf::FloatRect getCollisionBox() const;

    static float largeurDeLaBalle;
    static float hauteurDeLaBalle;
private:
    float x, y;
    float speed;
    float angle;
    sf::Texture bulletTexture;
    sf::Sprite bulletSprite;

};

#endif
