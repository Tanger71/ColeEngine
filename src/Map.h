#pragma once
#include <string>
#include "Game.h"

/**
 * @brief Object for Game Map.
 *
 * @author sawyercoletang
 *
 */
class Map {
public:

    /**
     * @note currently, only tile sets of width 10 are compatible with this engine.
     *
     * @param tid texture ID for tile sheet
     * @param ms map scale
     * @param ts size of each tile
     */
    Map(std::string tid, int ms, int ts);
    ~Map();

    /**
     *
     * @param path path to tile set asset
     * @param sizeX number of tiles horizontally
     * @param sizeY number of tiles vertically
     */
    void LoadMap(std::string path, int sizeX, int sizeY);

    /**
     *
     * @param srcX tile source rectangle x
     * @param srcY tile source rectangle y
     * @param x tile destination x
     * @param y tile destination y
     */
    void AddTile(int srcX, int srcY, int x, int y);

private:
    std::string texid;
    int mapScale;
    int tileSize;
    int scaledSize;
};
