//
// Created by dartmoor on 16.11.18.
//

#ifndef NIGHTSWORD_AI_H
#define NIGHTSWORD_AI_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/graphics.h"
#include <iostream>
#include "../characters/characters.h"
#include "preload.h"


bool tileInfo(float X , float Y, std::vector<Hero>* mans, std::vector<Enemy>* evils){
    bool check = true;

    if(mans != nullptr){
        for(auto it : *mans){
            if(X == it.getCordX() && Y == it.getCordY())
                return false;
        }}

    if(evils != nullptr){
        for(auto it : *evils){
            if(X == it.getCordX() && Y == it.getCordY())
                return false;
        }}

//
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
//

    return check;
}

void moveAI(std::vector<Enemy>& evils,std::vector<Hero>* mans,int countOfMove) {
    float X, Y;
    bool another;
    bool correct;
    int demension;

    for (auto it = 0; it != evils.size(); it++) {
        if(evils[it].getAgr()) it++;
        correct = false;
        another = false;
        demension = 2;
        X = evils[it].getCordX();
        Y = evils[it].getCordY();

        while(!correct) {
            if (countOfMove == 1 || another) { // down Y+
                X = evils[it].getCordX();
                Y = evils[it].getCordY();
                Y += 96;

            while(!correct){
                if (tileInfo(X, Y, mans, &evils) && tileInfo(X, Y - 64, nullptr, nullptr)
                    && tileInfo(X, Y - 32, nullptr, nullptr)) {
                    evils[it].setPlayerCordinate(X, Y);
                    correct = true;
                    another = false;
                    break;
                }
                if (tileInfo(X, Y - 64, nullptr, nullptr) && tileInfo(X, Y - 32, mans,  &evils)) {
                    evils[it].setPlayerCordinate(X, Y - 32);
                    correct = true;
                    another = false;
                    break;
                }
                if (tileInfo(X, Y - 64, mans,  &evils)) {
                    evils[it].setPlayerCordinate(X, Y - 64);
                    correct = true;
                    another = false;
                    break;
                } else another = true;
                break;

            }
            }


            if (countOfMove == 2 || another) { // left X-
                X = evils[it].getCordX();
                Y = evils[it].getCordY();
                X -= 96;

                while (!correct) {
                    if (tileInfo(X, Y, mans, &evils) && tileInfo(X + 64, Y, nullptr, nullptr)
                        && tileInfo(X + 32, Y, nullptr, nullptr)) {
                        evils[it].setPlayerCordinate(X, Y);
                        correct = true;
                        another = false;
                        break;
                    }
                    if (tileInfo(X + 64, Y, nullptr, nullptr) && tileInfo(X + 32, Y, mans,  &evils)) {
                        evils[it].setPlayerCordinate(X + 32, Y);
                        correct = true;
                        another = false;
                        break;
                    }
                    if (tileInfo(X - 64, Y, mans,  &evils)) {
                        evils[it].setPlayerCordinate(X + 64, Y);
                        correct = true;
                        another = false;
                        break;

                    } else another = true;
                    break;

                }
            }


            if (countOfMove == 3 || another) { // Up Y+
                X = evils[it].getCordX();
                Y = evils[it].getCordY();
                Y -= 96;
                while(!correct) {
                    if (tileInfo(X, Y, mans, &evils) && tileInfo(X, Y + 64, nullptr, nullptr)
                        && tileInfo(X, Y + 32, nullptr, nullptr)) {
                        evils[it].setPlayerCordinate(X, Y);
                        correct = true;
                        another = false;
                        break;

                    }
                    if (tileInfo(X, Y + 64, nullptr, nullptr) && tileInfo(X, Y + 32, mans,  &evils)) {
                        evils[it].setPlayerCordinate(X, Y + 32);
                        correct = true;
                        another = false;
                        break;

                    }
                    if (tileInfo(X, Y + 64, mans,  &evils)) {
                        evils[it].setPlayerCordinate(X, Y + 64);
                        correct = true;
                        another = false;
                        break;
                    } else another = true;
                    break;
                }

            }


            if (countOfMove == 4 || another) { // Right X+
                X = evils[it].getCordX();
                Y = evils[it].getCordY();
                X += 96;
                while(!correct) {
                    if (tileInfo(X, Y, mans, &evils) && tileInfo(X - 64, Y, nullptr, nullptr)
                        && tileInfo(X - 32, Y, nullptr, nullptr)) {
                        evils[it].setPlayerCordinate(X, Y);
                        correct = true;
                        another = false;
                        break;
                    }
                    if (tileInfo(X - 64, Y, nullptr, nullptr) && tileInfo(X - 32, Y, mans,  &evils)) {
                        evils[it].setPlayerCordinate(X - 32, Y);
                        correct = true;
                        another = false;
                        break;
                    }
                    if (tileInfo(X - 64, Y, mans,  &evils)) {
                        evils[it].setPlayerCordinate(X - 64, Y);
                        correct = true;
                        another = false;
                        break;
                    } else another = true;
                    break;
                }
            }
        }
        //evils[it].setPlayerCordinate(evils[it].getSprite().getPosition().x ,evils[it].getSprite().getPosition().y);
    }
}

void heroIsNear(std::vector<Enemy>& evils,std::vector<Hero>* mans){
 float enemyX,enemyY,heroX,heroY;
    for (auto it = 0; it != evils.size(); it++) {

        if(evils[it].getAgr())
            continue;

        enemyX = evils[it].getCordX();
        enemyY = evils[it].getCordY();

        for(auto j: *mans){
            heroX = j.getCordX();
            heroY = j.getCordY();
            //if(rangeOfAct( enemyX/32,enemyY/32, heroX/32, heroY/32, ((float)evils[it].getView()) )){
              //  evils[it].setAgr(true);
            }

        }

    }



#endif //NIGHTSWORD_AI_H
