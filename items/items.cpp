#include "items.h"
#include <random>




Weapon::Weapon(int Damage,int bullets,int Accuracy, int cap,const std::string& TypeOfAmmo,int Mass,const std::string& Name,sf::String File){

    this->HPchange = Damage;
    this->accuracy = Accuracy;
    this->name = Name;
    this->mass = Mass;
    this->typeOfAmmo = TypeOfAmmo;
    image.loadFromFile(File);
    image.createMaskFromColor(sf::Color(255,0,255,255));
    texture.loadFromImage(image);
    this->sprite.setTexture(texture);
   // this->sprite.setPosition(X,Y);
    this->sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    this->bulletsPerShoot = bullets;
    this->capacity = cap;
    this->currentCapacity = cap;
};

void Weapon::getInfo() {
    std::cout<<"WEAPON-----"<<std::endl;
    std::cout<<"Mass: " <<this->mass       <<std::endl;
    std::cout<<"damage: " <<this->HPchange     <<std::endl;
    std::cout<<"name: " <<this->name       <<std::endl;
    std::cout<<"accuracy: " <<this->accuracy   <<std::endl;
    std::cout<<"typeOfAmmo: " <<this->typeOfAmmo <<std::endl;
}

Ammo::Ammo(const std::string& Type,int Size,int Mass,sf::String File) {
    this->name = Type;
    this->size = Size;
    this->mass = Mass;
    image.loadFromFile(File);
    image.createMaskFromColor(sf::Color(255,0,255,255));
    texture.loadFromImage(image);
    this->sprite.setTexture(texture);
    //this->sprite.setPosition(X,Y);
    this->sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void Ammo::getInfo() {
    std::cout<<"AMMO------"<<std::endl;
    std::cout<<"Mass: " <<this->mass       <<std::endl;
    std::cout<<"Type: " <<this->name       <<std::endl;
    std::cout<<"Size: " <<this->size   <<std::endl;
}

void Ammo::setSize(int change) {
    this->size += change;
}

Medkit::Medkit(int Step, int Regen, int Mass,sf::String File) {
    this->step = Step;
    this->HPchange = Regen;
    this->mass = Mass;
    image.loadFromFile(File);
    image.createMaskFromColor(sf::Color(255,0,255,255));
    texture.loadFromImage(image);
    this->sprite.setTexture(texture);

    //this->sprite.setPosition(X,Y);
    this->sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}
void Medkit::getInfo() {
    std::cout<<"MEDKIT-----"<<std::endl;
    std::cout<<"Mass: " <<this->mass <<std::endl;
    std::cout<<"Regen: " <<this->HPchange<<std::endl;
    std::cout<<"Step: " <<this->step <<std::endl;
}

void Weapon::drawInventory(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3,float X,float Y){

    table.setPosition(X-90,Y+120);
    this->sprite.setPosition(X-85,Y+140);
    text1.setPosition(X - 50, Y + 125 );
    text2.setPosition(X - 50, Y + 145);
    text3.setPosition(X - 50, Y + 165);

    text1.setString("Name: " + this->name + " Damage: " + std::to_string(this->HPchange));
    text2.setString("Type of ammo: "+ this->typeOfAmmo);
    text3.setString("Weight: " + std::to_string(this->mass) + " Clip: " + std::to_string(this->currentCapacity)+ "/" +std::to_string(this->capacity) );

}

void Medkit::drawInventory(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3, float X,float Y){

    table.setPosition(X-90,Y+120);
    this->sprite.setPosition(X-85,Y+140);
    text1.setPosition(X - 50, Y + 125 );
    text2.setPosition(X - 50, Y + 145);
    text3.setPosition(X - 50, Y + 165);

    text1.setString("Regen: " + std::to_string(this->HPchange));
    text2.setString("Weight: " + std::to_string(this->mass));
    text3.setString("Step: " + std::to_string(this->step));
}

void Ammo::drawInventory(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3, float X,float Y){


    table.setPosition(X-90,Y+120);
    this->sprite.setPosition(X-85,Y+140);
    text1.setPosition(X - 50, Y + 125 );
    text2.setPosition(X - 50, Y + 145);
    text3.setPosition(X - 50, Y + 165);

    text1.setString("Type of ammo: " + this->name );
    text2.setString("Weight: " + std::to_string(this->mass));
    text3.setString("Size: " + std::to_string(this->size));

}


Item* Inventory::getItOne(int count){
    int i = 0;
    for(auto it: items){
        if(i == count)
            return it;
        i++;
    }
    return nullptr;
}

