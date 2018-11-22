//
// Created by dartmoor on 11.11.18.
//

#ifndef NIGHTSWORD_ITEMS_H
#define NIGHTSWORD_ITEMS_H



#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



class Item{
protected:

public:
    virtual void getInfo(){std::cout<<"nothing"<<std::endl;};

    virtual sf::Sprite& getSprite(){sf::Sprite p; return p;};

    virtual void drawInventory(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3,float,float){};
};


class Weapon: public Item {
protected:
    std::string name;
    int damage;
    int accuracy;
    std::string typeOfAmmo;
    int mass;
    sf::String File;
    sf::Image image;//сфмл изображение
    sf::Texture texture;//сфмл текстура
    sf::Sprite sprite;
public:
    sf::Sprite& getSprite(){ return this->sprite;};

    Weapon(int,int, const std::string&,int,const std::string&,sf::String);

    void getInfo();

    void drawInventory(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3,float, float);
};

class Ammo : public Item{
protected:
    std::string type;
    int size;
    int mass;
    sf::String File;
    sf::Image image;//сфмл изображение
    sf::Texture texture;//сфмл текстура
    sf::Sprite sprite;
public:
    Ammo(const std::string&, int, int,sf::String);

    sf::Sprite& getSprite(){ return this->sprite;};

    void setSize(int change);

    void getInfo();

    void drawInventory(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3,float,float);
};

class Medkit: public Item {
protected:
    int mass;
    int regen;
    int step;
    sf::String File;
    sf::Image image;//сфмл изображение
    sf::Texture texture;//сфмл текстура
    sf::Sprite sprite;

public:
    Medkit(int,int,int,sf::String);

    void getInfo();

    sf::Sprite& getSprite(){ return sprite;};

    void drawInventory(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3, float ,float );
};



class Inventory{
protected:
    ///// Наследовать все класса предметов и хранить тут указатели

    std::vector<Item*> items;
    //items.push_back(&medkit);
public:

    const std::vector<Item*>& getIt() const{ return items; };

    Item* getItOne(int);

    void setIt(Item* some){this->items.push_back(some);};

    void throwIt(int index){ this->items.erase(items.begin() + index);};

};


#endif //NIGHTSWORD_ITEMS_H


