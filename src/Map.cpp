//
// Created by Sawyer Tang on 11/13/22.
//

#include "Map.h"
#include "TextureManager.h"

int lvl1[20][25] = {
        {0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0},
};

Map::Map() {
    dirt = TextureManager::LoadTexture("assets/dirt.png");
    grass = TextureManager::LoadTexture("assets/grass.png");
    water = TextureManager::LoadTexture("assets/water.png");

    loadMap(lvl1);

    src.x = src.y = 0;
    src.w = dest.w = 32;
    src.h = dest.h = 32;

    dest.x = dest.y = 0;
}

Map::~Map() {
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(water);
    SDL_DestroyTexture(dirt);
}

void Map::loadMap(int arr[20][25]) {
    for(int i = 0 ; i < 20 ; i++){
        for(int j = 0 ; j < 25 ; j++){
            map[i][j] = arr[i][j];
        }
    }
}

void Map::drawMap() {
    int type = 0;

    for(int i = 0 ; i < 20 ; i++){
        for(int j = 0 ; j < 25 ; j++){
            type = map[i][j];

            dest.x = j * 32;
            dest.y = i * 32;

            switch(type){
                case 0:
                    TextureManager::Draw(water, src, dest);
                    break;
                case 1:
                    TextureManager::Draw(grass, src, dest);
                    break;
                case 2:
                    TextureManager::Draw(dirt, src, dest);
                    break;
                default:
                    break;
            }


        }
    }
}


