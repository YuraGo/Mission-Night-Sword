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

    Inventory someItem;

    bool moveHero(int,float, float);

   // void createItems();

};

class Location{
private:
    bool cellInfo[16][42];
public:

    std::string karta[16];
    //std::string karta;

    Location();

    bool getCellInfo(int x, int y){return cellInfo[x][y];}

    void clearMap();

    void minIpdate(int prevX, int prevY, int X, int Y){ cellInfo[X][Y]=true; cellInfo[prevX][prevY] = false;};

    void updateMap(int x,int y){cellInfo[x][y] = true;}
};



class AllForSprite{
public:
    sf::String File;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string name;

    void makeSprite(const sf::String& , float , float , float , float );

    void makeItemSprite(const sf::String&,const std::string&);

};

class Pictures{
public:


    std::vector<AllForSprite*> heroSprite;

    std::vector<AllForSprite*> itemSprite;

    std::vector<AllForSprite*> enemySprite;



};

#endif //NIGHTSWORD_CLASSGAME_H
