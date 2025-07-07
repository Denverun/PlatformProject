#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <string>

struct Character {
    std::string name;
    sf::Sprite sprite;
    sf::Vector2f position;
    int health;
    sf::Clock attackCD;
    float speed;
    int id;
    int attack1,attack2,attack3;
    float maxHealth;

    Character();
    Character(const std::string& n, const sf::Texture& texture, sf::Vector2f pos, int hp);
    Character(const std::string& n, const sf::Texture& texture, sf::Vector2f pos, int hp, int iden);

    void move(float dx, float dy);
    void setPosition(float x, float y);
    void attack();

    void attackA();
    void attackZ();
    void attackE();
    void attackR();
    void flash();
    void ignite();
};

struct CharacterLol {
    std::string name;
    sf::Sprite sprite;
    sf::Vector2f position;
    int health;
    sf::Clock attackCD;
    float speed;



    CharacterLol();
    CharacterLol(const std::string& n, const sf::Texture& texture, sf::Vector2f pos, int hp);

    void move(float dx, float dy);
    void setPosition(float x, float y);
    void attack();
};

#endif // CHARACTER_H