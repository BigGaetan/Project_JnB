#ifndef JNB_H_INCLUDED
#define JNB_H_INCLUDED

#include <SFML/Graphics.hpp>

class JnB {
public:
    JnB(); // Constructeur
    void draw(const std::vector<std::vector<int>>& ,sf::RenderWindow &window); // Fonction pour dessiner le personnage dans la fenêtre
    void update(const std::vector<std::vector<int>>& ); // Fonction pour mettre à jour la position du personnage en fonction des touches du clavier

private:
    float x, y;
    float speed;
    sf::RectangleShape character; // Sprite du personnage (un carré noir)
};



#endif // JNB_H_INCLUDED
