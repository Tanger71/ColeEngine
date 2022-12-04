#pragma once
#include <SDL_pixels.h>
#include "ECS/ECS.h"



class EntityFactory {
private:
    SDL_Color white;


public:

    EntityFactory();

    void initPlayer(Entity* e, float xpos, float ypos, std::string label);

    void initWorm(Entity* e, float xpos, float ypos, std::string label);

};
