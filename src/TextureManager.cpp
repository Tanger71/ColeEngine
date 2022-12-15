#include "TextureManager.h"
#include <regex>

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip){
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0.0, nullptr, flip);
}

void TextureManager::AddFlash(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip){
    SDL_SetTextureColorMod(tex, 255, 255, 255);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_ADD);
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0.0, nullptr, flip);
}

SDL_Color TextureManager::hexToColor(std::string hex){
    std::regex pattern("#?([0-9a-fA-F]{2})([0-9a-fA-F]{2})([0-9a-fA-F]{2})");

    std::smatch match;

    if (std::regex_match(hex, match, pattern))
    {
        Uint8 r = std::stoul(match[1].str(), nullptr, 16);
        Uint8 g = std::stoul(match[2].str(), nullptr, 16);
        Uint8 b = std::stoul(match[3].str(), nullptr, 16);

        std::cout << hex << ": r = " << r << ", g = " << g << ", b = " << b << "\n";

        return {r, g, b, 255};
    }
    else
    {
        std::cout << hex << " is an invalid rgb color\n";
        return {0, 0, 0, 0};
    }

}