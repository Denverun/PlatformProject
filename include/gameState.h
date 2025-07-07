#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "character.h"
#include "collect.h"
#include "mapvariables.h"
#include "enemy.h"
#include "globalVariables.h"

#include <iostream>
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

extern int WIN_X; // Définie ici pour pouvoir être utilisé dans main
extern int WIN_Y;
extern int nFPS;

extern float MeanFPS;
extern float globalSound;

extern bool debugMode;

extern bool initTruck;
extern sf::Sprite truck;

extern sf::RectangleShape boutonAccueil, boutonTuto, boutonDefeat; // Posé ici pour pouvoir être utilisé dans input
extern sf::Text txtRespawn;

extern int maxHealth, enemyHealth;
extern Character character1;
extern Enemy volibear;
extern float movSpeed;

extern sf::VertexArray border1,border2,border3,border4,border5,border5wall1,border5wall2,border6,border6wall,border7,border7wall;

extern int coinStock, orbStock;
extern int fractionCoinLost;

extern bool casse;

extern sf::Text lostHealth;
extern sf::Clock healthAnimation;

//------------------------------------------------------------------------

extern int inputValue, buttonValue;
extern sf::RectangleShape boutonVecteur1,boutonVecteur2,boutonVecteur3,boutonConfirmer;
extern int valueVecteur1,valueVecteur2,valueVecteur3;
extern sf::Clock falseClock;

//------------------------------------------------------------------------

extern bool initLol, initLol2, initBonus, initGacha;

extern sf::Clock manqueClock;
extern int manqueCoins;

extern int lolMaptype, championChosen;
extern sf::Texture textureAnivia, textureZed, textureNunu;
extern Character Anivia, Zed, Nunu;
extern sf::Sprite Jax, Katarina, Pantheon, Darius, Ashe, Dragon, Nashor;
extern Enemy Jax1, Katarina1, Pantheon1, Darius1, Ashe1, Dragon1, Nashor1;
extern int top1,top2,mid1,mid2,bot1,bot2,jgl;
extern sf::Sprite Map0,Map1,Map2,Map3,Map4,Map5,Map6,Map7,Map8,Map9,Map10,Map11,VictoryLoL;
extern sf::RectangleShape Nexus,RestartButton,NextPageButton;

extern int Aniviaprice, Zedprice, Nunuprice;
extern sf::Sprite AniviaSprite, ZedSprite, NunuSprite;

extern sf::VertexArray borderL1,borderL2,borderL3,borderL4,borderL5,borderL6,borderL7,borderL8,borderL9,borderL10,borderL11;

extern sf::Clock turnClock;
extern float turnDelay;
extern bool playerTurn;

extern int maxHP;

extern sf::String infoString1, infoString2, infoString3;
extern bool newFight;

extern bool isStun, isStunEnemy, isEscape;

extern bool canMove;
extern sf::CircleShape verifMove;

extern sf::RectangleShape buttonExchangeR, passerBonusR;
extern int goldExchange,orbExchange;
extern sf::Sprite buttonUp,buttonDown, smallGold, smallOrb;

extern sf::Text goldQuantity, orbQuantity;

extern bool afficherMessPauvreGold;
extern sf::Text PauvreGoldTxt;
extern sf::Clock afficheClock;

extern bool firstGainNexus;

//----------------

extern sf::RectangleShape inputZone1,inputZone2,inputZone3,inputZone4;
extern sf::RectangleShape confirmButton1,confirmButton2,confirmButton3,confirmButton4;
extern sf::RectangleShape gachaRect;

extern sf::Sprite gachaAizen4,gachaAizen5,gachaEvoli,gachaRukiasBlade,gachaZed,gachaNeeko,gachaVeigar,gachaMordekaiser,gachaKirby,gachaFrieren;
extern sf::Sprite gachaChar;

extern std::string inputString1,inputString2, inputString3,inputString4;

extern bool confirm1,confirm2,confirm3,confirm4;
extern int writingX;

extern sf::Clock reponseClock;

//-----------------
extern sf::RectangleShape gachaSoloRect,gachaVoirRect;

extern sf::RectangleShape returnHomeGacha,oneMoreSoloRect;
extern sf::Sprite gachaChar2;
extern bool gachaTry;
extern std::vector<std::string> characterList;

extern sf::RectangleShape returnHomeGacha2;
extern std::vector<sf::Sprite> charaList;

extern bool afficherMessPauvre;

extern sf::Sprite goLeft,goRight;
extern int pageGacha;
extern int numberFiveStars;

extern sf::Music mainMusic, hitHacheSound, DRVMusic, MathMusic, LolMapMusic, LolFightMusic1,LolFightMusic2,LolFightMusic3,LolFightMusic4,LolFightMusic5,LolVMusic,LolDMusic,orbExchangeMusic,questionMusic,questionVMusic,AccueilGachaMusic,GachaSound,ListPersoMusic;

bool Alea();
int AleaU(int n);
float AleaUReal(float a, float b);
void SetText(sf::Text &txt, const sf::String &str, const sf::Font &font);
void SetTextMid(sf::Text &txt, int X1, int Y1);

int signe(float x);
Character& chooseChar(int i);
Enemy& chooseEnemy(int i);

void resizeSprite(sf::Sprite& sprite, float targetWidth, float targetHeight);

#endif // !GAMESTATE_H