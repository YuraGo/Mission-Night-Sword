//
// Created by dartmoor on 02.12.18.
//

#ifndef NIGHTSWORD_PRELOAD_H
#define NIGHTSWORD_PRELOAD_H

#include "../characters/characters.h"
#include "preload.h"
#include "random"
#include "../items/items.h"


bool tileInfo(float X , float Y, std::vector<Hero>* mans, std::vector<Enemy>* evils){
    bool check = true;

    if(mans != nullptr){
        for(auto it : *mans){
            if(X == it.getSprite().getPosition().x && Y == it.getSprite().getPosition().y)
                check = false;
        }}

    if(evils != nullptr){
        for(auto it : *evils){
            if(X == it.getSprite().getPosition().x && Y == it.getSprite().getPosition().y)
                check = false;
        }}


    if(Y/32 <= 0)
        return false;
    if(X/32 <= 0)
        return false;
    if(X/32 >= 42-1)// W
        return false;
    if(Y/32 >= 16-1)//H
        return false;

    // for(int p = 0; p < 42 ;p ++) {//25
    if (Y / 32 == 6 && X / 32 != 25)
        return false;
    // }
    for(int p = 1; p < 4 ;p ++) {
        if (Y / 32 == p && X / 32 == 18)
            return false;
    }

    for(int p = 30; p < 35 ;p ++) {
        if (Y / 32 == 6 && X / 32 == p)
            return false;
    }

    for(int p = 25; p < 31 ;p ++) {
        if (Y / 32 == 9 && X / 32 == p)
            return false;
    }
    for(int p = 7; p < 11 ;p ++) {
        if (Y / 32 == p && X / 32 == 8)
            return false;
    }

    return check;
}

bool damageCorrect(float X, float Y,std::vector<Enemy>& mans,int Ac,int damage) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    if (dist(gen) >= Ac) return false;


    for(auto it = 0; it != mans.size(); it++){
        if(X == mans[it].getSprite().getPosition().x && Y == mans[it].getSprite().getPosition().y) {
            mans[it].setHP(damage);
            if(mans[it].getCurrentHP() <= 0){
                mans[it].setStep(-1000);
                mans.erase(mans.begin() + it);
            }
            break;
        }
    }
    return true;
}
////////play.mans[choiseMan].rukzak
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


void whereGo(sf::CircleShape& radiusOfMove,int speed, float X, float Y){
    //std::cout<<"?"<<std::endl;
    radiusOfMove.setRadius(32*speed);
    radiusOfMove.setPosition(X - 32*speed ,Y - 32*speed);
    //radiusOfMove.setPosition(X  ,Y );
    radiusOfMove.setFillColor(sf::Color(210,210,0,30));
}

bool rangeOfAct (float X, float Y,float anX, float anY,float plus=32.f ) {
    return ((X - anX)*(X - anX) + (Y - anY) * (Y - anY) ) <= (plus)*(plus);
}

bool openDoor(float X, float Y, float plX, float plY){

    if(X/32 == 25 && Y/32 == 6) {
        if( rangeOfAct(X,Y,plX,plY,32))
            return true;
    }
    return false;
}



void startCord(std::vector<Enemy> &evils,Inventory& item){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distY(1, 15);
    std::uniform_int_distribution<> distX(8, 38);
    float X,Y,Xi,Yi;

    for(auto it = 0;it != evils.size(); it++){
        X = distX(gen)*32;
        Y = distY(gen)*32;

        if(tileInfo(X,Y,nullptr, &evils)) {
            evils[it].getSprite().setPosition(X, Y);
            evils[it].setPlayerCordinate(X,Y);
        }
        else it--;
    }

    // for(auto it: item.getIt()){
    for(int it = 0;it != item.getIt().size(); it++){
        //item.getItOne(it)->getInfo();
        Xi = distX(gen)*32;
        Yi = distY(gen)*32;
        if(tileInfo(Xi,Yi,nullptr, nullptr))
            item.getItOne(it)->getSprite().setPosition(Xi,Yi);
        else it--;
    }


}



#endif //NIGHTSWORD_PRELOAD_H
