//
// Created by dartmoor on 27.11.18.
//

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "preload.h"


using namespace sf;
std::vector<int> whatPick;

void newGame(sf::RenderWindow &window,std::vector<int>& whatPick){

    sf::Texture menuBackground;
    menuBackground.loadFromFile("menu2.jpg");
    sf::Sprite menuBg(menuBackground);
    bool isMenu = true;
    menuBg.setPosition(0, 0);
    sf::Font font;
    font.loadFromFile("CyrilicOld.TTF");

    sf::Text hero1("3 - Name: Bob, HP: 100, Mass: 30, Accuracy: 60, Speed: 4",font,25);
    sf::Text hero2("4 - Name: Tesla, HP: 80, Mass: 40, Accuracy: 85, Speed: 5",font,25);
    sf::Text hero3("5 - Name: Eva, HP: 60, Mass: 25, Accuracy: 100, Speed: 8",font,25);
    sf::Text hero4("6 - Name: Beast, HP: 75, Mass: 35, Accuracy: 75, Speed: 5",font,25);
    sf::Text exit("To play enter Escape",font,40);

    hero1.setFillColor(sf::Color(214, 181, 15));
    hero2.setFillColor(sf::Color(22, 224, 150));
    hero3.setFillColor(sf::Color(230, 11, 200));
    hero4.setFillColor(sf::Color(224, 22, 22));
    exit.setFillColor(sf::Color::Blue);

    hero1.setPosition(20,100);
    hero2.setPosition(20,160);
    hero3.setPosition(20,220);
    hero4.setPosition(20,280);
    exit.setPosition(80,320);

    int i = 0;
    whatPick.push_back(0);
    whatPick.push_back(0);

    while (isMenu)
    {
        sf::Event eva;
        window.clear(Color::Black);

        while(window.pollEvent(eva)) {

            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                isMenu = false;
            }

            if (eva.type == sf::Event::KeyPressed && eva.key.code == sf::Keyboard::Num3) {
                whatPick[i] = 0;
                i++;
            }

            if (eva.type == sf::Event::KeyPressed && eva.key.code == sf::Keyboard::Num4) {
                whatPick[i] = 1;
                i++;
            }

            if(eva.type == sf::Event::KeyPressed && eva.key.code == sf::Keyboard::Num5) {
                whatPick[i] = 2;
                i++;
            }

            if(eva.type == sf::Event::KeyPressed && eva.key.code == sf::Keyboard::Num6) {
                whatPick[i] = 3;
                i++;
            }

        }

//        if(Keyboard::isKeyPressed(Keyboard::Num4)) {
//            whatPick[i] = 1;
//            i++;
//        }

        if(i > 2) isMenu = false;

        window.draw(menuBg);
        window.draw(hero1);
        window.draw(hero2);
        window.draw(hero3);
        window.draw(hero4);
        window.draw(exit);
        window.display();
    }
}



void menu(sf::RenderWindow &window,std::vector<int>& whatPick){
    sf::Texture menuBackground;
    menuBackground.loadFromFile("menu2.jpg");
    sf::Sprite menuBg(menuBackground);
    bool isMenu = true;
    int menuNum = 0;
    menuBg.setPosition(0, 0);

    sf::Font font;
    font.loadFromFile("CyrilicOld.TTF");
    sf::Text option1("Start Game - 0",font,40);
    sf::Text option2("Exit - Escape",font,40);
    option1.setFillColor(sf::Color::Black);
    option2.setFillColor(sf::Color::Black);

    option1.setPosition(10,30);
    option2.setPosition(10,250);

    while (isMenu)
    {

        window.clear(Color::Black);

        if(Keyboard::isKeyPressed(Keyboard::Escape)) {
            isMenu = false;
        }
        if(Keyboard::isKeyPressed(Keyboard::Num0)) {
            newGame(window, whatPick);
            isMenu = false;
        }

        window.draw(menuBg);
        window.draw(option1);
        window.draw(option2);
        window.display();
    }

}




void gameRun(RenderWindow& window, int &numberLevel){
    if (startGame(window,numberLevel,whatPick)) {
        numberLevel++;
        gameRun(window,numberLevel);
    }
}

int main(int argc,char *argv[]) {
   // std::vector<int> whatPick;
    int numberLevel=0;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Night Sword"); // 640 480
    menu(window,whatPick);
    gameRun(window,numberLevel);
    return 0;
}