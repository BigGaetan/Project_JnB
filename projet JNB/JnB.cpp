#include "JnB.h"
#include <cmath>
#include "Bullet.h"


#include <SFML/Graphics.hpp>


const float PI = 3.14159265f;
const float X_THRESHOLD = 100.0f;
const float SCREEN_WIDTH = 800.0f;
const float SCREEN_HEIGHT = 600.0f;
const int MAX_BULLETS = 1;
const int damageDeLaBalle = 1; // Ajustez la valeur selon vos besoins
// Définition de la classe Bullet




JnB::JnB() : x(100), y(100), speed(0.7), currentFrame(0), frameCount(8), pistolScale(0.03f), pistolDistance(50.0f), pistolAngle(10.0f), bulletSpeed(0.8), health(3) {
    characterTextures.resize(8);
    characterTexturesLeft.resize(8);

    for (int i = 0; i < 8; i++) {
        characterTextures[i].loadFromFile("/home/seatech/Bureau/projet JNB/image/character" + std::to_string(i + 1) + ".png");
        characterTexturesLeft[i].loadFromFile("/home/seatech/Bureau/projet JNB/image/character_left" + std::to_string(i + 1) + ".png");
    }

    character.setTexture(characterTextures[0]);
    frameWidth = characterTextures[0].getSize().x / frameCount;

    pistolTexture.loadFromFile("/home/seatech/Bureau/projet JNB/image/pistol.png");

    pistolLeftTexture.loadFromFile("/home/seatech/Bureau/projet JNB/image/pistol_left.png");

    pistol.setTexture(pistolTexture);
    pistol.setScale(pistolScale, pistolScale);

    updatePistolPosition();
}

void JnB::draw(sf::RenderWindow& window) {
    character.setPosition(x, y);
    window.draw(character);
    window.draw(pistol);
    drawBullets(window);

     // Affichage des points de vie
    sf::Font font;
    font.loadFromFile("/home/seatech/Bureau/projet JNB/arial.ttf"); // Vous devrez fournir le fichier de police

    sf::Text healthText;
    healthText.setFont(font);
    healthText.setCharacterSize(24);
    healthText.setFillColor(sf::Color::Red);
    healthText.setPosition(10, 10);
    healthText.setString("Health: " + std::to_string(health));
    window.draw(healthText);
}

void JnB::update(const std::vector<std::vector<int>>& collisionMap, sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ( collisionMap[y][x - 1-8] != 1)) {
        x -= speed;
        frameWidth = characterTexturesLeft[0].getSize().x / frameCount;
        character.setTexture(characterTexturesLeft[currentFrame]);
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ( collisionMap[y][x + 1+16] != 1))  {
        x += speed;
        frameWidth = characterTextures[0].getSize().x / frameCount;
        character.setTexture(characterTextures[currentFrame]);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ( collisionMap[y - 1-8][x+8] != 1)) {
        y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ( collisionMap[y + 1+16][x+16] != 1)) {
        y += speed;
    }

    int newFrame = static_cast<int>(x / X_THRESHOLD);
    if (newFrame != currentFrame) {
        currentFrame = newFrame;
    }

    // Changer la texture du pistolet en fonction de la direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        pistol.setTexture(pistolLeftTexture);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pistol.setTexture(pistolTexture);
    }

    // Obtenir la position de la souris par rapport à la fenêtre
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
    sf::Vector2f direction = mousePosition - sf::Vector2f(x, y);
    pistolAngle = std::atan2(direction.y, direction.x) * 180.0f / PI;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot(pistolAngle);
    }

    updatePistolPosition();
    updateBullets();
}

void JnB::shoot(float angle) {
    if (bulletCount < MAX_BULLETS) {
        Bullet bullet(pistol.getPosition().x, pistol.getPosition().y, bulletSpeed, angle);
        bullets.push_back(bullet);
        bulletCount++;
    }
}

void JnB::updateBullets() {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i].update();
        if (bullets[i].isOutOfBounds()) {
            bullets.erase(bullets.begin() + i);
            i--;
            bulletCount--; // Décrémentez le compteur
        }
    }
}

void JnB::drawBullets(sf::RenderWindow& window) {
    for (const Bullet& bullet : bullets) {
        bullet.draw(window);
    }
}

void JnB::updatePistolPosition() {
    // Mise à jour de la position du pistolet en fonction de l'angle
    float pistolX = x + pistolDistance * std::cos(pistolAngle * PI / 180.0f);
    float pistolY = y + pistolDistance * std::sin(pistolAngle * PI / 180.0f);
    pistol.setPosition(pistolX, pistolY);
}

// Ajoutez la fonction takeDamage pour gérer les dégâts
void JnB::takeDamage(int damage) {
    health -= damage;

    if (health <= 0) {
        // Implémentez la logique pour la mort du personnage
    }
}

void JnB::checkCollisionsWithEnemies(std::vector<Enemy>& enemies) {
    for (int i = 0; i < bullets.size(); i++) {
        sf::FloatRect bulletBox = bullets[i].getCollisionBox();

        for (int j = 0; j < enemies.size(); j++) {
            sf::FloatRect enemyBox = enemies[j].getCollisionBox();

            if (bulletBox.intersects(enemyBox)) {
                // Collision détectée entre la balle et l'ennemi
                enemies[j].takeDamage(damageDeLaBalle);
                bullets.erase(bullets.begin() + i);
                i--; // Décrémentez le compteur
            }
        }
    }
}
