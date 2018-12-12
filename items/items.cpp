#include "items.h"
#include <random>
#include "../Game/preload.h"





Weapon::Weapon(int Damage,int bullets,int Accuracy, int cap,const std::string& TypeOfAmmo,int Mass,const std::string& Name){
    this->type = 1;
    this->HPchange = Damage;
    this->accuracy = Accuracy;
    this->name = Name;
    this->mass = Mass;
    this->typeOfAmmo = TypeOfAmmo;

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

Ammo::Ammo(const std::string& Type,int Size,int Mass) {
    this->type = 2;
    this->name = Type;
    this->size = Size;
    this->mass = Mass;
    this->HPchange = 0;

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

Medkit::Medkit(int Step, int Regen, const std::string& Name,int Mass) {
    this->type = 3;
    this->name = Name;
    this->step = Step;
    this->HPchange = Regen;
    this->mass = Mass;

}
void Medkit::getInfo() {
    std::cout<<"MEDKIT-----"<<std::endl;
    std::cout<<"Mass: " <<this->mass <<std::endl;
    std::cout<<"Regen: " <<this->HPchange<<std::endl;
    std::cout<<"Step: " <<this->step <<std::endl;
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

