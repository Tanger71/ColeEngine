#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
#include "SDL_ttf.h"

/**
 * @brief Manager to access and organize assets.
 *
 * @author sawyercoletang
 *
 */
class AssetManager {
public:

    /**
     *
     * @param man Manager
     */
	AssetManager(Manager* man);
	~AssetManager();

    /**
     *
     * @param pos starting position
     * @param vel for direction
     * @param range distance till destroyed
     * @param speed movement speed
     * @param texid ID of texture
     *
     * @note Probably shouldn't be chillin in this class... ill move later
     */
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string texid); //TODO: shouldnt be done here

    /**
     *
     * @param id texture ID
     * @param path asset path
     */
	void addTexture(std::string id, const char* path); // TODO: learn diff between char* and std::string (prob just class vs array)
	SDL_Texture* getTexture(std::string id);

    /**
     *
     * @param id font ID
     * @param path asset path
     * @param fontsize size of font
     */
    void addFont(std::string id, std::string path, int fontsize);
    TTF_Font* getFont(std::string id);

private:

	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
};
