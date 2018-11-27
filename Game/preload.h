//
// Created by dartmoor on 12.11.18.
//

#ifndef NIGHTSWORD_PRELOAD_H
#define NIGHTSWORD_PRELOAD_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/graphics.h"
#include <iostream>
#include "../characters/characters.h"
#include "../items/items.h"
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <sstream>
#include <random>


void tableEnemyDraw(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2, float X,float Y, Enemy* player) {
    table.setPosition(X+40,Y) ;//-270
    text1.setPosition(X+45,Y+5);
    text2.setPosition(X+45,Y+23);

    table.setFillColor(sf::Color::Black);
    text1.setFillColor(sf::Color::Yellow);
    text2.setFillColor(sf::Color::Yellow);


    text1.setString("HP: " + std::to_string(player->getCurrentHP()) +"/"+ std::to_string(player->getHP()) + "  Speed: " + std::to_string(player->getSpeed()));

    text2.setString("Step: " + std::to_string(player->getStep()) +"  Accuracy: " + std::to_string(player->getAccuracy()) + " Arg: "+ std::to_string(player->getAgr()));

}



void tableInfodraw(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3, float X,float Y, Hero* player) {
    table.setPosition(X-270,Y + 120);//-270
    text1.setPosition(X-265,Y + 125);
    text2.setPosition(X-265,Y + 144);
    text3.setPosition(X-265,Y + 160);

    text1.setString("HP: " + std::to_string(player->getCurrentHP()) + "/" + std::to_string(player->getHP()) +" " + "Speed: " + std::to_string(player->getSpeed()));

    text2.setString("Step: " + std::to_string(player->getStep()) +"  " + "Mass: " + std::to_string(player->getCurrentMass()) + "/" +std::to_string(player->getMass()));

    text3.setString("Accuracy: " + std::to_string(player->getAccuracy() ));
}


sf::RectangleShape& cursorMove(sf::RectangleShape& Cursor,char dir){
    //sf::RectangleShape cursor;
    //sf::Vector2f pos = Cursor.getPosition();

    if(dir == 'r')
        Cursor.move(32.f,0);
    if(dir == 'l')
        Cursor.move(-32.f,0);
    if(dir == 'u')
        Cursor.move(0,-32.f);
    if(dir == 'd')
        Cursor.move(0,32.f); // move time


    //return cursor;
}



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
    if(X/32 >= W-1)
        return false;
    if(Y/32 >= H-1)
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

bool ammoCheck(std::vector<Inventory>& items, int index, int clip){
    int i=0;
    std::string type;
    while(i <= items[index].getIt().size()) {

        if(items[index].getItOne(i)->getTypeOfAmmo() != " ") {
            type = items[index].getItOne(i)->getTypeOfAmmo();
            break;
        }else i++;
    }

    for(auto it: items[index].getIt() ){
        if( it->getName() == type){

                //// SHOOT
                if(clip == 0 && items[index].getItOne(i)->getBullets() <= items[index].getItOne(i)->getCurrentCapacity() ) {
                    //it->setCurrentSize(items[index].getItOne(i)->getBullets());
                    items[index].getItOne(i)->setCurrentCapacity(items[index].getItOne(i)->getBullets());
                    return true;
                }
                //// RELOAD
                if(clip != 0 && it->getAmmoSize() > 0 ){

                    if(items[index].getItOne(i)->getCurrentCapacity() > 0)
                        return false;

                    if( it->getAmmoSize() >= items[index].getItOne(i)->getCapacity() ) {
                        items[index].getItOne(i)->setCapacity(items[index].getItOne(i)->getCapacity());
                        it->setCurrentSize(items[index].getItOne(i)->getCapacity());
                    }
                    else {
                        std::cout<<"tyt je";
                        items[index].getItOne(i)->setCapacity( it->getAmmoSize() );
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


sf::CircleShape& whereGo(sf::CircleShape& radiusOfMove,int speed, float X, float Y){
    //std::cout<<"?"<<std::endl;
    radiusOfMove.setRadius(32*speed);
    radiusOfMove.setPosition(X - 32*speed ,Y - 32*speed);
    //radiusOfMove.setPosition(X  ,Y );
    radiusOfMove.setFillColor(sf::Color(210,210,0,30));
}

bool rangeOfAct (float X, float Y,float anX, float anY,int plus=32 ) {
    return ((X - anX)*(X - anX) + (Y - anY) * (Y - anY) )<= (plus)*(plus) ? true : false;
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

        if(tileInfo(X,Y,nullptr, &evils))
        evils[it].getSprite().setPosition(X,Y);
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
