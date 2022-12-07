#pragma once
#include <iostream>
#include "../Components.h"

/**
 * @brief Finite State Automata for Worm Enemy.
 *
 * @author sawyercoletang
 *
 */
class WormFSM : public Component {
private:
    enum WormState : std::size_t {
        WORM_OUT,
        WORM_IN,
        WORM_HIDING_T,
        WORM_EMERGING_T
    };

    int animCount = 0;
    WormState curState;

    RectangleColliderComponent*recCollider;
    CircleColliderComponent *cirCollider;
    SpriteComponent *sprite;

public:

    WormFSM() : curState(WORM_OUT) {}
    ~WormFSM(){}

    void init() override {
        if (!entity->hasComponent<CircleColliderComponent>()) Game::throwErr("missing CircleColliderComponent!");
        if (!entity->hasComponent<RectangleColliderComponent>()) Game::throwErr("missing RectangleColliderComponent!");
        if (!entity->hasComponent<SpriteComponent>()) Game::throwErr("missing SpriteComponent!");

        recCollider = &(entity->getComponent<RectangleColliderComponent>());
        cirCollider = &(entity->getComponent<CircleColliderComponent>());
        sprite = &(entity->getComponent<SpriteComponent>());
    }

    void update() override {
        managerCollisions();
        manageFSM();

    }

    bool isImmune() {
        return curState == WORM_IN;
    }

    void managerCollisions() {
        
        //std::cout << recCollider->colliding.empty() << std::endl;
        if (recCollider->isColliding(Game::groupProjectiles)) {
            //std::cout << "HERE" << std::endl;
            sprite->Flash(2, 10, 3);
        }
    }

    void manageFSM() {
        animCount++;
        switch (curState) {
        case WORM_OUT:
            if (cirCollider->isColliding(Game::groupPlayers)) {
                //std::cout << "Hiding" << std::endl;
                sprite->PlayStart("Hiding");
                curState = WORM_HIDING_T;
                animCount = 0;
            }
            break;
        case WORM_IN:
            if (!cirCollider->isColliding(Game::groupPlayers)) {
                //std::cout << "Emerging" << std::endl;
                sprite->PlayStart("Emerging");
                curState = WORM_EMERGING_T;
                animCount = 0;
            }
            break;
        case WORM_HIDING_T:
            if (animCount > sprite->animations["Hiding"].getDuration() - 1) {
                //std::cout << "In" << std::endl;
                sprite->PlayStart("In");
                curState = WORM_IN;
                animCount = 0;
            }
            break;
        case WORM_EMERGING_T:
            if (animCount > sprite->animations["Emerging"].getDuration() - 1) {
                //std::cout << "Out" << std::endl;
                sprite->PlayStart("Out");
                curState = WORM_OUT;
            }
            break;
        }
    }

};
