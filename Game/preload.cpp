//
// Created by dartmoor on 02.12.18.
//

#include "../characters/characters.h"
#include "random"
#include "../items/items.h"
#include "../Game/classGame.h"
#include "../Graphics/graphics.h"
#include "preload.h"
#include "classGame.h"
#include "paint.h"

#include <fstream>
#include <iomanip>
#include <string>

void loadMap(std::vector<std::string>& lvl,int cL){
    std::string mps[16][42];
    std::string tmp,pl;
    std::vector<std::string> maps;
    std::ifstream in("level" + std::to_string(cL));
//    while (in >> tmp)
//        lvl.append(tmp);
int trr =0;

    while (getline(in, tmp)) {
        pl = tmp;
        lvl.push_back(tmp);
    }
}

void loadHero(vector<Hero>& mans,const std::vector<int> whatPick){
    std::string name;
    int HP, Mass, Speed,View,Accuracy, count=0,it=0;
    float X;
    float Y;
    int choiseHero[2]={0,1};
    int ctr=0;
    //еще один коаунт для выбора персонажа
    std::ifstream characterFile("characterFile");
    while(characterFile >>name>>HP>>Mass>>Speed>>View>>Accuracy>>X>>Y){
        if(count>=2)
            break;
        if(it == whatPick[count]) {
            mans[count].setHero(name, HP, Mass, Speed, View, Accuracy,X,Y);
            count++;
        }
        it++;
    }
    characterFile.close();

}




bool startGame(sf::RenderWindow &window,int numberLevel,std::vector<int> whatPick){

    sf::Clock clock;

    float CurrentFrame = 0;
// Включаем вертикальную синхронизацию (для плавной анимации)
    window.setVerticalSyncEnabled(true);

    sf::View overview;
    overview.setSize(sf::Vector2f(540.f, 380.f));//540 380
    overview.setCenter(320,240);//320, 240

    sf::RectangleShape pickHero(sf::Vector2f(32.f,64.f));
    sf::RectangleShape cursor(sf::Vector2f(32.f, 32.f));
    cursor.setPosition(sf::Vector2f(32.f, 32.f));
    cursor.setFillColor(sf::Color(0,255,0,40));
    pickHero.setFillColor(sf::Color(25, 88, 181,200));
    sf::CircleShape radiusOfMove(0);

    sf::Font font;
    font.loadFromFile("CyrilicOld.TTF");

    sf::Text message("",font,20);
    message.setFillColor(sf::Color::Red);

    sf::Text roundOver("",font,45);
    roundOver.setFillColor(sf::Color::Blue);
    sf::Text countOfRound("",font,35);
    countOfRound.setFillColor(sf::Color(40, 227, 11));


    sf::RectangleShape tableInfo(sf::Vector2f(180,70));
    sf::RectangleShape tableInfoEnemy(sf::Vector2f(180,80));
    sf::RectangleShape tableInventory(sf::Vector2f(220,70));
    tableInventory.setFillColor(sf::Color::Black);

    tableInfo.setFillColor(sf::Color::Black);
    sf::Text heroInfo1("", font, 18);
    sf::Text heroInfo2("", font, 18);
    sf::Text heroInfo3("", font, 18);
    sf::Text enemyInfo1("", font, 18);
    sf::Text enemyInfo2("", font, 18);
    sf::Text inventoryInfo1("",font,18);
    sf::Text inventoryInfo2("",font,18);
    sf::Text inventoryInfo3("",font,18);

    inventoryInfo1.setFillColor(sf::Color::Blue);
    inventoryInfo2.setFillColor(sf::Color::Blue);
    inventoryInfo3.setFillColor(sf::Color::Blue);

    sf::Text gameOver("Game Over",font,50);
    gameOver.setPosition(overview.getCenter());
    gameOver.setFillColor(sf::Color(35,41,126));

    sf::Image mapImage;
    mapImage.loadFromFile("mapTexture.png");
    sf::Texture map;
    map.loadFromImage(mapImage);
    sf::Sprite s_map;
    s_map.setTexture(map);

    classGame play;

    //std::string level;

    loadMap(play.lvl,numberLevel);

    Location location;
    bool flagTableHide=true;
    int choiseMan=0;
    bool doorOpen =false;
    int countOfMove =1;
    int countOfInventorySlot = 0;
    int numbOfRound = 1;

    location.clearMap();
    //Pictures pictures;
    //createAll(play,pictures);

    //////////////////////

    Hero player1;
    Hero player2;
    //player1.setHero("Bob",100,30,5,8,80,32,32);
    //player2.setHero("Silver",100,30,6,10,40,64,64);

    Weapon bow(20,1,80,4,"arrow",15,"bow");
    Weapon axe(40,5,70,15,"5.56",15,"axe");
    Medkit aid(1,20,"PotionTallRuby",5);
    Ammo bullets("5.56",20,5);
    Ammo arrows("arrow",10,5);

    player1.rukzak.setIt(&bow);
    player1.rukzak.setIt(&arrows);
    player1.rukzak.setIt(&aid);

    player2.rukzak.setIt(&axe);
    player2.rukzak.setIt(&bullets);
    player2.rukzak.setIt(&aid);

    play.mans.push_back(player1);
    play.mans.push_back(player2);

    loadHero(play.mans,whatPick);

    Enemy evil;
    evil.setHero("demon",60,0,5,8,100,96,96);

    play.evils.push_back(evil);
    play.evils.push_back(evil);
    play.evils.push_back(evil);
    play.evils.push_back(evil);


    Ammo bullets1("arrow",10,5);
    Ammo bullets2("7.62",20,10);
    Ammo bullets3("5.56",30,5);

    Medkit aid1(2,50,"PotionTriangularRuby",10);
    Medkit aid2(2,35,"PotionTallYellow2",5);
    Medkit aid3(1,30,"PotionTallYellow2",5);

    play.someItem.setIt(&aid1);
    play.someItem.setIt(&aid2);
    play.someItem.setIt(&aid3);
    play.someItem.setIt(&bullets1);
    play.someItem.setIt(&bullets2);
    play.someItem.setIt(&bullets3);

    Pictures pictures;
    AllForSprite slp,slt,spt,pr1,pr2,pr3,pr4,pr5,pr6,pr7,pr8;
    std::vector<AllForSprite> spr;
    slp.makeSprite("solder.png",32,32,50,70);

    pictures.heroSprite.push_back(slp);
    pictures.heroSprite.push_back(slp);

    slt.makeSprite("warrior1.png",64,64,55,55);
    pictures.enemySprite.push_back(slt);
    pictures.enemySprite.push_back(slt);
    pictures.enemySprite.push_back(slt);
    pictures.enemySprite.push_back(slt);


    pr1.makeItemSprite("Items/ArrowSteel.PNG","arrow");
    pictures.itemSprite.push_back(pr1);

    pr2.makeItemSprite("Items/CoinsGold.PNG","7.62");
    pictures.itemSprite.push_back(pr2);

    pr3.makeItemSprite("Items/CoinsTeal.PNG","5.56");
    pictures.itemSprite.push_back(pr3);

    pr4.makeItemSprite("Items/PotionTriangularRuby.PNG","PotionTriangularRuby");
    pictures.itemSprite.push_back(pr4);

    pr5.makeItemSprite("Items/PotionTallYellow2.PNG","PotionTallYellow2");
    pictures.itemSprite.push_back(pr5);

    pr6.makeItemSprite("Items/Axe02.PNG","bow");
    pictures.itemSprite.push_back(pr6);

    pr7.makeItemSprite("Items/Bow09.PNG","axe");
    pictures.itemSprite.push_back(pr7);

    pr8.makeItemSprite("Items/PotionTallRuby.PNG", "PotionTallRuby");
    pictures.itemSprite.push_back(pr8);


    //////////////////////////

    for(int it =0; it !=  play.mans[0].rukzak.getIt().size(); it++ ) {
        play.mans[0].setCurrentMass( play.mans[0].rukzak.getItOne(it)->getMass());
    }

    for(int it =0; it < play.mans[1].rukzak.getIt().size(); it++ ) {
        play.mans[1].setCurrentMass( play.mans[1].rukzak.getItOne(it)->getMass());
    }

    play.startCord(play.evils,play.someItem);

    for(auto i: play.evils){
        location.updateMap( i.getCordX(), i.getCordY() );
    }

    for(auto i: play.mans){
        location.updateMap( i.getCordX(), i.getCordY() );
    }


    while(window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds();
        sf::Event event;

        while(window.pollEvent(event)) {

            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed: {
                    if(event.key.code == sf::Keyboard::Escape) {
                        window.close();
                        return false;
                    }
                    if (event.key.code == sf::Keyboard::Num1 && play.mans[0].getCurrentHP() > 0) {
                        choiseMan=0;
                        countOfInventorySlot = 0;
                        cursor.setPosition(play.mans[0].getCordX(), play.mans[0].getCordY());

                    }
                    if (event.key.code == sf::Keyboard::Num2 && play.mans[1].getCurrentHP() > 0) {
                        choiseMan=1;
                        countOfInventorySlot = 0;
                        cursor.setPosition(play.mans[1].getCordX(), play.mans[1].getCordY());
                    }
                    if ( (event.key.code == sf::Keyboard::Tab && numberLevel < 2) || play.endGameCheck()) {
                        return true;
                    }
                }
                default:
                    break;
            }
        }


        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right){
            if( play.tileInfo(cursor.getPosition().x+32,cursor.getPosition().y, nullptr,nullptr) )
                cursorMove(cursor, 'r');
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left){
            if( play.tileInfo(cursor.getPosition().x-32,cursor.getPosition().y, nullptr,nullptr) )
                cursorMove(cursor, 'l');
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
            if( play.tileInfo(cursor.getPosition().x,cursor.getPosition().y-32, nullptr,nullptr) )
                cursorMove(cursor, 'u');
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){
            if( play.tileInfo(cursor.getPosition().x,cursor.getPosition().y+32, nullptr,nullptr) )
                cursorMove(cursor, 'd');
        }
        /////////////////////////////////// Atack /////////////////////////////////////
        if (event.key.code == sf::Keyboard::F && play.mans[choiseMan].getStep() > 0) {
            message.setString(play.mans[choiseMan].Attack(countOfInventorySlot,cursor.getPosition().x,cursor.getPosition().y,play.evils));
            message.setPosition(play.mans[choiseMan].getCordX(),play.mans[choiseMan].getCordY());
        }
/////////////// DOOR
        if (event.key.code == sf::Keyboard::D ) {
            if(play.openDoor(cursor.getPosition().x,cursor.getPosition().y,
                        play.mans[choiseMan].getCordX(),play.mans[choiseMan].getCordY()) && play.mans[choiseMan].getStep() >0){
                play.mans[choiseMan].setStep(-1);
                message.setString("");
                if(!doorOpen)
                    doorOpen = true;
                else doorOpen = false;
            } else{
                message.setPosition(play.mans[choiseMan].getCordX(),play.mans[choiseMan].getCordY()-32);
                message.setString("I cant");
            }

        }

        if (event.key.code == sf::Keyboard::H ) {

            if(!flagTableHide)
                flagTableHide=true;
            else
                flagTableHide = false;

        }
        //// Reaload
        if(event.key.code == sf::Keyboard::R) {

            message.setPosition(play.mans[choiseMan].getCordX(),play.mans[choiseMan].getCordY());
            if(play.mans[choiseMan].reload()){
                message.setString("I`m full");
            }else {
                message.setString("I cant");
            }
        }

        //// Swap item
        if(event.key.code == sf::Keyboard::K) {

            if (!play.mans[choiseMan].rukzak.getIt().empty()) {
                if (countOfInventorySlot >= play.mans[choiseMan].rukzak.getIt().size() - 1)
                    countOfInventorySlot = 0;
                else countOfInventorySlot++;
                message.setString("");
            } else message.setString("Empty");
        }
        //// Drop Item
        if(event.key.code == sf::Keyboard::L){

            if(!play.mans[choiseMan].rukzak.getIt().empty()) {
                play.mans[choiseMan].rukzak.getItOne(countOfInventorySlot)->setCrd(play.mans[choiseMan].getCordX(),play.mans[choiseMan].getCordY());//getSprite().getPosition()
                play.mans[choiseMan].setCurrentMass(- play.mans[choiseMan].rukzak.getItOne(countOfInventorySlot)->getMass());
                play.someItem.setIt(play.mans[choiseMan].rukzak.getItOne(countOfInventorySlot));
                play.mans[choiseMan].rukzak.throwIt(countOfInventorySlot);
                countOfInventorySlot = 0;
            }

        }
        //// Take item
        if(event.key.code == sf::Keyboard::J){
            for(int it =0; it < play.someItem.getIt().size(); it++ ) {
                if ( (play.someItem.getItOne(it)->getCrdX() == cursor.getPosition().x && play.someItem.getItOne(it)->getCrdY() == cursor.getPosition().y) &&
                    play.someItem.getItOne(it)->getMass() <= (play.mans[choiseMan].getMass() - play.mans[choiseMan].getCurrentMass())) {
                    play.mans[choiseMan].rukzak.setIt( play.someItem.getItOne(it) );
                    play.mans[choiseMan].setCurrentMass(play.someItem.getItOne(it)->getMass());
                    play.someItem.throwIt(it);
                    message.setString("");
                } else {
                    message.setString("So heavy...");
                    message.setPosition(play.mans[choiseMan].getCordX(),play.mans[choiseMan].getCordY()-32);
                }
            }
        }

        //// HEAL /////////////////////////////
        if(event.key.code == sf::Keyboard::M){

            if( !play.mans[choiseMan].heal(countOfInventorySlot)){
                message.setString("I cant use this");
                message.setPosition(play.mans[choiseMan].getCordX(),play.mans[choiseMan].getCordY() -32 );
            }
        }

 ///////////// MOVE//////////////
        if (event.key.code == sf::Keyboard::Space) {

            if( !play.moveHero(choiseMan, cursor.getPosition().x,cursor.getPosition().y,location)){
                message.setString("I cant");
                message.setPosition( play.mans[choiseMan].getCordX() , play.mans[choiseMan].getCordY()-20 );
            }else{
                message.setString("");
            }

        }

        window.clear(sf::Color(176, 147, 60));


        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {

                if (play.lvl[i][j] == '0'){
                    s_map.setTextureRect(sf::IntRect(384, 128, 416, 160));
                } // 8W 5H
                if (play.lvl[i][j] == 'D'){
                    if(doorOpen) s_map.setTextureRect(sf::IntRect(128, 224, 160, 256));
                    else s_map.setTextureRect(sf::IntRect(160, 96, 192, 128));
                }
                if (play.lvl[i][j] == ' '){
                    s_map.setTextureRect(sf::IntRect(128, 224, 160, 256));
                }

                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);
            }
        }



        bool endOfRound;
        clock.restart();

        overview.setCenter(play.mans[choiseMan].getCordX(), play.mans[choiseMan].getCordY());
        whereGo(radiusOfMove, play.mans[choiseMan].getSpeed(),play.mans[choiseMan].getCordX(), play.mans[choiseMan].getCordY());
        window.draw(radiusOfMove);
        pickHero.setPosition(play.mans[choiseMan].getCordX(),play.mans[choiseMan].getCordY());
        window.draw(pickHero);
        tableInfodraw(tableInfo, heroInfo1,heroInfo2,heroInfo3, overview.getCenter().x,overview.getCenter().y , &play.mans[choiseMan]);
        countOfRound.setPosition(overview.getCenter().x -150, overview.getCenter().y-150);
        countOfRound.setString("Round " + std::to_string(numbOfRound));


////////////////////////////////////////////////////////////////////////////////////


        for(int it = 0; it < play.someItem.getIt().size() ; it++ ){

            for(int iter = 0; iter != pictures.itemSprite.size(); iter++){

                if(play.someItem.getItOne(it)->getName() == pictures.itemSprite[iter].name){
                    pictures.itemSprite[iter].sprite.setPosition(play.someItem.getItOne(it)->getCrdX(), play.someItem.getItOne(it)->getCrdY());
                    window.draw(pictures.itemSprite[iter].sprite);
                }
            }
        }

        for(int it = 0; it < play.mans.size() ; it++ ) {

            if(play.mans[it].getCurrentHP() <= 0){
                play.mans[it].setStep(-1000);
                pictures.heroSprite[it].sprite.setColor(sf::Color(0,0,0,0));
            }

            pictures.heroSprite[it].sprite.setPosition(play.mans[it].getCordX(),play.mans[it].getCordY());
            window.draw(pictures.heroSprite[it].sprite);
        }

        for(int it = 0; it < play.evils.size() ; it++ ) {

            pictures.enemySprite[it].sprite.setPosition(play.evils[it].getCordX(), play.evils[it].getCordY());
            window.draw(pictures.enemySprite[it].sprite);

        }

            for(auto i: play.evils){

            if(cursor.getPosition().x == i.getCordX() && cursor.getPosition().y == i.getCordY() ){
                tableEnemyDraw(tableInfoEnemy,enemyInfo1,enemyInfo2,cursor.getPosition().x,cursor.getPosition().y,&i);

            }else{
                tableInfoEnemy.setFillColor(sf::Color(0,0,0,0));
                enemyInfo1.setFillColor(sf::Color(0,0,0,0));
                enemyInfo2.setFillColor(sf::Color(0,0,0,0));
            }
            window.draw(tableInfoEnemy);
            window.draw(enemyInfo1);
            window.draw(enemyInfo2);
        }

        if(play.mans[0].getStep() <= 0 && play.mans[1].getStep() <= 0) {
            numbOfRound++;
            if (play.endGameCheck()) return false;
            roundOver.setString("Round Over");
            roundOver.setPosition(overview.getCenter());
            if(play.mans[0].getCurrentHP() > 0) play.mans[0].setStep(2);
            else play.mans[0].setAlive();
            if(play.mans[1].getCurrentHP() > 0) play.mans[1].setStep(2);
            else play.mans[1].setAlive();
            if(countOfMove > 4) countOfMove = 1;
            play.moveAI(countOfMove);
            play.heroIsNear();
            countOfMove++;

            location.clearMap();
            for(auto i: play.evils){
                location.updateMap( i.getCordX(), i.getCordY() );
            }

            for(auto i: play.mans){
                location.updateMap( i.getCordX(), i.getCordY() );
            }

        }else roundOver.setString("");


        if(!play.mans[choiseMan].rukzak.getIt().empty() && flagTableHide){
            drawInventory(tableInventory,inventoryInfo1,inventoryInfo2,inventoryInfo3,overview.getCenter().x,overview.getCenter().y,
                          play.mans[choiseMan].rukzak.getItOne(countOfInventorySlot));

            window.draw(tableInventory);
            window.draw(inventoryInfo1);
            window.draw(inventoryInfo2);
            window.draw(inventoryInfo3);
            ////////////////////////////////
            for(int it = 0; it != pictures.itemSprite.size();it++) {//// X-85,Y+140

                if(play.mans[choiseMan].rukzak.getItOne(countOfInventorySlot)->getName() == pictures.itemSprite[it].name){
                    pictures.itemSprite[it].sprite.setPosition(overview.getCenter().x - 85,overview.getCenter().y + 140);
                    window.draw(pictures.itemSprite[it].sprite);
                }

            }
        }

        if(flagTableHide){
            window.draw(tableInfo);
            window.draw(heroInfo1);
            window.draw(heroInfo2);
            window.draw(heroInfo3);
        }

        window.draw(countOfRound);
        window.draw(roundOver);
        window.draw(message);
        window.draw(cursor);
        window.setView(overview);
        window.display();
    }


    //return true;
}
