//
// Created by dartmoor on 02.12.18.
//

#ifndef NIGHTSWORD_CLASSGAME_H
#define NIGHTSWORD_CLASSGAME_H
#include <iostream>
#include "../characters/characters.h"
#include "../items/items.h"
#include <vector>
#include <string>
#include "MyVector.h"







class Location;

class classGame {
public:
    vector<Hero> mans;
    std::vector<Enemy> evils;
    Inventory someItem;

    bool moveHero(int,float, float,Location&);

    void heroIsNear();

    void moveAI(int);

    bool endGameCheck();

    bool openDoor(float X, float Y, float plX, float plY);

    bool rangeOfAct (float X, float Y,float anX, float anY,float plus);

    bool tileInfo(float X , float Y, vector<Hero>*, std::vector<Enemy>*);

    bool tileCheck(float X , float Y, Location* location);

    float rangeOfMove(float X,float Y,float anX,float anY){return ((X - anX)*(X - anX) + (Y - anY) * (Y - anY) );}

    void startCord(std::vector<Enemy> &evils,Inventory& item);
};

class Location{
private:
    bool cellInfo[16][42];
public:

    bool getCellInfo(float x,float y){int X = (int)x/32;int Y = (int)y/32; return cellInfo[Y][X];}

    void clearMap();

    void miniUpdate(float ,float ,float , float );

    void updateMap(float x,float y){int X = (int)x/32;int Y = (int)y/32;  cellInfo[Y][X] = true;}
};








#endif //NIGHTSWORD_CLASSGAME_H
