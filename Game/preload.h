//
// Created by dartmoor on 12.11.18.
//

#ifndef NIGHTSWORD_PRELOAD_H
#define NIGHTSWORD_PRELOAD_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include "../Graphics/graphics.h"
#include <iostream>
#include "../characters/characters.h"
#include "../items/items.h"
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <sstream>
#include <random>
#include "../Game/classGame.h"


bool tileInfo(float X , float Y, std::vector<Hero>* mans, std::vector<Enemy>* evils);

bool tileCheck(float , float , Location* );

float rangeOfMove(float X,float Y,float anX,float anY);

void whereGo(sf::CircleShape& radiusOfMove,int speed, float X, float Y);

bool rangeOfAct (float X, float Y,float anX, float anY,float plus=32.f ) ;

bool openDoor(float X, float Y, float plX, float plY);

void startCord(std::vector<Enemy> &evils,Inventory& item);

bool startGame(sf::RenderWindow &window, int numberLevel);

void createAll(classGame&);



#endif //NIGHTSWORD_PRELOAD_H
