#ifndef COLLECT_H
#define COLLECT_H

#include "textureManager.h"
#include "globalVariables.h"
#include "character.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <cmath>

extern sf::Clock coinAnimation,eatAnimation,spikeAnimation,SpikeClock;
extern sf::Text gainCoin,gainHP,loseHP;
extern sf::Music coinSound,eatSound,hitSound;

class Collect {
private:
    int value;            // Valeur de la pièce
    sf::Vector2f position; // Position sur la carte
    sf::Sprite sprite1;    // Sprite de la pièce
    sf::Sprite sprite2;
    bool exists;

public:
    // Constructeur
    Collect();
    Collect(int val, const sf::Sprite& spriteX, const sf::Sprite& spriteY, sf::Vector2i pos);

    // Getter pour la valeur
    int getValue() const;

    // Getter pour la position
    sf::Vector2f getPosition() const;

    // Getter pour le sprite (pour affichage)
    const sf::Sprite& getSprite1() const;

    // Getter pour le sprite (pour affichage)
    const sf::Sprite& getSprite2() const;

    bool getExists();

    // Setter pour la position
    void setPosition(sf::Vector2f newPos);

    void setSprite(std::string txt, sf::IntRect rect);

    void collect();
    void appear();

    // Dessiner la pièce sur la fenêtre
    void draw(sf::RenderWindow& window) const;

    void getAffiche(sf::Text& txt, std::string str, const sf::Color& color, float posX, float posY);
    void coinGetAffiche(sf::Text& txt);
    void eatGetAffiche(sf::Text& txt, Character& character);
    void spikeGetAffiche(sf::Text& txt, Character& character);

    void addCoins(int &coinStock);
    void addHP(Character& character, int maxHealth);

    void checkCoin(Character& character, int& coinStock);
    void checkEat(Character& character, int maxHealth);
    void checkSpike(Character& character, int maxHealth);

    void drawCollect(float t1, float t2, float time, sf::RenderWindow &window, sf::Text& drawing, sf::Clock& animation);
    void drawSpike(float t1, float t2, float time, sf::RenderWindow &window, sf::Text& drawing, sf::Clock& animation);
};

#endif // !COLLECT_H