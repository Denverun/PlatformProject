#include "character.h"

// Constructeur de Character

Character::Character()
    : name("0"), position({0,0}), health(0), speed(0) {
    sf::Texture t;
    sprite.setTexture(t);
    sprite.setPosition(position);
}

Character::Character(const std::string& n, const sf::Texture& texture, sf::Vector2f pos, int hp)
    : name(n), position(pos), health(hp), speed(0), maxHealth(hp) {
    sprite.setTexture(texture);
    sf::FloatRect textBounds = sprite.getLocalBounds();
    sprite.setOrigin(textBounds.width/2, textBounds.height/2);
    sprite.setPosition(pos);
    attackCD.restart();
}

Character::Character(const std::string& n, const sf::Texture& texture, sf::Vector2f pos, int hp, int iden)
    : name(n), position(pos), health(hp), speed(0), id(iden), maxHealth(hp) {
    sprite.setTexture(texture);
    sf::FloatRect textBounds = sprite.getLocalBounds();
    sprite.setOrigin(textBounds.width/2, textBounds.height/2);
    sprite.setPosition(pos);
    attackCD.restart();
}

void Character::move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
    sprite.setPosition(position);
}

void Character::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    sprite.setPosition(position);
}

void Character::attack() {
    attackCD.restart();
}