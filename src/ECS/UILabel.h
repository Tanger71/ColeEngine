//
// Created by Sawyer Tang on 11/19/22.
//

#pragma once
#include "ECS.h"
#include "../AssetManager.h"
#include "../Game.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component {
public:
    UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& color) :
        labelText(text), labelFont(font), textColour(color){
        position.x = xpos;
        position.y = ypos;

        setLabelText(labelText, labelFont);
    }
    ~UILabel(){}

    void setLabelText(std::string text, std::string font){
        SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), textColour);
        labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);

        SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);

    }

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
