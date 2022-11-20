#pragma once
#include "Components.h"
#include "../Vector2D.h"

/**
 * @brief Component to handle the Transform of an Entity.
 *
 * @author sawyercoletang
 *
 */
class TransformComponent : public Component{
public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;

    int speed = 3;

    TransformComponent(){
        position.Zero();
    }

    /**
     *
     * @param sc  scale of Entity
     */
    TransformComponent(int sc) {
        position.x = 400;
        position.y = 320;
        scale = sc;
    }

    /**
     *
     * @param x position of Entity
     * @param y position of Entity
     */
    TransformComponent(float x, float y){
        position.x = x;
        position.y = y;
    }

    /**
     *
     * @param x position of Entity
     * @param y position of Entity
     * @param h height of Entity
     * @param w width of Entity
     * @param sc scale of Entity
     */
    TransformComponent(float x, float y, int h, int w, int sc) {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    /**
     * @brief initialize the component
     */
    void init() override {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }

    /**
     * @brief update the component
     */
    void update() override {
        position.x += velocity.x * (float)speed;
        position.y += velocity.y * (float)speed;
    }
};