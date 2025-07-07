#include "collect.h"

sf::Clock coinAnimation,eatAnimation,spikeAnimation,SpikeClock;
sf::Text gainCoin,gainHP,loseHP;
sf::Music coinSound,eatSound,hitSound;

// Constructeur
Collect::Collect()
    : value(1), position({0,0}), sprite1(), sprite2(), exists(true) {
    sprite1.setPosition(position.x,position.y);
}

Collect::Collect(int val, const sf::Sprite& spriteX, const sf::Sprite& spriteY, sf::Vector2i pos)
    : value(val), position(pos), sprite1(spriteX), sprite2(spriteY), exists(true) {
    sprite1.setPosition(position.x,position.y);
    sprite2.setPosition(position.x,position.y);
}

// Getter pour la valeur
int Collect::getValue() const {return value;}

// Getter pour la position
sf::Vector2f Collect::getPosition() const {return position;}

// Getter pour le sprite
const sf::Sprite& Collect::getSprite1() const {return sprite1;}
const sf::Sprite& Collect::getSprite2() const {return sprite2;}

bool Collect::getExists(){return exists;}

// Setter pour la position
void Collect::setPosition(sf::Vector2f newPos) {
    position = newPos;
    sprite1.setPosition(newPos);
    sprite2.setPosition(newPos);
}

// Setter pour le sprite
void Collect::setSprite(std::string txt, sf::IntRect rect) {
    sprite1.setTexture(TextureManager::getInstance().getTexture(txt));
    sprite1.setTextureRect(rect);
}

void Collect::collect(){exists=false;}
void Collect::appear(){exists=true;}

// Dessiner la pièce sur la fenêtre
void Collect::draw(sf::RenderWindow& window) const {
    window.draw(sprite1);
}

void Collect::getAffiche(sf::Text& txt, std::string str, const sf::Color& color, float posX, float posY){
    txt.setFont(font); // Changer la police
    txt.setString(str); // Changer le texte
    txt.setCharacterSize(30); //La taille
    txt.setFillColor(color);
    sf::FloatRect textBounds = txt.getLocalBounds();
    txt.setOrigin(textBounds.width / 2, textBounds.height / 2);
    txt.setPosition(posX,posY);
}

void Collect::coinGetAffiche(sf::Text& txt){
    getAffiche(txt,"+"+std::to_string(value)+" !",sf::Color::Yellow,position.x,position.y+100);
}

void Collect::eatGetAffiche(sf::Text& txt, Character& character){
    getAffiche(txt,"+"+std::to_string(value)+" !",sf::Color::Red,character.position.x-100,character.position.y-80);
}

void Collect::spikeGetAffiche(sf::Text& txt, Character& character){
    getAffiche(txt,std::to_string(value)+" !",sf::Color::Red,character.position.x-100,character.position.y-80);
}

void Collect::addCoins(int &coinStock){coinStock+=value;}

void Collect::addHP(Character& character, int maxHealth){character.health=std::min(character.health+value,maxHealth);}

void Collect::checkCoin(Character& character, int& coinStock){
    if(exists){
        if (character.sprite.getGlobalBounds().intersects(sprite1.getGlobalBounds())){
            this->collect();
            this->addCoins(coinStock);
            coinAnimation.restart();
            this->coinGetAffiche(gainCoin);
            coinSound.stop();
            coinSound.play();
        }
    }
}

void Collect::checkEat(Character& character, int maxHealth){
    if(exists){
        if (character.sprite.getGlobalBounds().intersects(sprite1.getGlobalBounds())){
            this->collect();
            this->addHP(character, maxHealth);
            eatAnimation.restart();
            this->eatGetAffiche(gainHP, character);
            eatSound.stop();
            eatSound.play();
        }
    }
}

void Collect::checkSpike(Character& character, int maxHealth){
    if(SpikeClock.getElapsedTime().asSeconds()>3.f){
        if (character.sprite.getGlobalBounds().intersects(sprite1.getGlobalBounds())){
            this->appear();
            this->addHP(character, maxHealth);
            character.move((character.position.x-sprite1.getPosition().x)/2,(character.position.y-sprite1.getPosition().y)/2);
            spikeAnimation.restart();
            this->spikeGetAffiche(loseHP, character);
            hitSound.stop();
            hitSound.play();
        }
    }
}

void Collect::drawCollect(float t1, float t2, float time, sf::RenderWindow &window, sf::Text& drawing, sf::Clock& animation){
    if(this->getExists()){
        if(time>t1 && time<t2){
            window.draw(this->getSprite2());
        }
        else{
            window.draw(this->getSprite1());
        }
    }
    else{
        if(animation.getElapsedTime().asSeconds()<2.f){
            window.draw(drawing);
        }
    }
}

void Collect::drawSpike(float t1, float t2, float time, sf::RenderWindow &window, sf::Text& drawing, sf::Clock& animation){
    if(time>t1 && time<t2){
        window.draw(sprite2);
    }
    else{
        window.draw(sprite1);
    }

    if(exists){
        if(animation.getElapsedTime().asSeconds()<2.f){
            window.draw(drawing);
        }
        else{
            this->collect();
        }
    }
}