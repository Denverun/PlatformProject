#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

#include "character.h"
#include <vector>

class CharacterManager {
private:
    std::vector<Character> characters;

public:
    void addCharacter(const std::string& name, const sf::Texture& texture, sf::Vector2f position, int health) {
        characters.emplace_back(name, texture, position, health); // Comme push back, ajoute un character a la fin du vecteur, mais sans copie, et en appelant le constructeur de character
    }
    void update() {
        for (auto& character : characters) {
            character.move(0.1f, 0.0f); // Exemple de mouvement
        }
    }
    void render(sf::RenderWindow& window) {
        for (const auto& character : characters) {
            window.draw(character.sprite);
        }
    }
    std::vector<Character>& getCharacters() {
        return characters;
    }

    Character& findCharacter(const std::string& name) {
        for (auto& character : characters) {
            if (character.name == name) {
                return character;  // Retourne une référence
            }
        }
        throw std::runtime_error("Personnage introuvable");  // Lève une exception si non trouvé
    }
};

#endif // CHARACTER_MANAGER_H








