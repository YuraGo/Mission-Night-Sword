//
// Created by dartmoor on 12.11.18.
//

#ifndef NIGHTSWORD_GRAPHICS_H
#define NIGHTSWORD_GRAPHICS_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


const int H = 16;
const int W = 45;

sf::String TileMap[H]={
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", //0
        "W   F      F  F      W       F     F     W", //1
        "W   F   F    F   F      W      F         W",//2
        "W F  F   D F       F  D  F   F      F    W",//3
        "W   F  F  F  F    F     W    F  F        W",//4
        "W     F   F     F      W   F             W",//5
        "WWWWWWWWWWWWWWWWWWWWWWWWW     WWW        W",//6
        "W       W  F              F              W",//7
        "W       W         F         F            W",//8
        "W       W                WWWWWW          W",//9
        "W       W                  F             W",//10
        "W                         F              W",//11
        "W         F      F                       W",//12
        "W                        F               W",//13
        "W          F                             W",//14
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"//15
};











#endif //NIGHTSWORD_GRAPHICS_H
