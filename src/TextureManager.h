//
// Created by Sawyer Tang on 11/13/22.
//

#pragma once

#include "Game.h"

class TextureManager {

public:
    static SDL_Texture* LoadTexture(const char* texture);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};


