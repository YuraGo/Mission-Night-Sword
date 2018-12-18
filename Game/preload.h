//
// Created by dartmoor on 12.11.18.
//

#ifndef NIGHTSWORD_PRELOAD_H
#define NIGHTSWORD_PRELOAD_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
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



bool startGame(sf::RenderWindow &window, int numberLevel,std::vector<int> whatPick);



#endif //NIGHTSWORD_PRELOAD_H
