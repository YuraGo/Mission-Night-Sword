#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Graphics/graphics.h"
#include <iostream>
#include "characters/characters.h"
#include "preload.h"
#include "AI.h"
#include "items/items.h"
#include <list>

#include "preload.h"


int main() {
    // Создаем главное окно приложения
    sf::RenderWindow window(sf::VideoMode(640, 480), "Test"); // 640 480
    sf::Clock clock;

    float CurrentFrame = 0;
// Включаем вертикальную синхронизацию (для плавной анимации)
    window.setVerticalSyncEnabled(true);

    sf::View overview;
    overview.setSize(sf::Vector2f(1000.f, 680.f));//540 380
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


    std::vector<Hero> mans;
    std::vector<Enemy> evils;

    Hero player1("solder.png",32,32,50,70);
    Hero player2("solder.png",64,64,55,55);
    player1.setHero("Bob",100,30,5,8,80);
    player2.setHero("Silver",100,30,6,10,40);
    mans.push_back(player1);
    mans.push_back(player2);


    bool flagTableHide=false;
    int choiseMan=0;
    bool doorOpen =false;
    int countOfMove =1;
    int countOfInventorySlot = 0;
    int numbOfRound = 1;

    Weapon bow(20,1,80,4,"arrow",15,"bow","Items/Axe02.PNG");
    Weapon axe(40,5,70,15,"5.56",15,"axe","Items/Bow09.PNG");
    Medkit aid(1,20,5,"Items/PotionTallRuby.PNG");
    Ammo bullets("5.56",20,5,"Items/CoinsTeal.PNG");
    Ammo arrows("arrow",10,5,"Items/ArrowSteel.PNG");
    //bow.getInfor();

    Ammo bullets1("arrow",10,5,"Items/ArrowSteel.PNG");
    Ammo bullets2("7.62",20,10,"Items/CoinsGold.PNG");
    Ammo bullets3("5.56",30,5,"Items/CoinsTeal.PNG");

    Medkit aid1(2,50,10,"Items/PotionTriangularRuby.PNG");
    Medkit aid2(2,35,6,"Items/PotionTallYellow2.PNG");
    Medkit aid3(1,30,6,"Items/PotionTallYellow2.PNG");

    std::vector<Inventory> stash;

    Inventory backpack;
    backpack.setIt(&bow);
    backpack.setIt(&arrows);
    backpack.setIt(&aid);

    Inventory backpack2;
    backpack2.setIt(&axe);
    backpack2.setIt(&bullets);
    backpack2.setIt(&aid);


    stash.push_back(backpack);
    stash.push_back(backpack2);

    Inventory someItem;
    someItem.setIt(&aid1);
    someItem.setIt(&aid2);
    someItem.setIt(&aid3);
    someItem.setIt(&bullets1);
    someItem.setIt(&bullets2);
    someItem.setIt(&bullets3);

    Enemy evil("warrior1.png",64,64,55,55);
    evil.setHero("demon",40,0,5,8,100);

    evils.push_back(evil);
    evils.push_back(evil);
    evils.push_back(evil);
    evils.push_back(evil);

    for(int it =0; it < stash[0].getIt().size(); it++ ) {
        mans[0].setCurrentMass( stash[0].getItOne(it)->getMass());
    }

    for(int it =0; it < stash[1].getIt().size(); it++ ) {
        mans[1].setCurrentMass( stash[0].getItOne(it)->getMass());
    }

    startCord(evils,someItem);
    //someItem.getItOne(0)->getSprite().setPosition(64,64);
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
                    if(event.key.code == sf::Keyboard::Escape)
                        window.close();


                    if (event.key.code == sf::Keyboard::Num1 && mans[0].getHP() > 0) {
                        choiseMan=0;
                        countOfInventorySlot = 0;
                        cursor.setPosition(mans[0].sprite.getPosition().x, mans[0].sprite.getPosition().y);

                    }
                    if (event.key.code == sf::Keyboard::Num2 && mans[1].getHP() > 0) {
                        choiseMan=1;
                        countOfInventorySlot = 0;
                        cursor.setPosition(mans[1].sprite.getPosition().x, mans[1].sprite.getPosition().y);
                    }

                    break;

                }
                default:
                    break;
            }


        }


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
        if (event.key.code == sf::Keyboard::F && mans[choiseMan].getStep() > 0) {

            bool damageCheck = damageCorrect(cursor.getPosition().x, cursor.getPosition().y, evils,
                    ( mans[choiseMan].getAccuracy() + stash[choiseMan].getItOne(countOfInventorySlot)->getAccuracy() )/2,
                     stash[choiseMan].getItOne(countOfInventorySlot)->getHpChange());

            bool ammoHave = ammoCheck( stash, choiseMan,0);

            if(mans[choiseMan].characterMove(cursor.getPosition().x,cursor.getPosition().y,2)) {
                if(ammoHave) {
                    if (damageCheck) {
                        message.setString("Damage is" + std::to_string(
                                stash[choiseMan].getItOne(countOfInventorySlot)->getHpChange()));
                        message.setPosition(cursor.getPosition().x, cursor.getPosition().y - 20);
                    } else message.setString("Miss...");
                    mans[choiseMan].setStep(-1);
                } else{
                    message.setString("Not enough ammo...");
                    message.setPosition(mans[choiseMan].sprite.getPosition());
                }
            }else {
                message.setString("Too far...");
                message.setPosition(mans[choiseMan].sprite.getPosition());
            }
        }

        if (event.key.code == sf::Keyboard::D ) {
            if(openDoor(cursor.getPosition().x,cursor.getPosition().y,
            mans[choiseMan].sprite.getPosition().x,mans[choiseMan].sprite.getPosition().y) && mans[choiseMan].getStep() >0){
                mans[choiseMan].setStep(-1);
                message.setString("");
                if(!doorOpen)
                    doorOpen = true;
                else doorOpen = false;
            } else{
                message.setPosition(mans[choiseMan].sprite.getPosition().x,mans[choiseMan].sprite.getPosition().y-32);
                message.setString("I cant");
            }

        }

        if (event.key.code == sf::Keyboard::H ) {

            if(!flagTableHide) {
                tableInfo.setFillColor(sf::Color(0, 0, 0, 0));
                heroInfo1.setFillColor(sf::Color(0, 0, 0, 0));
                heroInfo2.setFillColor(sf::Color(0, 0, 0, 0));
                heroInfo3.setFillColor(sf::Color(0, 0, 0, 0));


                mans[0].sprite.setScale(0,0);
                tableInventory.setFillColor(sf::Color(0,0,0,0));
                inventoryInfo1.setFillColor(sf::Color(0,0,0,0));
                inventoryInfo2.setFillColor(sf::Color(0,0,0,0));
                inventoryInfo3.setFillColor(sf::Color(0,0,0,0));


                flagTableHide=true;
            }else {

                flagTableHide = false;
                mans[0].sprite.setScale(1,1);
                tableInfo.setFillColor(sf::Color::Black);
                heroInfo1.setFillColor(sf::Color(120,150,83));
                heroInfo2.setFillColor(sf::Color(120,150,83));
                heroInfo3.setFillColor(sf::Color(120,150,83));

                tableInventory.setFillColor(sf::Color::Black);
                inventoryInfo1.setFillColor(sf::Color::Blue);
                inventoryInfo2.setFillColor(sf::Color::Blue);
                inventoryInfo3.setFillColor(sf::Color::Blue);

            }
        }
        //// Reaload
        if(event.key.code == sf::Keyboard::R) {

            if(ammoCheck( stash, choiseMan,1)){
                message.setString("I`m full");
                message.setPosition(mans[choiseMan].sprite.getPosition().x,mans[choiseMan].sprite.getPosition().y -32);
                mans[choiseMan].setStep(-1);
            }else {
                message.setString("I cant");
                message.setPosition(mans[choiseMan].sprite.getPosition().x,mans[choiseMan].sprite.getPosition().y -32);
            }

        }

        //// Swap item
        if(event.key.code == sf::Keyboard::K) {

            if (!stash[choiseMan].getIt().empty()) {
                if (countOfInventorySlot >= stash[choiseMan].getIt().size() - 1)
                    countOfInventorySlot = 0;
                else countOfInventorySlot++;
                message.setString("");
            } else message.setString("Empty");
        }
        //// Drop Item
        if(event.key.code == sf::Keyboard::L){

            if(!stash[choiseMan].getIt().empty()) {
                stash[choiseMan].getItOne(countOfInventorySlot)->getSprite().setPosition(mans[choiseMan].sprite.getPosition());
                mans[choiseMan].setCurrentMass(- stash[choiseMan].getItOne(countOfInventorySlot)->getMass());
                someItem.setIt(stash[choiseMan].getItOne(countOfInventorySlot));
                stash[choiseMan].throwIt(countOfInventorySlot);
                countOfInventorySlot = 0;


            }

        }
        //// Take item
        if(event.key.code == sf::Keyboard::J){
            for(int it =0; it < someItem.getIt().size(); it++ ) {
                if (someItem.getItOne(it)->getSprite().getPosition() == cursor.getPosition() &&
                someItem.getItOne(it)->getMass() <= (mans[choiseMan].getMass() - mans[choiseMan].getCurrentMass())) {
                    stash[choiseMan].setIt( someItem.getItOne(it) );
                    mans[choiseMan].setCurrentMass(someItem.getItOne(it)->getMass());
                    someItem.throwIt(it);
                    message.setString("");
                } else {
                    message.setString("So heavy...");
                    message.setPosition(mans[choiseMan].sprite.getPosition().x,mans[choiseMan].sprite.getPosition().y-32);
                }
            }
        }

        //// HEAL /////////////////////////////
        if(event.key.code == sf::Keyboard::M){

            std::cout<<"Aid step: " << stash[choiseMan].getItOne(countOfInventorySlot)->getAidStep() << std::endl;
            std::cout<<"pers step: "<< mans[choiseMan].getStep() <<std::endl;

            if( stash[choiseMan].getItOne(countOfInventorySlot)->getRegen() != 0 &&
                    mans[choiseMan].getStep() >= stash[choiseMan].getItOne(countOfInventorySlot)->getAidStep()) {

                mans[choiseMan].setHP(-stash[choiseMan].getItOne(countOfInventorySlot)->getRegen());
                mans[choiseMan].setStep( -stash[choiseMan].getItOne(countOfInventorySlot)->getAidStep() );
                stash[choiseMan].throwIt(countOfInventorySlot);
                countOfInventorySlot = 0;
                message.setString("");

            } else {
                message.setString("I cant use this");
                message.setPosition(mans[choiseMan].sprite.getPosition().x,mans[choiseMan].sprite.getPosition().y -32 );
                }
        }


        if (event.key.code == sf::Keyboard::Space) {
            //bool YouCan = pathIsCorrect(mans[0].sprite.getPosition().x,mans[0].sprite.getPosition().y,
            //                    cursor.getPosition().x , cursor.getPosition().y, mans[0].getSpeed());
            bool tileFree = tileInfo(cursor.getPosition().x,cursor.getPosition().y, &mans,&evils);
            bool lenghOfMove = mans[choiseMan].characterMove(cursor.getPosition().x,cursor.getPosition().y);
//            if(YouCan)
            //std::cout<<"X: "<<mans[choiseMan].sprite.getPosition().x<<" , "<<mans[choiseMan].sprite.getPosition().y << std::endl;
//            else std::cout<<"false: " << std::endl;

            if( !tileFree || !lenghOfMove || mans[choiseMan].getStep() <= 0){
                message.setString("I cant");
                message.setPosition( mans[choiseMan].sprite.getPosition().x , mans[choiseMan].sprite.getPosition().y-20 );
            }else{
                message.setString("");
                mans[choiseMan].sprite.setPosition(cursor.getPosition().x, cursor.getPosition().y);
                mans[choiseMan].setPlayerCordinate(cursor.getPosition().x, cursor.getPosition().y);
                mans[choiseMan].setStep(-1);
            }


        }

        // Очистка
        window.clear(sf::Color(176, 147, 60));


            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {

                    if (TileMap[i][j] == '0') s_map.setTextureRect(sf::IntRect(384, 128, 416, 160)); // 8W 5H
                    if (TileMap[i][j] == 'D'){
                        if(doorOpen) s_map.setTextureRect(sf::IntRect(128, 224, 160, 256));
                        else s_map.setTextureRect(sf::IntRect(160, 96, 192, 128));
                    }
                    if (TileMap[i][j] == ' ') s_map.setTextureRect(sf::IntRect(128, 224, 160, 256));

                    s_map.setPosition(j * 32, i * 32);
                    window.draw(s_map);
                }
            }



        bool endOfRound;
        //mans[0].update(time);
        clock.restart();

        overview.setCenter(mans[choiseMan].sprite.getPosition().x, mans[choiseMan].sprite.getPosition().y);
        whereGo(radiusOfMove, mans[choiseMan].getSpeed(),mans[choiseMan].sprite.getPosition().x, mans[choiseMan].sprite.getPosition().y);
        window.draw(radiusOfMove);
        pickHero.setPosition(mans[choiseMan].sprite.getPosition());
        window.draw(pickHero);
        tableInfodraw(tableInfo, heroInfo1,heroInfo2,heroInfo3, overview.getCenter().x,overview.getCenter().y , &mans[choiseMan]);
        countOfRound.setPosition(overview.getCenter().x -150, overview.getCenter().y-150);
        countOfRound.setString("Round " + std::to_string(numbOfRound));

        for(auto it: someItem.getIt()){
            window.draw(it->getSprite());
        }

        for(auto i: mans)
        window.draw(i.sprite);

        for(auto i: evils) {
            window.draw(i.sprite);
       // }

        //for(auto i: evils){
            if(cursor.getPosition().x == i.sprite.getPosition().x && cursor.getPosition().y == i.sprite.getPosition().y ){
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

        if(mans[0].getStep() <= 0 && mans[1].getStep() <= 0) {
            numbOfRound++;
            roundOver.setString("Round Over");
            roundOver.setPosition(overview.getCenter());
            mans[0].setStep(2);
            mans[1].setStep(2);
            if(countOfMove > 4) countOfMove = 1;
            moveAI(evils,&mans, countOfMove);
            countOfMove++;
        }else roundOver.setString("");

        if(evils.empty() || mans.empty()){
            window.draw(gameOver);
        }

        if(!stash[choiseMan].getIt().empty()){
            stash[choiseMan].getItOne(countOfInventorySlot)->drawInventory(tableInventory,inventoryInfo1,inventoryInfo2,inventoryInfo3,overview.getCenter().x,overview.getCenter().y);

            window.draw(tableInventory);
            window.draw(inventoryInfo1);
            window.draw(inventoryInfo2);
            window.draw(inventoryInfo3);
            window.draw(stash[choiseMan].getItOne(countOfInventorySlot)->getSprite());
        }



//        if(!stash[choiseMan].getIt().empty()) {
//            window.draw(stash[choiseMan].getItOne(countOfInventorySlot)->getSprite());
//        }

        window.draw(countOfRound);
        window.draw(tableInfo);
        window.draw(heroInfo1);
        window.draw(heroInfo2);
        window.draw(heroInfo3);
        window.draw(roundOver);
        window.draw(message);
        window.draw(cursor);
        window.setView(overview);
        window.display();
    }

    return 0;
}