//
// Created by Sawyer Tang on 11/13/22.
//

#include "TextureManager.h"
#include <iostream>


SDL_Texture *TextureManager::LoadTexture(const char* texture, SDL_Renderer *ren) {
    SDL_Surface* tempSurface = IMG_Load(texture);
    std::cout << IMG_GetError() << std::endl;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    std::cout << IMG_GetError() << std::endl;
    SDL_FreeSurface(tempSurface);
    std::cout << IMG_GetError() << std::endl;

    return tex;
}