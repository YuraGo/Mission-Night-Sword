//
// Created by dartmoor on 11.11.18.
//

#ifndef NIGHTSWORD_ITEMS_H
#define NIGHTSWORD_ITEMS_H


#include <string.h>
#include <iostream>
#include <string>
#include <vector>

class weapon {
private:
    std::string name;
    int damage;
    int accuracy;
    std::string typeOfAmmo;
    int mass;
public:
    weapon(int,int,int,std::string,int,std::string);

    void getInfo();

};

class Ammo{
private:
    std::string type;
    int size;
    int mass;
public:
    Ammo(std::string, int, int);

    void setSize(int change);
};

class Medkit {
private:
    int mass;
    int regen;
    int step;
public:
    Medkit(int,int,int);
};


#endif //NIGHTSWORD_ITEMS_H


