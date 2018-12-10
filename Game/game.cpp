//
// Created by dartmoor on 27.11.18.
//

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "preload.h"




int main(int argc,char *argv[]) {
    // Создаем главное окно приложения
    sf::RenderWindow window(sf::VideoMode(640, 480), "Test"); // 640 480
    startGame(window);

    return 0;
}