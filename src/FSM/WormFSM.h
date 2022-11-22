#pragma once
#include "FSMs.h"
#include "../Collision.h"

#include <iostream>

/**
 * @todo figure out OOP in C++ LOL
 */
class WormFSM : public Component {
private:
    enum WormState : std::size_t {
        WORM_OUT,
        WORM_IN,
        WORM_HIDING,
        WORM_EMERGING
    };

    int animCount = 0;
    WormState curState;
    ColliderComponent *collider;
    SpriteComponent *sprite;

    //tempvar
    bool stimulus = false;

public:

    WormFSM() : curState(WORM_OUT) {}
    ~WormFSM(){}

    void init() override {
        collider = &entity->getComponent<ColliderComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {
        animCount++;
//        std::cout << animCount << std::endl;
//        bool stimulus = false;
        //temp for testing
        if(Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_p){
//            std::cout << true << std::endl;
            stimulus = true;
        }else if (Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_o){
//            std::cout << false << std::endl;
            stimulus = false;
        }

        //hardcoded timing values
        switch(curState){
            case WORM_OUT:
                if(stimulus){
                    std::cout << "Hiding" << std::endl;
                    sprite->Play("Hiding");
                    curState = WORM_HIDING;
                    animCount = 0;
                }
                break;
            case WORM_IN:
                if(!stimulus){
                    std::cout << "Emerging" << std::endl;
                    sprite->Play("Emerging");
                    curState = WORM_EMERGING;
                    animCount = 0;
                }
                break;
            case WORM_HIDING:
                if(animCount > 46){
                    std::cout << "In" << std::endl;
                    sprite->Play("In");
                    curState = WORM_IN;
                    animCount = 0;
                }
                break;
            case WORM_EMERGING:
                if(animCount > 46){
                    std::cout << "Out" << std::endl;
                    sprite->Play("Out");
                    curState = WORM_OUT;
                }
                break;
        }
    }

};
