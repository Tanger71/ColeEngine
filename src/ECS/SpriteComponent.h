//
// Created by Sawyer Tang on 11/14/22.
//

#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component {
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    bool animated = false;
    int frames = 0;
    int speed = 100; // the millisecond delay between frames

public:
    SpriteComponent() = default;
    SpriteComponent(const char* path){
        setTexture(path);
    }
    SpriteComponent(const char* path, int nFrames, int mSpeed) {
        animated = true;
        setTexture(path);
        frames = nFrames;
        speed = mSpeed;
    }
    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    void setTexture(const char* path){
        texture = TextureManager::LoadTexture(path);
    }

    void init() override {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
        

    }

    void update() override {
        if (animated) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames); //TODO: understand
        }

        destRect.x = static_cast<int>(transform->position.x); //TODO: learn: -> or .
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }

};
