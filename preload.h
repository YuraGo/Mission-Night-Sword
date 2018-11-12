//
// Created by dartmoor on 12.11.18.
//

#ifndef NIGHTSWORD_PRELOAD_H
#define NIGHTSWORD_PRELOAD_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Graphics/graphics.h"
#include <iostream>
#include "characters/characters.h"
#include <stdio.h>

sf::RectangleShape& cursorMove(sf::RectangleShape& Cursor,char dir){
    //sf::RectangleShape cursor;
    sf::Vector2f pos = Cursor.getPosition();


    if(dir == 'r')
        Cursor.move(32,0);
    if(dir == 'l')
        Cursor.move(-32,0);
    if(dir == 'u')
        Cursor.move(0,-32);
    if(dir == 'd')
        Cursor.move(0,32); // move time


    //return cursor;
}


sf::CircleShape& whereGo(sf::CircleShape& radiusOfMove,int speed, float X, float Y){
    //std::cout<<"?"<<std::endl;
    radiusOfMove.setRadius(32*speed);
    radiusOfMove.setPosition(X - 32*speed ,Y - 32*speed);
    //radiusOfMove.setPosition(X  ,Y );
    radiusOfMove.setFillColor(sf::Color(210,210,0,40));
}

//bool pathIsCorrect(float startX, float startY, float X , float Y ){
//    std::cout<<"X = "<< X/32;
//    int x = X/32;
//    int y = Y/32;
//    std::cout<< "  x = "<< x/32<< std::endl;
//
//    if(TileMap[x][y] == 'W' || TileMap[x][y]=='D'){
//        return false;
//    }
//
//
//    for(int i = 0; i < H; i++){
//        for(int j = 0 ; j < W; j++){
//
//        }
//    }
//    return true;
//
//}




#endif //NIGHTSWORD_PRELOAD_H
