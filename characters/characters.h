//
// Created by dartmoor on 11.11.18.
//

#ifndef NIGHTSWORD_CHARACTERS_H
#define NIGHTSWORD_CHARACTERS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>


class Hero {

protected:
    std::string name;
    //std::vector<int> inventory;
    int HP;
    int mass;
    int speed;
    int view;
    int accuracy;
    int step;
    bool reload=false;
public:
    float cordX, cordY, w,h;

    int direction;

    sf::String File;

    sf::Image image;//сфмл изображение

    sf::Texture texture;//сфмл текстура

    sf::Sprite sprite;//сфмл


    Hero(sf::String , float , float , float , float );

    void setHero(std::string ,int ,int ,int ,int ,int );

    void setHP(int damage){this->HP -= damage;};

    int getView() { return  this->view;};

    int getSpeed() { return this->speed;};

    int setStep(){return this->step-=1;};

    bool isReload();

    void getInfo();

    void setPlayerCordinate(float X , float Y){this->cordX = X; this->cordY = Y;};

    float getplayercoordinateX();

    float getplayercoordinateY();

    void update(float);

    void characterMove(float  , float );
};

class SmartEnemy: public Hero {
private:
//link for texture
public:

    SmartEnemy(sf::String F, float X, float Y, float W, float H): Hero( F,  X,  Y,  W,  H){};

};


class Enemy: public Hero {
private:
    //link for texture
public:
    //Enemy(): Hero( "Demon",  50,  0,  4,  6, 60){};

};


#endif //NIGHTSWORD_CHARACTERS_H
