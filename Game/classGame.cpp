//
// Created by dartmoor on 02.12.18.
//

#include "classGame.h"
#include "preload.h"
#include <fstream>
#include <random>

std::string TileMap[16]={
        "000000000000000000000000000000000000000000", //0
        "0                 0                      0", //1
        "0                 0                      0",//2
        "0                 0                      0",//3
        "0                                        0",//4
        "0                                        0",//5
        "0000000000000000000000000D0000000000000000",//6
        "0       0                    0           0",//7
        "0       0                    0           0",//8
        "0       0                00000000        0",//9
        "0       00000000         0               0",//10
        "0       0                0               0",//11
        "0       0                0               0",//12
        "0                                        0",//13
        "0                                        0",//14
        "000000000000000000000000000000000000000000"//15
};


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

bool classGame::openDoor(float X, float Y, float plX, float plY){

    if(X/32 == 25 && Y/32 == 6) {
        if( rangeOfAct(X,Y,plX,plY,32))
            return true;
    }
    return false;
}

bool classGame::tileCheck(float X , float Y, Location* location){
    bool check = true;

    if(location->getCellInfo(X,Y))
        return false;

    int Xi, Yi;
    Xi = (int)X/32;
    Yi = (int)Y/32;

    if(Xi > 40 || Yi > 14 || Xi < 0 || Yi < 0)
        return false;

    if(TileMap[Yi][Xi] == '0')
        return false;

    return check;
}


void classGame::startCord(std::vector<Enemy> &evils,Inventory& item){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distY(1, 15);
    std::uniform_int_distribution<> distX(8, 38);
    float X,Y,Xi,Yi;

    for(auto it = 0;it != evils.size(); it++){
        X = distX(gen)*32;
        Y = distY(gen)*32;

        if(tileInfo(X,Y,nullptr, &evils)) {
            evils[it].setPlayerCordinate(X,Y);
        }
        else it--;
    }

    for(int it = 0;it != item.getIt().size(); it++){

        Xi = distX(gen)*32;
        Yi = distY(gen)*32;

        if(tileInfo(Xi,Yi,nullptr, nullptr)) {
            item.getItOne(it)->setCrd(Xi,Yi);
        }
        else it--;
    }


}


bool classGame::tileInfo(float X , float Y, vector<Hero>* mans, std::vector<Enemy>* evils){
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


    if(lvl[Yi][Xi] == '0')
        return false;

    return check;
}


bool classGame::rangeOfAct(float X, float Y,float anX, float anY,float plus) {
    return ((X - anX)*(X - anX) + (Y - anY) * (Y - anY) ) <= (plus)*(plus);
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

