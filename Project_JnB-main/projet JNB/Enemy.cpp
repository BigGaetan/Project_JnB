#include "Enemy.h"
#include <cmath>
#include "Bullet.h"



#include <SFML/Graphics.hpp>
const float PI = 3.14159265f;
const float X_THRESHOLD = 100.0f;
const float SCREEN_WIDTH = 800.0f;
const float SCREEN_HEIGHT = 600.0f;
const int MAX_BULLETS = 1;






Enemy::Enemy(float x, float y, float speed, float bulletSpeed) : x(x), y(y), speed(speed), bulletSpeed(bulletSpeed) {    if (enemyTexture.loadFromFile("/home/seatech/Bureau/projet JNB/image/ennemi.png")) {
        enemyTexture.setSmooth(true);
        enemySprite.setTexture(enemyTexture);
    }

    // Autres initialisations nécessaires pour l'ennemi, telles que l'échelle, l'angle initial, etc.
    enemySprite.setPosition(x, y);
    enemySprite.setScale(0.5f, 0.5f); // Par exemple, réglez l'échelle à 50%
    // Autres initialisations nécessaires pour l'apparence de l'ennemi

    // Vous pouvez initialiser d'autres propriétés de l'ennemi ici
}

void Enemy::update() {
    // Logique de mise à jour de l'ennemi, par exemple, le déplacement
    // Vous pouvez ajouter du code ici pour mettre à jour la position de l'ennemi en fonction de la logique du jeu

    // Par exemple, pour faire avancer l'ennemi vers la droite

    enemySprite.setPosition(x, y);

    // Assurez-vous de gérer la logique de l'ennemi en fonction du jeu
}

void Enemy::draw(sf::RenderWindow& window) const {
    // Dessinez l'ennemi et d'autres éléments de l'ennemi si nécessaire
    window.draw(enemySprite);
    // Dessinez d'autres éléments de l'ennemi ici, tels que des accessoires, des armes, etc.
}

void Enemy::shoot(float targetX, float targetY) {
    // Logique pour créer et tirer une balle en direction de (targetX, targetY)
    // Utilisez une méthode similaire à la méthode shoot de la classe Bullet

    // Calculez l'angle de tir en fonction de la position de la cible
    float angle = std::atan2(targetY - y, targetX - x) * 180.0f / PI;

    // Créez et ajoutez une balle
    Bullet bullet(x, y, bulletSpeed, angle);

    // Ajoutez cette balle à une liste de balles pour l'ennemi (à implémenter dans votre jeu)
    // Par exemple, vous pourriez avoir une liste de balles de l'ennemi pour gérer ses tirs.
    // ListeDeBalles.push_back(bullet);

    // Assurez-vous de gérer correctement la liste de balles et leur mise à jour
}


sf::FloatRect Enemy::getCollisionBox() const {
    // Retournez la boîte de collision de l'ennemi
    return enemySprite.getGlobalBounds();
}


void Enemy::takeDamage(int damage) {
    health -= damage;

    // Vérification si l'ennemi est mort
    if (health <= 0) {
        // Implémentez la logique pour la mort de l'ennemi, par exemple, arrêtez son mouvement et marquez-le comme mort
    }
}

bool Enemy::isDead() const {
    return health <= 0;
}
