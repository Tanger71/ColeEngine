#pragma once

#include <SDL_pixels.h>
#include <SDL_rect.h>
#include "ECS.h"
#include "../Game.h"
#include "TransformComponent.h"

/**
 * @brief Component to handle the HealthComponent of an Entity.
 *
 * @author sawyercoletang
 *
 * @todo:doxygen
 *
 */
class HealthComponent : public Component {
public:
    HealthComponent(int tot, int size) : totalHP(tot), currentHP(tot), lengthHealthBar(size) {}

    ~HealthComponent() = default;

    /**
     * @brief init the component.
     */
    void init() override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();

        emptyBar = SDL_Rect();
        fullBar = SDL_Rect();
        emptyBar.x = static_cast<int>(transform->position.x);
        emptyBar.y = static_cast<int>(transform->position.y) - 20;
        emptyBar.w = lengthHealthBar;
        emptyBar.h = heightHealthBar;
        fullBar.x = static_cast<int>(transform->position.x);
        fullBar.y = static_cast<int>(transform->position.y) - 20;
        fullBar.w = lengthHealthBar;
        fullBar.h = heightHealthBar;
    }

    /**
     * @brief update the component.
     */
    void update() override {
        emptyBar.x = static_cast<int>(transform->position.x) - Game::camera.x;
        emptyBar.y = static_cast<int>(transform->position.y) - 10 - Game::camera.y;

        fullBar.x = static_cast<int>(transform->position.x) - Game::camera.x;
        fullBar.y = static_cast<int>(transform->position.y) - 10 - Game::camera.y;

        fullBar.w = (currentHP/totalHP)*lengthHealthBar;
        fullBar.h = heightHealthBar;
    }

    /**
     * @brief draw the component.
     */
    void draw () override {
        SDL_SetRenderDrawColor(Game::renderer, colorEmpty.r, colorEmpty.g, colorEmpty.b, colorEmpty.a);
        SDL_RenderFillRect(Game::renderer, &(emptyBar));

        SDL_SetRenderDrawColor(Game::renderer, colorFull.r, colorFull.g, colorFull.b, colorFull.a);
        SDL_RenderFillRect(Game::renderer, &(fullBar));
    }

    int heal(int points){
        if(points + currentHP > totalHP){
            currentHP = totalHP;
            return totalHP;
        }
        currentHP += points;
        return currentHP;
    }

    int hit(int points){
        if(points >= currentHP){
            death();
            currentHP = 0;
            return 0;
        }
        currentHP -= points;
        return currentHP;
    }

    void death(){

    }

private:
    TransformComponent* transform;

    float totalHP = 100;
    float currentHP = 100;

    int lengthHealthBar = 100;
    int heightHealthBar = 8;

    SDL_Rect emptyBar;
    SDL_Rect fullBar;

    SDL_Color colorEmpty = {255, 0, 0, 255};
    SDL_Color colorFull = {0, 255, 0, 255};

};