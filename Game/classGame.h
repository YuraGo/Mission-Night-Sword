//
// Created by dartmoor on 02.12.18.
//

#ifndef NIGHTSWORD_CLASSGAME_H
#define NIGHTSWORD_CLASSGAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../characters/characters.h"
#include "../items/items.h"
#include <vector>
#include <string>



class Location;

class classGame {
public:
    std::vector<Hero> mans;
    std::vector<Enemy> evils;
    Inventory someItem;

    bool moveHero(int,float, float,Location&);

    void heroIsNear();

    void moveAI(int);

    bool endGameCheck();

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


    std::vector<AllForSprite> heroSprite;

    std::vector<AllForSprite> itemSprite;

    std::vector<AllForSprite> enemySprite;



};




#endif //NIGHTSWORD_CLASSGAME_H
