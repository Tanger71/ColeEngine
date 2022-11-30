#pragma once
#include <SDL.h>
#include "AbsColliderComponent.h"

//cleanup and add notes... add more robuestness to rects and stuff.
class RectangleColliderComponent : public AbsColliderComponent {

public:
    SDL_Rect collider;

    /**
     *
     * @param t tag name of collider for debugging
     */
    RectangleColliderComponent(std::string t) : AbsColliderComponent(t) {
        collider.x = 0;
        collider.y = 0;
        collider.w = 0;
        collider.h = 0;
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
    RectangleColliderComponent(std::string t, int xpos, int ypos, int size) : AbsColliderComponent(t) {
        collider.x = xpos;
        collider.y = ypos;
        collider.w = size;
        collider.h = size;
    }

    void init() override {
        AbsColliderComponent::init();

        tex = TextureManager::LoadTexture("assets/ColTex.png");
        AbsColliderComponent::srcR = { 0, 0, 32, 32 };
        AbsColliderComponent::destR = {collider.x, collider.y, collider.w, collider.h};
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

            AbsColliderComponent::destR.x = collider.x - Game::camera.x;
            AbsColliderComponent::destR.y = collider.y - Game::camera.y;


    }

    //fix later
    SDL_Rect getColliderRect(){
        SDL_Rect rect;
        rect.x = collider.x;
        rect.y = collider.y;
        rect.w = collider.w;
        rect.h = collider.h;
        return rect;
    }

    /**
     * @brief draw the component and clear vector of currently colliding components.
     *
     * @todo change to draw Collider **not** destR
     */
    void draw() override {
        AbsColliderComponent::draw();
//        TextureManager::Draw(tex, AbsColliderComponent::srcR, AbsColliderComponent::destR, SDL_FLIP_NONE);
//        if (tag == "player") {
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
            //std::cout <<  destR.x << std::endl;
            SDL_RenderDrawRect(Game::renderer, &(AbsColliderComponent::destR));
//        }


    }

};