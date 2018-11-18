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

    sf::String File;

    sf::Image image;//сфмл изображение

    sf::Texture texture;//сфмл текстура

    sf::Sprite sprite;//сфмл


    Hero(sf::String , float , float , float , float );

    void setHero(std::string ,int ,int ,int ,int ,int );

    void setHP(int damage){ this->HP -= damage; };

    int getView() { return  this->view;};

    int getSpeed() { return this->speed;};

    void setStep(int P){this->step+=P;};

    int getStep(){return this->step;};

    int getHP() { return  this->HP;};

    int getMass() { return  this->mass;};

    int getAccuracy() { return  this->accuracy;};

    bool isReload();

    void getInfo();

    void setPlayerCordinate(float X , float Y){this->cordX = X; this->cordY = Y;};

    float getplayercoordinateX();

    float getplayercoordinateY();

    void update(float);


    bool characterMove(float  , float,int x=0 );
};

class SmartEnemy: public Hero {
private:
//link for texture
public:

    SmartEnemy(sf::String F, float X, float Y, float W, float H): Hero( F,  X,  Y,  W,  H){};

};


class Enemy: public Hero {
private:
    bool agressive = false;
    //link for texture
public:
    Enemy(sf::String F, float X, float Y, float W, float H): Hero( F,  X,  Y,  W,  H){};

    bool getAgr(){return this->agressive;};

    void setAgr(bool agr){this->agressive = agr;};
};


#endif //NIGHTSWORD_CHARACTERS_H
