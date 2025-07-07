#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    sf::Texture& getTexture(const std::string& filename) {
        if (textures.find(filename) == textures.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile(filename)) {
                throw std::runtime_error("Erreur: Impossible de charger " + filename);
            }
            texture.setSmooth(true);
            textures[filename] = texture;  // Stocke la texture
        }
        return textures[filename];  // Retourne la texture stockée
    }

private:
    std::map<std::string, sf::Texture> textures;
    TextureManager() {}
    ~TextureManager() {}

    TextureManager(const TextureManager&) = delete;
    void operator=(const TextureManager&) = delete;
};

#endif