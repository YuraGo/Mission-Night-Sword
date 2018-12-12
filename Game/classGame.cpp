//
// Created by dartmoor on 02.12.18.
//

#include "classGame.h"
#include "preload.h"
#include <fstream>
#include <random>



bool classGame::moveHero(int choiseMan,float X, float Y, Location& location) {

    bool tileFree = location.getCellInfo(X, Y);
    bool lenghOfMove = mans[choiseMan].characterMove(X,Y);

    if( tileFree || !lenghOfMove || mans[choiseMan].getStep() <= 0){
        return false;
    }else{
        location.miniUpdate(mans[choiseMan].getCordX() ,mans[choiseMan].getCordY() , X, Y);
        mans[choiseMan].setPlayerCordinate(X, Y);
        mans[choiseMan].setStep(-1);
        return true;
    }

}

void classGame::heroIsNear() {

    float enemyX,enemyY,heroX,heroY;


    for (auto it = 0; it != evils.size(); it++) {

        if(!evils[it].getAgr())
            continue;

        enemyX = evils[it].getCordX();
        enemyY = evils[it].getCordY();

        for(auto i = 0; i != mans.size(); i++) {

            if (mans[i].getCurrentHP() <= 0) continue;

            heroX = mans[i].getCordX();
            heroY = mans[i].getCordY();

            if (rangeOfMove(heroX, heroY, enemyX, enemyY) > 4096 &&
                rangeOfMove(heroX, heroY, enemyX, enemyY) < 65536) {

                if (tileInfo(heroX + 32, heroY, &mans, &evils)) {
                    evils[it].setPlayerCordinate(heroX + 32, heroY);
                    mans[i].setHP(evils[it].getDamage());
                    break;
                }
                if (tileInfo(heroX - 32, heroY, &mans, &evils)) {
                    evils[it].setPlayerCordinate(heroX - 32, heroY);
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

bool classGame::endGameCheck() {

    int heroHP = 0;
    int enemHP = 0;

    for(auto it: mans){
        heroHP += it.getCurrentHP();
    }


    for(auto it: evils){
        enemHP += it.getCurrentHP();
    }

    return (heroHP <= 0 || enemHP <= 0);

}

void classGame::moveAI(int countOfMove) {

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
                        if (tileInfo(X, Y, &mans, &evils) && tileInfo(X, Y - 64, nullptr, nullptr)
                            && tileInfo(X, Y - 32, nullptr, nullptr)) {
                            evils[it].setPlayerCordinate(X, Y);
                            correct = true;
                            another = false;
                            break;
                        }
                        if (tileInfo(X, Y - 64, nullptr, nullptr) && tileInfo(X, Y - 32, &mans,  &evils)) {
                            evils[it].setPlayerCordinate(X, Y - 32);
                            correct = true;
                            another = false;
                            break;
                        }
                        if (tileInfo(X, Y - 64, &mans,  &evils)) {
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
                        if (tileInfo(X, Y, &mans, &evils) && tileInfo(X + 64, Y, nullptr, nullptr)
                            && tileInfo(X + 32, Y, nullptr, nullptr)) {
                            evils[it].setPlayerCordinate(X, Y);
                            correct = true;
                            another = false;
                            break;
                        }
                        if (tileInfo(X + 64, Y, nullptr, nullptr) && tileInfo(X + 32, Y, &mans,  &evils)) {
                            evils[it].setPlayerCordinate(X + 32, Y);
                            correct = true;
                            another = false;
                            break;
                        }
                        if (tileInfo(X - 64, Y, &mans,  &evils)) {
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
                        if (tileInfo(X, Y, &mans, &evils) && tileInfo(X, Y + 64, nullptr, nullptr)
                            && tileInfo(X, Y + 32, nullptr, nullptr)) {
                            evils[it].setPlayerCordinate(X, Y);
                            correct = true;
                            another = false;
                            break;

                        }
                        if (tileInfo(X, Y + 64, nullptr, nullptr) && tileInfo(X, Y + 32, &mans,  &evils)) {
                            evils[it].setPlayerCordinate(X, Y + 32);
                            correct = true;
                            another = false;
                            break;

                        }
                        if (tileInfo(X, Y + 64, &mans,  &evils)) {
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
                        if (tileInfo(X, Y, &mans, &evils) && tileInfo(X - 64, Y, nullptr, nullptr)
                            && tileInfo(X - 32, Y, nullptr, nullptr)) {
                            evils[it].setPlayerCordinate(X, Y);
                            correct = true;
                            another = false;
                            break;
                        }
                        if (tileInfo(X - 64, Y, nullptr, nullptr) && tileInfo(X - 32, Y, &mans,  &evils)) {
                            evils[it].setPlayerCordinate(X - 32, Y);
                            correct = true;
                            another = false;
                            break;
                        }
                        if (tileInfo(X - 64, Y, &mans,  &evils)) {
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


void AllForSprite::makeSprite(const sf::String& F, float X, float Y, float W, float H) {

    File = F;
    image.loadFromFile(F);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, (int)W,(int)H));

    //heroSprite.push_back(sprite);
    //heroSprite.push_back(sprite);
}

void AllForSprite::makeItemSprite(const sf::String &F,const std::string& Name) {

    name = Name;
    File = F;
    image.loadFromFile(File);
    image.createMaskFromColor(sf::Color(255,0,255,255));
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

}




void Location::clearMap() {
    for(int i = 0; i != 16; i++){
        for(int j = 0; j < 42; j++){
            cellInfo[i][j] = false;
        }
    }
}

void Location::miniUpdate(float x,float y,float prevX, float prevY){
    int Xprev = (int)prevX/32;
    int Yprev = (int)prevY/32;

    int X = (int)x/32;
    int Y = (int)y/32;
    cellInfo[Yprev][Xprev] = false;
    cellInfo[Y][X] = true;
}

