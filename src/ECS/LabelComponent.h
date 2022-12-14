//
// Created by Sawyer Tang on 11/19/22.
//

#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "ECS.h"
#include "../AssetManager.h"
#include "../Game.h"

/**
 * @brief Component to handle the LabelComponent of an Entity.
 *
 * @todo add background to label.
 *       fix local positioning of label.
 *
 * @author sawyercoletang
 *
 */
class LabelComponent : public Component {
public:

    /**
     *
     * @param xpos x position of label
     * @param ypos y position of label
     * @param text text shown in label
     * @param font font of label
     * @param color color of label font
     */
    LabelComponent(int xpos, int ypos, std::string text, std::string font, SDL_Color& color) :
        labelText(text), labelFont(font), textColour(color){
        local.x = xpos;
        local.y = ypos;

        setLabelText(labelText, labelFont);
    }
    ~LabelComponent(){}

    /**
     * @brief init the component.
     */
    void init() override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();

        dest.x = transform->position.x + local.x;
        dest.y = transform->position.y + local.y;
    }

    /**
     * @brief update the component.
     */
    void update() override {
        dest.x = transform->position.x + local.x + dest.w/2 - Game::camera.x;
        dest.y = transform->position.y + local.y + dest.h/2 - Game::camera.y;
    }

    /**
     * @brief draw the component.
     */
    void draw() override {
        if(!entity->hasGroup(Game::groupDebug) && !Game::debugGame) return;
        SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &dest);
    }

    /**
     *
     * @param text text to set label to
     * @param font font to set label to
     */
    void setLabelText(std::string text, std::string font){
        SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), textColour);
        labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);

        SDL_QueryTexture(labelTexture, nullptr, nullptr, &dest.w, &dest.h);
    }

private:
    TransformComponent* transform;

    SDL_Rect local;
    SDL_Rect dest;
    std::string labelText;
    std::string labelFont;
    SDL_Color textColour;
    SDL_Texture* labelTexture;
};
