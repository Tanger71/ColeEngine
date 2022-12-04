#pragma once
#include <SDL_pixels.h>
#include "ECS/ECS.h"
#include "Vector2D.h"

class EntityFactory {
private:
    Manager* manager;
    SDL_Color white{};

public:

    EntityFactory(Manager* man);

    /**
     *
     * @param pos starting position
     * @param label entity debugging label
     * @return ptr to player Entity
     */
    Entity* mintPlayer(Vector2D pos, std::string label); //change name

    /**
     *
     * @param pos starting position
     * @param label entity debugging label
     * @return ptr to Worm Entity
     */
    Entity* mintWorm(Vector2D pos, std::string label);

    /**
     *
     * @param pos starting position
     * @param vel for direction
     * @param range distance till destroyed
     * @param speed movement speed
     * @param texid ID of texture
     * @param label entity debugging label
     * @return ptr to Projectile Entity
     */
    Entity* mintProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string texid, std::string label);

};
