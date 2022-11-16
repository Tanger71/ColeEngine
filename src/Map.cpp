//
// Created by Sawyer Tang on 11/13/22.
//

#include "Map.h"
#include "Game.h"
#include <fstream>
#include <iostream>

Map::Map() {

}

Map::~Map() {

}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    char tile;
    std::fstream mapFile;
    mapFile.open(path);

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            std::cout << path << " " << x << "," << y << ": " << tile << std::endl;
            Game::AddTile(atoi(&tile), x * 32, y * 32);
            mapFile.ignore();
        }
    }

    mapFile.close();
}
