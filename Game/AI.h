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
        X = evils[it].getSprite().getPosition().x;
        Y = evils[it].getSprite().getPosition().y;

        while(!correct) {
            if (countOfMove == 1 || another) { // down Y+
                X = evils[it].getSprite().getPosition().x;
                Y = evils[it].getSprite().getPosition().y;
                Y += 96;

            while(!correct){
                if (tileInfo(X, Y, mans, &evils) && tileInfo(X, Y - 64, nullptr, nullptr)
                    && tileInfo(X, Y - 32, nullptr, nullptr)) {
                    evils[it].getSprite().setPosition(X, Y);
                    correct = true;
                    another = false;
                    break;
                }
                if (tileInfo(X, Y - 64, nullptr, nullptr) && tileInfo(X, Y - 32, mans,  &evils)) {
                    evils[it].getSprite().setPosition(X, Y - 32);
                    correct = true;
                    another = false;
                    break;
                }
                if (tileInfo(X, Y - 64, mans,  &evils)) {
                    evils[it].getSprite().setPosition(X, Y - 64);
                    correct = true;
                    another = false;
                    break;
                } else another = true;
                break;

            }
            }


            if (countOfMove == 2 || another) { // left X-
                X = evils[it].getSprite().getPosition().x;
                Y = evils[it].getSprite().getPosition().y;
                X -= 96;

                while (!correct) {
                    if (tileInfo(X, Y, mans, &evils) && tileInfo(X + 64, Y, nullptr, nullptr)
                        && tileInfo(X + 32, Y, nullptr, nullptr)) {
                        evils[it].getSprite().setPosition(X, Y);
                        correct = true;
                        another = false;
                        break;
                    }
                    if (tileInfo(X + 64, Y, nullptr, nullptr) && tileInfo(X + 32, Y, mans,  &evils)) {
                        evils[it].getSprite().setPosition(X + 32, Y);
                        correct = true;
                        another = false;
                        break;
                    }
                    if (tileInfo(X - 64, Y, mans,  &evils)) {
                        evils[it].getSprite().setPosition(X + 64, Y);
                        correct = true;
                        another = false;
                        break;

                    } else another = true;
                    break;

                }
            }


            if (countOfMove == 3 || another) { // Up Y+
                X = evils[it].getSprite().getPosition().x;
                Y = evils[it].getSprite().getPosition().y;
                Y -= 96;
                while(!correct) {
                    if (tileInfo(X, Y, mans, &evils) && tileInfo(X, Y + 64, nullptr, nullptr)
                        && tileInfo(X, Y + 32, nullptr, nullptr)) {
                        evils[it].getSprite().setPosition(X, Y);
                        correct = true;
                        another = false;
                        break;

                    }
                    if (tileInfo(X, Y + 64, nullptr, nullptr) && tileInfo(X, Y + 32, mans,  &evils)) {
                        evils[it].getSprite().setPosition(X, Y + 32);
                        correct = true;
                        another = false;
                        break;

                    }
                    if (tileInfo(X, Y + 64, mans,  &evils)) {
                        evils[it].getSprite().setPosition(X, Y + 64);
                        correct = true;
                        another = false;
                        break;
                    } else another = true;
                    break;
                }

            }


            if (countOfMove == 4 || another) { // Right X+
                X = evils[it].getSprite().getPosition().x;
                Y = evils[it].getSprite().getPosition().y;
                X += 96;
                while(!correct) {
                    if (tileInfo(X, Y, mans, &evils) && tileInfo(X - 64, Y, nullptr, nullptr)
                        && tileInfo(X - 32, Y, nullptr, nullptr)) {
                        evils[it].getSprite().setPosition(X, Y);
                        correct = true;
                        another = false;
                        break;
                    }
                    if (tileInfo(X - 64, Y, nullptr, nullptr) && tileInfo(X - 32, Y, mans,  &evils)) {
                        evils[it].getSprite().setPosition(X - 32, Y);
                        correct = true;
                        another = false;
                        break;
                    }
                    if (tileInfo(X - 64, Y, mans,  &evils)) {
                        evils[it].getSprite().setPosition(X - 64, Y);
                        correct = true;
                        another = false;
                        break;
                    } else another = true;
                    break;
                }
            }
        }
        evils[it].setPlayerCordinate(evils[it].getSprite().getPosition().x ,evils[it].getSprite().getPosition().y);
    }
}

void heroIsNear(std::vector<Enemy>& evils,std::vector<Hero>* mans){
 float enemyX,enemyY,heroX,heroY;
    for (auto it = 0; it != evils.size(); it++) {

        if(evils[it].getAgr())
            continue;

        enemyX = evils[it].getSprite().getPosition().x;
        enemyY = evils[it].getSprite().getPosition().y;

        for(auto j: *mans){
            heroX = j.getSprite().getPosition().x;
            heroY = j.getSprite().getPosition().y;
            if(rangeOfAct( enemyX/32,enemyY/32, heroX/32, heroY/32, ((float)evils[it].getView()) )){
                evils[it].setAgr(true);
            }

        }

    }
}


#endif //NIGHTSWORD_AI_H
