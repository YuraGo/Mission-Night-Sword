#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Graphics/graphics.h"
#include <iostream>
#include "characters/characters.h"
#include "preload.h"



int main() {
    // Создаем главное окно приложения
    sf::RenderWindow window(sf::VideoMode(640, 480), "Test");
    sf::Clock clock;

    float CurrentFrame = 0;
// Включаем вертикальную синхронизацию (для плавной анимации)
    window.setVerticalSyncEnabled(true);

    sf::View overview;
    overview.setSize(sf::Vector2f(540.f, 380.f));
    overview.setCenter(320,240);

    sf::RectangleShape cursor(sf::Vector2f(32.f, 32.f));
    cursor.setFillColor(sf::Color(0,255,0,60));
    sf::CircleShape radiusOfMove(0);


    sf::Font font;
    font.loadFromFile("CyrilicOld.TTF");

    sf::Text message("",font,20);
    message.setFillColor(sf::Color::Red);

    sf::Image mapImage;
    mapImage.loadFromFile("mapTexture.png");
    sf::Texture map;
    map.loadFromImage(mapImage);
    sf::Sprite s_map;
    s_map.setTexture(map);

    std::vector<Hero> mans;


    Hero player1("warrior1.png",32,32,55,55);
    Hero player2("warrior1.png",64,64,55,55);
    player1.setHero("Bob",20,50,5,8,80);
    player2.setHero("Silver",20,50,10,10,80);



    mans.push_back(player1);
    mans.push_back(player2);

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


                    if (event.key.code == sf::Keyboard::Num1) {
                        overview.setCenter(mans[0].sprite.getPosition().x, mans[0].sprite.getPosition().y);
                        cursor.setPosition(mans[0].sprite.getPosition().x, mans[0].sprite.getPosition().y);
                        whereGo(radiusOfMove, mans[0].getSpeed(),mans[0].sprite.getPosition().x, mans[0].sprite.getPosition().y);
                    }
                    if (event.key.code == sf::Keyboard::Num2) {
                        overview.setCenter(mans[1].sprite.getPosition().x, mans[1].sprite.getPosition().y);
                        cursor.setPosition(mans[1].sprite.getPosition().x, mans[1].sprite.getPosition().y);
                        whereGo(radiusOfMove, mans[1].getSpeed(), mans[1].sprite.getPosition().x, mans[1].sprite.getPosition().y);
                    }

//                    if (event.key.code == sf::Keyboard::Space) {
//                        if( pathIsCorrect( mans[0].sprite.getPosition().x,mans[0].sprite.getPosition().y,
//                                cursor.getPosition().x , cursor.getPosition().y) )
//                            mans[0].characterMove(cursor.getPosition().x, cursor.getPosition().y);
                        //player1.characterMove(32, 32);
                        //player1.sprite.move(128,128);
                    //}
                    break;

                }
                default:
                    break;
            }
//             Кроме обычного способа наше окно будет закрываться по нажатию на Escape
//            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
//                window.close();
//
//            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
//
//                cursor.setPosition(player1.sprite.getPosition().x, player1.sprite.getPosition().y);
//                whereGo(radiusOfMove, player1.getSpeed(), player1.sprite.getPosition().x, player1.sprite.getPosition().y);
//
//            }
//
//                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
//                    std::cout<<" ? "<< cursor.getPosition().x << " , "<< cursor.getPosition().y<<std::endl;
//                    player1.characterMove(cursor.getPosition().x, cursor.getPosition().y);
//                    //player1.characterMove(32, 32);
//                    //player1.sprite.move(128,128);
//                }


        }


        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right){
            //sf::Vector2f pos = cursor.getPosition();
            cursorMove(cursor, 'r');
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left){
            //sf::Vector2f pos = cursor.getPosition();
            cursorMove(cursor, 'l');
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
            //sf::Vector2f pos = cursor.getPosition();
            cursorMove(cursor, 'u');
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){
            //sf::Vector2f pos = cursor.getPosition();
            cursorMove(cursor, 'd');
        }

        if (event.key.code == sf::Keyboard::Space) {

           // bool YouCan = pathIsCorrect(mans[0].sprite.getPosition().x,mans[0].sprite.getPosition().y,
                                //cursor.getPosition().x , cursor.getPosition().y);

            if(cursor.getPosition().x == mans[1].sprite.getPosition().x  && cursor.getPosition().y == mans[1].sprite.getPosition().y ){
                std::cout<<"I cant"<<std::endl;
                message.setString("I cant");
                message.setPosition( mans[0].sprite.getPosition().x , mans[0].sprite.getPosition().y-20 );
            }else {
                message.setString("");
                mans[0].characterMove(cursor.getPosition().x, cursor.getPosition().y);
                mans[0].setPlayerCordinate(cursor.getPosition().x, cursor.getPosition().y);
            }


        }

        // Очистка
        window.clear(sf::Color(176, 147, 60));

        for(int i=0;i<H;i++){
            for(int j=0;j<W;j++) {

                if(TileMap[i][j] == 'W') s_map.setTextureRect(sf::IntRect(384,128,416,160)); // 8W 5H
                if(TileMap[i][j] == 'D') s_map.setTextureRect(sf::IntRect(160,96,192,128));
                if(TileMap[i][j] == ' ') s_map.setTextureRect(sf::IntRect(128,224,160,256));
                if(TileMap[i][j] == 'F') s_map.setTextureRect(sf::IntRect(128,160,160,192));

                s_map.setPosition(j*32,i*32);
                window.draw(s_map);
            }
        }
//        std::cout<<"X: " << player1.sprite.getPosition().x << "   "<< player1.cordX<<std::endl;
//        std::cout<<"Y: " << player1.sprite.getPosition().y << std::endl;

        mans[0].update(time);
        clock.restart();
        // Тут будут вызываться функции обновления и отрисовки объектов
        // Отрисовка
        window.draw(radiusOfMove);

        for(auto i: mans)
        window.draw(i.sprite);


        window.draw(message);
        window.draw(cursor);
        window.setView(overview);
        window.display();
    }

    return 0;
}