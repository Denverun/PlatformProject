#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>

#include "globalVariables.h"

struct Enemy {
    std::string name;
    sf::Sprite sprite;
    sf::Vector2f position;
    int health,goldValue,attackValue;
    int id;
    bool doesExist;
    float maxHealth;
    int turnNo;
    bool killed;

    Enemy(){
        name = "default";
        position = {0,0};
        health = 0;
        goldValue = 0;
        attackValue = 0;
    }
    Enemy(const std::string& n, const sf::Texture& texture, sf::Vector2f pos, int hp, int gold, int atk)
        : name(n), position(pos), health(hp), goldValue(gold), attackValue(atk), doesExist(true), maxHealth(hp), turnNo(0), killed(false) {
        sprite.setTexture(texture);
        sf::FloatRect textBounds = sprite.getLocalBounds();
        sprite.setOrigin(textBounds.width/2, textBounds.height/2);
        sprite.setPosition(pos);
    }

    void move(float dx, float dy){
        position.x += dx;
        position.y += dy;
        sprite.setPosition(position);
    };

    sf::Vector2f  getPosition(){
        return position;
    }

    void setPosition(float x, float y){
        position.x = x;
        position.y = y;
        sprite.setPosition(position);
    }

    
    void loseHealth(int x, sf::Text& txt, float posX, float posY){
        health -= x;
        txt.setFont(font); // Changer la police
        txt.setString("-"+std::to_string(x)+" !"); // Changer le texte
        txt.setCharacterSize(30); //La taille
        txt.setFillColor(sf::Color::Red);
        sf::FloatRect textBounds = txt.getLocalBounds();
        txt.setOrigin(textBounds.width / 2, textBounds.height / 2);
        txt.setPosition(posX,posY);
    }
};

#endif // ENEMY_H