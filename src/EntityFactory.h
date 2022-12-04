#pragma once
#include <SDL_pixels.h>
#include "ECS/ECS.h"
#include "Vector2D.h"

class EntityFactory {
private:
    Manager* manager;
    SDL_Color white;

public:

    EntityFactory(Manager* man);

    Entity* mintPlayer(float xpos, float ypos, std::string label); //change name

    Entity* mintWorm(float xpos, float ypos, std::string label);

    /**
     *
     * @param pos starting position
     * @param vel for direction
     * @param range distance till destroyed
     * @param speed movement speed
     * @param texid ID of texture
     */
    Entity* mintProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string texid);

};
