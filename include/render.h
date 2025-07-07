#ifndef RENDER_H
#define RENDER_H

#include "gameState.h"
#include "gameCheck.h"

#include "mapvariables.h"
#include "textureManager.h"
#include "collect.h"
#include "character.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

extern sf::Clock globalClockRender; // démarre le chrono

void initRender();
void draw(sf::RenderWindow &window);
void SetRectMid(sf::RectangleShape &rect, int X1, int Y1, const sf::Color color);
void SetSprite(sf::Sprite &sprite, const sf::String &str, const sf::Vector2f &scale);
void SetSpriteMid(sf::Sprite &sprite, const sf::String &str, const sf::Vector2f &scale , int X1, int Y1);
void SetSpriteMidEasy(sf::Texture &texture, sf::Sprite &sprite, const sf::String &str, const sf::Vector2f &scale , int X1, int Y1);
void SetSpriteMidText(sf::Sprite &sprite, const sf::String &txt , const sf::IntRect &rect, const sf::Vector2f &scale , int X1, int Y1);
void SetSpriteMidFromText(sf::Sprite &sprite, sf::Texture& texture, const sf::Vector2f &scale , int X1, int Y1);
void DRLayout(sf::RenderWindow &window, const sf::String &text, int map);
void CheckNextMap();

float fonctionOpacite(float temps,int tempsFull,int tempsProgressif,bool &boolValue);


void initSprites();
void initCollectibles();
void initBorder();

void draw2(sf::RenderWindow &window);
void drawInputValue(sf::Text& valeur, int caseNum, int& valueVecteur, int posX, int posY);

void drawShop(sf::RenderWindow &window);
void drawLol(Character& character, sf::RenderWindow &window);
void drawMap(int etat, sf::Sprite& map, std::string strM, sf::Vector2f scaleM, Character& character, sf::Sprite& enemyS, sf::VertexArray& border, sf::RenderWindow& window, int i, Enemy& enemy);
void drawLolMap2(Character& character, Enemy& enemy, sf::RenderWindow &window);

void initBorder2();
void CheckNextMap2(Character& character);
void CheckNextMap2New(Character& character);

void afficheGachaList(int pageGacha, sf::RenderWindow& window);

#endif // !RENDER_H