#pragma once
#include <map>
#include "Components.h"
#include "SDL.h"
#include "Animation.h"
#include "../TextureManager.h"
#include "../AssetManager.h"

/**
 * @brief Component for handling the sprite of an Entity.
 *
 * @author sawyercoletang
 *
 */
class SpriteComponent : public Component {
public:
    int animIndex = 0;
    std::map<const char*, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    /**
     * @note mby not necessary anymore?
     * @param id asset texture ID to assign to sprite
     */
    SpriteComponent(std::string id){
        animated = false;
        setTexture(id);
    }

    /**
     *
     * @param id asset texture ID to assign to sprite
     * @param initId id of the animation to initialize the sprite with
     * @param initAnim Animation to initialize the sprite with
     */
    SpriteComponent(std::string id, const char* initId, Animation initAnim) {
        animated = true;
        setTexture(id);

        animations.emplace(initId, initAnim);
        Play(initId);
    }
    ~SpriteComponent() {
    }

    /**
     * @note reasses this method
     *
     * @param id
     * @param i
     * @param f
     * @param s
     */
    void addAnimation(const char* id, int i, int f, int s){
        Animation anim = Animation(i, f, s);
        animations.emplace(id, anim);
    }

    /**
     * @brief initialize the component: link to TransformComponent
     */
    void init() override {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    /**
     * @brief set texture ID for Sprite
     *
     * @param id
     */
    void setTexture(std::string id) {
        texture = Game::assets->getTexture(id);
    }

    /**
     * @brief update the component: handle animation
     */
    void update() override {
        if (animated) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames); //TODO: understand
        }

        srcRect.y = animIndex * transform->height;

        destRect.x = static_cast<int>(transform->position.x) - Game::camera.x; //TODO: learn: -> or .
        destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    /**
     * @brief draw the component.
     */
    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

    /**
     *
     * @param animName animation to set to currently playing
     */
    void Play(const char* animName) {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }

private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    bool animated = false;
    int frames = 0;
    int speed = 100; // the millisecond delay between frames
};

