#pragma once
#include <SDL.h>
#include "AbsColliderComponent.h"

class RectangleColliderComponent : public AbsColliderComponent {

public:
    SDL_Rect collider;
    SDL_Rect srcR, destR;

    /**
     *
     * @param t tag name of collider for debugging
     */
    RectangleColliderComponent(std::string t) : AbsColliderComponent(t) {}

    /**
     *
     * @todo add for non-square colliders.
     *
     * @param t tag name of collider for debugging
     * @param xpos x positon of collider
     * @param ypos y position of collider
     * @param size size of collider square
     */
    RectangleColliderComponent(std::string t, int xpos, int ypos, int size) : AbsColliderComponent(t) {
        collider.x = xpos;
        collider.y = ypos;
        collider.w = size;
        collider.h = size;
    }

    void init() override {
        AbsColliderComponent::init();

        tex = TextureManager::LoadTexture("assets/ColTex.png");
        srcR = { 0, 0, 32, 32 };
        destR = {collider.x, collider.y, collider.w, collider.h};
    }

    /**
     * @brief update the component.
     */
    void update() override {
        AbsColliderComponent::update();

        if (tag != "terrain" ) {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }

//        if (tag == "worm" && colliding.count(Game::groupPlayers)) std::cout << "pog" << std::endl;

        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
    }

    /**
     * @brief draw the component and clear vector of currently colliding components.
     */
    void draw() override {
        AbsColliderComponent::draw();
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }

};