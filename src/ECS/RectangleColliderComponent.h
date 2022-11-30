#pragma once
#include <SDL.h>
#include "AbsColliderComponent.h"

class RectangleColliderComponent : public AbsColliderComponent {

public:
    SDL_Rect collider;

    /**
     *
     * @param t tag name of collider for debugging
     */
    RectangleColliderComponent(std::string t) : AbsColliderComponent(t) {
        localR.x = 0;
        localR.y = 0;
        localR.w = 10;
        localR.h = 10;
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
    RectangleColliderComponent(std::string t, int xpos, int ypos, int w, int h) : AbsColliderComponent(t) {
        localR.x = xpos;
        localR.y = ypos;
        localR.w = w;
        localR.h = h;
    }

    void init() override {
        AbsColliderComponent::init();

        collider.x = localR.x + static_cast<int>(transform->position.x);
        collider.y = localR.y + static_cast<int>(transform->position.y);
        collider.w = localR.w;
        collider.h = localR.h;

        destR.w = localR.w;
        destR.h = localR.h;
    }

    /**
     * @brief update the component.
     */
    void update() override {
        AbsColliderComponent::update();

        collider.x = localR.x + static_cast<int>(transform->position.x);
        collider.y = localR.y + static_cast<int>(transform->position.y);
        collider.w = localR.w;
        collider.h = localR.h;

        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
    }

    /**
     * @brief draw the component and clear vector of currently colliding components.
     *
     * @todo change to draw Collider **not** destR
     */
    void draw() override {
        AbsColliderComponent::draw();

        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(Game::renderer, &(destR));
    }

};