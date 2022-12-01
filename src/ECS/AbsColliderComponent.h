#pragma once
#include <set>
#include <string>
#include "ECS.h"
#include "../Game.h"
#include "TransformComponent.h"

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

    void addCollision(Game::groupLabels g) { // const i think
        colliding.insert(g);
    }

    bool isColliding(Game::groupLabels g) { // const i think
        return colliding.count(g) > 0;
    }

};