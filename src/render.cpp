#include "render.h"

sf::Clock debugClock; // Pour compter
int debugCompteur=1,lastFPS=0;
sf::Text fpsPratique;

sf::Sprite imageHomePage0,imageHomePage1,imageHomePage2,imageHomePage3,imageHomePage4; // Homepage Pictures
sf::Sprite imageAccueilDR0, zoomAccueilDR0; 
sf::Sprite imageAccueilDR1, zoomAccueilDR1;

bool gainCoinVolibear=true;

sf::Clock animationTemporaire; // Pour affichage début de l'étage
bool clockStart=true,clockFloor=true;
bool boolStart=true,boolFloor=true;

sf::Sprite coinSprite,coinSprite2;
sf::Sprite sausageSprite1,sausageSprite2;
sf::Sprite burgerSprite1,burgerSprite2;
sf::Clock TextureClock;
float texturetime;

sf::Sprite spikeSprite,spikeSprite2;
float timespike;


bool casse=false;

void compter(int &debugCompteur, sf::RenderWindow& window){ // Permet d'estimer le nombre de FPS Réel pour la vérification
    //cout << "tempsMean :" << debugClock.getElapsedTime().asSeconds()/debugCompteur << endl ;
    //cout << "numero :" << debugCompteur << endl;
    int nfpsP=debugCompteur/debugClock.getElapsedTime().asSeconds();
    SetText(fpsPratique,to_string(nfpsP),font);
    fpsPratique.setPosition(WIN_X-100,50);
    window.draw(fpsPratique);
    debugCompteur+=1;
}

void compterVrai(int &debugCompteur, sf::RenderWindow& window){ // Permet d'estimer le nombre de FPS Réel pour la vérification
    if(debugClock.getElapsedTime().asSeconds()>1.f){
        lastFPS=debugCompteur;
        debugClock.restart();
        debugCompteur=0;
    }
    SetText(fpsPratique,to_string(lastFPS),font);
    fpsPratique.setPosition(WIN_X-100,50);
    window.draw(fpsPratique);
    debugCompteur+=1;
}

void initRender(){

    SetRectMid(boutonAccueil, WIN_X/2, WIN_Y/2+250, sf::Color(100,175,80,200));
    imageHomePage0.setTexture(TextureManager::getInstance().getTexture("res/images/Accueil.jpeg"));
    imageHomePage0.setScale({0.5,0.5});
    SetSpriteMid(imageHomePage1, "res/images/Accueil1.jpg", {0.9,0.9}, WIN_X/6+10, 2*WIN_Y/7);
    SetSpriteMid(imageHomePage2, "res/images/Accueil2.jpg", {0.52,0.53}, WIN_X/6+10, 5*WIN_Y/7);
    SetSpriteMid(imageHomePage3, "res/images/Accueil3.jpg", {0.43,0.53}, 5.78*WIN_X/7, 2*WIN_Y/7);
    SetSpriteMid(imageHomePage4, "res/images/Accueil4.jpg", {1.15,1.1}, 5.78*WIN_X/7, 5*WIN_Y/7);

    SetSpriteMidText(imageAccueilDR0, "res/images/DR/Map/DRH0.png", sf::IntRect(0,0,553,300), {3,3}, WIN_X/2, WIN_Y/2);
    SetSpriteMidText(imageAccueilDR1, "res/images/DR/Map/DRH1.png", sf::IntRect(0,0,553,300), {3,3}, WIN_X/2, WIN_Y/2);    
    sf::IntRect rectADR0B = sf::IntRect(190,40,400-190,170-40);
    float pointAppuiX=(WIN_X-553*3)/2+190*3,pointAppuiY=(WIN_Y-300*3)/2+40*3;
    zoomAccueilDR0.setTexture(TextureManager::getInstance().getTexture("res/images/DR/Map/DRH0.png"));
    zoomAccueilDR0.setTextureRect(rectADR0B);
    zoomAccueilDR0.setScale({3,3});
    zoomAccueilDR0.setPosition(pointAppuiX,pointAppuiY);
    zoomAccueilDR1.setTexture(TextureManager::getInstance().getTexture("res/images/DR/Map/DRH1.png"));
    zoomAccueilDR1.setTextureRect(rectADR0B);
    zoomAccueilDR1.setScale({3,3});
    zoomAccueilDR1.setPosition(pointAppuiX,pointAppuiY);
    boutonTuto.setPosition(pointAppuiX,pointAppuiY);

    initSprites();
    initCollectibles();

    initBorder();

    SetRectMid(boutonDefeat, WIN_X/2, WIN_Y/2+300, sf::Color(100,175,80,200));
}

void draw(sf::RenderWindow &window){
    texturetime = TextureClock.getElapsedTime().asSeconds();
    
    if(etatMap == EtatM::Accueil) {
        window.draw(imageHomePage0);
        window.draw(imageHomePage1);
        window.draw(imageHomePage2);
        window.draw(imageHomePage3);
        window.draw(imageHomePage4); 

        sf::Text bienvenue;
        SetText(bienvenue, "Bienvenue au jeu !", font);
        SetTextMid(bienvenue, WIN_X/2, WIN_Y/4);
        window.draw(bienvenue);

        window.draw(boutonAccueil);
        sf::Text jouer;
        SetText(jouer, "Jouer !", font);
        SetTextMid(jouer, WIN_X/2, WIN_Y/2+245);
        window.draw(jouer);
    }
    else if(etatMap == EtatM::AccueilDR) {
        window.draw(imageAccueilDR0);
        sf::RectangleShape filtreGris(sf::Vector2f(553*3, 300*3)); // AccueilDR
        SetRectMid(filtreGris, WIN_X/2, WIN_Y/2, sf::Color(192,192,192,200));
        window.draw(filtreGris);
        window.draw(zoomAccueilDR0);
        character1.speed=movSpeed;
    }
    else if(etatMap == EtatM::ValideDR) {
        window.draw(imageAccueilDR0);
        sf::RectangleShape filtreGris(sf::Vector2f(553*3, 300*3)); // AccueilDR
        SetRectMid(filtreGris, WIN_X/2, WIN_Y/2, sf::Color(192,192,192,200));
        window.draw(filtreGris);
        window.draw(zoomAccueilDR1);
        character1.speed=movSpeed;
    }

    else if(etatMap == EtatM::GameDR1) {
        DRLayout(window, "res/images/DR/Map/Scene1.jpg",1);

        if(clockStart){
            animationTemporaire.restart();
            clockStart=false;
        }
        else if(clockFloor && !boolStart){
            animationTemporaire.restart();
            clockFloor=false;
        }

        if(boolStart){
            sf::Sprite imageDRStart;
            SetSpriteMid(imageDRStart, "res/images/DR/Start.png", {1.35,1.35}, WIN_X/2, WIN_Y/2);
            imageDRStart.setColor(sf::Color(255,255,255,fonctionOpacite(animationTemporaire.getElapsedTime().asSeconds(),2,2,boolStart)));
            window.draw(imageDRStart);
        }
        else if(boolFloor){
            sf::Sprite imageDRFloor;
            SetSpriteMidText(imageDRFloor, "res/images/DR/Stats.png", sf::IntRect(1,132,526-1,268-132),{1.35,1.35}, WIN_X/2, 9*WIN_Y/10);
            imageDRFloor.setColor(sf::Color(255,255,255,fonctionOpacite(animationTemporaire.getElapsedTime().asSeconds(),2,2,boolFloor)));
            window.draw(imageDRFloor);
        }

        coin1.drawCollect(1.5f,3.f,texturetime,window,gainCoin,coinAnimation);
        coin2.drawCollect(1.5f,3.f,texturetime,window,gainCoin,coinAnimation);
    }
    else if(etatMap == EtatM::GameDR2) {
        DRLayout(window, "res/images/DR/Map/Scene2.jpg",2);
        coin3.drawCollect(1.5f,3.f,texturetime,window,gainCoin,coinAnimation);
    }
    else if(etatMap == EtatM::GameDR3) {
        DRLayout(window, "res/images/DR/Map/Scene3.jpg",3);
        coin3.drawCollect(1.5f,3.f,texturetime,window,gainCoin,coinAnimation);
        coin4.drawCollect(1.5f,3.f,texturetime,window,gainCoin,coinAnimation);
    }
    else if(etatMap == EtatM::GameDR4) {
        DRLayout(window, "res/images/DR/Map/Scene4.jpg",4);
        if(volibear.health>0){
            if (isMovingEnemy==6*MeanFPS/5){
                isMovingEnemy=0;
            }
            if (isMovingEnemy>4*MeanFPS/5) {
                volibear.sprite.setTextureRect(sf::IntRect(265,2,472-265,235-2));
            } else {
                volibear.sprite.setTextureRect(sf::IntRect(475,2,692-475,210-2));
            }
            window.draw(volibear.sprite);
        }else if(gainCoinVolibear){
            gainCoinVolibear=false;
            coinStock+=2;
        }

        if(healthAnimation.getElapsedTime().asSeconds()<2.f){
            window.draw(lostHealth);
        }

        window.draw(character1.sprite);
    }
    else if(etatMap == EtatM::GameDR5) {
        DRLayout(window, "res/images/DR/Map/Scene5.jpg",5);
    }
    else if(etatMap == EtatM::GameDR6) {
        DRLayout(window, "res/images/DR/Map/Scene6.jpg",6);
    }
    else if(etatMap == EtatM::GameDR7) {
        DRLayout(window, "res/images/DR/Map/Scene7.jpg",7);
        sausage1.drawCollect(1.5f,3.f,texturetime,window,gainHP,eatAnimation);
        burger.drawCollect(1.5f,3.f,texturetime,window,gainHP,eatAnimation);
        timespike = SpikeClock.getElapsedTime().asSeconds();
        spike1.drawSpike(3.f,6.f,timespike,window,loseHP,spikeAnimation);
        spike2.drawSpike(3.f,6.f,timespike,window,loseHP,spikeAnimation);
        if(timespike>6.f){
            SpikeClock.restart();
        }
    }
    else if(etatMap == EtatM::DRVictory) {        
        sf::Sprite imageDRV;
        SetSpriteMid(imageDRV, "res/images/DR/Map/Victory.jpg", {1.35,1.35}, WIN_X/2, WIN_Y/2);
        window.draw(imageDRV);
    }
    else if(etatMap == EtatM::GameOverDR){
        SetSpriteMid(character1.sprite,"res/images/DR/death.png", {1.35,1.35}, character1.position.x, character1.position.y);
        character1.sprite.setTextureRect(sf::IntRect(0,0,118,131));
        character1.sprite.setOrigin(59,85);
        window.draw(character1.sprite);

        sf::Sprite imageDRDefeat;
        SetSpriteMid(imageDRDefeat, "res/images/DR/Map/Defeat.png", {0.8,0.8}, WIN_X/2, WIN_Y/2);
        window.draw(imageDRDefeat);

        window.draw(boutonDefeat);

        SetText(txtRespawn, "Perdu !", font); // Message accueil
        SetTextMid(txtRespawn, WIN_X/2, 19*WIN_Y/24);
        window.draw(txtRespawn);
    }
    
    else if(etatMap == EtatM::Example) {
        sf::CircleShape shap(50.f);
        shap.setFillColor(sf::Color::Blue);
        shap.setPosition(0,0); //Position
        window.draw(shap);
    }

    if(etatMap!=EtatM::GameOverDR){
        if (isMoving==MeanFPS/2){
            isMoving=0;
        }
        if (isMoving>2*MeanFPS/7){
            character1.sprite.setTexture(TextureManager::getInstance().getTexture("res/images/DR/perso2.png"));
            character1.sprite.setTextureRect(sf::IntRect(0,0,155,149));
        } else {
            character1.sprite.setTexture(TextureManager::getInstance().getTexture("res/images/DR/persos.png")); // Revenir à l’état idle si pas de mouvement
            character1.sprite.setTextureRect(sf::IntRect(598,271,741-598,418-271));
        }
        if(texturetime>3.f){
            TextureClock.restart();
        }
    }

    compterVrai(debugCompteur, window); //Vérification performances

}

// ------------------------------------------------------------------------------------------

void SetRectMid(sf::RectangleShape &rect, int X1, int Y1, const sf::Color color){
    sf::FloatRect textBounds = rect.getLocalBounds();
    rect.setOrigin(textBounds.width / 2, textBounds.height / 2);
    rect.setPosition(X1,Y1);
    rect.setFillColor(color);
}

void SetSprite(sf::Sprite &sprite, const sf::String &str, const sf::Vector2f &scale){
    sprite.setTexture(TextureManager::getInstance().getTexture(str));
    sprite.setScale(scale);
}

void SetSpriteMid(sf::Sprite &sprite, const sf::String &str, const sf::Vector2f &scale , int X1, int Y1){
    sprite.setTexture(TextureManager::getInstance().getTexture(str));
    sprite.setScale(scale);
    
    sf::FloatRect textBounds = sprite.getLocalBounds();
    sprite.setOrigin(textBounds.width/2, textBounds.height/2);
    sprite.setPosition(X1,Y1);
}

void SetSpriteMidEasy(sf::Texture &texture, sf::Sprite &sprite, const sf::String &str, const sf::Vector2f &scale , int X1, int Y1){
    texture.loadFromFile(str);
    sprite.setTexture(texture);
    sprite.setScale(scale);
    sf::FloatRect textBounds = sprite.getLocalBounds();
    sprite.setOrigin(textBounds.width/2, textBounds.height/2);
    sprite.setPosition(X1,Y1);
}

void SetSpriteMidText(sf::Sprite &sprite, const sf::String &txt , const sf::IntRect &rect, const sf::Vector2f &scale , int X1, int Y1){
    sprite.setTexture(TextureManager::getInstance().getTexture(txt));
    sprite.setTextureRect(rect);
    sprite.setScale(scale);
    
    sf::FloatRect textBounds = sprite.getLocalBounds();
    sprite.setOrigin(textBounds.width/2, textBounds.height/2);
    sprite.setPosition(X1,Y1);
}

void SetSpriteMidFromText(sf::Sprite &sprite, sf::Texture& texture, const sf::Vector2f &scale , int X1, int Y1){
    sprite.setTexture(texture);
    sprite.setScale(scale);
    
    sf::FloatRect textBounds = sprite.getLocalBounds();
    sprite.setOrigin(textBounds.width/2, textBounds.height/2);
    sprite.setPosition(X1,Y1);
}

float fonctionOpacite(float temps,int tempsFull,int tempsProgressif,bool &boolValue){
    if(temps<tempsFull){
        return 255;
    
    }
    else if(temps<tempsFull+tempsProgressif){
        return 255*(1-temps/(tempsFull+tempsProgressif));
    }
    else{
        boolValue=false;
        return 0;
    }
}

// ---------------------------

void DRLayout(sf::RenderWindow &window, const sf::String &text, int map){
    sf::Sprite imageMap;
    SetSpriteMid(imageMap, text, {1.35,1.35}, WIN_X/2, WIN_Y/2);
    window.draw(imageMap);

    if(debugMode){
        if(map==1){window.draw(border1);}
        else if(map==2){window.draw(border2);}
        else if(map==3){window.draw(border3);}
        else if(map==4){window.draw(border4);}
        else if(map==5){
            window.draw(border5);
            window.draw(border5wall1);
            window.draw(border5wall2);
        }
        else if(map==6){
            window.draw(border6);
            window.draw(border6wall);
        }
        else if(map==7){
            window.draw(border7);
            window.draw(border7wall);
        }
    }

    if(character1.attackCD.getElapsedTime().asSeconds()>=0.1f && character1.attackCD.getElapsedTime().asSeconds()<0.3f){
        character1.sprite.setTexture(TextureManager::getInstance().getTexture("res/images/DR/persos.png"));
        character1.sprite.setTextureRect(sf::IntRect(1,274,155-1,444-274));
    }
    else if(character1.attackCD.getElapsedTime().asSeconds()>=0.3f && character1.attackCD.getElapsedTime().asSeconds()<0.5f){
        character1.sprite.setTexture(TextureManager::getInstance().getTexture("res/images/DR/persos.png"));
        character1.sprite.setTextureRect(sf::IntRect(156,274,326-156,430-274));
    }

    window.draw(character1.sprite);
    
    sf::Sprite imageDRPV;
    SetSpriteMidText(imageDRPV, "res/images/DR/Stats.png", sf::IntRect(1,1,357-1,130-1),{1.35,1.35}, WIN_X/6, WIN_Y/10);
    window.draw(imageDRPV);

    sf::Sprite imageDRGold;
    SetSpriteMidText(imageDRGold, "res/images/DR/Stats.png", sf::IntRect(359,1,526-359,63-1),{1.35,1.35}, 47*WIN_X/100, 8*WIN_Y/100);
    window.draw(imageDRGold);

    sf::Text numberCoinStock;
    SetText(numberCoinStock, to_string(coinStock), font);
    SetTextMid(numberCoinStock, 47*WIN_X/100, 7*WIN_Y/100);
    window.draw(numberCoinStock);

    sf::Text healthNumber;
    SetText(healthNumber, to_string(character1.health), font);
    SetTextMid(healthNumber, WIN_X/5, WIN_Y/17);
    window.draw(healthNumber);

    CheckNextMap();

}

void CheckNextMap(){
    if(etatMap==EtatM::GameDR1){
        if(character1.position.x<0){
            if(casse==false){etatMap = EtatM::GameDR2;}
            else{etatMap = EtatM::GameDR3;}
            character1.setPosition(WIN_X-50,character1.position.y);
        }
    }
    if(etatMap==EtatM::GameDR2){
        if(character1.position.x<0){
            etatMap = EtatM::GameDR4;
            character1.setPosition(WIN_X-200,character1.position.y);
        }
        else if(character1.position.x>WIN_X){
            etatMap = EtatM::GameDR1;
            character1.setPosition(50,character1.position.y);
        }
    }
    if(etatMap==EtatM::GameDR3){
        if(character1.position.x<0){
            etatMap = EtatM::GameDR4;
            character1.setPosition(WIN_X-200,character1.position.y);
        }
        else if(character1.position.x>WIN_X){
            etatMap = EtatM::GameDR1;
            character1.setPosition(50,character1.position.y);
        }
    }
    if(etatMap==EtatM::GameDR4){
        if(character1.position.y<0){
            etatMap = EtatM::GameDR5;
            character1.setPosition(character1.position.x,WIN_Y-30);
        }
        else if(character1.position.x>WIN_X){
            if(casse==false){etatMap = EtatM::GameDR2;}
            else{etatMap = EtatM::GameDR3;}
            character1.setPosition(50,character1.position.y);
        }
    }
    if(etatMap==EtatM::GameDR5){
        if(character1.position.x>WIN_X){
            etatMap = EtatM::GameDR6;
            character1.setPosition(50,character1.position.y);
        }
        else if(character1.position.y>WIN_Y){
            etatMap = EtatM::GameDR4;
            character1.setPosition(character1.position.x,50);
        }
    }
    if(etatMap==EtatM::GameDR6){
        if(character1.position.y>WIN_Y){
            etatMap = EtatM::GameDR7;
            character1.setPosition(character1.position.x,50);
        }
        else if(character1.position.x<0){
            etatMap = EtatM::GameDR5;
            character1.setPosition(WIN_X-50,character1.position.y);
        }
    }
    if(etatMap==EtatM::GameDR7){
        if(character1.position.y<0){
            etatMap = EtatM::GameDR6;
            character1.setPosition(character1.position.x,WIN_Y-50);
        }
    }
}

void initSprites(){
    SetSpriteMidText(coinSprite, "res/images/DR/pieceBouffe.png", sf::IntRect(1,1,83-1,69-1), {1,1}, 500, 500);
    SetSpriteMidText(coinSprite2, "res/images/DR/pieceBouffe.png", sf::IntRect(85,1,153-85,69-1), {1,1}, 500, 500);
    SetSpriteMidText(sausageSprite1, "res/images/DR/pieceBouffe.png", sf::IntRect(155,1,224-155,69-1), {1,1}, 500, 500);
    SetSpriteMidText(sausageSprite2, "res/images/DR/pieceBouffe.png", sf::IntRect(155,1,224-155,69-1), {1,1}, 500, 500);
    SetSpriteMidText(burgerSprite1, "res/images/DR/pieceBouffe.png", sf::IntRect(1,71,80-1,134-80), {1,1}, 500, 500);
    SetSpriteMidText(burgerSprite2, "res/images/DR/pieceBouffe.png", sf::IntRect(157,71,224-157,134-71), {1,1}, 500, 500);
    SetSpriteMidText(spikeSprite, "res/images/DR/persos.png", sf::IntRect(328,239,457-328,329-239), {1.35,1.35}, 500, 500);
    SetSpriteMidText(spikeSprite2, "res/images/DR/persos.png", sf::IntRect(475,213,595-475,324-213), {1.35,1.35}, 500, 500);
}

void initCollectibles(){
    coin1 = Collect(1,coinSprite,coinSprite2,{100,450});
    coin2 = Collect(1,coinSprite,coinSprite2,{300,450});
    coin3 = Collect(1,coinSprite,coinSprite2,{1250,450});
    coin4 = Collect(1,coinSprite,coinSprite2,{750,390});
    sausage1 = Collect(1,sausageSprite1,sausageSprite2,{WIN_X/2,500});
    burger = Collect(2,burgerSprite1,burgerSprite2,{WIN_X/2,850});
    spikeSprite.setOrigin(391-328,325-239);
    spikeSprite2.setOrigin(535-475,322-213);
    spike1 = Collect(-1,spikeSprite,spikeSprite2,{500,350});
    spike2 = Collect(-1,spikeSprite,spikeSprite2,{WIN_X-500,350});
    spike1.collect();
    spike2.collect();
}

void initBorder(){
    border1[0].position = sf::Vector2f(-100, 320);
    border1[1].position = sf::Vector2f(450, 320);
    border1[2].position = sf::Vector2f(800, 70);
    border1[3].position = sf::Vector2f(980, 70);
    border1[4].position = sf::Vector2f(1300, 320);
    border1[5].position = sf::Vector2f(1300, 620);
    border1[6].position = sf::Vector2f(1210, 840);
    border1[7].position = sf::Vector2f(620, 840);
    border1[8].position = sf::Vector2f(300, 650);
    border1[9].position = sf::Vector2f(-100, 650);
    border1[10].position = sf::Vector2f(-100, 320);

    border2[0].position = sf::Vector2f(-100, 320);
    border2[1].position = sf::Vector2f(690, 320);
    border2[2].position = sf::Vector2f(690, 370);
    border2[3].position = sf::Vector2f(790, 370);
    border2[4].position = sf::Vector2f(790, 310);
    border2[5].position = sf::Vector2f(1900, 310);
    border2[6].position = sf::Vector2f(1900, 650);
    border2[7].position = sf::Vector2f(450, 650);
    border2[8].position = sf::Vector2f(450, 1000);
    border2[9].position = sf::Vector2f(-100, 1000);
    border2[10].position = sf::Vector2f(-100, 320);
    for (int i = 0; i < 11; ++i) {
        border1[i].color = sf::Color::Red;
        border2[i].color = sf::Color::Red;
    }
    border3[0].position = sf::Vector2f(-100, 320);
    border3[1].position = sf::Vector2f(1900, 320);
    border3[2].position = sf::Vector2f(1900, 650);
    border3[3].position = sf::Vector2f(450, 650);
    border3[4].position = sf::Vector2f(450, 950);
    border3[5].position = sf::Vector2f(-100, 950);
    border3[6].position = sf::Vector2f(-100, 350);
    
    border4[0].position = sf::Vector2f(145, 360);
    border4[1].position = sf::Vector2f(710, 360);
    border4[2].position = sf::Vector2f(710, 100);
    border4[3].position = sf::Vector2f(145, 100);
    border4[4].position = sf::Vector2f(145, -100);
    border4[5].position = sf::Vector2f(1600, -100);
    border4[6].position = sf::Vector2f(1600, 100);
    border4[7].position = sf::Vector2f(1350, 100);
    border4[8].position = sf::Vector2f(1200, 250);
    border4[9].position = sf::Vector2f(1200, 360);
    border4[10].position = sf::Vector2f(1900, 360);
    border4[11].position = sf::Vector2f(1900, 680);
    border4[12].position = sf::Vector2f(1600, 680);
    border4[13].position = sf::Vector2f(1600, 1000);
    border4[14].position = sf::Vector2f(145, 1000);
    border4[15].position = sf::Vector2f(145, 360);
    for (int i = 0; i < 16; ++i) {
        border4[i].color = sf::Color::Red;
    }
    border5[0].position = sf::Vector2f(145, 365);
    border5[1].position = sf::Vector2f(1900, 365);
    border5[2].position = sf::Vector2f(1900, 750);
    border5[3].position = sf::Vector2f(1600, 750);
    border5[4].position = sf::Vector2f(1600, 1100);
    border5[5].position = sf::Vector2f(145, 1100);
    border5[6].position = sf::Vector2f(145, 365);
    for (int i = 0; i < 7; ++i) {
        border3[i].color = sf::Color::Red;
        border5[i].color = sf::Color::Red;
    }
    border5wall1[0].position = sf::Vector2f(1150, 950);
    border5wall1[1].position = sf::Vector2f(1150, 870);
    border5wall1[2].position = sf::Vector2f(1050, 870);
    border5wall1[3].position = sf::Vector2f(1050, 950);
    border5wall1[4].position = sf::Vector2f(1150, 950);

    border5wall2[0].position = sf::Vector2f(680, 950);
    border5wall2[1].position = sf::Vector2f(680, 870);
    border5wall2[2].position = sf::Vector2f(580, 870);
    border5wall2[3].position = sf::Vector2f(580, 950);
    border5wall2[4].position = sf::Vector2f(680, 950);

    border6[0].position = sf::Vector2f(-100, 350);
    border6[1].position = sf::Vector2f(380, 350);
    border6[2].position = sf::Vector2f(380, 0);
    border6[3].position = sf::Vector2f(1620, 0);
    border6[4].position = sf::Vector2f(1620, 1100);
    border6[5].position = sf::Vector2f(440, 1100);
    border6[6].position = sf::Vector2f(440, 670);
    border6[7].position = sf::Vector2f(-100, 670);
    border6[8].position = sf::Vector2f(-100, 350);
    for (int i = 0; i < 9; ++i) {
        border6[i].color = sf::Color::Red;
    }
    border6wall[0].position = sf::Vector2f(1000, 270);
    border6wall[1].position = sf::Vector2f(1120, 270);
    border6wall[2].position = sf::Vector2f(1120, 925);
    border6wall[3].position = sf::Vector2f(1000, 925);
    border6wall[4].position = sf::Vector2f(1000, 270);

    border7[0].position = sf::Vector2f(285, -100);
    border7[1].position = sf::Vector2f(1450, -100);
    border7[2].position = sf::Vector2f(1450, 1000);
    border7[3].position = sf::Vector2f(285, 1000);
    border7[4].position = sf::Vector2f(285, -100);
    
    border7wall[0].position = sf::Vector2f(530, 655);
    border7wall[1].position = sf::Vector2f(1227, 655);
    border7wall[2].position = sf::Vector2f(1227, 735);
    border7wall[3].position = sf::Vector2f(530, 735);
    border7wall[4].position = sf::Vector2f(530, 655);
    for (int i = 0; i < 5; ++i) {
        border5wall1[i].color = sf::Color::Red;
        border5wall2[i].color = sf::Color::Red;
        border6wall[i].color = sf::Color::Red;
        border7[i].color = sf::Color::Red;
        border7wall[i].color = sf::Color::Red;
    }
}

//-----

void draw2(sf::RenderWindow &window){

    sf::Texture tTableau, tMatrice, tVecteur;
    tMatrice.setSmooth(true);
    tVecteur.setSmooth(true);
    sf::Sprite tableau, Matrice, Vecteur;
    SetSpriteMidEasy(tTableau, tableau, "res/images/Matrice/tableau.jpg", {6.f,6.f} , WIN_X/2,WIN_Y/2);
    window.draw(tableau);
    SetSpriteMidEasy(tMatrice, Matrice, "res/images/Matrice/Matrice.png", {1.f,1.f} , WIN_X/6,3*WIN_Y/4);
    Matrice.rotate(-35);
    window.draw(Matrice);
    SetSpriteMidEasy(tVecteur, Vecteur, "res/images/Matrice/Vecteur.png", {1.f,1.f} , 4*WIN_X/5,2*WIN_Y/7);
    Vecteur.rotate(20);
    window.draw(Vecteur);
    
    SetRectMid(boutonVecteur1, 3*WIN_X/4, 6*WIN_Y/10, sf::Color::Green);
    SetRectMid(boutonVecteur2, 3*WIN_X/4, 7*WIN_Y/10, sf::Color::Green);
    SetRectMid(boutonVecteur3, 3*WIN_X/4, 8*WIN_Y/10, sf::Color::Green);
    SetRectMid(boutonConfirmer, 9*WIN_X/10, 7*WIN_Y/10, sf::Color(100,175,80,200));
    
    window.draw(boutonVecteur1);
    window.draw(boutonVecteur2);
    window.draw(boutonVecteur3);
    window.draw(boutonConfirmer);

    sf::Text valeur1;
    drawInputValue(valeur1, 1,valueVecteur1, 3*WIN_X/4, 6*WIN_Y/10-10);
    window.draw(valeur1);

    sf::Text valeur2;
    drawInputValue(valeur2, 2,valueVecteur2, 3*WIN_X/4, 7*WIN_Y/10-10);
    window.draw(valeur2);

    sf::Text valeur3;
    drawInputValue(valeur3, 3,valueVecteur3, 3*WIN_X/4, 8*WIN_Y/10-10);
    window.draw(valeur3);

    sf::Text confirmer;
    SetText(confirmer,"Confirmer", font);
    SetTextMid(confirmer,9*WIN_X/10, 7*WIN_Y/10-10);
    window.draw(confirmer);

    if(falseClock.getElapsedTime().asSeconds()<3.0f){
        sf::Text falseConfirm,falseConfirm2;
        SetText(falseConfirm,"Votre reponse est erronee, vous avez perdu une piece.", font);
        SetTextMid(falseConfirm,WIN_X/2, WIN_Y/3);
        falseConfirm.setFillColor(sf::Color::Red);
        window.draw(falseConfirm);

        SetText(falseConfirm2,"Veuillez recommencer et ne pas faire de faute", font);
        SetTextMid(falseConfirm2,WIN_X/2, WIN_Y/3+50);
        falseConfirm2.setFillColor(sf::Color::Red);
        window.draw(falseConfirm2);
    }
}

void drawInputValue(sf::Text& valeur, int caseNum, int& valueVecteur, int posX, int posY){
    SetText(valeur,to_string(valueVecteur), font);
    SetTextMid(valeur,posX,posY);
    if(buttonValue==caseNum){
        if(abs(valueVecteur)>=100){
            valueVecteur=0;
        }
    }
}

void drawShop(sf::RenderWindow &window){
    if(lolMaptype==0){
        sf::Sprite ecranShop;
        sf::Text fail1;
        //SetSpriteMid(ecranShop,"",{1,1},WIN_X/2,WIN_Y/2);

        sf::Text characterShop;
        SetText(characterShop,"Character Shop", font);
        SetTextMid(characterShop,200,150);
        sf::Text choisirChampion;
        SetText(choisirChampion,"Choose your character :", font);
        SetTextMid(choisirChampion,WIN_X/2,300);
        sf::Text coinStockText;
        SetText(coinStockText,to_string(coinStock)+" golds", font);
        SetTextMid(coinStockText,WIN_X/2+300,300);
        
        SetSpriteMidFromText(AniviaSprite,textureAnivia,{0.2f,0.2f},250,600);
        SetSpriteMidFromText(ZedSprite,textureZed,{0.22f,0.22f},500,600);
        SetSpriteMidFromText(NunuSprite,textureNunu,{0.12f,0.12f},750,600);
        
        
        sf::Text AniviapriceText,ZedpriceText,NunupriceText;
        SetText(AniviapriceText,to_string(Aniviaprice)+" golds", font);
        SetTextMid(AniviapriceText,250,850);
        SetText(ZedpriceText,to_string(Zedprice)+" golds", font);
        SetTextMid(ZedpriceText,500,850);
        SetText(NunupriceText,to_string(Nunuprice)+" golds", font);
        SetTextMid(NunupriceText,750,850);

        //window.draw(ecranShop);
        window.draw(characterShop);
        window.draw(choisirChampion);
        window.draw(coinStockText);
        window.draw(AniviaSprite);
        window.draw(ZedSprite);
        window.draw(NunuSprite);
        window.draw(AniviapriceText);
        window.draw(ZedpriceText);
        window.draw(NunupriceText);

        if(manqueClock.getElapsedTime().asSeconds()<3.f){
            SetText(fail1,"Il vous manque "+to_string(manqueCoins)+" golds", font);
            SetTextMid(fail1,WIN_X/2,WIN_Y/3);
            fail1.setFillColor(sf::Color::Red);
            window.draw(fail1);
        }
    }
}

void drawLol(Character& character, sf::RenderWindow &window){
    drawShop(window);
    if(lolMaptype==1){

        drawMap(1,Map1,"res/images/LoL/Map1.jpg",{WIN_X/904.f,WIN_Y/879.f},character, Katarina, borderL1,window, 0,Katarina1);
        drawMap(2,Map2,"res/images/LoL/Map2.jpg",{WIN_X/300.f,WIN_Y/603.f},character, Katarina, borderL2,window, 0,Katarina1);
        drawMap(3,Map3,"res/images/LoL/Map3.jpg",{WIN_X/522.f,WIN_Y/426.f},character, Katarina, borderL3,window, 0,Katarina1);
        drawMap(4,Map4,"res/images/LoL/Map4.jpg",{WIN_X/997.f,WIN_Y/330.f},character, Katarina, borderL4,window, 0,Katarina1);
        drawMap(5,Map5,"res/images/LoL/Map5.jpg",{WIN_X/715.f,WIN_Y/400.f},character, Jax, borderL5,window, 1,Jax1);
        drawMap(6,Map6,"res/images/LoL/Map6.jpg",{WIN_X/640.f,WIN_Y/533.f},character, Katarina, borderL6,window, 1,Katarina1);
        drawMap(7,Map7,"res/images/LoL/Map7.jpg",{WIN_X/922.f,WIN_Y/721.f},character, Darius, borderL7,window, 1,Darius1);
        drawMap(8,Map8,"res/images/LoL/Map8.jpg",{WIN_X/1086.f,WIN_Y/340.f},character, Katarina, borderL8,window, 0,Katarina1);
        drawMap(9,Map9,"res/images/LoL/Map9.jpg",{WIN_X/1458.f,WIN_Y/880.f},character, Pantheon, borderL9,window, 1,Pantheon1);
        drawMap(10,Map10,"res/images/LoL/Map10.jpg",{WIN_X/466.f,WIN_Y/841.f},character, Ashe, borderL10,window, 1,Ashe1);
        drawMap(11,Map11,"res/images/LoL/Map11.jpg",{WIN_X/2000.f,WIN_Y/1125.f},character, Katarina, borderL11,window, 0,Katarina1);

        if(static_cast<int>(etatMap)==11){
            Nexus=sf::RectangleShape(sf::Vector2f(500, 450));
            Nexus.setPosition(915, 130);
            Nexus.setFillColor(sf::Color::Transparent); // Invisible
            //Nexus.setOutlineColor(sf::Color::Red); // Juste pour debug, peut être retiré
            //Nexus.setOutlineThickness(1.f); // Retirer si nécessaire
            window.draw(Nexus);
        }

        if(static_cast<int>(etatMap)==12){
            SetSpriteMid(VictoryLoL, "res/images/LoL/VictoryLoL.png", {1.f,1.f}, WIN_X/2,WIN_Y/2);
            RestartButton=sf::RectangleShape(sf::Vector2f(300, 80));
            SetRectMid(RestartButton, WIN_X/2, WIN_Y/2+350, sf::Color::Green);
            NextPageButton=sf::RectangleShape(sf::Vector2f(300, 80));
            SetRectMid(NextPageButton, WIN_X/2, WIN_Y/2+200, sf::Color::Green);
            sf::Text RestartTxt, NextPageTxt;

            SetText(RestartTxt,"Recommencer",font);
            SetTextMid(RestartTxt, WIN_X/2,WIN_Y/2+340);
            SetText(NextPageTxt,"Passer a la suite",font);
            SetTextMid(NextPageTxt, WIN_X/2,WIN_Y/2+190);

            window.draw(VictoryLoL);
            window.draw(RestartButton);
            window.draw(NextPageButton);
            window.draw(RestartTxt);
            window.draw(NextPageTxt);
        }

        if(static_cast<int>(etatMap)==13){
            sf::Sprite orbSprite;
            sf::Text exchangeRateGO, buttonExchange, passerBonus;
            std::string exchangeRateString;

            buttonExchangeR=sf::RectangleShape(sf::Vector2f(300, 80));
            SetRectMid(buttonExchangeR, 3.5*WIN_X/5,2*WIN_Y/3+10, sf::Color::Green);
            passerBonusR=sf::RectangleShape(sf::Vector2f(300, 80));
            SetRectMid(passerBonusR, WIN_X/2,2.5*WIN_Y/3+10, sf::Color::Green);

            SetSpriteMid(orbSprite, "res/images/Loot/Orbs.png", {1.2f,1.2f}, 1.5*WIN_X/5,2*WIN_Y/5);
            SetSpriteMid(smallOrb, "res/images/Loot/Orb.png", {0.1f,0.1f}, 3.6*WIN_X/5,WIN_Y/13);
            SetSpriteMid(smallGold, "res/images/Loot/Coins.png", {0.1f,0.1f}, 2.6*WIN_X/5,WIN_Y/13);
            

            exchangeRateString=to_string(goldExchange)+" gold -> "+to_string(orbExchange)+" orb";
            SetText(goldQuantity,to_string(coinStock),font);
            SetTextMid(goldQuantity,3*WIN_X/5,WIN_Y/13-10);
            SetText(orbQuantity,to_string(orbStock),font);
            SetTextMid(orbQuantity,4*WIN_X/5,WIN_Y/13-10);
            SetText(buttonExchange,"Echanger",font);
            SetTextMid(buttonExchange,3.5*WIN_X/5,2*WIN_Y/3);
            SetText(passerBonus,"Passer",font);
            SetTextMid(passerBonus,WIN_X/2,2.5*WIN_Y/3);
            SetText(exchangeRateGO,exchangeRateString,font);
            SetTextMid(exchangeRateGO,1.5*WIN_X/5,2*WIN_Y/3);

            SetSpriteMid(buttonUp, "res/images/Loot/Up.png", {0.5f,0.5f}, WIN_X/2,2*WIN_Y/3-60);
            SetSpriteMid(buttonDown, "res/images/Loot/Down.png", {0.5f,0.5f}, WIN_X/2,2*WIN_Y/3+60);

            if(afficherMessPauvreGold){
                afficherMessPauvreGold=false;
                SetText(PauvreGoldTxt,"Il vous manque "+to_string(goldExchange-coinStock),font);
                SetTextMid(PauvreGoldTxt,WIN_X/2,WIN_Y/3);
                afficheClock.restart();
            }

            
            //SetSpriteMid(VictoryLoL, "res/images/LoL/VictoryLoL.png", {1.f,1.f}, WIN_X/2,WIN_Y/2);
            
            window.draw(buttonExchangeR);
            window.draw(passerBonusR);
            window.draw(goldQuantity);
            window.draw(orbQuantity);
            window.draw(buttonExchange);
            window.draw(passerBonus);
            window.draw(exchangeRateGO);
            window.draw(buttonUp);
            window.draw(buttonDown);

            window.draw(orbSprite);
            window.draw(smallOrb);
            window.draw(smallGold);
            if(afficheClock.getElapsedTime().asSeconds()<3.f){
                window.draw(PauvreGoldTxt);
            }
        }
        
    }
    
    
    compterVrai(debugCompteur, window); //Vérification performances
    
}

void drawMap(int etat, sf::Sprite& map, std::string strM, sf::Vector2f scaleM, Character& character, sf::Sprite& enemyS, sf::VertexArray& border, sf::RenderWindow& window, int i, Enemy& enemy){
    if(static_cast<int>(etatMap)==etat){
        SetSpriteMid(map, strM, scaleM, WIN_X/2,WIN_Y/2);
        window.draw(map);
        if(debugMode){
            window.draw(border);
        }
        if(i==1 && enemy.doesExist){
            window.draw(enemyS); 
        }
        window.draw(character.sprite);
    }
}

void drawLolMap2(Character& character, Enemy& enemy, sf::RenderWindow &window){  
    if(static_cast<int>(etatMap)==5){
        SetSpriteMid(Map5, "res/images/LoL/Map5.jpg", {WIN_X/715.f,WIN_Y/400.f} , WIN_X/2,WIN_Y/2);
        window.draw(Map5);
        sf::Sprite Indice1,Indice2; 
        SetSpriteMid(Indice1, "res/images/LoL/persos/chaise.png", {-0.5f,0.5f} , 3*WIN_X/4+10,4*WIN_Y/7);
        window.draw(Indice1);
        SetSpriteMid(Indice2, "res/images/LoL/persos/boitenoire.png", {0.5f,0.5f} , 3*WIN_X/4+15,6*WIN_Y/7+20);
        window.draw(Indice2);
    }
    else if(static_cast<int>(etatMap)==6){
        SetSpriteMid(Map6, "res/images/LoL/Map6.jpg", {WIN_X/640.f,WIN_Y/533.f} , WIN_X/2,WIN_Y/2);
        window.draw(Map6);
    }
    else if(static_cast<int>(etatMap)==7){
        SetSpriteMid(Map7, "res/images/LoL/Map7.jpg", {WIN_X/922.f,WIN_Y/721.f} , WIN_X/2,WIN_Y/2);
        window.draw(Map7);
    }
    else if(static_cast<int>(etatMap)==9){
        SetSpriteMid(Map9, "res/images/LoL/Map9.jpg", {WIN_X/1458.f,WIN_Y/880.f} , WIN_X/2,WIN_Y/2);
        window.draw(Map9);
    }
    else if(static_cast<int>(etatMap)==10){
        SetSpriteMid(Map10, "res/images/LoL/Map10.jpg", {WIN_X/466.f,WIN_Y/841.f} , WIN_X/2,WIN_Y/2);
        window.draw(Map10);
    }
    window.draw(enemy.sprite);
    window.draw(character.sprite);

    sf::Sprite persoHPBar, enemyHPBar;
    SetSpriteMid(persoHPBar, "res/images/LoL/Fight/HealthBar.png", {1.f,1.f} , WIN_X/5,WIN_Y/2);
    SetSpriteMid(enemyHPBar, "res/images/LoL/Fight/HealthBar.png", {1.f,1.f} , 4*WIN_X/5,WIN_Y/2);

    sf::RectangleShape persoHPLost(sf::Vector2f(min(262.f-5.f,(character.maxHealth-static_cast<float>(character.health))/character.maxHealth*(262-5)), 25)),enemyHPLost(sf::Vector2f(min(262.f-5.f,(enemy.maxHealth-static_cast<float>(enemy.health))/enemy.maxHealth*(262-5)), 25));
    SetRectMid(persoHPLost, WIN_X/5+static_cast<float>(max(0,character.health))/character.maxHealth/2*(262-5), WIN_Y/2, sf::Color::Black);
    SetRectMid(enemyHPLost, 4*WIN_X/5+(static_cast<float>(max(0,enemy.health))/enemy.maxHealth)/2*(262-5), WIN_Y/2, sf::Color::Black);

    sf::Text persoHPNumber;
    SetText(persoHPNumber,to_string(character.health),font);
    SetTextMid(persoHPNumber, WIN_X/5,WIN_Y/2+50);

    sf::Sprite informations, stun1, stun2;
    SetSpriteMid(informations, "res/images/LoL/Fight/Cadre.png", {1.4f,0.7f} , WIN_X/2,3*WIN_Y/4);
    SetSpriteMid(stun1, "res/images/LoL/Fight/Stunned.png", {1.f,1.f} , character.position.x,character.position.y-200);
    stun1.setColor(sf::Color::Yellow);
    SetSpriteMid(stun2, "res/images/LoL/Fight/Stunned.png", {1.f,1.f} , enemy.getPosition().x,enemy.getPosition().y-200);
    stun2.setColor(sf::Color::Yellow);

    sf::Text infoLigne1, infoLigne2, infoLigne3;
    SetText(infoLigne1,infoString1,font);
    SetTextMid(infoLigne1, WIN_X/2,3*WIN_Y/4-50);
    infoLigne1.setFillColor(sf::Color::Red);
    SetText(infoLigne2,infoString2,font);
    SetTextMid(infoLigne2, WIN_X/2,3*WIN_Y/4+50);
    infoLigne2.setFillColor(sf::Color::Red);
    SetText(infoLigne3,infoString3,font);
    SetTextMid(infoLigne3, WIN_X/2,3*WIN_Y/4);
    infoLigne3.setFillColor(sf::Color::Red);

    window.draw(persoHPBar);
    window.draw(enemyHPBar);
    window.draw(persoHPLost);
    window.draw(enemyHPLost);
    window.draw(persoHPNumber);
    window.draw(informations);
    if(isStun){
        window.draw(stun1);
    }
    if(isStunEnemy){
        window.draw(stun2);
    }
    window.draw(infoLigne1);
    window.draw(infoLigne2);
    window.draw(infoLigne3);
    //if(turnClock.getElapsedTime().asSeconds()>=turnDelay){infoString3="";}
}

void initBorder2(){
    borderL1[0].position = sf::Vector2f(13, 30);
    borderL1[1].position = sf::Vector2f(WIN_X-13, 30);
    borderL1[2].position = sf::Vector2f(WIN_X-13, WIN_Y-13);
    borderL1[3].position = sf::Vector2f(13, WIN_Y-13);
    borderL1[4].position = sf::Vector2f(13, 30);

    borderL2[0].position = sf::Vector2f(250, 30);
    borderL2[1].position = sf::Vector2f(WIN_X-300, 30);
    borderL2[2].position = sf::Vector2f(WIN_X-300, WIN_Y-13);
    borderL2[3].position = sf::Vector2f(250, WIN_Y-13);
    borderL2[4].position = sf::Vector2f(250, 30);

    borderL5[0].position = sf::Vector2f(13, WIN_Y/2+55);
    borderL5[1].position = sf::Vector2f(WIN_X-13, WIN_Y/2-120);
    borderL5[2].position = sf::Vector2f(WIN_X-13, WIN_Y-13);
    borderL5[3].position = sf::Vector2f(13, WIN_Y-13);
    borderL5[4].position = sf::Vector2f(13, WIN_Y/2+55);

    borderL8[0].position = sf::Vector2f(13, 150);
    borderL8[1].position = sf::Vector2f(WIN_X-13, 150);
    borderL8[2].position = sf::Vector2f(WIN_X-13, WIN_Y-250);
    borderL8[3].position = sf::Vector2f(13, WIN_Y-250);
    borderL8[4].position = sf::Vector2f(13, 150);

    borderL11[0].position = sf::Vector2f(13, 30);
    borderL11[1].position = sf::Vector2f(WIN_X-13, 30);
    borderL11[2].position = sf::Vector2f(WIN_X-13, WIN_Y-13);
    borderL11[3].position = sf::Vector2f(13, WIN_Y-13);
    borderL11[4].position = sf::Vector2f(13, 30);

    borderL3[0].position = sf::Vector2f(13, WIN_Y/2+120);
    borderL3[1].position = sf::Vector2f(250, WIN_Y/2+170);
    borderL3[2].position = sf::Vector2f(WIN_X-440, 30);
    borderL3[3].position = sf::Vector2f(WIN_X-13, 30);
    borderL3[4].position = sf::Vector2f(WIN_X-13, 280);
    borderL3[5].position = sf::Vector2f(620, WIN_Y-80);
    borderL3[6].position = sf::Vector2f(710, WIN_Y-13);
    borderL3[7].position = sf::Vector2f(13, WIN_Y-13);
    borderL3[8].position = sf::Vector2f(13, WIN_Y/2+120);

    borderL6[0].position = sf::Vector2f(13, 730);
    borderL6[1].position = sf::Vector2f(WIN_X-330, 30);
    borderL6[2].position = sf::Vector2f(WIN_X-55, 70);
    borderL6[3].position = sf::Vector2f(150, WIN_Y-20);
    borderL6[4].position = sf::Vector2f(13, 825);
    borderL6[5].position = sf::Vector2f(13, 730);

    borderL9[0].position = sf::Vector2f(13, WIN_Y-13);
    borderL9[1].position = sf::Vector2f(WIN_X-450, 30);
    borderL9[2].position = sf::Vector2f(WIN_X-13, 30);
    borderL9[3].position = sf::Vector2f(WIN_X-40, 580);
    borderL9[4].position = sf::Vector2f(WIN_X-400, WIN_Y-13);
    borderL9[5].position = sf::Vector2f(13, WIN_Y-13);

    borderL4[0].position = sf::Vector2f(13, 200);
    borderL4[1].position = sf::Vector2f(WIN_X-13, 200);
    borderL4[2].position = sf::Vector2f(WIN_X-13, WIN_Y-170);
    borderL4[3].position = sf::Vector2f(13, WIN_Y-170);
    borderL4[4].position = sf::Vector2f(13, 200);

    borderL7[0].position = sf::Vector2f(13, 780);
    borderL7[1].position = sf::Vector2f(670, 775);
    borderL7[2].position = sf::Vector2f(WIN_X-520, 370);
    borderL7[3].position = sf::Vector2f(WIN_X-560, 30);
    borderL7[4].position = sf::Vector2f(WIN_X-230, 30);
    borderL7[5].position = sf::Vector2f(WIN_X-280, 600);
    borderL7[6].position = sf::Vector2f(WIN_X-620, 910);
    borderL7[7].position = sf::Vector2f(WIN_X/2-50, WIN_Y-13);
    borderL7[8].position = sf::Vector2f(13, WIN_Y-13);
    borderL7[9].position = sf::Vector2f(13, 780);

    borderL10[0].position = sf::Vector2f(500, WIN_Y-13);
    borderL10[1].position = sf::Vector2f(500, 30);
    borderL10[2].position = sf::Vector2f(1300, 30);
    borderL10[3].position = sf::Vector2f(1300, WIN_Y-13);
    borderL10[4].position = sf::Vector2f(500, WIN_Y-13);
    
    for (int i = 0; i < 5; ++i) {
        borderL1[i].color = sf::Color::Red;
        borderL2[i].color = sf::Color::Red;
        borderL5[i].color = sf::Color::Red;
        borderL8[i].color = sf::Color::Red;
        borderL11[i].color = sf::Color::Red;
        borderL4[i].color = sf::Color::Red;
        borderL10[i].color = sf::Color::Red;
    }
    for (int i = 0; i < 9; ++i) {
        borderL3[i].color = sf::Color::Red;
    }
    for (int i = 0; i < 6; ++i) {
        borderL6[i].color = sf::Color::Red;
        borderL9[i].color = sf::Color::Red;
    }
    for (int i = 0; i < 10; ++i) {
        borderL7[i].color = sf::Color::Red;
    }
}

void CheckNextMap2(Character& character){  // Ancienne version
    
    if(character.position.y<=0 && character.position.x<=0){
        character.setPosition(character.position.x,WIN_Y-100);
    }
    
    else if(static_cast<int>(etatMap)==1){
        if(character.position.y<50 && character.position.x<=WIN_X/2){
            etatMap=static_cast<EtatM>(2);
            character.setPosition(character.position.x*1.3+220,WIN_Y-100);
        }
        else if(character.position.y<=(250.f-100.f)/(9.f/10.f-3.f/4.f)/WIN_X*character.position.x+100-3.f/4.f*(250.f-100.f)/(9.f/10.f-3.f/4.f)){
            etatMap=static_cast<EtatM>(3);
            character.setPosition(WIN_X/5,WIN_Y-100);
        }
        else if(character.position.x>WIN_X-50 && character.position.y>=WIN_Y/2){
            etatMap=static_cast<EtatM>(4);
            character.setPosition(100,1.2*character.position.y-400);
        }
    }
    else if(static_cast<int>(etatMap)==2){
        if(character.position.y>WIN_Y-50){
            etatMap=static_cast<EtatM>(1);
            character.setPosition(WIN_X/4,100);
        }
        else if(character.position.y<=50){
            etatMap=static_cast<EtatM>(5);
            character.setPosition(100,3*WIN_Y/4);
        }
    }
    else if(static_cast<int>(etatMap)==5){
        if(character.position.x<50){
            etatMap=static_cast<EtatM>(2);
            character.setPosition(WIN_X/2,100);
        }
        else if(character.position.x>=WIN_X-50){
            etatMap=static_cast<EtatM>(8);
            character.setPosition(100,WIN_Y/2-25);
        }
    }
    else if(static_cast<int>(etatMap)==8){
        if(character.position.x<50){
            etatMap=static_cast<EtatM>(5);
            character.setPosition(WIN_X-100,3*WIN_Y/4);
        }
        else if(character.position.x>=WIN_X-50){
            etatMap=static_cast<EtatM>(11);
            character.setPosition(100,character.position.y/2);
        }
    }

    else if(static_cast<int>(etatMap)==3){///////////////////
        if(character.position.y>=character.position.x+WIN_Y-200){
            etatMap=static_cast<EtatM>(1);
            character.setPosition(WIN_X-400,300);
        }
        else if(character.position.y<=(250.f-100.f)/(9.f/10.f-3.f/4.f)/WIN_X*character.position.x+100-3.f/4.f*(250.f-100.f)/(9.f/10.f-3.f/4.f)){
            etatMap=static_cast<EtatM>(6);
            character.setPosition(150,WIN_Y-150);
        }
    }
    else if(static_cast<int>(etatMap)==6){
        if(character.position.x<50 || character.position.y>WIN_Y-100){
            etatMap=static_cast<EtatM>(3);
            character.setPosition(1500,250);
        }
        else if(character.position.y<=(250.f-100.f)/(9.f/10.f-3.f/4.f)/WIN_X*character.position.x+100-3.f/4.f*(250.f-100.f)/(9.f/10.f-3.f/4.f)){
            etatMap=static_cast<EtatM>(9);
            character.setPosition(600,WIN_Y-100);
        }
    }
    else if(static_cast<int>(etatMap)==9){
        if(character.position.y>WIN_Y-50){
            etatMap=static_cast<EtatM>(6);
            character.setPosition(WIN_X-500,180);
        }
        else if(character.position.y<=(250.f-100.f)/(9.f/10.f-3.f/4.f)/WIN_X*character.position.x+100-3.f/4.f*(250.f-100.f)/(9.f/10.f-3.f/4.f)){
            etatMap=static_cast<EtatM>(11);
            character.setPosition(100,WIN_Y-100);
        }
    }

    else if(static_cast<int>(etatMap)==4){
        if(character.position.x<50){
            etatMap=static_cast<EtatM>(1);
            character.setPosition(WIN_X-200,3*WIN_Y/4);
        }
        else if(character.position.x>=WIN_X-50){
            etatMap=static_cast<EtatM>(7);
            character.setPosition(100,7*WIN_Y/8);
        }
    }
    else if(static_cast<int>(etatMap)==7){
        if(character.position.x<50){
            etatMap=static_cast<EtatM>(4);
            character.setPosition(WIN_X-100,WIN_Y/2);
        }
        else if(character.position.y<=50){
            etatMap=static_cast<EtatM>(10);
            character.setPosition(WIN_X/2,WIN_Y-100);
        }
    }
    else if(static_cast<int>(etatMap)==10){
        if(character.position.y>WIN_Y-50){
            etatMap=static_cast<EtatM>(7);
            character.setPosition(4.7*WIN_X/6,100);
        }
        else if(character.position.y<=50){
            etatMap=static_cast<EtatM>(11);
            character.setPosition(1500,WIN_Y-100);
        }
    }

    else if(static_cast<int>(etatMap)==11){
        if(character.position.x<50 && character.position.y<WIN_Y/2){
            etatMap=static_cast<EtatM>(8);
            character.setPosition(WIN_X-100,WIN_Y/2-50);
        }
        else if(character.position.y>=character.position.x+WIN_Y-200){
            etatMap=static_cast<EtatM>(9);
            character.setPosition(WIN_X-400,300);
        }
        else if(character.position.x>WIN_X/2 && character.position.y>WIN_Y-50){
            etatMap=static_cast<EtatM>(10);
            character.setPosition(WIN_X/2,100);
        }
        else if(character.position.y<=(250.f-100.f)/(9.f/10.f-3.f/4.f)/WIN_X*character.position.x+100-3.f/4.f*(250.f-100.f)/(9.f/10.f-3.f/4.f)){
            character.setPosition(WIN_X-400,200);
            cout << "-1000 hp" << endl;
        }
    }
}

void CheckNextMap2New(Character& character){
    
    if(character.position.y<=0 && character.position.x<=0){
        character.setPosition(character.position.x,WIN_Y-100);
    }
    
    else if(static_cast<int>(etatMap)==1){
        if(character.position.y<50 && character.position.x<=WIN_X/2){
            etatMap=static_cast<EtatM>(2);
            character.setPosition(character.position.x*1.3+220,WIN_Y-100);
            top1=0;
        }
        else if(character.position.y<=(250.f-100.f)/(9.f/10.f-3.f/4.f)/WIN_X*character.position.x+100-3.f/4.f*(250.f-100.f)/(9.f/10.f-3.f/4.f)){
            etatMap=static_cast<EtatM>(3);
            character.setPosition(WIN_X/5,WIN_Y-100);
            mid1=0;
        }
        else if(character.position.x>WIN_X-50 && character.position.y>=WIN_Y/2){
            etatMap=static_cast<EtatM>(4);
            character.setPosition(100,1.2*character.position.y-400);
            bot1=0;
        }
    }
    else if(static_cast<int>(etatMap)==2){
        if(character.position.y>WIN_Y-50){
            if(top1==0){
                etatMap=static_cast<EtatM>(1);
                character.setPosition(WIN_X/4,100);    
            }
            else if(top1>0){
                etatMap=static_cast<EtatM>(2);
                character.setPosition(WIN_X/2,100);
                top1-=1;
            }
        }
        else if(character.position.y<=50){
            if(top1==2){
                etatMap=static_cast<EtatM>(5);
                character.setPosition(100,3*WIN_Y/4);
            }
            else if(top1>=0){
                top1+=1;
                etatMap=static_cast<EtatM>(2);
                character.setPosition(character.position.x,WIN_Y-100);
            }
        }
    }
    else if(static_cast<int>(etatMap)==5){
        if(character.position.x<50){
            etatMap=static_cast<EtatM>(2);
            character.setPosition(WIN_X/2,100);
            top1=2;
        }
        else if(character.position.x>=WIN_X-50){
            if(debugMode){
                etatMap=static_cast<EtatM>(8);
                character.setPosition(100,WIN_Y/2-25);
                top2=0;
            }else{
                if(!Jax1.doesExist){
                    etatMap=static_cast<EtatM>(8);
                    character.setPosition(100,WIN_Y/2-25);
                    top2=0;
                }
            }
            
        }
    }
    else if(static_cast<int>(etatMap)==8){
        if(character.position.x<50){
            if(top2==0){
                etatMap=static_cast<EtatM>(5);
                character.setPosition(WIN_X-100,3*WIN_Y/4);  
            }
            else if(top2>0){
                etatMap=static_cast<EtatM>(8);
                character.setPosition(WIN_X-100,WIN_Y/2-50);
                top2-=1;
            }
        }
        else if(character.position.x>=WIN_X-50){
            if(top2==2){
                etatMap=static_cast<EtatM>(11);
                character.setPosition(100,character.position.y/2);
            }
            else if(top2>=0){
                top2+=1;
                etatMap=static_cast<EtatM>(8);
                character.setPosition(100,WIN_Y/2-25);
            }
        }
    }

    else if(static_cast<int>(etatMap)==3){///////////////////
        if(character.position.y>=character.position.x+WIN_Y-200){
            if(mid1==0){
                etatMap=static_cast<EtatM>(1);
                character.setPosition(WIN_X-400,300);  
            }
            else if(mid1>0){
                etatMap=static_cast<EtatM>(3);
                character.setPosition(1500,250);
                mid1-=1;
            }
        }
        else if(character.position.y<=(250.f-100.f)/(9.f/10.f-3.f/4.f)/WIN_X*character.position.x+100-3.f/4.f*(250.f-100.f)/(9.f/10.f-3.f/4.f)){
            if(mid1==1){
                etatMap=static_cast<EtatM>(6);
                character.setPosition(150,WIN_Y-150);
            }
            else if(mid1>=0){
                mid1+=1;
                etatMap=static_cast<EtatM>(3);
                character.setPosition(WIN_X/5,WIN_Y-100);
            }
        }
    }
    else if(static_cast<int>(etatMap)==6){
        if(character.position.x<50 || character.position.y>WIN_Y-100){
            etatMap=static_cast<EtatM>(3);
            character.setPosition(1500,250);
            mid1=1;
        }
        else if(character.position.y<=(250.f-100.f)/(9.f/10.f-3.f/4.f)/WIN_X*character.position.x+100-3.f/4.f*(250.f-100.f)/(9.f/10.f-3.f/4.f)){
            if(debugMode){
                etatMap=static_cast<EtatM>(9);
                character.setPosition(600,WIN_Y-100);
            }else{
                if(!Katarina1.doesExist){
                    etatMap=static_cast<EtatM>(9);
                    character.setPosition(600,WIN_Y-100);
                }
            }
        }
    }
    else if(static_cast<int>(etatMap)==9){
        if(character.position.y>WIN_Y-50){
            etatMap=static_cast<EtatM>(6);
            character.setPosition(WIN_X-500,180);
        }
        else if(character.position.y<=(250.f-100.f)/(9.f/10.f-3.f/4.f)/WIN_X*character.position.x+100-3.f/4.f*(250.f-100.f)/(9.f/10.f-3.f/4.f)){
            if(debugMode){
                etatMap=static_cast<EtatM>(11);
                character.setPosition(100,WIN_Y-100);
            }else{
                if(!Pantheon1.doesExist){
                    etatMap=static_cast<EtatM>(11);
                    character.setPosition(100,WIN_Y-100);
                }
            }
        }
    }

    else if(static_cast<int>(etatMap)==4){
        if(character.position.x<50){
            if(bot1==0){
                etatMap=static_cast<EtatM>(1);
                character.setPosition(WIN_X-200,3*WIN_Y/4);
            }
            else if(bot1>0){
                etatMap=static_cast<EtatM>(4);
                character.setPosition(WIN_X-100,WIN_Y/2);
                bot1-=1;
            }
        }
        else if(character.position.x>=WIN_X-50){
            if(bot1==2){
                etatMap=static_cast<EtatM>(7);
                character.setPosition(100,7*WIN_Y/8);
            }
            else if(bot1>=0){
                bot1+=1;
                etatMap=static_cast<EtatM>(4);
                character.setPosition(100,WIN_Y/2);
            }
        }
    }
    else if(static_cast<int>(etatMap)==7){
        if(character.position.x<50){
            etatMap=static_cast<EtatM>(4);
            character.setPosition(WIN_X-100,WIN_Y/2);
            bot1=2;
        }
        else if(character.position.y<=50){
            if(debugMode){
                    etatMap=static_cast<EtatM>(10);
                    character.setPosition(WIN_X/2,WIN_Y-100);
                    bot2=0;
            }else{
                if(!Darius1.doesExist){
                    etatMap=static_cast<EtatM>(10);
                    character.setPosition(WIN_X/2,WIN_Y-100);
                    bot2=0;
                }
            }
        }
    }
    else if(static_cast<int>(etatMap)==10){
        if(character.position.y>WIN_Y-50){
            if(bot2==0){
                etatMap=static_cast<EtatM>(7);
                character.setPosition(4.7*WIN_X/6,100);
            }
            else if(bot2>0){
                etatMap=static_cast<EtatM>(10);
                character.setPosition(WIN_X/2,100);
                bot2-=1;
            }
        }
        else if(character.position.y<=50){

            if(bot2==2){
                etatMap=static_cast<EtatM>(11);
                character.setPosition(1500,WIN_Y-100);
            }
            else if(bot2>=0){
                
                if(debugMode){
                    bot2+=1;
                    etatMap=static_cast<EtatM>(10);
                    character.setPosition(WIN_X/2,WIN_Y-100);
            }else{
                if(!Ashe1.doesExist){
                    bot2+=1;
                    etatMap=static_cast<EtatM>(10);
                    character.setPosition(WIN_X/2,WIN_Y-100);
                }
            }
            }
        }
    }

    else if(static_cast<int>(etatMap)==11){
        if(character.position.x<50 && character.position.y<WIN_Y/2){
            etatMap=static_cast<EtatM>(8);
            character.setPosition(WIN_X-100,WIN_Y/2-50);
            top2=2;
        }
        else if(character.position.y>=character.position.x+WIN_Y-200){
            etatMap=static_cast<EtatM>(9);
            character.setPosition(WIN_X-400,300);
        }
        else if(character.position.x>WIN_X/2 && character.position.y>WIN_Y-50){
            etatMap=static_cast<EtatM>(10);
            character.setPosition(WIN_X/2,100);
            bot2=2;
        }
        else if(character.position.y<=(250.f-100.f)/(9.f/10.f-3.f/4.f)/WIN_X*character.position.x+100-3.f/4.f*(250.f-100.f)/(9.f/10.f-3.f/4.f)){
            character.setPosition(WIN_X-400,200);
            cout << "-1000 hp" << endl;
        }
    }
    
    
    
}

void afficheGachaList(int pageGacha, sf::RenderWindow& window){
    int nombreAffiche=0;
    if(pageGacha==static_cast<int>(charaList.size()/15)){
        nombreAffiche=charaList.size()%15;
    }
    else{nombreAffiche=15;}
    for (int i =0 ; i < nombreAffiche; ++i) {
        charaList[pageGacha*15+i].setPosition((i%5+2)*WIN_X/8,(i/5+2)*WIN_Y/5-125);
        window.draw(charaList[pageGacha*15+i]);
    }

}