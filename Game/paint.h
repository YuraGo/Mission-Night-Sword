//
// Created by dartmoor on 02.12.18.
//

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../characters/characters.h"

void whereGo(sf::CircleShape& radiusOfMove,int speed, float X, float Y){
    radiusOfMove.setRadius(32*speed);
    radiusOfMove.setPosition(X - 32*speed ,Y - 32*speed);
    radiusOfMove.setFillColor(sf::Color(210,210,0,30));
}


void tableEnemyDraw(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2, float X,float Y, Enemy* player) {
    table.setPosition(X+40,Y) ;//-270
    text1.setPosition(X+45,Y+5);
    text2.setPosition(X+45,Y+23);

    table.setFillColor(sf::Color::Black);
    text1.setFillColor(sf::Color::Yellow);
    text2.setFillColor(sf::Color::Yellow);

    text1.setString("HP: " + std::to_string(player->getCurrentHP()) +"/"+ std::to_string(player->getHP()) + "  Speed: " + std::to_string(player->getSpeed()));

    text2.setString("Step: " + std::to_string(player->getStep()) +"  Accuracy: " + std::to_string(player->getAccuracy()) + " Arg: "+ std::to_string(player->getAgr()));

}

void tableInfodraw(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3, float X,float Y, Hero* player) {
    table.setPosition(X-270,Y + 120);//-270
    text1.setPosition(X-265,Y + 125);
    text2.setPosition(X-265,Y + 144);
    text3.setPosition(X-265,Y + 160);

    text1.setString("HP: " + std::to_string(player->getCurrentHP()) + "/" + std::to_string(player->getHP()) +" " + "Speed: " + std::to_string(player->getSpeed()));

    text2.setString("Step: " + std::to_string(player->getStep()) +"  " + "Mass: " + std::to_string(player->getCurrentMass()) + "/" +std::to_string(player->getMass()));

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

void drawInventory(sf::RectangleShape& table, sf::Text& text1,sf::Text& text2,sf::Text& text3,float X, float Y,Item* item){

    table.setPosition(X-90,Y+120);
    text1.setPosition(X - 50, Y + 125 );
    text2.setPosition(X - 50, Y + 145);
    text3.setPosition(X - 50, Y + 165);
    
    if(item->getType() == 1){
        
    text1.setString("Name: " + item->getName() + " Damage: " + std::to_string(item->getHpChange()));
    text2.setString("Type of ammo: "+ item->getTypeOfAmmo());
    text3.setString("Weight: " + std::to_string(item->getMass()) + " Clip: "
    + std::to_string(item->getCurrentCapacity())+ "/" +std::to_string(item->getCapacity()) );
    
    }
    
    if(item->getType() == 2){

        text1.setString("Type of ammo: " + item->getName() );
        text2.setString("Weight: " + std::to_string(item->getMass()));
        text3.setString("Size: " + std::to_string(item->getAmmoSize()));
        
    }
    
    if(item->getType() == 3){

        text1.setString("Regen: " + std::to_string(item->getHpChange()));
        text2.setString("Weight: " + std::to_string(item->getMass()));
        text3.setString("Step: " + std::to_string(item->getAidStep()));
        
    }
    
}








class AllForSprite{
public:
    sf::String File;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string name;

    void makeSprite(const sf::String& F, float X, float Y, float W, float H) {

        File = F;
        image.loadFromFile(F);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, (int)W,(int)H));

        //heroSprite.push_back(sprite);
        //heroSprite.push_back(sprite);
    }


    void makeItemSprite(const sf::String &F,const std::string& Name) {

        name = Name;
        File = F;
        image.loadFromFile(File);
        image.createMaskFromColor(sf::Color(255,0,255,255));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

    }



};

class Pictures{
public:


    std::vector<AllForSprite> heroSprite;

    std::vector<AllForSprite> itemSprite;

    std::vector<AllForSprite> enemySprite;


};