#include "items.h"


Weapon::Weapon(int Damage,int Accuracy,int ,std::string TypeOfAmmo,int Mass,std::string Name){
    this->damage = Damage;
    this->accuracy = Accuracy;
    this->name = Name;
    this->mass = Mass;
    this->typeOfAmmo = TypeOfAmmo;
};

void Weapon::getInfo() {
    std::cout<<"Mass: " <<this->mass       <<std::endl;
    std::cout<<"damage: " <<this->damage     <<std::endl;
    std::cout<<"name: " <<this->name       <<std::endl;
    std::cout<<"accuracy: " <<this->accuracy   <<std::endl;
    std::cout<<"typeOfAmmo: " <<this->typeOfAmmo <<std::endl;
}

Ammo::Ammo(std::string Type,int Size,int Mass) {
    this->type = Type;
    this->size = Size;
    this->mass = Mass;
}

void Ammo::setSize(int change) {
    this->size += change;
}

Medkit::Medkit(int Step, int Regen, int Mass) {
    this->step = Step;
    this->regen = Regen;
    this->mass = Mass;
}
