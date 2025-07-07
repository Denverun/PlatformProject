#include "init.h"
// Définition fonctions importantes

//Cara
int originX = 659-598, originY = 388-270;
sf::Texture texture1;
sf::Vector2f position1 = {float(WIN_X)/2,float(WIN_Y)/2};
std::string name1 = "Barbarian";

void init(sf::ContextSettings& options, sf::RenderWindow& window){
    cout << "La compilation et l'exe sont : " << "Ok" << endl;
    printf("1, 2, 3, GO !\n");

    // Options de la fenêtre
    options.antialiasingLevel = 8; //lisser les formes
    // Création d'une fenêtre de type RenderWindow
    window.create(sf::VideoMode(WIN_X, WIN_Y,nFPS), "DreamStone", sf::Style::Default, options);
    // Activation du vsync
    window.setVerticalSyncEnabled(true);

    initFont(); // Init de police
    initChar(); // Init de personnage
    initEnemy();
    initRender(); // Init de l'affichage
    initSound();

    verifMove.setFillColor(sf::Color::Green);
    verifMove.setPosition({100,50});
}

// Définition fonctions utilitaires
void loadFont(std::string fontSource){ // Changement police
    if(!font.loadFromFile(fontSource)){
        cout << "Erreur chargement police" << endl;
    }
    cout << "Police importee" << endl;
}

void initFont(){
    loadFont("res/Barlow/Barlow-Bold.ttf"); // Importation de la police
}

void initChar(){
    texture1.loadFromFile("res/images/DR/persos.png");
    texture1.setSmooth(true);
    character1=Character(name1,texture1,position1,maxHealth);

    character1.sprite.setTextureRect(sf::IntRect(598,271,741-598,418-271));
    character1.sprite.scale({1.3,1.3});
    character1.sprite.setOrigin(originX,originY);
}

void initEnemy(){
    volibear=Enemy("Volibear",texture1,{float(WIN_X/2), float(WIN_Y/2)},enemyHealth,3,1);
    volibear.sprite.setTextureRect(sf::IntRect(265,2,472-265,235-2));
    volibear.sprite.scale({1.3,1.3});
    volibear.sprite.setOrigin(328-265,202-2);
}

void loadMusic(sf::Music& music, const sf::String& str){
    if (!music.openFromFile(str)) {
        std::cerr << "Erreur : Impossible de charger la musique!" << std::endl;
    }
}

void initSound(){
    loadMusic(eatSound,"res/sounds/2manger.ogg");
    eatSound.setVolume(globalSound*3);
    loadMusic(hitHacheSound,"res/sounds/3frapper.ogg");
    hitHacheSound.setVolume(globalSound*3);
    loadMusic(coinSound,"res/sounds/4coin.ogg");
    coinSound.setVolume(globalSound*3);
    loadMusic(hitSound,"res/sounds/5sardoche.ogg");
    hitSound.setVolume(globalSound*2);
    loadMusic(mainMusic,"res/sounds/1Bleach_OST_Invasion.ogg");
    mainMusic.setVolume(globalSound);   // reduce the volume
    mainMusic.setLoop(true);
    mainMusic.play();

    loadMusic(DRVMusic,"res/sounds/6WinBBS.ogg");
    DRVMusic.setLoop(true);
    DRVMusic.setVolume(globalSound);

    loadMusic(MathMusic,"res/sounds/7MathMyTurn.ogg");
    MathMusic.setLoop(true);
    MathMusic.setVolume(globalSound*1.1);
    
    loadMusic(LolMapMusic,"res/sounds/8LolMapHxH.ogg");
    LolMapMusic.setLoop(true);
    LolMapMusic.setVolume(globalSound*1.25);

    loadMusic(LolFightMusic1,"res/sounds/9TopNumber1.ogg");
    LolFightMusic1.setLoop(true);
    LolFightMusic1.setVolume(globalSound);
    loadMusic(LolFightMusic2,"res/sounds/10MidMagic.ogg");
    LolFightMusic2.setLoop(true);
    LolFightMusic2.setVolume(globalSound*2.2);
    loadMusic(LolFightMusic3,"res/sounds/11BotNaruto.ogg");
    LolFightMusic3.setLoop(true);
    LolFightMusic3.setVolume(globalSound*0.8);
    loadMusic(LolFightMusic4,"res/sounds/12PanthDeath.ogg");
    LolFightMusic4.setLoop(true);
    LolFightMusic4.setVolume(globalSound*0.8);
    loadMusic(LolFightMusic5,"res/sounds/13AsheFate.ogg");
    LolFightMusic5.setLoop(true);
    LolFightMusic5.setVolume(globalSound*1.6);

    loadMusic(LolVMusic,"res/sounds/14BohneurKotei.ogg");
    LolVMusic.setVolume(globalSound);
    loadMusic(LolDMusic,"res/sounds/15LolDYui.ogg"); //Not Used yet, because no death page
    LolDMusic.setLoop(true);
    LolDMusic.setVolume(globalSound);
    
    loadMusic(orbExchangeMusic,"res/sounds/16ExchangeHaruhiPlus.ogg");
    orbExchangeMusic.setLoop(true);
    orbExchangeMusic.setVolume(globalSound*1.15);
    
    loadMusic(questionMusic,"res/sounds/17QuestionsHahuriMoins.ogg");
    questionMusic.setLoop(true);
    questionMusic.setVolume(globalSound);
    loadMusic(questionVMusic,"res/sounds/18BleachPeace.ogg");
    questionVMusic.setLoop(true);
    questionVMusic.setVolume(globalSound*1.2);

    loadMusic(AccueilGachaMusic,"res/sounds/19BBSPride.ogg");
    AccueilGachaMusic.setLoop(true);
    AccueilGachaMusic.setVolume(globalSound);
    loadMusic(GachaSound,"res/sounds/20GachaSound.ogg");
    GachaSound.setVolume(globalSound*2.5);
    loadMusic(ListPersoMusic,"res/sounds/21ListBleach999.ogg");
    ListPersoMusic.setLoop(true);
    ListPersoMusic.setVolume(globalSound);


}