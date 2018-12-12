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

bool damageCorrect(float X, float Y,std::vector<Enemy>& mans,int Ac,int damage) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    if (dist(gen) >= Ac) return false;


    for(auto it = 0; it != mans.size(); it++){
        if(X == mans[it].getCordX() && Y == mans[it].getCordY()) {
            mans[it].setHP(damage);
            mans[it].setAgr(true);
            if(mans[it].getCurrentHP() <= 0){
                mans[it].setStep(-1000);
                mans.erase(mans.begin() + it);
            }
            break;
        }
    }
    return true;
}

bool ammoCheck(Inventory& items, int clip){
    int i=0;
    std::string type;
    //////// search type
    while(i <= items.getIt().size()) {

        if(items.getItOne(i)->getTypeOfAmmo() != " ") {
            type = items.getItOne(i)->getTypeOfAmmo();
            break;
        }else i++;
    }

    for(auto it: items.getIt() ){
        if( it->getName() == type){

            //// SHOOT
            if(clip == 0 && items.getItOne(i)->getBullets() <= items.getItOne(i)->getCurrentCapacity() ) {
                //it->setCurrentSize(items[index].getItOne(i)->getBullets());
                items.getItOne(i)->setCurrentCapacity(items.getItOne(i)->getBullets());
                return true;
            }
            //// RELOAD
            if(clip != 0 && it->getAmmoSize() > 0 ){

                if(items.getItOne(i)->getCurrentCapacity() > 0)
                    return false;

                if( it->getAmmoSize() >= items.getItOne(i)->getCapacity() ) {
                    items.getItOne(i)->setCapacity(items.getItOne(i)->getCapacity());
                    it->setCurrentSize(items.getItOne(i)->getCapacity());
                }
                else {

                    items.getItOne(i)->setCapacity( it->getAmmoSize() );

                    it->setCurrentSize(it->getAmmoSize());
                }

                return true;
            } else{
                return false;
            }

        }
    }
    return false;
}



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
        this->rukzak.getItOne(countOfInventorySlot)->modifyHP();
        //this->rukzak.throwIt(countOfInventorySlot);
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


