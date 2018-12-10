//
// Created by dartmoor on 02.12.18.
//

#include "classGame.h"
#include "preload.h"
#include <fstream>
#include <random>



bool classGame::moveHero(int choiseMan,float X, float Y) {

    bool tileFree = tileInfo(X, Y, &mans,&evils);
    bool lenghOfMove = mans[choiseMan].characterMove(X,Y);

    if( !tileFree || !lenghOfMove || mans[choiseMan].getStep() <= 0){
        return false;
    }else{
        mans[choiseMan].setPlayerCordinate(X, Y);
        mans[choiseMan].setStep(-1);
        return true;
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


Location::Location() {
    std::string name;
    std::ifstream fileMap("maps.txt");

    if (!fileMap)
    {
        std::cout << "File not found\n";
    }

    int it=0;
    while(getline(fileMap, name)) {
        karta[it] = name;
        it++;
    }
    fileMap.close();
}

void Location::clearMap() {
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 42; j++){
            cellInfo[i][j] = false;
        }
    }

}