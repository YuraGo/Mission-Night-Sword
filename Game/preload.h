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

void createHero(std::vector<Hero>& mans);

bool tileInfo(float X , float Y, std::vector<Hero>* mans, std::vector<Enemy>* evils);

bool damageCorrect(float X, float Y,std::vector<Enemy>& mans,int Ac,int damage);

bool ammoCheck(Inventory& items, int clip);

void whereGo(sf::CircleShape& radiusOfMove,int speed, float X, float Y);

bool rangeOfAct (float X, float Y,float anX, float anY,float plus=32.f ) ;

bool openDoor(float X, float Y, float plX, float plY);

void startCord(std::vector<Enemy> &evils,Inventory& item);

bool startGame(sf::RenderWindow &window);

void createAll(classGame&);



#endif //NIGHTSWORD_PRELOAD_H
