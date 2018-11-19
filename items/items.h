//
// Created by dartmoor on 11.11.18.
//

#ifndef NIGHTSWORD_ITEMS_H
#define NIGHTSWORD_ITEMS_H



#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Weapon {
private:
    std::string name;
    int damage;
    int accuracy;
    std::string typeOfAmmo;
    int mass;
    sf::String File;
    sf::Image image;//сфмл изображение
    sf::Texture texture;//сфмл текстура
public:
    Weapon(int,int,int,std::string,int,std::string);

    void getInfo();

};

class Ammo{
private:
    std::string type;
    int size;
    int mass;
    sf::String File;
    sf::Image image;//сфмл изображение
    sf::Texture texture;//сфмл текстура
public:
    Ammo(std::string, int, int);

    void setSize(int change);
};

class Medkit {
private:
    int mass;
    int regen;
    int step;
    sf::String File;
    sf::Image image;//сфмл изображение
    sf::Texture texture;//сфмл текстура
public:
    Medkit(int,int,int);
};

template <class item>
class Inventory{
protected:
    item *thing;

public:
    explicit Inventory(item ptr){this->thing = ptr;};

    void getInfo(){this->thing.getInfo();};


};


#endif //NIGHTSWORD_ITEMS_H


