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
 * @notes requires TransformComponent, SpriteComponent, RectangleColliderComponent
 *
 */
class PlayerController : public Controller {
public:
	TransformComponent *transform;
	SpriteComponent* sprite;
    //RectangleColliderComponent* rectCollider;
    HealthComponent* healthComponent;

    bool deadFlag = false;

    PlayerController() : Controller(){}

    /**
     * @brief initialize the component: link to TransformComponent and SpriteComponent.
     */
	void init() override {
		if (!entity->hasComponent<TransformComponent>()) Game::throwErr("missing TransformComponent!");
		if (!entity->hasComponent<SpriteComponent>()) Game::throwErr("missing SpriteComponent!");
        //if (!entity->hasComponent<RectangleColliderComponent>()) Game::throwErr("missing RectangleColliderComponent!");
        if (!entity->hasComponent<HealthComponent>()) Game::throwErr("missing HealthComponent!");


        transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
        //rectCollider = &entity->getComponent<RectangleColliderComponent>();
        healthComponent = &entity->getComponent<HealthComponent>();
	}

    /**
     * @brief update the component: handle key input.
     */
	void update() override {
        manageMovement();
        manageCollisions();
	}

    /**
     * @brief to be called then the entity dies
     */
    void onDeath() override {
        deadFlag = true;
        std::cout << "deathhhhhhh" << std::endl;
        sprite->PlayStart("Death");
    }

    void shootProjectile() {
        if (transform->velocity.Equals(Vector2D(0, 0))) { //TODO: fix cause scuffed
            if (sprite->spriteFlip == SDL_FLIP_HORIZONTAL) {
                Game::entityFactory->mintStoneProjectile(transform->position + Vector2D(16, 16), Vector2D(-1, 0), 200, 3, "playerStone");
            }
            else if (sprite->spriteFlip == SDL_FLIP_NONE) {
                Game::entityFactory->mintStoneProjectile(transform->position + Vector2D(16, 16), Vector2D(1, 0), 200, 3, "playerStone");
            }
        }
        else {
            Game::entityFactory->mintStoneProjectile(transform->position + Vector2D(16, 16), transform->velocity, 200, 3, "playerStone");

        }
    }

    void manageCollisions() {
        //if (rectCollider->isColliding(Game::groupProjectiles)) {}
    }

    void manageMovement(){
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
                    healthComponent->hit(50);
                    break;
                case SDLK_SLASH:
                    Game::debugGame = !Game::debugGame;
                    break;
                case SDLK_UP:
                    Game::entityFactory->mintProjectile( transform->position + Vector2D(16, 32), Vector2D(0, -1), 200, 4, "projectile", "playerBolt");
                    break;
                case SDLK_DOWN:
                    Game::entityFactory->mintProjectile( transform->position + Vector2D(16, 32), Vector2D(0, 1), 200, 4, "projectile", "playerBolt");
                    break;
                case SDLK_RIGHT:
                    Game::entityFactory->mintProjectile( transform->position + Vector2D(16, 32), Vector2D(1, 0), 200, 4, "projectile", "playerBolt");
                    break;
                case SDLK_LEFT:
                    Game::entityFactory->mintProjectile( transform->position + Vector2D(16, 32), Vector2D(-1, 0), 200, 4, "projectile", "playerBolt");
                    break;
                case SDLK_o:
                    shootProjectile();
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
//                case SDLK_SLASH:
//                    Game::debugGame = false;
//                    break;
                default:
                    break;
            }
        }

        //transform->velocity.Unit();
        if (!deadFlag)
        if (transform->velocity.x == 0 && transform->velocity.y == 0) {
            sprite->Play("Idle");
        } else {
            sprite->Play("Walk");
        }
    }
};
