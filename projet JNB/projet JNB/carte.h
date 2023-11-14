#ifndef CARTE_INCLUDED
#define CARTE_INCLUDED


#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
class Carte {
public:
    Carte(const std::string& cheminTileset, const std::string& cheminCarte);
    Carte(const Carte& autre);
    Carte& operator=(const Carte& autre);
    ~Carte();

    void dessiner(sf::RenderWindow& fenetre);

private:
    void chargerTileset(const std::string& cheminTileset);
    void chargerDonneesCarte(const std::string& cheminCarte);

    sf::Texture tilesetTexture;
    std::vector<sf::Sprite> tuiles;
    std::vector<std::vector<int>> donneesCarte;
    int tailleTuile;
};




// Classe Tile (Tuile) :
// Représente une tuile individuelle dans le jeu.
// Chaque tuile a une texture associée et un masque de collision spécifique.
class Tile {
public:
    // Constructeur de la classe Tile.
    // Prend une texture et un masque de collision comme paramètres.

    Tile(const sf::Texture& texture, const std::vector<std::vector<int>>& collisionMask);

    // Vérifie si les coordonnées spécifiées entrent en collision avec cette tuile.
    bool isCollision(int x, int y) const;

private:
    sf::Sprite sprite; // La texture de la tuile.
    std::vector<std::vector<int>> collisionMask; // Masque de collision de la tuile.
};


std::unordered_map<int, std::vector<std::vector<int>>> createCollisionMasks();
std::vector<std::vector<int>> createTileMapCollision(const std::vector<std::vector<int>>& tileMap) ;
std::vector<std::vector<int>> createTileMapFromFile(const std::string& filePath);
std::vector<std::vector<int>> createEmptyCollisionMask();
// Classe TileMap (Carte de Tuiles) :
// Représente l'ensemble de la carte de jeu composée de tuiles.
// Gère les collisions pour l'ensemble de la carte de tuiles en utilisant les masques de collision des tuiles individuelles.
class TileMap {
public:
    // Constructeur de la classe TileMap.
    // Prend les ID des tuiles, le dictionnaire de tuiles et la taille des tuiles comme paramètres.
    TileMap(const std::vector<std::vector<int>>& tileIDs, const std::unordered_map<int, Tile>& tileDictionary, int tileSize);

    // Vérifie si les coordonnées spécifiées entrent en collision avec la carte de tuiles.
    bool isCollision(int x, int y) const;

private:
    std::vector<std::vector<int>> tileIDs; // ID des tuiles composant la carte.
    std::unordered_map<int, Tile> tileDictionary; // Dictionnaire de tuiles avec ID associés aux instances de la classe Tile.
    int tileSize; // Taille des tuiles dans la carte.
};




#endif // CARTE_INCLUDED
