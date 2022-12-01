#pragma once
#include "Game.h"

/**
 * @brief Management class to access and organize textures.
 *
 * @author sawyercoletang
 *
 */
class TextureManager {
public:

    /**
     *
     * @param texture path to texture asset
     * @return SDL_Texture object containing texture
     */
    static SDL_Texture* LoadTexture(const char* texture);

    /**
     *
     * @param tex texture to draw
     * @param src source rectangle
     * @param dest destination rectangle
     * @param flip true for flipped
     */
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};
