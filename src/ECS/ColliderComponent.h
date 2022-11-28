#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

/**
 * @brief Component to handle the Collider(s) of an Entity.
 *
 * @todo add different shapes and support for multiple colliders.
 *
 * @author sawyercoletang
 *
 */
class ColliderComponent : public Component {
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	TransformComponent* transform;


    /**
     *
     * @param t tag name of collider for debugging
     */
	ColliderComponent(std::string t) {
		tag = t;
	}

    /**
     *
     * @todo add for non-square colliders.
     *
     * @param t tag name of collider for debugging
     * @param xpos x positon of collider
     * @param ypos y position of collider
     * @param size size of collider square
     */
	ColliderComponent(std::string t, int xpos, int ypos, int size) {
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.w = size;
		collider.h = size;
	}

    /**
     * @brief initialize the component: link to TransformComponent.
     */
	void init() override { //TODO: learn when do use &entity vs entity
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("assets/ColTex.png");
		srcR = { 0, 0, 32, 32 };
		destR = {collider.x, collider.y, collider.w, collider.h};
	}

    /**
     * @brief update the component.
     */
	void update() override {
		if (tag != "terrain") {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
		
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;
	}

    /**
     * @brief draw the component.
     */
	void draw() override {
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}

};
