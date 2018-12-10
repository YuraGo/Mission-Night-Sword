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

    int Xi, Yi;

    Xi = (int)X/32;
    Yi = (int)Y/32;

    if(Xi > 40 || Yi > 14 || Xi < 0 || Yi < 0)
        return false;


    if(TileMap[Yi][Xi] == '0')
        return false;

    return check;
}

void moveAI(std::vector<Enemy>& evils,std::vector<Hero>* mans,int countOfMove) {
    float X, Y;
    bool another;
    bool correct;
    int demension;

    for (auto it = 0; it != evils.size(); it++) {
        if(evils[it].getAgr()) continue;
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

float rangeOfMove(float X,float Y,float anX,float anY){
    return ((X - anX)*(X - anX) + (Y - anY) * (Y - anY) );
}

void heroIsNear(std::vector<Enemy>& evils,std::vector<Hero>& mans){
 float enemyX,enemyY,heroX,heroY;


    for (auto it = 0; it != evils.size(); it++) {

        if(!evils[it].getAgr())
            continue;

        enemyX = evils[it].getCordX();
        enemyY = evils[it].getCordY();

        for(auto i = 0; i != mans.size(); i++) {
            heroX = mans[i].getCordX();
            heroY = mans[i].getCordY();

            if (mans[i].getCurrentHP() <= 0) continue;

                if (rangeOfMove(heroX, heroY, enemyX, enemyY) > 4096 &&
                    rangeOfMove(heroX, heroY, enemyX, enemyY) < 65536) {

                    if (tileInfo(heroX - 32, heroY, &mans, &evils)) {
                        evils[it].setPlayerCordinate(heroX - 32, heroY);
                        mans[i].setHP(evils[it].getDamage());
                        break;
                    }
                    if (tileInfo(heroX + 32, heroY, &mans, &evils)) {
                        evils[it].setPlayerCordinate(heroX + 32, heroY);
                        mans[i].setHP(evils[it].getDamage());
                        break;
                    }
                    if (tileInfo(heroX, heroY - 32, &mans, &evils)) {
                        evils[it].setPlayerCordinate(heroX, heroY - 32);
                        mans[i].setHP(evils[it].getDamage());
                        break;
                    }
                    if (tileInfo(heroX, heroY + 32, &mans, &evils)) {
                        evils[it].setPlayerCordinate(heroX, heroY + 32);
                        mans[i].setHP(evils[it].getDamage());
                        break;
                    }
                    if (tileInfo(heroX - 32, heroY + 32, &mans, &evils)) {
                        evils[it].setPlayerCordinate(heroX - 32, heroY + 32);
                        mans[i].setHP(evils[it].getDamage());
                        break;
                    }
                    if (tileInfo(heroX + 32, heroY - 32, &mans, &evils)) {
                        evils[it].setPlayerCordinate(heroX + 32, heroY - 32);
                        mans[i].setHP(evils[it].getDamage());
                        break;
                    }
                } else if (rangeOfMove(heroX, heroY, enemyX, enemyY) <= 4096) {

                    mans[i].setHP(evils[it].getDamage());
                    break;
                } else continue;

        }
    }

}



#endif //NIGHTSWORD_AI_H
