//
// Created by dartmoor on 02.12.18.
//

#ifndef NIGHTSWORD_PRELOAD_H
#define NIGHTSWORD_PRELOAD_H

#include "../characters/characters.h"
#include "preload.h"
#include "random"
#include "../items/items.h"
#include "../Game/classGame.h"
#include "../Graphics/graphics.h"
#include "preload.h"
#include "AI.h"
#include "classGame.h"
#include "paint.h"


//bool tileInfo(float X , float Y, std::vector<Hero>* mans, std::vector<Enemy>* evils){
//    bool check = true;
//
//    if(mans != nullptr){
//        for(auto it : *mans){
//            if(X == it.getCordX() && Y == it.getCordY())
//                check = false;
//        }}
//
//    if(evils != nullptr){
//        for(auto it : *evils){
//            if(X == it.getCordX() && Y == it.getCordY())
//                check = false;
//        }}
//
////
//    if(Y/32 <= 0)
//        return false;
//    if(X/32 <= 0)
//        return false;
//    if(X/32 >= 42-1)// W
//        return false;
//    if(Y/32 >= 16-1)//H
//        return false;
//
//    // for(int p = 0; p < 42 ;p ++) {//25
//    if (Y / 32 == 6 && X / 32 != 25)
//        return false;
//    // }
//    for(int p = 1; p < 4 ;p ++) {
//        if (Y / 32 == p && X / 32 == 18)
//            return false;
//    }
//
//    for(int p = 30; p < 35 ;p ++) {
//        if (Y / 32 == 6 && X / 32 == p)
//            return false;
//    }
//
//    for(int p = 25; p < 31 ;p ++) {
//        if (Y / 32 == 9 && X / 32 == p)
//            return false;
//    }
//    for(int p = 7; p < 11 ;p ++) {
//        if (Y / 32 == p && X / 32 == 8)
//            return false;
//    }
////
//
//    return check;
//}

bool damageCorrect(float X, float Y,std::vector<Enemy>& mans,int Ac,int damage) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    if (dist(gen) >= Ac) return false;


    for(auto it = 0; it != mans.size(); it++){
        if(X == mans[it].getCordX() && Y == mans[it].getCordY()) {
            mans[it].setHP(damage);
            if(mans[it].getCurrentHP() <= 0){
                mans[it].setStep(-1000);
                mans.erase(mans.begin() + it);
            }
            break;
        }
    }
    return true;
}
////////play.mans[choiseMan].rukzak
bool ammoCheck(Inventory& items, int clip){
    int i=0;
    std::string type;
    //////// search type
    while(i <= items.getIt().size()) {

        if(items.getItOne(i)->getTypeOfAmmo() != " ") {
            type = items.getItOne(i)->getTypeOfAmmo();
            break;
        }else i++;
    }

    for(auto it: items.getIt() ){
        if( it->getName() == type){

            //// SHOOT
            if(clip == 0 && items.getItOne(i)->getBullets() <= items.getItOne(i)->getCurrentCapacity() ) {
                //it->setCurrentSize(items[index].getItOne(i)->getBullets());
                items.getItOne(i)->setCurrentCapacity(items.getItOne(i)->getBullets());
                return true;
            }
            //// RELOAD
            if(clip != 0 && it->getAmmoSize() > 0 ){

                if(items.getItOne(i)->getCurrentCapacity() > 0)
                    return false;

                if( it->getAmmoSize() >= items.getItOne(i)->getCapacity() ) {
                    items.getItOne(i)->setCapacity(items.getItOne(i)->getCapacity());
                    it->setCurrentSize(items.getItOne(i)->getCapacity());
                }
                else {

                    items.getItOne(i)->setCapacity( it->getAmmoSize() );

                    it->setCurrentSize(it->getAmmoSize());
                }

                return true;
            } else{
                return false;
            }

        }
    }
    return false;
}


void whereGo(sf::CircleShape& radiusOfMove,int speed, float X, float Y){
    //std::cout<<"?"<<std::endl;
    radiusOfMove.setRadius(32*speed);
    radiusOfMove.setPosition(X - 32*speed ,Y - 32*speed);
    //radiusOfMove.setPosition(X  ,Y );
    radiusOfMove.setFillColor(sf::Color(210,210,0,30));

}

bool rangeOfAct (float X, float Y,float anX, float anY,float plus=32.f ) {
    return ((X - anX)*(X - anX) + (Y - anY) * (Y - anY) ) <= (plus)*(plus);
}

bool openDoor(float X, float Y, float plX, float plY){

    if(X/32 == 25 && Y/32 == 6) {
        if( rangeOfAct(X,Y,plX,plY,32))
            return true;
    }
    return false;
}



void startCord(std::vector<Enemy> &evils,Inventory& item){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distY(1, 15);
    std::uniform_int_distribution<> distX(8, 38);
    float X,Y,Xi,Yi;

    for(auto it = 0;it != evils.size(); it++){
        X = distX(gen)*32;
        Y = distY(gen)*32;

        if(tileInfo(X,Y,nullptr, &evils)) {
            evils[it].setPlayerCordinate(X,Y);
        }
        else it--;
    }

    for(int it = 0;it != item.getIt().size(); it++){

        Xi = distX(gen)*32;
        Yi = distY(gen)*32;

        if(tileInfo(Xi,Yi,nullptr, nullptr)) {
            item.getItOne(it)->setCrd(Xi,Yi);
        }
        else it--;
    }


}



void createAll(classGame& play){

    Hero player1;
    Hero player2;
    player1.setHero("Bob",100,30,5,8,80,32,32);
    player2.setHero("Silver",100,30,6,10,40,64,64);

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

}

bool startGame(sf::RenderWindow &window){

    sf::Clock clock;

    float CurrentFrame = 0;
// Включаем вертикальную синхронизацию (для плавной анимации)
    window.setVerticalSyncEnabled(true);

    sf::View overview;
    overview.setSize(sf::Vector2f(1300.f, 680.f));//540 380
    overview.setCenter(600,360);//320, 240

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

    //LevelMap objectMap;
    bool flagTableHide=true;
    int choiseMan=0;
    bool doorOpen =false;
    int countOfMove =1;
    int countOfInventorySlot = 0;
    int numbOfRound = 1;


    Location loc;

    //loc.clearMap();

    //createAll(play);

    //////////////////////

    Hero player1;
    Hero player2;
    player1.setHero("Bob",100,30,5,8,80,32,32);
    player2.setHero("Silver",100,30,6,10,40,64,64);

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
    AllForSprite slp,slt,spt;
    std::vector<AllForSprite> spr;
    slp.makeSprite("solder.png",32,32,50,70);

    pictures.heroSprite.push_back(&slp);
    pictures.heroSprite.push_back(&slp);

    slt.makeSprite("warrior1.png",64,64,55,55);
    pictures.enemySprite.push_back(&slt);
    pictures.enemySprite.push_back(&slt);
    pictures.enemySprite.push_back(&slt);
    pictures.enemySprite.push_back(&slt);


    spt.makeItemSprite("Items/ArrowSteel.PNG","arrow");
    spr.push_back(spt);

    spt.makeItemSprite("Items/CoinsGold.PNG","7.62");
    spr.push_back(spt);

    spt.makeItemSprite("Items/CoinsTeal.PNG","5.56");
    spr.push_back(spt);

    spt.makeItemSprite("Items/PotionTriangularRuby.PNG","PotionTriangularRuby");
    spr.push_back(spt);

    spt.makeItemSprite("Items/PotionTallYellow2.PNG","PotionTallYellow2");
    spr.push_back(spt);

    spt.makeItemSprite("Items/Axe02.PNG","bow");
    spr.push_back(spt);

    spt.makeItemSprite("Items/Bow09.PNG","axe");
    spr.push_back(spt);

    spt.makeItemSprite("Items/PotionTallRuby.PNG", "PotionTallRuby");
    spr.push_back(spt);


    std::cout<< spr.size()<<std::endl;
    for(int i =0; i != spr.size(); i++ ) {
        pictures.itemSprite.push_back(&spr[i]);
        std::cout<<i<<" - " <<pictures.itemSprite[i]->name<<std::endl;
    }

    //////////////////////////

    for(int it =0; it <  play.mans[0].rukzak.getIt().size(); it++ ) {
        play.mans[0].setCurrentMass(  play.mans[0].rukzak.getItOne(it)->getMass());
    }

    for(int it =0; it < play.mans[1].rukzak.getIt().size(); it++ ) {
        play.mans[1].setCurrentMass( play.mans[1].rukzak.getItOne(it)->getMass());
    }

    startCord(play.evils,play.someItem);


    // Главный цикл приложения
    while(window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds();
        time /= 800;
        // Обрабатываем события в цикле
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


                    if (event.key.code == sf::Keyboard::Num1 && play.mans[0].getHP() > 0) {
                        choiseMan=0;
                        countOfInventorySlot = 0;
                        cursor.setPosition(play.mans[0].getCordX(), play.mans[0].getCordY());

                    }
                    if (event.key.code == sf::Keyboard::Num2 && play.mans[1].getHP() > 0) {
                        choiseMan=1;
                        countOfInventorySlot = 0;
                        cursor.setPosition(play.mans[1].getCordX(), play.mans[1].getCordY());
                    }

                    break;

                }
                default:
                    break;
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) { return true; }//если таб, то перезагружаем игру


        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right){
            if( tileInfo(cursor.getPosition().x+32,cursor.getPosition().y, nullptr,nullptr) )
                cursorMove(cursor, 'r');
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left){
            if( tileInfo(cursor.getPosition().x-32,cursor.getPosition().y, nullptr,nullptr) )
                cursorMove(cursor, 'l');
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
            if( tileInfo(cursor.getPosition().x,cursor.getPosition().y-32, nullptr,nullptr) )
                cursorMove(cursor, 'u');
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){
            if( tileInfo(cursor.getPosition().x,cursor.getPosition().y+32, nullptr,nullptr) )
                cursorMove(cursor, 'd');
        }
        /////////////////////////////////// Atack /////////////////////////////////////
        if (event.key.code == sf::Keyboard::F && play.mans[choiseMan].getStep() > 0) {
            message.setString(play.mans[choiseMan].Attack(countOfInventorySlot,cursor.getPosition().x,cursor.getPosition().y,play.evils));
            message.setPosition(play.mans[choiseMan].getCordX(),play.mans[choiseMan].getCordY());
        }
/////////////// DOOR
        if (event.key.code == sf::Keyboard::D ) {
            if(openDoor(cursor.getPosition().x,cursor.getPosition().y,
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


        if (event.key.code == sf::Keyboard::Space) {

            if( !play.moveHero(choiseMan, cursor.getPosition().x,cursor.getPosition().y)){
                message.setString("I cant");
                message.setPosition( play.mans[choiseMan].getCordX() , play.mans[choiseMan].getCordY()-20 );
            }else{
                message.setString("");
            }

        }

        // Очистка
        window.clear(sf::Color(176, 147, 60));


        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {

                if (TileMap[i][j] == '0'){
                    s_map.setTextureRect(sf::IntRect(384, 128, 416, 160));
                    //objectMap.update(i,j,true);
                } // 8W 5H
                if (TileMap[i][j] == 'D'){
                    if(doorOpen) s_map.setTextureRect(sf::IntRect(128, 224, 160, 256));
                    else s_map.setTextureRect(sf::IntRect(160, 96, 192, 128));
                    //objectMap.update(i,j,false);
                }
                if (TileMap[i][j] == ' '){
                    s_map.setTextureRect(sf::IntRect(128, 224, 160, 256));
                    //objectMap.update(i,j,false);
                }

                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);
            }
        }



        bool endOfRound;
        //play.mans[0].update(time);
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

        //loc.clearMap();
        for(int it = 0; it < play.someItem.getIt().size() ; it++ ){
            //std::cout<<"x:" << play.someItem.getItOne(it)->getCordX()<<std::endl;
            //play.someItem.getItOne(it)->getSprite().setPosition(play.someItem.getItOne(it)->getCrdX(),play.someItem.getItOne(it)->getCrdY());
            //window.draw(play.someItem.getItOne(it)->getSprite());
            for(int iter = 0; iter != pictures.itemSprite.size(); iter++){

                if(play.someItem.getItOne(it)->getName() == pictures.itemSprite[iter]->name){
                    pictures.itemSprite[iter]->sprite.setPosition(play.someItem.getItOne(it)->getCrdX(), play.someItem.getItOne(it)->getCrdY());
                    window.draw(pictures.itemSprite[iter]->sprite);
                }

            }


        }

//        window.draw(play.mans[0].getSprite());
//        window.draw(play.mans[1].getSprite());
        for(int it = 0; it < play.mans.size() ; it++ ) {

            pictures.heroSprite[it]->sprite.setPosition(play.mans[it].getCordX(),play.mans[it].getCordY());
            window.draw(pictures.heroSprite[it]->sprite);

        }

        for(int it = 0; it < play.evils.size() ; it++ ) {

            pictures.enemySprite[it]->sprite.setPosition(play.evils[it].getCordX(), play.evils[it].getCordY());
            window.draw(pictures.enemySprite[it]->sprite);

        }

            for(auto i: play.evils){
            //// cursor.getPosition().x == i.getSprite().getPosition().x && cursor.getPosition().y == i.getSprite().getPosition().y
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
            roundOver.setString("Round Over");
            roundOver.setPosition(overview.getCenter());
            play.mans[0].setStep(2);
            play.mans[1].setStep(2);
            if(countOfMove > 4) countOfMove = 1;
            moveAI(play.evils,&play.mans, countOfMove);
            //heroIsNear(play.evils,&play.mans);
            countOfMove++;
        }else roundOver.setString("");

        if(play.evils.empty() || play.mans.empty()){
            window.draw(gameOver);
        }

        if(!play.mans[choiseMan].rukzak.getIt().empty() && flagTableHide){
            play.mans[choiseMan].rukzak.getItOne(countOfInventorySlot)->drawInventory(tableInventory,inventoryInfo1,inventoryInfo2,inventoryInfo3,overview.getCenter().x,overview.getCenter().y);

            window.draw(tableInventory);
            window.draw(inventoryInfo1);
            window.draw(inventoryInfo2);
            window.draw(inventoryInfo3);
            ////////////////////////////////
            for(int it = 0; it != pictures.itemSprite.size();it++) {//// X-85,Y+140

                if(play.mans[choiseMan].rukzak.getItOne(countOfInventorySlot)->getName() == pictures.itemSprite[it]->name){
                    pictures.itemSprite[it]->sprite.setPosition(overview.getCenter().x - 85,overview.getCenter().y + 140);
                    window.draw(pictures.itemSprite[it]->sprite);
                }

            }
        }

        if(flagTableHide){
            window.draw(tableInfo);
            window.draw(heroInfo1);
            window.draw(heroInfo2);
            window.draw(heroInfo3);
        }

        pictures.itemSprite[6]->sprite.setPosition(96,96);
        window.draw(pictures.itemSprite[6]->sprite);
        window.draw(countOfRound);

        window.draw(roundOver);
        window.draw(message);
        window.draw(cursor);
        window.setView(overview);
        window.display();
    }


    return true;
}


#endif //NIGHTSWORD_PRELOAD_H
