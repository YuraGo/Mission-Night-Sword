

#include "../characters/characters.h"
#include <gtest/gtest.h>
#include <iostream>
#include "../items/items.h"
#include "../Game/preload.h"




TEST(ClassHero, GetterTest){


    Hero testPlayer;
    testPlayer.setHero("Bob",100,30,5,8,80,1,1);

    Weapon axe(40,5,70,15,"5.56",15,"axe");
    Medkit aid(1,20,"PotionTallRuby",5);
    Ammo bullets("5.56",20,5);

    testPlayer.rukzak.setIt(&axe);
    testPlayer.rukzak.setIt(&bullets);
    testPlayer.rukzak.setIt(&aid);


    EXPECT_EQ(100 , testPlayer.getHP());
    EXPECT_EQ(30 , testPlayer.getMass());
    EXPECT_EQ(80 , testPlayer.getAccuracy());
    EXPECT_EQ(2 , testPlayer.getStep());
    EXPECT_EQ(8 , testPlayer.getView());
    EXPECT_EQ(0 , testPlayer.getCurrentMass());
}

TEST(ClassHero, SetterTest){
    Hero testPlayer;
    testPlayer.setHero("Bob",100,30,5,8,80,1,1);

    testPlayer.setStep(-1);
    EXPECT_EQ(1 , testPlayer.getStep());

    testPlayer.setCurrentMass(5);
    EXPECT_EQ(5 , testPlayer.getCurrentMass());

    testPlayer.setHP(25);
    EXPECT_EQ(75 , testPlayer.getCurrentHP());
    EXPECT_EQ(100 , testPlayer.getHP());

}

TEST(ClassWeapon, Methods){

    Weapon gun(40,5,70,15,"5.56",15,"gun");

    EXPECT_EQ(70 , gun.getAccuracy());
    EXPECT_EQ(15 , gun.getMass());
    EXPECT_EQ(5 , gun.getBullets());
    EXPECT_EQ(40 , gun.getHpChange());
    EXPECT_EQ(15 , gun.getCurrentCapacity());
    EXPECT_EQ(15 , gun.getCapacity());

    gun.setCapacity(10);
    EXPECT_EQ(10 , gun.getCurrentCapacity());
    gun.setCurrentCapacity(5);
    EXPECT_EQ(5 , gun.getCurrentCapacity());

}

TEST(ClassAmmo , Methods){
    Ammo five("5.56",10,5);

    EXPECT_EQ(10, five.getAmmoSize());

    EXPECT_EQ(5 , five.getMass());

    five.setCurrentSize(4);
    EXPECT_EQ(5, five.getMass());

}

TEST(ClassMedkit, Methods){

    Medkit kit(2,50,"PotionTriangularRuby.PNG",10);

    EXPECT_EQ(2 , kit.getAidStep());
    EXPECT_EQ(50, kit.getRegen());
    EXPECT_EQ(10, kit.getMass());

}



TEST(ClassInventory, Method){

    Weapon gun(40,5,70,15,"5.56",15,"gun");
    Ammo five("5.56",10,5);
    Medkit kit(2,50,"PotionTriangularRuby.PNG",10);

    Inventory items;

    items.setIt(&gun);
    items.setIt(&five);
    items.setIt(&kit);

    EXPECT_EQ(3 , items.getIt().size());

    items.throwIt(2);

    EXPECT_EQ(2, items.getIt().size());

    EXPECT_EQ(40 , items.getItOne(0)->getHpChange());

}


int main(int argc,char *argv[]) {
        ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}