//
// Created by Sawyer Tang on 11/13/22.
//

#pragma once
#include "Game.h"

class GameObject {

public:
    GameObject(const char* textureSheet, SDL_Renderer* ren, int x, int y);
    ~GameObject();

    void update();
    void render();

private:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;


};


