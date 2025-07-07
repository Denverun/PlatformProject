#include "gameState.h"

int WIN_X=1778;
int WIN_Y=1000;
int nFPS=32;

float MeanFPS=100.f;
float globalSound=30.f; //max 30 a 35

bool debugMode=false;

sf::Font font;

EtatM etatMap = EtatM::Accueil;

//------------------------------------------------

bool initTruck=true;
sf::Sprite truck;

//------------------------------------------------

sf::RectangleShape boutonAccueil(sf::Vector2f(500, 100)), boutonTuto(sf::Vector2f((400-190)*3, (170-40)*3)), boutonDefeat(sf::Vector2f(500,100));
sf::Text txtRespawn;

int maxHealth = 3, enemyHealth = 8;
Character character1;
Enemy volibear;
float movSpeed=3.f;

sf::VertexArray border1(sf::LinesStrip, 11);
sf::VertexArray border2(sf::LinesStrip, 11); 
sf::VertexArray border3(sf::LinesStrip, 7);
sf::VertexArray border4(sf::LinesStrip, 16);
sf::VertexArray border5(sf::LinesStrip, 7), border5wall1(sf::LinesStrip, 5), border5wall2(sf::LinesStrip, 5);
sf::VertexArray border6(sf::LinesStrip, 9), border6wall(sf::LinesStrip, 5);
sf::VertexArray border7(sf::LinesStrip, 5), border7wall(sf::LinesStrip, 5);

int coinStock = 1, orbStock=1000;
int fractionCoinLost=0;

sf::Text lostHealth;
sf::Clock healthAnimation;

//------------------------------------------------

int inputValue=-2, buttonValue=0;

sf::RectangleShape boutonVecteur1(sf::Vector2f(100,50)),boutonVecteur2(sf::Vector2f(100,50)),boutonVecteur3(sf::Vector2f(100,50)),boutonConfirmer(sf::Vector2f(200,100));
int valueVecteur1=0,valueVecteur2=0,valueVecteur3=0;

sf::Clock falseClock;

//------------------------------------------------------------------------
bool initLol= true,initLol2=true, initBonus=true, initGacha=true;

sf::Clock manqueClock;
int manqueCoins=0;

int lolMaptype=0, championChosen=-1;
sf::Texture textureAnivia, textureZed, textureNunu;
Character Anivia, Zed, Nunu;
sf::Sprite Jax, Katarina, Pantheon, Darius, Ashe, Dragon, Nashor;
Enemy Jax1, Katarina1, Pantheon1, Darius1, Ashe1, Dragon1, Nashor1;
int top1,top2,mid1,mid2,bot1,bot2,jgl;
sf::Sprite Map0,Map1,Map2,Map3,Map4,Map5,Map6,Map7,Map8,Map9,Map10,Map11,VictoryLoL;
sf::RectangleShape Nexus,RestartButton,NextPageButton;

int Aniviaprice=8, Zedprice=14, Nunuprice=1;
sf::Sprite AniviaSprite, ZedSprite, NunuSprite;

sf::VertexArray borderL1(sf::LinesStrip, 5);
sf::VertexArray borderL2(sf::LinesStrip, 5); 
sf::VertexArray borderL3(sf::LinesStrip, 9); //
sf::VertexArray borderL4(sf::LinesStrip, 5);
sf::VertexArray borderL5(sf::LinesStrip, 5);
sf::VertexArray borderL6(sf::LinesStrip, 5); //
sf::VertexArray borderL7(sf::LinesStrip, 10);
sf::VertexArray borderL8(sf::LinesStrip, 5);
sf::VertexArray borderL9(sf::LinesStrip, 6);
sf::VertexArray borderL10(sf::LinesStrip, 5);
sf::VertexArray borderL11(sf::LinesStrip, 5);

sf::Clock turnClock;
float turnDelay;

bool playerTurn=true;

int maxHP=1000;
//bool JaxExist=true, KatarinaExist=true, PantheonExist=true, DariusExist=true, AsheExist=true, DragonExist=true, NashorExist=true;

sf::String infoString1="Le combat commence", infoString2="Appuyez sur la competence souhaitee", infoString3="";
bool newFight=true;

bool isStun=false, isStunEnemy=false, isEscape=false;

//Move
bool canMove=true;
sf::CircleShape verifMove(10);

sf::RectangleShape buttonExchangeR, passerBonusR;
int goldExchange=2,orbExchange=1;
sf::Sprite buttonUp,buttonDown, smallGold, smallOrb;

sf::Text goldQuantity, orbQuantity;

bool afficherMessPauvreGold=false;
sf::Text PauvreGoldTxt;
sf::Clock afficheClock;

bool firstGainNexus=true;

//--------------------------------
sf::RectangleShape inputZone1({400,60}),inputZone2({400,60}),inputZone3({400,60}),inputZone4({400,60});
sf::RectangleShape confirmButton1({250,60}),confirmButton2({250,60}),confirmButton3({250,60}),confirmButton4({250,60});
sf::RectangleShape gachaRect({150,90});

std::string inputString1,inputString2, inputString3,inputString4;

bool confirm1=false,confirm2=false,confirm3=false,confirm4=false;
int writingX=0;

sf::Clock reponseClock;

//----------------------------------
sf::Sprite gachaAizen4,gachaAizen5,gachaEvoli,gachaRukiasBlade,gachaZed,gachaNeeko,gachaVeigar,gachaMordekaiser,gachaKirby,gachaFrieren;
sf::Sprite gachaChar;

//----------
sf::RectangleShape gachaSoloRect({200,90}),gachaVoirRect({200,90});

sf::RectangleShape returnHomeGacha({250,80}),oneMoreSoloRect({250,80});
sf::Sprite gachaChar2;
bool gachaTry=false;
std::vector<std::string> characterList;

sf::RectangleShape returnHomeGacha2({400,80});
std::vector<sf::Sprite> charaList;

bool afficherMessPauvre=false;

sf::Sprite goLeft,goRight;
int pageGacha=0;
int numberFiveStars=0;

sf::Music mainMusic, hitHacheSound, DRVMusic, MathMusic, LolMapMusic, LolFightMusic1,LolFightMusic2,LolFightMusic3,LolFightMusic4,LolFightMusic5,LolVMusic,LolDMusic,orbExchangeMusic,questionMusic,questionVMusic,AccueilGachaMusic,GachaSound,ListPersoMusic;

bool Alea(){
    // Création aléatoire
    random_device rd;  // Générateur basé sur le matériel
    mt19937 gen(rd()); // Mersenne Twister PRNG
    bernoulli_distribution dist(0.5); // Probabilité de 50%
    return dist(gen);
}

int AleaU(int n){
    // Création aléatoire
    random_device rd;  // Générateur basé sur le matériel
    mt19937 gen(rd()); // Mersenne Twister PRNG
    uniform_int_distribution dist(1,n); // Probabilité de 50%
    return dist(gen);
}

float AleaUReal(float a, float b){
    // Création aléatoire
    random_device rd;  // Générateur basé sur le matériel
    mt19937 gen(rd()); // Mersenne Twister PRNG
    uniform_real_distribution dist(a,b); // Probabilité de 50%
    return dist(gen);
}

void SetText(sf::Text &txtBloc, const sf::String &str, const sf::Font &font){
    txtBloc.setFont(font); // Changer la police
    txtBloc.setString(str); // Changer le texte
    txtBloc.setCharacterSize(30); //La taille
    //txtBloc.setStyle(sf::Text::Bold| Text::Underlined);
}

void SetTextMid(sf::Text &txtBloc, int X1, int Y1){
    sf::FloatRect textBounds = txtBloc.getLocalBounds();
    txtBloc.setOrigin(textBounds.width / 2, textBounds.height / 2);
    txtBloc.setPosition(X1,Y1);
}

int signe(float x){
    if(x>=0){
        return 1;
    }
    return -1;
}

Character& chooseChar(int i){
    if(i==0){
        return Anivia;
    }
    else if(i==1){
        return Zed;
    }
    else if(i==2){
        return Nunu;
    }
    else{
        return Anivia;
    }
}

Enemy& chooseEnemy(int i){
    if(i==5){
        return Jax1;
    }
    else if(i==6){
        return Katarina1;
    }
    else if(i==7){
        return Darius1;
    }
    else if(i==9){
        return Pantheon1;
    }
    else if(i==10){
        return Ashe1;
    }
    else{
        return Katarina1;
    }
}

void resizeSprite(sf::Sprite& sprite, float targetWidth, float targetHeight) {
    sf::FloatRect spriteBounds = sprite.getLocalBounds();  // Récupère la taille originale
    float scaleX = targetWidth / spriteBounds.width;
    float scaleY = targetHeight / spriteBounds.height;

    float scale = std::min(scaleX, scaleY);  // Conserve le ratio
    sprite.setScale(scale, scale);  // Applique l'échelle
}