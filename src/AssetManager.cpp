#include "AssetManager.h"

AssetManager::AssetManager(Manager* man) : manager(man) {
}

AssetManager::~AssetManager() = default;

void AssetManager::addTexture(std::string id, const char* path) {
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::getTexture(std::string id) {
	return textures[id];
}

void AssetManager::addFont(std::string id, std::string path, int fontsize){
    fonts.emplace(id, TTF_OpenFont(path.c_str(), fontsize));
}

TTF_Font* AssetManager::getFont(std::string id){
    return fonts[id];
}