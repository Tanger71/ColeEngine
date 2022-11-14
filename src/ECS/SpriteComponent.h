//
// Created by Sawyer Tang on 11/14/22.
//

#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component {
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

public:
    SpriteComponent() = default;
    SpriteComponent(const char* path){
        setTexture(path);
    }

    void setTexture(const char* path){
        texture = TextureManager::LoadTexture(path);
    }

    void init() override {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = srcRect.h = 32;
        destRect.w = destRect.h = 64;

    }

    void update() override {
        destRect.x = transform->position.x; //TODO: learn: -> or .
        destRect.y = transform->position.y;
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }

};
