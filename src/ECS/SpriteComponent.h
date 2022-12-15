#pragma once
#include <map>
#include <string>
#include "Components.h"
#include "SDL.h"
#include "../Animation.h"
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
    std::map<std::string, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    ~SpriteComponent() = default;

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
    SpriteComponent(std::string id, std::string initId, Animation anim) {
        animated = true;
        setTexture(id);

        animations.emplace(initId, anim);
        Play(initId);
    }

    /**
     * @note reasses this method
     *
     * @param id
     * @param i
     * @param f
     * @param s
     */
    void addAnimation(std::string id, Animation anim){
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
        texture = Game::assets->getTexture(std::move(id));
    }

    /**
     * @todo make way to make abs fram number and shit
     * 
     * @brief update the component: handle animation
     */
    void update() override {
        if(animated && (Game::frameCnt % speed) == 0){
            srcRect.x = srcRect.w * curFrame++;
            srcRect.y = animIndex * transform->height;
            if(curFrame >= frames) curFrame = 0;
        }

        flashing = ((Game::frameCnt - flashOffset) % flashInterval) < flashDuration && ((Game::frameCnt) < flashBegin + (flashInterval*flashReps));

        destRect.x = static_cast<int>(transform->position.x) - Game::camera.x; //TODO: learn: -> or .
        destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    /**
     * @brief draw the component.
     */
    void draw() override {
        if(flashing){
            TextureManager::AddFlash(texture, srcRect, destRect, spriteFlip);
        } else {
            TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
        }
    }

    /**
     * @brief set animation and maintain current frame.
     *
     * @param animName animation to set to currently playing
     */
    void Play(std::string animName) {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
        std::cout << animIndex << std::endl;
    }

    /**
     * @brief set animation from beginning. curFrame = 0
     *
     * @param animName animation to set to currently playing
     */
    void PlayStart(std::string animName) {
        Play(animName);
        curFrame = 0;
    }

    void Flash(int duration, int interval, int reps){ //line up start times
        flashDuration = duration;
        flashInterval = interval;
        flashReps = reps;
        flashBegin = Game::frameCnt;
        flashOffset = Game::frameCnt % flashInterval;
    }

private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    bool animated = false;
    int frames = 0;
    int speed = 10; // game frames per animation frame
    int curFrame = 0;

    int flashDuration = 0;
    int flashInterval = 10;
    int flashReps = 1;
    int flashBegin = 0;
    int flashOffset = 0;

    bool flashing = false;
};

