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

//// getSprite

class Item{
protected:
    float crdX, crdY;
    std::string name;
    int HPchange;
    int mass;
    int type;
public:

    float getCrdX(){return this->crdX;};

    float getCrdY(){return this->crdY;};

    void setCrd(float X, float Y){this->crdX = X;this->crdY=Y;}

    virtual void getInfo(){std::cout<<"nothing"<<std::endl;};

    int getMass(){return this->mass;};

    int getHpChange(){return this->HPchange;};

    virtual int getRegen(){return 0;};

    virtual int getAidStep(){return 0;};

    virtual int getAmmoSize(){return 0;};

    virtual int getAccuracy(){return 100;};

    virtual void setCurrentSize(int count){};

    std::string getName(){return this->name;};

    virtual std::string getTypeOfAmmo(){return " ";};

    virtual int getBullets(){ return 0;};

    virtual void setCapacity(int cap){};

    virtual int getCapacity(){return 0;};

    virtual int getCurrentCapacity(){return 0;};

    virtual void setCurrentCapacity(int shot){};

    int getType(){return this->type;};

    void modifyHP(){this->HPchange = 0;};

};


class Weapon: public Item {
protected:
    int accuracy;
    std::string typeOfAmmo;
    int bulletsPerShoot;
    int capacity;
    int currentCapacity;
public:

    Weapon(int,int,int,int ,const std::string&,int,const std::string&);

    int getAccuracy()override{return this->accuracy;};

    std::string getTypeOfAmmo()override{return this->typeOfAmmo;};

    void getInfo()override;

    int getBullets()override{ return this->bulletsPerShoot;};

    void setCapacity(int cap)override{this->currentCapacity = cap;};

    int getCapacity()override{return this->capacity;};

    int getCurrentCapacity()override{return this->currentCapacity;};

    void setCurrentCapacity(int shot)override{this->currentCapacity -= shot;};

};

class Ammo : public Item{
protected:
    int size;
public:

    Ammo(const std::string&, int, int);

    void setSize(int change);

    void getInfo()override;

    int getAmmoSize()override{return this->size;};

    void setCurrentSize(int count)override{this->size-=count;};

};

class Medkit: public Item {
protected:
    int step;

public:

    Medkit(int,int,const std::string&,int);

    void getInfo()override;

    virtual int getAidStep()override{return this->step;};

    int getRegen()override{return this->HPchange;};

};



class Inventory{
protected:
    std::vector<Item*> items;
public:

    const std::vector<Item*>& getIt() const{ return items; };

    Item* getItOne(int);

    void setIt(Item* some){this->items.push_back(some);};

    void throwIt(int index){ this->items.erase(items.begin() + index);};

};


#endif //NIGHTSWORD_ITEMS_H


