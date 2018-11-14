//
// Created by dartmoor on 12.11.18.
//

#ifndef NIGHTSWORD_PRELOAD_H
#define NIGHTSWORD_PRELOAD_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Graphics/graphics.h"
#include <iostream>
#include "characters/characters.h"
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <sstream>
#include <random>

void tableInfodraw(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3, float X,float Y, Hero* player) {
    table.setPosition(X-270,Y + 65);//-270
    text1.setPosition(X-265,Y + 85);
    text2.setPosition(X-265,Y + 105);
    text3.setPosition(X-265,Y + 125);

    text1.setString("HP: " + std::to_string(player->getHP()) + "  " + "Speed: " + std::to_string(player->getSpeed()));

    text2.setString("Step: " + std::to_string(player->getStep()) +"  " + "Mass: " + std::to_string(player->getMass()));

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



bool tileInfo(float X , float Y, std::vector<Hero>* mans){
    bool check = true;

    if(mans != nullptr){
    for(auto it : *mans){
        if(X == it.sprite.getPosition().x && Y == it.sprite.getPosition().y)
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

bool damageCorrect(float X, float Y,std::vector<Hero> &mans,int Ac) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    if (dist(gen) > Ac) return false;


    for(auto it = 0; it != mans.size(); it++){
        if(X == mans[it].sprite.getPosition().x && Y == mans[it].sprite.getPosition().y) {
            mans[it].setHP(10);
            std::cout<<"?";
            if(mans[it].getHP() <= 0){
                mans[it].setStep(-1000);
                mans.erase(mans.begin() + it);
            }
            break;
        }
    }
    return true;
}


sf::CircleShape& whereGo(sf::CircleShape& radiusOfMove,int speed, float X, float Y){
    //std::cout<<"?"<<std::endl;
    radiusOfMove.setRadius(32*speed);
    radiusOfMove.setPosition(X - 32*speed ,Y - 32*speed);
    //radiusOfMove.setPosition(X  ,Y );
    radiusOfMove.setFillColor(sf::Color(210,210,0,30));
}

//bool pathIsCorrect(float startX, float startY, float X , float Y , int longPath){
//
//    int count=0;
//
//
//    std::cout<<"star cord: "<< startX/32<< " , "<< startY/32 << std::endl;
//    std::cout<<"cord: "<< X/32<< " , "<< Y/32 << std::endl;
//
////    if(MapHelper[x][y] == '0'){
////        std::cout<<"Map111: "<< MapHelper[x][y] << std::endl;
////        std::cout<<"cord111: "<< x << " , "<< y << std::endl;
////        return false;
////    }
//
//
//        while(startX != X || startY != Y ) {
//            //std::cout<<" "<<count <<" ";
//            if(count > longPath)
//                return false;
//
//            if (startX < X) {
//                if (tileInfo(startX + 32, startY, nullptr)) {
//                    startX += 32;
//                    count++;
//                }
//            }
//
//            if (startY < Y) {
//                if (tileInfo(startX, startY + 32, nullptr)) {
//                    count++;
//                    startY += 32;
//                }else if (tileInfo(startX + 32, startY, nullptr)) {
//                    startX += 32;
//                    count++;
//                }
//            }
//        }
//
//
//    if(longPath >= count)
//        return true;
//    else return false;
//
//}

//using namespace std;
//
//bool pathIsCorrect(float startX, float startY, float X , float Y , int longPath){
//
//    vector<pair<float, float> > wave;
//    vector<pair<float, float> > oldWave;
//    oldWave.emplace_back(pair<float, float>(startX/32, startY/32));
//
//    int nstep = 0;
//
//    const float dx[] = { 0, 1, 0, -1 };
//    const float dy[] = { -1, 0, 1, 0 };
//
//    while (oldWave.size() > 0) {
//
//        ++nstep;
//        wave.clear();
//        for (auto i = oldWave.begin(); i != oldWave.end(); ++i)
//        {
//            for (int d = 0; d < 4; ++d)
//            {
//                float nx = i->first + dx[d];
//                float ny = i->second + dy[d];
//                if (mapInt[(int)nx][(int)ny] == 1)
//                {
//                    wave.emplace_back(pair<float, float>(nx, ny));
//                    //mapInt[nx][ny] = nstep;
//                    if (nx == X/32 && ny == Y/32)
//                        goto done;
//
//                }
//            }
//        }
//        oldWave = wave;
//    }
//    done:
////    float x = X;
////    float y = Y;
////    wave.clear();
////    wave.emplace_back(pair<float, float>(x, y));
////    while (mapInt[x][y] != 0)
////    {
////        for (int d = 0; d < 4; ++d)
////        {
////            float nx = x + dx[d];
////            float ny = y + dy[d];
////            if (mapInt[x][y] - 1 == mapInt[nx][ny])
////            {
////                x = nx;
////                y = ny;
////                wave.emplace_back(pair<float, float>(x, y));
////                break;
////            }
////        }
////    }
//    std::cout<<"wave: "<< wave.size() << std::endl;
//    std::cout<<"Oldwave: "<< oldWave.size() << std::endl;
//
//return true;
//}
bool openDoor(float X, float Y, float plX, float plY){
int i=0;
    if(X/32 == 7 && Y/32 == 3) {
        i++;
        return true;
    }
    else return false;
}




#endif //NIGHTSWORD_PRELOAD_H
