//
// Created by Sawyer Tang on 11/13/22.
//

#pragma once
#include "Game.h"
#include <string>

class Map {
public:
    Map();
    ~Map();

    static void LoadMap(std::string path, int sizeX, int sizeY);

};
