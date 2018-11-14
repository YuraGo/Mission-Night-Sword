////
//// Created by dartmoor on 12.11.18.
////
//
//#include "graphics.h"
//
//sfText::sfText(sf::Text text, float X, float Y) {
//
//    this->sourceText.emplace_back(text);
//    this->cordx= X;
//    this->cordy= Y;
//
//}
//
//void sfText::addEL(sf::Text text) {
//    this->sourceText.emplace_back();
//}
//
//void sfText::setXY(float X, float Y) {
//    this->cordx = X;
//    this->cordy = Y;
//}
//
//void sfText::draw(sf::RenderWindow* window) {
//    for(auto it: sourceText)
//        window->draw(it);
//}
//
//void sfText::enter(){
//    this->cordx = 0;
//    this->cordy+=sizeOfSymb;
//
//}