#ifndef GAMECHECK_H
#define GAMECHECK_H

#include "gameState.h"
#include "input.h"

#include "character.h"
#include "characterManager.h"
#include "mapvariables.h"

#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

extern bool directionBool;
extern int isMoving,isMovingEnemy;

extern Collect coin1,coin2,coin3,coin4,sausage1,spike1,spike2,burger;

extern sf::Music mainMusic;

void CheckGame(Input &input);

void CheckCollect(Character& character);
void characKey(Character& character, Enemy& enemy, Input& input);
void characMove(Character& character);
void checkBordures(Character& character);
void CheckEnemy(Enemy& enemy, Character& character);
void rotat(sf::Sprite &perso);
void CheckDeath(Character& character);
extern bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);




bool pointInPolygon(const sf::Vector2f& point, const sf::VertexArray& polygon);
void CheckNextMap();
void moveBack(Character& character);

void checkBordures2(Character& character);

void fightPart(Character& character,Enemy& enemy, int mapNumber);

void enemyTurn(Enemy& enemy, Character& character);

enum class dirEtat {
    Left,
    Right
};

extern dirEtat direc;

std::string gachaRes(int n);
std::string gachaResGuaranteed(int n);

#endif // GAMECHECK_H