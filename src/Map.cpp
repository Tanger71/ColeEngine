#include "Map.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <utility>
#include "ECS/ECS.h"
#include "ECS/Components.h"

extern Manager manager;

Map::Map(std::string tid, int ms, int ts) : texid(std::move(tid)), mapScale(ms), tileSize(ts){

    scaledSize = ms * ts;
}

Map::~Map() = default;

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    //Load Tiles
    for (int y = 0; y < sizeY; y++) { // ONLY WORKS WITH TILE SHEETS OF 10 WIDTH
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(c);
            srcY = atoi(&c) * tileSize;
            mapFile.get(c);
            srcX = atoi(&c) * tileSize;
            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }
    }

    mapFile.ignore();

    //Load Colliders
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(c);
            if (c == '1') {
                auto& tcol(manager.addEntity());
                tcol.addComponent<TransformComponent>(x * scaledSize, y * scaledSize, tileSize, mapScale, 0);
                tcol.addComponent<RectangleColliderComponent>("terrain", 0, 0, scaledSize, scaledSize);
                tcol.addGroup(Game::groupWall);
            }
            mapFile.ignore();
        }
    }

    mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int x, int y) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, x, y, tileSize, mapScale, texid);
    tile.addGroup(Game::groupMap);
}