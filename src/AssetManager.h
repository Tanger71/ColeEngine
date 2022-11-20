#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
#include "SDL_ttf.h"

class AssetManager {
public:
	AssetManager(Manager* man);
	~AssetManager();

	//gameobjects

	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string texid);

	//texture management
	void addTexture(std::string id, const char* path); // TODO: learn diff between char* and std::string (prob just class vs array)
	SDL_Texture* getTexture(std::string id);

    void addFont(std::string id, std::string path, int fontsize);
    TTF_Font* getFont(std::string id);

private:

	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
};
