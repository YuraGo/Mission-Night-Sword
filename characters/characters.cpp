//
// Created by dartmoor on 11.11.18.
//

#include "characters.h"
#include <iostream>
#include <random>
#include "../Game/preload.h"


Hero::Hero(sf::String F, float X, float Y, float W, float H) {
    File = F;//имя файла+расширение
    w = W;
    h = H;//высота и ширина
    image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
    //image.createMaskFromColor(sf::Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
    texture.loadFromImage(image);//закидываем наше изображение в текстуру
    sprite.setTexture(texture);//заливаем спрайт текстурой
    cordX = X;
    cordY = Y;//координата появления спрайта
    sprite.setPosition(cordX,cordY);
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

void Hero::setHero(const std::string &Name, int hp, int Mass, int Speed, int View,int Accuracy){
    this->name = Name;
    this->HP = hp;
    this->currentHP = hp;
    this->currentMass = 0;
    this->mass = Mass;
    this->speed = Speed;
    this->view = View;
    this->accuracy = Accuracy;
    this->step = 2;
}


void Hero::getInfo() {
    std::cout<<"name "<<this->name<<std::endl;
    std::cout<<"HP "<<this->HP<<std::endl;
    std::cout<<"mass "<<this->mass<<std::endl;
    std::cout<<"speed "<<this->speed<<std::endl;
    std::cout<<"View "<<this->view<<std::endl;
    std::cout<<"accuracy "<<this->accuracy<<std::endl;
    std::cout<<"step "<<this->step<<std::endl;
    //std::cout<<"inventory "<<this->inventory<<std::endl;
}



bool Hero::characterMove(float X, float Y,int range) {

    if( (X-this->sprite.getPosition().x)*(X - this->sprite.getPosition().x) +
            (Y - this->sprite.getPosition().y) * (Y - this->sprite.getPosition().y)
    <= ((this->speed+range)*32)*((this->speed+range)*32) ) {
        this->cordX = X;
        this->cordY = Y;
        return true;
    }else return false;

}


std::string Hero::Attack(int countOfInventorySlot, float X, float Y, std::vector<Enemy>& evils) {

    if(this->characterMove(X,Y,2)) {
        if(ammoCheck( this->rukzak,0)) {
            if (damageCorrect(X, Y, evils,( this->getAccuracy() + this->rukzak.getItOne(countOfInventorySlot)->getAccuracy() )/2,
                              this->rukzak.getItOne(countOfInventorySlot)->getHpChange())) {
                this->setStep(-1);
                return ("Damage is" + std::to_string(this->rukzak.getItOne(countOfInventorySlot)->getHpChange()));
            } else {
                this->setStep(-1);
                return ("Miss...");
            }

        } else{
            return ("Not enough ammo...");
        }
    }else {
        return ("Too far...");
    }


}

bool Hero::reload() {

    if(ammoCheck( this->rukzak,1)){
        this->setStep(-1);
        return true;
    }else {
        return false;
    }

}

void Hero::update(float time)
{
//    switch (direction)
//    {
//        case 0: dx = speed; dy = 0; break;
//        case 1: dx = -speed; dy = 0; break;
//        case 2: dx = 0; dy = speed; break;
//        case 3: dx = 0; dy = -speed; break;
//    }

    //cordX += dx*time;
    //cordY += dy*time;

    //speed = 0;
    //sprite.setPosition(x, y);
}


