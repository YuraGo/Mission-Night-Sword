//
// Created by dartmoor on 02.12.18.
//

#include "classGame.h"
#include "preload.h"

void classGame::createHero(std::string file) {
    sf::String f;
    f = "solder.png";
    Hero player1("solder.png",32,32,50,70);
    Hero player2("solder.png",64,64,55,55);
    player1.setHero("Bob",100,30,5,8,80);
    player2.setHero("Silver",100,30,6,10,40);
    mans.push_back(player1);
    mans.push_back(player2);
}

void classGame::createEnemy() {
    Enemy evil("warrior1.png",64,64,55,55);
    evil.setHero("demon",60,0,5,8,100);
    evils.push_back(evil);
    evils.push_back(evil);
    evils.push_back(evil);
    evils.push_back(evil);
}

bool classGame::moveHero(int choiseMan,float X, float Y) {

    bool tileFree = tileInfo(X, Y, &mans,&evils);
    bool lenghOfMove = mans[choiseMan].characterMove(X,Y);

    if( !tileFree || !lenghOfMove || mans[choiseMan].getStep() <= 0){
        return false;
    }else{
        mans[choiseMan].getSprite().setPosition(X,Y); /////////////////////////
        mans[choiseMan].setPlayerCordinate(X, Y);
        mans[choiseMan].setStep(-1);
        return true;
    }

}