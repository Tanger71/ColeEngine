#pragma once
#include <SDL.h>
#include "AbsColliderComponent.h"
#include "../Circle.h"

class CircleColliderComponent : public AbsColliderComponent {
public:
    Circle collider, localC, destC;

    /**
     *
     * @param t tag name of collider for debugging
     */
    CircleColliderComponent(std::string t) : AbsColliderComponent(t) {
        localC = Circle(18, 1, 1);
    }

    CircleColliderComponent(std::string t, int xpos, int ypos, int r) : AbsColliderComponent(t){
        localC = Circle(xpos, ypos, r);
    }

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
        AbsColliderComponent::draw();

        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
        Circle::drawCircle(&destC);
    }

};
