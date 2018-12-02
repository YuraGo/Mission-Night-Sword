//
// Created by dartmoor on 02.12.18.
//

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../characters/characters.h"

void tableEnemyDraw(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2, float X,float Y, Enemy* player) {
    table.setPosition(X+40,Y) ;//-270
    text1.setPosition(X+45,Y+5);
    text2.setPosition(X+45,Y+23);

    table.setFillColor(sf::Color::Black);
    text1.setFillColor(sf::Color::Yellow);
    text2.setFillColor(sf::Color::Yellow);

    text1.setString("HP: " + std::to_string(player->getCurrentHP()) +"/"+ std::to_string(player->getHP()) + "  Speed: " + std::to_string(player->getSpeed()));

    text2.setString("Step: " + std::to_string(player->getStep()) +"  Accuracy: " + std::to_string(player->getAccuracy()) + " Arg: "+ std::to_string(player->getAgr()));

}

void tableInfodraw(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3, float X,float Y, Hero* player) {
    table.setPosition(X-270,Y + 120);//-270
    text1.setPosition(X-265,Y + 125);
    text2.setPosition(X-265,Y + 144);
    text3.setPosition(X-265,Y + 160);

    text1.setString("HP: " + std::to_string(player->getCurrentHP()) + "/" + std::to_string(player->getHP()) +" " + "Speed: " + std::to_string(player->getSpeed()));

    text2.setString("Step: " + std::to_string(player->getStep()) +"  " + "Mass: " + std::to_string(player->getCurrentMass()) + "/" +std::to_string(player->getMass()));

    text3.setString("Accuracy: " + std::to_string(player->getAccuracy() ));
}

sf::RectangleShape& cursorMove(sf::RectangleShape& Cursor,char dir){
    //sf::RectangleShape cursor;
    //sf::Vector2f pos = Cursor.getPosition();
    if(dir == 'r')
        Cursor.move(32.f,0);
    if(dir == 'l')
        Cursor.move(-32.f,0);
    if(dir == 'u')
        Cursor.move(0,-32.f);
    if(dir == 'd')
        Cursor.move(0,32.f); // move time

    //return cursor;
}