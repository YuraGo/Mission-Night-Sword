//
// Created by dartmoor on 12.11.18.
//

#ifndef NIGHTSWORD_GRAPHICS_H
#define NIGHTSWORD_GRAPHICS_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../characters/characters.h"
#include "../items/items.h"


const int H = 16;
const int W = 42;


    std::string TileMap[H]={
            "000000000000000000000000000000000000000000", //0
            "0                 0                      0", //1
            "0                 0                      0",//2
            "0                 0                      0",//3
            "0                                        0",//4
            "0                                        0",//5
            "0000000000000000000000000D0000000000000000",//6
            "0       0                    0           0",//7
            "0       0                    0           0",//8
            "0       0                00000000        0",//9
            "0       00000000         0               0",//10
            "0       0                0               0",//11
            "0       0                0               0",//12
            "0                                        0",//13
            "0                                        0",//14
            "000000000000000000000000000000000000000000"//15
    };








#endif //NIGHTSWORD_GRAPHICS_H
