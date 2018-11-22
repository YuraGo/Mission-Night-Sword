////
//// Created by dartmoor on 12.11.18.
////

//#include "graphics.h"


//LevelMap::LevelMap(sf::String* TileMap){
//
//    for(int i = 0; i < H; i++){
//        for(int j = 0; j < W; j++ ){
//
//         if(TileMap[i][j] == '0') {
//             this->infoOfTile[i][j] = false;
//         }
//         else this->infoOfTile[i][j] = true;
//        }
//    }
//
//}
//
//
//void LevelMap::updateTileInfo(std::vector<Hero>* mans, std::vector<Enemy>* evils){
//
//    for(auto it: *mans){
//        int X = (int) (it.sprite.getPosition().x)/32;
//        int Y = (int) (it.sprite.getPosition().y)/32;
//        this->infoOfTile[X][Y] = false;
//    }
//
//    for(auto it: *evils){
//        int X = (int) (it.sprite.getPosition().x)/32;
//        int Y = (int) (it.sprite.getPosition().y)/32;
//        this->infoOfTile[X][Y] = false;
//    }
//
//
//}