#pragma once
#include <set>
#include <string>
#include "ECS.h"
#include "../Game.h"
#include "TransformComponent.h"

/**
 * @brief Component for handling Collider Components of an Entity.
 *
 * @author sawyercoletang
 *
 */
class AbsColliderComponent : public Component{
public:
    TransformComponent* transform;

    std::string tag;
    std::set<Game::groupLabels> colliding; // TODO: mby make this bitmap or smth

    /**
     *
     * @param t tag name of collider for debugging
     */
    AbsColliderComponent(std::string t) {
        tag = t;
    }

    /**
     * @brief initialize the component: link to TransformComponent.
     */
    void init() override { //TODO: learn when do use &entity vs entity
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();
    }

    /**
     * @brief update the component.
     */
    void update() override {}

    /**
     * @brief draw the component and clear vector of currently colliding components.
     */
    void draw() override {
        colliding.clear();
    }

    /**
     * @brief add collision label to internal set of intersecting collisions each frame
     *
     * @param g label to be added to set
     */
    void addCollision(Game::groupLabels g) { // const i think
        colliding.insert(g);
    }

    /**
     *
     * @param g label to be check for collision
     * @return true if label is colliding with this collider this frame
     */
    bool isColliding(Game::groupLabels g) { // const i think
        return colliding.count(g) > 0;
    }

};