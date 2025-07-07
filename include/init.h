#ifndef INIT_H
#define INIT_H

#include "input.h"
#include "gameCheck.h"
#include "render.h"

// Importation modules
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

void init(sf::ContextSettings& options, sf::RenderWindow& window);
void loadFont(std::string fontSource);
void initFont();

void initChar();
void initEnemy();

void loadMusic(sf::Music& music, const sf::String& str);
void initSound();



#endif // !INIT_H

