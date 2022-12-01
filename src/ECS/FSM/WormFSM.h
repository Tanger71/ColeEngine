#pragma once
#include <iostream>
#include "../Components.h"

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

    RectangleColliderComponent *collider;
    SpriteComponent *sprite;

public:

    WormFSM() : curState(WORM_OUT) {}
    ~WormFSM(){}

    void init() override {
        if (!entity->hasComponent<RectangleColliderComponent>()) Game::throwErr("missing RectangleColliderComponent!");
        if (!entity->hasComponent<SpriteComponent>()) Game::throwErr("missing SpriteComponent!");

        collider = &(entity->getComponent<RectangleColliderComponent>());
        sprite = &(entity->getComponent<SpriteComponent>());
    }

    void update() override {
        animCount++;

        //hardcoded timing values
        switch(curState){
            case WORM_OUT:
                if(collider->isColliding(Game::groupPlayers)) {
                    std::cout << "Hiding" << std::endl;
                    sprite->PlayStart("Hiding");
                    curState = WORM_HIDING_T;
                    animCount = 0;
                }
                break;
            case WORM_IN:
                if(!collider->isColliding(Game::groupPlayers)){
                    std::cout << "Emerging" << std::endl;
                    sprite->PlayStart("Emerging");
                    curState = WORM_EMERGING_T;
                    animCount = 0;
                }
                break;
            case WORM_HIDING_T:
                if(animCount > 39){
                    std::cout << "In" << std::endl;
                    sprite->PlayStart("In");
                    curState = WORM_IN;
                    animCount = 0;
                }
                break;
            case WORM_EMERGING_T:
                if(animCount > 39){
                    std::cout << "Out" << std::endl;
                    sprite->PlayStart("Out");
                    curState = WORM_OUT;
                }
                break;
        }
    }

};
