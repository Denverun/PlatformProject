#include "main.h"

// Variables
int gamemode=1;

sf::ContextSettings options;
sf::RenderWindow window;

sf::Sprite questionSprite1,questionSprite2,questionSprite3,questionSprite4;
sf::RectangleShape bonusRect({300,80}), questionRect1({750,300});
sf::RectangleShape questionRect2({750,300});
sf::RectangleShape questionRect3({750,300});
sf::RectangleShape questionRect4({750,300});
sf::Text bonusTxt, questionText1, inputText1, confirmText1;
sf::Text questionText2, inputText2, confirmText2;
sf::Text questionText3, inputText3, confirmText3;
sf::Text questionText4, inputText4, confirmText4;


sf::Text gachaTxt;

int int1;
bool bool1;
int charInt;
bool clickGacha=true;
sf::Clock aleaClock;

//---
sf::RectangleShape FrontRect({400,80});
sf::Text gachaFrontTxt,gachaSoloTxt,gachaVoirTxt,messagePauvrete;
sf::Sprite gachaSprite;


sf::Text returnHomeGachaTxt,oneMoreSoloTxt,numberChar;
sf::Sprite gachaFondSprite;
sf::Text returnHomeGachaTxt2,gachaFrontListTxt;

sf::Clock afficherClock;

bool initMusic1=true;

int main()
{   
    std::ifstream fichier("Game.txt");
    std::string ligne;
    if(fichier.is_open()){
        /*
        while (std::getline(fichier, ligne)){
            std::cout << ligne << std::endl;
        }
        */
        std::getline(fichier, ligne);
        std::cout << ligne << std::endl;
        fichier.close();
    } else {
        std::cerr << "erreur" << std::endl;
    }

    if(ligne=="TruckKun"){
        cout << "Start TruckKun" << endl;
        options.antialiasingLevel = 8;
        window.create(sf::VideoMode(WIN_X, WIN_Y,nFPS), "TruckKun !", sf::Style::Default, options);
        window.setVerticalSyncEnabled(true);

        loadFont("res/Barlow/Barlow-Bold.ttf"); // Importation de la police

        sf::Sprite road1, road2, road3;
        sf::RectangleShape topBorder(sf::Vector2f(500, 80));
        sf::Text topText;

        while (window.isOpen())
        {
            sf::Event event; // Objet pour gérer l'évènement
            
            if(initTruck){
                SetSpriteMid(truck, "res/images/truckkun.jpg", {1,1}, WIN_X/6, WIN_Y/4);
                SetSpriteMid(road1, "res/images/Road.jpg", {static_cast<float>(WIN_X)/493.f,3.f}, WIN_X/2, WIN_Y/4);
                SetSpriteMid(road2, "res/images/Road.jpg", {static_cast<float>(WIN_X)/493.f,3.f}, WIN_X/2, 2*WIN_Y/4);
                SetSpriteMid(road3, "res/images/Road.jpg", {static_cast<float>(WIN_X)/493.f,3.f}, WIN_X/2, 3*WIN_Y/4);

                SetRectMid(topBorder, WIN_X/2, WIN_Y/12, sf::Color(192,192,192,200));
                SetText(topText, "Truck Kun !", font);
                SetTextMid(topText, WIN_X/2, WIN_Y/12);

                initTruck=false;
            }
            
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::KeyPressed){
                    switch(event.key.code){
                        case sf::Keyboard::Left:
                            truck.move(-20,0);
                            break;
                        case sf::Keyboard::Right:
                            truck.move(20,0);
                            break;
                        case sf::Keyboard::Down:
                            truck.move(0,20);
                            break;
                        case sf::Keyboard::Up:
                            truck.move(0,-20);
                            break;
                        default:
                            break;
                    }
                }
                if (event.type == sf::Event::Closed) // Fenêtre fermée
                    window.close();
            }
            window.clear();
            window.draw(topBorder);
            window.draw(topText);
            window.draw(road1);
            window.draw(road2);
            window.draw(road3);
            window.draw(truck);
            window.display();

            float sleepsleep=AleaUReal(0.0,1.5);
            sf::sleep(sf::milliseconds(sleepsleep*1000));
        }
    } else if(ligne=="DreamStone"){
        cout << "Start DreamStone" << endl;
        // Initialisation (init.cpp)
        init(options,window);

        // Gestion du jeu
        while (window.isOpen())
        {
            if(gamemode==1){
                // Evenements avant ecoute

                // Ecoute
                listenInput(window);
                
                // Verifications et actions
                CheckGame(input);

                // Actions à réaliser pour tous 

                //window.setTitle("ez"); // Changement de titre du jeu

                window.clear();
                
                draw(window);
                
                window.display();
                
                // Debug
                //sf::sleep(sf::milliseconds(SLEEP_TIME));
                //cout << "temps :" << mainClock.getElapsedTime().asSeconds() << endl ;
            }
            else if(gamemode==2){
                
                listenInputMath(window);
                
                window.clear();
                draw2(window);
                window.display();
            }
            else if(gamemode==3){
                
                if(initLol==true){

                    if(debugMode){turnDelay=2.f;}
                    else{turnDelay=5.f;}

                    textureAnivia.loadFromFile("res/images/LoL/Persos/OiseauGlace.png");
                    textureAnivia.setSmooth(true);
                    textureZed.loadFromFile("res/images/LoL/Persos/Kiba.png");
                    textureZed.setSmooth(true);
                    textureNunu.loadFromFile("res/images/LoL/Persos/EnfantMonstre.png");
                    textureNunu.setSmooth(true);
                    
                    SetSpriteMid(Jax, "res/images/LoL/Persos/HommeLampadaire.png", {1.3f,0.8f} , 3*WIN_X/4,2.5f*WIN_Y/4);
                    SetSpriteMid(Katarina, "res/images/LoL/Persos/FemmeDague.png", {0.33f,0.33f} , 4.2f*WIN_X/7,1*WIN_Y/3);
                    SetSpriteMid(Darius, "res/images/LoL/Persos/HommeHallebarde.png", {0.3f,0.3f} , 3.15*WIN_X/4,1*WIN_Y/3);
                    SetSpriteMid(Pantheon, "res/images/LoL/Persos/SoldatRomain.png", {0.28f,0.22f} , 3*WIN_X/4,1*WIN_Y/2);
                    SetSpriteMid(Ashe, "res/images/LoL/Persos/ArcherGlace.png", {0.9f,0.9f} , 1*WIN_X/2,1*WIN_Y/5);
                    SetSpriteMid(Dragon, "res/images/LoL/Persos/SuperDragon.png", {1.f,1.f} , 3*WIN_X/4,1*WIN_Y/3);
                    SetSpriteMid(Nashor, "res/images/LoL/Persos/Zygarde.png", {1.f,1.f} , 3*WIN_X/4,1*WIN_Y/3);
                    
                    Jax1 = Enemy("Jax", TextureManager::getInstance().getTexture("res/images/LoL/Persos/HommeLampadaire.png"), {3*static_cast<float>(WIN_X)/4,3*static_cast<float>(WIN_Y)/4}, 2000, 10, 0);
                    Jax1.sprite.scale({0.8f,0.4f});
                    Jax1.id=5;
                    Jax1.health=400;
                    Katarina1 = Enemy("Katarina", TextureManager::getInstance().getTexture("res/images/LoL/Persos/FemmeDague.png"), {3*static_cast<float>(WIN_X)/5,2.5f*static_cast<float>(WIN_Y)/10}, 1200, 10, 0);
                    Katarina1.sprite.scale({0.28f,0.28f});
                    Katarina1.id=6;
                    Darius1 = Enemy("Darius", TextureManager::getInstance().getTexture("res/images/LoL/Persos/HommeHallebarde.png"), {3*static_cast<float>(WIN_X)/4+50,static_cast<float>(WIN_Y)/3+100}, 1300, 10, 0);
                    Darius1.sprite.scale({0.25f,0.25f});
                    Darius1.id=7;
                    Pantheon1 = Enemy("Pantheon", TextureManager::getInstance().getTexture("res/images/LoL/Persos/SoldatRomain.png"), {3*static_cast<float>(WIN_X)/4+100,static_cast<float>(WIN_Y)/3+100}, 800, 10, 0);
                    Pantheon1.sprite.scale({0.25f,0.2f});
                    Pantheon1.id=9;
                    Ashe1 = Enemy("Ashe", TextureManager::getInstance().getTexture("res/images/LoL/Persos/ArcherGlace.png"), {3*static_cast<float>(WIN_X)/4,static_cast<float>(WIN_Y)/3}, 800, 10, 0);
                    Ashe1.sprite.scale({0.8f,0.8f});
                    Ashe1.id=10;

                    initLol=false;
                }
                if(initLol2==true && championChosen!=-1){
                    initBorder2();
                    if(championChosen==0){
                        Anivia = Character("Anivia",textureAnivia,{200,WIN_Y-100.f},1000);
                        Anivia.sprite.setOrigin(225,570);
                        Anivia.sprite.scale({0.2f,0.2f});
                        Anivia.speed=95.f/MeanFPS;
                        Anivia.id=1;
                    }
                    else if(championChosen==1){
                        Zed = Character("Zed",textureZed,{200,WIN_Y-100.f},1300);
                        Zed.sprite.setOrigin(350,428);
                        Zed.sprite.scale({0.22f,0.22f});
                        Zed.speed=125.f/MeanFPS;
                        Zed.id=2;
                    }
                    else if(championChosen==2){
                        Nunu = Character("Nunu",textureNunu,{200,WIN_Y-100.f},1000);
                        Nunu.sprite.setOrigin(500,760);
                        Nunu.sprite.scale({0.12f,0.12f});
                        Nunu.speed=112.f/MeanFPS;
                        Nunu.id=3;
                    }

                    initLol2=false;
                }

                
                if(lolMaptype==2){
                    fightPart(chooseChar(championChosen),chooseEnemy(static_cast<int>(etatMap)), static_cast<int>(etatMap));
                    if(turnClock.getElapsedTime().asSeconds()>turnDelay){
                        if(!playerTurn){
                            enemyTurn(chooseEnemy(static_cast<int>(etatMap)), chooseChar(championChosen));
                        }
                    }
                }
                


                if(playerTurn){
                    listenInputLoL(chooseChar(championChosen), window);

                    characMove(chooseChar(championChosen));

                    checkBordures2(chooseChar(championChosen));
                }

                if(turnClock.getElapsedTime().asSeconds()>turnDelay){canMove=true;}
                else{canMove=false;}
                
                

                if(lolMaptype!=2){
                    CheckNextMap2New(chooseChar(championChosen));
                }

                
                
                
                
                window.clear();
                drawLol(chooseChar(championChosen),window);
                if(lolMaptype==2){drawLolMap2(chooseChar(championChosen), chooseEnemy(static_cast<int>(etatMap)), window);}
                
                if(canMove){
                    window.draw(verifMove);
                }
                window.display();
                
            }

            else if(gamemode==4){
                
                if(initBonus==true){
                    //initRenderBonus();
                    SetRectMid(bonusRect, WIN_X/2, WIN_Y/13-10, sf::Color::Yellow);
                    SetText(bonusTxt,"Bonus !",font);
                    SetTextMid(bonusTxt,WIN_X/2, WIN_Y/13-20);
                    bonusTxt.setFillColor(sf::Color::Green);

                    //
                    SetRectMid(questionRect1, WIN_X/4-50, 3*WIN_Y/13+70, sf::Color::White);
                    SetRectMid(inputZone1, 220, 6*WIN_Y/13+25, sf::Color::White);
                    SetRectMid(confirmButton1, 645, 6*WIN_Y/13+25, sf::Color::Green);

                    inputString1="Ecrire";
                    SetText(questionText1,"Combien de pieces pouvait-on recuperer dans la salle 1 ?",font);
                    SetTextMid(questionText1,WIN_X/4-50, 3*WIN_Y/13+70);
                    questionText1.setFillColor(sf::Color::Black);
                    SetText(inputText1,inputString1,font);
                    SetTextMid(inputText1,220, 6*WIN_Y/13-7+25);
                    inputText1.setFillColor(sf::Color::Black);
                    SetText(confirmText1,"Confirmer",font);
                    SetTextMid(confirmText1, 645, 6*WIN_Y/13-7+25);
                    confirmText1.setFillColor(sf::Color::Black);

                    SetSpriteMid(questionSprite1, "res/images/Bonus/Image1.jpg", {0.1f,0.1f} , WIN_X/4-50, 3*WIN_Y/13+70);
                    resizeSprite(questionSprite1,750,300);

                    //
                    SetRectMid(questionRect2, WIN_X/4-50, 9*WIN_Y/13+20, sf::Color::White);
                    SetRectMid(inputZone2, 220, 12*WIN_Y/13-25, sf::Color::White);
                    SetRectMid(confirmButton2, 645, 12*WIN_Y/13-25, sf::Color::Green);

                    inputString2="Ecrire";
                    SetText(questionText2,"Quel etait le code secret de la solution du systeme ?",font);
                    SetTextMid(questionText2,WIN_X/4-50, 9*WIN_Y/13+20);
                    questionText2.setFillColor(sf::Color::Black);
                    SetText(inputText2,inputString2,font);
                    SetTextMid(inputText2,220, 12*WIN_Y/13-7-25);
                    inputText2.setFillColor(sf::Color::Black);
                    SetText(confirmText2,"Confirmer",font);
                    SetTextMid(confirmText2, 645, 12*WIN_Y/13-7-25);
                    confirmText2.setFillColor(sf::Color::Black);

                    SetSpriteMid(questionSprite2, "res/images/Bonus/Image2.jpg", {0.1f,0.1f} , WIN_X/4-50, 9*WIN_Y/13+20);
                    resizeSprite(questionSprite2,750,300);

                    //
                    SetRectMid(questionRect3, 3*WIN_X/4+50, 3*WIN_Y/13+70, sf::Color::White);
                    SetRectMid(inputZone3, WIN_X-220, 6*WIN_Y/13+25, sf::Color::White);
                    SetRectMid(confirmButton3, WIN_X-645, 6*WIN_Y/13+25, sf::Color::Green);

                    inputString3="Ecrire";
                    SetText(questionText3,"Quelle est la plus belle des sciences ?",font);
                    SetTextMid(questionText3,3*WIN_X/4+50, 3*WIN_Y/13+70);
                    questionText3.setFillColor(sf::Color::Black);
                    SetText(inputText3,inputString3,font);
                    SetTextMid(inputText3,WIN_X-220, 6*WIN_Y/13-7+25);
                    inputText3.setFillColor(sf::Color::Black);
                    SetText(confirmText3,"Confirmer",font);
                    SetTextMid(confirmText3, WIN_X-645, 6*WIN_Y/13-7+25);
                    confirmText3.setFillColor(sf::Color::Black);

                    SetSpriteMid(questionSprite3, "res/images/Bonus/Image3.jpg", {0.1f,0.1f} , 3*WIN_X/4+50, 3*WIN_Y/13+70);
                    resizeSprite(questionSprite3,750,300);

                    //
                    SetRectMid(questionRect4, 3*WIN_X/4+50, 9*WIN_Y/13+20, sf::Color::White);
                    SetRectMid(inputZone4, WIN_X-220, 12*WIN_Y/13-25, sf::Color::White);
                    SetRectMid(confirmButton4, WIN_X-645, 12*WIN_Y/13-25, sf::Color::Green);

                    inputString4="Ecrire";
                    SetText(questionText4,"Qui etait l'ennemi se trouvant en toplane ?",font);
                    SetTextMid(questionText4,3*WIN_X/4+50, 9*WIN_Y/13+20);
                    questionText4.setFillColor(sf::Color::Black);
                    SetText(inputText4,inputString4,font);
                    SetTextMid(inputText4,WIN_X-220, 12*WIN_Y/13-7-25);
                    inputText4.setFillColor(sf::Color::Black);
                    SetText(confirmText4,"Confirmer",font);
                    SetTextMid(confirmText4, WIN_X-645, 12*WIN_Y/13-7-25);
                    confirmText4.setFillColor(sf::Color::Black);

                    SetSpriteMid(questionSprite4, "res/images/Bonus/Image4.jpg", {0.1f,0.1f} , 3*WIN_X/4+50, 9*WIN_Y/13+20);
                    resizeSprite(questionSprite4,750,300);

                    SetRectMid(gachaRect, WIN_X/2, WIN_Y/2, sf::Color::Red);
                    SetText(gachaTxt,"Gacha",font);
                    SetTextMid(gachaTxt,WIN_X/2, WIN_Y/2-10);
                    gachaTxt.setFillColor(sf::Color::Black);

                    initBonus=false;
                }
                
                listenInputBonus(window);

                

                SetText(inputText1,inputString1,font);
                SetText(inputText2,inputString2,font);
                SetText(inputText3,inputString3,font);
                SetText(inputText4,inputString4,font);

                
                window.clear();
                if(static_cast<int>(etatMap) == 0){
                    window.draw(bonusRect);
                    window.draw(bonusTxt);

                    window.draw(questionRect1);
                    window.draw(inputZone1);
                    window.draw(confirmButton1);
                    window.draw(inputText1);
                    window.draw(confirmText1);
                    if(confirm1){
                        window.draw(questionSprite1);
                    }else{window.draw(questionText1);}

                    //window.draw();
                    window.draw(questionRect2);
                    window.draw(inputZone2);
                    window.draw(confirmButton2);
                    window.draw(inputText2);
                    window.draw(confirmText2);
                    if(confirm2){
                        window.draw(questionSprite2);
                    }else{window.draw(questionText2);}

                    window.draw(questionRect3);
                    window.draw(inputZone3);
                    window.draw(confirmButton3);
                    window.draw(inputText3);
                    window.draw(confirmText3);
                    if(confirm3){
                        window.draw(questionSprite3);
                    }else{window.draw(questionText3);}

                    window.draw(questionRect4);
                    window.draw(inputZone4);
                    window.draw(confirmButton4);
                    window.draw(inputText4);
                    window.draw(confirmText4);
                    if(confirm4){
                        window.draw(questionSprite4);
                    }else{window.draw(questionText4);}

                    if(confirm1 && confirm2 && confirm3 && confirm4){
                        window.draw(gachaRect);
                        window.draw(gachaTxt);
                        if(initMusic1){
                            questionVMusic.play();
                            questionMusic.stop();
                            initMusic1=false;
                        }
                    }

                    if(reponseClock.getElapsedTime().asSeconds()<3.f){
                        sf::Text fausseReponse;
                        SetText(fausseReponse,"Votre reponse est fausse, veuillez reessayer",font);
                        SetTextMid(fausseReponse,WIN_X/2, WIN_Y/3);
                        fausseReponse.setFillColor(sf::Color::Red);
                        window.draw(fausseReponse);
                    }
                    
                }
                window.display();
                
            }

            else if(gamemode==5){
                if(initGacha==true){
                    SetRectMid(FrontRect, WIN_X/2, WIN_Y/13-10, sf::Color::Yellow);
                    SetText(gachaFrontTxt,"Gacha edition limitee !",font);
                    SetTextMid(gachaFrontTxt,WIN_X/2, WIN_Y/13-20);
                    gachaFrontTxt.setFillColor(sf::Color::Green);
                    
                    SetSpriteMid(gachaSprite, "res/images/gacha/0FondGacha.png", {0.9f,0.9f} , WIN_X/2, WIN_Y/2+50);

                    SetRectMid(gachaSoloRect, WIN_X/3, WIN_Y/2, sf::Color::Red);
                    SetText(gachaSoloTxt,"Invocation x1",font);
                    SetTextMid(gachaSoloTxt,WIN_X/3, WIN_Y/2-10);
                    gachaSoloTxt.setFillColor(sf::Color::White);

                    SetRectMid(gachaVoirRect, 2*WIN_X/3, WIN_Y/2, sf::Color::Red);
                    SetText(gachaVoirTxt,"Voir drops",font);
                    SetTextMid(gachaVoirTxt,2*WIN_X/3, WIN_Y/2-10);
                    gachaVoirTxt.setFillColor(sf::Color::White);

                    //--

                    SetText(gachaFrontListTxt,"Liste persos obtenus !",font);
                    SetTextMid(gachaFrontListTxt,WIN_X/2, WIN_Y/13-20);
                    gachaFrontListTxt.setFillColor(sf::Color::Green);

                    SetSpriteMid(gachaFondSprite, "res/images/gacha/0FondGacha.png", {0.9f,0.9f} , WIN_X/2, WIN_Y/2+50);

                    SetRectMid(returnHomeGacha, WIN_X/3-75, 8.65*WIN_Y/10, sf::Color::Red);
                    SetText(returnHomeGachaTxt,"Retourner Maison",font);
                    SetTextMid(returnHomeGachaTxt,WIN_X/3-75, 8.65*WIN_Y/10-10);
                    returnHomeGachaTxt.setFillColor(sf::Color::White);

                    SetRectMid(oneMoreSoloRect, WIN_X/2, 8.65*WIN_Y/10, sf::Color::Red);
                    SetText(oneMoreSoloTxt,"Encore une solo !",font);
                    SetTextMid(oneMoreSoloTxt,WIN_X/2, 8.65*WIN_Y/10-10);
                    oneMoreSoloTxt.setFillColor(sf::Color::White);

                    SetRectMid(returnHomeGacha2, WIN_X/2, 8.65*WIN_Y/10, sf::Color::Red);
                    SetText(returnHomeGachaTxt2,"Retourner Maison",font);
                    SetTextMid(returnHomeGachaTxt2,WIN_X/2, 8.65*WIN_Y/10-10);
                    returnHomeGachaTxt2.setFillColor(sf::Color::White);

                    SetTextMid(numberChar,4*WIN_X/5-165, 9*WIN_Y/10-22);
                    numberChar.setFillColor(sf::Color::White);

                    SetText(messagePauvrete,"Vous n'avez pas assez d'orbe !",font);
                    SetTextMid(messagePauvrete,WIN_X/2,WIN_Y/3);
                    messagePauvrete.setFillColor(sf::Color::Red);


                    goLeft.setTexture(TextureManager::getInstance().getTexture("res/images/gacha/leftClick.png"));
                    sf::FloatRect textBounds1 = goLeft.getLocalBounds();
                    goLeft.setOrigin(textBounds1.width/2, textBounds1.height/2);
                    goLeft.setPosition(4*WIN_X/5-165+10, 9*WIN_Y/10-22-60);
                    goLeft.setScale({0.2f,0.2f});

                    goRight.setTexture(TextureManager::getInstance().getTexture("res/images/gacha/leftClick.png"));
                    sf::FloatRect textBounds2 = goRight.getLocalBounds();
                    goRight.setOrigin(textBounds2.width/2, textBounds2.height/2);
                    goRight.setPosition(4*WIN_X/5-165+110, 9*WIN_Y/10-22-60);
                    goRight.setScale({-0.2f,0.2f});

                    initGacha=false;
                }
                
                listenInputGacha(window);

                if(afficherMessPauvre){
                    afficherClock.restart();
                    afficherMessPauvre=false;
                }

                if(static_cast<int>(etatMap) == 2 && gachaTry==true){
                    std::string gachaResult;
                    int aleaGacha;
                    if(orbStock>=1 || numberFiveStars>=1){
                        aleaGacha=AleaU(200);
                        gachaResult=gachaRes(aleaGacha);
                        if(aleaGacha<=19){
                            numberFiveStars+=1;
                        }
                    }
                    else{
                        aleaGacha=AleaU(21);
                        gachaResult=gachaResGuaranteed(aleaGacha);
                        numberFiveStars+=1;
                    }
                    characterList.emplace_back(gachaResult);

                    sf::Sprite ResultGacha;
                    SetSpriteMid(ResultGacha,gachaResult,{1,1},(charaList.size()%5+2)*WIN_X/8,(charaList.size()/5+2)*WIN_Y/5-125);
                    resizeSprite(ResultGacha,180,180);
                    charaList.emplace_back(ResultGacha);

                    //
                    std::ofstream fichier("data/output.txt", std::ios::app);  // Mode ajout
                    if (!fichier) {
                        std::cerr << "Erreur lors de l'ouverture du fichier !" << std::endl;
                        return 1;
                    }
                    //for (size_t i = 0; i < characterList.size(); ++i) {
                    //    fichier << characterList[i] << std::endl;
                    //}
                    fichier << gachaResult << std::endl;
                    fichier.close();
                    //

                    gachaChar2.setTexture(TextureManager::getInstance().getTexture(gachaResult),true);
                    gachaChar2.setScale({1,1});
                    sf::FloatRect textBounds = gachaChar2.getLocalBounds();
                    gachaChar2.setOrigin(textBounds.width/2, textBounds.height/2);
                    gachaChar2.setPosition(WIN_X/2,WIN_Y/2-50);
                    resizeSprite(gachaChar2,500,500);
                    gachaTry=false;

                    //

                }

                window.clear();
                if(static_cast<int>(etatMap) == 1){
                    window.draw(FrontRect);
                    window.draw(gachaFrontTxt);
                    window.draw(gachaSprite);
                    window.draw(gachaSoloRect);
                    window.draw(gachaSoloTxt);
                    window.draw(gachaVoirRect);
                    window.draw(gachaVoirTxt);
                    if(afficherClock.getElapsedTime().asSeconds()<3.f){
                        window.draw(messagePauvrete);
                    }
                }
                else if(static_cast<int>(etatMap) == 2){
                    window.draw(gachaFondSprite);
                    window.draw(returnHomeGacha);
                    window.draw(oneMoreSoloRect);
                    window.draw(returnHomeGachaTxt);
                    window.draw(oneMoreSoloTxt);
                    window.draw(gachaChar2);
                    SetText(numberChar,to_string(charaList.size())+"/1000",font);
                    window.draw(numberChar);
                    if(afficherClock.getElapsedTime().asSeconds()<3.f){
                        window.draw(messagePauvrete);
                    }
                }
                else if(static_cast<int>(etatMap) == 3){
                    window.draw(FrontRect);
                    window.draw(gachaFrontListTxt);
                    window.draw(gachaFondSprite);
                    window.draw(returnHomeGacha2);
                    window.draw(returnHomeGachaTxt2);
                    SetText(numberChar,to_string(charaList.size())+"/1000",font);
                    window.draw(numberChar);
                    
                    if (charaList.size()<=15){
                        for (size_t i = 0; i < charaList.size(); ++i) {
                            window.draw(charaList[i]);
                        }
                    }
                    else{
                        afficheGachaList(pageGacha,window);
                    }

                    if(pageGacha!=0){
                        goLeft.setScale({0.2f,0.2f});
                        window.draw(goLeft);
                    }else{goLeft.setScale({0,0});}
                    if(pageGacha!=static_cast<int>(charaList.size()/15)){
                        goRight.setScale({-0.2f,0.2f});
                        window.draw(goRight);
                    }else{goRight.setScale({0,0});}
                    
                    
                }
                SetText(orbQuantity,to_string(orbStock),font);
                window.draw(orbQuantity);
                window.draw(smallOrb);
                window.display();   
            }
            
        }
    } else{
        cout << "erreur de jeu" << endl;
    }

    
    return 0;
}

            