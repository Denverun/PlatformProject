#include "input.h"

// Variables

Input input;

void listenInput(sf::RenderWindow &window){
    sf::Event event; // Objet pour gérer l'évènement

    // Ecoute des évènements, touches
    while (window.pollEvent(event))
    {   
        // Gestion des évènements
        if(etatMap==EtatM::Accueil){
            input.InputHandlerHome(event, window); 
        }
        else if(etatMap==EtatM::AccueilDR){
            input.InputHandlerHomeDR(event, window); 
        }
        else if(etatMap==EtatM::ValideDR){
            input.InputHandlerHomeVDR(event, window); 
        }
        else if(etatMap==EtatM::GameDR1){
            input.InputHandlerG1DR(event, window); 
        }
        else if(etatMap==EtatM::GameDR2){
            input.InputHandlerG2DR(event, window); 
        }
        else if(etatMap==EtatM::GameDR3){
            input.InputHandlerG3DR(event, window); 
        }
        else if(etatMap==EtatM::GameDR4){
            input.InputHandlerG4DR(event, window); 
        }
        else if(etatMap==EtatM::GameDR5){
            input.InputHandlerG5DR(event, window); 
        }
        else if(etatMap==EtatM::GameDR6){
            input.InputHandlerG6DR(event, window); 
        }
        else if(etatMap==EtatM::GameDR7){
            input.InputHandlerG7DR(event, window); 
        }
        else if(etatMap==EtatM::GameOverDR){
            input.InputHandlerDRDefeat(event, window); 
        }
        else if(etatMap==EtatM::DRVictory){
            input.InputHandlerDRV(event, window); 
        }
    }
}

// Définition Constructeur
Input::Input()
{
    button.left = button.right = button.up = button.down = button.attack = button.escape = button.spacebar = false;
}

// Définition Fonctions de classe
Input::Button Input::GetButton(void) const {
    return button;
}

// Définition Fonctions de classe
void Input::ResetButton(void) {
    button.left = button.right = button.up = button.down = button.attack = button.escape = button.spacebar = false;
}

void Input::InputHandlerHome(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);
    // Ecoute Souris (statique)
    
    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (boutonAccueil.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                etatMap = EtatM::AccueilDR;
            }
        }
    }
    
    // Ecoute appui touches (statique)
    if(event.key.code == sf::Keyboard::Space){
        button.spacebar=true;
    }
}

void Input::InputHandlerHomeDR(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);
    // Ecoute Souris (statique)
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (boutonTuto.getGlobalBounds().contains(mousePos.x, mousePos.y)) {etatMap = EtatM::ValideDR;}
}

void Input::InputHandlerHomeVDR(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);

    // Ecoute Souris (statique)
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (boutonTuto.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        if(event.type == sf::Event::MouseButtonPressed){etatMap = EtatM::GameDR1;}
    }
    else{
        etatMap = EtatM::AccueilDR;
    }
}

void Input::InputHandlerG1DR(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);
    changeMap(EtatM::AccueilDR,EtatM::GameDR2, event);
    Input::touchesDyn(event, window);
}

void Input::InputHandlerG2DR(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);
    changeMap(EtatM::GameDR1,EtatM::GameDR3, event);
    Input::touchesDyn(event, window);
}

void Input::InputHandlerG3DR(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);
    changeMap(EtatM::GameDR2,EtatM::GameDR4, event);
    Input::touchesDyn(event, window);
}

void Input::InputHandlerG4DR(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);
    changeMap(EtatM::GameDR3,EtatM::GameDR5, event);
    Input::touchesDyn(event, window);
}

void Input::InputHandlerG5DR(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);
    changeMap(EtatM::GameDR4,EtatM::GameDR6, event);
    Input::touchesDyn(event, window);
}

void Input::InputHandlerG6DR(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);
    changeMap(EtatM::GameDR5,EtatM::GameDR7, event);
    Input::touchesDyn(event, window);
}

void Input::InputHandlerG7DR(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);
    changeMap(EtatM::GameDR6,EtatM::DRVictory, event);
    Input::touchesDyn(event, window);
}

void Input::InputHandlerDRV(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);

    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            gamemode=2;
            //cout << "jeu2" << endl;
            DRVMusic.stop();
            MathMusic.play();
        }
    }
}

void Input::InputHandlerDRDefeat(sf::Event &event, sf::RenderWindow &window){
    clicFermer(event, window);
    
    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (txtRespawn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                etatMap = EtatM::AccueilDR;
                button.left=button.right=button.up=button.down=false;
                character1.position={float(WIN_X)/2,float(WIN_Y)/2};

                LolDMusic.pause();
                mainMusic.play();
            }
        }
    }
    
    // Ecoute appui touches (statique)
    if(event.key.code == sf::Keyboard::Space){
            button.spacebar=true;
            cout << "ez" << endl;
        }
}

// ------------------------------------------------------------------------------------------

void clicFermer(sf::Event &event, sf::RenderWindow &window){
    if (event.type == sf::Event::Closed) // Fenêtre fermée
        window.close();
}

void Input::touchesDyn(sf::Event &event, sf::RenderWindow &window){
    // Ecoute de l'appui d'une touche de clavier (dynamique, pour jeu)
    if (event.type == sf::Event::KeyPressed){
        // Verifie boutons en appui
        switch(event.key.code){
            case sf::Keyboard::Escape:
                button.escape = true;
                break;
            case sf::Keyboard::Left:
                button.left = true;
                break;
            case sf::Keyboard::Right:
                button.right = true;
                break;
            case sf::Keyboard::Down:
                button.down = true;
                break;
            case sf::Keyboard::Up:
                button.up = true;
                break;
            case sf::Keyboard::P:
                button.p = true;
                break;
            case sf::Keyboard::A:
                button.a = true;
                break;
            case sf::Keyboard::Z:
                button.z = true;
                break;
            case sf::Keyboard::E:
                button.e = true;
                break;
            case sf::Keyboard::R:
                button.r = true;
                break;
            case sf::Keyboard::D:
                button.d = true;
                break;
            case sf::Keyboard::F:
                button.f = true;
                break;
            default:
                break;
        }
    }

    // Ecoute relâchement d'une touche de clavier (dynamique, pour jeu)
    if (event.type == sf::Event::KeyReleased){
        // Verifie lorsque relache

        switch(event.key.code){
            case sf::Keyboard::Escape:
                button.escape = false;
                break;
            case sf::Keyboard::Left:
                button.left = false;
                break;
            case sf::Keyboard::Right:
                button.right = false;
                break;
            case sf::Keyboard::Down:
                button.down = false;
                break;
            case sf::Keyboard::Up:
                button.up = false;
                break;
            case sf::Keyboard::P:
                button.p = false;
                break;
            case sf::Keyboard::A:
                button.a = false;
                break;
            case sf::Keyboard::Z:
                button.z = false;
                break;
            case sf::Keyboard::E:
                button.e = false;
                break;
            case sf::Keyboard::R:
                button.r = false;
                break;
            case sf::Keyboard::D:
                button.d = false;
                break;
            case sf::Keyboard::F:
                button.f = false;
                break;
            default:
                break;
        }
    }
}

void changeMap(const EtatM& etat1, const EtatM& etat2, sf::Event& event){
    if(debugMode){
        if(event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                etatMap = etat2;
                if(etat2==EtatM::DRVictory){
                    mainMusic.stop();
                    DRVMusic.play();
                }
                
            }
            else if (event.mouseButton.button == sf::Mouse::Right){
                etatMap = etat1;
            }
        }
    }
}


//--------------------------------------------------

void listenInputMath(sf::RenderWindow &window){
    sf::Event event; // Objet pour gérer l'évènement

    // Ecoute des évènements, touches
    while (window.pollEvent(event))
    {   
        input.InputHandlerCalculus(event, window);
        
    }
}

void Input::InputHandlerCalculus(sf::Event &event, sf::RenderWindow &window){

    clicFermer(event, window);
    
    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (boutonVecteur1.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                buttonValue=1;
            }
            else if (boutonVecteur2.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                buttonValue=2;
            }
            else if (boutonVecteur3.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                buttonValue=3;
            }
            else if (boutonConfirmer.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                //valueVecteur1==0 && valueVecteur2==45 && valueVecteur3==-45  //Ancien
                if(valueVecteur1==12 && valueVecteur2==0 && valueVecteur3==12){
                    gamemode=3;
                    etatMap=static_cast<EtatM>(0);
                    lolMaptype=0;
                    coinStock+=4;
                    MathMusic.stop();
                    LolMapMusic.play();
                }
                else{
                    falseClock.restart();
                    coinStock=max(coinStock-1,0);
                }
            }
        }
    }
    
    inputValue=-2;

    if (event.type == sf::Event::TextEntered){
        // Vérifier si la touche est un chiffre ou une lettre, ici on limite aux chiffres
        if (event.text.unicode >= '0' && event.text.unicode <= '9')
        {
            inputValue = event.text.unicode-'0';
        }
        else if (event.text.unicode == '-')
        {
            inputValue = -1;
        }
    }

    if(inputValue>=0){
        if(buttonValue==1){
            valueVecteur1=valueVecteur1*10+signe(valueVecteur1)*inputValue;
        }
        if(buttonValue==2){
            valueVecteur2=valueVecteur2*10+signe(valueVecteur2)*inputValue;
        }
        if(buttonValue==3){
            valueVecteur3=valueVecteur3*10+signe(valueVecteur3)*inputValue;
        }
    }
    else if(inputValue==-1){
        if(buttonValue==1){
            valueVecteur1*=-1;
        }
        if(buttonValue==2){
            valueVecteur2*=-1;
        }
        if(buttonValue==3){
            valueVecteur3*=-1;
        }
    }
}

void listenInputLoL(Character& character, sf::RenderWindow &window){
    sf::Event event; // Objet pour gérer l'évènement

    // Ecoute des évènements, touches
    while (window.pollEvent(event))
    {   
        if(lolMaptype==0){

            clicFermer(event, window);
            
            input.ResetButton();
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (AniviaSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if(Aniviaprice<=coinStock){
                            championChosen=0;
                            coinStock-=Aniviaprice;
                            etatMap = static_cast<EtatM>(1);
                            lolMaptype=1;
                        }else{
                            manqueCoins=Aniviaprice-coinStock;
                            manqueClock.restart();
                        }
                        
                    }
                    else if (ZedSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if(Zedprice<=coinStock){
                            championChosen=1;
                            coinStock-=Zedprice;
                            etatMap = static_cast<EtatM>(1);
                            lolMaptype=1;
                        }else{
                            manqueCoins=Zedprice-coinStock;
                            manqueClock.restart();
                        }
                    }
                    else if (NunuSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if(Nunuprice<=coinStock){
                            championChosen=2;
                            coinStock-=Nunuprice;
                            etatMap = static_cast<EtatM>(1);
                            lolMaptype=1;
                        }else{
                            manqueCoins=Nunuprice-coinStock;
                            manqueClock.restart();
                        }
                    }
                }
            }
        }
        else if(lolMaptype==1){input.InputHandlerLoLMap(character, event, window);}
        else if (lolMaptype==2){input.InputHandlerLoLFight(character,chooseEnemy(static_cast<int>(etatMap)), event, window);}
    }
}

void Input::InputHandlerLoLMap(Character& character, sf::Event &event, sf::RenderWindow &window){

    clicFermer(event, window);

    if(etatMap == static_cast<EtatM>(1)){
        ClicDroit(Katarina, 2,1,character,false,event,window);
    }
    else if(etatMap == static_cast<EtatM>(2)){
        ClicDroit(Katarina, 5,1,character,false,event,window);
    }
    else if(etatMap == static_cast<EtatM>(5)){
        ClicDroit(Jax, 8,5,character,Jax1.doesExist,event,window);
    }
    else if(etatMap == static_cast<EtatM>(8)){
        ClicDroit(Katarina, 11,1,character,false,event,window);
    }
    else if(etatMap == static_cast<EtatM>(11)){
        ClicDroit(Katarina, 3,1,character,false,event,window);
        ClicDroit(Nexus, 12, event, window);
    }
    else if(etatMap == static_cast<EtatM>(3)){
        ClicDroit(Katarina, 6,1,character,false,event,window);
    }
    else if(etatMap == static_cast<EtatM>(6)){
        ClicDroit(Katarina, 9,6,character,Katarina1.doesExist,event,window);
    }
    else if(etatMap == static_cast<EtatM>(9)){
        ClicDroit(Pantheon, 4,9,character,Pantheon1.doesExist,event,window);
    }
    else if(etatMap == static_cast<EtatM>(4)){
        ClicDroit(Katarina, 7,1,character,false,event,window);
    }
    else if(etatMap == static_cast<EtatM>(7)){
        ClicDroit(Darius, 10,7,character,Darius1.doesExist,event,window);
    }
    else if(etatMap == static_cast<EtatM>(10)){
        ClicDroit(Ashe, 1,10,character,Ashe1.doesExist,event,window);
    }

    else if(etatMap == static_cast<EtatM>(12)){
        ClicDroit(NextPageButton, 13, event, window);
        if(event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Right){
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (RestartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    etatMap = static_cast<EtatM>(0);
                    lolMaptype=0;

                    initLol2=true;

                    if(championChosen == 0){coinStock+=Aniviaprice;}
                    else if(championChosen== 1){coinStock+=Zedprice;}
                    else if(championChosen== 2){coinStock+=Nunuprice;}
                    championChosen=-1;
                    playerTurn=true;
                    
                    character.health=character.maxHealth;
                    Jax1.health=400,Jax1.doesExist=true,Jax1.turnNo=0;
                    Katarina1.health=Katarina1.maxHealth,Katarina1.doesExist=true,Katarina1.turnNo=0;
                    Darius1.health=Darius1.maxHealth,Darius1.doesExist=true,Darius1.turnNo=0;
                    Pantheon1.health=Pantheon1.maxHealth,Pantheon1.doesExist=true,Pantheon1.turnNo=0;
                    Ashe1.health=Ashe1.maxHealth,Ashe1.doesExist=true,Ashe1.turnNo=0;

                    LolMapMusic.play();
                }
            }
        }
        
    }
    
    
    else if(etatMap == static_cast<EtatM>(13)){
        if(event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (passerBonusR.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    etatMap = static_cast<EtatM>(0);
                    gamemode=4;
                    orbExchangeMusic.stop();
                    questionMusic.play();
                }
                else if (buttonExchangeR.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if(coinStock-goldExchange>=0){
                        coinStock-=goldExchange;
                        orbStock+=orbExchange;
                    }
                    else{
                        afficherMessPauvreGold=true;
                    }
                }
                else if (buttonUp.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if(coinStock-goldExchange>=2){
                        goldExchange+=2;
                        orbExchange+=1;
                    }
                }
                else if (buttonDown.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if(goldExchange>=1){
                        goldExchange-=2;
                        orbExchange-=1;
                    }
                }
                
                
            }
        }
    }

    Input::touchesDyn(event, window);
    
    
}

void Input::InputHandlerLoLFight(Character& character, Enemy& enemy, sf::Event &event, sf::RenderWindow &window){

    clicFermer(event, window);

    Input::touchesDyn(event, window);

    

    if(turnClock.getElapsedTime().asSeconds()>turnDelay){
        if(playerTurn){
            isEscape=false;

            if(isStun){
                playerTurn=false;
                isStun=false;
                infoString1="Vous etes stunned";
                infoString2="Vous passez votre tour";
                infoString3="";
                turnClock.restart();
            }else
            {
            if(event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Right){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (enemy.sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {button.attack=true;}
                }
            }

            if(button.a || button.z || button.e || button.r || button.d || button.f){
                playerTurn=false;
                infoString3="";
            }

            if(character.id==1){
                if(button.a==true){
                    if(character.attack3==0){
                        enemy.health-=200;
                        character.attack1=1;
                        isStunEnemy=true;
                        infoString1="Le Q de Anivia a ete lance";
                        infoString2="Ca fait mal et stun l'ennemi !";
                        character.attack3=4;
                    }
                    else{
                        infoString1="Vous appuyez sur la touche Q";
                        infoString2="Votre sort est en CD, c'est un missclick !";
                    }
                }
                if(button.z==true){
                    infoString1="Le mur de Anivia a ete lance";
                    infoString2="Mais cela n'a aucun effet sur l'ennemi";
                }
                if(button.e==true){
                    infoString1="Le pic de glace de Anivia a ete lance";
                    if(character.attack1==1){
                        enemy.health-=300;
                        infoString2="Et ca fait tres mal a l'ennemi";
                    }
                    else{
                        enemy.health-=120;
                        infoString2="Mais ca ne fait pas tres mal a l'ennemi";
                    }
                }
                if(button.r==true){
                    infoString1="Le R de Anivia a ete lance";
                    if(character.attack2==0){
                        character.attack2=1;
                        character.attack1=1;
                        infoString2="Une tempete de neige se prepare";
                    }
                    else{
                        character.attack2=0;
                        character.attack1=0;
                        infoString2="La tempete de neige disparait";
                    }
                }
                if(button.d==true){
                    infoString1="Le sort de teleportation a ete utilise sur l'ennemi";
                    infoString2="Ce qui vous permet de vous enfuir en oeuf";
                    lolMaptype=1;
                }
                if(button.f==true){
                    infoString1="Anivia utilise le sort flash";
                    infoString2="Il s'enfuit avec succes du combat";
                    lolMaptype=1;
                }

                if(button.a || button.z || button.e || button.r || button.d || button.f){
                    turnClock.restart();
                    if(character.attack2==1){enemy.health-=100;}
                    if(character.attack3>=1){character.attack3-=1;}
                }
            }

            else if(character.id==2){
                int dmg=0;
                if(button.a==true){
                    enemy.health-=110*(character.attack1+1);
                    dmg+=110*(character.attack1+1);

                    infoString1="Le Q de Zed a ete lance";
                    if(character.attack1==3){
                        infoString2="Votre reve se realise !";
                        infoString3=to_string(character.attack1+1)+" shurikens ont touche l'ennemi";
                    }
                    else{
                        infoString2=to_string(character.attack1+1)+" shurikens ont touche l'ennemi";
                        infoString3="";
                    }
                }
                if(button.z==true){
                    character.attack1=min(character.attack1+1,3);
                    isEscape=true;
                    infoString1="Le Z de Zed a ete lance";
                    infoString2="Une ombre sauvage est apparue.";
                }
                if(button.e==true){
                    enemy.health-=100;
                    dmg+=100;
                    infoString1="Le E de Zed a ete lance";
                    infoString2="L'ennemi a ete ralenti.";
                }
                if(button.r==true){
                    character.attack1=min(character.attack1+1,3);
                    character.attack2=4;
                    isEscape=true;
                    infoString1="Le R de Zed a ete lance. Une ombre apparait";
                    infoString2="Une marque est cree sur l'ennemi";
                }
                if(button.d==true){
                    enemy.health-=50;
                    dmg+=50;
                    infoString1="Le sort de brulure a ete utilise sur l'ennemi";
                    infoString2="Ce qui le chatouille.";
                }
                if(button.f==true){
                    infoString1="Zed utilise le sort flash";
                    infoString2="Il se prend le mur et ne peut pas s'enfuir.";
                }
                if(button.attack==true){
                    if(enemy.health<enemy.maxHealth/2){
                        if(enemy.id==5 && !Ashe1.killed && !Pantheon1.killed){
                            enemy.health-=10;
                            infoString1="Zed a du mepris pour l'ennemi";
                            infoString2="Mais cela chatouille l'ennemi.";
                            infoString3="";
                        }
                        else{
                            enemy.health=0;
                            infoString1="Zed a du mepris pour l'ennemi";
                            infoString2="L'ennemi se fait executer.";
                            infoString3="";
                        }
                    }
                    else{
                        enemy.health-=150;
                        infoString1="Zed utilise son attaque normale";
                        infoString2="L'ennemi a mal et semble avoir peur.";
                    }
                    playerTurn=false;
                }

                if(button.a || button.z || button.e || button.r || button.d || button.f || button.attack){
                    turnClock.restart();
                    if(character.attack2>=2){
                        character.attack3+=0.5*dmg;
                        character.attack2-=1;
                    }
                    else if(character.attack2==1){
                        character.attack3+=0.5*dmg;
                        enemy.health-=character.attack3;
                        character.attack2=0;
                        infoString2+=" La marque explose !";
                    }
                    button.attack=false;
                }
            }

            else if(character.id==3){
                if(button.a==true){
                    character.health=min(character.health+50,static_cast<int>(character.maxHealth));
                    enemy.health-=100;
                    
                    infoString1="Le Q de Nunu a ete lance";
                    infoString2="Il a goute a son ennemi !";
                }
                if(button.z==true){
                    if(character.attack2==0){
                        enemy.health-=200;
                        character.attack2=3;
                        isStunEnemy=true;
                        infoString1="Le Z de Nunu a ete lance";
                        infoString2="Une grosse boule de neige frappe l'ennemi";
                    }
                    else{
                        infoString1="Vous appuyez sur la touche Z";
                        infoString2="Votre sort est en CD, c'est un missclick !";
                    }
                }
                if(button.e==true){
                    enemy.health-=100;
                    infoString1="Le E de Nunu a ete lance";
                    infoString2="Des petites boules de neige chatouillent l'ennemi";
                }

                if(button.r==true){
                    if(character.attack1==0){
                        character.attack1=2;
                        character.health=min(character.health+200,static_cast<int>(character.maxHealth));
                        enemy.health-=200;
                        infoString1="Le R de Nunu a ete lance";
                        infoString3="Une zone de glace enveloppe le terrain";
                        infoString2="Cela regenere Nunu";
                    }
                    else{
                        infoString1="Vous appuyez sur la touche R";
                        infoString3="L'ultime est en cooldown, vous avez missclick";
                        infoString2="ce qui vous fait perdre votre tour";
                    }
                    
                }
                if(button.d==true){
                    infoString1="Le sort de chatiment a ete utilise sur l'ennemi";
                    infoString2="Ce qui le chatouille";
                    enemy.health-=50;
                }
                if(button.f==true){
                    infoString1="Nunu utilise le sort flash";
                    infoString2="Il s'enfuit avec succes du combat";
                }

                if(button.a || button.z || button.e || button.r || button.d || button.f){
                    turnClock.restart();
                    if(character.attack2>=1){
                        character.attack2-=1;
                    }
                }
            }

            }

            

        }
    }
}

void ClicDroit(sf::Sprite& buttonSprite, int nextMapL, int nextMapR, Character& character, bool presenceEnnemi, sf::Event &event, sf::RenderWindow &window){
    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Right){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (buttonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) && presenceEnnemi) {
                etatMap = static_cast<EtatM>(nextMapR);
                lolMaptype=2;
                LolMapMusic.pause();
                if(nextMapR==5){
                    LolFightMusic1.play();
                }
                if(nextMapR==6){
                    LolFightMusic2.play();
                }
                if(nextMapR==7){
                    LolFightMusic3.play();
                }
                if(nextMapR==9){
                    LolFightMusic4.play();
                }
                if(nextMapR==10){
                    LolFightMusic5.play();
                }
            }
            else{
                //if(pointInPolygon(character.position,borderL9)){character.setPosition(mousePos.x,mousePos.y);}
                if(debugMode){character.setPosition(mousePos.x,mousePos.y);}
            }
        }
        else if(event.mouseButton.button == sf::Mouse::Left){
            if(debugMode){etatMap = static_cast<EtatM>(nextMapL);}
        }
    }
}

void ClicDroit(sf::RectangleShape& buttonSprite, int nextMap, sf::Event &event, sf::RenderWindow &window){
    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Right){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (buttonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                etatMap = static_cast<EtatM>(nextMap);
                if(nextMap==12){
                    LolMapMusic.pause();
                    LolVMusic.stop();
                    LolVMusic.play();
                    if(firstGainNexus){
                        coinStock+=10;
                        firstGainNexus=false;
                    }
                }
                else if(nextMap==13){
                    orbExchangeMusic.play();
                    if(championChosen == 0){coinStock+=Aniviaprice;}
                    else if(championChosen== 1){coinStock+=Zedprice;}
                    else if(championChosen== 2){coinStock+=Nunuprice;}
                }
                
                
            }
        }
    }
}

void ClicGauche(sf::RectangleShape& buttonSprite, int nextMap, int nextGame, sf::Event &event, sf::RenderWindow &window){
    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (buttonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                etatMap = static_cast<EtatM>(nextMap);
                gamemode=nextGame;
            }
        }
    }
}


//-----------------------------------------------------------------

void listenInputBonus(sf::RenderWindow &window){
    sf::Event event; // Objet pour gérer l'évènement

    // Ecoute des évènements, touches
    while (window.pollEvent(event))
    {   
        input.InputHandlerBonus(event, window);
        
    }
}

void Input::InputHandlerBonus(sf::Event &event, sf::RenderWindow &window){

    clicFermer(event, window);
    
    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (inputZone1.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                writingX=1;
            }
            else if (inputZone2.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                writingX=2;
            }
            else if (inputZone3.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                writingX=3;
            }
            else if (inputZone4.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                writingX=4;
            }
            else{writingX=0;}

            if (confirmButton1.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                if(inputString1=="4" && !confirm1){
                    confirm1=true;
                    orbStock+=1;
                }
                else if(inputString1=="6" && !confirm1){
                    confirm1=true;
                    orbStock+=2;
                }
                else if(confirm1){}
                else{reponseClock.restart();}
            }
            else if (confirmButton2.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                if((inputString2=="LoL" || inputString2=="Lol" || inputString2=="lol") && !confirm2){
                    confirm2=true;
                    orbStock+=1;
                }else if(confirm2){}
                else{reponseClock.restart();}
            }
            else if (confirmButton3.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                if((inputString3=="physique"||inputString3=="Physique") && !confirm3){
                    confirm3=true;
                    orbStock+=1;
                }
                else if((inputString3=="maths"||inputString3=="Maths"||inputString3=="mathematiques"||inputString3=="Mathematiques" ||inputString3=="les maths"||inputString3=="Les maths"||inputString3=="Les Maths"||inputString3=="les mathematiques"||inputString3=="Les mathematiques"||inputString3=="Les Mathematiques") && !confirm3){
                    confirm3=true;
                    orbStock+=3;
                }
                else if(confirm3){}
                else{reponseClock.restart();}
            }
            else if (confirmButton4.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                if((inputString4=="Aizen" || inputString4=="aizen") && !confirm4){
                    confirm4=true;
                    orbStock+=2;
                }
                else if(confirm4){}
                else{reponseClock.restart();}
            }
            else if (gachaRect.getGlobalBounds().contains(mousePos.x, mousePos.y) && confirm1 && confirm2 && confirm3 && confirm4){
                gamemode=5;
                etatMap=static_cast<EtatM>(1);
                questionVMusic.stop();
                AccueilGachaMusic.play();
            }

            
        }
    }

    

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) { // Vérifier si c'est un caractère ASCII
            
            if (event.text.unicode == 8) {
                // Touche "Backspace" (suppression du dernier caractère)
                if(writingX==1 && !inputString1.empty()){
                    inputString1.pop_back();
                }
                else if(writingX==2 && !inputString2.empty()){
                    inputString2.pop_back();
                }
                else if(writingX==3 && !inputString3.empty()){
                    inputString3.pop_back();
                }
                else if(writingX==4 && !inputString4.empty()){
                    inputString4.pop_back();
                }
                
            } 
            else if (event.text.unicode != 8 && event.text.unicode != 13) {
                // Ajouter le caractère au texte (sauf retour à la ligne)
                if(writingX==1){
                    if(inputString1=="Ecrire"){
                        while(!inputString1.empty()){inputString1.pop_back();}
                    }
                    inputString1 += static_cast<char>(event.text.unicode);
                }
                else if(writingX==2){
                    if(inputString2=="Ecrire"){
                        while(!inputString2.empty()){inputString2.pop_back();}
                    }
                    inputString2 += static_cast<char>(event.text.unicode);
                }
                else if(writingX==3){
                    if(inputString3=="Ecrire"){
                        while(!inputString3.empty()){inputString3.pop_back();}
                    }
                    inputString3 += static_cast<char>(event.text.unicode);
                }
                else if(writingX==4){
                    if(inputString4=="Ecrire"){
                        while(!inputString4.empty()){inputString4.pop_back();}
                    }
                    inputString4 += static_cast<char>(event.text.unicode);
                }
            }
        }
    }


}

void listenInputGacha(sf::RenderWindow &window){
    sf::Event event; // Objet pour gérer l'évènement

    // Ecoute des évènements, touches
    while (window.pollEvent(event))
    {   
        if(static_cast<int>(etatMap) == 1){
            input.InputHandlerGachaHome(event, window);
        }
        else if(static_cast<int>(etatMap) == 2){
            input.InputHandlerGachaPage(event, window);
        }
        else if(static_cast<int>(etatMap) == 3){
            input.InputHandlerListChar(event, window);
        }
   
    }
}

void Input::InputHandlerGachaHome(sf::Event &event, sf::RenderWindow &window){

    clicFermer(event, window);
    
    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (gachaSoloRect.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                if(orbStock>=1){
                    orbStock-=1;
                    gamemode=5;
                    etatMap=static_cast<EtatM>(2);
                    gachaTry=true;
                    GachaSound.play();
                }
                else{
                    afficherMessPauvre=true;
                }
                
            }
            else if (gachaVoirRect.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                gamemode=5;
                etatMap=static_cast<EtatM>(3);
                pageGacha=0;
                AccueilGachaMusic.pause();
                ListPersoMusic.play();
            }
            
        }
    }
}

void Input::InputHandlerGachaPage(sf::Event &event, sf::RenderWindow &window){

    clicFermer(event, window);
    
    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (returnHomeGacha.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                gamemode=5;
                etatMap=static_cast<EtatM>(1);
                AccueilGachaMusic.play();
            }
            else if (oneMoreSoloRect.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                if(orbStock>=1){
                    orbStock-=1;
                    gamemode=5;
                    etatMap=static_cast<EtatM>(2);
                    gachaTry=true;
                    GachaSound.stop();
                    GachaSound.play();
                }
                else{
                    afficherMessPauvre=true;
                }
            }

            
        }
    }
}

void Input::InputHandlerListChar(sf::Event &event, sf::RenderWindow &window){

    clicFermer(event, window);
    
    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (returnHomeGacha2.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                gamemode=5;
                etatMap=static_cast<EtatM>(1);
                ListPersoMusic.pause();
                AccueilGachaMusic.play();
            }
            else if (goLeft.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                pageGacha=max(pageGacha-1,0);
            }
            else if (goRight.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                pageGacha=min(pageGacha+1,static_cast<int>(charaList.size()/15));
            }
        }
    }
}