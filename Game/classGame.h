//
// Created by dartmoor on 02.12.18.
//

#ifndef NIGHTSWORD_CLASSGAME_H
#define NIGHTSWORD_CLASSGAME_H
#include "game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../characters/characters.h"
#include "../items/items.h"
//#include "../Graphics/graphics.h"

//#include "AI.h"
#include <vector>
#include <string>

class classGame {
public:
    std::vector<Hero> mans;
    std::vector<Enemy> evils;

    std::vector<Inventory> stash;
    std::vector<Inventory> someItem;

    void createHero(std::string);

    void createEnemy();

    bool moveHero(int,float, float);


   // void createItems();




};


#endif //NIGHTSWORD_CLASSGAME_H
