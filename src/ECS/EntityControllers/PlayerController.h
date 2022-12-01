#pragma once
#include "../ECS.h"
#include "../Components.h"
#include "../../Game.h"

/**
 * @brief Component for handling keyboard input.
 *
 * @todo normalize movement vector for top-down movement.
 *		 implement the sum method for direction determination.
 *
 * @author sawyercoletang
 *
 */
class PlayerController : public Component {
public:
	TransformComponent *transform;
	SpriteComponent* sprite;

    /**
     * @brief initialize the component: link to TransformComponent and SpriteComponent.
     */
	void init() override {
		if (!entity->hasComponent<TransformComponent>()) Game::throwErr("missing TransformComponent!");
		if (!entity->hasComponent<SpriteComponent>()) Game::throwErr("missing SpriteComponent!");
		
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

    /**
     * @brief update the component: handle key input.
     */
	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = -1;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
            case SDLK_p:
                sprite->Flash(2, 10, 3);
                break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				if (transform->velocity.y < 0) {
					transform->velocity.y = 0;
				}
				break;
			case SDLK_a:
				if (transform->velocity.x < 0) {
					transform->velocity.x = 0;
				}
				break;
			case SDLK_s:
				if (transform->velocity.y > 0) {
					transform->velocity.y = 0;
				}
				break;
			case SDLK_d:
				if (transform->velocity.x > 0) {
					transform->velocity.x = 0;
				}
				break;
			default:
				break;
			}
		}

		if (transform->velocity.x == 0 && transform->velocity.y == 0) {
			sprite->Play("Idle");
		} else {
			sprite->Play("Walk");
		}

	}
};
