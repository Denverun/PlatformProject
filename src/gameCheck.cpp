#include "gameCheck.h"

float speedEnemy= 2.f;
bool directionBool=false;
int isMoving=0,isMovingEnemy=0;
dirEtat direc=dirEtat::Right, direcEnemy=dirEtat::Right;

float visionRange=450.f, hitRange = 30.f;

Collect coin1,coin2,coin3,coin4,sausage1,spike1,spike2,burger;

sf::Sprite destroyable;

bool characDeath=false, enemyDeath=false;

void CheckGame(Input &input){
    CheckCollect(character1); // Regarde si les collectibles ont été actionnés, s'occupe du back
    characKey(character1, volibear, input); // Effectue les actions en lien avec les touches du perso
    characMove(character1); // Bouge le personnage
    checkBordures(character1); // Vérifie les bordures
    
    if (etatMap == EtatM::GameDR4 && volibear.health>0){
        CheckEnemy(volibear, character1); // Déplace l'ennemi et vérifie les bordures
    }
    CheckDeath(character1); // Vérifie le statut du personnage
}

void CheckCollect(Character& character){
    if(etatMap == EtatM::GameDR1){
        coin1.checkCoin(character, coinStock);
        coin2.checkCoin(character, coinStock);
    }
    else if(etatMap == EtatM::GameDR2){
        coin3.checkCoin(character, coinStock);
    }
    else if(etatMap == EtatM::GameDR3){
        coin3.checkCoin(character, coinStock);
        coin4.checkCoin(character, coinStock);
    }
    else if(etatMap == EtatM::GameDR7){
        spike1.checkSpike(character,maxHealth);
        spike2.checkSpike(character,maxHealth);
        sausage1.checkEat(character,maxHealth);
        burger.checkEat(character,maxHealth);
        if(!burger.getExists()){
            etatMap = EtatM::DRVictory;
            mainMusic.stop();
            DRVMusic.play();
            coinStock+=3;
        }
    }
}

void characKey(Character& character, Enemy& enemy, Input& input){
    if(input.GetButton().p== true){
        character.setPosition(WIN_X/2,WIN_Y/2);
    }
    if(input.GetButton().z== true){
        if(character.attackCD.getElapsedTime().asSeconds()>1.f){
            character.attack();
            hitHacheSound.stop();
            hitHacheSound.play();
            if(checkCollision(character.sprite,enemy.sprite) && enemy.health>0 && etatMap==EtatM::GameDR4){
                enemy.loseHealth(1,lostHealth,enemy.position.x-30,enemy.position.y-150);
                healthAnimation.restart();
            }
            destroyable.setTextureRect(sf::IntRect(690,310,790-690,370-310));
            destroyable.setPosition(690,310);
            if(checkCollision(character.sprite,destroyable) && etatMap==EtatM::GameDR2){
                casse=true;
                etatMap=EtatM::GameDR3;
                //cout << "detruit" << endl;
            }
        }
    }

    else if(etatMap == EtatM::DRVictory){
           
    }
}

void characMove(Character& character){
    if(input.GetButton().left== true){
        if(direc==dirEtat::Right){
            directionBool=true;
            direc=dirEtat::Left;
        }
        else{
            character.move(-character.speed,0);
            isMoving+=1;
        }
    }
    if(input.GetButton().right== true){
        if(direc==dirEtat::Left){
            directionBool=true;
            direc=dirEtat::Right;
        }
        else{
            character.move(character.speed,0);
            isMoving+=1;
        }
    }
    if(input.GetButton().down== true){
        character.move(0,character.speed);
    }
    if(input.GetButton().up== true){
        character.move(0,-character.speed);
    }

    if(directionBool){
        rotat(character.sprite);
    }
}

void checkBordures(Character& character){
    if(etatMap == EtatM::GameDR1){
        if(!pointInPolygon(character.position,border1)){
            moveBack(character);
        }
    }
    else if(etatMap == EtatM::GameDR2){
        if(!pointInPolygon(character.position,border2)){
            moveBack(character);
        }
    }
    else if(etatMap == EtatM::GameDR3){
        if(!pointInPolygon(character.position,border3)){
            moveBack(character);
        }
    }
    else if(etatMap == EtatM::GameDR4){
        if(!pointInPolygon(character.position,border4)){
            moveBack(character);
        }
    }
    else if(etatMap == EtatM::GameDR5){
        if(!pointInPolygon(character.position,border5) || pointInPolygon(character.position,border5wall1) || pointInPolygon(character.position,border5wall2)){
            moveBack(character);
        }
    }
    else if(etatMap == EtatM::GameDR6){
        if(!pointInPolygon(character.position,border6) || pointInPolygon(character.position,border6wall)){
            moveBack(character);
        }
    }
    else if(etatMap == EtatM::GameDR7){
        if(!pointInPolygon(character.position,border7) || pointInPolygon(character.position,border7wall)){
            moveBack(character);
        }
    }
}

void CheckEnemy(Enemy& enemy, Character& character){
    
    sf::Vector2f vecteurDistance = character.position-enemy.getPosition();
    float distance = sqrt(vecteurDistance.x*vecteurDistance.x+vecteurDistance.y*vecteurDistance.y);
    if(distance<=visionRange && distance>hitRange){
        
        isMovingEnemy+=1;
        enemy.move(vecteurDistance.x/distance*speedEnemy,0);
        if(!pointInPolygon(enemy.getPosition(),border4)){
            enemy.move(-vecteurDistance.x/distance*speedEnemy,0);
        }
        enemy.move(0,vecteurDistance.y/distance*speedEnemy);
        if(!pointInPolygon(enemy.getPosition(),border4)){
            enemy.move(0,-vecteurDistance.y/distance*speedEnemy);
        }
    }
    else if(distance<=hitRange){
        //cout << "Tape !!" << endl;
        isMovingEnemy=0;
    }
    else{
        isMovingEnemy=0;
    }
    enemy.sprite.setScale(std::abs(enemy.sprite.getScale().x)*signe(vecteurDistance.x),enemy.sprite.getScale().y);
}

void rotat(sf::Sprite &perso){
    if (direc==dirEtat::Left){
        perso.setScale(-std::abs(perso.getScale().x),perso.getScale().y);
    }
    else{
        perso.setScale(std::abs(perso.getScale().x), perso.getScale().y);
    }

    directionBool=false;
}

void CheckDeath(Character& character){
    if (character.health<=0){
        etatMap = EtatM::GameOverDR;
        character.speed=0.1f;
        character.health=maxHealth;
        coinStock=max(coinStock-1,0);

        mainMusic.pause();
        LolDMusic.play();
    }
}

bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
    return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

bool pointInPolygon(const sf::Vector2f& point, const sf::VertexArray& polygon) {
    // La méthode de Ray-casting pour tester si un point est dans un polygone
    bool inside = false;
    for (size_t i = 0, j = polygon.getVertexCount() - 1; i < polygon.getVertexCount(); j = i++) {
        const sf::Vector2f& v1 = polygon[i].position;
        const sf::Vector2f& v2 = polygon[j].position;

        // Vérifier si le point est dans l'intervalle vertical du segment de ligne
        if (((v1.y > point.y) != (v2.y > point.y)) &&
            (point.x < (v2.x - v1.x) * (point.y - v1.y) / (v2.y - v1.y) + v1.x)) {
            inside = !inside;
        }
    }
    return inside;
}

void moveBack(Character& character){
    if(input.GetButton().left== true){
        character.move(character.speed,0);
        isMoving-=1;
        
    }
    if(input.GetButton().right== true){
        character.move(-character.speed,0);
        isMoving-=1;
        
    }
    if(input.GetButton().down== true){
        character.move(0,-character.speed);
    }
    if(input.GetButton().up== true){
        character.move(0,character.speed);
    }
}

void checkBordures2(Character& character){
    if(etatMap == static_cast<EtatM>(1)){
        if(!pointInPolygon(character.position,borderL1)){
            moveBack(character);
        }
    }
    else if(etatMap == static_cast<EtatM>(2)){
        if(!pointInPolygon(character.position,borderL2)){
            moveBack(character);
        }
    }
    else if(etatMap == static_cast<EtatM>(3)){
        if(!pointInPolygon(character.position,borderL3)){
            moveBack(character);
        }
    }
    else if(etatMap == static_cast<EtatM>(4)){
        if(!pointInPolygon(character.position,borderL4)){
            moveBack(character);
        }
    }
    else if(etatMap == static_cast<EtatM>(5)){
        if(!pointInPolygon(character.position,borderL5)){
            moveBack(character);
        }
    }
    else if(etatMap == static_cast<EtatM>(6)){
        if(!pointInPolygon(character.position,borderL6)){
            moveBack(character);
        }
    }
    else if(etatMap == static_cast<EtatM>(7)){
        if(!pointInPolygon(character.position,borderL7)){
            moveBack(character);
        }
    }
    else if(etatMap == static_cast<EtatM>(8)){
        if(!pointInPolygon(character.position,borderL8)){
            moveBack(character);
        }
    }
    else if(etatMap == static_cast<EtatM>(9)){
        if(!pointInPolygon(character.position,borderL9)){
            moveBack(character);
        }
    }
    else if(etatMap == static_cast<EtatM>(10)){
        if(!pointInPolygon(character.position,borderL10)){
            moveBack(character);
        }
    }
    else if(etatMap == static_cast<EtatM>(11)){
        if(!pointInPolygon(character.position,borderL11)){
            moveBack(character);
        }
    }

}

void fightPart(Character& character,Enemy& enemy, int mapNumber){
    if(lolMaptype==2){
        if(newFight){
            infoString1="Le combat commence";
            infoString2="Appuyez sur la competence souhaitee";
            infoString3="";
            newFight=false;
            character.attack1=character.attack2=character.attack3=0;
        }
        
        if(turnClock.getElapsedTime().asSeconds()>=turnDelay){
            
            //GameCheck

            if(characDeath){
                characDeath=false;
                
                fractionCoinLost+=1;
                if(fractionCoinLost==3){
                    coinStock=max(coinStock-1,0);
                    fractionCoinLost=0;
                }
                
                etatMap = static_cast<EtatM>(1);
                character.setPosition(200,WIN_Y-100.f);
                lolMaptype=1;
                character.health=character.maxHealth;
                newFight=true;
                isStun=false;
                isStunEnemy=false;

                Jax1.health=400,Jax1.doesExist=true,Jax1.turnNo=0;
                Katarina1.health=Katarina1.maxHealth,Katarina1.doesExist=true,Katarina1.turnNo=0;
                Darius1.health=Darius1.maxHealth,Darius1.doesExist=true,Darius1.turnNo=0;
                Pantheon1.health=Pantheon1.maxHealth,Pantheon1.doesExist=true,Pantheon1.turnNo=0;
                Ashe1.health=Ashe1.maxHealth,Ashe1.doesExist=true,Ashe1.turnNo=0;

                LolFightMusic1.pause();
                LolFightMusic2.pause();
                LolFightMusic3.pause();
                LolFightMusic4.pause();
                LolFightMusic5.pause();
                LolMapMusic.play();
            }
            else if(character.health<=0){
                characDeath=true;
                turnClock.restart();
                infoString1="Vous n'avez plus de PV";
                infoString2="Vous avez ete vaincu";
                infoString3="";

            }
            else if (enemyDeath){
                enemyDeath=false;
                etatMap = static_cast<EtatM>(mapNumber);
                lolMaptype=1;
                
                if(!enemy.killed){
                    coinStock+=2;
                    enemy.killed=true;
                }
                enemy.doesExist=false;
                newFight=true;
                isStun=false;
                isStunEnemy=false;

                LolFightMusic1.pause();
                LolFightMusic2.pause();
                LolFightMusic3.pause();
                LolFightMusic4.pause();
                LolFightMusic5.pause();
                LolMapMusic.play();
            }
            else if(enemy.health<=0){
                enemyDeath=true;
                turnClock.restart();
                infoString1="L'ennemi n'a plus de PV";
                infoString2="Il a ete vaincu";
                infoString3="";
                
            }
            else{
                //Input
            }
        }
        
    }
}

void enemyTurn(Enemy& enemy, Character& character){
if(enemy.health>0){
    infoString3="";
if(isStunEnemy){
    infoString1="L'ennemi est stunned !";
    infoString2="Il ne peut pas jouer";
    infoString3="";
    isStunEnemy=false;
}
else{
    
    if(enemy.id==6){ // Katarina
        if(enemy.turnNo==0){
            infoString1="L'ennemi lance son Q";
            infoString2="Une dague vous atteint et se pose";
            character.health-=100;
        }
        else if(enemy.turnNo==1){
            infoString1="L'ennemi lance son E";
            infoString3="Elle se rapproche de vous";
            infoString2="Elle prend sa dague et vous blesse";
            character.health-=200;
        }
        else if(enemy.turnNo>=2){
            character.health-=400;
            infoString1="L'ennemi lance son R";
            infoString2="Elle vous taillade de partout";
        }
    }

    if(enemy.id==7){ // Darius
        if(enemy.turnNo==0){
            infoString1="L'ennemi lance son Z";
            infoString2="Vous subissez un violent coup de hache";
            character.health-=200;
        }
        else if(enemy.turnNo==1){
            infoString1="L'ennemi lance son Q";
            if(isEscape){
                infoString2="Et rate son violent coup de hache";    
            }
            else{
                infoString3="L'ennemi vous violente avec sa hache";
                infoString2="Il se delecte de votre sang";
                character.health-=300;
                enemy.health+=150;
            }
        }
        else if(enemy.turnNo==2){
            character.health-=150;
            infoString1="L'ennemi vous envoie plusieurs coups";
            infoString2="Votre sang coule fortement";
        }
        else if(enemy.turnNo==3){
            character.health-=500;
            infoString1="L'ennemi lance son R";
            infoString3="Il profite de vos plaies";
            infoString2="pour essayer de vous executer";
        }
        else if(enemy.turnNo>=3){
            character.health-=300;
            infoString1="L'ennemi taillade vos plaies";
            infoString2="";
        }
    }

    if(enemy.id==9){ // Pantheon
        if(enemy.turnNo==0){
            infoString1="L'ennemi lance son E";
            infoString3="Vous subissez un violent coup de bouclier";
            infoString2="Cela vous laisse dans un etat second";
            character.health-=100;
            isStun=true;
        }
        else if(enemy.turnNo==1){
            infoString1="Vous etes a portee d'une tour ennemie";
            infoString3="Elle vous prend pour cible";
            infoString2="Et vous met a mal";
            character.health-=500;
        }
        else if(enemy.turnNo>=2){
            character.health-=400;
            infoString1="L'ennemi lance son Q";
            infoString2="Et vous lance une lance";
        }
        else{}
    }

    if(enemy.id==10){ // Ashe
        if(enemy.turnNo==0){
            infoString1="L'ennemi lance son R";
            infoString3="";
            if(isEscape){
                infoString2="Et rate sa grande fleche de glace";    
            }
            else{
                infoString2="Vous subissez une grande fleche de glace";
                character.health-=150;
                isStun=true;
            }
        }
        else if(enemy.turnNo>=1){
            infoString1="L'ennemi lance son Q";
            infoString3="L'ennemi vous coche plusieurs fleches de glace";
            infoString2="Cela a pour effet de vous ralentir";
            character.health-=200;
        }
    }

    enemy.turnNo+=1;
    
}
if(enemy.id==5){ // Jax
    if(character.id==1){
        infoString1="L'ennemi a flash vos spells";
        infoString3="Il a utilise son auto cheate";
        infoString2="Vous a tue et a mange votre oeuf";
    }
    else if(character.id==2){
        infoString1="L'ennemi est immunise contre les sorts AD";
        infoString3="Il a utilise son auto cheate";
        infoString2="Vous etes mort, on ne tue pas Jax";
    }
    else{
        infoString1="Reve pas";
        infoString2="Vous etes mort";
    }
    character.health=0;
    LolFightMusic1.stop();
}
}
playerTurn=true;
turnClock.restart();

}

std::string gachaRes(int n){
    switch (n)
    {
    case 1:
        return "res/images/gacha/5-7Frieren.jpg";
        break;
    case 2:
        return "res/images/gacha/5-9Kirby.png";
        break;
    case 3:
        return "res/images/gacha/5w-1RukiasBlade.jpg";
        break;
    case 4:
        return "res/images/gacha/5w-1RukiasBlade.jpg";
        break;
    case 5:
        return "res/images/gacha/5-8Evoli.png";
        break;
    case 6:
        return "res/images/gacha/5-8Evoli.png";
        break;
    case 7:
        return "res/images/gacha/5-2Zed.png";
        break;
    case 8:
        return "res/images/gacha/5-2Zed.png";
        break;
    case 9:
        return "res/images/gacha/5-3Veigar.png";
        break;
    case 10:
        return "res/images/gacha/5-3Veigar.png";
        break;
    case 11:
        return "res/images/gacha/5-5Morde.png";
        break;
    case 12:
        return "res/images/gacha/5-4Neeko.png";
        break;
    case 13:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 14:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 15:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 16:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 17:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 18:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 19:
        return "res/images/gacha/5-6Nanika.png";
        break;
    
    default:
        return "res/images/gacha/4-1Aizen.png";
        break;
    }
}

std::string gachaResGuaranteed(int n){
    switch (n)
    {
    case 1:
        return "res/images/gacha/5-7Frieren.jpg";
        break;
    case 2:
        return "res/images/gacha/5-9Kirby.png";
        break;
    case 3:
        return "res/images/gacha/5w-1RukiasBlade.jpg";
        break;
    case 4:
        return "res/images/gacha/5w-1RukiasBlade.jpg";
        break;
    case 5:
        return "res/images/gacha/5-8Evoli.png";
        break;
    case 6:
        return "res/images/gacha/5-8Evoli.png";
        break;
    case 7:
        return "res/images/gacha/5-2Zed.png";
        break;
    case 8:
        return "res/images/gacha/5-2Zed.png";
        break;
    case 9:
        return "res/images/gacha/5-3Veigar.png";
        break;
    case 10:
        return "res/images/gacha/5-3Veigar.png";
        break;
    case 11:
        return "res/images/gacha/5-5Morde.png";
        break;
    case 12:
        return "res/images/gacha/5-4Neeko.png";
        break;
    case 13:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 14:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 15:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 16:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 17:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 18:
        return "res/images/gacha/5-1Aizen.png";
        break;
    case 19:
        return "res/images/gacha/5-6Nanika.png";
        break;
    case 20:
        return "res/images/gacha/5-2Zed.png";
        break;
    case 21:
        return "res/images/gacha/5-3Veigar.png";
        break;
    
    default:
        return "res/images/gacha/4-1Aizen.png";
        break;
    }
}

