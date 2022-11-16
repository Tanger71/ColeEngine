//
// Created by Sawyer Tang on 11/13/22.
//

#pragma once
#include "Game.h"
#include <string>

class Map {
public:
    Map(std::string tid, int ms, int ts);
    ~Map();

    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int x, int y);

private:
    std::string texid;
    int mapScale;
    int tileSize;
    int scaledSize;
};
