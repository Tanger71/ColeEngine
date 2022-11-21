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
 * @brief Component to handle the UILabel of an Entity.
 *
 * @todo add background to label.
 *
 * @author sawyercoletang
 *
 */
class UILabel : public Component {
public:

    /**
     *
     * @param xpos x position of label
     * @param ypos y position of lebel
     * @param text text shown in label
     * @param font font of label
     * @param color color of label font
     */
    UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& color) :
        labelText(text), labelFont(font), textColour(color){
        position.x = xpos;
        position.y = ypos;

        setLabelText(labelText, labelFont);
    }
    ~UILabel(){}

    /**
     *
     * @param text text to set label to
     * @param font font to set label to
     */
    void setLabelText(std::string text, std::string font){
        SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), textColour);
        labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);

        SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
    }

    /**
     * @brief draw the component.
     */
    void draw() override {
        SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
    }

private:
    SDL_Rect position;
    std::string labelText;
    std::string labelFont;
    SDL_Color textColour;
    SDL_Texture* labelTexture;
};
