#include "carte.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
Carte::Carte(const std::string& cheminTileset, const std::string& cheminCarte) : tailleTuile(16) {
    chargerTileset(cheminTileset);
    chargerDonneesCarte(cheminCarte);
}

Carte::~Carte() {
    // Le destructeur prend en charge la libération des ressources allouées
}

void Carte::chargerTileset(const std::string& cheminTileset) {
    if (!tilesetTexture.loadFromFile(cheminTileset)) {
        std::cerr << "Erreur lors du chargement du tileset." << std::endl;
    }

    for (int y = 0; y < 64; ++y) {
        for (int x = 0; x < 192; ++x) {
            sf::IntRect rect(x * tailleTuile, y * tailleTuile, tailleTuile, tailleTuile);
            sf::Sprite tuile(tilesetTexture, rect);
            tuiles.push_back(tuile);
        }
    }
}

void Carte::chargerDonneesCarte(const std::string& cheminCarte) {
    std::ifstream fichierCarte(cheminCarte);
    if (fichierCarte) {
        std::string ligne;
        while (std::getline(fichierCarte, ligne)) {
            std::vector<int> ligneCarte;
            std::stringstream ss(ligne);
            std::string cellule;

            while (std::getline(ss, cellule, ',')) {
                int numeroTuile = std::stoi(cellule);
                ligneCarte.push_back(numeroTuile);
            }

            donneesCarte.push_back(ligneCarte);
        }
    } else {
        std::cerr << "Erreur lors de la lecture du fichier de carte." << std::endl;
    }
}

void Carte::dessiner(sf::RenderWindow& fenetre) {
    for (int y = 0; y < donneesCarte.size(); ++y) {
        for (int x = 0; x < donneesCarte[y].size(); ++x) {
            int numeroTuile = donneesCarte[y][x];
            sf::Sprite& tuile = tuiles[numeroTuile];
            tuile.setPosition(x * tailleTuile, y * tailleTuile);
            fenetre.draw(tuile);
        }
    }
}
//fonction pour creer le masque de collis
std::unordered_map<int, std::vector<std::vector<int>>> createCollisionMasks() {
    std::unordered_map<int, std::vector<std::vector<int>>> collisionMasks;

    // Masque de collision pour la tuile pleine
    std::vector<std::vector<int>> collisionMaskPlein = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    // Masque de collision pour la tuile demi-pleine droite
    std::vector<std::vector<int>> collisionMaskDroite = {
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    // Masque de collision pour la tuile demi-pleine gauche
    std::vector<std::vector<int>> collisionMaskGauche = {
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    // Masque de collision pour la tuile demi-pleine gauche
    std::vector<std::vector<int>> collisionMaskHautGauche = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}
    };
        // Masque de collision pour la tuile cooin-pleine droite
		std::vector<std::vector<int>> collisionMaskHautDroite = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1}
    };
        // Masque de collision pour la tuile demi Haute 
    std::vector<std::vector<int>> collisionMaskDemiHaut = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Masque de collision pour d'autres types de tuiles...
    // Ajoutez ici les masques de collision pour d'autres types de tuiles si nécessaire.

    // Ajout des masques à la map
    collisionMasks.emplace(48, collisionMaskPlein);
    collisionMasks.emplace(53, collisionMaskHautGauche);
    collisionMasks.emplace(54, collisionMaskDemiHaut);
    collisionMasks.emplace(55, collisionMaskHautDroite);
    collisionMasks.emplace(247, collisionMaskPlein);
    collisionMasks.emplace(245, collisionMaskGauche);

    // Ajoutez d'autres masques de collision si nécessaire ici.

    return collisionMasks;
}
//helper
std::vector<std::vector<int>> createEmptyCollisionMask() {
    // Crée un masque de collision 16x16 avec tous les zéros
    std::vector<std::vector<int>> emptyMask(16, std::vector<int>(16, 0));
    return emptyMask;
}

//fonction de création de la map des colisions


std::vector<std::vector<int>> createTileMapCollision(const std::vector<std::vector<int>>& tileMap) {
    // Pour obtenir le nombre de lignes (taille du vecteur extérieur)
    std::size_t numRows = tileMap.size();

    // Pour obtenir le nombre de colonnes (taille d'une ligne, supposons que toutes les lignes ont la même taille)
    std::size_t numCols = (numRows > 0) ? tileMap[0].size() : 0;
 
    std::unordered_map<int, std::vector<std::vector<int>>> collisionMasks = createCollisionMasks();
    std::vector<std::vector<int>> collisionMap(16*numRows, std::vector<int>(16*numCols,1));

    // Créez un masque de collision par défaut (16x16 avec des zéros) pour les tuiles sans masque spécifique
    std::vector<std::vector<int>> defaultCollisionMask(16, std::vector<int>(16, 0));

    // Itérateurs pour suivre la position du masque sur la ligne et la colonne
    size_t i = 0;
    size_t j = 0;

    for (size_t rowIdx = 0; rowIdx < numRows; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < numCols; ++colIdx) {
            const auto& row = tileMap[rowIdx];
            int tileID = row[colIdx];

            std::vector<std::vector<int>> collisionMask;  // Masque de collision pour cette tuile

            if (collisionMasks.find(tileID) != collisionMasks.end()) {
                // Si un masque de collision est défini pour cette tuile, utilisez-le
                collisionMask = collisionMasks[tileID];
            } else {
                // Sinon, utilisez le masque de collision par défaut
                collisionMask = defaultCollisionMask;
            }

            // Écrasez les valeurs existantes dans la carte de collision avec le masque de collision actuel
            for (size_t maskRow = 0; maskRow < collisionMask.size(); ++maskRow) {
                for (size_t maskCol = 0; maskCol < collisionMask[maskRow].size(); ++maskCol) {
                    collisionMap[rowIdx * 16 + maskRow][colIdx * 16 + maskCol] = collisionMask[maskRow][maskCol];
                }
            }
        }
    }

    return collisionMap;
}


// Fonction pour créer le tileMap à partir des valeurs lues à partir du fichier
std::vector<std::vector<int>> createTileMapFromFile(const std::string& filePath) {
    std::vector<std::vector<int>> tileMap;
    std::ifstream inputFile(filePath); // Ouvre le fichier en lecture

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::vector<int> row;
            std::istringstream iss(line);
            std::string value;

            // Parse chaque valeur séparée par une virgule et ajoute à la ligne
            while (std::getline(iss, value, ',')) {
                int tileID = std::stoi(value); // Convertit la chaîne en entier
                row.push_back(tileID);
            }

            // Ajoute la ligne au tileMap
            tileMap.push_back(row);
        }

        inputFile.close(); // Ferme le fichier après la lecture
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }

    return tileMap;
}
