//
// Created by Sawyer Tang on 11/13/22.
//

#pragma once
#include "Game.h"
#include <string>

class Map {
public:
    Map(const char* mfp, int ms, int ts);
    ~Map();

    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int x, int y);

private:
    const char* mapFilePath;
    int mapScale;
    int tileSize;
    int scaledSize;
};
