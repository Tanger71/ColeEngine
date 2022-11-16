//
// Created by Sawyer Tang on 11/13/22.
//

#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>

class AssetManager; // TODO: Why tho... https://stackoverflow.com/questions/23283080/compiler-error-c4430-missing-type-specifier-int-assumed
class ColliderComponent;

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    bool running() { return isRunning; }
    void render();
    void clean();
    
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;
    static AssetManager* assets;

    enum groupLabels : std::size_t {
        groupMap,
        groupPlayers,
        groupColliders,
        groupProjectiles
    };

private:
    int cnt = 0;
    SDL_Window *window;
};
