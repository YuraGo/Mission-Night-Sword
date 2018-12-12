//
// Created by dartmoor on 27.11.18.
//

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "preload.h"

using namespace sf;
void menu(sf::RenderWindow &window){
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
            isMenu = false;
        }

        window.draw(menuBg);
        window.draw(option1);
        window.draw(option2);
        window.display();
    }

}

void gameRun(RenderWindow & window, int & numberLevel){
    if (startGame(window,numberLevel)) {
        numberLevel++;
        gameRun(window,numberLevel);
    }
}

int main(int argc,char *argv[]) {
    int numberLevel=0;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test"); // 640 480
    menu(window);
    gameRun(window,numberLevel);
    return 0;
}