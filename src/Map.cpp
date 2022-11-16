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
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    for (int y = 0; y < sizeY; y++) { // ONLY WORKS WITH TILE SHEETS OF 10 WIDTH
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(c);
            srcY = atoi(&c) * 32;
            mapFile.get(c);
            srcX = atoi(&c) * 32;
            //std::cout << path << " " << x << "," << y << ": " << c << std::endl;
            Game::AddTile(srcX, srcY, x * 64, y * 64);
            mapFile.ignore();
        }
    }

    mapFile.close();
}
