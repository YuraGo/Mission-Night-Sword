//
// Created by dartmoor on 11.11.18.
//

#include "characters.h"
#include <iostream>
#include <random>
#include "../Game/preload.h"


//Hero::Hero(const sf::String& F, float X, float Y, float W, float H) {
//    File = F;//имя файла+расширение
//    //File = "solder.png";
//    w = W;
//    h = H;//высота и ширина
//    image.loadFromFile(File);
//    texture.loadFromImage(image);
//    sprite.setTexture(texture);
//    cordX = X;
//    cordY = Y;
//    sprite.setPosition(cordX,cordY);
//    sprite.setTextureRect(sf::IntRect(0, 0, (int)w,(int)h));
//}

void Hero::setHero(const std::string &Name, int hp, int Mass, int Speed, int View,int Accuracy ,float X, float Y){
    this->name = Name;
    this->HP = hp;
    this->currentHP = hp;
    this->currentMass = 0;
    this->mass = Mass;
    this->speed = Speed;
    this->view = View;
    this->accuracy = Accuracy;
    this->step = 2;

    this->cordX = X;
    this->cordY = Y;
}


void Hero::getInfo() {
    std::cout<<"name "<<this->name<<std::endl;
    std::cout<<"HP "<<this->HP<<std::endl;
    std::cout<<"mass "<<this->mass<<std::endl;
    std::cout<<"speed "<<this->speed<<std::endl;
    std::cout<<"View "<<this->view<<std::endl;
    std::cout<<"accuracy "<<this->accuracy<<std::endl;
    std::cout<<"step "<<this->step<<std::endl;
    //std::cout<<"inventory "<<this->inventory<<std::endl;
}



bool Hero::characterMove(float X, float Y,int range) {
    return ( (X-this->getCordX())*(X - this->getCordX()) +
            (Y - this->getCordY()) * (Y - this->getCordY())
    <= ((this->speed+range)*32)*((this->speed+range)*32) );
}


std::string Hero::Attack(int countOfInventorySlot, float X, float Y, std::vector<Enemy>& evils) {

    if(this->characterMove(X,Y,2)) {
        if(ammoCheck( this->rukzak,0)) {
            if (damageCorrect(X, Y, evils,( this->getAccuracy() + this->rukzak.getItOne(countOfInventorySlot)->getAccuracy() )/2,
                              this->rukzak.getItOne(countOfInventorySlot)->getHpChange())) {
                this->setStep(-1);
                return ("Damage is" + std::to_string(this->rukzak.getItOne(countOfInventorySlot)->getHpChange()));
            } else {
                this->setStep(-1);
                return ("Miss...");
            }

        } else{
            return ("Not enough ammo...");
        }
    }else {
        return ("Too far...");
    }

}

bool Hero::heal(int countOfInventorySlot) {

    if( this->rukzak.getItOne(countOfInventorySlot)->getRegen() != 0 &&
            this->getStep() >= rukzak.getItOne(countOfInventorySlot)->getAidStep() &&
            this->getCurrentHP() != this->getHP()) {
        this->setHP(-rukzak.getItOne(countOfInventorySlot)->getRegen());
        this->setStep(-rukzak.getItOne(countOfInventorySlot)->getAidStep());
        this->rukzak.throwIt(countOfInventorySlot);
        if (this->getCurrentHP() > this->getHP())
            this->setHP(this->getCurrentHP() - this->getHP());
        return true;

    } else return false;
}

bool Hero::reload() {

    if(ammoCheck( this->rukzak,1)){
        this->setStep(-1);
        return true;
    }else {
        return false;
    }

}

void Hero::update(float time)
{
//    switch (direction)
//    {
//        case 0: dx = speed; dy = 0; break;
//        case 1: dx = -speed; dy = 0; break;
//        case 2: dx = 0; dy = speed; break;
//        case 3: dx = 0; dy = -speed; break;
//    }

    //cordX += dx*time;
    //cordY += dy*time;

    //speed = 0;
    //sprite.setPosition(x, y);
}


