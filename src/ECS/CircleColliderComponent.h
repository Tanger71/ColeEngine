#pragma once
#include <SDL.h>
#include "AbsColliderComponent.h"
#include "../Circle.h"

/**
 * @brief Component for handling the Circle Collider of an Entity.
 *
 * @author sawyercoletang
 *
 */
class CircleColliderComponent : public AbsColliderComponent {
public:
    Circle collider, localC, destC;

    /**
     *
     * @param t tag name of collider for debugging
     */
    CircleColliderComponent(std::string t) : AbsColliderComponent(t) {
        localC = Circle(1, 1, 1);
    }

    /**
     *
     * @param t tag name of collider
     * @param xpos x positon of collider Circle centre
     * @param ypos y positon of collider Circle centre
     * @param r radius of collider Circle
     */
    CircleColliderComponent(std::string t, int xpos, int ypos, int r) : AbsColliderComponent(t){
        localC = Circle(xpos, ypos, r);
    }

    /**
     * @brief initialize the component: link to TransformComponent.
     */
    void init() override {
        AbsColliderComponent::init();

        collider.x = localC.x + static_cast<int>(transform->position.x);
        collider.y = localC.y + static_cast<int>(transform->position.y);
        collider.r = localC.r;

        destC.r = localC.r;
    }

    /**
     * @brief update the component.
     */
    void update() override {
        AbsColliderComponent::update();

        collider.x = localC.x + static_cast<int>(transform->position.x);
        collider.y = localC.y + static_cast<int>(transform->position.y);
        collider.r = localC.r;

        destC.x = collider.x - Game::camera.x;
        destC.y = collider.y - Game::camera.y;
    }

    /**
    * @brief draw the component and clear vector of currently colliding components.
    */
    void draw() override {
        if(isColliding(Game::groupPlayers)){
            SDL_SetRenderDrawColor(Game::renderer, 255, 0, 255, 255);
        }else{
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
        }
        AbsColliderComponent::draw();

        Circle::drawCircle(&destC);

        SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
        SDL_RenderDrawPoint(Game::renderer, destC.x, destC.y);
    }

};
