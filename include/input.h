#ifndef INPUT_H
#define INPUT_H

#include "gameState.h"

#include "mapvariables.h"

//#include "render.h"


// Importation modules
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

// Variables globales

// Declaration de classe
class Input{
    struct Button { bool left, right, up, down, attack, escape, spacebar, p, a, z, e, r, d, f; };

public:
    // Prototype Constructeur
    Input();
    
    // Prototypes fonctions de classe
    Button GetButton(void) const;
    void ResetButton(void);

    void InputHandlerHome(sf::Event &event, sf::RenderWindow &window);
    void InputHandlerHomeDR(sf::Event &event, sf::RenderWindow &window);
    void InputHandlerHomeVDR(sf::Event &event, sf::RenderWindow &window);
    void InputHandlerG1DR(sf::Event &event, sf::RenderWindow &window);
    
    void InputHandlerG2DR(sf::Event &event, sf::RenderWindow &window);
    void InputHandlerG3DR(sf::Event &event, sf::RenderWindow &window);
    void InputHandlerG4DR(sf::Event &event, sf::RenderWindow &window);
    void InputHandlerG5DR(sf::Event &event, sf::RenderWindow &window);
    void InputHandlerG6DR(sf::Event &event, sf::RenderWindow &window);
    void InputHandlerG7DR(sf::Event &event, sf::RenderWindow &window);

    void InputHandlerDRV(sf::Event &event, sf::RenderWindow &window);
    void InputHandlerDRDefeat(sf::Event &event, sf::RenderWindow &window);

    void touchesDyn(sf::Event &event, sf::RenderWindow &window);

    void InputHandlerCalculus(sf::Event &event, sf::RenderWindow &window);

    void InputHandlerLoLMap(Character& character, sf::Event &event, sf::RenderWindow &window);
    void InputHandlerLoLFight(Character& character, Enemy& enemy, sf::Event &event, sf::RenderWindow &window);

    void InputHandlerBonus(sf::Event &event, sf::RenderWindow &window);

    void InputHandlerGachaHome(sf::Event &event, sf::RenderWindow &window);
    void InputHandlerGachaPage(sf::Event &event, sf::RenderWindow &window);
    void InputHandlerListChar(sf::Event &event, sf::RenderWindow &window);

private:
    Button button;
};

extern Input input;

void listenInput(sf::RenderWindow &window);
void clicFermer(sf::Event &event, sf::RenderWindow &window);
void changeMap(const EtatM& etat1, const EtatM& etat2, sf::Event& event);

void listenInputMath(sf::RenderWindow &window);
void listenInputLoL(Character& character, sf::RenderWindow &window);

void ClicDroit(sf::Sprite& buttonSprite,  int nextMapL , int nextMapR, Character& character, bool presenceEnnemi, sf::Event &event, sf::RenderWindow &window);
void ClicDroit(sf::RectangleShape& buttonSprite, int nextMap, sf::Event &event, sf::RenderWindow &window);
void ClicGauche(sf::RectangleShape& buttonSprite, int nextMap, int nextGame, sf::Event &event, sf::RenderWindow &window);

void listenInputBonus(sf::RenderWindow &window);
void listenInputGacha(sf::RenderWindow &window);

#endif // !INPUT_H