//
// Created by dartmoor on 11.11.18.
//

#ifndef NIGHTSWORD_CHARACTERS_H
#define NIGHTSWORD_CHARACTERS_H

#include <string.h>
#include <string>
#include <vector>
#include "../items/items.h"



class Enemy;

bool damageCorrect(float , float ,std::vector<Enemy>& ,int ,int );
bool ammoCheck(Inventory& , int );

class Hero {

protected:
    std::string name;
    int HP;
    int mass;
    int currentMass;
    int currentHP;
    int speed;
    int view;
    int accuracy;
    int step;
    float cordX, cordY, w,h;
public:

    Inventory rukzak;

    void setHero(const std::string&,int ,int ,int ,int ,int , float, float);

    void setHP(int damage){ this->currentHP -= damage; };

    int getView() { return  this->view;};

    int getSpeed() { return this->speed;};

    void setStep(int P){this->step+=P;};

    int getStep(){return this->step;};

    int getHP() { return  this->HP;};

    int getMass() { return  this->mass;};

    void setCurrentMass(int mass){this->currentMass +=mass;};

    int getAccuracy() { return  this->accuracy;};

    int getCurrentMass(){return this->currentMass;};

    int getCurrentHP(){return this->currentHP;};

    void getInfo();

    void setPlayerCordinate(float X , float Y){this->cordX = X; this->cordY = Y;};

    float getCordX(){return this->cordX;};

    float getCordY(){return this->cordY;};

    void update(float);

    bool characterMove(float  , float,int range=0 );

    std::string Attack(int countOfInventorySlot, float X, float Y,std::vector<Enemy>& );

    bool reload();

    bool heal(int countOfInventorySlot);
};

class SmartEnemy: public Hero {
private:
    bool agressive = false;
public:

    bool getAgr(){return this->agressive;};

    void setAgr(bool agr){this->agressive = agr;};

};


class Enemy: public Hero {
private:
    bool agressive = false;
    int damage = 20;
    //link for texture
public:

    bool getAgr(){return this->agressive;};

    void setAgr(bool agr){this->agressive = agr;};

    int getDamage(){return this->damage;};
};


#endif //NIGHTSWORD_CHARACTERS_H
