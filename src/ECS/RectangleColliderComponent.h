#pragma once
#include <SDL.h>
#include "AbsColliderComponent.h"

/**
 * @brief Component for handling the Rectangle Collider of an Entity.
 *
 * @author sawyercoletang
 *
 */
class RectangleColliderComponent : public AbsColliderComponent {

public:
    SDL_Rect collider, localR, destR;

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
     * @param t tag name of collider
     * @param xpos x positon of collider rectangle top left corner
     * @param ypos y position of collider rectangle top left corner
     * @param w width of collider rectangle
     * @param h height of collider rectangle
     */
    RectangleColliderComponent(std::string t, int xpos, int ypos, int w, int h) : AbsColliderComponent(t) {
        localR.x = xpos;
        localR.y = ypos;
        localR.w = w;
        localR.h = h;
    }

    /**
     * @brief initialize the component: link to TransformComponent.
     */
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
     */
    void draw() override {
        AbsColliderComponent::draw();

        if(!entity->hasGroup(Game::groupDebug) && !Game::debugGame) return;

        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(Game::renderer, &(destR));
        SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
        SDL_RenderDrawPoint(Game::renderer, destR.x, destR.y);
        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 0, 255);
        SDL_RenderDrawPoint(Game::renderer, destR.x + destR.w/2, destR.y + destR.h/2);
    }

};