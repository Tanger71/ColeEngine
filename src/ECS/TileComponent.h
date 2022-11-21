#pragma once
#include "ECS.h"
#include "SDL.h"
#include "../AssetManager.h"

/**
 * @brief Component for Tile attributes of an Entity.
 *
 * @todo no init() ??
 *
 * @author sawyercoletang
 *
 */
class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

    /**
     *
     * @param srcX texture source x position
     * @param srcY texture source y position
     * @param xpos tile x position
     * @param ypos tile y position
     * @param tsize tile size
     * @param tscale tile scale
     * @param id texture ID for tileset
     */
	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id) {
		texture = Game::assets->getTexture(id);

		position.x = static_cast<float>(xpos);
		position.y = static_cast<float>(ypos);
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = tsize;
		srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = tsize * tscale;
		destRect.h = tsize * tscale;
	}
    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }

    /**
     * @brief update the component
     */
	void update() override {
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

    /**
     * @brief draw the component
     */
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};
